#include "0420.h"
#include "SPI.h"

void Init_DAC(void)
{
		SSP_CFG_Type SSP_ConfigStruct;
		scu_pinmux(0x3, 0, MD_PLN_FAST, FUNC1); 
		scu_pinmux(0x9, 2, MD_PLN_FAST, FUNC1);  
		scu_pinmux(0xE, 2, MD_PDN,      FUNC4);       
		GPIO_SetDir(DAC_GPIO,(1 << DAC_GPIO_PIN), 1); 
		
		SSP_ConfigStructInit(&SSP_ConfigStruct);
		SSP_Init(LPC_SSP0, &SSP_ConfigStruct);
		SSP_Cmd(LPC_SSP0, ENABLE);
		GPIO_SetValue(DAC_GPIO,(1<<DAC_GPIO_PIN));
}


