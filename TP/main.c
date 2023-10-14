#include "led.h"
#include "clocks.h"

int _exit = 0;

int main(){
	clocks_init();
	led_init();
	for(int i=0; i< 50; i++){
		
		led_g_on();
		wait(20);

		led_g_off();
		wait(20);

		led(LED_YELLOW);
		wait(20);
		
		led(LED_OFF);

		led(LED_BLUE);
		wait(20);

		led(LED_OFF);
	}
	while(!_exit);
	return 0;
}