#include "dialog.h"

WM_HWIN hpage[4];
void MainTask(void)
{
    GUI_Init();                     //��ʼ��emWin/ucGUI
//    GUI_UC_SetEncodeGBK();
   //CreateFramewin(WM_HBKWIN);      //��������,�����������汳��
   //CreateWindow();
   _InterDataRefresh();
   WindowMainCreat();
   WIN_WindowsTreeInit();              //�������ṹ��ʼ��
   WIN_ContextInit();
   // CreateWin
    //GUI_UC_SetEncodeUTF8();
    //WM_ShowWindow(hpage[0]);
    while(1)
    {
        _DataRefresh();
        //_InterDataRefresh();
        GUI_Delay(20);
    }       //����GUI_Delay������ʱ20MS(����Ŀ���ǵ���GUI_Exec()����)
}
