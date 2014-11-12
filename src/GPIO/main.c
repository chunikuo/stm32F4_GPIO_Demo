#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_syscfg.h"
#include "demo1.h"
#include "demo2.h"

int main()
{
	demo2();
	//RCC_Configuration();
	//GPIO_Configuration();
	//Interrupts_Configuration();

	//GPIO_ToggleBits(GPIOG, GPIO_Pin_14);

	while(1)
	{
		//if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) != status)
		{
			//GPIO_ToggleBits(GPIOG, GPIO_Pin_13);
			//GPIOG->ODR = GPIOA->IDR << 13;
			//GPIOG->ODR ^= GPIO_Pin_13;
		//	status ^= status;
		}


	}	
	return 0;
}

