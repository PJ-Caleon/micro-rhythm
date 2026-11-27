#include <stdint.h>
#include "clock.h"
#include "gpio.h"
#include "helper.h"
#include "button.h"
#include "adc.h"
#include "dma.h"
#include "usart.h"
#include "controller.h"
#include "rng.h"
#include "game_logic.h"
#include "FreeRTOS.h"
#include "task.h"

static TaskHandle_t game_handle;

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName){
  (void)xTask;
  (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  for(;;){}
}

static void serial_task(void *arg){
  (void)arg; 
  for (;;){
    //serial_print("pot",    player_position());  
    //serial_print("button", buttons_read());
    //serial_print("falling", object_falling(1));
    //serial_print("rng", random(0xABCDABCD));

    vTaskDelay(pdMS_TO_TICKS(200));
  }
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

  dma_init();
  adc_init();
  usart_init();

  xTaskCreate(game_task,   "game", 256, NULL,                 tskIDLE_PRIORITY + 1, &game_handle);
  xTaskCreate(button_task, "btn",  128, (void *)game_handle,  tskIDLE_PRIORITY + 2, NULL);
  xTaskCreate(serial_task, "serial", 128, NULL, tskIDLE_PRIORITY + 1, NULL);

  vTaskStartScheduler();
}
