#include <stddef.h>
#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"

/* Objet global qui contiendra la trame affichée. Il sera modifé par le handler d'IRQ du port série, et lu par la tâche d'affichage. */
volatile rgb_color frames[64];

int main(){
	clocks_init();
	led_init();
	irq_init();
	button_init();
    matrix_init();
	uart_init(38400);

	USART1->CR1 |= USART_CR1_RXNEIE;
    NVIC_EnableIRQ(37);

    while(1){display_image((rgb_color *)frames);}
	return 0;
}