//#include "ds1302.h"
//#include "stm32f10x.h"

//#define nop()  __NOP

//#define DS1302_CLK_H()	(GPIOE->BSRR=GPIO_Pin_2)
//#define DS1302_CLK_L()	(GPIOE->BRR=GPIO_Pin_2)

//#define DS1302_OUT_H()	(GPIOE->BSRR=GPIO_Pin_3)
//#define DS1302_OUT_L()	(GPIOE->BRR=GPIO_Pin_3)

//#define DS1302_RST_H()	(GPIOE->BSRR=GPIO_Pin_4)
//#define DS1302_RST_L()	(GPIOE->BRR=GPIO_Pin_4)
//											
//#define DS1302_IN_X		(GPIOE->IDR&GPIO_Pin_3)

//#define Time_24_Hour	0x00	//24ʱ�ƿ���	
//#define Time_Start		0x00	//��ʼ��ʱ

////д�Ĵ��������Ĵ�����ַ�ֱ��һ���ɡ�
//#define DS1302_SECOND	0x80	//DS1302���Ĵ������������
//#define DS1302_MINUTE	0x82
//#define DS1302_HOUR		0x84
//#define DS1302_DAY		0x86
//#define DS1302_MONTH	0x88
//#define DS1302_WEEK		0x8A
//#define DS1302_YEAR		0x8C
//#define DS1302_WRITE	0x8E
//#define DS1302_POWER	0x90

//static GPIO_InitTypeDef GPIO_InitStructure;

//void DS1302_Configuration(void)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

//	//E2-CLK,E3-IO,E4-RST
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50Mʱ���ٶ�
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
//	GPIO_ResetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
//}


//void DelayNOP(u32 count)
//{
//	u8 cnt=0;
////	while(count--) nop();
//	while(count--) cnt--;
//}

//static void DS1302_OUT(void)
//{
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
//}

//static void DS1302_IN(void)
//{
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
//}

//void DS1302SendByte(u8 byte)
//{
//	u8	i;
//	for(i=0x01;i;i<<=1)
//	{
//		if(byte&i)	DS1302_OUT_H();
//		else	DS1302_OUT_L();
//		DS1302_CLK_H();
//		DelayNOP(50);		//����ʱ
//		DS1302_CLK_L();
//	}
//}

//u8 DS1302ReceiveByte(void)
//{
//	u8	i,byte=0;

//	for(i=0x01;i;i<<=1)
//	{
//		if(DS1302_IN_X)	byte |= i;
//		DS1302_CLK_H();
//		DelayNOP(50);		//����ʱ
//		DS1302_CLK_L();
//	}
//	return(byte);
//}

//void Write1302(u8 addr,u8 data)
//{
//  DS1302_OUT();
//	DS1302_RST_L();
//	DS1302_CLK_L();
//	DS1302_RST_H();
//	DelayNOP(100);
//	DS1302SendByte(addr);
//	DS1302SendByte(data);
//	DelayNOP(100);
//	DS1302_RST_L();
//}

//u8 Read1302(u8 addr)
//{
//    u8 data=0;

//    DS1302_OUT();
//	DS1302_RST_L();
//	DS1302_CLK_L();
//	DS1302_RST_H();
//	DelayNOP(100);
//	DS1302SendByte(addr|0x01);
//	DS1302_IN();
//	data = DS1302ReceiveByte();
//	DelayNOP(100);
//	DS1302_RST_L();
//	return(data);
//}

////��ȡʱ�亯��
//void DS1302_GetTime(u8 *time)
//{
////	u8 tmp;
//	
//	time[0] = Read1302(DS1302_YEAR+1);
//	time[1] = Read1302(DS1302_WEEK+1);
//	time[2] = Read1302(DS1302_MONTH+1);
//	time[3] = Read1302(DS1302_DAY+1);
//	time[4] = Read1302(DS1302_HOUR+1);
//	time[5] = Read1302(DS1302_MINUTE+1);
//	time[6] = Read1302(DS1302_SECOND+1);
//}

