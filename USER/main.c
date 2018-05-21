#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "adc.h"
#include "key.h"
#include "collect.h"
#include "myiic.h"
#include "stdlib.h"
#include <stdio.h>
#include "mpu6050.h"
#include "pwm.h"
#include  "Gray.h"


extern __IO uint16_t uhADCxConvertedValue[8] ;
extern __IO uint32_t uwADCxConvertedVoltage;

int minGray = 0,maxGray = 255;

int ErrTwo = 0;
int ErrOne = 0;
int ErrNow = 0;

float sum;

u16 C_6; //ͷ�����  TIM3     1ͨ��
u16 C_7; //��۶��  TIM3     2ͨ��
u16 C_8; //�ұ۶��  TIM3     3ͨ��

u16 F_9; //��ײ����

u16 F_10; //��ͷ�ϵĹ��
u16 F_11;  //���ϵĹ��
u16 F_12;  //��߼���
u16 F_13;  //�ұ߼���
u16 F_14;  //�װ��µĹ��

u16 Flag_1; // ��¼��1
u16 Flag_2; // ��¼��2
u16 Flag_3; // ��¼��3
u16 Flag_4; // ��¼��4

u16 Flag_K;

u16 Road_1=1;//��һ���ߵı�־λ
	
u16 Road_2=0;//�ڶ����ߵı�־λ

/*ǰ�Ҷ���������*/
u16 D_0;  //1�ŵ�
u16 D_1;  //2�ŵ�
u16 D_2;  //11�ŵ�
u16 D_3;  //12�ŵ�

u16 E_9;  //��ͷ�ϵĵ�������
u16 E_10;  //��߰��������
u16 E_11;  //�ұ߰��������
u16 E_4;
u16 E_5;
u16 E_6;


u16 i=0;
void Go(u16 Duty )
{
       TIM_SetCompare1(TIM4,0);	
	
       TIM_SetCompare2(TIM4,Duty);	
	
       TIM_SetCompare3(TIM4,0);	
	
       TIM_SetCompare4(TIM4,Duty);	
}

void Back(u16 Duty )
{
       TIM_SetCompare1(TIM4,Duty);	
	
       TIM_SetCompare2(TIM4,0);	
	
       TIM_SetCompare3(TIM4,Duty);	
	
       TIM_SetCompare4(TIM4,0);	
}

void Stop(u16 Duty )
{
       TIM_SetCompare1(TIM4,0);	
	
       TIM_SetCompare2(TIM4,0);	
	
       TIM_SetCompare3(TIM4,0);	
	
       TIM_SetCompare4(TIM4,0);	

}


void Adjust_Right(u16 Duty ,u16 Rate)
{
       TIM_SetCompare1(TIM4,0);	 
	
       TIM_SetCompare2(TIM4,Duty-Rate);	
	
       TIM_SetCompare3(TIM4,0);	
	
       TIM_SetCompare4(TIM4,Duty);	

}

void Adjust_Left(u16 Duty ,u16 Rate)
{

       TIM_SetCompare1(TIM4,0);	
	
       TIM_SetCompare2(TIM4,Duty);	
	
       TIM_SetCompare3(TIM4,0);	
	
       TIM_SetCompare4(TIM4,Duty-Rate);	
}

void Adjust_Right_back(u16 Duty ,u16 Rate)
{
       TIM_SetCompare1(TIM4,Duty);	
	
       TIM_SetCompare2(TIM4,0);	
	
       TIM_SetCompare3(TIM4,Duty-Rate);	
	
       TIM_SetCompare4(TIM4,0);	
}

void Adjust_Left_back(u16 Duty ,u16 Rate)
{
       TIM_SetCompare1(TIM4,Duty-Rate);	
	
       TIM_SetCompare2(TIM4,0);	
	
       TIM_SetCompare3(TIM4,Duty);	
	
       TIM_SetCompare4(TIM4,0);	
}

void TurnRight(u16 Duty )
{
       TIM_SetCompare1(TIM4,Duty);	
	
       TIM_SetCompare2(TIM4,0);	
	
       TIM_SetCompare3(TIM4,0);	
	
       TIM_SetCompare4(TIM4,Duty);	
}

void TurnLeft(u16 Duty)
{
       TIM_SetCompare1(TIM4,0);	
	
       TIM_SetCompare2(TIM4,Duty);	
	
       TIM_SetCompare3(TIM4,Duty);	
	
       TIM_SetCompare4(TIM4,0);	
}



void Wave_hand(void)
{
	 TIM_SetCompare1(TIM3,1000);delay_ms(200);
	
	 TIM_SetCompare1(TIM3,1900);delay_ms(200);
	
	 TIM_SetCompare1(TIM3,1000);delay_ms(200);
	
	 TIM_SetCompare1(TIM3,1900);delay_ms(200);
	
 	 TIM_SetCompare2(TIM3,1300);delay_ms(100);
	
	 TIM_SetCompare3(TIM3,1600);delay_ms(100);	
		
     TIM_SetCompare2(TIM3,2000);delay_ms(100);
	
 	 TIM_SetCompare3(TIM3,1100);delay_ms(500);
		
	
}
void Shake_Head(void)
{
 	 TIM_SetCompare3(TIM3,1100);delay_ms(2000);
		
     TIM_SetCompare3(TIM3,2000);delay_ms(2000);		       
}
void FollowLine(){
	uint16_t GRAY[8];
	int Rate,i,AL = 0,AR = 0;
	
	for( i = 0;i<8;i++){
		GRAY[i] = normalization(uhADCxConvertedValue[i], maxGray, minGray);
	}
	
	AL = 2*GRAY[0] + 1*GRAY[1] + 0.8*GRAY[2] + 0.5*GRAY[3];  
	AR = 2*GRAY[7] + 1*GRAY[6] + 0.8*GRAY[5] + 0.5*GRAY[4];  
	
	ErrNow = AL - AR;
	Rate = 0.3*ErrNow - 0.02*ErrOne + 0.01*ErrTwo;
	
	ErrTwo = ErrOne;
	ErrOne = ErrNow;
	
	if(Rate < 0){
		//Turn LEFT
	}else{
		//Turn RIGHT
	}
	
}



