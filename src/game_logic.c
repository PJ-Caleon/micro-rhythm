#include "game_logic.h"
#include "clock.h"
#include "rng.h"
#include "helper.h"

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

uint32_t spawn(uint32_t speed){
  uint32_t seed_pos = random(0xABCDABCD);  
  uint32_t size = numsize(seed_pos);
  uint32_t spawn_val = 0;

  // parse number to separate digits
  for (uint32_t i = 0; i < size; i++){
    uint8_t bit = seed_pos % 10; 
    seed_pos = seed_pos / 10; 

    if (bit > 8){
      bit = 1; 
    } else {
      bit = 0;
    }
  
    spawn_val = spawn_val * 10 + bit;        
  }
  
  return spawn_val; 
}
