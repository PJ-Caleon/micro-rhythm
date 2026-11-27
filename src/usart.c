#include "usart.h"
#include "gpio.h"
#include "controller.h"
#include "button.h"
#include "stm32f401.h"

#define USART_BAUD 115200u

static void usart_putc(char c){
  while(!(USART1->SR & USART_SR_TXE)){}
  USART1->DR = (uint32_t)c;
}

static void usart_puts(const char *s){
  while(*s){ usart_putc(*s++); }
}

static void usart_put_u32(uint32_t v){
  char buf[11];
  unsigned i = 0;
  do {
    buf[i++] = (char)('0' + (v % 10u));
    v /= 10u;
  } while(v);
  while(i){ usart_putc(buf[--i]); }
}

void usart_init(void){
  // GPIO pins
  usart1_init();

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  (void)RCC->APB2ENR;

  USART1->BRR = (SYSCLK_HZ + USART_BAUD / 2u) / USART_BAUD;   // 729
  USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void serial_print(const char *label, uint32_t value){
  usart_puts(label);
  usart_puts("=");
  usart_put_u32(value);
  usart_puts("\r\n");
}
