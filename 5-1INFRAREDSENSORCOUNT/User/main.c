#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CounterSensor.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();//OLED初始化
	OLED_Clear();
	Init_Counter_Sensor();
	while (1)
	{
		OLED_ShowNum(1, 7, GetCount(), 5);
	}
}
