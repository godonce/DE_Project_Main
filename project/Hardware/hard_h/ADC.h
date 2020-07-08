#ifndef _ADC_H_
#define _ADC_H_

#define  ADC_GPIO              7
#define  ADC_GPIO_PIN          1
void Init_ADC(void);
float c_entry_ADC(void);

/*DATASHEET P17*/

//ADC ADS1018
//Symbol   part   pin    definaction    description
//P9_2     N8     pin3   SSP0_MOSI      D[7]
//PE_1     N14    pin4   GPIO7[1]       D[4]
//P3_0     F13    pin5   SSP0_SCK       D[4]
//P9_1     N6     pin6   SSP0_MISO      D[7]
#endif
