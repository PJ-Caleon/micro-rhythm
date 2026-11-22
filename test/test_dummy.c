#include "unity.h"
#include "add.h"

void setUp(void){}
void tearDown(void){}

void test_adding(void){
  TEST_ASSERT_EQUAL_INT(5, sum(3,2));
}

int main(void){
  UNITY_BEGIN();
  RUN_TEST(test_adding);
  return UNITY_END();
}

