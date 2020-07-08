/**
  ******************************************************************************
  * <h2><center>&copy; COPYRIGHT 2013 Embest Tech. Co., Ltd.</center></h2>
  * @file    tsc2064.h
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-February-2013
  * @brief   Header for tsc2046.c    
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
#ifndef __TSC2046_H__
#define __TSC2046_H__
/* Includes ------------------------------------------------------------------*/  
#include "lpc43xx_ssp.h"  


/* The Min AD value */
#define  TOUCH_AD_MIN         10
/* The Max AD value */
#define  TOUCH_AD_MAX         4000     

void      TSC2046_Init          (void);
uint16_t  Touch_MeasurementX    (void);
uint16_t  Touch_MeasurementY    (void);
uint8_t   Get_TouchDetected     (void);

#endif /*__TSC2046_H__*/
