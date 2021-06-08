#include "mcc_generated_files/system.h"
#include "lcd.h"
#include "pin_manager.h"
#include "delay.h"


int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    IO_LCDBL_SetHigh();
    LCD_Init(LCD_MODE_1);
    
    uint8_t buffer[64] = {0};
    uint8_t counter = 0;        
    
    for(;;){
        sprintf(buffer, "adc=%i", counter++);
        
        LCD_putStr(0,0, buffer, false);
        DELAY_milliseconds(250);
        LATE ^= 0xFF;
        // Add your application code
    }

    /*
     #if defined(MRF24J40)
        PHY_CS_TRIS = 0;
        PHY_CS = 1;
        PHY_RESETn_TRIS = 0;
        PHY_RESETn = 1;
    #endif

    RF_INT_TRIS = 1;

    SDI_TRIS = 1;
    SDO_TRIS = 0;
    SCK_TRIS = 0;
    SPI_SDO = 0;
    SPI_SCK = 0;

        PHY_WAKE_TRIS = 0;
        PHY_WAKE = 1;    

    #if defined(HARDWARE_SPI)
        SPI1CON1 = 0b0000000100111110;
        SPI1STAT = 0x8000;

        SPI2CON1 = 0b0000000100111110;
        SPI2STAT = 0x8000;
    #endif

    #if defined(ENABLE_NVM)
    EE_nCS_TRIS = 0;
    EE_nCS = 1;
    #endif

    #if defined (ENABLE_NVM_MAC)
    MAC_nCS_TRIS = 0;
    MAC_nCS = 1;
    #endif

    RFIF = 0;
    if(RF_INT_PIN == 0){
        RFIF = 1;
    }
     */
    
    return 1;
}
