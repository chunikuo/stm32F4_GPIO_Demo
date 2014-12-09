#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_syscfg.h"

const uint16_t pins[] = {GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15};
const uint16_t pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
const uint8_t steps[4][4] = {{1,0,0,0} , {0,1,0,0} , {0,0,1,0} , {0,0,0,1}};
uint32_t i = 0;
uint32_t n = 10;

void RCC_Configuration_Demo()
{
    // RCC Configuration
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
}

void GPIO_Configuration_Demo()
{
    // GPIO Configuration
    // LED3 (Green): GPIO_Pin_13
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

}
void Interrupts_Configuration_Demo(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Connect EXTI Line 0 to the button GPIO Pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, GPIO_PinSource0);
	
	/* Configure the EXTI line to generate an interrupt when the button is
	 * pressed. The button pin is high when pressed, so it needs to trigger
	 * when rising from low to high. */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetFlagStatus(EXTI_Line0) != RESET)
	{
        --n;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void delay(uint32_t ms) {
    ms *= 3360;
    while(ms--) {
        __NOP();
    }
}

void demo()
{
    RCC_Configuration_Demo();
    GPIO_Configuration_Demo();
    Interrupts_Configuration_Demo();

    while(1)
    {
        uint8_t j;
        for (j = 0; j < 4; j++) {
            if (steps[i % 4][j] == 0) {
                GPIO_ResetBits(GPIOG, pins[j]);
            } else {
                GPIO_SetBits(GPIOG, pins[j]);
            }
        }
        delay(n);
        i++;
    }
}
