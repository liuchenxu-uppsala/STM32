#include "stm32f10x.h"                  // Device header
void Encoder_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitTypeDef_Structure;
	GPIO_InitTypeDef_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitTypeDef_Structure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_InitTypeDef_Structure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDef_Structure);
	//TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDef_structure;
	TIM_TimeBaseInitTypeDef_structure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeDef_structure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeDef_structure.TIM_Period = 65536 -1 ;
	TIM_TimeBaseInitTypeDef_structure.TIM_Prescaler = 1-1;
	TIM_TimeBaseInitTypeDef_structure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitTypeDef_structure);
	
	TIM_ICInitTypeDef TIM_ICInitTypeDef_Structure;
	TIM_ICStructInit(&TIM_ICInitTypeDef_Structure);
	TIM_ICInitTypeDef_Structure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitTypeDef_Structure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitTypeDef_Structure);
	TIM_ICInitTypeDef_Structure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitTypeDef_Structure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitTypeDef_Structure);
	
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,
                                TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);							
	TIM_Cmd(TIM3, ENABLE);
}

int16_t Get_Counter(void){
//	int16_t Temp;
//	Temp = TIM_GetCounter(TIM3);
//	TIM_SetCounter(TIM3, 0);
	return (int16_t)TIM_GetCounter(TIM3);
}