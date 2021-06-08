#ifndef _ADC_H_
#define _ADC_H_

#define ADC_MAX_VALUE 1023

void adc_init(void);
uint16_t adc_read(uint8_t channel);
uint16_t adc_range(uint8_t channel, uint16_t min_val, uint16_t max_val);

#endif
