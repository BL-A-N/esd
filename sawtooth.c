//SAWTOOTH
#include "lpc214x.h"    // LPC214x register definitions
#include "stdint.h"     // standard integer types

// Delay function (controls waveform frequency)
void delay_ms(uint16_t j)
{
    uint16_t x, i;
    for(i = 0; i < j; i++)
    {
        for(x = 0; x < 6000; x++);   // delay loop
    }
}

int main(void)
{
    uint16_t i = 0;   // loop variable

    PINSEL1 = 0x00080000;   // configure P0.25 as DAC output
    IO0DIR  = 0xFFFFFFFF;   // set port 0 as output

    while(1)   // infinite loop
    {
        // Rising ramp (0 → 1023)
        for(i = 0; i < 1023; i++)
        {
            DACR = i << 6;   // send value to DAC (10-bit aligned)
            delay_ms(1);     // controls waveform speed
        }
        // After reaching max, it resets to 0 → creates sawtooth
    }
}
