#include<avr/io.h>
#include<util/delay.h>

int main()
	{
	DDRB=0b11111111;
	while(1){
	

	for(int i=1,j=128;i=j;i=i*2,j=j/2)
	{
	PORTB=i+j;
	_delay_ms(1000);
	}
	


	}
	return 0;
	}
	
