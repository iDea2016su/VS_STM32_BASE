#include "sys.h"
#include  "delay.h"
#include "led.h"
#include "usart.h"
#include "IUsart.h"
int main()
{	
	delay_init();	 
	uart_init(9600);
	LED led(PortC, 13);
	IUsart uart = IUsart(USART1, 9600, 2, USART_StopBits_1, USART_Parity_No, USART_WordLength_8b);
	while (1)
	{
	 
		delay_ms(1000); 
		led.off();
		
		delay_ms(100);
		led.on();
		uart.sendStr("hello\r\n");
//		Usart1_print(__FILE__);
	    //printf("%shhhh\r\n", __FILE__);
	}
}	 

