#include "TIM_Capture.h"
#include "stdio.h"



//arr���Զ���װֵ	
//psc��ʱ��Ԥ��Ƶ��
/*�Ƽ�����TIM4_Cap_Init(0xFFFF,71)��1MhzƵ�ʼ���,65536usһ���ж�
*/
void TIM4_Cap_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//   NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef  TIM4_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);	//ʹ��TIM4ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOBʱ��
	
	//GPIO���úòŻ��ȶ����ױ�����
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6);						
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);						
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
	
	//��ʼ����ʱ��4 TIM4	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM4���벶�����
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;	//�½��ز���
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM4_ICInitStructure.TIM_ICFilter = 0x08;//����8���������µ�
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; 
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 
  TIM4_ICInitStructure.TIM_ICFilter = 0x08;
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; 
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 
  TIM4_ICInitStructure.TIM_ICFilter = 0x08;
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4; 
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;	
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 
  TIM4_ICInitStructure.TIM_ICFilter = 0x08;
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	//����nvic.c��
//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  
	
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//������������жϺͲ����ж�	
																						/*ע�����ﲻҪ©��TIM_IT_CC2*/
   TIM_Cmd(TIM4,ENABLE );//ʹ�ܶ�ʱ��4
}
/////////////////////////
//TIMxCHx_CAPTURE_STA����
//[7]		:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]		:0,��û���񵽸ߵ�ƽ;1,�Ѿ����񵽸ߵ�ƽ��.
//[5:0]	:����ߵ�ƽ������Ĵ���
u8  TIM4CH1_CAPTURE_STA=0,TIM4CH2_CAPTURE_STA=0,TIM4CH3_CAPTURE_STA=0,TIM4CH4_CAPTURE_STA=0; //���벶��״̬  
u16 TIM4CH1_CAPTURE_VAL_A,TIM4CH2_CAPTURE_VAL_A,TIM4CH3_CAPTURE_VAL_A,TIM4CH4_CAPTURE_VAL_A; //���벶��ֵ
u16 TIM4CH1_CAPTURE_VAL_B,TIM4CH2_CAPTURE_VAL_B,TIM4CH3_CAPTURE_VAL_B,TIM4CH4_CAPTURE_VAL_B;

