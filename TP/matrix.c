#include "matrix.h"


static void output_mode(){
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2_1) | GPIO_MODER_MODE2_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3_1) | GPIO_MODER_MODE3_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4_1) | GPIO_MODER_MODE4_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5_1) | GPIO_MODER_MODE5_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6_1) | GPIO_MODER_MODE6_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7_1) | GPIO_MODER_MODE7_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE15_1) | GPIO_MODER_MODE15_0;

    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_Msk;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_Msk;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_Msk;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_Msk;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_Msk;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED7_Msk;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED15_Msk;

    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE0_1) | GPIO_MODER_MODE0_0;
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE1_1) | GPIO_MODER_MODE1_0;
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE2_1) | GPIO_MODER_MODE2_0;

    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_Msk;
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_Msk;
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_Msk;

    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE3_1) | GPIO_MODER_MODE3_0;
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE4_1) | GPIO_MODER_MODE4_0;
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE5_1) | GPIO_MODER_MODE5_0;

    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_Msk;
    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_Msk;
    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_Msk;
}

/*   Positionne ces sorties à une valeur initiale acceptable :

    RST : 0 (reset le DM163) // PC3
    LAT : 1  // PC4
    SB : 1 // PC5 
    SCK et SDA : 0 // PB1 et PA4
    C0 à C7 : 0 (éteint toutes les lignes) 
*/
static void output_init(){
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

/* waiting : n * 1/f = n/80_000_000 */
static void wait(uint32_t n){
  for(uint32_t i = 0; i < n; i++)
    asm volatile("nop");
}

static void init_bank0();

void matrix_init(){
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);
    output_mode();
    output_init();
    wait(100000);
    RST(1);
    init_bank0();
}



/*******    Génération de pulse    *********/


/*cette fonciton effectue un pulse positif (état bas, attente, état haut, attente, état bas, attente)
 sur SCK respectant les timings attendus par le DM163.*/
static void pulse_SCK(){
    SCK(0);
    SCK(1);
    SCK(0);
}


/* effectue un pulse négatif (état haut, attente, état bas, attente, état haut, attente)
 sur LAT respectant les timings attendus par le DM163.*/
static void pulse_LAT(){
    LAT(1);
    LAT(0);
    LAT(1);
}



/*************      Contrôle des lignes     ***************/

/* éteint toutes les lignes */
static void deactivate_rows(){
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
static void activate_row(int row){
    switch (row)
    {
        case 0: ROW0(1); break;
        case 1: ROW1(1); break;  
        case 2: ROW2(1); break;
        case 3: ROW3(1); break;
        case 4: ROW4(1); break;
        case 5: ROW5(1); break;
        case 6: ROW6(1); break;
        case 7: ROW7(1); break;
    }
}


/******* Contrôle du DM163 *********/

/* envoie 8 bits consécutifs au bank spécifié par 
 le paramètre bank (0 ou 1) du DM163 (dans l'ordre attendu par celui-ci).*/
void send_byte(uint8_t val, int bank){
    SB(bank);
    uint8_t counter = 5;
    if(bank){counter = 7;} // bank 1 stocke 8 bits par LED
    do { // on envoie le bit de poids fort
        SDA((val>>counter)& 1);
        pulse_SCK();
    } while(counter--);

}



/*
    prend en argument un tableau val de 8 pixels
    à l'aide de send_byte envoie ces 8 pixels au BANK1 du DM163 dans le bon ordre (B7, G7, R7, B6, G6, R6, ..., B0, G0, R0)
    puis à l'aide de activate_row et pulse_LAT active la rangée passée en paramètre et les sorties du DM163.
*/
void mat_set_row(uint8_t row, const rgb_color *val){
    uint8_t i = 7;
    do{
        send_byte(val[i].b, 1);
        send_byte(val[i].g, 1);
        send_byte(val[i].r, 1);
    }while(i--);
    deactivate_rows();
    wait(750);
    pulse_LAT();
    activate_row(row);
}


/* Init BANK0 */
static void init_bank0(){
    for (uint8_t i = 0; i<18; i++)
        send_byte((uint8_t) 0xFF, 0);
    pulse_LAT();
}


void test_pixels() {
    /*INIT MATRIX*/
    matrix_init();

    /* DEACTIVATE ROWS*/
    deactivate_rows();

    const rgb_color g[8] = {
    {0, 0, 255},
    {0, 0, 200},
    {0, 0, 150},
    {0, 0, 100},
    {0, 0, 50},
    {0, 0, 25},
    {0, 0, 12},
    {0, 0, 5}
    };

    const rgb_color r[8] = {
    {0, 255, 0},
    {0, 200, 0},
    {0, 150, 0},
    {0, 100, 0},
    {0, 50, 0},
    {0, 25, 0},
    {0, 12, 0},
    {0, 5, 0}
    };

const rgb_color b[8] = {
    {255, 0, 0},
    {200, 0, 0},
    {150, 0, 0},
    {100, 0, 0},
    {50, 0, 0},
    {25, 0, 0},
    {12, 0, 0},
    {5, 0, 0}
    };

    while(1)
        for ( int j = 0; j<8; j++) {
            switch(j%3){
                case 0 :   mat_set_row(j, r); break;
                case 1 :   mat_set_row(j, g) ; break;
                case 2 :   mat_set_row(j, b) ; break;
            }
            wait(2500000);
        }
    wait((uint32_t)0xFFF00);
}


void display_image(const rgb_color *image){
    /* Séparation pour affichage de ligne par ligne à chaque interruption au lieu de toute la matrice */
    /* Parceque l'affichage correct n'est pas possible sur toute la matrice ( sans optimisation, ..)*/
    static rgb_color row[8];
    static int row_num;

    for (int num = 0; num < 8 ; num++){
        row[num] = image[row_num*8 + num];
    }

    mat_set_row(row_num++, row);

    if( row_num == 7){
        row_num = 0;
    }
}