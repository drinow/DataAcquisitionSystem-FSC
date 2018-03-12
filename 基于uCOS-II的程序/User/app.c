/*
*********************************************************************************************************
*	                                  
*	ģ������ : uCOS-II
*	�ļ����� : app.c
*	��    �� : V1.0
*	Copyright (C), 2015-2020, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/
//SD����GPS����������������¼����궨���ڴ����
//OS_TASK_TMR_STK_SIZE 
//OS_CPU_EXCEPT_STK_SIZE
//APP_TASK_GPS_DEAL_STK_SIZE

#define  APP_TASK_START_STK_SIZE               256
#define  APP_TASK_CAP_DEAL_STK_SIZE						 256
#define  APP_TASK_CAN_DEAL_STK_SIZE						 256
#define  APP_TASK_ATT_DEAL_STK_SIZE						 256
#define  APP_TASK_GPS_DEAL_STK_SIZE						 512
//#define  OS_CPU_EXCEPT_STK_SIZE              512     

/*
********************************************************************************************************
*                              �����ջ
********************************************************************************************************
*/

/* ����ÿ������Ķ�ջ�ռ䣬app_cfg.h�ļ��к궨��ջ��С */
static OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];
static OS_STK AppTaskCapDealStk[APP_TASK_CAP_DEAL_STK_SIZE];
static OS_STK AppTaskCanDealStk[APP_TASK_CAN_DEAL_STK_SIZE];
static OS_STK AppTaskAttDealStk[APP_TASK_ATT_DEAL_STK_SIZE];
static OS_STK AppTaskGPSDealStk[APP_TASK_GPS_DEAL_STK_SIZE];
/*
*******************************************************************************************************
*                              ��������
*******************************************************************************************************
*/
static void DispTaskInfo(void);
static void AppTaskCreate(void);
static void AppTaskStart(void *p_arg);
static void App_Printf (CPU_CHAR *format, ...);
static void AppTaskCapDeal(void* pdata);
static void AppTaskCanDeal(void* pdata);
static void AppTaskAttDeal(void* pdata);
static void AppTaskGPSDeal(void* pdata);
static void LEDCallback(void *ptmr, void *callback_arg);
static void SENDCallback(void *ptmr, void *callback_arg);
static void FILECallback(void *ptmr, void *callback_arg);
static void TEST(void);
u8 DectoBCD(u8 temp);
u8  BCDtoDec(u8 temp);  
void Protection(void);
void FileDataPreDeal(u8 * str,u8 type);

/*
*******************************************************************************************************
*                               ����
*******************************************************************************************************
*/

/* ����һ�����䣬 ��ֻ��һ������ָ�룬 OSMboxCreate�����ᴴ������������Դ */
static OS_EVENT *AppUserIFMbox;

/*����һ���ź���*/
static OS_EVENT *AppPrintfSemp;

