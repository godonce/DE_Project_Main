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

/******************************全局变量***************************************/
//GUI共用BUFF
char        g_LCDBuff[LCD_BUFFTER_SIZE]     = {0};

//  0)英语    1)中文
volatile char   g_LanguageIndex             = 0;


static WIN_INTERFACE_t  m_KeyValue          = {0};



/*******************************************************************************
* Function Name :WIN_KeyBoard
* Description   :发送键值
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
    case GUI_KEY_SPACE: printf("按键SPACE按下\r\n"); break;
    case GUI_KEY_ENTER: printf("按键ENTER按下\r\n"); break;
    case GUI_KEY_UP: printf("按键UP按下\r\n"); break;
    case GUI_KEY_DOWN: printf("按键DOWN按下\r\n"); break;
    case GUI_KEY_ESCAPE: printf("按键ESC按下\r\n"); break;
    }

}


/*******************************************************************************
* Function Name :_RefreshData
* Description   :数据刷新
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

//主菜单
static MENU_INFO_TYPE m_MainWinInfo = {
    {"", ""},
    &g_MainWin,
    _MainWinInterface,
    _voidFun
};

/*****************************************************************************/
//主界面进入文本信息显示
static MENU_INFO_TYPE m_MenuStateShowInfo = {
    {"状态", "DeviceState"},
    &g_ListBoxShowMainInfo,
    ListBoxShowMainInfoInterface,
};

/*****************************************************************************/
//主界面进入帮助信息显示 最后一层
static MENU_INFO_TYPE m_MenuHelpShowInfo = {
    {"帮助", "Help"},
    &g_WinShowHelpInfo,
};

/*****************************************************************************/
//就地操作
static MENU_INFO_TYPE m_MenuLocalOp = {
    {"就地操作", "Local Operation"},
    &g_WinLocalOp,
};

/*****************************************************************************/
//主菜单
static MENU_INFO_TYPE m_MainMenuInfo = {
    {"zhucaidan ", "Main menu"},   //主菜单   0428
    &g_WinMainMenu,
    _WinMainMenuInterface,
};

/*****************************************************************************/
//主菜单
static MENU_INFO_TYPE m_UserManagInfo = {
    {"yonghuguanli", "user management"},          //用户管理    0428
    &g_WinCommonMenu,
    _WinCommonMenuInterface,
    _voidFun,
    MENU_USER_MANAG_NUM,
    *menuUserManagCn,
    *menuUserManagEn,
    menuUserManagSettings
};

/*****************************************************************************/
//主菜单
static MENU_INFO_TYPE m_CurUserInfo = {
    {"dangqianyonghu", "Current user"},        //当前用户   0428
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
    {"金智", "MenuTest1CN"},
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
    BT_InitBiTree(p);                                               // 1级菜单


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
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo), BT_RIGHT);     // 3级水平菜单 m_MenuHelpShowInfo

#if 0
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo), BT_RIGHT);      // testinfo

    p = BT_GetRightChild(p); // testinfo
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo1), BT_RIGHT);     // 3级水平菜单

    p = BT_GetRightChild(p); // testinfo1
    pTemp = p;                                                      // 3级菜单要增加水平菜单 所以保留
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo2), BT_LEFT);      // 3级水平菜单

    p = BT_GetLeftChild(p);  // testinfo2                                       // 3级水平菜单
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
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo3_1), BT_RIGHT);     // 3级水平菜单

    p = BT_GetRightChild(p); // testinfo31
    pTemp = p;                                                      // 3级菜单要增加水平菜单 所以保留
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo3_2), BT_LEFT);      // 3级水平菜单

    p = BT_GetLeftChild(p);  // testinfo32                                       // 3级水平菜单
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo3_3), BT_LEFT);

    p = pTemp;               // testinfo31                                              // 3级菜单要增加水平菜单 所以保留
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo4_1), BT_RIGHT);      // 3级水平菜单

    p = BT_GetRightChild(p); // testinfo41
    BT_AddChild(p, BT_GetDataItem(&m_MenuTestInfo4_2), BT_LEFT);

#endif

}


