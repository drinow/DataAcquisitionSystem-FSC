#include "led.h"
#define TIM_PULSE_MAX 999
void PWM_LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE); 
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE); 
	
	//C6-CH1-LED2;C7-CH2-LED1
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = TIM_PULSE_MAX; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =0; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//CH1 LED2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	//CH2 LED1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
}


u8 BreathOrFlash_LED1=0;
u8 BreathOrFlash_LED2=0;
void PWM_LED_STATE(u8 num,u8 state)
{
	if(num==LED1)//LED1
	{
		switch(state)
		{
			case OFF:TIM3->CCR2=TIM_PULSE_MAX;BreathOrFlash_LED1=NORMAL;break;
			case ON:TIM3->CCR2=0;						BreathOrFlash_LED1=NORMAL;break;
			case BREATH:										BreathOrFlash_LED1=BREATH;break;//����
			case FASTFLICKER:								BreathOrFlash_LED1=FASTFLICKER;break;//��˸
			case MEDIFLICKER:								BreathOrFlash_LED1=MEDIFLICKER;break;
			case SLOWFLICKER:								BreathOrFlash_LED1=SLOWFLICKER;break;
		}
	}
	if(num==LED2)
	{
		switch(state)
		{
			case OFF:TIM3->CCR1=TIM_PULSE_MAX;BreathOrFlash_LED2=NORMAL;break;
			case ON:TIM3->CCR1=0;							BreathOrFlash_LED2=NORMAL;break;
			case BREATH:											BreathOrFlash_LED2=BREATH;break;
			case FASTFLICKER:								BreathOrFlash_LED2=FASTFLICKER;break;//��˸
			case MEDIFLICKER:								BreathOrFlash_LED2=MEDIFLICKER;break;
			case SLOWFLICKER:								BreathOrFlash_LED2=SLOWFLICKER;break;
		}
	}
}

//extern u32 SysCnt;
void LED_STATE_Fun(void)
{
	s16 temp1=0,temp2=0;
	static u8 state1=0;
	static u8 state2=0;
	static u16 cnt1=0;
	static u16 cnt2=0;
	//����
		if(BreathOrFlash_LED1==BREATH)
		{
			temp1=TIM3->CCR2;
			
			if(state1)temp1--;
			else temp1++;
			if(temp1>TIM_PULSE_MAX){state1=~state1;temp1=TIM_PULSE_MAX;}
			if(temp1<0){state1=~state1;temp1=0;}
			TIM3->CCR2=temp1;
		}
		if(BreathOrFlash_LED2==BREATH)
		{
			temp2=TIM3->CCR1;
			
			if(state2)temp2--;
			else temp2++;
			if(temp2>TIM_PULSE_MAX){state2=~state2;temp2=TIM_PULSE_MAX;}
			if(temp2<0){state2=~state2;temp2=0;}	
			TIM3->CCR1=temp2;
		}
		//��˸
		if(BreathOrFlash_LED1==FASTFLICKER)
		{
			cnt1++;
			if(cnt1<100)
				TIM3->CCR2=0;
			else if(cnt1>100)TIM3->CCR2=TIM_PULSE_MAX;
			if(cnt1==200)cnt1=0;
		}
		if(BreathOrFlash_LED2==FASTFLICKER)
		{
			cnt2++;
			if(cnt2<100)
				TIM3->CCR1=0;
			else if(cnt2>100)TIM3->CCR1=TIM_PULSE_MAX;
			if(cnt2==200)cnt2=0;
		}
		//����
		if(BreathOrFlash_LED1==MEDIFLICKER)
		{
			cnt1++;
			if(cnt1<200)
				TIM3->CCR2=0;
			else if(cnt1>200)TIM3->CCR2=TIM_PULSE_MAX;
			if(cnt1==400)cnt1=0;
		}
		if(BreathOrFlash_LED2==MEDIFLICKER)
		{
			cnt2++;
			if(cnt2<200)
				TIM3->CCR1=0;
			else if(cnt2>200)TIM3->CCR1=TIM_PULSE_MAX;
			if(cnt2==400)cnt2=0;
		}
		//����
		if(BreathOrFlash_LED1==SLOWFLICKER)
		{
			cnt1++;
			if(cnt1<500)
				TIM3->CCR2=0;
			else if(cnt1>500)TIM3->CCR2=TIM_PULSE_MAX;
			if(cnt1==1000)cnt1=0;
		}
		if(BreathOrFlash_LED2==SLOWFLICKER)
		{
			cnt2++;
			if(cnt2<500)
				TIM3->CCR1=0;
			else if(cnt2>500)TIM3->CCR1=TIM_PULSE_MAX;
			if(cnt2==1000)cnt2=0;
		}
}
