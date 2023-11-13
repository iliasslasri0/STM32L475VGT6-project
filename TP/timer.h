#ifndef TIMER_H_
#define TIMER_H_

#include "stm32l475xx.h"
#include <stdint.h>
#include "led.h"
#include "matrix.h"


void timer_init(int );
void TIM2_IRQHandler();

extern volatile uint8_t frames[192];

#endif