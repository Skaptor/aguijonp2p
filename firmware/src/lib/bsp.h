/********************************************************************
 FileName:    	BSP.h
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
    Board Support Package


 Change History:
  Rev   Description                                 Modified by:
  ----  -----------------------------------------  --------------
  1.0   Initial release                             JCOG
  2.0   Updated with [VD] HammerHead libraries      JCOG
  2.1   Added support for Aguijon rev4.0            JCOG
  2.2   Added support for Aguijon rev4.1            JCOG

 For extra documentation and support:
 *  http://www.vinagrondigital.com
********************************************************************/

#ifndef AGUIJON_BSP_H
#define	AGUIJON_BSP_H

#define ON    TRUE
#define OFF   FALSE

#if defined(AGUIJON_REV_3)

    #define HAMMERHEAD_DEVICE "Aguijon rev3.0"

    //opto isolated inputs
    #define INPUT1                  PORTBbits.RB0
    #define INPUT2                  PORTBbits.RB1
    #define INPUT3                  PORTBbits.RB2
    #define INPUT4                  PORTBbits.RB3

    #define INPUT1_TRIS             TRISBbits.TRISB0
    #define INPUT2_TRIS             TRISBbits.TRISB1
    #define INPUT3_TRIS             TRISBbits.TRISB2
    #define INPUT4_TRIS             TRISBbits.TRISB3

    //On board switches & DIP Switch (shared)
    #define SWITCH1                 PORTBbits.RB13  //SWITCH 1 is shared with DIP 4 & 8
    #define SWITCH2                 PORTBbits.RB12  //SWITCH 2 is shared with DIP 3 & 7
    #define SWITCH3                 PORTBbits.RB11  //SWITCH 3 is shared with DIP 2 & 6
    #define SWITCH4                 PORTBbits.RB10  //SWITCH 4 is shared with DIP 1 & 5

    #define SWITCH1_TRIS            TRISBbits.TRISB13
    #define SWITCH2_TRIS            TRISBbits.TRISB12
    #define SWITCH3_TRIS            TRISBbits.TRISB11
    #define SWITCH4_TRIS            TRISBbits.TRISB10

    #define DIPSW_KEY_1_5           PORTBbits.RB10  //DIP SW keys 1 & 5 are shared
    #define DIPSW_KEY_2_6           PORTBbits.RB11  //DIP SW keys 2 & 6 are shared
    #define DIPSW_KEY_3_7           PORTBbits.RB12  //DIP SW keys 3 & 7 are shared
    #define DIPSW_KEY_4_8           PORTBbits.RB13  //DIP SW keys 4 & 8 are shared

    #define DIPSW_ENABLE_LSB_PIN    LATFbits.LATF1  //Control lines to allow sharing
    #define DIPSW_ENABLE_MSB_PIN    LATFbits.LATF0  //Control lines to allow sharing

    #define KEYBOARD_MASK           0x3C00
    #define INPUT_MASK              0x000F

    //end of input definitions

    //Analog
    #define ADC_PIN                 15
    #define ADC_PIN_MASK            0x7FFF

    //LCD
    #define LCD_RESET_PIN           LATDbits.LATD11
    #define LCD_RESET_TRIS          TRISDbits.TRISD11

    #define LCD_BLIGHT_PIN          LATGbits.LATG6
    #define LCD_BLIGHT_TRIS         TRISGbits.TRISG6

    //Relays
    #define RLY1_SET                LATDbits.LATD7
    #define RLY2_SET                LATDbits.LATD6
    #define RLY3_SET                LATDbits.LATD5
    #define RLY4_SET                LATDbits.LATD4

    #define RLY1_READ               PORTDbits.RD7
    #define RLY2_READ               PORTDbits.RD6
    #define RLY3_READ               PORTDbits.RD5
    #define RLY4_READ               PORTDbits.RD4

    #define RLY1_TRIS               TRISDbits.TRISD7
    #define RLY2_TRIS               TRISDbits.TRISD6
    #define RLY3_TRIS               TRISDbits.TRISD5
    #define RLY4_TRIS               TRISDbits.TRISD4

    //Open Collector
    #define OC1_SET                 LATDbits.LATD3
    #define OC2_SET                 LATDbits.LATD2
    #define OC3_SET                 LATDbits.LATD1
    #define OC4_SET                 LATDbits.LATD0

    #define OC1_READ                PORTDbits.RD3
    #define OC2_READ                PORTDbits.RD2
    #define OC3_READ                PORTDbits.RD1
    #define OC4_READ                PORTDbits.RD0

    #define OC1_TRIS                TRISDbits.TRISD3
    #define OC2_TRIS                TRISDbits.TRISD2
    #define OC3_TRIS                TRISDbits.TRISD1
    #define OC4_TRIS                TRISDbits.TRISD0

    //LED port
    #define LED1_SET                LATEbits.LATE0
    #define LED2_SET                LATEbits.LATE1
    #define LED3_SET                LATEbits.LATE2
    #define LED4_SET                LATEbits.LATE3
    #define LED5_SET                LATEbits.LATE4
    #define LED6_SET                LATEbits.LATE5
    #define LED7_SET                LATEbits.LATE6
    #define LED8_SET                LATEbits.LATE7

    #define LED1_READ               PORTEbits.RE0
    #define LED2_READ               PORTEbits.RE1
    #define LED3_READ               PORTEbits.RE2
    #define LED4_READ               PORTEbits.RE3
    #define LED5_READ               PORTEbits.RE4
    #define LED6_READ               PORTEbits.RE5
    #define LED7_READ               PORTEbits.RE6
    #define LED8_READ               PORTEbits.RE7

    #define LED1_TRIS               TRISEbits.TRISE0
    #define LED2_TRIS               TRISEbits.TRISE1
    #define LED3_TRIS               TRISEbits.TRISE2
    #define LED4_TRIS               TRISEbits.TRISE3
    #define LED5_TRIS               TRISEbits.TRISE4
    #define LED6_TRIS               TRISEbits.TRISE5
    #define LED7_TRIS               TRISEbits.TRISE6
    #define LED8_TRIS               TRISEbits.TRISE7

    //USB
    #define USB_5V_ENABLE           LATGbits.LATG9
    #define USB_5V_FAULT            PORTGbits.RG8

    #define USB_5V_ENABLE_TRIS      TRISGbits.TRISG9
    #define USB_5V_FAULT_TRIS       TRISGbits.TRISG8

    //SPI
    #define AGUIJON_PHY_CS                  LATFbits.LATF5
    #define AGUIJON_PHY_CS_TRIS             TRISFbits.TRISF5

    #define AGUIJON_SPI_SDO                 PORTBbits.RB5
    #define AGUIJON_SDO_TRIS                TRISBbits.TRISB5
    #define AGUIJON_SPI_SDI                 LATBbits.LATB14
    #define AGUIJON_SDI_TRIS                TRISBbits.TRISB14
    #define AGUIJON_SPI_SCK                 LATBbits.LATB4
    #define AGUIJON_SCK_TRIS                TRISBbits.TRISB4



