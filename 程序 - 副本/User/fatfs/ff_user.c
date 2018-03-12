#include "ff_user.h"

/* ���������������̷������� */
#define EXAMPLE_NAME	"SDIO+FatFs�ļ�ϵͳ����"
#define EXAMPLE_DATE	"2011-10-16"
#define DEMO_VER		"2.0"

/* ���ڲ��Զ�д�ٶ� */
#define TEST_FILE_LEN			(2*1024*1024)	/* ���ڲ��Ե��ļ����� */
#define BUF_SIZE				512				/* ÿ�ζ�дSD����������ݳ��� */
uint8_t g_TestBuf[BUF_SIZE];		


/*
*********************************************************************************************************
*	�� �� ��: ViewRootDir
*	����˵��: ��ʾSD����Ŀ¼�µ��ļ���
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/


 void ViewRootDir(void)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FRESULT result;
	FATFS fs;
	DIR DirInf;  
	FILINFO FileInf;
	
	uint8_t tmpStr[20];
	uint32_t cnt = 0;
	
 	/* �����ļ�ϵͳ */
	result = f_mount(0, &fs);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}

	/* �򿪸��ļ��� */
	result = f_opendir(&DirInf, "/"); /* ���������������ӵ�ǰĿ¼��ʼ */
	if (result != FR_OK) 
	{
		printf("�򿪸�Ŀ¼ʧ�� (%d)\r\n", result);
		return;
	}

	/* ��ȡ��ǰ�ļ����µ��ļ���Ŀ¼ */
	printf("Name\t\tTyepe\t\tSize\r\n");
	for (cnt = 0; ;cnt++) 
	{
		result = f_readdir(&DirInf,&FileInf); 		/* ��ȡĿ¼��������Զ����� */
		if (result != FR_OK || FileInf.fname[0] == 0)
		{
			break;
		}
		
		if (FileInf.fname[0] == '.')
		{
			continue;
		}
		
		printf("%s", FileInf.fname);

		if (strlen(FileInf.fname) < 8)	/* ���� */
		{
			printf("\t\t");
		}
		else
		{
			printf("\t");
		}
		if (FileInf.fattrib == AM_DIR)
		{
			printf("Ŀ¼\t\t");
		} 
		else 
		{
			printf("�ļ�\t\t");
		}
		printf("%d\r\n", FileInf.fsize);
		sprintf((char *)tmpStr, "%d", FileInf.fsize);
	}

	/* ж���ļ�ϵͳ */
	f_mount(0, NULL);	
}

/*
*********************************************************************************************************
*	�� �� ��: CreateNewFile
*	����˵��: ��SD������һ�����ļ����ļ�������д��www.armfly.com��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 void CreateNewFile(void)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FRESULT result;
	FATFS fs;
	FIL file;
	DIR DirInf;  
	uint32_t bw;
	
 	/* �����ļ�ϵͳ */
	result = f_mount(0, &fs);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}

	/* �򿪸��ļ��� */
	result = f_opendir(&DirInf, "/"); /* ���������������ӵ�ǰĿ¼��ʼ */
	if (result != FR_OK) 
	{
		printf("�򿪸�Ŀ¼ʧ�� (%d)\r\n", result);
		return;
	}

	/* ���ļ� */
//	result = f_open(&file, "armfly.txt",  FA_OPEN_ALWAYS|FA_WRITE);
	result = f_open(&file, "armfly.txt",  FA_WRITE);
	if(result==FR_NO_FILE) //��ʱ������  �����г�Ŀ¼����ļ���
	{
		f_close(&file);
		printf("result:%d\r\n",result);
		result =f_open(&file, "armfly.txt",  FA_OPEN_ALWAYS);
	}
	printf("result:%d\r\n",result);
	result = f_lseek(&file,file.fsize); //�ƶ�ָ����ĩβ
	/* дһ������ */
	result = f_write(&file, "FatFS Write Demo \r\n www.armfly.com \r\n", 37, &bw);	
	
	if (result == FR_OK)
	{
		printf("armfly.txt �ļ�д��ɹ�\r\n");
	}
	else
	{
		printf("armfly.txt �ļ�д��ʧ��\r\n");
		printf("result:%d\r\n",result);
	}
	
	/* �ر��ļ�*/
	f_close(&file);
 	
	/* ж���ļ�ϵͳ */
	f_mount(0, NULL);	
}

