#ifndef _temperature_H_
#define _temperature_H_
//Symbol   part   pin    definaction    description
//ADC0_1    C3     pin1   ADC0_1     D[4]
#include "lpc43xx_adc.h"
#include "lpc43xx_cgu.h"
#include "lpc43xx_libcfg.h"
#include "lpc43xx_gpdma.h"



void Init_DMA(void);
int ADC_temperature();

#endif