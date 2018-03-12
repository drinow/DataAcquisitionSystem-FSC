#ifndef __LED_H
#define __LED_H

#include "includes.h"

#define LED1 1
#define LED2 2

#define OFF  				0
#define ON	 				1

#define NORMAL			0
#define BREATH 			2
#define FASTFLICKER 3//���� 10hz
#define MEDIFLICKER	4//����	5hz
#define SLOWFLICKER	5//����	2hz

void PWM_LED_Init(void);
void PWM_LED_STATE(u8 num,u8 state);
void LED_STATE_Fun(void);

#endif
