#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "ADC.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	OLED_ShowString(1,1,"ADC1:");
	OLED_ShowString(2,1,"ADC1:");
	uint16_t ADC_Value1 = 0;
	uint16_t ADC_Value2 = 0;
	AD_Init();
	while (1)
	{
		ADC_Value1 = Get_AD_Value(ADC_Channel_2);
		ADC_Value2 = Get_AD_Value(ADC_Channel_1);
		OLED_ShowNum(1, 6, ADC_Value1, 4);
		OLED_ShowNum(2, 6, ADC_Value2, 4);
		Delay_ms(100);
	}
}
