#include "stm32f10x.h"                  // Device header

void Init_PMW(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitTypeDef_Structure;
	GPIO_InitTypeDef_Structure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeDef_Structure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitTypeDef_Structure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDef_Structure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_OCInitTypeDef TIM_OCInitTypeDef_Structure;
	TIM_OCStructInit(&TIM_OCInitTypeDef_Structure);
	TIM_OCInitTypeDef_Structure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitTypeDef_Structure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitTypeDef_Structure.TIM_OutputState = ENABLE;
	TIM_OCInitTypeDef_Structure.TIM_Pulse = 50;//CCR
	TIM_OC1Init(TIM2, &TIM_OCInitTypeDef_Structure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100 -1;//ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1;//PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	TIM_Cmd(TIM2,ENABLE);
}

void set_CCR(uint16_t compare_value){
	TIM_SetCompare1(TIM2,compare_value);
}

void set_psc(uint32_t prescaller){
	TIM_PrescalerConfig(TIM2,prescaller,TIM_PSCReloadMode_Immediate);
}