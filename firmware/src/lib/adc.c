#include "system.h"
#include "adc.h"
#include "adc1.h"

void adc_init(void)
{
    AD1CON1          = 0x00E0;      //internal counter ends sampling and starts conversion
    AD1CON2          = 0;           //use AVDD, AVSS as reference pins
    AD1CON3          = 0x1F02;      //Tsamp = 32 x Tad; Tad=125ns
    AD1CSSL          = 0;           //no scanning required
    AD1CON1bits.ADON = 1;           //turn on the ADC
}

uint16_t adc_read(uint8_t channel)
{
    AD1CHS           = channel; // 1. select analog input channel
    AD1CON1bits.SAMP = 1; 	// 2. start sampling
    while (!AD1CON1bits.DONE); 	// 3. wait for the conversion to complete
    return ADC1BUF0; 		// 4. read the conversion result
}

uint16_t adc_range(uint8_t channel, uint16_t min_val, uint16_t max_val)
{
    if(min_val > max_val){
        return 0;
    }

    float x = ADC_MAX_VALUE / (max_val - min_val);
    return (uint16_t)( (adc_read(channel) / x) + min_val);
}
