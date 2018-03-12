#include "nvic.h"

/***										***/
/************���ļ����ڹ����ж�����************/
/***	  �뽫�����ж��������������˴�		***/

void NVIC_Config(void)
{	
	NVIC_InitTypeDef NVIC_InitStructure; 	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
//====================================����USART1�����ж�======================================//
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
//====================================����DMA�����ж�======================================//
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
//====================================����CAN�����ж�======================================//
  /* Enable CAN1 RX0 interrupt IRQ channel */
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
//====================================���� ���Ź� �ж�======================================//	
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;    //WWDG�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);
//====================================���� PWM �ж�======================================//	
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�2��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
		NVIC_Init(&NVIC_InitStructure); 
//====================================���� CAPTURE �ж�======================================//	
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�2��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�0��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
		NVIC_Init(&NVIC_InitStructure);
//====================================����  DMA1 �ж�======================================//	
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�2��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�0��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
		NVIC_Init(&NVIC_InitStructure);
#ifdef STM32F10X_HD
//====================================����  DMA2 �ж�======================================//
		NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel4_5_IRQn;  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�2��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�0��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
		NVIC_Init(&NVIC_InitStructure);
//====================================����  SDIO �ж�======================================//	
		NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
#endif
}
