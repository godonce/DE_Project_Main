

#include "DIALOG.h"
#include "WIN_Tree.h"
#include "stdlib.h"
#include "stdio.h"


static ELEMENT *m_BiTreeRoot = NULL;     
static int m_StackSize = 0;


 StatusUI BT_InitBiTree(ELEMENT *T)
 {
     if (T == NULL)
         return TREE_ERROR;

     m_BiTreeRoot   = T;
     T->Lift        = NULL;
     T->Right       = NULL;

     return OK;
 }

#if 1
ELEMENT *BT_GetDataItem(DATA_TYPE *data)
{
    GUI_HMEM hMem;
    ELEMENT *p = NULL;

        hMem = GUI_ALLOC_AllocZero(sizeof(ELEMENT));

        p = (ELEMENT *)GUI_ALLOC_h2p(hMem);
    
    if (p != NULL)
    {
        p->data = data;
        p->Lift = NULL;
        p->Right = NULL;
        m_StackSize += sizeof(ELEMENT);
    }

    return p;
}
#endif
int BT_GetStackSize(void)
{
    return m_StackSize;
}


ELEMENT *BT_GetRoot(void)
{
    return m_BiTreeRoot;
}

ELEMENT *BT_GetLeftChild(ELEMENT *e)
{
    if (e == NULL)
        return TREE_ERROR;

    return e->Lift;
}

ELEMENT *BT_GetRightChild(ELEMENT *e)
{
    if (e == NULL)
        return TREE_ERROR;

    return e->Right;
}

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

StatusUI BT_InsertLChildElem(ELEMENT *e, ELEMENT *newE)
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

StatusUI BT_InsertRChildElem(ELEMENT *e, ELEMENT *newE)
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

         
StatusUI BT_DeleteLChildElem(ELEMENT *e, int l_R)
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
           
StatusUI BT_DeleteRChildElem(ELEMENT *e, int l_R)
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
StatusUI BT_AddChild(ELEMENT *e, ELEMENT *newE, int l_R)
{
    if (e == NULL)
        return TREE_ERROR;
    
    l_R?  (e->Lift = newE) :(e->Right = newE);
    
    return OK;
}

StatusUI BT_DeleteChild(ELEMENT *e, int l_R)
{
    if (e == NULL)
        return TREE_ERROR;
    
    l_R? (e->Lift = NULL) : (e->Right = NULL);
    
    return OK;
}

