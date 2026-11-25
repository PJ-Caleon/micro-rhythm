#ifndef ADC_H 
#define ADC_H 

#include <stdint.h>

void adc_init(void);
int adc_read(uint16_t *out);
uint16_t adc_get(void);

#endif
