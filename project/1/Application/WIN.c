/*
********************************************************************************
*                            WIN.c
*
* File          : WIN.c
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     :
* Description   :
*
* Date          : 2013/06/02
* History		:
*
*******************************************************************************/
#include <string.h>
#include "GUI.h"

#include "WIN.h"
#include "WIN_Context.h"
#include "WinWindow.h"
//#include "WIN_OS.h"

//#include "WINAPP.h"
#include "Dialog.h"
#include "LISTVIEW.h"
#include "HEADER.h"

#include "DataInterface.h"
#include "stdio.h"

/******************************ȫ�ֱ���***************************************/
//GUI����BUFF
char        g_LCDBuff[LCD_BUFFTER_SIZE]     = {0};

//  0)Ӣ��    1)����
volatile char   g_LanguageIndex             = 0;


static WIN_INTERFACE_t  m_KeyValue          = {0};



/*******************************************************************************
* Function Name :WIN_KeyBoard
* Description   :���ͼ�ֵ
* Input         :int key
* Output        :void
* Other         :
* Date          :2013/06/16
*******************************************************************************/
void WIN_KeyBoard(int key)
{
    m_KeyValue.D.val    = key;
    m_KeyValue.active   = 1;
    switch (key)
    {
    case GUI_KEY_SPACE: printf("����SPACE����\r\n"); break;
    case GUI_KEY_ENTER: printf("����ENTER����\r\n"); break;
    case GUI_KEY_UP: printf("����UP����\r\n"); break;
    case GUI_KEY_DOWN: printf("����DOWN����\r\n"); break;
    case GUI_KEY_ESCAPE: printf("����ESC����\r\n"); break;
    }

}


/*******************************************************************************
* Function Name :_RefreshData
* Description   :����ˢ��
* Input         :void
* Output        :void
* Other         :
* Date          :2014/04/03
*******************************************************************************/
void _DataRefresh(void)
{
    if (m_KeyValue.active)
    {
        m_KeyValue.active   = 0;

        if (m_KeyValue.D.val == GUI_KEY_SPACE)
        {
            //WINAPP_MessageBox(" ssb  ", 50);
        }
        else
            GUI_SendKeyMsg(m_KeyValue.D.val, 1);
    }
}

//���˵�
static MENU_INFO_TYPE m_MainWinInfo = {
    {"", ""},
    &g_MainWin,
    _MainWinInterface,
    _voidFun
};

/*****************************************************************************/
//����������ı���Ϣ��ʾ
static MENU_INFO_TYPE m_MenuStateShowInfo = {
    {"״̬", "DeviceState"},
    &g_ListBoxShowMainInfo,
    ListBoxShowMainInfoInterface,
};

/*****************************************************************************/
//��������������Ϣ��ʾ ���һ��
static MENU_INFO_TYPE m_MenuHelpShowInfo = {
    {"����", "Help"},
    &g_WinShowHelpInfo,
};

/*****************************************************************************/
//�͵ز���
static MENU_INFO_TYPE m_MenuLocalOp = {
    {"�͵ز���", "Local Operation"},
    &g_WinLocalOp,
};

/*****************************************************************************/
//���˵�
static MENU_INFO_TYPE m_MainMenuInfo = {
    {"zhucaidan ", "Main menu"},   //���˵�   0428
    &g_WinMainMenu,
    _WinMainMenuInterface,
};

/*****************************************************************************/
//���˵�
static MENU_INFO_TYPE m_UserManagInfo = {
    {"yonghuguanli", "user management"},          //�û�����    0428
    &g_WinCommonMenu,
    _WinCommonMenuInterface,
    _voidFun,
    MENU_USER_MANAG_NUM,
    *menuUserManagCn,
    *menuUserManagEn,
    menuUserManagSettings
};

/*****************************************************************************/
//���˵�
static MENU_INFO_TYPE m_CurUserInfo = {
    {"dangqianyonghu", "Current user"},        //��ǰ�û�   0428
    &g_WinCurUserMenu,
    _WinCurUserInterface,
    _voidFun,
    MENU_CUR_USER_NUM,
    *menuCurUserCn,
    *menuCurUserEn,
    menuCurUserSettings
};

/*****************************************************************************/
static MENU_INFO_TYPE m_MenuTestInfo = {
    {"MenuTestMain", "MenuTestMainCN"},
    &g_ListBox,
    ListBoxInterface,
};

/*****************************************************************************/
static MENU_INFO_TYPE m_MenuTestInfo1 = {
    {"����", "MenuTest1CN"},
    &g_ListBox,
    ListBoxInterface,
};

/*****************************************************************************/
static MENU_INFO_TYPE m_MenuTestInfo2 = {
    {"MenuTest2", "MenuTest2CN"},
    &g_ListBox,
    ListBoxInterface,
};

