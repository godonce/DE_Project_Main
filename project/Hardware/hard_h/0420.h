#ifndef _0420_H_
#define _0420_H_
#include "includes.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_gpio.h"
#include "lpc43xx_cgu.h"
#define PD0 0x00    //normal operation
#define PD1 0x01    //output 1k¦¸ to GND
#define PD2 0x02    //output 100k¦¸  to GND 
#define PD3 0x03    //High-z

/*DATASHEET P28*/
#define  DAC_GPIO              7
#define  DAC_GPIO_PIN          2

#define SSP0_SCK_PORT          3
#define SSP0_SCK_PORT_PIN      0
#define SSP0_SCK_PORT_FUNC     FUNC4

#define SSP0_MOSI_PORT          9
#define SSP0_MOSI_PORT_PIN      2
#define SSP0_MOSI_PORT_FUNC     FUNC7

#define SSP0_MISO_PORT          9
#define SSP0_MISO_PORT_PIN      1
#define SSP0_MISO_PORT_FUNC     FUNC7

#define EN_AI1_PORT          0xE
#define EN_AI1_PORT_PIN      1
#define EN_AI1_PORT_FUNC     FUNC4
#define EN_AI1_GPIO          7
#define EN_AI1_GPIO_PIN      1

#define EN_AO1_PORT          0xE
#define EN_AO1_PORT_PIN      2
#define EN_AO1_PORT_FUNC     FUNC4
#define EN_AO1_GPIO          7
#define EN_AO1_GPIO_PIN      2

void Init_Analog(void);
void c_entry_AO1(int dac );
short  c_entry_AI1(void);
void remote_control(void);
void remote_mode(void);

char remote_ctr(void);
void remote_EME(void);
void m0420_Read(void);
short READ_0420_remote(void);
//DAC DAC73111DCKR
//Symbol   part   pin    definaction    description
//P9_2     N8     pin3   SSP0_MOSI      D[7]
//PE_2     M14    pin4   GPIO7[2]       D[4]
//P3_0     F13    pin5   SSP0_SCK       D[4]
#endif