/*
********************************************************************************
*
*                                 WIN_Windows
*
* File          : WIN_Windows.c
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     :
* Description   : 窗口元素   所有窗口
*
* Date          : 2013/06/02
* History		:
*
*******************************************************************************/
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "WIN.h"
//#include "WIN_API.h"
#include "WinWindow.h"
//#include "WIN_Context.h"

#include "GUI.h"
#include "WM.h"
#include "DIALOG.h"
#include "LCDConf.H"
#include "FRAMEWIN.h"

#include "Bitmap_use.c"
#include "song16all.c"
#include "song64.c"
#include "song33.c"
#include "CodeConvert.h"
#include "DataInterface.h"
//#include "Library.h"

#define MAG 4


typedef struct {
  GUI_AUTODEV_INFO AutoDevInfo; /* Information about what has to be displayed */
  GUI_POINT aPoints[7];         /* Polygon data */
  float Angle;
} PARAM;

typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hText;
    GUI_HWIN hProgbar;
    GUI_HWIN hList;
    GUI_HWIN hBtnNationFlag;
    GUI_HWIN hBtnLocal;
    GUI_HWIN hBtnRemote;
    GUI_HWIN hBtnTurnOff;
    GUI_AUTODEV AutoDev;
    PARAM Param;            /* Parameters for drawing routine */
}MAIN_WIN_BAR_TYPE;

static MAIN_WIN_BAR_TYPE m_MainWin = {0};     //主界面句柄

char strShow[STRSHOWBUF_SIZE];
void _WinLocalOpRefresh(void);
/*******************************************************************************
* Function Name :_MainWinKeyDown
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/15
*******************************************************************************/
void _MainWinKeyDown(void)
{
	char curIndex=0;
    //焦点在text上面
	if(MAIN_MENU_FOCUS_TEXT == g_mainMenuFocus)
	{
      g_mainMenuFocus = MAIN_MENU_FOCUS_LIST;
      LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
      TEXT_SetBkColor(m_MainWin.hText,GUI_WHITE);
	    //WM_SetFocus(m_MainWin.hList);
	    if(DEVICE_STATE_LOCAL == g_deviceState)   //本地操作，index  = 0 开放
	    {
	        LISTBOX_SetSel(m_MainWin.hList,0);
	    }
	    else
	    {
	        LISTBOX_SetSel(m_MainWin.hList,1);
	    }
	}
	else if((MAIN_MENU_FOCUS_LIST == g_mainMenuFocus))//焦点在list上面 最后一行翻转到text上面
  {
      curIndex = LISTBOX_GetSel(m_MainWin.hList);
  	  if(curIndex < (LISTBOX_GetNumItems(m_MainWin.hList)-1))
  	  {
  	  	  curIndex++;
  	      LISTBOX_SetSel(m_MainWin.hList,curIndex);
  	  }
      else if( curIndex == (LISTBOX_GetNumItems(m_MainWin.hList)-1) )
      {
          g_mainMenuFocus = MAIN_MENU_FOCUS_TEXT;
          TEXT_SetBkColor(m_MainWin.hText,GUI_ORANGE);
          LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_SEL      , GUI_WHITE);
          //WM_SetFocus(m_MainWin.hText);
      }
  }
}

/*******************************************************************************
* Function Name :_MainWinKeyUp
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/15
*******************************************************************************/
void _MainWinKeyUp(void)
{
	char curIndex=0;
    //焦点在text上面
	if(MAIN_MENU_FOCUS_TEXT == g_mainMenuFocus)
	{
      g_mainMenuFocus = MAIN_MENU_FOCUS_LIST;
      LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
      TEXT_SetBkColor(m_MainWin.hText,GUI_WHITE);
	    //WM_SetFocus(m_MainWin.hList);
	    LISTBOX_SetSel(m_MainWin.hList,3);
	}
	else if((MAIN_MENU_FOCUS_LIST == g_mainMenuFocus))//焦点在list上面 最后一行翻转到text上面
  {
      curIndex = LISTBOX_GetSel(m_MainWin.hList);
      if(DEVICE_STATE_LOCAL == g_deviceState)  //本地操作，index  = 0 开放
      {
          if(curIndex == 0)
          {
              g_mainMenuFocus = MAIN_MENU_FOCUS_TEXT;
              TEXT_SetBkColor(m_MainWin.hText,GUI_ORANGE);
              LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_SEL      , GUI_WHITE);
          }
          else
          {
              curIndex--;
              LISTBOX_SetSel(m_MainWin.hList,curIndex);
          }
      }
      else
      {
          if(curIndex == 1)
          {
              g_mainMenuFocus = MAIN_MENU_FOCUS_TEXT;
              TEXT_SetBkColor(m_MainWin.hText,GUI_ORANGE);
              LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_SEL      , GUI_WHITE);
          }
          else
          {
              curIndex--;
              LISTBOX_SetSel(m_MainWin.hList,curIndex);
          }
      }
  }
}


/*******************************************************************************
* Function Name :_MainWinKeyEnter
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/15
*******************************************************************************/
void _MainWinKeyEnter(void)
{
    int id = 0;
	  if (m_MainWin.hList != 0) id = LISTBOX_GetSel(m_MainWin.hList);
    if(MAIN_MENU_FOCUS_TEXT == g_mainMenuFocus)
    {
    	  id = 0;
        //printf("g_mainMenuFocus = MAIN_MENU_FOCUS_TEXT      id =%d \n",id);
        WIN_Enter((int)&id);
    }
    else
    {
        //printf("g_mainMenuFocus != MAIN_MENU_FOCUS_TEXT      id =%d \n",id);
        if(1 == id) //远方就地关闭选项
        {
            if(DEVICE_STATE_LOCAL == g_deviceState)
            {
                g_deviceState = DEVICE_STATE_REMOTE;
                BUTTON_SetPressed(m_MainWin.hBtnLocal,0);
                BUTTON_SetPressed(m_MainWin.hBtnRemote,1);
                _MainWinShowRefresh();
            }
            else if(DEVICE_STATE_REMOTE == g_deviceState)
            {
                g_deviceState = DEVICE_STATE_OFF;
                BUTTON_SetPressed(m_MainWin.hBtnRemote,0);
                BUTTON_SetPressed(m_MainWin.hBtnTurnOff,1);
                _MainWinShowRefresh();
            }
            else if(DEVICE_STATE_OFF == g_deviceState)
            {
                g_deviceState = DEVICE_STATE_LOCAL;
                BUTTON_SetPressed(m_MainWin.hBtnTurnOff,0);
                BUTTON_SetPressed(m_MainWin.hBtnLocal,1);
                _MainWinShowRefresh();
            }
        }
        else if(0 == id) //远方就地关闭选项
        {
            id = 1;
            WIN_Enter((int)&id);
        }
        else
        {
            WIN_Enter((int)&id);
        }
    }
}

/*******************************************************************************
* Function Name :_MainWinShowRefresh
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/15
*******************************************************************************/
void _MainWinShowRefresh(void)
{
    memset(strShow,0,sizeof(strShow));
    if(LANGUAGE_CN == g_LanguageIndex)
    {
        if(DEVICE_STATE_LOCAL == g_deviceState)
        {
            enc_unicode_to_utf8_str(infoWinMainList0CN[DEVICE_STATE_LOCAL],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,0);
        }
        else if(DEVICE_STATE_REMOTE == g_deviceState)
        {
            enc_unicode_to_utf8_str(infoWinMainList0CN[DEVICE_STATE_REMOTE],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,1);
        }
        else if(DEVICE_STATE_OFF == g_deviceState)
        {
            enc_unicode_to_utf8_str(infoWinMainList0CN[DEVICE_STATE_OFF],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,1);
        }
    }
    else if(LANGUAGE_EN == g_LanguageIndex)
    {
        if(DEVICE_STATE_LOCAL == g_deviceState)
        {
            enc_unicode_to_utf8_str(infoWinMainList0EN[DEVICE_STATE_LOCAL],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,0);
        }
        else if(DEVICE_STATE_REMOTE == g_deviceState)
        {
            enc_unicode_to_utf8_str(infoWinMainList0EN[DEVICE_STATE_REMOTE],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,1);
        }
        else if(DEVICE_STATE_OFF == g_deviceState)
        {
            enc_unicode_to_utf8_str(infoWinMainList0EN[DEVICE_STATE_OFF],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,1);
        }
    }
}


