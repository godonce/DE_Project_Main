/**
  ******************************************************************************
  * <h2><center>&copy; COPYRIGHT 2012 Embest Tech. Co., Ltd.</center></h2>
  * @file    lcd_driver.c
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-December-2012
  * @brief   Header for lcd_driver.c      
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
#ifndef __LCD_DRIVER_H__
#define __LCD_DRIVER_H__
#include "lpc43xx_lcd.h"
#include "lpc43xx_scu.h"

#define LCD480272
//#define LCD800480

#ifdef  LCD800480
#define LCD_WIDTH               800
#define LCD_HEIGHT              480
#else
#ifdef LCD480272
#define LCD_WIDTH               480
#define LCD_HEIGHT               272
#endif
#endif

#define BACKLIGHT_PORT          0x07
#define BACKLIGHT_PORT_PIN      0x0
#define BACKLIGHT_PORT_FUNC     FUNC0
#define BACKLIGHT_GPIO          0x03
#define BACKLIGHT_GPIO_PIN      0x08

#define LCD_VRAM_BASE_ADDR      0x28000000

extern  void   Lcd_clear         (void);
extern  void   Lcd_drive_Init    (void);
extern  void   Lcd_Backlight     (uint8_t en);
#endif/*__LCD_DRIVER_H__*/
