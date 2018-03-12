#include "includes.h"

//JTAG����ģʽ
//mode:jtag,swd  0��ȫʹ�ܣ�1��ʹ��SWD��2��ȫ�ر� 	  
void JTAG_Set(u8 mode)
{
	u32 temp;

	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //��������ʱ��	   
	AFIO->MAPR&=0XF8FFFFFF; //���MAPR��[26:24]
	AFIO->MAPR|=temp;       //����jtagģʽ
}

//�Լ����
u8 RC_NRF=0;
void SelfTest(void)
{
	u8 status;
	//���ڲ���
	printf("\r\n���ڲ���\r\n");
	//����ģ���Լ�
	status = NRF_Check(); 
 if(status == SUCCESS)	   
 {
	 NRF_TX_Mode();
	 printf("\r\nNRF��MCU���ӳɹ���\r\n\r\n");
	 RC_NRF = 1;
 }
 else
 {		 
		RC_NRF = 0;
		printf("\r\nNRF����ʧ�ܣ���\r\n");
 }
	printf("\r\n");
}

extern u8 RTCDate[6];
void Init(void)//��ģ���ʼ������
{
	JTAG_Set(1);

	USART1_Config();//ok
	CAN_Config();//work
	
	DS1302_Configuration();//work
	ReadDS1302Clock(RTCDate);
	
	STMFLASH_Read (FLASH_SAVE_ADDR,&Licence.RunTime,sizeof(Licence.RunTime));//ok
	ANBT_I2C_Configuration();//work
	AnBT_DMP_MPU6050_Init();
	SPI_NRF_Init();//work
	DMA1_ADC1_Init();//ok
	PWM_TIM2_Config();//ok
	LED_TIM3_Init();//ok
	LED_STATE(LED1,BREATH);//LED1�����ں���ģʽ
	LED_STATE(LED2,FASTFLICKER);//LED2�����ڿ���ģʽ
	TIM4_Cap_Init(0xFFFF,71);//ok
	//WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);//������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ8	   

	SelfTest();//�Լ�
	
	//�Ǵ�����оƬ�������溯���ᵼ�¶�ջ���
#if 0
	SD_UserInit();
	GPS_Config();
#endif
}

//end of file
