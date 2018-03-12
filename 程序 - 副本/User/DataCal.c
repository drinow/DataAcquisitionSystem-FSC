#include "DataCal.h"

u32 CAPTURE_Buff[4]={0,0,0,0};
extern u8  TIM4CH1_CAPTURE_STA,TIM4CH2_CAPTURE_STA,  //���벶��״̬   
					 TIM4CH3_CAPTURE_STA,TIM4CH4_CAPTURE_STA;
					 
extern u16 TIM4CH1_CAPTURE_VAL_A,TIM4CH1_CAPTURE_VAL_B, //���벶��ֵ
					 TIM4CH2_CAPTURE_VAL_A,TIM4CH2_CAPTURE_VAL_B,
					 TIM4CH3_CAPTURE_VAL_A,TIM4CH3_CAPTURE_VAL_B,	
					 TIM4CH4_CAPTURE_VAL_A,TIM4CH4_CAPTURE_VAL_B;		
//����ʱ�����
void CAPTURE_Cal(void)
{
		u32 temp=0;
		//TIM4
		if(TIM4CH1_CAPTURE_STA&0X80)   
		{
			temp=TIM4CH1_CAPTURE_STA&0X3F;					
			temp*=65536;             
			temp+=TIM4CH1_CAPTURE_VAL_B;    
			temp-=TIM4CH1_CAPTURE_VAL_A;
			CAPTURE_Buff[0]=temp;
			TIM4CH1_CAPTURE_STA=0;
		}
		if(TIM4CH2_CAPTURE_STA&0X80) 
		{
			temp=TIM4CH2_CAPTURE_STA&0X3F;					
			temp*=65536;             
			temp+=TIM4CH2_CAPTURE_VAL_B;    
			temp-=TIM4CH2_CAPTURE_VAL_A;
			CAPTURE_Buff[1]=temp;
			TIM4CH2_CAPTURE_STA=0;
		}
		if(TIM4CH3_CAPTURE_STA&0X80)   
		{
			temp=TIM4CH3_CAPTURE_STA&0X3F;	
			temp*=65536;            
			temp+=TIM4CH3_CAPTURE_VAL_B;    
			temp-=TIM4CH3_CAPTURE_VAL_A;
			CAPTURE_Buff[2]=temp;
			TIM4CH3_CAPTURE_STA=0;   
		}
		if(TIM4CH4_CAPTURE_STA&0X80)      //�ɹ���ƽ����һ������
		{
			temp=TIM4CH4_CAPTURE_STA&0X3F;					 //���������������
			temp*=65536;              //���ʱ���ܺ�		 ��һ���������һ��ʮ��λ�ļ���������
			temp+=TIM4CH4_CAPTURE_VAL_B;    //�õ��ܵĸߵ�ƽʱ��
			temp-=TIM4CH4_CAPTURE_VAL_A;
			CAPTURE_Buff[3]=temp;
			TIM4CH3_CAPTURE_STA=0;      //������һ�β���
		}
}

