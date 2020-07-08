/*
********************************************************************************
*                            WIN_Context.c
*
* File          : WIN_Context.c
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     :
* Description   : ���ڵ��Ȳ���
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

/****************������������**************************************************/
typedef struct{
    MENU_INFO_ITEM  *menu;                  //���ڽڵ�
    WIN_RETURN_TYPE ret;                   //�ϴη���ֵ �ϴ��������¼�����ʱ��ID
}ELEM_BLOCK_TYPE;

typedef struct {                            //��ͨ���� ���ݽڵ�����λ����ʾ
    ELEM_BLOCK_TYPE elem[WIN_LEVEL_LAYER_COUNT];
    int index;
}GENERIC_WIN_TYPE;

typedef struct {                            //�߼����� ����������������һʱ����ʾ�����ϲ�
    ELEM_BLOCK_TYPE elem[WIN_HIGH_LEVEL_LAYER_COUNT];
    int index;
}ADVANCE_WIN_TYPE;

/****************��̬����******************************************************/
GENERIC_WIN_TYPE m_WinList = {0};
ADVANCE_WIN_TYPE m_WinAdvaceList = {0};


//��Ҫ���� ���ڸ߼����� ����ͨ�����л�ʱ���������ѭ���������⡣
static volatile char m_ReentrantTag = 0;


/*******************************************************************************
* Function Name :WIN_Home
* Description   :����������
* Input         :int id:�ѽ����ID��
* Output        :void
* Other         :
* Date          :2013/06/02
*******************************************************************************/
int WIN_Home(void)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;
    MENU_INFO_ITEM *pCur = NULL;                    //��ǰ�Ĵ���
    int res = FALSE;
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index < 3)                       //����Ϊ��������ڻ��߲����
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)    //������� �������Χ
        goto ext;

    if (m_WinAdvaceList.index > 0)                  //��ǰ����ʾ�߼�����
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   //��õ�ǰ����
    pCur = pElem->menu;
    pInfo = m_WinList.elem[0].menu;                 //��ǰ���ڵ���һ������
    id = m_WinList.elem[0].ret.id;
    printf("WIN_Home id =%d \n",m_WinList.elem[0].ret.id);

    if (pCur == NULL)                               //��ǰ�����쳣
        goto end;

    if (pCur->data == NULL)                         //��ǰ����Ԫ��Ϊ��
        goto end;

    if (pInfo == NULL)                              //��ǰ��һ�������쳣
        goto end;

    if (pInfo->data == NULL)                        //��ǰ��һ������Ԫ��Ϊ��
        goto end;

    pElem->ret.id = 0;                              //��ս����ID
    while(m_WinList.index > 1)
    {
        m_WinList.index--;
        m_WinList.elem[m_WinList.index].menu = NULL;    //ɾ���б��еĴ���
        m_WinList.elem[m_WinList.index].ret.id = 0;    //ɾ���б��еĴ���
    }

    if (pCur->data->win == NULL)                    //��ǰ�����޴�������
        goto end;

    if (pInfo->data->win == NULL)                   //��һ�������޴�������
        goto end;

    if (pCur->data->win->destroy)                   //���ٵ�ǰ����
        (*pCur->data->win->destroy)(NULL);

    if (pInfo->data->win->create)                   //��һ�����ڽ���
        (*pInfo->data->win->create)(pInfo);

end:
    //WIN_ContextUnlock();