void back_line(u16 Duty,u16 Rate)
{	    
	E_4=ReadE4;

	E_5=ReadE5;

    E_6=ReadE6;	
	
	 if(E_4==1&&E_5==0&&E_6==1)
	 {
	 Back(Duty); 
	 }
	 else if(E_4==1&&E_5==1&&E_6==0)
	 {
	 Adjust_Right_back(Duty,Rate);
	 }
	 else if(E_4==0&&E_5==1&&E_6==1)
	 {
     Adjust_Left_back(Duty,Rate);
	 }
	 else
	 {
	 Back(Duty);
	 }

}

int GetAvg(){
	int i,sum = 0;
	for(i = 0;i<6;i++){
		sum += uhADCxConvertedValue[0];
	}
	return sum/6;
}


void NumGet(){
	u8 key1;
	int sta;
	
	OLED_Clear();
	OLED_Refresh_Gram();
	delay_ms(200);
	
	OLED_ShowString(0,0,"Program Start",12);
	OLED_Refresh_Gram();
	delay_ms(200);
	
	
	
	sta = waitKey();
	OLED_Clear();
	OLED_Refresh_Gram();
	delay_ms(200);
	
	if(sta == 1){
		while(1){
			OLED_ShowString(0,0,"The Max",12);
			OLED_Refresh_Gram();
			delay_ms(200);
			
			maxGray = GetAvg();
			OLED_ShowNum(25,30,maxGray,3,12);
						
			key1 = ReadE9;
			
			if(key1 == 0){
				waitKey();
				break;
			}
		}
		
		OLED_Clear();
		OLED_Refresh_Gram();
		delay_ms(200);
		
		while(1){
			OLED_ShowString(0,0,"The Min",12);
			OLED_Refresh_Gram();
			delay_ms(200);
			
			minGray = GetAvg();
			OLED_ShowNum(25,30,minGray,3,12);
			
			key1 = ReadE9;
			
			if(key1 == 0){
				waitKey();
				break;
			}
		}
	}else{
		
		OLED_ShowNum(25,30,maxGray,3,12);
		OLED_ShowNum(50,30,minGray,3,12);
		OLED_Refresh_Gram();
		delay_ms(1000);
	
		
	}
}



float Get_GYz()
{
	short add_count;
	float res;
	u8 buf[2];  
	MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG+4,2,buf);
	add_count = ((u16)buf[0]<<8)|buf[1];
	add_count/=4;  //������ʼ��
	res = (float)add_count/200;
	return res;		
}

void Mpu6050_Turn180(int Saver)
{
	  sum = 0;
	
		while(1)
		{
		
	  float gyorz = Get_GYz(); 	//�õ�����������
		
		sum += gyorz; 
		
		if(sum > Saver)
		{

			Stop(0); delay_ms(100);
			
		   break;
		}
		
		TurnLeft(80);

		delay_ms(3);

		}

}

void Mpu6050_Turn90(int Saver)  //��б��
{
	  sum = 0;
	
		while(1)
		{
		
	  float gyorz = Get_GYz(); 	//�õ�����������
		
		sum += gyorz; 
		
		if(sum > Saver)
		{

			Stop(0); delay_ms(100);
			
		   break;
		}
		
		Adjust_Left(50,20);

		delay_ms(3);

		}

}

void LeftRoad(int Duty,int time) 
{
		
		TurnLeft(Duty); delay_ms(time);	
		
		do{
		TurnLeft(Duty);
			
		E_9 = ReadE9;
			
		}while(E_9==1); 
}
void LeftRoad_F(int Duty,int time) 
{
	do{
		FollowLine();
		
		F_12 = ReadF12;
		
		}while(F_12 == 1);
	
		Stop(0);delay_ms(50);
		
		TurnLeft(Duty);delay_ms(time);	
		
		do{
		TurnLeft(Duty);
			
		E_9 = ReadE9;
			
		}while(E_9==1); 
}

