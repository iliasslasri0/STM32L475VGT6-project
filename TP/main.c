#include <stddef.h>
#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"

int _exit = 0;

int main(){
	clocks_init();
	// uart_init();

	// uint8_t s1 = 'a';

	// uart_putchar(s1);
	
	// const char s[] = "Hello World!\n";
	// uart_puts(s);
    
	// int S = checksum();

	// uint8_t data[4];

	// /* Pour afficher notre somme, on divise ( shift et mask pour n'avoir que les bits voulue et tt les autres à 0)
	//  le int32 sur 4 int8 pour pouvoir le transmettre */
    // data[0] = (uint8_t)((S >> 24) & 0xFF);
    // data[1] = (uint8_t)((S >> 16) & 0xFF);
    // data[2] = (uint8_t)((S >> 8) & 0xFF);
    // data[3] = (uint8_t)(S & 0xFF);

    // for (int i = 0; i < 4; i++) {
    //     uart_putchar(data[i]);
    // }

	test_pixels();
	while(!_exit);
	return 0;
}