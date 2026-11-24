#include "unity.h"
#include "rng.h"

void setUp(void){}
void tearDown(void){}

void test_lfsr(void) {
  static uint32_t pre_seed = 0x1234ABCEu;
  TEST_ASSERT_EQUAL_HEX32(0x891A55E7, random(pre_seed));
  TEST_ASSERT_EQUAL_HEX32(0xCD977F14, random(pre_seed));
  TEST_ASSERT_EQUAL_HEX32(0xAB5CC09E, random(pre_seed));
  TEST_ASSERT_EQUAL_HEX32(0x7EF2A0D1, random(pre_seed));
  TEST_ASSERT_EQUAL_HEX32(0xC18BF0B9, random(pre_seed));
  TEST_ASSERT_EQUAL_HEX32(0x214E08E5, random(pre_seed));
}

void test_reject_zero_seed(void){
  static uint16_t pre_seed = 0x00000000;
  TEST_ASSERT_EQUAL_INT(-1, random(pre_seed));
}

int main(void){
  UNITY_BEGIN();
  RUN_TEST(test_reject_zero_seed);
  RUN_TEST(test_lfsr);
  return UNITY_END();
}
