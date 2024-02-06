extern void i2c_init(void);
extern void i2c_write_frame(unsigned char slave_addr,unsigned char mem_loc,unsigned char data);
extern unsigned char i2c_read_frame(unsigned char	slave_addr,unsigned char mem_loc);

extern void lcd_init(void);
extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_string(char *ptr);

extern void delay_ms(unsigned int ms);

extern void config_vic_BCM(void);
extern void config_eint(void);