/*******************************************************************************
* Function Name :_MainWinCallback
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/15
*******************************************************************************/
static void _MainWinCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_ESCAPE:
            WIN_Enter((int)&id);
            break;
        case GUI_KEY_DOWN:
            _MainWinKeyDown();
            break;
        case GUI_KEY_UP:
            _MainWinKeyUp();
            break;
        case GUI_KEY_ENTER:
            _MainWinKeyEnter();
            //WIN_Enter((int)&id);
            //WIN_Exit(0);
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}
/*******************************************************************************
* Function Name :_MainWinCreate
* Description   :主界面窗口建立
* Input         :void * p
* Output        :void
* Other         :
* Date          :2013/06/15
*******************************************************************************/
static void _MainWinCreate(void *p)
{
    unsigned int i=0;
    GUI_HWIN        hWin        = 0;

    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    /* Enable high resolution for antialiasing */
    //GUI_AA_EnableHiRes();
    GUI_AA_SetFactor(MAG);

    /* Create GUI_AUTODEV-objects */
    GUI_MEMDEV_CreateAuto(&m_MainWin.AutoDev);

    //m_MainWin.Param.Angle = 225 * DEG2RAD;

    //GUI_RotatePolygon(m_MainWin.Param.aPoints, _aNeedle_1, GUI_COUNTOF(_aNeedle_1), m_MainWin.Param.Angle);
    //GUI_MEMDEV_DrawAuto(&m_MainWin.AutoDev, &m_MainWin.Param.AutoDevInfo, _Draw, &m_MainWin.Param);
    _DebugUseFreeBytesShow();

/*********************************主界面显示数字还是图标**********************************/
    if(dataStructInterface.stateOpen)
    {
        GUI_DrawBitmap(&bm333,20+150-33,5+2);
    }
    else if(dataStructInterface.stateClose)
    {
        GUI_DrawBitmap(&bm444,20+150-33,5+2);
    }
    else if(dataStructInterface.stateMid)
    {
        GUI_SetColor(GUI_BLACK);
        GUI_SetFont(&GUI_Fontsong64);
        GUI_UC_SetEncodeUTF8();
        GUI_DispDecAt(dataStructInterface.numMid1,20+150-32-18,5+2,2);//32+32+16+20
        GUI_DispCharAt('.',20+150-32-18+64,5+2);
        GUI_SetFont(&GUI_Fontsong33);
        GUI_DispDecAt(dataStructInterface.numMid2,20+150+18+14,5+2+32-4,1);
        GUI_DispCharAt('%',20+150+32+20,5+2+32-4);
    }

/*********************************主界面开关的图标**********************************/
    if(0 == dataStructInterface.stateOpen)
    {
        GUI_DrawBitmap(&bm222,20+250,5+2*46);
    }
    else if(1 == dataStructInterface.stateOpen)
    {
        GUI_DrawBitmap(&bm222_2,20+250,5+2*46);
    }

    if(0 == dataStructInterface.stateClose)
    {
        GUI_DrawBitmap(&bm111,20,5+2*46);
    }
    else if(1 == dataStructInterface.stateClose)
    {
        GUI_DrawBitmap(&bm111_2,20,5+2*46);
    }

/*********************************主界面信息文本显示**********************************/
    m_MainWin.hFrame = WM_HBKWIN;
    hWin = m_MainWin.hFrame;
    memset(strShow,0,sizeof(strShow));
    if(LANGUAGE_CN == g_LanguageIndex)
    {
        i = strlen(infoWinMainCN[dataStructInterface.IndexWinMainInfo]);
        enc_unicode_to_utf8_str(infoWinMainCN[dataStructInterface.IndexWinMainInfo],strShow,STRSHOWBUF_SIZE);
    }
    else if(LANGUAGE_EN == g_LanguageIndex)
    {
        i = strlen(infoWinMainEN[dataStructInterface.IndexWinMainInfo]);
        enc_unicode_to_utf8_str(infoWinMainEN[dataStructInterface.IndexWinMainInfo],strShow,STRSHOWBUF_SIZE);
    }
    m_MainWin.hText = TEXT_CreateAsChild(20+(300-i*8)/2,5+69+3,23+i*8,20,hWin,NULL,WM_CF_SHOW,strShow,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetBkColor(m_MainWin.hText,GUI_WHITE);
    TEXT_SetFont(m_MainWin.hText,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    GUI_DrawBitmap(&bmerror,20+(300-i*8)/2-23,5+69+2);
    if(MAIN_MENU_FOCUS_TEXT == g_mainMenuFocus)
    {
        TEXT_SetBkColor(m_MainWin.hText,GUI_ORANGE);
    }
    else
    {
        TEXT_SetBkColor(m_MainWin.hText,GUI_WHITE);
    }

/*********************************主界面进度条显示**********************************/
    m_MainWin.hProgbar    = PROGBAR_CreateAsChild(20+50+5, 5+2*46+10, 190, 26,hWin,NULL, WM_CF_SHOW);
    PROGBAR_SetText(m_MainWin.hProgbar,"");
    PROGBAR_SetValue(m_MainWin.hProgbar,dataStructInterface.numMid1);

/*********************************主界面List显示**********************************/
    m_MainWin.hList = LISTBOX_CreateEx( 20+50+5+5, 5+3*46, 180, 92, hWin, WM_CF_SHOW, NULL, NULL, NULL);
    WIDGET_SetEffect(m_MainWin.hList,&WIDGET_Effect_None);
    LISTBOX_SetFont(m_MainWin.hList, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(m_MainWin.hList, 7);
    LISTBOX_SetTextAlign(m_MainWin.hList,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_DISABLED , GUI_WHITE);
    LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_SEL      , GUI_WHITE);
    LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_SELFOCUS , GUI_ORANGE);
    LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_UNSEL    , GUI_WHITE);
    LISTBOX_SetTextColor(m_MainWin.hList,LISTBOX_CI_DISABLED , GUI_GRAY);
    LISTBOX_SetTextColor(m_MainWin.hList,LISTBOX_CI_SEL      , GUI_BLACK);
    LISTBOX_SetTextColor(m_MainWin.hList,LISTBOX_CI_SELFOCUS , GUI_BLACK);
    LISTBOX_SetTextColor(m_MainWin.hList,LISTBOX_CI_UNSEL    , GUI_BLACK);

    if(LANGUAGE_CN == g_LanguageIndex)
    {
        memset(strShow,0,sizeof(strShow));
        enc_unicode_to_utf8_str(infoWinMainList0CN[g_deviceState],strShow,STRSHOWBUF_SIZE);
        LISTBOX_AddString(m_MainWin.hList, strShow);
    }
    else if(LANGUAGE_EN == g_LanguageIndex)
    {
        memset(strShow,0,sizeof(strShow));
        enc_unicode_to_utf8_str(infoWinMainList0EN[g_deviceState],strShow,STRSHOWBUF_SIZE);
        LISTBOX_AddString(m_MainWin.hList, strShow);
    }

    if(DEVICE_STATE_LOCAL != g_deviceState)
    {
        LISTBOX_SetItemDisabled(m_MainWin.hList,0,1);
    }

    for(i=1;i<WINMAIN_LIST_NUM;i++)
    {
        memset(strShow,0,sizeof(strShow));
        if(LANGUAGE_CN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(infoWinMainListCN[i-1],strShow,STRSHOWBUF_SIZE);
        }
        else if(LANGUAGE_EN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(infoWinMainListEN[i-1],strShow,STRSHOWBUF_SIZE);
        }
        LISTBOX_AddString(m_MainWin.hList, strShow);
    }

/*********************************主界面button显示**********************************/
    m_MainWin.hBtnNationFlag = BUTTON_CreateAsChild(20+50+5+5+180-34, 5+3*46+23*2, 34, 23,hWin,NULL, WM_CF_SHOW);
    BUTTON_SetBitmapEx(m_MainWin.hBtnNationFlag,0,&bmflagCN,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnNationFlag,1,&bmflagCN,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnNationFlag,2,&bmflagCN,0,0);

    m_MainWin.hBtnLocal = BUTTON_CreateAsChild(20+50+5+5+180-34*3, 5+3*46+23, 34, 23,hWin,NULL, WM_CF_SHOW);
    BUTTON_SetBitmapEx(m_MainWin.hBtnLocal,BUTTON_BI_DISABLED  ,&bmlocal1,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnLocal,BUTTON_BI_PRESSED   ,&bmlocal2,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnLocal,BUTTON_BI_UNPRESSED ,&bmlocal1,0,0);
    if(DEVICE_STATE_LOCAL == g_deviceState)
    {
        BUTTON_SetPressed(m_MainWin.hBtnLocal,1);

    }
    else
    {
        BUTTON_SetPressed(m_MainWin.hBtnLocal,0);
    }


    m_MainWin.hBtnRemote = BUTTON_CreateAsChild(20+50+5+5+180-34*2, 5+3*46+23, 34, 23,hWin,NULL, WM_CF_SHOW);
    BUTTON_SetBitmapEx(m_MainWin.hBtnRemote,BUTTON_BI_DISABLED,&bmremote1,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnRemote,BUTTON_BI_PRESSED,&bmremote2,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnRemote,BUTTON_BI_UNPRESSED,&bmremote1,0,0);
    if(DEVICE_STATE_REMOTE == g_deviceState)
    {
        BUTTON_SetPressed(m_MainWin.hBtnRemote,1);
    }
    else
    {
        BUTTON_SetPressed(m_MainWin.hBtnRemote,0);
    }

    m_MainWin.hBtnTurnOff = BUTTON_CreateAsChild(20+50+5+5+180-34*1, 5+3*46+23, 34, 23,hWin,NULL, WM_CF_SHOW);
    BUTTON_SetBitmapEx(m_MainWin.hBtnTurnOff,BUTTON_BI_DISABLED,&bmturnoff1,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnTurnOff,BUTTON_BI_PRESSED,&bmturnoff2,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnTurnOff,BUTTON_BI_UNPRESSED,&bmturnoff1,0,0);
    if(DEVICE_STATE_OFF == g_deviceState)
    {
        BUTTON_SetPressed(m_MainWin.hBtnTurnOff,1);
    }
    else
    {
        BUTTON_SetPressed(m_MainWin.hBtnTurnOff,0);
    }

    WM_SetCallback(WM_HBKWIN,_MainWinCallback);
    WM_SetFocus(WM_HBKWIN);
}



/*******************************************************************************
* Function Name :_MainWinDestroy
* Description   :窗口销毁
* Input         :void * p
* Output        :void
* Other         :
* Date          :2013/06/15
*******************************************************************************/
static void _MainWinDestroy(void *p)
{
    /* Delete GUI_AUTODEV-objects */
    GUI_MEMDEV_DeleteAuto(&m_MainWin.AutoDev);
    WM_DeleteWindow(m_MainWin.hText);
    WM_DeleteWindow(m_MainWin.hProgbar);
    WM_DeleteWindow(m_MainWin.hList);
    WM_DeleteWindow(m_MainWin.hBtnNationFlag);
    WM_DeleteWindow(m_MainWin.hBtnLocal);
    WM_DeleteWindow(m_MainWin.hBtnRemote);
    WM_DeleteWindow(m_MainWin.hBtnTurnOff);
    //WM_DeleteWindow(m_MainWin.hFrame);
    WM_SetCallback(WM_HBKWIN,NULL);
    GUI_Clear();
    memset(&m_MainWin, 0, sizeof(m_MainWin));
    //PARAM Param;            /* Parameters for drawing routine */
}

/*******************************************************************************
* Function Name :_MainWinInterface
* Description   :设定当前 选择项
* Input         :int sel
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _MainWinInterface(void *val)
{
    int sel = *(int *)val;

    //printf("sel = %d \n",sel);
    g_mainMenuFocus = MAIN_MENU_FOCUS_LIST;
    if(0 == sel)
    {
        g_mainMenuFocus = MAIN_MENU_FOCUS_TEXT;
    }
    else if(1 == sel)
    {
        LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        LISTBOX_SetSel(m_MainWin.hList,0);
    }
    else
    {
        LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        LISTBOX_SetSel(m_MainWin.hList,sel);
    }
}


WIN_INFO_TYPE g_MainWin = {
    &m_MainWin.hFrame,
    _MainWinCreate,
    _MainWinDestroy,
};





/******************************列表窗口***************************************/
typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hList;
}LIST_BOX_TYPE;
static LIST_BOX_TYPE m_HListBox = {0};                         //列表窗口句柄

/*******************************************************************************
* Function Name :ListCallback
* Description   :回调函数
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _ListCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_ESCAPE:
            WIN_Exit(0);
            break;

        case GUI_KEY_ENTER:
            if (m_HListBox.hList != 0)
                id = LISTBOX_GetSel(m_HListBox.hList);
            WIN_Enter(&id);
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

/*******************************************************************************
* Function Name :_ListBoxCreate
* Description   :列表窗口建立 或 显示
* Input         :void *
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _ListBoxCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    //建立新窗口
    m_HListBox.hFrame = FRAMEWIN_CreateAsChild(-1, -3, LCD_HSIZE + 3, LCD_VSIZE + 8,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);

    FRAMEWIN_SetFont(m_HListBox.hFrame, GUI_DEFAULT_FONT);  //字体
    FRAMEWIN_SetTitleVis(m_HListBox.hFrame, 1);             //显示标题
    //FRAMEWIN_SetTitleHeight(m_HListBox.hFrame, 24);         //标题宽度
    FRAMEWIN_SetTextAlign(m_HListBox.hFrame, GUI_TA_HCENTER | GUI_TA_HCENTER);

    pMenu = BT_GetRightChild(pMenu);
    val = BT_GetLeftDepth(pMenu);

    hWin = WM_GetFirstChild(m_HListBox.hFrame);             //获得窗口桌面

    //建立列表窗口
    m_HListBox.hList = LISTBOX_CreateAsChild(NULL, hWin, 0, 0, 0, 0,WM_CF_SHOW);
    //LISTBOX_SetFont(m_HListBox.hList, GUI_DEFAULT_FONT);
    LISTBOX_SetFont(m_HListBox.hList, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(m_HListBox.hList, 0);

    WM_SetFocus(m_HListBox.hFrame);
    for (i = 0; i < val; i++)
    {
        memset(pBuffter, 0, bufSize);
        sprintf(pBuffter, "%d.", i + 1);
        pTitle = BT_GetLChildElem(pMenu, i)->data->title[g_LanguageIndex];
        if (NULL == pTitle) pTitle = "";
        strcat(pBuffter, pTitle);
        memset(strShow,0,64);
        enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
        //增加列表项
        LISTBOX_AddString(m_HListBox.hList, strShow);
    }
    WM_SetCallback(WM_HBKWIN, _ListCallback);
}

/*******************************************************************************
* Function Name :_ListBoxDestroy
* Description   :
* Input         :void * p
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _ListBoxDestroy(void *p)
{
    WM_DeleteWindow(m_HListBox.hList);
    WM_DeleteWindow(m_HListBox.hFrame);
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_HListBox, 0, sizeof(m_HListBox));
}

/*******************************************************************************
* Function Name :ListBoxInterface
* Description   :设定当前 选择项
* Input         :int sel
* Output        :void
* Other         :
* Date          :2013/06/07
*******************************************************************************/
void ListBoxInterface(void *val)
{
    int sel = *(int *)val;

    if (m_HListBox.hList == 0)
        return;

    if ((sel < (int)LISTBOX_GetNumItems(m_HListBox.hList)) && (sel >= 0))
        LISTBOX_SetSel(m_HListBox.hList, sel);
}