u8 RTCDate[6]={0,0,0,0,0,0};
struct Limit Licence={0,1,1,0};
u32 CAPTURE_Buff[4]={0,0,0,0};
u16 RPM,EngineTemperature,BattVoltage,Gear,ThrottlePosition,SpeedA,SpeedB,SpeedC,SpeedD,Lambda1;
u8 String[55];
/*
*******************************************************************************************************
*	�� �� ��: main
*	����˵��: ��׼c������ڡ�
*	��    ��: ��
*	�� �� ֵ: ��
*******************************************************************************************************
*/
int main(void)
{
	INT8U  err;

	/* ��ʼ��"uC/OS-II"�ں� */
	OSInit();
  
	/* ����һ����������Ҳ���������񣩡���������ᴴ�����е�Ӧ�ó������� */
	OSTaskCreateExt(AppTaskStart,	/* ����������ָ�� */
                    (void *)0,		/* ���ݸ�����Ĳ��� */
                    (OS_STK *)&AppTaskStartStk[APP_TASK_START_STK_SIZE-1], /* ָ������ջջ����ָ�� */
                    APP_TASK_START_PRIO,	/* ��������ȼ�������Ψһ������Խ�����ȼ�Խ�� */
                    APP_TASK_START_PRIO,	/* ����ID��һ����������ȼ���ͬ */
                    (OS_STK *)&AppTaskStartStk[0],/* ָ������ջջ�׵�ָ�롣OS_STK_GROWTH ������ջ�������� */
                    APP_TASK_START_STK_SIZE, /* ����ջ��С */
                    (void *)0,	/* һ���û��ڴ�����ָ�룬����������ƿ�TCB����չ����
                       ���������л�ʱ����CPU����Ĵ��������ݣ���һ�㲻�ã���0���� */
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR); /* ����ѡ���� */
					
					/*  �������£�
						OS_TASK_OPT_STK_CHK      ʹ�ܼ������ջ��ͳ������ջ���õĺ�δ�õ�
						OS_TASK_OPT_STK_CLR      �ڴ�������ʱ����������ջ
						OS_TASK_OPT_SAVE_FP      ���CPU�и���Ĵ��������������л�ʱ���渡��Ĵ���������
					*/                  

	/* ָ����������ƣ����ڵ��ԡ���������ǿ�ѡ�� */
	OSTaskNameSet(APP_TASK_START_PRIO, APP_TASK_START_NAME, &err);
	
	/*ucosII�Ľ��ļ�������0    ���ļ�������0-4294967295*/ 
	OSTimeSet(0);	
	
	/* ����������ϵͳ������Ȩ����uC/OS-II */
	OSStart();
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskStart
*	����˵��: ����һ�����������ڶ�����ϵͳ�����󣬱����ʼ���δ������(��BSP_Init��ʵ��)
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 0
*********************************************************************************************************
*/
static void AppTaskStart(void *p_arg)
{
    /* �����ڱ���������澯����������������κ�Ŀ����� */	
    (void)p_arg;  
	
	 
	/* BSP ��ʼ���� BSP = Board Support Package �弶֧�ְ����������Ϊ�ײ�������*/
	bsp_Init();
    CPU_Init();          
	BSP_Tick_Init();   
	

	/* ���CPU������ͳ��ģ���ʼ�����ú�����������CPUռ���� */
	#if (OS_TASK_STAT_EN > 0)
		OSStatInit();
	#endif	
		
	/* ����Ӧ�ó�������� */
	AppTaskCreate();
	
	/* �������壬������һ����ѭ�� */
	while (1)     
	{ 
		OSTimeDlyHMSM(0, 0, 0, 500);										
	}      
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskCreate
*	����˵��: ����Ӧ������
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
	INT8U      err;
	static OS_TMR  *Tmr;

	/* ����CapDeal���� */
	OSTaskCreateExt(AppTaskCapDeal,
                    (void *)0,
                    (OS_STK *)&AppTaskCapDealStk[APP_TASK_CAP_DEAL_STK_SIZE - 1],
                    APP_TASK_CAP_DEAL_PRIO,
                    APP_TASK_CAP_DEAL_PRIO,
                    (OS_STK *)&AppTaskCapDealStk[0],
                    APP_TASK_CAP_DEAL_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

	OSTaskNameSet(APP_TASK_CAP_DEAL_PRIO, APP_TASK_CAP_DEAL_NAME, &err);

/* ����CanDeal���� */
	OSTaskCreateExt(AppTaskCanDeal,
                    (void *)0,
                    (OS_STK *)&AppTaskCanDealStk[APP_TASK_CAN_DEAL_STK_SIZE - 1],
                    APP_TASK_CAN_DEAL_PRIO,
                    APP_TASK_CAN_DEAL_PRIO,
                    (OS_STK *)&AppTaskCanDealStk[0],
                    APP_TASK_CAN_DEAL_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

	OSTaskNameSet(APP_TASK_CAN_DEAL_PRIO, APP_TASK_CAN_DEAL_NAME, &err);
	
	/* ����AttDeal���� */
	OSTaskCreateExt(AppTaskAttDeal,
                    (void *)0,
                    (OS_STK *)&AppTaskAttDealStk[APP_TASK_ATT_DEAL_STK_SIZE - 1],
                    APP_TASK_ATT_DEAL_PRIO,
                    APP_TASK_ATT_DEAL_PRIO,
                    (OS_STK *)&AppTaskAttDealStk[0],
                    APP_TASK_ATT_DEAL_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

	OSTaskNameSet(APP_TASK_ATT_DEAL_PRIO, APP_TASK_ATT_DEAL_NAME, &err);
	
	/* ����GPSDeal���� */
	OSTaskCreateExt(AppTaskGPSDeal,
                    (void *)0,
                    (OS_STK *)&AppTaskGPSDealStk[APP_TASK_GPS_DEAL_STK_SIZE - 1],
                    APP_TASK_GPS_DEAL_PRIO,
                    APP_TASK_GPS_DEAL_PRIO,
                    (OS_STK *)&AppTaskGPSDealStk[0],
                    APP_TASK_GPS_DEAL_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

	OSTaskNameSet(APP_TASK_GPS_DEAL_PRIO, APP_TASK_GPS_DEAL_NAME, &err);
	
	/* ����һ��NRF��ʱ������*/
	Tmr = OSTmrCreate(1, //��ʼ�ӳ�ʱ�� 1*(1000/OS_TMR_CFG_TICKS_PER_SEC)msִ��һ��
										1, //����		
										OS_TMR_OPT_PERIODIC, 
										SENDCallback,
										(void *)0,
										"nrftmr",
										&err);
	
	if (err == OS_ERR_NONE) 
	{
		OSTmrStart(Tmr, &err);
	}
	
	/* ����һ��FILE��ʱ������*/
	Tmr = OSTmrCreate(1, //��ʼ�ӳ�ʱ�� 1*(1000/OS_TMR_CFG_TICKS_PER_SEC)msִ��һ��
										1, //����		
										OS_TMR_OPT_PERIODIC, 
										FILECallback,
										(void *)0,
										"filetmr",
										&err);
	
	if (err == OS_ERR_NONE) 
	{
		OSTmrStart(Tmr, &err);
	}

	/* ����һ��LED��ʱ������*/
	Tmr = OSTmrCreate(1, //��ʼ�ӳ�ʱ�� 2*(1000/OS_TMR_CFG_TICKS_PER_SEC)msִ��һ��
										2, //����		
										OS_TMR_OPT_PERIODIC, 
										LEDCallback,
										(void *)0,
										"ledtmr",
										&err);
	
	if (err == OS_ERR_NONE) 
	{
		OSTmrStart(Tmr, &err);
	}
	
}

void AppTaskCapDeal(void* pdata)
{
	
	while(1)
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
			TIM4CH4_CAPTURE_STA=0;      //������һ�β���
		}
		/* �ӳ�5ms�������ͷ�CPU����������ȼ���������� */  
		OSTimeDlyHMSM(0, 0, 0, 5);
	}
	
}

static void AppTaskCanDeal(void* pdata)
{
	while(1)
	{
		if( CanFlag == ENABLE ) //�յ�һ֡��ȷ�����ݣ�����ӡ������
	  {
      CanFlag = DISABLE;
      if(MotecCache[0]==0X82)//����֤
				if(MotecCache[1]==0X81)
					if(MotecCache[2]==0X80)
					{
						CAN_ITConfig(CAN1,CAN_IT_FMP0, DISABLE);
						
						RPM=(MotecCache[4]<<8)|MotecCache[5];
						Lambda1=(MotecCache[14]<<8)|MotecCache[15];
						ThrottlePosition=(MotecCache[6]<<8)|MotecCache[7];
						EngineTemperature=(MotecCache[12]<<8)|MotecCache[13];
						BattVoltage=(MotecCache[48]<<8)|MotecCache[49];
						//Gear=(MotecCache[116]<<8)|MotecCache[117];
						SpeedA=(MotecCache[52]<<8)|MotecCache[53];
						SpeedB=(MotecCache[54]<<8)|MotecCache[55];
						SpeedC=(MotecCache[56]<<8)|MotecCache[57];
						SpeedD=(MotecCache[58]<<8)|MotecCache[59];
						
						MotecCnt=0;
						MotecFlag=0;
						CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);
					}
	  }
		/*�ӳ�5ms�������ͷ�CPU����������ȼ���������� */
		OSTimeDlyHMSM(0, 0, 0, 5);
	}
}

static void AppTaskAttDeal(void* pdata)
{
	while(1)
	{
		dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more);	//��ȡ������̬������
		if(sensors&INV_WXYZ_QUAT)//��ʱͦ�������Է�������
		{
			q0=quat[0] / q30;
			q1=quat[1] / q30;
			q2=quat[2] / q30;
			q3=quat[3] / q30;
			Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; // 
			Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3;
			Yaw = 	atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;		//�о�û�м�ֵ��ע��
		}
		/*�ӳ�5ms�������ͷ�CPU����������ȼ���������� */
		OSTimeDlyHMSM(0, 0, 0, 5);
	}
}
static void AppTaskGPSDeal(void* pdata)
{
	while(1)
	{
		//GPS������
//		nmea_decode_test();
		/*�ӳ�5ms�������ͷ�CPU����������ȼ���������� */
		OSTimeDlyHMSM(0, 0, 0, 5);
	}
}
static void  FILECallback(void *ptmr, void *callback_arg)
{
	if(OpenFileSave)
	 {
		 static u8 FileCnt=0;
		 FileCnt++;
		 FileDataPreDeal(String,FileCnt);
		 switch(FileCnt)
		 {
			case 1: WriteSomething(DirStringE,"Motec.txt"  ,(u8 *)String,sizeof(String)); break;
			case 2: WriteSomething(DirStringE,"ADC.txt"    ,(u8 *)String,sizeof(String)); break;
			case 3: WriteSomething(DirStringE,"MPU6050.txt",(u8 *)String,sizeof(String)); break;
			default: FileCnt=0;break;
		 }
	 }
}
static void  SENDCallback(void *ptmr, void *callback_arg)
{
	//SendDATA();
}
static void  LEDCallback(void *ptmr, void *callback_arg)
{
	Protection();
	LED_STATE_Fun();
	TEST();
}

/*
*********************************************************************************************************
*	�� �� ��: App_Printf
*	����˵��: �̰߳�ȫ��printf��ʽ		  			  
*	��    ��: ͬprintf�Ĳ�����
*             ��C�У����޷��г����ݺ���������ʵ�ε����ͺ���Ŀʱ,������ʡ�Ժ�ָ��������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void  App_Printf (CPU_CHAR *format, ...)
{
    CPU_CHAR  buf_str[80 + 1];
    va_list   v_args;
    CPU_INT08U  os_err;


    va_start(v_args, format);
   (void)vsnprintf((char       *)&buf_str[0],
                   (size_t      ) sizeof(buf_str),
                   (char const *) format,
                                  v_args);
    va_end(v_args);

    OSSemPend((OS_EVENT  *)AppPrintfSemp,
              (INT32U     )0,
              (INT8U     *)&os_err);

    printf("%s", buf_str);

    os_err = OSSemPost((OS_EVENT *)AppPrintfSemp);
}

//LED2������ʾϵͳ��������
//LED2������ʾϵͳ���ƹ���
//LED2������ʾϵͳֹͣ����
void Protection(void)
{
	static u16 cnt=0;
	cnt++;
	if(cnt%100==0)//ÿ��
	{
		//2016.10.8��ǰ��������Ȩ��
		if(  (GPSTime.year==2016&&GPSTime.mon<=10  &&GPSTime.day<8)
			 ||(RTCDate[0]	==0x16&&RTCDate[1] <=0x10&&RTCDate[2]<0x08)	)
		{	Licence.TimeLimit=0;Licence.RunTime=0;Licence.STOP=0;}
		//�������������������Ȩ�ޣ���Ҫ����4������
		if((GPS_num>4)&&(GPS_lon<110||GPS_lon>114||GPS_lat<30||GPS_lat>33))
		{	Licence.LocationLimit=0;Licence.RunTime=0;Licence.STOP=0;}
		
		//����������Ȩ�ޣ����������ݲ���ʾ
		if(Licence.STOP==0&&(Licence.LocationLimit||Licence.TimeLimit))
		{
			//����ʱ�����
			Licence.RunTime++;
			LED_STATE(LED2,SLOWFLICKER);
		}
		else
			LED_STATE(LED2,BREATH);
		
		//ÿ10s�洢һ��RunTime��RTC
		if(cnt%1000==0)
		{
			STMFLASH_Write(FLASH_SAVE_ADDR,&Licence.RunTime,sizeof(Licence.RunTime));
			//���GPS�����������ʱ����RTC
			if(Licence.LocationLimit==0)
			{
				RTCDate[0]=DectoBCD(GPSTime.year);
				RTCDate[1]=DectoBCD(GPSTime.mon);
				RTCDate[2]=DectoBCD(GPSTime.day);
				RTCDate[3]=DectoBCD(GPSTime.hour);
				RTCDate[4]=DectoBCD(GPSTime.min);
				RTCDate[5]=DectoBCD(GPSTime.sec);
				WriteDS1302Clock(RTCDate);
			}
			//����������
			cnt=0;
		}
		
		//1800s������ֹȨ�ޣ����������ݲ���ʾ����λά����1������Ļ��ʾδ��Ȩ
		if(Licence.RunTime>1800&&Licence.RunTime<65535)
		{	Licence.STOP =1;LED_STATE(LED2,FASTFLICKER); }
	}
}

//�ļ�����Ԥ������
void FileDataPreDeal(u8 * str,u8 type)
{
	memset(str,'\0',55);
	switch(type)
	{
	case 1:sprintf((char*)str,  "%4d %4d %4d %4d %4d %5.1f %5.1f\r\n",RPM,SpeedA,SpeedB,SpeedC,SpeedD,(float)ThrottlePosition/10,(float)BattVoltage/100);
		break;
  case 2:sprintf((char*)str, "%4d %4d %4d %4d\r\n",ADCBuff[0],ADCBuff[1],ADCBuff[2],ADCBuff[3]);
		break;
	case 3:sprintf((char*)str,"%5d %5d %5d | %5d %5d %5d | %4.1f %4.1f\r\n",accel[0],accel[1],accel[2],gyro[0],gyro[1],gyro[2],Pitch*100,Roll*100);
		break;
	default:break;
	}
}

u8  BCDtoDec(u8 temp)  
{  
	return ((temp/16)*10+temp%16);  
}  

u8 DectoBCD(u8 temp)  
{  
	return ((temp/10)*16+temp%10);  
}

/*
*********************************************************************************************************
*	�� �� ��: DispTaskInfo
*	����˵��: ��uCOS-II������Ϣ��ӡ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void DispTaskInfo(void)
{
	OS_TCB      *ptcb;	        /* ����һ��������ƿ�ָ��, TCB = TASK CONTROL BLOCK */
	OS_STK_DATA stk;	        /* ���ڶ�ȡ����ջʹ����� */

	ptcb    = &OSTCBTbl[0];		/* ָ���1��������ƿ�(TCB) */

	/* ��ӡ���� */
	App_Printf("==================================================\r\n");
	App_Printf("  ���ȼ�   ʹ��ջ  ʣ��ջ  �ٷֱ�   ������\r\n");
	App_Printf("  Prio     Used    Free    Per      Taskname\r\n");

	OSTimeDly(10);
	
	/* ����������ƿ��б�(TCB list)����ӡ���е���������ȼ������� */
	while (ptcb != NULL)
	{
		/* 
			ptcb->OSTCBPrio : ������ƿ��б������������ȼ�
			ptcb->OSTCBTaskName : ������ƿ��б�����������ƣ���Ҫ�ڴ��������ʱ��
			����OSTaskNameSet()ָ���������ƣ����磺
			OSTaskNameSet(APP_TASK_USER_IF_PRIO, "User I/F", &err);
		*/
		OSTaskStkChk(ptcb->OSTCBPrio, &stk);	/* �������ջ���ÿռ� */
		App_Printf("   %2d    %5d    %5d    %02d%%     %s\r\n", ptcb->OSTCBPrio, 
			stk.OSUsed, stk.OSFree, (stk.OSUsed * 100) / (stk.OSUsed + stk.OSFree),
			ptcb->OSTCBTaskName);		
		ptcb = ptcb->OSTCBPrev;		            /* ָ����һ��������ƿ� */
	}
    printf("Tick Rate : %d  \r\n",OS_TICKS_PER_SEC);//����Ƶ��
    printf("CPU  Usage: %d% \r\n",OSCPUUsage);//CPUʹ����
}

