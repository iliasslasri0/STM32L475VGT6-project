// #include "matrix.h"
#include "stm32l475xx.h"
#include "matrix.h"

/* Macros contrôle des broches */
#define SB(value)   (GPIOC->BSRR = value ? GPIO_BSRR_BS5_Msk : GPIO_BSRR_BR5_Msk)
#define LAT(value)  (GPIOC->BSRR = value ? GPIO_BSRR_BS4_Msk : GPIO_BSRR_BR4_Msk)
#define RST(value)  (GPIOC->BSRR = value ? GPIO_BSRR_BS3_Msk : GPIO_BSRR_BR3_Msk)
#define SCK(value)  (GPIOB->BSRR = value ? GPIO_BSRR_BS1_Msk : GPIO_BSRR_BR1_Msk)
#define SDA(value)  (GPIOA->BSRR = value ? GPIO_BSRR_BS4_Msk : GPIO_BSRR_BR4_Msk)
#define ROW0(value) (GPIOB->BSRR = value ? GPIO_BSRR_BS2_Msk : GPIO_BSRR_BR2_Msk)
#define ROW1(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS15_Msk : GPIO_BSRR_BR15_Msk)
#define ROW2(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS2_Msk : GPIO_BSRR_BR2_Msk)
#define ROW3(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS7_Msk : GPIO_BSRR_BR7_Msk)
#define ROW4(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS6_Msk : GPIO_BSRR_BR6_Msk)
#define ROW5(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS5_Msk : GPIO_BSRR_BR5_Msk)
#define ROW6(value) (GPIOB->BSRR = value ? GPIO_BSRR_BS0_Msk : GPIO_BSRR_BR0_Msk)
#define ROW7(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS3_Msk : GPIO_BSRR_BR3_Msk)



/* Configurer les ports en vitesse max  */
static void vitesse_max(){
    GPIOC->OSPEEDR |=  GPIO_OSPEEDR_OSPEED3_Msk | GPIO_OSPEEDR_OSPEED4_Msk | GPIO_OSPEEDR_OSPEED5_Msk;  
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_Msk | GPIO_OSPEEDR_OSPEED0_Msk| GPIO_OSPEEDR_OSPEED2_Msk; 
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED15_Msk| GPIO_OSPEEDR_OSPEED3_Msk | GPIO_OSPEEDR_OSPEED5_Msk | GPIO_OSPEEDR_OSPEED4_Msk | GPIO_OSPEEDR_OSPEED2_Msk | GPIO_OSPEEDR_OSPEED7_Msk | GPIO_OSPEEDR_OSPEED6_Msk;
} 


/* configure toutes les broches reliées au driver en mode GPIO Output */
static void ouput_mode(){
    // PB5
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE5_1) | GPIO_MODER_MODE5_0;

    // PB4
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE4_1) | GPIO_MODER_MODE4_0;
    
    // PB3
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE3_1) | GPIO_MODER_MODE3_0;

    // PA4
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4_1) | GPIO_MODER_MODE4_0;

    // PB2
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE2_1) | GPIO_MODER_MODE2_0;

    // PA15
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE15_1) | GPIO_MODER_MODE15_0;

    // PA2
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2_1) | GPIO_MODER_MODE2_0;

    // PA7
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7_1) | GPIO_MODER_MODE7_0;

    // PA6
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6_1) | GPIO_MODER_MODE6_0;

    // PA5
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5_1) | GPIO_MODER_MODE5_0;

    // PB0
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE0_1) | GPIO_MODER_MODE0_0;

    // PA3
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3_1) | GPIO_MODER_MODE3_0;
}

/*   Positionne ces sorties à une valeur initiale acceptable :

    RST : 0 (reset le DM163) // PC3
    LAT : 1  // PC4
    SB : 1 // PC5 
    SCK et SDA : 0 // PB1 et PA4
    C0 à C7 : 0 (éteint toutes les lignes) 
*/

static void v(){
    // GPIOC->BSRR = GPIO_BSRR_BR3_Msk; // RST
    // GPIOC->BSRR = GPIO_BSRR_BS4_Msk;
    // GPIOC->BSRR = GPIO_BSRR_BS5_Msk;

    // GPIOB->BSRR = GPIO_BSRR_BR1_Msk;
    // GPIOA->BSRR = GPIO_BSRR_BR4_Msk;

    // GPIOB->BSRR = GPIO_BSRR_BR2_Msk; // C0
    // GPIOA->BSRR = GPIO_BSRR_BR15_Msk; // C1
    // GPIOA->BSRR = GPIO_BSRR_BR2_Msk; // C2
    // GPIOA->BSRR = GPIO_BSRR_BR7_Msk;// C3
    // GPIOA->BSRR = GPIO_BSRR_BR6_Msk; //C4
    // GPIOA->BSRR = GPIO_BSRR_BR5_Msk; //C5
    // GPIOB->BSRR = GPIO_BSRR_BR0_Msk; //C6
    // GPIOA->BSRR = GPIO_BSRR_BR3_Msk; //C7

    RST(0);
    SB(1);
    LAT(1);
    SCK(0);
    SDA(0);
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
    
}