WIN_INFO_TYPE g_ListBox = {                         //列表窗口
    &m_HListBox.hFrame,
    _ListBoxCreate,
    _ListBoxDestroy,
};




extern GUI_CONST_STORAGE GUI_BITMAP bmback1;
extern GUI_CONST_STORAGE GUI_BITMAP bmback2;
extern GUI_CONST_STORAGE GUI_BITMAP bmhome;
extern GUI_CONST_STORAGE GUI_BITMAP bmhome2;
/******************************列表窗口***************************************/
typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hBtnRtn;
    GUI_HWIN hBtnMain;
    GUI_HWIN hTextAlign;
    GUI_HWIN hList;
}LIST_VIEWER_TYPE;
static LIST_VIEWER_TYPE m_HListView = {0};                         //列表窗口句柄

/*******************************************************************************
* Function Name :ListKeyDown
* Description   :回调函数
* Input         :void
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _ListKeyDown(void)
{
    if(BUTTON_IsPressed(m_HListView.hBtnRtn))
    {
        BUTTON_SetPressed(m_HListView.hBtnRtn,0);
        BUTTON_SetPressed(m_HListView.hBtnMain,1);
    }
    else if(BUTTON_IsPressed(m_HListView.hBtnMain))
    {
        BUTTON_SetPressed(m_HListView.hBtnMain,0);
        WM_SetFocus(m_HListView.hList);
        LISTVIEW_SetSel(m_HListView.hList,1);
    }
}

/*******************************************************************************
* Function Name :ListCallback
* Description   :回调函数
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _ListViewCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_ESCAPE:
            WIN_Exit(0);
            break;
        case GUI_KEY_UP:
            break;
        case GUI_KEY_DOWN:
            _ListKeyDown();
            //BUTTON_SetPressed(m_HListView.hBtnRtn,0);
            //BUTTON_SetPressed(m_HListView.hBtnMain,1);
            break;
        case GUI_KEY_ENTER:
            if (m_HListView.hList != 0)
                id = LISTVIEW_GetSel(m_HListView.hList);
            WIN_Enter(&id);
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

/*******************************************************************************
* Function Name :_ListBoxCreate
* Description   :列表窗口建立 或 显示
* Input         :void *
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _ListViewCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    char            *pBuffter   = g_LCDBuff;
    const char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    //建立新窗口
    m_HListView.hFrame = FRAMEWIN_CreateAsChild(-1, -3, LCD_HSIZE + 3, LCD_VSIZE + 8,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);

    FRAMEWIN_SetFont(m_HListView.hFrame, GUI_DEFAULT_FONT);  //字体
    FRAMEWIN_SetTitleVis(m_HListView.hFrame, 0);             //显示标题
    //FRAMEWIN_SetTitleHeight(m_HListBox.hFrame, 24);         //标题宽度
    FRAMEWIN_SetTextAlign(m_HListView.hFrame, GUI_TA_HCENTER | GUI_TA_HCENTER);

    pMenu = BT_GetRightChild(pMenu);
    val = BT_GetLeftDepth(pMenu);

    hWin = WM_GetFirstChild(m_HListView.hFrame);             //获得窗口桌面

    //建立列表窗口
    m_HListView.hBtnRtn    = BUTTON_CreateAsChild(130, 0, 30, 30,hWin,NULL, WM_CF_SHOW);
    m_HListView.hBtnMain   = BUTTON_CreateAsChild(160, 0, 30, 30,hWin,NULL, WM_CF_SHOW);
    m_HListView.hTextAlign = TEXT_CreateEx( 0, 30, 320, 30, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_HListView.hList = LISTVIEW_CreateEx( 0, 60, 320, 150, hWin, WM_CF_SHOW, NULL, NULL);

    LISTVIEW_AddColumn(m_HListView.hList,320, "Col 0", GUI_TA_VCENTER | GUI_TA_LEFT);//添加1列
    LISTVIEW_SetFont(m_HListView.hList,GUI_FONT_16_1);
    LISTVIEW_SetHeaderHeight(m_HListView.hList,0);
    LISTVIEW_SetGridVis(m_HListView.hList,1);//单元格可见
    LISTVIEW_SetAutoScrollV(m_HListView.hList,1);
    LISTVIEW_SetRowHeight(m_HListView.hList,30);
    LISTVIEW_SetBkColor(m_HListView.hList,LISTVIEW_CI_DISABLED , GUI_WHITE);
    LISTVIEW_SetBkColor(m_HListView.hList,LISTVIEW_CI_SEL      , GUI_WHITE);
    LISTVIEW_SetBkColor(m_HListView.hList,LISTVIEW_CI_SELFOCUS , GUI_ORANGE);
    LISTVIEW_SetBkColor(m_HListView.hList,LISTVIEW_CI_UNSEL    , GUI_WHITE);

    LISTVIEW_SetFont(m_HListView.hList, GUI_DEFAULT_FONT);
    //LISTVIEW_SetItemSpacing(m_HListBox.hList, 0);
    hWin = m_HListView.hBtnRtn;
    BUTTON_SetBitmapEx(hWin,0,&bmback1,0,0);
    BUTTON_SetBitmapEx(hWin,1,&bmback2,0,0);
    BUTTON_SetBitmapEx(hWin,2,&bmback1,0,0);
    BUTTON_SetPressed(hWin,1);

    hWin = m_HListView.hBtnMain;
    BUTTON_SetBitmapEx(hWin,0,&bmhome,0,0);
    BUTTON_SetBitmapEx(hWin,1,&bmhome2,0,0);
    BUTTON_SetBitmapEx(hWin,2,&bmhome,0,0);

    hWin = m_HListView.hTextAlign;
    TEXT_SetBkColor(hWin,GUI_ORANGE);
    TEXT_SetTextAlign(hWin,TEXT_CF_LEFT|TEXT_CF_VCENTER);
    TEXT_SetText(hWin, pTitle);

    WM_SetFocus(m_HListView.hFrame);
    for (i = 0; i < val; i++)
    {
        memset(pBuffter, 0, bufSize);
        sprintf(pBuffter, "%d.", i + 1);
        pTitle = BT_GetLChildElem(pMenu, i)->data->title[g_LanguageIndex];
        if (NULL == pTitle) pTitle = "";
        strcat(pBuffter, pTitle);
        //增加列表项
        //LISTBOX_AddString(m_HListBox.hList, pBuffter);
        LISTVIEW_AddRow(m_HListView.hList, NULL);
        LISTVIEW_SetItemText(m_HListView.hList, 0, i, pBuffter);
    }
    WM_SetCallback(WM_HBKWIN, _ListViewCallback);
}

/*******************************************************************************
* Function Name :_ListBoxDestroy
* Description   :
* Input         :void * p
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _ListViewDestroy(void *p)
{
    WM_DeleteWindow(m_HListView.hList);
    WM_DeleteWindow(m_HListView.hFrame);
    WM_DeleteWindow(m_HListView.hBtnRtn);
    WM_DeleteWindow(m_HListView.hBtnMain);
    WM_DeleteWindow(m_HListView.hTextAlign);
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_HListView, 0, sizeof(m_HListView));
}

/*******************************************************************************
* Function Name :ListBoxInterface
* Description   :设定当前 选择项
* Input         :int sel
* Output        :void
* Other         :
* Date          :2013/06/07
*******************************************************************************/
void ListViewInterface(void *val)
{
    int sel = *(int *)val;

    if (m_HListView.hList == 0)
        return;

    if ((sel < (int)LISTVIEW_GetNumRows(m_HListView.hList)) && (sel >= 0))
        LISTVIEW_SetSel(m_HListView.hList, sel);
}

WIN_INFO_TYPE g_ListView = {                         //列表窗口
    &m_HListView.hFrame,
    _ListViewCreate,
    _ListViewDestroy,
};



extern GUI_CONST_STORAGE GUI_BITMAP bmbackSel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbackUnsel;
extern GUI_CONST_STORAGE GUI_BITMAP bmhomeSel;
extern GUI_CONST_STORAGE GUI_BITMAP bmhomeUnsel;
/******************************列表窗口***************************************/
typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hBtnRtn;
    GUI_HWIN hText;
    GUI_HWIN hList;
}LIST_BOX_TYPE_SHOWMAININFO;
static LIST_BOX_TYPE_SHOWMAININFO m_HListBoxShowMainInfo = {0};                         //列表窗口句柄

/*******************************************************************************
* Function Name :_ListBoxShowMainInfoCallback
* Description   :回调函数
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _ListBoxShowMainInfoCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_ESCAPE:
            WIN_Exit(0);
            break;
        case GUI_KEY_UP:
            _ListBoxShowMainInfoKeyUp();
            break;
        case GUI_KEY_DOWN:
            _ListBoxShowMainInfoKeyDown();
            break;
        case GUI_KEY_ENTER:
//            if (m_HListView.hList != 0)
//                id = LISTVIEW_GetSel(m_HListView.hList);
//            WIN_Enter(&id);
            _ListBoxShowMainInfoKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

/*******************************************************************************
* Function Name :_ListBoxShowMainInfoCreate
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/01
*******************************************************************************/
static void _ListBoxShowMainInfoCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    char            *pBuffter   = g_LCDBuff;
     char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);

    //建立新窗口
    m_HListBoxShowMainInfo.hFrame = FRAMEWIN_CreateAsChild(0, 0, LCD_HSIZE+3, LCD_VSIZE+3 ,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);

    FRAMEWIN_SetFont(m_HListBoxShowMainInfo.hFrame, &GUI_Fontsong16all);  //字体
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_HListBoxShowMainInfo.hFrame, 0);             //显示标题
    //FRAMEWIN_SetTitleHeight(m_HListBox.hFrame, 24);         //标题宽度
    //FRAMEWIN_SetTextAlign(m_HListBoxShowMainInfo.hFrame, GUI_TA_HCENTER | GUI_TA_HCENTER);

    pMenu = BT_GetRightChild(pMenu);
    val = BT_GetLeftDepth(pMenu);

    hWin = WM_GetFirstChild(m_HListBoxShowMainInfo.hFrame);             //获得窗口桌面

    //建立列表窗口
    m_HListBoxShowMainInfo.hBtnRtn    = BUTTON_CreateAsChild(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, 23, 23,hWin,NULL, WM_CF_SHOW);
    m_HListBoxShowMainInfo.hText      = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+23, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_HListBoxShowMainInfo.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23, PER_CM_OFFSET*4.5, PER_CM_OFFSET*5, hWin, WM_CF_SHOW, NULL, NULL,NULL);

    /***********************************返回按钮************************************/
    hWin = m_HListBoxShowMainInfo.hBtnRtn;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmbackUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmbackSel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmbackUnsel,0,0);
    BUTTON_SetPressed(hWin,1);

    /***********************************标题，中英文可以自由切换************************************/
    hWin = m_HListBoxShowMainInfo.hText;
    TEXT_SetFont(m_HListBoxShowMainInfo.hText,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_BLUE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);

    /***********************************LISTBOX************************************/
    hWin = m_HListBoxShowMainInfo.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 7);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_DISABLED , GUI_WHITE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SEL      , GUI_ORANGE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SELFOCUS , GUI_ORANGE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_UNSEL    , GUI_WHITE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_DISABLED , GUI_BLUE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SEL      , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SELFOCUS , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_UNSEL    , GUI_BLACK);

    memset(strShow,0,sizeof(strShow));
    if(LANGUAGE_CN == g_LanguageIndex)enc_unicode_to_utf8_str(infoTitleCN[0],strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN == g_LanguageIndex)enc_unicode_to_utf8_str(infoTitleEN[0],strShow,STRSHOWBUF_SIZE);
    LISTBOX_AddString(hWin, strShow);
    LISTBOX_SetItemDisabled(hWin,0,1);

    //装置状态
    memset(strShow,0,sizeof(strShow));
    if(LANGUAGE_CN == g_LanguageIndex)enc_unicode_to_utf8_str(infoDeviceStateCN[dataStructInterface.indexDeviceState],strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN == g_LanguageIndex)enc_unicode_to_utf8_str(infoDeviceStateEN[dataStructInterface.indexDeviceState],strShow,STRSHOWBUF_SIZE);
    LISTBOX_AddString(hWin, strShow);

    memset(strShow,0,sizeof(strShow));
    if(LANGUAGE_CN == g_LanguageIndex)enc_unicode_to_utf8_str(infoTitleCN[1],strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN == g_LanguageIndex)enc_unicode_to_utf8_str(infoTitleEN[1],strShow,STRSHOWBUF_SIZE);
    LISTBOX_AddString(hWin, strShow);
    LISTBOX_SetItemDisabled(hWin,2,1);

    for(i=0;i<dataStructInterface.numFault;i++)
    {
    	memset(strShow,0,sizeof(strShow));
        if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str(infoWinMainCN[dataStructInterface.indexFaultNum[i]],strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str(infoWinMainEN[dataStructInterface.indexFaultNum[i]],strShow,STRSHOWBUF_SIZE);
        LISTBOX_AddString(hWin, strShow);
    }

    WM_SetCallback(WM_HBKWIN, _ListBoxShowMainInfoCallback);
}

