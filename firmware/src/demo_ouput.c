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

//#define LIGHT   0x01
//#define SWITCH  0x02
///*************************************************************************/
//// AdditionalNodeID variable array defines the additional 
//// information to identify a device on a PAN. This array
//// will be transmitted when initiate the connection between 
//// the two devices. This  variable array will be stored in 
//// the Connection Entry structure of the partner device. The 
//// size of this array is ADDITIONAL_NODE_ID_SIZE, defined in 
//// ConfigApp.h.
//// In this demo, this variable array is set to be empty.
///*************************************************************************/
#if ADDITIONAL_NODE_ID_SIZE > 0
    uint8_t AdditionalNodeID[ADDITIONAL_NODE_ID_SIZE] = {0x01};
#endif
//
//
///*************************************************************************/
//// The variable myChannel defines the channel that the device
//// is operate on. This variable will be only effective if energy scan
//// (ENABLE_ED_SCAN) is not turned on. Once the energy scan is turned
//// on, the operating channel will be one of the channels available with
//// least amount of energy (or noise).
///*************************************************************************/
//uint8_t myChannel = 25;
//
//bool role = false ;  // Default : Any device will be END_DEVICE
//
//void EscorpionRojo_StartConnection(void)
//{
//    uint8_t i, j;
//
//    /*******************************************************************/
//    // Function MiApp_ProtocolInit initialize the protocol stack. In
//    // this example, if button 1 is released when powering up, we assume
//    // that the user want the network to start from scratch.
//    /*******************************************************************/
//    MiApp_ProtocolInit(false);
//
//    myChannel = 0xFF;
//    DemoOutput_StartActiveScan();
//
//    /*******************************************************************/
//    // Function MiApp_SearchConnection will return the number of
//    // existing connections in all channels. It will help to decide
//    // which channel to operate on and which connection to add.
//    // The return value is the number of connections. The connection
//    //     data are stored in global variable ActiveScanResults.
//    //     Maximum active scan result is defined as
//    //     ACTIVE_SCAN_RESULT_SIZE
//    // The first parameter is the scan duration, which has the same
//    //     definition in Energy Scan. 10 is roughly 1 second. 9 is a
//    //     half second and 11 is 2 seconds. Maximum scan duration is 14,
//    //     or roughly 16 seconds.
//    // The second parameter is the channel map. Bit 0 of the
//    //     double word parameter represents channel 0. For the 2.4GHz
//    //     frequency band, all possible channels are channel 11 to
//    //     channel 26. As the result, the bit map is 0x07FFF800. Stack
//    //     will filter out all invalid channels, so the application
//    //     only needs to pay attention to the channels that are not
//    //     preferred.
//    /*******************************************************************/
////    i = MiApp_SearchConnection(9, 0x000F0000);
//    i = MiApp_SearchConnection(9, 0xFFFFFFFF);
////    DemoOutput_ActiveScanResults(i);
//
//    /*******************************************************************/
//    // Function MiApp_ConnectionMode sets the connection mode for the
//    // protocol stack. Possible connection modes are:
//    //  - ENABLE_ALL_CONN       accept all connection request
//    //  - ENABLE_PREV_CONN      accept only known device to connect
//    //  - ENABL_ACTIVE_SCAN_RSP do not accept connection request, but
//    //                          allow response to active scan
//    //  - DISABLE_ALL_CONN      disable all connection request, including
//    //                          active scan request
//    /*******************************************************************/
//    MiApp_ConnectionMode(ENABLE_ALL_CONN);
//
//    if( i > 0 )
//    {
//        /*******************************************************************/
//        // Function MiApp_EstablishConnection try to establish a new
//        // connection with peer device.
//        // The first parameter is the index to the active scan result, which
//        //      is acquired by discovery process (active scan). If the value
//        //      of the index is 0xFF, try to establish a connection with any
//        //      peer.
//        // The second parameter is the mode to establish connection, either
//        //      direct or indirect. Direct mode means connection within the
//        //      radio range; Indirect mode means connection may or may not
//        //      in the radio range.
//        /*******************************************************************/
//        if( MiApp_EstablishConnection(0, CONN_MODE_DIRECT) == 0xFF )
//        {
//            DemoOutput_JoinFail();
//        }
//    }
//    else
//    {
//        DemoOutput_EnergyScan();
//        /*******************************************************************/
//        // Function MiApp_StartConnection tries to start a new network
//        //
//        // The first parameter is the mode of start connection. There are
//        // two valid connection modes:
//        //   - START_CONN_DIRECT        start the connection on current
//        //                              channel
//        //   - START_CONN_ENERGY_SCN    perform an energy scan first,
//        //                              before starting the connection on
//        //                              the channel with least noise
//        //   - START_CONN_CS_SCN        perform a carrier sense scan
//        //                              first, before starting the
//        //                              connection on the channel with
//        //                              least carrier sense noise. Not
//        //                              supported for current radios
//        //
//        // The second parameter is the scan duration, which has the same
//        //     definition in Energy Scan. 10 is roughly 1 second. 9 is a
//        //     half second and 11 is 2 seconds. Maximum scan duration is
//        //     14, or roughly 16 seconds.
//        //
//        // The third parameter is the channel map. Bit 0 of the
//        //     double word parameter represents channel 0. For the 2.4GHz
//        //     frequency band, all possible channels are channel 11 to
//        //     channel 26. As the result, the bit map is 0x07FFF800. Stack
//        //     will filter out all invalid channels, so the application
//        //     only needs to pay attention to the channels that are not
//        //     preferred.
//        /*******************************************************************/
//        MiApp_StartConnection(START_CONN_ENERGY_SCN,9, 0xFFFFFFFF);
//    }
//    
//    /*A:0x11665544332211ff  
//     *PANID:0x1234 Ch:26
//     */
//    
//    uint8_t buffer1[24];
//    uint8_t buffer2[24];
//    
//    
//    DumpConnectionShort(0xFF, buffer1, buffer2);
//    LCD_putStr(0, 0, buffer1, true);
//    LCD_putStr(1, 0, buffer2, false);
//
//    DumpConnection(0xFF);
//    
//    DELAY_milliseconds(2000);
//}

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





