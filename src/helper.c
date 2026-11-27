#include "helper.h"

uint32_t field_set(uint32_t reg, unsigned shift, unsigned width, uint32_t value){
  uint32_t mask = (1u << width) - 1u;
  reg &= ~(mask << shift);
  reg |= (mask & value) << shift;
  return reg;
}

int wait_flag(volatile uint32_t *reg, uint32_t mask, int want_set, uint32_t tries){
  while(tries--){
    uint32_t is_set = (*reg & mask) != 0u;
    if (is_set == (want_set != 0)){
      return 0;
    }
  }
  return -1;
}

unsigned pin_shift(unsigned pin){
  return (pin & 7u) * 4u;
}

void gpio_cfg(GPIO_TypeDef *g, unsigned pin, unsigned mode){
  g->MODER = field_set(g->MODER, pin * 2u, 2u, mode & 3u);
  g->OTYPER = field_set(g->OTYPER, pin, 1u, (mode >> 2) & 1u);
  g->PUPDR = field_set(g->PUPDR, pin * 2u, 2u, (mode >> 3) & 3u);
}

void gpio_af(GPIO_TypeDef *g, unsigned pin, unsigned af){
  volatile uint32_t *reg = (pin < 8u) ? &g->AFRL : &g->AFRH;
  *reg = field_set(*reg, pin_shift(pin), 4u, af);
}

uint32_t elapsed(uint32_t now, uint32_t start){
  return now - start;
}

unsigned smpr_field(unsigned channel){
  return (channel < 10u)? (channel*3u) : (channel - 10u) * 3u;
}

unsigned set_threshold(unsigned high, unsigned low, unsigned val){
  if(val > high){
    return high;
  } else if (val < low){
    return low;
  }
  return val;
}

uint32_t numsize(uint32_t number){
  uint32_t digit = 0;
  while (number > 0){
    number = number / 10; 
    digit++;
  }
  return digit;
}
