#include "adc.h"
#include "dma.h"
#include "stm32f401.h"
#include "helper.h"

void adc_init(void){
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  (void)RCC->APB2ENR;

  // prescaler set to 21 MHz (max is 36 MHz)
  ADC_CCR = field_set(ADC_CCR, ADC_CCR_ADCPRE_Pos, 2u, 1u); 
  // set sample time for channel 1 
  ADC1->SMPR2 = field_set(ADC1->SMPR2, smpr_field(1u), 3u, 4u);
  ADC1->SQR1 = 0u;
  ADC1->SQR3 = field_set(ADC1->SQR3, 0u, 5u, 1u);

  // Enable DMA + DDS 
  uint32_t cr2 = ADC_CR2_DMA | ADC_CR2_DDS; 
  cr2 = field_set(cr2, ADC_CR2_EXTSEL_Pos, 4u, 6u);
  cr2 = field_set(cr2, ADC_CR2_EXTEN_Pos, 2u, 1u);
  ADC1->CR2 = cr2;

  // Power on and wait for ADC stability 
  ADC1->CR2 |= ADC_CR2_ADON;
  for (volatile int i = 0; i < 1000; i++){}
}

int adc_read(uint16_t *out){
  if (out == 0){
    return -1;
  }
  *out = adc_get();
  return 0;
}

uint16_t adc_get(void){
  uint32_t ndtr = DMA2->S[0].NDTR;
  if (ndtr == 0u || ndtr > ADC_BUF_LEN){
    return adc_buf[0];
  }

  uint32_t written = ADC_BUF_LEN - ndtr;
  uint32_t latest_idx = (written + ADC_BUF_LEN - 1u) % ADC_BUF_LEN;
  return adc_buf[latest_idx];
}
