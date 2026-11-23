#include "button.h"
#include "helper.h"
#include "game_config.h"
#include "FreeRTOS.h"
#include "task.h"

int debounce(debounce_t *d, uint8_t raw, uint32_t now_ms){
  raw = (raw != 0);
  if (raw != d->last){
    d->last = raw;
    d->t_change = now_ms;
    return 0;
  }
  if (raw != d->stable && elapsed(now_ms, d->t_change) >= DEBOUNCE_MS){
    d->stable = (uint8_t)raw;
    return raw;
  }
  return 0;
}

uint8_t buttons_read(void){
  return (uint8_t)(((~GPIOB->IDR) >> 12) & 3u);
}

void button_task(void *arg){
  TaskHandle_t target = (TaskHandle_t)arg;
  static debounce_t db[2u];
  TickType_t last_wake = xTaskGetTickCount();

  for(;;){
    uint32_t raw = buttons_read();
    uint32_t now = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);

    for(uint8_t i = 0; i < 2u; i++){
      if (debounce(&db[i], (raw >> i) & 1u, now)){
        xTaskNotifyGive(target);
      }
    }
    vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(5u));
  }
}
