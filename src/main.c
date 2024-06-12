#include "UARTBitBangSender.h"



int main(){
    
    softwareUARTinit();
    *gpiobCrh       &= ~(1<<22);   
    *gpiobCrh       |= (3<<23);

    while (1){

      uint8_t data[12] = "\f Hello World\n\r";
      


      //if((*gpiobIdr & 0x2000) == 0x2000){

        softwareUARTSendData(data, sizeof(data));
      //}
      

   

       
    }
    
}
