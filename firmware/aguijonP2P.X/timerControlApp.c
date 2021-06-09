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

void tca_tasks(void)
{
    static MIWI_TICK tick;
    
    switch(state){
        case INIT:
            tick = MiWi_TickGet();
            state = WAIT_KEY;
            
        case WAIT_KEY:
//            if(MiWi_TickGetDiff(MiWi_TickGet(), tick) > ONE_SECOND){
//                tick = MiWi_TickGet();
//                state = SEND;
//            }
            
            DELAY_milliseconds(1000);
            state = SEND;
            break;
            
        case SEND:
            MiApp_FlushTx();
            MiApp_WriteData(0);
            if(MiApp_BroadcastPacket(false) == false){
                LCD_putStr(1,0, "FAIL :(", false);
            }
            state = WAIT_RESPONSE;
            break;
            
        case WAIT_RESPONSE:
            if(!MiApp_MessageAvailable()){
                break;                
            }       
            
            LCD_putStr(0,0, "Rcvd response", true);
            
            state = INIT;
            break;
    }
}

