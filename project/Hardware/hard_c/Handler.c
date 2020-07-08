#include "Handler.h"


void SysTick_Handler (void) 					
{
	OSIntEnter();
	OSTimeTick(); 
	OSIntExit();
}



void Delay(void)
{
  volatile uint32_t i;
	
  for (i = 2000; i > 0; i--);
}

void wait_ms(uint8_t ms)
{
	uint32_t count=0x8888;
	while(ms>0)
	{
		for(; count != 0; count--);
		ms--;
	}
}
void wait(uint8_t s)
{
	uint32_t count=0x02FFFFFF;
	while(s>0)
	{
		for(; count != 0; count--);
		s--;
	}
}

void Delay_us(void)
{
  volatile uint32_t i;
	
  for (i = 10; i > 0; i--);
}

