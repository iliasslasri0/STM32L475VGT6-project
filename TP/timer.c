#include "timer.h"

void timer_init(int max_us){

    /* Active l'horloge du timer TIM2 */
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    /* effacer d'éventuels flags dans le registre de statut (TIMx_SR) 
    et mettre à zéro la valeur du compteur (TIMx_CNT)*/
    TIM2->SR = TIM2->SR & 0x0; // reset value is 0x0
    TIM2->CNT = TIM2->CNT & ~TIM_CNT_CNT;

    
}
