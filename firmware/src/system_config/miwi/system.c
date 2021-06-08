/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/

#include "system.h"
#include "system_config.h"


//CONFIGURATION PARAMETERS

#pragma config FNOSC = PRI
#pragma config POSCMOD = XT
#pragma config JTAGEN = OFF
#pragma config FWDTEN = OFF
#pragma config WDTPS = PS1024


/*********************************************************************
 * Function:        void SYSTEM_Initialize( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Board is initialized for P2P usage
 *
 * Overview:        This function configures the board
 *
 * Note:            This routine needs to be called before the function
 *                  to initialize P2P stack or any other function that
 *                  operates on the stack
 ********************************************************************/

void SYSTEM_Initialize(void)
{

   
    #if defined(MRF24J40)
        PHY_CS_TRIS = 0;
        PHY_CS = 1;
        PHY_RESETn_TRIS = 0;
        PHY_RESETn = 1;
    #endif

    RF_INT_TRIS = 1;

    SDI_TRIS = 1;
    SDO_TRIS = 0;
    SCK_TRIS = 0;
    SPI_SDO = 0;
    SPI_SCK = 0;

        PHY_WAKE_TRIS = 0;
        PHY_WAKE = 1;    

    #if defined(HARDWARE_SPI)
        SPI1CON1 = 0b0000000100111110;
        SPI1STAT = 0x8000;

        SPI2CON1 = 0b0000000100111110;
        SPI2STAT = 0x8000;
    #endif

    #if defined(ENABLE_NVM)
    EE_nCS_TRIS = 0;
    EE_nCS = 1;
    #endif

    #if defined (ENABLE_NVM_MAC)
    MAC_nCS_TRIS = 0;
    MAC_nCS = 1;
    #endif

    RFIF = 0;
    if(RF_INT_PIN == 0){
        RFIF = 1;
    }
}


