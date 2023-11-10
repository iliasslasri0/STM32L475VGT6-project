#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stddef.h>
#include "stm32l475xx.h"

void uart_init();

void uart_putchar(uint8_t); 
int8_t uart_getchar();

void uart_puts(const char *);
void uart_gets(char *, size_t );


void echo();
uint32_t checksum();
void USART1_IRQHandler();


/* OBJETS GLOBAUX */

/* err = 0 : No FE ou OR error
    err = 1 : FE ou OR error   */
extern uint8_t err;

extern volatile uint8_t frames[192]; // 8*8*3 = 192

#endif