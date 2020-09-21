

#include "USB_MAIN.h"
#include <string.h>
#include "lpc43xx.H"                        /* LPC23xx definitions */
#include "lpc_types.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_uart.h"
#include <stdio.h>

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "cdc.h"
#include "cdcuser.h"
#include "usbuser.h"

#include "lpc43xx_cgu.h"
#include "lpc43xx_libcfg.h"
#include "debug_frmwrk.h"
#include "serial.h"


#include "0420.h"
#include "com_torque.h"
#include  "datafigures.h"
//#include "main.h"

/* Example group ----------------------------------------------------------- */
/** @defgroup USBDEV_USBCDC	USBCDC
 * @ingroup USBDEV_Examples
 * @{
 */
volatile uint32_t systicks=0;
void MODBUS_READ(void);
extern DQH_T ep_QH[EP_NUM_MAX];
extern DTD_T ep_TD[EP_NUM_MAX];
extern uint32_t DevStatusFS2HS;

extern void USB_EndPoint0 (uint32_t event);
typedef struct __CDC_BUF_T {
  unsigned char data[(64)   ];
  unsigned int wrIdx;
  unsigned int rdIdx;
} CDC_BUF_T;
extern CDC_BUF_T  CDC_OutBuf;       
void IOInit(void);
/*----------------------------------------------------------------------------
 Initialises the VCOM port.
 Call this function before using VCOM_putchar or VCOM_getchar
 *---------------------------------------------------------------------------*/
void VCOM_Init(void) {
#if PORT_NUM
  CDC_Init (1);
#else
  CDC_Init (0);
#endif
}

  int  numBytesToRead, numBytesRead, numAvailByte;
/*----------------------------------------------------------------------------
  Reads character from serial port buffer and writes to USB buffer
 *---------------------------------------------------------------------------*/
char send[10];
/*----------------------------------------------------------------------------
  Reads character from USB buffer and writes to serial port buffer
 *---------------------------------------------------------------------------*/
	//ai_o420.AI_0420  shuru moniliang
	//ai_o420.AO_0420_UI   shuchu moniliang

uint8_t usb_count_flag = 0;
extern unsigned char usb_handshake;
void VCOM_Usb2Serial_send(void)
{
	/*if(ai_o420.AI_0420_old!=ai_o420.AI_0420)
	{
		MODBUS_SEND_0420(2,(unsigned short)(ai_o420.AI_0420*100));
						ai_o420.AI_0420_old=ai_o420.AI_0420;
	}
		if(ai_o420.AO_0420_old!=ai_o420.AO_0420_UI)
	{
		MODBUS_SEND_0420(3,(unsigned short)(ai_o420.AO_0420_UI*100));
				ai_o420.AO_0420_old=ai_o420.AO_0420_UI;
	}*/
    
    //byj上位机程序
    if(usb_handshake == 1)
    {
        ai_o420.flag_save0420_o=1;
        if(usb_count_flag == 0)
        {
            MODBUS_SEND_0420(2,(unsigned short)(ai_o420.AI_0420 * 100));
            usb_count_flag = 1;
        }
        else if(usb_count_flag == 1)
        {
            MODBUS_SEND_0420(3,(unsigned short)(ai_o420.AO_0420_UI * 100));
            usb_count_flag = 2;
        }
        else if (usb_count_flag == 2)
        {
            MODBUS_SEND_0420(4,(unsigned short)(ai_o420.G0420_slope));
            usb_count_flag = 3;
        }
        else if (usb_count_flag == 3)
        {
            MODBUS_SEND_0420(5,(unsigned short)(ai_o420.G0420_offset));
            usb_count_flag = 4;
        }
        else if (usb_count_flag == 4)
        {
            MODBUS_SEND_0420(6,(unsigned short)(ai_o420.G0420_OUT_slope));
            usb_count_flag = 5;
        }
        else if (usb_count_flag == 5)
        {
            MODBUS_SEND_0420(7,(unsigned short)(ai_o420.G0420_OUT_offset));
            usb_count_flag = 0;
            usb_handshake  = 0;  //握手结束
        }
    } 
}
//char read[50];
//char Read_buf[20];
extern unsigned char Read_buf_modbus[20];
extern unsigned char Send_buf_modbus[40];
void VCOM_Usb2Serial(void)
{
    int i;
    VCOM_Usb2Serial_send();
    CDC_OutBufAvailChar (&numAvailByte);
    if (numAvailByte > 0) 
    {
        numBytesToRead = numAvailByte > 32 ? 32 : numAvailByte;
        numBytesRead = CDC_RdOutBuf (&Read_buf_modbus[0], &numBytesToRead);
		//MODBUS_READ();
		m0420_Read();
		m_torque_Read();
		//USB_WriteEP (0x82, (unsigned char *)&Read_buf[0], numBytesToRead);
//		for(i=0;i<numBytesToRead;i++)
//		{
//		  send[i]=read[i];
//			read[i]=0;
//		}
  }
}



/*----------------------------------------------------------------------------
  checks the serial state and initiates notification
 *---------------------------------------------------------------------------*/
void VCOM_CheckSerialState (void) {
         unsigned short temp;
  static unsigned short serialState;

  temp = CDC_GetSerialState();
  if (serialState != temp) {
    serialState = temp;
    CDC_NotificationIn();                  // send SERIAL_STATE notification
  }
}

/*----------------------------------------------------------------------------
  Main Program
 *---------------------------------------------------------------------------*/

//int main (void) 
void USB_init(void)
	{

  LPC_USBDRV_INIT_T usb_cb;


  /* initilize call back structures */
  memset((void*)&usb_cb, 0, sizeof(LPC_USBDRV_INIT_T));
  usb_cb.USB_Reset_Event = USB_Reset_Event;
  usb_cb.USB_P_EP[0] = USB_EndPoint0;
  usb_cb.USB_P_EP[1] = USB_EndPoint1;
  usb_cb.USB_P_EP[2] = USB_EndPoint2;
  usb_cb.ep0_maxp = USB_MAX_PACKET0;

  USB_Init(&usb_cb);                               // USB Initialization
  USB_Connect(TRUE);                        // USB Connect
  //while (!USB_Configuration) ;              // wait until USB is configured
//  while (1) {                               // Loop forever
//    VCOM_Usb2Serial();
//  } // end while
} // end main ()


void MODBUS_SEND_0420(char data,unsigned short dat)
{
	  int len=0;
		Send_buf_modbus[0]=0x5a;
		Send_buf_modbus[1]=0xA5;
		Send_buf_modbus[2]=0x40;
		Send_buf_modbus[3]=data;
		Send_buf_modbus[4]=0x00;
    Send_buf_modbus[5]=0x00;
		Send_buf_modbus[6]=(dat%256)&0xff;
		Send_buf_modbus[7]=(dat>>8)&0xff;
	 USB_WriteEP (0x82, (unsigned char *)&Send_buf_modbus[0], 8);
}

#ifdef  DEBUG
/*******************************************************************************
* @brief        Reports the name of the source file and the source line number
*               where the CHECK_PARAM error has occurred.
* @param[in]    file Pointer to the source file name
* @param[in]    line assert_param error line source number
* @return       None
*******************************************************************************/
void check_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while(1);
}
#endif
/**
 * @}
 */
