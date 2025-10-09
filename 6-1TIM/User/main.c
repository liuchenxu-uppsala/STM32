#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Tim.h"
uint32_t count;
int main(void)
{
	
	OLED_Init();
	OLED_Clear();	
	Init_Tim();				
	OLED_ShowString(1, 3, "HelloWorld!");				
	while (1)
	{
		OLED_ShowNum(2, 3, count, 5);
		Delay_ms(5);
	}
}
