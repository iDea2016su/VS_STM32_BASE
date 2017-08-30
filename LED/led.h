#pragma once
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>	
#include "sys.h"
#define PortA 0
#define PortB 1
#define PortC 2
#define PortD 3
#define PortE 4
#define PortF 5

class LED
{
public:
	LED();
	LED(u8 GPIO, uint16_t io);
    ~LED();
	void config(u8 GPIO, uint16_t io);
	void on();
	void off();
private:
	int status;
	GPIO_TypeDef * mygpio;
	uint16_t myio;
};
