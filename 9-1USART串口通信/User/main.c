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
		Send_String("Hello World!\r\n");
		Delay_s(1);
		Serial_Printf("\r\nSerial_Printf Num4=%d", 444);
		Delay_s(1);
	}
//	uint16_t arr[4] = {0x41,0x42,0x43,0x44};
//	Send_Array(arr,4);
}
