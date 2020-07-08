#include "DIALOG.h"
#include "WIN_Context.h"
//#include "WIN_OS.h"
#include "WIN.h"
#include "WinWindow.h"
#include "stdio.h"

#pragma  diag_suppress 177 

typedef struct{
    MENU_INFO_ITEM  *menu;                
    WIN_RETURN_TYPE ret;                  
}ELEM_BLOCK_TYPE;

typedef struct {                           
    ELEM_BLOCK_TYPE elem[WIN_LEVEL_LAYER_COUNT];
    int index;
}GENERIC_WIN_TYPE;

typedef struct {                            
    ELEM_BLOCK_TYPE elem[WIN_HIGH_LEVEL_LAYER_COUNT];
    int index;
}ADVANCE_WIN_TYPE;

GENERIC_WIN_TYPE m_WinList = {0};
ADVANCE_WIN_TYPE m_WinAdvaceList = {0};


static volatile char m_ReentrantTag = 0;


int WIN_Home(void)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;
    MENU_INFO_ITEM *pCur = NULL;                   
    int res = FALSE;
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index < 3)                       
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)   
        goto ext;

    if (m_WinAdvaceList.index > 0)                 
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];  
    pCur = pElem->menu;
    pInfo = m_WinList.elem[0].menu;                
    id = m_WinList.elem[0].ret.id;

    if (pCur == NULL)                              
        goto end;

    if (pCur->data == NULL)                        
        goto end;

    if (pInfo == NULL)                             
        goto end;

    if (pInfo->data == NULL)                       
        goto end;

    pElem->ret.id = 0;                             
    while(m_WinList.index > 1)
    {
        m_WinList.index--;
        m_WinList.elem[m_WinList.index].menu = NULL;   
        m_WinList.elem[m_WinList.index].ret.id = 0;    
    }

    if (pCur->data->win == NULL)                   
        goto end;

    if (pInfo->data->win == NULL)                  
        goto end;

    if (pCur->data->win->destroy)                  
        (*pCur->data->win->destroy)(NULL);

    if (pInfo->data->win->create)                  
        (*pInfo->data->win->create)(pInfo);

end:


    if (pInfo->data->enter)
    {
        (*pInfo->data->enter)(&id);
    }

    if (m_ReentrantTag > 0) m_ReentrantTag--;
    return  OK;

ext:
    return FALSE;
}


int WIN_Enter(int *id)
{
    ELEM_BLOCK_TYPE *pElem;
    MENU_INFO_ITEM *pInfo;
    MENU_INFO_ITEM *pCur;                          

    //WIN_ContextLock();

    if (m_WinList.index < 1)                       
        goto ext;

    if (m_WinList.index >= WIN_LEVEL_LAYER_COUNT - 1)  
        goto ext;

    if (m_WinAdvaceList.index > 0)                  
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   
    pCur = pInfo = pElem->menu;

    pInfo = BT_GetRightChild(pInfo);                
    pInfo = BT_GetLChildElem(pInfo, *id);

    if (pInfo == NULL)                              
        goto ext;

    if (pInfo->data == NULL)                        
        goto ext;

    pElem->ret.id = *(int *)id;                     

    if (pInfo->data->win == NULL)                   
        goto end;

    if (pCur->data->win->destroy)                   
        (*pCur->data->win->destroy)(NULL);
    GUI_Exec1();
    if (pInfo->data->win->create)                   
        (*pInfo->data->win->create)(pInfo);
    GUI_Exec1();
    m_WinList.elem[m_WinList.index++].menu = pInfo; 

end:

    m_ReentrantTag++;

    if (pInfo->data->enter)
    {
        *id = 100;
        (*pInfo->data->enter)(id);
    }

    if (m_ReentrantTag > 0) m_ReentrantTag--;
    return OK;

ext:
    return FALSE;
}


