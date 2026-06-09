#include "lpc214x.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

void InitLPC(void)
{
  
PINSEL0 = 0x00000000;
PINSEL1=0x01000000;     
IO0DIR = 0XFFFFFFFF;
}

void delay_ms(uint16_t j)
{
    uint16_t x,i;
for(i=0;i<j;i++)
{
    for(x=0; x<6000; x++);   
}
}

void LCD_Command(char command)
{
IO0SET = command<<8;
IO0SET = IO0SET |0x00000040; 
delay_ms(2);
        IO0CLR = 0x00000040;
         IO0CLR=0xFFFFFFFF;
}

void LCD_Init(void)
{

LCD_Command(0x38);  
LCD_Command(0x0C);   
LCD_Command(0x06);  
LCD_Command(0x01);   

}

void LCD_String (char* msg)
{  uint8_t i=0;
    while(msg[i]!=0)
    {
IO0SET = msg[i]<<8;
IO0SET = IO0SET|0x00000050; 
delay_ms(2);
        IO0CLR = 0x00000040;
        delay_ms(5);
        IO0CLR=0xFFFFFFFF;
        i++;
}
}
int main(void)
{
uint32_t result;
float voltage;
char adc[18];
InitLPC();
LCD_Init();

    AD0CR = 0x00200402;
while(1)
{
AD0CR = AD0CR | (1<<24);
while ( !(AD0GDR & 0x80000000) ); 
result = AD0GDR;
result = (result>>6);
result = (result & 0x000003FF);
                voltage=result;
LCD_Command(0x80);
sprintf(adc, "ADC=%f V  ", voltage);
LCD_String(adc);

}
}
