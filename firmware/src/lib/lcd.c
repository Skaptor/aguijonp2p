#include <string.h>
#include "system.h"
#include "lcd.h"
#include "pin_manager.h"
#include "lib/i2c.h"

//LCD initialization generic commands
static const uint8_t lcd_init_cmds[2][9] = {
    {0x38, 0x39, 0x14, 0x70, 0x5E, 0x6D, 0x0C, 0x01, 0x06}, //used when LCD_MODE_1
    {0x34, 0x34, 0x14, 0x70, 0x5E, 0x6D, 0x00, 0x00, 0x00}, //used when LCD_MODE_2
};

static void sendCommand(uint8_t cmd)
{
    //for more info on commands, refer to st7036i controller
    i2c_start();
    i2c_sendByte(LCD_I2C_ADDR);
    i2c_sendByte(LCD_CMD_CMD);
    i2c_sendByte(cmd);
    i2c_stop();
}

void lcd_GotoYX(int y, int x)
{
    uint8_t cmd = 0x80 + ((y == 0) ? x : (0x40+x));
    sendCommand(cmd);
}

void lcd_Clear(void)
{
    sendCommand(0x01);
}

void lcd_putStr(int y, int x, uint8_t *msg, bool clear)
{
    if(clear){
        LCD_Clear();
        DELAY_milliseconds(1);
    }

    LCD_GotoYX(y,x);

    i2c_start();
    i2c_sendByte(LCD_I2C_ADDR);
    i2c_sendByte(LCD_DATA_CMD);

    do{
        i2c_sendByte(*msg++);
    }while(*msg);

    i2c_stop();
}

#define LCD_SIZE 20
void lcd_scrollInit(uint8_t delaya, uint8_t *pText, Scroller_t *pScroller)
{
    uint8_t textSize = 0;
    
    textSize = strlen(pText);
    
    if(textSize > SCROLLER_SIZE){
        textSize = SCROLLER_SIZE;
    }
    
    pScroller->currPos  = LCD_SIZE-1;
    pScroller->textSize = textSize;
    pScroller->delay = delaya;
    memcpy(pScroller->text, pText, textSize);
    
}


bool LCD_scroll(uint8_t y, Scroller_t *pScroller, bool loop)
{
    #define SPACE 0x20
    uint8_t textBuffer[LCD_SIZE];
    uint8_t toCopy = 0;
    
    memset(textBuffer, SPACE, sizeof(textBuffer));  
        
    if(pScroller->currPos < 0){
        toCopy = (-1*pScroller->currPos);
        memcpy(&textBuffer[0], &pScroller->text[toCopy], ((pScroller->textSize-toCopy) > LCD_SIZE) ? LCD_SIZE : pScroller->textSize-toCopy);                   
    }else{
        toCopy = ((LCD_SIZE-pScroller->currPos) > pScroller->textSize) ? pScroller->textSize : (LCD_SIZE-pScroller->currPos)+1;
        memcpy(&textBuffer[pScroller->currPos], &pScroller->text[0], toCopy);
    }    
        
    LCD_putStr(y, 0, textBuffer, false);   
    
    DELAY_milliseconds(pScroller->delay);
    
    pScroller->currPos = (pScroller->currPos > (-pScroller->textSize)) ? pScroller->currPos-1 : (LCD_SIZE-1);
    
    return (loop) ? (pScroller->currPos == (LCD_SIZE-1)) : (pScroller->currPos < 0); 
}

void lcd_Init(bool mode)
{
    IO_LCDRST_SetHigh();
    DELAY_milliseconds(100);

    i2c_start();
    i2c_sendByte(LCD_I2C_ADDR);
    i2c_sendByte(LCD_CMD_CMD);

    if(mode == LCD_MODE_1){
        i2c_sendByte(0x38);
        DELAY_milliseconds(60);
        i2c_sendByte(0x39);//8bits,line 2,instruction table 01(IS1)
        DELAY_milliseconds(60);
        i2c_sendByte(0x14);//IS1: 1/5 bias,FX not fixed
        i2c_sendByte(0x70);//IS1: Contrast set for internal follower mode C3:C0 = 0
        i2c_sendByte(0x5E);//IS1: ICON display on, Booster on,Contrast C5,C4=1,0
        i2c_sendByte(0x6D);//IS1: Follower circuit on, follower circuit ratio
        i2c_sendByte(0x0C);//Display on, cursor off,cursor position off
        i2c_sendByte(0x01);//Clear display
        i2c_sendByte(0x06);//Cursor direction, no display shift
    }else{
        i2c_sendByte(0x34);
        DELAY_milliseconds(20);
        i2c_sendByte(0x34);
        DELAY_milliseconds(20);
        i2c_sendByte(0x14);
        i2c_sendByte(0x70);
        i2c_sendByte(0x5E);
        i2c_sendByte(0x6D);
    }
    
    DELAY_milliseconds(60);
    i2c_stop();
}
