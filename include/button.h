#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

typedef struct { uint8_t stable; uint8_t last; uint32_t t_change; } debounce_t;

int debounce(debounce_t *d, uint8_t raw, uint32_t now_ms);
uint8_t buttons_read(void);

#ifndef UNIT_TEST 
void button_task(void *arg);
#endif

#endif
