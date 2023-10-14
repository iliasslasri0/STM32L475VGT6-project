#ifndef LED_H
#define LED_H

#include <stdint.h>

enum state { LED_OFF, LED_YELLOW, LED_BLUE};

void led_init();
void led_g_on();
void led_g_off();
void led(const enum state);
void wait(const uint8_t);

#endif