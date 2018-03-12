#include "datatransfer.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))
#define Grav 0.0006125	//�������ٶ�ת������ 9.8/160000 ��160000Ϊ��ֹʱ��Z��ֵ��

void Uart1_Put_Buf(unsigned char *DataToSend , u8 data_num)
{
	u8 i=0;
	for(i=0;i<data_num;i++)
	{
		USART_SendData(USART1,*(DataToSend+i));
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	
	}
}

void CAN_SendGPS_A(void)
{
	s32 _temp;
	CanTxMsg TxMessage;
	TxMessage.StdId=0xF4;
	TxMessage.Data[0]=GPS_sta;//��λ״̬
	TxMessage.Data[1]=GPS_num;//��������
	_temp=(s16)(GPS_elvetion*10);//����
	TxMessage.Data[2]=BYTE1(_temp);
	TxMessage.Data[3]=BYTE0(_temp);
	_temp = (s16)(GPS_direction*10);//����
	TxMessage.Data[4]=BYTE1(_temp);
	TxMessage.Data[5]=BYTE0(_temp);
	_temp = (u16)(GPS_Speed*100);//����
	TxMessage.Data[6]=BYTE1(_temp);
	TxMessage.Data[7]=BYTE0(_temp);
	
	CAN_Transmit(CAN1,&TxMessage);
}

void CAN_SendGPS_B(void)
{
	s32 _temp;
	CanTxMsg TxMessage;
	TxMessage.StdId=0xF5;
	_temp = (int)(GPS_lon*10000000);//����
	TxMessage.Data[0]=BYTE3(_temp);
	TxMessage.Data[1]=BYTE2(_temp);
	TxMessage.Data[2]=BYTE1(_temp);
	TxMessage.Data[3]=BYTE0(_temp);
	_temp = (int)(GPS_lat*10000000);//ά��
	TxMessage.Data[4]=BYTE3(_temp);
	TxMessage.Data[5]=BYTE2(_temp);
	TxMessage.Data[6]=BYTE1(_temp);
	TxMessage.Data[7]=BYTE0(_temp);
	
	CAN_Transmit(CAN1,&TxMessage);
}

void CAN_SendADC_A(void)
{
	s32 _temp;
	CanTxMsg TxMessage;
	TxMessage.StdId=0xF2;
		_temp = ADCBuff[0];
	TxMessage.Data[0]=BYTE1(_temp);
	TxMessage.Data[1]=BYTE0(_temp);
		_temp = ADCBuff[1];
	TxMessage.Data[2]=BYTE1(_temp);
	TxMessage.Data[3]=BYTE0(_temp);
		_temp = ADCBuff[2];
	TxMessage.Data[4]=BYTE1(_temp);
	TxMessage.Data[5]=BYTE0(_temp);
		_temp = ADCBuff[3];
	TxMessage.Data[6]=BYTE1(_temp);
	TxMessage.Data[7]=BYTE0(_temp);
	
	CAN_Transmit(CAN1,&TxMessage);
}

void CAN_SendADC_B(void)
{
	s32 _temp;
	CanTxMsg TxMessage;
	TxMessage.StdId=0xF3;
		_temp = ADCBuff[4];
	TxMessage.Data[0]=BYTE1(_temp);
	TxMessage.Data[1]=BYTE0(_temp);
		_temp = ADCBuff[5];
	TxMessage.Data[2]=BYTE1(_temp);
	TxMessage.Data[3]=BYTE0(_temp);
		_temp = ADCBuff[6];
	TxMessage.Data[4]=BYTE1(_temp);
	TxMessage.Data[5]=BYTE0(_temp);
		_temp = ADCBuff[7];
	TxMessage.Data[6]=BYTE1(_temp);
	TxMessage.Data[7]=BYTE0(_temp);
	
	CAN_Transmit(CAN1,&TxMessage);
}

