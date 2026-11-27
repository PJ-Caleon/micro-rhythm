#ifndef GAME_LOGIC_H 
#define GAME_LOGIC_H 

#include <stdint.h>

uint32_t game_clock(void);
uint8_t object_falling(uint32_t speed);
const char* spawn(uint32_t speed, uint32_t seed);
uint8_t spawn_pos(char *spawn_str);
uint8_t is_collision(uint8_t obj_x, uint8_t obj_y, uint32_t ply_x, uint8_t ply_press);

#endif
