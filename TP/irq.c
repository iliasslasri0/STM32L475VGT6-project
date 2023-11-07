#include "irq.h"

#define MAKE_DEFAULT_HANDLER(truc_IRQHandler) \
    void __attribute__((weak)) truc_IRQHandler(void) { \
        // Désactiver toutes les interruptions
        __asm__ ("cpsid i")\
        while(1);}

extern int _strt_stack, _start;

void * const vector_table[] = {
    // Stack and Reset Handler
    &_strt_stack,            /* Top of stack  (initial value of the SP register) */
    _start,             /* Reset handler (initial value of the PC register) */

    // ARM internal exceptions
    NonMaskableInt_IRQn,
    HardFault_IRQn,
    MemoryManagement_IRQn,
    BusFault_IRQn,
    UsageFault_IRQn,
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    SVCall_IRQn,        /* SVC handler */
    0,                  /* Reserved */
    0,                  /* Reserved */
    PendSV_IRQn,     /* Pending SVC handler */
    SysTick_IRQn,    /* SysTick hanlder */

    // STM32L475 External interrupts
    WWDG_IRQn                   ,      /*!< Window WatchDog Interrupt                                         */
    PVD_PVM_IRQn                ,      /*!< PVD/PVM1/PVM2/PVM3/PVM4 through EXTI Line detection Interrupts    */
    TAMP_STAMP_IRQn             ,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
    RTC_WKUP_IRQn               ,      /*!< RTC Wakeup interrupt through the EXTI line                        */
    FLASH_IRQn                  ,      /*!< FLASH global Interrupt                                            */
    RCC_IRQn                    ,      /*!< RCC global Interrupt                                              */
    EXTI0_IRQn                  ,      /*!< EXTI Line0 Interrupt                                              */
    EXTI1_IRQn                  ,      /*!< EXTI Line1 Interrupt                                              */
    EXTI2_IRQn                  ,      /*!< EXTI Line2 Interrupt                                              */
    EXTI3_IRQn                  ,      /*!< EXTI Line3 Interrupt                                              */
    EXTI4_IRQn                  ,     /*!< EXTI Line4 Interrupt                                              */
    DMA1_Channel1_IRQn          ,     /*!< DMA1 Channel 1 global Interrupt                                   */
    DMA1_Channel2_IRQn          ,     /*!< DMA1 Channel 2 global Interrupt                                   */
    DMA1_Channel3_IRQn          ,     /*!< DMA1 Channel 3 global Interrupt                                   */
    DMA1_Channel4_IRQn          ,     /*!< DMA1 Channel 4 global Interrupt                                   */
    DMA1_Channel5_IRQn          ,     /*!< DMA1 Channel 5 global Interrupt                                   */
    DMA1_Channel6_IRQn          ,     /*!< DMA1 Channel 6 global Interrupt                                   */
    DMA1_Channel7_IRQn          ,     /*!< DMA1 Channel 7 global Interrupt                                   */
    ADC1_2_IRQn                 ,     /*!< ADC1, ADC2 SAR global Interrupts                                  */
    CAN1_TX_IRQn                ,     /*!< CAN1 TX Interrupt                                                 */
    CAN1_RX0_IRQn               ,     /*!< CAN1 RX0 Interrupt                                                */
    CAN1_RX1_IRQn               ,     /*!< CAN1 RX1 Interrupt                                                */
    CAN1_SCE_IRQn               ,     /*!< CAN1 SCE Interrupt                                                */
    EXTI9_5_IRQn                ,     /*!< External Line[9:5] Interrupts                                     */
    TIM1_BRK_TIM15_IRQn         ,     /*!< TIM1 Break interrupt and TIM15 global interrupt                   */
    TIM1_UP_TIM16_IRQn          ,     /*!< TIM1 Update Interrupt and TIM16 global interrupt                  */
    TIM1_TRG_COM_TIM17_IRQn     ,     /*!< TIM1 Trigger and Commutation Interrupt and TIM17 global interrupt */
    TIM1_CC_IRQn                ,     /*!< TIM1 Capture Compare Interrupt                                    */
    TIM2_IRQn                   ,     /*!< TIM2 global Interrupt                                             */
    TIM3_IRQn                   ,     /*!< TIM3 global Interrupt                                             */
    TIM4_IRQn                   ,     /*!< TIM4 global Interrupt                                             */
    I2C1_EV_IRQn                ,     /*!< I2C1 Event Interrupt                                              */
    I2C1_ER_IRQn                ,     /*!< I2C1 Error Interrupt                                              */
    I2C2_EV_IRQn                ,     /*!< I2C2 Event Interrupt                                              */
    I2C2_ER_IRQn                ,     /*!< I2C2 Error Interrupt                                              */
    SPI1_IRQn                   ,     /*!< SPI1 global Interrupt                                             */
    SPI2_IRQn                   ,     /*!< SPI2 global Interrupt                                             */
    USART1_IRQn                 ,     /*!< USART1 global Interrupt                                           */
    USART2_IRQn                 ,     /*!< USART2 global Interrupt                                           */
    USART3_IRQn                 ,     /*!< USART3 global Interrupt                                           */
    EXTI15_10_IRQn              ,     /*!< External Line[15:10] Interrupts                                   */
    RTC_Alarm_IRQn              ,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
    DFSDM1_FLT3_IRQn            ,     /*!< DFSDM1 Filter 3 global Interrupt                                  */
    TIM8_BRK_IRQn               ,     /*!< TIM8 Break Interrupt                                              */
    TIM8_UP_IRQn                ,     /*!< TIM8 Update Interrupt                                             */
    TIM8_TRG_COM_IRQn           ,     /*!< TIM8 Trigger and Commutation Interrupt                            */
    TIM8_CC_IRQn                ,     /*!< TIM8 Capture Compare Interrupt                                    */
    ADC3_IRQn                   ,     /*!< ADC3 global  Interrupt                                            */
    FMC_IRQn                    ,     /*!< FMC global Interrupt                                              */
    SDMMC1_IRQn                 ,     /*!< SDMMC1 global Interrupt                                           */
    TIM5_IRQn                   ,     /*!< TIM5 global Interrupt                                             */
    SPI3_IRQn                   ,     /*!< SPI3 global Interrupt                                             */
    UART4_IRQn                  ,     /*!< UART4 global Interrupt                                            */
    UART5_IRQn                  ,     /*!< UART5 global Interrupt                                            */
    TIM6_DAC_IRQn               ,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
    TIM7_IRQn                   ,     /*!< TIM7 global interrupt                                             */
    DMA2_Channel1_IRQn          ,     /*!< DMA2 Channel 1 global Interrupt                                   */
    DMA2_Channel2_IRQn          ,     /*!< DMA2 Channel 2 global Interrupt                                   */
    DMA2_Channel3_IRQn          ,     /*!< DMA2 Channel 3 global Interrupt                                   */
    DMA2_Channel4_IRQn          ,     /*!< DMA2 Channel 4 global Interrupt                                   */
    DMA2_Channel5_IRQn          ,     /*!< DMA2 Channel 5 global Interrupt                                   */
    DFSDM1_FLT0_IRQn            ,     /*!< DFSDM1 Filter 0 global Interrupt                                  */
    DFSDM1_FLT1_IRQn            ,     /*!< DFSDM1 Filter 1 global Interrupt                                  */
    DFSDM1_FLT2_IRQn            ,     /*!< DFSDM1 Filter 2 global Interrupt                                  */
    COMP_IRQn                   ,     /*!< COMP1 and COMP2 Interrupts                                        */
    LPTIM1_IRQn                 ,     /*!< LP TIM1 interrupt                                                 */
    LPTIM2_IRQn                 ,     /*!< LP TIM2 interrupt                                                 */
    OTG_FS_IRQn                 ,     /*!< USB OTG FS global Interrupt                                       */
    DMA2_Channel6_IRQn          ,     /*!< DMA2 Channel 6 global interrupt                                   */
    DMA2_Channel7_IRQn          ,     /*!< DMA2 Channel 7 global interrupt                                   */
    LPUART1_IRQn                ,     /*!< LP UART1 interrupt                                                */
    QUADSPI_IRQn                ,     /*!< Quad SPI global interrupt                                         */
    I2C3_EV_IRQn                ,     /*!< I2C3 event interrupt                                              */
    I2C3_ER_IRQn                ,     /*!< I2C3 error interrupt                                              */
    SAI1_IRQn                   ,     /*!< Serial Audio Interface 1 global interrupt                         */
    SAI2_IRQn                   ,     /*!< Serial Audio Interface 2 global interrupt                         */
    SWPMI1_IRQn                 ,     /*!< Serial Wire Interface 1 global interrupt                          */
    TSC_IRQn                    ,     /*!< Touch Sense Controller global interrupt                           */
    RNG_IRQn                    ,     /*!< RNG global interrupt                                              */
    FPU_IRQn                     ,     /*!< FPU global interrupt                                              */
};


void irq_init(void){
    SCB->VTOR = (uint32_t) vector_table;
}