void RightRoad(int Duty,int time)  
{

		TurnRight(Duty);delay_ms(time);
		
		do{
			
		TurnRight(Duty);
			
		E_9 = ReadE9;
			
		}while(E_9==1); 
		
		Stop(0);delay_ms(50);
}
void RightRoad_F(int Duty,int time)   
{
		do{
			
		FollowLine();
			
		F_13 = ReadF13;
			
		}while(F_13 == 1);
		
		Stop(0);delay_ms(50);

		TurnRight(Duty);delay_ms(time);
		
		do{
			
		TurnRight(Duty);
			
		E_9 = ReadE9;
			
		}while(E_9==1); 
		
		Stop(0);
}
void GotoPlatForm_1(int Angle)   //��2��ƽ̨
{
			do{
				FollowLine();
				D_1 = ReadD1;
				D_2 = ReadD2;
			}while(D_1 == 1 && D_2 == 1);
			
			Go(50); delay_ms(200);
			
			do{
				Go(50);
				D_1 = ReadD1;
				D_2 = ReadD2;
			}while(D_1 == 1 && D_2 == 1);
			
			Go(50); delay_ms(200);
			
			Stop(0); delay_ms(500);
			
			Wave_hand();
			
			MPU_Init();
						
			Mpu6050_Turn180(Angle);
			
			Stop(0);delay_ms(500);
}

