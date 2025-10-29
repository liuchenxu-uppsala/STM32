#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_WriteBackupRegister(BKP_DR1,0x1234);
	OLED_ShowHexNum(1, 1, BKP_ReadBackupRegister(BKP_DR1), 4);
	while(1);
}
