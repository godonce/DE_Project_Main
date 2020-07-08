#include "Usart_task.h"
#include "lpc43xx_uart.h"
#include "lpc43xx_cgu.h"
#include "lpc43xx_libcfg.h"
#include "lpc43xx_scu.h"
//#include "lpc43xx_gpdma.h"
#include "debug_frmwrk.h"
#include "FIGURES.h"
/* buffer size definition */
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

#define DIRECTION 0

#if (DIRECTION==0)
  uint8_t TURN=0x48;
#elif (DIRECTION==1)
  uint8_t TURN= 0x4C;
#elif (DIRECTION==2)
  uint8_t TURN =0x44;
#endif

char Flag_Ready,Flag_Start;
typedef struct
{
    __IO uint32_t tx_head;                /*!< UART Tx ring buffer head index */
    __IO uint32_t tx_tail;                /*!< UART Tx ring buffer tail index */
    __IO uint32_t rx_head;                /*!< UART Rx ring buffer head index */
    __IO uint32_t rx_tail;                /*!< UART Rx ring buffer tail index */
    __IO uint8_t  tx[UART_RING_BUFSIZE];  /*!< UART Tx data ring buffer */
    __IO uint8_t  rx[UART_RING_BUFSIZE];  /*!< UART Rx data ring buffer */
} UART_RING_BUFFER_T;

typedef struct __UsartSend
{
  uint8_t		TURN;
	uint8_t 	Speed_H;
	uint8_t 	Speed_L;
	uint8_t		Torque_H;
  uint8_t		Torque_L; 
  uint8_t		Null;
	uint8_t		CheckSum_H;
	uint8_t		CheckSum_L;
}Send_Message;

/************************** PRIVATE VARIABLES *************************/
uint8_t menu1[] = "Hello NXP Semiconductors \n\r";
uint8_t menu2[] =
 "UART interrupt mode demo using ring buffer \n\r\t "
 "- MCU lpc18xx/LPC43xx \n\r\t" 
 "- CORE ARM Cortex-M3/M4 \n\r\t"
 "UART0 - 9600bps \n\r";
uint8_t menu3[] = "UART demo terminated!\n";


uint16_t MOTOR_Speed;
uint16_t MOTOR_Torque;

// UART Ring buffer
UART_RING_BUFFER_T rb;
Send_Message USART3_Send;
// Current Tx Interrupt enable state
__IO FlagStatus TxIntStat;


/************************** PRIVATE FUNCTIONS *************************/
/* Interrupt service routines */
void UART0_IRQHandler(void);
void UART_IntErr(uint8_t bLSErrType);
void UART_IntTransmit(void);
void UART_IntReceive(void);
uint32_t UARTReceive(LPC_USARTn_Type *UARTPort, uint8_t *rxbuf, uint8_t buflen);
uint32_t UARTSend(LPC_USARTn_Type *UARTPort, uint8_t *txbuf, uint8_t buflen);
uint32_t PowerSend( uint8_t *txbuf, uint8_t buflen);
void print_menu(void);

uint32_t UART3Receive( uint8_t *rxbuf, uint8_t buflen)
{
  uint8_t *data = (uint8_t *) rxbuf;
  uint32_t bytes = 0;
  UART_IntConfig(LPC_USART3, UART_INTCFG_RBR, DISABLE);
  while ((buflen > 0) && (!(__BUF_IS_EMPTY(rb.rx_head, rb.rx_tail)))) 
	{
    *data = rb.rx[rb.rx_tail];
    data++;

    /* Update tail pointer */
    __BUF_INCR(rb.rx_tail);
    bytes++;
    buflen--;
  }
  UART_IntConfig(LPC_USART3, UART_INTCFG_RBR, ENABLE);
  return bytes;
}

/********************************************************************//**
 * @brief       UART receive function (ring buffer used)
 * @param[in]   None
 * @return      None
 *********************************************************************/
