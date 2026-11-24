#include "rng.h"

int random(uint16_t pre_seed){
  static uint16_t seed = 1;
  static uint16_t last_pre_seed = 0;

  if(pre_seed == 0x0000){
    return -1;
  }

  if (pre_seed != last_pre_seed){
    seed = pre_seed;
    last_pre_seed = pre_seed;
  }

  uint16_t new = (uint16_t)((seed & 1u) ^ ((seed >> 1) & 1u));
  seed = seed >> 1;
  seed = (uint16_t)((seed) | (new << 15));
  uint16_t out = (uint16_t)(seed & 1u);
  return out;
}
