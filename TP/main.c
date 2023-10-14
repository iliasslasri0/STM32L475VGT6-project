#include "led.h"

int _exit = 0;

int main(){

	led_init();
	for(int i=0; i< 50; i++){
		
		led_g_on();
		asm volatile("nop");

		led_g_off();
		asm volatile("nop");

		led(LED_YELLOW);
		asm volatile("nop");
		
		led(LED_OFF);

		led(LED_BLUE);
		asm volatile("nop");

		led(LED_OFF);
	}
	while(!_exit);
	return 0;
}