#include "key.h"

void KeyInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
	
	//��������
  GPIO_InitStructure.GPIO_Pin  = (GPIO_Pin_6|GPIO_Pin_7);				 					 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	//DRS����(D6)+Ԥ������
	GPIO_InitStructure.GPIO_Pin  = (GPIO_Pin_6|GPIO_Pin_7);				 					 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
  GPIO_Init(GPIOD, &GPIO_InitStructure);			
	
}
	//
	//KeyValueֵ����
	//0x01=0000 0001 ��������
	//0x02=0000 0010 ��������
	//0x04=0000 0100 DRS��
	//0x08=0000 1000 Ԥ������
	//0xFF=1111 1111 ���±�־λ
	u8 KeyValue=0;
u8 Key_Scan(void)          //�ú������������жϺ���
{	
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)==0)//��������
//	{
//		key_delay_ms(5);
//		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)==0)
//		{
//			while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)==0);
//			Shifting(UP);
//			//KeyValue=KeyValue|0x01;
//		}
//	}
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)==0)//�������� 
//	{
//		key_delay_ms(5);
//		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)==0)
//		{
//			while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)==0);
//			Shifting(DOWN);
//			//KeyValue=KeyValue|0x02;
//		}
//	}
//	//if(KeyValue==0xC0);
//	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)==0)//DRS����
//	{
//		key_delay_ms(5);
//		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)==0)
//		{
//			while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)==0);
//			//KeyValue=KeyValue|0x04;
//		}
//	}
//	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)==0)//Ԥ������
//	{
//		key_delay_ms(5);
//		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)==0)
//		{
//			while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)==0);
//			//KeyValue=KeyValue|0x08;
//		}
//	}
//	return(KeyValue);             //���ؼ�ֵ

	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)==0)//��������
	{
		if(KeyValue==0)			//������ν�������
		{	KeyValue=KeyValue|0xFF;	return KeyValue;}
		else if(KeyValue==0xFF)
		{	KeyValue=0x01;return KeyValue;}
	}
	else if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)==0)//��������
	{
		if(KeyValue==0)
		{	KeyValue=KeyValue|0xFF;	return KeyValue;}
		else if(KeyValue==0xFF)
		{	KeyValue=0x02;return KeyValue;}
	}
	//if(KeyValue==0xC0);
	else if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)==0)//DRS
	{
		if(KeyValue==0)
		{	KeyValue=KeyValue|0xFF;	return KeyValue;}
		else if(KeyValue==0xFF)
		{	KeyValue=0x04;return KeyValue;}
	}
	else if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)==0)//Ԥ������
	{
		if(KeyValue==0)
		{	KeyValue=KeyValue|0xFF;	return KeyValue;}
		else if(KeyValue==0xFF)
		{	KeyValue=0x08;return KeyValue;}
	}
	else KeyValue=0;
	
	return(KeyValue);             //���ؼ�ֵ
}

void Key_Deal(void)
{
	if(KeyValue==0x01)
	{KeyValue=0;}
	if(KeyValue==0x02)
	{KeyValue=0;}
	if(KeyValue==0x04)
	{KeyValue=0;}
	if(KeyValue==0x08)
	{KeyValue=0;}
}
void key_delay_ms(vu32 m)
{	 		  	  
	u32 i; 
	for(; m != 0; m--)	
       for (i=0; i<72000; i++);
} 

