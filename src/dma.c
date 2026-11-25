#include "dma.h"
#include "stm32f401.h"
#include "helper.h"

volatile uint16_t adc_buf[ADC_BUF_LEN];

void dma_init(void){
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
  (void)RCC->AHB1ENR;

  // Ram using DMA2  
  DMA_Stream_TypeDef *s = &DMA2->S[0];

  // Disable stream before configuring 
  s->CR &= ~DMA_SxCR_EN;
  wait_flag(&s->CR, DMA_SxCR_EN, 0, 100000u);

  DMA2->LIFCR = BIT(0) | BIT(2) | BIT(3) | BIT(4) | BIT(5);

  // Set source to ADC data register 
  s->PAR  = (uint32_t)&ADC1->DR;   
  // Set destination to RAM buffer 
  s->M0AR = (uint32_t)adc_buf;     
  // Send to circular buffer 
  s->NDTR = ADC_BUF_LEN;           
  // direct mode 
  s->FCR  = 0u;

  // incremement memory circular 
  s->CR = (0u << DMA_SxCR_CHSEL_Pos)
        | (0u << DMA_SxCR_DIR_Pos)
        | (1u << DMA_SxCR_PSIZE_Pos)
        | (1u << DMA_SxCR_MSIZE_Pos)
        | DMA_SxCR_MINC
        | DMA_SxCR_CIRC;

  // wait for ADC request
  s->CR |= DMA_SxCR_EN;
}
