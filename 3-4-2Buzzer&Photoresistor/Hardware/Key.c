#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Init_Key(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef InitTypeDefStructure;
	InitTypeDefStructure.GPIO_Mode = GPIO_Mode_IPU;
	InitTypeDefStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&InitTypeDefStructure);
}

uint8_t GetKeyNum(void){
	uint8_t keyNum = 0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == Bit_RESET){
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == Bit_RESET);
		return 1;
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == Bit_RESET){
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == Bit_RESET);
		return 2;
	}
	return 0;
}