/*******************************************************************************
* Function Name :_ListBoxDestroy
* Description   :
* Input         :void * p
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _ListBoxShowMainInfoDestroy(void *p)
{
    WM_DeleteWindow(m_HListBoxShowMainInfo.hList);
    WM_DeleteWindow(m_HListBoxShowMainInfo.hBtnRtn);
    WM_DeleteWindow(m_HListBoxShowMainInfo.hText);
    WM_DeleteWindow(m_HListBoxShowMainInfo.hFrame);
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_HListBoxShowMainInfo, 0, sizeof(m_HListBoxShowMainInfo));
}

/*******************************************************************************
* Function Name :ListBoxShowMainInfoInterface
* Description   :设定当前 选择项
* Input         :int sel
* Output        :void
* Other         :
* Date          :2013/06/07
*******************************************************************************/
void ListBoxShowMainInfoInterface(void *val)
{
//    int sel = *(int *)val;
//
//    if (m_HListBoxShowMainInfo.hList == 0)
//        return;
//
//    printf("ListBoxShowMainInfoInterface  sel=%d \n",sel);
//
//    if ((sel < (int)LISTBOX_GetNumItems(m_HListBoxShowMainInfo.hList)) && (sel >= 0))
//        LISTBOX_SetSel(m_HListBoxShowMainInfo.hList, sel);
}

/*******************************************************************************
* Function Name :_ListBoxShowMainInfoKeyDown
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/15
*******************************************************************************/
void _ListBoxShowMainInfoKeyDown(void)
{
	  char curIndex=0;
	  char curIndexDisable=0;

    curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
    if(BUTTON_IsPressed(m_HListBoxShowMainInfo.hBtnRtn))//返回键被按下
    {
        BUTTON_SetPressed(m_HListBoxShowMainInfo.hBtnRtn,0);
        LISTBOX_SetBkColor(m_HListBoxShowMainInfo.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        while(curIndexDisable)
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
        }
        LISTBOX_SetSel(m_HListBoxShowMainInfo.hList,curIndex);
    }
    else
    {
        curIndex = LISTBOX_GetSel(m_HListBoxShowMainInfo.hList);
        curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
        if(curIndex == (LISTBOX_GetNumItems(m_HListBoxShowMainInfo.hList)-1) )
        {
            BUTTON_SetPressed(m_HListBoxShowMainInfo.hBtnRtn,1);
            LISTBOX_SetBkColor(m_HListBoxShowMainInfo.hList,LISTBOX_CI_SEL      , GUI_WHITE);
        }
        else
        {
        	  curIndex++;
        	  curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
            while(curIndexDisable)
            {
                curIndex++;
                curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
            }
            LISTBOX_SetSel(m_HListBoxShowMainInfo.hList,curIndex);
        }
    }
}

/*******************************************************************************
* Function Name :_ListBoxShowMainInfoKeyUp
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/15
*******************************************************************************/
void _ListBoxShowMainInfoKeyUp(void)
{
	  char curIndex =0;
	  char curIndexDisable =0;
	  char curLen= LISTBOX_GetNumItems(m_HListBoxShowMainInfo.hList);

    curIndex = curLen-1;
    curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
    if(BUTTON_IsPressed(m_HListBoxShowMainInfo.hBtnRtn))//返回键被按下
    {
        BUTTON_SetPressed(m_HListBoxShowMainInfo.hBtnRtn,0);
        LISTBOX_SetBkColor(m_HListBoxShowMainInfo.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        while(curIndexDisable)
        {
            if(curIndex>0)
            {
                curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
            }
            else break;
        }
        LISTBOX_SetSel(m_HListBoxShowMainInfo.hList,curIndex);
    }
    else
    {
        curIndex = LISTBOX_GetSel(m_HListBoxShowMainInfo.hList);
        curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
        if(curIndex == 1 )
        {
            BUTTON_SetPressed(m_HListBoxShowMainInfo.hBtnRtn,1);
            LISTBOX_SetBkColor(m_HListBoxShowMainInfo.hList,LISTBOX_CI_SEL      , GUI_WHITE);
        }
        else
        {
            if(curIndex>0)
            {
                curIndex--;
        	      curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
        	      while(curIndexDisable)
                {
                    if(curIndex>0)
                    {
                        curIndex--;
                        curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
                    }
                    else break;
                }
            }
            LISTBOX_SetSel(m_HListBoxShowMainInfo.hList,curIndex);
        }
    }
}


/*******************************************************************************
* Function Name :_ListBoxShowMainInfoKeyEnter
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/15
*******************************************************************************/
void _ListBoxShowMainInfoKeyEnter(void)
{
     int id = 0;
     if(BUTTON_IsPressed(m_HListBoxShowMainInfo.hBtnRtn))//返回键被按下
     {
         WIN_Exit(0);
     }
     else
     {
         WIN_Enter((int)&id);
     }
}

WIN_INFO_TYPE g_ListBoxShowMainInfo = {                         //列表窗口
    &m_HListBoxShowMainInfo.hFrame,
    _ListBoxShowMainInfoCreate,
    _ListBoxShowMainInfoDestroy,
};



/******************************列表窗口***************************************/
typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hBtnRtn;
    GUI_HWIN hText;
    GUI_HWIN hTextExp;
    GUI_HWIN hTextMethod;
}HELP_INFO_SHOW_TYPE;
static HELP_INFO_SHOW_TYPE m_WinShowHelpInfo = {0};                         //列表窗口句柄

/*******************************************************************************
* Function Name :_WinShowHelpInfoCallback
* Description   :回调函数
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _WinShowHelpInfoCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            break;
        case GUI_KEY_DOWN:
            break;
        case GUI_KEY_ENTER:
            WIN_Exit(0);
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

/*******************************************************************************
* Function Name :_WinShowHelpInfoCreate
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _WinShowHelpInfoCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    char            *pBuffter   = g_LCDBuff;
     char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);

    //建立新窗口
    m_WinShowHelpInfo.hFrame = FRAMEWIN_CreateAsChild(0, 0, LCD_HSIZE+3, LCD_VSIZE+3 ,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);

    FRAMEWIN_SetFont(m_WinShowHelpInfo.hFrame, &GUI_Fontsong16all);  //字体
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_WinShowHelpInfo.hFrame, 0);             //显示标题
    //FRAMEWIN_SetTitleHeight(m_HListBox.hFrame, 24);         //标题宽度
    //FRAMEWIN_SetTextAlign(m_HListBoxShowMainInfo.hFrame, GUI_TA_HCENTER | GUI_TA_HCENTER);

    pMenu = BT_GetRightChild(pMenu);
    val = BT_GetLeftDepth(pMenu);

    hWin = WM_GetFirstChild(m_WinShowHelpInfo.hFrame);             //获得窗口桌面

    //建立列表窗口
    m_WinShowHelpInfo.hBtnRtn    = BUTTON_CreateAsChild(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, 23, 23,hWin,NULL, WM_CF_SHOW);
    m_WinShowHelpInfo.hText      = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+23, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_WinShowHelpInfo.hTextExp   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+PER_CM_OFFSET  , PER_CM_OFFSET*4.5, PER_CM_OFFSET*2, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_WinShowHelpInfo.hTextMethod= TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+PER_CM_OFFSET*3, PER_CM_OFFSET*4.5, PER_CM_OFFSET*2, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");

    /**************************返回按键**************************/
    hWin = m_WinShowHelpInfo.hBtnRtn;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmbackUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmbackSel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmbackUnsel,0,0);
    BUTTON_SetPressed(hWin,1);

    /**************************返回标题**************************/
    hWin = m_WinShowHelpInfo.hText;
    TEXT_SetFont(m_WinShowHelpInfo.hText,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_BLUE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);

    /**************************返回标题**************************/
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(GetExpInfoPtr(dataStructInterface.helpExpIndex,g_LanguageIndex),strShow,STRSHOWBUF_SIZE);
    hWin = m_WinShowHelpInfo.hTextExp;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_TOP);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetWrapMode(hWin,GUI_WRAPMODE_CHAR);
    TEXT_SetText(hWin, strShow);

    /**************************返回标题**************************/
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(GetHandleInfoPtr(dataStructInterface.helpMethodIndex,g_LanguageIndex),strShow,STRSHOWBUF_SIZE);
    hWin = m_WinShowHelpInfo.hTextMethod;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_TOP);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetWrapMode(hWin,GUI_WRAPMODE_CHAR);
    TEXT_SetText(hWin, strShow);

    WM_SetCallback(WM_HBKWIN, _WinShowHelpInfoCallback);
}

/*******************************************************************************
* Function Name :_WinShowHelpInfoDestroy
* Description   :
* Input         :void * p
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _WinShowHelpInfoDestroy(void *p)
{
    WM_DeleteWindow(m_WinShowHelpInfo.hFrame);
    WM_DeleteWindow(m_WinShowHelpInfo.hBtnRtn);
    WM_DeleteWindow(m_WinShowHelpInfo.hText);
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_WinShowHelpInfo, 0, sizeof(m_WinShowHelpInfo));
}

/*******************************************************************************
* Function Name :WinShowHelpInfoInterface
* Description   :设定当前 选择项
* Input         :int sel
* Output        :void
* Other         :
* Date          :2013/06/07
*******************************************************************************/
void WinShowHelpInfoInterface(void *val)
{
//    int sel = *(int *)val;
//
//    if (m_HListView.hList == 0)
//        return;
//
//    if ((sel < (int)LISTVIEW_GetNumRows(m_HListView.hList)) && (sel >= 0))
//        LISTVIEW_SetSel(m_HListView.hList, sel);
}



WIN_INFO_TYPE g_WinShowHelpInfo = {                         //列表窗口
    &m_WinShowHelpInfo.hFrame,
    _WinShowHelpInfoCreate,
    _WinShowHelpInfoDestroy,
};


