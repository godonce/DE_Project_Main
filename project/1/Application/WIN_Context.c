/*
********************************************************************************
*                            WIN_Context.c
*
* File          : WIN_Context.c
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     :
* Description   : 窗口调度操作
*
* Date          : 2013/06/02
* History		:
*
*******************************************************************************/

#include "WIN_Context.h"
//#include "WIN_OS.h"
#include "WIN.h"
#include "WinWindow.h"
#include "stdio.h"

/****************变量类型声明**************************************************/
typedef struct{
    MENU_INFO_ITEM  *menu;                  //窗口节点
    WIN_RETURN_TYPE ret;                   //上次返回值 上次所进入下级窗口时的ID
}ELEM_BLOCK_TYPE;

typedef struct {                            //普通窗口 根据节点所在位置显示
    ELEM_BLOCK_TYPE elem[WIN_LEVEL_LAYER_COUNT];
    int index;
}GENERIC_WIN_TYPE;

typedef struct {                            //高级窗口 不根据树决定，第一时间显示在最上层
    ELEM_BLOCK_TYPE elem[WIN_HIGH_LEVEL_LAYER_COUNT];
    int index;
}ADVANCE_WIN_TYPE;

/****************静态变量******************************************************/
GENERIC_WIN_TYPE m_WinList = {0};
ADVANCE_WIN_TYPE m_WinAdvaceList = {0};


//主要作用 是在高级窗口 和普通窗口切换时，避免出现循环重入问题。
static volatile char m_ReentrantTag = 0;


/*******************************************************************************
* Function Name :WIN_Home
* Description   :进入主界面
* Input         :int id:把进入的ID号
* Output        :void
* Other         :
* Date          :2013/06/02
*******************************************************************************/
int WIN_Home(void)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;
    MENU_INFO_ITEM *pCur = NULL;                    //当前的窗口
    int res = FALSE;
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index < 3)                       //窗口为最基础窗口或者不跨度
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)    //窗口深度 超出最大范围
        goto ext;

    if (m_WinAdvaceList.index > 0)                  //当前正显示高级窗口
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   //获得当前窗口
    pCur = pElem->menu;
    pInfo = m_WinList.elem[0].menu;                 //当前窗口的上一级窗口
    id = m_WinList.elem[0].ret.id;
    printf("WIN_Home id =%d \n",m_WinList.elem[0].ret.id);

    if (pCur == NULL)                               //当前窗口异常
        goto end;

    if (pCur->data == NULL)                         //当前窗口元素为空
        goto end;

    if (pInfo == NULL)                              //当前上一级窗口异常
        goto end;

    if (pInfo->data == NULL)                        //当前上一级窗口元素为空
        goto end;

    pElem->ret.id = 0;                              //清空进入的ID
    while(m_WinList.index > 1)
    {
        m_WinList.index--;
        m_WinList.elem[m_WinList.index].menu = NULL;    //删除列表中的窗口
        m_WinList.elem[m_WinList.index].ret.id = 0;    //删除列表中的窗口
    }

    if (pCur->data->win == NULL)                    //当前窗口无窗口数据
        goto end;

    if (pInfo->data->win == NULL)                   //上一级窗口无窗口数据
        goto end;

    if (pCur->data->win->destroy)                   //销毁当前窗口
        (*pCur->data->win->destroy)(NULL);

    if (pInfo->data->win->create)                   //上一级窗口建立
        (*pInfo->data->win->create)(pInfo);

end:
    //WIN_ContextUnlock();
//    if (result)                                     //有返回值
//    {
//        if (pCur->data->exit)                       //有回调函数
//        {
//            (*pCur->data->exit)(result);
//        }
//    }
//
//    m_ReentrantTag++;

    if (pInfo->data->enter)
    {
        (*pInfo->data->enter)(&id);
    }

    if (m_ReentrantTag > 0) m_ReentrantTag--;
    return  OK;

ext:
    //WIN_ContextUnlock();
    return FALSE;
}


/*******************************************************************************
* Function Name :WIN_Enter
* Description   :进入下一级窗口
* Input         :int id:把进入的ID号
* Output        :void
* Other         :
* Date          :2013/06/02
*******************************************************************************/
int WIN_Enter(int *id)
{
    ELEM_BLOCK_TYPE *pElem;
    MENU_INFO_ITEM *pInfo;
    MENU_INFO_ITEM *pCur;                           //当前的窗口

    //WIN_ContextLock();

    if (m_WinList.index < 1)                        //窗口调度没有初始化
        goto ext;

    if (m_WinList.index >= WIN_LEVEL_LAYER_COUNT - 1)   //窗口深度 超出最大范围
        goto ext;

    if (m_WinAdvaceList.index > 0)                  //当前正显示高级窗口
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   //获得当前窗口
    pCur = pInfo = pElem->menu;

    pInfo = BT_GetRightChild(pInfo);                //获取下级窗口
    pInfo = BT_GetLChildElem(pInfo, *id);

    if (pInfo == NULL)                              //无下级窗口
        goto ext;

    if (pInfo->data == NULL)                        //下级窗口元素为空
        goto ext;

    pElem->ret.id = *(int *)id;                     //保存所进入的ID

    //printf("pElem->ret.id=%d \n",pElem->ret.id);

    if (pInfo->data->win == NULL)                   //下级窗口无窗口数据
        goto end;

    if (pCur->data->win->destroy)                   //销毁当前窗口
        (*pCur->data->win->destroy)(NULL);

    if (pInfo->data->win->create)                   //新窗口建立
        (*pInfo->data->win->create)(pInfo);

    m_WinList.elem[m_WinList.index++].menu = pInfo; //保存新窗口到 窗口列表中

end:
    //WIN_ContextUnlock();

    m_ReentrantTag++;

    if (pInfo->data->enter)
    {
        *id = 100;
        (*pInfo->data->enter)(id);
    }

    if (m_ReentrantTag > 0) m_ReentrantTag--;
    return OK;

ext:
    //WIN_ContextUnlock();
    return FALSE;
}

