#include "stm32f10x.h"                  // Device header
int16_t num = 0;
void Init_Encoder(void){
	// Enable Bus
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	// Enable GPIOB
	GPIO_InitTypeDef GPIO_InitTypeDef_Structure;
	GPIO_InitTypeDef_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitTypeDef_Structure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitTypeDef_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitTypeDef_Structure);
	
	//Enable AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	//EXTI
	EXTI_InitTypeDef EXTI_InitTypeDef_Struct;
	EXTI_InitTypeDef_Struct.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	EXTI_InitTypeDef_Struct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitTypeDef_Struct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitTypeDef_Struct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitTypeDef_Struct);
	
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//NVIC Config
	NVIC_InitTypeDef NVIC_InitTypeDef_Struct;
	NVIC_InitTypeDef_Struct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitTypeDef_Struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeDef_Struct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitTypeDef_Struct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitTypeDef_Struct);
	
	NVIC_InitTypeDef_Struct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitTypeDef_Struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeDef_Struct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitTypeDef_Struct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitTypeDef_Struct);
}

// Line0 Interrupt
void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0) == SET) {
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 1){
			num++;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);	
	}
}

// Line1 Interrupt
void EXTI1_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line1) == SET) {
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 1){
			num--;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);	
	}
}

int16_t GetNum(){
	return num;
}

