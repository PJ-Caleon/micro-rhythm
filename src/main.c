#include <stdint.h>
#include "clock.h"
#include "gpio.h"
#include "helper.h"
#include "button.h"
#include "adc.h"
#include "dma.h"
#include "FreeRTOS.h"
#include "task.h"

static TaskHandle_t game_handle;

static void blink_test(void *arg){
  (void)arg;

  for(;;){
   GPIOC->ODR ^= (1u << 13);
   vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName){
  (void)xTask;
  (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  for(;;){}
}

static void game_task(void *arg){
  (void)arg;
  for(;;){
    uint32_t clicks = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    (void)clicks;   
  }
}

int main(void){
  // setup 
  clock_init();
  
  gpio_clock_init();
  buttons_init();
  pot_init();
  led_init();

  dma_init();
  adc_init();

  xTaskCreate(blink_test, "blink", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
  xTaskCreate(game_task,   "game", 256, NULL,                 tskIDLE_PRIORITY + 1, &game_handle);
  xTaskCreate(button_task, "btn",  128, (void *)game_handle,  tskIDLE_PRIORITY + 2, NULL);

  vTaskStartScheduler();
  for(;;){}
}
