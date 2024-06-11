#include <stdint.h>


// timer 2 will be used tim2 address is x40000000
// it is connected to APB1 bus

// lets use b12 pin for tests

// enable gpiob and tim2 from rcc
// tim2 PSC will be 7 so our clock will be 1Mhz
// let ARR 9600 like baudrate
// for test lets CCR1 to 104 just for checking

//cfg gpiob to high speed push pull output mode

#define RCC_BASE        0x40021000
#define RCC_APB1ENR     (RCC_BASE+0x1C)
#define RCC_APB2ENR     (RCC_BASE+0x18)

#define GPIOB_BASE      0x40010C00
#define GPIOB_CRH       (GPIOB_BASE+0x04)
#define GPIOB_ODR       (GPIOB_BASE+0x0C)
#define GPIOB_IDR       (GPIOB_BASE+0x08)

#define TIM2_BASE       0x40000000 
#define TIM2_PSC        (TIM2_BASE+0x28)
#define TIM2_ARR        (TIM2_BASE+0x2C)
#define TIM2_CCR1       (TIM2_BASE+0x34)
#define TIM2_SR         (TIM2_BASE+0x10)
#define TIM2_CNT        (TIM2_BASE+0x24)




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



int main(){


    *rccApb1enr     |= (1<<0);      //TIM2 en
    *rccApb2enr     |= (1<<3);      //GPIOB en

    *tim2Psc         = 7;           //PSC set to 7
    *tim2Arr         = 104;
    *tim2Ccr1        = 0;

    *tim2Cr1        |= (1<<0);

    *gpiobCrh       |= (3<<16);
    *gpiobCrh       &= ~(1<<18);

    *gpiobCrh       &= ~(1<<22);
    *gpiobCrh       |= (3<<23);


    *gpiobOdr       |= (1<<12);
   
    int bitNo = 0;
    while (1){
        uint8_t data = 31;
        
        
        
        
        if((*gpiobIdr & 0x2000) == 0x2000){
            if(((*tim2Sr & 2)>>1) == 1){
                *tim2Sr &= ~(2);
                
                if(bitNo == 0){
                    *gpiobOdr       &= ~(1<<12);
                }

                if (bitNo > 0){


                    *gpiobOdr = (((data>>(bitNo-1))&1) == 1) ? *gpiobOdr | (1<<12) : *gpiobOdr & ~(1<<12);
                }
                if (bitNo == 9){
                    bitNo =0;
                    *gpiobOdr       |= (1<<12);

                }else{
                    bitNo++;
                }
                
                

            
            }
        }
        
        
        
        
    }
   
   
    


}