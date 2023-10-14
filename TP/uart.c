#include "uart.h"
#include "stm32l475xx.h"

void uart_init(){
    RX_TX();
    PB_enclock();
    PLCK();
    reset_USART1();
    Baud_rate_conf();
    oversampling_conf();
    enable_T_R();
}



/* TO DO : Passer les broches RX et TX du port B (à vous de trouver lesquelles) en mode USART . Pour cela, 
    configurez ces broches en mode Alternate Function (registre MODER), 
    et donnez le bon numéro de fonction dans le registre AFRL 
    (numéro que vous trouverez dans la datasheet du processeur).*/
static void RX_TX(){

}





static void PBclocken(){
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN_Msk; // enable port B clock
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // enbel USART1 clock
}

 
static void PLCK(){ // PCLK 
    RCC->CCIPR &= ~RCC_CCIPR_USART1SEL_Msk;
}

static void reset_USART1(){
    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST_Msk; // reset USART1 (cf. p248 ref man)
}

/// ////////////// ************ TO DO ***********//////////////////
//** Configurer la vitesse du port série à 115200 bauds : registres USART1->BRR.**//
static void Baud_rate_conf(){ 
    USART1->BRR = XXXXXXXXXXXXXXXX ;// ( cf p 1388 ref man)

}

/* TO DO : mettre le port série en mode 8N1*/
static void oversampling_conf(){
    USART1->CR1 &= ~USART_CR1_OVER8_Msk; // configurate the over sampling to 16  (p. 1377 ref man)  
}


static void enable_T_R(){ // Enabling the transmitter and reciever ( p. 1379 ref man)
    USART1->CR1 |= USART_CR1_RE_Msk;
    USART1->CR1 |= USART_CR1_TE_Msk;
}

