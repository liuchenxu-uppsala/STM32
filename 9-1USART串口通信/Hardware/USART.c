#include "stm32f10x.h"                  // Device header

void Init_USART(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitTypeDef_Structure;
	GPIO_InitTypeDef_Structure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeDef_Structure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitTypeDef_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDef_Structure);
	
	USART_InitTypeDef USART_InitTypeDef_Structure;
	USART_InitTypeDef_Structure.USART_BaudRate = 9600;
	USART_InitTypeDef_Structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitTypeDef_Structure.USART_Mode = USART_Mode_Tx;
	USART_InitTypeDef_Structure.USART_Parity = USART_Parity_No;
	USART_InitTypeDef_Structure.USART_StopBits = USART_StopBits_1;
	USART_InitTypeDef_Structure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitTypeDef_Structure);
	
	USART_Cmd(USART1, ENABLE);
}

void Send_Byte(uint16_t data) {
	USART_SendData(USART1, data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}
