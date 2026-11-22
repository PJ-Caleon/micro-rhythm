#ifndef HELPER_H
#define HELPER_H

#include <stdint.h>

uint32_t field_set(uint32_t reg, unsigned shift, unsigned width, uint32_t value);
int wait_flag(volatile uint32_t *reg, uint32_t mask, int want_set, uint32_t tries);

#endif
