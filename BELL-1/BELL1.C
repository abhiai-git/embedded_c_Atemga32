#include<avr/io.h>
#include<util/delay.h>

#define RS PD0
#define RW PD1
#define EN PD2


void LCD_cmd(unsigned char item)
{
	PORTD=item;
	PORTD |=(0<<RS)|(0<<RW)|(1<<EN);
	_delay_ms(1);
	PORTD |=(0<<RS)|(0<<RW)|(0<<EN);
}
void LCD_data(unsigned char item)
{
	PORTD=item;
	PORTD |=(1<<RS)|(0<<RW)|(1<<EN);
	_delay_ms(1);
	PORTD |=(1<<RS)|(0<<RW)|(0<<EN);
}
void dis_data(unsigned char item)
{
	unsigned char value;
	value = item & 0XF0;
	LCD_data(value);
	_delay_ms(1);
	value=(item <<4)& 0xf0;
	LCD_data(value);
}
void dis_cmd(unsigned char item)
{
	unsigned char value;
	value = item & 0XF0;
	LCD_cmd(value);
	_delay_ms(1);
	value=(item<<4) & 0xf0;
	LCD_cmd(value);
}

void LCD_init()
{
	dis_cmd(0x02);
	dis_cmd(0x28);
	_delay_ms(1);
	dis_cmd(0x0e);
	_delay_ms(1);	
	dis_cmd(0x01);
	_delay_ms(1);


}

void LCD_string(unsigned char *str)
{
	unsigned int x=0;
	
	while(str[x]!='\0')
	{
	dis_data(str[x]);
	x++;
	}
}
void LCD_num(unsigned int data)
{
unsigned int val;
dis_cmd(0x04);
	while(data!=0)
	{
		val=data%10;
		dis_data(val+48);
		data=data/10;
	}
//dis_cmd(0x06);
} 
int main()
{	DDRD=0b11111111;	
	LCD_init();

	while(1)
	{	
			dis_cmd(0x40);
		dis_data(0x04);
		dis_data(0x0e);
		dis_data(0x0e);
		dis_data(0x0e);
		dis_data(0x1f);
		dis_data(0x00);
		dis_data(0x04);
		
	dis_cmd(0x80);
	dis_data(0);
	
	}
	return 0;
	}
