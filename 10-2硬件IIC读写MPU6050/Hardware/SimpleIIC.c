#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Init_IIC(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitTypeDef_Structure;
	GPIO_InitTypeDef_Structure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitTypeDef_Structure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10;
	GPIO_InitTypeDef_Structure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitTypeDef_Structure);
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);	
}

//CLK PB10
void Write_CLK(uint8_t bit){
	if(bit == 0){
		GPIO_WriteBit(GPIOB, GPIO_Pin_10, 0);
	} else {
		GPIO_WriteBit(GPIOB, GPIO_Pin_10, 1);
	}
	Delay_us(10);
}

//SDA PB11
void Write_SDA(uint8_t bit){
	if(bit == 0){
		GPIO_WriteBit(GPIOB, GPIO_Pin_11, 0);
	} else {
		GPIO_WriteBit(GPIOB, GPIO_Pin_11, 1);
	}
	Delay_us(10);
}

//SDA PB11
uint8_t Read_SDA(void) {
	uint8_t value;
	value = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	Delay_us(10);
	return value;
}

void IIC_Start(void){
	Write_SDA(1);
	Write_CLK(1);
	Write_SDA(0);
	Write_CLK(0);
}

void IIC_Stop(void){
	Write_SDA(0);
	Write_CLK(1);
	Write_SDA(1);
}

void IIC_SendByte(uint8_t data){
	for (uint8_t index = 0; index <= 7; index++)
	{
		Write_SDA(data & (0x80 >> index));
		Write_CLK(1);
		Write_CLK(0);
	}
}

uint8_t IIC_ReadByte(void){
	Write_SDA(1);
	uint8_t value = 0x00;
	for (uint8_t index = 0; index < 8; index++)
	{
		Write_CLK(1);
		if (Read_SDA()){value |= (0x80 >> index);}
		Write_CLK(0);
	}
	return value;
}

void IIC_SendAck(uint8_t AckBit){
	Write_SDA(AckBit);
	Write_CLK(1);
	Write_CLK(0);
}

uint8_t IIC_RecvACk(void) {
	Write_SDA(1);
	Write_CLK(1);
	uint8_t value = Read_SDA();
	Write_CLK(0);
	return value;
}

