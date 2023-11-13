#include <stddef.h>
#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"
#include "timer.h"

/* Objet global qui contiendra la trame affichée. Il sera modifé par le handler d'IRQ du port série, et lu par la tâche d'affichage. */
volatile uint8_t frames[192];
uint8_t err = 0;

int main(){
	clocks_init();
	led_init();
	irq_init();
	button_init();
    matrix_init();
	uart_init(38400);

	// Initialiser le timer
    timer_init((int)(10000/8));
	while(1);
	return 0;
}