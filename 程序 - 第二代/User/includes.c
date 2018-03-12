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

extern 	TIME_TypeDef RTCTime;
void Init(void)//��ģ���ʼ������
{
	JTAG_Set(1);
	//������Ź������ǲ����û��ǵ���ʱ������?
	SysTick_Init();//ֻ�ǳ�ʼ������û��,1ms
	USART1_Config();
	CAN_Config();
	ds1302_init();
	DS1302_ReadTime(&RTCTime);
	STMFLASH_Read (FLASH_SAVE_ADDR,&Licence.RunTime,sizeof(Licence.RunTime));
	ANBT_I2C_Configuration();
	AnBT_DMP_MPU6050_Init();
	SPI_NRF_Init();
  DMA1_ADC1_Init();
  PWM_TIM2_Config();
	PWM_LED_Init();
	PWM_LED_STATE(LED1,BREATH);//LED1����GPS����ָʾ
	PWM_LED_STATE(LED2,BREATH);//LED2����RTC����ָʾ
	TIM4_Cap_Init(0xFFFF,71);
	CD4067Init();
	//WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);//������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ8	   
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;//����SysTick
	
	SelfTest();//�Լ�
	
	//�Ǵ�����оƬ�������溯���ᵼ�¶�ջ���

		SD_UserInit();
	  GPS_Config();

}

//�Լ����
volatile u8 RC_NRF=0;
//u8 TxPack[32]={'n','r','f',' ','d','a','t','a',' ','s','e','n','d',' ','t','e','s','t'};
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
		printf("\r\n  NRF����ʧ�ܣ���\r\n");
 }
	printf("\r\n");
}

//end of file
