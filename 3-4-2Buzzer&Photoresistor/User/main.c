#include "stm32f10x.h" // Device header
#include "delay.h"
#include "Buzzer.h"
#include "LightSensor.h"
int main()
{
	Init_LightSensor();
	InitBuzzer();
	while(1){
		uint8_t flag = Get_LightSensor();
		if(flag == 1) {
			Buzzer_ON();
			Delay_ms(500);
		} else {
			Buzzer_OFF();
			Delay_ms(500);
		}
	}
}
