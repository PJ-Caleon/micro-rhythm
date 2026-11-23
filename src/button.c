#include "button.h"
#include "helper.h"
#include "game_config.h"

int debounce(debounce_t *d, uint8_t raw, uint32_t now_ms){
  raw = (raw != 0);
  if (raw != d->last){
    d->t_change = now_ms;
    return 0;
  }
  if (raw != d->stable && elapsed(now_ms, d->t_change) >= DEBOUNCE_MS){
    d->stable = (uint8_t)raw;
    return raw;
  }
  return 0;
}

uint8_t buttons_read(void){
  return (uint8_t)(((~GPIOB->IDR) >> 12) & 3u);
}
