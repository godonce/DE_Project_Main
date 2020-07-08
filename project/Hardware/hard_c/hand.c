#include "hand.h"

void hand_Init(void)
{
	scu_pinmux(Hand_use_PORT ,Hand_use_PIN , MD_EZI, Hand_use_PORT_FUNC);
  GPIO_SetDir(Hand_use_GPIO,(1<<Hand_use_GPIO_PIN), 0);
	scu_pinmux(Hand_unuse_PORT ,Hand_unuse_PIN , MD_EZI, Hand_unuse_PORT_FUNC);
  GPIO_SetDir(Hand_unuse_GPIO,(1<<Hand_unuse_GPIO_PIN), 0);

  SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000);
}

void poweron_Init(void)
{
		scu_pinmux(Poweron_PORT ,Poweron_PIN , MD_EZI, Poweron_PORT_FUNC);
  GPIO_SetDir(Poweron_GPIO,(1<<Poweron_GPIO_PIN), 0);

  SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000);
}

int power_on(void)
{
	if(GPIO_ReadValue(Poweron_GPIO)&(1<<Poweron_GPIO_PIN))
	{
		return 0;
	}else
	{
		return 1;
	}
	
}

int handdetection()
{
	if(GPIO_ReadValue(Hand_use_GPIO)&(1<<Hand_use_GPIO_PIN))  
	{
		if(GPIO_ReadValue(Hand_unuse_GPIO)&(1<<Hand_unuse_GPIO_PIN))   
		{
			return 0;
		}else
		{
			return 1;
		}
	}else
	{
		if(GPIO_ReadValue(Hand_unuse_GPIO)&(1<<Hand_unuse_GPIO_PIN))
		{
			return 0;
		}else
		{
			return 0;
		}
	}

}
