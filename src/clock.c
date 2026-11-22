#include "clock.h"
#include "helper.h"
#include "stm32f401.h"

static volatile uint32_t g_ms;
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

uint32_t tick_reload(uint32_t clk_hz, uint32_t tick_hz){
  return (clk_hz/ tick_hz) - 1u;
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

  SYSTICK->LOAD = tick_reload(SYSCLK_HZ, 1000u);
  SYSTICK->VAL = 0u;
  SYSTICK->CTRL = SYSTICK_ENABLE | SYSTICK_TICKINT | SYSTICK_CLKSRC;
  return 0;
}

void SysTick_Handler(void) {
  g_ms++;
}
uint32_t millis(void){
  return g_ms;
}
