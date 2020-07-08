#ifndef _Encoder_H_
#define _Encoder_H_

#include "lpc43xx_adc.h"
#include "lpc43xx_cgu.h"
#include "lpc43xx_gpio.h"
#include "lpc43xx_uart.h"
#include "lpc43xx_scu.h"


#include "USART_Conf.h"
#include "FIGURES.h"
#include "Handler.h"
#include "timer.h"

//#define _ADC_INT             ADC_ADINTEN5
//#define _ADC_CHANNEL         ADC_CHANNEL_5   

extern unsigned char  ssi_m,ssi_s;

#define Restart_Encoder_PORT          0xF
#define Restart_Encoder_PORT_PIN      9
#define Restart_Encoder_PORT_FUNC     FUNC4
#define Restart_Encoder_GPIO          7
#define Restart_Encoder_GPIO_PIN      23

#ifdef Encnew
	#define KEY_NOW 0x08000000
	#define Read_all_zero  0xFFFFFFF
#elif  Encold
	#define KEY_NOW 0x008000000000
	#define Read_all_zero  0xFFFFFFFFFFFF
#endif

void Init_Encoder(void);
void Restart_Encoder_Init(void);
void Restart_Encoder(int set);

int graytobinary(uint32_t graycode);


void c_entry_Encoder2 (void) ;
void UART2_Init(void);
void UART2_IRQHandler(void);
void c_entry_uart2_encoder (void) ;
#endif