/************************************就地操作菜单*******************************************/
typedef struct {
    GUI_HWIN hFrame;        //框架
    GUI_HWIN hBtnRtn;       //返回
    GUI_HWIN hBtnState;     //开关状态位图显示
    GUI_HWIN hBtnLeft;      //左边位图按钮
    GUI_HWIN hBtnRight;     //右边位图按钮
    GUI_HWIN hBtnInfo;      //信息按钮
    GUI_HWIN hTextHeader;   //窗口标题
    GUI_HWIN hTextInfo;     //信息
    GUI_HWIN hTextNum1;     //百分比数字1
    GUI_HWIN hTextNum2;     //百分比数字2
    GUI_HWIN hProgbar;      //进度条
}LOCAL_OPERATION_TYPE;

static LOCAL_OPERATION_TYPE m_WinLocalOp = {0};     //就地操作

/*******************************************************************************
* Function Name :_WinLocalOpKeyDown
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
void _WinLocalOpKeyDown(void)
{
    if(BUTTON_IsPressed(m_WinLocalOp.hBtnRtn))//返回被按下
    {
        BUTTON_SetPressed(m_WinLocalOp.hBtnRtn,0);
        TEXT_SetBkColor(m_WinLocalOp.hTextInfo,GUI_ORANGE);
        g_hdlMenuFocus = MAIN_MENU_FOCUS_TEXT;
    }
    else if(MAIN_MENU_FOCUS_TEXT == g_hdlMenuFocus)
    {
        g_hdlMenuFocus = MAIN_MENU_FOCUS_LIST;
        TEXT_SetBkColor(m_WinLocalOp.hTextInfo,GUI_WHITE);
        BUTTON_SetPressed(m_WinLocalOp.hBtnLeft,1);
    }
    else if(BUTTON_IsPressed(m_WinLocalOp.hBtnLeft))
    {
        BUTTON_SetPressed(m_WinLocalOp.hBtnLeft,0);
        BUTTON_SetPressed(m_WinLocalOp.hBtnRight,1);
    }
    else if(BUTTON_IsPressed(m_WinLocalOp.hBtnRight))
    {
        BUTTON_SetPressed(m_WinLocalOp.hBtnRtn,1);
        BUTTON_SetPressed(m_WinLocalOp.hBtnRight,0);
    }
}

/*******************************************************************************
* Function Name :_WinLocalOpKeyUp
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
void _WinLocalOpKeyUp(void)
{
    if(BUTTON_IsPressed(m_WinLocalOp.hBtnRtn))//返回被按下
    {
        BUTTON_SetPressed(m_WinLocalOp.hBtnRtn,0);
        BUTTON_SetPressed(m_WinLocalOp.hBtnRight,1);
    }
    else if(MAIN_MENU_FOCUS_TEXT == g_hdlMenuFocus)
    {
        g_hdlMenuFocus = MAIN_MENU_FOCUS_LIST;
        TEXT_SetBkColor(m_WinLocalOp.hTextInfo,GUI_WHITE);
        BUTTON_SetPressed(m_WinLocalOp.hBtnRtn,1);
    }
    else if(BUTTON_IsPressed(m_WinLocalOp.hBtnLeft))
    {
        g_hdlMenuFocus = MAIN_MENU_FOCUS_TEXT;
        TEXT_SetBkColor(m_WinLocalOp.hTextInfo,GUI_ORANGE);
        BUTTON_SetPressed(m_WinLocalOp.hBtnLeft,0);
    }
    else if(BUTTON_IsPressed(m_WinLocalOp.hBtnRight))
    {
        BUTTON_SetPressed(m_WinLocalOp.hBtnLeft,1);
        BUTTON_SetPressed(m_WinLocalOp.hBtnRight,0);
    }
}


/*******************************************************************************
* Function Name :_WinLocalOpKeyEnter
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
void _WinLocalOpKeyEnter(void)
{
    int id = 0;
    if(BUTTON_IsPressed(m_WinLocalOp.hBtnRtn))//返回被按下
    {
        WIN_Exit(0);
    }
    else if(MAIN_MENU_FOCUS_TEXT == g_hdlMenuFocus)//选中了文本 故障信息显示
    {
        WIN_Enter((int)&id);
    }
    else if(BUTTON_IsPressed(m_WinLocalOp.hBtnLeft))
    {
        GUI_Delay(200);
        WM_DisableWindow(m_WinLocalOp.hBtnLeft);
        GUI_Delay(200);
        BUTTON_SetPressed(m_WinLocalOp.hBtnLeft,1);
        WM_EnableWindow(m_WinLocalOp.hBtnLeft);
        if(dataStructInterface.numMid1 < 99)
        {
            dataStructInterface.numMid1+=1;
            dataStructInterface.stateOpen  = 0;
            dataStructInterface.stateClose = 0;
            dataStructInterface.stateMid   = 1;
        }
        else
        {
            dataStructInterface.numMid1=99;
            dataStructInterface.numMid2=0;
            dataStructInterface.stateClose    = 1;
            dataStructInterface.stateMid   = 0;
        }
        _WinLocalOpRefresh();
    }
    else if(BUTTON_IsPressed(m_WinLocalOp.hBtnRight))
    {
        GUI_Delay(200);
        WM_DisableWindow(m_WinLocalOp.hBtnRight);
        GUI_Delay(200);
        BUTTON_SetPressed(m_WinLocalOp.hBtnRight,1);
        WM_EnableWindow(m_WinLocalOp.hBtnRight);
        if(dataStructInterface.numMid1 > 1)
        {
            dataStructInterface.numMid1    -=1;
            dataStructInterface.stateOpen  = 0;
            dataStructInterface.stateClose = 0;
            dataStructInterface.stateMid   = 1;
        }
        else
        {
            dataStructInterface.numMid1=0;
            dataStructInterface.numMid2=0;
            dataStructInterface.stateOpen    = 1;
            dataStructInterface.stateMid   = 0;
        }
        _WinLocalOpRefresh();
    }
}

/*******************************************************************************
* Function Name :_WinLocalOpRefresh
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
void _WinLocalOpRefresh(void)
{
    GUI_HWIN        hWin        = 0;
    char numShow[8];
    hWin = WM_GetFirstChild(m_WinLocalOp.hFrame);             //获得窗口桌面
    if(dataStructInterface.stateOpen)
    {
        if(m_WinLocalOp.hTextNum1)
        {
            TEXT_SetText(m_WinLocalOp.hTextNum1, "  ");
            WM_DeleteWindow(m_WinLocalOp.hTextNum1);
            m_WinLocalOp.hTextNum1 = 0;
        }
        if(m_WinLocalOp.hTextNum2)
        {
            TEXT_SetText(m_WinLocalOp.hTextNum2, "  ");
            WM_DeleteWindow(m_WinLocalOp.hTextNum2);
            m_WinLocalOp.hTextNum2 = 0;
        }
        if(0 == m_WinLocalOp.hBtnState)  m_WinLocalOp.hBtnState = BUTTON_CreateAsChild(DEBUG_X_OFFSET+150-20, DEBUG_Y_OFFSET+23+2, 40, 40,hWin,NULL, WM_CF_SHOW);
        hWin = m_WinLocalOp.hBtnState;
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmopens,0,0);
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmopens,0,0);
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmopens,0,0);
        BUTTON_SetPressed(hWin,0);
    }
    else if(dataStructInterface.stateClose)
    {
        if(m_WinLocalOp.hTextNum1)
        {
            TEXT_SetText(m_WinLocalOp.hTextNum1, "  ");
            WM_DeleteWindow(m_WinLocalOp.hTextNum1);
            m_WinLocalOp.hTextNum1 = 0;
        }
        if(m_WinLocalOp.hTextNum2)
        {
            TEXT_SetText(m_WinLocalOp.hTextNum2, "  ");
            WM_DeleteWindow(m_WinLocalOp.hTextNum2);
            m_WinLocalOp.hTextNum2 = 0;
        }
        if(0 == m_WinLocalOp.hBtnState) m_WinLocalOp.hBtnState  = BUTTON_CreateAsChild(DEBUG_X_OFFSET+150-20, DEBUG_Y_OFFSET+23+2, 40, 40,hWin,NULL, WM_CF_SHOW);
        hWin = m_WinLocalOp.hBtnState;
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmcloses,0,0);
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmcloses,0,0);
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmcloses,0,0);
        BUTTON_SetPressed(hWin,0);
    }
    else if(dataStructInterface.stateMid)
    {
        if(m_WinLocalOp.hBtnState)
        {
            WM_DeleteWindow(m_WinLocalOp.hBtnState);
            m_WinLocalOp.hBtnState = 0;
        }
        if(0 == m_WinLocalOp.hTextNum1) m_WinLocalOp.hTextNum1  = TEXT_CreateEx( DEBUG_X_OFFSET+150-34, DEBUG_Y_OFFSET+23+2, 33, 33, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
        if(0 == m_WinLocalOp.hTextNum2) m_WinLocalOp.hTextNum2  = TEXT_CreateEx( DEBUG_X_OFFSET+150   , DEBUG_Y_OFFSET+23+0+16, 32, 16, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
        hWin = m_WinLocalOp.hTextNum1;
        TEXT_SetFont(hWin,&GUI_Fontsong33);
        GUI_UC_SetEncodeUTF8();
        TEXT_SetBkColor(hWin,GUI_WHITE);
        TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
        TEXT_SetTextColor(hWin,GUI_BLACK);
        memset(numShow,0,sizeof(numShow));
        StrShowClear();
        sprintf(numShow,"%2d",dataStructInterface.numMid1);
        enc_unicode_to_utf8_str(numShow,strShow,STRSHOWBUF_SIZE);
        TEXT_SetText(hWin, strShow);

        hWin = m_WinLocalOp.hTextNum2;
        TEXT_SetFont(hWin,&GUI_Fontsong16all);
        GUI_UC_SetEncodeUTF8();
        TEXT_SetBkColor(hWin,GUI_WHITE);
        TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
        TEXT_SetTextColor(hWin,GUI_BLACK);
        memset(numShow,0,sizeof(numShow));
        StrShowClear();
        sprintf(numShow,".%1d",dataStructInterface.numMid2);
        numShow[2] = '%';
        enc_unicode_to_utf8_str(numShow,strShow,STRSHOWBUF_SIZE);
        TEXT_SetText(hWin, strShow);
    }
    PROGBAR_SetValue(m_WinLocalOp.hProgbar,dataStructInterface.numMid1);
}


/*******************************************************************************
* Function Name :_WinLocalOpCallback
* Description   :
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
static void _WinLocalOpCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
            case GUI_KEY_DOWN:
                _WinLocalOpKeyDown();
                break;
            case GUI_KEY_UP:
                _WinLocalOpKeyUp();
                break;
            case GUI_KEY_ENTER:
                _WinLocalOpKeyEnter();
                break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}
/*******************************************************************************
* Function Name :_WinLocalOpCreate
* Description   :主界面窗口建立
* Input         :void * p
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
static void _WinLocalOpCreate(void *p)
{
    unsigned int i=0;
	 MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
	 char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    char numShow[8];
    GUI_HWIN        hWin        = 0;

    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    /* Enable high resolution for antialiasing */
    //GUI_AA_EnableHiRes();
    GUI_AA_SetFactor(MAG);

    /* Create GUI_AUTODEV-objects */
    //GUI_MEMDEV_CreateAuto(&m_MainWin.AutoDev);

