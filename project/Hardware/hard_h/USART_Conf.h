#ifndef _USART_Conf_H_
#define _USART_Conf_H_
#include "lpc43xx_uart.h"
#include "lpc43xx_cgu.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_gpio.h"
#include "lpc43xx_libcfg.h"
#include "lpc43xx_gpdma.h"
#include "lpc43xx_timer.h"
#include "FIGURES.h"
#include "stdarg.h"
#include "stdint.h"
#include "dataCRC.h"

#define UART_RING_BUFSIZE   256





/* Buf mask */
#define __BUF_MASK (UART_RING_BUFSIZE-1)
/* Check buf is full or not */
#define __BUF_IS_FULL(head, tail)   ((tail&__BUF_MASK)==((head+1)&__BUF_MASK))
/* Check buf will be full in next receiving or not */
#define __BUF_WILL_FULL(head, tail) ((tail&__BUF_MASK)==((head+2)&__BUF_MASK))
/* Check buf is empty */
#define __BUF_IS_EMPTY(head, tail)  ((head&__BUF_MASK)==(tail&__BUF_MASK))
/* Reset buf */
#define __BUF_RESET(bufidx)         (bufidx=0)
#define __BUF_INCR(bufidx)          (bufidx=(bufidx+1)&__BUF_MASK)

//#define LCD480272
////#define LCD800480

//#ifdef  LCD800480
//#define LCD_WIDTH               800
////#define LCD_HEIGHT              480
//#else
//#ifdef LCD480272
//#define LCD_WIDTH               480
//#define LCD_HEIGHT               272
//#endif
//#endif

void UART_IntErr(uint8_t bLSErrType);

void UART3_IntReceive(void);
uint32_t UART3Send( uint8_t *txbuf, uint8_t buflen);
uint32_t UART3Receive( uint8_t *rxbuf, uint8_t buflen);
void UART3_IntTransmit(void);
void UART3_IRQHandler(void);
void UART3_Init(void);
void PowerSend( uint8_t *txbuf, uint8_t buflen);
void c_entry_uart3 (void) ;

void UART0_IntReceive(void);
uint32_t UART0Send( uint8_t *txbuf, uint8_t buflen);
uint32_t UART0Receive( uint8_t *rxbuf, uint8_t buflen);
void UART0_IntTransmit(void);
void UART0_IRQHandler(void);
void UART0_Init(void);
uint32_t TestSend( uint8_t *txbuf, uint8_t buflen);
void c_entry_uart0 (void) ;



void motor_dir(uint8_t DIR);

#endif

