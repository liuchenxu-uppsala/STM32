#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CounterSensor.h"
#include "RotaryEncoder.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();//OLED初始化
	OLED_Clear();
	Init_Encoder();
	OLED_ShowString(1, 1, "Num:");
	while (1)
	{
		OLED_ShowSignedNum(1, 7, GetNum(), 5);
	}
}
