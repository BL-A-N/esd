#include "lpc214x.h"
#include <math.h>
#include <stdint.h>

#define PI 3.14159265

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
  uint16_t value;
  uint16_t i;
  float angle;

  PINSEL1 = 0x00080000;   // Enable DAC (P0.25)
  IO0DIR  = 0xFFFFFFFF;

  while(1)
  {
    for(i = 0; i < 64; i++)
    {
      angle = (2 * PI * i) / 64.0;              // angle in radians
      value = (uint16_t)((sin(angle) * 511) + 512); // scale to 0–1023
      DACR  = (value << 6);                     // align to DAC register

      delay_ms(1);
    }
  }
}
