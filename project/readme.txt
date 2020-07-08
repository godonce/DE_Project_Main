/**
  @page Camera
1、四个LED等闪烁完成
2、显示屏点亮但不正确   V4.0

USART3调试OK 
显示屏OK

10.15_设置堵转OK

GUI_SetBkColor(GUI_WHITE);

FRAMEWIN_SetClientColor(m_WinLocalOp.hFrame,GUI_WHITE);
FRAMEWIN_SetClientColor(m_CommonMenu.hFrame,GUI_WHITE);//WY change background to white 20181031 NJ
灏卞湴鎿嶄綔鑳借В鏀惧牭杞?
按键检测OK


--主菜单
  --用户管理
  --观察
  --诊断
  --末端位置
  --参数
  --力矩曲线
  --与系统有关的设定
  



16.1:
	鎸夐挳娣诲姞鍒板洓涓姸鎬侊細escape銆丒NTER_BEF銆乀AB銆丒NTER
	
	
	11.23_1:
	ceshi kongge keyi 

"lpc43xx_uart.h"       #define UART_TX_FIFO_SIZE		(16)--->#define UART_TX_FIFO_SIZE		(8)




  @verbatim
  *********************** COPYRIGHT 2013 Embest Tech. Co., Ltd.*****************
  * @file    readme.txt 
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-February-2013
  * @brief   Example description file
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
  @endverbatim
  */

@Example description:
  Purpose:
    This example describes how to use the uCOS-II v2.91 and emWin5.18 on EDM1070N-1TR embeded display module.
  Process:
    After reset, LEDs will be blinking and LCD display emWin Demo.

					
@Directory contents:
  - \Keil: includes Keil project and configuration files  

  - \EWARM: includes IAR project and configuration files  
  
  - "inc": contains the project firmware header files    
    - lpc43xx_libcfg.h:        Library configuration file - include needed driver library for this example 
    - bsp.h                    Heard for bsp.c
    - app_cfg.h                Application configuration file.
    - os_cfg.h                 uc/os-ii configuration file.
    - includes.h               Library header file.
    - lib.h                    library functions and define    
	
  - "src": contains the project firmware source files  
    - main.c:                  Main program
    - bsp.c                    board support package.

@par Hardware and Software environment

  - This example has been tested with the following environment: 
    - EDM1043N-1TR Board
    - EDM1070N-1TR Board

  - Software development tools
    - EWARM V6.40 with J-Link v9.1
    - MDK-ARM V4.60 with ULINK2
      						
  - Running mode:
    - On Keil
      - Internal Flash mode:    This example can run on Internal Flash mode.
    - On IAR
      - Internal Flash mode:    This example can run on Internal Flash mode.
		
@par How to use it ?
  1. Download uC/OS-II-v2.91 source code.
     You can get it on the Micrium website.As below:
     http://micrium.com/page/downloads/source_code
     Copy uC/OS-II-v2.91 source from the Micrium folder(Micrium\Software\uCOS-II\Source) to Project folder(STM32F4xx_uCOSII_Example\uCOS-II\Source).
     
  2. Load the demonstration code in the LPC4357 Flash memory (see below)

  In order to load the Project code, you have do the following:
   - EWARM
      - Open the Project.eww workspace
      - Rebuild all files: Project->Rebuild all
      - Load project image: Project->Debug
      - Run program: Debug->Go(F5)
      
   - MDK-ARM
      - Open the Project.uvproj project
      - Rebuild all files: Project->Rebuild all target files
      - Load project image: Debug->Start/Stop Debug Session
      - Run program: Debug->Run (F5)    
  

/**************** COPYRIGHT 2013 Embest Tech. Co., Ltd.*******END OF FILE******/

Program Size: Code=282916 RO-data=565876 RW-data=49260 ZI-data=47608  


#ifdef Encnew
		#elif  Encold
		#endif
