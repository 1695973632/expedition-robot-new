#include "adc.h"
#include "delay.h"		 
__IO uint16_t uhADCxConvertedValue[6] ;

__IO uint32_t uwADCxConvertedVoltage = 0;

void ADC_Config(void)
{ 
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;
 /* Enable ADC3, DMA and GPIO clocks ****************************************/ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);    //RCC_AHB1Periph_GPIOF
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  //RCC_APB2Periph_ADC3

/* DMA2 Stream0 channel2 configuration **************************************/
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;     //DMA_Channel_2
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADCx_DR_ADDRESS;     // ((uint32_t)&ADC3->DR)
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)uhADCxConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 6;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
   DMA_Init(DMA2_Stream0, &DMA_InitStructure);   //DMA2_Stream0
   DMA_Cmd(DMA2_Stream0, ENABLE);
 
   /* Configure ADC3 Channel7 pin as analog input ******************************/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;   
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;   
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
   
   /* ADC Common Init **********************************************************/
   ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
   ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
   ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
   ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
   ADC_CommonInit(&ADC_CommonInitStructure);
 
   /* ADC3 Init ****************************************************************/
   ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
   ADC_InitStructure.ADC_ScanConvMode = ENABLE;
   ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
   ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
   ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
   ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
   ADC_InitStructure.ADC_NbrOfConversion = 6;
   ADC_Init(ADCx, &ADC_InitStructure);
 
   /* ADCx regular channel7 configuration **************************************/
   ADC_RegularChannelConfig(ADCx, ADC_Channel_7, 1, ADC_SampleTime_480Cycles);
   ADC_RegularChannelConfig(ADCx, ADC_Channel_8, 2, ADC_SampleTime_480Cycles);
   ADC_RegularChannelConfig(ADCx, ADC_Channel_9, 3, ADC_SampleTime_480Cycles);
   ADC_RegularChannelConfig(ADCx, ADC_Channel_10, 4, ADC_SampleTime_480Cycles);
   ADC_RegularChannelConfig(ADCx, ADC_Channel_11, 5, ADC_SampleTime_480Cycles);
   ADC_RegularChannelConfig(ADCx, ADC_Channel_12, 6, ADC_SampleTime_480Cycles);
  /* Enable DMA request after last transfer (Single-ADC mode) */
   ADC_DMARequestAfterLastTransferCmd(ADCx, ENABLE);   //ADC3
 
   /* Enable ADC3 DMA */
   ADC_DMACmd(ADCx, ENABLE);
 
   /* Enable ADC3 */
   ADC_Cmd(ADCx, ENABLE);
   ADC_SoftwareStartConv(ADCx);
}


