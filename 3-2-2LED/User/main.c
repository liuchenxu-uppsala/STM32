#include "stm32f10x.h" // Device header
#include "delay.h"
int main()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // GPIO_ResetBits(GPIOA, GPIO_Pin_0);
    // GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
    unsigned long index = 0;
    GPIO_WriteBit(GPIOA,GPIO_InitStructure.GPIO_Pin,Bit_SET);
    while (1)
    {   
        GPIO_WriteBit(GPIOA, GPIO_Pin_0 << index % 8, Bit_RESET);
        Delay_ms(100);
        GPIO_WriteBit(GPIOA, GPIO_Pin_0 << index % 8, Bit_SET);
        index = index + 1;
        if (index == 8)
        {
            index = 0;
        }
        Delay_ms(100);
    }
}
