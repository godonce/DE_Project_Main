#ifndef _Hand_H_
#define _Hand_H_
#include  "datafigures.h"
#include "lpc43xx_gpio.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_cgu.h"
//Symbol   part   pin    definaction    description
//PC_12     L6    pin6   GPIO6[11]      D[4]
//PD_10    P11    pin4   GPIO6[24]      D[4]


#define Hand_use_PORT          0xC
#define Hand_use_PIN           12
#define Hand_use_PORT_FUNC     FUNC4
#define Hand_use_GPIO          6
#define Hand_use_GPIO_PIN      11

#define Hand_unuse_PORT          0xD
#define Hand_unuse_PIN           10
#define Hand_unuse_PORT_FUNC     FUNC4
#define Hand_unuse_GPIO          6
#define Hand_unuse_GPIO_PIN      24



#define Poweron_PORT          0x09
#define Poweron_PIN           3
#define Poweron_PORT_FUNC     FUNC0
#define Poweron_GPIO          4
#define Poweron_GPIO_PIN      15

void hand_Init(void);
void poweron_Init(void);
int power_on(void);
int handdetection();

#endif