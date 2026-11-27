#ifndef GAME_CONFIG_H 
#define GAME_CONFIG_H

#define HIT_RADIUS_X 2
#define HIT_RADIUS_Y 2 
#define DEBOUNCE_MS 20u 
#define DROP_SPEED 10

// OLED is 128x32 pixels 
#define PLAYER_WIDTH 4
#define ARENA_X_MIN 0
#define ARENA_X_MAX 128

extern uint32_t player_health;
extern uint32_t score;

#endif
