#include <LPC21xx.H>
void delay_ms(int ms)
{
	T0PR=15000-1;
	T0PC=0;
	T0TC=0;
	T0TCR=1;
	while(T0TC<ms);
	T0TCR=0;
}