/*******************************************************************************
* Function Name :WIN_Exit
* Description   :返回上一级窗口
* Input         :int result所退出窗口的返回值 为地址值 0表示无返回值
* Output        :void
* Other         :
* Date          :2013/06/02
*******************************************************************************/
int WIN_Exit(int *result)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;
    MENU_INFO_ITEM *pCur = NULL;                    //当前的窗口
    int res = FALSE;
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index <= 1)                       //窗口为最基础窗口
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)    //窗口深度 超出最大范围
        goto ext;

    if (m_WinAdvaceList.index > 0)                  //当前正显示高级窗口
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   //获得当前窗口
    pCur = pElem->menu;
    pInfo = m_WinList.elem[m_WinList.index - 2].menu;//当前窗口的上一级窗口
    id = m_WinList.elem[m_WinList.index - 2].ret.id;

    if (pCur == NULL)                               //当前窗口异常
        goto end;

    if (pCur->data == NULL)                         //当前窗口元素为空
        goto end;

    if (pInfo == NULL)                              //当前上一级窗口异常
        goto end;

    if (pInfo->data == NULL)                        //当前上一级窗口元素为空
        goto end;

    pElem->ret.id = 0;                              //清空进入的ID
    m_WinList.index--;
    m_WinList.elem[m_WinList.index].menu = NULL;    //删除列表中的窗口

    if (pCur->data->win == NULL)                    //当前窗口无窗口数据
        goto end;

    if (pInfo->data->win == NULL)                   //上一级窗口无窗口数据
        goto end;

    if (pCur->data->win->destroy)                   //销毁当前窗口
        (*pCur->data->win->destroy)(NULL);

    if (pInfo->data->win->create)                   //上一级窗口建立
        (*pInfo->data->win->create)(pInfo);
end:
    //WIN_ContextUnlock();

    if (result)                                     //有返回值
    {
        if (pCur->data->exit)                       //有回调函数
        {
            (*pCur->data->exit)(result);
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
    //WIN_ContextUnlock();
    return  res;
}


/*******************************************************************************
* Function Name :WIN_Refresh
* Description   :当前普通窗口刷新 (销毁再建立)
* Input         :void
* Output        :int
* Other         :
* Date          :2014/10/22
*******************************************************************************/
int WIN_Refresh(void)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;
    MENU_INFO_ITEM *pCur = NULL;                    //当前的窗口
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index <= 1)                       //窗口为最基础窗口
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)    //窗口深度 超出最大范围
        goto ext;

    if (m_WinAdvaceList.index > 0)                  //当前正显示高级窗口
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   //获得当前窗口
    pCur = pElem->menu;

    pInfo = m_WinList.elem[m_WinList.index - 2].menu;//当前窗口的上一级窗口
    id = m_WinList.elem[m_WinList.index - 2].ret.id;

    if (pCur == NULL)                               //当前窗口异常
        goto end;

    if (pCur->data == NULL)                         //当前窗口元素为空
        goto end;

    if (pInfo == NULL)                              //当前上一级窗口异常
        goto end;

    if (pInfo->data == NULL)                        //当前上一级窗口元素为空
        goto end;

    if (pCur->data->win == NULL)                    //当前窗口无窗口数据
        goto end;

    if (pCur->data->win->destroy)                   //销毁当前窗口
        (*pCur->data->win->destroy)(NULL);

    if (pCur->data->win->create)                    //当前窗口重新建立
        (*pCur->data->win->create)(pCur);
end:
    //WIN_ContextUnlock();

    m_ReentrantTag++;

    if (pInfo->data->enter)                         //当前窗口初始回调函数
    {
        (*pInfo->data->enter)(&id);
    }

    if (m_ReentrantTag > 0) m_ReentrantTag--;
    return  OK;

ext:
    //WIN_ContextUnlock();
    return  FALSE;
}

