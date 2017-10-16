#include "sys.h"
#include "string.h"
#include "delay.h"
#include "led.h"
#include <IUsart.h>
#include <ITimer.h>
#include "flash.h"
#include "usart.h"
#include "IRam.h"
#include "INb.h"

using namespace flash;
using namespace atcom;

string ip = "139.224.129.147";
string socket = "1234";
string pdp = "CTWAP";
string plmn = "46011";


LED led(PortB, 10);
IUsart log = IUsart(USART1, 9600, 0, USART_StopBits_1, USART_Parity_No, USART_WordLength_8b);
IRam ram = IRam(250);
INb nb = INb(USART2, ip, socket, pdp, plmn, TRUE, B8);

void f()
{
	delay_ms(100); 
	led.off();
	delay_ms(100);
	led.on();
}
void tf()
{
	//uart.sendStr((char *)uart.getBuf());
	//uart.clear();
}
int main()
{	

	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	nb.connectUdp();
   // nb.connectCoap();
   //s ITimer t(500,2,tf);
//	ITimer t1(1000, 3, f);
//	t.start();
//	t1.start();
	//uart.sendStrwithRep(AT_CFUN_0, "OK", 10);
	while (1)
	{
		//log.
	    //log.sendStr(uart.getBuf());
		delay_ms(10000);
		nb.udpStrMsg("okko");
		
	}
}	