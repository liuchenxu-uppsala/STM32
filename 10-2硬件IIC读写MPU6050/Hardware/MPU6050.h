#ifndef __MPU6050_H_
#define __MPU6050_H_
void Init_MPU6050(void);
void Write_Data(uint8_t RegAddress,uint8_t data);
uint8_t Read_Data(uint8_t RegAddress);
#endif