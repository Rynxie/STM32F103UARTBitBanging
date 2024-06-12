#include "UARTBitBangSender.h"

volatile uint32_t * rccApb1enr      = (volatile uint32_t *) RCC_APB1ENR;
volatile uint32_t * rccApb2enr      = (volatile uint32_t *) RCC_APB2ENR;

volatile uint32_t * gpiobCrh        = (volatile uint32_t *) GPIOB_CRH;
volatile uint32_t * gpiobOdr        = (volatile uint32_t *) GPIOB_ODR;
volatile uint32_t * gpiobIdr        = (volatile uint32_t *) GPIOB_IDR;

volatile uint32_t * tim2Cr1         = (volatile uint32_t *) TIM2_BASE;
volatile uint32_t * tim2Psc         = (volatile uint32_t *) TIM2_PSC;
volatile uint32_t * tim2Arr         = (volatile uint32_t *) TIM2_ARR;
volatile uint32_t * tim2Ccr1        = (volatile uint32_t *) TIM2_CCR1;
volatile uint32_t * tim2Sr          = (volatile uint32_t *) TIM2_SR;
volatile uint32_t * tim2Cnt         = (volatile uint32_t *) TIM2_CNT;

void softwareUARTinit(){

    *rccApb1enr     |= (1<<0);      //TIM2 en
    *rccApb2enr     |= (1<<3);      //GPIOB en

    *tim2Psc         = 7;           //PSC set to 7
    *tim2Arr         = 104;         //counter will reset after 104 counts
    *tim2Ccr1        = 0;           //the CC1IF flag will be set by software ecery time the cnt hit 0

    *tim2Cr1        |= (1<<0);      //enable the tim2

    *gpiobCrh       |= (3<<16);     // Configuring GPIO B12 Pin to Push Pull Output
    *gpiobCrh       &= ~(1<<18);    

    /*
    
    *gpiobCrh       &= ~(1<<22);   
    *gpiobCrh       |= (3<<23);
    */


    *gpiobOdr       |= (1<<12);     //Setting the B12 High it is standart for UART when data has not sended
}

void softwareUARTSendData(uint8_t * data, int size){
    volatile int length = size/sizeof(data[0]);

    for(volatile int i = 0; i<length;i++){
        volatile int bitNo = 0;
        volatile uint8_t debugData = data[i]; //its for debuging

        while (bitNo<10){
            if(((*tim2Sr & 2)>>1) == 1){
                *tim2Sr &= ~(2); //clean the flag
                
                if(bitNo == 0){
                    *gpiobOdr       &= ~(1<<12);     // start bit
                }
                if (bitNo > 0){
                    *gpiobOdr = (((data[i]>>(bitNo-1))&1) == 1) ? *gpiobOdr | (1<<12) : *gpiobOdr & ~(1<<12);
                }
                if (bitNo == 9){
                    *gpiobOdr       |= (1 << 12);   //stop bit
                }
                
                bitNo++;
            }
        }
       

        
    }
}
