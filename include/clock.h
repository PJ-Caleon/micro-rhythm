#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

uint32_t clock_pllcfgr_word(void);
uint32_t clock_cfgr_word(void);
int clock_init(void);
void SysTick_Handler(void);
uint32_t millis(void);

#endif
