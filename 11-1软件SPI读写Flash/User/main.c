#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "W25Q64Driver.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Init_Q64();
	uint8_t MID;
	uint16_t DID;
	Get_JEDEC_ID(&MID,&DID);
	OLED_ShowHexNum(1,1,MID,2);
	OLED_ShowHexNum(1,5,DID,4);
}
