#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint16_t value;
uint8_t flag;
void Init_USART(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitTypeDef_Structure;
	GPIO_InitTypeDef_Structure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeDef_Structure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitTypeDef_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDef_Structure);
	
	GPIO_InitTypeDef_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitTypeDef_Structure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitTypeDef_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDef_Structure);
	
	USART_InitTypeDef USART_InitTypeDef_Structure;
	USART_InitTypeDef_Structure.USART_BaudRate = 9600;
	USART_InitTypeDef_Structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitTypeDef_Structure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitTypeDef_Structure.USART_Parity = USART_Parity_No;
	USART_InitTypeDef_Structure.USART_StopBits = USART_StopBits_1;
	USART_InitTypeDef_Structure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitTypeDef_Structure);
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitTypeDef_Structure;
	NVIC_InitTypeDef_Structure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitTypeDef_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeDef_Structure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitTypeDef_Structure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitTypeDef_Structure);
	
	USART_Cmd(USART1, ENABLE);
}

uint8_t Get_ReadStatus(void) {
	if(flag == 1){
		flag = 0;
		return 1;
	}
	return 0;
}

uint16_t GetReadValue(void) {
	return value;
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
		value = USART_ReceiveData(USART1);
		flag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

void Send_Byte(uint16_t data) {
	USART_SendData(USART1, data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

void Send_Array(uint16_t* arr,uint16_t length){
	uint16_t index = 0;
	for(index= 0; index<length; index++){
		Send_Byte(arr[index]);
	}
}

void Send_String(char* string) {
	uint16_t index = 0;
	for(index = 0 ; string[index] != '\0';index++){
		Send_Byte(string[index]);
	}
}

/**
  * 函    数：次方函数（内部使用）
  * 返 回 值：返回值等于X的Y次方
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;	//设置结果初值为1
	while (Y --)			//执行Y次
	{
		Result *= X;		//将X累乘到结果
	}
	return Result;
}

/**
  * 函    数：串口发送数字
  * 参    数：Number 要发送的数字，范围：0~4294967295
  * 参    数：Length 要发送数字的长度，范围：0~10
  * 返 回 值：无
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)		//根据数字长度遍历数字的每一位
	{
		Send_Byte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');	//依次调用Serial_SendByte发送每位数字
	}
}

/**
  * 函    数：使用printf需要重定向的底层函数
  * 参    数：保持原始格式即可，无需变动
  * 返 回 值：保持原始格式即可，无需变动
  */
int fputc(int ch, FILE *f)
{
	Send_Byte(ch);			//将printf的底层重定向到自己的发送字节函数
	return ch;
}

/**
  * 函    数：自己封装的prinf函数
  * 参    数：format 格式化字符串
  * 参    数：... 可变的参数列表
  * 返 回 值：无
  */
void Serial_Printf(char *format, ...)
{
	char String[100];				//定义字符数组
	va_list arg;					//定义可变参数列表数据类型的变量arg
	va_start(arg, format);			//从format开始，接收参数列表到arg变量
	vsprintf(String, format, arg);	//使用vsprintf打印格式化字符串和参数列表到字符数组中
	va_end(arg);					//结束变量arg
	Send_String(String);		//串口发送字符数组（字符串）
}
