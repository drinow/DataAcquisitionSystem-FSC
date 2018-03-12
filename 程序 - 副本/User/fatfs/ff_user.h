#ifndef __FF_USER_H
#define __FF_USER_H

#include "includes.h"
#include "stm32f10x.h"
#include "bsp_sdio_sd.h"  	/* SD������ģ�� */
#include "ff.h"				/* FatFS�ļ�ϵͳģ��*/	

/* �������ļ��ڵ��õĺ������� */
 void ViewRootDir(void);
 void CreateNewFile(void);
 void ReadFileData(void);
 void CreateDir(void);
 void WriteFileTest(void);

void SearchDir(void);
void CreateOneDir(const char *str);
void CreateAFile(const char *filedir, char *filename);
void WriteSomething(const char *filedir, char *filename,unsigned char* data,u8 length);

void SD_UserInit(void);
#endif
