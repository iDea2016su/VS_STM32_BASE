#pragma once
#include <string>
#include <stm32f10x_usart.h>
using namespace std;

extern const uint8_t IPriority[12][2];
class IUsart
{
public:
	IUsart();
	IUsart(USART_TypeDef* usartx,u32 bound,u8 pri,uint16_t stopbits,uint16_t party,uint16_t wordlen);
	~IUsart();
	void sendStr(char * str);
	void sendChar(u8 c);
	void sendInt(int data);
	void sendHex(u8* hex, int len);
	void close();
	void open();
	void config(u32 bound, uint16_t stopbits, uint16_t party, uint16_t wordlen);
	void clear();
	void bufAdd();
	void bufSub();
	void setCount(u8 c);
	USART_TypeDef* getUst();
	void receive(u8 h);
	int getReceiveLen();
	u8 * getBuf();
	static u8 getNumber();
	static IUsart** ust;
private:
	u32 BoundRate;
	USART_TypeDef* USARTx;
	uint16_t StopBits;
	uint16_t Party;
	uint16_t WordLen;
	u8 Ipri;
	u8 status;
	int bufLen;
	static u8 number;
	u8 BUF[500];
	int receiveLen;
};