///*
//��ȡDS1302�е�RAM
//addr:��ַ,��0��30,��31���ֽڵĿռ�
//����Ϊ����ȡ������
//*/
//u8 ReadDS1302Ram(u8 addr)
//{
//	u8	tmp,res;

//	tmp = (addr<<1)|0xc0;
//	res = Read1302(tmp);
//	return(res);
//}

///*
//дDS1302�е�RAM
//addr:��ַ,��0��30,��31���ֽڵĿռ�
//data:Ҫд������
//*/
//void WriteDS1302Ram(u8 addr,u8 data)
//{
//	u8	tmp;

//	Write1302(DS1302_WRITE,0x00);		//�ر�д����
//	tmp = (addr<<1)|0xc0;
//	Write1302(tmp,data);
//	Write1302(DS1302_WRITE,0x80);		//��д����
//}

//void ReadDSRam(u8 *p,u8 add,u8 cnt)
//{
//	u8 i;
//	
//	if(cnt>30) return;
//	for(i=0;i<cnt;i++)
//	{
//		*p = ReadDS1302Ram(add+1+i);
//		p++;
//	}
//}

//void WriteDSRam(u8 *p,u8 add,u8 cnt)
//{
//	u8 i;
//	if(cnt>30) return;
//	for(i=0;i<cnt;i++)
//	{
//		WriteDS1302Ram(add+1+i,*p++);
//	}
//}
//  
///*
//��ʱ�亯��,˳��Ϊ:��������ʱ����
//*/
//void ReadDS1302Clock(u8 *p)
//{
//	DS1302_OUT();
//	DS1302_RST_L();
//	DS1302_CLK_L();
//	DS1302_RST_H();
//	DelayNOP(100);
//	DS1302SendByte(0xbf);			//ͻ��ģʽ
//	DS1302_IN();
//	p[5] = DS1302ReceiveByte();		//��
//	p[4] = DS1302ReceiveByte();		//��
//	p[3] = DS1302ReceiveByte();		//ʱ
//	p[2] = DS1302ReceiveByte();		//��
//	p[1] = DS1302ReceiveByte();		//��
//	DS1302ReceiveByte();			//��
//	p[0] = DS1302ReceiveByte();		//��
//	DS1302ReceiveByte();			//������־�ֽ�
//	DelayNOP(100);
//	DS1302_RST_L();
//}

///*
//дʱ�亯��,˳��Ϊ:��������ʱ����
//*/
//void WriteDS1302Clock(u8 *p)
//{
//	Write1302(DS1302_WRITE,0x00);		//�ر�д����
//	DS1302_OUT();
//	DS1302_RST_L();
//	DS1302_CLK_L();
//	DS1302_RST_H();
//	DelayNOP(100);
//	DS1302SendByte(0xbe);				//ͻ��ģʽ
//	DS1302SendByte(p[5]);				//��
//	DS1302SendByte(p[4]);				//��
//	DS1302SendByte(p[3]);				//ʱ
//	DS1302SendByte(p[2]);				//��
//	DS1302SendByte(p[1]);				//��
//	DS1302SendByte(0x01);				//�ܣ����ó���һ��û��ʹ��
//	DS1302SendByte(p[0]);				//��
//	DS1302SendByte(0x80);				//������־�ֽ�
//	DelayNOP(100);
//	DS1302_RST_L();
//}

//void InitClock(void)
//{
//	u8	tmp;

//	DS1302_Configuration();
//	tmp = ReadDS1302Ram(0);
//	if(tmp^0xa5)
//	{
//		WriteDS1302Ram(0,0xa5);
//		Write1302(DS1302_WRITE,0x00);		//�ر�д����
//		Write1302(0x90,0x03);				//��ֹ������
//		Write1302(DS1302_HOUR,0x00);		//���ó�24Сʱ��
//		Write1302(DS1302_SECOND,0x00);	//ʹ��ʱ������
//		Write1302(DS1302_WRITE,0x80);		//��д����
//	}
//}

