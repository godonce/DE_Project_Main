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
* Description   : ������ һЩ��صĻ�������
*
* Date          : 2012/12/16
* History		: 
* 
*******************************************************************************/



#include "WIN_Tree.h"
#include "stdlib.h"
#include "stdio.h"

/******************************��̬����****************************************/

static ELEMENT *m_BiTreeRoot = NULL;     //�����
static int m_StackSize = 0;


 /*******************************************************************************
 * Function Name :BT_InitBiTree
 * Description   :��ʼ��������
 * Input         :ELEMENT * T:Ԫ�ص�ַ�� ����Ϊ��
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
* Description   :����һ��������
* Input         :DATA_TYPE * data ����
* Output        :ELEMENT * ������(���ڵ�)
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
* Description   :��ȡ�����öѿռ��С
* Output        :׵�ռ䣬�ֽ���
* Other         :
* Date          :2013/06/06
*******************************************************************************/
int BT_GetStackSize(void)
{
    return m_StackSize;
}


/*******************************************************************************
* Function Name :BT_GetRoot
* Description   :�������ĸ����
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
* Description   :���ظ�Ԫ�ص�����
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
* Description   :���ظ�Ԫ�ص��Һ���
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
* Description   :���ظ�Ԫ�ص��������
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
* Description   :���ظ�Ԫ�ص��Һ������
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
* Description   :���ظ�Ԫ�� ����number��ȵ�Ԫ��
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
* Description   :���ظ�Ԫ�� �Һ���number��ȵ�Ԫ��
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
* Description   :��Ԫ�ز��뵽��Ԫ�ص������ϣ���Ԫ��ԭ�ȵ�����ת��Ϊ�����ӵ�������
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
* Description   :��Ԫ�ز��뵽��Ԫ�ص��Һ����ϣ���Ԫ��ԭ�ȵ��Һ���ת��Ϊ���Һ��ӵ��Һ�����
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
* Description   :ɾ������ ����L_R����ɾ����Ԫ���������ӻ����Һ��Ӽ̳��丸Ԫ�ؽ��
* Input         :ELEMENT * e
* Input         :int l_R    0:�Һ��Ӽ̳�
*                           1:���Ӽ̳�
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
* Description   :ɾ���Һ��� ����L_R����ɾ����Ԫ���������ӻ����Һ��Ӽ̳��丸Ԫ�ؽ��
* Input         :ELEMENT * e
* Input         :int l_R    0:�Һ��Ӽ̳�
*                           1:���Ӽ̳�
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
* Description   :��Ԫ�ؼ��ص��ý��ĺ�����
* Input         :ELEMENT * e
* Input         :ELEMENT * newE
* Input         :int l_R    0:�Һ���
*                           1:����
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
* Description   :ɾ����Ԫ�ص�һ������(�����ú��ӵ����к���)
* Input         :ELEMENT * e
* Input         :int l_R    0:�Һ���
*                           1:����
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


