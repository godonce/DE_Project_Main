#ifndef _LED_H_
#define _LED_H_

#include "includes.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_gpio.h"
#include "lpc43xx_cgu.h"
/*PD_14*/
#define LED1_PORT               0xD
#define LED1_PIN                14
/*GPIO2_1*/
#define LED1_GPIO_PORT          6
#define LED1_GPIO_PIN           28
/*P4_1*/
#define LED2_PORT               4
#define LED2_PIN                1
/*GPIO2_1*/
#define LED2_GPIO_PORT          2
#define LED2_GPIO_PIN           1
/*PE_14*/


#define Open_PORT               0xE
#define Open_PIN                0
#define Open_GPIO_PORT          7
#define Open_GPIO_PIN           0
#define Open_PORT_FUNC          FUNC4

#define Local_PORT               0xE
#define Local_PIN                3
#define Local_GPIO_PORT          7
#define Local_GPIO_PIN           3
#define Local_PORT_FUNC          FUNC4

#define PC_PORT               0xC
#define PC_PIN                11
#define PC_GPIO_PORT          6
#define PC_GPIO_PIN           10
#define PC_PORT_FUNC          FUNC4

#define Close_PORT               6
#define Close_PIN                1
#define Close_GPIO_PORT          3
#define Close_GPIO_PIN           0
#define Close_PORT_FUNC          FUNC0

void Init_LED(void);
int c_entry_led (void) ;

void Init_States(void);
void c_entry_states (void) ;

void c_entry_OPEN(void);
void c_entry_LOCAL(void);
void c_entry_PC(void);
void c_entry_CLOSE(void);
void c_entry_allclose(void);

void c_enty_allclose_pc_local();
void c_enty_allclose_close_open();


void c_entry_LOCAL1(void);
void c_entry_LOCAL2(void);


void RUN_CLOSE (void) ;
void RUN_OPEN (void) ;
#endif
