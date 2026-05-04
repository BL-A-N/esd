#include "lpc214x.h"
#include "stdint.h"
void delay_ms(uint16_t j)
{
  uint16_t x,i;
  for(i=0;i<j;i++)
  {
    for(x=0;x<6000;x++);
  }
}
int main(void)
{
  uint16_t i=0;
  PINSEL1=0x00080000;
  IO0DIR=0xFFFFFFFF;
  while(1)
  {
    i=0;
    while(i!=1023)
    {
      DACR=i<<6;
      i++;
    }
    i=1023;
    while (i!=0)
    {
      DACR=i<<6;
      i--;
    }
  }
}
