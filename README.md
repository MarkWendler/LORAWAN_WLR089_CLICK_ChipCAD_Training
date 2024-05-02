# WLR089-click_LORAWAN_H3 End device demo
This repo containing a simplified demo from Microchip official LORAWAN stack repo.
https://github.com/MicrochipTech/ATSAMR34_LORAWAN_H3

Harmony 3 configurator does not work with this project. The original project is based on Harmony 3 framework, then modified manually to add sercom3 and make it compatible with new compiler and WLR089.

Target board WLR089-click from ChipCAD Ltd. (https://www.chipcad.hu/)
![Alt text](resources/wlr089_click_main.png)

1. Download and install [MPLAB® X IDE v6.15 tested](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide)
2. Download and install [MPLAB XC32 Compiler v4.35 tested](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-xc-compilers)
3. Clone this repo
4. Connect HW to EDBG-USB (on board programmer/debugger)
5. Build and Program the device from MPLAB X IDE under **Production -> Make and Program Device**
6. LED2 (GREEN) should start to blink with 1 Hz after programming is succesful
7. Connect to the virtual com port with a serial communication program (EDBG-USB built-in USB-UART functionality) 
   1.  115200-8-N-1 
8. Observe the output on the terminal


```
Last reset cause: External Reset

Microchip LoRaWAN Stack - MLS v2.0.0

Init - Successful


 1. Demo application
 2. Enable/disable Certification mode

Enter your choice:
```

> Note #1: Checkout the [SAM R34 MLS Getting Started Guide](https://www.microchip.com/en-us/product/ATSAMR34J18#document-table) to get details on the application flow.

</br>

> Note #2: If using ATECC608 as crypto companion for the Join process, checkout the following resources to get more details :
> - [Develop with the SAM R34 LoRa SiP and WLR089U0 Module with Microchip LoRaWAN stack on TTI join server](https://github.com/MicrochipTech/atsamr34_ecc608a_tti)
> - [Develop with the SAM R34 LoRa SiP and WLR089U0 Module with Microchip LoRaWAN stack on Actility join server](https://github.com/MicrochipTech/atsamr34_ecc608a_actility)
> - [Secure Authentication with SAMR34 & ATECC608 and The Things Industries’s Join Server](https://github.com/MicrochipTech/secure_lorawan_with_tti)


