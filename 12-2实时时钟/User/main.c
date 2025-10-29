#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "SimpleRTC.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	init_rtc();
	while(1) {
		OLED_ShowNum(1,1,GetCounter(),10);
	}
}
