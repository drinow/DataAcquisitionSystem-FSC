#include"exti.h"

void  EXTI_Configuration(void)
{


	/*GPIO Configuration*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
{
	/* ����GPIO��ʼ���ṹ�� GPIO_InitStructure */
  	GPIO_InitTypeDef GPIO_InitStructure;
    
  	/* ����PA.0Ϊ�������루EXTI Line0��*/
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_Init(GPIOA , &GPIO_InitStructure);

	/* ����PA.0,PA.1,PA.2,PA.3Ϊ�ⲿ�ж�0����ͨ����EXIT0,EXIT1,EXIT2,EXIT3�� */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA , GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA , GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA , GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA , GPIO_PinSource3);

}

/**********************************************************************/
	/*EXTI_InitStructure*/
{
	/* ����EXIT��ʼ���ṹ�� EXTI_InitStructure */
	EXTI_InitTypeDef EXTI_InitStructure;

	/* �����ⲿ�ж�0ͨ����EXIT Line0�����½���ʱ�����ж� */  
  	EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line1|EXTI_Line2|EXTI_Line3 ;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);
}

/********************************************************************/
{
	/* ����NVIC��ʼ���ṹ�� NVIC_InitStructure */
	NVIC_InitTypeDef NVIC_InitStructure;	
  	/* ѡ��NVIC���ȼ�����2 */
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  	/* ʹ��EXIT 0ͨ�� ��2����ռ���ȼ� ��0����ռ���ȼ� */
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQChannel;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

	/* ʹ��EXIT 1ͨ�� ��2����ռ���ȼ� ��0����ռ���ȼ� */
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQChannel;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

	/* ʹ��EXIT 2ͨ�� ��2����ռ���ȼ� ��0����ռ���ȼ� */
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQChannel;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

	/* ʹ��EXIT 3ͨ�� ��2����ռ���ȼ� ��0����ռ���ȼ� */
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQChannel;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);


}

	EXTI_ClearFlag(EXTI_Line0);	 //��ֹ��ʼ���Ͳ����ж�
	EXTI_ClearFlag(EXTI_Line1);	 //��ֹ��ʼ���Ͳ����ж�
	EXTI_ClearFlag(EXTI_Line2);	 //��ֹ��ʼ���Ͳ����ж�
	EXTI_ClearFlag(EXTI_Line3);	 //��ֹ��ʼ���Ͳ����ж�


	
}

//void EXTI0_IRQHandler(void)
//{	
////	EXTI_GenerateSWInterrupt(EXTI_Line1);
//	extern u8 state,begin;
//	if(state==0)
//	{TIM_Cmd(TIM3, ENABLE);state=1;begin=1;} 		             //TIM1�ܿ��أ�����
//	else
//	{TIM_Cmd(TIM3, DISABLE);state=0;} 		             //TIM1�ܿ��أ�����
//	
//	printf("\r\nEXIT0 IRQHandler return.\r\n");
//	
//	EXTI_ClearFlag(EXTI_Line0);
//}




