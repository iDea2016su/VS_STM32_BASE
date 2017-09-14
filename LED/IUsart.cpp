#include "IUsart.h"
#include "string.h"
#include "delay.h"

const uint8_t IPriority[12][2] = { 0, 1, 0, 2, 0, 3, 1, 1, 1, 2, 1, 3, 2, 1, 2, 2, 2, 3, 3, 1, 3, 2, 3, 3 };
u8 IUsart::number = 0;
IUsart** IUsart::ust = new IUsart*[5];
IUsart::IUsart()
{
}

IUsart::~IUsart()
{
}
IUsart::IUsart(USART_TypeDef* usartx, 
	u32 bound, 
	u8 pri, 
	uint16_t stopbits, 
	uint16_t party, 
	uint16_t wordlen)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef    USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	IUsart::USARTx = usartx;
	IUsart::Ipri = pri;
	IUsart::Party = party;
	IUsart::StopBits = stopbits;
	IUsart::WordLen = wordlen;
	ust[number] = this;
	number++;
	if (usartx == USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
		GPIO_Init(GPIOA, &GPIO_InitStructure); 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure); 
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	}
	else if (usartx == USART2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	}
	else if (usartx == USART3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	}
#ifdef STM32F10X_HD
	else if (usartx == UART4)
	{
		
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
		USART_DeInit(usartx);  
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	}

	else if (usartx == UART5)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
		USART_DeInit(usartx);  
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	}			  
#endif // STM32F10X_HD
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = IPriority[pri][0];
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = IPriority[pri][1];		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = wordlen;
	USART_InitStructure.USART_StopBits = stopbits;
	USART_InitStructure.USART_Parity = party; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	 
	USART_Init(usartx, &USART_InitStructure); 
	USART_ITConfig(usartx, USART_IT_RXNE, ENABLE); 
	USART_Cmd(usartx, ENABLE); 
}

void IUsart::sendStr(char *str)
{
	while ((*str) != 0)
	{
		while ((USARTx->SR & 0X40) == 0); 
		USARTx->DR = (*str);
		str++;
	}
}
void IUsart::sendStr(const char * str)
{
	while ((*str) != 0)
	{
		while ((USARTx->SR & 0X40) == 0)
			; 
		USARTx->DR = (*str);
		str++;
	}
}


void IUsart::sendStr(u8 * str)
{
	while ((*str) != 0)
	{
		while ((USARTx->SR & 0X40) == 0); 
		USARTx->DR = (*str);
		str++;
	}
}
void IUsart::config(u32 bound, uint16_t stopbits, uint16_t party, uint16_t wordlen)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef    USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = IPriority[Ipri][0];
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = IPriority[Ipri][1];		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = wordlen;
	USART_InitStructure.USART_StopBits = stopbits;
	USART_InitStructure.USART_Parity = party; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	 
	USART_Init(USARTx, &USART_InitStructure); 
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE); 
	USART_Cmd(USARTx, ENABLE); 
}


void IUsart::clear()
{
	receiveLen = 0;
	memset(BUF, 0, 500);
}


void IUsart::open()
{
	status = 1;
	USART_Cmd(USARTx, ENABLE); 
}

void IUsart::close()
{
	status = 0;
	USART_Cmd(USARTx, DISABLE); 
}

void IUsart::sendHex(u8* hex, int len)
{
	int i = 0;
	for (i = 0; i < len; i++)
	{
		while ((USARTx->SR & 0X40) == 0)
			; 
		USARTx->DR = (*hex);
		hex++;
	}
}
void IUsart::sendChar(u8 c)
{
	while ((USARTx->SR & 0X40) == 0)
		; 
	USARTx->DR = c;
}
void IUsart::bufSub()
{
	bufLen--;
}

void IUsart::bufAdd()
{
	bufLen++;
}

void IUsart::setCount(u8 c)
{
	number = c;
}
u8 IUsart::getNumber()
{
	return number;
}
USART_TypeDef* IUsart::getUst()
{
	return USARTx;
}


void IUsart::receive(u8 h)
{
	BUF[receiveLen] = h;
	receiveLen++;
}


int IUsart::getReceiveLen()
{
	return receiveLen;
}


u8 * IUsart::getBuf()
{
	return BUF;
}

void IUsart::sendStrwithRep(string stri, const char* rep, u8 num)
{
	int test_num = 0;
	int i = 0;
	const char * str = stri.c_str();
	while (1)
	{   
		test_num++;
		receiveLen = 0;
		memset(BUF, 0, 500);
		sendStr(str);
		delay_ms(3000);

#ifdef DEBUG
		print("func:  ");
		print(__func__);
		print("\r\n");
		print("Command:");
		print(str);
		print("\r\n");
		print("Reply:");
		print("(");
		print(rep);
		print(")");
		print("\r\nreceive:");
		print((const char *)BUF);	 
		print("\r\n");
#endif // DEBUG
		if ((NULL != strstr((const char *)BUF, (const char *)rep)))
		{
			test_num = 0;
			break;
		}
		else 
		{
			delay_ms(100);
		}
		if (test_num >= num) 
		{
			test_num = 0;
			NVIC_SystemReset();
		}
	}
}
void print(const char* str)
{
	while ((*str) != 0)
	{
		while ((USART1->SR & 0X40) == 0)
			; 
		USART1->DR = (*str);
		str++;
	}
}


extern "C" void USART1_IRQHandler(void)                 
{
	u8 data;
	u8 n, i;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
	{
		data = USART_ReceiveData(USART1); 
		n = IUsart::getNumber();
		for (i = 0; i < n; i++)
		{
			if (IUsart::ust[i]->getUst() == USART1)
			{
				IUsart::ust[i]->receive(data);
				break;
			}
		}
	} 
}
extern "C" void USART2_IRQHandler(void)                 
{
	u8 data;
	u8 n, i;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
	{
		data = USART_ReceiveData(USART2); 
		n = IUsart::getNumber();
		for (i = 0; i < n; i++)
		{
			if (IUsart::ust[i]->getUst() == USART2)
			{
				IUsart::ust[i]->receive(data);
				break;
			}
		}
	} 
}



