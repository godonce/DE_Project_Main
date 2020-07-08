/*
********************************************************************************
*
*                                 WIN_Tree
*
* File          : WIN_Tree.c
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     :                      
* Description   : 二叉树 一些相关的基本操作
*
* Date          : 2012/12/16
* History		: 
* 
*******************************************************************************/



#include "WIN_Tree.h"
#include "stdlib.h"
#include "stdio.h"

/******************************静态变量****************************************/

static ELEMENT *m_BiTreeRoot = NULL;     //根结点
static int m_StackSize = 0;


 /*******************************************************************************
 * Function Name :BT_InitBiTree
 * Description   :初始化二叉树
 * Input         :ELEMENT * T:元素地址， 不可为空
 * Output        :Status
 * Other         :
 * Date          :2012/12/16
 *******************************************************************************/
 Status BT_InitBiTree(ELEMENT *T)
 {
     if (T == NULL)
         return TREE_ERROR;

     m_BiTreeRoot   = T;
     T->Lift        = NULL;
     T->Right       = NULL;

     return OK;
 }

/*******************************************************************************
* Function Name :BT_GetDataItem
* Description   :开辟一个数据项
* Input         :DATA_TYPE * data 数据
* Output        :ELEMENT * 数据项(树节点)
* Other         :
* Date          :2013/06/06
*******************************************************************************/
ELEMENT *BT_GetDataItem(DATA_TYPE *data)
{
    ELEMENT *p = NULL;

    p = (ELEMENT *)malloc(sizeof(ELEMENT));
    if (p != NULL)
    {
        p->data = data;
        p->Lift = NULL;
        p->Right = NULL;
        m_StackSize += sizeof(ELEMENT);
    }

    return p;
}

/*******************************************************************************
* Function Name :BT_GetStackSize
* Description   :读取树所用堆空间大小
* Output        :椎空间，字节数
* Other         :
* Date          :2013/06/06
*******************************************************************************/
int BT_GetStackSize(void)
{
    return m_StackSize;
}


/*******************************************************************************
* Function Name :BT_GetRoot
* Description   :返回树的根结点
* Input         :void
* Output        :ELEMENT *
* Other         :
* Date          :2012/12/16
*******************************************************************************/
ELEMENT *BT_GetRoot(void)
{
    return m_BiTreeRoot;
}

/*******************************************************************************
* Function Name :BT_GetLeftChild
* Description   :返回该元素的左孩子
* Input         :ELEMENT * e
* Output        :ELEMENT *
* Other         :
* Date          :2012/12/16
*******************************************************************************/
ELEMENT *BT_GetLeftChild(ELEMENT *e)
{
    if (e == NULL)
        return TREE_ERROR;

    return e->Lift;
}

/*******************************************************************************
* Function Name :BT_GetRightChild
* Description   :返回该元素的右孩子
* Input         :ELEMENT * e
* Output        :ELEMENT *
* Other         :
* Date          :2012/12/16
*******************************************************************************/
ELEMENT *BT_GetRightChild(ELEMENT *e)
{
    if (e == NULL)
        return TREE_ERROR;

    return e->Right;
}

/*******************************************************************************
* Function Name :BT_GetLeftDepth
* Description   :返回该元素的左孩子深度
* Input         :ELEMENT * e
* Output        :int
* Other         :
* Date          :2012/12/16
*******************************************************************************/
int BT_GetLeftDepth(ELEMENT *e)
{
    ELEMENT *p;
    int     iDepth = 0;

    if (e == NULL)
        return TREE_ERROR;
    
    p = e;
    while (p)
    {
        iDepth++;
        p = p->Lift;

        if (iDepth >= ADT_MAX_NUM)
            return OVERFLOW;
    }

    return iDepth;
}

/*******************************************************************************
* Function Name :BT_GetRightDepth
* Description   :返回该元素的右孩子深度
* Input         :ELEMENT * e
* Output        :int
* Other         :
* Date          :2012/12/16
*******************************************************************************/
int BT_GetRightDepth(ELEMENT *e)
{
    ELEMENT *p;
    int     iDepth = 0;

    if (e == NULL)
        return TREE_ERROR;
    
    p = e;
    while (p)
    {
        iDepth++;
        p = p->Right;

        if (iDepth >= ADT_MAX_NUM)
            return OVERFLOW;
    }

    return iDepth;
}


/*******************************************************************************
* Function Name :BT_GetLChildElem
* Description   :返回该元素 左孩子number深度的元素
* Input         :ELEMENT * e
* Input         :int number
* Output        :ELEMENT *
* Other         :
* Date          :2013/06/06
*******************************************************************************/
ELEMENT *BT_GetLChildElem(ELEMENT *e, int number)
{
    ELEMENT *p;
    int     i = 0;

    if (e == NULL)
        return TREE_ERROR;

    p = e;
    while (p && (i < number))
    {
        p = p->Lift;
        i++;
    }

    if (p == NULL)
        return TREE_ERROR;

    return p;
}