/*
*********************************************************************************************************
*	�� �� ��: ReadFileData
*	����˵��: ��ȡ�ļ�armfly.txtǰ128���ַ�������ӡ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 void ReadFileData(void)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FRESULT result;
	FATFS fs;
	FIL file;
	DIR DirInf;  
	uint32_t bw;
	char buf[128];
	
 	/* �����ļ�ϵͳ */
	result = f_mount(0, &fs);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ��(%d)\r\n", result);
	}

	/* �򿪸��ļ��� */
	result = f_opendir(&DirInf, "/"); /* ���������������ӵ�ǰĿ¼��ʼ */
	if (result != FR_OK) 
	{
		printf("�򿪸�Ŀ¼ʧ��(%d)\r\n", result);
		return;
	}

	/* ���ļ� */
	result = f_open(&file, "armfly.txt", FA_OPEN_EXISTING | FA_READ);
	if (result !=  FR_OK)
	{
		printf("Don't Find File : armfly.txt\r\n");
		return;		
	}

	/* ��ȡ�ļ� */
	result = f_read(&file, &buf, sizeof(buf) - 1, &bw);
	if (bw > 0)
	{
		buf[bw] = 0;
		printf("\r\narmfly.txt �ļ����� : \r\n%s\r\n", buf);
	}
	else
	{
		printf("\r\narmfly.txt �ļ����� : \r\n");		
	}
	
	/* �ر��ļ�*/
	f_close(&file);
 	
	/* ж���ļ�ϵͳ */
	f_mount(0, NULL);
}

/*
*********************************************************************************************************
*	�� �� ��: CreateDir
*	����˵��: ��SD����Ŀ¼����Dir1��Dir2Ŀ¼����Dir1Ŀ¼�´�����Ŀ¼Dir1_1
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 void CreateDir(void)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FRESULT result;
	FATFS fs;
	
 	/* �����ļ�ϵͳ */
	result = f_mount(0, &fs);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}

	/* ����Ŀ¼/Dir1 */
	result = f_mkdir("/Dir1"); 
	if (result == FR_OK) 
	{
		printf("f_mkdir Dir1 Ok\r\n");
	}
	else if (result == FR_EXIST)
	{
		printf("Dir1 Ŀ¼�Ѿ�����(%d)\r\n", result);
	}
	else
	{
		printf("f_mkdir Dir1 ʧ�� (%d)\r\n", result);
		return;
	}

	/* ����Ŀ¼/Dir2 */
	result = f_mkdir("/Dir2"); 
	if (result == FR_OK) 
	{
		printf("f_mkdir Dir2 Ok\r\n");
	}
	else if (result == FR_EXIST)
	{
		printf("Dir2 Ŀ¼�Ѿ�����(%d)\r\n", result);
	}
	else
	{
		printf("f_mkdir Dir2 ʧ�� (%d)\r\n", result);
		return;
	}			

	/* ������Ŀ¼ /Dir1/Dir1_1	   ע�⣺������Ŀ¼Dir1_1ʱ�������ȴ�����Dir1 */
	result = f_mkdir("/Dir1/Dir1_1"); /* */
	if (result == FR_OK) 
	{
		printf("f_mkdir Dir1_1 �ɹ�\r\n");
	}
	else if (result == FR_EXIST)
	{
		printf("Dir1_1 Ŀ¼�Ѿ����� (%d)\r\n", result);
	}
	else
	{
		printf("f_mkdir Dir1_1 ʧ�� (%d)\r\n", result);
		return;
	}
 	
	/* ж���ļ�ϵͳ */
	f_mount(0, NULL);	
}

