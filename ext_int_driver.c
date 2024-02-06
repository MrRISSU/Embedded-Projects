#include <LPC21XX.H>
extern int mode_flag,cur_flag,inc_flag;
extern int flag;
void mode_sw(void) __irq
{
	flag=1;
	mode_flag++;
	if(mode_flag==3)
		mode_flag=0;
	EXTINT=0x1;
	VICVectAddr=0x0;
}

void inc_sw(void) __irq
{
	inc_flag=1;
	EXTINT=0x2;
	VICVectAddr=0x0;
}
void curser_sw(void) __irq
{
	cur_flag++;
	if(cur_flag==4)
		cur_flag=1;
	EXTINT=0x4;
	VICVectAddr=0x0;
}
void config_vic_BCM(void)
{
	VICIntSelect=0;
	VICVectCntl0=14|(1<<5);//eint0
	VICVectCntl1=15|(1<<5);//eint1
	VICVectCntl2=16|(1<<5);//eint2
	VICVectAddr0=(int)mode_sw;
	VICVectAddr1=(int)inc_sw;
	VICVectAddr2=(int)curser_sw;
	VICIntEnable=(1<<14)|(1<<15)|(1<<16);
}
void config_eint(void)
{
	PINSEL0|=0xA0000000;
	PINSEL1|=0x1;
	EXTMODE=0x7;
	EXTPOLAR=0x0;
}