/*********************************标题**********************************/
   
   

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);

    //建立新窗口
    m_WinLocalOp.hFrame = FRAMEWIN_CreateAsChild(0, 0, LCD_HSIZE+3, LCD_VSIZE+3 ,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);

    FRAMEWIN_SetFont(m_WinLocalOp.hFrame, &GUI_Fontsong16all);  //字体
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_WinLocalOp.hFrame, 0);             //显示标题

    hWin = WM_GetFirstChild(m_WinLocalOp.hFrame);             //获得窗口桌面

    //建立列表窗口
    m_WinLocalOp.hBtnRtn    = BUTTON_CreateAsChild(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, 23, 23,hWin,NULL, WM_CF_SHOW);
    m_WinLocalOp.hTextHeader= TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+23, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");

    /***********************************返回按钮************************************/
    hWin = m_WinLocalOp.hBtnRtn;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmbackUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmbackSel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmbackUnsel,0,0);
    BUTTON_SetPressed(hWin,1);

    /***********************************标题，中英文可以自由切换************************************/
    hWin = m_WinLocalOp.hTextHeader;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_BLUE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    /*********************************主界面显示数字还是图标**********************************/
    hWin = WM_GetFirstChild(m_WinLocalOp.hFrame);             //获得窗口桌面

    if(dataStructInterface.stateOpen)
    {
        m_WinLocalOp.hBtnState  = BUTTON_CreateAsChild(DEBUG_X_OFFSET+150-20, DEBUG_Y_OFFSET+23+2, 40, 40,hWin,NULL, WM_CF_SHOW);
        hWin = m_WinLocalOp.hBtnState;
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmopens,0,0);
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmopens,0,0);
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmopens,0,0);
        BUTTON_SetPressed(hWin,0);
    }
    else if(dataStructInterface.stateClose)
    {
        m_WinLocalOp.hBtnState  = BUTTON_CreateAsChild(DEBUG_X_OFFSET+150-20, DEBUG_Y_OFFSET+23+2, 40, 40,hWin,NULL, WM_CF_SHOW);
        hWin = m_WinLocalOp.hBtnState;
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmcloses,0,0);
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmcloses,0,0);
        BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmcloses,0,0);
        BUTTON_SetPressed(hWin,0);
    }
    else if(dataStructInterface.stateMid)
    {
        m_WinLocalOp.hTextNum1  = TEXT_CreateEx( DEBUG_X_OFFSET+150-34, DEBUG_Y_OFFSET+23+2, 33, 33, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
        m_WinLocalOp.hTextNum2  = TEXT_CreateEx( DEBUG_X_OFFSET+150   , DEBUG_Y_OFFSET+23+0+16, 32, 16, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
        hWin = m_WinLocalOp.hTextNum1;
        TEXT_SetFont(hWin,&GUI_Fontsong33);
        GUI_UC_SetEncodeUTF8();
        TEXT_SetBkColor(hWin,GUI_WHITE);
        TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
        TEXT_SetTextColor(hWin,GUI_BLACK);
        memset(numShow,0,sizeof(numShow));
        StrShowClear();
        sprintf(numShow,"%2d",dataStructInterface.numMid1);
        enc_unicode_to_utf8_str(numShow,strShow,STRSHOWBUF_SIZE);
        TEXT_SetText(hWin, strShow);

        hWin = m_WinLocalOp.hTextNum2;
        TEXT_SetFont(hWin,&GUI_Fontsong16all);
        GUI_UC_SetEncodeUTF8();
        TEXT_SetBkColor(hWin,GUI_WHITE);
        TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
        TEXT_SetTextColor(hWin,GUI_BLACK);
        memset(numShow,0,sizeof(numShow));
        StrShowClear();
        sprintf(numShow,".%1d",dataStructInterface.numMid2);
        numShow[2] = '%';
        enc_unicode_to_utf8_str(numShow,strShow,STRSHOWBUF_SIZE);
        TEXT_SetText(hWin, strShow);
    }
    /*********************************主界面开关的图标**********************************/
    hWin = WM_GetFirstChild(m_WinLocalOp.hFrame);
    m_WinLocalOp.hBtnRight  = BUTTON_CreateAsChild(DEBUG_X_OFFSET+250, DEBUG_Y_OFFSET+2*PER_CM_OFFSET, 50, 50,hWin,NULL, WM_CF_SHOW);
    m_WinLocalOp.hBtnLeft   = BUTTON_CreateAsChild(DEBUG_X_OFFSET    , DEBUG_Y_OFFSET+2*PER_CM_OFFSET, 50, 50,hWin,NULL, WM_CF_SHOW);

    hWin = m_WinLocalOp.hBtnLeft;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bm111_3,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bm111_2,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bm111,0,0);
    BUTTON_SetPressed(hWin,0);
    //暂时少一个状态
    if(0 == dataStructInterface.stateClose)
    {
        BUTTON_SetPressed(hWin,0);
    }
    else if(1 == dataStructInterface.stateClose)
    {
        BUTTON_SetPressed(hWin,0);
    }

    //暂时少一个状态
    hWin = m_WinLocalOp.hBtnRight;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bm222_3,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bm222_2,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bm222,0,0);
    BUTTON_SetPressed(hWin,0);
    if(0 == dataStructInterface.stateOpen)
    {
        BUTTON_SetPressed(hWin,0);
    }
    else if(1 == dataStructInterface.stateOpen)
    {
        BUTTON_SetPressed(hWin,0);
    }

    /*********************************主界面信息文本显示**********************************/
    hWin = m_WinLocalOp.hFrame;
    StrShowClear();
    if(LANGUAGE_CN == g_LanguageIndex)
    {
        i = strlen(infoWinMainCN[dataStructInterface.IndexWinMainInfo]);
        enc_unicode_to_utf8_str(infoWinMainCN[dataStructInterface.IndexWinMainInfo],strShow,STRSHOWBUF_SIZE);
    }
    else if(LANGUAGE_EN == g_LanguageIndex)
    {
        i = strlen(infoWinMainEN[dataStructInterface.IndexWinMainInfo]);
        enc_unicode_to_utf8_str(infoWinMainEN[dataStructInterface.IndexWinMainInfo],strShow,STRSHOWBUF_SIZE);
    }
    m_WinLocalOp.hTextInfo = TEXT_CreateAsChild(20+(300-i*8)/2,5+69+3,23+i*8,20,hWin,NULL,WM_CF_SHOW,strShow,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetBkColor(m_WinLocalOp.hTextInfo,GUI_WHITE);
    TEXT_SetFont(m_WinLocalOp.hTextInfo,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    if(MAIN_MENU_FOCUS_TEXT == g_hdlMenuFocus)
    {
        TEXT_SetBkColor(m_WinLocalOp.hTextInfo,GUI_ORANGE);
    }
    else
    {
        TEXT_SetBkColor(m_WinLocalOp.hTextInfo,GUI_WHITE);
    }

    hWin = m_WinLocalOp.hFrame;
    m_WinLocalOp.hBtnInfo  = BUTTON_CreateAsChild(DEBUG_X_OFFSET+(300-i*8)/2-23, DEBUG_Y_OFFSET+69+2, 23, 23,hWin,NULL, WM_CF_SHOW);
    hWin = m_WinLocalOp.hBtnInfo;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmerror,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmerror,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmerror,0,0);

    /*********************************主界面进度条显示**********************************/
    hWin = m_WinLocalOp.hFrame;
    m_WinLocalOp.hProgbar    = PROGBAR_CreateAsChild(DEBUG_X_OFFSET+50+5+5,DEBUG_Y_OFFSET+2*46+10+4, 190, 26,hWin,NULL, WM_CF_SHOW);
    PROGBAR_SetText(m_WinLocalOp.hProgbar,"");
    PROGBAR_SetValue(m_WinLocalOp.hProgbar,dataStructInterface.numMid1);

    WM_SetCallback(WM_HBKWIN,_WinLocalOpCallback);
    WM_SetFocus(WM_HBKWIN);
}



/*******************************************************************************
* Function Name :__WinLocalOpDestroy
* Description   :窗口销毁
* Input         :void * p
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
static void _WinLocalOpDestroy(void *p)
{
    /* Delete GUI_AUTODEV-objects */
    WM_DeleteWindow(m_WinLocalOp.hTextHeader);
    WM_DeleteWindow(m_WinLocalOp.hTextInfo);
    WM_DeleteWindow(m_WinLocalOp.hTextNum1);
    WM_DeleteWindow(m_WinLocalOp.hTextNum2);
    WM_DeleteWindow(m_WinLocalOp.hProgbar);
    WM_DeleteWindow(m_WinLocalOp.hBtnRtn);
    WM_DeleteWindow(m_WinLocalOp.hBtnState);
    WM_DeleteWindow(m_WinLocalOp.hBtnLeft);
    WM_DeleteWindow(m_WinLocalOp.hBtnRight);
    WM_DeleteWindow(m_WinLocalOp.hBtnInfo);
    WM_DeleteWindow(m_WinLocalOp.hFrame);
    WM_SetCallback(WM_HBKWIN,NULL);
    memset(&m_WinLocalOp, 0, sizeof(m_WinLocalOp));
}


/*******************************************************************************
* Function Name :_WinLocalOpInterface
* Description   :设定当前 选择项
* Input         :int sel
* Output        :void
* Other         :
* Date          :2013/06/07
*******************************************************************************/
void _WinLocalOpInterface(void *val)
{
//    int sel = *(int *)val;
//
//    if (m_HListView.hList == 0)
//        return;
//
//    if ((sel < (int)LISTVIEW_GetNumRows(m_HListView.hList)) && (sel >= 0))
//        LISTVIEW_SetSel(m_HListView.hList, sel);
}


WIN_INFO_TYPE g_WinLocalOp = {
    &m_WinLocalOp.hFrame,
    _WinLocalOpCreate,
    _WinLocalOpDestroy,
};

/*******************************************************************************
* Function Name :StrShowClear
* Description   :窗口销毁
* Input         :void * p
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
void StrShowClear(void)
{
    unsigned char i;
    for(i=0;i<STRSHOWBUF_SIZE;i++) strShow[i] = '\0';
}


/*******************************************************************************
* Function Name :_DebugUseFreeBytesShow
* Description   :显示内存数
* Input         :void * p
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
void _DebugUseFreeBytesShow(void)
{
    printf("GUI_ALLOC_GetNumFreeBytes = %d \n",GUI_ALLOC_GetNumFreeBytes());
    printf("GUI_ALLOC_GetNumUsedBytes = %d \n",GUI_ALLOC_GetNumUsedBytes());
}


/******************************主菜单窗口***************************************/
typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hBtnHome;
    GUI_HWIN hText;
    GUI_HWIN hList;
}MAIN_MENU_TYPE;
static MAIN_MENU_TYPE m_MainMenu = {0};                         //主菜单窗口

