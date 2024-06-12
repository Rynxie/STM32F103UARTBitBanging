#include <stdint.h>

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

extern volatile uint32_t * rccApb1enr;      
extern volatile uint32_t * rccApb2enr;

extern volatile uint32_t * gpiobCrh;    
extern volatile uint32_t * gpiobOdr;    
extern volatile uint32_t * gpiobIdr;  

extern volatile uint32_t * tim2Cr1;    
extern volatile uint32_t * tim2Psc;   
extern volatile uint32_t * tim2Arr;   
extern volatile uint32_t * tim2Ccr1;    
extern volatile uint32_t * tim2Sr;  
extern volatile uint32_t * tim2Cnt;   


void softwareUARTinit();

void softwareUARTSendData(uint8_t * data, int size);