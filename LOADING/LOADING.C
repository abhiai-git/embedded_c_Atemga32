#define F_CPU 1000000
#include<avr/io.h>
#include<util/delay.h>

#define RS PD0
#define RW PD1
#define EN PD2

void LCD_clr(void);
void LCD_cmd(unsigned char);
void LCD_data(unsigned char);
void dis_data(unsigned char);
void dis_cmd(unsigned char);
void LCD_init(void);
void LCD_string(unsigned char *);
void LCD_num(unsigned int);

void ld(unsigned char item)
	{
		dis_cmd(0x40);
		dis_data(0b00010000);
		dis_data(0b00010000);
		dis_data(0b00010000);
		dis_data(0b00010000);
		dis_data(0b00010000);
		dis_data(0b00010000);
		dis_data(0b00010000);
		dis_cmd(item);
		dis_data(0);
		
		_delay_ms(6000);	


		dis_cmd(0x40);
		dis_data(0b00011000);
		dis_data(0b00011000);
		dis_data(0b00011000);
		dis_data(0b00011000);
		dis_data(0b00011000);
		dis_data(0b00011000);
		dis_data(0b00011000);
		dis_cmd(item);
		dis_data(0);
		
		_delay_ms(6000);
		
		dis_cmd(0x40);
		dis_data(0b00011100);
		dis_data(0b00011100);
		dis_data(0b00011100);
		dis_data(0b00011100);
		dis_data(0b00011100);
		dis_data(0b00011100);
		dis_data(0b00011100);
		dis_cmd(item);
		dis_data(0);

		_delay_ms(6000);
		
		dis_cmd(0x40);
		dis_data(0b00011110);
		dis_data(0b00011110);
		dis_data(0b00011110);
		dis_data(0b00011110);
		dis_data(0b00011110);
		dis_data(0b00011110);
		dis_data(0b00011110);
		dis_cmd(item);
		dis_data(0);

		_delay_ms(6000);		

		dis_cmd(0x40);
		dis_data(0b00011111);
		dis_data(0b00011111);
		dis_data(0b00011111);
		dis_data(0b00011111);
		dis_data(0b00011111);
		dis_data(0b00011111);
		dis_data(0b00011111);
		dis_cmd(item);
		dis_data(0);
	}	



int main()
{	DDRD=0b11111111;	
	LCD_init();
//dis_cmd(0x01);


	{
	dis_cmd(0x80);
	LCD_string("LOADING....");
	ld(0xc0);
	ld(0xc1);
	ld(0xc2);
	ld(0xc3);
	ld(0xc4);
	ld(0xc5);
	ld(0xc6);
	ld(0xc7);
	ld(0xc8);
	ld(0xc9);
	ld(0xca);
	ld(0xcb);
	ld(0xcc);
	ld(0xcd);
	ld(0xce);
	ld(0xcf);
	
	}


	return 0;
}
void LCD_clr(void)
{
	dis_cmd(0X01);
}

void LCD_cmd(unsigned char item)
{
	PORTD=item;
	PORTD &=~(1<<RS);
	PORTD &=~(1<<RW);
	PORTD |= (1<<EN);
	_delay_ms(1);
	PORTD &= ~(1<<EN);
}

void LCD_data(unsigned char item)
{
	PORTD=item;
	PORTD |= (1<<RS);
	PORTD &=~(1<<RW);
	PORTD |= (1<<EN);
	_delay_ms(1);
	PORTD &= ~(1<<EN);
}

void dis_data(unsigned char item)
{
	unsigned char value;
	value = item & 0XF0;
	LCD_data(value);
	_delay_ms(1);
	value=(item << 4) & 0xF0;
	LCD_data(value);
}

void dis_cmd(unsigned char item)
{
	unsigned char value;
	value = item & 0XF0;
	LCD_cmd(value);
	_delay_ms(1);
	value=(item << 4) & 0xF0;
	LCD_cmd(value);
}

void LCD_init()
{
	dis_cmd(0x02);
	dis_cmd(0x28);
	_delay_ms(1);
	//dis_cmd(0x01);
	_delay_ms(1);
	dis_cmd(0x0C);
	_delay_ms(1);
	dis_cmd(0X06);
	dis_cmd(0x80);
	
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
dis_cmd(0x06);
} 
