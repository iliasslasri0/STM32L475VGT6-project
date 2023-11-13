#include "timer.h"

void timer_init(int max_us){

    /* Active l'horloge du timer TIM2 */
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    /* effacer d'éventuels flags dans le registre de statut (TIMx_SR) 
    et mettre à zéro la valeur du compteur (TIMx_CNT)*/
    TIM2->SR = TIM2->SR & ~TIM_SR_UIF; // reset value is 0x0
    TIM2->CNT = TIM2->CNT & ~TIM_CNT_CNT; // c'est 0 aussi

    /* Configurer le timer pour avoir le bon mode de fonctionnement, sans l'activer */
    TIM2->CR1 |= TIM_CR1_CKD_1;

    /* Changer le prescaler du timer (TIMx_PSC) pour compter à la microseconde
        La fréquence du timer est la fréquence de l'horloge principale (SYSCLK)
        Divisée par le prescaler + 1.
        Timer frequency = (System Clock / (prescaler + 1))
        Dans ce cas, on veut que le timer compte à 1 MHz (1 microseconde)*/
    uint32_t prescaler_value = (80000000 / 1000000) - 1;
    TIM2->PSC = prescaler_value;

    /* Modifier la valeur d'auto chargement (TIMx_ARR) en fonction du paramètre de la fonction */
    TIM2->ARR =  max_us;

    /* Autoriser la génération d'une interruption sur l'événement de mise à jour du timer (TIMx_DIER) */
    TIM2->DIER |= TIM_DIER_UIE_Msk;

    /* Autoriser l'interruption de TIM2 au niveau du NVIC !!! TODO : Nouveau handler */
    NVIC_EnableIRQ(28);

    /* Activer le timer*/
    TIM2->CR1 |= TIM_CR1_CEN;
}


void TIM2_IRQHandler(){
    /* Vérifier si c'est l'interruption de mise à jour (UIF) */
    if(TIM2->SR & TIM_SR_UIF_Msk){
        display_image((rgb_color *)frames);
        TIM2->SR &= ~TIM_SR_UIF;
    }
}