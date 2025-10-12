#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PMW.h"

int main(void)
{
	Init_PMW();
	while (1)
	{
		for(int index =25;index<126;index = index + 25) {
			set_percentage(index);
			Delay_ms(200);
		}
		for(int index =0;index<124;index = index + 25){
			set_percentage(125 -index);
			Delay_ms(200);
		}
	}
}