/*
*********************************************************************************************************
*	�� �� ��: WriteFileTest
*	����˵��: �����ļ���д�ٶ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/

uint8_t g_TestBuf[BUF_SIZE];	
 void WriteFileTest(void)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FRESULT result;
	FATFS fs;
	FIL file;
	DIR DirInf;  
	uint32_t bw;
	uint32_t i;
	uint32_t runtime1,runtime2,timelen;
	uint8_t err = 0;
	
	for (i = 0; i < sizeof(g_TestBuf); i++)
	{
		g_TestBuf[i] = (i % 10) + '0';
	}

  	/* �����ļ�ϵͳ */
	result = f_mount(0, &fs);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}

	/* �򿪸��ļ��� */
	result = f_opendir(&DirInf, "/"); /* ���������������ӵ�ǰĿ¼��ʼ */
	if (result != FR_OK) 
	{
		printf("�򿪸�Ŀ¼ʧ�� (%d)\r\n", result);
		return;
	}

	/* ���ļ� */
	result = f_open(&file, "Speed1.txt", FA_CREATE_ALWAYS | FA_WRITE);
	
	/* дһ������ */
	printf("��ʼд�ļ� %dKB ...\r\n", TEST_FILE_LEN / 1024);
	runtime1 = SysCnt;	/* ��ȡϵͳ����ʱ�� */
	for (i = 0; i < TEST_FILE_LEN / BUF_SIZE; i++)
	{
		result = f_write(&file, g_TestBuf, sizeof(g_TestBuf), &bw);	
		if (result == FR_OK)
		{
			if ((i % 100) == 0)
			{
				//bsp_LedToggle(1);	/* ��˸LED */
			}
		}
		else
		{
			err = 1;
			printf("Speed1.txt �ļ�дʧ��\r\n");
			break;
		}
	}
	runtime2 = SysCnt;	/* ��ȡϵͳ����ʱ�� */
	
	if (err == 0)
	{
		timelen = (runtime2 - runtime1);
		printf("  д�ĳ� : %dms   ƽ��д�ٶ� : %dB/S (%dKB/S)\r\n", timelen, 
			(TEST_FILE_LEN * 1000) / timelen, ((TEST_FILE_LEN / 1024) * 1000) / timelen);
	}
	
	f_close(&file);		/* �ر��ļ�*/

	/* ��ʼ���ļ����� */
	result = f_open(&file, "Speed1.txt", FA_OPEN_EXISTING | FA_READ);
	if (result !=  FR_OK)
	{
		printf("û���ҵ��ļ�: Speed1.txtt\r\n");
		return;		
	}

	printf("��ʼ���ļ� %dKB ...\r\n", TEST_FILE_LEN / 1024);
	runtime1 = SysCnt;	/* ��ȡϵͳ����ʱ�� */
	for (i = 0; i < TEST_FILE_LEN / BUF_SIZE; i++)
	{
		result = f_read(&file, g_TestBuf, sizeof(g_TestBuf), &bw);	
		if (result == FR_OK)
		{
			if ((i % 100) == 0)
			{
				//bsp_LedToggle(1);	/* ��˸LED */
			}
		}
		else
		{
			err = 1;
			printf("Speed1.txt �ļ���ʧ��\r\n");
			break;
		}
	}
	runtime2 = SysCnt;	/* ��ȡϵͳ����ʱ�� */
	
	if (err == 0)
	{
		timelen = (runtime2 - runtime1);
		printf("  ����ʱ : %dms   ƽ�����ٶ� : %dB/S (%dKB/S)\r\n", timelen, 
			(TEST_FILE_LEN * 1000) / timelen, ((TEST_FILE_LEN / 1024) * 1000) / timelen);
	}

	/* �ر��ļ�*/
	f_close(&file);
 	
	/* ж���ļ�ϵͳ */
	f_mount(0, NULL);	
}

char filepath[20];
extern unsigned char MotecSend[255];
u8 OpenFileSave=0;
void CreateAFile(const char *filedir, char *filename)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FRESULT result;
	FATFS fs;
	FIL file;
	DIR DirInf;  
	uint32_t bw;
	
	sprintf(filepath,"%s/%s",filedir,filename);

	
 	/* �����ļ�ϵͳ */
	result = f_mount(0, &fs);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}
	/* �򿪸��ļ��� */
	result = f_opendir(&DirInf, "/"); /* ���������������ӵ�ǰĿ¼��ʼ */
	if (result != FR_OK) 
	{
		printf("�򿪸�Ŀ¼ʧ�� (%d)\r\n", result);
		return;
	}

	/* ���ļ� */
	result = f_open(&file, filepath,  FA_OPEN_ALWAYS|FA_WRITE);

	result = f_lseek(&file,file.fsize); //�ƶ�ָ����ĩβ
		/* дһ������ */
	result = f_write(&file," QTU DATA ACQUISITION SYSTEM \r\n\r\n", 33, &bw);	

	if (result == FR_OK)
	{
		printf("armfly.txt �ļ�д��ɹ�\r\n");
		OpenFileSave=1;
	}
	else
	{
		printf("�ļ�д��ʧ��,���룺(%d) \r\n",result);
	}
	
	/* �ر��ļ�*/
	f_close(&file);
 	
	/* ж���ļ�ϵͳ */
	f_mount(0, NULL);	
	
}


