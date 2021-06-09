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

#ifndef SYSTEM_CONFIG_H
#define	SYSTEM_CONFIG_H

#include "../../lib/bsp.h"
#include "../../lib/24LC01.h"
#include "miwi_config.h"          //MiWi Application layer configuration file
#include "miwi_config_p2p.h"      //MiWi Protocol layer configuration file
#include "config_24j40.h"         //Tranceiver configuration file

#define USE_EXTERNAL_EEPROM

#define RFIF                        IFS1bits.INT1IF
#define RFIE                        IEC1bits.INT1IE
#define PHY_CS                      LATDbits.LATD8
#define PHY_CS_TRIS                 TRISDbits.TRISD8
#define PHY_RESETn                  LATDbits.LATD9
#define PHY_RESETn_TRIS             TRISDbits.TRISD9
#define RF_INT_PIN                  PORTDbits.RD15
#define RF_INT_TRIS                 TRISDbits.TRISD15
#define PHY_WAKE                    LATDbits.LATD11
#define PHY_WAKE_TRIS               TRISDbits.TRISD11
#define SPI_SDI                     PORTFbits.RF5
#define SDI_TRIS                    TRISFbits.TRISF5
#define SPI_SDO                     PORTFbits.RF2
#define SDO_TRIS                    TRISFbits.TRISF2
#define SPI_SCK                     PORTFbits.RF4
#define SCK_TRIS                    TRISFbits.TRISF4

//#define EE_nCS_TRIS                 int x123
//#define EE_nCS                      int x456
//
//#define MAC_nCS                     int x789
//#define MAC_nCS_TRIS                int x987

#define TMRL TMR2



#endif	/* SYSTEM_CONFIG_H */

