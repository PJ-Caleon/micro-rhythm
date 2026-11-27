#include "game_logic.h"
#include "clock.h"

static uint32_t previous_clock = 0;
static uint8_t y = 64;

uint32_t game_clock(void){
  uint32_t clock = millis(); 
  return clock;
}

// oled 128x64
uint8_t object_falling(uint32_t speed){
  // object y = 64 
  // after every 10ms, y-- 
  uint32_t current_clock = game_clock();
  uint32_t value = 100000/speed;
  
  if (current_clock - previous_clock >= value){
    previous_clock = current_clock;
    y--;
  }

  if (y == 0){
    y = 64;
  }

  return y;
} 
