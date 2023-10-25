#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;


void matrix_init();
void pulse_SCK();
void pulse_LAT();
void deactivate_rows();
void activate_row(int);
void send_byte(uint8_t , int );
void mat_set_row(int , const rgb_color *);
void init_bank0();

#endif