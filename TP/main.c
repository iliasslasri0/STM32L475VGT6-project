#include <stddef.h>
#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"


int main(){
	clocks_init();
	while(1){test_pixels();}
	return 0;
}