// #include "matrix.h"
#include "stm32l475xx.h"
#include "matrix.h"

/* Macros contrôle des broches */
#define SB(value)   do {GPIOC->BSRR = value ? GPIO_BSRR_BS5  : GPIO_BSRR_BR5 ;} while(0)
#define LAT(value)  do {GPIOC->BSRR = value ? GPIO_BSRR_BS4  : GPIO_BSRR_BR4 ;} while(0)
#define RST(value)  do {GPIOC->BSRR = value ? GPIO_BSRR_BS3  : GPIO_BSRR_BR3 ;} while(0)
#define SCK(value)  do {GPIOB->BSRR = value ? GPIO_BSRR_BS1  : GPIO_BSRR_BR1 ;} while(0)
#define SDA(value)  do {GPIOA->BSRR = value ? GPIO_BSRR_BS4  : GPIO_BSRR_BR4 ;} while(0)
#define ROW0(value) do {GPIOB->BSRR = value ? GPIO_BSRR_BS2  : GPIO_BSRR_BR2 ;} while(0)
#define ROW1(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS15 : GPIO_BSRR_BR15;} while(0)
#define ROW2(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS2  : GPIO_BSRR_BR2 ;} while(0) 
#define ROW3(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS7  : GPIO_BSRR_BR7 ;} while(0) 
#define ROW4(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS6  : GPIO_BSRR_BR6 ;} while(0) 
#define ROW5(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS5  : GPIO_BSRR_BR5 ;} while(0) 
#define ROW6(value) do {GPIOB->BSRR = value ? GPIO_BSRR_BS0  : GPIO_BSRR_BR0 ;} while(0) 
#define ROW7(value) do {GPIOA->BSRR = value ? GPIO_BSRR_BS3  : GPIO_BSRR_BR3 ;} while(0) 


/* Configurer les ports en vitesse max  */
static void vitesse_max(){
    GPIOC->OSPEEDR |=  GPIO_OSPEEDR_OSPEED3_Msk | GPIO_OSPEEDR_OSPEED4_Msk | GPIO_OSPEEDR_OSPEED5_Msk;  
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_Msk | GPIO_OSPEEDR_OSPEED0_Msk| GPIO_OSPEEDR_OSPEED2_Msk; 
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED15_Msk| GPIO_OSPEEDR_OSPEED3_Msk | GPIO_OSPEEDR_OSPEED5_Msk | GPIO_OSPEEDR_OSPEED4_Msk | GPIO_OSPEEDR_OSPEED2_Msk | GPIO_OSPEEDR_OSPEED7_Msk | GPIO_OSPEEDR_OSPEED6_Msk;
} 


/* configure toutes les broches reliées au driver en mode GPIO Output */
static void ouput_mode(){
    // PB5
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE5_1) | GPIO_MODER_MODE5_0; // & ~GPIO_MODER_MODE5_Msk) | (0x2 << GPIO_MODER_MODE5_Pos)
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

/*** INIT MATRIX ***/
void matrix_init(){
    // enable horloges des ports A, B et C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN_Msk | RCC_AHB2ENR_GPIOCEN_Msk | RCC_AHB2ENR_GPIOAEN_Msk;
    ouput_mode();
    vitesse_max();
    output_init();

    wait(8000000); // n = ( f = 80*10**6 )*(T = 100 * 10**(-3))

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
void init_bank0(){
    for (uint8_t i = 0; i<24; i++)
        send_byte((uint8_t) 0b111111, 0);
    pulse_LAT();
}


void test_pixels() {
    /*INIT MATRIX*/
     matrix_init();

    /* DEACTIVATE ROWS*/
     deactivate_rows();

    const rgb_color r[8] = { {255,255,0}, {255, 255,0}, {255, 255,0}, {0,255,0}, 
                    {255,0,0}, {0,255,0}, {0,255,0}, {0,255,0} };

    // rgb_color g[8] = { {0,255,0}, {0,255,0}, {0,255,0}, {0,255,0},
	//      {0,255,0}, {0,255,0}, {0,255,0}, {0,255,0} };
    // rgb_color b[8] = { {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255},
	//     {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255} };

//     // chaque rgb_color est le dégradé de bleu, vert ou rouge
//     // couleur de départ
//     uint8_t r1 = 70;
//     uint8_t g1 = 30;
//     uint8_t b1 = 30;

//    //couleur d'arrivée
//     uint8_t r2 = 255;
//     uint8_t g2 = 235;
//     uint8_t b2 = 235;

// ///pour chaque canal, calcul du différenciel entre chaque teinte (nbVal est le nombre de teintes du dégradé)
//     uint8_t dr = (uint8_t)(r2 - r1) / 8;
//     uint8_t dg = (uint8_t)(g2 - g1)/ 8;
//     uint8_t db = (uint8_t)(b2 - b1)/ 8;

// /// on boucle pour remplir un tableau contenant toutes les valeurs des teintes
//     for(int i = 0; i<8; i++){
//         Rouge[i].r = r2;
//         Rouge[i].g = g2;
//         Rouge[i].r = b2;
//         r2 = r2 - dr;
//         g2 = g2 - dg;
//         b2 = b2 - db;
//     }

//     while(1)
//         for ( int j = 0; j<8; j++) {
//             switch(j%3){
//                 case 0 :   mat_set_row(j, Rouge); break;
//                 case 1 :   mat_set_row(j, Rouge) ; break;
//                 case 2 :   mat_set_row(j, Bleu) ; break;
//             }
//         }
//     // TODO: annimation? wait();
//     wait((uint32_t)0xFFF00);


    uint8_t row = 0;

    // const rgb_color *color = r;
    while(1){
        mat_set_row(row++, r);
        
        // TODO animation ? wait(800000);

        // if(row == 8){
        //     if(color == b)
        //         color = g;
        //     else if (color == g)  
        //         color = r;
        //     else color = b;
        //     row = 0;
        // }
        if(row==8){
            row = 0;
        }
    }
}
