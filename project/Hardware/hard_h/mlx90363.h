#ifndef _MLX90363_H_
#define _MLX90363_H_

#include "includes.h"

#include "dataCRC.h"

#define  MLX_GPIO              7
#define  MLX_GPIO_PIN          15

#define KEY_ESCAPE   8
#define KEY_TAB  9
#define KEY_UP  17
#define KEY_DOWN  19
#define KEY_ENTER  13
#define KEY_ENTER_BEF  15

//char ComputeCRC(char Byte0, char Byte1, char Byte2, char Byte3,char Byte4, char Byte5, char Byte6);
void Init_MLX90363(void);
void c_entry_mlx_I(void);
char c_entry_mlx(void);

//MLX90363
//Symbol   part   pin    definaction    description
//P0_0     L3     pin2   SSP1_MISO      D[1]
//P1_19    M11    pin4   SSP1_SCK       D[1]
//PE_15    E13    pin5   GPIO7[15]      D[4]
//P0_1     M2     pin6   SSP1_MOSI      D[1]

#endif

