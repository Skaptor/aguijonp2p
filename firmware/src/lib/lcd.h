/********************************************************************
 FileName:    	LCD.h
 Dependencies: 	none
 Hardware:	Aguijon rev3.0 & rev4.0
 Complier:  	Microchip XC16, C30
 Company:	Vinagrón Digital
 Author:	Juan Carlos Orozco Gutierrez

 Software License Agreement:

 This software has been licensed under the GNU General Public
 License is intended to guarantee your freedom to share and change free
 software--to make sure the software is free for all its users.

********************************************************************
 File Description:
    LCD header file


 Change History:
  Rev   Description                                 Modified by:
  ----  -----------------------------------------  --------------
  1.0   Initial release                             JCOG
  2.0   Updated with [VD] HammerHead libraries      JCOG
  2.1   Added #define USE_LCD_EXTRA_FEATURES        JCOG
  2.2   Added #define LCD_MODE_x                    JCOG

 For extra documentation and support:
 *  http://www.vinagrondigital.com
********************************************************************/

#ifndef LCD_H
#define	LCD_H

//Uncomment to access LCD extra features
#define USE_LCD_EXTRA_FEATURES

#define LCD_I2C_ADDR    0x78    //LCD's address on the I2C bus
#define LCD_DATA_CMD    0x40    //data write command
#define LCD_CMD_CMD     0x00    //command write command

#define LCD_MODE_1      0x00
#define LCD_MODE_2      0x01

#define BLIGHT_LVL_OFF  0x00    //no PWM'd or full on backlight
#define BLIGHT_LVL_ON   0xFF	//no PWM'd backlight
#define BLIGHT_LVL_5    400     //highest intensity 95%
#define BLIGHT_LVL_4    2000    //highest intensity 75%
#define BLIGHT_LVL_3    4000    //..  50%
#define BLIGHT_LVL_2    6000    //..  25%
#define BLIGHT_LVL_1    7600    //lowest intensity   5%


void LCD_GotoYX(int y, int x);
void LCD_putStr(int y, int x, uint8_t *msg, bool clear);
void LCD_Init(bool mode);



#endif	/* LCD_H */

