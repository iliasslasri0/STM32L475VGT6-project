#ifndef MATRIX_H
#define MATRIX_H

#include "stm32l475xx.h"

/* Macros contrôle des broches */
#define SB(value)   do {GPIOC->BSRR = value ? GPIO_BSRR_BS5  : GPIO_BSRR_BR5 ;} while(0)
#define LAT(value)  do {GPIOC->BSRR = value ? GPIO_BSRR_BS4  : GPIO_BSRR_BR4 ;} while(0)
#define RST(value)  do {GPIOC->BSRR = value ? GPIO_BSRR_BS3  : GPIO_BSRR_BR3 ;} while(0)
#define SCK(value)  do {GPIOB->BSRR = value ? GPIO_BSRR_BS1  : GPIO_BSRR_BR1 ;} while(0)
#define SDA(value)  do {GPIOA->BSRR = value ? GPIO_BSRR_BS4  : GPIO_BSRR_BR4 ;} while(0)
#define ROW0(value) do {GPIOB->BSRR = value ? GPIO_BSRR_BS2  : GPIO_BSRR_BR2 ;} while(0)
#define ROW1(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS15 : GPIO_BSRR_BR15;} while(0)
#define ROW2(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS2  : GPIO_BSRR_BR2 ;} while(0) 
#define ROW3(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS7  : GPIO_BSRR_BR7 ;} while(0) 
#define ROW4(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS6  : GPIO_BSRR_BR6 ;} while(0) 
#define ROW5(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS5  : GPIO_BSRR_BR5 ;} while(0) 
#define ROW6(value) do {GPIOB->BSRR = value ? GPIO_BSRR_BS0  : GPIO_BSRR_BR0 ;} while(0) 
#define ROW7(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS3  : GPIO_BSRR_BR3 ;} while(0) 


typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;

void test_pixels(void);
void display_image(const rgb_color * );
void matrix_init();
#endif