////���ע�� DS1302��BCD��ʽ�ģ�����0x13Ӧ����ָ13�������19��
//void TestDS1302(void)
//{
//	u8 i,tt[7],dd1[30],dd2[30];
//	
//	DS1302_Configuration();
////	InitClock();
////	tt[0] = 0x13;
////	tt[1] = 0x05;
////	tt[2] = 0x23;
////	tt[3] = 0x09;
////	tt[4] = 0x25;
////	tt[5] = 0x00;
////	WriteDS1302Clock(tt);
////	for(i=0;i<30;i++)
////	{
////		dd1[i] = i;
////		dd2[i] = 0;
////	}
////	WriteDSRam(dd1,0,30);
////	ReadDSRam(dd2,0,30);
//	Write1302(0x8e,0x00);//�ر�д����
//	Write1302(0x80,0x00);//s
//	Write1302(0x82,0x00);//min
//	Write1302(0x84,0x22);//h
//	Write1302(0x86,0x27);//d
//	Write1302(0x88,0x06);//m
//	Write1302(0x8a,0x08);//zhou
//	Write1302(0x8c,0x16);//year
//	Write1302(0x8e,0x80);//��д����
//	while(1) 
//	{
////		ReadDS1302Clock(tt);
//		DS1302_GetTime(tt);
//		printf("%s\r\n",tt);
//	}
//}
////end

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/********************************copyright ythuitong by wit_yuan**************************/

#include "ds1302.h"

//////////////////////////////////////////////////////////////////////////
//			 	???		:		ds1302_init		
//			   	??		:		ds1302?????
//				??		:		void
//				??		:		wit_yuan
//				??		:		2014-08-08
////////////////////////////////////////////////////////////////////////////
void Delay_10us(u8 temp)
{
	u8 i=0;
	u8 j=0xff;
	for(;i<temp;i++)
		for(;j>0;j--)
	;
}
void ds1302_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE );	  
	GPIO_InitStructure.GPIO_Pin = (DS1302_SCK_PIN | DS1302_IO_PIN | DS1302_CE_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DS1302_PORT, &GPIO_InitStructure);

	DS1302_WriteByte(WrControl,0x00);  //?????,???????	

	Delay_10us(10);
	if(DS1302_ReadByte(RdTrickleCharge) != 0xA6)
	{
		Delay_10us(10);
		DS1302_WriteByte(WrTrickleCharge,0xA6);

		printf("??\r\n");
	}	
	Delay_10us(10);
	DS1302_WriteByte(WrControl,0x80);  //?????,??????
}


void DS1302_IO_OUT()
{
    GPIO_InitTypeDef GPIO_InitStructure;                                                                
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;           
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			
    GPIO_Init(GPIOE, &GPIO_InitStructure);         
}

void DS1302_IO_IN()
{
    GPIO_InitTypeDef GPIO_InitStructure;                                                                
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;           
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      
			
    GPIO_Init(GPIOE, &GPIO_InitStructure);         
}

//DS1302??8bit
void DS1302_Write8bit(unsigned char code)
{
	unsigned char i;
	DS1302_IO_OUT();						//????
	DS1302_CLRSCK();						//SCK = 0
	for(i=0;i<8;i++)
	{
		  Delay_10us(5);
		  if(code&0x01) 
				(DS1302_SETIO());			//I/0  = 1
		  else 
				(DS1302_CLRIO());			//I/0 = 0
		  Delay_10us(5);
		  
		  DS1302_SETSCK();				//SCLK  = 1
		  Delay_10us(5);
															
		  DS1302_CLRSCK();				//SCLK = 0
		  code = code >> 1;
	}
}

//DS1302??8bit???
unsigned char DS1302_Read8bit(void)
{
	unsigned char i,code;
	unsigned char temp;
	DS1302_IO_IN();
	code = 0;
	DS1302_CLRSCK();						//SCLK = 0

	Delay_10us(5);

	for(i=0;i<8;i++)
	{
			
		  code = code >>1;
			
		  if(DS1302_READ_SDA())
			{
				code = code | 0x80;
			}	
					
		  Delay_10us(5);
		  DS1302_SETSCK();			//SCLK = 1
		  Delay_10us(5);
	
		  DS1302_CLRSCK();			//SCLK = 0

	}
	
	temp = code /16;
	code = code % 16;
	code = code + temp * 10;			//???????
	
	return code;
}