#elif defined(AGUIJON_REV_4) || defined(AGUIJON_REV_41)

    #if defined(AGUIJON_REV_4)
        #define HAMMERHEAD_DEVICE "Aguijon rev4.0"
    #elif defined(AGUIJON_REV_41)
        #define HAMMERHEAD_DEVICE "Aguijon rev4.1"
    #endif


    //opto isolated inputs
    #define INPUT1                  PORTAbits.RA9
    #define INPUT2                  PORTEbits.RE9
    #define INPUT3                  PORTEbits.RE8
    #define INPUT4                  PORTCbits.RC3
    
    //On board switches & DIP Switch (shared)
    #define SWITCH1                 PORTBbits.RB13  //SWITCH 1 is shared with DIP 4 & 8
    #define SWITCH2                 PORTBbits.RB12  //SWITCH 2 is shared with DIP 3 & 7
    #define SWITCH3                 PORTBbits.RB11  //SWITCH 3 is shared with DIP 2 & 6
    #define SWITCH4                 PORTBbits.RB10  //SWITCH 4 is shared with DIP 1 & 5

    #define SWITCH1_TRIS            TRISBbits.TRISB13
    #define SWITCH2_TRIS            TRISBbits.TRISB12
    #define SWITCH3_TRIS            TRISBbits.TRISB11
    #define SWITCH4_TRIS            TRISBbits.TRISB10

    #define DIPSW_KEY_1_5           PORTBbits.RB10  //DIP SW keys 1 & 5 are shared
    #define DIPSW_KEY_2_6           PORTBbits.RB11  //DIP SW keys 2 & 6 are shared
    #define DIPSW_KEY_3_7           PORTBbits.RB12  //DIP SW keys 3 & 7 are shared
    #define DIPSW_KEY_4_8           PORTBbits.RB13  //DIP SW keys 4 & 8 are shared

    #define DIPSW_ENABLE_LSB_PIN    LATFbits.LATF1  //Control lines to allow sharing
    #define DIPSW_ENABLE_MSB_PIN    LATFbits.LATF0  //Control lines to allow sharing

    #define KEYBOARD_MASK           0x3C00
    #define INPUT1_MASK             0x0200
    #define INPUT2_MASK             0x0200
    #define INPUT3_MASK             0x0100
    #define INPUT4_MASK             0x0008
    //end of input definitions

    //Watchdog & reset
    #define WDOG_PIN                PORTBbits.RB7
    #define WDOG_PIN_TRIS           TRISBbits.TRISB7

    #define WDOG_Pet()              do{ WDOG_PIN ^= 1;     }while(0);
    #define WDOG_SoftDisable()      do{ WDOG_PIN_TRIS = 1; }while(0);
    #define WDOG_SoftEnable()       do{ WDOG_PIN_TRIS = 0; }while(0);

    //Analog
    #define ADC_PIN                 3
    #define ADC_PIN_MASK            0xFFF7

    //LCD
    #define LCD_RESET_PIN           LATAbits.LATA10
    #define LCD_BLIGHT_PIN          LATGbits.LATG6

    #define LCD_RESET_TRIS          TRISAbits.TRISA10
    #define LCD_BLIGHT_TRIS         TRISGbits.TRISG6

    //Relays
    #define RLY1_SET                LATDbits.LATD13
    #define RLY2_SET                LATDbits.LATD12
    #define RLY3_SET                LATDbits.LATD7
    #define RLY4_SET                LATDbits.LATD6

    #define RLY1_READ               PORTDbits.RD13
    #define RLY2_READ               PORTDbits.RD12
    #define RLY3_READ               PORTDbits.RD7
    #define RLY4_READ               PORTDbits.RD6

    #define RLY1_TRIS               TRISDbits.TRISD13
    #define RLY2_TRIS               TRISDbits.TRISD12
    #define RLY3_TRIS               TRISDbits.TRISD11
    #define RLY4_TRIS               TRISDbits.TRISD10

    //Open Collector
    #define OC1_SET                 LATDbits.LATD3
    #define OC2_SET                 LATDbits.LATD2
    #define OC3_SET                 LATDbits.LATD1
    #define OC4_SET                 LATDbits.LATD0

    #define OC1_READ                PORTDbits.RD3
    #define OC2_READ                PORTDbits.RD2
    #define OC3_READ                PORTDbits.RD1
    #define OC4_READ                PORTDbits.RD0

    #define OC1_TRIS                TRISDbits.TRISD3
    #define OC2_TRIS                TRISDbits.TRISD2
    #define OC3_TRIS                TRISDbits.TRISD1
    #define OC4_TRIS                TRISDbits.TRISD0

    //LED port
    #define LED1_SET                LATEbits.LATE0
    #define LED2_SET                LATEbits.LATE1
    #define LED3_SET                LATEbits.LATE2
    #define LED4_SET                LATEbits.LATE3
    #define LED5_SET                LATEbits.LATE4
    #define LED6_SET                LATEbits.LATE5
    #define LED7_SET                LATEbits.LATE6
    #define LED8_SET                LATEbits.LATE7

    #define LED1_READ               PORTEbits.RE0
    #define LED2_READ               PORTEbits.RE1
    #define LED3_READ               PORTEbits.RE2
    #define LED4_READ               PORTEbits.RE3
    #define LED5_READ               PORTEbits.RE4
    #define LED6_READ               PORTEbits.RE5
    #define LED7_READ               PORTEbits.RE6
    #define LED8_READ               PORTEbits.RE7

    #define LED1_TRIS               TRISEbits.TRISE0
    #define LED2_TRIS               TRISEbits.TRISE1
    #define LED3_TRIS               TRISEbits.TRISE2
    #define LED4_TRIS               TRISEbits.TRISE3
    #define LED5_TRIS               TRISEbits.TRISE4
    #define LED6_TRIS               TRISEbits.TRISE5
    #define LED7_TRIS               TRISEbits.TRISE6
    #define LED8_TRIS               TRISEbits.TRISE7

    #define STATUS_LEDA_SET         LATDbits.LATD14
    #define STATUS_LEDA_GET         PORTDbits.RD14
    #define STATUS_LEDA_TRIS        TRISDbits.TRISD14

    #define STATUS_LEDB_SET         LATCbits.LATC1
    #define STATUS_LEDB_GET         PORTCbits.RC1
    #define STATUS_LEDB_TRIS        TRISCbits.TRISC1

    //USB
    #define USB_5V_ENABLE           LATGbits.LATG1
    #define USB_5V_FAULT            PORTGbits.RG0

    #define USB_5V_ENABLE_TRIS      TRISGbits.TRISG1
    #define USB_5V_FAULT_TRIS       TRISGbits.TRISG0
   
    //Expansion ports (ExpPort standard)
    #if defined(AGUIJON_REV_4)
        /*
            J5 & J6:
            Pin1  -> GND
            Pin7  -> +5  VDC
            Pin8  -> +12 VDC
            Pin14 -> +3.3VDC
        */

        /*Expansion port #1 (J5)*/
        #define EXP_PORT1_PIN2_LAT      LATDbits.LATD9
        #define EXP_PORT1_PIN2_PORT     PORTDbits.RD9
        #define EXP_PORT1_PIN2_TRIS     TRISDbits.TRISD9
        #define EXP_PORT1_PIN2_RPOUT    RPOR2bits.RP4R
        #define EXP_PORT1_PIN2_RPIN     (4)

        #define EXP_PORT1_PIN3_LAT      LATDbits.LATD10
        #define EXP_PORT1_PIN3_PORT     PORTDbits.RD10
        #define EXP_PORT1_PIN3_TRIS     TRISDbits.TRISD10
        #define EXP_PORT1_PIN3_RPOUT    RPOR1bits.RP3R
        #define EXP_PORT1_PIN3_RPIN     (3)

        #define EXP_PORT1_PIN4_LAT      LATDbits.LATD11
        #define EXP_PORT1_PIN4_PORT     PORTDbits.RD11
        #define EXP_PORT1_PIN4_TRIS     TRISDbits.TRISD11
        #define EXP_PORT1_PIN4_RPOUT    RPOR6bits.RP12R
        #define EXP_PORT1_PIN4_RPIN     (12)

        #define EXP_PORT1_PIN5_LAT      LATDbits.LATD8
        #define EXP_PORT1_PIN5_PORT     PORTDbits.RD8
        #define EXP_PORT1_PIN5_TRIS     TRISDbits.TRISD8
        #define EXP_PORT1_PIN5_RPOUT    RPOR1bits.RP2R
        #define EXP_PORT1_PIN5_RPIN     (2)

        #define EXP_PORT1_PIN6_LAT      LATFbits.LATF8
        #define EXP_PORT1_PIN6_PORT     PORTFbits.RF8
        #define EXP_PORT1_PIN6_TRIS     TRISFbits.TRISF8
        #define EXP_PORT1_PIN6_RPOUT    RPOR7bits.RP15R
        #define EXP_PORT1_PIN6_RPIN     (15)

        #define EXP_PORT1_PIN9_LAT      LATFbits.LATF2
        #define EXP_PORT1_PIN9_PORT     PORTFbits.RF2
        #define EXP_PORT1_PIN9_TRIS     TRISFbits.TRISF2
        #define EXP_PORT1_PIN9_RPOUT    RPOR15bits.RP30R
        #define EXP_PORT1_PIN9_RPIN     (30)

        #define EXP_PORT1_PIN10_LAT     LATFbits.LATF5
        #define EXP_PORT1_PIN10_PORT    PORTFbits.RF5
        #define EXP_PORT1_PIN10_TRIS    TRISFbits.TRISF5
        #define EXP_PORT1_PIN10_RPOUT   RPOR8bits.RP17R
        #define EXP_PORT1_PIN10_RPIN    (17)

        #define EXP_PORT1_PIN11_LAT     LATFbits.LATF4
        #define EXP_PORT1_PIN11_PORT    PORTFbits.RF4
        #define EXP_PORT1_PIN11_TRIS    TRISFbits.TRISF4
        #define EXP_PORT1_PIN11_RPOUT   RPOR5bits.RP10R
        #define EXP_PORT1_PIN11_RPIN    (10)

        #define EXP_PORT1_PIN12_LAT     LATDbits.LATD15
        #define EXP_PORT1_PIN12_PORT    PORTDbits.RD15
        #define EXP_PORT1_PIN12_TRIS    TRISDbits.TRISD15
        #define EXP_PORT1_PIN12_RPOUT   RPOR2bits.RP5R
        #define EXP_PORT1_PIN12_RPIN    (5)

        #define EXP_PORT1_PIN13_LAT     LATBbits.LATB15
        #define EXP_PORT1_PIN13_PORT    PORTBbits.RB15
        #define EXP_PORT1_PIN13_TRIS    TRISBbits.TRISB15
        #define EXP_PORT1_PIN13_RPOUT   RPOR14bits.RP29R
        #define EXP_PORT1_PIN13_RPIN    (29)
        
        /* Expansion port #2 (J6)*/
        #define EXP_PORT2_PIN2_LAT      LATBbits.LATB14
        #define EXP_PORT2_PIN2_PORT     PORTBbits.RB14
        #define EXP_PORT2_PIN2_TRIS     TRISBbits.TRISB14
        #define EXP_PORT2_PIN2_RPOUT    RPOR7bits.RP14R
        #define EXP_PORT2_PIN2_RPIN     (14)

        #define EXP_PORT2_PIN3_LAT      LATDbits.LATD4
        #define EXP_PORT2_PIN3_PORT     PORTDbits.RD4
        #define EXP_PORT2_PIN3_TRIS     TRISDbits.TRISD4
        #define EXP_PORT2_PIN3_RPOUT    RPOR12bits.RP25R
        #define EXP_PORT2_PIN3_RPIN     (25)

        #define EXP_PORT2_PIN4_LAT      LATDbits.LATD5
        #define EXP_PORT2_PIN4_PORT     PORTDbits.RD5
        #define EXP_PORT2_PIN4_TRIS     TRISDbits.TRISD5
        #define EXP_PORT2_PIN4_RPOUT    RPOR10bits.RP20R
        #define EXP_PORT2_PIN4_RPIN     (20)

        #define EXP_PORT2_PIN5_LAT      LATBbits.LATB0
        #define EXP_PORT2_PIN5_PORT     PORTBbits.RB0
        #define EXP_PORT2_PIN5_TRIS     TRISBbits.TRISB0
        #define EXP_PORT2_PIN5_RPOUT    RPOR0bits.RP0R
        #define EXP_PORT2_PIN5_RPIN     (0)

        #define EXP_PORT2_PIN6_LAT      LATBbits.LATB1
        #define EXP_PORT2_PIN6_PORT     PORTBbits.RB1
        #define EXP_PORT2_PIN6_TRIS     TRISBbits.TRISB1
        #define EXP_PORT2_PIN6_RPOUT    RPOR0bits.RP1R
        #define EXP_PORT2_PIN6_RPIN     (1)

        #define EXP_PORT2_PIN9_LAT      LATBbits.LATB2
        #define EXP_PORT2_PIN9_PORT     PORTBbits.RB2
        #define EXP_PORT2_PIN9_TRIS     TRISBbits.TRISB2
        #define EXP_PORT2_PIN9_RPOUT    RPOR6bits.RP13R
        #define EXP_PORT2_PIN9_RPIN     (13)

        #define EXP_PORT2_PIN10_LAT     LATBbits.LATB4
        #define EXP_PORT2_PIN10_PORT    PORTBbits.RB4
        #define EXP_PORT2_PIN10_TRIS    LATBbits.LATB4
        #define EXP_PORT2_PIN10_RPOUT   RPOR9bits.RP18R
        #define EXP_PORT2_PIN10_RPIN    (28)

        #define EXP_PORT2_PIN11_LAT     LATBbits.LATB5
        #define EXP_PORT2_PIN11_PORT    PORTBbits.RB5
        #define EXP_PORT2_PIN11_TRIS    LATBbits.LATB5
        #define EXP_PORT2_PIN11_RPOUT   RPOR13bits.RP27R
        #define EXP_PORT2_PIN11_RPIN    (18)

        #define EXP_PORT2_PIN12_LAT     LATDbits.LATD15
        #define EXP_PORT2_PIN12_PORT    PORTDbits.RD15
        #define EXP_PORT2_PIN12_TRIS    LATDbits.LATD15
        #define EXP_PORT2_PIN12_RPOUT   RPOR7bits.RP15R
        #define EXP_PORT2_PIN12_RPIN    (27)

        #define EXP_PORT2_PIN13_LAT     LATGbits.LATG8
        #define EXP_PORT2_PIN13_PORT    PORTGbits.RG8
        #define EXP_PORT2_PIN13_TRIS    TRISGbits.TRISG8
        #define EXP_PORT2_PIN13_RPOUT   RPOR9bits.RP19R
        #define EXP_PORT2_PIN13_RPIN    (19)
       
    #elif defined(AGUIJON_REV_41)
        /*
            J5 & J6:
            Pin1  -> +5  VDC
            Pin2  -> +12 VDC
            Pin13 -> +3.3VDC
            Pin14 -> GND
        */

        /*Expansion port #1 (J5)*/
        #define EXP_PORT1_PIN3_LAT      LATBbits.LATB15
        #define EXP_PORT1_PIN3_PORT     PORTBbits.RB15
        #define EXP_PORT1_PIN3_TRIS     TRISBbits.TRISB15
        #define EXP_PORT1_PIN3_RPOUT    RPOR14bits.RP29R
        #define EXP_PORT1_PIN3_RPIN     (29)
		
        #define EXP_PORT1_PIN4_LAT      LATDbits.LATD15
        #define EXP_PORT1_PIN4_PORT     PORTDbits.RD15
        #define EXP_PORT1_PIN4_TRIS     TRISDbits.TRISD15
        #define EXP_PORT1_PIN4_RPOUT    RPOR2bits.RP5R
        #define EXP_PORT1_PIN4_RPIN     (5)
		
        #define EXP_PORT1_PIN5_LAT      LATFbits.LATF4
        #define EXP_PORT1_PIN5_PORT     PORTFbits.RF4
        #define EXP_PORT1_PIN5_TRIS     TRISFbits.TRISF4
        #define EXP_PORT1_PIN5_RPOUT    RPOR5bits.RP10R
        #define EXP_PORT1_PIN5_RPIN     (10)
		
        #define EXP_PORT1_PIN6_LAT      LATFbits.LATF5
        #define EXP_PORT1_PIN6_PORT     PORTFbits.RF5
        #define EXP_PORT1_PIN6_TRIS     TRISFbits.TRISF5
        #define EXP_PORT1_PIN6_RPOUT    RPOR8bits.RP17R
        #define EXP_PORT1_PIN6_RPIN     (17)
		
        #define EXP_PORT1_PIN7_LAT      LATFbits.LATF2
        #define EXP_PORT1_PIN7_PORT     PORTFbits.RF2
        #define EXP_PORT1_PIN7_TRIS     TRISFbits.TRISF2
        #define EXP_PORT1_PIN7_RPOUT    RPOR15bits.RP30R
        #define EXP_PORT1_PIN7_RPIN     (30)
		
        #define EXP_PORT1_PIN8_LAT      LATFbits.LATF8
        #define EXP_PORT1_PIN8_PORT     PORTFbits.RF8
        #define EXP_PORT1_PIN8_TRIS     TRISFbits.TRISF8
        #define EXP_PORT1_PIN8_RPOUT    RPOR7bits.RP15R
        #define EXP_PORT1_PIN8_RPIN     (15)
		
        #define EXP_PORT1_PIN9_LAT      LATDbits.LATD8
        #define EXP_PORT1_PIN9_PORT     PORTDbits.RD8
        #define EXP_PORT1_PIN9_TRIS     TRISDbits.TRISD8
        #define EXP_PORT1_PIN9_RPOUT    RPOR1bits.RP2R
        #define EXP_PORT1_PIN9_RPIN     (2)
		
        #define EXP_PORT1_PIN10_LAT     LATDbits.LATD11
        #define EXP_PORT1_PIN10_PORT    PORTDbits.RD11
        #define EXP_PORT1_PIN10_TRIS    TRISDbits.TRISD11
        #define EXP_PORT1_PIN10_RPOUT   RPOR6bits.RP12R
        #define EXP_PORT1_PIN10_RPIN    (12)
		
        #define EXP_PORT1_PIN11_LAT     LATDbits.LATD10
        #define EXP_PORT1_PIN11_PORT    PORTDbits.RD10
        #define EXP_PORT1_PIN11_TRIS    TRISDbits.TRISD10
        #define EXP_PORT1_PIN11_RPOUT   RPOR1bits.RP3R
        #define EXP_PORT1_PIN11_RPIN    (3)

        #define EXP_PORT1_PIN12_LAT     LATDbits.LATD9
        #define EXP_PORT1_PIN12_PORT    PORTDbits.RD9
        #define EXP_PORT1_PIN12_TRIS    TRISDbits.TRISD9
        #define EXP_PORT1_PIN12_RPOUT   RPOR2bits.RP4R
        #define EXP_PORT1_PIN12_RPIN    (4)

        /* Expansion port #2 (J6)*/
        #define EXP_PORT2_PIN3_LAT      LATGbits.LATG8
        #define EXP_PORT2_PIN3_PORT     PORTGbits.RG8
        #define EXP_PORT2_PIN3_TRIS     TRISGbits.TRISG8
        #define EXP_PORT2_PIN3_RPOUT    RPOR9bits.RP19R
        #define EXP_PORT2_PIN3_RPIN     (19)

        #define EXP_PORT2_PIN4_LAT      LATGbits.LATG9
        #define EXP_PORT2_PIN4_PORT     PORTGbits.RG9
        #define EXP_PORT2_PIN4_TRIS     TRISGbits.TRISG9
        #define EXP_PORT2_PIN4_RPOUT    RPOR13bits.RP27R
        #define EXP_PORT2_PIN4_RPIN     (27)
	
	#define EXP_PORT2_PIN5_LAT      LATBbits.LATB5
        #define EXP_PORT2_PIN5_PORT     PORTBbits.RB5
        #define EXP_PORT2_PIN5_TRIS     TRISBbits.TRISB5
        #define EXP_PORT2_PIN5_RPOUT    RPOR9bits.RP18R
        #define EXP_PORT2_PIN5_RPIN     (18)
		
	#define EXP_PORT2_PIN6_LAT      LATBbits.LATB4
        #define EXP_PORT2_PIN6_PORT     PORTBbits.RB4
        #define EXP_PORT2_PIN6_TRIS     TRISBbits.TRISB4
        #define EXP_PORT2_PIN6_RPOUT    RPOR14bits.RP28R
        #define EXP_PORT2_PIN6_RPIN     (28)

	#define EXP_PORT2_PIN7_LAT      LATBbits.LATB2
        #define EXP_PORT2_PIN7_PORT     PORTBbits.RB2
        #define EXP_PORT2_PIN7_TRIS     TRISBbits.TRISB2
        #define EXP_PORT2_PIN7_RPOUT    RPOR6bits.RP13R
        #define EXP_PORT2_PIN7_RPIN     (13)

	#define EXP_PORT2_PIN8_LAT      LATBbits.LATB1
        #define EXP_PORT2_PIN8_PORT     PORTBbits.RB1
        #define EXP_PORT2_PIN8_TRIS     TRISBbits.TRISB1
        #define EXP_PORT2_PIN8_RPOUT    RPOR0bits.RP1R
        #define EXP_PORT2_PIN8_RPIN     (1)

	#define EXP_PORT2_PIN9_LAT      LATBbits.LATB0
        #define EXP_PORT2_PIN9_PORT     PORTBbits.RB0
        #define EXP_PORT2_PIN9_TRIS     TRISBbits.TRISB0
        #define EXP_PORT2_PIN9_RPOUT    RPOR0bits.RP0R
        #define EXP_PORT2_PIN9_RPIN     (0)

	#define EXP_PORT2_PIN10_LAT     LATDbits.LATD5
        #define EXP_PORT2_PIN10_PORT    PORTDbits.RD5
        #define EXP_PORT2_PIN10_TRIS    TRISDbits.TRISD5
        #define EXP_PORT2_PIN10_RPOUT   RPOR10bits.RP20R
        #define EXP_PORT2_PIN10_RPIN    (20)

	#define EXP_PORT2_PIN11_LAT     LATDbits.LATD4
        #define EXP_PORT2_PIN11_PORT    PORTDbits.RD4
        #define EXP_PORT2_PIN11_TRIS    TRISDbits.TRISD4
        #define EXP_PORT2_PIN11_RPOUT   RPOR12bits.RP25R
        #define EXP_PORT2_PIN11_RPIN    (25)

		
	#define EXP_PORT2_PIN13_LAT     LATBbits.LATB14
        #define EXP_PORT2_PIN12_PORT    PORTBbits.RB14
        #define EXP_PORT2_PIN12_TRIS    TRISBbits.TRISB14
        #define EXP_PORT2_PIN12_RPOUT   RPOR7bits.RP14R
        #define EXP_PORT2_PIN12_RPIN    (14)
    #endif


#endif

#endif	/* AGUIJON_BSP_H */

