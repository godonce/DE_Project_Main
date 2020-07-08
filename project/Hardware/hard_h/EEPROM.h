#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "includes.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_gpio.h"
#include "lpc43xx_cgu.h"

#include "SPI.h"
#include "handler.h"
#include "dataCRC.h"
char WRITE_READ_EEPROM(char function,short  address,char data);
int states_EEPROM(void);
void read_eeprom(void);
void write_eeprom(void);
char *WRITE_READ_EEPROM_PAGE(char function,short address,uint32_t data[]);

#endif