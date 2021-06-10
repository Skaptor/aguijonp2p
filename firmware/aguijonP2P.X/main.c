#include "mcc_generated_files/system.h"
#include "lcd.h"
#include "pin_manager.h"
#include "delay.h"
#include "adc.h"
#include "i2c.h"
#include "adc1.h"
#include "bsp.h"
#include "miwi/miwi_api.h"
#include "miwi/miwi_nvm.h"
#include "demo_output.h"
#include "oc1.h"
#include "rtcc.h"
#include "tmr1.h"
#include <time.h>
#include "tick.h"
#include "switches.h"
#include "waterTimer.h"



int main(void)
{
    SYSTEM_Initialize();
    InitSymbolTimer();
    i2c_init();
    tickInit();    
    sw_initialize();
    water_initialize();
    
    IO_LCDBL_SetHigh();
    LCD_Init(LCD_MODE_1);           
    
    IO_DIPSW_MSBENABLE_SetHigh();
    IO_DIPSW_LSBENABLE_SetHigh();
    
//    ta_initialize();
    
    for(;;){
        water_tasks();        
        sw_tasks();
    }

    return 1;
}
