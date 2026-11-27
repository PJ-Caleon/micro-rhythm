#include <unity.h>
#include "game_logic.h"

void setUp(void) {}
void tearDown(void) {}

void test_example_from_spec(void){
  TEST_ASSERT_EQUAL_STRING("00000100", spawn(0, 12456743));
}

void test_max_at_first_digit(void){
  TEST_ASSERT_EQUAL_STRING("10000", spawn(0, 98765));
}

void test_max_at_last_digit(void){
  TEST_ASSERT_EQUAL_STRING("00001", spawn(0, 12345));
}

void test_tie_picks_leftmost(void){
  TEST_ASSERT_EQUAL_STRING("0100", spawn(0, 3434));
}

void test_two_digits(void){
  TEST_ASSERT_EQUAL_STRING("10", spawn(0, 91));
}

void test_pos_example(void){
  TEST_ASSERT_EQUAL_UINT8(5, spawn_pos((char *)"00000100"));
}

void test_pos_first(void){
  TEST_ASSERT_EQUAL_UINT8(0, spawn_pos((char *)"10000"));
}

void test_pos_last_of_12(void){
  TEST_ASSERT_EQUAL_UINT8(11, spawn_pos((char *)"000000000001"));
}

void test_pos_not_found(void){
  TEST_ASSERT_EQUAL_UINT8(0xFF, spawn_pos((char *)"0000"));
}

void test_collision_x_out(void){
  TEST_ASSERT_EQUAL_UINT8(0, is_collision(6, 0, 3, 0));
}

int main(void){
  UNITY_BEGIN();
  RUN_TEST(test_example_from_spec);
  RUN_TEST(test_max_at_first_digit);
  RUN_TEST(test_max_at_last_digit);
  RUN_TEST(test_tie_picks_leftmost);
  RUN_TEST(test_two_digits);

  RUN_TEST(test_pos_example);
  RUN_TEST(test_pos_first);
  RUN_TEST(test_pos_last_of_12);
  RUN_TEST(test_pos_not_found);

  RUN_TEST(test_collision_x_out);
  return UNITY_END();
}