/*******************************************************************************
* Function Name :_WinMainMenuKeyDown
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _WinMainMenuKeyDown(void )
{
    char curIndex=0;
    char curIndexDisable=0;
    curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
    if(BUTTON_IsPressed(m_MainMenu.hBtnHome))
    {
        BUTTON_SetPressed(m_MainMenu.hBtnHome,0);
        LISTBOX_SetBkColor(m_MainMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        while(curIndexDisable)
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
        }
        LISTBOX_SetSel(m_MainMenu.hList,curIndex);
    }
     else
    {
        curIndex = LISTBOX_GetSel(m_MainMenu.hList);
        curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
        if(curIndex == (LISTBOX_GetNumItems(m_MainMenu.hList)-1) )
        {
            BUTTON_SetPressed(m_MainMenu.hBtnHome,1);
            LISTBOX_SetBkColor(m_MainMenu.hList,LISTBOX_CI_SEL      , GUI_WHITE);
        }
        else
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
            while(curIndexDisable)
            {
                curIndex++;
                curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
            }
            LISTBOX_SetSel(m_MainMenu.hList,curIndex);
        }
    }
}


/*******************************************************************************
* Function Name :_WinMainMenuKeyEnter
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _WinMainMenuKeyEnter(void )
{
    int id = 0;
    if(BUTTON_IsPressed(m_MainMenu.hBtnHome))
    {
        WIN_Exit(0);
    }
    else
    {
        id = LISTBOX_GetSel(m_MainMenu.hList);
        WIN_Enter(&id);
    }
}

/*******************************************************************************
* Function Name :_WinMainMenuKeyUp
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _WinMainMenuKeyUp(void)
{
    char curIndex =0;
    char curIndexDisable =0;
    char curLen= LISTBOX_GetNumItems(m_MainMenu.hList);

    curIndex = curLen-1;
    curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
    if(BUTTON_IsPressed(m_MainMenu.hBtnHome))//返回键被按下
    {
        BUTTON_SetPressed(m_MainMenu.hBtnHome,0);
        LISTBOX_SetBkColor(m_MainMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        while(curIndexDisable)
        {
            if(curIndex>0)
            {
                curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
            }
            else break;
        }
        LISTBOX_SetSel(m_MainMenu.hList,curIndex);
    }
    else
    {
        curIndex = LISTBOX_GetSel(m_MainMenu.hList);
        curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);

        if(curIndex>0)
        {
            curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
                while(curIndexDisable)
            {
                if(curIndex>0)
                {
                    curIndex--;
                    curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
                }
                else break;
            }
        }
        else if(curIndex == 0 )
        {
            BUTTON_SetPressed(m_MainMenu.hBtnHome,1);
            LISTBOX_SetBkColor(m_MainMenu.hList,LISTBOX_CI_SEL      , GUI_WHITE);
        }
        LISTBOX_SetSel(m_MainMenu.hList,curIndex);
    }
}

/*******************************************************************************
* Function Name :_WinMainMenuCallback
* Description   :回调函数
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
static void _WinMainMenuCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinMainMenuKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinMainMenuKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinMainMenuKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

/*******************************************************************************
* Function Name :_WinMainMenuCreate
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _WinMainMenuCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);

    //建立新窗口
    m_MainMenu.hFrame = FRAMEWIN_CreateAsChild(0, 0, LCD_HSIZE+3, LCD_VSIZE+3 ,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);

    FRAMEWIN_SetFont(m_MainMenu.hFrame, &GUI_Fontsong16all);  //字体
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_MainMenu.hFrame, 0);             //显示标题

    hWin = WM_GetFirstChild(m_MainMenu.hFrame);             //获得窗口桌面

    //建立列表窗口
    m_MainMenu.hBtnHome  = BUTTON_CreateAsChild(DEBUG_X_OFFSET+150-11, DEBUG_Y_OFFSET, 23, 23,hWin,NULL, WM_CF_SHOW);
    m_MainMenu.hText     = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+25, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_MainMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23+25+10, PER_CM_OFFSET*4.5, PER_CM_OFFSET*3, hWin, WM_CF_SHOW, NULL, NULL,NULL);
    /**************************返回按键**************************/
    hWin = m_MainMenu.hBtnHome;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmbackUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmhomeSel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmhomeUnsel,0,0);
    BUTTON_SetPressed(hWin,1);

    /**************************返回标题**************************/
    hWin = m_MainMenu.hText;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_BLUE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);

    /**************************LIST标题**************************/
    hWin = m_MainMenu.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 7);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_DISABLED , GUI_WHITE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SEL      , GUI_WHITE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SELFOCUS , GUI_ORANGE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_UNSEL    , GUI_WHITE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_DISABLED , GUI_BLUE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SEL      , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SELFOCUS , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_UNSEL    , GUI_BLACK);
    LISTBOX_SetAutoScrollV(hWin,1);

    for(i=0;i<MAIN_MENU_NUM;i++)
    {
    	memset(strShow,0,sizeof(strShow));
        if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str(menuMainCn[i],strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str(menuMainEn[i],strShow,STRSHOWBUF_SIZE);
        LISTBOX_AddString(hWin, strShow);
    }

    WM_SetCallback(WM_HBKWIN, _WinMainMenuCallback);
}

/*******************************************************************************
* Function Name :_WinMainMenuDestroy
* Description   :
* Input         :void * p
* Output        :void
* Other         :
* Date          :2013/06/05
*******************************************************************************/
static void _WinMainMenuDestroy(void *p)
{
    WM_DeleteWindow(m_MainMenu.hFrame);
    WM_DeleteWindow(m_MainMenu.hList);
    WM_DeleteWindow(m_MainMenu.hBtnHome);
    WM_DeleteWindow(m_MainMenu.hText);
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_MainMenu, 0, sizeof(m_MainMenu));
}

/*******************************************************************************
* Function Name :_WinMainMenuInterface
* Description   :设定当前 选择项
* Input         :int sel
* Output        :void
* Other         :
* Date          :2013/06/07
*******************************************************************************/
void _WinMainMenuInterface(void *val)
{
    int sel = *(int *)val;

    if(sel == 100 )
    {
        return ;
    }
    else
    {
        if (m_MainMenu.hList == 0) return;

        if ((sel < (int)LISTBOX_GetNumItems(m_MainMenu.hList)) && (sel >= 0))
        {
            BUTTON_SetPressed(m_MainMenu.hBtnHome,0);
            LISTBOX_SetBkColor(m_MainMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
            LISTBOX_SetSel(m_MainMenu.hList, sel);
        }
    }
}

/*******************************************************************************
* Function Name :_voidFun
* Description   :空函数
* Input         :int sel
* Output        :void
* Other         :
* Date          :2018/04/21
*******************************************************************************/
void _voidFun(void)
{
    return ;
}



WIN_INFO_TYPE g_WinMainMenu = {                         //列表窗口
    &m_MainMenu.hFrame,
    _WinMainMenuCreate,
    _WinMainMenuDestroy,
};




/******************************主菜单窗口***************************************/
typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hBtnRtn;
    GUI_HWIN hBtnHome;
    GUI_HWIN hText;
    GUI_HWIN hList;
}COMMON_MENU_TYPE;
static COMMON_MENU_TYPE m_CommonMenu = {0};                         //主菜单窗口

/*******************************************************************************
* Function Name :_WinCommonMenuKeyDown
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _WinCommonMenuKeyDown(void )
{
    char curIndex=0;
    char curIndexDisable=0;

    curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
    if(BUTTON_IsPressed(m_CommonMenu.hBtnRtn))//返回键被按下
    {
        BUTTON_SetPressed(m_CommonMenu.hBtnRtn,0);
        BUTTON_SetPressed(m_CommonMenu.hBtnHome,1);
    }
    else if(BUTTON_IsPressed(m_CommonMenu.hBtnHome))//Home键被按下
    {
        BUTTON_SetPressed(m_CommonMenu.hBtnHome,0);
        LISTBOX_SetBkColor(m_CommonMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        while(curIndexDisable)  //当前的条目失效，是标题
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
        }
        LISTBOX_SetSel(m_CommonMenu.hList,curIndex);
    }
    else
    {
        curIndex = LISTBOX_GetSel(m_CommonMenu.hList);
        curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
        if(curIndex == (LISTBOX_GetNumItems(m_CommonMenu.hList)-1) ) //是List最后一个条目
        {
            BUTTON_SetPressed(m_CommonMenu.hBtnRtn,1);
            LISTBOX_SetBkColor(m_CommonMenu.hList,LISTBOX_CI_SEL      , GUI_WHITE);
        }
        else
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
            while(curIndexDisable)
            {
                if(curIndex == (LISTBOX_GetNumItems(m_CommonMenu.hList)-1) ) //是List最后一个条目
                {
                    BUTTON_SetPressed(m_CommonMenu.hBtnRtn,1);
                    LISTBOX_SetBkColor(m_CommonMenu.hList,LISTBOX_CI_SEL      , GUI_WHITE);
                    return ;
                }
                curIndex++;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
            }
            LISTBOX_SetSel(m_CommonMenu.hList,curIndex);
        }
    }
}

/*******************************************************************************
* Function Name :_WinCommonMenuKeyUp
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _WinCommonMenuKeyUp(void)
{
    char curIndex =0;
    char curIndexDisable =0;
    char curLen= LISTBOX_GetNumItems(m_CommonMenu.hList);

    curIndex = curLen-1;
    curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
    if(BUTTON_IsPressed(m_CommonMenu.hBtnRtn))//返回键被按下
    {
        BUTTON_SetPressed(m_CommonMenu.hBtnRtn,0);
        LISTBOX_SetBkColor(m_CommonMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        while(curIndexDisable)
        {
            if(curIndex>0)
            {
                curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
            }
            else break;
        }
        LISTBOX_SetSel(m_CommonMenu.hList,curIndex);
    }
    else if(BUTTON_IsPressed(m_CommonMenu.hBtnHome))//返回键被按下
    {
        BUTTON_SetPressed(m_CommonMenu.hBtnHome,0);
        BUTTON_SetPressed(m_CommonMenu.hBtnRtn,1);
    }
    else
    {
        curIndex = LISTBOX_GetSel(m_CommonMenu.hList);
        curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
        if(curIndex>0)
        {
            curIndex--;
            curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
            while(curIndexDisable)
            {
                if(curIndex>0)
                {
                    curIndex--;
                    curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
                }
                else
                {
                    BUTTON_SetPressed(m_CommonMenu.hBtnHome,1);
                    LISTBOX_SetBkColor(m_CommonMenu.hList,LISTBOX_CI_SEL      , GUI_WHITE);
                    break;
                }
            }
        }
        else
        {
            BUTTON_SetPressed(m_CommonMenu.hBtnHome,1);
            LISTBOX_SetBkColor(m_CommonMenu.hList,LISTBOX_CI_SEL      , GUI_WHITE);
        }
        LISTBOX_SetSel(m_CommonMenu.hList,curIndex);
    }
}

/*******************************************************************************
* Function Name :_WinCommonMenuKeyEnter
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _WinCommonMenuKeyEnter(void)
{
    int id = 0;
    int i=0;
    int j=0;
    if(BUTTON_IsPressed(m_CommonMenu.hBtnRtn))//返回键被按下
    {
        WIN_Exit(0);
    }
    else if(BUTTON_IsPressed(m_CommonMenu.hBtnHome))//返回键被按下
    {
        WIN_Home();
    }
    else
    {
        while(i<LISTBOX_GetNumItems(m_CommonMenu.hList))
        {
            if(0==LISTBOX_GetItemDisabled(m_CommonMenu.hList,i))
            {
                if(i==LISTBOX_GetSel(m_CommonMenu.hList))
                {
                    id = j;
                    WIN_Enter(&id);
                    break;
                }
                j++;
            }
            i++;
        }
    }
}

/*******************************************************************************
* Function Name :_WinCommonMenuCallback
* Description   :回调函数
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
static void _WinCommonMenuCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinCommonMenuKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinCommonMenuKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinCommonMenuKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

/*******************************************************************************
* Function Name :_WinCommonMenuCreate
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
static void _WinCommonMenuCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    char            *pContentCn = pMenu->data->menutitleCn;
    char            *pContentEn = pMenu->data->menutitleEn;

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);

    //建立新窗口
    m_CommonMenu.hFrame = FRAMEWIN_CreateAsChild(0, 0, LCD_HSIZE+3, LCD_VSIZE+3 ,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);

    FRAMEWIN_SetFont(m_CommonMenu.hFrame, &GUI_Fontsong16all);  //字体
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_CommonMenu.hFrame, 0);             //显示标题

    hWin = WM_GetFirstChild(m_CommonMenu.hFrame);             //获得窗口桌面

    //建立列表窗口
    m_CommonMenu.hBtnRtn   = BUTTON_CreateAsChild(DEBUG_X_OFFSET+150-23, DEBUG_Y_OFFSET, 23, 23,hWin,NULL, WM_CF_SHOW);
    m_CommonMenu.hBtnHome  = BUTTON_CreateAsChild(DEBUG_X_OFFSET+150, DEBUG_Y_OFFSET, 23, 23,hWin,NULL, WM_CF_SHOW);
    m_CommonMenu.hText     = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CommonMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23+23+10, PER_CM_OFFSET*4.5, PER_CM_OFFSET*3, hWin, WM_CF_SHOW, NULL, NULL,NULL);
    /**************************返回按键**************************/
    hWin = m_CommonMenu.hBtnRtn;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmbackUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmbackSel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmbackUnsel,0,0);
    BUTTON_SetPressed(hWin,1);
    /**************************Home按键**************************/
    hWin = m_CommonMenu.hBtnHome;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmhomeUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmhomeSel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmhomeUnsel,0,0);
    BUTTON_SetPressed(hWin,0);

    /**************************返回标题**************************/
    hWin = m_CommonMenu.hText;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_BLUE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);

    /**************************LIST标题**************************/
    hWin = m_CommonMenu.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 7);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_DISABLED , GUI_WHITE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SEL      , GUI_WHITE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SELFOCUS , GUI_ORANGE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_UNSEL    , GUI_WHITE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_DISABLED , GUI_BLUE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SEL      , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SELFOCUS , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_UNSEL    , GUI_BLACK);
    LISTBOX_SetAutoScrollV(hWin,1);

    pMenu->data->title[g_LanguageIndex];
    for(i=0;i<pMenu->data->menunum;i++)
    {
    	memset(strShow,0,sizeof(strShow));
        if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str(pContentEn,strShow,STRSHOWBUF_SIZE);
        pContentCn += MAX_INFO_CHAR;
        pContentEn += MAX_INFO_CHAR;
        LISTBOX_AddString(hWin, strShow);
        if(MENU_SETTING_TITLE == pMenu->data->menuattri[i]) LISTBOX_SetItemDisabled(hWin,i,1);
    }

    WM_SetCallback(WM_HBKWIN, _WinCommonMenuCallback);
}

