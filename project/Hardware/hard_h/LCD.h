#ifndef _LCD_H_
#define _LCD_H_

//#include "includes.h"
#include "lpc43xx_lcd.h"
#include "lpc43xx_gpio.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_libcfg.h"
#include "lpc43xx_cgu.h"
#include "lpc43xx_mcpwm.h"
#define LCD480272
//#define LCD800480
//#define LCD320240

#ifdef  LCD800480
#define LCD_WIDTH               800//320
#define LCD_HEIGHT            480// 240
#else
#ifdef LCD480272
#define LCD_WIDTH               320// 480
#define LCD_HEIGHT              240//272
#endif
#endif


#define BACKLIGHT_PORT          9
#define BACKLIGHT_PORT_PIN      4
#define BACKLIGHT_PORT_FUNC     FUNC4
#define BACKLIGHT_GPIO          5
#define BACKLIGHT_GPIO_PIN      17

#define LCD_VRAM_BASE_ADDR      0x28000000


void Lcd_Backlight(uint8_t en);
void Lcd_drive_Init(void);
int c_entry_lcd (void);
void Lcd_clear(void);
void Lcd_Backlight_change(void);
void MCOWM_set(MCPWM_CHANNEL_CFG_Type * channelSetup,char PWM);
void MCOWM_SetPWM(char PWM);

#endif/*__LCD_DRIVER_H__*/

