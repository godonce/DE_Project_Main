#ifndef _dataCRC_H_
#define _dataCRC_H_

#include "stdint.h"

char ComputeCRC(char Byte0, char Byte1, char Byte2, char Byte3,char Byte4, char Byte5, char Byte6);
uint16_t CRC_Compute(uint8_t *puchMsg, uint16_t usDataLen) ;

#endif