#ifndef __USART1_H
#define	__USART1_H

#include "includes.h"

void USART1_Config(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void SendArray(unsigned char *loc,unsigned char num);//USART1�����鷢�ͺ���

#endif /* __USART1_H */
