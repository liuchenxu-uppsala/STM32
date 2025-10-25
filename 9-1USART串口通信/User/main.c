#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "USART.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Init_USART();
	while(1) {
		Send_Byte(0x41);
		Delay_s(1);
	}
}
