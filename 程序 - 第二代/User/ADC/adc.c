#include "adc.h"

/*				���㹫ʽ��
*	 		m1=Average(0)*3.3/4096.0 ;
*   		m2=Average(1)*3.3/4096.0;
*/
u16 volatile ADCSample[1];
u16 volatile ADCBuff[10];

void ADC1_Configuration(void)
{
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO , ENABLE);

		GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
	}

	{	
		ADC_InitTypeDef ADC_InitStructure; 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);//����ADCʱ��
		RCC_ADCCLKConfig(RCC_PCLK2_Div6); //����ADCʱ�� PCLK2��6��Ƶ
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1�����ڶ���ģʽ
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;//������ͨ��ɨ��ģʽ
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//������������ģʽ
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ת��������������ⲿ��������
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ADC�����Ҷ���
		ADC_InitStructure.ADC_NbrOfChannel = 1;//�涨��˳����й���ת����ADCͨ������Ŀ
		ADC_Init(ADC1, &ADC_InitStructure);
	 
	   /* ADC1 ����ת��˳�� */ 
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5);
//		ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_55Cycles5);
//		ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_55Cycles5);
//		ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_55Cycles5);
		
	   ADC_DMACmd(ADC1, ENABLE);//����DMA����
	   ADC_Cmd(ADC1, ENABLE);//����ADC1
	   ADC_ResetCalibration(ADC1);//У׼ADC1
	   while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�У׼���
	 
	   /* Start ADC1 calibration */
	   ADC_StartCalibration(ADC1);
	   /* Check the end of ADC1 calibration */
	   while(ADC_GetCalibrationStatus(ADC1));
	      
	   /* Start ADC1 Software Conversion */ 
	   ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ʹ�ܻ���ʧ��ָ����ADC�����ת����������
   }
}
void DMA1_Configuration(void)
{
   DMA_InitTypeDef DMA_InitStructure;
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//ʹ�ܻ���ʧ��AHB����ʱ��

   DMA_DeInit(DMA1_Channel1);//��DMA��ͨ��x�Ĵ�������Ϊȱʡֵ
   DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;//����DMA�������ַ
   DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADCSample;//����DMA�ڴ����ַ �ŵ�������
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//�涨����������Ϊ���ݴ����Ŀ�ĵػ�����Դ������ڴ���Ϊ��Դ�����ڴ����
   DMA_InitStructure.DMA_BufferSize = 1*2;	//ͨ����*������*�ֽ�
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�Ĵ�������
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�ڴ��ַ�Ĵ�������
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord ;//�������ݿ��Ϊ16λ
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord ;//�ڴ����ݿ��Ϊ16λ
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ѭ������
   DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMAͨ��xӵ�и����ȼ�
   DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫�� 
   DMA_Init(DMA1_Channel1, &DMA_InitStructure);//����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��x�Ĵ���
   
   /* Enable DMA1 channel1 */
   DMA_Cmd(DMA1_Channel1, ENABLE);
   DMA_ClearFlag(DMA1_FLAG_TC1);
   DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);//ʹ�ܻ���ʧ��ָ����ͨ��x�ж�
}

void DMA1_ADC1_Init(void)
{
	DMA1_Configuration();
	ADC1_Configuration();
}

void DMA1_Channel1_IRQHandler(void)
{
	DMA_ClearITPendingBit(DMA1_IT_TC1);
}

