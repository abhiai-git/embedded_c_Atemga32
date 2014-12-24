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
void ADC_init(void);
unsigned int read_adc(unsigned char);

int main()
{	DDRD=0b11111111;	
	DDRB=0xff;	
		unsigned int x,y;
		LCD_init();
	//	LCD_num(1234);
		_delay_ms(1000);
		ADC_init();
		while(1)
		{
			dis_cmd(0X80);
			LCD_string("Temperature");
			x=read_adc(0);
			y=x/2;
			dis_cmd(0X8e);
			LCD_num(y);
			
		if (y>70)
{PORTB=0xff;}
else
{PORTB=0x00;}
			
		
				dis_cmd(0xc5);
		LCD_string("Group-34");
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

void ADC_init(void)
{
	ADMUX=ADC_VREE_TYPE & 0xff;
	ADCSRA=0x81;
}

unsigned int read_adc(unsigned char adc_input)
{
	ADMUX=adc_input | (ADC_VREE_TYPE & 0xff);
	_delay_ms(10);
	ADCSRA |=0x40;
	while((ADCSRA & 0x10)==0);
	
	return ADCW;
}