void GotoPlatForm(int Angle)
{
			do{
				FollowLine();
				D_1 = ReadD1;
				D_2 = ReadD2;
			}while(D_1 == 1 && D_2 == 1);
			
			Go(50); delay_ms(200);
			
			do{
				Go(50);
				D_1 = ReadD1;
				D_2 = ReadD2;
			}while(D_1 == 1 && D_2 == 1);
			
			Go(50); delay_ms(240);
			
			Stop(0); delay_ms(500);
			
			MPU_Init();
						
			Mpu6050_Turn180(Angle);
			
			Stop(0);delay_ms(500);
}
void MoveTo(int A,int B){
	int i = 0;
	
	switch(A){
		
		case 1:
		{
			switch(B){
				case 2:{					
					Go(50); delay_ms(800);		//��1��ƽ̨
					do {
						FollowLine();				
						D_0 = ReadD0;
					}while(D_0 == 1);
					
					do{
						FollowLine();
						F_12 = ReadF12;
					}while(F_12 == 1);
				
				} break;
			}
		}
		break;
		
		case 2:
		{
			switch(B){
				
				case 3:
				{
					do {
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);
					
					do{
						FollowLine();
						F_12 = ReadF12;
					}while(F_12 == 1);
				}break;
				case 1:
				{
				GotoPlatForm(1020);
				}
				break;
			}
		}
		break;
		
		case 3:
		{
			switch(B){
				case 4:{
					GotoPlatForm_1(1000);
				}
				break;
				
				case 5:{
					do{
						FollowLine();
						D_1 =  ReadD1;
					}while(D_1 == 1);
					
					for(i = 0; i< 1400;i++){      //�����ٴ�
						FollowLine();
						delay_ms(1);
					}
					do{
						FollowLine();
						D_2 =  ReadD2;
					}while(D_2 == 1);
					
					do{
						Go(50);
						F_12 =  ReadF12;
					}while(F_12 == 1);
					
	
				}
				break;
								
			}
		}
		break;
		
		case 4:
		{
			switch(B){
				case 3:{
					Go(50); delay_ms(500);
					
					do{
						FollowLine();
						 D_2 = ReadD2;
					}while(D_2 == 1) ;
					
					do{
						FollowLine();
						 E_11 = ReadE11;
					}while(E_11 == 1) ;
					
					Stop(0);	delay_ms(100);			
				}
				break;
				
				
			}
		} 
		break;
		
		case 5:
		{
			switch(B){
				case 6:{
					for(i = 0; i< 600;i++){
						FollowLine();
						delay_ms(1);
					}
					
					do{
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);
					
					Stop(0);delay_ms(50);
					do{
						FollowLine();
						E_10 = ReadE10;
					}while(E_10 == 1);				
				}
			    break;
				
				case  2:
				{
					do{
						FollowLine();
						F_10 = ReadF10;
					}while(F_10 == 1);

				//Stop(50, 50);	
					
				do{
					Go(50);
					F_14 = ReadF14;
					}while(F_14 == 1);	
				Stop(0);
				Go(50);delay_ms(200);					
				Stop(0);delay_ms(500);
				do{
					FollowLine();
					F_12 = ReadF12;
					}while(F_12 == 1);
				//Stop(150, 50);delay_ms(100);
				}
				break;
			}
		}
		break;
		case 6:
		{
			switch(B)
			{
					case 5:{
						do{
							FollowLine();D_0=ReadD0;
						}while(D_0==1);Stop(0);
						
						do{
							FollowLine();F_12=ReadF12;
						}while(F_12==1);Stop(0);
						
						do{
							FollowLine();E_10=ReadE10;
						}while(E_10==1);
						
					}
					break;				
				
					case 7:{
						do{
							FollowLine();F_11=ReadF11;
						}while(F_11==1);Stop(0);
						TIM_SetCompare3(TIM3,2000);delay_ms(100);
						do{
							FollowLine();F_9=ReadF9;
						}while(F_9==1);
						for(i = 0; i< 600;i++)
						{
						back_line(100,50);delay_ms(1);
						}
						TIM_SetCompare3(TIM3,1100);delay_ms(100);
					}
					break;
				
					case 8:
					{
						GotoPlatForm(1010);
					}
					break;
					
					case 9:
					{
						do{
						FollowLine();F_14=ReadF14;
						}while(F_14==1);
						
						Stop(0); delay_ms(700);
						Flag_1 = ReadF11;
						
						if(Flag_1 == 0)     //1���Ź�
						{
							
						Flag_1=0;
							
					    do{back_line(100,50);E_5=ReadE5;}while(E_5==1);
					    //Stop(150,50);
					    do{back_line(50,50);F_13=ReadF13;}while(F_13==1);							
						RightRoad(80,200);
						}
						
						else{       //1���ſ�
							Flag_1=1;
							
							Go(50);delay_ms(500);   //���ż����黻��Ѱ��
							
							do{
							FollowLine();D_0 = ReadD0;
							}while(D_0==1);Stop(0);delay_ms(50);
							
							
						}
						
						
						
						
					}
					break;
					case 17:
					{
						do{
						FollowLine();D_3 = ReadD3;
						}while(D_3==1);
						
						for(i = 0; i< 600;i++){
						FollowLine();
						delay_ms(1);
					}
					
					do{
						FollowLine();
						D_2= ReadD2;
					}while(D_2 == 1);
					
					Stop(0);
					do{
						FollowLine();
						E_11 = ReadE11;
					}while(E_11 == 1);		
						
					}
					break;
					case 20:
					{
						do{
						FollowLine();F_14=ReadF14;
						}while(F_14==1);
						
						Stop(0); delay_ms(700);
						Flag_2 = ReadF11;	
                        
						if(Flag_2==0)  //2���Ź�
						{
							
						Flag_2=0;
							
					    do{back_line(80,50);E_5=ReadE5;}while(E_5==1);
					    //Stop(150,50);
						
					    do{back_line(50,50);F_13=ReadF13;}while(F_13==1);
						
						RightRoad(80,200);						
						}
						else
						{
					    Go(50);delay_ms(500);    //���黻��Ѱ��
							
						do{
							FollowLine();D_0 = ReadD0;
						}while(D_0==1);Stop(0);							
						}
					
					}
					break;
			}
					
			
			}	
					
		break;
			
		case 7:
		{
			switch(B)
			{
				case 6:{
					do{back_line(150,50);E_5=ReadE5;}while(E_5==1);
					Stop(0);
					do{back_line(50,50);F_13=ReadF13;}while(F_13==1);
				}break;
			
			

			}
					
			
		}	
					
		break;
			
		case 8:
		{
		switch(B)
		{
			case 6:
			{
				do{
					FollowLine();
					D_0 = ReadD0;
					}while(D_0 == 1);	
				Stop(0);delay_ms(50);
		     } 
			break;  
			 
			case 9:
			{

			
			}
			break;
		}
		
		
		}			
		break;	
		
		case 9:
		{
			switch(B)
			{
				case 10:
				{
						GotoPlatForm(1020);
				}
				break;
				
				case 11:
				{
					do{
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);
					
					Go(50);	delay_ms(300);
				}
				break;
				
				case 12:
				{
					for(i = 0; i< 400;i++)
					{FollowLine();delay_ms(1);}
						
					do{
						FollowLine();
						D_3 = ReadD3;
					}while(D_3 == 1);	
					
				}
				break;	
				case 20:
				{
					do{
						FollowLine();
						D_3= ReadD3;
					}while(D_3 == 1);						
				}
				break;
				
			}
		}
		break;
	
		case 10:
		{
			switch(B)
			{
				case 9:
				{
					Go(50); delay_ms(500);
					do{
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);Stop(0);	
					do{
						//Tracking(420, 0.2, 0.05, 0.02);
						
						Go(50);
						F_12 = ReadF12;
					}while(F_12 == 1);	
				}
				break;
				
				
			}
		}
		break;
		
		case 11:
		{
			switch(B)
			{
				case 12:
				{
					do{
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);	
					
					do{
						FollowLine();
						F_12 = ReadF12;
					}while(F_12 == 1);

					Stop(0);
				}
				break;
			}
			
		}
         break;
		case 12:
		{
			switch(B)
			{
				case 17:
				{
					do{
						FollowLine();
						F_14 = ReadF14;
					}while(F_14 == 1);

					Stop(0);delay_ms(500);
					
					Go(50);delay_ms(500);				
				
					do{
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);	
			
				}
				break;
				
				case 13:
				{
				for(i=0;i<100;i++)
				{
				FollowLine();delay_ms(1);
				}	
				
				RightRoad_F(50,200);			

			    TIM_SetCompare3(TIM3,2000);delay_ms(100);
				
				    do{
					FollowLine();F_9=ReadF9;
					}while(F_9==1);
				
					for(i = 0; i< 100;i++)
					{
					back_line(50,50);delay_ms(1);
					}
					
					TIM_SetCompare3(TIM3,1100);delay_ms(100);
					
					do{
					back_line(50,50);F_12=ReadF12;
					}while(F_12==1);
					
				   Stop(0);
					
				  LeftRoad(50,200);
					
			      do{
					FollowLine();
					F_12 = ReadF12;
				   }while(F_12 == 1);Stop(0);	
				 
				 LeftRoad(50,1);
		
			
				}
			break;	
				
				case 20:
				{
				RightRoad_F(50,200);			

			    TIM_SetCompare3(TIM3,2000);delay_ms(100);
				
				    do{
					FollowLine();F_9=ReadF9;
					}while(F_9==1);
				
					for(i = 0; i< 100;i++)
					{
					back_line(50,50);delay_ms(1);
					}
					
					TIM_SetCompare3(TIM3,1100);delay_ms(100);
					
					do{
					back_line(50,50);F_12=ReadF12;
					}while(F_12==1);
					
				   Stop(0);
					
				  LeftRoad(50,200);
					
			      do{
					FollowLine();
					F_12 = ReadF12;
				   }while(F_12 == 1);Stop(0);	
				 
				 LeftRoad(50,1);
				
				
				}break;					
			}
			
		}
		break;
		case 13:
		{
			switch(B)
			{
				case 12:
				{
					do{
						FollowLine();
						D_3 = ReadD3;
					}while(D_3 == 1);	
						
					
				}
				break;				
				case 15:
				{
				do{
					FollowLine();
					D_0 = ReadD0;
					}while(D_0 == 1);
				for(i=0;i<350;i++)
					{
					FollowLine();delay_ms(1);
					}
					do{
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);
					
				   Stop(0);
					
				   LeftRoad_F(50,200);

			      TIM_SetCompare3(TIM3,2000);delay_ms(100);
					
				    do{
					FollowLine();F_9=ReadF9;
					}while(F_9==1);
					
					for(i = 0; i< 100;i++)
					{
					back_line(50,50);delay_ms(1);
					}
					TIM_SetCompare3(TIM3,1100);delay_ms(100);
					do{
					back_line(50,50);F_12=ReadF12;
					}while(F_12==1);
					
				    Stop(0);
					
					LeftRoad(50,200);
   
				}	
				break;			
				
				case 16:
				{
				do{
					FollowLine();
					D_0 = ReadD0;
					}while(D_0 == 1);
				for(i=0;i<350;i++)
					{
					FollowLine();delay_ms(1);
					}
					do{
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);
					
				   Stop(0);
					
				   LeftRoad_F(50,200);

			      TIM_SetCompare3(TIM3,2000);delay_ms(100);
					
				    do{
					FollowLine();F_9=ReadF9;
					}while(F_9==1);
					
					for(i = 0; i< 100;i++)
					{
					back_line(50,50);delay_ms(1);
					}
					TIM_SetCompare3(TIM3,1100);delay_ms(100);
					do{
					back_line(50,50);F_12=ReadF12;
					}while(F_12==1);
					
				    Stop(0);
					
					RightRoad(50,200);

            		do{
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);
					
				    Stop(0);
					
					LeftRoad_F(50,200);
					
			
				}	
				break;
			}
			
		}
		break;
		case 14:
		{
			switch(B)
			{
				case 13:
				{
						do{
						FollowLine();D_3=ReadD3;
						}while(D_3==1);								
											
				}
                break;						
				
				case 22:
				{
					do{
						FollowLine();
						F_10 = ReadF10;
					}while(F_10 == 1);Stop(0);	
					do{
						Go(50);
						F_12 = ReadF12;
					}while(F_12 == 1);	
					
				Mpu6050_Turn90(500);  //������Ҫ����
				
				for(i=0;i<100;i++)
				{
				Go(50);delay_ms(1);
				}
					
				}
               break;	

				case 16:
				{
						do{
						FollowLine();E_10=ReadE10;
						}while(E_10==1);
								
						do{
						FollowLine();D_0=ReadD0;
						}while(D_0==1);	
											
				}
                break;				
			}
			
		}	
		break;
		case 15:
	  {
		switch(B)
			{
			   case 13:
				  {
						
				do{
					FollowLine();
					D_0 = ReadD0;
					}while(D_0 == 1);
				for(i=0;i<350;i++)
					{
					FollowLine();delay_ms(1);
					}
					do{
						FollowLine();
						D_3 = ReadD3;
					}while(D_3== 1);
   
				}	
				break;	
				
			   case 14:
				  {
						
				do{
					FollowLine();
					D_0 = ReadD0;
					}while(D_0 == 1);
   
				}	
				break;						  
			}
			
			}
	  break;
		case 16:
		{
			switch(B)
			{
				case 6:
				{
				    do{
					FollowLine();F_14=ReadF14;
					}while(F_14==1);
					
					Stop(0);delay_ms(200);
					
					Go(50);delay_ms(500);
							
					do{
						FollowLine();D_3 = ReadD3;
					}while(D_3==1);Stop(0);
				
				
				}break;	
				case 9:
				{
					do{
						FollowLine();D_3 = ReadD3;
					}while(D_3==1);Stop(0);					
				}
				break;
				
			}
			
		}
		break;
		case 17:
		{
			switch(B)
			{
				case 12:
				{
					do{
						FollowLine();F_14=ReadF14;
						}while(F_14==1);
						
						Stop(0); delay_ms(500);	
                
						Go(50);delay_ms(500);
						
						do{
						FollowLine();F_13=ReadF13;
						}while(F_13==1);	
						
					do{
						FollowLine();D_3=ReadD3;
						}while(D_3==1);	

						Stop(0); delay_ms(100);	
						   						
    						
				}
				break;					
				
				case 18:
				{
					do{
					FollowLine();F_11=ReadF11;
						
					}while(F_11==1);Stop(0);
					
					TIM_SetCompare3(TIM3,2000);delay_ms(100);
					
					do{
				FollowLine();F_9=ReadF9;
					}while(F_9==1);
					
					for(i = 0; i< 600;i++)
					{
					back_line(100,50);delay_ms(1);
					}
					
					TIM_SetCompare3(TIM3,1100);delay_ms(100);				
				}
				break;	
				
				case 19:
				{
				GotoPlatForm(1000);
				}
				break;
			}
			
		}
		break;
		case 18:
		{
			switch(B)
			{
				case 17:
				{
					do{back_line(150,50);E_5=ReadE8;}while(E_5==1);
					Stop(0);
					do{back_line(50,50);F_12=ReadF12;}while(F_12==1);			
				}
				break;
			}
			
		}
		break;
		
		case 19:
		{
			switch(B)
			{
				case 5:
				{
					Go(450); delay_ms(500);
					do{
						FollowLine();
						D_2 = ReadD2;
					}while(D_2 == 1);Stop(0);	
					do{
						Go(50);
						F_13 = ReadF13;
					}while(F_13 == 1);
                   for(i=0;i<300;i++)
					{
					FollowLine();delay_ms(1);
					}
					do{
						FollowLine();
						F_12 = ReadF12;
					}while(F_12 == 1);					
				Stop(0);delay_ms(100);
                  for(i=0;i<200;i++)
					{
					Go(50);delay_ms(1);
					}					
					
				do{
					Go(50);
						F_12 = ReadF12;
					}while(F_12 == 1);	

					Stop(0);delay_ms(100);
				}
               break;				
			}
		
		}	
	    break;
		case 20:
		{
			switch(B)
			{
				case 9:
				{
					do{
						FollowLine();
						D_3 = ReadD3;
					}while(D_3 == 1);Stop(0);	
					do{
						Go(50);
						F_13 = ReadF13;
					}while(F_13 == 1);				
				
				}
               break;	

				case 6:
				{
						do{
						FollowLine();F_14=ReadF14;
						}while(F_14==1);
				
						Stop(0); delay_ms(100);
						
						Go(50);delay_ms(500);
						
						do{
						FollowLine();D_1=ReadD1;
						}while(D_1==1);	
						
						do{
						Go(50);F_12=ReadF12;
						}while(F_12==1);
				
					
				}
                break;				
			}
			
		}
		break;
		case 22:
		{
			switch(B)
			{
				case 14:
				{
					
				for(i=0;i<200;i++)
				{
				FollowLine();delay_ms(1);
				}									
					
				do{
						FollowLine();
						D_3 = ReadD3;
					}while(D_3 == 1);

				
				}
               break;					
				case 23:
				{
				do{
						FollowLine();
						D_3 = ReadD3;
					}while(D_3 == 1);
				
				do{
						FollowLine();
						F_13 = ReadF13;
					}while(F_13 == 1);

				do{
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);		

				for(i=0;i<200;i++)
				{
				FollowLine();delay_ms(1);
				}	

				do{
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);

				for(i=0;i<200;i++)
				{
				FollowLine();delay_ms(1);
				}	
	
				GotoPlatForm(1000);
				
				
				}
               break;	

				case 24:
				{
						do{
						FollowLine();F_10=ReadF10;
						}while(F_10==1);
				
                        GotoPlatForm(1000);
				
					
				}
                break;				
			}
			
		}
      break;
		case 23:
		{
			switch(B)
			{
				case 22:
				{
				for(i=0;i<500;i++)
				{
				FollowLine();delay_ms(1);
				}						
					
				do{
						FollowLine();
						D_3 = ReadD3;
					}while(D_3 == 1);

				for(i=0;i<200;i++)
				{
				FollowLine();delay_ms(1);
				}	

				do{
						FollowLine();
						D_3 = ReadD3;
					}while(D_3 == 1);	

				do{
						FollowLine();
						D_0 = ReadD0;
					}while(D_0 == 1);		

				do{
						FollowLine();
						F_10 = ReadF10;
					}while(F_10 == 1);
          
				for(i=0;i<500;i++)     //��б��
				{
				Go(50);delay_ms(1);
				}					
				
				
				}
               break;			
			}
			
		}
      break;
		case 24:
		{
			switch(B)
			{
				case 22:
				{
				for(i=0;i<500;i++)
				{
				FollowLine();delay_ms(1);
				}						
					
				do{
						FollowLine();
						F_10 = ReadF10;
					}while(F_10 == 1);

				for(i=0;i<250;i++)
				{
				Go(50);delay_ms(1);
				}	
				
                Stop(0);delay_ms(500);
				
				Mpu6050_Turn180(500);
				
				
				}
               break;			
			}
			
		}
      break;		
		
	}	
}