char *LastfName=NULL; 

char DirString[20];
const char *DirStringE;
u16 DirNum;
u8 ReadmeFlag=1;
void SearchDir(void)
{
		/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FRESULT result;
	FATFS fs;
	DIR DirInf;  
	FILINFO FileInf;
	
	uint8_t tmpStr[20];
	uint32_t cnt = 0;
	
 	/* �����ļ�ϵͳ */
	result = f_mount(0, &fs);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}

	/* �򿪸��ļ��� */
	result = f_opendir(&DirInf, "/"); /* ���������������ӵ�ǰĿ¼��ʼ */
	if (result != FR_OK) 
	{
		printf("�򿪸�Ŀ¼ʧ�� (%d)\r\n", result);
		return ;
	}

	/* ��ȡ��ǰ�ļ����µ��ļ���Ŀ¼ */

	for (cnt = 0; ;cnt++) 
	{
		result = f_readdir(&DirInf,&FileInf); 		/* ��ȡĿ¼��������Զ����� */
		if (result != FR_OK || FileInf.fname[0] == 0)
		{
			DirNum++;
			if(DirNum==500)DirNum=1;
			printf("DirNum��%d\r\n",DirNum);
			sprintf(DirString, "/%d", DirNum);
			DirStringE=DirString;
			printf("Ŀ¼�ַ���%s\r\n",DirStringE);
			break;
		}
		
		if (FileInf.fname[0] == '.')
		{
			continue;
		}
		
		if (FileInf.fattrib == AM_DIR)
		{
			DirNum = atoi(FileInf.fname);
			//printf("%d\r\n", DirNum);
		}

		if(FileInf.fname=="Readme")
			ReadmeFlag=0;
		
		sprintf((char *)tmpStr, "%d", FileInf.fsize);
	}

	/* ж���ļ�ϵͳ */
	f_mount(0, NULL);	
	
}

void CreateOneDir(const char *str)
{
		/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FRESULT result;
	FATFS fs;

 	/* �����ļ�ϵͳ */
	result = f_mount(0, &fs);			/* Mount a logical drive */

	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}

	/* ����Ŀ¼/Dir1 */
	result = f_mkdir(str); 

	if (result == FR_OK) 
	{
		//printf("Ok\r\n");
	}
	else if (result == FR_EXIST)
	{
		//printf("Dir1 Ŀ¼�Ѿ�����(%d)\r\n", result);
	}
	else
	{
		printf("f_mkdir Dir1 ʧ�� (%d)\r\n", result);
		return;
	}
 	
	/* ж���ļ�ϵͳ */
	f_mount(0, NULL);	
}

void WriteSomething(const char *filedir, char *filename,unsigned char* data,u8 length)
{
		FRESULT result;
	FATFS fs;
	FIL file;
	DIR DirInf;  
	uint32_t bw;
	
	sprintf(filepath,"%s/%s",filedir,filename);

	
 	/* �����ļ�ϵͳ */
	result = f_mount(0, &fs);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}
	/* �򿪸��ļ��� */
	result = f_opendir(&DirInf, "/"); /* ���������������ӵ�ǰĿ¼��ʼ */
	if (result != FR_OK) 
	{
		printf("�򿪸�Ŀ¼ʧ�� (%d)\r\n", result);
		return;
	}

	/* ���ļ� */
	result = f_open(&file, filepath,  FA_OPEN_ALWAYS|FA_WRITE);

	result = f_lseek(&file,file.fsize); //�ƶ�ָ����ĩβ
		/* дһ������ */
	result = f_write(&file, data , length, &bw);	

	if (result == FR_OK)
	{
		//printf("Success�\r\n");
	}
	else
	{
		printf("Failure,���룺(%d) \r\n",result);
	}
	
	/* �ر��ļ�*/
	f_close(&file);
 	
	/* ж���ļ�ϵͳ */
	f_mount(0, NULL);	
}

//�û���ʼ������
void SD_UserInit(void)
{
	SearchDir();//��ѰĿ¼
	CreateOneDir(DirStringE);//������Ŀ¼
	CreateAFile(DirStringE,"Motec.txt");//����Ŀ¼�½������ļ�
	CreateAFile(DirStringE,"ADC.txt");
	CreateAFile(DirStringE,"MPU6050.txt");
}
