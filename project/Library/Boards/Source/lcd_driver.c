/**
  ******************************************************************************
  * <h2><center>&copy; COPYRIGHT 2012 Embest Tech. Co., Ltd.</center></h2>
  * @file    lcd_driver.c
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-December-2012
  * @brief   LCD  Initialization    
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
#include "lpc43xx_lcd.h"
#include "lpc43xx_gpio.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_libcfg.h"
#include "lpc43xx_cgu.h"
#include "lcd_driver.h"

/* LCD configured struct */
const LCD_CFG_Type lcd_cfg = {
  LCD_WIDTH,
  LCD_HEIGHT,
  {12,47},
  {8,24},
  2,
  2,
  1,
  LCD_SIGNAL_ACTIVE_LOW,
  LCD_SIGNAL_ACTIVE_LOW,
  LCD_CLK_RISING,
  LCD_SIGNAL_ACTIVE_HIGH,
  10,
  LCD_BPP16_565,
  LCD_TFT,
  LCD_COLOR_FORMAT_BGR,
  FALSE
};
/********************************************************************************
 * @brief       Initialization lcd
 * @param[in]	None
 * @return      None 
 *******************************************************************************/
void Lcd_drive_Init(void)
{
  uint32_t i;
  

  CGU_SetDIV(CGU_CLKSRC_IDIVE, 5);
  CGU_EntityConnect(CGU_CLKSRC_PLL1, CGU_CLKSRC_IDIVE);
  CGU_EntityConnect(CGU_CLKSRC_IDIVE,CGU_BASE_LCD);

  /*pin set up for LCD */
  scu_pinmux(0x07, 7, MD_PUP, FUNC3); 	/* LCD_PWR @ P7.7 */
  
  scu_pinmux(0x04, 7, MD_PUP, FUNC0);	/* LCD_DCLK @ P4.7 */
  scu_pinmux(0x04, 5, MD_PUP, FUNC2);	/* LCD_FP @ P4.5 */
  scu_pinmux(0x04, 6, MD_PUP, FUNC2); 	/* LCD_ENAB_M @ P4.6 */
  scu_pinmux(0x07, 6, MD_PUP, FUNC3);	/* LCD_LP @ P7.6 */
  scu_pinmux(0x04, 2, MD_PUP, FUNC2);	/* LCD_VD_3 @ P4.2 */
  scu_pinmux(0x08, 7, MD_PUP, FUNC3);	/* LCD_VD_4 @ P8.7 */
  scu_pinmux(0x08, 6, MD_PUP, FUNC3);	/* LCD_VD_5 @ P8.6 */
  scu_pinmux(0x08, 5, MD_PUP, FUNC3);	/* LCD_VD_6 @ P8.5 */
  scu_pinmux(0x08, 4, MD_PUP, FUNC3);	/* LCD_VD_7 @ P8.4 */
  scu_pinmux(0x04, 10, MD_PUP, FUNC2);	/* LCD_VD_10 @ P4.10 */
  scu_pinmux(0x04, 9, MD_PUP, FUNC2); 	/* LCD_VD_11 @ P4.9 */
  scu_pinmux(0x08, 3, MD_PUP, FUNC3); 	/* LCD_VD_12 @ P8.3 */
  scu_pinmux(0x0B, 6, MD_PUP, FUNC2); 	/* LCD_VD_13 @ PB.6 */
  scu_pinmux(0x0B, 5, MD_PUP, FUNC2); 	/* LCD_VD_14 @ PB.5 */
  scu_pinmux(0x0B, 4, MD_PUP, FUNC2); 	/* LCD_VD_15 @ PB.4 */
  scu_pinmux(0x07, 1, MD_PUP, FUNC3); 	/* LCD_VD_19 @ P7.1 */
  scu_pinmux(0x0B, 3, MD_PUP, FUNC2); 	/* LCD_VD_20 @ PB.3 */
  scu_pinmux(0x0B, 2, MD_PUP, FUNC2); 	/* LCD_VD_21 @ PB.2 */
  scu_pinmux(0x0B, 1, MD_PUP, FUNC2); 	/* LCD_VD_22 @ PB.1 */
  scu_pinmux(0x0B, 0, MD_PUP, FUNC2); 	/* LCD_VD_23 @ PB.0 */
  
  scu_pinmux(BACKLIGHT_PORT, BACKLIGHT_PORT_PIN, MD_PUP, BACKLIGHT_PORT_FUNC);

  GPIO_SetDir(BACKLIGHT_GPIO, 1 << BACKLIGHT_GPIO_PIN, 1);	


  GPIO_ClearValue(BACKLIGHT_GPIO, 1 << BACKLIGHT_GPIO_PIN);
  for(i=0;i<1000000;i++);

  LPC_RGU->RESET_CTRL0 = (1UL << 16);

  /* clear display memory */
  Lcd_clear();
  
  LPC43xx_LCD_Init(LPC_LCD, (LCD_CFG_Type*)&lcd_cfg);
  LCD_SetFrameBuffer(LPC_LCD, (void*)LCD_VRAM_BASE_ADDR);
  LCD_Power(LPC_LCD, ENABLE);
 
  for(i = 0; i < 1000000; i++);
  Lcd_Backlight(1);
}
/********************************************************************************
 * @brief       Enable LCD Backlight entity
 * @param[in]	en :   1     Enable backlight
 *                     0     Disable backlight
 * @return      None 
 *******************************************************************************/
void Lcd_Backlight(uint8_t en)
{
  if (en) {
    GPIO_SetValue(BACKLIGHT_GPIO, 1 << BACKLIGHT_GPIO_PIN); 
  } else {
    GPIO_ClearValue(BACKLIGHT_GPIO, 1 << BACKLIGHT_GPIO_PIN);  
  }
}

/********************************************************************************
 * @brief       clear display memory 
 * @param[in]	None
 * @return      None 
 *******************************************************************************/
void Lcd_clear(void)
{
  uint32_t i;
  uint32_t *pDst = (uint32_t *)LCD_VRAM_BASE_ADDR;
	
  for(i = 0; (LCD_WIDTH * LCD_HEIGHT / 2) > i; i++) {
    *pDst++ = 0;
  }
}

