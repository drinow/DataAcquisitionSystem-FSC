#ifndef __INCLUDES_H
#define __INCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nvic.h"
#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "adc.h"
#include "usart.h"
#include "bsp_spi_nrf.h"
#include "wdg.h"
#include "bsp_pwm_output.h"
#include "TIM_Capture.h"
#include "datatransfer.h"
#include "anbt_dmp_fun.h"
#include "anbt_i2c.h"
#include "anbt_dmp_mpu6050.h"
#include "anbt_dmp_driver.h"
#include "DataCal.h"
#include "can.h"
#include "bsp_sdio_sd.h"  	/* SD������ģ�� */
#include "ff.h"				/* FatFS�ļ�ϵͳģ��*/	
#include "ff_user.h"
#include "gps_config.h"
#include "nmea/nmea.h"
#include "ds1302.h"
#include "stmflash.h"
#include "led.h"

//RC��
//#define RC_UART 								//������رմ��ڷ���

extern volatile float GPS_Speed,GPS_lat,GPS_lon,GPS_direction,GPS_elvetion;
extern volatile u8 GPS_sta,GPS_num;
extern volatile nmeaTIME GPSTime;

extern volatile u32 SysCnt;

extern volatile u8 RC_NRF;

extern short accel[3],gyro[3];
extern u16 volatile ADCBuff[10];

extern volatile uint8_t CanFlag;
extern volatile u8 MotecCache[176];
extern volatile u8 MotecCnt,MotecFlag;

void Init(void);
void SelfTest(void);//�Լ����
extern u8 DectoBCD(u8 temp);  
extern u8 BCDtoDec(u8 temp);

#endif

