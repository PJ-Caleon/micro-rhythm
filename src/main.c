#include <stdint.h>
#include "clock.h"
#include "gpio.h"
#include "helper.h"
#include "FreeRTOS.h"
#include "task.h"

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName){
  (void)xTask;
  (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  for(;;){}
}

int main(void){
  // setup 
  clock_init();
  
  gpio_clock_init();
  buttons_init();

  // loop 
  for (;;){

  }
}
