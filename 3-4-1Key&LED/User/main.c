#include "stm32f10x.h" // Device header
#include "delay.h"
#include "LED.h"
#include "Key.h"
int main()
{
	uint8_t KeyNum;
    LED_Init();
	Init_Key();
	while(1){
		KeyNum = GetKeyNum();
		if(KeyNum == 1){
			LED1Turn();
		}
		if(KeyNum == 2){
			LED2Turn();
		}
	}
}