//    if (result)                                     //�з���ֵ
//    {
//        if (pCur->data->exit)                       //�лص�����
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
* Description   :������һ������
* Input         :int id:�ѽ����ID��
* Output        :void
* Other         :
* Date          :2013/06/02
*******************************************************************************/
int WIN_Enter(int *id)
{
    ELEM_BLOCK_TYPE *pElem;
    MENU_INFO_ITEM *pInfo;
    MENU_INFO_ITEM *pCur;                           //��ǰ�Ĵ���

    //WIN_ContextLock();

    if (m_WinList.index < 1)                        //���ڵ���û�г�ʼ��
        goto ext;

    if (m_WinList.index >= WIN_LEVEL_LAYER_COUNT - 1)   //������� �������Χ
        goto ext;

    if (m_WinAdvaceList.index > 0)                  //��ǰ����ʾ�߼�����
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   //��õ�ǰ����
    pCur = pInfo = pElem->menu;

    pInfo = BT_GetRightChild(pInfo);                //��ȡ�¼�����
    pInfo = BT_GetLChildElem(pInfo, *id);

    if (pInfo == NULL)                              //���¼�����
        goto ext;

    if (pInfo->data == NULL)                        //�¼�����Ԫ��Ϊ��
        goto ext;

    pElem->ret.id = *(int *)id;                     //�����������ID

    //printf("pElem->ret.id=%d \n",pElem->ret.id);

    if (pInfo->data->win == NULL)                   //�¼������޴�������
        goto end;

    if (pCur->data->win->destroy)                   //���ٵ�ǰ����
        (*pCur->data->win->destroy)(NULL);

    if (pInfo->data->win->create)                   //�´��ڽ���
        (*pInfo->data->win->create)(pInfo);

    m_WinList.elem[m_WinList.index++].menu = pInfo; //�����´��ڵ� �����б���

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
* Description   :������һ������
* Input         :int result���˳����ڵķ���ֵ Ϊ��ֵַ 0��ʾ�޷���ֵ
* Output        :void
* Other         :
* Date          :2013/06/02
*******************************************************************************/
int WIN_Exit(int *result)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;
    MENU_INFO_ITEM *pCur = NULL;                    //��ǰ�Ĵ���
    int res = FALSE;
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index <= 1)                       //����Ϊ���������
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)    //������� �������Χ
        goto ext;

    if (m_WinAdvaceList.index > 0)                  //��ǰ����ʾ�߼�����
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   //��õ�ǰ����
    pCur = pElem->menu;
    pInfo = m_WinList.elem[m_WinList.index - 2].menu;//��ǰ���ڵ���һ������
    id = m_WinList.elem[m_WinList.index - 2].ret.id;

    if (pCur == NULL)                               //��ǰ�����쳣
        goto end;

    if (pCur->data == NULL)                         //��ǰ����Ԫ��Ϊ��
        goto end;

    if (pInfo == NULL)                              //��ǰ��һ�������쳣
        goto end;

    if (pInfo->data == NULL)                        //��ǰ��һ������Ԫ��Ϊ��
        goto end;

    pElem->ret.id = 0;                              //��ս����ID
    m_WinList.index--;
    m_WinList.elem[m_WinList.index].menu = NULL;    //ɾ���б��еĴ���

    if (pCur->data->win == NULL)                    //��ǰ�����޴�������
        goto end;

    if (pInfo->data->win == NULL)                   //��һ�������޴�������
        goto end;

    if (pCur->data->win->destroy)                   //���ٵ�ǰ����
        (*pCur->data->win->destroy)(NULL);

    if (pInfo->data->win->create)                   //��һ�����ڽ���
        (*pInfo->data->win->create)(pInfo);
end:
    //WIN_ContextUnlock();

    if (result)                                     //�з���ֵ
    {
        if (pCur->data->exit)                       //�лص�����
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
* Description   :��ǰ��ͨ����ˢ�� (�����ٽ���)
* Input         :void
* Output        :int
* Other         :
* Date          :2014/10/22
*******************************************************************************/
int WIN_Refresh(void)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;
    MENU_INFO_ITEM *pCur = NULL;                    //��ǰ�Ĵ���
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index <= 1)                       //����Ϊ���������
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)    //������� �������Χ
        goto ext;

    if (m_WinAdvaceList.index > 0)                  //��ǰ����ʾ�߼�����
        goto ext;

    pElem = &m_WinList.elem[m_WinList.index - 1];   //��õ�ǰ����
    pCur = pElem->menu;

    pInfo = m_WinList.elem[m_WinList.index - 2].menu;//��ǰ���ڵ���һ������
    id = m_WinList.elem[m_WinList.index - 2].ret.id;

    if (pCur == NULL)                               //��ǰ�����쳣
        goto end;

    if (pCur->data == NULL)                         //��ǰ����Ԫ��Ϊ��
        goto end;

    if (pInfo == NULL)                              //��ǰ��һ�������쳣
        goto end;

    if (pInfo->data == NULL)                        //��ǰ��һ������Ԫ��Ϊ��
        goto end;

    if (pCur->data->win == NULL)                    //��ǰ�����޴�������
        goto end;

    if (pCur->data->win->destroy)                   //���ٵ�ǰ����
        (*pCur->data->win->destroy)(NULL);

    if (pCur->data->win->create)                    //��ǰ�������½���
        (*pCur->data->win->create)(pCur);
end:
    //WIN_ContextUnlock();

    m_ReentrantTag++;

    if (pInfo->data->enter)                         //��ǰ���ڳ�ʼ�ص�����
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
* Description   :�и߼����ڽ��롣�����������
                    1)��ǰ��������ͨ���ڣ���������ͨ����
                    2)��ǰ�����Ǹ߼����ڣ����ٵ�ǰ�߼����ڣ��ٽ����´���
