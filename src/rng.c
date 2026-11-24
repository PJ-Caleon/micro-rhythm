#include "rng.h"

int64_t random(uint32_t pre_seed){
  static uint32_t seed = 1;
  static uint32_t last_pre_seed = 0;
  uint32_t out = 0;

  if(pre_seed == 0x0u){
    return -1;
  }

  if (pre_seed != last_pre_seed){
    seed = pre_seed;
    last_pre_seed = pre_seed;
  }

  for (int i = 0; i < 32; i++){
    uint32_t new = (seed & 1u) ^ ((seed >> 1) & 1u);
    seed = seed >> 1;
    seed = (seed) | (new << 31);
    uint32_t bit = seed & 1u;
    out |= bit << i;
  }
  return (int64_t)out;
}
