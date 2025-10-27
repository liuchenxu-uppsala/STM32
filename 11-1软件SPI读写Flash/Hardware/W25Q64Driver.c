#include "stm32f10x.h"                  // Device header
#include "SPI.h"

void Init_Q64(void){
	Init_SPI();
}

void Get_JEDEC_ID(uint8_t* MID, uint16_t* DID) {
	Start();
	SendReceiveMessage(0x9F);
	*MID = SendReceiveMessage(0xFF);
	uint8_t high = SendReceiveMessage(0xFF);
	uint8_t low = SendReceiveMessage(0xFF);
	*DID =  high<<8 | low;
	Stop();
}
