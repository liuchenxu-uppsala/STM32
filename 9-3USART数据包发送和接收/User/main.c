#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "USART.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Init_USART();
//	send_packet[0] = 0x0;
//	send_packet[1] = 0x01;
//	send_packet[2] = 0x02;
//	send_packet[3] = 0x03;
//	Send_Packet();
	while(1) {
		if(Get_ReadStatus() == 1){
			OLED_ShowHexNum(1,1,read_packet[0],2);
			OLED_ShowHexNum(1,4,read_packet[1],2);
			OLED_ShowHexNum(1,7,read_packet[2],2);
			OLED_ShowHexNum(1,10,read_packet[3],2);
		}
	}
}