/*******************************************************************************
* Function Name :WIN_AdvanceEnter
* Description   :有高级窗口进入。有两种情况：
                    1)当前窗口是普通窗口，先销毁普通窗口
                    2)当前窗口是高级窗口，销毁当前高级窗口，再建立新窗口
* Input         :void * pNewMenu :新窗口元素
* Output        :int
* Other         :
* Date          :2014/10/22
*******************************************************************************/
int WIN_AdvanceEnter(void *pNewMenu)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = (MENU_INFO_ITEM *)pNewMenu; //新打开的窗口
    MENU_INFO_ITEM *pCur = NULL;                        //当前的窗口

    //WIN_ContextLock();
    if (m_WinList.index < 1)                            //窗口为最基础窗口
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)        //窗口深度 超出最大范围
        goto ext;

    if (m_WinAdvaceList.index >= WIN_HIGH_LEVEL_LAYER_COUNT)//高级窗口深度 超出最大范围
        goto ext;

    if (pInfo == NULL)                                  //新窗口异常
        goto end;

    if (pInfo->data == NULL)                            //新窗口元素为空
        goto end;

    if (0 == m_WinAdvaceList.index)
    {
        pElem = &m_WinList.elem[m_WinList.index - 1];   //获得当前窗口
    }
    else
    {
        pElem = &m_WinAdvaceList.elem[m_WinAdvaceList.index - 1];
    }

    pCur = pElem->menu;

    if (pCur == NULL)                                   //当前窗口异常
        goto end;

    if (pCur->data == NULL)                             //当前窗口元素为空
        goto end;

    if (pCur->data->win->destroy)                   //销毁当前窗口
        (*pCur->data->win->destroy)(NULL);


    if (pInfo->data->win->create)                       //新窗口建立
        (*pInfo->data->win->create)(pInfo);

    m_WinAdvaceList.elem[m_WinAdvaceList.index].ret.id = 0;
    m_WinAdvaceList.elem[m_WinAdvaceList.index++].menu = pInfo;      //保存新窗口到 窗口列表中
end:
    //WIN_ContextUnlock();

    if (pInfo->data->enter)
    {
        (*pInfo->data->enter)(NULL);
    }
    return  OK;

ext:
    //WIN_ContextUnlock();
    return  FALSE;
}

/*******************************************************************************
* Function Name :WIN_AdvanceExit
* Description   :高级窗口退出
* Input         :void
* Output        :int
* Other         :
* Date          :2014/10/23
*******************************************************************************/
int WIN_AdvanceExit(void)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;                       //上一级窗口
    MENU_INFO_ITEM *pCur = NULL;                        //当前的窗口
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index < 1)                            //窗口为最基础窗口
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)        //窗口深度 超出最大范围
        goto ext;

    if (m_WinAdvaceList.index < 1)                      //无高级窗口
        goto ext;

    if (m_WinAdvaceList.index > WIN_HIGH_LEVEL_LAYER_COUNT)         //窗口深度 超出最大范围
        goto ext;

    pElem = &m_WinAdvaceList.elem[m_WinAdvaceList.index - 1];       //获得当前窗口
    pCur = pElem->menu;

    if (pCur == NULL)                                   //当前窗口异常
        goto end;

    if (pCur->data == NULL)                             //当前窗口元素为空
        goto end;

    if (1 == m_WinAdvaceList.index)
    {
        pInfo = m_WinList.elem[m_WinList.index - 1].menu;           //高级窗口回退到普通级窗口
        id = m_WinList.elem[m_WinList.index - 1].ret.id;
    }
    else
    {
        pInfo = m_WinAdvaceList.elem[m_WinAdvaceList.index - 2].menu;//前一级窗口仍然是高级窗口
        id = m_WinAdvaceList.elem[m_WinAdvaceList.index - 2].ret.id;
    }

    if (pInfo == NULL)                                  //当前上一级窗口异常
        goto end;

    if (pInfo->data == NULL)                            //窗口元素为空
        goto end;

    if (pCur->data->win->destroy)                       //销毁当前高级窗口
        (*pCur->data->win->destroy)(NULL);

    if (pInfo->data->win->create)                       //上一级窗口建立
        (*pInfo->data->win->create)(pInfo);

    m_WinAdvaceList.elem[--m_WinAdvaceList.index].ret.id = 0;
    m_WinAdvaceList.elem[m_WinAdvaceList.index].menu = NULL;       //清除当前高级窗口列表
end:
    //WIN_ContextUnlock();

    //在普通窗口 Enter回调函数没有执行完的情况下，不再进入
    if (0 == m_ReentrantTag)
    {
        if (pInfo->data->enter)
        {
            (*pInfo->data->enter)(&id);
        }
    }

    return  OK;

ext:
    //WIN_ContextUnlock();
    return  FALSE;
}

/*******************************************************************************
* Function Name :WIN_ContextInit
* Description   :
* Input         :void
* Output        :void
* Other         :
* Date          :2013/06/02
*******************************************************************************/
void WIN_ContextInit(void)
{
    MENU_INFO_ITEM *pInfo = NULL;

    //WIN_ContextLock();

    pInfo = BT_GetRoot();

    if (pInfo)
    {
        m_WinList.elem[0].menu = pInfo;
        m_WinList.index = 1;

        if (pInfo->data->win->create)
            (*pInfo->data->win->create)(pInfo);
    }
    //WIN_ContextUnlock();
}