void CAN_SendLicence(void)
{
	s32 _temp;
	CanTxMsg TxMessage;
	TxMessage.StdId=0xE0;
	
	TxMessage.Data[0]=Licence.STOP;
	TxMessage.Data[1]=Licence.LocationLimit ;
	TxMessage.Data[2]=Licence.TimeLimit ;
	_temp = Licence.RunTime;
	TxMessage.Data[3]=BYTE1(_temp);
	TxMessage.Data[4]=BYTE0(_temp);
	TxMessage.Data[5]=0;
	TxMessage.Data[6]=0;
	TxMessage.Data[7]=0;
	
	CAN_Transmit(CAN1,&TxMessage);
}

//���ͳ�����̬����
extern float Yaw,Roll,Pitch;//ŷ����
void ANO_SendAtt(void)
{
	u8 _cnt=0;vs16 _temp;	u8 sum = 0;u8 i=0;
	u8 data_to_send[32];
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;
	
	_temp = (int)(Roll*100);
	data_to_send[_cnt++]=BYTE1(_temp);//ȡ1���ֽڣ���ɼ����ֽ�ȡ����_temp������
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = (int)(Pitch*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = (int)(Yaw*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	

	data_to_send[_cnt++]=0;//CSB
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=0;//PRS
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=0;//ARMED

	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
#ifdef RC_UART	
	Uart1_Put_Buf(data_to_send,_cnt);
#endif
if(RC_NRF)
	NRF_Tx_Dat(data_to_send);
}
//

//����6050
void ANO_Send6050(void)
{
	u8 _cnt=0;vs16 _temp;	u8 sum = 0;u8 i=0;
	u8 data_to_send[32];
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	/*
	���ڴ������ڷ�λ��ԭ����б90�㣩��������ֵ�ķ���˳����Щ��ı�
	*/
	_temp = accel[0];
		data_to_send[_cnt++]=BYTE1(_temp);//ȡ1���ֽڣ���ɼ����ֽ�ȡ����_temp������
		data_to_send[_cnt++]=BYTE0(_temp);
	_temp = accel[2];
		data_to_send[_cnt++]=BYTE1(_temp);
		data_to_send[_cnt++]=BYTE0(_temp);
	_temp = accel[1];
		data_to_send[_cnt++]=BYTE1(_temp);
		data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = gyro[0];
		data_to_send[_cnt++]=BYTE1(_temp);//
		data_to_send[_cnt++]=BYTE0(_temp);
	_temp = gyro[2];
		data_to_send[_cnt++]=BYTE1(_temp);
		data_to_send[_cnt++]=BYTE0(_temp);
	_temp = gyro[1];
		data_to_send[_cnt++]=BYTE1(_temp);
		data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp =0;
	data_to_send[_cnt++]=BYTE1(_temp);//
	data_to_send[_cnt++]=BYTE0(_temp);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);

	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
#ifdef RC_UART	
	Uart1_Put_Buf(data_to_send,_cnt);
#endif
if( RC_NRF )
	NRF_Tx_Dat(data_to_send);
}


void ANO_SendMotec(void)
{
	u8 _cnt=0, sum = 0,i=0;
	u8 data_to_send[32];
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xF1;
	data_to_send[_cnt++]=0;

	data_to_send[_cnt++]=MotecCache[4];//ת�� 1
	data_to_send[_cnt++]=MotecCache[5];

	data_to_send[_cnt++]=MotecCache[6];//������λ��
	data_to_send[_cnt++]=MotecCache[7];

	data_to_send[_cnt++]=MotecCache[8];//���ѹǿ
	data_to_send[_cnt++]=MotecCache[9];

	data_to_send[_cnt++]=MotecCache[10];//�����¶�
	data_to_send[_cnt++]=MotecCache[11];

	data_to_send[_cnt++]=MotecCache[12];//�������¶� 5
	data_to_send[_cnt++]=MotecCache[13];

	data_to_send[_cnt++]=MotecCache[14];//lambda1
	data_to_send[_cnt++]=MotecCache[15];

	data_to_send[_cnt++]=MotecCache[48];//��ص�ѹ
	data_to_send[_cnt++]=MotecCache[49];

	data_to_send[_cnt++]=MotecCache[52];//�����ٶ�����1
	data_to_send[_cnt++]=MotecCache[53];

	data_to_send[_cnt++]=MotecCache[54];//�����ٶ�����2
	data_to_send[_cnt++]=MotecCache[55];
	
	data_to_send[_cnt++]=MotecCache[56];//�����ٶ�����3   10
	data_to_send[_cnt++]=MotecCache[57];
	
	data_to_send[_cnt++]=MotecCache[58];//�����ٶ�����4
	data_to_send[_cnt++]=MotecCache[59];
	
	data_to_send[_cnt++]=MotecCache[64];//������
	data_to_send[_cnt++]=MotecCache[65];
	
	//��λ�յ�����0�������õ�λ��ѹ����
	data_to_send[_cnt++]=MotecCache[30];//��λ  13
	data_to_send[_cnt++]=MotecCache[31];
	
	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
#ifdef RC_UART	
	Uart1_Put_Buf(data_to_send,_cnt);
#endif
if(RC_NRF)
	NRF_Tx_Dat(data_to_send);
}

//
void ANO_SendADC(void)	
{
	u8 _cnt=0;vs16 _temp;	u8 sum = 0;u8 i=0;
	u8 data_to_send[32];
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xF2;
	data_to_send[_cnt++]=0;
	
	//4·����
	_temp = ADCBuff[0];
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = ADCBuff[1];
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = ADCBuff[2];
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = ADCBuff[3];
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	//ʣ��ADC
	_temp = ADCBuff[4];
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = ADCBuff[5];
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = ADCBuff[6];
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = ADCBuff[7];
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = ADCBuff[8];
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = ADCBuff[9];
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
#ifdef RC_UART	
	Uart1_Put_Buf(data_to_send,_cnt);
#endif
if(RC_NRF)
	NRF_Tx_Dat(data_to_send);
}


void ANO_SendGPS(void)
{
	u8 _cnt=0;vs32 _temp;	u8 sum = 0;u8 i=0;
	u8 data_to_send[32];
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x04;
	data_to_send[_cnt++]=0;

	data_to_send[_cnt++]=GPS_sta;//��λ״̬

	data_to_send[_cnt++]=GPS_num;//��������
	
	_temp = (int)(GPS_lon*10000000);//����
	data_to_send[_cnt++]=BYTE3(_temp);
	data_to_send[_cnt++]=BYTE2(_temp);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = (int)(GPS_lat*10000000);//ά��
	data_to_send[_cnt++]=BYTE3(_temp);
	data_to_send[_cnt++]=BYTE2(_temp);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = (s16)(GPS_elvetion*10);//����
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);

	_temp = (s16)(GPS_direction*10);//����
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);

	_temp = (u16)(GPS_Speed*100);//����
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);

	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
