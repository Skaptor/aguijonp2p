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

#include <stdio.h>
#include "system.h"
#include "system_config.h"
#include "delay.h"
#include "demo_output.h"
#include "driver/mrf_miwi/drv_mrf_miwi.h"


/*************************************************************************/
// the following two variable arrays are the data to be transmitted
// in this demo. They are bit map of English word "MiWi" and "DE"
// respectively.
/*************************************************************************/
const uint8_t MiWi[6][21] =
{
    {0x20,0xB2,0x20,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0x20,0x20,0xB2,0x20,0xB2,0x0D,0x0A},
    {0xB2,0x20,0xB2,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0x20,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0xB2,0x20,0x20,0xB2,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0xB2,0x0D,0x0A},
    {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0D,0x0A}
    
};   

const uint8_t DE[6][11] =
{
    {0xB2,0xB2,0xB2,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0xB2,0xB2,0xB2,0xB2,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0x0D,0x0A},
    {0xB2,0xB2,0xB2,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x0D,0x0A},
    {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0D,0x0A}
}; 


#define DEBOUNCE_TIME 0x00003FFF

bool PUSH_BUTTON_pressed;
MIWI_TICK PUSH_BUTTON_press_time;


void DemoOutput_Greeting(void)
{
    printf((char *)"Simple P2P Demo MRF24J40 Node ");
    printf("\r\nStarting Node 1 of Simple Demo for MiWi(TM) P2P Stack ...");  

    printf("\r\n     RF Transceiver: MRF24J40");        
    printf("\r\n   Demo Instruction:");
    printf("\r\n                     Power on the board until LED 1 lights up");
    printf("\r\n                     to indicate connecting with peer. Push");
    printf("\r\n                     Button 1 to broadcast message. Push Button");
    printf("\r\n                     2 to unicast encrypted message. LED 2 will");
    printf("\r\n                     be toggled upon receiving messages. ");
    printf("\r\n\r\n");    
}        

void demo_output_freezer_options(void)
{ 
    #if defined(EXPLORER16)
        printf((char *)"RD6:New Network RD7:Freezer", 0, false);
    #elif defined(PIC18_EXPLORER)
        printf((char *)"RB0:New Network RA5:Freezer", 0, false);
    #elif defined(EIGHT_BIT_WIRELESS_BOARD)
        printf((char *)"RB0:New Network RB2:Freezer", 0, false);
    #elif defined(MIWIKIT)
        printf((char *)"SW1:New Network SW2:Freezer", 0, false);
    #endif
}
void DemoOutput_Channel(uint8_t channel, uint8_t Step)
{
    if( Step == 0 )
    {
        
        printf((char *)"Connecting Peer  on Channel %d ", channel);
        #if !defined(MIWIKIT)
        printf("\r\nConnecting Peer on Channel ");
        CONSOLE_PrintDec(channel);
        printf("\r\n");
        #endif
    }
    else
    {    
      
        printf((char *)"Connected Peer  on Channel %d", channel);
        #if !defined(MIWIKIT)
        printf("\r\nConnected Peer on Channel ");
        CONSOLE_PrintDec(channel);
        printf("\r\n");
        #endif
    }
}    

void DemoOutput_StartActiveScan(void)
{
    LCD_putStr(0,0,"Active Scanning",true);
    printf("\r\nStarting Active Scan...");
}

void DemoOutput_EnergyScan(void)
{    
    LCD_putStr(0,0,"Active Scanning",true);
    LCD_putStr(1,0,"Energy Scanning",false);
}  

void DemoOutput_JoinFail(void)
{
//    Printf("\r\nJoin Fail");
    LCD_putStr(0,0,"Join Fail",true);
}    

void DemoOutput_Instruction(void)
{
    
}    


void DemoOutput_HandleMessage(void)
{
    uint8_t i;

    if(rxMessage.flags.bits.secEn){
        printf("Secured ");
    }
    
    printf((rxMessage.flags.bits.broadcast) ? "Broadcast Packet with RSSI " : "Unicast Packet with RSSI ");
    
    CONSOLE_PrintHex(rxMessage.PacketRSSI);
    if( rxMessage.flags.bits.srcPrsnt )
    {
        printf(" from ");
        if( rxMessage.flags.bits.altSrcAddr )
        {
            CONSOLE_PrintHex( rxMessage.SourceAddress[1]);
            CONSOLE_PrintHex( rxMessage.SourceAddress[0]);
        }
        else
        {    
            for(i = 0; i < MY_ADDRESS_LENGTH; i++)
            {
                CONSOLE_PrintHex(rxMessage.SourceAddress[MY_ADDRESS_LENGTH-1-i]);
            }    
        }
    }
    printf(": ");
    
    for(i = 0; i < rxMessage.PayloadSize; i++){
        CONSOLE_Put(rxMessage.Payload[i]);
    }       
}    

void DemoOutput_UpdateTxRx(uint8_t TxNum, uint8_t RxNum)
{
    
}    

void DemoOutput_ChannelError(uint8_t channel)
{
    printf("\r\nSelection of channel %i", channel);
    printf(" is not supported in current configuration.\r\n");
}    

void DemoOutput_UnicastFail(void)
{
    printf("\r\nUnicast Failed\r\n");
}    

/*********************************************************************
 * Function:        uint8_t ButtonPressed(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Return value to indicate which button has been pressed.
 *                  Return 0 if no button pressed.
 *
 * Side Effects:
 *
 * Overview:        This function check if any button has been pressed
 *
 * Note:
 ********************************************************************/
uint8_t ButtonPressed(void)
{
    return 0;
}





