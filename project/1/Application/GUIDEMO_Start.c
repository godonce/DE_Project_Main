#include "dialog.h"

WM_HWIN hpage[4];
void MainTask(void)
{
    GUI_Init();                     //初始化emWin/ucGUI
//    GUI_UC_SetEncodeGBK();
   //CreateFramewin(WM_HBKWIN);      //创建窗体,父窗体是桌面背景
   //CreateWindow();
   _InterDataRefresh();
   WindowMainCreat();
   WIN_WindowsTreeInit();              //窗口树结构初始化
   WIN_ContextInit();
   // CreateWin
    //GUI_UC_SetEncodeUTF8();
    //WM_ShowWindow(hpage[0]);
    while(1)
    {
        _DataRefresh();
        //_InterDataRefresh();
        GUI_Delay(20);
    }       //调用GUI_Delay函数延时20MS(最终目的是调用GUI_Exec()函数)
}
