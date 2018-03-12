/*
*********************************************************************************************************
*
*	ģ������ : ͷ�ļ�����
*	�ļ����� : includes.h
*	��    �� : V1.0
*	˵    �� : ��ǰʹ��ͷ�ļ�����
*
*	�޸ļ�¼ :
*		�汾��    ����        ����     ˵��
*		V1.0    2015-08-02  Eric2013   �״η���
*
*	Copyright (C), 2015-2020, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__
/*
*********************************************************************************************************
*                                         ��׼��
*********************************************************************************************************
*/

#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>


/*
*********************************************************************************************************
*                                         ������
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_ascii.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <lib_str.h>
#include  <app_cfg.h>


/*
*********************************************************************************************************
*                                           OS
*********************************************************************************************************
*/

#include  <ucos_ii.h>


/*
*********************************************************************************************************
*                                           �궨��
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                        APP / BSP
*********************************************************************************************************
*/

#include  <bsp.h>

/*
*********************************************************************************************************
*                                         ȫ�ֱ���
*********************************************************************************************************
*/
#define RC_UART 						

//���֤����
struct Limit
{
	u8 STOP;  
	u8 TimeLimit;
	u8 LocationLimit; 
	u16 RunTime;
};
extern struct Limit Licence;

//GPS����
extern float GPS_Speed,GPS_lat,GPS_lon,GPS_direction,GPS_elvetion;
extern u8 GPS_sta,GPS_num;
extern nmeaTIME GPSTime;

//CAN��������
extern uint8_t CanFlag;
extern u8 MotecCache[176];
extern u8 MotecCnt,MotecFlag;

//��̬����������
#define q30  1073741824.0f
extern long quat[4];//��Ԫ���������
extern float Yaw,Roll,Pitch;//ŷ����
extern float q0,q1,q2,q3;//������̬�����õ��ı���
extern short gyro[3], accel[3], sensors;//�����Ǵ�����飬���ٶȴ�����飬����״̬��
extern unsigned char more;
extern unsigned long sensor_timestamp;

//CAPTURE
extern u8	TIM4CH1_CAPTURE_STA,TIM4CH2_CAPTURE_STA,  //���벶��״̬   
					TIM4CH3_CAPTURE_STA,TIM4CH4_CAPTURE_STA;
					 
extern u16	TIM4CH1_CAPTURE_VAL_A,TIM4CH1_CAPTURE_VAL_B, //���벶��ֵ
						TIM4CH2_CAPTURE_VAL_A,TIM4CH2_CAPTURE_VAL_B,
						TIM4CH3_CAPTURE_VAL_A,TIM4CH3_CAPTURE_VAL_B,	
						TIM4CH4_CAPTURE_VAL_A,TIM4CH4_CAPTURE_VAL_B;	
//���߿���
extern u8 RC_NRF;

//FILE���
extern u8 OpenFileSave;
extern	const char *DirStringE;

//ADC����
extern u16 volatile ADCBuff[10];

//��ģ���ʼ������
void Init(void);
extern int nmea_decode_test(void);
#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
