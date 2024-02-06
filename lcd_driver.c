#include <LPC21xx.H>
#include "header.h"
#define RS (1<<17)
#define RW (1<<18)
#define EN (1<<19)
void lcd_data(unsigned char data)
{
	int temp;
	IOCLR1=0xFE0000;
	temp=(data & 0xF0)<<16;//1st nibble
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
	
	IOCLR1=0xFE0000;
	temp=(data & 0xF)<<20;//2nd nibble
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
}
void lcd_cmd(unsigned char cmd)
{
	int temp;
	IOCLR1=0xFE0000;
	temp=(cmd	& 0xF0)<<16;//1st nibble
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
	IOCLR1=0xFE0000;
	temp=(cmd & 0xF)<<20;//2nd nibble
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
}
void lcd_init(void)
{
	IODIR1|=0xFE0000;
	PINSEL2=(0x0);
	lcd_cmd(0x3);
	lcd_cmd(0x2);
	lcd_cmd(0x28);
	lcd_cmd(0xE);
	lcd_cmd(0x1);
}
void lcd_string(char *ptr)
{
	while(*ptr)
	{
		lcd_data(*ptr);
		ptr++;
	}
}
