/*
********************************************************************************
*                            WIN_Context.h
*
* File          : WIN_Context.h
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     :
* Description   : 窗口调度头文件
*
* Date          : 2013/06/02
* History		:
*
*******************************************************************************/
#ifndef WIN_CONTEXT_H_INCLUDED
#define WIN_CONTEXT_H_INCLUDED

/****************   宏定义   **************************************************/
#define WIN_LEVEL_LAYER_COUNT               10      //窗口的最大层数
#define WIN_HIGH_LEVEL_LAYER_COUNT          4       //高级窗口的最大层数



/****************   函数声明   ************************************************/

int WIN_Enter(int *id);
//int WIN_Exit(int *result);
int WIN_Exit(int *result);
int WIN_Exit_Lv(int lvl);
//void WIN_ContextInit(void);
int WIN_Home(void);

int WIN_Refresh(void);
int WIN_AdvanceEnter(void *pNewMenu);
int WIN_AdvanceExit(void);



#endif // WIN_CONTEXT_H_INCLUDED
