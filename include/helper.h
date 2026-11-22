#ifndef HELPER_H
#define HELPER_H

#include <stdint.h>
#include "stm32f401.h"

#define GPIO_MODE(moder, otype, pupd) ((moder) | ((otype) << 2) | ((pupd) << 3))

enum {
  GPIO_IN_FLOAT       = GPIO_MODE(0u,0u,0u),
  GPIO_IN_PULLUP      = GPIO_MODE(0u,0u,1u),
  GPIO_IN_PULLDOWN    = GPIO_MODE(0u,0u,2u),
  GPIO_OUT_PP         = GPIO_MODE(1u,0u,0u),
  GPIO_OUT_OD         = GPIO_MODE(1u,1u,0u),
  GPIO_AF_PP          = GPIO_MODE(2u,0u,0u),
  GPIO_AF_OD          = GPIO_MODE(2u,1u,0u),
  GPIO_ANALOG         = GPIO_MODE(3u,0u,0u),
};

uint32_t field_set(uint32_t reg, unsigned shift, unsigned width, uint32_t value);
int wait_flag(volatile uint32_t *reg, uint32_t mask, int want_set, uint32_t tries);
void gpio_cfg(GPIO_TypeDef *g, unsigned pin, unsigned mode);
void gpio_af(GPIO_TypeDef *g, unsigned pin, unsigned af);
unsigned pin_shift(unsigned pin);
uint32_t elapsed(uint32_t now, uint32_t start);

#endif
