#include "stm32f10x.h"                  // Device header
uint32_t DataCounter;

void SimpleDMA_Init(uint32_t source,uint32_t des, uint32_t size){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DataCounter = size;
	DMA_InitTypeDef DMA_InitTypeDef_Structure;
	DMA_InitTypeDef_Structure.DMA_BufferSize = size;
	DMA_InitTypeDef_Structure.DMA_DIR = DMA_DIR_PeripheralSRC; //外设作为SRC
	DMA_InitTypeDef_Structure.DMA_M2M = DMA_M2M_Enable;
	DMA_InitTypeDef_Structure.DMA_MemoryBaseAddr = des;
	DMA_InitTypeDef_Structure.DMA_MemoryDataSize= DMA_MemoryDataSize_Byte;
	DMA_InitTypeDef_Structure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitTypeDef_Structure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitTypeDef_Structure.DMA_PeripheralBaseAddr = source;
	DMA_InitTypeDef_Structure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitTypeDef_Structure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitTypeDef_Structure.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA1_Channel1, &DMA_InitTypeDef_Structure);
	DMA_Cmd(DMA1_Channel1,DISABLE);
}

void Transfer(){
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1,DataCounter);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	while(DMA_GetFlagStatus(DMA1_FLAG_GL1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_GL1);
}
