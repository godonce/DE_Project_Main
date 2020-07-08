/*
********************************************************************************
*                            WIN_Context.h
*
* File          : WIN_Context.h
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     :
* Description   : ���ڵ���ͷ�ļ�
*
* Date          : 2013/06/02
* History		:
*
*******************************************************************************/
#ifndef WIN_CONTEXT_H_INCLUDED
#define WIN_CONTEXT_H_INCLUDED

/****************   �궨��   **************************************************/
#define WIN_LEVEL_LAYER_COUNT               10      //���ڵ�������
#define WIN_HIGH_LEVEL_LAYER_COUNT          4       //�߼����ڵ�������



/****************   ��������   ************************************************/

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
