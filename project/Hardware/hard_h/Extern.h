#ifndef _Extern_H_
#define _Extern_H_
#include "includes.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_gpio.h"
#include "lpc43xx_cgu.h"



#define ExClose_PORT          0xC
#define ExClose_PORT_PIN      10
#define ExClose_PORT_FUNC     FUNC4
#define ExClose_GPIO          6
#define ExClose_GPIO_PIN      9

#define ExOpen_PORT          0xD
#define ExOpen_PORT_PIN      1
#define ExOpen_PORT_FUNC     FUNC4
#define ExOpen_GPIO          6
#define ExOpen_GPIO_PIN      15

#define ExStop_PORT          8
#define ExStop_PORT_PIN      2
#define ExStop_PORT_FUNC     FUNC0
#define ExStop_GPIO          4
#define ExStop_GPIO_PIN      2

#define ExEme_PORT          0xC
#define ExEme_PORT_PIN      13
#define ExEme_PORT_FUNC     FUNC4
#define ExEme_GPIO          6
#define ExEme_GPIO_PIN      12

#define ExMod_PORT          0xE
#define ExMod_PORT_PIN      14
#define ExMod_PORT_FUNC     FUNC4
#define ExMod_GPIO          7
#define ExMod_GPIO_PIN      14
#if 0
#define ExOUT1_PORT          0xC   //F6
#define ExOUT1_PORT_PIN      2
#define ExOUT1_PORT_FUNC     FUNC4
#define ExOUT1_GPIO          6
#define ExOUT1_GPIO_PIN      1


#define ExOUT2_PORT          0xC  //F4
#define ExOUT2_PORT_PIN      4
#define ExOUT2_PORT_FUNC     FUNC4
#define ExOUT2_GPIO          6
#define ExOUT2_GPIO_PIN      3

#define ExOUT3_PORT          0xC   //G4
#define ExOUT3_PORT_PIN      5
#define ExOUT3_PORT_FUNC     FUNC4
#define ExOUT3_GPIO          6
#define ExOUT3_GPIO_PIN      4

#define ExOUT4_PORT          0xC//0xD  E4
#define ExOUT4_PORT_PIN      1//11
#define ExOUT4_PORT_FUNC     FUNC4
#define ExOUT4_GPIO          6
#define ExOUT4_GPIO_PIN      0//25
#endif
#if 1
#define ExOUT2_PORT          0xC   //F6
#define ExOUT2_PORT_PIN      2
#define ExOUT2_PORT_FUNC     FUNC4
#define ExOUT2_GPIO          6
#define ExOUT2_GPIO_PIN      1


#define ExOUT3_PORT          0xC  //F4
#define ExOUT3_PORT_PIN      4
#define ExOUT3_PORT_FUNC     FUNC4
#define ExOUT3_GPIO          6
#define ExOUT3_GPIO_PIN      3

#define ExOUT4_PORT          0xC   //G4
#define ExOUT4_PORT_PIN      5
#define ExOUT4_PORT_FUNC     FUNC4
#define ExOUT4_GPIO          6
#define ExOUT4_GPIO_PIN      4

#define ExOUT1_PORT          0xC//0xD  E4
#define ExOUT1_PORT_PIN      1//11
#define ExOUT1_PORT_FUNC     FUNC4
#define ExOUT1_GPIO          6
#define ExOUT1_GPIO_PIN      0//25
#endif
#define ExOUT5_PORT          0xC   //H6
#define ExOUT5_PORT_PIN      6
#define ExOUT5_PORT_FUNC     FUNC4
#define ExOUT5_GPIO          6
#define ExOUT5_GPIO_PIN      5

#define ExOUT6_PORT          0xC  //G5
#define ExOUT6_PORT_PIN      7
#define ExOUT6_PORT_FUNC     FUNC4
#define ExOUT6_GPIO          6
#define ExOUT6_GPIO_PIN      6

#define ExOUT7_PORT          0xC  //N4
#define ExOUT7_PORT_PIN      8
#define ExOUT7_PORT_FUNC     FUNC4
#define ExOUT7_GPIO          6
#define ExOUT7_GPIO_PIN      7

#define ExOUT8_PORT          0xC  //K2
#define ExOUT8_PORT_PIN      9
#define ExOUT8_PORT_FUNC     FUNC4
#define ExOUT8_GPIO          6
#define ExOUT8_GPIO_PIN      8

#define ExEN_PORT          0xD  //
#define ExEN_PORT_PIN      11
#define ExEN_PORT_FUNC     FUNC4
#define ExEN_GPIO          6
#define ExEN_GPIO_PIN      25

void ExternIN_Init(void);
void ExternOUT_Init(void);
void Extern_out(void);
void Extern_in(void);

void Extern_out_set(void);
void Extern_out_ONOFF(void);
void Extern_out0(void);
void Extern_out1(void);
void Extern_out2(void);
void Extern_out3(void);
void Extern_out4(void);
void Extern_out5(void);
void Extern_out6(void);
void Extern_out7(void);


void Extern_out0_ex(void);
void Extern_out1_ex(void);
void Extern_out2_ex(void);
void Extern_out3_ex(void);
void Extern_out4_ex(void);
void Extern_out5_ex(void);
void Extern_out6_ex(void);
void Extern_out7_ex(void);

void SET_IO_Extern(void);
void SET_Extern(void);

void Extern_set(void);
void Extern_set_IO(void);
#endif
