#include "system.h"
#include "miwi/miwi_api.h"
#include "miwi/miwi_nvm.h"
#include "oc1.h"
#include "../lib/lcd.h"

typedef enum
{
    WAIT_MSG,
    PROCESS,
    RESPOND,
}Tastate_t;

static const uint8_t msg1[] = "water saving timer app exception invariant error :V";
static const uint8_t msg2[] = "press the buttons for water saving :V";
static const uint8_t msg3[] = "ERROR WAS DETECTED, CALL EXTx116 BRIAN FLORES FOR ASSISTANCE";
static const uint8_t msg4[] = "INMINENT SOFTWARE CRASH DETECTED";

static uint8_t msgCounter = 0;

Tastate_t state = WAIT_MSG;
Scroller_t scroller;

//    LCD_scrollInit(100, "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ12345678901234", &scroller2);  

static void initMsg(void)
{
    switch(msgCounter){
        case 0:     LCD_scrollInit(0, msg1, &scroller);  msgCounter++;  break;
        case 1:     LCD_scrollInit(0, msg2, &scroller);  msgCounter++;  break;
        case 2:     LCD_scrollInit(0, msg3, &scroller);  msgCounter++;  break;
        case 3:     LCD_scrollInit(0, msg4, &scroller);  msgCounter=0;  break;
    }
}

void ta_initialize(void)
{
    initMsg();
}

    
void ta_tasks(void)
{
    static uint32_t _tick = 0;
    
    switch(state){
        case WAIT_MSG:
            if(!MiApp_MessageAvailable()){
                break;                
            }                        
            
            state = PROCESS;            
            
        case PROCESS:
            switch(rxMessage.Payload[0]){
                case 0:
                    OC1_Stop();                   
                    OC1_PrimaryValueSet(0x1F40);
                    OC1_SecondaryValueSet(0x3E80);
                    OC1_Start();
                    DELAY_milliseconds(50);
                    OC1_Stop();                   
                    break;
                    
                case 1:
                    break;
            }
            
            MiApp_DiscardMessage();
            
            state = RESPOND;
            break;
            
        case RESPOND:
            MiApp_FlushTx();
            MiApp_WriteData(0x03);
            MiApp_WriteData(0x7F);
            if(MiApp_BroadcastPacket(false) == false){
                LCD_putStr(1,0, "FAIL :(", false);
            }     
            
            state = WAIT_MSG;
            break;
    }
    
    if(tickGet()-_tick > 150){
        _tick = tickGet();
        if(LCD_scroll(0, &scroller, true)){
            initMsg();
        }
    }
    
}

