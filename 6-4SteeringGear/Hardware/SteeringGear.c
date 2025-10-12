#include "stm32f10x.h"                  // Device header

void InitSteeringGear(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitTypeDef_Structure;
	GPIO_InitTypeDef_Structure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeDef_Structure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitTypeDef_Structure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDef_Structure);
	
	TIM_InternalClockConfig(TIM2);
	
	
}
