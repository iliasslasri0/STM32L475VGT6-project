#include "led.h"

void led_init(){
	// for clock activation
	RCC_AHB2ENR |= (1 << 1) ; // set the bit 1 to 1 (p. 251 of the Ref man)
	RCC_AHB2ENR |= (1 << 2) ; // for GPIOC EN

	// for GPIO config I or O
	GPIOB_MODER = ((GPIOB_MODER & ~(1<<29)) | (1 <<28)); // to turn the PB14 to GP output mode (p. 303 of the Ref man)
	// GPIOC_MODER = ((GPIOC_MODER & ~(1<<19)) | (1 <<18)); // for PC9, we don't need ... 
}

void led_g_on(){
	GPIOB_BSRR =  (1 << 14); // set PB14
}

void led_g_off(){
	GPIOB_BSRR = (1 << (14 + 16)); // reset PB14
}


void led(const enum state x){
	switch (x)
	{
		case LED_OFF:
			GPIOC_MODER = ((GPIOC_MODER & ~(1<<19)) & ~(1 <<18));
			break;

		// Here we must change the values in the BSSRegister before activation the output mode to have 
		// the desired function
		case LED_YELLOW:
			GPIOC_BSRR = (1 << 9 ); // set PC9
			GPIOC_MODER = ((GPIOC_MODER & ~(1<<19)) | (1 <<18));
			
			break;

		case LED_BLUE:
			GPIOC_BSRR = (1 << (9+16) ); // reset PC9
			GPIOC_MODER = ((GPIOC_MODER & ~(1<<19)) | (1 <<18));
			break;
	}
}