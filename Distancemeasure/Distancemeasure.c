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
		
		unsigned int x;
		LCD_init();
		
		ADC_init();
		while(1)
		{
			dis_cmd(0X80);
			LCD_string("Sensor::");
			x=read_adc(0);
			dis_cmd(0X8c);
			LCD_num(x);
			dis_cmd(0xc1);
			dis_cmd(0x18);
			_delay_ms(4000);
			if(x>=414)
			{LCD_string("Distance:: 0.0 to 0.5cm");}
			if((x>412)&&(x<=414))
			{LCD_string("Distance:: 0.5 to 1.0cm");}
			if((x>399)&&(x<=412))
			{LCD_string("Distance:: 1.5 to 2.0cm");}
			if((x>391)&&(x<=399))
			{LCD_string("Distance:: 2.0 to 2.5cm");}
			if((x>384)&&(x<=391))
			{LCD_string("Distance:: 2.5 to 3.0cm");}
			if((x>359)&&(x<=384))
			{LCD_string("Distance:: 3.0 to 3.5cm");}
			if((x>344)&&(x<=359))
			{LCD_string("Distance:: 3.5 to 4.0cm");}
			if((x>335)&&(x<=344))
			{LCD_string("Distance:: 4.0 to 4.5cm");}
			if((x>327)&&(x<=335))
			{LCD_string("Distance:: 4.5 to 5.0cm");}
			if(x<=327)
			{LCD_string("Distance:: 5.0 to above");}

			
		
			
			
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