int WIN_Exit(int *result)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;
    MENU_INFO_ITEM *pCur = NULL;                    
    int res = FALSE;
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index <= 1)                       
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)    
        goto ext;

    if (m_WinAdvaceList.index > 0)                  
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   
    pCur = pElem->menu;
    pInfo = m_WinList.elem[m_WinList.index - 2].menu;
    id = m_WinList.elem[m_WinList.index - 2].ret.id;

    if (pCur == NULL)                               
        goto end;

    if (pCur->data == NULL)                         
        goto end;

    if (pInfo == NULL)                              
        goto end;

    if (pInfo->data == NULL)                        
        goto end;

    pElem->ret.id = 0;                              
    m_WinList.index--;
    m_WinList.elem[m_WinList.index].menu = NULL;    

    if (pCur->data->win == NULL)                    
        goto end;

    if (pInfo->data->win == NULL)                   
        goto end;

    if (pCur->data->win->destroy)                   
        (*pCur->data->win->destroy)(NULL);
    //GUI_Exec1();  //删除此处的刷新，以免回退的时候出现闪屏
    if (pInfo->data->win->create)                   
        (*pInfo->data->win->create)(pInfo);
    //GUI_Exec1();  //删除此处的刷新，以免回退的时候出现闪屏
end:
    //WIN_ContextUnlock();

    if (result)                                     
    {
        if (pCur->data->exit)                       
        {
            (*pCur->data->exit)((char *)result);
        }
    }

    m_ReentrantTag++;

    if (pInfo->data->enter)
    {
        (*pInfo->data->enter)(&id);
    }

    if (m_ReentrantTag > 0) m_ReentrantTag--;
    return  OK;

ext:
    return  res;
}

/**************************************************************************
* 函数名称： WIN_Exit_Lv
* 功能描述： 从当前界面回退lvl级界面
* 输入参数： lvl回退级数，根据二叉树中的结构
* 输出参数： 
* 返 回 值： 
* 其它说明： zxc 20200707
**************************************************************************/
int WIN_Exit_Lv(int lvl)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;
    MENU_INFO_ITEM *pCur = NULL;                    
    int res = FALSE;
    int id = 0;
    int i = 0;

    if (m_WinList.index <= 1)                       
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)    
        goto ext;

    if (m_WinAdvaceList.index > 0)                  
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   
    pCur = pElem->menu;
    pInfo = m_WinList.elem[m_WinList.index - 1 - lvl].menu;
    id = m_WinList.elem[m_WinList.index - 1 - lvl].ret.id;

    if (pCur == NULL)                               
        goto end;

    if (pCur->data == NULL)                         
        goto end;

    if (pInfo == NULL)                              
        goto end;

    if (pInfo->data == NULL)                        
        goto end;
    
    pElem->ret.id = 0;
    while(i < lvl)
    {
        m_WinList.index--;
        m_WinList.elem[m_WinList.index].menu = NULL;    
        i ++;
    }
    
    if (pCur->data->win == NULL)                    
        goto end;

    if (pInfo->data->win == NULL)                   
        goto end;

    if (pCur->data->win->destroy)                   
        (*pCur->data->win->destroy)(NULL);
    if (pInfo->data->win->create)                   
        (*pInfo->data->win->create)(pInfo);
end:

    m_ReentrantTag++;

    if (pInfo->data->enter)
    {
        (*pInfo->data->enter)(&id);
    }

    if (m_ReentrantTag > 0) m_ReentrantTag--;
    return  OK;

ext:
    return  res;
}


int WIN_Refresh(void)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;
    MENU_INFO_ITEM *pCur = NULL;                    
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index <= 1)                       
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)    
        goto ext;

    if (m_WinAdvaceList.index > 0)                  
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   
    pCur = pElem->menu;

    pInfo = m_WinList.elem[m_WinList.index - 2].menu;
    id = m_WinList.elem[m_WinList.index - 2].ret.id;

    if (pCur == NULL)                              
        goto end;

    if (pCur->data == NULL)                        
        goto end;

    if (pInfo == NULL)                             
        goto end;

    if (pInfo->data == NULL)                       
        goto end;

    if (pCur->data->win == NULL)                   
        goto end;

    if (pCur->data->win->destroy)                  
        (*pCur->data->win->destroy)(NULL);

    if (pCur->data->win->create)                   
        (*pCur->data->win->create)(pCur);
