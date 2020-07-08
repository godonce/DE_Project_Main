#ifndef _timer_H_
#define _timer_H_

#include "lpc43xx_timer.h"
#include "lpc43xx_cgu.h"
#include "lpc43xx_gpio.h"



void TIMER0_IRQHandler(void);
void Timer0_Init(void);


void TIMER1_IRQHandler(void);
void Init_Timer1(void);

void TIMER2_IRQHandler(void);
void Init_Timer2(void);

void TIMER3_IRQHandler(void);
void Init_Timer3(void);
#endif