//??DS1302???1Byte
unsigned char DS1302_ReadByte(unsigned char con)
{
	unsigned char code;
	DS1302_CLRCE();		   //??DS1302					//CE = 0
	Delay_10us(5);       
	DS1302_CLRSCK();													//SCLK = 0
	Delay_10us(5);
	DS1302_SETCE();          //??DS1302			//CE = 1;
	Delay_10us(5);
	DS1302_Write8bit(con);   //????				//????
	code = DS1302_Read8bit();  //??????
	
	//printf("code = %d\r\n" ,code );
	Delay_10us(5);
	DS1302_SETSCK();													//SCLK = 1
	Delay_10us(5);
	DS1302_CLRCE();         //??DS1302			//CE = 0
	return code;
}


//u8  DS1302_ReadRam(u8 addr)
//{
//	u8	tmp,res;
//	
//	tmp = addr;
//	res = DS1302_ReadByte(tmp);
//	return(res);	
//}

////????DS1302????
//void DS1302_ReadBurst(unsigned char *rstr)
//{
//	int i = 0;
//	unsigned char code;
//	DS1302_CLRCE();		   			//??DS1302					//CE = 0
//	Delay_10us(5);       
//	DS1302_CLRSCK();													//SCLK = 0
//	Delay_10us(5);
//	DS1302_SETCE();          		//??DS1302			//CE = 1;
//	Delay_10us(5);
//	DS1302_Write8bit(RdRamBurst);   //????				//????
//	
//   	for(i = 0 ;i < 31 ; i++)
//	{
//   		rstr[i] = DS1302_ReadRam(2 * i + 1 + 0xc0);  		//??????
//	}
//	
//	//printf("code = %d\r\n" ,code );
//	Delay_10us(5);
//	DS1302_SETSCK();													//SCLK = 1
//	Delay_10us(5);
//	DS1302_CLRCE();         //??DS1302			//CE = 0
//
//	for(i = 0 ;i < 31 ; i ++)
//	{
//	 	printf("rstr[%d] = %d\r\n",i,rstr[i]);
//	}
//
//}


//?DS1302???1Byte
void DS1302_WriteByte(unsigned char con,unsigned char code)
{
	DS1302_CLRCE();         		//??DS1302		//CE = 0
	Delay_10us(5);
	DS1302_CLRSCK();														//SCK = 0
	Delay_10us(5);
	
	DS1302_SETCE();          		//??DS1302		//CE = 1
	Delay_10us(5);
	DS1302_Write8bit(con);     	//?????		//????
	DS1302_Write8bit(code); 		//????			//????
	Delay_10us(5);
	DS1302_SETSCK();
	Delay_10us(5);
	DS1302_CLRCE();          //??DS1302

}


//????
void DS1302_WriteTime(TIME_TypeDef* time)
{

	DS1302_WriteByte(WrControl,0x00);  		//?????,??????
		
	DS1302_WriteByte(WrYear,time->year);
	DS1302_WriteByte(WrMonth,time->month);
	DS1302_WriteByte(WrDate,time->date);
	DS1302_WriteByte(WrWeek,time->week);
	DS1302_WriteByte(WrHour,time->hour);
	DS1302_WriteByte(WrMin,time->min);
	DS1302_WriteByte(WrSec,time->sec);

	DS1302_WriteByte(WrControl,0x80);  		//?????,??????

}

u8  DS1302_ReadRam(u8 addr)
{
	u8	tmp,res;
	
	tmp = addr;
	res = DS1302_ReadByte(tmp);
	return(res);	
}

typedef struct
{
	unsigned char  sec;
	unsigned char min;
	unsigned char hour;
	unsigned char date;
	unsigned char month;
	unsigned char week;
	unsigned char year;
}Time;


