#include "stm32f10x.h"                  // Device header
#include "SimpleIIC.h"
void Write_Data(uint8_t RegAddress,uint8_t data);

void Init_MPU6050(void){
	Init_IIC();
	Write_Data(0x6B,0x00);
}

void Write_Data(uint8_t RegAddress,uint8_t data){
	IIC_Start();
	IIC_SendByte(0xD0);
	IIC_RecvACk();
	IIC_SendByte(RegAddress);
	IIC_RecvACk();
	IIC_SendByte(data);
	IIC_RecvACk();
	IIC_Stop();
}

uint8_t Read_Data(uint8_t RegAddress){
	uint8_t value;
	
	IIC_Start();
	IIC_SendByte(0xD0);
	IIC_RecvACk();
	IIC_SendByte(RegAddress);
	IIC_RecvACk();
	
	IIC_Start();
	IIC_SendByte(0xD1);
	IIC_RecvACk();
	value = IIC_ReadByte();
	IIC_SendAck(1);
	IIC_Stop();
	return value;
}