#include "controller.h"
#include "adc.h"
#include "button.h"
#include "helper.h"
#include "game_config.h"

unsigned set_threshold(unsigned high, unsigned low, unsigned val);
uint16_t adc_get(void);

uint32_t player_position(void){
  uint32_t raw = adc_get();

  // Output from 0 - 128
  uint32_t pot_pos = (raw - 128u)/3300u;

  // limit movement to border 
  uint32_t limit_x = PLAYER_WIDTH/2;
  pot_pos = set_threshold(128u - limit_x, limit_x, pot_pos);
  return pot_pos;
}

uint8_t player_press(void){
  return buttons_read() != 0u;
}
