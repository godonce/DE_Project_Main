// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "stdio.h"

#define ID_BUTTON_UP (GUI_ID_USER + 0x01)
#define ID_BUTTON_DOWN (GUI_ID_USER + 0x02)
#define ID_BUTTON_OK (GUI_ID_USER + 0x03)
#define ID_BUTTON_Test (GUI_ID_USER + 0x04)


#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, " ", 0              ,  0,  0, 20,240, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "U", ID_BUTTON_UP  ,  0,  0, 20, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "D", ID_BUTTON_DOWN,  0, 30, 20, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "E", ID_BUTTON_OK  ,  0, 60, 20, 20, 0, 0x0, 0 },
  //{ BUTTON_CreateIndirect, " ", ID_BUTTON_Test  , 0,100, 100, 100, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

static void InitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    int i = 0;
    //WIDGET_SetEffect(hWin, &WIDGET_Effect_Simple);
    WM_SetStayOnTop(hWin, 1);
    for (i = 0; i < GUI_COUNTOF(_aDialogCreate); i++)
    {
        BUTTON_SetFocussable(WM_GetDialogItem(hWin, _aDialogCreate[i].Id), 0);    //失能所有所有按键 焦点
        WIDGET_SetEffect(WM_GetDialogItem(hWin, _aDialogCreate[i].Id), &WIDGET_Effect_Simple);
    }
    //hWin = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_Test);
    //BUTTON_SetBitmapEx(hWin,0,&bm111_2,0,0);
    //GUI_DrawBitmap(&bm111,100,100);
    //GUI_DrawBitmap(&bm111_2,100,100);
}


// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
extern void WIN_KeyBoard(int key);
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  int key = 0;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    InitDialog(pMsg);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(NCode) {
        case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
        case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
            switch (Id)
            {
              case ID_BUTTON_UP:      key = GUI_KEY_UP; break; //WINAPI_KeyHandler(3); break;//
              case ID_BUTTON_DOWN:    key = GUI_KEY_DOWN; break; //WINAPI_KeyHandler(4); break;//
              case ID_BUTTON_OK:      key = GUI_KEY_ENTER; break; //WINAPI_KeyHandler(2); break;//
              break; //WINAPI_KeyHandler(5); break;//
            }
            //GUI_SendKeyMsg(key, 0);
            //GUI_Delay(20);
            //GUI_SendKeyMsg(key, 1);
            WIN_KeyBoard(key);
        // USER END
        break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN WindowMainCreat(void);
WM_HWIN WindowMainCreat(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/