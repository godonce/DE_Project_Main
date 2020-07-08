/**
  ******************************************************************************
  * <h2><center>&copy; COPYRIGHT 2012 Embest Tech. Co., Ltd.</center></h2>
  * @file    os_cfg.h 
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-February-2013
  * @brief   application configuration file.                       
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Embest SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
  * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
  * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  */
#ifndef __APP_CFG_H__
#define __APP_CFG_H__

/* Exported define -----------------------------------------------------------*/
#define  APP_OS_PROBE_EN                         DEF_DISABLED 

#define  APP_TASK_START_PRIO                               11
#define  APP_TASK_GUI_PRIO                                 6//9//6
#define  APP_TASK_States_PRIO                             7 //5
#define  APP_TASK_Touch_PRIO                               10
#define  APP_TASK_UART_PRIO                              	 5//7
#define  APP_TASK_UART2_PRIO                              9// 8//9
#define  APP_TASK_UART0_PRIO                               8//7//8
#define  OS_TASK_TMR_PRIO                (OS_LOWEST_PRIO - 2)

#define  APP_TASK_START_STK_SIZE                         512
#define  APP_TASK_States_STK_SIZE                        1024 // 512
#define  APP_TASK_GUI_STK_SIZE                           0xC00//0xA00
#define  APP_TASK_Touch_STK_SIZE                         512
#define  APP_TASK_UART_STK_SIZE                         512*2
#define  APP_TASK_UART0_STK_SIZE                         512*2
#define  APP_TASK_UART2_STK_SIZE                         1024//512


#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED

#endif /*__APP_CFG_H__*/
