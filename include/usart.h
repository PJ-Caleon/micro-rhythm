#ifndef USART_H 
#define USART_H

#include <stdint.h>

void usart_init(void);
void serial_print(const char *label, uint32_t value);

#endif
