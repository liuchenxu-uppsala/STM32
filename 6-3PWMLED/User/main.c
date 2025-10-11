#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PMW.h"

int main(void)
{
	Init_PMW();
	while (1)
	{
		for(int index =0;index<100;index++) {
			set_percentage(index);
			Delay_ms(5);
		}
		for(int index =0;index<100;index++) {
			set_percentage(100 -index);
			Delay_ms(5);
		}
	}
}