/*******************************************************************************
* Function Name :BT_GetRChildElem
* Description   :返回该元素 右孩子number深度的元素
* Input         :ELEMENT * e
* Input         :int number 
* Output        :ELEMENT *
* Other         :
* Date          :2012/12/16
*******************************************************************************/
ELEMENT *BT_GetRChildElem(ELEMENT *e, int number)
{
    ELEMENT *p;
    int     i = 0;

    if (e == NULL)
        return TREE_ERROR;

    p = e;
    while (p && (i < number))
    {
        p = p->Right;
        i++;
    }

    if (p == NULL)
        return TREE_ERROR;

    return p;
}

/*******************************************************************************
* Function Name :BT_InsertLChildElem
* Description   :新元素插入到该元素的左孩子上，该元素原先的左孩子转换为现左孩子的左孩子上
* Input         :ELEMENT * e
* Input         :ELEMENT * newE
* Output        :Status
* Other         :
* Date          :2012/12/16
*******************************************************************************/
Status BT_InsertLChildElem(ELEMENT *e, ELEMENT *newE)
{
    ELEMENT *p;

    if (e == NULL)
        return TREE_ERROR;

    if (newE == NULL)
        return TREE_ERROR;

    p           = e->Lift;
    e->Lift     = newE;
    newE->Lift  = p;
    newE->Right = NULL;

    return OK;
}

/*******************************************************************************
* Function Name :BT_InsertRChildElem
* Description   :新元素插入到该元素的右孩子上，该元素原先的右孩子转换为现右孩子的右孩子上
* Input         :ELEMENT * e
* Input         :ELEMENT * newE
* Output        :Status
* Other         :
* Date          :2013/06/06
*******************************************************************************/
Status BT_InsertRChildElem(ELEMENT *e, ELEMENT *newE)
{
    ELEMENT *p;

    if (e == NULL)
        return TREE_ERROR;

    if (newE == NULL)
        return TREE_ERROR;

    p           = e->Right;
    e->Right    = newE;
    newE->Right = p;
    newE->Lift  = NULL;

    return OK;
}

         
/*******************************************************************************
* Function Name :BT_DeleteLChildElem
* Description   :删除左孩子 根据L_R决定删除的元素由其左孩子还是右孩子继承其父元素结点
* Input         :ELEMENT * e
* Input         :int l_R    0:右孩子继承
*                           1:左孩子继承
* Output        :Status
* Other         :
* Date          :2012/12/16
*******************************************************************************/
Status BT_DeleteLChildElem(ELEMENT *e, int l_R)
{
    ELEMENT *p;

    if (e == NULL)
        return TREE_ERROR;

    if (e->Lift == NULL)
        return OK;

    p = e->Lift;
    l_R? (e->Lift = p->Lift) : (e->Lift = p->Right);

    return OK;
}
           
/*******************************************************************************
* Function Name :BT_DeleteRChildElem
* Description   :删除右孩子 根据L_R决定删除的元素由其左孩子还是右孩子继承其父元素结点
* Input         :ELEMENT * e
* Input         :int l_R    0:右孩子继承
*                           1:左孩子继承
* Output        :Status
* Other         :
* Date          :2012/12/16
*******************************************************************************/
Status BT_DeleteRChildElem(ELEMENT *e, int l_R)
{
    ELEMENT *p;

    if (e == NULL)
        return TREE_ERROR;

    if (e->Right == NULL)
        return OK;

    p = e->Right;
    l_R? (e->Right = p->Lift) : (e->Right = p->Right);

    return OK;
}

/*******************************************************************************
* Function Name :BT_AddChild
* Description   :新元素加载到该结点的孩子上
* Input         :ELEMENT * e
* Input         :ELEMENT * newE
* Input         :int l_R    0:右孩子
*                           1:左孩子
* Output        :Status
* Other         :
* Date          :2012/12/16
*******************************************************************************/
Status BT_AddChild(ELEMENT *e, ELEMENT *newE, int l_R)
{
    if (e == NULL)
        return TREE_ERROR;
    
    l_R?  (e->Lift = newE) :(e->Right = newE);
    
    return OK;
}

/*******************************************************************************
* Function Name :BT_DeleteChild
* Description   :删除该元素的一个孩子(包括该孩子的所有孩子)
* Input         :ELEMENT * e
* Input         :int l_R    0:右孩子
*                           1:左孩子
* Output        :Status
* Other         :
* Date          :2012/12/16
*******************************************************************************/
Status BT_DeleteChild(ELEMENT *e, int l_R)
{
    if (e == NULL)
        return TREE_ERROR;
    
    l_R? (e->Lift = NULL) : (e->Right = NULL);
    
    return OK;
}