/*****************************************************************************/
static MENU_INFO_TYPE m_MenuTestInfo1_1 = {
    {"MenuTest11", "MenuTest11CN"},
    &g_ListBox,
    ListBoxInterface,
};

/*****************************************************************************/
static MENU_INFO_TYPE m_MenuTestInfo1_2 = {
    {"MenuTest12", "MenuTest12CN"},
    &g_ListView,
    ListViewInterface,
};

/*****************************************************************************/
static MENU_INFO_TYPE m_MenuTestInfo3_1 = {
    {"MenuTest31", "MenuTest31CN"},
    &g_ListView,
    ListViewInterface,
};

/*****************************************************************************/
static MENU_INFO_TYPE m_MenuTestInfo3_2 = {
    {"MenuTest32", "MenuTest32CN"},
    &g_ListView,
    ListViewInterface,
};

/*****************************************************************************/
static MENU_INFO_TYPE m_MenuTestInfo3_3 = {
    {"MenuTest33", "MenuTest33CN"},
    &g_ListView,
    ListViewInterface,
};

/*****************************************************************************/
static MENU_INFO_TYPE m_MenuTestInfo4_1 = {
    {"MenuTest41", "MenuTest33CN"},
    &g_ListView,
    ListViewInterface,
};

/*****************************************************************************/
static MENU_INFO_TYPE m_MenuTestInfo4_2 = {
    {"MenuTest42", "MenuTest33CN"},
    &g_ListView,
    ListViewInterface,
};

/*****************************************************************************/
static MENU_INFO_TYPE m_MenuTestInfo4_3 = {
    {"MenuTest43", "MenuTest33CN"},
    &g_ListView,
    ListViewInterface,
};

/*******************************************************************************
* Function Name :WIN_WindowsTreeInit
* Description   :
* Input         :void
* Output        :void
* Other         :
* Date          :2013/06/03
*******************************************************************************/
void WIN_WindowsTreeInit(void)
{
    void *p = NULL;
    void *pTemp = NULL;

    p = BT_GetDataItem(&m_MainWinInfo);
    BT_InitBiTree(p);                                               // 1���˵�


    BT_AddChild(p, BT_GetDataItem(&m_MenuStateShowInfo), BT_RIGHT);      // testinfo  m_MenuLocalOp

    pTemp = p;

    p = BT_GetRightChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuLocalOp), BT_LEFT);      // testinfo  m_MenuLocalOp

    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MainMenuInfo), BT_LEFT);      // testinfo  m_MenuLocalOp m_MainMenuInfo

    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MainMenuInfo), BT_LEFT);      // testinfo  m_MenuLocalOp m_MainMenuInfo m_UserManagInfo

    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_UserManagInfo), BT_RIGHT);      // testinfo  m_MenuLocalOp m_MainMenuInfo m_CurUserInfo

    p = BT_GetRightChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_CurUserInfo), BT_RIGHT);      // testinfo  m_MenuLocalOp m_MainMenuInfo m_CurUserInfo


    p = pTemp;
    p = BT_GetRightChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo), BT_RIGHT);     // 3��ˮƽ�˵� m_MenuHelpShowInfo

#if 0
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo), BT_RIGHT);      // testinfo

    p = BT_GetRightChild(p); // testinfo
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo1), BT_RIGHT);     // 3��ˮƽ�˵�

    p = BT_GetRightChild(p); // testinfo1
    pTemp = p;                                                      // 3���˵�Ҫ����ˮƽ�˵� ���Ա���
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo2), BT_LEFT);      // 3��ˮƽ�˵�

    p = BT_GetLeftChild(p);  // testinfo2                                       // 3��ˮƽ�˵�
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo1_1), BT_LEFT);

    p = pTemp;              // testinfo1
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo1_2), BT_RIGHT);

    p = BT_GetRightChild(p);  // testinfo1-2
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo3_1), BT_RIGHT);

    p = BT_GetRightChild(p);  // testinfo3-1
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo3_2), BT_LEFT);
#endif

#if 0
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo1_2), BT_RIGHT);      // testinfo

    p = BT_GetRightChild(p); // testinfo12
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo3_1), BT_RIGHT);     // 3��ˮƽ�˵�

    p = BT_GetRightChild(p); // testinfo31
    pTemp = p;                                                      // 3���˵�Ҫ����ˮƽ�˵� ���Ա���
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo3_2), BT_LEFT);      // 3��ˮƽ�˵�

    p = BT_GetLeftChild(p);  // testinfo32                                       // 3��ˮƽ�˵�
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo3_3), BT_LEFT);

    p = pTemp;               // testinfo31                                              // 3���˵�Ҫ����ˮƽ�˵� ���Ա���
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo4_1), BT_RIGHT);      // 3��ˮƽ�˵�

    p = BT_GetRightChild(p); // testinfo41
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo4_2), BT_LEFT);

#endif

}