/*******************************************************************************
* Function Name :_WinCommonMenuDestroy
* Description   :
* Input         :void * p
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
static void _WinCommonMenuDestroy(void *p)
{
    WM_DeleteWindow(m_CommonMenu.hFrame);
    WM_DeleteWindow(m_CommonMenu.hList);
    WM_DeleteWindow(m_CommonMenu.hBtnHome);
    WM_DeleteWindow(m_CommonMenu.hBtnRtn);
    WM_DeleteWindow(m_CommonMenu.hText);
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_CommonMenu, 0, sizeof(m_CommonMenu));
}

/*******************************************************************************
* Function Name :_WinCommonMenuInterface
* Description   :设定当前 选择项
* Input         :int sel
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _WinCommonMenuInterface(void *val)
{
    int sel = *(int *)val;
    int i=0;
    int j=0;

    if(sel == 100 )  //进入新建的菜单
    {
        return ;
    }
    else             //返回的菜单
    {
        if (m_CommonMenu.hList == 0) return;

        if ((sel < (int)LISTBOX_GetNumItems(m_CommonMenu.hList)) && (sel >= 0))
        {
            BUTTON_SetPressed(m_CommonMenu.hBtnHome,0);
            BUTTON_SetPressed(m_CommonMenu.hBtnRtn,0);
            while(i<LISTBOX_GetNumItems(m_CommonMenu.hList))
            {
                if(0==LISTBOX_GetItemDisabled(m_CommonMenu.hList,i))
                {
                    if(j==sel)
                    {
                        LISTBOX_SetBkColor(m_CommonMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
                        LISTBOX_SetSel(m_CommonMenu.hList, i);
                        break;
                    }
                    j++;
                }
                i++;
            }
        }
    }
}


WIN_INFO_TYPE g_WinCommonMenu = {                         //列表窗口
    &m_CommonMenu.hFrame,
    _WinCommonMenuCreate,
    _WinCommonMenuDestroy
};



/******************************主菜单窗口***************************************/
typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hText;
    GUI_HWIN hList;
    GUI_HWIN hChkBox[AUTHRITY_NUM];
}CUR_USER_MENU_TYPE;
static CUR_USER_MENU_TYPE m_CurUserMenu = {0};                         //主菜单窗口

/*******************************************************************************
* Function Name :_WinCurUserKeyEnter
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _WinCurUserKeyEnter(void )
{
    unsigned char i=0;
    unsigned char j=0;
    for(i=0,j=0;i<MENU_CUR_USER_NUM;i++)
    {
        if(0 == LISTBOX_GetItemDisabled(m_CurUserMenu.hList,i) )
        {
            if(i == LISTBOX_GetSel(m_CurUserMenu.hList) )
            {
                g_authority = j;
                break;
            }
            j++;
        }
    }
    WIN_Exit(0);
}

/*******************************************************************************
* Function Name :_WinCurUserKeyDown
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _WinCurUserKeyDown(void )
{
    char curIndex=0;
    char curIndexDisable=0;


    curIndex = LISTBOX_GetSel(m_CurUserMenu.hList);
    curIndex++;
    if(curIndex == LISTBOX_GetNumItems(m_CurUserMenu.hList) )
    {
        curIndex = 0;
        curIndexDisable = LISTBOX_GetItemDisabled(m_CurUserMenu.hList,curIndex);
        while(curIndexDisable)
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_CurUserMenu.hList,curIndex);
        }
        LISTBOX_SetSel(m_CurUserMenu.hList,curIndex);
    }
    else
    {
        curIndexDisable = LISTBOX_GetItemDisabled(m_CurUserMenu.hList,curIndex);
        while(curIndexDisable)
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_CurUserMenu.hList,curIndex);
        }
        LISTBOX_SetSel(m_CurUserMenu.hList,curIndex);
    }
}

/*******************************************************************************
* Function Name :_WinCurUserKeyUp
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _WinCurUserKeyUp(void)
{
    char curIndex =0;
    char curIndexDisable =0;
    char curLen= LISTBOX_GetNumItems(m_CurUserMenu.hList);

    curIndex = LISTBOX_GetSel(m_CurUserMenu.hList);
    if(curIndex>0)
    {
        curIndex--;
        curIndexDisable = LISTBOX_GetItemDisabled(m_CurUserMenu.hList,curIndex);
        while(curIndexDisable)
        {
            if(curIndex>0)
            {
                curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CurUserMenu.hList,curIndex);
            }
            else
            {
                curIndex = curLen - 1;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CurUserMenu.hList,curIndex);
            }
        }
    }
    else
    {
        curIndex = curLen - 1;
        curIndexDisable = LISTBOX_GetItemDisabled(m_CurUserMenu.hList,curIndex);
        while(curIndexDisable)
        {
            if(curIndex>0)
            {
                curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CurUserMenu.hList,curIndex);
            }
            else
            {
                curIndex = curLen - 1;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CurUserMenu.hList,curIndex);
            }
        }
    }
    LISTBOX_SetSel(m_CurUserMenu.hList,curIndex);
}

/*******************************************************************************
* Function Name :_WinCurUserCallback
* Description   :回调函数
* Input         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
static void _WinCurUserCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinCurUserKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinCurUserKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinCurUserKeyEnter();
            //WIN_Exit(0);
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

/*******************************************************************************
* Function Name :_WinCurUserCreate
* Description   :主菜单的文本显示选项
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
static void _WinCurUserCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    short           j           = 0;
    char            *pBuffter   = g_LCDBuff;
     char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    char            *pContentCn = pMenu->data->menutitleCn;
    char            *pContentEn = pMenu->data->menutitleEn;

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);

    //建立新窗口
    m_CurUserMenu.hFrame = FRAMEWIN_CreateAsChild(0, 0, LCD_HSIZE+3, LCD_VSIZE+3 ,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);

    FRAMEWIN_SetFont(m_CurUserMenu.hFrame, &GUI_Fontsong16all);  //字体
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_CurUserMenu.hFrame, 0);             //显示标题

    hWin = WM_GetFirstChild(m_CurUserMenu.hFrame);             //获得窗口桌面

    //建立列表窗口
    m_CurUserMenu.hText      = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CurUserMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23+10, PER_CM_OFFSET*4.5, PER_CM_OFFSET*4, hWin, WM_CF_SHOW, NULL, NULL,NULL);
    /**************************返回标题**************************/
    hWin = m_CurUserMenu.hText;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_BLUE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);

    /**************************LIST标题**************************/
    hWin = m_CurUserMenu.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 7);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_DISABLED , GUI_WHITE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SEL      , GUI_ORANGE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SELFOCUS , GUI_ORANGE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_UNSEL    , GUI_WHITE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_DISABLED , GUI_BLUE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SEL      , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SELFOCUS , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_UNSEL    , GUI_BLACK);
    //LISTBOX_SetAutoScrollV(hWin,1);

    pMenu->data->title[g_LanguageIndex];
    for(i=0;i<pMenu->data->menunum;i++)
    {
    	memset(strShow,0,sizeof(strShow));
        if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str(pContentEn,strShow,STRSHOWBUF_SIZE);
        pContentCn += MAX_INFO_CHAR;
        pContentEn += MAX_INFO_CHAR;
        LISTBOX_AddString(hWin, strShow);
        if(MENU_SETTING_TITLE == pMenu->data->menuattri[i]) LISTBOX_SetItemDisabled(hWin,i,1);
    }

    for(i=0,j=0;i<MENU_CUR_USER_NUM;i++)
    {
        if(MENU_SETTING_CONTENT == pMenu->data->menuattri[i])
        {
            if(j==g_authority)
            {
                LISTBOX_SetSel(hWin,i);
                break;
            }
            j++;
        }
    }
    /**************************返回标题**************************/
    hWin = WM_GetFirstChild(m_CurUserMenu.hFrame);             //获得窗口桌面
    for(i=0,j=0;i<MENU_CUR_USER_NUM;i++)
    {
       if(MENU_SETTING_CONTENT == pMenu->data->menuattri[i])
       {
            m_CurUserMenu.hChkBox[j]    = CHECKBOX_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+PER_CM_OFFSET*4.5-23,DEBUG_Y_OFFSET+23+10+23*i,23,23,hWin,WM_CF_SHOW,NULL,NULL);
            j++;
       }
    }

    for(i=0;i<AUTHRITY_NUM;i++)
    {
        if(i==g_authority)
        {
             hWin = m_CurUserMenu.hChkBox[i];
             CHECKBOX_SetState(hWin,1);
             break;
        }
    }

    WM_SetCallback(WM_HBKWIN, _WinCurUserCallback);
    WM_SetFocus(WM_HBKWIN);
}

/*******************************************************************************
* Function Name :_WinCurUserDestroy
* Description   :
* Input         :void * p
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
static void _WinCurUserDestroy(void *p)
{
	  unsigned char i=0;
    WM_DeleteWindow(m_CurUserMenu.hFrame);
    WM_DeleteWindow(m_CurUserMenu.hList);
    WM_DeleteWindow(m_CurUserMenu.hText);
    for(;i<AUTHRITY_NUM;i++) WM_DeleteWindow(m_CurUserMenu.hChkBox[i]);
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_CurUserMenu, 0, sizeof(m_CurUserMenu));
}

/*******************************************************************************
* Function Name :_WinCurUserInterface
* Description   :设定当前 选择项
* Input         :int sel
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
void _WinCurUserInterface(void *val)
{
//    int sel = *(int *)val;
//
//    if (m_HListView.hList == 0)
//        return;
//
//    if ((sel < (int)LISTVIEW_GetNumRows(m_HListView.hList)) && (sel >= 0))
//        LISTVIEW_SetSel(m_HListView.hList, sel);
}


WIN_INFO_TYPE g_WinCurUserMenu = {                         //列表窗口
    &m_CurUserMenu.hFrame,
    _WinCurUserCreate,
    _WinCurUserDestroy
};