* Input         :void * pNewMenu :�´���Ԫ��
* Output        :int
* Other         :
* Date          :2014/10/22
*******************************************************************************/
int WIN_AdvanceEnter(void *pNewMenu)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = (MENU_INFO_ITEM *)pNewMenu; //�´򿪵Ĵ���
    MENU_INFO_ITEM *pCur = NULL;                        //��ǰ�Ĵ���

    //WIN_ContextLock();
    if (m_WinList.index < 1)                            //����Ϊ���������
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)        //������� �������Χ
        goto ext;

    if (m_WinAdvaceList.index >= WIN_HIGH_LEVEL_LAYER_COUNT)//�߼�������� �������Χ
        goto ext;

    if (pInfo == NULL)                                  //�´����쳣
        goto end;

    if (pInfo->data == NULL)                            //�´���Ԫ��Ϊ��
        goto end;

    if (0 == m_WinAdvaceList.index)
    {
        pElem = &m_WinList.elem[m_WinList.index - 1];   //��õ�ǰ����
    }
    else
    {
        pElem = &m_WinAdvaceList.elem[m_WinAdvaceList.index - 1];
    }

    pCur = pElem->menu;

    if (pCur == NULL)                                   //��ǰ�����쳣
        goto end;

    if (pCur->data == NULL)                             //��ǰ����Ԫ��Ϊ��
        goto end;

    if (pCur->data->win->destroy)                   //���ٵ�ǰ����
        (*pCur->data->win->destroy)(NULL);


    if (pInfo->data->win->create)                       //�´��ڽ���
        (*pInfo->data->win->create)(pInfo);

    m_WinAdvaceList.elem[m_WinAdvaceList.index].ret.id = 0;
    m_WinAdvaceList.elem[m_WinAdvaceList.index++].menu = pInfo;      //�����´��ڵ� �����б���
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
* Description   :�߼������˳�
* Input         :void
* Output        :int
* Other         :
* Date          :2014/10/23
*******************************************************************************/
int WIN_AdvanceExit(void)
{
    ELEM_BLOCK_TYPE *pElem = NULL;
    MENU_INFO_ITEM *pInfo = NULL;                       //��һ������
    MENU_INFO_ITEM *pCur = NULL;                        //��ǰ�Ĵ���
    int id = 0;

    //WIN_ContextLock();
    if (m_WinList.index < 1)                            //����Ϊ���������
        goto ext;

    if (m_WinList.index > WIN_LEVEL_LAYER_COUNT)        //������� �������Χ
        goto ext;

    if (m_WinAdvaceList.index < 1)                      //�޸߼�����
        goto ext;

    if (m_WinAdvaceList.index > WIN_HIGH_LEVEL_LAYER_COUNT)         //������� �������Χ
        goto ext;

    pElem = &m_WinAdvaceList.elem[m_WinAdvaceList.index - 1];       //��õ�ǰ����
    pCur = pElem->menu;

    if (pCur == NULL)                                   //��ǰ�����쳣
        goto end;

    if (pCur->data == NULL)                             //��ǰ����Ԫ��Ϊ��
        goto end;

    if (1 == m_WinAdvaceList.index)
    {
        pInfo = m_WinList.elem[m_WinList.index - 1].menu;           //�߼����ڻ��˵���ͨ������
        id = m_WinList.elem[m_WinList.index - 1].ret.id;
    }
    else
    {
        pInfo = m_WinAdvaceList.elem[m_WinAdvaceList.index - 2].menu;//ǰһ��������Ȼ�Ǹ߼�����
        id = m_WinAdvaceList.elem[m_WinAdvaceList.index - 2].ret.id;
    }

    if (pInfo == NULL)                                  //��ǰ��һ�������쳣
        goto end;

    if (pInfo->data == NULL)                            //����Ԫ��Ϊ��
        goto end;

    if (pCur->data->win->destroy)                       //���ٵ�ǰ�߼�����
        (*pCur->data->win->destroy)(NULL);

    if (pInfo->data->win->create)                       //��һ�����ڽ���
        (*pInfo->data->win->create)(pInfo);

    m_WinAdvaceList.elem[--m_WinAdvaceList.index].ret.id = 0;
    m_WinAdvaceList.elem[m_WinAdvaceList.index].menu = NULL;       //�����ǰ�߼������б�
end:
    //WIN_ContextUnlock();

    //����ͨ���� Enter�ص�����û��ִ���������£����ٽ���
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




