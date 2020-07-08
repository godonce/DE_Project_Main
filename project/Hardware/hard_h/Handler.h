#ifndef Handler_H_
#define Handler_H_

#include "includes.h"
void SysTick_Handler (void);
void Delay(void);

void wait_ms(uint8_t ms);
void wait(uint8_t s);
void Delay_us(void);

#endif
