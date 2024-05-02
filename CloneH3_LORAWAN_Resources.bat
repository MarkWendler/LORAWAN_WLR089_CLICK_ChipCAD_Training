:: get Harmony ressources for LORAWAN H3 stack
:: Use this line to set the target location
set H3_INSTALL="../H3"
::
set H3_GITHUB="https://github.com/Microchip-MPLAB-Harmony"


git clone -b "v3.10.0"              %H3_GITHUB%/csp.git  %H3_INSTALL%/csp 
git clone -b "v3.10.0"              %H3_GITHUB%/core.git %H3_INSTALL%/core    
git clone -b "v3.10.0"              %H3_GITHUB%/dev_packs.git %H3_INSTALL%/dev_packs
git clone -b "v3.9.2"               %H3_GITHUB%/net.git %H3_INSTALL%/net
git clone -b "v4.7.0"               %H3_GITHUB%/wolfssl.git %H3_INSTALL%/wolfssl
git clone -b "v3.7.1"               %H3_GITHUB%/crypto.git %H3_INSTALL%/crypto     

git clone -b "v3.3.2"                https://github.com/MicrochipTech/cryptoauthlib %H3_INSTALL%/cryptoauthlib

pause

