#include "stm32f10x.h"                  // Device header
uint16_t counter = 0;
void Init_Counter_Sensor(void){
	//GPIO AFIO Enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//GPIO Config
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitTypeDefStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitTypeDefStructure);
	
	//AFIO Config
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
	//EXTI Config
	EXTI_InitTypeDef EXTI_InitTypeDefStructure;
	EXTI_InitTypeDefStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitTypeDefStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitTypeDefStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitTypeDefStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitTypeDefStructure);
	
	//NVIC Group
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	
	//NVIC Config
	NVIC_InitTypeDef NVIC_InitTypeDefStructure;
	NVIC_InitTypeDefStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitTypeDefStructure);
}

uint16_t GetCount(){
	return counter;
}

void EXTI15_10_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line14) == SET){
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
				counter ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
