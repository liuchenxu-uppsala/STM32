#ifndef __USART_H_
#define __USART_H_
#include <stdio.h>
void Init_USART(void);
void Send_Byte(uint16_t data);
void Send_Array(uint16_t* arr,uint16_t length);
void Send_String(char* string);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);
#endif