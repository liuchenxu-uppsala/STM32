#ifndef __SIMPLE_IIC_H_
#define __SIMPLE_IIC_H_
#include "stdint.h"
void Init_IIC(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendByte(uint8_t data);
uint8_t IIC_ReadByte(void);
void IIC_SendAck(uint8_t AckBit);
uint8_t IIC_RecvACk(void);
#endif