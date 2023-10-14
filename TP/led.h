#ifndef LED_H
#define LED_H

#include <stdint.h>

#define RCC_AHB2ENR  (*(volatile uint32_t *)0x4002104C)

#define GPIOB_MODER (*(volatile uint32_t *)0x48000400)
#define GPIOC_MODER (*(volatile uint32_t *)0x48000800)

#define GPIOB_BSRR (*(volatile uint32_t *)0x48000418)
#define GPIOC_BSRR (*(volatile uint32_t *)0x48000818)

enum state { LED_OFF, LED_YELLOW, LED_BLUE};

void led_init();
void led_g_on();
void led_g_off();
void led(const enum state);

#endif