#include  "Gray.h"



//���ø�����IO�ڵ�������� E1~4 ǰ��ĻҶ�  E5~8����ĻҶ�  E9~10��翪��  11��ײ����


//���ø�����IO�ڵ�������� E1~4 ǰ��ĻҶ�  E5~8����ĻҶ�  E9~10��翪��  11��ײ���� 

//��ײģ��δ�����ߵ�ƽ 1

//�ҶȰ�����0 ������1

//���û���ϰ���ߵ�ƽ
void Gray_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure1;	
	GPIO_InitTypeDef  GPIO_InitStructure2;
	GPIO_InitTypeDef  GPIO_InitStructure3;
	GPIO_InitTypeDef  GPIO_InitStructure4;
    GPIO_InitTypeDef  GPIO_InitStructure5;
    GPIO_InitTypeDef  GPIO_InitStructure6;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//GPIOEʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//GPIOFʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//GPIOAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//GPIOBʱ��
	
    GPIO_InitStructure6.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	
    GPIO_InitStructure6.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
    GPIO_InitStructure6.GPIO_Speed = GPIO_Speed_100MHz;//100M
    GPIO_InitStructure6.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOA, &GPIO_InitStructure6);//��ʼ��GPIOE2,3,4	
	
	
    GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;//E1234 ǰ��ĻҶ�  5678����ĻҶ� 9 10��� 11��ײ
	
    GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
    GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_100MHz;//100M
    GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOE, &GPIO_InitStructure1);//��ʼ��GPIOE2,3,4
	
    GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_11;	
    GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
    GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_100MHz;//100M
    GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOE, &GPIO_InitStructure2);//��ʼ��GPIOE2,3,4
	
    GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
    GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_50MHz;//50M
    GPIO_InitStructure3.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure3);
	
	
    GPIO_InitStructure4.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
    GPIO_InitStructure4.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
    GPIO_InitStructure4.GPIO_Speed = GPIO_Speed_50MHz;//50M
    GPIO_InitStructure4.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &GPIO_InitStructure4);
  
    GPIO_InitStructure5.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;//LED0��LED1��ӦIO��
    GPIO_InitStructure5.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
    GPIO_InitStructure5.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure5.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure5.GPIO_PuPd = GPIO_PuPd_DOWN;//����
    GPIO_Init(GPIOB, &GPIO_InitStructure5);//��ʼ��GPIO
	
    //GPIO_SetBits(GPIOB,GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7);//GPIOF9,F10���øߣ�����
  

} 

