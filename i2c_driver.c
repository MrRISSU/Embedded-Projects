#include <LPC21XX.H>
#define SI ((I2CONSET>>3)&1)//to chek SI flag
void i2c_init(void)
{
	PINSEL0|=0x50;//p0.2 SCL & SCA p0.3
	I2SCLH=75;
	I2SCLL=75;
	I2CONSET=(1<<6);
}


void i2c_write_frame(unsigned char slave_addr,unsigned char mem_loc,unsigned char data)
{
	I2CONSET=(1<<5);//generate start condition
	while(SI==0);//checking SI flag
	I2CONCLR=(1<<5);//clear STA bit
	
	I2DAT=slave_addr;//send SA+W
	I2CONCLR=(1<<3);//clear SI flag
	while(SI==0);//checking SI
	
	I2DAT=mem_loc;//send m/r address
	I2CONCLR=(1<<3);
	while(SI==0);//checking SI flag
	
	I2DAT=data;//sending data
	I2CONCLR=(1<<3);
	while(SI==0);
	
	I2CONSET=(1<<4);//generate stop condition
	I2CONCLR=(1<<3);//clear SI flag
}
unsigned char i2c_read_frame(unsigned char	slave_addr,unsigned char mem_loc)
{
	unsigned char temp;
	I2CONSET=(1<<5);//generate start condition
	while(SI==0);//checking SI flag
	I2CONCLR=(1<<5);//clear STA bit
	
	I2DAT=slave_addr;//send SA+W
	I2CONCLR=(1<<3);//clear SI flag
	while(SI==0);//checking SI
	
	I2DAT=mem_loc;//send m/r address
	I2CONCLR=(1<<3);
	while(SI==0);//checking SI flag
 //end of dummy write frame
	
	I2CONSET=(1<<5);//generate restart conditon
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);
	I2CONCLR=(1<<5);//clear STA condition
	
	I2DAT=slave_addr|1;//send SA+r
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);
	
	
	I2CONCLR=(1<<3);
	while(SI==0);
	temp=I2DAT;//read data from slave
	
	I2CONSET=(1<<4);//generate stop condition
	I2CONCLR=(1<<3);//clear SI
	return temp;
}
