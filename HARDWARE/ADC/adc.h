#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"         
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ADC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

#define ADCx                     ADC1
#define ADC_CHANNEL              ADC_Channel_8
#define ADCx_CLK                 RCC_APB2Periph_ADC1
#define ADCx_CHANNEL_GPIO_CLK    RCC_AHB1Periph_GPIOB
#define GPIO_PIN                 GPIO_Pin_0
#define GPIO_PORT                GPIOB
#define DMA_CHANNELx             DMA_Channel_0
#define DMA_STREAMx              DMA2_Stream0
#define ADCx_DR_ADDRESS          ((uint32_t)&ADC1->DR)

void ADC_Config(void);
#endif 







