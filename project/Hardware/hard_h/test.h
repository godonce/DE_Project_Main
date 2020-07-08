#ifndef  _TEST_H_
#define  _TEST_H_

#include "includes.h"
//extern uint8_t SPI_ReadWrite(LPC_SSPn_Type* SSPx,uint8_t data);
extern uint8_t SPI_ReadWrite(uint8_t data);
#define Marker 0x40
char ComputeCRC(char Byte0, char Byte1, char Byte2, char Byte3,char Byte4, char Byte5, char Byte6);
int c_entry_test1(void) ;
int c_entry_test2(void);
#endif 
