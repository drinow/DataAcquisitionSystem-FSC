/**
  ******************************************************************************
  * @file    nmea_decode_test.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����NEMA�����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "stm32f10x.h"
//#include "bsp_sdio_sdcard.h"
#include "includes.h"
#include "ff.h"
#include "nmea/nmea.h"
#include "gps_config.h"

  

#ifdef __GPS_LOG_FILE             //��SD���ϵ�gpslog.txt�ļ����н��룻����Ҫ��sd���ϴ��gpslog.txt�ļ���

FATFS fs;
FIL log_file;
FRESULT res; 
UINT br, bw;            					/* File R/W count */

/**
  * @brief  nmea_decode_test ����GPS�ļ���Ϣ
  * @param  ��
  * @retval ��
  */
void nmea_decode_test(void)
{

    nmeaINFO info;          //GPS�����õ�����Ϣ
    nmeaPARSER parser;      //����ʱʹ�õ����ݽṹ  
    
    nmeaTIME beiJingTime;    //����ʱ�� 

    char buff[2048];
  
    	/* ע���̷� */
		f_mount(0,&fs);	

    /* �򿪼�¼��GPS��Ϣ���ļ� */
    res = f_open(&log_file,"0:gpslog.txt", FA_OPEN_EXISTING|FA_READ);

    if(!(res == FR_OK))
    {
        printf("\r\n��gpslog.txt�ļ�ʧ�ܣ�����SD���ĸ�Ŀ¼�Ƿ�����gpslog.txt�ļ�!\r\n");
        return ;      
    }

    /* �����������������Ϣ�ĺ��� */
    nmea_property()->trace_func = &trace;
    nmea_property()->error_func = &error;

    /* ��ʼ��GPS���ݽṹ */
    nmea_zero_INFO(&info);
    nmea_parser_init(&parser);

    while(!f_eof(&log_file))
    {
      
        f_read(&log_file, &buff[0], 100, &br);

        /* ����nmea��ʽ���� */
        nmea_parse(&parser, &buff[0], br, &info);
      
        /* �Խ�����ʱ�����ת����ת���ɱ���ʱ�� */
        GMTconvert(&info.utc,&beiJingTime,8,1);
        
        /* �������õ�����Ϣ */
        printf("\r\nʱ��%d,%d,%d,%d,%d,%d\r\n", beiJingTime.year+1900, beiJingTime.mon+1,beiJingTime.day,beiJingTime.hour,beiJingTime.min,beiJingTime.sec);
        printf("\r\nγ�ȣ�%f,����%f\r\n",info.lat,info.lon);
        printf("\r\n����ʹ�õ����ǣ�%d,�ɼ����ǣ�%d",info.satinfo.inuse,info.satinfo.inview);
        printf("\r\n���θ߶ȣ�%f �� ", info.elv);
        printf("\r\n�ٶȣ�%f km/h ", info.speed);
        printf("\r\n����%f ��", info.direction);
	
	}

    f_lseek(&log_file, f_size(&log_file));

    /* �ͷ�GPS���ݽṹ */
    nmea_parser_destroy(&parser);
  
    /* �ر��ļ� */
    f_close(&log_file);
    
   
}
#else       //��GPSģ�鴫�ص���Ϣ���н���

/**
  * @brief  nmea_decode_test ����GPSģ����Ϣ
  * @param  ��
  * @retval ��
  */
int nmea_decode_test(void)
{
	//u8 temp[50];
  	nmeaINFO info;          //GPS�����õ�����Ϣ
    nmeaPARSER parser;      //����ʱʹ�õ����ݽṹ  
    uint8_t new_parse=0;    //�Ƿ����µĽ������ݱ�־
  
    nmeaTIME beiJingTime;    //����ʱ�� 

    /* �����������������Ϣ�ĺ��� */
    nmea_property()->trace_func = &trace;
    nmea_property()->error_func = &error;

    /* ��ʼ��GPS���ݽṹ */
    nmea_zero_INFO(&info);
    nmea_parser_init(&parser);


//    while(1)
//    {
      if(GPS_HalfTransferEnd)     /* ���յ�GPS_RBUFF_SIZEһ������� */
      {
        /* ����nmea��ʽ���� */
        nmea_parse(&parser, (const char*)&gps_rbuff[0], HALF_GPS_RBUFF_SIZE, &info);
        
        GPS_HalfTransferEnd = 0;   //��ձ�־λ
        new_parse = 1;             //���ý�����Ϣ��־ 
				//printf("HH\r\n");
      }
      else if(GPS_TransferEnd)    /* ���յ���һ������ */
      {

        nmea_parse(&parser, (const char*)&gps_rbuff[HALF_GPS_RBUFF_SIZE], HALF_GPS_RBUFF_SIZE, &info);
       
        GPS_TransferEnd = 0;
        new_parse =1;
				//printf("TT\r\n");
      }
      
      if(new_parse )                //���µĽ�����Ϣ   
      {    
        /* �Խ�����ʱ�����ת����ת���ɱ���ʱ�� */
        GMTconvert(&info.utc,&beiJingTime,8,1);
        /* �������õ�����Ϣ */
//        printf("\r\nʱ��%d,%d,%d,%d,%d,%d\r\n", beiJingTime.year+1900, beiJingTime.mon+1,beiJingTime.day,beiJingTime.hour,beiJingTime.min,beiJingTime.sec);
//        printf("\r\nγ�ȣ�%f,����%f\r\n",info.lat,info.lon);
//        printf("\r\n����ʹ�õ����ǣ�%d,�ɼ����ǣ�%d",info.satinfo.inuse,info.satinfo.inview);
//        printf("\r\n���θ߶ȣ�%f �� ", info.elv);
//        printf("\r\n�ٶȣ�%f km/h ", info.speed);
//        printf("\r\n����%f ��", info.direction);
				GPSTime.year=beiJingTime.year+1900;
				GPSTime.mon=beiJingTime.mon+1;
				GPSTime.day=beiJingTime.day;
				GPSTime.hour=beiJingTime.hour;
				GPSTime.min =beiJingTime.min ;
				GPSTime.sec =beiJingTime.sec ;
				GPSTime.hsec =beiJingTime.hsec ;
        GPS_Speed = info.speed;
				GPS_elvetion = info.elv;
				GPS_direction = info.direction;
				GPS_lat = info.lat;
				GPS_lon = info.lon;
				GPS_num = info.satinfo.inuse;
				GPS_sta = info.fix;/**< Operating mode, used for navigation (1 = Fix not available; 2 = 2D; 3 = 3D) */
				//��γ�ȶȷֽ��Ƶ�ʮ����ת��
				GPS_lat = (GPS_lat /100.0-(int)(GPS_lat/100.0))/60.0*100.0+(int)(GPS_lat/100.0);
				GPS_lon = (GPS_lon /100.0-(int)(GPS_lon/100.0))/60.0*100.0+(int)(GPS_lon/100.0);
//				sprintf((char*)temp,"lt:%.2f ln:%.2f sta:%d use:%d\r\n",GPS_lat,GPS_lon,GPS_sta,info.satinfo.inview);
//				New_NRF_Tx(temp,sizeof(temp));
        new_parse = 0;
      }
//	}

    /* �ͷ�GPS���ݽṹ */
     nmea_parser_destroy(&parser);
     return 0;
}

#endif






/**************************************************end of file****************************************/

