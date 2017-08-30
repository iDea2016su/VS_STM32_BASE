#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>	
#include <led.h>

LED::LED(u8 GPIO, uint16_t io)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	switch (GPIO)
	{
	case PortA: RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); break;
	case PortB: RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); break;
	case PortC: RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); break;
	case PortD: RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); break;
	case PortE: RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); break;
	case PortF: RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE); break;
	default:break;
	}
	switch (io)
	{
	case 0:myio = io = GPIO_Pin_0; break;
	case 1:myio = io = GPIO_Pin_1; break;
	case 2:myio = io = GPIO_Pin_2; break;
	case 3:myio = io = GPIO_Pin_3; break;
	case 4:myio = io = GPIO_Pin_4; break;
	case 5:myio = io = GPIO_Pin_5; break;
	case 6:myio = io = GPIO_Pin_6; break;
	case 7:myio = io = GPIO_Pin_7; break;
	case 8:myio = io = GPIO_Pin_8; break;
	case 9:myio = io = GPIO_Pin_9; break;
	case 10:myio = io = GPIO_Pin_10; break;
	case 11:myio = io = GPIO_Pin_11; break;
	case 12:myio = io = GPIO_Pin_12; break;
	case 13:myio = io = GPIO_Pin_13; break;
	case 14:myio = io = GPIO_Pin_14; break;
	case 15:myio = io = GPIO_Pin_15; break; 
	default:break;
	}
	GPIO_InitStructure.GPIO_Pin = io;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	switch (GPIO)
	{
	case PortA: 
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//GPIO_SetBits(GPIOA, io);
		mygpio = GPIOA; 
		break;
	case PortB: 
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		//GPIO_SetBits(GPIOB, io);
		mygpio = GPIOB; 
		break;
	case PortC: 
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		//GPIO_SetBits(GPIOC, io);
		mygpio = GPIOC; 
		break;
	case PortD: 
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		//GPIO_SetBits(GPIOD, io);
		mygpio = GPIOD;
		break;
	case PortE: 
		GPIO_Init(GPIOE, &GPIO_InitStructure);
		//GPIO_SetBits(GPIOE, io);
		mygpio = GPIOE;
		break;
	case PortF: 
		GPIO_Init(GPIOF, &GPIO_InitStructure);
		//GPIO_SetBits(GPIOF, io);
		mygpio = GPIOF;
		break;
	default:break;
	}
}
void LED::on()
{
	GPIO_SetBits(mygpio, myio);
}
void LED::off()
{
	GPIO_ResetBits(mygpio, myio);
}
LED::~LED()
{
	
}