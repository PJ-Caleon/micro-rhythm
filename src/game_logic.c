#include "game_logic.h"
#include "game_config.h"
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

const char* spawn(uint32_t speed, uint32_t seed){
  static char spawn_str[11];

  uint32_t size = numsize(seed);

  uint8_t  max_digit = 0;
  uint32_t max_pos   = 0;                   

  // parse number to separate digits 
  for (uint32_t i = 0; i < size; i++){
    uint8_t digit = seed % 10;
    seed = seed / 10;

    if (digit >= max_digit){
      max_digit = digit;
      max_pos   = i;
    }
  }

  // 0 everywhere, then a 1 at the position of the highest digit
  for (uint32_t i = 0; i < size; i++){
    spawn_str[i] = '0';
  }
  spawn_str[size - 1 - max_pos] = '1';       
  spawn_str[size] = '\0';

  return spawn_str;
}

uint8_t spawn_pos(char *spawn_str){
  uint8_t x = 0;

  while (spawn_str[x] != '\0'){
    if (spawn_str[x] == '1'){
      return x;                  
    }
    x++;
  }
  return 0xFF;
}

uint8_t is_collision(uint8_t obj_x, uint8_t obj_y, uint32_t ply_x, uint8_t ply_press){
  // min and max of ply_x and check if the obj_x is in range 
  int32_t ply_min = (int32_t)ply_x - PLAYER_WIDTH/2;
  int32_t ply_max = (int32_t)ply_x + PLAYER_WIDTH/2;

  int32_t obj_min = (int32_t)obj_x - HIT_RADIUS_X/2; 
  int32_t obj_max = (int32_t)obj_x + HIT_RADIUS_X/2;

  if (ply_max < obj_min || ply_min > obj_max){
    return 0;
  }

  if ((!ply_press) || !(obj_y <= HIT_RADIUS_Y)){
    return 0;
  }
  return 1;
}