void UART_IntReceive(void)
{
  uint8_t tmpc;
  uint32_t rLen;

  while (1) {
    // Call UART read function in UART driver
    rLen = UART_Receive(LPC_USART3, &tmpc, 1, NONE_BLOCKING);
    // If data received
    if (rLen){
      /* Check if buffer is more space
       * If no more space, remaining character will be trimmed out
       */
      if (!__BUF_IS_FULL(rb.rx_head,rb.rx_tail)){
        rb.rx[rb.rx_head] = tmpc;
        __BUF_INCR(rb.rx_head);
      }
    } else {
      // no more data
      break;
    }
  }
}

/********************************************************************//**
 * @brief       UART transmit function (ring buffer used)
 * @param[in]   None
 * @return      None
 *********************************************************************/
void UART_IntTransmit(void)
{
  // Disable THRE interrupt
  UART_IntConfig(LPC_USART3, UART_INTCFG_THRE, DISABLE);

  /* Wait for FIFO buffer empty, transfer UART_TX_FIFO_SIZE bytes
   * of data or break whenever ring buffers are empty */
  /* Wait until THR empty */
  while (UART_CheckBusy(LPC_USART3) == SET);

  while (!__BUF_IS_EMPTY(rb.tx_head,rb.tx_tail)) {
    /* Move a piece of data into the transmit FIFO */
    if (UART_Send(LPC_USART3, (uint8_t *)&rb.tx[rb.tx_tail], 1, NONE_BLOCKING)){
      /* Update transmit ring FIFO tail pointer */
      __BUF_INCR(rb.tx_tail);
    } else {
      break;
    }
  }

  /* If there is no more data to send, disable the transmit
     interrupt - else enable it or keep it enabled */
  if (__BUF_IS_EMPTY(rb.tx_head, rb.tx_tail)) {
    UART_IntConfig(LPC_USART3, UART_INTCFG_THRE, DISABLE);
    // Reset Tx Interrupt state
    TxIntStat = RESET;
  } else {
    // Set Tx Interrupt state
    TxIntStat = SET;
    UART_IntConfig(LPC_USART3, UART_INTCFG_THRE, ENABLE);
  }
}


/*********************************************************************//**
 * @brief       UART Line Status Error
 * @param[in]   bLSErrType  UART Line Status Error Type
 * @return      None
 **********************************************************************/
void UART_IntErr(uint8_t bLSErrType)
{
  uint8_t test;
  while (1) {
    test = bLSErrType;
    test = test;
  }
}

/*-------------------------PRIVATE FUNCTIONS------------------------------*/
/*********************************************************************//**
 * @brief       UART transmit function for interrupt mode (using ring buffers)
 * @param[in]   UARTPort   Selected UART peripheral used to send data,
 *              should be UART0
 * @param[out]  txbuf Pointer to Transmit buffer
 * @param[in]   buflen Length of Transmit buffer
 * @return      Number of bytes actually sent to the ring buffer
 **********************************************************************/
uint32_t PowerSend( uint8_t *txbuf, uint8_t buflen)
{
  uint8_t *data = (uint8_t *) txbuf;
  uint32_t bytes = 0;
  UART_IntConfig(LPC_USART3, UART_INTCFG_THRE, DISABLE);
  while ((buflen > 0) && (!__BUF_IS_FULL(rb.tx_head, rb.tx_tail))) 
	{
    rb.tx[rb.tx_head] = *data;
    data++;
    __BUF_INCR(rb.tx_head);
    bytes++;
    buflen--;
  }
  if (TxIntStat == RESET) {
    UART_IntTransmit();
  } else 
	{ 
    UART_IntConfig(LPC_USART3, UART_INTCFG_THRE, ENABLE);
  }
  return bytes;	
}


/*********************************************************************//**
 * @brief       UART read function for interrupt mode (using ring buffers)
 * @param[in]   UARTPort  Selected UART peripheral used to send data,
 *              should be UART0
 * @param[out]  rxbuf Pointer to Received buffer
 * @param[in]   buflen Length of Received buffer
 * @return      Number of bytes actually read from the ring buffer
 **********************************************************************/
