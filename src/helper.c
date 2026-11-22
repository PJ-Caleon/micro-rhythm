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
