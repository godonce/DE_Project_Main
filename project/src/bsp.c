#include "lpc43xx.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_cgu.h"
#include <includes.h>
#include "lpc43xx_gpio.h"
INT32U  OS_CPU_SysTickClkFreq (void)
{
  INT32U  freq;

  freq = CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE);
  return (freq);
}

void  BSP_IntDisAll (void)
{
    CPU_IntDis();
}

void BSP_InitLED(void)
{
  scu_pinmux(LED1_PORT ,LED1_PIN , MD_PDN, FUNC0);
  GPIO_SetDir(LED1_GPIO_PORT,(1<<LED1_GPIO_PIN), 1);
}

void LED_Toggle(void)
{
  LPC_GPIO_PORT->NOT[LED1_GPIO_PORT] = (1 << LED1_GPIO_PIN);  
}


