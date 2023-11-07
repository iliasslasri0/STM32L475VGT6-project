#include "buttons.h"
#include "led.h"
static void hard_interrupt_sel();

void button_init(void){
    led_init();
    // enable port C clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN_Msk;

    // configure la broche PC13 en GPIO et en entrée
    GPIOC->MODER = GPIOC->MODER & ~GPIO_MODER_MODE13;

    // sélectionne la broche PC13 comme source d'IRQ pour EXTI13 (registre SYSCFG_EXTICRn, cf page 403)
    SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] & ~SYSCFG_EXTICR4_EXTI13_Msk) | SYSCFG_EXTICR4_EXTI13_PC; /// TODO : pas sûr mais on veut mettre ( 0x2 = 0b0010)

    // Hardware interrupt selection
    hard_interrupt_sel();

}


/* Hardware interrupt selection */
static void hard_interrupt_sel(){

    EXTI->IMR1 |= EXTI_IMR1_IM13_Msk;

    EXTI->RTSR1 &= ~EXTI_RTSR1_RT13_Msk;
    
    EXTI->FTSR1 |= EXTI_FTSR1_FT13_Msk;

    NVIC_EnableIRQ(40);
}


void EXTI15_10_IRQHandler(void){
    //acquittement de l'interruption dans l'EXTI
    EXTI->PR1 |= EXTI_PR1_PIF13_Msk;
    toggle_led();
}