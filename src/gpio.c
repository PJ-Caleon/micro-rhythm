#include "gpio.h"
#include "helper.h"

void gpio_clock_init(void){
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  (void)RCC->AHB1ENR;
}

void buttons_init(void){
  gpio_cfg(GPIOB, 12u, GPIO_IN_PULLUP);
  gpio_cfg(GPIOB, 13u, GPIO_IN_PULLUP);
}

void pot_init(void){
  gpio_cfg(GPIOA, 1u, GPIO_ANALOG);
}

void oled_init(void){
  // SCL 
  gpio_cfg(GPIOB, 6u, GPIO_AF_OD); 
  gpio_af(GPIOB, 6u, 4u);

  // SDA 
  gpio_cfg(GPIOB, 7u, GPIO_AF_OD);
  gpio_af(GPIOB, 7u, 4u);

  GPIOB->OSPEEDR = field_set(GPIOB->OSPEEDR, 6u * 2u, 2u, 2u);
  GPIOB->OSPEEDR = field_set(GPIOB->OSPEEDR, 7u * 2u, 2u, 2u);
}

void usart1_init(void){
  // USART1 TX 
  gpio_cfg(GPIOA, 9u, GPIO_AF_PP);
  gpio_af(GPIOA, 9u, 7u);

  // USART1 RX
  gpio_cfg(GPIOA, 10u, GPIO_MODE(2u, 0u, 1u));
  gpio_af(GPIOA, 10u, 7u);

  GPIOA->OSPEEDR = field_set(GPIOA->OSPEEDR, 9u * 2u, 2u, 2u);
}
