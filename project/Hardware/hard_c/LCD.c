#include "lcd.h"
#include "Handler.h"

const LCD_CFG_Type lcd_cfg = {
  LCD_WIDTH,   //320
  LCD_HEIGHT,  //
  {20,68},//{HFP,HBP}
  {4,18},//{VFP,VBP}
  2,
  2,
  1,
  LCD_SIGNAL_ACTIVE_LOW,        //1
  LCD_SIGNAL_ACTIVE_LOW,        //1
	LCD_CLK_FALLING,               //0
	LCD_SIGNAL_ACTIVE_HIGH,       //0
  0,//10,
	LCD_BPP24,
  LCD_TFT,
  LCD_COLOR_FORMAT_RGB,
  FALSE
};
void Lcd_drive_Init(void)
{
    uint32_t i;
    CGU_SetDIV(CGU_CLKSRC_IDIVE,6);           
    CGU_EntityConnect(CGU_CLKSRC_PLL1, CGU_CLKSRC_IDIVE);    
    CGU_EntityConnect(CGU_CLKSRC_IDIVE,CGU_BASE_LCD);
    scu_pinmux(0x04, 6, MD_PUP, FUNC2); 	
    scu_pinmux(0x04, 5, MD_PUP, FUNC2);		
    scu_pinmux(0x07, 6, MD_PUP, FUNC3);		
    scu_pinmux(0x04, 7, MD_PUP, FUNC0);		
    scu_pinmux(0x04, 1, MD_PUP, FUNC2);		
    scu_pinmux(0x04, 4, MD_PUP, FUNC2);		
    scu_pinmux(0x04, 3, MD_PUP, FUNC2);		
    scu_pinmux(0x04, 2, MD_PUP, FUNC2);		
    scu_pinmux(0x08, 7, MD_PUP, FUNC3);		
    scu_pinmux(0x08, 6, MD_PUP, FUNC3);		
    scu_pinmux(0x08, 5, MD_PUP, FUNC3);		
    scu_pinmux(0x07, 1, MD_PUP, FUNC4);		
    scu_pinmux(0x07, 5, MD_PUP, FUNC3);		
    scu_pinmux(0x04, 8, MD_PUP, FUNC2);		
    scu_pinmux(0x04,10, MD_PUP, FUNC2);	  
    scu_pinmux(0x04, 9, MD_PUP, FUNC2); 	
    scu_pinmux(0x08, 3, MD_PUP, FUNC3); 	
    scu_pinmux(0x04, 0, MD_PUP, FUNC5); 	
    scu_pinmux(0x0B, 5, MD_PUP, FUNC2); 	
    scu_pinmux(0x0B, 4, MD_PUP, FUNC2); 	
    scu_pinmux(0x08, 4, MD_PUP, FUNC4);		
    scu_pinmux(0x07, 3, MD_PUP, FUNC3);		
    scu_pinmux(0x07, 2, MD_PUP, FUNC3);		
    scu_pinmux(0x0B, 6, MD_PUP, FUNC6); 	 
    scu_pinmux(0x0B, 3, MD_PUP, FUNC2); 	
    scu_pinmux(0x0B, 2, MD_PUP, FUNC2); 	
    scu_pinmux(0x0B, 1, MD_PUP, FUNC2); 	
    scu_pinmux(0x0B, 0, MD_PUP, FUNC2); 
    scu_pinmux(5, 4, MD_PDN,      FUNC1);  
    scu_pinmux(9, 4, MD_PDN,      FUNC1);  
    MCPWM_Init(LPC_MCPWM);
    MCOWM_SetPWM(10);
    LPC_RGU->RESET_CTRL0 = (1UL << 16);
    Lcd_clear();
    LPC43xx_LCD_Init(LPC_LCD, (LCD_CFG_Type*)&lcd_cfg);
    LCD_SetFrameBuffer(LPC_LCD, (void*)LCD_VRAM_BASE_ADDR);
    LCD_Power(LPC_LCD, ENABLE);
	
}

void Lcd_Backlight(uint8_t en)
{
  if (en) 
	{
    GPIO_SetValue(BACKLIGHT_GPIO, 1 << BACKLIGHT_GPIO_PIN); 
  } else 
	{
    GPIO_ClearValue(BACKLIGHT_GPIO, 1 << BACKLIGHT_GPIO_PIN);  
  }
}

void Lcd_clear(void)
{
  uint32_t i;
  uint32_t *pDst = (uint32_t *)LCD_VRAM_BASE_ADDR;
  for(i = 0; (LCD_WIDTH * LCD_HEIGHT / 2) > i; i++) 
	{
    *pDst++ = 0;
  }
}

int c_entry_lcd (void) 
{                     
  SystemInit();
  Lcd_drive_Init();
  while (1) {
	Lcd_Backlight(1);
  }
	
}

void Lcd_Backlight_change(void)
{ 
    GPIO_SetValue(BACKLIGHT_GPIO, 1 << BACKLIGHT_GPIO_PIN); 
	Delay();
	Delay();
    GPIO_ClearValue(BACKLIGHT_GPIO, 1 << BACKLIGHT_GPIO_PIN); 
	Delay_us();

}

void MCOWM_set(MCPWM_CHANNEL_CFG_Type * channelSetup,char PWM)
{
	
			channelSetup->channelType=MCPWM_CHANNEL_EDGE_MODE;
			channelSetup->channelPolarity=MCPWM_CHANNEL_PASSIVE_HI;
			channelSetup->channelDeadtimeEnable=DISABLE;
			channelSetup->channelDeadtimeValue=100;
			channelSetup->channelUpdateEnable	=ENABLE;
			channelSetup->channelTimercounterValue=0;   
			channelSetup->channelPeriodValue=500000;        
			channelSetup->channelPulsewidthValue=5000*PWM;
}


void MCOWM_SetPWM(char PWM)
{
	MCPWM_CHANNEL_CFG_Type CHANNEL_MCPWM;
	MCOWM_set(&CHANNEL_MCPWM,PWM);
	MCPWM_ConfigChannel(LPC_MCPWM,0,&CHANNEL_MCPWM);
	MCPWM_WriteToShadow(LPC_MCPWM,0,&CHANNEL_MCPWM);	
	MCPWM_DCMode(LPC_MCPWM,ENABLE,DISABLE,MCPWM_PATENT_B0);
	MCPWM_Start(LPC_MCPWM,ENABLE,DISABLE,DISABLE);
	
}