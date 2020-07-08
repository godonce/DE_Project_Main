#ifndef _DAC_H_
#define _DAC_H_

#define PD0 0x00    //normal operation
#define PD1 0x01    //output 1k¦¸ to GND
#define PD2 0x02    //output 100k¦¸  to GND 
#define PD3 0x03    //High-z

/*DATASHEET P28*/
#define  DAC_GPIO              7
#define  DAC_GPIO_PIN          2

void Init_ADC(void);
//int c_entry_DAC(void);
void c_entry_DAC(int dac );
//DAC DAC73111DCKR
//Symbol   part   pin    definaction    description
//P9_2     N8     pin3   SSP0_MOSI      D[7]
//PE_2     M14    pin4   GPIO7[2]       D[4]
//P3_0     F13    pin5   SSP0_SCK       D[4]
#endif
