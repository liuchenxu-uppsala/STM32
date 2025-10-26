#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Init_MPU6050();
	Write_Data(0x19,0xAA);
	uint8_t data = Read_Data(0x19);
	OLED_ShowHexNum(1, 1, data, 2);
}
