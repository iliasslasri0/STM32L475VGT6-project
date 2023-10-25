#include <stddef.h>
#include "uart.h"
#include "stm32l475xx.h"


/* Passer les broches RX et TX du port B (à vous de trouver lesquelles) en mode USART . Pour cela, 
    configurez ces broches en mode Alternate Function (registre MODER), 
    et donnez le bon numéro de fonction dans le registre AFRL 
    (numéro que vous trouverez dans la datasheet du processeur).*/
/* TX: PB6, RX: PB7  (cf p70 stm32l475xx_ds )*/
static void RX_TX(){

    // Les broches en mode AF
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE6_0) | GPIO_MODER_MODE6_1; // 10
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7_0) | GPIO_MODER_MODE7_1;

    // Les broches en AF7 
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL6_Msk) | (7 << GPIO_AFRL_AFSEL6_Pos); // 0111
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL7_Msk) | (7 << GPIO_AFRL_AFSEL7_Pos); // 0111
    //GPIOB->AFR[0] &= (GPIO_AFRL_AFSEL7_Msk & ~(1<<(GPIO_AFRL_AFSEL7_Pos + 3))); // 0111
}


static void PB_enclock(){
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN_Msk; // enable port B clock
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // enable USART1 clock
}

 
static void PLCK(){ // PCLK 
    RCC->CCIPR &= ~RCC_CCIPR_USART1SEL_Msk;
}


static void reset_USART1(){
    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST_Msk; // reset USART1 (cf. p248 ref man)
    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST_Msk; // reset USART1 (cf. p248 ref man)
}

//** Configurer la vitesse du port série à 115200 bauds : registres USART1->BRR.**//
static void Baud_rate_conf(){ 
    USART1->BRR = 80000000 / 115200 ;// ( cf p 1388 ref man)

}

/* mettre le port série en mode 8N1 */
static void oversampling_conf(){
    USART1->CR1 &= ~USART_CR1_OVER8_Msk; // configurate the over sampling to 16  (p. 1377 ref man)

    /// mettre le port série en mode 8N1
    USART1->CR1 &= ~USART_CR1_M_Msk; 
    USART1->CR1 &= ~USART_CR1_PCE_Msk; // Parity control disabled
    USART1->CR2 &= ~USART_CR2_STOP_Msk; // 1 stop bit (cf. page 1880 of ref man)
}


static void enable_T_R(){ // Enabling the transmitter and reciever ( p. 1379 ref man)
    USART1->CR1 |= USART_CR1_RE_Msk;
    USART1->CR1 |= USART_CR1_TE_Msk;
    USART1->CR1 |= USART_CR1_UE;
}


/*** INIT ****/
void uart_init(){
    PB_enclock();
    RX_TX();
    PLCK();
    reset_USART1();
    Baud_rate_conf();
    oversampling_conf();
    enable_T_R();
}


/* Attend que l'USART1 soit prêt à transmettre quelque chose, puis lui demande de l'envoyer */
void uart_putchar(uint8_t c){
    uint8_t x;
    do { x = (USART1->ISR) & USART_ISR_TXE_Msk; }while (!x); // ( cf ref man 1394)
    USART1->TDR = c;
}


/* Attend que l'UART ait reçu un caractère puis le retourne  */
int8_t uart_getchar(){
    uint8_t x;
    do {
        if( ( (USART1->ISR) & USART_ISR_ORE_Msk ) | ( (USART1->ISR) & USART_ISR_FE_Msk ) ){
            while(1);
        }
        x = (USART1->ISR) & USART_ISR_RXNE_Msk;

    }while(!x);
    return (int8_t)USART1->RDR;
}


/* fonction qui fait la même chose que puts sous Linux */
void uart_puts(const char *s){
    while(*s){
        uart_putchar((uint8_t )*s);
        s++;
    }
}


void uart_gets(char *s, size_t size){
    for(int i=0; i<(int)size - 1; i++){
        *(s+i) = (char) uart_getchar();
    }
    *(s+ size) = '\n';
}


void echo(){
    while(1)
        uart_putchar(uart_getchar());
}


uint32_t checksum(){
    uint32_t S = 0;
    int i = 1000;
    while(i--)
        S += uart_getchar();

    return S;
}