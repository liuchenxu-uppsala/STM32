#include "stm32f10x.h"                  // Device header
void Init_IC(void){
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitTypeDef_Structure;
	GPIO_InitTypeDef_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitTypeDef_Structure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitTypeDef_Structure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDef_Structure);
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDef_structure;
	TIM_TimeBaseInitTypeDef_structure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeDef_structure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeDef_structure.TIM_Period = 65536 -1 ;
	TIM_TimeBaseInitTypeDef_structure.TIM_Prescaler = 72 -1;
	TIM_TimeBaseInitTypeDef_structure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitTypeDef_structure);
	
	TIM_ICInitTypeDef TIM_ICInitTypeDef_Structure;
	TIM_ICInitTypeDef_Structure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitTypeDef_Structure.TIM_ICFilter = 0xF;
	TIM_ICInitTypeDef_Structure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitTypeDef_Structure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitTypeDef_Structure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3, &TIM_ICInitTypeDef_Structure);
	
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3,ENABLE);
	
}

uint32_t get_Freq(){
	return 1000000/(TIM_GetCapture1(TIM3) + 1);
}