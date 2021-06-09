#include "system.h"
#include "miwi/miwi_api.h"
#include "miwi/miwi_nvm.h"
#include "oc1.h"
#include "pin_manager.h"
#include "lcd.h"

typedef enum
{
    INIT,
    WAIT_KEY,
    SEND,
    WAIT_RESPONSE,
}TCastate_t;

static TCastate_t state = WAIT_KEY;

//temp

//end temp


void tca_tasks(void)
{
    static MIWI_TICK tick;
    
    switch(state){
        case INIT:
            tick = MiWi_TickGet();
            state = WAIT_KEY;
            
        case WAIT_KEY:           
            if(IO_DIPSW0_GetValue() == 0){
                DELAY_milliseconds(10);
                if(IO_DIPSW0_GetValue() != 0){
                    break;
                }

                LCD_putStr(0, 0, "sent                   ", false);
                state = SEND;
            }
            break;
            
        case SEND:
            MiApp_FlushTx();
            MiApp_WriteData(0x00);
            MiApp_WriteData(0x00); //minutes
            MiApp_WriteData(0x0A); //seconds
            MiApp_WriteData(true);
            if(MiApp_BroadcastPacket(false) == false){
                LCD_putStr(1,0, "FAIL :(", false);
            }
            state = WAIT_RESPONSE;
            break;
            
        case WAIT_RESPONSE:
            if(!MiApp_MessageAvailable()){
                break;                
            }       
            
            LCD_putStr(1,0, "Rcvd response", false);
            
            state = INIT;
            break;
    }
}

