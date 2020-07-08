#include "DIALOG.h"
#include "DataInterface.h"
#include "WIN_Context.h"
#include "WIN.h"
#include "os_cpu.h"
#pragma  diag_suppress 177 

extern WM_HWIN WindowMainCreat(void);
extern void WIN_WindowsTreeInit(void);
extern void WIN_ContextInit(void);
extern void  OSTimeDly (INT32U ticks);
void Line_Right(int x0,int y0,int ix,int iy,int num,GUI_COLOR color1,GUI_COLOR color2);
WM_HWIN hpage[4];
WM_HWIN hItem;
void MainTask(void)
{  
    WindowMainCreat();
    GUI_Exec();
}

void Main2Task(void) {
GUI_MEMDEV_Handle hMemData; GUI_MEMDEV_Handle hMemMask;
GUI_Init();
hMemMask = GUI_MEMDEV_CreateFixed(0, 0, 320, 240, GUI_MEMDEV_NOTRANS,
GUI_MEMDEV_APILIST_1, GUICC_1);
GUI_MEMDEV_Select(hMemMask);
GUI_SetPenSize(8);
GUI_DrawLine(0, 240, 320, 0);
GUI_DrawLine(0, 0, 320, 240);
GUI_MEMDEV_Select(0);
GUI_MEMDEV_ClearAlpha(hMemData, hMemMask);
GUI_MEMDEV_Write(hMemData);
while (1) {
GUI_Delay(100);
}
}
void Main1Task(void)
{
		int i=0;
	int num=260;
	int j,k;
	GUI_SetBkColor(GUI_BLUE);
	GUI_SetFont(&GUI_Font24B_ASCII); 
	GUI_GotoXY(0,10);
	GUI_DispDecAt(100,0,10,2);
		BUTTON_SetTextColor(hItem,1,(0x00FFFF00));
		for(i=0;i<num;i++)
		{
		Line_Right(0,162,10,10,i,0x00EEAC5C,0x00ffffff);
		Line_Right(0,182,10,-10,i,0x00EEAC5C,0x00ffffff);

		Line_Right(0,142,0,10,i,0x00EEAC5C,0x00ffffff);
		Line_Right(0,162,0,-10,i,0x00EEAC5C,0x00ffffff);

		Line_Right(0,193,10,-10,i,0x00EEAC5C,0x00ffffff);
		Line_Right(0,193,10,10,i,0x00EEAC5C,0x00ffffff);
			OSTimeDly(10);
		}
		for(i=num;i>0;i--)
		{

		Line_Right(i,162,10,10,num,0x0,0x0);
		Line_Right(i,182,10,-10,num,0x0,0x0);

		Line_Right(i,142,0,10,num,0x0,0x0);
		Line_Right(i,162,0,-10,num,0x0,0x0);

		Line_Right(i,193,10,-10,num,0x0,0x0);
		Line_Right(i,193,10,10,num,0x0,0x0);
			
			OSTimeDly(10);
		}
	
}	
void Line(int x0,int x1,int y0,int y1,GUI_COLOR color)
{
    GUI_SetColor(color);
    GUI_DrawLine(x0,y0,x1,y1);
}
void Line_Right(int x0,int y0,int ix,int iy,int num,GUI_COLOR color1,GUI_COLOR color2)
{

     int i;
     int y,n;
     GUI_COLOR color;
      for(i=x0;i<=num;i++)
      {
        y=i/10;
        n=y%2;
        if (n==0)
        {
            color=color1 ;
        }else
        {
            color=color2;
        }
        Line(i,i+ix,y0,y0+iy,color);
        y=y%10;
      }
}