int main(void)
{ 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);     //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
 	OLED_Init();				//��ʼ��OLED
	ADC_Config();
	KEY_Init();
	IIC_Init(); 
    MPU_Init();
	Gray_Init();
	TIM4CH_PWM_Init(199,83);   //���ڲ��ܳ���190
	TIM3CH_PWM_Init(19999,83);
	
	
	NumGet();
	
	while(1) 
	{	
		
	Flag_K=0;
	
	F_9=0;
     while(1)  //�������
	{
		F_11=ReadF11; if(F_11==1) break;
	}		
		
	if(Road_1==1)   //��һ��·��
	{		
			MoveTo(1, 2); 
		
			MoveTo(2, 3);   
		
			MoveTo(3, 4);   
		
			MoveTo(4, 3);   
		
			do{
			TurnRight(50);
			E_9=ReadE9;
			}while(E_9==1); 
			
			Stop(0); delay_ms(100);

			MoveTo(3, 5);
			
			LeftRoad(50,1);

			MoveTo(5, 6);
			
			LeftRoad(50,1);
		         	
			MoveTo(6, 7);
			
            MoveTo(7, 6);
			
            RightRoad(50,1);
			
			MoveTo(6, 8);
			
			MoveTo(8, 6);
			
			LeftRoad_F(50,500);
			
			MoveTo(6, 9);
			
		if(Flag_1==1)	  //1���ſ�
		{
			
			LeftRoad_F(50,200);
			
			MoveTo(9, 10);
			
			MoveTo(10, 9);
			
			MoveTo(9,12);
			
			LeftRoad_F(50,200);
			
			MoveTo(12,13);
			
			MoveTo(13,15);
			
			MoveTo(15,14);	

			LeftRoad_F(50,200);
			
			MoveTo(14,22);		

			MoveTo(22,23);	
			
			MoveTo(23,22);	

			MoveTo(22,24);	
			
			MoveTo(24,22);	

			MoveTo(22,14);	
			
			RightRoad(80,200);
			
			MoveTo(14,16);		

            LeftRoad(80,200);
			
			MoveTo(16,6);
			
			LeftRoad_F(50,200);
			
			MoveTo(6,17);
			
			RightRoad(50,200);
			
			MoveTo(17,18);
			
            MoveTo(18,17);
			
			LeftRoad(50,200);
			
			MoveTo(17,19);
			
			MoveTo(19,5);
			
			LeftRoad(50,200);
			
			MoveTo(5,2);
			
		    RightRoad(50,200);			
			
			MoveTo(2,1);
			
			delay_ms(3000);
			
		}
			
		
	else    //1���Ź�
	{
	MoveTo(6, 20);
		
    if(Flag_2==1)   //2���ſ�	
	{	
	LeftRoad_F(50,200);
		
    MoveTo(20, 9);
	
	LeftRoad(50,200);
		
	MoveTo(9, 10);
					
	MoveTo(10, 9);
			
	MoveTo(9,12);
			
	LeftRoad_F(50,200);
			
	MoveTo(12,13);
			
	MoveTo(13,15);
			
	MoveTo(15,14);	

	LeftRoad_F(50,200);
			
	MoveTo(14,22);		

	MoveTo(22,23);	
			
	MoveTo(23,22);	

	MoveTo(22,24);	
			
	MoveTo(24,22);	

	MoveTo(22,14);	
			
	RightRoad(80,200);
			
	MoveTo(14,16);		

    LeftRoad(80,200);		
	/**/	
		
	MoveTo(16,9);

    LeftRoad(50,200);
	
	MoveTo(9,20);

    RightRoad_F(50,200);
	
	MoveTo(20,6);
	
	LeftRoad(50,200);
	
	MoveTo(6,17);
	
	RightRoad(50,200);
			
	MoveTo(17,18);
			
    MoveTo(18,17);
			
	LeftRoad(50,200);
			
	MoveTo(17,19);
			
	MoveTo(19,5);
			
	LeftRoad(50,200);
			
	MoveTo(5,2);
			
    RightRoad(50,200);			
			
	MoveTo(2,1);
			
	delay_ms(3000);
	
       }
	else   //1���Ź� 2���Ź�  4���ſ�
	{
		
	MoveTo(6,5);	
		
	LeftRoad(50,200);
		
	MoveTo(17,12);	
		
	MoveTo(12,20);		
		
	MoveTo(13,15);	
		
	MoveTo(15,14);	

	LeftRoad_F(50,200);
			
	MoveTo(14,22);		

	MoveTo(22,23);	
			
	MoveTo(23,22);	

	MoveTo(22,24);	
			
	MoveTo(24,22);	

	MoveTo(22,14);	
			
	LeftRoad(80,200);
			
	MoveTo(14,13);			
	/**/	
	
	RightRoad_F(80,200);
		
	MoveTo(13,12);		

	MoveTo(12,17);	

    LeftRoad(50,200);

	MoveTo(17,18);
			
    MoveTo(18,17);
			
	LeftRoad(50,200);
			
	MoveTo(17,19);
			
	MoveTo(19,5);
			
	LeftRoad(50,200);
			
	MoveTo(5,2);
			
    RightRoad(50,200);			
			
	MoveTo(2,1);
	
	Flag_K=1; Road_2=1; Road_1=0;
			
	delay_ms(3000);
	
	
	}
	   
	   
	}
		
		
       }
	
	if(Flag_K==1)  
	 {
			 
		Stop(0); delay_ms(2000); 

		Flag_K=0;
				 
		 break;
				 
	  }


     if(Road_2==1)   //�ڶ���·��
    {
   if(Flag_1==1)     //1���ſ�
   {
 			MoveTo(1, 2); 
		
			MoveTo(2, 3);   
		
			MoveTo(3, 4);   
		
			MoveTo(4, 3);   
		
			do{
			TurnRight(50);
			E_9=ReadE9;
			}while(E_9==1); 
			
			Stop(0); delay_ms(100);

			MoveTo(3, 5);
			
			LeftRoad(50,1);

			MoveTo(5, 6);
			
			LeftRoad(50,1);
		         	
			MoveTo(6, 7);
			
            MoveTo(7, 6);
			
            RightRoad(50,1);
			
			MoveTo(6, 8);
			
			MoveTo(8, 6);
			
			LeftRoad_F(50,500);
			
			MoveTo(6, 9);  
   
			LeftRoad_F(50,200);
			
			MoveTo(9, 10);
			
			MoveTo(10, 9);
			
			MoveTo(9,12);
			
			LeftRoad_F(50,200);
			
			MoveTo(12,13);
			
			MoveTo(13,15);
			
			MoveTo(15,14);	

			LeftRoad_F(50,200);
			
			MoveTo(14,22);		

			MoveTo(22,23);	
			
			MoveTo(23,22);	

			MoveTo(22,24);	
			
			MoveTo(24,22);	

			MoveTo(22,14);	
			
			RightRoad(80,200);
			
			MoveTo(14,16);		

            LeftRoad(80,200);
			
			MoveTo(16,6);
			
			LeftRoad_F(50,200);
			
			MoveTo(6,17);
			
			RightRoad(50,200);
			
			MoveTo(17,18);
			
            MoveTo(18,17);
			
			LeftRoad(50,200);
			
			MoveTo(17,19);
			
			MoveTo(19,5);
			
			LeftRoad(50,200);
			
			MoveTo(5,2);
			
		    RightRoad(50,200);			
			
			MoveTo(2,1);
			
			delay_ms(3000);
   }
   else     //1���Ź�
   {
	   
   if(Flag_2==1)   //2���ſ�
   {
	MoveTo(1, 2); 
		
	MoveTo(2, 3);   
		
	MoveTo(3, 4);   
		
	MoveTo(4, 3);   
		
	do{
	TurnRight(50);
	E_9=ReadE9;
	}while(E_9==1); 
			
	Stop(0); delay_ms(100);

	MoveTo(3, 5);
			
	LeftRoad(50,1);

	MoveTo(5, 6);
			
	LeftRoad(50,1);
		         	
	MoveTo(6, 7);
			
    MoveTo(7, 6);
			
    RightRoad(50,1);
			
	MoveTo(6, 8);
			
	MoveTo(8, 6);
			
	LeftRoad(80,200);
			
	MoveTo(6, 20);
			
	LeftRoad_F(50,200);
		
    MoveTo(20, 9);
	
	LeftRoad(50,200);
		
	MoveTo(9, 10);
					
	MoveTo(10, 9);
			
	MoveTo(9,12);
			
	LeftRoad_F(50,200);
			
	MoveTo(12,13);
			
	MoveTo(13,15);
			
	MoveTo(15,14);	

	LeftRoad_F(50,200);
			
	MoveTo(14,22);		

	MoveTo(22,23);	
			
	MoveTo(23,22);	

	MoveTo(22,24);	
			
	MoveTo(24,22);	

	MoveTo(22,14);	
			
	RightRoad(80,200);
			
	MoveTo(14,16);		

    LeftRoad(80,200);		
	/**/	
		
	MoveTo(16,9);

    LeftRoad(50,200);
	
	MoveTo(9,20);

    RightRoad_F(50,200);
	
	MoveTo(20,6);
	
	LeftRoad(50,200);
	
	MoveTo(6,17);
	
	RightRoad(50,200);
			
	MoveTo(17,18);
			
    MoveTo(18,17);
			
	LeftRoad(50,200);
			
	MoveTo(17,19);
			
	MoveTo(19,5);
			
	LeftRoad(50,200);
			
	MoveTo(5,2);
			
    RightRoad(50,200);			
			
	MoveTo(2,1);
			
	delay_ms(3000);
   
   }
   else      //2���Ź�
   {
	MoveTo(1, 2); 
		
	MoveTo(2, 3);   
		
	MoveTo(3, 4);   
		
	MoveTo(4, 3);   
		
	do{
	TurnRight(50);
	E_9=ReadE9;
	}while(E_9==1); 
			
	Stop(0); delay_ms(100);

	MoveTo(3, 5);
			
	LeftRoad(50,1);

	MoveTo(5, 6);
			
	LeftRoad(50,1);
		         	
	MoveTo(6, 7);
			
    MoveTo(7, 6);
			
    RightRoad(50,1);
			
	MoveTo(6, 8);
			
	MoveTo(8, 6);  
	   
	do{FollowLine();F_12=ReadF12;}while(F_12==1);
		   
	MoveTo(6,5);	
				
	LeftRoad(50,200);
				
	MoveTo(17,12);	
		
	MoveTo(12,20);		
		
	MoveTo(13,15);	
		
	MoveTo(15,14);	

	LeftRoad_F(50,200);
			
	MoveTo(14,22);		

	MoveTo(22,23);	
			
	MoveTo(23,22);	

	MoveTo(22,24);	
			
	MoveTo(24,22);	

	MoveTo(22,14);	
			
	LeftRoad(80,200);
			
	MoveTo(14,13);			
	/**/	
	
	RightRoad_F(80,200);
		
	MoveTo(13,12);		

	MoveTo(12,17);	

    LeftRoad(50,200);

	MoveTo(17,18);
			
    MoveTo(18,17);
			
	LeftRoad(50,200);
			
	MoveTo(17,19);
			
	MoveTo(19,5);
			
	LeftRoad(50,200);
			
	MoveTo(5,2);
			
    RightRoad(50,200);			
			
	MoveTo(2,1);
	
	Flag_K=1; Road_2=1; Road_1=0;
			
	delay_ms(3000);
		   
   
   }
   
   }

}	
	   
	}
}