uint32_t UARTReceive(LPC_USARTn_Type *UARTPort, uint8_t *rxbuf, uint8_t buflen)
{
  uint8_t *data = (uint8_t *) rxbuf;
  uint32_t bytes = 0;

  /* Temporarily lock out UART receive interrupts during this
     read so the UART receive interrupt won't cause problems
     with the index values */
  UART_IntConfig(UARTPort, UART_INTCFG_RBR, DISABLE);

  /* Loop until receive buffer ring is empty or
     until max_bytes expires */
  while ((buflen > 0) && (!(__BUF_IS_EMPTY(rb.rx_head, rb.rx_tail)))) {
    /* Read data from ring buffer into user buffer */
    *data = rb.rx[rb.rx_tail];
    data++;

    /* Update tail pointer */
    __BUF_INCR(rb.rx_tail);

    /* Increment data count and decrement buffer size count */
    bytes++;
    buflen--;
  }

  /* Re-enable UART interrupts */
  UART_IntConfig(UARTPort, UART_INTCFG_RBR, ENABLE);

  return bytes;
}

//void print_menu(void)
//{
//  uint32_t tmp, tmp2;
//  uint8_t *pDat;

//  tmp = sizeof(menu1);
//  tmp2 = 0;
//  pDat = (uint8_t *)&menu1[0];
//  while(tmp) {
//    tmp2 = PowerSend(pDat, tmp);
//    pDat += tmp2;
//    tmp -= tmp2;
//  }

//  tmp = sizeof(menu2);
//  tmp2 = 0;
//  pDat = (uint8_t *)&menu2[0];
//  while(tmp) {
//    tmp2 = PowerSend(pDat, tmp);
//    pDat += tmp2;
//    tmp -= tmp2;
//  }
//}
#define CCU_CLK_CFG_RUN   (1 << 0)
#define CCU_CLK_CFG_AUTO  (1 << 1)
#define CCU_CLK_STAT_RUN  (1 << 0)

void UART3_Init(void)
{
	UART_CFG_Type UARTConfigStruct;
	scu_pinmux(0xF ,2 , MD_PDN, FUNC1); 	// PF1.0 : UART0_TXD
	scu_pinmux(0xF ,3 , MD_PLN|MD_EZI|MD_ZI, FUNC1); 	// PF.11 : UART0_RXD
	UART_ConfigStructInit(&UARTConfigStruct);
	UARTConfigStruct.Baud_rate = 115200;
	UART_Init(LPC_USART3, &UARTConfigStruct);
	UART_TxCmd(LPC_USART3, ENABLE);
#if defined(HITEX_LCD_TERM)
	xferConfig = InitLCDTerm();
#endif
}

void UART3_IRQHandler(void)
{
	
	uint8_t *GetBuf[8];
	//uint8_t GetBuffer;
	
	int i;
	for(i=0;i<8;i++)
	{
		(*GetBuf)[8] = UARTGetChar(LPC_USART3);
	}
	if((*GetBuf)[8]==0)
	{
			Flag_Ready=1;
	}
	if(Flag_Ready==1)
	{
		Flag_Ready=0;	
		Flag_Ready=0;
		if((*GetBuf)[0]==0x1E)
		{
			if((*GetBuf)[2]==0x00)
			{
				if((*GetBuf)[4]==0x00)
				{
					if((*GetBuf)[5]==0x25)
					{
						
								Flag_Start=1;
							
					}
				}
			}
		}
	}
	if(Flag_Start==1)
	{
		 
	}

}

int c_entry_uart3 (void) 
{
	 GPIO_ClearValue(LED1_GPIO_PORT,(1<<LED1_GPIO_PIN));
	if(Flag_Start==1)
	{
		USART3_Send.TURN=0xFF;
		USART3_Send.Speed_H=(MOTOR_Speed/256)<<8;
		USART3_Send.Speed_L=MOTOR_Speed&0xff;
		USART3_Send.Torque_H=(MOTOR_Torque/256)<<8;
		USART3_Send.Torque_L=MOTOR_Torque&0xff;
		
		
		PowerSend((uint8_t *)&USART3_Send,(sizeof(USART3_Send)));
	}
	return 0;
}
