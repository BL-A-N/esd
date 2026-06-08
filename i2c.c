#include "lpc214x.h"
#include "stdint.h"
#include "stdio.h"


void delay()
{
  unsigned int a;
  for(a=1;a<=60000;a++);
}

#define I2EN (1<<6)
#define STA (1<<5)
#define STO (1<<4)
#define SI (1<<3)
#define AA (1<<2)

void waitforsi (void)
{
  while(!(I2C0CONSET & SI));
}

void i2c_send_start (void)
{
 I2C0CONSET = STA;
 waitforsi();
}


void i2c_write (unsigned char data)
{
 I2C0DAT = data;
  I2C0CONCLR = SI|STA|AA;
  waitforsi();
}


void i2c_send_stop (void)
{
  I2C0CONCLR = AA|SI;
 I2C0CONSET = STO;
}

void i2c_init (void)
{
 I2C0SCLH = 75;
 I2C0SCLL = 75;
  I2C0CONCLR = SI|STA|AA|STO;
  I2C0CONSET = I2EN;
 }

void lcd_write_data (int data)
{
  unsigned char address = 0x40;
  unsigned char a[]={0x3F,0x6,0x5B,0X4F,0X66,0X6D,0X7D,0X7,0X7F,0X6F};
  
  i2c_send_start();
  i2c_write (address);
  i2c_write (a[data]);
  i2c_send_stop();
}

int main()
{
  int l;
  PINSEL0 = (1<<4)|(1<<6);
  i2c_init();
  while(1)
  {
    for(l=0;l<10;l++)
    {
      lcd_write_data(l);
      delay();
    }
    
  }
}
