#include "lpc214x.h"
#include "stdio.h"

void delay(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 6000; j++);
}

void LCD_Cmd(char cmd) {
    IO0CLR = 0xFFFFFFFF;
    IO0SET = (cmd << 8) | 0x40;       // Data + EN high, RS=0
    delay(2);
    IO0CLR = 0x40;                     // EN low
}

void LCD_Char(char ch) {
    IO0CLR = 0xFFFFFFFF;
    IO0SET = (ch << 8) | 0x50;        // Data + EN high + RS high
    delay(2);
    IO0CLR = 0x40;                     // EN low
}

void LCD_Print(char *s) {
    while (*s) LCD_Char(*s++);
}

void LCD_Init(void) {
    LCD_Cmd(0x38);                     // 8-bit, 2-line
    LCD_Cmd(0x0C);                     // Display on, cursor off
    LCD_Cmd(0x06);                     // Auto-increment
    LCD_Cmd(0x01);                     // Clear
    delay(2);
}

int main(void) {
    unsigned int result;
    char buf[16];

    PINSEL0 = 0x00000000;
    PINSEL1 = 0x01000000;             // P0.28 as AD0.1
    IO0DIR  = 0xFFFFFFFF;

    LCD_Init();
    AD0CR = 0x00200402;               // ADC on, channel 1, 10-bit

    while (1) {
        AD0CR |= (1 << 24);           // Start conversion
        while (!(AD0GDR & 0x80000000)); // Wait for DONE

        result = (AD0GDR >> 6) & 0x3FF;

        LCD_Cmd(0x80);                 // Cursor to line 1
        sprintf(buf, "ADC=%04d", result);
        LCD_Print(buf);
    }
}
