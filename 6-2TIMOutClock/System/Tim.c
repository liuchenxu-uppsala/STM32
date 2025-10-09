#include "stm32f10x.h"                  // Device header

extern uint32_t count;

void Init_Tim(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitTypeDefStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeDefStructure);
	//TIM_InternalClockConfig(TIM2);
	
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0F);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDefStructure;
	TIM_TimeBaseInitTypeDefStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitTypeDefStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeDefStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeDefStructure.TIM_Period = 9;
	TIM_TimeBaseInitTypeDefStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitTypeDefStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitTypeDefStructure;
	NVIC_InitTypeDefStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitTypeDefStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
		count++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

uint32_t GetCounter(){
	return TIM_GetCounter(TIM2);
}