end:
    //WIN_ContextUnlock();

    m_ReentrantTag++;

    if (pInfo->data->enter)                        
    {
        (*pInfo->data->enter)(&id);
    }

    if (m_ReentrantTag > 0) m_ReentrantTag--;
    return  OK;

ext:
    return  FALSE;
}

int WIN_AdvanceEnter(void *pNewMenu)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = (MENU_INFO_ITEM *)pNewMenu; 
    MENU_INFO_ITEM *pCur = NULL;                        

    if (m_WinList.index < 1)                            
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)        
        goto ext;

    if (m_WinAdvaceList.index >= WIN_HIGH_LEVEL_LAYER_COUNT)
        goto ext;

    if (pInfo == NULL)                                 
        goto end;

    if (pInfo->data == NULL)                           
        goto end;

    if (0 == m_WinAdvaceList.index)
    {
        pElem = &m_WinList.elem[m_WinList.index - 1];  
    }
    else
    {
        pElem = &m_WinAdvaceList.elem[m_WinAdvaceList.index - 1];
    }

    pCur = pElem->menu;

    if (pCur == NULL)                              
        goto end;

    if (pCur->data == NULL)                        
        goto end;

    if (pCur->data->win->destroy)                  
        (*pCur->data->win->destroy)(NULL);


    if (pInfo->data->win->create)                  
        (*pInfo->data->win->create)(pInfo);

    m_WinAdvaceList.elem[m_WinAdvaceList.index].ret.id = 0;
    m_WinAdvaceList.elem[m_WinAdvaceList.index++].menu = pInfo;      
end:

    if (pInfo->data->enter)
    {
        (*pInfo->data->enter)(NULL);
    }
    return  OK;

ext:
    return  FALSE;
}

int WIN_AdvanceExit(void)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;                      
    MENU_INFO_ITEM *pCur = NULL;                       
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index < 1)                           
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)       
        goto ext;

    if (m_WinAdvaceList.index < 1)                     
        goto ext;

    if (m_WinAdvaceList.index > WIN_HIGH_LEVEL_LAYER_COUNT)        
        goto ext;

    pElem = &m_WinAdvaceList.elem[m_WinAdvaceList.index - 1];      
    pCur = pElem->menu;

    if (pCur == NULL)                                  
        goto end;

    if (pCur->data == NULL)                            
        goto end;

    if (1 == m_WinAdvaceList.index)
    {
        pInfo = m_WinList.elem[m_WinList.index - 1].menu;           
        id = m_WinList.elem[m_WinList.index - 1].ret.id;
    }
    else
    {
        pInfo = m_WinAdvaceList.elem[m_WinAdvaceList.index - 2].menu;
        id = m_WinAdvaceList.elem[m_WinAdvaceList.index - 2].ret.id;
    }

    if (pInfo == NULL)                                
        goto end;

    if (pInfo->data == NULL)                          
        goto end;

    if (pCur->data->win->destroy)                     
        (*pCur->data->win->destroy)(NULL);

    if (pInfo->data->win->create)                     
        (*pInfo->data->win->create)(pInfo);

    m_WinAdvaceList.elem[--m_WinAdvaceList.index].ret.id = 0;
    m_WinAdvaceList.elem[m_WinAdvaceList.index].menu = NULL;      
end:
    if (0 == m_ReentrantTag)
    {
        if (pInfo->data->enter)
        {
            (*pInfo->data->enter)(&id);
        }
    }

    return  OK;

ext:
    return  FALSE;
}


void WIN_ContextInit(void)
{
    MENU_INFO_ITEM *pInfo = NULL;
    pInfo = BT_GetRoot();

    if (pInfo)
    {
        m_WinList.elem[0].menu = pInfo;
        m_WinList.index = 1;

        if (pInfo->data->win->create)
            (*pInfo->data->win->create)(pInfo);
    }
}


