#include "unity.h"
#include "rng.h"

void setUp(void){}
void tearDown(void){}

void test_lfsr(void){
  static uint16_t pre_seed = 0b1001010111000111u;
  TEST_ASSERT_EQUAL_INT(1, random(pre_seed));
  TEST_ASSERT_EQUAL_INT(1, random(pre_seed));
  TEST_ASSERT_EQUAL_INT(0, random(pre_seed));
  TEST_ASSERT_EQUAL_INT(0, random(pre_seed));
  TEST_ASSERT_EQUAL_INT(0, random(pre_seed));
  TEST_ASSERT_EQUAL_INT(1, random(pre_seed));
}

void test_reject_zero_seed(void){
  static uint16_t pre_seed = 0b0000000000000000u;
  TEST_ASSERT_EQUAL_INT(-1, random(pre_seed));
}

int main(void){
  UNITY_BEGIN();
  RUN_TEST(test_reject_zero_seed);
  RUN_TEST(test_lfsr);
  return UNITY_END();
}
