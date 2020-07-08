/*
********************************************************************************
*
*                                 WIN_Tree
*
* File          : WIN_Tree.h
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     :                      
* Description   : 数据抽象宏定义
*                   用户数据的类型可以宏定义DATA_TYPE
* Date          : 2012/12/16
* History		: 
* 
*******************************************************************************/
#if 0
#ifndef _ADT_H_
#define _ADT_H_


#define ADT_MAX_NUM 50              //最大深度50  超出会报溢出错误

#ifndef DATA_TYPE               
#define DATA_TYPE   void
#endif



#ifndef NULL
#define NULL            ((void *)0)
#endif

#ifndef OK
#define OK              1
#endif

#ifndef TREE_ERROR
#define TREE_ERROR      0
#endif

#ifndef INFEASIBLE
#define INFEASIBLE      -1
#endif

#ifndef OVERFLOW
#define OVERFLOW        -2
#endif

#define BT_RIGHT        0
#define BT_LEFT         1

typedef int         Status;
 
typedef struct BiTreeElem{
    DATA_TYPE           *data;
    struct BiTreeElem   *Lift;
    struct BiTreeElem   *Right;
}ELEMENT;




 Status BT_InitBiTree(ELEMENT *T);
 ELEMENT *BT_GetRoot(void);
 ELEMENT *BT_GetLeftChild(ELEMENT *e);
 ELEMENT *BT_GetRightChild(ELEMENT *e);
 int BT_GetLeftDepth(ELEMENT *e);
 int BT_GetRightDepth(ELEMENT *e);
 ELEMENT *BT_GetLChildElem(ELEMENT *e, int number);
 ELEMENT *BT_GetRChildElem(ELEMENT *e, int number);
 Status BT_InsertLChildElem(ELEMENT *e, ELEMENT *newE);
 Status BT_InsertRChildElem(ELEMENT *e, ELEMENT *newE);
 Status BT_DeleteLChildElem(ELEMENT *e, int l_R);
 Status BT_DeleteRChildElem(ELEMENT *e, int l_R);
 Status BT_AddChild(ELEMENT *e, ELEMENT *newE, int l_R);
 Status BT_DeleteChild(ELEMENT *e, int l_R);

 ELEMENT *BT_GetDataItem(DATA_TYPE *data);
 int BT_GetStackSize(void);
#endif
#endif


#if 1
/*
********************************************************************************
*
*                                 WIN_Tree
*
* File          : WIN_Tree.h
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     :                      
* Description   : 数据抽象宏定义
*                   用户数据的类型可以宏定义DATA_TYPE
* Date          : 2012/12/16
* History		: 
* 
*******************************************************************************/

#ifndef _ADT_H_
#define _ADT_H_

#define ADT_MAX_NUM 50              //最大深度50  超出会报溢出错误

#ifndef DATA_TYPE               
#define DATA_TYPE   void
#endif



#ifndef NULL
#define NULL            ((void *)0)
#endif

#ifndef OK
#define OK              1
#endif

#ifndef TREE_ERROR
#define TREE_ERROR      0
#endif

#ifndef INFEASIBLE
#define INFEASIBLE      -1
#endif

#ifndef OVERFLOW
#define OVERFLOW        -2
#endif

#define BT_RIGHT        0
#define BT_LEFT         1

//#ifndef _lpc_types_h
//#define _lpc_types_h

//#endif

typedef int         StatusUI;

typedef struct BiTreeElem{
    DATA_TYPE           *data;
    struct BiTreeElem   *Lift;
    struct BiTreeElem   *Right;
}ELEMENT;




 StatusUI BT_InitBiTree(ELEMENT *T);
 ELEMENT *BT_GetRoot(void);
 ELEMENT *BT_GetLeftChild(ELEMENT *e);
 ELEMENT *BT_GetRightChild(ELEMENT *e);
 int BT_GetLeftDepth(ELEMENT *e);
 int BT_GetRightDepth(ELEMENT *e);
 ELEMENT *BT_GetLChildElem(ELEMENT *e, int number);
 ELEMENT *BT_GetRChildElem(ELEMENT *e, int number);
 StatusUI BT_InsertLChildElem(ELEMENT *e, ELEMENT *newE);
 StatusUI BT_InsertRChildElem(ELEMENT *e, ELEMENT *newE);
 StatusUI BT_DeleteLChildElem(ELEMENT *e, int l_R);
 StatusUI BT_DeleteRChildElem(ELEMENT *e, int l_R);
 StatusUI BT_AddChild(ELEMENT *e, ELEMENT *newE, int l_R);
 StatusUI BT_DeleteChild(ELEMENT *e, int l_R);

 ELEMENT *BT_GetDataItem(DATA_TYPE *data);
 int BT_GetStackSize(void);
#endif




#endif