//????DS1302????
void DS1302_ReadBurst(unsigned char *rstr)
{
	int i = 0;
//	unsigned char code;
	DS1302_CLRCE();		   			//??DS1302					//CE = 0
	Delay_10us(5);       
	DS1302_CLRSCK();													//SCLK = 0
	Delay_10us(5);
	DS1302_SETCE();          		//??DS1302			//CE = 1;
	Delay_10us(5);
	DS1302_Write8bit(RdRamBurst);   //????				//????
	
   	for(i = 0 ;i < 7 ; i++)
	{
		rstr[i] = DS1302_Read8bit();
	}
	
	//printf("code = %d\r\n" ,code );
	Delay_10us(5);
	DS1302_SETSCK();													//SCLK = 1
	Delay_10us(5);
	DS1302_CLRCE();         //??DS1302			//CE = 0

//	for(i = 0 ;i < 7 ; i ++)
	{
	 	//printf("rstr[%d] = %d\r\n",i,rstr[i]);
	}

}
//////////////????/////////////////////////////////////////////////////
void readTimeTest(void)
{
	Time myTime;
	DS1302_ReadBurst((u8 *)&myTime);

	printf("time:%d-%d-%d %d:%d:%d\r\n",myTime.year, myTime.month, myTime.date,
		myTime.hour,myTime.min,myTime.sec);

}

void DS1302_ReadTime(TIME_TypeDef* time)
{
	Time myTime;
	DS1302_ReadBurst((u8 *)&myTime);
	
 	time->year 	= myTime.year;
	time->month = myTime.month;	
	time->date 	= myTime.date;

	time->hour 	= myTime.hour;
	time->min 	= myTime.min;
	time->sec 	= myTime.sec;

//	printf("time:%d-%d-%d %d:%d:%d\r\n",myTime.year, myTime.month, myTime.date,
//		myTime.hour,myTime.min,myTime.sec);
}

