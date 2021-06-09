#include "mcc_generated_files/system.h"
#include "lcd.h"
#include "pin_manager.h"
#include "delay.h"
#include "adc.h"
#include "i2c.h"
#include "adc1.h"
#include "bsp.h"
#include "miwi/miwi_api.h"
#include "miwi/miwi_nvm.h"
#include "demo_output.h"
#include "oc1.h"
#include "rtcc.h"
#include <time.h>

#define LIGHT   0x01
#define SWITCH  0x02
/*************************************************************************/
// AdditionalNodeID variable array defines the additional 
// information to identify a device on a PAN. This array
// will be transmitted when initiate the connection between 
// the two devices. This  variable array will be stored in 
// the Connection Entry structure of the partner device. The 
// size of this array is ADDITIONAL_NODE_ID_SIZE, defined in 
// ConfigApp.h.
// In this demo, this variable array is set to be empty.
/*************************************************************************/
#if ADDITIONAL_NODE_ID_SIZE > 0
    uint8_t AdditionalNodeID[ADDITIONAL_NODE_ID_SIZE] = {LIGHT};
#endif


/*************************************************************************/
// The variable myChannel defines the channel that the device
// is operate on. This variable will be only effective if energy scan
// (ENABLE_ED_SCAN) is not turned on. Once the energy scan is turned
// on, the operating channel will be one of the channels available with
// least amount of energy (or noise).
/*************************************************************************/
uint8_t myChannel = 25;

bool role = false ;  // Default : Any device will be END_DEVICE

