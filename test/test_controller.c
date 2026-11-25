#include "unity.h"
#include "controller.h"
#include "adc.h"
#include "game_config.h"
#include "stm32f401.h"
#include "dma.h"

// Helper hardware 
static void set_buttons(int pb12_pressed, int pb13_pressed){
  uint32_t idr = (1u << 12) | (1u << 13);        
  if (pb12_pressed) idr &= ~(1u << 12);          
  if (pb13_pressed) idr &= ~(1u << 13);
  GPIOB->IDR = idr;
}

static void set_pot(uint16_t raw){
  adc_buf[0] = raw;
  DMA2->S[0].NDTR = ADC_BUF_LEN - 1u;
}

void setUp(void){
  set_buttons(0,0);
  set_pot(2048u);
}
void tearDown(void){}

void test_player_movement(void){
  set_pot(2048u);                                
  TEST_ASSERT_EQUAL_UINT32(64u, player_position());

  set_pot(1024u);
  TEST_ASSERT_EQUAL_UINT32(32u, player_position());
}

void test_player_mov_limit(void){
  set_pot(0u);                                   
  TEST_ASSERT_EQUAL_UINT32(PLAYER_WIDTH / 2u, player_position());

  set_pot(4095u);                                
  TEST_ASSERT_EQUAL_UINT32(128u - PLAYER_WIDTH / 2u, player_position());
}

void test_button_interactions(void){
  set_buttons(0, 0);
  TEST_ASSERT_EQUAL_INT(0, player_press());

  set_buttons(1, 0);
  TEST_ASSERT_EQUAL_INT(1, player_press());

  set_buttons(0, 1);
  TEST_ASSERT_EQUAL_INT(1, player_press());

  set_buttons(1, 1);
  TEST_ASSERT_EQUAL_INT(1, player_press());
}

int main(void){
  UNITY_BEGIN();
  RUN_TEST(test_player_movement);
  RUN_TEST(test_player_mov_limit);
  RUN_TEST(test_button_interactions);
  return UNITY_END();
}
