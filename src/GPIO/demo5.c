#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_syscfg.h"

void RCC_Configuration_Demo4()
{
	// RCC Configuration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
}

void GPIO_Configuration_Demo()
{
	// GPIO Configuration
	// LED3 (Green): GPIO_Pin_13
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

}


void demo()
{
	RCC_Configuration_Demo();
	GPIO_Configuration_Demo();
	Interrupts_Configuration_Demo();

	// Demo Code: Open Drain, no pull. 
	// Open : Noise on Oscilloscope
	// Drain : 0 on Oscilloscope
	while(1)
	{
        GPIOG -> ODR ^= 1u << 13;
        for(int i = 0;i < 100000;++i) ;
	}
}
