#include "stm32f10x.h"                  // Device header

void Write_MOSI(uint8_t data){
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)data);
}

void Write_CLK(uint8_t data){
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)data);
}

void Write_CS(uint8_t data){
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)data);
}
uint8_t Read_MISO(void) {
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void Init_SPI(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitTypeDefStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitTypeDefStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	Write_CS(1);//CS 片选
	Write_CLK(0);//CLK
}

void Start(void){
	Write_CS(0);
}

void Stop(void) {
	Write_CS(1);
}

uint8_t SendReceiveMessage(uint8_t send_data){
	uint8_t i, ByteReceive = 0x00;
	for (i = 0; i < 8; i ++)
	{
		Write_MOSI(!!(send_data & (0x80 >> i)));
		Write_CLK(1);
		if (Read_MISO()){ByteReceive |= (0x80 >> i);}
		Write_CLK(0);
	}
	return ByteReceive;	
}
