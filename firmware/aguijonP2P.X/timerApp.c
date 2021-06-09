#include "system.h"
#include "miwi/miwi_api.h"
#include "miwi/miwi_nvm.h"
#include "oc1.h"
#include "../lib/lcd.h"
#include "pin_manager.h"

typedef enum
{
    WAIT_MSG,
    PROCESS,
    RESPOND,
}Tastate_t;

typedef enum
{
    CMD_TIMER_START,
    CMD_TIMER_STOP,
    CMD_TIMER_STATUS,
}Tascmds_t;

static const uint8_t msg1[] = "water saving timer app exception invariant error :V";
static const uint8_t msg2[] = "press the buttons for water saving :V";
static const uint8_t msg3[] = "ERROR WAS DETECTED, CALL EXTx116 BRIAN FLORES FOR ASSISTANCE";
static const uint8_t msg4[] = "INMINENT SOFTWARE CRASH DETECTED";

static uint8_t msgCounter = 0;

Tastate_t state = WAIT_MSG;
Scroller_t scroller;


typedef struct
{
    bool        beep;
    bool        enabled;
    bool        cancel;
    bool        finished;
    uint32_t    secondsGoal;
    uint32_t    tick;
    
}Timercontrol_t;

uint8_t lcdBuffer[64];

Timercontrol_t myControl;

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

void Beep(void)
{
    OC1_Stop();                   
    OC1_PrimaryValueSet(0x1F40);
    OC1_SecondaryValueSet(0x3E80);
    OC1_Start();
    DELAY_milliseconds(50);
    OC1_Stop();
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
            asm("nop");
            asm("nop");
            asm("nop");
            MiApp_FlushTx();
            
            switch(rxMessage.Payload[0]){
                case CMD_TIMER_START:
                    myControl.secondsGoal = (rxMessage.Payload[1] * 60) | rxMessage.Payload[2];
                    
                    if(myControl.secondsGoal == 0){
                        MiApp_WriteData(0x7F);
                        break;
                    }
                    
                    myControl.beep = rxMessage.Payload[3];
                    myControl.cancel = false;
                    myControl.enabled = true;
                    myControl.finished = false;
                    myControl.tick = tickGet();
                    
                    MiApp_WriteData(0x64);
                    
                    IO_RLY0_SetHigh();
                    break;
                    
                case CMD_TIMER_STOP:
                    myControl.beep = true;
                    myControl.enabled = true;
                    myControl.cancel = true;
                    
                    MiApp_WriteData(0x64);
                    break;
                    
                case CMD_TIMER_STATUS:
                    MiApp_WriteData(0x64);
                    MiApp_WriteData(myControl.finished);
                    MiApp_WriteData(myControl.secondsGoal>>8);
                    MiApp_WriteData(myControl.secondsGoal);
                    break;
            }
            
            MiApp_DiscardMessage();
            
            state = RESPOND;
            break;
            
        case RESPOND:
            
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
        
        if(myControl.enabled){
            //sprintf(lcdBuffer, "Time remaining: %d  ", (int)myControl.secondsGoal);
            sprintf(lcdBuffer, "Time left: %02d:%02d           ", (int)(myControl.secondsGoal / 60), (int)(myControl.secondsGoal % 60));
            LCD_putStr(1, 0, lcdBuffer, false);            
        }else{
            LCD_putStr(1, 0, "timer not started   ", false);                        
        }
    }
    
    if(!myControl.enabled || myControl.finished){
        return;
    }
    
    if(myControl.cancel){
        Beep();
        
        myControl.enabled = false;
    }
    
    if(tickGet()-myControl.tick >= 1000){
        myControl.tick = tickGet();
        
        myControl.secondsGoal--;
        
        if(myControl.secondsGoal == 0){
            myControl.enabled = false;
            myControl.finished = true;
            IO_RLY0_SetLow();
            
            if(myControl.beep){
                Beep();
            }
        }
    }
}