//TIM4�жϷ�����
void TIM4_IRQHandler(void)
{     
	u16 tsr;
	OS_CPU_SR  cpu_sr;

	OS_ENTER_CRITICAL();                         
	OSIntEnter();
	OS_EXIT_CRITICAL();
	
	tsr=TIM4->SR;
	//ͨ��1�����¼�
/*1*/if((TIM4CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
	{
/*3(b)*/if(tsr&0X01)//����¼�
		{
			if(TIM4CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM4CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM4CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM4CH1_CAPTURE_VAL_B=0XFFFF;
				} else TIM4CH1_CAPTURE_STA++;
			}	
		}
/*3(a)*/if(tsr&0x02)//�����¼�
		{
			if(TIM4CH1_CAPTURE_STA&0X40)    //������һ���½���
			{ 
				TIM4CH1_CAPTURE_STA|=0X80;  //��ǳɹ�����һ�θߵ�ƽ����
				TIM4CH1_CAPTURE_VAL_B=TIM4->CCR1;//��ȡ��ǰ�Ĳ���ֵ.
				TIM4->CCER&=~(1<<1);      //CC1P=0  ����Ϊ�����ز���		1<<1 �ǵ�һͨ����������ͨ��Ҫ�ı䣬�ĳ�ʲô���ο��ֲἴ��
			}
/*2*/		else                   //��δ��ʼ,��һ�β����½���
			{
				TIM4CH1_CAPTURE_STA=0;    //���
				TIM4CH1_CAPTURE_VAL_B=0;
				TIM4CH1_CAPTURE_STA|=0X40;  //��ǲ������½���
				//TIM4->CNT=0;          //���������,����տ���ʵ�ֶ�ͨ������
				TIM4CH1_CAPTURE_VAL_A=TIM4->CCR1;
				TIM4->CCER|=1<<1;          //CC1P=1  ����Ϊ�½��ز���
			} 
		}                   
	}
	//ͨ��2�����¼�
	if((TIM4CH2_CAPTURE_STA&0X80)==0)
	{
		if(tsr&0X01)//���	  
		{
			if(TIM4CH2_CAPTURE_STA&0X40)
			{
				if((TIM4CH2_CAPTURE_STA&0X3F)==0X3F)
				{
					TIM4CH2_CAPTURE_STA|=0X80;
					TIM4CH2_CAPTURE_VAL_B=0XFFFF;
				} else TIM4CH2_CAPTURE_STA++;
			}	
		}
		if(tsr&0x04)//����				 //====��֮ͬ��:0x02->0x04
		{
			if(TIM4CH2_CAPTURE_STA&0X40)   
			{ 
				TIM4CH2_CAPTURE_STA|=0X80; 
				TIM4CH2_CAPTURE_VAL_B=TIM4->CCR2;//====��֮ͬ��:CCR1->CCR2
				TIM4->CCER&=~(1<<5);      
			}
		else                   
			{
				TIM4CH2_CAPTURE_STA=0;    
				TIM4CH2_CAPTURE_VAL_B=0;
				TIM4CH2_CAPTURE_STA|=0X40;  
				TIM4CH2_CAPTURE_VAL_A=TIM4->CCR2;	//====��֮ͬ��:CCR1->CCR2
				TIM4->CCER|=1<<5;          
			} 
		}                   
	}
  //ͨ��3�����¼�
	if((TIM4CH3_CAPTURE_STA&0X80)==0)
	{
		if(tsr&0X01)//���	  
		{
			if(TIM4CH3_CAPTURE_STA&0X40)
			{
				if((TIM4CH3_CAPTURE_STA&0X3F)==0X3F)
				{
					TIM4CH3_CAPTURE_STA|=0X80;
					TIM4CH3_CAPTURE_VAL_B=0XFFFF;
				} else TIM4CH3_CAPTURE_STA++;
			}	
		}
		if(tsr&0x08)//����				 //====��֮ͬ��:0x02->0x04
		{
			if(TIM4CH3_CAPTURE_STA&0X40)   
			{ 
				TIM4CH3_CAPTURE_STA|=0X80; 
				TIM4CH3_CAPTURE_VAL_B=TIM4->CCR3;//====��֮ͬ��:CCR1->CCR2
				TIM4->CCER&=~(1<<9);      
			}
		else                   
			{
				TIM4CH3_CAPTURE_STA=0;    
				TIM4CH3_CAPTURE_VAL_B=0;
				TIM4CH3_CAPTURE_STA|=0X40;  
				TIM4CH3_CAPTURE_VAL_A=TIM4->CCR3;	//====��֮ͬ��:CCR1->CCR2
				TIM4->CCER|=1<<9;          
			} 
		}                   
	}
	//ͨ��4�����¼�
	if((TIM4CH4_CAPTURE_STA&0X80)==0)
	{
		if(tsr&0X01)//���	  
		{
			if(TIM4CH4_CAPTURE_STA&0X40)
			{
				if((TIM4CH4_CAPTURE_STA&0X3F)==0X3F)
				{
					TIM4CH4_CAPTURE_STA|=0X80;
					TIM4CH4_CAPTURE_VAL_B=0XFFFF;
				} else TIM4CH4_CAPTURE_STA++;
			}	
		}
		if(tsr&0x10)//����				 //====��֮ͬ��:0x02->0x04
		{
			if(TIM4CH4_CAPTURE_STA&0X40)   
			{ 
				TIM4CH4_CAPTURE_STA|=0X80; 
				TIM4CH4_CAPTURE_VAL_B=TIM4->CCR4;//====��֮ͬ��:CCR1->CCR2
				TIM4->CCER&=~(1<<13);      
			}
		else                   
			{
				TIM4CH4_CAPTURE_STA=0;    
				TIM4CH4_CAPTURE_VAL_B=0;
				TIM4CH4_CAPTURE_STA|=0X40;  
				TIM4CH4_CAPTURE_VAL_A=TIM4->CCR4;	//====��֮ͬ��:CCR1->CCR2
				TIM4->CCER|=1<<13;          
			} 
		}                   
	}
	TIM4->SR=0;//����жϱ�־λ     
	OSIntExit();  
}
//end of file
