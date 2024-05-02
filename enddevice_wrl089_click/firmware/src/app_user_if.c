/* **************************************************************************
 User interface application

 @Summary
 Handling buttons and LEDs on the board


*******   Section: Included Files   *********/
#include "config/default/peripheral/port/plib_port.h"
#include "config/default/MLS/services/sw_timer/sw_timer.h"


#define LED1_PIN      PORT_PIN_PA18
#define LED2_PIN      PORT_PIN_PA19
#define LED3_PIN      PORT_PIN_PA27

#define LED1_ON()     PORT_PinSet(LED1_PIN)
#define LED1_OFF()    PORT_PinClear(LED1_PIN)
#define LED1_TOGGLE() PORT_PinToggle(LED1_PIN)

#define LED2_ON()     PORT_PinSet(LED2_PIN)
#define LED2_OFF()    PORT_PinClear(LED2_PIN)
#define LED2_TOGGLE() PORT_PinToggle(LED2_PIN)

#define LED3_ON()     PORT_PinSet(LED3_PIN)
#define LED3_OFF()    PORT_PinClear(LED3_PIN)
#define LED3_TOGGLE() PORT_PinToggle(LED3_PIN)

#define K1_PIN PORT_PIN_PA28

#define K1_STATE() PORT_PinRead(K1_PIN)

typedef enum
{
    /* Application's state machine's initial state. */
    USERIF_STATE_INIT=0,
    USERIF_SERVICE_TASKS,
    USERIF_STATE_K1_TRIGGERED,

} USERIF_STATES;

USERIF_STATES userIfState = USERIF_STATE_INIT, userIfStatePrevious;
uint8_t ucMyTimerID;

/********   Section: Local Functions  *********/

static void PIN28_ExternalIntCallback(void);
int buttonPressHandle(void);
void printArrayU8HEX(uint8_t *array, uint8_t length);
/********   Section: Interface Functions  *********/

void APP_UserIf_PostTask(void){
    SYSTEM_PostTask(APP_USER_IF_ID);
    
        if (SwTimerStart(ucMyTimerID,
                MS_TO_US(1000),
                SW_TIMEOUT_RELATIVE,
                APP_UserIf_PostTask,
                NULL) != LORAWAN_SUCCESS) {
                printf("Failed to restart periodic timer for APP_User_If\r\n");
        }    
}


/* *****************************************************************************
 Summary:
 Initializes the user interface application.

 Description:
 This function initializes the user interface application and all its variables
 and modules.

 */
void APP_UserIfInit(void){
    // Initialize LED1 and LED2 PA18 and PA19 
    PORT_PinGPIOConfig(LED1_PIN);
    PORT_PinGPIOConfig(LED2_PIN);
    PORT_PinGPIOConfig(LED3_PIN);
    PORT_PinOutputEnable(LED1_PIN);
    PORT_PinOutputEnable(LED2_PIN);
    PORT_PinOutputEnable(LED3_PIN);
    
    // Initialize K1 PA28
    PORT_PinGPIOConfig(K1_PIN);
    PORT_PinInputEnable(K1_PIN);
    PORT_PinWrite(K1_PIN, true);//Enable pull-up
    //K1 - input enable & pull enable
	PORT_REGS->GROUP[0].PORT_PINCFG[28]= 0b0111;
    
    EIC_CallbackRegister(EIC_PIN_8, (EIC_CALLBACK)PIN28_ExternalIntCallback, (uintptr_t)NULL);
    EIC_InterruptEnable(EIC_PIN_8);
    
    if( SwTimerCreate(&ucMyTimerID)!= LORAWAN_SUCCESS) {
			printf("Failed to create SW timer for APP_User_If\r\n");
	}
    else{
    
        if (SwTimerStart(ucMyTimerID,
                MS_TO_US(1000),
                SW_TIMEOUT_RELATIVE,
                APP_UserIf_PostTask,
                NULL) != LORAWAN_SUCCESS) {
                printf("Failed to start periodic timer for APP_User_If\r\n");
        }
    }

}

/* *****************************************************************************
 Summary:
 Tasks the user interface application. Handles button presses and LoRaWANdemosend message call.

 Description:
 This has a state machine that handles the button presses and LoRaWANdemosend message call.

 */
SYSTEM_TaskStatus_t APP_UserIfTask(void)
{
    switch(userIfState)
    {
        case APP_STATE_INIT:
        {
            APP_UserIfInit();
            userIfState = USERIF_SERVICE_TASKS;
            //printf("APP_USER_IF INITIALIZED\r\n");
            break;
        }

        case USERIF_SERVICE_TASKS:
        {
            SERCOM3_USART_Write("U", 1);//SERCOM3_USART_Write(0xAA, 1);
            
            if(K1_STATE() == 0)
            {
                printf("Button ON\r\n");
            }
            else
            {
                
            }
            
            break;
        }
        
        case USERIF_STATE_K1_TRIGGERED:
            buttonPressHandle();
            userIfState = USERIF_SERVICE_TASKS; //return to prev state stored in the K1 interrupt
            break;

        default:
        {
          //userIfState = USERIF_STATE_INIT;
            break;
        }
    }
    
    return SYSTEM_TASK_SUCCESS;

}



int buttonPressHandle(void){
    LED3_ON();
    printf("Button K1 PA28 pressed. Interrupt callback executing...\r\n");
    LorawanStatus_t lwstat;

    LORAWAN_GetAttr(LORAWAN_STATUS, NULL, &lwstat);

    if (!lwstat.networkJoined)
    {
        printf("Could not send message, LORAWAN is not joined\r\n");
    }
    else{ //LORAWAN connected so send mock GPS signal
        printf("Sending message...\r\n");
    
        DEMO_SendMessage();

   LED3_OFF();     
    }
    return 0;
}

static void PIN28_ExternalIntCallback(void){
    userIfStatePrevious = userIfState;
    userIfState = USERIF_STATE_K1_TRIGGERED;
}

void printArrayU8HEX(uint8_t *array, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++)
    {
        printf("%02X", *array);
        array++;
    }
    printf("\r\n");
}


/* *****************************************************************************
 End of File
 */
