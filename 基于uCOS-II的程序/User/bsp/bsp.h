/*
*********************************************************************************************************
*
*	ģ������ : BSPģ��
*	�ļ����� : bsp.h
*	˵    �� : ���ǵײ�����ģ�����е�h�ļ��Ļ����ļ��� Ӧ�ó���ֻ�� #include bsp.h ���ɣ�
*			  ����Ҫ#include ÿ��ģ��� h �ļ�
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#ifndef _BSP_H_
#define _BSP_H

#define STM32_V4
//#define STM32_X2

/* ����Ƿ����˿������ͺ� */
#if !defined (STM32_V4) && !defined (STM32_X2)
	#error "Please define the board model : STM32_X2 or STM32_V4"
#endif

/* ���� BSP �汾�� */
#define __STM32F1_BSP_VERSION		"1.1"

/* CPU����ʱִ�еĺ��� */
//#define CPU_IDLE()		bsp_Idle()

/* ʹ����Դ�ļ���ʹ��uCOS-II�ĺ���, �����Դ�ļ���Ҫ��ָBSP�����ļ� */
#define uCOS_EN       1

#if uCOS_EN == 1    
	#include "ucos_ii.h"   

	#define  ENABLE_INT()      OS_EXIT_CRITICAL()     /* ʹ��ȫ���ж� */
	#define  DISABLE_INT()     OS_ENTER_CRITICAL()    /* ��ֹȫ���ж� */
#else
	/* ����ȫ���жϵĺ� */
	#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
	#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */
#endif

/* ���������ڵ��Խ׶��Ŵ� */
#define BSP_Printf		printf
//#define BSP_Printf(...)

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

/*
	EXTI9_5_IRQHandler ���жϷ�������ɢ�ڼ��������� bsp�ļ��С�
	��Ҫ���ϵ� stm32f4xx_it.c �С�

	���������б�ʾEXTI9_5_IRQHandler��ں������зŵ� stm32f4xx_it.c��
*/
#define EXTI9_5_ISR_MOVE_OUT

#define DEBUG_GPS_TO_COM1	/* ��ӡGPS���ݵ�����1 */

/* ͨ��ȡ��ע�ͻ������ע�͵ķ�ʽ�����Ƿ�����ײ�����ģ�� */

//#include "bsp_timer.h"

//#include "bsp_msg.h"
#include "nvic.h"
#include "stm32f10x.h"
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

/* �ṩ������C�ļ����õĺ��� */
void bsp_Init(void);
void bsp_Idle(void);
void BSP_Tick_Init (void);

#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
