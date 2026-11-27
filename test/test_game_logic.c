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

int main(void){
  UNITY_BEGIN();
  RUN_TEST(test_example_from_spec);
  RUN_TEST(test_max_at_first_digit);
  RUN_TEST(test_max_at_last_digit);
  RUN_TEST(test_tie_picks_leftmost);
  RUN_TEST(test_two_digits);
  return UNITY_END();
}
