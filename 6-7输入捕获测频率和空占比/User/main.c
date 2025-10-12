#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PMW.h"
#include "IC.h"

int main(void)
{
	OLED_Init();
	Init_PMW();
	set_psc(7200 - 1);
	set_CCR(80);
	Init_IC();
	OLED_ShowString(1, 1, "Freq:");
	OLED_ShowString(3, 1, "Duty:");
	while(1) {
		OLED_ShowSignedNum(2, 1, get_Freq(), 7);
		Delay_ms(5);
		OLED_ShowSignedNum(4, 1, get_Duty(), 7);
	}
}
