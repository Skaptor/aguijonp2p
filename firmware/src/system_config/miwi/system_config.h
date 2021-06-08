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

#include "miwi_config.h"          //MiWi Application layer configuration file
#include "miwi_config_p2p.h"      //MiWi Protocol layer configuration file
#include "config_24j40.h"         //Tranceiver configuration file


#define USE_EXTERNAL_EEPROM


//Transceiver Configuration
#define RFIF                        IFS1bits.INT1IF
#define RFIE                        IEC1bits.INT1IE
#define PHY_CS                      LATBbits.LATB2
#define PHY_CS_TRIS                 TRISBbits.TRISB2
#define PHY_RESETn                  LATGbits.LATG2
#define PHY_RESETn_TRIS             TRISGbits.TRISG2
#define RF_INT_PIN                  PORTEbits.RE8
#define RF_INT_TRIS                 TRISEbits.TRISE8
#define PHY_WAKE                    LATGbits.LATG3
#define PHY_WAKE_TRIS               TRISGbits.TRISG3

#define SPI_SDI                     PORTFbits.RF8
#define SDI_TRIS                    TRISFbits.TRISF8
#define SPI_SDO                     LATFbits.LATF8
#define SDO_TRIS                    TRISFbits.TRISF8
#define SPI_SCK                     LATFbits.LATF8
#define SCK_TRIS                    TRISFbits.TRISF8

// Define SUPPORT_TWO_SPI if external EEPROM use the second SPI
// port alone, not sharing SPI port with the transceiver
#define SUPPORT_TWO_SPI

// External EEPROM SPI chip select pin definition
#define EE_nCS_TRIS                 TRISDbits.TRISD12
#define EE_nCS                      LATDbits.LATD12

// MAC_EEPROM 
#define MAC_nCS                     LATFbits.LATF1
#define MAC_nCS_TRIS                 TRISFbits.TRISF1

#define TMRL TMR2



#endif	/* SYSTEM_CONFIG_H */

