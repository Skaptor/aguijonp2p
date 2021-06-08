///********************************************************************
// FileName:    	LCD.c
// Dependencies: 	aguijon.h
// Hardware:	Aguijon rev3.0 & rev4.0
// Complier:  	Microchip XC16, C30
// Company:	Vinagrón Digital
// Author:	Juan Carlos Orozco Gutierrez
//
// Software License Agreement:
//
// This software has been licensed under the GNU General Public
// License is intended to guarantee your freedom to share and change free
// software--to make sure the software is free for all its users.
//
//********************************************************************
// File Description:
//    Analog Support File
//
//
// Change History:
//  Rev   Description                                 Modified by:
//  ----  -----------------------------------------  --------------
//  1.0   Initial release                             JCOG
//  2.0   Updated with [VD] HammerHead libraries      JCOG
//  2.1   Added unified LCD_Init() function           JCOG
//
// For extra documentation and support:
// *  http://www.vinagrondigital.com
//********************************************************************/
//#include "system.h"
//#include "bsp.h"
//#include "lcd.h"
//
//static const uint8_t VDcustomChar1[] = {0x04, 0x0C, 0x1C, 0x14, 0x1C, 0x0C, 0x0E, 0x0F};
//static const uint8_t VDcustomChar2[] = {0x00, 0x00, 0x00, 0x08, 0x0C, 0x0C, 0x14, 0x18};
//static const uint8_t VDcustomChar3[] = {0x1F, 0x0F, 0x1E, 0x0F, 0x1C, 0x0E, 0x18, 0x18};
//static const uint8_t VDcustomChar4[] = {0x19, 0x15, 0x15, 0x15, 0x19, 0x00, 0x00, 0x00};
//static const uint8_t VDcustomChar5[] = {0x0D, 0x11, 0x15, 0x15, 0x19, 0x00, 0x00, 0x00};
//static const uint8_t VDcustomChar6[] = {0x1F, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00};
//static const uint8_t VDcustomChar7[] = {0x09, 0x15, 0x1D, 0x15, 0x15, 0x00, 0x00, 0x00};
//
///*LCD initialization generic commands. Do not remove!!!*/
//static const uint8_t lcd_init_cmds[2][9] = {
//    {0x38, 0x39, 0x14, 0x70, 0x5E, 0x6D, 0x0C, 0x01, 0x06}, //used when LCD_MODE_1
//    {0x34, 0x34, 0x14, 0x70, 0x5E, 0x6D, 0x00, 0x00, 0x00}, //used when LCD_MODE_2
//};
/////////////////////////////////////////////////////////////////////////////////
//static void LCD_Command(uint8_t cmd)
//{
//    //for more info on commands, refer to st7036i controller
//    IO_I2Cstart();
//    IO_I2CsendByte(LCD_I2C_ADDR);
//    IO_I2CsendByte(LCD_CMD_CMD);
//    IO_I2CsendByte(cmd);
//    IO_I2Cstop();
//}
//
//static void LCD_Data(uint8_t data)
//{
//    IO_I2Cstart();
//    IO_I2CsendByte(LCD_I2C_ADDR);
//    IO_I2CsendByte(LCD_DATA_CMD);
//    IO_I2CsendByte(data);
//    IO_I2Cstop();
//}
//
//void LCD_StoreCustomChar(uint8_t *rows, uint8_t cgram_loc)
//{
//    int i;
//
//    if(cgram_loc >= 8) return; //we only have 8 (0-7) spaces at CGRAM
//
//    // Set up the display to write into CGRAM - configure LCD to use func table 0
//    IO_I2Cstart();
//    IO_I2CsendByte(LCD_I2C_ADDR);     //address
//    IO_I2CsendByte(LCD_CMD_CMD);      //command
//    IO_I2CsendByte(0x38);             //set to func table 0
//    delayms(5);                         //wait for the LCD
//    //Set CGRAM position to write
//    IO_I2CsendByte(0x40 + (cgram_loc*8));
//    IO_I2Cstop();
//
//    IO_I2Cstart();
//    IO_I2CsendByte(0x78);
//    IO_I2CsendByte(0x40);    //RS=1 (write data to ram)
//
//    //send the 8 rows of the uint8_tacter
//    for(i=0;i<8;i++){
//        IO_I2CsendByte(*rows); // write the current pointed row to CGRAM
//        rows++;             //increment the pointer
//    }
//
//    IO_I2Cstop();
//    delayms(1);
//
//    // Leave the LCD as it was - function table 1 DDRAM and set the cursor
//    LCD_Command(0x39);
//}
//
//void LCD_Clear(void)
//{
//    LCD_Command(0x01);
//}
//
//void LCD_GotoXY(int x, int y)
//{
//    uint8_t cmd = 0;
//
//    switch(y){
//        case 1: cmd = (0x00 + x); break;
//        case 2: cmd = (0x40 + x); break;
//    }
//
//    cmd += 0x80;    //0x80 is set cursor pos.
//
//    LCD_Command(cmd);
//}
//
//void LCD_GotoYX(int y, int x)
//{
//    uint8_t cmd = 0;
//
//    switch(y){
//        case 1: cmd = (0x00 + x); break;
//        case 2: cmd = (0x40 + x); break;
//    }
//
//    cmd += 0x80;
//
//    LCD_Command(cmd);
//}
//
//void LCD_SetCursorHome(void)
//{
//    LCD_Command(0x02);
//}
//
//void LCD_SetCursorBlink(bool enabled)
//{
//    if(enabled){
//        LCD_Command(0x0F);
//    }else{
//        LCD_Command(0x0C);
//    }
//}
//
//void LCD_Putc(uint8_t letter)
//{
//    /* the user must call: LCD_GotoXY or LCD_GotoYX and set the cursor before
//     * calling this function, otherwise the letter will be displayed in the
//     * current cursor position */
//    IO_I2Cstart();
//    IO_I2CsendByte(LCD_I2C_ADDR);
//    IO_I2CsendByte(LCD_DATA_CMD);
//    IO_I2CsendByte(letter);
//    IO_I2Cstop();
//}
//
//void LCD_PutCustomChar(uint8_t cgram_loc)
//{
//    /* the user must call: LCD_GotoXY or LCD_GotoYX and set the cursor before
//     * calling this function, otherwise the uint8_tacter will be displayed in the
//     * current cursor position */
//    if(cgram_loc > 8){ return; }
//    
//    IO_I2Cstart();
//    IO_I2CsendByte(LCD_I2C_ADDR);
//    IO_I2CsendByte(LCD_DATA_CMD);
//    IO_I2CsendByte(cgram_loc);
//    IO_I2Cstop();
//}
//
//void LCD_PutStr(int y, int x, uint8_t *msg, bool clear)
//{
//    if(clear){
//        LCD_Clear();
//        delayms(1);
//    }
//
//    LCD_GotoYX(y,x);
//
//    IO_I2Cstart();
//    IO_I2CsendByte(LCD_I2C_ADDR);
//    IO_I2CsendByte(LCD_DATA_CMD);
//
//    while(*msg){
//        IO_I2CsendByte(*msg);
//        msg++;
//    }
//    IO_I2Cstop();
//}
//
//void LCD_BacklightSet(int level)
//{
////    if(level != BLIGHT_LVL_OFF && level != BLIGHT_LVL_ON){
////        CloseOC1();
////        if(level){
////            OpenOC1(OC_SYSCLK_SRC  | OC_CONTINUE_PULSE, OC_SYNC_TRIG_IN_CURR_OC, 8000, level);
////        }
////    }else if(level == BLIGHT_LVL_ON){
////        CloseOC1();
////        LCD_BLIGHT_PIN = 1;
////    }else{
////        CloseOC1();
////        LCD_BLIGHT_PIN = 0;
////    }
//}
//
//void LCD_Init(bool mode)
//{
//    static bool init_i2c = true;    //do we need to initialize i2c?
//    int i;
//
//    if(init_i2c){
//        IO_I2Cinit();       //init i2c module
//        init_i2c = false;   //i2c init done
//        delayms(10);        //wait a bit
//    }
//
//    if((mode == LCD_MODE_1) || (mode == LCD_MODE_2)){
//        /*Reset LCD*/
//        LCD_RESET_PIN = 1;
//        delayms(10);
//
//        IO_I2Cstart();  //start I2C comm
//
//        IO_I2CsendByte(LCD_I2C_ADDR);   //send LCD address
//        IO_I2CsendByte(LCD_CMD_CMD);    //tell the lcd we will send a cmd
//
//        for(i=0 ; i<9 ; i++){
//            IO_I2CsendByte(lcd_init_cmds[mode][i]);
//
//            //we need a delay only when the first two cmds are sent
//            if(i <= 1){ delayms(10); }
//            else if(!lcd_init_cmds[mode][i]){ break; }//only 6 cmds are required for LCD_MODE_2, so exit
//        }
//        delayms(10);
//        
//        IO_I2Cstop();
//    }
//}
//void LCD_IntroAnimation(void)
//{
//    uint8_t msg1[] = {"inagr\xE2n"};  //inagrón
//
//    /*First, store custom uint8_ts for VD logo*/    
//    LCD_StoreCustomChar((uint8_t *)VDcustomChar1,0);    
//    LCD_StoreCustomChar((uint8_t *)VDcustomChar2,1);
//    LCD_StoreCustomChar((uint8_t *)VDcustomChar3,2);
//    LCD_StoreCustomChar((uint8_t *)VDcustomChar4,3);
//    LCD_StoreCustomChar((uint8_t *)VDcustomChar5,4);
//    LCD_StoreCustomChar((uint8_t *)VDcustomChar6,5);
//    LCD_StoreCustomChar((uint8_t *)VDcustomChar7,6);    
//
//    /*Second, display first screen and wait*/
//    LCD_GotoYX(1,5);
//    LCD_Data(0);
//    LCD_Data(1);
//    LCD_GotoYX(2,5);
//    LCD_Data(2);
//
//    LCD_GotoYX(2,10);
//    LCD_Data(3);
//    LCD_Data(4);
//    LCD_Data(5);
//    LCD_Data(6);  
//
//    LCD_PutStr(1,7,msg1,false);
//
//    /*Third, */
//    delayms(500);
//}
////
////#if defined(USE_LCD_EXTRA_FEATURES)
////void LCD_BacklightFadeIn(void)
////{
////    LCD_BacklightSet(BLIGHT_LVL_OFF);
////    delayms(50);
////    LCD_BacklightSet(BLIGHT_LVL_1);
////    delayms(50);
////    LCD_BacklightSet(BLIGHT_LVL_2);
////    delayms(50);
////    LCD_BacklightSet(BLIGHT_LVL_3);
////    delayms(50);
////    LCD_BacklightSet(BLIGHT_LVL_4);
////    delayms(50);
////    LCD_BacklightSet(BLIGHT_LVL_5);
////}
////
////void LCD_BacklightFadeOut(void)
////{
////    LCD_BacklightSet(BLIGHT_LVL_5);
////    delayms(50);
////    LCD_BacklightSet(BLIGHT_LVL_4);
////    delayms(50);
////    LCD_BacklightSet(BLIGHT_LVL_3);
////    delayms(50);
////    LCD_BacklightSet(BLIGHT_LVL_2);
////    delayms(50);
////    LCD_BacklightSet(BLIGHT_LVL_1);
////    delayms(50);
////    LCD_BacklightSet(BLIGHT_LVL_OFF);
////}
////#endif
