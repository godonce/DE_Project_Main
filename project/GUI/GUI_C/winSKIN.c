#include "winSKIN.h"
static int _GetItemSizeX_CommonList(WM_HWIN hWin, int ItemIndex) {
  char acBuffer[100];
  int  DistX;

  LISTBOX_GetItemText(hWin, ItemIndex, acBuffer, sizeof(acBuffer));
  DistX = GUI_GetStringDistX(acBuffer);
  return DistX;
}

static int _GetItemSizeY_CommonList3(WM_HWIN hWin, int ItemIndex) {
  int DistY;
  DistY = GUI_GetFontDistY()+ 8+18-16;
  return DistY;
}

static int _GetItemSizeY_CommonList(WM_HWIN hWin, int ItemIndex) {
  int DistY;
  DistY = GUI_GetFontDistY()+ 6;
  return DistY;
}

 void DrawGradientH_PointWhite(int x0, int y0, int x1, int y1)
{
  int x_mid = (x1-x0)/2+x0;
  GUI_DrawGradientH(x0,y0,x_mid,y1 ,GUI_WHITE,GUI_BLACK);
  GUI_DrawGradientH(x_mid+1,y0,x1,y1,GUI_BLACK,GUI_WHITE);
}

static void DrawGradientV_PointWhite(int x0, int y0, int x1, int y1)
{
  int y_mid = (y1-y0)/2+y0;
  GUI_DrawGradientV(x0,y0,x0,y_mid ,GUI_WHITE,GUI_BLACK);
  GUI_DrawGradientV(x0,y_mid+1,x1,y1,GUI_BLACK,GUI_WHITE);
}




void jiance_error(int x0,int y0)
{

	GUI_SetColor(GUI_RED);
	GUI_FillCircle(x0,y0,7);//10
	GUI_SetColor(GUI_BLACK);
	GUI_DrawCircle(x0,y0,7);//9
	GUI_DrawCircle(x0,y0,8);//10
	GUI_SetColor(GUI_WHITE);
	GUI_DrawLine(x0-3,y0-3+1,x0+3-1,y0+3);
	GUI_DrawLine(x0-3,y0-3,x0+3,y0+3);
	GUI_DrawLine(x0-3+1,y0-3,x0+3,y0+3-1);
	
	GUI_DrawLine(x0-3,y0+3-1,x0+3-1,y0-3);
	GUI_DrawLine(x0-3,y0+3,x0+3,y0-3);
	GUI_DrawLine(x0-3+1,y0+3,x0+3,y0-3+1);
	GUI_SetColor(GUI_BLACK);
}


void jiance_ok(int x0,int y0)
{
	GUI_SetPenSize(1);
			GUI_DrawGradientRoundedV(x0-8, y0-8, x0+8, y0+8, 2, GUI_GREEN, GUI_GREEN);
	GUI_SetColor(GUI_BLACK);
	GUI_DrawArc(x0+6,y0-6,2,2,0,90);
	GUI_DrawArc(x0+6,y0+6,2,2,-90,0);
	GUI_DrawArc(x0-6,y0-6,2,2,90,180);
	GUI_DrawArc(x0-6,y0+6,2,2,180,270);
	GUI_DrawLine(x0-6,y0+8,x0+6,y0+8);
	GUI_DrawLine(x0-6,y0-8,x0+6,y0-8);
	GUI_DrawLine(x0-8,y0-6,x0-8,y0+6);
	GUI_DrawLine(x0+8,y0-6,x0+8,y0+6);
	GUI_SetColor(GUI_WHITE);
	
	GUI_DrawLine(x0-2,y0-2+1+1,x0+0-1,y0+1+2);
	GUI_DrawLine(x0-2,y0-2+1,x0+0,y0+1+2);
	GUI_DrawLine(x0-2+1,y0-2+1,x0+0,y0+1-1+2);
	
	GUI_DrawLine(x0-0,y0+2-1+2,x0+4-1+2,y0+2-4-2);
	GUI_DrawLine(x0-0,y0+2+2,x0+4+2,y0+2-4-2);
	GUI_DrawLine(x0-0+1,y0+2+2,x0+4+2,y0+2-4-2+1);
	GUI_SetColor(GUI_BLACK);
}

void quan_drive(int x0,int y0)
{
	GUI_SetColor(GUI_BLACK);
	GUI_DrawCircle(x0+15,y0+14,25);
}

void open_drive1(int x0,int y0,GUI_COLOR color1)
{
	GUI_SetColor(color1);
	GUI_FillCircle(x0+15,y0+14,25);
	GUI_SetColor(GUI_BLACK);
	GUI_DrawCircle(x0+15,y0+14,25);
	GUI_DrawGradientV(x0,y0,x0+31,y0+3,GUI_BLACK,GUI_BLACK);
	GUI_DrawGradientV(x0,y0+24,x0+31,y0+3+24,GUI_BLACK,GUI_BLACK);
	
	GUI_DrawGradientRoundedV(x0+9, y0+7, x0+9+12, y0+7+12, 6, GUI_BLACK, GUI_BLACK);
	
	GUI_DrawGradientV(x0+4,y0+11,x0+4+5,y0+11+3,GUI_BLACK,GUI_BLACK);
	GUI_DrawGradientV(x0+21,y0+11,x0+21+4+1,y0+11+3,GUI_BLACK,GUI_BLACK);
	GUI_SetColor(GUI_BLACK);
}

void open_drive(int x0,int y0)
{
	GUI_DrawGradientV(x0,y0,x0+31,y0+3,GUI_BLACK,GUI_BLACK);
	GUI_DrawGradientV(x0,y0+24,x0+31,y0+3+24,GUI_BLACK,GUI_BLACK);
	
	GUI_DrawGradientRoundedV(x0+9, y0+7, x0+9+12, y0+7+12, 6, GUI_BLACK, GUI_BLACK);
	
	GUI_DrawGradientV(x0+4,y0+11,x0+4+5,y0+11+3,GUI_BLACK,GUI_BLACK);
	GUI_DrawGradientV(x0+21,y0+11,x0+21+4+1,y0+11+3,GUI_BLACK,GUI_BLACK);
	
}

void close_drive(int x0,int y0)
{
	GUI_DrawGradientV(x0,y0,x0+31,y0+3,GUI_BLACK,GUI_BLACK);
	GUI_DrawGradientV(x0,y0+24,x0+31,y0+3+24,GUI_BLACK,GUI_BLACK);
	
	GUI_DrawGradientRoundedV(x0+9, y0+7, x0+9+12, y0+7+12, 6, GUI_BLACK, GUI_BLACK);
	
	GUI_DrawGradientV(x0+14-1,y0+3,x0+14+3-1,y0+14+4,GUI_BLACK,GUI_BLACK);
	GUI_DrawGradientV(x0+14-1,y0+3+12+4,x0+14+3-1,y0+3+12+4+4,GUI_BLACK,GUI_BLACK);	
}











