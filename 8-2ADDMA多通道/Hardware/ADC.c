#include "stm32f10x.h"                  // Device header

uint16_t PeripheralValues[2];

void AD_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_1;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_55Cycles5);
	ADC_InitTypeDef ADC_InitTypeDef_Structure;
	ADC_InitTypeDef_Structure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitTypeDef_Structure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitTypeDef_Structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitTypeDef_Structure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitTypeDef_Structure.ADC_NbrOfChannel = 2;
	ADC_InitTypeDef_Structure.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1, &ADC_InitTypeDef_Structure);
	
	/*********************************************************************************/
	
	DMA_InitTypeDef DMA_InitTypeDef_Structure;
	DMA_InitTypeDef_Structure.DMA_BufferSize = 2;
	DMA_InitTypeDef_Structure.DMA_DIR = DMA_DIR_PeripheralSRC; //外设作为SRC
	DMA_InitTypeDef_Structure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitTypeDef_Structure.DMA_MemoryBaseAddr = (uint32_t)PeripheralValues;
	DMA_InitTypeDef_Structure.DMA_MemoryDataSize= DMA_MemoryDataSize_HalfWord;
	DMA_InitTypeDef_Structure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitTypeDef_Structure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitTypeDef_Structure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitTypeDef_Structure.DMA_PeripheralDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitTypeDef_Structure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitTypeDef_Structure.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA1_Channel1, &DMA_InitTypeDef_Structure);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	/*********************************************************************************/
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
