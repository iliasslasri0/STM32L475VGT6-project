#include "led.h"
#include "stm32l475xx.h"

/* Pour le toggler */
static uint8_t state_led = 0;

void led_init(){
	// for clock activation
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN_Msk;

	// for GPIO config I or O
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE14_1) | GPIO_MODER_MODE14_0; // to turn the PB14 to GP output mode (p. 303 of the Ref man)
	// GPIOC_MODER = ((GPIOC_MODER & ~(1<<19)) | (1 <<18)); // for PC9, we don't need ... 
}

void led_g_on(){
	GPIOB->BSRR =  GPIO_BSRR_BS14_Msk; // set PB14
	state_led = 1;
}

void led_g_off(){
	GPIOB->BSRR = GPIO_BSRR_BR14_Msk; // reset PB14
	state_led = 0;
}


void led(const enum state x){
	switch (x)
	{
		case LED_OFF:
			GPIOC->MODER = GPIOC->MODER & ~GPIO_MODER_MODE9_Msk;
			break;

		// Here we must change the values in the BSSRegister before activation the output mode to have 
		// the desired function
		case LED_YELLOW:
			GPIOC->BSRR = GPIO_BSRR_BS9_Msk; // set PC9
			GPIOC->MODER = ((GPIOC->MODER & ~GPIO_MODER_MODE9_1) | GPIO_MODER_MODE9_0);
			
			break;

		case LED_BLUE:
			GPIOC->BSRR = GPIO_BSRR_BR9_Msk; // reset PC9
			GPIOC->MODER = ((GPIOC->MODER & ~(GPIO_MODER_MODE9_1)) | (GPIO_MODER_MODE9_0));
			break;
	}
}


void wait(const uint16_t n){
  for(uint8_t i = 0; i<n; i++)
    asm volatile("nop");
}


void toggle_led(){
	// if(state_led)led_g_off();
    // else led_g_on ();


	led_g_on();
	wait(1000);
	led_g_off();
}