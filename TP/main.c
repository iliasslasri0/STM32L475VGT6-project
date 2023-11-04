#include <stddef.h>
#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"

int _exit = 0;

int main(){
	clocks_init();
	test_pixels();
	while(!_exit);
	return 0;
}