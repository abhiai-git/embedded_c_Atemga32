#include<avr/io.h>
#include<util/delay.h>

int main()
	{
	DDRB=0b11111111;
	while(1){
	

	for(int i=1;i<=128;i=i*2)
	{
	PORTB=i;
	_delay_ms(1000);
	}
	
	for(int j=128;j>=1;j=j/2)
	{
	PORTB=j;
	_delay_ms(1000);
	}

	}
	return 0;
	}
	
