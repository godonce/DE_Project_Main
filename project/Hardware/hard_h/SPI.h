#ifndef _SPI_H_
#define _SPI_H

#include "includes.h"

//#define  CS_GPIO              7
//#define  CS_GPIO_PIN          16


/*ENABLE*/
#define EN_PORT                0xE
#define EN_PIN                 15
/*GPIO7_15*/
#define EN_GPIO_PORT           7
#define EN_GPIO_PIN            15
//FUNC4

#define EEPROM_PORT               0x9
#define EEPROM_PIN                0
#define EEPROM_GPIO_PORT          4
#define EEPROM_GPIO_PIN           12
#define EEPROM_DEF                FUNC0

#define ADC_PORT               0xE
#define ADC_PIN                1
#define ADC_GPIO_PORT          7
#define ADC_GPIO_PIN           1
#define ADC_DEF                FUNC4

#define DAC_PORT               0xE
#define DAC_PIN                2
#define DAC_GPIO_PORT          7
#define DAC_GPIO_PIN           2
#define DAC_DEF                FUNC4


uint8_t SPI0_ReadWrite(uint8_t data);
uint8_t SPI1_ReadWrite(uint8_t data);

void Init_EESPI0(void);
void Init_SPI0(void);
void Init_EESPI0_ADDA(void);
void states_spi0(int states);
void Init_EESPI0_ADDA_EN(void);

void Init_EESPI0(void);
void Init_EESPI0_EN(void);
void Init_SPI0(void);
void states_spi0(int states);
//void SPI0_Init(void);
#endif
