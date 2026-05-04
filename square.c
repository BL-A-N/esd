#include "lpc214x.h"
#include "stdint.h"
void delay_ms(uint16_t j)
{
  uint16_t x,i;
  for(i=0;i<j;i++)
  {
    for(x=0;x<60;x++);
  }
}
int main(void)
{
  PINSEL1=0x00080000;
  IO0DIR=0xFFFFFFFF;
  while(1)
  {
    DACR=1023<<6;
    delay_ms(1);
    DACR=0;
    delay_ms(1);    
  }
}
