#pragma once
#include <string>
#include <stm32f10x_usart.h>
using namespace std;
class IUsart
{
public:
	IUsart();
	IUsart(USART_TypeDef* usartx, u32 bound, u8 pri, uint16_t stopbits, uint16_t party, uint16_t wordlen);
	~IUsart();
	void sendStr(u8 * str);
	void sendStr(string str);
	void sendChar(u8 c);
	void sendInt(int data);
	u8 BUF[500];
private:
	u32 BoundRate;
	USART_TypeDef* USARTx;
	uint16_t StopBits;
	uint16_t Party;
	uint16_t WordLen;
	u8 Ipri;
};

