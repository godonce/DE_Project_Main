/**
  ******************************************************************************
  * <h2><center>&copy; COPYRIGHT 2013 Embest Tech. Co., Ltd.</center></h2>
  * @file    bsp.h
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-February-2013
  * @brief   Heard for bsp.c
  *         
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
#ifndef __BSP_H__
#define __BSP_H__

INT32U   OS_CPU_SysTickClkFreq     (void);
void     BSP_IntDisAll             (void);
void     BSP_InitLED               (void);
void     LED_Toggle                (void);


#endif /*__BSP_H__*/
