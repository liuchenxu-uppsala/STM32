#include "stm32f10x.h"                  // Device header

void Init_Motor(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitTypeDef_Structure_Diresction;
	GPIO_InitTypeDef_Structure_Diresction.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitTypeDef_Structure_Diresction.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitTypeDef_Structure_Diresction.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDef_Structure_Diresction);
	
	GPIO_InitTypeDef GPIO_InitTypeDef_Structure;
	GPIO_InitTypeDef_Structure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeDef_Structure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitTypeDef_Structure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDef_Structure);
	
	//TIM_InternalClockConfig(TIM2);
	
	TIM_OCInitTypeDef TIM_OCInitTypeDef_Structure;
	TIM_OCStructInit(&TIM_OCInitTypeDef_Structure);
	TIM_OCInitTypeDef_Structure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitTypeDef_Structure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitTypeDef_Structure.TIM_OutputState = ENABLE;
	//TIM_OCInitTypeDef_Structure.TIM_Pulse = 25;//CCR
	TIM_OC3Init(TIM2, &TIM_OCInitTypeDef_Structure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100;//ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 14400;//PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	TIM_Cmd(TIM2,ENABLE);
}

//void set_percentage_motor(uint16_t compare_value){
//	TIM_SetCompare3(TIM2,compare_value);
//}

void set_speed(uint16_t speed){
	if(speed > 0){
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	} else{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	}
	TIM_SetCompare3(TIM2,speed);
}