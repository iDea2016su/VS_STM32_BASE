#include "sys.h"
#include  "delay.h"
#include "led.h"
#include "usart.h"
int main()
{	
	delay_init();	 
	uart_init(9600);
	LED led(PortC, 13);
	led.on();

	while (1)
	{
	 
		delay_ms(1000); 
		led.off();
		
		delay_ms(100);
		led.on();
//		Usart1_print(__FILE__);
	    //printf("%shhhh\r\n", __FILE__);
	}
}	 

