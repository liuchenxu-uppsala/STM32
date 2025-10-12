#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Tim.h"
#include "Encoder.h"
int main(void)
{
	
	OLED_Init();
	OLED_Clear();
	Encoder_Init();
	OLED_ShowString(1, 3, "Counter:");				
	while (1)
	{
		OLED_ShowSignedNum(2, 3, Get_Counter(), 5);
		//OLED_ShowSignedNum(2, 3, Get_Counter(), 5);
		Delay_ms(5);
	}
}
