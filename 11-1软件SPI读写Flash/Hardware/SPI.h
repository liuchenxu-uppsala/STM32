#ifndef __SPI_H_
#define __SPI_H_
void Init_SPI(void);
void Start(void);
void Stop(void);
uint8_t SendReceiveMessage(uint8_t send_data);
#endif