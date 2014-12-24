#define F_CPU 1000000
#include<avr/io.h>
#include<util/delay.h>

#define RS PD0
#define RW PD1
#define EN PD2
#define ADC_VREE_TYPE 0x40

void LCD_clr(void);
void LCD_cmd(unsigned char);
void LCD_data(unsigned char);
void dis_data(unsigned char);
void dis_cmd(unsigned char);
void LCD_init(void);
void LCD_string(unsigned char *);
void LCD_num(unsigned int);


int main()
{	DDRD=0b11111111;	
		
		
		LCD_init();
		_delay_ms(1000);
		
		while(1)
		{
		for(int h=00 ;h<12;h++)
			{for(int m=00;m<60;m++)
				{for(int s=00;s<60;s++)
					{
					dis_cmd(0x80);					
					LCD_string("THE DIGITALCLOCK");		
					dis_cmd(0xc3);
					dis_data(48);
						dis_cmd(0xc6);
					LCD_string(":");
					dis_cmd(0xc7);
					dis_data(48);
					dis_cmd(0xc9);
					LCD_string(":");
					dis_cmd(0xcb);
					dis_data(48);
		
					
					


					
					dis_cmd(0x80);					
					LCD_string("THE DIGITALCLOCK");		
					dis_cmd(0xc3);
					LCD_num(h);
						dis_cmd(0xc6);
					LCD_string(":");
					dis_cmd(0xc7);
					LCD_num(m);
					dis_cmd(0xc9);
					LCD_string(":");
					dis_cmd(0xcb);
					LCD_num(s);
					_delay_ms(4000);
					}
			
				}
			}
		
			
			//_delay_ms(2000);
			//dis_cmd(0x01);
			//x=read_adc(0);
			//	dis_cmd(0xc7);
			//	LCD_num(25354);
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
	dis_cmd(0x01);
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