////????
//void DS1302_ReadTime(TIME_TypeDef* time)
//{
//	u8 i = 0;
//	u8 year_temp[3];
//	u8 month_temp[3];		
//	u8 date_temp[3];
//	u8 hour_temp[3];
//	u8 min_temp[3];
//	u8 sec_temp[3];
//
//	u8 max;
//	u8 min;
//
//	for(i = 0 ; i < 3 ; i ++)
//	{
//		year_temp[i]  =  DS1302_ReadByte(RdYear);
//		month_temp[i] =  DS1302_ReadByte(RdMonth);
//		date_temp[i]  =  DS1302_ReadByte(RdDate);
//		hour_temp[i]  =  DS1302_ReadByte(RdHour);
//		min_temp[i]   =  DS1302_ReadByte(RdMin);
//		sec_temp[i]   =  DS1302_ReadByte(RdSec);
//	}
//	//?
//	max = year_temp[0];
//	min = year_temp[0];
//	for(i = 1 ; i < 3 ; i ++)
//	{
//		if(year_temp[i] > max)
//		{
//			max = year_temp[i];
//		}
//		if(year_temp[i] < min)
//		{
//			min = year_temp[i];
//		}
//	}
//	time->year = year_temp[0] + year_temp[1] + year_temp[2] - max - min; 
//	//?
//	max = month_temp[0];
//	min = month_temp[0];
//	for(i = 1 ; i < 3 ; i ++)
//	{
//		if(month_temp[i] > max)
//		{
//			max = month_temp[i];
//		}
//		if(month_temp[i] < min)
//		{
//			min = month_temp[i];
//		}
//	}
//	time->month = month_temp[0] + month_temp[1] + month_temp[2] - max - min; 
//	//?
//	max = date_temp[0];
//	min = date_temp[0];
//	for(i = 1 ; i < 3 ; i ++)
//	{
//		if(date_temp[i] > max)
//		{
//			max = date_temp[i];
//		}
//		if(date_temp[i] < min)
//		{
//			min = date_temp[i];
//		}
//	}
//	time->date = date_temp[0] + date_temp[1] + date_temp[2] - max - min; 
//	//?
//	max = hour_temp[0];
//	min = hour_temp[0];
//	for(i = 1 ; i < 3 ; i ++)
//	{
//		if(hour_temp[i] > max)
//		{
//			max = hour_temp[i];
//		}
//		if(hour_temp[i] < min)
//		{
//			min = hour_temp[i];
//		}
//	}
//	time->hour = hour_temp[0] + hour_temp[1] + hour_temp[2] - max - min;	
//
//	//?
//	max = min_temp[0];
//	min = min_temp[0];
//	for(i = 1 ; i < 3 ; i ++)
//	{
//		if(min_temp[i] > max)
//		{
//			max = min_temp[i];
//		}
//		if(min_temp[i] < min)
//		{
//			min = min_temp[i];
//		}
//	}
//	time->min = min_temp[0] + min_temp[1] + min_temp[2] - max - min;
//
//	//?
//	max = sec_temp[0];
//	min = sec_temp[0];
//	for(i = 1 ; i < 3 ; i ++)
//	{
//		if(sec_temp[i] > max)
//		{
//			max = sec_temp[i];
//		}
//		if(sec_temp[i] < min)
//		{
//			min = sec_temp[i];
//		}
//	}
//	time->sec = sec_temp[0] + sec_temp[1] + sec_temp[2] - max - min;
//
////	time->year 	= DS1302_ReadByte(RdYear);
////	time->month = DS1302_ReadByte(RdMonth);	
////	time->date 	= DS1302_ReadByte(RdDate);
////	time->week 	= DS1302_ReadByte(RdWeek);
////
////	time->hour 	= DS1302_ReadByte(RdHour);
////	time->min 	= DS1302_ReadByte(RdMin);
////	time->sec 	= DS1302_ReadByte(RdSec);
//
////	year_temp  =  DS1302_ReadByte(RdYear);
////	year_month =  DS1302_ReadByte(RdMonth);
////	year_date  =  DS1302_ReadByte(RdDate);
////	year_hour  =  DS1302_ReadByte(RdHour);
////	year_min   =  DS1302_ReadByte(RdMin);
////	year_sec   =  DS1302_ReadByte(RdSec);
//
////	printf("year = %d\r\n",time->year);
////	printf("month = %d\r\n",time->month);
////	printf("year = %d\r\n",time->date);
////	printf("year = %d\r\n",time->hour);
////	printf("year = %d\r\n",time->min);
////	printf("year = %d\r\n",time->sec);
////
////	printf("year_temp = %d\r\n",year_temp);
////	printf("year_month = %d\r\n",year_month);
////	printf("year_date = %d\r\n",year_date);
////	printf("year_hour = %d\r\n",year_hour);
////	printf("year_min = %d\r\n",year_min);
////	printf("year_sec = %d\r\n",year_sec);
//
//
////	if(	(year_temp + year_month + year_date + year_hour + year_min + year_sec)
////		< ( time->year + time->month +  ))
////	{
////	
////	}
//}
	
	
unsigned char time[20]="\0";

void time_convert(TIME_TypeDef *time_get)
{
	time[0] = '2';															//2
	time[1] = '0';															//0
	time[2] = time_get->year / 10 + '0';		//1
	time[3] = time_get->year % 10 + '0';        //4
	time[4] = '-';	                            //-
	time[5] = time_get->month / 10 + '0';				//0
	time[6] = time_get->month % 10 + '0';       //4
	time[7] = '-';															//-
	
	time[8] = time_get->date / 10 + '0';        //1
	time[9] = time_get->date % 10 + '0';	      //0
	time[10] = ' ';                             // 
	time[11] = time_get->hour / 10 + '0';       //1
	time[12] = time_get->hour % 10 + '0';       //4
	time[13] = ':';															//:
	time[14] = time_get->min / 10 + '0';        //2
	time[15] = time_get->min % 10 + '0';      	//1
	time[16] = ':';															//:
	time[17] = time_get->sec / 10 + '0';		    //3
	time[18] = time_get->sec % 10 + '0';	      //0
	time[19] = '\0';															// 
	
	
//	printf("time = %s\r\n",time);
}


/************************************end of file 2014-08-08*********************************/