/* waiting : n * 1/f = n/ 80_000_000 TODO */
static void wait(uint32_t n){
  for(uint32_t i = 0; i < n; i++)
    asm volatile("nop");
}


static void RST_to_1(){
    GPIOC->BSRR = GPIO_BSRR_BS3_Msk; // RST
}

/*** INIT MATRIX ***/
void matrix_init(){
    // enable horloges des ports A, B et C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN_Msk | RCC_AHB2ENR_GPIOCEN_Msk | RCC_AHB2ENR_GPIOAEN_Msk;
    ouput_mode();
    vitesse_max();
    v();

    wait(8000000); // n = ( f = 80*10**6 )*(T = 100 * 10**(-3))

    RST_to_1();
    init_bank0();
}



/*******    Génération de pulse    *********/


/*cette fonciton effectue un pulse positif (état bas, attente, état haut, attente, état bas, attente)
 sur SCK respectant les timings attendus par le DM163.*/
void pulse_SCK(){
    SCK(0);
    wait( 80000000 * 25 * 10^(-9)); // n = ( f = 80*10**6 )*(T = 25 * 10**(-9)) = 25 ns
    SCK(1);
    wait(80000000 * 25 * 10^(-9) );
    SCK(0);
    wait( 80000000 * 25 * 10^(-9));
}


/* effectue un pulse négatif (état haut, attente, état bas, attente, état haut, attente)
 sur LAT respectant les timings attendus par le DM163.*/
void pulse_LAT(){
    LAT(1);
    wait( 80000000 * 25 * 10^(-9)); // 25ns
    LAT(0);
    wait(80000000 * 7 * 10^(-9) ); // 7ns
    LAT(0);
    wait( 80000000 * 25 * 10^(-9));
}



/*************      Contrôle des lignes     ***************/

/* éteint toutes les lignes */
void deactivate_rows(){
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}


/* Active la ligne dont le numéro est passé en argument. */
void activate_row(int row){
    switch (row)
    {
        case 0:
            ROW0(1);
            break;

        case 1:
            ROW1(1);
            break;  
        
        case 2:
            ROW2(1);
            break;

        case 3:
            ROW3(1);
            break;

        case 4:
            ROW4(1);
            break;

        case 5:
            ROW5(1);
            break;

        case 6:
            ROW6(1);
            break;

        case 7:
            ROW7(1);
            break;

        // default:
    }
}


/******* Contrôle du DM163 *********/

/* envoie 8 bits consécutifs au bank spécifié par 
 le paramètre bank (0 ou 1) du DM163 (dans l'ordre attendu par celui-ci).*/
void send_byte(uint8_t val, int bank){
    SB(bank);
    uint8_t counter = 5; // bank 0 stocke 6 bits par LED
    if(bank)
        counter = 7; // bank 1 stocke 8 bits par LED
    do{ // on envoie le bit de poids fort
        SDA((1<<counter) & val);
        pulse_SCK();
    }while(counter--);
    pulse_LAT();

}



/*
    prend en argument un tableau val de 8 pixels
    à l'aide de send_byte envoie ces 8 pixels au BANK1 du DM163 dans le bon ordre (B7, G7, R7, B6, G6, R6, ..., B0, G0, R0)
    puis à l'aide de activate_row et pulse_LAT active la rangée passée en paramètre et les sorties du DM163.
*/
void mat_set_row(int row, const rgb_color *val){
    uint8_t i = 8;
     while (i--){
        send_byte(val[i].b, 1);
        send_byte(val[i].g, 1);
        send_byte(val[i].r, 1);
    }
    deactivate_rows();
    pulse_LAT();
    activate_row(row);
}


/* Init BANK0 */
void init_bank0(){
    for (uint8_t i = 0; i<24; i++)
        send_byte(0xFF, 0);
    pulse_LAT();
}


void test_pixels() {
    uint8_t row = 0;
    rgb_color bleu[8];
    rgb_color vert[8];
    rgb_color rouge[8];

    // chaque rgb_color est le dégradé de bleu, vert ou rouge

}
