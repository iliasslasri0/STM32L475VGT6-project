#include <stddef.h>
#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"

extern rgb_color _binary_image_raw_start;

int main(){
	clocks_init();
	//while(1){test_pixels();}
	/* l'init est faite dans ces fonctions */
	// display_image(&_binary_image_raw_start);

	irq_init();
	return 0;
}