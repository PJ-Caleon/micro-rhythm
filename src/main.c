#include <stdint.h>
#include "clock.h"
#include "gpio.h"
#include "helper.h"

uint32_t a = 10;

int main(void){
  // setup 
  clock_init();
  
  gpio_clock_init();
  buttons_init();

  // loop 
  for (;;){

  }
}
