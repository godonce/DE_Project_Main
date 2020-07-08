/**
  ******************************************************************************
  * <h2><center>&copy; COPYRIGHT 2013 Embest Tech. Co., Ltd.</center></h2>
  * @file    tsc2046.c
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-February-2013
  * @brief   LCD  Touch Initialization    
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Embest SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
  * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
  * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/  
#include "lpc43xx_ssp.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_cgu.h"
#include "lpc43xx_gpio.h"
#include "lpc43xx_libcfg.h"
#include "tsc2046.h"
#include "Handler.h"

#define  TOUCH_AD_X           0xD0
#define  TOUCH_AD_Y           0x90
#define  BUSY_PORT            4
#define  BUSY_PORT_PIN        8
#define  BUSY_PORT_FUNC       FUNC4
#define  BUSY_GPIO            5
#define  BUSY_GPIO_PIN        12

#define  CS_GPIO              7
#define  CS_GPIO_PIN          16

#define SET_CS                GPIO_ClearValue(CS_GPIO, (1 << CS_GPIO_PIN));
#define CLR_CS                GPIO_SetValue(CS_GPIO, (1 << CS_GPIO_PIN));




uint8_t TouchDetected = 0;

/********************************************************************************
 * @brief       Delay 
 * @param[in]	None
 * @return      None 
 *******************************************************************************/
//void Delay(void)
//{
//  volatile uint32_t i;
//	
//  for (i = 2000; i > 0; i--);
//}

/********************************************************************************
 * @brief       Tsc2046 interrupt configure 
 * @param[in]	None
 * @return      None 
 *******************************************************************************/
void TSC2046_IRQ_CFG(void)
{
#if 0
  scu_pinmux(0x4, 8, PUP_ENABLE,  FUNC4);    //TP_PENIRQ
  LPC_SCU->PINTSEL0 = (5 << 5) | 0xC;        //Pint interrupt 0 select GPIO5[12]
  GPIO_SetDir(5,(1<<12), 0);                 //GPIO5[12] select input mode
  GPIO_SetValue(5,(1<<12));
  LPC_GPIO_PIN_INT->ISEL &= ~(1 << 0);       //Edge sensitive
  LPC_GPIO_PIN_INT->IENR |= 1 << 0;
  LPC_GPIO_PIN_INT->SIENR |= 1 << 0;
  /* preemption = 1, sub-priority = 1 */
  NVIC_SetPriority(PIN_INT0_IRQn, ((0x01<<3)|0x01));
  /* Enable Interrupt for UART0 channel */
  NVIC_EnableIRQ(PIN_INT0_IRQn);
#else
    scu_pinmux(BUSY_PORT, BUSY_PORT_PIN, PUP_ENABLE | INBUF_ENABLE, BUSY_PORT_FUNC);
    GPIO_SetDir(BUSY_GPIO, 1 << BUSY_GPIO_PIN, 0);
#endif
}
uint8_t Get_TouchDetected(void)
{	
  if (GPIO_ReadValue(BUSY_GPIO) & (1 << BUSY_GPIO_PIN)) {
    return 0;
  }
  return 1;
}
/********************************************************************************
 * @brief       Initialization Tsc2046
 * @param[in]	None
 * @return      None 
 *******************************************************************************/
void TSC2046_Init(void)
{
  /* SSP Configuration structure variable */
  SSP_CFG_Type SSP_ConfigStruct;
	
  /* Configure SSP0 pins*/
  scu_pinmux(0xF, 0, MD_PLN_FAST, FUNC0);  // PF.0 connected to SCL/SCLK  func0=SSP0 SCK0
  scu_pinmux(0xF, 2, MD_PLN_FAST, FUNC2);  // PF.2 connected to SO        func2=SSP0 MISO0
  scu_pinmux(0xF, 3, MD_PLN_FAST, FUNC2);  // PF.3 connected to nSI       func2=SSP0 MOSI0
  scu_pinmux(0xF, 1, MD_PDN,      FUNC4);  // nCS      
  GPIO_SetDir(CS_GPIO,(1 << CS_GPIO_PIN), 1);
  /* initialize SSP configuration structure to default */
  SSP_ConfigStructInit(&SSP_ConfigStruct);

  /* Initialize SSP peripheral with parameter given in structure above */
  SSP_Init(LPC_SSP0, &SSP_ConfigStruct);
  /* Enable SSP peripheral */
  SSP_Cmd(LPC_SSP0, ENABLE);
  TSC2046_IRQ_CFG();
}
/********************************************************************************
 * @brief       SPI read and write 
 * @param[in]	data   spi write data
 * @return      spi read data
 *******************************************************************************/
static uint8_t SPI_ReadWrite(uint8_t data)
{
  while(!(LPC_SSP0->SR & (1 << 1)));
  LPC_SSP0->DR = data;
  while(!(LPC_SSP0->SR & (1 << 0)));
  while(!(LPC_SSP0->SR & (1 << 2)));
  data = LPC_SSP0->DR;
 
  return data;	
}
/********************************************************************************
 * @brief       Read the touch ad value form touch ic
 * @param[in]	cmd    read cmd
 * @return      ad value 
 *******************************************************************************/
uint16_t Touch_Read_AD(uint8_t cmd)
{
  uint16_t data;

  SET_CS;
  SPI_ReadWrite(cmd);
  
  Delay();

  data = SPI_ReadWrite(0);
  data = data << 8;
  data |= SPI_ReadWrite(0);
  data = data >> 3;
  data &= 0xFFF;
  CLR_CS;  
  return data;	
}
/********************************************************************************
 * @brief       measure x AD value
 * @param[in]	None
 * @return      ad value 
 *******************************************************************************/
uint16_t  Touch_MeasurementX(void)
{
  uint32_t i, sum;

  sum = 0;
  for (i = 0; i < 4; i++){
    sum += Touch_Read_AD(TOUCH_AD_X);
    Delay();
  }
  sum >>= 2;
  if ((sum > TOUCH_AD_MAX) || (sum < TOUCH_AD_MIN)) {
    sum = 0;
  }	  
  return sum;
}

/********************************************************************************
 * @brief       measure y AD value
 * @param[in]	None
 * @return      ad value 
 *******************************************************************************/
uint16_t  Touch_MeasurementY(void)
{
  uint32_t i, sum;

  sum = 0;
  for (i = 0; i < 4; i++){
    sum += Touch_Read_AD(TOUCH_AD_Y);
    Delay();
  }
  sum >>= 2;
  if ((sum > TOUCH_AD_MAX) || (sum < TOUCH_AD_MIN)) {
    sum = 0;
  }	  
  return sum;
}
