
#include "header.h"
int mode_flag,cur_flag=1,inc_flag;
int flag;

int BCD_to_DEC(unsigned char BCD)
{
	int DEC;
	DEC=BCD/0x10;
	DEC*=10;
	DEC+=BCD%0x10;
	return DEC;
}

unsigned char DEC_to_BCD(unsigned char DEC)
{
	unsigned char BCD;
	BCD=(DEC/10)<<4;
	BCD|=(DEC%10);
	return BCD;
}

int main()
{
	unsigned char hrs,min,sec;
	unsigned char date,month,year;
	lcd_init();
	i2c_init();
	config_eint();
	config_vic_BCM();
	//////default setting//////
	i2c_write_frame(0xD0,0x02,0x00);//hr
	i2c_write_frame(0xD0,0x01,0x00);//min
	i2c_write_frame(0xD0,0x00,0x00);//sec
	
	i2c_write_frame(0xD0,0x03,0x06);//day
	
	i2c_write_frame(0xD0,0x04,0x22);//date
	i2c_write_frame(0xD0,0x05,0x09);//mon
	i2c_write_frame(0xD0,0x06,0x23);//yr

	while(1)
	{
		hrs=BCD_to_DEC(i2c_read_frame(0xD0,0x2));
		min=BCD_to_DEC(i2c_read_frame(0xD0,0x1));
		sec=BCD_to_DEC(i2c_read_frame(0xD0,0x0));
		
		date=BCD_to_DEC(i2c_read_frame(0xD0,0x4));
		month=BCD_to_DEC(i2c_read_frame(0xD0,0x5));
		year=BCD_to_DEC(i2c_read_frame(0xD0,0x6));
		
		//displays hrs:min:sec
		lcd_cmd(0x80);
		lcd_string("Time : ");
		lcd_data((hrs/10)+48);
		lcd_data((hrs%10)+48);
		lcd_data(':');
		lcd_data((min/10)+48);
		lcd_data((min%10)+48);
		lcd_data(':');
		lcd_data((sec/10)+48);
		lcd_data((sec%10)+48);
		
		//displays yr:mon:date
		lcd_cmd(0xC0);
		lcd_string("Date : ");
		lcd_data((date/10)+48);
		lcd_data((date%10)+48);
		lcd_data(':');
		lcd_data((month/10)+48);
		lcd_data((month%10)+48);
		lcd_data(':');
		lcd_data((year/10)+48);
		lcd_data((year%10)+48);
		
		///////edit mode//////
		if(flag)
		{
			flag=0;
			if(mode_flag)
			{
				do//edit time
				{
					if(cur_flag==1)//setting hrs
					{
						lcd_cmd(0x1);
						lcd_string("edit hr :");
						lcd_data((hrs/10)+48);
						lcd_data((hrs%10)+48);
						if(inc_flag)
						{
							inc_flag=0;
							hrs++;
							if(hrs==25)
								hrs=0;
						}
					}
					else if(cur_flag==2)//setting mins
					{
						lcd_cmd(0x1);
						lcd_string("edit min :");
						lcd_data((min/10)+48);
						lcd_data((min%10)+48);
						if(inc_flag)
						{
							inc_flag=0;
							min++;
							if(min==60)
								min=0;
						}
					}
					else if(cur_flag==3)//after setting hrs and min, making sec zero
					{
						cur_flag=1;//to go back to hr setting
						sec=0;
					}
				}while(mode_flag==1);
				i2c_write_frame(0xD0,0x02,DEC_to_BCD(hrs));//hr
				i2c_write_frame(0xD0,0x01,DEC_to_BCD(min));//min
				i2c_write_frame(0xD0,0x00,DEC_to_BCD(sec));//sec
				cur_flag=1;//setting back to one in case if it does'nt set to 1 inside sec edit 
				do//edit date
				{
					if(cur_flag==1)//setting hrs
					{
						lcd_cmd(0x1);
						lcd_string("edit date :");
						lcd_data((date/10)+48);
						lcd_data((date%10)+48);
						if(inc_flag)
						{
							inc_flag=0;
							date++;
							if(date==32)
								date=1;
						}
					}
					else if(cur_flag==2)//setting mins
					{
						lcd_cmd(0x1);
						lcd_string("edit month :");
						lcd_data((month/10)+48);
						lcd_data((month%10)+48);
						if(inc_flag)
						{
							inc_flag=0;
							month++;
							if(month==13)
								month=1;
						}
					}
					else if(cur_flag==3)//after setting hrs and min, making sec zero
					{
						lcd_cmd(0x1);
						lcd_string("edit year :");
						lcd_data((year/10)+48);
						lcd_data((year%10)+48);
						if(inc_flag)
						{
							inc_flag=0;
							year++;
							if(year==100)
								year=1;
						}
					}
				}while(mode_flag==2);
				i2c_write_frame(0xD0,0x04,DEC_to_BCD(date));//date
				i2c_write_frame(0xD0,0x05,DEC_to_BCD(month));//mon
				i2c_write_frame(0xD0,0x06,DEC_to_BCD(year));//yr
				cur_flag=1;
			}
		}
	}
}
