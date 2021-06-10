#include "system.h"
#include "waterTimer.h"
#include "tick.h"
#include "lcd.h"
#include "switches.h"
#include "24LC01.h"
#include "pin_manager.h"
#include <string.h>

static WaterData_t waterData;


uint16_t ee_seconds=0;

Scroller_t lcdScroller;
uint8_t counter = 0;

uint8_t msg0[] = "Timer Started please wait";
uint8_t msg1[] = "ERROR DETECTED, PLEASE DIAL x116 BRIAN FLORES FOR ASSISTANCE";
uint8_t msg2[] = "inminent software crash detected, be careful";
uint8_t msg3[] = "this is taking a long time, huh?";
uint8_t msg4[] = "better not waste this water";
uint8_t msg5[] = "what do you need it for anyways?";
uint8_t msg6[] = "are you reading these messages? is your life so bad?";
uint8_t msg7[] = "what are you doing here, this is what im here for, GO!";

void updateScroller(void)
{
    switch(counter){
        case 0: LCD_scrollInit(0, msg0, &lcdScroller); counter++; break;
        case 1: LCD_scrollInit(0, msg1, &lcdScroller); counter++; break;
        case 2: LCD_scrollInit(0, msg2, &lcdScroller); counter++; break;
        case 3: LCD_scrollInit(0, msg3, &lcdScroller); counter++; break;
        case 4: LCD_scrollInit(0, msg4, &lcdScroller); counter++; break;
        case 5: LCD_scrollInit(0, msg5, &lcdScroller); counter++; break;
        case 6: LCD_scrollInit(0, msg6, &lcdScroller); counter++; break;
        case 7: LCD_scrollInit(0, msg7, &lcdScroller); counter=0; break;
    }
}

static void stop(void)
{
    IO_RLY0_SetLow();
    waterData.seconds = ee_seconds;
    waterData.state = STATE_WAIT_KEY;
    counter = 0;
    updateScroller();
}

static void updateLCDData(void)
{
    switch(waterData.state){
        case STATE_READ_EEPROM:
            sprintf(waterData.lcdLine0, "Reading EEPROM...   ");
            sprintf(waterData.lcdLine1, "ERROR WHILE READING ");
            break;

        case STATE_WAIT_KEY:
        case STATE_WAIT_KEY_RELEASE:
            sprintf(waterData.lcdLine0, "Config: %02i:%02i   ", (int)waterData.seconds/60, (int)waterData.seconds%60);
            sprintf(waterData.lcdLine1, "+1m  -1m  +1s  START");
            break;

        case STATE_COUNT:
            if(LCD_scroll(0, &lcdScroller, true)){
                updateScroller();
            }                       
            
            sprintf(waterData.lcdLine1, "     %02i:%02i    CANCEL", (int)waterData.seconds/60, (int)waterData.seconds%60);
            LCD_putStr(1, 0, waterData.lcdLine1, false);    
            return;
    }
   
    LCD_putStr(0, 0, waterData.lcdLine0, true);
    LCD_putStr(1, 0, waterData.lcdLine1, false);    
    
}

void water_initialize(void)
{
    waterData.seconds = 0;
    waterData.state = STATE_READ_EEPROM;
    waterData.lcdTick = tickGet();
    memset(waterData.lcdLine0, 0x00, sizeof(waterData.lcdLine0));
    memset(waterData.lcdLine1, 0x00, sizeof(waterData.lcdLine1));
    
    updateScroller();
}

void water_tasks(void)
{
    uint8_t keys = 0;
    static uint32_t stickyTick = 0;
   
    switch(waterData.state){
        case STATE_READ_EEPROM:
            waterData.seconds  = EEPROM_Read2(0x00) << 8;
            waterData.seconds |= EEPROM_Read2(0x01);
            ee_seconds = waterData.seconds;
            waterData.state = STATE_WAIT_KEY;
            break;

        case STATE_WAIT_KEY:
            keys = sw_getPort();

            if(!keys){
                break;
            }
            
            waterData.state = STATE_WAIT_KEY_RELEASE;
            waterData.newState = STATE_WAIT_KEY;
            if(keys & 0x01){
                waterData.seconds += 60;
                break;
            }

            if(keys & 0x02){
                if(waterData.seconds < 60){
                    waterData.seconds = 0;
                }else{
                    waterData.seconds -= 60;
                }
                break;
            }

            if(keys & 0x04){
                waterData.seconds += 1;
                stickyTick = tickGet();
                break;
            }

            if(keys & 0x08){
                waterData.newState = STATE_COUNT;
                
                if(ee_seconds != waterData.seconds){
                    EEPROM_Write(0x00, waterData.seconds >> 8);
                    DELAY_milliseconds(50);
                    EEPROM_Write(0x01, waterData.seconds);
                    ee_seconds = waterData.seconds;
                }                
                
                IO_RLY0_SetHigh();
                break;
            }
            break;

        case STATE_WAIT_KEY_RELEASE:
            
            if(!sw_getPort()){
                waterData.state = waterData.newState;
                waterData.tick = tickGet();
            }
            break;

        case STATE_COUNT:
            if(sw_get(3)){
                stop();
                waterData.state = STATE_WAIT_KEY_RELEASE;
                waterData.newState = STATE_WAIT_KEY;
                break;
            }
            
            if(tickGet()-waterData.tick >= 1000){
                waterData.tick = tickGet();

                --waterData.seconds;
                if(waterData.seconds == 0){
                    stop();
                }
            }
            break;
    }

    if(tickGet()-waterData.lcdTick > 200){
        waterData.lcdTick = tickGet();
        updateLCDData();
            
    }
}