#ifdef RC_UART	
	Uart1_Put_Buf(data_to_send,_cnt);
#endif
if(RC_NRF)
	NRF_Tx_Dat(data_to_send);
}


void ANO_SendVotage(void)
{
	u8 _cnt=0;vs32 _temp;	u8 sum = 0;u8 i=0;
	u8 data_to_send[32];
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x05;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=MotecCache[48];
	data_to_send[_cnt++]=MotecCache[49];

	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;


	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
#ifdef RC_UART	
	Uart1_Put_Buf(data_to_send,_cnt);
#endif
if(RC_NRF)
	NRF_Tx_Dat(data_to_send);
}
//
extern volatile u8 SendAtt,SendMotec,SendGPS,SendADC,STOP;
void SendDATA(void)
{
	if(Licence.STOP==0)//δͣ��
	{
		if(SendMotec)
		{
			SendMotec=0;
			ANO_SendMotec();//31Byte
		}
		if(SendADC)
	  {
			SendADC=0;
			CAN_SendADC_A();
			CAN_SendADC_B();
			ANO_SendADC();//25Byte
		}
		if(SendAtt)
		{
			SendAtt=0;
			ANO_SendAtt();//18Byte
			ANO_Send6050();//21Byte
		}
		if(SendGPS)
		{
			SendGPS=0;
			CAN_SendLicence();
			CAN_SendGPS_A();
			CAN_SendGPS_B();
			ANO_SendGPS();//21Byte
			ANO_SendVotage();//9Byte
		}
	}
	else
	{
		CAN_SendLicence();
	}
}
//

