#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "SimpleIIC.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Init_IIC();
	IIC_Start();
	IIC_SendByte(0xD0);
	uint8_t ack = IIC_RecvACk();
	OLED_ShowNum(1,1,ack,2);
}
