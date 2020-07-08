#include "SPI.h"
#include  "datafigures.h"

uint8_t SPI0_ReadWrite(uint8_t data)
{
  while(!(LPC_SSP0->SR & (1 << 1)));
  LPC_SSP0->DR = data;
  while(!(LPC_SSP0->SR & (1 << 0)));
  while(!(LPC_SSP0->SR & (1 << 2)));
  data = LPC_SSP0->DR;
 
  return data;	
}
uint8_t SPI1_ReadWrite(uint8_t data)
{
  while(!(LPC_SSP1->SR & (1 << 1)));
  LPC_SSP1->DR = data;
  while(!(LPC_SSP1->SR & (1 << 0)));
  while(!(LPC_SSP1->SR & (1 << 2)));
  data = LPC_SSP1->DR;
 
  return data;	
}

void Init_EESPI0(void)
{
		SSP_CFG_Type SSP_ConfigStruct;
		scu_pinmux(0x3, 0, MD_PLN_FAST, FUNC4); 
		scu_pinmux(0x9, 1, MD_PLN_FAST, FUNC7);  
		scu_pinmux(0x9, 2, MD_PLN_FAST, FUNC7); 	
		SSP_ConfigStructInit_SPI0_init(&SSP_ConfigStruct);
		SSP_Init(LPC_SSP0, &SSP_ConfigStruct);
		SSP_Cmd(LPC_SSP0, ENABLE);
		states.as=1;
		states.qw=0;
}
void Init_EESPI0_EN(void)
{
	SSP_CFG_Type SSP_ConfigStruct;
	SSP_ConfigStructInit_SPI0_init(&SSP_ConfigStruct);
	SSP_Init(LPC_SSP0, &SSP_ConfigStruct);
	SSP_Cmd(LPC_SSP0, ENABLE);
}
void Init_EESPI0_ADDA(void)
{
		SSP_CFG_Type SSP_ConfigStruct;
		scu_pinmux(0x3, 0, MD_PLN_FAST, FUNC4);  
		scu_pinmux(0x9, 1, MD_PLN_FAST, FUNC7);  
		scu_pinmux(0x9, 2, MD_PLN_FAST, FUNC7);  
	
		SSP_ConfigStructInit_SPI0(&SSP_ConfigStruct);
		SSP_Init(LPC_SSP0, &SSP_ConfigStruct);
		SSP_Cmd(LPC_SSP0, ENABLE);
		states.as=0;
		states.qw=1;
}
void Init_EESPI0_ADDA_EN(void)
{
		SSP_CFG_Type SSP_ConfigStruct;
		SSP_ConfigStructInit_SPI0(&SSP_ConfigStruct);
		SSP_Init(LPC_SSP0, &SSP_ConfigStruct);
		SSP_Cmd(LPC_SSP0, ENABLE);
}
void Init_SPI0(void)
{

		scu_pinmux(EEPROM_PORT, EEPROM_PIN, MD_PDN, EEPROM_DEF);  
		scu_pinmux(ADC_PORT, ADC_PIN, MD_PDN, ADC_DEF);  
		scu_pinmux(DAC_PORT, DAC_PIN, MD_PDN, DAC_DEF);  
	
		GPIO_SetDir(EEPROM_GPIO_PORT,(1 << EEPROM_GPIO_PIN), 1); 
		GPIO_SetDir(ADC_GPIO_PORT,(1 <<ADC_GPIO_PIN), 1);  
		GPIO_SetDir(DAC_GPIO_PORT,(1 << DAC_GPIO_PIN), 1);  
	
		GPIO_SetValue(EEPROM_GPIO_PORT,(1<<EEPROM_GPIO_PIN));
		GPIO_SetValue(ADC_GPIO_PORT,(1<<ADC_GPIO_PIN));
		GPIO_SetValue(DAC_GPIO_PORT,(1<<DAC_GPIO_PIN));

}
	
	
void states_spi0(int states)
{
	if(states==1)   
	{
		GPIO_ClearValue(EEPROM_GPIO_PORT,(1<<EEPROM_GPIO_PIN));
		GPIO_SetValue(ADC_GPIO_PORT,(1<<ADC_GPIO_PIN));
		GPIO_ClearValue(DAC_GPIO_PORT,(1<<DAC_GPIO_PIN));
		
	}else
	if(states==2)
	{
		GPIO_SetValue(EEPROM_GPIO_PORT,(1<<EEPROM_GPIO_PIN));
		GPIO_ClearValue(ADC_GPIO_PORT,(1<<ADC_GPIO_PIN));
		GPIO_ClearValue(DAC_GPIO_PORT,(1<<DAC_GPIO_PIN));
		
	}else
	if(states==3)  
	{
		GPIO_SetValue(EEPROM_GPIO_PORT,(1<<EEPROM_GPIO_PIN));
		GPIO_SetValue(ADC_GPIO_PORT,(1<<ADC_GPIO_PIN));
		GPIO_SetValue(DAC_GPIO_PORT,(1<<DAC_GPIO_PIN));
		
	}else     
	{
		GPIO_SetValue(EEPROM_GPIO_PORT,(1<<EEPROM_GPIO_PIN));
		GPIO_SetValue(ADC_GPIO_PORT,(1<<ADC_GPIO_PIN));
		GPIO_ClearValue(DAC_GPIO_PORT,(1<<DAC_GPIO_PIN));
		
	}	
}