static void TEST(void)
{
	static u16 cnt=0;
	cnt++;
	if(cnt%10==0)
	{
//	printf("ADC:\r\n");
//	printf("A4:%4d A5:%4d A6:%4d A7:%4d\r\n",ADCBuff[0],ADCBuff[1],ADCBuff[2],ADCBuff[3]);
//	printf("C0:%4d C1:%4d C2:%4d C3:%4d C4:%4d C5:%4d\r\n",ADCBuff[4],ADCBuff[5],ADCBuff[6],ADCBuff[7],ADCBuff[8],ADCBuff[9]);
//	printf("\r\n");

	printf("CAPTURE\r\n");
	printf("B6:%d B7:%d B8:%d B9:%d\r\n",CAPTURE_Buff[0],CAPTURE_Buff[1],CAPTURE_Buff[2],CAPTURE_Buff[3]);
	printf("\r\n");
	}
	if(cnt%100==0)
	{
		DispTaskInfo();	
		if(Licence.RunTime!=0)
		{	printf("����ʱ�䣺%d\r\n",Licence.RunTime);
			if(Licence.LocationLimit)	printf("�ص���Ϣȱʧ\r\n");
			if(Licence.TimeLimit)		printf("ʱ����Ϣȱʧ\r\n");
		}
	  else if(Licence.STOP)			printf("ϵͳֹͣ����\r\n");
	}
}
/***************************** ���������� www.armfly.com (END OF FILE) *********************************/

