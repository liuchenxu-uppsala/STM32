#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "SimpleDMA.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	uint8_t Source[4] = {0x01,0x02,0x03,0x04};
	uint8_t Dest[4] = {0x00,0x00,0x00,0x00};
	OLED_ShowString(1, 1, "S:");
	OLED_ShowString(2, 1, "D:");
	
	OLED_ShowHexNum(1, 3, Source[0], 2);
	OLED_ShowHexNum(1, 5, Source[1], 2);
	OLED_ShowHexNum(1, 7, Source[2], 2);
	OLED_ShowHexNum(1, 9, Source[3], 2);
	
	OLED_ShowHexNum(2, 3, Dest[0], 2);
	OLED_ShowHexNum(2, 5, Dest[1], 2);
	OLED_ShowHexNum(2, 7, Dest[2], 2);
	OLED_ShowHexNum(2, 9, Dest[3], 2);
	
	SimpleDMA_Init((uint32_t)Source,(uint32_t)Dest, 4);
	Transfer();
	
	OLED_ShowString(3, 1, "D:");
	OLED_ShowHexNum(3, 3, Dest[0], 2);
	OLED_ShowHexNum(3, 5, Dest[1], 2);
	OLED_ShowHexNum(3, 7, Dest[2], 2);
	OLED_ShowHexNum(3, 9, Dest[3], 2);
}
