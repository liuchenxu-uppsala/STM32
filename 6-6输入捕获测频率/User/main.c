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
	set_CCR(50);
	Init_IC();
	OLED_ShowString(1, 1, "freq");
	while(1) {
		OLED_ShowSignedNum(2, 1, get_Freq(), 7);
		Delay_ms(5);
	}
}