void EscorpionRojo_StartConnection(void)
{
    uint8_t i, j;

    /*******************************************************************/
    // Function MiApp_ProtocolInit initialize the protocol stack. In
    // this example, if button 1 is released when powering up, we assume
    // that the user want the network to start from scratch.
    /*******************************************************************/
    MiApp_ProtocolInit(false);

    myChannel = 0xFF;
    DemoOutput_StartActiveScan();

    /*******************************************************************/
    // Function MiApp_SearchConnection will return the number of
    // existing connections in all channels. It will help to decide
    // which channel to operate on and which connection to add.
    // The return value is the number of connections. The connection
    //     data are stored in global variable ActiveScanResults.
    //     Maximum active scan result is defined as
    //     ACTIVE_SCAN_RESULT_SIZE
    // The first parameter is the scan duration, which has the same
    //     definition in Energy Scan. 10 is roughly 1 second. 9 is a
    //     half second and 11 is 2 seconds. Maximum scan duration is 14,
    //     or roughly 16 seconds.
    // The second parameter is the channel map. Bit 0 of the
    //     double word parameter represents channel 0. For the 2.4GHz
    //     frequency band, all possible channels are channel 11 to
    //     channel 26. As the result, the bit map is 0x07FFF800. Stack
    //     will filter out all invalid channels, so the application
    //     only needs to pay attention to the channels that are not
    //     preferred.
    /*******************************************************************/
//    i = MiApp_SearchConnection(9, 0x000F0000);
    i = MiApp_SearchConnection(9, 0xFFFFFFFF);
//    DemoOutput_ActiveScanResults(i);

    /*******************************************************************/
    // Function MiApp_ConnectionMode sets the connection mode for the
    // protocol stack. Possible connection modes are:
    //  - ENABLE_ALL_CONN       accept all connection request
    //  - ENABLE_PREV_CONN      accept only known device to connect
    //  - ENABL_ACTIVE_SCAN_RSP do not accept connection request, but
    //                          allow response to active scan
    //  - DISABLE_ALL_CONN      disable all connection request, including
    //                          active scan request
    /*******************************************************************/
    MiApp_ConnectionMode(ENABLE_ALL_CONN);

    if( i > 0 )
    {
        /*******************************************************************/
        // Function MiApp_EstablishConnection try to establish a new
        // connection with peer device.
        // The first parameter is the index to the active scan result, which
        //      is acquired by discovery process (active scan). If the value
        //      of the index is 0xFF, try to establish a connection with any
        //      peer.
        // The second parameter is the mode to establish connection, either
        //      direct or indirect. Direct mode means connection within the
        //      radio range; Indirect mode means connection may or may not
        //      in the radio range.
        /*******************************************************************/
        if( MiApp_EstablishConnection(0, CONN_MODE_DIRECT) == 0xFF )
        {
            DemoOutput_JoinFail();
        }
    }
    else
    {
        DemoOutput_EnergyScan();
        /*******************************************************************/
        // Function MiApp_StartConnection tries to start a new network
        //
        // The first parameter is the mode of start connection. There are
        // two valid connection modes:
        //   - START_CONN_DIRECT        start the connection on current
        //                              channel
        //   - START_CONN_ENERGY_SCN    perform an energy scan first,
        //                              before starting the connection on
        //                              the channel with least noise
        //   - START_CONN_CS_SCN        perform a carrier sense scan
        //                              first, before starting the
        //                              connection on the channel with
        //                              least carrier sense noise. Not
        //                              supported for current radios
        //
        // The second parameter is the scan duration, which has the same
        //     definition in Energy Scan. 10 is roughly 1 second. 9 is a
        //     half second and 11 is 2 seconds. Maximum scan duration is
        //     14, or roughly 16 seconds.
        //
        // The third parameter is the channel map. Bit 0 of the
        //     double word parameter represents channel 0. For the 2.4GHz
        //     frequency band, all possible channels are channel 11 to
        //     channel 26. As the result, the bit map is 0x07FFF800. Stack
        //     will filter out all invalid channels, so the application
        //     only needs to pay attention to the channels that are not
        //     preferred.
        /*******************************************************************/
        MiApp_StartConnection(START_CONN_ENERGY_SCN,9, 0xFFFFFFFF);
    }
    
    /*A:0x11665544332211ff  
     *PANID:0x1234 Ch:26
     */
    
    uint8_t buffer1[24];
    uint8_t buffer2[24];
    
    
    DumpConnectionShort(0xFF, buffer1, buffer2);
    LCD_putStr(0, 0, buffer1, true);
    LCD_putStr(1, 0, buffer2, false);

    DumpConnection(0xFF);
    
    DELAY_milliseconds(2000);
}

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    InitSymbolTimer();
    
    i2c_init();
    
    IO_LCDBL_SetHigh();
    LCD_Init(LCD_MODE_1);           
    EscorpionRojo_StartConnection();    
    
    Scroller_t scroller;
    Scroller_t scroller2;
    
    asm("nop");
    asm("nop");
    asm("nop");
    LCD_scrollInit(0, "skaptor:V", &scroller);    
    LCD_scrollInit(100, "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ12345678901234", &scroller2);    
    while(true){
//        LCD_scroll(0, &scroller, false);
        LCD_scroll(1, &scroller2, false);
    }

    //    struct tm currentTime;
    
    for(;;){
        ta_tasks();
//        tca_tasks();
        
//        sprintf(buffer, "adc=%.4i", adc_read(AN3_POT));
//        
//        LCD_putStr(0,0, buffer, true);
//        
//        if(MiApp_MessageAvailable()){
//            uint16_t remoteADC = (rxMessage.Payload[0] << 8) | rxMessage.Payload[1];
//            sprintf(buffer, "remote adc=%.4i", remoteADC);
//            LCD_putStr(1,0, buffer, false);
//            MiApp_DiscardMessage();
//        }
//        
//        MiApp_FlushTx();
//        MiApp_WriteData(adc_read(AN3_POT)>>8);
//        MiApp_WriteData(adc_read(AN3_POT));
//        if(MiApp_BroadcastPacket(false) == false){
//            LCD_putStr(1,0, "FAIL :(", false);
//        }
//        
//        while(!RTCC_TimeGet(&currentTime));
//        
//        printf("time is: %i\r", currentTime.tm_sec);
//        
//        DELAY_milliseconds(50);
//        LATE ^= 0xFF;
        
        
        // Add your application code
    }

    return 1;
}
