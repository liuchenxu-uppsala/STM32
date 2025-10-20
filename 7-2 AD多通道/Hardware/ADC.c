#include "stm32f10x.h"                  // Device header
void AD_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_1;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	
	
	ADC_InitTypeDef ADC_InitTypeDef_Structure;
	ADC_InitTypeDef_Structure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitTypeDef_Structure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitTypeDef_Structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitTypeDef_Structure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitTypeDef_Structure.ADC_NbrOfChannel = 1;
	ADC_InitTypeDef_Structure.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &ADC_InitTypeDef_Structure);
	
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t Get_AD_Value(uint8_t ADC_Channel){
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}
