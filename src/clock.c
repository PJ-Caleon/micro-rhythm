#include "clock.h"
#include "helper.h"
#include "stm32f401.h"
#include "FreeRTOS.h"
#include "task.h"

#define WAIT_TRIES 100000u

uint32_t clock_pllcfgr_word(void){
  volatile uint32_t w = RCC_PLLCFGR_PLLSRC_HSE;
  w = field_set(w, RCC_PLLCFGR_PLLM_Pos, 6u, 25u);
  w = field_set(w, RCC_PLLCFGR_PLLN_Pos, 9u, 336u);
  w = field_set(w, RCC_PLLCFGR_PLLP_Pos, 2u, 1u); 
  w = field_set(w, RCC_PLLCFGR_PLLQ_Pos, 4u, 7u);
  return w;
}

uint32_t clock_cfgr_word(void){
  uint32_t w = 0u;
  w = field_set(w, RCC_CFGR_PPRE1_Pos, 3u, 4u); // APB1 = 84/2 = 42 MHz 
  w = field_set(w, RCC_CFGR_PPRE2_Pos, 3u, 0u); // APB2 = 84 MHz
  return w;
}

int clock_init(void){
  RCC->CR |= RCC_CR_HSEON;
  if (wait_flag(&RCC->CR, RCC_CR_HSERDY, 1, WAIT_TRIES) != 0){
    return -1;
  }

  FLASH->ACR = field_set(0u, FLASH_ACR_LATENCY_Pos, 4u, 2u) | FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN;

  RCC->PLLCFGR = clock_pllcfgr_word();
  RCC->CR |= RCC_CR_PLLON;
  if (wait_flag(&RCC->CR, RCC_CR_PLLRDY, 1, WAIT_TRIES) != 0){
    return -1;
  }

  RCC->CFGR = clock_cfgr_word();

  RCC->CFGR = field_set(RCC->CFGR, RCC_CFGR_SW_Pos, 2u, 2u);
  if (wait_flag(&RCC->CFGR, BIT(3), 1, WAIT_TRIES) != 0){
    return -1;
  }

  return 0;
}

uint32_t millis(void){
  if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED){
    return 0u;
  }
  return (uint32_t)xTaskGetTickCount();
}
