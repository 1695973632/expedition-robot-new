#include "pwm.h"




//�ĸ������PWM 
 void TIM4CH_PWM_Init(u32 arr,u32 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure12;
	GPIO_InitTypeDef GPIO_InitStructure13;
	GPIO_InitTypeDef GPIO_InitStructure14;
	GPIO_InitTypeDef GPIO_InitStructure15;
	
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	  TIM_OCInitTypeDef  TIM_OCInitStructure1;
	  TIM_OCInitTypeDef  TIM_OCInitStructure2;
	  TIM_OCInitTypeDef  TIM_OCInitStructure3;
	  TIM_OCInitTypeDef  TIM_OCInitStructure4;
	
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM4ʱ��ʹ�� 
	
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTDʱ��	
	
	 

 //GPIOB6�ĳ�ʼ�� 

	GPIO_InitStructure12.GPIO_Pin = GPIO_Pin_12 ;      
	GPIO_InitStructure12.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure12.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure12.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure12.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOD,&GPIO_InitStructure12);              //��ʼ��PD12
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);	//��������
	
	 //GPIOB7�ĳ�ʼ�� 

	GPIO_InitStructure13.GPIO_Pin = GPIO_Pin_13 ;      
	GPIO_InitStructure13.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure13.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure13.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure13.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOD,&GPIO_InitStructure13);              //��ʼ��PD13
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);//��������
	
	 //GPIOB8�ĳ�ʼ�� 

	GPIO_InitStructure14.GPIO_Pin = GPIO_Pin_14 ;      
	GPIO_InitStructure14.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure14.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure14.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure14.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOD,&GPIO_InitStructure14);               //��ʼ��PD14
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);//��������
	
	 //GPIOB9�ĳ�ʼ�� 

	GPIO_InitStructure15.GPIO_Pin = GPIO_Pin_15 ;      
	GPIO_InitStructure15.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure15.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure15.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure15.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOD,&GPIO_InitStructure15);               //��ʼ��PD15
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);//��������
	
//��ʼ����ʱ��4
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��4
	
	
	//��ʼ��TIM4 Channe1 PWMģʽ	 
	TIM_OCInitStructure1.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure1.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure1.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM4,&TIM_OCInitStructure1);



//��ʼ��TIM4 Channe2 PWMģʽ	
	TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC2Init(TIM4,&TIM_OCInitStructure2);
	
	
	//��ʼ��TIM4 Channe3 PWMģʽ	
  TIM_OCInitStructure3.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure3.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure3.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC3Init(TIM4,&TIM_OCInitStructure3);
	
	
	//��ʼ��TIM4 Channe4 PWMģʽ		
	TIM_OCInitStructure4.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure4.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure4.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC4Init(TIM4,&TIM_OCInitStructure4);
	

  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
 
  TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4
}




 



//���������

 void TIM3CH_PWM_Init(u32 arr,u32 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure6;
	  GPIO_InitTypeDef GPIO_InitStructure7;
	  GPIO_InitTypeDef GPIO_InitStructure8;
	  GPIO_InitTypeDef GPIO_InitStructure9;
	
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	  TIM_OCInitTypeDef  TIM_OCInitStructure1;
	  TIM_OCInitTypeDef  TIM_OCInitStructure2;
	  TIM_OCInitTypeDef  TIM_OCInitStructure3;
	  TIM_OCInitTypeDef  TIM_OCInitStructure4;
	
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3ʱ��ʹ�� 
	
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��PORTCʱ��	
	
	 

 //GPIOC6�ĳ�ʼ�� 

	GPIO_InitStructure6.GPIO_Pin = GPIO_Pin_6 ;      
	GPIO_InitStructure6.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure6.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure6.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure6.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure6);              //��ʼ��PC6
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);	//��������
	
	 //GPIOC7�ĳ�ʼ�� 

	GPIO_InitStructure7.GPIO_Pin = GPIO_Pin_7 ;      
	GPIO_InitStructure7.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure7.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure7.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure7.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure7);   
	//��ʼ��PB6
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);//��������
	
	 //GPIOC8�ĳ�ʼ�� 

	GPIO_InitStructure8.GPIO_Pin = GPIO_Pin_8 ;      
	GPIO_InitStructure8.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure8.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure8.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure8.GPIO_PuPd = GPIO_PuPd_DOWN;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure8);              //��ʼ��PB6
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3);//��������
	
	 //GPIOC9�ĳ�ʼ�� 

	GPIO_InitStructure9.GPIO_Pin = GPIO_Pin_9 ;      
	GPIO_InitStructure9.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure9.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure9.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure9.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure9);              //��ʼ��PB6
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3);//��������
	
//��ʼ����ʱ��4
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��4
	
	
	//��ʼ��TIM4 Channe1 PWMģʽ	 
	TIM_OCInitStructure1.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure1.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure1.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM3,&TIM_OCInitStructure1);



//��ʼ��TIM4 Channe2 PWMģʽ	
	TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC2Init(TIM3,&TIM_OCInitStructure2);
	
	
	//��ʼ��TIM4 Channe3 PWMģʽ	
  TIM_OCInitStructure3.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure3.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure3.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC3Init(TIM3,&TIM_OCInitStructure3);
	
	
	//��ʼ��TIM4 Channe4 PWMģʽ		
	TIM_OCInitStructure4.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure4.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure4.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC4Init(TIM3,&TIM_OCInitStructure4);
	

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
    TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM4
}

void Tim_Reset(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure1;
	

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//GPIOAʱ��
 
  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8;//E1234 ǰ��ĻҶ�  5678����ĻҶ� 9 10��� 11��ײ
	
  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure1);//��ʼ��GPIOE2,3,4



}


 
