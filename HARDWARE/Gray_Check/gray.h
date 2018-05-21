#ifndef __GRAY_H

#define __GRAY_H

#include "sys.h" 

//��ȡE1~11��ֵ 
#define ReadA4 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)  
#define ReadA5 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)   
#define ReadA6 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)   

#define ReadE1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)   //PE1
#define ReadE2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)   //PE2
#define ReadE3 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)   //PE3
#define ReadE4 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)   //PE4
#define ReadE5 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)   //PE5  ��Ҷ�1�ŵ�
#define ReadE6 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)   //PE6  ��Ҷ�2�ŵ�
#define ReadE7 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)   //PE7  ��Ҷ�6�ŵ�
#define ReadE8 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)   //PE8  ��Ҷ�7�ŵ�
#define ReadE9 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)   //PE9
#define ReadE10 	    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10) //PE10
#define ReadE11 	    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11) //PE11

#define ReadF8  	    GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8)   //PF8  ��ײ����
#define ReadF9  	    GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_9)   

#define ReadF10  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)  //��ͷ�ϵĹ��
#define ReadF11  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_11)  //���ϵĹ��
#define ReadF12  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_12)  //��߼���
#define ReadF13  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_13)  //�ұ߼���
#define ReadF14      GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_14)  //�װ��µĹ��

/*ǰ�Ҷȵ���������*/
#define ReadD0 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) //PD1
#define ReadD1 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1) //PD1
#define ReadD2 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) //PD2
#define ReadD3 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3) //PD3
#define ReadD4 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4) //PD4
#define ReadD5 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5) //PD5
#define ReadD6 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6) //PD6
#define ReadD7 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7) //PD7

void Gray_Init(void);

#endif


