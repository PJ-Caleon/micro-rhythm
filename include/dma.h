#ifndef DMA_H
#define DMA_H
#include <stdint.h>

#define ADC_BUF_LEN 64u

extern volatile uint16_t adc_buf[ADC_BUF_LEN];

void dma_init(void);

#endif
