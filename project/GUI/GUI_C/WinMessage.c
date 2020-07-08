/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.30                          *
*        Compiled Jul  1 2015, 10:50:32                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/


#include "DIALOG.h"
#include "DataInterface.h"

extern GUI_CONST_STORAGE GUI_FONT GUI_Fontsong16all;
#define ID_WIN_SHOWMESSAGE (GUI_ID_USER + 0x10)
#define ID_TEXT_SHOWMESSAGE (GUI_ID_USER + 0x11)


#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

static const GUI_WIDGET_CREATE_INFO _aMessageDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, " "         , ID_WIN_SHOWMESSAGE   ,  DEBUG_X_OFFSET+PER_CM_OFFSET,     DEBUG_Y_OFFSET+23*2, PER_CM_OFFSET*4.5, 23*6, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "���浱ǰλ��", ID_TEXT_SHOWMESSAGE  ,  DEBUG_X_OFFSET  ,  DEBUG_Y_OFFSET+23*1, PER_CM_OFFSET*4.5, 23  , 0, 0x0, 0 },

};

void StrShowClear(void);
static void InitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    int i = 0;
    WM_SetStayOnTop(hWin, 1);

    hWin = WM_GetDialogItem(hWin, ID_TEXT_SHOWMESSAGE);
    StrShowClear();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetText(hWin, "Save Current Pos");

}

static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  int key = 0;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    InitDialog(pMsg);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(NCode) {
        case WM_NOTIFICATION_CLICKED:
        break;
        case WM_NOTIFICATION_RELEASED:
        break;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}


WM_HWIN UserMessageBoxCreat(void);
WM_HWIN UserMessageBoxCreat(void) {
  WM_HWIN hWin;
  hWin = GUI_CreateDialogBox(_aMessageDialogCreate, GUI_COUNTOF(_aMessageDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}
