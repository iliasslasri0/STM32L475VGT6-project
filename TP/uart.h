#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stddef.h>

void uart_init();

void uart_putchar(uint8_t); 
int8_t uart_getchar();

void uart_puts(const char *);
void uart_gets(char *, size_t );


void echo();
uint32_t checksum();

#endif