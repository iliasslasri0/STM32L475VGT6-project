#include <stddef.h>
#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"

extern rgb_color _binary_image_raw_start;

int main(){
	clocks_init();
	led_init();
	irq_init();
	button_init();
    matrix_init();
	display_image(&_binary_image_raw_start);
	return 0;
}