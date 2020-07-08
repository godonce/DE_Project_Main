#include <math.h>    
#include <string.h>
#include "stdio.h"
#include "stdint.h"
#include "WIN.h"
#include "WinWindow.h"

#include "GUI.h"
#include "WM.h"
#include "DIALOG.h"
#include "LCDConf.H"
#include "FRAMEWIN.h"

#include "bit_flash.c"
#include "bit_second.c"
#include "bit_zhunbei.c"
#include "song16all.c"
#include "song64.c"
#include "song33.c"
#include "CodeConvert.h"
#include "DataInterface.h"
#include "os_cpu.h"
#include  "datafigures.h"

#include "winSKIN.h"

#define window_1  1
#define window_onlylist  1
#define window_00  1

#define MAG 4
extern int WIN_Enter(int *id);
extern int WIN_Exit(int result);
void _WinLocalOpRefresh(void);
void _WinCommonSelectFresh(void *p);
extern void  OSTimeDly (INT32U ticks);
int datadula=2;

extern volatile char   g_authority_bak;
extern unsigned char ssi_m,ssi_s;
extern uint16_t SPEED_Stand;
extern uint16_t TORQUE_Stand;
extern char flag_estop;
extern uint8_t DIR_MOTOR ; 

extern char motorset_stop;
extern char motorset_n;
extern char motorset_s;

extern int _WinCommonMenuListOwnerDraw2(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
extern int _WinCommonMenuListOwnerDraw3(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
extern int _WinCommonMenuListOwnerDraw4(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
extern int _WinCommonMenuListOwnerDraw5(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
extern int _WinCommonMenuListOwnerDraw00(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
extern int _WinCommonMenuListOwnerDraw51(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
void header_txt(int x0,int y0,int longx,int longy);

extern void blue(void);

int NUM_OF_USED;
int NUM_OF_FREE;
static int SKIN_Btn_Btn(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);//emWinĬɏ¿ؼ�¯�?
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
				GUI_DrawBitmap(&bmbackUnsel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
				GUI_DrawBitmap(&bmbackSel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
				GUI_DrawBitmap(&bmbackUnsel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
				GUI_DrawBitmap(&bmbackUnsel, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}


static int SKIN_DriverLeft_Button_Return(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
				GUI_DrawBitmap(&bmclose_blue, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
				GUI_DrawBitmap(&bmclose_brow, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
				GUI_DrawBitmap(&bmclose_blue, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
				GUI_DrawBitmap(&bmclose_blue, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}

static int SKIN_DriverRight_Button_Return(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
				GUI_DrawBitmap(&bmopen_blue, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
				GUI_DrawBitmap(&bmopen_brow, 0, 0);
				
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
				GUI_DrawBitmap(&bmopen_blue, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
				GUI_DrawBitmap(&bmopen_blue, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}
static int SKIN_DriverRight_Button_Return3(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);//emWinĬɏ¿ؼ�¯�?
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
				GUI_DrawBitmap(&bmqwe, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
				
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
				GUI_DrawBitmap(&bmqwe, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}

int SKIN_DriverRight_Button_Return2(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
				GUI_DrawBitmap(&bmComBack, 0, 0);
				
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}

static int SKIN_Left_Button_Return(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
				GUI_DrawBitmap(&bmleft_back_unsel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
				GUI_DrawBitmap(&bmleft_back_sel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
				GUI_DrawBitmap(&bmleft_back_unsel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
				GUI_DrawBitmap(&bmleft_back_unsel, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}

static int SKIN_TEST(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
         GUI_DrawBitmap(&bmqwe, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
         GUI_DrawBitmap(&bmqwe, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
         GUI_DrawBitmap(&bmqwe, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}
static int SKIN_TEST1(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
         GUI_DrawBitmap(&bmstates_ok, 0, 2);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
         GUI_DrawBitmap(&bmstates_error, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
         GUI_DrawBitmap(&bmstates_ok, 0, 2);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
         GUI_DrawBitmap(&bmstates_ok, 0, 2);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}
static int SKIN_NUMBER_Button(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
				GUI_DrawBitmap(&bmShu_Blue, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
				GUI_DrawBitmap(&bmShu_Orn, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
				GUI_DrawBitmap(&bmShu_Blue, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
				GUI_DrawBitmap(&bmShu_Blue, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}
static int SKIN_Two_NUMBER_Button(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
         GUI_DrawBitmap(&bmrect_orange_2num, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
         GUI_DrawBitmap(&bmrect_orange_2num, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
         GUI_DrawBitmap(&bmrect_orange_2num, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
         GUI_DrawBitmap(&bmrect_orange_2num, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}
static int SKIN_textheader_Button(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
         
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
        
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
        
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
        
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}
static int SKIN_Three_NUMBER_Button(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
         GUI_DrawBitmap(&bmrect_orange_3num, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
         GUI_DrawBitmap(&bmrect_orange_3num, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
         GUI_DrawBitmap(&bmrect_orange_3num, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
         GUI_DrawBitmap(&bmrect_orange_3num, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}

static int SKIN_Five_NUMBER_Button(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
         GUI_DrawBitmap(&bmrect_orange_5num, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
         GUI_DrawBitmap(&bmrect_orange_5num, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
        GUI_DrawBitmap(&bmrect_orange_5num, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
        GUI_DrawBitmap(&bmrect_orange_5num, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}

static int _ProgOwnerSkin2(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
    WM_HWIN hWin;
    int     Index;
	int i,j,k;
	int m,n;
    PROGBAR_SKINFLEX_INFO *pSkin =(PROGBAR_SKINFLEX_INFO *)pDrawItemInfo->p;;
    hWin     = pDrawItemInfo->hWin;
    Index    = pDrawItemInfo->ItemIndex;
  
    switch (pDrawItemInfo->Cmd) {
    case WIDGET_ITEM_CREATE:
        break;
    case WIDGET_ITEM_DRAW_BACKGROUND:
        if(pSkin->Index == PROGBAR_SKINFLEX_L)
        {
			if(flag_estop==0)
			{
					for(i=(pDrawItemInfo->x0);i<(pDrawItemInfo->x1);i++)
					{		
						if(i%10<2)
						{
							GUI_SetColor(GUI_WHITE);
						}else
						{
							GUI_SetColor(GUI_BLUE);
						}				
						GUI_DrawLine(i,pDrawItemInfo->y0,i,pDrawItemInfo->y1);					
					}
			}else
			if(flag_estop==1)
			{
							
					if(set_end.flag_move_right==1)
					{
						for(i=(pDrawItemInfo->x0);i<(pDrawItemInfo->x1);i++)
						{		
							if(i%10<2)
							{
							GUI_SetColor(GUI_WHITE);
							}else
							{
								GUI_SetColor(GUI_BLUE);
							}				
							GUI_DrawLine(i,pDrawItemInfo->y0,i,pDrawItemInfo->y1);					
						}
					}	else
					if(set_end.flag_move_left==1)
					{
						for(m=pDrawItemInfo->x0;m<pDrawItemInfo->x1;m++)
						{
							if(m%10<5)
							{
							GUI_SetColor(GUI_WHITE);
							}else
							{
								GUI_SetColor(GUI_RED);
							}
							GUI_DrawLine(m,pDrawItemInfo->y0,m-5,((pDrawItemInfo->y1-pDrawItemInfo->y0)/2));
							GUI_DrawLine(m,pDrawItemInfo->y1,m-5,((pDrawItemInfo->y1-pDrawItemInfo->y0)/2));
						}
						
					}																	
			}
			
			
        }
        if(pSkin->Index == PROGBAR_SKINFLEX_R)
        {		
			#if 1
			GUI_ClearRect(pDrawItemInfo->x0,pDrawItemInfo->y0,pDrawItemInfo->x1-1,pDrawItemInfo->y1-1);
		
			if(flag_estop==1)
			{
					if(set_end.flag_move_right==1)
					{
						for(j=pDrawItemInfo->x1;j>pDrawItemInfo->x0;j--)
							{
								if(j%10<5)
								{
								GUI_SetColor(GUI_WHITE);
								}else
								{
									GUI_SetColor(GUI_RED);
								}	
								GUI_DrawLine(j,pDrawItemInfo->y0,j+5,((pDrawItemInfo->y1-pDrawItemInfo->y0)/2));
							GUI_DrawLine(j,pDrawItemInfo->y1,j+5,((pDrawItemInfo->y1-pDrawItemInfo->y0)/2));
							}
							
					}	else
					if(set_end.flag_move_left==1)
					{
						GUI_ClearRect(pDrawItemInfo->x0,pDrawItemInfo->y0,pDrawItemInfo->x1-1,pDrawItemInfo->y1-1);
					}
				
				
				
			}else
			{
			GUI_ClearRect(pDrawItemInfo->x0,pDrawItemInfo->y0,pDrawItemInfo->x1-1,pDrawItemInfo->y1-1);
			}
			#endif
        }
        break;
    case WIDGET_ITEM_DRAW_FRAME:
        GUI_SetBkColor(GUI_WHITE);
        GUI_Clear();
        GUI_SetColor(GUI_BLACK);
        GUI_DrawRoundedRect(pDrawItemInfo->x0,pDrawItemInfo->y0,pDrawItemInfo->x1,pDrawItemInfo->y1,1);
        break;
    case WIDGET_ITEM_DRAW_TEXT:
        break;
    default:
        return PROGBAR_DrawSkinFlex(pDrawItemInfo);
    }
    return 0;
}


static int SKIN_Right_Button_Home(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
         GUI_DrawBitmap(&bmright_home_unsel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
         GUI_DrawBitmap(&bmright_home_sel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
         GUI_DrawBitmap(&bmright_home_unsel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
         GUI_DrawBitmap(&bmright_home_unsel, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}


static int _GetItemSizeX(WM_HWIN hWin, int ItemIndex) {
  char acBuffer[100];
  int  DistX;

  LISTBOX_GetItemText(hWin, ItemIndex, acBuffer, sizeof(acBuffer));
  DistX = GUI_GetStringDistX(acBuffer);
  return DistX;
}

static int _GetItemSizeY(WM_HWIN hWin, int ItemIndex) {
  int DistY;

  DistY = GUI_GetFontDistY();
  if (LISTBOX_GetSel(hWin) == ItemIndex) {
    DistY = GUI_GetFontDistY()+ 4;
  }
  else DistY = GUI_GetFontDistY()+6;
  DistY = GUI_GetFontDistY()+ 4;
  return DistY;
}


static int _OwnerDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN hWin;
  int     Index;

  hWin     = pDrawItemInfo->hWin;
  Index    = pDrawItemInfo->ItemIndex;
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    return _GetItemSizeX(hWin, Index);
  case WIDGET_ITEM_GET_YSIZE:
    return _GetItemSizeY(hWin, Index);
  case WIDGET_ITEM_DRAW:
#if 1
    {
      int   Sel;
      int   YSize;
      int   FontDistY;
      int   IsDisabled;
      int   IsSelected;
      int   ColorIndex;
      char  acBuffer[100];
      const GUI_BITMAP * pBm;
      const GUI_FONT * pOldFont = 0;
			GUI_RECT rFocus;
      GUI_COLOR aColor[4] = {GUI_BLACK, GUI_BLACK, GUI_BLACK, GUI_BLACK};
      GUI_COLOR aBkColor[4] = {GUI_TRANSPARENT, GUI_TRANSPARENT, GUI_TRANSPARENT, GUI_TRANSPARENT};
      IsDisabled = LISTBOX_GetItemDisabled(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex);
      IsSelected = LISTBOX_GetItemSel(hWin, Index);
      Sel        = LISTBOX_GetSel(hWin);
      YSize      = _GetItemSizeY(hWin, Index);
        if (IsDisabled) {
          ColorIndex = 3;
        } else {
          if (pDrawItemInfo->ItemIndex == Sel) {
            ColorIndex = WM_HasFocus(pDrawItemInfo->hWin) ? 2 : 1;
          } else {
            ColorIndex = 0;
          }
        }
      GUI_SetBkColor(aBkColor[ColorIndex]);
      GUI_SetColor  (aColor[ColorIndex]);
      LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex, acBuffer, sizeof(acBuffer));
      GUI_Clear();
      GUI_SetColor(GUI_ORANGE);
      rFocus.x0 = pDrawItemInfo->x0;
      rFocus.y0 = pDrawItemInfo->y0;
      rFocus.x1 = pDrawItemInfo->x0 + 176;
      rFocus.y1 = pDrawItemInfo->y0 + 22;
      if (pDrawItemInfo->ItemIndex == Sel)
      {
          GUI_Clear();
          GUI_AA_FillRoundedRectEx(&rFocus, 8);
      }

      GUI_SetColor(GUI_BLACK);
      FontDistY  = GUI_GetFontDistY();
      GUI_DispStringAt(acBuffer, pDrawItemInfo->x0 , pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
      GUI_DispCEOL();
    }
#endif // 0
    break;
  default:
    return LISTBOX_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}




typedef struct {
  GUI_AUTODEV_INFO AutoDevInfo; 
  GUI_POINT aPoints[7];        
  float Angle;
} PARAM;



#if window_00 
typedef struct {
    GUI_HWIN hFrame;
	
	#if 1      
	GUI_HWIN hImage_CB_1;   
	GUI_HWIN hImage_CB_2;   
	GUI_HWIN hQuan_left;    
	GUI_HWIN hQuan_right;   
	WM_HTIMER hTimer;       
	GUI_HWIN hList;         
	GUI_HWIN hImage_close;  
	GUI_HWIN hImage_open;   
	GUI_HWIN hAll_close;    
	GUI_HWIN hAll_open;     
	GUI_HWIN hStates;       
	GUI_HWIN hText_close;   
	GUI_HWIN hText_open;    
	#endif	                     
	GUI_HWIN hText;         
	GUI_HWIN hText1;        
	GUI_HWIN hText2;        
	GUI_HWIN hText3;        
	GUI_HWIN hProgbar;      
	GUI_HWIN hBtnNationFlag;
	GUI_HWIN hBtnLocal;     
	GUI_HWIN hBtnRemote;    
	GUI_HWIN hBtnTurnOff;   
	GUI_HWIN hBtnTurnOff_1; 
	GUI_HWIN hImage;        
	GUI_HWIN hImage_123123; 
	GUI_HWIN hImage_1231234;
	GUI_HWIN hImage1;       
	GUI_HWIN hImage2;       
	GUI_HWIN hImage3;       
	GUI_HWIN hImage4;       
	GUI_HWIN hImage5;       
	GUI_HWIN hImage_left;   
	GUI_HWIN hImage_right;  
	GUI_HWIN hImage_test;   
	GUI_HWIN hBtnNew;       
    GUI_AUTODEV AutoDev; 
	GUI_HWIN hImage_left_1; 
	GUI_HWIN hImage_right_1; 
}MAIN_WIN_BAR_TYPE;



static MAIN_WIN_BAR_TYPE m_MainWin = {0};    

unsigned char strShow[STRSHOWBUF_SIZE];

void backgroundmbit()
{
}

char hxmk;
void _MainWinKeyDown(void)
{
	char curIndex=0;
	if(MAIN_MENU_FOCUS_TEXT == g_mainMenuFocus)
	{
        g_mainMenuFocus = MAIN_MENU_FOCUS_LIST;
        TEXT_SetBkColor(m_MainWin.hText,GUI_WHITE);
	    if(DEVICE_STATE_LOCAL == g_deviceState)   
	    {
	        LISTBOX_SetSel(m_MainWin.hList,0);
	    }
	    else
	    {
	        LISTBOX_SetSel(m_MainWin.hList,1);
	    }
	}
	else if((MAIN_MENU_FOCUS_LIST == g_mainMenuFocus))
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
            LISTBOX_SetSel(m_MainWin.hList,-1);  
        }
    }
}


void _MainWinKeyUp(void)
{	
	char curIndex=0;
	if(MAIN_MENU_FOCUS_TEXT == g_mainMenuFocus)
	{
      g_mainMenuFocus = MAIN_MENU_FOCUS_LIST;
      LISTBOX_SetBkColor(m_MainWin.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
      TEXT_SetBkColor(m_MainWin.hText,GUI_WHITE);
	    LISTBOX_SetSel(m_MainWin.hList,3);
	}
	else if((MAIN_MENU_FOCUS_LIST == g_mainMenuFocus))
    {
        curIndex = LISTBOX_GetSel(m_MainWin.hList);
        if(DEVICE_STATE_LOCAL == g_deviceState)  
        {
            if(curIndex == 0)
            {
                g_mainMenuFocus = MAIN_MENU_FOCUS_TEXT;
                TEXT_SetBkColor(m_MainWin.hText,GUI_ORANGE);
                LISTBOX_SetSel(m_MainWin.hList,-1);    
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


void _MainWinKeyEnter(void)
{
    int id = 0;
    if (m_MainWin.hList != 0) id = LISTBOX_GetSel(m_MainWin.hList);
    if(MAIN_MENU_FOCUS_TEXT == g_mainMenuFocus)
    {
    	id = 0;
        WIN_Enter(&id);
    }
    else
    {
        if(1 == id) 
        {
            if(DEVICE_STATE_LOCAL == g_deviceState)  //点选主界面控制模式，如果当前为就地，检测到旋钮按下，调整为远控
            {
                eeprom.g_deviceState_flag=1;
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                motorset.stop=46;
                g_deviceState = DEVICE_STATE_REMOTE;
                BUTTON_SetPressed(m_MainWin.hBtnLocal,0);
                BUTTON_SetPressed(m_MainWin.hBtnRemote,1);
                _MainWinShowRefresh();
            }
            else if(DEVICE_STATE_REMOTE == g_deviceState)
            {
                eeprom.g_deviceState_flag=1;
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                motorset.stop=45;
                g_deviceState = DEVICE_STATE_OFF;
                BUTTON_SetPressed(m_MainWin.hBtnRemote,0);
                BUTTON_SetPressed(m_MainWin.hBtnTurnOff,1);
                _MainWinShowRefresh();
            }
            else if(DEVICE_STATE_OFF == g_deviceState)
            {       
                eeprom.g_deviceState_flag=1;
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                motorset.stop=44;
                g_deviceState = DEVICE_STATE_LOCAL;
                BUTTON_SetPressed(m_MainWin.hBtnTurnOff,0);
                BUTTON_SetPressed(m_MainWin.hBtnLocal,1);
                _MainWinShowRefresh();
            }
        }
        else if(0 == id) 
        {
            id = 1;
            WIN_Enter(&id);
        }
        else
        {
            WIN_Enter(&id);
        }
    }
}


void _MainWinShowRefresh(void)
{

    memset(strShow,0,sizeof(strShow));
    if(LANGUAGE_CN == g_LanguageIndex)
    {
        if(DEVICE_STATE_LOCAL == g_deviceState)
        {
            enc_unicode_to_utf8_str(infoWinMainList0CN[DEVICE_STATE_LOCAL],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, (char *)strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,0);
            ledstates.local=1;
            ledstates.remote=0;
            ledstates.off=0;
        }
        else if(DEVICE_STATE_REMOTE == g_deviceState)
        {
            enc_unicode_to_utf8_str(infoWinMainList0CN[DEVICE_STATE_REMOTE],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, (char *)strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,1);
            ledstates.remote=1;
            ledstates.local=0;
            ledstates.off=0;
        }
        else if(DEVICE_STATE_OFF == g_deviceState)
        {
					
            enc_unicode_to_utf8_str(infoWinMainList0CN[DEVICE_STATE_OFF],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, (char *)strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,1);
            ledstates.off=1;
            ledstates.local=0;
            ledstates.remote=0;
        }
    }
    else if(LANGUAGE_EN == g_LanguageIndex)
    {
        if(DEVICE_STATE_LOCAL == g_deviceState)
        {
            enc_unicode_to_utf8_str(infoWinMainList0EN[DEVICE_STATE_LOCAL],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, (char *)strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,0);
        }
        else if(DEVICE_STATE_REMOTE == g_deviceState)
        {
            enc_unicode_to_utf8_str(infoWinMainList0EN[DEVICE_STATE_REMOTE],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, (char *)strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,1);
        }
        else if(DEVICE_STATE_OFF == g_deviceState)
        {
					
            enc_unicode_to_utf8_str(infoWinMainList0EN[DEVICE_STATE_OFF],strShow,STRSHOWBUF_SIZE);
            LISTBOX_SetString(m_MainWin.hList, (char *)strShow,0);
            LISTBOX_SetItemDisabled(m_MainWin.hList,0,1);
        }
    }
}
	int i=0;
	int b=5;


void _MainWinShowDataRefresh()
{
		
	GUI_HWIN        hWin        = 0;
		if(dataStructInterface.ctrlMode == 0 )
		{
			ai_o420.flag_mode1=1;
			ai_o420.flag_mode2=0;
			ai_o420.flag_mode3=0;
			ai_o420.flag_mode4=0;
		}
		else if(dataStructInterface.ctrlMode == 1 )
		{
			ai_o420.flag_mode1=0;
			ai_o420.flag_mode2=1;
			ai_o420.flag_mode3=0;
			ai_o420.flag_mode4=0;
		}
		else if(dataStructInterface.ctrlMode == 2 )
		{
			ai_o420.flag_mode1=0;
			ai_o420.flag_mode2=0;
			ai_o420.flag_mode3=1;
			ai_o420.flag_mode4=0;
		}
		else if(dataStructInterface.ctrlMode == 3 )
		{
			ai_o420.flag_mode1=0;
			ai_o420.flag_mode2=0;
			ai_o420.flag_mode3=0;
			ai_o420.flag_mode4=1;
		}
        if(DEVICE_STATE_OFF == g_deviceState)
        {
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
            motorset.stop=43;
        }

    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_Fontsong64);
    GUI_UC_SetEncodeUTF8();
#if 1
	
    if(motorset.flag_MOTOR_Close==1)  //全关显示全关的图片
	{
		if((encoder.num==7)||(encoder.num==8)||(encoder.num==5))
		{
			if(flag_figures.run1_100==1)
			{
				GUI_DrawGradientV(80,15,240,70,GUI_WHITE,GUI_WHITE);
				flag_figures.run1_100=0;
			}
			flag_figures.run100_100=1;
			GUI_DrawBitmap(&bmopen, 140,20);
			WM_ShowWindow(m_MainWin.hAll_open);
			PROGBAR_SetValue(m_MainWin.hProgbar,1000);
		}else
		{
			if(flag_figures.run1_100==1)
			{
				GUI_DrawGradientV(80,15,240,70,GUI_WHITE,GUI_WHITE);
				flag_figures.run1_100=0;
			}
			flag_figures.run0_0=1;
			flag_figures.run1_100=0;
			GUI_DrawBitmap(&bmclose, 140,20);
			WM_ShowWindow(m_MainWin.hAll_close);
			PROGBAR_SetValue(m_MainWin.hProgbar,0);
		}

	}
    else if(motorset.flag_MOTOR_Open==1)  //全开显示全开的图片
	{
		if((encoder.num==7)||(encoder.num==8)||(encoder.num==5))
		{
			if(flag_figures.run1_100==1)
			{
				GUI_DrawGradientV(80,15,240,70,GUI_WHITE,GUI_WHITE);
				flag_figures.run1_100=0;
			}
			flag_figures.run0_0=1;
			flag_figures.run1_100=0;
			WM_HideWindow(m_MainWin.hText1);
			GUI_DrawBitmap(&bmclose, 140,20);
			WM_ShowWindow(m_MainWin.hAll_close);
			PROGBAR_SetValue(m_MainWin.hProgbar,0);
		}else
		{
            if(flag_figures.run1_100==1)
            {
                GUI_DrawGradientV(80,15,240,70,GUI_WHITE,GUI_WHITE);
                flag_figures.run1_100=0;
            }
            flag_figures.run100_100=1;
            WM_HideWindow(m_MainWin.hText1);
            GUI_DrawBitmap(&bmopen, 140,20);
            WM_ShowWindow(m_MainWin.hText_open);
            WM_ShowWindow(m_MainWin.hAll_open);
            PROGBAR_SetValue(m_MainWin.hProgbar,1000);
        }
	}
    else if(motorset.flag_MOTOR_Run==1)  //运行显示行程百分比
	{
		#if 1
		flag_figures.run1_100=1;
		if(key_mlx90363.READ_run_1>=1000)
        {
            datadula=3;
        }
        else
		{
            datadula=2;
        }
        
		if(datadula==3)
		{
			GUI_DrawGradientV(80,15,240,70,GUI_WHITE,GUI_WHITE);
			flag_figures.datadula3=1;
			GUI_DispDecAt(100,DEBUG_X_OFFSET+150-32-18-32,5+5+5,datadula);
			GUI_SetFont(&GUI_Fontsong33);
			GUI_DispDecAt(0,20+150+18+15,5+2+32,1);
			if(flag_figures.datadula2==1)
			{
                flag_figures.datadula2=0;
                WM_ShowWindow(m_MainWin.hText2);
				WM_ShowWindow(m_MainWin.hText1);				
			}	
					
		}else
		{
			datadula=2;	
			flag_figures.datadula2=1;
			if(flag_figures.datadula3==1)
			{
				GUI_DrawGradientV(80,15,240,70,GUI_WHITE,GUI_WHITE);
				flag_figures.datadula3=0;
				WM_HideWindow(m_MainWin.hText2);
				WM_HideWindow(m_MainWin.hText1);
			}
            
            //主界面显示行程百分比
            GUI_DispDecAt(key_mlx90363.Integer_3,DEBUG_X_OFFSET+150-32-18,5+2+5+5,datadula);
			GUI_SetFont(&GUI_Fontsong33);
            GUI_DispDecAt(key_mlx90363.decimal_3,20+150+18+15,5+2+32,1);				
		}
		#endif
		WM_HideWindow(m_MainWin.hText_open);
		WM_HideWindow(m_MainWin.hText_close);
		PROGBAR_SetValue(m_MainWin.hProgbar,key_mlx90363.READ_run_1);
		GUI_SetFont(&GUI_Fontsong64);
		GUI_DispStringAt(",",20+150-32-18+52,17);
		GUI_SetFont(&GUI_Fontsong33);
		
		GUI_SetFont(&GUI_Fontsong33);
		GUI_DispStringAt("%",DEBUG_X_OFFSET+150+18+20+5,15/*+32-4*/);
		if((flag_figures.run100_100==1)||(flag_figures.run0_0==1))
		{
				WM_ShowWindow(m_MainWin.hText2);
				WM_ShowWindow(m_MainWin.hText1);
			if(flag_figures.run100_100==1)
			{
				flag_figures.run100_100=0;
				GUI_DrawGradientV(246,76,322,159,GUI_WHITE,GUI_WHITE);
				WM_HideWindow(m_MainWin.hAll_open);	
				WM_ShowWindow(m_MainWin.hProgbar);	
				WM_ShowWindow(m_MainWin.hQuan_right);	
				WM_ShowWindow(m_MainWin.hImage_open);	
			}
			if(flag_figures.run0_0==1)
			{
				flag_figures.run0_0=0;
				GUI_DrawGradientV(-3,76,76,159,GUI_WHITE,GUI_WHITE);
				WM_HideWindow(m_MainWin.hAll_close);	
				WM_ShowWindow(m_MainWin.hProgbar);	
				WM_ShowWindow(m_MainWin.hQuan_left);	
				WM_ShowWindow(m_MainWin.hImage_close);	
			}			
		}
		#if 1
		else
		{
		}		
		#endif		
	}
	#endif
	if(flag_figures.ready_old!=flag_figures.ready)
	{
		GUI_DrawGradientV(70,69,240,91,GUI_WHITE,GUI_WHITE);
		GUI_DrawGradientV(70,70,240,91,GUI_WHITE,GUI_WHITE);
		TEXT_SetText(m_MainWin.hText, (char *)infoWinMainCN[dataStructInterface.indexFaultNum[0]]);
		if(flag_figures.ready==0)
        {
				GUI_DrawGradientV(0,0,60,76,GUI_WHITE,GUI_WHITE);
				GUI_DrawGradientV(0,76,15,160,GUI_WHITE,GUI_WHITE);
				GUI_DrawGradientV(0,160,60,240,GUI_WHITE,GUI_WHITE);
				GUI_DrawGradientV(60,0,260,15,GUI_WHITE,GUI_WHITE);
				
				GUI_DrawGradientV(260,0,3200,76,GUI_WHITE,GUI_WHITE);
				GUI_DrawGradientV(300,76,320,160,GUI_WHITE,GUI_WHITE);
				GUI_DrawGradientV(260,160,320,240,GUI_WHITE,GUI_WHITE);
				
				GUI_DrawGradientV(60,228,260,240,GUI_WHITE,GUI_WHITE);
				flag_figures.ready_old=flag_figures.ready;
				BUTTON_SetPressed(m_MainWin.hStates,0);
				WM_HideWindow(m_MainWin.hImage);
        }else
        {	
            flag_figures.ready_old=flag_figures.ready;
            BUTTON_SetPressed(m_MainWin.hStates,1);
            WM_ShowWindow(m_MainWin.hImage);
        }
        TEXT_SetBkColor(m_MainWin.hText,GUI_TRANSPARENT);
        TEXT_SetFont(m_MainWin.hText,&GUI_Fontsong16all);
        TEXT_SetTextColor(m_MainWin.hText, GUI_BLACK);
		if(MAIN_MENU_FOCUS_TEXT == g_mainMenuFocus)
        {
            TEXT_SetBkColor(m_MainWin.hText,GUI_ORANGE);
        }
        else
        {
            TEXT_SetBkColor(m_MainWin.hText,GUI_WHITE);
        }
	}
}

static void _MainWinCreate(void *p);
static void _MainWinCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
	int i;
    int     NCode =0;
    switch (pMsg->MsgId)
    {
        case WM_PAINT://:		
            break;
        case WM_TIMER:	
            WM_RestartTimer(pMsg->Data.v, 100);
            _MainWinShowDataRefresh();	
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
            {
                case GUI_KEY_ESCAPE:
                    WIN_Enter(&id);
                    break;
                case GUI_KEY_DOWN:
                    _MainWinKeyDown();
                    break;
                case GUI_KEY_UP:
                    _MainWinKeyUp();
                    break;
                case GUI_KEY_ENTER:
                    _MainWinKeyEnter();
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            id     = WM_GetId(pMsg->hWinSrc);    
            NCode  = pMsg->Data.v;               
            switch (NCode) 
            {
                case WM_NOTIFICATION_SEL_CHANGED:
                    LISTBOX_InvalidateItem(m_MainWin.hList, LISTBOX_ALL_ITEMS);
                    break;
            }

        default:
            WM_DefaultProc(pMsg);
    }
}

#if 1

static void _cbWin(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_DrawBitmap(&bmComBack, 0, 0);
    break;
  }
}
int _WinCommonMenuListOwnerDraw01(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int _WinCommonMenuListOwnerDraw00(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
static void _MainWinCreate(void *p)
{
    unsigned int i=0;
    GUI_HWIN        hWin        = 0;
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    GUI_AA_SetFactor(MAG);
    GUI_EnableAlpha(1);
    GUI_UC_SetEncodeUTF8();
    _InterDataRefresh();

    NUM_OF_FREE=GUI_ALLOC_GetNumFreeBytes();
	NUM_OF_USED=GUI_ALLOC_GetNumUsedBytes();
	ledstates.OPEN_remote=1;
	motorset.local_error=0;
	
    m_MainWin.hFrame = WM_HBKWIN;
    hWin = m_MainWin.hFrame;
    memset(strShow,0,sizeof(strShow));

    m_MainWin.hAll_close = IMAGE_CreateEx(-5+2,75+3-1-1,76,83,WM_HBKWIN,WM_CF_HIDE,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_MainWin.hAll_close,&bmqwe);
    m_MainWin.hAll_open = IMAGE_CreateEx(240+5+1,75+3-1-1,76,83,WM_HBKWIN,WM_CF_HIDE,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_MainWin.hAll_open,&bmqwer);
    GUI_Exec1();
	m_MainWin.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_MainWin.hImage_CB_1,&bmComBack_1);
	
	m_MainWin.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_MainWin.hImage_CB_2,&bmComBack_2);
    GUI_Exec1();

    //关关断模式显示
    if(dataStructInterface.closeOffMode==1)
    {
        m_MainWin.hImage_left = IMAGE_CreateEx(-2,77,70,77,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_MainWin.hImage_left,&bmliju_left);
        m_MainWin.hImage_left_1 = IMAGE_CreateEx(54+10-7,103,47,30,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_MainWin.hImage_left_1,&bmliju_left_brown);
    }else
    {
        m_MainWin.hImage_left = IMAGE_CreateEx(-2+4,78+2+2,67,71,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_MainWin.hImage_left,&bmxingcheng_left);
        m_MainWin.hImage_left_1 = IMAGE_CreateEx(54+10-7,103,47,30,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_MainWin.hImage_left_1,&bmxingcheng_left_green);
    }
    GUI_Exec1();
    
    //开关断模式显示
    if(dataStructInterface.openOffMode==1)
    {
        m_MainWin.hImage_right = IMAGE_CreateEx(244,76,76,81,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);	
        IMAGE_SetBitmap(m_MainWin.hImage_right,&bmliju_right);
        m_MainWin.hImage_right_1 = IMAGE_CreateEx(250-36,103,47,30,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_MainWin.hImage_right_1,&bmliju_right_brown);
    }else
    {
        m_MainWin.hImage_right = IMAGE_CreateEx(245+1+6-4,78+2+2,67,71,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);	
        IMAGE_SetBitmap(m_MainWin.hImage_right,&bmxingcheng_right);
        m_MainWin.hImage_right_1 = IMAGE_CreateEx(250/*-36*/,103,47,30,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_MainWin.hImage_right_1,&bmxingcheng_right_green);
    }
    GUI_Exec1();
    m_MainWin.hImage_close = IMAGE_CreateEx(15+3,103,32,27,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    m_MainWin.hImage_open = IMAGE_CreateEx(268,103,31,27,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_MainWin.hImage_close,&bmclose);
    IMAGE_SetBitmap(m_MainWin.hImage_open,&bmopen);
    m_MainWin.hQuan_left = IMAGE_CreateEx(15-10-1 ,103-10-10+3+2,59,59,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_MainWin.hQuan_left,&bmdrive_quan);
    m_MainWin.hQuan_right = IMAGE_CreateEx(255 ,103-10-10+3+2,59,59,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_MainWin.hQuan_right,&bmdrive_quan);
    GUI_Exec1();	
    m_MainWin.hImage3 = IMAGE_CreateEx(141,20,37,34,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        
    //主界面错误码显示
    m_MainWin.hText = TEXT_CreateAsChild(120,70,120,20,hWin,NULL,WM_CF_SHOW|WM_CF_HASTRANS,(char *)infoWinMainCN[dataStructInterface.indexFaultNum[0]],TEXT_CF_LEFT|TEXT_CF_VCENTER);
    TEXT_SetBkColor(m_MainWin.hText,GUI_TRANSPARENT);
    TEXT_SetFont(m_MainWin.hText,&GUI_Fontsong16all);
    TEXT_SetTextColor(m_MainWin.hText, GUI_BLACK);
		
    DrawGradientH_PointWhite(73-5,68,240+5,68);
    DrawGradientH_PointWhite(73-5,93,240+5,93);
    m_MainWin.hImage2 = IMAGE_CreateEx(95,70,22,20,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    GUI_Exec1();

	#if 1
	if(MAIN_MENU_FOCUS_TEXT == g_mainMenuFocus)
    {
        TEXT_SetBkColor(m_MainWin.hText,GUI_ORANGE);
    }
    else
    {
        TEXT_SetBkColor(m_MainWin.hText,GUI_WHITE);
    }
	#endif
    #if 1
    m_MainWin.hStates    = BUTTON_CreateEx(90,70,22,20,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    BUTTON_SetSkin(m_MainWin.hStates,SKIN_TEST1);
    GUI_Exec1();
   #endif
    if(flag_figures.ready==0)
    {
        flag_figures.ready_old=flag_figures.ready;
        BUTTON_SetPressed(m_MainWin.hStates,0);
    }else
    {
        flag_figures.ready_old=flag_figures.ready;
        BUTTON_SetPressed(m_MainWin.hStates,1);
    }

    m_MainWin.hList = LISTBOX_CreateEx( 73-10+2+2+1, 137+1+1+2, 180-10+20-4-2, 104-14, hWin, WM_CF_SHOW, NULL, NULL, NULL);//96  |WM_CF_HASTRANS
    WIDGET_SetEffect(m_MainWin.hList,&WIDGET_Effect_None);
    LISTBOX_SetFont(m_MainWin.hList, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(m_MainWin.hList, 7);//wuxiao
    LISTBOX_SetTextAlign(m_MainWin.hList,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetSel(m_MainWin.hList,-1);
    LISTBOX_SetAutoScrollV(m_MainWin.hList,0);
    LISTBOX_SetOwnerDraw(m_MainWin.hList, _WinCommonMenuListOwnerDraw00);
    if(LANGUAGE_CN == g_LanguageIndex)
    {
			LISTBOX_AddString(m_MainWin.hList,infoWinMainList0CN[g_deviceState]);
    }
    else if(LANGUAGE_EN == g_LanguageIndex)
    {
        LISTBOX_AddString(m_MainWin.hList, (char *)strShow);
    }
    for(i=1;i<WINMAIN_LIST_NUM;i++)
    {
			LISTBOX_AddString(m_MainWin.hList, infoWinMainListCN[i-1]);
		
    }
    GUI_Exec1();
    #if 1
    /*绘制国旗图标*/
    BUTTON_SetDefaultSkinClassic();
    m_MainWin.hBtnNationFlag = BUTTON_CreateEx(200+20, 188, 22, 16,WM_HBKWIN, WM_CF_SHOW|WM_CF_HASTRANS,NULL,NULL);
    BUTTON_SetBitmapEx(m_MainWin.hBtnNationFlag,0,&bmNationalFlag,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnNationFlag,1,&bmNationalFlag,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnNationFlag,2,&bmNationalFlag,0,0);

    /*绘制就地模式按钮*/
    m_MainWin.hBtnLocal = BUTTON_CreateEx(154+14, 164, 27, 20,WM_HBKWIN, WM_CF_SHOW|WM_CF_HASTRANS,NULL,NULL);
    BUTTON_SetBitmapEx(m_MainWin.hBtnLocal,BUTTON_BI_DISABLED  ,&bmLocalNoSelected,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnLocal,BUTTON_BI_PRESSED   ,&bmLocalSelected,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnLocal,BUTTON_BI_UNPRESSED ,&bmLocalNoSelected,0,0);
    if(DEVICE_STATE_LOCAL == g_deviceState)
    {
        BUTTON_SetPressed(m_MainWin.hBtnLocal,1);
    }else
    {
        BUTTON_SetPressed(m_MainWin.hBtnLocal,0);
    }

    /*绘制远控模式按钮*/
    m_MainWin.hBtnRemote = BUTTON_CreateEx(180+14, 164, 27, 20,WM_HBKWIN, WM_CF_SHOW|WM_CF_HASTRANS,NULL,NULL);
    BUTTON_SetBitmapEx(m_MainWin.hBtnRemote,BUTTON_BI_DISABLED,&bmRemoteNoSelected,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnRemote,BUTTON_BI_PRESSED,&bmRemoteSelected,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnRemote,BUTTON_BI_UNPRESSED,&bmRemoteNoSelected,0,0);
    if(DEVICE_STATE_REMOTE == g_deviceState)
    {
        BUTTON_SetPressed(m_MainWin.hBtnRemote,1);
        
    }else
    {
        BUTTON_SetPressed(m_MainWin.hBtnRemote,0);
    }
    GUI_Exec1();
    
    /*绘制关闭模式按钮*/
    m_MainWin.hBtnTurnOff = BUTTON_CreateEx(206+14, 164, 27, 20,WM_HBKWIN, WM_CF_SHOW|WM_CF_HASTRANS,NULL,NULL);
    BUTTON_SetBitmapEx(m_MainWin.hBtnTurnOff,BUTTON_BI_DISABLED,&bmOffNoSelected,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnTurnOff,BUTTON_BI_PRESSED,&bmOffSelected,0,0);
    BUTTON_SetBitmapEx(m_MainWin.hBtnTurnOff,BUTTON_BI_UNPRESSED,&bmOffNoSelected,0,0);
    if(DEVICE_STATE_OFF == g_deviceState)
    {
        BUTTON_SetPressed(m_MainWin.hBtnTurnOff,1);
    }else
    {
        BUTTON_SetPressed(m_MainWin.hBtnTurnOff,0);
    }
    #endif
    GUI_Exec1();
    #if 1
    GUI_SetColor(GUI_GRAY);	
    GUI_SetPenSize(1);	
    GUI_DrawLine(70-3-5,100,252+5,100);	
    GUI_DrawLine(70-3-5,134,252+5,134);	
		
    m_MainWin.hProgbar = PROGBAR_CreateEx(65, 5+2*46+10, 185+3, 22,WM_HBKWIN,WM_CF_SHOW|WM_CF_HASTRANS,PROGBAR_CF_HORIZONTAL,NULL);	  
    WIDGET_SetEffect(m_MainWin.hProgbar, &WIDGET_Effect_None);  
    PROGBAR_SetText(m_MainWin.hProgbar,"");
    PROGBAR_SetMinMax(m_MainWin.hProgbar,0,1000);
    PROGBAR_SetBarColor(m_MainWin.hProgbar,0,GUI_GREEN);
    PROGBAR_SetBarColor(m_MainWin.hProgbar,1,GUI_RED);
    PROGBAR_SetValue(m_MainWin.hProgbar,key_mlx90363.READ_run);
    PROGBAR_SetSkin(m_MainWin.hProgbar,_ProgOwnerSkin2);
    GUI_Exec1();
    #if 1
    if(flag_figures.ready==0)
    {
        m_MainWin.hImage = IMAGE_CreateEx(0,0,320,240,WM_HBKWIN,WM_CF_HIDE,IMAGE_CF_ALPHA,3);
        IMAGE_SetBitmap(m_MainWin.hImage,&bmComBack);
    }else
    {
        m_MainWin.hImage = IMAGE_CreateEx(0,0,320,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,3);
        IMAGE_SetBitmap(m_MainWin.hImage,&bmComBack);
    }
    #endif
		
    GUI_Exec1();

    #endif
    m_MainWin.hTimer = WM_CreateTimer(WM_HBKWIN,0,100,0);
    WM_SetCallback(WM_HBKWIN,_MainWinCallback);
    WM_SetFocus(WM_HBKWIN);
}




#endif

static void _MainWinDestroy(void *p)
{
		WM_DeleteWindow(m_MainWin.hImage_CB_1);      
		WM_DeleteWindow(m_MainWin.hImage_CB_2);      
		WM_DeleteWindow(m_MainWin.hQuan_left);       
		WM_DeleteWindow(m_MainWin.hQuan_right);      
		WM_DeleteWindow(m_MainWin.hList);            
		WM_DeleteWindow(m_MainWin.hImage_close);     
		WM_DeleteWindow(m_MainWin.hImage_open);      
		WM_DeleteWindow(m_MainWin.hAll_close);       
		WM_DeleteWindow(m_MainWin.hAll_open);        
		WM_DeleteWindow(m_MainWin.hStates);          
		WM_DeleteWindow(m_MainWin.hText_close);      
		WM_DeleteWindow(m_MainWin.hText_open);       
		WM_DeleteWindow(m_MainWin.hText);            
		WM_DeleteWindow(m_MainWin.hText1);           
		WM_DeleteWindow(m_MainWin.hText2);           
		WM_DeleteWindow(m_MainWin.hText3);           
		WM_DeleteWindow(m_MainWin.hProgbar);         
		WM_DeleteWindow(m_MainWin.hBtnNationFlag);   
		WM_DeleteWindow(m_MainWin.hBtnLocal);         
		WM_DeleteWindow(m_MainWin.hBtnRemote);        
		WM_DeleteWindow(m_MainWin.hBtnTurnOff);       
		WM_DeleteWindow(m_MainWin.hBtnTurnOff_1);     
		WM_DeleteWindow(m_MainWin.hImage);            
		WM_DeleteWindow(m_MainWin.hImage_123123);     
		WM_DeleteWindow(m_MainWin.hImage_1231234);    
		WM_DeleteWindow(m_MainWin.hImage1);           
		WM_DeleteWindow(m_MainWin.hImage2);           
		WM_DeleteWindow(m_MainWin.hImage3);           
		WM_DeleteWindow(m_MainWin.hImage4);           
		WM_DeleteWindow(m_MainWin.hImage5);           
		WM_DeleteWindow(m_MainWin.hImage_left);       
		WM_DeleteWindow(m_MainWin.hImage_right);      
		WM_DeleteWindow(m_MainWin.hImage_test);       
	  WM_DeleteWindow(m_MainWin.hBtnNew);            
		WM_DeleteWindow(m_MainWin.hImage_left_1);     
		WM_DeleteWindow(m_MainWin.hImage_right_1);    
		
		WM_DeleteTimer(m_MainWin.hTimer);		
	 WM_SetCallback(WM_HBKWIN,NULL);
    memset(&m_MainWin, 0, sizeof(m_MainWin));
}

void _MainWinInterface(void *val)
{
    int sel = *(int *)val;

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
#endif

typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hList;
}LIST_BOX_TYPE;
static LIST_BOX_TYPE m_HListBox = {0};                         
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

    m_HListBox.hFrame = FRAMEWIN_CreateAsChild(-1, -3, LCD_HSIZE + 3, LCD_VSIZE + 8,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);
    FRAMEWIN_SetFont(m_HListBox.hFrame, GUI_DEFAULT_FONT);  
    FRAMEWIN_SetTitleVis(m_HListBox.hFrame, 1);             
FRAMEWIN_SetTextAlign(m_HListBox.hFrame, GUI_TA_HCENTER | GUI_TA_HCENTER);
    pMenu = BT_GetRightChild(pMenu);
    val = BT_GetLeftDepth(pMenu);

    hWin = WM_GetFirstChild(m_HListBox.hFrame);      
    m_HListBox.hList = LISTBOX_CreateAsChild(NULL, hWin, 0, 0, 0, 0,WM_CF_SHOW);
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
      
        LISTBOX_AddString(m_HListBox.hList, (char *)strShow);
    }
    WM_SetCallback(WM_HBKWIN, _ListCallback);
}

static void _ListBoxDestroy(void *p)
{
    WM_DeleteWindow(m_HListBox.hList);
    WM_DeleteWindow(m_HListBox.hFrame);
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_HListBox, 0, sizeof(m_HListBox));
}

void ListBoxInterface(void *val)
{
    int sel = *(int *)val;

    if (m_HListBox.hList == 0)
        return;

    if ((sel < (int)LISTBOX_GetNumItems(m_HListBox.hList)) && (sel >= 0))
        LISTBOX_SetSel(m_HListBox.hList, sel);
}

WIN_INFO_TYPE g_ListBox = {                        
    &m_HListBox.hFrame,
    _ListBoxCreate,
    _ListBoxDestroy,
};

extern GUI_CONST_STORAGE GUI_BITMAP bmback1;
extern GUI_CONST_STORAGE GUI_BITMAP bmback2;
extern GUI_CONST_STORAGE GUI_BITMAP bmhome;
extern GUI_CONST_STORAGE GUI_BITMAP bmhome2;
typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hBtnRtn;
    GUI_HWIN hBtnMain;
    GUI_HWIN hTextAlign;
    GUI_HWIN hList;
}LIST_VIEWER_TYPE;
static LIST_VIEWER_TYPE m_HListView = {0};                        
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

static void _ListViewCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";
    m_HListView.hFrame = FRAMEWIN_CreateAsChild(-1, -3, LCD_HSIZE + 3, LCD_VSIZE + 8,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);
		FRAMEWIN_SetClientColor(m_HListView.hFrame,GUI_WHITE);
    FRAMEWIN_SetFont(m_HListView.hFrame, GUI_DEFAULT_FONT);  
    FRAMEWIN_SetTitleVis(m_HListView.hFrame, 0);             
    pMenu = BT_GetRightChild(pMenu);
    val = BT_GetLeftDepth(pMenu);

    hWin = WM_GetFirstChild(m_HListView.hFrame);
    m_HListView.hBtnRtn    = BUTTON_CreateAsChild(130, 0, 30, 30,hWin,NULL, WM_CF_SHOW);
    m_HListView.hBtnMain   = BUTTON_CreateAsChild(160, 0, 30, 30,hWin,NULL, WM_CF_SHOW);
    m_HListView.hTextAlign = TEXT_CreateEx( 0, 30, 320, 30, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_HListView.hList = LISTVIEW_CreateEx( 0, 60, 320, 150, hWin, WM_CF_SHOW, NULL, NULL);

    LISTVIEW_AddColumn(m_HListView.hList,320, "Col 0", GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTVIEW_SetFont(m_HListView.hList,GUI_FONT_16_1);
    LISTVIEW_SetHeaderHeight(m_HListView.hList,0);
    LISTVIEW_SetGridVis(m_HListView.hList,1);
    LISTVIEW_SetRowHeight(m_HListView.hList,30);
    LISTVIEW_SetBkColor(m_HListView.hList,LISTVIEW_CI_DISABLED , GUI_WHITE);
    LISTVIEW_SetBkColor(m_HListView.hList,LISTVIEW_CI_SEL      , GUI_WHITE);
    LISTVIEW_SetBkColor(m_HListView.hList,LISTVIEW_CI_SELFOCUS , GUI_ORANGE);
    LISTVIEW_SetBkColor(m_HListView.hList,LISTVIEW_CI_UNSEL    , GUI_WHITE);

    LISTVIEW_SetFont(m_HListView.hList, GUI_DEFAULT_FONT);
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
        LISTVIEW_AddRow(m_HListView.hList, NULL);
        LISTVIEW_SetItemText(m_HListView.hList, 0, i, pBuffter);
    }
    WM_SetCallback(WM_HBKWIN, _ListViewCallback);
}

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

void ListViewInterface(void *val)
{
    int sel = *(int *)val;

    if (m_HListView.hList == 0)
        return;

    if ((sel < (int)LISTVIEW_GetNumRows(m_HListView.hList)) && (sel >= 0))
        LISTVIEW_SetSel(m_HListView.hList, sel);
}

WIN_INFO_TYPE g_ListView = {                        
    &m_HListView.hFrame,
    _ListViewCreate,
    _ListViewDestroy,
};



extern GUI_CONST_STORAGE GUI_BITMAP bmbackSel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbackUnsel;
extern GUI_CONST_STORAGE GUI_BITMAP bmhomeSel;
extern GUI_CONST_STORAGE GUI_BITMAP bmhomeUnsel;
typedef struct {
    GUI_HWIN hFrame;
		GUI_HWIN hImage_CB_1;         
		GUI_HWIN hImage_CB_2;	        
    GUI_HWIN hBtnRtn;             
    GUI_HWIN hText;               
    GUI_HWIN hList;               
		GUI_HWIN hImage;              
	WM_HTIMER hTimer;
}LIST_BOX_TYPE_SHOWMAININFO;
static LIST_BOX_TYPE_SHOWMAININFO m_HListBoxShowMainInfo = {0};           
static void _ListBoxShowMainInfoCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
			case WM_PAINT:
				break;
			case WM_TIMER:	
					WM_RestartTimer(pMsg->Data.v, 100);
        break;
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
            _ListBoxShowMainInfoKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

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
	
	GUI_Clear();
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	#if 1       
	m_HListBoxShowMainInfo.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_HListBoxShowMainInfo.hImage_CB_1,&bmComBack_1);
	
	m_HListBoxShowMainInfo.hImage_CB_2 = IMAGE_CreateEx(259,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_HListBoxShowMainInfo.hImage_CB_2,&bmComBack_2);
    #endif
    FRAMEWIN_SetFont(m_HListBoxShowMainInfo.hFrame, &GUI_Fontsong16all);  
    GUI_UC_SetEncodeUTF8();

    FRAMEWIN_SetTitleVis(m_HListBoxShowMainInfo.hFrame, 0);    
    pMenu = BT_GetRightChild(pMenu);
    val = BT_GetLeftDepth(pMenu);

    hWin = WM_GetFirstChild(m_HListBoxShowMainInfo.hFrame);  
    m_HListBoxShowMainInfo.hBtnRtn    = BUTTON_CreateAsChild(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, 23, 23,hWin,NULL, WM_CF_SHOW);
    m_HListBoxShowMainInfo.hText      = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+23, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_HListBoxShowMainInfo.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23, PER_CM_OFFSET*4.5, PER_CM_OFFSET*5, hWin, WM_CF_SHOW, NULL, NULL,NULL);

    hWin = m_HListBoxShowMainInfo.hBtnRtn;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmbackUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmbackSel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmbackUnsel,0,0);
    BUTTON_SetPressed(hWin,1);

    hWin = m_HListBoxShowMainInfo.hText;
    TEXT_SetFont(m_HListBoxShowMainInfo.hText,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_BLUE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, (char *)strShow);

    hWin = m_HListBoxShowMainInfo.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 7);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_DISABLED , GUI_WHITE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SEL      , GUI_ORANGE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SELFOCUS , GUI_ORANGE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_UNSEL    , GUI_WHITE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_DISABLED , GUI_RED);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SEL      , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SELFOCUS , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_UNSEL    , GUI_BLACK);

    memset(strShow,0,sizeof(strShow));
    if(LANGUAGE_CN == g_LanguageIndex)enc_unicode_to_utf8_str(infoTitleCN[0],strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN == g_LanguageIndex)enc_unicode_to_utf8_str(infoTitleEN[0],strShow,STRSHOWBUF_SIZE);
    LISTBOX_AddString(hWin, (char *)strShow);
    LISTBOX_SetItemDisabled(hWin,0,1);

    memset(strShow,0,sizeof(strShow));
    if(LANGUAGE_CN == g_LanguageIndex)enc_unicode_to_utf8_str(infoDeviceStateCN[dataStructInterface.indexDeviceState],strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN == g_LanguageIndex)enc_unicode_to_utf8_str(infoDeviceStateEN[dataStructInterface.indexDeviceState],strShow,STRSHOWBUF_SIZE);
    LISTBOX_AddString(hWin, (char *)strShow);

    memset(strShow,0,sizeof(strShow));
    if(LANGUAGE_CN == g_LanguageIndex)enc_unicode_to_utf8_str(infoTitleCN[1],strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN == g_LanguageIndex)enc_unicode_to_utf8_str(infoTitleEN[1],strShow,STRSHOWBUF_SIZE);
    LISTBOX_AddString(hWin, (char *)strShow);
    LISTBOX_SetItemDisabled(hWin,2,1);

    for(i=0;i<dataStructInterface.numFault;i++)
    {
    	memset(strShow,0,sizeof(strShow));
        if(LANGUAGE_CN == g_LanguageIndex) 
					enc_unicode_to_utf8_str(infoWinMainCN[dataStructInterface.indexFaultNum[i]],strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) 
					enc_unicode_to_utf8_str(infoWinMainEN[dataStructInterface.indexFaultNum[i]],strShow,STRSHOWBUF_SIZE);
        LISTBOX_AddString(hWin, (char *)strShow);
    }
	
		m_HListBoxShowMainInfo.hTimer = WM_CreateTimer(WM_HBKWIN,0,100,0);
		WM_SetCallback(WM_HBKWIN, _ListBoxShowMainInfoCallback);
    WM_SetFocus(WM_HBKWIN);
    
}

static void _ListBoxShowMainInfoDestroy(void *p)
{
		WM_DeleteWindow(m_HListBoxShowMainInfo.hImage_CB_1);          
		WM_DeleteWindow(m_HListBoxShowMainInfo.hImage_CB_2);	        
    WM_DeleteWindow(m_HListBoxShowMainInfo.hBtnRtn);              
    WM_DeleteWindow(m_HListBoxShowMainInfo.hText);                
    WM_DeleteWindow(m_HListBoxShowMainInfo.hList);                
		WM_DeleteWindow(m_HListBoxShowMainInfo.hImage);               
	WM_DeleteTimer(m_HListBoxShowMainInfo.hTimer); 
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_HListBoxShowMainInfo, 0, sizeof(m_HListBoxShowMainInfo));
}

void ListBoxShowMainInfoInterface(void *val)
{
    int sel = *(int *)val;
    char setSel = 0;
    if (m_HListBoxShowMainInfo.hList == 0)       return;

    if(sel == 100 )
    {
        return ;
    }
    else
    {
        BUTTON_SetPressed(m_HListBoxShowMainInfo.hBtnRtn,0);
        LISTBOX_SetBkColor(m_HListBoxShowMainInfo.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        if(sel > 0)
        {
            setSel = sel + 2 ;
            LISTBOX_SetSel(m_HListBoxShowMainInfo.hList, setSel);
        }
        else
        {
            setSel = sel + 1 ;
            LISTBOX_SetSel(m_HListBoxShowMainInfo.hList, setSel);
        }
    }
}

void _ListBoxShowMainInfoKeyDown(void)
{
	  char curIndex=0;
	  char curIndexDisable=0;

    curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
    if(BUTTON_IsPressed(m_HListBoxShowMainInfo.hBtnRtn))
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

void _ListBoxShowMainInfoKeyUp(void)
{
	  char curIndex =0;
	  char curIndexDisable =0;
	  char curLen= LISTBOX_GetNumItems(m_HListBoxShowMainInfo.hList);

    curIndex = curLen-1;
    curIndexDisable = LISTBOX_GetItemDisabled(m_HListBoxShowMainInfo.hList,curIndex);
    if(BUTTON_IsPressed(m_HListBoxShowMainInfo.hBtnRtn))
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

void _ListBoxShowMainInfoKeyEnter(void)
{
     int idm = 0;
     int sel = 0;
     sel = LISTBOX_GetSel(m_HListBoxShowMainInfo.hList);
     if( sel>2 )
     {
         idm =sel -2;
     }
     else
     {
         idm =sel -1;
     }
     if(BUTTON_IsPressed(m_HListBoxShowMainInfo.hBtnRtn))
     {
         WIN_Exit(0);
     }
     else
     {
         WIN_Enter(&idm);
     }
}

WIN_INFO_TYPE g_ListBoxShowMainInfo = {                        
    &m_HListBoxShowMainInfo.hFrame,
    _ListBoxShowMainInfoCreate,
    _ListBoxShowMainInfoDestroy,
};



typedef struct {
    GUI_HWIN hFrame;    
		GUI_HWIN hImage_CB_1;           
		GUI_HWIN hImage_CB_2;           
    GUI_HWIN hBtnRtn;               
    GUI_HWIN hText;                 
    GUI_HWIN hTextExp;              
    GUI_HWIN hTextMethod;           
		GUI_HWIN hImage;                
}HELP_INFO_SHOW_TYPE;
static HELP_INFO_SHOW_TYPE m_WinShowHelpInfo = {0};                       
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

static void _WinShowHelpInfoCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    char            *pBuffter   = g_LCDBuff;
     char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    unsigned char   show_index  = pMenu->data->menunum;
GUI_Clear();

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
#if 1     
	m_WinShowHelpInfo.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_WinShowHelpInfo.hImage_CB_1,&bmComBack_1);
	
	m_WinShowHelpInfo.hImage_CB_2 = IMAGE_CreateEx(259,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_WinShowHelpInfo.hImage_CB_2,&bmComBack_2);
    #endif
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_WinShowHelpInfo.hFrame, 0);   
    pMenu = BT_GetRightChild(pMenu);
    val = BT_GetLeftDepth(pMenu);

    hWin = WM_GetFirstChild(m_WinShowHelpInfo.hFrame);     
    m_WinShowHelpInfo.hBtnRtn    = BUTTON_CreateAsChild(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, 23, 23,hWin,NULL, WM_CF_SHOW);
    m_WinShowHelpInfo.hText      = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+23, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_WinShowHelpInfo.hTextExp   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+PER_CM_OFFSET  , PER_CM_OFFSET*4.5, PER_CM_OFFSET*2, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_WinShowHelpInfo.hTextMethod= TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+PER_CM_OFFSET*3, PER_CM_OFFSET*4.5, PER_CM_OFFSET*2, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");

    hWin = m_WinShowHelpInfo.hBtnRtn;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmbackUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmbackSel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmbackUnsel,0,0);
    BUTTON_SetPressed(hWin,1);

    hWin = m_WinShowHelpInfo.hText;
    TEXT_SetFont(m_WinShowHelpInfo.hText,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_BLUE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);

    memset(strShow,0,sizeof(strShow));
    memcpy(strShow,GetExpInfoPtr(dataStructInterface.helpExpIndex[show_index],g_LanguageIndex),STRSHOWBUF_SIZE);
    hWin = m_WinShowHelpInfo.hTextExp;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_TOP);
    TEXT_SetTextColor(hWin,GUI_BLACK);// GUI_BLACK
    TEXT_SetWrapMode(hWin,GUI_WRAPMODE_CHAR);
    TEXT_SetText(hWin, strShow);

    memset(strShow,0,sizeof(strShow));
   memcpy(strShow,GetHandleInfoPtr(dataStructInterface.helpMethodIndex[show_index],g_LanguageIndex),STRSHOWBUF_SIZE);
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

static void _WinShowHelpInfoDestroy(void *p)
{
		WM_DeleteWindow(m_WinShowHelpInfo.hImage_CB_1);          
		WM_DeleteWindow(m_WinShowHelpInfo.hImage_CB_2);          
    WM_DeleteWindow(m_WinShowHelpInfo.hBtnRtn);              
    WM_DeleteWindow(m_WinShowHelpInfo.hText);                
    WM_DeleteWindow(m_WinShowHelpInfo.hTextExp);             
    WM_DeleteWindow(m_WinShowHelpInfo.hTextMethod);          
		WM_DeleteWindow(m_WinShowHelpInfo.hImage);               
    WM_SetCallback(WM_HBKWIN, NULL);
		
    memset(&m_WinShowHelpInfo, 0, sizeof(m_WinShowHelpInfo));
}

void WinShowHelpInfoInterface(void *val)
{

}

WIN_INFO_TYPE g_WinShowHelpInfo = {                        
    &m_WinShowHelpInfo.hFrame,
    _WinShowHelpInfoCreate,
    _WinShowHelpInfoDestroy,
};


typedef struct {
    GUI_HWIN hFrame;       
	
	#if 1   
		GUI_HWIN hImage_CB_1;           
		GUI_HWIN hImage_CB_2;           
		GUI_HWIN hStates;               
		GUI_HWIN hImage_left_1;         
		GUI_HWIN hImage_right_1;        
		GUI_HWIN hAll_close;            
		GUI_HWIN hAll_open;             
		GUI_HWIN  hQuan_left;           
		GUI_HWIN  hQuan_right;          
		GUI_HWIN  hText_close;          
		GUI_HWIN  hText_open;           
		GUI_HWIN   hImage;              
		#endif                                
		GUI_HWIN hBtnRtn;       
		GUI_HWIN hBtnState;     
		GUI_HWIN hBtnLeft;      
		GUI_HWIN hBtnRight;     
		GUI_HWIN hBtnInfo;      
		GUI_HWIN hTextHeader;   
		GUI_HWIN hTextInfo;     
		GUI_HWIN hTextNum1;     
		GUI_HWIN hTextNum2;     
		GUI_HWIN hProgbar;      
		GUI_HWIN hStateimage;   
		GUI_HWIN hImage_test;   
		GUI_HWIN hImage1;       
		GUI_HWIN hImage_left;   
		GUI_HWIN hImage_right;  
		GUI_HWIN  hImage_TEST;  
		
		WM_HTIMER hTimer; 
		
}LOCAL_OPERATION_TYPE;

static LOCAL_OPERATION_TYPE m_WinLocalOp = {0};    
int flag_TAB_3s=0;
int flag_TAB_3s_start=0;
void _WinLocalOpKeyDown(void)
{
	motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
	motorset.stop=42;
    if(BUTTON_IsPressed(m_WinLocalOp.hBtnRtn))
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

void _WinLocalOpKeyUp(void)
{	
	motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
	motorset.stop=41;
    if(BUTTON_IsPressed(m_WinLocalOp.hBtnRtn))
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

uint16_t flag_stop_button_left=0;
uint16_t flag_stop_button_right=0;
void _WinLocalOpKeyEnter(void)
{
    int id = 0;
	#if 1
	if(flag_TAB_3s==1)
	{
		flag_figures.handle_stop=0;   
	}else
	{
		flag_figures.handle_stop=1;   
	}
	flag_TAB_3s_start=0;
	#endif
    if(BUTTON_IsPressed(m_WinLocalOp.hBtnRtn))
    {
        WIN_Exit(0);
    }
    else if(MAIN_MENU_FOCUS_TEXT == g_hdlMenuFocus)
    {
        WIN_Enter(&id);
    }
    else if(BUTTON_IsPressed(m_WinLocalOp.hBtnLeft))
    {
        SPEED_Stand=dataStructInterface.speed_close;
        TORQUE_Stand=dataStructInterface.moment_close;
        dataStructInterface.stateOpen=0;
			if(motorset.DIR==1)
			{
					if(dataStructInterface.stateClose==0)
					{
						if(flag_figures.handle_stop==0)
						{
								
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
							motorset_s=12;

						}else
						if(flag_figures.handle_stop==1)
						{
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
							motorset.stop=40;
						}
					}else
					{			
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
						motorset.stop=39;
					}
			}else
			if(motorset.DIR==2)
			{
				if(dataStructInterface.stateOpen==0)
					{
						if(flag_figures.handle_stop==0)
						{
								
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
							motorset_s=11;

						}else
						if(flag_figures.handle_stop==1)
						{
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
							motorset.stop=38;
						}
					}else
					if(dataStructInterface.stateOpen==1)
					{			
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
						motorset.stop=37;
					}
			}
    }
		else if(BUTTON_IsPressed(m_WinLocalOp.hBtnRight))
    {
				SPEED_Stand=dataStructInterface.speed_open;
				TORQUE_Stand=dataStructInterface.moment_open;
				dataStructInterface.stateClose=0;
			if(motorset.DIR==1)
			{
					if(dataStructInterface.stateOpen==0)
					{
						if(flag_figures.handle_stop==0)
						{
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
							motorset_n=10;
					
						}else
						if(flag_figures.handle_stop==1)
						{
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
							motorset.stop=36;
						}
					}else
					{			
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
						motorset.stop=35;
					}
			}else
			if(motorset.DIR==2)
			{
				if(dataStructInterface.stateClose==0)
					{
						if(flag_figures.handle_stop==0)
						{
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
							motorset_n=9;
					
						}else
						if(flag_figures.handle_stop==1)
						{
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
							motorset.stop=34;
						}
					}
					else
					{			
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
						motorset.stop=33;
					}
			}
    }
}
void _WinLocalOpKeyTAB()
{
	flag_TAB_3s_start=1;
}

void  _WinLocalOpKeyENTER_BEF()
{
	if(BUTTON_IsPressed(m_WinLocalOp.hBtnLeft))
    {
        SPEED_Stand=dataStructInterface.speed_close;
        TORQUE_Stand=dataStructInterface.moment_close;
        if(flag_estop==1)
        {
            flag_estop=0;
            if(motorset.DIR_MOTOR_old==motorset.DIR_MOTOR_s)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t; 
                motorset.stop=32;
            }
            flag_stop_button_left=1;
				
        }
        if(flag_stop_button_left==1)
        {
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t; 
            motorset.stop=31;
        }else
        {
            #if 1
            flag_stop_button_right=0;
            dataStructInterface.stateOpen=0;
            if(motorset.DIR==1)
            {
                if(dataStructInterface.stateClose==0)
                {
                    flag_estop=0;
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
                    motorset_s=10;
                    GUI_Delay(10);
                    WM_DisableWindow(m_WinLocalOp.hBtnLeft);
                    GUI_Delay(10);
                    BUTTON_SetPressed(m_WinLocalOp.hBtnLeft,1);
                    WM_EnableWindow(m_WinLocalOp.hBtnLeft);
                    if(flag_figures.handle_stop==1)
                    {
                        motorset.DIR_MOTOR=motorset.DIR_MOTOR_s; 
                        motorset_s=9;
                    }else
                    {
                        flag_stop_button_left=0;
                        motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;  
                        motorset.stop=30;
                    }
                }else
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                    motorset.stop=29;
                }	
            }
            else if(motorset.DIR==2)
            {
                if(dataStructInterface.stateOpen==0)
                {
                    flag_estop=0;
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
                    motorset_s=8;
                    GUI_Delay(10);
                    WM_DisableWindow(m_WinLocalOp.hBtnLeft);
                    GUI_Delay(10);
                    BUTTON_SetPressed(m_WinLocalOp.hBtnLeft,1);
                    WM_EnableWindow(m_WinLocalOp.hBtnLeft);
                    if(flag_figures.handle_stop==1)
                    {
                        motorset.DIR_MOTOR=motorset.DIR_MOTOR_s; 
                        motorset_s=7;
                    }else
                    {
                        flag_stop_button_left=0;
                        motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;  
                        motorset.stop=28;
                    }
                }else
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                    motorset.stop=27;
                }	
            }					
			#endif
        }
    }
    else if(BUTTON_IsPressed(m_WinLocalOp.hBtnRight))
    {
        SPEED_Stand=dataStructInterface.speed_open;
        TORQUE_Stand=dataStructInterface.moment_open;
        if(flag_estop==1)
        {
            flag_estop=0;
            if(motorset.DIR_MOTOR_old==motorset.DIR_MOTOR_n)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t; 
                motorset.stop=26;
            }
            flag_stop_button_right=1;
        }
        if(flag_stop_button_right==1)
        {
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t; 
            motorset.stop=25;
        }else
        {
			#if 1
            flag_stop_button_left=0;
            dataStructInterface.stateClose=0;
            if(motorset.DIR==1)
            {
                if(dataStructInterface.stateOpen==0)
                {
                    dataStructInterface.stateClose=0;
                    if(flag_figures.handle_stop==1)
                    {
                        motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;  	
                        motorset_n=8;
                    }else
                    if(flag_figures.handle_stop==0)
                    {
                        motorset.DIR_MOTOR=motorset.DIR_MOTOR_t; 
                        motorset.stop=24;
                    }
                }else
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                    motorset.stop=23;
                }
            }else
            if(motorset.DIR==2)
            {
                if(dataStructInterface.stateClose==0)
                {
                    dataStructInterface.stateClose=0;
                    if(flag_figures.handle_stop==1)
                    {
                        motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;  
                        motorset_n=7;							
                    }else
                    if(flag_figures.handle_stop==0)
                    {
                        motorset.DIR_MOTOR=motorset.DIR_MOTOR_t; 
                        motorset.stop=22;
                    }
                }else
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                    motorset.stop=21;
                }
            }
			#endif
        }
        GUI_Delay(10);
        WM_DisableWindow(m_WinLocalOp.hBtnRight);
        GUI_Delay(10);
        BUTTON_SetPressed(m_WinLocalOp.hBtnRight,1);
        WM_EnableWindow(m_WinLocalOp.hBtnRight);
						
    }
}

extern uint16_t SPEED_send;
extern uint16_t current_up;
extern uint16_t Current_BASE;
extern uint16_t Current_UP;
extern int ADC_temp;
void _WinLocalOpRefresh(void)
{
    GUI_HWIN        hWin        = 0;
    char numShow[8];
    hWin = WM_GetFirstChild(m_WinLocalOp.hFrame);            
	GUI_SetFont(&GUI_Fontsong33);

	if(motorset.flag_MOTOR_Run)
	{
		dataStructInterface.stateOpen  = 0;
		dataStructInterface.stateClose = 0;
		dataStructInterface.stateMid   = 1;
	}else
	if(motorset.flag_MOTOR_Close)
	{
		dataStructInterface.stateOpen  = 0;
		dataStructInterface.stateClose = 1;
		dataStructInterface.stateMid   = 0;
	}else
	if(motorset.flag_MOTOR_Open)
	{
		dataStructInterface.stateOpen  = 1;
		dataStructInterface.stateClose = 0;
		dataStructInterface.stateMid   = 0;
	}
	
if(motorset.flag_MOTOR_Close==1)	
	{
		if((encoder.num==2)||(encoder.num==1)||(encoder.num==4)||(encoder.num==3))
		{
			if(flag_figures.run1_100==1)
			{
				GUI_DrawGradientV(80,35-1,240,65+2+1,GUI_WHITE,GUI_WHITE);
				DrawGradientH_PointWhite(73,68,240,68);
				flag_figures.run1_100=0;
				
			}
			flag_figures.run0_0=1;
			GUI_DrawBitmap(&bmclose, 140,20+14);
			WM_ShowWindow(m_WinLocalOp.hAll_close);
			PROGBAR_SetValue(m_WinLocalOp.hProgbar,0);
		}else
		if((encoder.num==7)||(encoder.num==8)||(encoder.num==5))
		{
				if(flag_figures.run1_100==1)
				{
					GUI_DrawGradientV(80,35-1,240,65+2+1,GUI_WHITE,GUI_WHITE);
					DrawGradientH_PointWhite(73,68,240,68);
					flag_figures.run1_100=0;
				}
						flag_figures.run100_100=1;
				GUI_DrawBitmap(&bmopen, 140,20+14);
				WM_ShowWindow(m_WinLocalOp.hAll_open);
				PROGBAR_SetValue(m_WinLocalOp.hProgbar,1000);
		}else
		{
			if(flag_figures.run1_100==1)
			{
				GUI_DrawGradientV(80,35-1,240,65+2+1,GUI_WHITE,GUI_WHITE);
				DrawGradientH_PointWhite(73,68,240,68);
				flag_figures.run1_100=0;
			}
			flag_figures.run0_0=1;
			GUI_DrawBitmap(&bmclose, 140,20+14);
			WM_ShowWindow(m_WinLocalOp.hAll_close);
			PROGBAR_SetValue(m_WinLocalOp.hProgbar,0);
		}
	}
    else if(motorset.flag_MOTOR_Open==1)
	{
		if((encoder.num==2)||(encoder.num==1)||(encoder.num==4)||(encoder.num==3))
		{
				if(flag_figures.run1_100==1)
				{
					GUI_DrawGradientV(80,35-1,240,65+2+1,GUI_WHITE,GUI_WHITE);
					DrawGradientH_PointWhite(73,68,240,68);
					flag_figures.run1_100=0;
				}
                flag_figures.run100_100=1;
                GUI_DrawBitmap(&bmopen,140,20+14);
				WM_ShowWindow(m_WinLocalOp.hAll_open);
				PROGBAR_SetValue(m_WinLocalOp.hProgbar,1000);
		}else
		if((encoder.num==7)||(encoder.num==8)||(encoder.num==5))
		{
			if(flag_figures.run1_100==1)
			{
				GUI_DrawGradientV(80,35-1,240,65+2+1,GUI_WHITE,GUI_WHITE);
				DrawGradientH_PointWhite(73,68,240,68);
				flag_figures.run1_100=0;
			}
			flag_figures.run0_0=1;
			GUI_DrawBitmap(&bmclose,140,20+14);
			WM_ShowWindow(m_WinLocalOp.hAll_close);
				WM_ShowWindow(m_WinLocalOp.hText_close);
			PROGBAR_SetValue(m_WinLocalOp.hProgbar,0);
		}else
		{
				if(flag_figures.run1_100==1)
				{
					GUI_DrawGradientV(80,35-1,240,65+2+1,GUI_WHITE,GUI_WHITE);
					DrawGradientH_PointWhite(73,68,240,68);
					flag_figures.run1_100=0;
				}
						flag_figures.run100_100=1;
				GUI_DrawBitmap(&bmopen, 140,20+14);
				WM_ShowWindow(m_WinLocalOp.hAll_open);
				PROGBAR_SetValue(m_WinLocalOp.hProgbar,1000);
		}
	}else
	if(motorset.flag_MOTOR_Run==1)
	{
		GUI_SetColor(GUI_BLACK);	
		#if 1
		if((flag_figures.run100_100==1)||(flag_figures.run0_0==1))
		{
			GUI_DrawGradientV(80,29,240,65+4,GUI_WHITE,GUI_WHITE);
			DrawGradientH_PointWhite(73,68,240,68);
			if(flag_figures.run100_100==1)
			{
				flag_figures.run100_100=0;
				GUI_DrawGradientV(246,76,322,159,GUI_WHITE,GUI_WHITE);
				WM_HideWindow(m_WinLocalOp.hAll_open);	
				WM_ShowWindow(m_WinLocalOp.hProgbar);	
				WM_ShowWindow(m_WinLocalOp.hQuan_right);	
				WM_ShowWindow(m_WinLocalOp.hImage_right);	
			}
			if(flag_figures.run0_0==1)
			{
				flag_figures.run0_0=0;
				GUI_DrawGradientV(-3,76,76,159,GUI_WHITE,GUI_WHITE);
				WM_HideWindow(m_WinLocalOp.hAll_close);	
				WM_ShowWindow(m_WinLocalOp.hProgbar);	
				WM_ShowWindow(m_WinLocalOp.hQuan_left);	
				WM_ShowWindow(m_WinLocalOp.hImage_left);	
			}
			GUI_DrawGradientV(80,29,240,65+4,GUI_WHITE,GUI_WHITE);
			DrawGradientH_PointWhite(73,68,240,68);
			
		}
		flag_figures.run1_100=1;
		if(key_mlx90363.READ_run_1>=1000)
		{datadula=3;}else
		{datadula=2;}
		if(datadula==3)
		{
			GUI_DrawGradientV(80,35-1,240,65+4,GUI_WHITE,GUI_WHITE);
			DrawGradientH_PointWhite(73,68,240,68);
			flag_figures.datadula3=1;
			GUI_SetFont(&GUI_Fontsong33);
			GUI_DispDecAt(100,DEBUG_X_OFFSET+150-10-10-20,35,datadula);
			GUI_SetFont(&GUI_Fontsong16all);
			GUI_DispDecAt(0,20+150+18,49,1);
			if(flag_figures.datadula2==1)
			{
					flag_figures.datadula2=0;
				}		
		}else
		{
			datadula=2;	
			flag_figures.datadula2=1;
			if(flag_figures.datadula3==1)
			{
				GUI_DrawGradientV(80,35-1,240,65+4,GUI_WHITE,GUI_WHITE);
				DrawGradientH_PointWhite(73,68,240,68);
				flag_figures.datadula3=0;				
			}
            GUI_SetFont(&GUI_Fontsong33);
            GUI_DispDecAt(key_mlx90363.Integer_3,140,35+2,datadula);
			GUI_SetColor(GUI_BLACK);
			GUI_SetFont(&GUI_Fontsong16all);
            GUI_DispDecAt(key_mlx90363.decimal_3,20+150+18,49,1);		
		}
		#endif
		PROGBAR_SetValue(m_WinLocalOp.hProgbar,key_mlx90363.READ_run_1);
		
		#if  1		
		GUI_SetFont(&GUI_Fontsong16all);
		GUI_DispStringAt(",",20+150-32-18+52,45);//184，7		
		GUI_SetFont(&GUI_Fontsong16all);
		GUI_DispStringAt("%",DEBUG_X_OFFSET+150+18+10,35/*+32-4*/);

		#endif
		if(motorset.flag_estop_old!=  flag_estop)
		{
			motorset.flag_estop_old=  flag_estop;
			PROGBAR_SetSkin(m_WinLocalOp.hProgbar,_ProgOwnerSkin2);
		}
		
		
	}
	
	if(flag_figures.ready_old!=flag_figures.ready)
	{
		GUI_DrawGradientV(75,75,240,91,GUI_WHITE,GUI_WHITE);
		GUI_DrawGradientV(75,75,240,91,GUI_WHITE,GUI_WHITE);
		if(flag_figures.ready==0)
		{
			
			GUI_DrawGradientV(0,0,60,76,GUI_WHITE,GUI_WHITE);
				GUI_DrawGradientV(0,76,15,160,GUI_WHITE,GUI_WHITE);
				GUI_DrawGradientV(0,160,60,240,GUI_WHITE,GUI_WHITE);
				GUI_DrawGradientV(60,0,260,15,GUI_WHITE,GUI_WHITE);
				
				GUI_DrawGradientV(260,0,3200,76,GUI_WHITE,GUI_WHITE);
				GUI_DrawGradientV(300,76,320,160,GUI_WHITE,GUI_WHITE);
				GUI_DrawGradientV(260,160,320,240,GUI_WHITE,GUI_WHITE);
				
				GUI_DrawGradientV(60,228,260,240,GUI_WHITE,GUI_WHITE);
			flag_figures.ready_old=flag_figures.ready;
			BUTTON_SetPressed(m_WinLocalOp.hStates,0);
			WM_HideWindow(m_WinLocalOp.hImage);
			header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+41, DEBUG_Y_OFFSET,184-20,23);
		}else
		{	
			flag_figures.ready_old=flag_figures.ready;
			BUTTON_SetPressed(m_WinLocalOp.hStates,1);
			WM_ShowWindow(m_WinLocalOp.hImage);
			
		}
			TEXT_SetBkColor(m_WinLocalOp.hTextInfo,GUI_TRANSPARENT);
			TEXT_SetFont(m_WinLocalOp.hTextInfo,&GUI_Fontsong16all);
			TEXT_SetTextColor(m_WinLocalOp.hTextInfo, GUI_BLACK);
		if(MAIN_MENU_FOCUS_TEXT == g_mainMenuFocus)
    {
        TEXT_SetBkColor(m_WinLocalOp.hTextInfo,GUI_ORANGE);
    }
    else
    {
        TEXT_SetBkColor(m_WinLocalOp.hTextInfo,GUI_WHITE);
    }
	}

}

static void _WinLocalOpCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
			case WM_TIMER:
				WM_RestartTimer(pMsg->Data.v, 100);
				_WinLocalOpRefresh();
					break;
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
            case GUI_KEY_TAB:
                _WinLocalOpKeyTAB();
                break;
            case GUI_KEY_ENTER_BEF:
                _WinLocalOpKeyENTER_BEF();
                break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}
static void _WinLocalOpCreate(void *p)
{
    unsigned int i=0;
    char numShow[8];
    GUI_HWIN        hWin        = 0;
	MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
	 char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    GUI_AA_SetFactor(MAG);
	WIDGET_SetDefaultEffect_None();
    if (NULL == pTitle) pTitle = "";	
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	motorset.flag_estop_old=  flag_estop;
	motorset.local_error=1;
	
	GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_WinLocalOp.hFrame, 0);             
    flag_figures.ready_old=flag_figures.ready;		
    hWin = WM_GetFirstChild(m_WinLocalOp.hFrame);             
    m_WinLocalOp.hBtnRtn    = BUTTON_CreateAsChild(56, 5, 40, 22,hWin,NULL, WM_CF_SHOW);    
    hWin = m_WinLocalOp.hBtnRtn;		
    BUTTON_SetSkin(hWin,SKIN_Btn_Btn);
    BUTTON_SetPressed(hWin,1);

    header_txt(97, 5,164,23);
    hWin = WM_GetFirstChild(m_WinLocalOp.hFrame); 
    m_WinLocalOp.hTextHeader= TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+40, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    hWin = m_WinLocalOp.hTextHeader;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    hWin = WM_GetFirstChild(m_WinLocalOp.hFrame);
    m_WinLocalOp.hBtnLeft   = BUTTON_CreateAsChild(4+1,88 ,59, 60,hWin,NULL, WM_CF_SHOW);
    hWin = m_WinLocalOp.hBtnLeft;
    BUTTON_SetSkin(hWin,SKIN_DriverLeft_Button_Return);
    BUTTON_SetPressed(hWin,0);
    hWin = WM_GetFirstChild(m_WinLocalOp.hFrame);	
    m_WinLocalOp.hBtnRight  = BUTTON_CreateAsChild(250+5, 88-1, 59, 60,hWin,NULL, WM_CF_SHOW);
    hWin = m_WinLocalOp.hBtnRight;
    BUTTON_SetSkin(hWin,SKIN_DriverRight_Button_Return);
    BUTTON_SetPressed(hWin,0);		
    m_WinLocalOp.hQuan_left = IMAGE_CreateEx(15-10-1 ,103-10-10+3+2,59,59,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_WinLocalOp.hQuan_left,&bmdrive_quan);
    m_WinLocalOp.hQuan_right = IMAGE_CreateEx(255 ,103-10-10+3+2,59,59,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_WinLocalOp.hQuan_right,&bmdrive_quan);
		
		
    m_WinLocalOp.hAll_close = IMAGE_CreateEx(-5+2,75+3-1-1,76,83,WM_HBKWIN,WM_CF_HIDE,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_WinLocalOp.hAll_close,&bmqwe);
    m_WinLocalOp.hAll_open = IMAGE_CreateEx(240+5+1,75+3-1-1,76,83,WM_HBKWIN,WM_CF_HIDE,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_WinLocalOp.hAll_open,&bmqwer);
    DrawGradientH_PointWhite(73,68,240,68);
    DrawGradientH_PointWhite(73,93,240,93);
    hWin = m_WinLocalOp.hFrame;
    StrShowClear();
    m_WinLocalOp.hTextInfo = TEXT_CreateAsChild(120,70,120,20,hWin,NULL,WM_CF_SHOW|WM_CF_HASTRANS,(char *)infoWinMainCN[dataStructInterface.indexFaultNum[0]],TEXT_CF_LEFT|TEXT_CF_VCENTER);			
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
    m_WinLocalOp.hStates    = BUTTON_CreateEx(90,70,22,20,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    BUTTON_SetSkin(m_WinLocalOp.hStates,SKIN_TEST1);
    if(flag_figures.ready==0)
    {
        flag_figures.ready_old=flag_figures.ready;
        BUTTON_SetPressed(m_WinLocalOp.hStates,0);
    }else
    {
        flag_figures.ready_old=flag_figures.ready;
        BUTTON_SetPressed(m_WinLocalOp.hStates,1);
    }
    #if 1	
    if(dataStructInterface.closeOffMode==1)
    {
        m_WinLocalOp.hImage_left = IMAGE_CreateEx(-2,77,70,77,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_WinLocalOp.hImage_left,&bmliju_left);
        m_WinLocalOp.hImage_left_1 = IMAGE_CreateEx(54+10-7,103,47,30,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_WinLocalOp.hImage_left_1,&bmliju_left_brown);
    }else
    {
        m_WinLocalOp.hImage_left = IMAGE_CreateEx(-2+4,78+2+2,67,71,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_WinLocalOp.hImage_left,&bmxingcheng_left);
        m_WinLocalOp.hImage_left_1 = IMAGE_CreateEx(54+10-7,103,47,30,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_WinLocalOp.hImage_left_1,&bmxingcheng_left_green);
    }
		
    if(dataStructInterface.openOffMode==1)
    {
        m_WinLocalOp.hImage_right = IMAGE_CreateEx(244,76,76,81,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);	
        IMAGE_SetBitmap(m_WinLocalOp.hImage_right,&bmliju_right);
        m_WinLocalOp.hImage_right_1 = IMAGE_CreateEx(250-36,103,47,30,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_WinLocalOp.hImage_right_1,&bmliju_right_brown);
    }else
    {
        m_WinLocalOp.hImage_right = IMAGE_CreateEx(245+1+6-4,78+2+2,67,71,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);	
        IMAGE_SetBitmap(m_WinLocalOp.hImage_right,&bmxingcheng_right);
        m_WinLocalOp.hImage_right_1 = IMAGE_CreateEx(250/*-36*/,103,47,30,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_WinLocalOp.hImage_right_1,&bmxingcheng_right_green);
    }
    #endif
    GUI_SetColor(GUI_GRAY);	
    GUI_SetPenSize(1);	
    GUI_DrawLine(70-3-5,100,252+5,100);	
    GUI_DrawLine(70-3-5,134,252+5,134);	
    hWin = m_WinLocalOp.hFrame;
    m_WinLocalOp.hProgbar    = PROGBAR_CreateEx(65, 5+2*46+10, 185+3, /*19*/22,WM_HBKWIN,WM_CF_SHOW|WM_CF_HASTRANS,PROGBAR_CF_HORIZONTAL,NULL);
    PROGBAR_SetText(m_WinLocalOp.hProgbar,"");
    PROGBAR_SetMinMax(m_WinLocalOp.hProgbar,0,1000);
    PROGBAR_SetValue(m_WinLocalOp.hProgbar,key_mlx90363.READ_run_1);
    PROGBAR_SetSkin(m_WinLocalOp.hProgbar,_ProgOwnerSkin2);
	m_WinLocalOp.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	hWin = m_WinLocalOp.hImage_CB_1;
	IMAGE_SetBitmap(hWin,&bmComBack_1);
	
	m_WinLocalOp.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	hWin = m_WinLocalOp.hImage_CB_2;
	IMAGE_SetBitmap(hWin,&bmComBack_2);
	
	
	#if 1
    if(flag_figures.ready==0)
    {
        m_WinLocalOp.hImage = IMAGE_CreateEx(0,0,320,240,WM_HBKWIN,WM_CF_HIDE,IMAGE_CF_ALPHA,3);
        IMAGE_SetBitmap(m_WinLocalOp.hImage,&bmComBack);
    }else
    {
        m_WinLocalOp.hImage = IMAGE_CreateEx(0,0,320,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,3);
        IMAGE_SetBitmap(m_WinLocalOp.hImage,&bmComBack);
    }
    #endif
	
    WM_SetCallback(WM_HBKWIN,_WinLocalOpCallback);
    m_WinLocalOp.hTimer = WM_CreateTimer(WM_HBKWIN,0,100,0);
    WM_SetFocus(WM_HBKWIN);
}


static void _WinLocalOpDestroy(void *p)
{
	
		WM_DeleteWindow(m_WinLocalOp.hImage_CB_1);            
		WM_DeleteWindow(m_WinLocalOp.hImage_CB_2);            
		WM_DeleteWindow(m_WinLocalOp.hStates);                
		WM_DeleteWindow(m_WinLocalOp.hImage_left_1);          
		WM_DeleteWindow(m_WinLocalOp.hImage_right_1);         
		WM_DeleteWindow(m_WinLocalOp.hAll_close);             
		WM_DeleteWindow(m_WinLocalOp.hAll_open);              
		WM_DeleteWindow(m_WinLocalOp.hQuan_left);             
		WM_DeleteWindow(m_WinLocalOp.hQuan_right);            
		WM_DeleteWindow(m_WinLocalOp.hText_close);            
		WM_DeleteWindow(m_WinLocalOp.hText_open);             
		WM_DeleteWindow(m_WinLocalOp.hImage);                                   
		WM_DeleteWindow(m_WinLocalOp.hBtnRtn);      
		WM_DeleteWindow(m_WinLocalOp.hBtnState);    
		WM_DeleteWindow(m_WinLocalOp.hBtnLeft);     
		WM_DeleteWindow(m_WinLocalOp.hBtnRight);    
		WM_DeleteWindow(m_WinLocalOp.hBtnInfo);     
		WM_DeleteWindow(m_WinLocalOp.hTextHeader);  
		WM_DeleteWindow(m_WinLocalOp.hTextInfo);    
		WM_DeleteWindow(m_WinLocalOp.hTextNum1);    
		WM_DeleteWindow(m_WinLocalOp.hTextNum2);    
		WM_DeleteWindow(m_WinLocalOp.hProgbar);     
		WM_DeleteWindow(m_WinLocalOp.hStateimage);  
		WM_DeleteWindow(m_WinLocalOp.hImage_test);  
		WM_DeleteWindow(m_WinLocalOp.hImage1);      
		WM_DeleteWindow(m_WinLocalOp.hImage_left);  
		WM_DeleteWindow(m_WinLocalOp.hImage_right); 
		WM_DeleteWindow(m_WinLocalOp.hImage_TEST);  
		WM_DeleteTimer(m_WinLocalOp.hTimer);
    WM_SetCallback(WM_HBKWIN,NULL);
	
    memset(&m_WinLocalOp, 0, sizeof(m_WinLocalOp));
}

void _WinLocalOpInterface(void *val)
{
    int sel = *(int *)val;

    if(sel == 100 )
    {
        return ;
    }
    else
    {
        TEXT_SetBkColor(m_WinLocalOp.hTextInfo,GUI_ORANGE);
        BUTTON_SetPressed(m_WinLocalOp.hBtnRtn,0);
    }
}


WIN_INFO_TYPE g_WinLocalOp = {
    &m_WinLocalOp.hFrame,
    _WinLocalOpCreate,
    _WinLocalOpDestroy,
};

void StrShowClear(void)
{
    unsigned char i;
    for(i=0;i<STRSHOWBUF_SIZE;i++) strShow[i] = '\0';
}

#if window_1 
typedef struct {
    GUI_HWIN hFrame;   
    GUI_HWIN hBtnHome;                  
    GUI_HWIN hText;                     
    GUI_HWIN hList;                     
    GUI_HWIN hImageBack;                
    GUI_HWIN hImage;                    
    GUI_HWIN hImage_CB_1;               
    GUI_HWIN hImage_CB_2;               
    GUI_HWIN 	hTimer;                   
    SCROLLBAR_Handle hScrollBar;        
}MAIN_MENU_TYPE;
static MAIN_MENU_TYPE m_MainMenu = {0};                        

void _WinMainMenuKeyDown(void )
{
    char curIndex=0;
    char curIndexDisable=0;
    curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
    if(BUTTON_IsPressed(m_MainMenu.hBtnHome))
    {
        BUTTON_SetPressed(m_MainMenu.hBtnHome,0);
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
					LISTBOX_SetSel(m_MainMenu.hList,-1);        
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

void _WinMainMenuKeyUp(void)
{
    char curIndex =0;
    char curIndexDisable =0;
    char curLen= LISTBOX_GetNumItems(m_MainMenu.hList);

    curIndex = curLen-1;
    curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
    if(BUTTON_IsPressed(m_MainMenu.hBtnHome))
    {
        BUTTON_SetPressed(m_MainMenu.hBtnHome,0);
        while(curIndexDisable)
        {
            if(curIndex>0)
            {
                curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_MainMenu.hList,curIndex);
            }
            else 	break;
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
					LISTBOX_SetSel(m_MainMenu.hList,-1);        
					return ;             
        }
        LISTBOX_SetSel(m_MainMenu.hList,curIndex);
    }
}

static void _WinMainMenuCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
	int     NCode =0;
	
    switch (pMsg->MsgId)
    {
			case WM_TIMER:
				WM_RestartTimer(pMsg->Data.v, 100);	
        break;
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


static int _GetItemSizeX2(WM_HWIN hWin, int ItemIndex) {
  char acBuffer[100];
  int  DistX;

  LISTBOX_GetItemText(hWin, ItemIndex, acBuffer, sizeof(acBuffer));
  DistX = GUI_GetStringDistX(acBuffer);
  return DistX;
}

static int _GetItemSizeY2(WM_HWIN hWin, int ItemIndex) {
  int DistY;

  DistY = GUI_GetFontDistY();
  if (LISTBOX_GetSel(hWin) == ItemIndex) {
    DistY = GUI_GetFontDistY()+ 4;
  }
  else DistY = GUI_GetFontDistY()+6;
  DistY = GUI_GetFontDistY()+ 6;
  return DistY;
}

static int SKIN_Main_Menu_Button_Home(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
   WM_HWIN hWin;
   int x0, y0;

   switch (pDrawItemInfo->Cmd)
   {
   case WIDGET_ITEM_CREATE:
   case WIDGET_ITEM_DRAW_BITMAP:
      break;
   default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   case WIDGET_ITEM_DRAW_BACKGROUND:
   	  GUI_SetBkColor(GUI_WHITE);
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED)
			{
         GUI_DrawBitmap(&bmhome_unsel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED)
			{
         GUI_DrawBitmap(&bmhome_sel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED)
			{
         GUI_DrawBitmap(&bmhome_unsel, 0, 0);
			}
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED)
			{
         GUI_DrawBitmap(&bmhome_unsel, 0, 0);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
   case WIDGET_ITEM_DRAW_TEXT:
      return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}
static void _WinMainMenuCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    char            *pBuffter   = g_LCDBuff;
    const char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";
    encoder.Set_Ready=0;
	ledstates.OPEN_remote=0;
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	hWin = WM_HBKWIN;

    m_MainMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_MainMenu.hImage_CB_1,&bmComBack_1);	
    m_MainMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_MainMenu.hImage_CB_2,&bmComBack_2);
    WIDGET_SetDefaultEffect_None();
	#if 1
    m_MainMenu.hBtnHome   = BUTTON_CreateEx(DEBUG_X_OFFSET+160-83-6-2-2,DEBUG_Y_OFFSET,166, 23,hWin,WM_CF_SHOW|WM_CF_HASTRANS,NULL,NULL);
    m_MainMenu.hText      = TEXT_CreateEx( DEBUG_X_OFFSET+35-6-2-2, DEBUG_Y_OFFSET+25, 250, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_MainMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+35-6-2-2, DEBUG_Y_OFFSET+23+25+10, 250,130, hWin, WM_CF_SHOW|WM_CF_HASTRANS, NULL, NULL,NULL);
	#endif
    hWin = m_MainMenu.hBtnHome;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmbackUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmhomeSel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmhomeUnsel,0,0);
    BUTTON_SetPressed(hWin,1);
    BUTTON_SetSkin(hWin, SKIN_Main_Menu_Button_Home);
	header_txt(DEBUG_X_OFFSET+35-6-2-2, DEBUG_Y_OFFSET+25,250,22);
    hWin = m_MainMenu.hText;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, (char *)strShow);

    hWin = m_MainMenu.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);		
    LISTBOX_SetItemSpacing(hWin, 7);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_DISABLED , GUI_BLACK);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SEL      , GUI_BLACK);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SELFOCUS , GUI_BLACK);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_UNSEL    , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_DISABLED , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SEL      , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SELFOCUS , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_UNSEL    , GUI_BLACK);
    LISTBOX_SetSel(hWin,-1);
    LISTBOX_SetAutoScrollV(hWin,0);	
    LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw4);

    for(i=0;i<MAIN_MENU_NUM;i++)
    {
    	memset(strShow,0,sizeof(strShow));
        if(LANGUAGE_CN == g_LanguageIndex) 
        {
            memcpy(strShow,menuMainCn[i],STRSHOWBUF_SIZE);
        }else 
        if(LANGUAGE_EN == g_LanguageIndex) 
        {
            memcpy(strShow,menuMainEn[i],STRSHOWBUF_SIZE);
        }
        LISTBOX_AddString(hWin, (char *)strShow);
        if(MENU_SETTING_TITLE == menuMainSettings[i]) 
            LISTBOX_SetItemDisabled(hWin,i,1);
    }		
    m_MainMenu.hTimer = WM_CreateTimer(WM_HBKWIN,0,100,0);
    WM_SetCallback(WM_HBKWIN, _WinMainMenuCallback);
}

static void _WinMainMenuDestroy(void *p)
{	
		WM_DeleteWindow(m_MainMenu.hBtnHome);             
		WM_DeleteWindow(m_MainMenu.hText);                
		WM_DeleteWindow(m_MainMenu.hList);                
		WM_DeleteWindow(m_MainMenu.hImageBack);           
		WM_DeleteWindow(m_MainMenu.hImage);               
		WM_DeleteWindow(m_MainMenu.hImage_CB_1);          
		WM_DeleteWindow(m_MainMenu.hImage_CB_2);          
		WM_DeleteTimer(m_MainMenu.hTimer);                
		WM_DeleteWindow(m_MainMenu.hScrollBar);           
	
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_MainMenu, 0, sizeof(m_MainMenu));
}

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

void _voidFun(void)
{
    return ;
}



WIN_INFO_TYPE g_WinMainMenu = {                        
    &m_MainMenu.hFrame,
    _WinMainMenuCreate,
    _WinMainMenuDestroy,
};

#endif





#if window_onlylist 
static int _GetItemSizeX_CommonList(WM_HWIN hWin, int ItemIndex) {
  char acBuffer[100];
  int  DistX;

  LISTBOX_GetItemText(hWin, ItemIndex, acBuffer, sizeof(acBuffer));
  DistX = GUI_GetStringDistX(acBuffer);
  return DistX;
}


static int _GetItemSizeY_CommonList(WM_HWIN hWin, int ItemIndex) {
  int DistY;
  DistY = GUI_GetFontDistY()+ 6;//6
  return DistY;
}


 void DrawGradientH_color(int x0, int y0, int x1, int y1,GUI_COLOR color1,GUI_COLOR color2)
{
  int x_mid = (x1-x0)/2+x0;
	GUI_DrawGradientH(x0,y0,x_mid,y0 ,GUI_WHITE,GUI_BLACK);
  GUI_DrawGradientH(x_mid+1,y0,x1,y0,GUI_BLACK,GUI_WHITE);
	
	GUI_DrawGradientH(x0,y1,x_mid,y1 ,GUI_WHITE,GUI_BLACK);
  GUI_DrawGradientH(x_mid+1,y1,x1,y1,GUI_BLACK,GUI_WHITE);
	
  GUI_DrawGradientH(x0,y0+1,x_mid,y1-1 ,color1,color2);
  GUI_DrawGradientH(x_mid+1,y0+1,x1,y1-1,color2,color1);
}
int _WinCommonMenuListOwnerDraw2(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN hWin;
  int     Index;

  hWin     = pDrawItemInfo->hWin;
  Index    = pDrawItemInfo->ItemIndex;
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    return _GetItemSizeX_CommonList(hWin, Index);
  case WIDGET_ITEM_GET_YSIZE:
    return _GetItemSizeY_CommonList(hWin, Index);
  case WIDGET_ITEM_DRAW:
#if 1
    {
      int   Sel;
      int   YSize;
      int   FontDistY;
      int   IsDisabled;
      int   IsSelected;
      int   ColorIndex;
      char  acBuffer[100];
	  int   FontDistX;
    GUI_RECT rFocus;
      IsDisabled = LISTBOX_GetItemDisabled(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex);
      IsSelected = LISTBOX_GetItemSel(hWin, Index);

      Sel        = LISTBOX_GetSel(hWin);
      YSize      = _GetItemSizeY_CommonList(hWin, Index);

      memset(acBuffer,0,100);
      GUI_SetBkColor(GUI_WHITE);
      GUI_SetColor  (GUI_WHITE);
      LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex, acBuffer, sizeof(acBuffer));
			GUI_Clear();
      if(pDrawItemInfo->ItemIndex == 0)
        {
          DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0, pDrawItemInfo->x0+180, pDrawItemInfo->y0);
	  	  DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+180, pDrawItemInfo->y0+25);
      	}
	  else
	  	{
	  	  DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+180, pDrawItemInfo->y0+25);
	  	}

      GUI_SetColor(GUI_ORANGE);

      
      rFocus.x0 = pDrawItemInfo->x0;
      rFocus.y0 = pDrawItemInfo->y0+1+2;
      rFocus.x1 = pDrawItemInfo->x0+180;
      rFocus.y1 = pDrawItemInfo->y0+25-1-2;
      if (pDrawItemInfo->ItemIndex == Sel)
      {
          GUI_AA_FillRoundedRectEx(&rFocus, 4);
      }

	  GUI_SetTextMode(GUI_TM_TRANS);
      FontDistY  = GUI_GetFontDistY();

	  GUI_SetColor(GUI_BLACK);
	  FontDistX = pDrawItemInfo->x0+1;

      GUI_DispStringAt(acBuffer, FontDistX , pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
    }
#endif // 0
    break;
  default:
    return LISTBOX_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}


typedef struct {
    GUI_HWIN hFrame;  
    GUI_HWIN hImage_CB_1;       
    GUI_HWIN hImage_CB_2;       
    GUI_HWIN hBtnRtn;           
    GUI_HWIN hBtnHome;          
    GUI_HWIN hText;             
    GUI_HWIN hList;             
    WM_HTIMER hTimer;           
    GUI_HWIN hImageBack;        
	
}COMMON_MENU_TYPE;
static COMMON_MENU_TYPE m_CommonMenu = {0};                       
void _WinCommonMenuKeyDown(void )
{
    char curIndex=0;
    char curIndexDisable=0;

    curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
    if(BUTTON_IsPressed(m_CommonMenu.hBtnRtn))
    {
        BUTTON_SetPressed(m_CommonMenu.hBtnRtn,0);
        BUTTON_SetPressed(m_CommonMenu.hBtnHome,1);
    }
    else if(BUTTON_IsPressed(m_CommonMenu.hBtnHome))
    {
        BUTTON_SetPressed(m_CommonMenu.hBtnHome,0);
        if(LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex))
        {
            LISTBOX_SetItemDisabled(m_CommonMenu.hList,curIndex,0);
            LISTBOX_SetSel(m_CommonMenu.hList,curIndex);
            LISTBOX_SetItemDisabled(m_CommonMenu.hList,curIndex,1);
        }
        LISTBOX_SetBkColor(m_CommonMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        while(curIndexDisable) 
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
        if(curIndex == (LISTBOX_GetNumItems(m_CommonMenu.hList)-1) ) 
        {
            BUTTON_SetPressed(m_CommonMenu.hBtnRtn,1);
						LISTBOX_SetSel(m_CommonMenu.hList,-1);
				}
        else
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
            while(curIndexDisable)
            {
                if(curIndex == (LISTBOX_GetNumItems(m_CommonMenu.hList)-1) ) 
                {
                    BUTTON_SetPressed(m_CommonMenu.hBtnRtn,1);
                    LISTBOX_SetSel(m_CommonMenu.hList,-1);
									return ;
                }
                curIndex++;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
            }
            LISTBOX_SetSel(m_CommonMenu.hList,curIndex);
        }
    }
}

void _WinCommonMenuKeyUp(void)
{
    char curIndex =0;
    char curIndexDisable =0;
    char curLen= LISTBOX_GetNumItems(m_CommonMenu.hList);

    curIndex = curLen-1;
    curIndexDisable = LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex);
    if(BUTTON_IsPressed(m_CommonMenu.hBtnRtn))
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
    else if(BUTTON_IsPressed(m_CommonMenu.hBtnHome))
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
						LISTBOX_SetSel(m_CommonMenu.hList,-1);
			return ;
				}
        LISTBOX_SetSel(m_CommonMenu.hList,curIndex);
    }
}

void _WinCommonMenuKeyEnter(void)
{
    int id = 0;
    int i=0;
    int j=0;
    if(BUTTON_IsPressed(m_CommonMenu.hBtnRtn))
    {
        WIN_Exit(0);
    }
    else if(BUTTON_IsPressed(m_CommonMenu.hBtnHome))
    {
        WIN_Home();
    }
    else
    {
        if(dataStructInterface.Frame_SN == 11)  //针对参数菜单单独处理
        {
            
            id = LISTBOX_GetSel(m_CommonMenu.hList);  //菜单中第id个项目（id包含未使能的项目）
            WIN_Enter(&id);
        }
        else
        {
            while(i<LISTBOX_GetNumItems(m_CommonMenu.hList))  //菜单中第j个使能的项目（j不包含未使能的项目）
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
}

int kkk;
extern 	float B_b;
void _WinCommonMenuRefresh()
{
		char str[MAX_INFO_CHAR];
	if(dataStructInterface.Frame_SN==5)       //ABCDE
	{
			sprintf(str,"模拟量输入AI1     %.1f mA ",ai_o420.AI_0420_UI);//,ai_o420.AI_0420		            
//		sprintf(str,"模拟量输入AI1   %d.%d mA ",(int)((ai_o420.AI_0420_UI*10)/10),(int)((int)(ai_o420.AI_0420_UI*10)%10));//,ai_o420.AI_0420
			strcpy(menuObAnalogCn[0],str);
			strcpy(menuObAnalogEn[0],str);
			sprintf(str,"模拟量输出AO1     %.1f mA ",ai_o420.AO_0420_UI);	           
	//	sprintf(str,"模拟量输出AO1   %d.%d mA ",(int)((int)(ai_o420.AO_0420_UI*10)/10),(int)((int)(ai_o420.AO_0420_UI*10)%10));
			strcpy(menuObAnalogCn[1],str);
			strcpy(menuObAnalogEn[1],str);
	}else
	if(dataStructInterface.Frame_SN==8)       //ABCDE
	{
		if(ai_o420.AI_0420_UI_old!=ai_o420.AI_0420_UI)
		{
			ai_o420.AI_0420_UI_old=ai_o420.AI_0420_UI;
			sprintf(str,"模拟量输入AI1     %.1f mA ",ai_o420.AI_0420_UI);//,ai_o420.AI_0420
			            
			//sprintf(str,"模拟量输入AI1   %d.%d mA ",(int)((ai_o420.AI_0420_UI*10)/10),(int)((int)(ai_o420.AI_0420_UI*10)%10));//,ai_o420.AI_0420
		strcpy(menuObAnalogCn[0],str);
			strcpy(menuObAnalogEn[0],str);
			LISTBOX_SetString(m_CommonMenu.hList,str,0);
		}
		if(ai_o420.AO_0420_UI_old!=ai_o420.AO_0420_UI)
		{
			ai_o420.AO_0420_UI_old=ai_o420.AO_0420_UI;
			sprintf(str,"模拟量输出AO1     %.1f mA ",ai_o420.AO_0420_UI);			            
			//sprintf(str,"模拟量输出AO1   %d.%d mA ",(int)((int)(ai_o420.AO_0420_UI*10)/10),(int)((int)(ai_o420.AO_0420_UI*10)%10));
			strcpy(menuObAnalogCn[1],str);
			strcpy(menuObAnalogEn[1],str);
			LISTBOX_SetString(m_CommonMenu.hList,str,1);
		}
	}else
	if(dataStructInterface.Frame_SN==1)
	{
		
	}else
	if(dataStructInterface.Frame_SN==16)
	{
		
	}else
	if(dataStructInterface.Frame_SN==12)
	{
		if(dataStructInterface.gearType_old!=dataStructInterface.gearType)
		{
			dataStructInterface.gearType_old=dataStructInterface.gearType;
		switch(dataStructInterface.gearType)
		{
			case 0:		sprintf(str," No additional gear      ");
								strcpy(menuGearCn[1],str);
								strcpy(menuGearEn[1],str);
								break;
			case 1:		sprintf(str," Rotary gear             ");
								strcpy(menuGearCn[1],str);
								strcpy(menuGearEn[1],str);
								break;
			case 2:		sprintf(str," Part turn               ");
								strcpy(menuGearCn[1],str);
								strcpy(menuGearEn[1],str);
								break;
			case 3:		sprintf(str," Linear                  ");
								strcpy(menuGearCn[1],str);
								strcpy(menuGearEn[1],str);
								break;
			default : break;
		}
		LISTBOX_SetString(m_CommonMenu.hList,str,1);
	}
	}else
	if(dataStructInterface.Frame_SN==14)
	{
		#if 1

		strcpy(menuKrOutputCn[1],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[1]]);
        strcpy(menuKrOutputEn[1],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[1]]);
		strcpy(menuKrOutputCn[2],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[1]]);
        strcpy(menuKrOutputEn[2],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[1]]);
		strcpy(menuKrOutputCn[4],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[2]]);
        strcpy(menuKrOutputEn[4],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[2]]);
		strcpy(menuKrOutputCn[5],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[2]]);
        strcpy(menuKrOutputEn[5],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[2]]);
		strcpy(menuKrOutputCn[7],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[3]]);
        strcpy(menuKrOutputEn[7],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[3]]);
		strcpy(menuKrOutputCn[8],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[3]]);
        strcpy(menuKrOutputEn[8],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[3]]);
		strcpy(menuKrOutputCn[10],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[4]]);
        strcpy(menuKrOutputEn[10],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[4]]);
		strcpy(menuKrOutputCn[11],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[4]]);
        strcpy(menuKrOutputEn[11],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[4]]);
		strcpy(menuKrOutputCn[13],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[5]]);
        strcpy(menuKrOutputEn[13],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[5]]);
		strcpy(menuKrOutputCn[14],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[5]]);
        strcpy(menuKrOutputEn[14],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[5]]);
		strcpy(menuKrOutputCn[16],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[6]]);
        strcpy(menuKrOutputEn[16],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[6]]);
		strcpy(menuKrOutputCn[17],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[6]]);
        strcpy(menuKrOutputEn[17],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[6]]);
		strcpy(menuKrOutputCn[19],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[7]]);
        strcpy(menuKrOutputEn[19],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[7]]);
		strcpy(menuKrOutputCn[20],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[7]]);
        strcpy(menuKrOutputEn[20],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[7]]);
		strcpy(menuKrOutputCn[22],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[8]]);
        strcpy(menuKrOutputEn[22],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[8]]);
		strcpy(menuKrOutputCn[23],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[8]]);
        strcpy(menuKrOutputEn[23],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[8]]);
		#endif
		if(flag_figures.KEYMod==1)
		{
			strcpy(menuObKrInputCn[0],menuObKrInputCn_H1[0]);
		}else
		{
			strcpy(menuObKrInputCn[0],menuObKrInputCn_L1[0]);
		}
		if(flag_figures.KEYClose==1)
		{
			strcpy(menuObKrInputCn[1],menuObKrInputCn_H1[1]);
		}else
		{
			strcpy(menuObKrInputCn[1],menuObKrInputCn_L1[1]);
		}
		
		if(flag_figures.KEYOpen==1)
		{
			strcpy(menuObKrInputCn[2],menuObKrInputCn_H1[2]);
		}else
		{
			strcpy(menuObKrInputCn[2],menuObKrInputCn_L1[2]);
		}
		
		if(flag_figures.KEYStop==1)
		{
			strcpy(menuObKrInputCn[3],menuObKrInputCn_H1[3]);
		}else
		{
			strcpy(menuObKrInputCn[3],menuObKrInputCn_L1[3]);
		}
		
		if(flag_figures.KEYEme==1)
		{
			strcpy(menuObKrInputCn[4],menuObKrInputCn_H1[4]);
		}else
		{
			strcpy(menuObKrInputCn[4],menuObKrInputCn_L1[4]);
		}
		
	}else
    if (dataStructInterface.Frame_SN==9)
    {	
        if(states.Coils_temp_old!=states.Coils_temp)
        {
            states.Coils_temp_old=states.Coils_temp;
				            
		    sprintf(str,"                     %d ",states.Coils_temp);
            strcpy(menuObStatusCn[6],str);
            strcpy(menuObStatusEn[6],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,6);
        }
        if(states.Ele_temp_old!=states.Ele_temp)
        {
            states.Ele_temp_old=states.Ele_temp;
				            
            sprintf(str,"                     %d ",states.Ele_temp);
            strcpy(menuObStatusCn[8],str);
            strcpy(menuObStatusEn[8],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,8);
        }
        if(powerboard.lcd_current_old!=powerboard.lcd_current)
        {
            powerboard.lcd_current_old=powerboard.lcd_current;
				          
            sprintf(str,"                  %.1f A ",powerboard.lcd_current);
            strcpy(menuObStatusCn[17],str);
            strcpy(menuObStatusEn[17],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,17);
        }
        if(powerboard.lcd_voltage_old!=powerboard.lcd_voltage)
        {
            powerboard.lcd_voltage_old=powerboard.lcd_voltage;
				           
            sprintf(str,"                    %d V ",(int)powerboard.lcd_voltage);
            strcpy(menuObStatusCn[19],str);
            strcpy(menuObStatusEn[19],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,19);
        }
    }else
	if (dataStructInterface.Frame_SN==10)   //ABCDE
	{
		if(diagnose.switch_num_old!=diagnose.switch_num)
		{
			diagnose.switch_num_old=diagnose.switch_num;
			              
            sprintf(str," 开关次数              %d ",diagnose.switch_num);
            strcpy(menuDiagnoseCn[1],str);
            strcpy(menuDiagnoseEn[1],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,1);
		}
		if(diagnose.switch_num_old!=diagnose.switch_num)
		{
			diagnose.switch_num_old=diagnose.switch_num;
			              
            sprintf(str," 开关频率(次/小时)     %d",1);
            strcpy(menuDiagnoseCn[2],str);
            strcpy(menuDiagnoseEn[2],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,2);
		}
		if(diagnose.switch_num_old!=diagnose.switch_num)
		{
			diagnose.switch_num_old=diagnose.switch_num;
			             
            sprintf(str," 力矩关断次数          %d",2);
            strcpy(menuDiagnoseCn[3],str);
            strcpy(menuDiagnoseEn[3],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,3);
		}
		if(diagnose.switch_num_old!=diagnose.switch_num)
		{
			diagnose.switch_num_old=diagnose.switch_num;
			             
            sprintf(str," 行程关断次数          %d",3);
            strcpy(menuDiagnoseCn[4],str);
            strcpy(menuDiagnoseEn[4],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,4);
		}
		if(diagnose.switch_num_old!=diagnose.switch_num)
		{
			diagnose.switch_num_old=diagnose.switch_num;
			              
            sprintf(str," 电机运行小时数        %d",timer.run_coils_h);
            strcpy(menuDiagnoseCn[5],str);
            strcpy(menuDiagnoseEn[5],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,5);
		}
		if(diagnose.switch_num_old!=diagnose.switch_num)
		{
			diagnose.switch_num_old=diagnose.switch_num;
			              
            sprintf(str," 电子单元运行小时数    %d",timer.run_h);
            strcpy(menuDiagnoseCn[6],str);
            strcpy(menuDiagnoseEn[6],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,6);
		}
		if(diagnose.switch_num_old!=diagnose.switch_num)
		{
			diagnose.switch_num_old=diagnose.switch_num;
			              
            sprintf(str," 运行时间/小时         %d",6);
            strcpy(menuDiagnoseCn[7],str);
            strcpy(menuDiagnoseEn[7],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,7);
		}
		if(diagnose.switch_num_old!=diagnose.switch_num)
		{
			diagnose.switch_num_old=diagnose.switch_num;
			             
            sprintf(str," 开关次数              %d",7);
            strcpy(menuDiagnoseCn[9],str);
            strcpy(menuDiagnoseEn[9],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,9);
		}
		if(diagnose.switch_num_old!=diagnose.switch_num)
		{
			diagnose.switch_num_old=diagnose.switch_num;
			              
            sprintf(str," 力矩关断次数         %d ",8);
            strcpy(menuDiagnoseCn[10],str);
            strcpy(menuDiagnoseEn[10],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,10);
		}
		if(diagnose.switch_num_old!=diagnose.switch_num)
		{
			diagnose.switch_num_old=diagnose.switch_num;
			              
            sprintf(str," 电机运行小时数        %d",timer.run_s);
            strcpy(menuDiagnoseCn[11],str);
            strcpy(menuDiagnoseEn[11],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,11);
		}
		if(diagnose.switch_num_old!=diagnose.switch_num)
		{
			diagnose.switch_num_old=diagnose.switch_num;
			             
            sprintf(str,"                     需要");
            strcpy(menuDiagnoseCn[13],str);
            strcpy(menuDiagnoseEn[13],str);
            LISTBOX_SetString(m_CommonMenu.hList,str,13);
		}
	}
	if(dataStructInterface.Frame_SN==13)
	{
	
	}
	if(dataStructInterface.Frame_SN==25)
	{
        encoder.dufangxiang=1;
		encoder.dufangxianng_flag=0;
	}
}


static void _WinCommonMenuCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
    char str[MAX_INFO_CHAR];
    
    switch (pMsg->MsgId)
    {
        #if 1
        case WM_TIMER:
				WM_RestartTimer(pMsg->Data.v, 100);
                _WinCommonMenuRefresh();	
                break;
        #endif
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

extern int _WinCommonMenuListOwnerDraw6(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
static void _WinCommonMenuCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);
    WM_HTIMER hTimer;
    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    char            *pBuffter   = g_LCDBuff;
    const char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    const char      *pContentCn = pMenu->data->menutitleCn;
    const char      *pContentEn = pMenu->data->menutitleEn;
    if (NULL == pTitle) pTitle = "";

    states.Coils_temp_old=states.Coils_temp;
    states.Ele_temp_old=states.Ele_temp;
    powerboard.lcd_current_old=powerboard.lcd_current;
    powerboard.lcd_voltage_old=powerboard.lcd_voltage;
    dataStructInterface.gearType_old=dataStructInterface.gearType;
    eeprom.flag_IO_O=1;
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	
    dataStructInterface.Frame_SN=pMenu->data->SN;
    _InterDataRefresh();
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_CommonMenu.hFrame, 0);             
    hWin = WM_GetFirstChild(m_CommonMenu.hFrame); 
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	#if 1       
		m_CommonMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
		IMAGE_SetBitmap(m_CommonMenu.hImage_CB_1,&bmComBack_1);
	
		m_CommonMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
		IMAGE_SetBitmap(m_CommonMenu.hImage_CB_2,&bmComBack_2);
    #endif
		
    #if 1
    m_CommonMenu.hBtnRtn   = BUTTON_CreateEx(DEBUG_X_OFFSET+160-83-3-2-5+1, DEBUG_Y_OFFSET, 83, 23,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    m_CommonMenu.hBtnHome  = BUTTON_CreateEx(DEBUG_X_OFFSET+160-3-2-5+1   , DEBUG_Y_OFFSET, 83, 23,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    m_CommonMenu.hText     = TEXT_CreateEx( DEBUG_X_OFFSET+35-3-2-5+1, DEBUG_Y_OFFSET+23+2, 250, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CommonMenu.hList     = LISTBOX_CreateEx( DEBUG_X_OFFSET+35-3-2+1, DEBUG_Y_OFFSET+23+23+10, 250-10, 160, hWin, WM_CF_SHOW|WM_CF_HASTRANS, NULL, NULL,NULL);
    hWin = m_CommonMenu.hBtnRtn;  //设置返回键基本属性
    BUTTON_SetSkin(hWin,SKIN_Left_Button_Return);
    BUTTON_SetPressed(hWin,1);
    hWin = m_CommonMenu.hBtnHome; //设置HOME键基本属性
    BUTTON_SetSkin(hWin,SKIN_Right_Button_Home);
    BUTTON_SetPressed(hWin,0);
    #endif
    
    header_txt(DEBUG_X_OFFSET+35-3-2-5+1, DEBUG_Y_OFFSET+23+2, 250, 23);
    hWin = m_CommonMenu.hText;  //设置文本框基本属性
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
	
    #if 1
    _WinMomentCloseRefesh();
    _WinMomentOpenRefresh();
    _WinMomentCloseRefesh ();
    _WinMomentOpenRefresh ();
    _WinEndPosCloseRefresh();
    _WinEndPosOpenRefresh ();
    _WinOverMomentTimesRefresh();
    _WinSpeedCloseRefresh();
    _WinSpeedOpenRefresh ();
    _WinEmgSpeedCloseRefresh();
    __WinEmgSpeedOpenRefresh();
    _WinEmergencyPosKeyRefresh();		
		
    hWin = m_CommonMenu.hList;  //设置列表框基本属性
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 7);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_DISABLED , GUI_TRANSPARENT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SEL      , GUI_TRANSPARENT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SELFOCUS , GUI_TRANSPARENT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_UNSEL    , GUI_TRANSPARENT);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_DISABLED , GUI_BLUE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SEL      , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SELFOCUS , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_UNSEL    , GUI_BLACK);
    LISTBOX_SetSel(hWin,-1);
    LISTBOX_SetAutoScrollV(hWin,0);
    if(dataStructInterface.Frame_SN==11)
    {
        LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw6);
    }else
    {
		LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw50);
    }
    #endif
    
    dataStructInterface.menunum=pMenu->data->menunum;
    if(dataStructInterface.Frame_SN==28)
    {
        dataStructInterface.menunum=flag_figures.user;
    }
    
    for(i=0;i<dataStructInterface.menunum;i++)
    {
        memset(strShow,0,sizeof(strShow));
        if(LANGUAGE_CN == g_LanguageIndex) 
            enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) 
            enc_unicode_to_utf8_str(pContentEn,strShow,STRSHOWBUF_SIZE);
        pContentCn += MAX_INFO_CHAR;
        pContentEn += MAX_INFO_CHAR;
        LISTBOX_AddString(hWin, (char *)strShow);
        if(MENU_SETTING_TITLE == pMenu->data->menuattri[i])  //若属性为0，则置为灰色
            LISTBOX_SetItemDisabled(hWin,i,1);
				
    }
    m_CommonMenu.hTimer = WM_CreateTimer(WM_HBKWIN,0,1000,0);

    WM_SetCallback(WM_HBKWIN, _WinCommonMenuCallback);
		
}

static void _WinCommonMenuDestroy(void *p)
{
    WM_DeleteWindow(m_CommonMenu.hImage_CB_1);     
    WM_DeleteWindow(m_CommonMenu.hImage_CB_2);     
    WM_DeleteWindow(m_CommonMenu.hBtnRtn);         
    WM_DeleteWindow(m_CommonMenu.hBtnHome);        
    WM_DeleteWindow(m_CommonMenu.hText);           
    WM_DeleteWindow(m_CommonMenu.hList);           
    WM_DeleteTimer(m_CommonMenu.hTimer);           
    WM_DeleteWindow(m_CommonMenu.hImageBack);      
	
    WM_SetCallback(WM_HBKWIN, NULL);
	
    memset(&m_CommonMenu, 0, sizeof(m_CommonMenu));
}

void _WinCommonMenuInterface(void *val)
{
    int sel = *(int *)val;
    int i=0;
    int j=0;

    if(sel == 100 ) 
    {
        return ;
    }
    else             
    {
        if (m_CommonMenu.hList == 0) return;

        if ((sel < (int)LISTBOX_GetNumItems(m_CommonMenu.hList)) && (sel >= 0))
        {
            BUTTON_SetPressed(m_CommonMenu.hBtnHome,0);
            BUTTON_SetPressed(m_CommonMenu.hBtnRtn,0);
            
            if(dataStructInterface.Frame_SN == 11)  //针对参数菜单特殊处理
            {
                LISTBOX_SetBkColor(m_CommonMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
                LISTBOX_SetSel(m_CommonMenu.hList, sel);
            }
            else
            {
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
}


WIN_INFO_TYPE g_WinCommonMenu = {                      
    &m_CommonMenu.hFrame,
    _WinCommonMenuCreate,
    _WinCommonMenuDestroy
};
#endif


typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hText;
    GUI_HWIN hList;
    GUI_HWIN hChkBox[AUTHRITY_NUM];
}CUR_USER_MENU_TYPE;
static CUR_USER_MENU_TYPE m_CurUserMenu = {0};                        
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
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

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
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
    m_CurUserMenu.hFrame = FRAMEWIN_CreateAsChild(0, 0, LCD_HSIZE+3, LCD_VSIZE+3 ,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);
		FRAMEWIN_SetClientColor(m_CurUserMenu.hFrame,GUI_WHITE);
    FRAMEWIN_SetFont(m_CurUserMenu.hFrame, &GUI_Fontsong16all);  
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_CurUserMenu.hFrame, 0);            
    hWin = WM_GetFirstChild(m_CurUserMenu.hFrame);            
    m_CurUserMenu.hText      = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CurUserMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23+10, PER_CM_OFFSET*4.5, PER_CM_OFFSET*4, hWin, WM_CF_SHOW, NULL, NULL,NULL);
   header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_CurUserMenu.hText;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
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
    hWin = WM_GetFirstChild(m_CurUserMenu.hFrame);            
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

void _WinCurUserInterface(void *val)
{
}


WIN_INFO_TYPE g_WinCurUserMenu = {                        
    &m_CurUserMenu.hFrame,
    _WinCurUserCreate,
    _WinCurUserDestroy
};


typedef struct {
    GUI_HWIN  hFrame;
		GUI_HWIN hImage_CB_1;                        
		GUI_HWIN hImage_CB_2;                        
		GUI_HWIN  hText;                             
		GUI_HWIN  hList;                             
		GUI_HWIN  hImageBack;                        
		GUI_HWIN  hChkBox[MAX_ITEAM_PER_PAGE];       
}COMMON_SELECT_MENU_TYPE;
static COMMON_SELECT_MENU_TYPE m_CommonSelectMenu = {0};                        

MENU_INFO_ITEM  *pWinCommonSelecMenu;
#if 1
void _WinCommonSelectRefresh_save(unsigned char selet)
{
	if(dataStructInterface.Select_SN==2)
	{
		eeprom.closeDir_save=selet;
		eeprom.flag_closeDir=1;
        encoder.set_end_ok=0;
	}
	if(dataStructInterface.Select_SN==5)
	{
		eeprom.ctrlMode_save=selet;
		eeprom.flag_ctrlMode=1;
	}
	if(dataStructInterface.Select_SN==11)
	{
		ext_IO.eep_TEST_of1=selet;
		ext_IO.eep_save_out1=1;
	}
	if(dataStructInterface.Select_SN==12)
	{
		ext_IO.eep_TEST2_of1=selet;
		ext_IO.eep_save_of1=1;
	}
	if(dataStructInterface.Select_SN==13)
	{
		ext_IO.eep_TEST_of2=selet;
		ext_IO.eep_save_out2=1;
	}
	if(dataStructInterface.Select_SN==14)
	{
		ext_IO.eep_TEST2_of2=selet;
		ext_IO.eep_save_of2=1;
	}
	if(dataStructInterface.Select_SN==15)
	{
		ext_IO.eep_TEST_of3=selet;
		ext_IO.eep_save_out3=1;
	}
	if(dataStructInterface.Select_SN==16)
	{
		ext_IO.eep_TEST2_of3=selet;
		ext_IO.eep_save_of3=1;
	}
	if(dataStructInterface.Select_SN==17)
	{
		ext_IO.eep_TEST_of4=selet;
		ext_IO.eep_save_out4=1;
	}
	if(dataStructInterface.Select_SN==18)
	{
		ext_IO.eep_TEST2_of4=selet;
		ext_IO.eep_save_of4=1;
	}
	if(dataStructInterface.Select_SN==19)
	{
		ext_IO.eep_TEST_of5=selet;
		ext_IO.eep_save_out5=1;
	}
	if(dataStructInterface.Select_SN==20)
	{
		ext_IO.eep_TEST2_of5=selet;
		ext_IO.eep_save_of5=1;
	}
	if(dataStructInterface.Select_SN==21)
	{
		ext_IO.eep_TEST_of6=selet;
		ext_IO.eep_save_out6=1;
	}
	if(dataStructInterface.Select_SN==22)
	{
		ext_IO.eep_TEST2_of6=selet;
		ext_IO.eep_save_of6=1;
	}
	if(dataStructInterface.Select_SN==23)
	{
		ext_IO.eep_TEST_of7=selet;
		ext_IO.eep_save_out7=1;
	}
	if(dataStructInterface.Select_SN==24)
	{
		ext_IO.eep_TEST2_of7=selet;
		ext_IO.eep_save_of7=1;
	}
	if(dataStructInterface.Select_SN==25)
	{
		ext_IO.eep_TEST_of8=selet;
		ext_IO.eep_save_out8=1;
	}
	if(dataStructInterface.Select_SN==26)
	{
		ext_IO.eep_TEST2_of8=selet;
		ext_IO.eep_save_of8=1;
	}
}
void _WinCommonSelctRefresh()
{
	char str[MAX_INFO_CHAR];	
	if(dataStructInterface.Select_SN==2)
	{
			if(0 == dataStructInterface.closeDir)
			{
					sprintf(str,"                  顺时针 ");
					strcpy(menuVavleParaCn[1],str);
					strcpy(menuVavleParaEn[1],str);
					strcpy(menu1EndPosParaCn[1],str);
					strcpy(menu1EndPosParaEn[1],str);
			}
			else if(1 == dataStructInterface.closeDir)
			{               
					sprintf(str,"                  逆时针 ");
					strcpy(menuVavleParaCn[1],str);
					strcpy(menuVavleParaEn[1],str);
					strcpy(menu1EndPosParaCn[1],str);
					strcpy(menu1EndPosParaEn[1],str);
			}
	}else
	if(dataStructInterface.Select_SN==3)
	{
	  if(0 == dataStructInterface.closeOffMode)
    {
        sprintf(str,"            行程关断模式 ");
        strcpy(menuVavleParaCn[6],str);
        strcpy(menuVavleParaEn[6],str);
			strcpy(menu2EndPosParaCn[1],str);
        strcpy(menu2EndPosParaEn[1],str);
    }
    else if(1 == dataStructInterface.closeOffMode)
    {               
        sprintf(str,"            力矩关断模式 ");
        strcpy(menuVavleParaCn[6],str);
        strcpy(menuVavleParaEn[6],str);
			strcpy(menu2EndPosParaCn[1],str);
        strcpy(menu2EndPosParaEn[1],str);
    }
	}else
	if(dataStructInterface.Select_SN==4)
	{
		 if(0 == dataStructInterface.openOffMode)
    {               
        sprintf(str,"            行程关断模式 ");
        strcpy(menuVavleParaCn[7],str);
        strcpy(menuVavleParaEn[7],str);
			strcpy(menu2EndPosParaCn[2],str);
        strcpy(menu2EndPosParaEn[2],str);
    }
    else if(1 == dataStructInterface.openOffMode)
    {
        sprintf(str,"            力矩关断模式 ");
        strcpy(menuVavleParaCn[7],str);
        strcpy(menuVavleParaEn[7],str);
			strcpy(menu2EndPosParaCn[2],str);
        strcpy(menu2EndPosParaEn[2],str);
    }
	}
	if(dataStructInterface.Select_SN==11)
	{
		
		strcpy(menuKrOutputCn[1],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[1]]);
    strcpy(menuKrOutputEn[1],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[1]]);
	}
	if(dataStructInterface.Select_SN==12)
	{
		strcpy(menuKrOutputCn[2],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[1]]);
    strcpy(menuKrOutputEn[2],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[1]]);
	}
	if(dataStructInterface.Select_SN==13)
	{
		strcpy(menuKrOutputCn[4],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[2]]);
    strcpy(menuKrOutputEn[4],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[2]]);
	}
	if(dataStructInterface.Select_SN==14)
	{
		strcpy(menuKrOutputCn[5],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[2]]);
    strcpy(menuKrOutputEn[5],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[2]]);
	}
	if(dataStructInterface.Select_SN==15)
	{
		strcpy(menuKrOutputCn[7],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[3]]);
    strcpy(menuKrOutputEn[7],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[3]]);
	}
	if(dataStructInterface.Select_SN==16)
	{
		strcpy(menuKrOutputCn[8],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[3]]);
    strcpy(menuKrOutputEn[8],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[3]]);
	}
	if(dataStructInterface.Select_SN==17)
	{
		strcpy(menuKrOutputCn[10],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[4]]);
    strcpy(menuKrOutputEn[10],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[4]]);
	}
	if(dataStructInterface.Select_SN==18)
	{
		strcpy(menuKrOutputCn[11],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[4]]);
    strcpy(menuKrOutputEn[11],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[4]]);
	}
	if(dataStructInterface.Select_SN==19)
	{
		strcpy(menuKrOutputCn[13],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[5]]);
    strcpy(menuKrOutputEn[13],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[5]]);
	}
	if(dataStructInterface.Select_SN==20)
	{
		strcpy(menuKrOutputCn[14],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[5]]);
    strcpy(menuKrOutputEn[14],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[5]]);
	}
	if(dataStructInterface.Select_SN==21)
	{
		strcpy(menuKrOutputCn[16],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[6]]);
    strcpy(menuKrOutputEn[16],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[6]]);
	}
	if(dataStructInterface.Select_SN==22)
	{
		strcpy(menuKrOutputCn[17],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[6]]);
    strcpy(menuKrOutputEn[17],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[6]]);
	}
	if(dataStructInterface.Select_SN==23)
	{
		strcpy(menuKrOutputCn[19],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[7]]);
    strcpy(menuKrOutputEn[19],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[7]]);
	}
	if(dataStructInterface.Select_SN==24)
	{

		strcpy(menuKrOutputCn[20],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[7]]);
    strcpy(menuKrOutputEn[20],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[7]]);
	}
	if(dataStructInterface.Select_SN==25)
	{
		strcpy(menuKrOutputCn[22],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[8]]);
    strcpy(menuKrOutputEn[22],menuKrOutputSel1Cn_1[dataStructInterface.krOutputSel1[8]]);
	}
	if(dataStructInterface.Select_SN==26)
	{

		strcpy(menuKrOutputCn[23],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[8]]);
    strcpy(menuKrOutputEn[23],menuKrOutputSel2Cn_1[dataStructInterface.krOutputSel2[8]]);
	}


}
#endif	
static void _WinCommonSelectRefresh(void)
{
	char str[MAX_INFO_CHAR];
  	if(dataStructInterface.Select_SN==1)
	{
		switch(dataStructInterface.gearType)
		{
			case 0:		
                sprintf(str," No additional gear      ");
				strcpy(menuGearCn[1],str);
				strcpy(menuGearEn[1],str);
				break;
			case 1:
                sprintf(str," Rotary gear             ");
				strcpy(menuGearCn[1],str);
				strcpy(menuGearEn[1],str);
				break;
			case 2:
                sprintf(str," Part turn               ");
				strcpy(menuGearCn[1],str);
				strcpy(menuGearEn[1],str);
				break;
			case 3:
                sprintf(str," Linear                  ");
				strcpy(menuGearCn[1],str);
				strcpy(menuGearEn[1],str);
				break;
			default:
                break;
		}
	}else
	if(dataStructInterface.Select_SN==2)
	{
		eeprom.flag_closeDir=1;
		encoder.set_end_ok=0;
	}else
	if(dataStructInterface.Select_SN==5)
	{
        if(dataStructInterface.ctrlMode == 0 )
		{
			ai_o420.flag_mode1=1;
			ai_o420.flag_mode2=0;
			ai_o420.flag_mode3=0;
			ai_o420.flag_mode4=0;
			            
			sprintf(str,"      开关量持续节点控制 ");
			strcpy(menuCtrlSysParaCn[1],str);
			strcpy(menuCtrlSysParaEn[1],str);
		}
		else if(dataStructInterface.ctrlMode == 1 )
		{
			ai_o420.flag_mode1=0;
			ai_o420.flag_mode2=1;
			ai_o420.flag_mode3=0;
			ai_o420.flag_mode4=0;
			            
			sprintf(str,"      开关量脉冲节点控制 ");
			strcpy(menuCtrlSysParaCn[1],str);
			strcpy(menuCtrlSysParaEn[1],str);
		}
		else if(dataStructInterface.ctrlMode == 2 )
		{
			ai_o420.flag_mode1=0;
			ai_o420.flag_mode2=0;
			ai_o420.flag_mode3=1;
			ai_o420.flag_mode4=0;
			            
			sprintf(str,"          开关量比例控制 ");
			strcpy(menuCtrlSysParaCn[1],str);
			strcpy(menuCtrlSysParaEn[1],str);
		}
		else if(dataStructInterface.ctrlMode == 3 )
		{
			ai_o420.flag_mode1=0;
			ai_o420.flag_mode2=0;
			ai_o420.flag_mode3=0;
			ai_o420.flag_mode4=1;
			            
			sprintf(str,"       模拟量位置控制AI1 ");
			strcpy(menuCtrlSysParaCn[1],str);
			strcpy(menuCtrlSysParaEn[1],str);
		}
		eeprom.flag_ctrlMode=1;
	}else
	if(dataStructInterface.Select_SN==6)
	{
		if(dataStructInterface.rmtChoose == 0 )
        {              
            sprintf(str,"                    无效 ");
            strcpy(menuCtrlSysParaCn[3],str);
            strcpy(menuCtrlSysParaEn[3],str);
        }
        else if(dataStructInterface.rmtChoose == 1 )
        {         
            sprintf(str,"      开关量持续节点控制 ");
            strcpy(menuCtrlSysParaCn[3],str);
            strcpy(menuCtrlSysParaEn[3],str);
        }
        else if(dataStructInterface.rmtChoose == 2 )
        {              
            sprintf(str,"          开关量比例控制 ");
            strcpy(menuCtrlSysParaCn[3],str);
            strcpy(menuCtrlSysParaEn[3],str);
        }
        else if(dataStructInterface.rmtChoose == 3 )
        {
            sprintf(str,"       模拟量位置控制AI1 ");
            strcpy(menuCtrlSysParaCn[3],str);
            strcpy(menuCtrlSysParaEn[3],str);
        }
		eeprom.rmtChoose=dataStructInterface.rmtChoose;
		eeprom.flag_rmtChoose=1;
	}else
	if(dataStructInterface.Select_SN==7)
	{
		if(dataStructInterface.krInput == 0 )
		{               
			sprintf(str,"            常闭接点(NC) ");
			strcpy(menuCtrlSysParaCn[5],str);
			strcpy(menuCtrlSysParaEn[5],str);
		}
		else if(dataStructInterface.krInput == 1 )
		{              
			sprintf(str,"            常开接点(NO) ");
			strcpy(menuCtrlSysParaCn[5],str);
			strcpy(menuCtrlSysParaEn[5],str);
		}
		eeprom.krInput_save=dataStructInterface.krInput;
		eeprom.flag_krInput=1;
	}else
	if(dataStructInterface.Select_SN==9)   //4-20
	{
		if(dataStructInterface.anologInput==0)
		{	  
            ai_o420.flag_I_up=1;
            ai_o420.flag_I_down=0;
			            
            sprintf(str," 斜坡               上升 ");
            strcpy(menuCtrlSysParaCn[9],str);
            strcpy(menuCtrlSysParaEn[9],str);
		}else
		if(dataStructInterface.anologInput==1)
		{
            ai_o420.flag_I_up=0;
            ai_o420.flag_I_down=1;
			              
            sprintf(str," 斜坡               下降 ");
            strcpy(menuCtrlSysParaCn[9],str);
            strcpy(menuCtrlSysParaEn[9],str);
		}
	}else
	if(dataStructInterface.Select_SN==10)
	{
		if(dataStructInterface.anologInputRange==0)
		{
            ai_o420.flag_I_0020=0;
            ai_o420.flag_I_0420=1;
			              
            sprintf(str," 范围          4 - 20 mA ");
            strcpy(menuCtrlSysParaCn[10],str);
            strcpy(menuCtrlSysParaEn[10],str);
		}else
		if(dataStructInterface.anologInputRange==1)
		{
            ai_o420.flag_I_0020=1;
            ai_o420.flag_I_0420=0;
			              
            sprintf(str," 范围          0 - 20 mA ");
            strcpy(menuCtrlSysParaCn[10],str);
            strcpy(menuCtrlSysParaEn[10],str);
		}
	}else
	if(dataStructInterface.Select_SN==27)
	{
		if(dataStructInterface.anologOutputSel1==1)
		{             
            sprintf(str,"              实际位置值 ");
            strcpy(menuCtrlSysParaCn[14],str);
            strcpy(menuCtrlSysParaEn[14],str);
		}else
		if(dataStructInterface.anologOutputSel1==0)
		{               
            sprintf(str,"              实际过程值 ");
            strcpy(menuCtrlSysParaCn[14],str);
            strcpy(menuCtrlSysParaEn[14],str);
		}
	}else
		if(dataStructInterface.Select_SN==28)
	{
		if(dataStructInterface.anologOutputSel2==0)
		{                       
            sprintf(str," 范围          4 - 20 mA ");
            strcpy(menuCtrlSysParaCn[15],str);
            strcpy(menuCtrlSysParaEn[15],str);
		}else
		if(dataStructInterface.anologOutputSel2==1)
		{               
            sprintf(str," 范围          0 - 20 mA ");
            strcpy(menuCtrlSysParaCn[15],str);
            strcpy(menuCtrlSysParaEn[15],str);
		}
	}else
	if(dataStructInterface.Select_SN==30)
	{
		if(dataStructInterface.emgInput==0)
		{                 
            sprintf(str,"            常闭接点(NC) ");
            strcpy(menuSaftyCn[1],str);
            strcpy(menuSaftyEn[1],str);
			remote_conntrol.EME_Flag=0;
		}else
		if(dataStructInterface.emgInput==1)
		{                
            sprintf(str,"            常开接点(NO) ");
            strcpy(menuSaftyCn[1],str);
            strcpy(menuSaftyEn[1],str);
			remote_conntrol.EME_Flag=1;
		}
		eeprom.emgInput=dataStructInterface.emgInput;
		eeprom.flag_emgInput=1;
	}else
	if(dataStructInterface.Select_SN==29)
	{
		if(dataStructInterface.anologOutputSel3==0)
		{
            ai_o420.flag_O_up=1;
            ai_o420.flag_O_down=0;
			             
            sprintf(str," 斜坡               上升 ");
            strcpy(menuCtrlSysParaCn[16],str);
            strcpy(menuCtrlSysParaEn[16],str);
		}else
		if(dataStructInterface.anologOutputSel3==1)
		{
            ai_o420.flag_O_up=0;
            ai_o420.flag_O_down=1;
			              
            sprintf(str," 斜坡               下降 ");
            strcpy(menuCtrlSysParaCn[16],str);
            strcpy(menuCtrlSysParaEn[16],str);
		}
	}else
	if(dataStructInterface.Select_SN==3)
	{		
        eeprom.flag_closeOffMode=1;
        encoder.set_end_ok=0;
        if(dataStructInterface.closeOffMode==1)
		{
			eeprom.flag_UI_closeOffMode=1;
		}else
		if(dataStructInterface.closeOffMode==0)
		{
			eeprom.flag_UI_closeOffMode=0;
		}
	}else
	if(dataStructInterface.Select_SN==4)
	{
		eeprom.flag_openOffMode=1;
		encoder.set_end_ok=0;
        if(dataStructInterface.openOffMode==1)
		{
			eeprom.flag_UI_openOffMode=1;
		}else
		if(dataStructInterface.openOffMode==0)
		{
			eeprom.flag_UI_openOffMode=0;
		}
	}else
	if(dataStructInterface.Select_SN==45)
	{
        switch(dataStructInterface.showDirect)
        {                       
            case 0:
                sprintf(str,"                     0度 ");
                GUI_SetOrientation(0);
                eeprom.showDirect=1;
                strcpy(menuParaSysShowDirCn[1],str);
                strcpy(menuParaSysShowDirEn[1],str);
                break;      
            case 1:
                sprintf(str,"                   180度 ");
                GUI_SetOrientation(GUI_MIRROR_X | GUI_MIRROR_Y);
                eeprom.showDirect=1;
                strcpy(menuParaSysShowDirCn[1],str);
                strcpy(menuParaSysShowDirEn[1],str);
                break;
            default :
                break;
        }
	}	
}

	
void _WinCommonSelectKeyEnter(void )
{
    unsigned char i=0;
    unsigned char j=0;
    for(i=0,j=0;i< pWinCommonSelecMenu->data->menunum; i++)
    {
        if(0 == LISTBOX_GetItemDisabled(m_CommonSelectMenu.hList,i) )
        {
            if(i == LISTBOX_GetSel(m_CommonSelectMenu.hList) )
            {
                *(pWinCommonSelecMenu->data->menusel) = j;
								ext_IO.flag_refresh=1;
							//ext_IO.eep_save=1;
								_WinCommonSelectRefresh();
								_WinCommonSelctRefresh();
							_WinCommonSelectRefresh_save(j);
							
                break;
            }
            j++;
        }
    }
    WIN_Exit(0);
}

void _WinCommonSelectKeyDown(void )
{
    char curIndex=0;
    char curIndexDisable=0;
    char NumItems = LISTBOX_GetNumItems(m_CommonSelectMenu.hList);

    curIndex = LISTBOX_GetSel(m_CommonSelectMenu.hList);
    curIndex++;
    if(curIndex == LISTBOX_GetNumItems(m_CommonSelectMenu.hList) )
    {
        curIndex = 0;
        curIndexDisable = LISTBOX_GetItemDisabled(m_CommonSelectMenu.hList,curIndex);
        while(curIndexDisable)
        {
            LISTBOX_SetItemDisabled(m_CommonSelectMenu.hList,curIndex,0);
            LISTBOX_SetSel(m_CommonSelectMenu.hList,curIndex);
            LISTBOX_SetItemDisabled(m_CommonSelectMenu.hList,curIndex,1);
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_CommonSelectMenu.hList,curIndex);
        }
        LISTBOX_SetSel(m_CommonSelectMenu.hList,curIndex);
    }
    else
    {
        curIndexDisable = LISTBOX_GetItemDisabled(m_CommonSelectMenu.hList,curIndex);
        while(curIndexDisable)
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_CommonSelectMenu.hList,curIndex);
        }
        LISTBOX_SetSel(m_CommonSelectMenu.hList,curIndex);
    }
}

void _WinCommonSelectKeyUp(void)
{
    char curIndex =0;
    char curIndexDisable =0;
    char curLen= LISTBOX_GetNumItems(m_CommonSelectMenu.hList);

    curIndex = LISTBOX_GetSel(m_CommonSelectMenu.hList);
    if(curIndex>0)
    {
        curIndex--;
        curIndexDisable = LISTBOX_GetItemDisabled(m_CommonSelectMenu.hList,curIndex);
        while(curIndexDisable)
        {
            if(curIndex>0)
            {
                curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CommonSelectMenu.hList,curIndex);
            }
            else
            {
                curIndex = curLen - 1;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CommonSelectMenu.hList,curIndex);
            }
        }
    }
    else
    {
        curIndex = curLen - 1;
        curIndexDisable = LISTBOX_GetItemDisabled(m_CommonSelectMenu.hList,curIndex);
        while(curIndexDisable)
        {
            if(curIndex>0)
            {
                curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CommonSelectMenu.hList,curIndex);
            }
            else
            {
                curIndex = curLen - 1;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CommonSelectMenu.hList,curIndex);
            }
        }
    }
    LISTBOX_SetSel(m_CommonSelectMenu.hList,curIndex);
}

static void _WinCommonSelectCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinCommonSelectKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinCommonSelectKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinCommonSelectKeyEnter();
            _WinCommonSelectRefresh();
            _WinCommonSelctRefresh();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinCommonSelectCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    short           j           = 0;
    short           maxIteam    = 0;
    short           headIndex   = 0;
    short           curSel      = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;
    unsigned char    m_content_num = 0;
    pWinCommonSelecMenu = p;
	dataStructInterface.Select_SN=pMenu->data->SN;
		#if 0
	
	dataStructInterface.Select_SN=pMenu->data->SN;
	#endif
    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
		memcpy(strShow,pTitle,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_CommonSelectMenu.hFrame, 0);             	
	hWin = WM_GetFirstChild(m_CommonSelectMenu.hFrame);
	   GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
		hWin = WM_HBKWIN;
#if 1       
	m_CommonSelectMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_CommonSelectMenu.hImage_CB_1,&bmComBack_1);
	
	m_CommonSelectMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_CommonSelectMenu.hImage_CB_2,&bmComBack_2);
    #endif
    m_CommonSelectMenu.hText      = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    if(pMenu->data->menunum < MAX_ITEAM_PER_PAGE)
        m_CommonSelectMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23+10, PER_CM_OFFSET*4.5, PER_CM_OFFSET*4, hWin, WM_CF_SHOW, NULL, NULL,NULL);//
    else
        m_CommonSelectMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23+10,PER_CM_OFFSET*4.5+11, PER_CM_OFFSET*4,  hWin, WM_CF_SHOW, NULL, NULL,NULL);//	
		#if 1
		header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
		  hWin = m_CommonSelectMenu.hText;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
		#endif
#if 1
    hWin = m_CommonSelectMenu.hList;
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
    LISTBOX_SetAutoScrollV(hWin,1);
#endif
    pMenu->data->title[g_LanguageIndex];
    for(i=0;i<pMenu->data->menunum;i++)
    {
    	memset(strShow,0,sizeof(strShow));
        if(LANGUAGE_CN == g_LanguageIndex) 
				{
					memcpy(strShow,pContentCn,STRSHOWBUF_SIZE);
				}
        else if(LANGUAGE_EN == g_LanguageIndex) 
				{
					memcpy(strShow,pContentEn,STRSHOWBUF_SIZE);
				}
        pContentCn += MAX_INFO_CHAR;
        pContentEn += MAX_INFO_CHAR;
        LISTBOX_AddString(hWin, strShow);
        if(MENU_SETTING_TITLE == pMenu->data->menuattri[i]) LISTBOX_SetItemDisabled(hWin,i,1);
    }

    for(i=0,j=0;i<pMenu->data->menunum;i++)
    {
        if(MENU_SETTING_CONTENT == pMenu->data->menuattri[i])
        {
            if(j ==( (*(pMenu->data->menusel) )))
            {
                LISTBOX_SetSel(hWin,i);
                curSel = i;
            }
            j++;
        }
    }
    m_content_num = j;
    _WinCommonSelectFresh(p);

    WM_SetCallback(WM_HBKWIN, _WinCommonSelectCallback);
    WM_SetFocus(WM_HBKWIN);
}

void _WinCommonSelectFresh(void *p)
{
    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;

    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    short           j           = 0;
    short           maxIteam    = 0;
    short           headIndex   = 0;
    short           curSel      = 0;
	SCROLLBAR_Handle hScrollV ;     
    for( i=0;i<MAX_ITEAM_PER_PAGE;i++) WM_DeleteWindow(m_CommonSelectMenu.hChkBox[i] );

    hWin = m_CommonSelectMenu.hList;
    for(i=0,j=0;i<pMenu->data->menunum;i++)
    {
        if(MENU_SETTING_CONTENT == pMenu->data->menuattri[i])
        {
            if(j == *(pMenu->data->menusel) )
            {
                curSel = i;
                break;
            }
            j++;
        }
    }
    hScrollV = WM_GetDialogItem(hWin, GUI_ID_VSCROLL);
    i=SCROLLBAR_GetNumItems(hScrollV);
    headIndex=SCROLLBAR_GetValue(hScrollV);
    hWin = WM_GetFirstChild(m_CommonSelectMenu.hFrame);  
    if(headIndex+MAX_ITEAM_PER_PAGE < pMenu->data->menunum) maxIteam = headIndex+MAX_ITEAM_PER_PAGE;
    else maxIteam = pMenu->data->menunum;
    for(i=headIndex,j=0;i< maxIteam; i++)
    {
       if(MENU_SETTING_CONTENT == pMenu->data->menuattri[i])
       {
            m_CommonSelectMenu.hChkBox[j]    = CHECKBOX_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+PER_CM_OFFSET*4.5-23,DEBUG_Y_OFFSET+23+10+23*(i-headIndex),23,23,hWin,WM_CF_SHOW,NULL,NULL);
            if(curSel == i)
            {
                CHECKBOX_SetState(m_CommonSelectMenu.hChkBox[j],1);
            }
            j++;
       }
    }
}
static void _WinCommonSelectDestroy(void *p)
{
    unsigned char index = 0;
		WM_DeleteWindow(m_CommonSelectMenu.hImage_CB_1);                    
		WM_DeleteWindow(m_CommonSelectMenu.hImage_CB_2);                    
		WM_DeleteWindow(m_CommonSelectMenu.hText);                          
		WM_DeleteWindow(m_CommonSelectMenu.hList);                          
		WM_DeleteWindow(m_CommonSelectMenu.hImageBack);                         
    for( ;index<MAX_ITEAM_PER_PAGE;index++) WM_DeleteWindow(m_CommonSelectMenu.hChkBox[index] );  
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_CommonSelectMenu, 0, sizeof(m_CommonSelectMenu));
}

void _WinCommonSelectInterface(void *val)
{
}


WIN_INFO_TYPE g_WinCommonSelectMenu = {                       
    &m_CommonSelectMenu.hFrame,
    _WinCommonSelectCreate,
    _WinCommonSelectDestroy
};

typedef struct {
    GUI_HWIN  hFrame;  
		GUI_HWIN hImage_CB_1;                  
		GUI_HWIN hImage_CB_2;                  
		GUI_HWIN  hTextHead;                   
		GUI_HWIN  hBtnBitMap;                  
		GUI_HWIN  hEdit;                       
		GUI_HWIN  hProg;                       
		GUI_HWIN  hTextUnit;                   
		GUI_HWIN  hTextMin;                    
		GUI_HWIN  hTextMax;                    
		GUI_HWIN  hButtonEdit;                 
		GUI_HWIN  hImageBack;                  
}SPEED_CLOSE_MENU_TYPE;
static SPEED_CLOSE_MENU_TYPE m_SpeedCloseMenu = {0};                         
void _WinSpeedCloseRefresh(void)
{
	char str[MAX_INFO_CHAR];	              
    sprintf(str,"                  %d rpm ",dataStructInterface.speed_close);
    strcpy(menuVavleParaCn[3],str);
    strcpy(menuVavleParaEn[3],str);
    strcpy(menu1EndPosParaCn[3],str);
    strcpy(menu1EndPosParaEn[3],str);
}
void _WinSpeedCloseKeyEnter(void )
{
	eeprom.flag_speed_close=1;
    WIN_Exit(0);
}
void _WinSpeedCloseKeyDown(void )
{
    switch(dataStructInterface.speed_close)
    {
        case rang1: dataStructInterface.speed_close = rang2;
        break;
        case rang2: dataStructInterface.speed_close = rang3;
        break;
        case rang3: dataStructInterface.speed_close = rang4;
        break;
        case rang4: dataStructInterface.speed_close = rang5;
        break;
        case rang5: dataStructInterface.speed_close = rang6;
        break;
        case rang6: dataStructInterface.speed_close = rang7;
        break;
        case rang7: dataStructInterface.speed_close = rang1;
        break;
        default :   dataStructInterface.speed_close = rang1;
        break;
    }
    EDIT_SetValue(m_SpeedCloseMenu.hEdit,dataStructInterface.speed_close);
    PROGBAR_SetValue(m_SpeedCloseMenu.hProg,dataStructInterface.speed_close);
}

void _WinSpeedCloseKeyUp(void)
{
    switch(dataStructInterface.speed_close)
    {
        case rang1: dataStructInterface.speed_close = rang7;
        break;
        case rang2: dataStructInterface.speed_close = rang1;
        break;
        case rang3: dataStructInterface.speed_close = rang2;
        break;
        case rang4: dataStructInterface.speed_close = rang3;
        break;
        case rang5: dataStructInterface.speed_close = rang4;
        break;
        case rang6: dataStructInterface.speed_close = rang5;
        break;
        case rang7: dataStructInterface.speed_close = rang6;
        break;
        default :   dataStructInterface.speed_close = rang7;
        break;
    }
    EDIT_SetValue(m_SpeedCloseMenu.hEdit,dataStructInterface.speed_close);
    PROGBAR_SetValue(m_SpeedCloseMenu.hProg,dataStructInterface.speed_close);
}

static void _WinSpeedCloseCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinSpeedCloseKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinSpeedCloseKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinSpeedCloseKeyEnter();
				_WinSpeedCloseRefresh();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}
static int _ProgOwnerSkin3(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN hWin;
  int     Index;
	int i,j,k;
	int m,n;
PROGBAR_SKINFLEX_INFO *pSkin =(PROGBAR_SKINFLEX_INFO *)pDrawItemInfo->p;;
  hWin     = pDrawItemInfo->hWin;
  Index    = pDrawItemInfo->ItemIndex;
  
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_CREATE:
		break;
  case WIDGET_ITEM_DRAW_BACKGROUND:
    if(pSkin->Index == PROGBAR_SKINFLEX_L)
    {
			if(flag_estop==0)
			{
					for(i=(pDrawItemInfo->x0);i<(pDrawItemInfo->x1);i++)
					{		
						if(i%10<2)
						{
						GUI_SetColor(GUI_WHITE);
						}else
						{
							GUI_SetColor(GUI_BLUE);
						}				
						GUI_DrawLine(i,pDrawItemInfo->y0,i,pDrawItemInfo->y1);					
					}
			}
		
    }
    if(pSkin->Index == PROGBAR_SKINFLEX_R)
    {		
			#if 1
			GUI_ClearRect(pDrawItemInfo->x0,pDrawItemInfo->y0,pDrawItemInfo->x1-1,pDrawItemInfo->y1-1);
			#endif
    }
    break;
  case WIDGET_ITEM_DRAW_FRAME:
  GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
    GUI_SetColor(GUI_BLACK);
    GUI_DrawRoundedRect(pDrawItemInfo->x0,pDrawItemInfo->y0,pDrawItemInfo->x1,pDrawItemInfo->y1,1);
    break;
  case WIDGET_ITEM_DRAW_TEXT:
  	break;
  default:
    return PROGBAR_DrawSkinFlex(pDrawItemInfo);
  }
  return 0;
}

static void _WinSpeedCloseCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char            *pTitle     = pMenu->data->title[g_LanguageIndex];
    const char      *pContentCn = pMenu->data->menutitleCn;
    const char      *pContentEn = pMenu->data->menutitleEn;

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_SpeedCloseMenu.hFrame, 0);            

    hWin = WM_GetFirstChild(m_SpeedCloseMenu.hFrame); 
    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	WIDGET_SetDefaultEffect_None();	
		#if 1
			m_SpeedCloseMenu.hButtonEdit   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+80-5, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 70, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_SpeedCloseMenu.hButtonEdit,SKIN_Three_NUMBER_Button);
    BUTTON_SetPressed(m_SpeedCloseMenu.hButtonEdit,1);

    m_SpeedCloseMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SpeedCloseMenu.hTextUnit  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+10, 20*2, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SpeedCloseMenu.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SpeedCloseMenu.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SpeedCloseMenu.hEdit      = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+80, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 60, 40, hWin, WM_CF_SHOW, NULL , NULL, 3);
    m_SpeedCloseMenu.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET+30   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, 162+2, 19+2, hWin,  NULL, WM_CF_SHOW);
		#endif
		#if 1
		header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
		hWin = m_SpeedCloseMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    hWin = m_SpeedCloseMenu.hEdit;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetDecMode(hWin,dataStructInterface.speed_close,SPEED_MIN,SPEED_MAX,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
	close_drive(50,80);
    StrShowClear();
    enc_unicode_to_utf8_str("rpm",strShow,STRSHOWBUF_SIZE);
    hWin = m_SpeedCloseMenu.hTextUnit;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("20 rpm",strShow,STRSHOWBUF_SIZE);
    hWin = m_SpeedCloseMenu.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("160 rpm",strShow,STRSHOWBUF_SIZE);
    hWin = m_SpeedCloseMenu.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);	
    hWin = m_SpeedCloseMenu.hProg;
    PROGBAR_SetText(m_SpeedCloseMenu.hProg,"");
    #ifdef  CE12
    PROGBAR_SetMinMax(hWin,/*20*/05,/*160*/40);   
		#endif
		#ifdef  DE13
    PROGBAR_SetMinMax(hWin,10,80);   
		#endif
		
		#ifdef  EE13
    PROGBAR_SetMinMax(hWin,20,160);  
		#endif
    PROGBAR_SetValue(m_SpeedCloseMenu.hProg,dataStructInterface.speed_close);
	PROGBAR_SetSkin(hWin,_ProgOwnerSkin3);

    WM_SetCallback(WM_HBKWIN, _WinSpeedCloseCallback);
    WM_SetFocus(WM_HBKWIN);
		#endif
}

static void _WinSpeedCloseDestroy(void *p)
{
    WM_DeleteWindow(m_SpeedCloseMenu.hImage_CB_1);               
    WM_DeleteWindow(m_SpeedCloseMenu.hImage_CB_2);               
    WM_DeleteWindow(m_SpeedCloseMenu.hTextHead);                 
    WM_DeleteWindow(m_SpeedCloseMenu.hBtnBitMap);                
    WM_DeleteWindow(m_SpeedCloseMenu.hEdit);                     
    WM_DeleteWindow(m_SpeedCloseMenu.hProg);                     
    WM_DeleteWindow(m_SpeedCloseMenu.hTextUnit);                 
    WM_DeleteWindow(m_SpeedCloseMenu.hTextMin);                  
    WM_DeleteWindow(m_SpeedCloseMenu.hTextMax);                  
    WM_DeleteWindow(m_SpeedCloseMenu.hButtonEdit);               
    WM_DeleteWindow(m_SpeedCloseMenu.hImageBack);                
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_SpeedCloseMenu, 0, sizeof(m_SpeedCloseMenu));
}

void _WinSpeedCloseInterface(void *val)
{
}


WIN_INFO_TYPE g_WinSpeedCloseMenu = {                        
    &m_SpeedCloseMenu.hFrame,
    _WinSpeedCloseCreate,
    _WinSpeedCloseDestroy
};


typedef struct {
    GUI_HWIN  hFrame;  
		GUI_HWIN  hTextHead;            
		GUI_HWIN  hBtnBitMap;           
		GUI_HWIN  hEdit;                
		GUI_HWIN  hProg;                
		GUI_HWIN  hTextUnit;            
		GUI_HWIN  hTextMin;             
		GUI_HWIN  hTextMax;             
		GUI_HWIN  hButtonEdit;          
		GUI_HWIN  hImageBack;           
}SPEED_OPEN_MENU_TYPE;
static SPEED_OPEN_MENU_TYPE m_SpeedOpenMenu = {0};                         
void _WinSpeedOpenRefresh(void)
{
		char str[MAX_INFO_CHAR];
	             
		sprintf(str,"                  %d rpm ",dataStructInterface.speed_open);
    strcpy(menuVavleParaCn[4],str);
    strcpy(menuVavleParaEn[4],str);
		strcpy(menu1EndPosParaCn[4],str);
    strcpy(menu1EndPosParaEn[4],str);
}
void _WinSpeedOpenKeyEnter(void )
{
	eeprom.flag_speed_open=1;
    WIN_Exit(0);
}

void _WinSpeedOpenKeyDown(void )
{
    switch(dataStructInterface.speed_open)
    {
        case rang1: dataStructInterface.speed_open = rang2;
        break;
        case rang2: dataStructInterface.speed_open = rang3;
        break;
        case rang3: dataStructInterface.speed_open = rang4;
        break;
        case rang4: dataStructInterface.speed_open = rang5;
        break;
        case rang5: dataStructInterface.speed_open = rang6;
        break;
        case rang6: dataStructInterface.speed_open = rang7;
        break;
        case rang7: dataStructInterface.speed_open = rang1;
        break;
        default :   dataStructInterface.speed_open = rang1;
        break;
    }
    EDIT_SetValue(m_SpeedOpenMenu.hEdit,dataStructInterface.speed_open);
    PROGBAR_SetValue(m_SpeedOpenMenu.hProg,dataStructInterface.speed_open);
}

void _WinSpeedOpenKeyUp(void)
{
    switch(dataStructInterface.speed_open)
    {
        case rang1: dataStructInterface.speed_open = rang7;
        break;
        case rang2: dataStructInterface.speed_open = rang1;
        break;
        case rang3: dataStructInterface.speed_open = rang2;
        break;
        case rang4: dataStructInterface.speed_open = rang3;
        break;
        case rang5: dataStructInterface.speed_open = rang4;
        break;
        case rang6: dataStructInterface.speed_open = rang5;
        break;
        case rang7: dataStructInterface.speed_open = rang6;
        break;
        default :   dataStructInterface.speed_open = rang7;
        break;
    }
    EDIT_SetValue(m_SpeedOpenMenu.hEdit,dataStructInterface.speed_open);
    PROGBAR_SetValue(m_SpeedOpenMenu.hProg,dataStructInterface.speed_open);
}

static void _WinSpeedOpenCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinSpeedOpenKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinSpeedOpenKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinSpeedOpenKeyEnter();
				_WinSpeedOpenRefresh();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinSpeedOpenCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);

    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_SpeedOpenMenu.hFrame, 0);             

    hWin = WM_GetFirstChild(m_SpeedOpenMenu.hFrame);            
			GUI_Clear();
	GUI_EnableAlpha(1);
	WIDGET_SetDefaultEffect_None();
		
#if 1     
	m_SpeedCloseMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_SpeedCloseMenu.hImage_CB_1,&bmComBack_1);	
	m_SpeedCloseMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_SpeedCloseMenu.hImage_CB_2,&bmComBack_2);
    #endif
		m_SpeedOpenMenu.hButtonEdit   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+80-5, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 70, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_SpeedOpenMenu.hButtonEdit,SKIN_Three_NUMBER_Button);
    BUTTON_SetPressed(m_SpeedOpenMenu.hButtonEdit,1);
		
    m_SpeedOpenMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SpeedOpenMenu.hTextUnit  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+10, 20*2, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SpeedOpenMenu.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SpeedOpenMenu.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SpeedOpenMenu.hEdit      = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+80, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 60, 40, hWin, WM_CF_SHOW, NULL , NULL, 3);
    m_SpeedOpenMenu.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, PER_CM_OFFSET*4.5, 23, hWin,  NULL, WM_CF_SHOW);
    header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_SpeedOpenMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
   TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);

    hWin = m_SpeedOpenMenu.hEdit;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_ORANGE);
    EDIT_SetDecMode(hWin,dataStructInterface.speed_open,SPEED_MIN,SPEED_MAX,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
		open_drive(50,80);
    StrShowClear();
    enc_unicode_to_utf8_str("rpm",strShow,STRSHOWBUF_SIZE);
    hWin = m_SpeedOpenMenu.hTextUnit;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("20 rpm",strShow,STRSHOWBUF_SIZE);
    hWin = m_SpeedOpenMenu.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("160 rpm",strShow,STRSHOWBUF_SIZE);
    hWin = m_SpeedOpenMenu.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);

    hWin = m_SpeedOpenMenu.hProg;
    PROGBAR_SetText(m_SpeedOpenMenu.hProg,"");
		#ifdef  CE12
    PROGBAR_SetMinMax(hWin,/*20*/05,/*160*/40);   
		#endif
		#ifdef  DE13
    PROGBAR_SetMinMax(hWin,10,80);   
		#endif
		
		#ifdef  EE13
    PROGBAR_SetMinMax(hWin,20,160);   
		#endif
    PROGBAR_SetValue(m_SpeedOpenMenu.hProg,dataStructInterface.speed_open);
		PROGBAR_SetSkin(hWin,_ProgOwnerSkin3);

    WM_SetCallback(WM_HBKWIN, _WinSpeedOpenCallback);
    WM_SetFocus(WM_HBKWIN);
}

static void _WinSpeedOpenDestroy(void *p)
{
		WM_DeleteWindow(m_SpeedOpenMenu.hTextHead);            
		WM_DeleteWindow(m_SpeedOpenMenu.hBtnBitMap);           
		WM_DeleteWindow(m_SpeedOpenMenu.hEdit);                
		WM_DeleteWindow(m_SpeedOpenMenu.hProg);                
		WM_DeleteWindow(m_SpeedOpenMenu.hTextUnit);            
		WM_DeleteWindow(m_SpeedOpenMenu.hTextMin);             
		WM_DeleteWindow(m_SpeedOpenMenu.hTextMax);             
		WM_DeleteWindow(m_SpeedOpenMenu.hButtonEdit);          
		WM_DeleteWindow(m_SpeedOpenMenu.hImageBack);           
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_SpeedOpenMenu, 0, sizeof(m_SpeedOpenMenu));
}

void _WinSpeedOpenInterface(void *val)
{

}


WIN_INFO_TYPE g_WinSpeedOpenMenu = {                        
    &m_SpeedOpenMenu.hFrame,
    _WinSpeedOpenCreate,
    _WinSpeedOpenDestroy
};


typedef struct {
    GUI_HWIN  hFrame;
		GUI_HWIN hImage_CB_1;          
		GUI_HWIN hImage_CB_2;          
		GUI_HWIN  hTextHead;           
		GUI_HWIN  hBtnBitMap;          
		GUI_HWIN  hEdit;               
		GUI_HWIN  hTextEnd;            
		GUI_HWIN  hTextUnit;           
		GUI_HWIN  hButtonEdit;         
		GUI_HWIN  hImageBack;          
}ENDPOS_CLOSE_MENU_TYPE;
static ENDPOS_CLOSE_MENU_TYPE m_EndPosCloseMenu = {0};                       
void _WinEndPosCloseRefresh(void)
{
	char str[MAX_INFO_CHAR];	
	            
	sprintf(str,"              0 - %d %%% ",dataStructInterface.endPosClose);
    strcpy(menuVavleParaCn[12],str);
    strcpy(menuVavleParaEn[12],str);
	eeprom.flag_endPosClose=1;
}
void _WinEndPosCloseKeyEnter(void )
{
	_WinEndPosCloseRefresh();
    WIN_Exit(0);
}

void _WinEndPosCloseKeyDown(void )
{
    if(dataStructInterface.endPosClose>=END_POS_CLOSE_MIN)
    {
        if(dataStructInterface.endPosClose < END_POS_CLOSE_MAX)
        {
            dataStructInterface.endPosClose++;
        }
        else
        {
            dataStructInterface.endPosClose = END_POS_CLOSE_MIN;
        }
    }
    else
    {
        dataStructInterface.endPosClose = END_POS_CLOSE_MIN;
    }
    EDIT_SetValue(m_EndPosCloseMenu.hEdit,dataStructInterface.endPosClose);
}

void _WinEndPosCloseKeyUp(void)
{
    if(dataStructInterface.endPosClose<=END_POS_CLOSE_MAX)
    {
        if(dataStructInterface.endPosClose > END_POS_CLOSE_MIN)
        {
            dataStructInterface.endPosClose--;
        }
        else
        {
            dataStructInterface.endPosClose = END_POS_CLOSE_MAX;
        }
    }
    else
    {
        dataStructInterface.endPosClose = END_POS_CLOSE_MAX;
    }
    EDIT_SetValue(m_EndPosCloseMenu.hEdit,dataStructInterface.endPosClose);
}

static void _WinEndPosCloseCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinEndPosCloseKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinEndPosCloseKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinEndPosCloseKeyEnter();
				_WinEndPosCloseRefresh();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinEndPosCloseCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
     char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_EndPosCloseMenu.hFrame, 0);            

    hWin = WM_GetFirstChild(m_EndPosCloseMenu.hFrame);  
    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	WIDGET_SetDefaultEffect_None();
#if 1       //界面修改
	m_EndPosCloseMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EndPosCloseMenu.hImage_CB_1,&bmComBack_1);	
	m_EndPosCloseMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EndPosCloseMenu.hImage_CB_2,&bmComBack_2);
    #endif
	m_EndPosCloseMenu.hButtonEdit   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+90-5-5-5, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80-5, 70, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_EndPosCloseMenu.hButtonEdit,SKIN_Two_NUMBER_Button);
    m_EndPosCloseMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EndPosCloseMenu.hTextEnd   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET-10, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, 20*4, 40, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EndPosCloseMenu.hTextUnit  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, 20*2, 40, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EndPosCloseMenu.hEdit      = EDIT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+80, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, 60, 40, hWin, WM_CF_SHOW, NULL , NULL, 2);
    header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_EndPosCloseMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    hWin = m_EndPosCloseMenu.hEdit;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_ORANGE);
    EDIT_SetTextAlign(hWin,GUI_TA_VCENTER|GUI_TA_HCENTER);
    EDIT_SetDecMode(hWin,dataStructInterface.endPosClose,END_POS_CLOSE_MIN,END_POS_CLOSE_MAX,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
			close_drive(150,60);
    StrShowClear();
    enc_unicode_to_utf8_str("0 - ",strShow,STRSHOWBUF_SIZE);
    hWin = m_EndPosCloseMenu.hTextEnd;
    TEXT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("%",strShow,STRSHOWBUF_SIZE);
    hWin = m_EndPosCloseMenu.hTextUnit;
    TEXT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    WM_SetCallback(WM_HBKWIN, _WinEndPosCloseCallback);
    WM_SetFocus(WM_HBKWIN);
}

static void _WinEndPosCloseDestroy(void *p)
{
		WM_DeleteWindow(m_EndPosCloseMenu.hImage_CB_1);       
		WM_DeleteWindow(m_EndPosCloseMenu.hImage_CB_2);       
		WM_DeleteWindow(m_EndPosCloseMenu.hTextHead);         
		WM_DeleteWindow(m_EndPosCloseMenu.hBtnBitMap);        
		WM_DeleteWindow(m_EndPosCloseMenu.hEdit);             
		WM_DeleteWindow(m_EndPosCloseMenu.hTextEnd);          
		WM_DeleteWindow(m_EndPosCloseMenu.hTextUnit);         
		WM_DeleteWindow(m_EndPosCloseMenu.hButtonEdit);       
		WM_DeleteWindow(m_EndPosCloseMenu.hImageBack);        
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_EndPosCloseMenu, 0, sizeof(m_EndPosCloseMenu));
}



WIN_INFO_TYPE g_WinEndPosCloseMenu = {                        
    &m_EndPosCloseMenu.hFrame,
    _WinEndPosCloseCreate,
    _WinEndPosCloseDestroy
};


typedef struct {
    GUI_HWIN  hFrame; 
		GUI_HWIN hImage_CB_1;            
		GUI_HWIN hImage_CB_2;            
		GUI_HWIN  hTextHead;             
		GUI_HWIN  hBtnBitMap;            
		GUI_HWIN  hEdit;                 
		GUI_HWIN  hTextEnd;              
		GUI_HWIN  hTextUnit;             
		GUI_HWIN  hButtonEdit;           
		GUI_HWIN  hImageBack;            
}ENDPOS_OPEN_MENU_TYPE;
static ENDPOS_OPEN_MENU_TYPE m_EndPosOpenMenu = {0};                        
void _WinEndPosOpenRefresh(void)
{
	char str[MAX_INFO_CHAR];
	           
	sprintf(str,"              %d - 100%%% ",dataStructInterface.endPosOpen);
	//eeprom.endPosOpen=dataStructInterface.endPosOpen;
    strcpy(menuVavleParaCn[13],str);
    strcpy(menuVavleParaEn[13],str);
	eeprom.flag_endPosOpen=1;
}

void _WinEndPosOpenKeyEnter(void )
{
	_WinEndPosOpenRefresh();
    WIN_Exit(0);
}

void _WinEndPosOpenKeyDown(void )
{
    if(dataStructInterface.endPosOpen>=END_POS_OPEN_MIN)
    {
        if(dataStructInterface.endPosOpen < END_POS_OPEN_MAX)
        {
            dataStructInterface.endPosOpen++;
        }
        else
        {
            dataStructInterface.endPosOpen = END_POS_OPEN_MIN;
        }
    }
    else
    {
        dataStructInterface.endPosOpen = END_POS_OPEN_MIN;
    }
    EDIT_SetValue(m_EndPosOpenMenu.hEdit,dataStructInterface.endPosOpen);
}
void _WinEndPosOpenKeyUp(void)
{
    if(dataStructInterface.endPosOpen<=END_POS_OPEN_MAX)
    {
        if(dataStructInterface.endPosOpen > END_POS_OPEN_MIN)
        {
            dataStructInterface.endPosOpen--;
        }
        else
        {
            dataStructInterface.endPosOpen = END_POS_OPEN_MAX;
        }
    }
    else
    {
        dataStructInterface.endPosOpen = END_POS_OPEN_MAX;
    }
    EDIT_SetValue(m_EndPosOpenMenu.hEdit,dataStructInterface.endPosOpen);
}

static void _WinEndPosOpenCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinEndPosOpenKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinEndPosOpenKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinEndPosOpenKeyEnter();
				_WinEndPosOpenRefresh();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinEndPosOpenCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
     char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_EndPosOpenMenu.hFrame, 0);             

    hWin = WM_GetFirstChild(m_EndPosOpenMenu.hFrame);
    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	WIDGET_SetDefaultEffect_None();
#if 1      
	m_EndPosOpenMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EndPosOpenMenu.hImage_CB_1,&bmComBack_1);	
	m_EndPosOpenMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EndPosOpenMenu.hImage_CB_2,&bmComBack_2);
    #endif
	m_EndPosOpenMenu.hButtonEdit   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80-5, 70, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_EndPosOpenMenu.hButtonEdit,SKIN_Two_NUMBER_Button);
    m_EndPosOpenMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EndPosOpenMenu.hTextEnd   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+80+10, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, 20*4, 40, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EndPosOpenMenu.hTextUnit  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, 20*2, 40, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
   m_EndPosOpenMenu.hEdit      = EDIT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+5, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, 60, 40, hWin, WM_CF_SHOW, NULL , NULL, 2);
    header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_EndPosOpenMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
hWin = m_EndPosOpenMenu.hEdit;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_ORANGE);
    EDIT_SetTextAlign(hWin,GUI_TA_VCENTER|GUI_TA_HCENTER);
    EDIT_SetDecMode(hWin,dataStructInterface.endPosOpen,END_POS_OPEN_MIN,END_POS_OPEN_MAX,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
		open_drive(150,60);
    StrShowClear();
    enc_unicode_to_utf8_str("-100",strShow,STRSHOWBUF_SIZE);
    hWin = m_EndPosOpenMenu.hTextEnd;
    TEXT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("%",strShow,STRSHOWBUF_SIZE);
    hWin = m_EndPosOpenMenu.hTextUnit;
    TEXT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    WM_SetCallback(WM_HBKWIN, _WinEndPosOpenCallback);
    WM_SetFocus(WM_HBKWIN);
}
static void _WinEndPosOpenDestroy(void *p)
{
		WM_DeleteWindow(m_EndPosOpenMenu.hImage_CB_1);         
		WM_DeleteWindow(m_EndPosOpenMenu.hImage_CB_2);         
		WM_DeleteWindow(m_EndPosOpenMenu.hTextHead);           
		WM_DeleteWindow(m_EndPosOpenMenu.hBtnBitMap);          
		WM_DeleteWindow(m_EndPosOpenMenu.hEdit);               
		WM_DeleteWindow(m_EndPosOpenMenu.hTextEnd);            
		WM_DeleteWindow(m_EndPosOpenMenu.hTextUnit);           
		WM_DeleteWindow(m_EndPosOpenMenu.hButtonEdit);         
		WM_DeleteWindow(m_EndPosOpenMenu.hImageBack);          
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_EndPosOpenMenu, 0, sizeof(m_EndPosOpenMenu));
}



WIN_INFO_TYPE g_WinEndPosOpenMenu = {                        
    &m_EndPosOpenMenu.hFrame,
    _WinEndPosOpenCreate,
    _WinEndPosOpenDestroy
};

typedef struct {
    GUI_HWIN  hFrame; 
		GUI_HWIN hImage_CB_1;           
		GUI_HWIN hImage_CB_2;           
		GUI_HWIN hTextHead;             
		GUI_HWIN hBtnBitMap;            
		GUI_HWIN hEdit;                 
		GUI_HWIN hProg;                 
		GUI_HWIN hTextUnit;             
		GUI_HWIN hTextMin;              
		GUI_HWIN hTextMax;              
		GUI_HWIN hButtonEdit;           
		GUI_HWIN hImageBack;            
}MOMENT_CLOSE_MENU_TYPE;
static MOMENT_CLOSE_MENU_TYPE m_MomentCloseMenu = {0};                       
void _WinMomentCloseRefesh(void)
{
	char str[MAX_INFO_CHAR];
	           
	sprintf(str,"                  %d  Nm ",(int)dataStructInterface.moment_close);
	strcpy(menuVavleParaCn[9],str);
	strcpy(menuVavleParaEn[9],str);
	strcpy(menu2EndPosParaCn[4],str);
	strcpy(menu2EndPosParaEn[4],str);

}
void _WinMomentCloseKeyEnter(void )
{
	eeprom.flag_moment_close=1;
	_WinMomentCloseRefesh();
    WIN_Exit(0);
}

void _WinMomentCloseKeyDown(void )
{
    if(dataStructInterface.moment_close < MOMENT_MAX)
    {
        if(dataStructInterface.moment_close >= MOMENT_MIN)
        {
            dataStructInterface.moment_close+=MOMENT_STEP;
            if(dataStructInterface.moment_close > MOMENT_MAX)
            {
                dataStructInterface.moment_close = MOMENT_MIN;
            }
        }
        else
        {
            dataStructInterface.moment_close = MOMENT_MIN;
        }

    }
    else
    {
        dataStructInterface.moment_close=MOMENT_MIN;
    }
    EDIT_SetFloatValue(m_MomentCloseMenu.hEdit,dataStructInterface.moment_close);
    PROGBAR_SetValue(m_MomentCloseMenu.hProg,dataStructInterface.moment_close);
}

void _WinMomentCloseKeyUp(void)
{
    if(dataStructInterface.moment_close > MOMENT_MIN)
    {
        if(dataStructInterface.moment_close <= MOMENT_MAX)
        {
            dataStructInterface.moment_close -= MOMENT_STEP;
            if(dataStructInterface.moment_close < MOMENT_MIN)
            {
                dataStructInterface.moment_close = MOMENT_MAX;
            }
        }
        else
        {
            dataStructInterface.moment_close = MOMENT_MAX;
        }

    }
    else
    {
        dataStructInterface.moment_close=MOMENT_MAX;
    }
    EDIT_SetFloatValue(m_MomentCloseMenu.hEdit,dataStructInterface.moment_close);
    PROGBAR_SetValue(m_MomentCloseMenu.hProg,dataStructInterface.moment_close);
}
static void _WinMomentCloseCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinMomentCloseKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinMomentCloseKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinMomentCloseKeyEnter();
				_WinMomentCloseRefesh();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinMomentCloseCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_MomentCloseMenu.hFrame, 0);            
    hWin = WM_GetFirstChild(m_MomentCloseMenu.hFrame); 
   hWin = WM_GetFirstChild(m_MomentCloseMenu.hFrame);
    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	WIDGET_SetDefaultEffect_None();
#if 1      
	m_MomentCloseMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_MomentCloseMenu.hImage_CB_1,&bmComBack_1);	
	m_MomentCloseMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_MomentCloseMenu.hImage_CB_2,&bmComBack_2);
    #endif
	m_MomentCloseMenu.hButtonEdit   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+60-5, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 100, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_MomentCloseMenu.hButtonEdit,SKIN_Five_NUMBER_Button);
    BUTTON_SetPressed(m_MomentCloseMenu.hButtonEdit,1);
    m_MomentCloseMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_MomentCloseMenu.hTextUnit  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+10, 20*2, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_MomentCloseMenu.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_MomentCloseMenu.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_MomentCloseMenu.hEdit      = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+60, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 90, 40, hWin, WM_CF_SHOW, NULL , NULL, 5);
    m_MomentCloseMenu.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, PER_CM_OFFSET*4.5, 23, hWin,  NULL, WM_CF_SHOW);
    header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_MomentCloseMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
   TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    hWin = m_MomentCloseMenu.hEdit;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_ORANGE);
    EDIT_SetFloatMode(hWin,dataStructInterface.moment_close,MOMENT_MIN,MOMENT_MAX,1,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
close_drive(50,80);
    StrShowClear();
    enc_unicode_to_utf8_str("Nm ",strShow,STRSHOWBUF_SIZE);
		memcpy(strShow,"Nm ",STRSHOWBUF_SIZE);
    hWin = m_MomentCloseMenu.hTextUnit;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("18 Nm",strShow,STRSHOWBUF_SIZE);
		memcpy(strShow,"18 Nm",STRSHOWBUF_SIZE);
    hWin = m_MomentCloseMenu.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("60 Nm",strShow,STRSHOWBUF_SIZE);
		memcpy(strShow,"60 Nm",STRSHOWBUF_SIZE);
    hWin = m_MomentCloseMenu.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    hWin = m_MomentCloseMenu.hProg;
    PROGBAR_SetText(hWin,"");
    PROGBAR_SetMinMax(hWin,MOMENT_MIN,MOMENT_MAX);
    PROGBAR_SetValue(hWin,dataStructInterface.moment_close);
		PROGBAR_SetSkin(hWin,_ProgOwnerSkin3);
    WM_SetCallback(WM_HBKWIN, _WinMomentCloseCallback);
    WM_SetFocus(WM_HBKWIN);
}

static void _WinMomentCloseDestroy(void *p)
{	
		WM_DeleteWindow(m_MomentCloseMenu.hImage_CB_1);            
		WM_DeleteWindow(m_MomentCloseMenu.hImage_CB_2);            
		WM_DeleteWindow(m_MomentCloseMenu.hTextHead);              
		WM_DeleteWindow(m_MomentCloseMenu.hBtnBitMap);             
		WM_DeleteWindow(m_MomentCloseMenu.hEdit);                  
		WM_DeleteWindow(m_MomentCloseMenu.hProg);                  
		WM_DeleteWindow(m_MomentCloseMenu.hTextUnit);              
		WM_DeleteWindow(m_MomentCloseMenu.hTextMin);               
		WM_DeleteWindow(m_MomentCloseMenu.hTextMax);               
		WM_DeleteWindow(m_MomentCloseMenu.hButtonEdit);            
		WM_DeleteWindow(m_MomentCloseMenu.hImageBack);             
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_MomentCloseMenu, 0, sizeof(m_MomentCloseMenu));
}


WIN_INFO_TYPE g_WinMomentCloseMenu = {                      
    &m_MomentCloseMenu.hFrame,
    _WinMomentCloseCreate,
    _WinMomentCloseDestroy
};

typedef struct {
    GUI_HWIN  hFrame;  
		GUI_HWIN hImage_CB_1;       
		GUI_HWIN hImage_CB_2;       
		GUI_HWIN hTextHead;         
		GUI_HWIN hBtnBitMap;        
		GUI_HWIN hEdit;             
		GUI_HWIN hProg;             
		GUI_HWIN hTextUnit;         
		GUI_HWIN hTextMin;          
		GUI_HWIN hTextMax;          
		GUI_HWIN hButtonEdit;       
		GUI_HWIN hImageBack;        
}MOMENT_OPEN_MENU_TYPE;
static MOMENT_OPEN_MENU_TYPE m_MomentOpenMenu = {0};                         
void _WinMomentOpenRefresh(void)
{
		char str[MAX_INFO_CHAR];
	                
			sprintf(str,"                  %d  Nm ",(int)dataStructInterface.moment_open);
			strcpy(menuVavleParaCn[10],str);
			strcpy(menuVavleParaEn[10],str);
			strcpy(menu2EndPosParaCn[5],str);
			strcpy(menu2EndPosParaEn[5],str);
}
void _WinMomentOpenKeyEnter(void )
{
	eeprom.flag_moment_open=1;
	_WinMomentOpenRefresh();
    WIN_Exit(0);
}

void _WinMomentOpenKeyDown(void )
{
    if(dataStructInterface.moment_open < MOMENT_MAX)
    {
        if(dataStructInterface.moment_open >= MOMENT_MIN)
        {
            dataStructInterface.moment_open+=MOMENT_STEP;
            if(dataStructInterface.moment_open > MOMENT_MAX)
            {
                dataStructInterface.moment_open = MOMENT_MIN;
            }
        }
        else
        {
            dataStructInterface.moment_open = MOMENT_MIN;
        }

    }
    else
    {
        dataStructInterface.moment_open=MOMENT_MIN;
    }
    EDIT_SetFloatValue(m_MomentOpenMenu.hEdit,dataStructInterface.moment_open);
    PROGBAR_SetValue(m_MomentOpenMenu.hProg,dataStructInterface.moment_open);
}

void _WinMomentOpenKeyUp(void)
{
    if(dataStructInterface.moment_open > MOMENT_MIN)
    {
        if(dataStructInterface.moment_open <= MOMENT_MAX)
        {
            dataStructInterface.moment_open -= MOMENT_STEP;
            if(dataStructInterface.moment_open < MOMENT_MIN)
            {
                dataStructInterface.moment_open = MOMENT_MAX;
            }
        }
        else
        {
            dataStructInterface.moment_open = MOMENT_MAX;
        }

    }
    else
    {
        dataStructInterface.moment_open=MOMENT_MAX;
    }
    EDIT_SetFloatValue(m_MomentOpenMenu.hEdit,dataStructInterface.moment_open);
    PROGBAR_SetValue(m_MomentOpenMenu.hProg,dataStructInterface.moment_open);
}

static void _WinMomentOpenCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinMomentOpenKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinMomentOpenKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinMomentOpenKeyEnter();
				_WinMomentOpenRefresh();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinMomentOpenCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	memcpy(strShow,pTitle,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_MomentOpenMenu.hFrame, 0);            
    hWin = WM_GetFirstChild(m_MomentOpenMenu.hFrame);   
    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	WIDGET_SetDefaultEffect_None();
#if 1      
	m_MomentOpenMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_MomentOpenMenu.hImage_CB_1,&bmComBack_1);	
	m_MomentOpenMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_MomentOpenMenu.hImage_CB_2,&bmComBack_2);
    #endif
	m_MomentOpenMenu.hButtonEdit   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+60-5, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 100, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_MomentOpenMenu.hButtonEdit,SKIN_Five_NUMBER_Button);
    BUTTON_SetPressed(m_MomentOpenMenu.hButtonEdit,1);
    m_MomentOpenMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_MomentOpenMenu.hTextUnit  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+10, 20*2, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_MomentOpenMenu.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_MomentOpenMenu.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
   m_MomentOpenMenu.hEdit      = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+60, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 90, 40, hWin, WM_CF_SHOW, NULL , NULL, 5);
    m_MomentOpenMenu.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, PER_CM_OFFSET*4.5, 23, hWin,  NULL, WM_CF_SHOW);
   header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_MomentOpenMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
   TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    hWin = m_MomentOpenMenu.hEdit;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_ORANGE);
    EDIT_SetFloatMode(hWin,dataStructInterface.moment_open,MOMENT_MIN,MOMENT_MAX,1,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
open_drive(50,80);
    StrShowClear();
    enc_unicode_to_utf8_str("Nm ",strShow,STRSHOWBUF_SIZE);
		memcpy(strShow,"Nm ",STRSHOWBUF_SIZE);
    hWin = m_MomentOpenMenu.hTextUnit;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("18 Nm",strShow,STRSHOWBUF_SIZE);
		memcpy(strShow,"18 Nm",STRSHOWBUF_SIZE);
    hWin = m_MomentOpenMenu.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("60 Nm",strShow,STRSHOWBUF_SIZE);
		memcpy(strShow,"60 Nm",STRSHOWBUF_SIZE);
    hWin = m_MomentOpenMenu.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    hWin = m_MomentOpenMenu.hProg;
    PROGBAR_SetText(hWin,"");
    PROGBAR_SetMinMax(hWin,MOMENT_MIN,MOMENT_MAX);
    PROGBAR_SetValue(hWin,dataStructInterface.moment_close);
		PROGBAR_SetSkin(hWin,_ProgOwnerSkin3);
    WM_SetCallback(WM_HBKWIN, _WinMomentOpenCallback);
    WM_SetFocus(WM_HBKWIN);
}

static void _WinMomentOpenDestroy(void *p)
{
		WM_DeleteWindow(m_MomentOpenMenu.hImage_CB_1);     
		WM_DeleteWindow(m_MomentOpenMenu.hImage_CB_2);     
		WM_DeleteWindow(m_MomentOpenMenu.hTextHead);       
		WM_DeleteWindow(m_MomentOpenMenu.hBtnBitMap);      
		WM_DeleteWindow(m_MomentOpenMenu.hEdit);           
		WM_DeleteWindow(m_MomentOpenMenu.hProg);           
		WM_DeleteWindow(m_MomentOpenMenu.hTextUnit);       
		WM_DeleteWindow(m_MomentOpenMenu.hTextMin);        
		WM_DeleteWindow(m_MomentOpenMenu.hTextMax);        
		WM_DeleteWindow(m_MomentOpenMenu.hButtonEdit);     
		WM_DeleteWindow(m_MomentOpenMenu.hImageBack);      
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_MomentOpenMenu, 0, sizeof(m_MomentOpenMenu));
}


WIN_INFO_TYPE g_WinMomentOpenMenu = {                         
    &m_MomentOpenMenu.hFrame,
    _WinMomentOpenCreate,
    _WinMomentOpenDestroy
};

typedef struct {
    GUI_HWIN  hFrame; 
    GUI_HWIN hImage_CB_1;          
    GUI_HWIN hImage_CB_2;          
    GUI_HWIN  hTextHead;           
    GUI_HWIN  hEdit;               
    GUI_HWIN  hProg;               
    GUI_HWIN  hTextUnit;           
    GUI_HWIN  hTextMin;            
    GUI_HWIN  hTextMax;            
    GUI_HWIN  hButtonEdit;         
    GUI_HWIN  hImageBack;          
}OVERMOMENT_TIMES_MENU_TYPE;
static OVERMOMENT_TIMES_MENU_TYPE m_OverMomentTimesMenu = {0};                        
void _WinOverMomentTimesRefresh(void)
{
	char str[MAX_INFO_CHAR];
	           
	sprintf(str," 重试次数            %d x ",dataStructInterface.moment_overtimes);
    strcpy(menuVavleParaCn[15],str);
    strcpy(menuVavleParaEn[15],str);
}
void _WinOverMomentTimesKeyEnter(void )
{
    WIN_Exit(0);
}

void _WinOverMomentTimesKeyDown(void )
{
    dataStructInterface.moment_overtimes++;
    if(dataStructInterface.moment_overtimes > MOMENT_OVERTIMES_MAX)
    {
        dataStructInterface.moment_overtimes = MOMENT_OVERTIMES_MIN;
    }
    EDIT_SetFloatValue(m_OverMomentTimesMenu.hEdit,dataStructInterface.moment_overtimes);
    PROGBAR_SetValue(m_OverMomentTimesMenu.hProg,dataStructInterface.moment_overtimes);
}

void _WinOverMomentTimesKeyUp(void)
{
    dataStructInterface.moment_overtimes--;
    if(dataStructInterface.moment_overtimes < MOMENT_OVERTIMES_MIN)
    {
        dataStructInterface.moment_overtimes = MOMENT_OVERTIMES_MAX;
    }
    EDIT_SetFloatValue(m_OverMomentTimesMenu.hEdit,dataStructInterface.moment_overtimes);
    PROGBAR_SetValue(m_OverMomentTimesMenu.hProg,dataStructInterface.moment_overtimes);
}

static void _WinOverMomentTimesCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinOverMomentTimesKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinOverMomentTimesKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinOverMomentTimesKeyEnter();
				_WinOverMomentTimesRefresh();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinOverMomentTimesCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
     char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	memcpy(strShow,pTitle,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_OverMomentTimesMenu.hFrame, 0);             
    hWin = WM_GetFirstChild(m_OverMomentTimesMenu.hFrame);         
		    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	WIDGET_SetDefaultEffect_None();
#if 1       
	m_OverMomentTimesMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_OverMomentTimesMenu.hImage_CB_1,&bmComBack_1);	
	m_OverMomentTimesMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_OverMomentTimesMenu.hImage_CB_2,&bmComBack_2);
    #endif
	m_OverMomentTimesMenu.hButtonEdit   = BUTTON_CreateEx(DEBUG_X_OFFSET+150-30-5, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 70, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_OverMomentTimesMenu.hButtonEdit,SKIN_Two_NUMBER_Button);
    m_OverMomentTimesMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_OverMomentTimesMenu.hTextUnit  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+10, 20*2, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_OverMomentTimesMenu.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_OverMomentTimesMenu.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_OverMomentTimesMenu.hEdit      = EDIT_CreateEx   ( DEBUG_X_OFFSET+150-30, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 60, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_OverMomentTimesMenu.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, PER_CM_OFFSET*4.5, 23, hWin,  NULL, WM_CF_SHOW);
    header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_OverMomentTimesMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    hWin = m_OverMomentTimesMenu.hEdit;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_ORANGE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    EDIT_EnableBlink(hWin,400,1);
    EDIT_SetDecMode(hWin,dataStructInterface.moment_overtimes,MOMENT_OVERTIMES_MIN,MOMENT_OVERTIMES_MAX,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    StrShowClear();
    enc_unicode_to_utf8_str("x ",strShow,STRSHOWBUF_SIZE);
		memcpy(strShow,"x ",STRSHOWBUF_SIZE);
    hWin = m_OverMomentTimesMenu.hTextUnit;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("0 x",strShow,STRSHOWBUF_SIZE);
		memcpy(strShow,"0 x",STRSHOWBUF_SIZE);
    hWin = m_OverMomentTimesMenu.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("5 x",strShow,STRSHOWBUF_SIZE);
    memcpy(strShow,"5 x",STRSHOWBUF_SIZE);
    hWin = m_OverMomentTimesMenu.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    hWin = m_OverMomentTimesMenu.hProg;
    PROGBAR_SetText(hWin,"");
    PROGBAR_SetMinMax(hWin,MOMENT_OVERTIMES_MIN,MOMENT_OVERTIMES_MAX);
    PROGBAR_SetValue(hWin,dataStructInterface.moment_overtimes);
		PROGBAR_SetSkin(hWin,_ProgOwnerSkin3);
    WM_SetCallback(WM_HBKWIN, _WinOverMomentTimesCallback);
    WM_SetFocus(WM_HBKWIN);
}

static void _WinOverMomentTimesDestroy(void *p)
{
		WM_DeleteWindow(m_OverMomentTimesMenu.hImage_CB_1);        
		WM_DeleteWindow(m_OverMomentTimesMenu.hImage_CB_2);        
    WM_DeleteWindow(m_OverMomentTimesMenu.hTextHead);          
    WM_DeleteWindow(m_OverMomentTimesMenu.hEdit);              
    WM_DeleteWindow(m_OverMomentTimesMenu.hProg);              
    WM_DeleteWindow(m_OverMomentTimesMenu.hTextUnit);          
    WM_DeleteWindow(m_OverMomentTimesMenu.hTextMin);           
    WM_DeleteWindow(m_OverMomentTimesMenu.hTextMax);           
		WM_DeleteWindow(m_OverMomentTimesMenu.hButtonEdit);        
		WM_DeleteWindow(m_OverMomentTimesMenu.hImageBack);         
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_OverMomentTimesMenu, 0, sizeof(m_OverMomentTimesMenu));
}


WIN_INFO_TYPE g_WinOverMomentTimesMenu = {                       
    &m_OverMomentTimesMenu.hFrame,
    _WinOverMomentTimesCreate,
    _WinOverMomentTimesDestroy
};


#if 1         
typedef struct {
    GUI_HWIN  hFrame;  	
    GUI_HWIN hImage_CB_1;        
    GUI_HWIN hImage_CB_2;        
    GUI_HWIN  hTextHead;         
    GUI_HWIN  hEditH; 
    GUI_HWIN  hEditD; 
    GUI_HWIN  hEditS; 
    GUI_HWIN  hProg;             
    GUI_HWIN  hTextMin;          
    GUI_HWIN  hTextMax;          
    GUI_HWIN  hList;             
    unsigned char currentSel;    
    unsigned char value_show_h;  
    unsigned char value_show_d;  
    unsigned char value_show_s;  
    GUI_HWIN  hImageBack;        
	GUI_HWIN  hButtonEditH;        
	GUI_HWIN  hButtonEditD;        
	GUI_HWIN  hButtonEditS;        
	GUI_HWIN  hTimer;             
	unsigned char cTimerCnt;      
}EMERGENCY_POS_MENU_TYPE;
static EMERGENCY_POS_MENU_TYPE m_EmergencyPosMenu = {0};                        
void _WinEmergencyPosKeyRefresh(void )
{
char str[MAX_INFO_CHAR];
	if(dataStructInterface.emergency_pos==1)
	{             
		sprintf(str,"                   %d %%% ",0);
	}else
	{            
		sprintf(str,"                   %d %%% ",(dataStructInterface.emergency_pos/*-1*/));
	}
    strcpy(menuSaftyCn[6],str);
    strcpy(menuSaftyEn[6],str);
}
void _WinEmergencyPosKeyEnter(void )
{
    unsigned char m_value=0;
    if(0 == m_EmergencyPosMenu.currentSel)
    {
        m_EmergencyPosMenu.currentSel = 5;
		EDIT_SetTextColor(m_EmergencyPosMenu.hEditH,EDIT_CI_ENABELD,GUI_ORANGE);   
    }
    else if(1 == m_EmergencyPosMenu.currentSel)
    {
        m_EmergencyPosMenu.currentSel = 6;
		EDIT_SetTextColor(m_EmergencyPosMenu.hEditD,EDIT_CI_ENABELD,GUI_ORANGE);  
    }
    else if(2 == m_EmergencyPosMenu.currentSel)
    {
        m_EmergencyPosMenu.currentSel = 7;
		EDIT_SetTextColor(m_EmergencyPosMenu.hEditS,EDIT_CI_ENABELD,GUI_ORANGE);  
    }
    else if(3 == m_EmergencyPosMenu.currentSel)
    {
        m_value = m_EmergencyPosMenu.value_show_h*100 + m_EmergencyPosMenu.value_show_d*10 + m_EmergencyPosMenu.value_show_s;
        if(m_value==0)
        {
            m_value=1;
        }
        if(m_value > 100 ) m_value = 100;
        dataStructInterface.emergency_pos = m_value;
        eeprom.Save_eme_pos=1;
        WIN_Exit(0);
    }
    else if(4 == m_EmergencyPosMenu.currentSel)
    {
        WIN_Exit(0);
    }
    else if(5 == m_EmergencyPosMenu.currentSel)
    {
        EDIT_SetTextColor(m_EmergencyPosMenu.hEditH,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_EmergencyPosMenu.hEditD,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditH,0);
		BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditD,1);
        m_EmergencyPosMenu.currentSel = 6;
		EDIT_SetDecMode(m_EmergencyPosMenu.hEditH,m_EmergencyPosMenu.value_show_h,0,9,0,GUI_EDIT_NORMAL); 
    }
    else if(6 == m_EmergencyPosMenu.currentSel)
    {
        EDIT_SetTextColor(m_EmergencyPosMenu.hEditD,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_EmergencyPosMenu.hEditS,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditD,0);
		BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditS,1);
		m_EmergencyPosMenu.currentSel = 7;
		EDIT_SetDecMode(m_EmergencyPosMenu.hEditD,m_EmergencyPosMenu.value_show_d,0,9,0,GUI_EDIT_NORMAL);  
    }
    else if(7 == m_EmergencyPosMenu.currentSel)
    {
        EDIT_SetTextColor(m_EmergencyPosMenu.hEditS,EDIT_CI_ENABELD,GUI_BLUE);
        LISTBOX_SetSel(m_EmergencyPosMenu.hList,0);
        BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditS,0);
        m_EmergencyPosMenu.currentSel = 3;
		EDIT_SetDecMode(m_EmergencyPosMenu.hEditS,m_EmergencyPosMenu.value_show_s,0,9,0,GUI_EDIT_NORMAL);  
    }
    
    m_value = m_EmergencyPosMenu.value_show_h*100 + m_EmergencyPosMenu.value_show_d*10 + m_EmergencyPosMenu.value_show_s;
    PROGBAR_SetValue(m_EmergencyPosMenu.hProg,m_value);
}

void _WinEmergencyPosKeyDown(int keyValue)
{
    unsigned char m_value=0;
    if(0 == m_EmergencyPosMenu.currentSel)
    {
        BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditH,0);
		BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditD,1);
        m_EmergencyPosMenu.currentSel = 1;
    }
    else if(1 == m_EmergencyPosMenu.currentSel)
    {
        BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditD,0);
		BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditS,1);
        m_EmergencyPosMenu.currentSel = 2;
    }
    else if(2 == m_EmergencyPosMenu.currentSel)
    {
        BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditS,0);
        LISTBOX_SetSel(m_EmergencyPosMenu.hList,0);
        m_EmergencyPosMenu.currentSel = 3;
    }
    else if(3 == m_EmergencyPosMenu.currentSel)
    {
        LISTBOX_SetSel(m_EmergencyPosMenu.hList,1);
        m_EmergencyPosMenu.currentSel = 4;
    }
    else if(4 == m_EmergencyPosMenu.currentSel)
    {
        LISTBOX_SetSel(m_EmergencyPosMenu.hList,-1);
        BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditH,1);
        m_EmergencyPosMenu.currentSel = 0;
    }
    else if(5 == m_EmergencyPosMenu.currentSel)
    {
        m_EmergencyPosMenu.value_show_h++;
        if(m_EmergencyPosMenu.value_show_h>9) m_EmergencyPosMenu.value_show_h = 0;
        EDIT_SetValue(m_EmergencyPosMenu.hEditH,m_EmergencyPosMenu.value_show_h);
    }
    else if(6 == m_EmergencyPosMenu.currentSel)
    {
        m_EmergencyPosMenu.value_show_d++;
        if(m_EmergencyPosMenu.value_show_d>9) m_EmergencyPosMenu.value_show_d = 0;
        EDIT_SetValue(m_EmergencyPosMenu.hEditD,m_EmergencyPosMenu.value_show_d);
    }
    else if(7 == m_EmergencyPosMenu.currentSel)
    {
        m_EmergencyPosMenu.value_show_s++;
        if(m_EmergencyPosMenu.value_show_s>9) m_EmergencyPosMenu.value_show_s = 0;
        EDIT_SetValue(m_EmergencyPosMenu.hEditS,m_EmergencyPosMenu.value_show_s);		
    }
    
    m_value = m_EmergencyPosMenu.value_show_h*100 + m_EmergencyPosMenu.value_show_d*10 + m_EmergencyPosMenu.value_show_s;
    PROGBAR_SetValue(m_EmergencyPosMenu.hProg,m_value);
}

void _WinEmergencyPosKeyUp(void)
{
    unsigned char m_value=0;
    if(0 == m_EmergencyPosMenu.currentSel)
    {
        BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditH,0);
        LISTBOX_SetSel(m_EmergencyPosMenu.hList,1);
        m_EmergencyPosMenu.currentSel = 4;
    }
    else if(1 == m_EmergencyPosMenu.currentSel)
    {
        BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditH,1);
		BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditD,0);
        m_EmergencyPosMenu.currentSel = 0;
    }
    else if(2 == m_EmergencyPosMenu.currentSel)
    {
        BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditD,1);
		BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditS,0);
        m_EmergencyPosMenu.currentSel = 1;
    }
     else if(3 == m_EmergencyPosMenu.currentSel)
    {
        LISTBOX_SetSel(m_EmergencyPosMenu.hList,-1);
        BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditS,1);
        m_EmergencyPosMenu.currentSel = 2;
    }
    else if(4 == m_EmergencyPosMenu.currentSel)
    {
        LISTBOX_SetSel(m_EmergencyPosMenu.hList,0);
        m_EmergencyPosMenu.currentSel = 3;
    }
    else if(5 == m_EmergencyPosMenu.currentSel)
    {
        if(m_EmergencyPosMenu.value_show_h>0)m_EmergencyPosMenu.value_show_h--;
        else  m_EmergencyPosMenu.value_show_h = 9;
        EDIT_SetValue(m_EmergencyPosMenu.hEditH,m_EmergencyPosMenu.value_show_h);
    }
    else if(6 == m_EmergencyPosMenu.currentSel)
    {
        if(m_EmergencyPosMenu.value_show_d>0)m_EmergencyPosMenu.value_show_d--;
        else  m_EmergencyPosMenu.value_show_d = 9;
        EDIT_SetValue(m_EmergencyPosMenu.hEditD,m_EmergencyPosMenu.value_show_d);   
    }
    else if(7 == m_EmergencyPosMenu.currentSel)
    {
        if(m_EmergencyPosMenu.value_show_s>0)m_EmergencyPosMenu.value_show_s--;
        else  m_EmergencyPosMenu.value_show_s = 9;
        EDIT_SetValue(m_EmergencyPosMenu.hEditS,m_EmergencyPosMenu.value_show_s);
    }
    
    m_value = m_EmergencyPosMenu.value_show_h*100 + m_EmergencyPosMenu.value_show_d*10 + m_EmergencyPosMenu.value_show_s;
    PROGBAR_SetValue(m_EmergencyPosMenu.hProg,m_value);
}

static void WinEmergencyPosNumberShowStyle(void)
{
    m_EmergencyPosMenu.cTimerCnt++;
	if(5 == m_EmergencyPosMenu.currentSel)
	{
	    if(m_EmergencyPosMenu.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_EmergencyPosMenu.hEditH);
	    }
		else
		{
			EDIT_SetDecMode(m_EmergencyPosMenu.hEditH,m_EmergencyPosMenu.value_show_h,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(6 == m_EmergencyPosMenu.currentSel)
	{
	    if(m_EmergencyPosMenu.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_EmergencyPosMenu.hEditD);
	    }
		else
		{
			EDIT_SetDecMode(m_EmergencyPosMenu.hEditD,m_EmergencyPosMenu.value_show_d,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(7 == m_EmergencyPosMenu.currentSel)
	{
	    if(m_EmergencyPosMenu.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_EmergencyPosMenu.hEditS);
	    }
		else
		{
			EDIT_SetDecMode(m_EmergencyPosMenu.hEditS,m_EmergencyPosMenu.value_show_s,0,9,0,GUI_EDIT_NORMAL);
		}

	}
}

static void _WinEmergencyPosCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
    switch (pMsg->MsgId)
    {
        case WM_TIMER:
            WM_RestartTimer(pMsg->Data.v, 500);
            WinEmergencyPosNumberShowStyle();
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
            {
                case GUI_KEY_UP:
                    _WinEmergencyPosKeyUp();
                    break;
                case GUI_KEY_DOWN:
                    _WinEmergencyPosKeyDown(GUI_KEY_DOWN);
                    break;
                case GUI_KEY_ENTER:
                    _WinEmergencyPosKeyEnter();
                    break;
            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}

static void _WinEmergencyPosCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    unsigned char    i = 0;

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	memcpy(strShow,pTitle,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_EmergencyPosMenu.hFrame, 0);             
    hWin = WM_GetFirstChild(m_EmergencyPosMenu.hFrame);       
    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
#if 1     
	m_EmergencyPosMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EmergencyPosMenu.hImage_CB_1,&bmComBack_1);
	m_EmergencyPosMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EmergencyPosMenu.hImage_CB_2,&bmComBack_2);
    #endif
	m_EmergencyPosMenu.hButtonEditH   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+48-6-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_EmergencyPosMenu.hButtonEditH,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditH,1);
	m_EmergencyPosMenu.hButtonEditD   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+48+50-6-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_EmergencyPosMenu.hButtonEditD,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditD,0);
	m_EmergencyPosMenu.hButtonEditS   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+48+100-6-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_EmergencyPosMenu.hButtonEditS,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_EmergencyPosMenu.hButtonEditS,0);
    #if 1
    m_EmergencyPosMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+10-6, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EmergencyPosMenu.hEditH     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+48-6      , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_EmergencyPosMenu.hEditD     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+48+50-6   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_EmergencyPosMenu.hEditS     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+48+100-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_EmergencyPosMenu.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET+30-6   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60, 162+2, 19+2, hWin,  NULL, WM_CF_SHOW);
    m_EmergencyPosMenu.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EmergencyPosMenu.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EmergencyPosMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+13-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+50, 180, 52, hWin, WM_CF_SHOW, NULL, NULL, NULL);
   #endif
    header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_EmergencyPosMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
		
    #if 1
    hWin = m_EmergencyPosMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_BLUE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    hWin = m_EmergencyPosMenu.hEditH;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_EmergencyPosMenu.value_show_h = dataStructInterface.emergency_pos/100;
    EDIT_SetDecMode(hWin,m_EmergencyPosMenu.value_show_h,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_EmergencyPosMenu.hEditD;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_EmergencyPosMenu.value_show_d = (dataStructInterface.emergency_pos%100)/10;
    EDIT_SetDecMode(hWin,m_EmergencyPosMenu.value_show_d,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_EmergencyPosMenu.hEditS;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_EmergencyPosMenu.value_show_s = (dataStructInterface.emergency_pos%100)%10;
    EDIT_SetDecMode(hWin,m_EmergencyPosMenu.value_show_s,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_EmergencyPosMenu.hProg;
    PROGBAR_SetText(hWin,"");
    PROGBAR_SetMinMax(hWin,0,100);
    PROGBAR_SetValue(hWin,(dataStructInterface.emergency_pos));
	PROGBAR_SetSkin(hWin, _ProgOwnerSkin2);
    StrShowClear();
    enc_unicode_to_utf8_str("0 %",strShow,STRSHOWBUF_SIZE);
    hWin = m_EmergencyPosMenu.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
		
    StrShowClear();
    enc_unicode_to_utf8_str("100 %",strShow,STRSHOWBUF_SIZE);
    hWin = m_EmergencyPosMenu.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
		
    #endif
	
    #if 1
    hWin = m_EmergencyPosMenu.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 6);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw3);
	LISTBOX_SetSel(hWin, -1);
    for(i=0;i<INFO_MENU_SAVE_NUM;i++)
    {
        StrShowClear();
        if(LANGUAGE_CN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_CN[i],strShow,STRSHOWBUF_SIZE);
        }
        else if(LANGUAGE_EN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_EN[i],strShow,STRSHOWBUF_SIZE);
        }
        LISTBOX_AddString(hWin, strShow);
    }
	m_EmergencyPosMenu.hTimer = WM_CreateTimer(WM_HBKWIN,0,500,0);
    WM_SetCallback(WM_HBKWIN, _WinEmergencyPosCallback);
    WM_SetFocus(WM_HBKWIN);
    #endif
}

static void _WinEmergencyPosDestroy(void *p)
{
			WM_DeleteWindow(m_EmergencyPosMenu.hImage_CB_1);      
			WM_DeleteWindow(m_EmergencyPosMenu.hImage_CB_2);      
			WM_DeleteWindow(m_EmergencyPosMenu.hTextHead);        
			WM_DeleteWindow(m_EmergencyPosMenu.hEditH);  
			WM_DeleteWindow(m_EmergencyPosMenu.hEditD);  
			WM_DeleteWindow(m_EmergencyPosMenu.hEditS);  
			WM_DeleteWindow(m_EmergencyPosMenu.hProg);            
			WM_DeleteWindow(m_EmergencyPosMenu.hTextMin);         
			WM_DeleteWindow(m_EmergencyPosMenu.hTextMax);         
			WM_DeleteWindow(m_EmergencyPosMenu.hList);            
			WM_DeleteWindow(m_EmergencyPosMenu.hImageBack);       
			WM_DeleteWindow(m_EmergencyPosMenu.hButtonEditH);     
			WM_DeleteWindow(m_EmergencyPosMenu.hButtonEditD);     
			WM_DeleteWindow(m_EmergencyPosMenu.hButtonEditS);     
	WM_DeleteTimer(m_EmergencyPosMenu.hTimer);  
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_EmergencyPosMenu, 0, sizeof(m_EmergencyPosMenu));
}


WIN_INFO_TYPE g_WinEmergencyPosMenu = {                        
    &m_EmergencyPosMenu.hFrame,
    _WinEmergencyPosCreate,
    _WinEmergencyPosDestroy
};

#endif


typedef struct {
    GUI_HWIN  hFrame;
		GUI_HWIN hImage_CB_1;        
		GUI_HWIN hImage_CB_2;        
    GUI_HWIN  hTextHead;         
    GUI_HWIN  hBtnBitMap;        
    GUI_HWIN  hEdit;             
    GUI_HWIN  hProg;             
    GUI_HWIN  hTextUnit;         
    GUI_HWIN  hTextMin;          
    GUI_HWIN  hTextMax;          
		GUI_HWIN  hButtonEdit;       
	GUI_HWIN  hImageBack;          
}EMERGENCY_SPEED_CLOSE_MENU_TYPE;
static EMERGENCY_SPEED_CLOSE_MENU_TYPE m_EmgSpeedCloseMenu = {0};                        
void _WinEmgSpeedCloseKeyEnter(void )
{
	eeprom.Save_emg_speed_close_flag=1;
    WIN_Exit(0);
}

void _WinEmgSpeedCloseKeyDown(void )
{
    switch(dataStructInterface.emg_speed_close)
    {
        case rang1: dataStructInterface.emg_speed_close = rang2;
        break;
        case rang2: dataStructInterface.emg_speed_close = rang3;
        break;
        case rang3: dataStructInterface.emg_speed_close = rang4;
        break;
        case rang4: dataStructInterface.emg_speed_close = rang5;
        break;
        case rang5: dataStructInterface.emg_speed_close = rang6;
        break;
        case rang6: dataStructInterface.emg_speed_close = rang7;
        break;
        case rang7: dataStructInterface.emg_speed_close = rang1;
        break;
        default :   dataStructInterface.emg_speed_close = rang1;
        break;
    }
    eeprom.emg_speed_close_ee=dataStructInterface.emg_speed_close;
    EDIT_SetValue(m_EmgSpeedCloseMenu.hEdit,dataStructInterface.emg_speed_close);
    PROGBAR_SetValue(m_EmgSpeedCloseMenu.hProg,dataStructInterface.emg_speed_close);
		
}

void _WinEmgSpeedCloseKeyUp(void)
{
    switch(dataStructInterface.emg_speed_close)
    {
        case rang1: dataStructInterface.emg_speed_close = rang7;
        break;
        case rang2: dataStructInterface.emg_speed_close = rang1;
        break;
        case rang3: dataStructInterface.emg_speed_close = rang2;
        break;
        case rang4: dataStructInterface.emg_speed_close = rang3;
        break;
        case rang5: dataStructInterface.emg_speed_close = rang4;
        break;
        case rang6: dataStructInterface.emg_speed_close = rang5;
        break;
        case rang7: dataStructInterface.emg_speed_close = rang6;
        break;
        default :   dataStructInterface.emg_speed_close = rang7;
        break;
    }
    eeprom.emg_speed_close_ee=dataStructInterface.emg_speed_close;
    EDIT_SetValue(m_EmgSpeedCloseMenu.hEdit,dataStructInterface.emg_speed_close);
    PROGBAR_SetValue(m_EmgSpeedCloseMenu.hProg,dataStructInterface.emg_speed_close);
}

void _WinEmgSpeedCloseRefresh(void)
{
	char str[MAX_INFO_CHAR];
	             
    sprintf(str," 关               %d rpm ",dataStructInterface.emg_speed_close);
    strcpy(menuSaftyCn[3],str);
    strcpy(menuSaftyEn[3],str);
	
}
static void _WinEmgSpeedCloseCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinEmgSpeedCloseKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinEmgSpeedCloseKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinEmgSpeedCloseKeyEnter();
				_WinEmgSpeedCloseRefresh();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinEmgSpeedCloseCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	memcpy(strShow,pTitle,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_EmgSpeedCloseMenu.hFrame, 0);            

    hWin = WM_GetFirstChild(m_EmgSpeedCloseMenu.hFrame);             
       GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	WIDGET_SetDefaultEffect_None();
#if 1       
	m_EmgSpeedCloseMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EmgSpeedCloseMenu.hImage_CB_1,&bmComBack_1);	
	m_EmgSpeedCloseMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EmgSpeedCloseMenu.hImage_CB_2,&bmComBack_2);
    #endif
	m_EmgSpeedCloseMenu.hButtonEdit   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+80-5, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 70, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_EmgSpeedCloseMenu.hButtonEdit,SKIN_Three_NUMBER_Button);
    BUTTON_SetPressed(m_EmgSpeedCloseMenu.hButtonEdit,1);
    m_EmgSpeedCloseMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EmgSpeedCloseMenu.hTextUnit  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+10, 20*2, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EmgSpeedCloseMenu.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EmgSpeedCloseMenu.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
   m_EmgSpeedCloseMenu.hEdit      = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+80, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 60, 40, hWin, WM_CF_SHOW, NULL , NULL, 3);
    m_EmgSpeedCloseMenu.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, PER_CM_OFFSET*4.5, 23, hWin,  NULL, WM_CF_SHOW);
    header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_EmgSpeedCloseMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
   TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, (char *)strShow);
    hWin = m_EmgSpeedCloseMenu.hEdit;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_ORANGE);
    EDIT_SetDecMode(hWin,dataStructInterface.emg_speed_close,SPEED_MIN,SPEED_MAX,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    close_drive(60,80);
    StrShowClear();
    enc_unicode_to_utf8_str("rpm",strShow,STRSHOWBUF_SIZE);
    memcpy(strShow,"rpm",STRSHOWBUF_SIZE);
    hWin = m_EmgSpeedCloseMenu.hTextUnit;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, (char *)strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("20 rpm",strShow,STRSHOWBUF_SIZE);
    memcpy(strShow,"20 rpm",STRSHOWBUF_SIZE);
    hWin = m_EmgSpeedCloseMenu.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, (char *)strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("160 rpm",strShow,STRSHOWBUF_SIZE);
    memcpy(strShow,"160 rpm",STRSHOWBUF_SIZE);
    hWin = m_EmgSpeedCloseMenu.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, (char *)strShow);
    hWin = m_EmgSpeedCloseMenu.hProg;
    PROGBAR_SetText(m_EmgSpeedCloseMenu.hProg,"");
		#ifdef  CE12
    PROGBAR_SetMinMax(hWin,/*20*/05,/*160*/40);   
		#endif
		#ifdef  DE13
    PROGBAR_SetMinMax(hWin,10,80);   
		#endif
		#ifdef  EE13
    PROGBAR_SetMinMax(hWin,20,160);   
		#endif
    PROGBAR_SetValue(m_EmgSpeedCloseMenu.hProg,dataStructInterface.emg_speed_close);

    WM_SetCallback(WM_HBKWIN, _WinEmgSpeedCloseCallback);
    WM_SetFocus(WM_HBKWIN);
}


static void _WinEmgSpeedCloseDestroy(void *p)
{
		WM_DeleteWindow(m_EmgSpeedCloseMenu.hImage_CB_1);    
		WM_DeleteWindow(m_EmgSpeedCloseMenu.hImage_CB_2);    
    WM_DeleteWindow(m_EmgSpeedCloseMenu.hTextHead);      
    WM_DeleteWindow(m_EmgSpeedCloseMenu.hBtnBitMap);     
    WM_DeleteWindow(m_EmgSpeedCloseMenu.hEdit);          
    WM_DeleteWindow(m_EmgSpeedCloseMenu.hProg);          
    WM_DeleteWindow(m_EmgSpeedCloseMenu.hTextUnit);      
    WM_DeleteWindow(m_EmgSpeedCloseMenu.hTextMin);       
    WM_DeleteWindow(m_EmgSpeedCloseMenu.hTextMax);       
		WM_DeleteWindow(m_EmgSpeedCloseMenu.hButtonEdit);    
		WM_DeleteWindow(m_EmgSpeedCloseMenu.hImageBack);     
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_EmgSpeedCloseMenu, 0, sizeof(m_EmgSpeedCloseMenu));
}

void _WinEmgSpeedCloseInterface(void *val)
{
}


WIN_INFO_TYPE g_WinEmgSpeedCloseMenu = {                        
    &m_EmgSpeedCloseMenu.hFrame,
    _WinEmgSpeedCloseCreate,
    _WinEmgSpeedCloseDestroy
};


typedef struct {
    GUI_HWIN  hFrame;
		GUI_HWIN hImage_CB_1;       
		GUI_HWIN hImage_CB_2;       
    GUI_HWIN  hTextHead;        
    GUI_HWIN  hBtnBitMap;       
    GUI_HWIN  hEdit;            
    GUI_HWIN  hProg;            
    GUI_HWIN  hTextUnit;        
    GUI_HWIN  hTextMin;         
    GUI_HWIN  hTextMax;         
		GUI_HWIN  hButtonEdit;      
	GUI_HWIN  hImageBack;         
}EMERGENCY_SPEED_OPEN_MENU_TYPE;
static EMERGENCY_SPEED_OPEN_MENU_TYPE m_EmgSpeedOpenMenu = {0};                         
void _WinEmgSpeedOpenKeyEnter(void )
{
	eeprom.flag_speed_open=1;
    WIN_Exit(0);
}

void _WinEmgSpeedOpenKeyDown(void )
{
    switch(dataStructInterface.emg_speed_open)
    {
        case rang1: dataStructInterface.emg_speed_open = rang2;
        break;
        case rang2: dataStructInterface.emg_speed_open = rang3;
        break;
        case rang3: dataStructInterface.emg_speed_open = rang4;
        break;
        case rang4: dataStructInterface.emg_speed_open = rang5;
        break;
        case rang5: dataStructInterface.emg_speed_open = rang6;
        break;
        case rang6: dataStructInterface.emg_speed_open = rang7;
        break;
					case rang7: dataStructInterface.emg_speed_open = rang1;
        break;
        default :   dataStructInterface.emg_speed_open = rang1;
        break;
    }
		eeprom.emg_speed_open_ee=dataStructInterface.emg_speed_open;
    EDIT_SetValue(m_EmgSpeedOpenMenu.hEdit,dataStructInterface.emg_speed_open);
    PROGBAR_SetValue(m_EmgSpeedOpenMenu.hProg,dataStructInterface.emg_speed_open);
}

void _WinEmgSpeedOpenKeyUp(void)
{
    switch(dataStructInterface.emg_speed_open)
    {
        case rang1: dataStructInterface.emg_speed_open = rang7;
        break;
        case rang2: dataStructInterface.emg_speed_open = rang1;
        break;
        case rang3: dataStructInterface.emg_speed_open = rang2;
        break;
        case rang4: dataStructInterface.emg_speed_open = rang3;
        break;
        case rang5: dataStructInterface.emg_speed_open = rang4;
        break;
        case rang6: dataStructInterface.emg_speed_open = rang5;
        break;
        case rang7: dataStructInterface.emg_speed_open = rang6;
        break;
        default :   dataStructInterface.emg_speed_open = rang7;
        break;
    }
    eeprom.emg_speed_open_ee=dataStructInterface.emg_speed_open;
    EDIT_SetValue(m_EmgSpeedOpenMenu.hEdit,dataStructInterface.speed_open);
    PROGBAR_SetValue(m_EmgSpeedOpenMenu.hProg,dataStructInterface.speed_open);
}

void __WinEmgSpeedOpenRefresh(void)
{
	char str[MAX_INFO_CHAR];
	              
    sprintf(str," 开               %d rpm ",dataStructInterface.emg_speed_open);
    strcpy(menuSaftyCn[4],str);
    strcpy(menuSaftyEn[4],str);
	eeprom.Save_emg_speed_open_flag=1;
	
}
static void _WinEmgSpeedOpenCallback(WM_MESSAGE * pMsg)
{
    int id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinEmgSpeedOpenKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinEmgSpeedOpenKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinEmgSpeedOpenKeyEnter();
				__WinEmgSpeedOpenRefresh();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinEmgSpeedOpenCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	memcpy(strShow,pTitle,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_EmgSpeedOpenMenu.hFrame, 0);             
    hWin = WM_GetFirstChild(m_EmgSpeedOpenMenu.hFrame);            
        GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	WIDGET_SetDefaultEffect_None();
#if 1       
	m_EmgSpeedOpenMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EmgSpeedOpenMenu.hImage_CB_1,&bmComBack_1);	
	m_EmgSpeedOpenMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EmgSpeedOpenMenu.hImage_CB_2,&bmComBack_2);
    #endif
	m_EmgSpeedOpenMenu.hButtonEdit   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+80-5, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 70, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_EmgSpeedOpenMenu.hButtonEdit,SKIN_Three_NUMBER_Button);
    BUTTON_SetPressed(m_EmgSpeedOpenMenu.hButtonEdit,1);
    m_EmgSpeedOpenMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EmgSpeedOpenMenu.hTextUnit  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+10, 20*2, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EmgSpeedOpenMenu.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EmgSpeedOpenMenu.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
   m_EmgSpeedOpenMenu.hEdit      = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+80, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 60, 40, hWin, WM_CF_SHOW, NULL , NULL, 3);
    m_EmgSpeedOpenMenu.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+80, PER_CM_OFFSET*4.5, 23, hWin,  NULL, WM_CF_SHOW);
   header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_EmgSpeedOpenMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, (char *)strShow);
    hWin = m_EmgSpeedOpenMenu.hEdit;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_ORANGE);
    EDIT_SetDecMode(hWin,dataStructInterface.emg_speed_open,SPEED_MIN,SPEED_MAX,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
			open_drive(60,80);
    StrShowClear();
    enc_unicode_to_utf8_str("rpm",strShow,STRSHOWBUF_SIZE);
		 memcpy((char *)strShow,"rpm",STRSHOWBUF_SIZE);
    hWin = m_EmgSpeedOpenMenu.hTextUnit;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, (char *)strShow);
    StrShowClear();
    enc_unicode_to_utf8_str("20 rpm",strShow,STRSHOWBUF_SIZE);
		memcpy((char *)strShow,"20 rpm",STRSHOWBUF_SIZE);
    hWin = m_EmgSpeedOpenMenu.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, (char *)strShow);

    StrShowClear();
    enc_unicode_to_utf8_str("160 rpm",strShow,STRSHOWBUF_SIZE);//WY change speed NJ
		memcpy((char *)strShow,"160 rpm",STRSHOWBUF_SIZE);
    hWin = m_EmgSpeedOpenMenu.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, (char *)strShow);
    hWin = m_EmgSpeedOpenMenu.hProg;
    PROGBAR_SetText(m_EmgSpeedOpenMenu.hProg,"");
		#ifdef  CE12
    PROGBAR_SetMinMax(hWin,/*20*/05,/*160*/40);   
		#endif
		#ifdef  DE13
    PROGBAR_SetMinMax(hWin,10,80);   
		#endif
		#ifdef  EE13
    PROGBAR_SetMinMax(hWin,20,160);   
		#endif
    PROGBAR_SetValue(m_EmgSpeedOpenMenu.hProg,dataStructInterface.emg_speed_open);
    WM_SetCallback(WM_HBKWIN, _WinEmgSpeedOpenCallback);
    WM_SetFocus(WM_HBKWIN);
}


static void _WinEmgSpeedOpenDestroy(void *p)
{	
		WM_DeleteWindow(m_EmgSpeedOpenMenu.hImage_CB_1);      
		WM_DeleteWindow(m_EmgSpeedOpenMenu.hImage_CB_2);      
    WM_DeleteWindow(m_EmgSpeedOpenMenu.hTextHead);        
    WM_DeleteWindow(m_EmgSpeedOpenMenu.hBtnBitMap);       
    WM_DeleteWindow(m_EmgSpeedOpenMenu.hEdit);            
    WM_DeleteWindow(m_EmgSpeedOpenMenu.hProg);            
    WM_DeleteWindow(m_EmgSpeedOpenMenu.hTextUnit);        
    WM_DeleteWindow(m_EmgSpeedOpenMenu.hTextMin);         
    WM_DeleteWindow(m_EmgSpeedOpenMenu.hTextMax);         
		WM_DeleteWindow(m_EmgSpeedOpenMenu.hButtonEdit);      
		WM_DeleteWindow(m_EmgSpeedOpenMenu.hImageBack);       
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_EmgSpeedOpenMenu, 0, sizeof(m_EmgSpeedOpenMenu));
}

void _WinEmgSpeedOpenInterface(void *val)
{

}

WIN_INFO_TYPE g_WinEmgSpeedOpenMenu = {                        
    &m_EmgSpeedOpenMenu.hFrame,
    _WinEmgSpeedOpenCreate,
    _WinEmgSpeedOpenDestroy
};


typedef struct {
    GUI_HWIN  hFrame; 
		GUI_HWIN hImage_CB_1;             
		GUI_HWIN hImage_CB_2;             
    GUI_HWIN  hTextHead;              
    GUI_HWIN  hEditH;    
    GUI_HWIN  hEditL;    
    GUI_HWIN  hProg;                  
    GUI_HWIN  hTextMin;               
    GUI_HWIN  hTextMax;               
    GUI_HWIN  hList;                  
    unsigned char currentSel;        
    unsigned char value_show_h;       
    unsigned char value_show_l;       
    unsigned char max;                
		GUI_HWIN  hImageBack;             
		GUI_HWIN  hButtonEditH;           
		GUI_HWIN  hButtonEditL;           
		GUI_HWIN  hTimer;                 
		unsigned char cTimerCnt;          
}WIN_PENCENTAGE_TYPE;
static WIN_PENCENTAGE_TYPE m_PercentageMenu = {0};                        
static unsigned short *mp_return_value=0;
static unsigned short  m_return_value=0;

void _WinPercentageKeyEnter(void )
{
    unsigned char m_value=0;
    if(0 == m_PercentageMenu.currentSel)
    {
        EDIT_SetTextColor(m_PercentageMenu.hEditH,EDIT_CI_ENABELD,GUI_ORANGE);
        m_PercentageMenu.currentSel = 4;
    }
    else if(1 == m_PercentageMenu.currentSel)
    {
        EDIT_SetTextColor(m_PercentageMenu.hEditL,EDIT_CI_ENABELD,GUI_ORANGE);
        m_PercentageMenu.currentSel = 5;
    }
    else if(2 == m_PercentageMenu.currentSel)
    {
        m_value = m_PercentageMenu.value_show_h*10 + m_PercentageMenu.value_show_l;
        if(m_value > 100 ) m_value = 100;
        WIN_Exit(1);
    }
    else if(3 == m_PercentageMenu.currentSel)
    {
        WIN_Exit(0);
    }
    else if(4 == m_PercentageMenu.currentSel)
    {
        EDIT_SetTextColor(m_PercentageMenu.hEditH,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_PercentageMenu.hEditL,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_PercentageMenu.hButtonEditH,0);
		BUTTON_SetPressed(m_PercentageMenu.hButtonEditL,1);
        m_PercentageMenu.currentSel = 5;
		EDIT_SetDecMode(m_PercentageMenu.hEditH,m_PercentageMenu.value_show_h,0,9,0,GUI_EDIT_NORMAL);
    }
    else if(5 == m_PercentageMenu.currentSel)
    {
        EDIT_SetTextColor(m_PercentageMenu.hEditL,EDIT_CI_ENABELD,GUI_BLUE);
        LISTBOX_SetSel(m_PercentageMenu.hList,0);
        m_PercentageMenu.currentSel = 2;
        BUTTON_SetPressed(m_PercentageMenu.hButtonEditL,0);
		EDIT_SetDecMode(m_PercentageMenu.hEditL,m_PercentageMenu.value_show_l,0,9,0,GUI_EDIT_NORMAL);	
    }
    m_value = m_PercentageMenu.value_show_h*10 + m_PercentageMenu.value_show_l;
    PROGBAR_SetValue(m_PercentageMenu.hProg,m_value);
}

void _WinPercentageKeyDown(void)
{
    unsigned char m_value=0;
    if(0 == m_PercentageMenu.currentSel)
    {
			BUTTON_SetPressed(m_PercentageMenu.hButtonEditH,0);
		BUTTON_SetPressed(m_PercentageMenu.hButtonEditL,1);
        m_PercentageMenu.currentSel = 1;
    }
    else if(1 == m_PercentageMenu.currentSel)
    {
			BUTTON_SetPressed(m_PercentageMenu.hButtonEditL,0);
        LISTBOX_SetSel(m_PercentageMenu.hList,0);
        m_PercentageMenu.currentSel = 2;
    }
     else if(2 == m_PercentageMenu.currentSel)
    {
			LISTBOX_SetSel(m_PercentageMenu.hList,1);
        m_PercentageMenu.currentSel = 3;
    }
    else if(3 == m_PercentageMenu.currentSel)
    {
			LISTBOX_SetSel(m_PercentageMenu.hList,-1);
        BUTTON_SetPressed(m_PercentageMenu.hButtonEditH,1);
        m_PercentageMenu.currentSel = 0;
    }
    else if(4 == m_PercentageMenu.currentSel)
    {
			     m_PercentageMenu.value_show_h++;
        if(m_PercentageMenu.value_show_h>9) m_PercentageMenu.value_show_h = 0;
        EDIT_SetValue(m_PercentageMenu.hEditH,m_PercentageMenu.value_show_h);
			}
    else if(5 == m_PercentageMenu.currentSel)
    {
			       m_PercentageMenu.value_show_l++;
        if(m_PercentageMenu.value_show_l>9) m_PercentageMenu.value_show_l = 0;
        EDIT_SetValue(m_PercentageMenu.hEditL,m_PercentageMenu.value_show_l);
			}
    m_value = m_PercentageMenu.value_show_h*10 + m_PercentageMenu.value_show_l ;
    PROGBAR_SetValue(m_PercentageMenu.hProg,m_value);
}

void _WinPercentageKeyUp(void)
{
    unsigned char m_value=0;
    if(0 == m_PercentageMenu.currentSel)
    {
			BUTTON_SetPressed(m_PercentageMenu.hButtonEditH,0);
        LISTBOX_SetSel(m_PercentageMenu.hList,1);
        m_PercentageMenu.currentSel = 3;
    }
    else if(1 == m_PercentageMenu.currentSel)
    {
			  BUTTON_SetPressed(m_PercentageMenu.hButtonEditH,1);
		BUTTON_SetPressed(m_PercentageMenu.hButtonEditL,0);
        m_PercentageMenu.currentSel = 0;
    }
     else if(2 == m_PercentageMenu.currentSel)
    {
			LISTBOX_SetSel(m_PercentageMenu.hList,-1);
        BUTTON_SetPressed(m_PercentageMenu.hButtonEditL,1);
        m_PercentageMenu.currentSel = 1;
    }
    else if(3 == m_PercentageMenu.currentSel)
    {
			LISTBOX_SetSel(m_PercentageMenu.hList,0);
        m_PercentageMenu.currentSel = 2;
    }
    else if(4 == m_PercentageMenu.currentSel)
    {
			       if(m_PercentageMenu.value_show_h>0)m_PercentageMenu.value_show_h--;
        else  m_PercentageMenu.value_show_h = 9;
        EDIT_SetValue(m_PercentageMenu.hEditH,m_PercentageMenu.value_show_h);
			}
    else if(5 == m_PercentageMenu.currentSel)
    {
        if(m_PercentageMenu.value_show_l>0)m_PercentageMenu.value_show_l--;
        else  m_PercentageMenu.value_show_l = 9;
        EDIT_SetValue(m_PercentageMenu.hEditL,m_PercentageMenu.value_show_l);
			}
    m_value = m_PercentageMenu.value_show_h*10 + m_PercentageMenu.value_show_l;
    PROGBAR_SetValue(m_PercentageMenu.hProg,m_value);
}
static void WinPercentageNumberShowStyle(void)
{
    m_PercentageMenu.cTimerCnt++;
	if(4 == m_PercentageMenu.currentSel)
	{
	    if(m_PercentageMenu.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_PercentageMenu.hEditH);
	    }
		else
		{
			EDIT_SetDecMode(m_PercentageMenu.hEditH,m_PercentageMenu.value_show_h,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(5 == m_PercentageMenu.currentSel)
	{
	    if(m_PercentageMenu.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_PercentageMenu.hEditL);
	    }
		else
		{
			EDIT_SetDecMode(m_PercentageMenu.hEditL,m_PercentageMenu.value_show_l,0,9,0,GUI_EDIT_NORMAL);
		}

	}
}

static void _WinPercentageCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
    switch (pMsg->MsgId)
    {
			 case WM_TIMER:
        WM_RestartTimer(pMsg->Data.v, 1000);
		WinPercentageNumberShowStyle();
        break;
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinPercentageKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinPercentageKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinPercentageKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinPercentageCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);
    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;
    unsigned char    m_max = *(pMenu->data->menuattri);
    unsigned char    i = 0;
    if (NULL == pTitle) pTitle = "";
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	memcpy(strShow,pTitle,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_PercentageMenu.hFrame, 0);             
    hWin = WM_GetFirstChild(m_PercentageMenu.hFrame);   
		GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
#if 1       
	m_PercentageMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_PercentageMenu.hImage_CB_1,&bmComBack_1);	
	m_PercentageMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_PercentageMenu.hImage_CB_2,&bmComBack_2);
    #endif
#if 1
	m_PercentageMenu.hButtonEditH   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+48-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_PercentageMenu.hButtonEditH,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_PercentageMenu.hButtonEditH,1);
	m_PercentageMenu.hButtonEditL   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+48+50-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_PercentageMenu.hButtonEditL,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_PercentageMenu.hButtonEditL,0);
#endif
    m_PercentageMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_PercentageMenu.hEditH     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+48      , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_PercentageMenu.hEditL     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+48+50   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_PercentageMenu.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET+30   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60, 162+2, 19+2, hWin,  NULL, WM_CF_SHOW);
    m_PercentageMenu.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_PercentageMenu.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_PercentageMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+13, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+50, 180, 52, hWin, WM_CF_SHOW, NULL, NULL, NULL);
   
#if 1
header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
hWin = m_PercentageMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    hWin = m_PercentageMenu.hEditH;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_PercentageMenu.value_show_h = *(pMenu->data->menusel)/10;
    EDIT_SetDecMode(hWin,m_PercentageMenu.value_show_h,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_PercentageMenu.hEditL;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_PercentageMenu.value_show_l = *(pMenu->data->menusel)%10;
    EDIT_SetDecMode(hWin,m_PercentageMenu.value_show_l,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_PercentageMenu.hProg;
    PROGBAR_SetText(hWin,"");
    PROGBAR_SetMinMax(hWin,0,m_max);
    PROGBAR_SetValue(hWin,*(pMenu->data->menusel));
	PROGBAR_SetSkin(hWin, _ProgOwnerSkin2);
    StrShowClear();
    enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
    hWin = m_PercentageMenu.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str(pContentEn,strShow,STRSHOWBUF_SIZE);
    hWin = m_PercentageMenu.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    hWin = m_PercentageMenu.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 6);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw3);
	LISTBOX_SetSel(hWin, -1);
	#endif
		#if 1
		    for(i=0;i<INFO_MENU_SAVE_NUM;i++)
    {
        StrShowClear();
        if(LANGUAGE_CN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_CN[i],strShow,STRSHOWBUF_SIZE);
        }
        else if(LANGUAGE_EN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_EN[i],strShow,STRSHOWBUF_SIZE);
        }
        LISTBOX_AddString(hWin, strShow);
    }
    m_PercentageMenu.max       = m_max;
    mp_return_value = pMenu->data->menusel;

    m_PercentageMenu.hTimer = WM_CreateTimer(WM_HBKWIN,0,1000,0);

    WM_SetCallback(WM_HBKWIN, _WinPercentageCallback);
    WM_SetFocus(WM_HBKWIN);
		#endif
}

static void _WinPercentageDestroy(void *p)
{
    m_return_value = m_PercentageMenu.value_show_h*10 + m_PercentageMenu.value_show_l;
    if(m_return_value > m_PercentageMenu.max ) m_return_value = m_PercentageMenu.max;	
		WM_DeleteWindow(m_PercentageMenu.hImage_CB_1);          
		WM_DeleteWindow(m_PercentageMenu.hImage_CB_2);          
    WM_DeleteWindow(m_PercentageMenu.hTextHead);            
    WM_DeleteWindow(m_PercentageMenu.hEditH);       
    WM_DeleteWindow(m_PercentageMenu.hEditL); 
    WM_DeleteWindow(m_PercentageMenu.hProg);                
    WM_DeleteWindow(m_PercentageMenu.hTextMin);             
    WM_DeleteWindow(m_PercentageMenu.hTextMax);             
    WM_DeleteWindow(m_PercentageMenu.hList);                
		WM_DeleteWindow(m_PercentageMenu.hImageBack);           
		WM_DeleteWindow(m_PercentageMenu.hButtonEditH);         
		WM_DeleteWindow(m_PercentageMenu.hButtonEditL);         
		WM_DeleteTimer(m_PercentageMenu.hTimer);                
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_PercentageMenu, 0, sizeof(m_PercentageMenu));
}

void _WinPercentageInterface(void *val)
{
    *mp_return_value = m_return_value;
}


WIN_INFO_TYPE g_WinPercentageMenu = {                      
    &m_PercentageMenu.hFrame,
    _WinPercentageCreate,
    _WinPercentageDestroy
};

typedef struct {
    GUI_HWIN  hFrame;
		GUI_HWIN hImage_CB_1;      
		GUI_HWIN hImage_CB_2;      
    GUI_HWIN  hTextHead;       
    GUI_HWIN  hEditH; 
    GUI_HWIN  hEditD;          
    GUI_HWIN  hEditL;  
    GUI_HWIN  hProg;           
    GUI_HWIN  hTextMin;        
    GUI_HWIN  hTextMax;        
    GUI_HWIN  hList;           
    unsigned char currentSel;  
    unsigned char value_show_h;
    unsigned char value_show_d;
    unsigned char value_show_l;
    unsigned short max;        
		GUI_HWIN  hImageBack;      
	GUI_HWIN  hButtonEditH;      
	GUI_HWIN  hButtonEditD;      
	GUI_HWIN  hButtonEditS;      
	GUI_HWIN  hTimer;            
	unsigned char cTimerCnt;     
}WIN_COMMON_THREE_NUM_TYPE;
static WIN_COMMON_THREE_NUM_TYPE m_CommonThreeNum = {0};                        
static unsigned short *mp_return_value_three_num=0;
static unsigned short  m_return_value_three_num=0;

void _WinComThreeNumKeyEnter(void )
{
    unsigned short m_value=0;
    if(0 == m_CommonThreeNum.currentSel)
    {
			      m_CommonThreeNum.currentSel = 5;
		EDIT_SetTextColor(m_CommonThreeNum.hEditH,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(1 == m_CommonThreeNum.currentSel)
    {
			     m_CommonThreeNum.currentSel = 6;
		EDIT_SetTextColor(m_CommonThreeNum.hEditD,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(2 == m_CommonThreeNum.currentSel)
    {
			     m_CommonThreeNum.currentSel = 7;
		EDIT_SetTextColor(m_CommonThreeNum.hEditL,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(3 == m_CommonThreeNum.currentSel)
    {
			        m_value = m_CommonThreeNum.value_show_h*100 +  m_CommonThreeNum.value_show_d*10 + m_CommonThreeNum.value_show_l;
        if(m_value > 100 ) m_value = 100;
        WIN_Exit(1);
    }
    else if(4 == m_CommonThreeNum.currentSel)
    {
        WIN_Exit(0);
    }
    else if(5 == m_CommonThreeNum.currentSel)
    {
        EDIT_SetTextColor(m_CommonThreeNum.hEditH,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_CommonThreeNum.hEditD,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_CommonThreeNum.hButtonEditH,0);
		BUTTON_SetPressed(m_CommonThreeNum.hButtonEditD,1);
        m_CommonThreeNum.currentSel = 6;
		EDIT_SetDecMode(m_CommonThreeNum.hEditH,m_CommonThreeNum.value_show_h,0,9,0,GUI_EDIT_NORMAL);
    }
    else if(6 == m_CommonThreeNum.currentSel)
    {
        EDIT_SetTextColor(m_CommonThreeNum.hEditD,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_CommonThreeNum.hEditL,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_CommonThreeNum.hButtonEditD,0);
		BUTTON_SetPressed(m_CommonThreeNum.hButtonEditS,1);
        m_CommonThreeNum.currentSel = 7;
		EDIT_SetDecMode(m_CommonThreeNum.hEditD,m_CommonThreeNum.value_show_d,0,9,0,GUI_EDIT_NORMAL);
    }
    else if(7 == m_CommonThreeNum.currentSel)
    {
        EDIT_SetTextColor(m_CommonThreeNum.hEditL,EDIT_CI_ENABELD,GUI_BLUE);
		LISTBOX_SetSel(m_CommonThreeNum.hList,0);
        BUTTON_SetPressed(m_CommonThreeNum.hButtonEditS,0);
        m_CommonThreeNum.currentSel = 3;
        EDIT_SetDecMode(m_CommonThreeNum.hEditL,m_CommonThreeNum.value_show_l,0,9,0,GUI_EDIT_NORMAL);			
    }
    m_value = m_CommonThreeNum.value_show_h*100 + m_CommonThreeNum.value_show_d*10 + m_CommonThreeNum.value_show_l;
    PROGBAR_SetValue(m_CommonThreeNum.hProg,m_value);
}

void _WinComThreeNumKeyDown(void)
{
    unsigned short m_value=0;
    if(0 == m_CommonThreeNum.currentSel)
    {
        BUTTON_SetPressed(m_CommonThreeNum.hButtonEditH,0);
		BUTTON_SetPressed(m_CommonThreeNum.hButtonEditD,1);
        m_CommonThreeNum.currentSel = 1;
    }
    else if(1 == m_CommonThreeNum.currentSel)
    {
        BUTTON_SetPressed(m_CommonThreeNum.hButtonEditD,0);
		BUTTON_SetPressed(m_CommonThreeNum.hButtonEditS,1);
        m_CommonThreeNum.currentSel = 2;
    }
    else if(2 == m_CommonThreeNum.currentSel)
    {
        BUTTON_SetPressed(m_CommonThreeNum.hButtonEditS,0);
        LISTBOX_SetSel(m_CommonThreeNum.hList,0);
        m_CommonThreeNum.currentSel = 3;
    }
     else if(3 == m_CommonThreeNum.currentSel)
    {
        LISTBOX_SetSel(m_CommonThreeNum.hList,1);
        m_CommonThreeNum.currentSel = 4;
    }
    else if(4 == m_CommonThreeNum.currentSel)
    {
        LISTBOX_SetSel(m_CommonThreeNum.hList,-1);
        BUTTON_SetPressed(m_CommonThreeNum.hButtonEditH,1);
        m_CommonThreeNum.currentSel = 0;
    }
    else if(5 == m_CommonThreeNum.currentSel)
    {
        m_CommonThreeNum.value_show_h++;
        if(m_CommonThreeNum.value_show_h>9) m_CommonThreeNum.value_show_h = 0;
        EDIT_SetValue(m_CommonThreeNum.hEditH,m_CommonThreeNum.value_show_h);
    }
    else if(6 == m_CommonThreeNum.currentSel)
    {
        m_CommonThreeNum.value_show_d++;
        if(m_CommonThreeNum.value_show_d>9) m_CommonThreeNum.value_show_d = 0;
        EDIT_SetValue(m_CommonThreeNum.hEditD,m_CommonThreeNum.value_show_d);
    }
    else if(7 == m_CommonThreeNum.currentSel)
    {
        m_CommonThreeNum.value_show_l++;
        if(m_CommonThreeNum.value_show_l>9) m_CommonThreeNum.value_show_l = 0;
        EDIT_SetValue(m_CommonThreeNum.hEditL,m_CommonThreeNum.value_show_l);
    }
    m_value = m_CommonThreeNum.value_show_h*100 + m_CommonThreeNum.value_show_d*10 + m_CommonThreeNum.value_show_l ;
    PROGBAR_SetValue(m_CommonThreeNum.hProg,m_value);
}


void _WinComThreeNumKeyUp(void)
{
    unsigned char m_value=0;
    if(0 == m_CommonThreeNum.currentSel)
    {
			BUTTON_SetPressed(m_CommonThreeNum.hButtonEditH,0);
        LISTBOX_SetSel(m_CommonThreeNum.hList,1);
        m_CommonThreeNum.currentSel = 4;
    }
    else if(1 == m_CommonThreeNum.currentSel)
    {
			BUTTON_SetPressed(m_CommonThreeNum.hButtonEditH,1);
		BUTTON_SetPressed(m_CommonThreeNum.hButtonEditD,0);
        m_CommonThreeNum.currentSel = 0;
    }
    else if(2 == m_CommonThreeNum.currentSel)
    {
			  BUTTON_SetPressed(m_CommonThreeNum.hButtonEditD,1);
		BUTTON_SetPressed(m_CommonThreeNum.hButtonEditS,0);
        m_CommonThreeNum.currentSel = 1;
    }
     else if(3 == m_CommonThreeNum.currentSel)
    {
				LISTBOX_SetSel(m_CommonThreeNum.hList,-1);
        BUTTON_SetPressed(m_CommonThreeNum.hButtonEditS,1);
        m_CommonThreeNum.currentSel = 2;
    }
    else if(4 == m_CommonThreeNum.currentSel)
    {
			LISTBOX_SetSel(m_CommonThreeNum.hList,0);
        m_CommonThreeNum.currentSel = 3;
    }
    else if(5 == m_CommonThreeNum.currentSel)
    {
			   if(m_CommonThreeNum.value_show_h>0)m_CommonThreeNum.value_show_h--;
        else  m_CommonThreeNum.value_show_h = 9;
        EDIT_SetValue(m_CommonThreeNum.hEditH,m_CommonThreeNum.value_show_h);
			}
    else if(6 == m_CommonThreeNum.currentSel)
    {
			 if(m_CommonThreeNum.value_show_d>0)m_CommonThreeNum.value_show_d--;
        else  m_CommonThreeNum.value_show_d = 9;
        EDIT_SetValue(m_CommonThreeNum.hEditD,m_CommonThreeNum.value_show_d);
			}
    else if(7 == m_CommonThreeNum.currentSel)
    {
			 if(m_CommonThreeNum.value_show_l>0)m_CommonThreeNum.value_show_l--;
        else  m_CommonThreeNum.value_show_l = 9;
        EDIT_SetValue(m_CommonThreeNum.hEditL,m_CommonThreeNum.value_show_l);
			}
    m_value = m_CommonThreeNum.value_show_h*100 + m_CommonThreeNum.value_show_d*10 + m_CommonThreeNum.value_show_l;
    PROGBAR_SetValue(m_CommonThreeNum.hProg,m_value);
}

static void WinThreeNumberShowStyle(void)
{
    m_CommonThreeNum.cTimerCnt++;
	if(5 == m_CommonThreeNum.currentSel)
	{
	    if(m_CommonThreeNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonThreeNum.hEditH);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonThreeNum.hEditH,m_CommonThreeNum.value_show_h,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(6 == m_CommonThreeNum.currentSel)
	{
	    if(m_CommonThreeNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonThreeNum.hEditD);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonThreeNum.hEditD,m_CommonThreeNum.value_show_d,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(7 == m_CommonThreeNum.currentSel)
	{
	    if(m_CommonThreeNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonThreeNum.hEditL);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonThreeNum.hEditL,m_CommonThreeNum.value_show_l,0,9,0,GUI_EDIT_NORMAL);
		}

	}
}
static void _WinComThreeNumCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
    switch (pMsg->MsgId)
    {
			 case WM_TIMER:
        WM_RestartTimer(pMsg->Data.v, 1000);
		WinThreeNumberShowStyle();
        break;
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinComThreeNumKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinComThreeNumKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinComThreeNumKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinComThreeNumCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;
    unsigned char    m_max = *(pMenu->data->menuattri);
    unsigned char    i = 0;

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
 memcpy(strShow,pTitle,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_CommonThreeNum.hFrame, 0);             

    hWin = WM_GetFirstChild(m_CommonThreeNum.hFrame); 
    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
#if 1       
	m_CommonThreeNum.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_CommonThreeNum.hImage_CB_1,&bmComBack_1);	
	m_CommonThreeNum.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_CommonThreeNum.hImage_CB_2,&bmComBack_2);
    #endif 
#if 1
m_CommonThreeNum.hButtonEditH   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+48-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonThreeNum.hButtonEditH,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonThreeNum.hButtonEditH,1);
	m_CommonThreeNum.hButtonEditD   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+48+50-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonThreeNum.hButtonEditD,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonThreeNum.hButtonEditD,0);
	m_CommonThreeNum.hButtonEditS   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+48+100-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonThreeNum.hButtonEditS,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonThreeNum.hButtonEditS,0);
    m_CommonThreeNum.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CommonThreeNum.hEditH     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+48      , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonThreeNum.hEditD     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+48+50   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonThreeNum.hEditL     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+48+100   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonThreeNum.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET+30   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60, 162+2, 19+2, hWin,  NULL, WM_CF_SHOW);
    m_CommonThreeNum.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CommonThreeNum.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CommonThreeNum.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+13, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+50, 180, 52, hWin, WM_CF_SHOW, NULL, NULL, NULL);
    
#endif
#if 1
header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
hWin = m_CommonThreeNum.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    hWin = m_CommonThreeNum.hEditH;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonThreeNum.value_show_h = *(pMenu->data->menusel)/100;
    EDIT_SetDecMode(hWin,m_CommonThreeNum.value_show_h,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_CommonThreeNum.hEditD;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonThreeNum.value_show_d = (*(pMenu->data->menusel)%100)/10;;
    EDIT_SetDecMode(hWin,m_CommonThreeNum.value_show_d,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_CommonThreeNum.hEditL;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonThreeNum.value_show_l = (*(pMenu->data->menusel)%100)%10;;
    EDIT_SetDecMode(hWin,m_CommonThreeNum.value_show_l,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_CommonThreeNum.hProg;
    PROGBAR_SetText(hWin,"");
    PROGBAR_SetMinMax(hWin,0,m_max);
    PROGBAR_SetValue(hWin,*(pMenu->data->menusel));
	PROGBAR_SetSkin(hWin, _ProgOwnerSkin2);
    StrShowClear();
    enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
    hWin = m_CommonThreeNum.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str(pContentEn,strShow,STRSHOWBUF_SIZE);
    hWin = m_CommonThreeNum.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    hWin = m_CommonThreeNum.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 6);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw3);
	LISTBOX_SetSel(hWin, -1);
#endif		
		#if 1
		for(i=0;i<INFO_MENU_SAVE_NUM;i++)
    {
        StrShowClear();
        if(LANGUAGE_CN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_CN[i],strShow,STRSHOWBUF_SIZE);
        }
        else if(LANGUAGE_EN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_EN[i],strShow,STRSHOWBUF_SIZE);
        }
        LISTBOX_AddString(hWin, strShow);
    }
    m_CommonThreeNum.max       = m_max;
    mp_return_value_three_num = pMenu->data->menusel;
	m_CommonThreeNum.hTimer = WM_CreateTimer(WM_HBKWIN,0,1000,0);
    WM_SetCallback(WM_HBKWIN, _WinComThreeNumCallback);
    WM_SetFocus(WM_HBKWIN);
		#endif
}


static void _WinComThreeNumDestroy(void *p)
{
    m_return_value_three_num = m_CommonThreeNum.value_show_h*100 + m_CommonThreeNum.value_show_d*10 + m_CommonThreeNum.value_show_l;
    if(m_return_value_three_num > m_CommonThreeNum.max ) m_return_value_three_num = m_CommonThreeNum.max;	
		WM_DeleteWindow(m_CommonThreeNum.hImage_CB_1);      
		WM_DeleteWindow(m_CommonThreeNum.hImage_CB_2);      
		WM_DeleteWindow(m_CommonThreeNum.hTextHead);        
		WM_DeleteWindow(m_CommonThreeNum.hEditH); 
		WM_DeleteWindow(m_CommonThreeNum.hEditD); 
		WM_DeleteWindow(m_CommonThreeNum.hEditL); 
		WM_DeleteWindow(m_CommonThreeNum.hProg);            
		WM_DeleteWindow(m_CommonThreeNum.hTextMin);         
		WM_DeleteWindow(m_CommonThreeNum.hTextMax);         
		WM_DeleteWindow(m_CommonThreeNum.hList);             
		WM_DeleteWindow(m_CommonThreeNum.hImageBack);       
		WM_DeleteWindow(m_CommonThreeNum.hButtonEditH);     
		WM_DeleteWindow(m_CommonThreeNum.hButtonEditD);     
		WM_DeleteWindow(m_CommonThreeNum.hButtonEditS);     
	WM_DeleteTimer(m_CommonThreeNum.hTimer);
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_CommonThreeNum, 0, sizeof(m_CommonThreeNum));
}

void _WinComThreeNumInterface(void *val)
{
    *mp_return_value_three_num = m_return_value_three_num;
}


WIN_INFO_TYPE g_WinComThreeNumMenu = {                        
    &m_CommonThreeNum.hFrame,
    _WinComThreeNumCreate,
    _WinComThreeNumDestroy
};

typedef struct {
    GUI_HWIN  hFrame;
		GUI_HWIN hImage_CB_1;             
		GUI_HWIN hImage_CB_2;             
    GUI_HWIN  hTextHead;              
    GUI_HWIN  hEdit1;    
    GUI_HWIN  hEdit2;    
    GUI_HWIN  hEdit3;    
    GUI_HWIN  hEdit4;                 
    GUI_HWIN  hEdit5;                 
    GUI_HWIN  hProg;                  
    GUI_HWIN  hTextMin;               
    GUI_HWIN  hTextMax;               
    GUI_HWIN  hList;                  
    unsigned char currentSel;      
    unsigned char value_show_1;       
    unsigned char value_show_2;       
    unsigned char value_show_3;       
    unsigned char value_show_4;       
    unsigned char value_show_5;       
    unsigned short max;               
	GUI_HWIN  hImageBack;               
	GUI_HWIN  hButtonEdit1;             
	GUI_HWIN  hButtonEdit2;             
	GUI_HWIN  hButtonEdit3;             
	GUI_HWIN  hButtonEdit4;             
	GUI_HWIN  hButtonEdit5;             
	GUI_HWIN  hTimer;                   
	unsigned char cTimerCnt;            
}WIN_COMMON_FIVE_NUM_TYPE;
static WIN_COMMON_FIVE_NUM_TYPE m_CommonFiveNum = {0};                        
static unsigned short *mp_return_value_five_num=0;
static unsigned short  m_return_value_five_num=0;
void _WinComFiveNumKeyEnter(void )
{
    unsigned short m_value=0;
    if(0 == m_CommonFiveNum.currentSel)
    {
        m_CommonFiveNum.currentSel = 7;
		EDIT_SetTextColor(m_CommonFiveNum.hEdit1,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(1 == m_CommonFiveNum.currentSel)
    {
        m_CommonFiveNum.currentSel = 8;
		EDIT_SetTextColor(m_CommonFiveNum.hEdit2,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(2 == m_CommonFiveNum.currentSel)
    {
        m_CommonFiveNum.currentSel = 9;
		EDIT_SetTextColor(m_CommonFiveNum.hEdit3,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(3 == m_CommonFiveNum.currentSel)
    {
        m_CommonFiveNum.currentSel = 10;
		EDIT_SetTextColor(m_CommonFiveNum.hEdit4,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(4 == m_CommonFiveNum.currentSel)
    {
        m_CommonFiveNum.currentSel = 11;
		EDIT_SetTextColor(m_CommonFiveNum.hEdit5,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(5 == m_CommonFiveNum.currentSel)
    {
        WIN_Exit(1);
    }
    else if(6 == m_CommonFiveNum.currentSel)
    {
        WIN_Exit(0);
    }
    else if(7 == m_CommonFiveNum.currentSel)
    {
        EDIT_SetTextColor(m_CommonFiveNum.hEdit1,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_CommonFiveNum.hEdit2,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit1,0);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit2,1);
        m_CommonFiveNum.currentSel = 8;
		EDIT_SetDecMode(m_CommonFiveNum.hEdit1,m_CommonFiveNum.value_show_1,0,9,0,GUI_EDIT_NORMAL);
    }
    else if(8 == m_CommonFiveNum.currentSel)
    {
        EDIT_SetTextColor(m_CommonFiveNum.hEdit2,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_CommonFiveNum.hEdit3,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit2,0);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit3,1);
        m_CommonFiveNum.currentSel = 9;
		EDIT_SetDecMode(m_CommonFiveNum.hEdit2,m_CommonFiveNum.value_show_2,0,9,0,GUI_EDIT_NORMAL);
    }
     else if(9 == m_CommonFiveNum.currentSel)
    {
        EDIT_SetTextColor(m_CommonFiveNum.hEdit3,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_CommonFiveNum.hEdit4,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit3,0);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit4,1);
        m_CommonFiveNum.currentSel = 10;
		EDIT_SetDecMode(m_CommonFiveNum.hEdit3,m_CommonFiveNum.value_show_3,0,9,0,GUI_EDIT_NORMAL);
    }
     else if(10 == m_CommonFiveNum.currentSel)
    {
        EDIT_SetTextColor(m_CommonFiveNum.hEdit4,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_CommonFiveNum.hEdit5,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit4,0);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit5,1);
        m_CommonFiveNum.currentSel = 11;
		EDIT_SetDecMode(m_CommonFiveNum.hEdit4,m_CommonFiveNum.value_show_4,0,9,0,GUI_EDIT_NORMAL);
    }
    else if(11 == m_CommonFiveNum.currentSel)
    {
        EDIT_SetTextColor(m_CommonFiveNum.hEdit5,EDIT_CI_ENABELD,GUI_BLUE);
        LISTBOX_SetSel(m_CommonFiveNum.hList,0);
        m_CommonFiveNum.currentSel = 5;
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit5,0);
		EDIT_SetDecMode(m_CommonFiveNum.hEdit5,m_CommonFiveNum.value_show_5,0,9,0,GUI_EDIT_NORMAL);
    }
    m_value = m_CommonFiveNum.value_show_1*10000 + m_CommonFiveNum.value_show_2*1000 + m_CommonFiveNum.value_show_3*100+m_CommonFiveNum.value_show_4*10+m_CommonFiveNum.value_show_5;
    PROGBAR_SetValue(m_CommonFiveNum.hProg,m_value);
}

void _WinComFiveNumKeyDown(void)
{
    unsigned short m_value=0;
    if(0 == m_CommonFiveNum.currentSel)
    {
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit1,0);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit2,1);
        m_CommonFiveNum.currentSel = 1;
    }
    else if(1 == m_CommonFiveNum.currentSel)
    {
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit2,0);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit3,1);
        m_CommonFiveNum.currentSel = 2;
    }
    else if(2 == m_CommonFiveNum.currentSel)
    {
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit3,0);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit4,1);
        m_CommonFiveNum.currentSel = 3;
    }
    else if(3 == m_CommonFiveNum.currentSel)
    {
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit4,0);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit5,1);
        m_CommonFiveNum.currentSel = 4;
    }
    else if(4 == m_CommonFiveNum.currentSel)
    {
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit5,0);
        LISTBOX_SetSel(m_CommonFiveNum.hList,0);
        m_CommonFiveNum.currentSel = 5;		
    }
     else if(5 == m_CommonFiveNum.currentSel)
    {
        LISTBOX_SetSel(m_CommonFiveNum.hList,1);
        m_CommonFiveNum.currentSel = 6;
    }
    else if(6 == m_CommonFiveNum.currentSel)
    {
        LISTBOX_SetSel(m_CommonFiveNum.hList,-1);
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit1,1);
        m_CommonFiveNum.currentSel = 0;
    }
    else if(7 == m_CommonFiveNum.currentSel)
    {
        m_CommonFiveNum.value_show_1++;
        if(m_CommonFiveNum.value_show_1>9) m_CommonFiveNum.value_show_1 = 0;
        EDIT_SetValue(m_CommonFiveNum.hEdit1,m_CommonFiveNum.value_show_1);
    }
    else if(8 == m_CommonFiveNum.currentSel)
    {
        m_CommonFiveNum.value_show_2++;
        if(m_CommonFiveNum.value_show_2>9) m_CommonFiveNum.value_show_2 = 0;
        EDIT_SetValue(m_CommonFiveNum.hEdit2,m_CommonFiveNum.value_show_2);
    }
    else if(9 == m_CommonFiveNum.currentSel)
    {
        m_CommonFiveNum.value_show_3++;
        if(m_CommonFiveNum.value_show_3>9) m_CommonFiveNum.value_show_3 = 0;
        EDIT_SetValue(m_CommonFiveNum.hEdit3,m_CommonFiveNum.value_show_3);
    }
    else if(10 == m_CommonFiveNum.currentSel)
    {
        m_CommonFiveNum.value_show_4++;
        if(m_CommonFiveNum.value_show_4>9) m_CommonFiveNum.value_show_4 = 0;
        EDIT_SetValue(m_CommonFiveNum.hEdit4,m_CommonFiveNum.value_show_4);
    }
    else if(11 == m_CommonFiveNum.currentSel)
    {
        m_CommonFiveNum.value_show_5++;
    }
    m_value = m_CommonFiveNum.value_show_1*10000 + m_CommonFiveNum.value_show_2*1000 + m_CommonFiveNum.value_show_3*100+m_CommonFiveNum.value_show_4*10+m_CommonFiveNum.value_show_5;
    PROGBAR_SetValue(m_CommonFiveNum.hProg,m_value);
}


void _WinComFiveNumKeyUp(void)
{
    unsigned short m_value=0;
    if(0 == m_CommonFiveNum.currentSel)
    {
			 BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit1,0);
        LISTBOX_SetSel(m_CommonFiveNum.hList,1);
        m_CommonFiveNum.currentSel = 6;
    }
    else if(1 == m_CommonFiveNum.currentSel)
    {
			BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit1,1);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit2,0);
        m_CommonFiveNum.currentSel = 0;
    }
    else if(2 == m_CommonFiveNum.currentSel)
    {
			BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit2,1);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit3,0);
        m_CommonFiveNum.currentSel = 1;
    }
    else if(3 == m_CommonFiveNum.currentSel)
    {
			BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit3,1);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit4,0);
        m_CommonFiveNum.currentSel = 2;
    }
    else if(4 == m_CommonFiveNum.currentSel)
    {
			BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit4,1);
		BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit5,0);
        m_CommonFiveNum.currentSel = 3;
    }
     else if(5 == m_CommonFiveNum.currentSel)
    {
			LISTBOX_SetSel(m_CommonFiveNum.hList,-1);
        BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit5,1);
        m_CommonFiveNum.currentSel = 4;
    }
    else if(6 == m_CommonFiveNum.currentSel)
    {
			 LISTBOX_SetSel(m_CommonFiveNum.hList,0);
        m_CommonFiveNum.currentSel = 5;
    }
    else if(7 == m_CommonFiveNum.currentSel)
    {
			       if(m_CommonFiveNum.value_show_1>0)m_CommonFiveNum.value_show_1--;
        else  m_CommonFiveNum.value_show_1 = 9;
        EDIT_SetValue(m_CommonFiveNum.hEdit1,m_CommonFiveNum.value_show_1);
			}
    else if(8 == m_CommonFiveNum.currentSel)
    {
			        if(m_CommonFiveNum.value_show_2>0)m_CommonFiveNum.value_show_2--;
        else  m_CommonFiveNum.value_show_2 = 9;
        EDIT_SetValue(m_CommonFiveNum.hEdit2,m_CommonFiveNum.value_show_2);
			}
    else if(9 == m_CommonFiveNum.currentSel)
    {
			        if(m_CommonFiveNum.value_show_3>0)m_CommonFiveNum.value_show_3--;
        else  m_CommonFiveNum.value_show_3 = 9;
        EDIT_SetValue(m_CommonFiveNum.hEdit3,m_CommonFiveNum.value_show_3);
			}
    else if(10 == m_CommonFiveNum.currentSel)
    {
			        if(m_CommonFiveNum.value_show_4>0)m_CommonFiveNum.value_show_4--;
        else  m_CommonFiveNum.value_show_4 = 9;
        EDIT_SetValue(m_CommonFiveNum.hEdit4,m_CommonFiveNum.value_show_4);
			}
    else if(11 == m_CommonFiveNum.currentSel)
    {
       if(m_CommonFiveNum.value_show_5>0)m_CommonFiveNum.value_show_5--;
        else  m_CommonFiveNum.value_show_5 = 9;
        EDIT_SetValue(m_CommonFiveNum.hEdit5,m_CommonFiveNum.value_show_5);		
		}
    m_value = m_CommonFiveNum.value_show_1*10000 + m_CommonFiveNum.value_show_2*1000 + m_CommonFiveNum.value_show_3*100+m_CommonFiveNum.value_show_4*10+m_CommonFiveNum.value_show_5;
    PROGBAR_SetValue(m_CommonFiveNum.hProg,m_value);
}
static void WinFiveNumberShowStyle(void)
{
    m_CommonFiveNum.cTimerCnt++;
	if(7 == m_CommonFiveNum.currentSel)
	{
	    if(m_CommonFiveNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonFiveNum.hEdit1);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonFiveNum.hEdit1,m_CommonFiveNum.value_show_1,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(8 == m_CommonFiveNum.currentSel)
	{
	    if(m_CommonFiveNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonFiveNum.hEdit2);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonFiveNum.hEdit2,m_CommonFiveNum.value_show_2,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(9 == m_CommonFiveNum.currentSel)
	{
	    if(m_CommonFiveNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonFiveNum.hEdit3);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonFiveNum.hEdit3,m_CommonFiveNum.value_show_3,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(10 == m_CommonFiveNum.currentSel)
	{
	    if(m_CommonFiveNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonFiveNum.hEdit4);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonFiveNum.hEdit4,m_CommonFiveNum.value_show_4,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(11 == m_CommonFiveNum.currentSel)
	{
	    if(m_CommonFiveNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonFiveNum.hEdit5);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonFiveNum.hEdit5,m_CommonFiveNum.value_show_5,0,9,0,GUI_EDIT_NORMAL);
		}

	}

}
static void _WinComFiveNumCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
    switch (pMsg->MsgId)
    {
			 case WM_TIMER:
        WM_RestartTimer(pMsg->Data.v, 1000);
		WinFiveNumberShowStyle();
        break;
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinComFiveNumKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinComFiveNumKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinComFiveNumKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinComFiveNumCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;
    unsigned short   m_max = *((unsigned short *)pMenu->data->menuattri);
    unsigned short   m_setvalue = *((unsigned short *)pMenu->data->menusel);
    unsigned char    i = 0;
    if (NULL == pTitle) pTitle = "";
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	memcpy(strShow,pTitle,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_CommonFiveNum.hFrame, 0); 
#if 1
    hWin = WM_GetFirstChild(m_CommonFiveNum.hFrame);
    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
#if 1      
	m_CommonFiveNum.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_CommonFiveNum.hImage_CB_1,&bmComBack_1);	
	m_CommonFiveNum.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_CommonFiveNum.hImage_CB_2,&bmComBack_2);
    #endif
	m_CommonFiveNum.hButtonEdit1   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET-6-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonFiveNum.hButtonEdit1,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit1,1);
	m_CommonFiveNum.hButtonEdit2   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+50-6-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonFiveNum.hButtonEdit2,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit2,0);
	m_CommonFiveNum.hButtonEdit3   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+100-6-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonFiveNum.hButtonEdit3,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit3,0);
	m_CommonFiveNum.hButtonEdit4   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+150-6-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonFiveNum.hButtonEdit4,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit4,0);
	m_CommonFiveNum.hButtonEdit5   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+200-6-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonFiveNum.hButtonEdit5,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonFiveNum.hButtonEdit5,0);
    m_CommonFiveNum.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+10-8, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CommonFiveNum.hEdit1     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET-8      , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonFiveNum.hEdit2     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+50-8   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonFiveNum.hEdit3     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+100-8   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonFiveNum.hEdit4     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+150-8   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonFiveNum.hEdit5     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+200-8   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonFiveNum.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET+30-8   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60, 162+2, 19+2, hWin,  NULL, WM_CF_SHOW);
    m_CommonFiveNum.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CommonFiveNum.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CommonFiveNum.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+13-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+50, 180, 52, hWin, WM_CF_SHOW, NULL, NULL, NULL);
    
#endif
#if 1
header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
  hWin = m_CommonFiveNum.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
   // TEXT_SetBkColor(hWin,GUI_BLUE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
#endif
		#if 1
		  hWin = m_CommonFiveNum.hEdit1;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonFiveNum.value_show_1 = m_setvalue/10000;
    EDIT_SetDecMode(hWin,m_CommonFiveNum.value_show_1,0,9,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    hWin = m_CommonFiveNum.hEdit2;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonFiveNum.value_show_2 = (m_setvalue%10000)/1000;
    EDIT_SetDecMode(hWin,m_CommonFiveNum.value_show_2,0,9,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    hWin = m_CommonFiveNum.hEdit3;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonFiveNum.value_show_3 = ((m_setvalue%10000)%1000)/100;
    EDIT_SetDecMode(hWin,m_CommonFiveNum.value_show_3,0,9,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    hWin = m_CommonFiveNum.hEdit4;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonFiveNum.value_show_4 = (((m_setvalue%10000)%1000)%100)/10;
    EDIT_SetDecMode(hWin,m_CommonFiveNum.value_show_4,0,9,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    hWin = m_CommonFiveNum.hEdit5;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonFiveNum.value_show_5 = (((m_setvalue%10000)%1000)%100)%10;
    EDIT_SetDecMode(hWin,m_CommonFiveNum.value_show_5,0,9,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    hWin = m_CommonFiveNum.hProg;
    PROGBAR_SetText(hWin,"");
    PROGBAR_SetMinMax(hWin,0,m_max);
    PROGBAR_SetValue(hWin,m_setvalue);
	PROGBAR_SetSkin(hWin, _ProgOwnerSkin2);
		#endif
		#if 1
		StrShowClear();
    enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
    hWin = m_CommonFiveNum.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str(pContentEn,strShow,STRSHOWBUF_SIZE);
    hWin = m_CommonFiveNum.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
		#endif
		#if 1
		    hWin = m_CommonFiveNum.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 6);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw3);
	LISTBOX_SetSel(hWin, -1);
    for(i=0;i<INFO_MENU_SAVE_NUM;i++)
    {
        StrShowClear();
        if(LANGUAGE_CN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_CN[i],strShow,STRSHOWBUF_SIZE);
        }
        else if(LANGUAGE_EN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_EN[i],strShow,STRSHOWBUF_SIZE);
        }
        LISTBOX_AddString(hWin, strShow);
    }
    m_CommonFiveNum.max       = m_max;
    mp_return_value_five_num = (unsigned short *)pMenu->data->menusel;
    m_CommonFiveNum.hTimer = WM_CreateTimer(WM_HBKWIN,0,1000,0);
    WM_SetCallback(WM_HBKWIN, _WinComFiveNumCallback);
    WM_SetFocus(WM_HBKWIN);
		#endif
}


static void _WinComFiveNumDestroy(void *p)
{
    m_return_value_five_num = m_CommonFiveNum.value_show_1*10000 + m_CommonFiveNum.value_show_2*1000 + m_CommonFiveNum.value_show_3*100+m_CommonFiveNum.value_show_4*10+m_CommonFiveNum.value_show_5;
    if(m_return_value_five_num > m_CommonFiveNum.max ) m_return_value_five_num = m_CommonFiveNum.max;	
WM_DeleteWindow(m_CommonFiveNum.hImage_CB_1);            
WM_DeleteWindow(m_CommonFiveNum.hImage_CB_2);            
WM_DeleteWindow(m_CommonFiveNum.hTextHead);              
WM_DeleteWindow(m_CommonFiveNum.hEdit1); 
WM_DeleteWindow(m_CommonFiveNum.hEdit2); 
WM_DeleteWindow(m_CommonFiveNum.hEdit3); 
WM_DeleteWindow(m_CommonFiveNum.hEdit4);                 
WM_DeleteWindow(m_CommonFiveNum.hEdit5);                 
WM_DeleteWindow(m_CommonFiveNum.hProg);                  
WM_DeleteWindow(m_CommonFiveNum.hTextMin);               
WM_DeleteWindow(m_CommonFiveNum.hTextMax);               
WM_DeleteWindow(m_CommonFiveNum.hList);                  
WM_DeleteWindow(m_CommonFiveNum.hImageBack);             
WM_DeleteWindow(m_CommonFiveNum.hButtonEdit1);           
WM_DeleteWindow(m_CommonFiveNum.hButtonEdit2);           
WM_DeleteWindow(m_CommonFiveNum.hButtonEdit3);           
WM_DeleteWindow(m_CommonFiveNum.hButtonEdit4);           
WM_DeleteWindow(m_CommonFiveNum.hButtonEdit5);                         
	WM_DeleteTimer(m_CommonFiveNum.hTimer);   
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_CommonFiveNum, 0, sizeof(m_CommonFiveNum));
}

void _WinComFiveNumInterface(void *val)
{
    *((unsigned short *)mp_return_value_five_num) = m_return_value_five_num;
}


WIN_INFO_TYPE g_WinComFiveNumMenu = {                        
    &m_CommonFiveNum.hFrame,
    _WinComFiveNumCreate,
    _WinComFiveNumDestroy
};

typedef struct {
    GUI_HWIN  hFrame; 
		GUI_HWIN hImage_CB_1;       
		GUI_HWIN hImage_CB_2;       
    GUI_HWIN  hTextHead;        
    GUI_HWIN  hEdit1;  
    GUI_HWIN  hEdit2;           
    GUI_HWIN  hEdit3;  
    GUI_HWIN  hEdit4;           
    GUI_HWIN  hProg;            
    GUI_HWIN  hTextMin;         
    GUI_HWIN  hTextMax;         
    GUI_HWIN  hList;            
    unsigned char currentSel;   
    unsigned char value_show_1; 
    unsigned char value_show_2; 
    unsigned char value_show_3; 
    unsigned char value_show_4; 
    unsigned short max;         
	GUI_HWIN  hImageBack;         
	GUI_HWIN  hButtonEdit1;       
	GUI_HWIN  hButtonEdit2;       
	GUI_HWIN  hButtonEdit3;     
	GUI_HWIN  hButtonEdit4;     
	GUI_HWIN  hTimer;           
	unsigned char cTimerCnt;    
}WIN_COMMON_FOUR_NUM_TYPE;
static WIN_COMMON_FOUR_NUM_TYPE m_CommonFourNum = {0};                        
static unsigned short *mp_return_value_four_num=0;
static unsigned short  m_return_value_four_num=0;

void _WinComFourNumKeyEnter(void )
{
    unsigned short m_value=0;
    if(0 == m_CommonFourNum.currentSel)
    {
        m_CommonFourNum.currentSel = 6;
			EDIT_SetTextColor(m_CommonFourNum.hEdit1,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(1 == m_CommonFourNum.currentSel)
    {
        m_CommonFourNum.currentSel = 7;
			EDIT_SetTextColor(m_CommonFourNum.hEdit1,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(2 == m_CommonFourNum.currentSel)
    {
        m_CommonFourNum.currentSel = 8;
			EDIT_SetTextColor(m_CommonFourNum.hEdit1,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(3 == m_CommonFourNum.currentSel)
    {
        m_CommonFourNum.currentSel = 9;
			EDIT_SetTextColor(m_CommonFourNum.hEdit1,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(4 == m_CommonFourNum.currentSel)
    {
        WIN_Exit(1);
    }
    else if(5 == m_CommonFourNum.currentSel)
    {
        WIN_Exit(0);
    }
    else if(6 == m_CommonFourNum.currentSel)
    {		
        EDIT_SetTextColor(m_CommonFourNum.hEdit1,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_CommonFourNum.hEdit2,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_CommonFourNum.hButtonEdit1,0);
		BUTTON_SetPressed(m_CommonFourNum.hButtonEdit2,1);
        m_CommonFourNum.currentSel = 7;
		EDIT_SetDecMode(m_CommonFourNum.hEdit1,m_CommonFourNum.value_show_1,0,9,0,GUI_EDIT_NORMAL);
    }
    else if(7 == m_CommonFourNum.currentSel)
    {
        EDIT_SetTextColor(m_CommonFourNum.hEdit2,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_CommonFourNum.hEdit3,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_CommonFourNum.hButtonEdit2,0);
		BUTTON_SetPressed(m_CommonFourNum.hButtonEdit3,1);
        m_CommonFourNum.currentSel = 8;
		EDIT_SetDecMode(m_CommonFourNum.hEdit2,m_CommonFourNum.value_show_2,0,9,0,GUI_EDIT_NORMAL);
    }
     else if(8 == m_CommonFourNum.currentSel)
    {
        EDIT_SetTextColor(m_CommonFourNum.hEdit3,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_CommonFourNum.hEdit4,EDIT_CI_ENABELD,GUI_ORANGE);
        BUTTON_SetPressed(m_CommonFourNum.hButtonEdit3,0);
		BUTTON_SetPressed(m_CommonFourNum.hButtonEdit4,1);
        m_CommonFourNum.currentSel = 9;
		EDIT_SetDecMode(m_CommonFourNum.hEdit3,m_CommonFourNum.value_show_3,0,9,0,GUI_EDIT_NORMAL);
    }
    else if(9 == m_CommonFourNum.currentSel)
    {
        EDIT_SetTextColor(m_CommonFourNum.hEdit4,EDIT_CI_ENABELD,GUI_BLUE);
        LISTBOX_SetSel(m_CommonFourNum.hList,0);
        m_CommonFourNum.currentSel = 4;
        BUTTON_SetPressed(m_CommonFourNum.hButtonEdit4,0);
		EDIT_SetDecMode(m_CommonFourNum.hEdit4,m_CommonFourNum.value_show_4,0,9,0,GUI_EDIT_NORMAL);
    }
    m_value = m_CommonFourNum.value_show_1*1000 + m_CommonFourNum.value_show_2*100 + m_CommonFourNum.value_show_3*10+m_CommonFourNum.value_show_4;
    PROGBAR_SetValue(m_CommonFourNum.hProg,m_value);
}

void _WinComFourNumKeyDown(void)
{
    unsigned short m_value=0;
    if(0 == m_CommonFourNum.currentSel)
    {
			  BUTTON_SetPressed(m_CommonFourNum.hButtonEdit1,0);
		BUTTON_SetPressed(m_CommonFourNum.hButtonEdit2,1);
        m_CommonFourNum.currentSel = 1;
    }
    else if(1 == m_CommonFourNum.currentSel)
    {
			BUTTON_SetPressed(m_CommonFourNum.hButtonEdit2,0);
		BUTTON_SetPressed(m_CommonFourNum.hButtonEdit3,1);
        m_CommonFourNum.currentSel = 2;
    }
    else if(2 == m_CommonFourNum.currentSel)
    {
			  BUTTON_SetPressed(m_CommonFourNum.hButtonEdit3,0);
		BUTTON_SetPressed(m_CommonFourNum.hButtonEdit4,1);
        m_CommonFourNum.currentSel = 3;
    }
    else if(3 == m_CommonFourNum.currentSel)
    {
			 BUTTON_SetPressed(m_CommonFourNum.hButtonEdit4,0);
        LISTBOX_SetSel(m_CommonFourNum.hList,0);
        m_CommonFourNum.currentSel = 4;
    }
     else if(4 == m_CommonFourNum.currentSel)
    {
			LISTBOX_SetSel(m_CommonFourNum.hList,1);
        m_CommonFourNum.currentSel = 5;
    }
    else if(5 == m_CommonFourNum.currentSel)
    {
			LISTBOX_SetSel(m_CommonFourNum.hList,-1);
        BUTTON_SetPressed(m_CommonFourNum.hButtonEdit1,1);
        m_CommonFourNum.currentSel = 0;
    }
    else if(6 == m_CommonFourNum.currentSel)
    {
			      m_CommonFourNum.value_show_1++;
        if(m_CommonFourNum.value_show_1>9) m_CommonFourNum.value_show_1 = 0;
        EDIT_SetValue(m_CommonFourNum.hEdit1,m_CommonFourNum.value_show_1);
			}
    else if(7 == m_CommonFourNum.currentSel)
    {
			        m_CommonFourNum.value_show_2++;
        if(m_CommonFourNum.value_show_2>9) m_CommonFourNum.value_show_2 = 0;
        EDIT_SetValue(m_CommonFourNum.hEdit2,m_CommonFourNum.value_show_2);
		}
    else if(8 == m_CommonFourNum.currentSel)
    {
			        m_CommonFourNum.value_show_3++;
        if(m_CommonFourNum.value_show_3>9) m_CommonFourNum.value_show_3 = 0;
        EDIT_SetValue(m_CommonFourNum.hEdit3,m_CommonFourNum.value_show_3);
			}
    else if(9 == m_CommonFourNum.currentSel)
    {
			        m_CommonFourNum.value_show_4++;
        if(m_CommonFourNum.value_show_4>9) m_CommonFourNum.value_show_4 = 0;
        EDIT_SetValue(m_CommonFourNum.hEdit4,m_CommonFourNum.value_show_4);
			}
    m_value = m_CommonFourNum.value_show_1*1000 + m_CommonFourNum.value_show_2*100 + m_CommonFourNum.value_show_3*10+m_CommonFourNum.value_show_4;
    PROGBAR_SetValue(m_CommonFourNum.hProg,m_value);
}


void _WinComFourNumKeyUp(void)
{
    unsigned short m_value=0;
    if(0 == m_CommonFourNum.currentSel)
    {
			 BUTTON_SetPressed(m_CommonFourNum.hButtonEdit1,0);
        LISTBOX_SetSel(m_CommonFourNum.hList,1);
        m_CommonFourNum.currentSel = 5;
    }
    else if(1 == m_CommonFourNum.currentSel)
    {
			 BUTTON_SetPressed(m_CommonFourNum.hButtonEdit1,1);
		BUTTON_SetPressed(m_CommonFourNum.hButtonEdit2,0);
        m_CommonFourNum.currentSel = 0;
    }
    else if(2 == m_CommonFourNum.currentSel)
    {
			BUTTON_SetPressed(m_CommonFourNum.hButtonEdit2,1);
		BUTTON_SetPressed(m_CommonFourNum.hButtonEdit3,0);
        m_CommonFourNum.currentSel = 1;
    }
    else if(3 == m_CommonFourNum.currentSel)
    {
			  BUTTON_SetPressed(m_CommonFourNum.hButtonEdit3,1);
		BUTTON_SetPressed(m_CommonFourNum.hButtonEdit4,0);
        m_CommonFourNum.currentSel = 2;
    }
     else if(4 == m_CommonFourNum.currentSel)
    {
			LISTBOX_SetSel(m_CommonFourNum.hList,-1);
        BUTTON_SetPressed(m_CommonFourNum.hButtonEdit4,1);
        m_CommonFourNum.currentSel = 3;
    }
    else if(5 == m_CommonFourNum.currentSel)
    {
			LISTBOX_SetSel(m_CommonFourNum.hList,0);
        m_CommonFourNum.currentSel = 4;
    }
    else if(6 == m_CommonFourNum.currentSel)
    {
			  if(m_CommonFourNum.value_show_1>0)m_CommonFourNum.value_show_1--;
        else  m_CommonFourNum.value_show_1 = 9;
        EDIT_SetValue(m_CommonFourNum.hEdit1,m_CommonFourNum.value_show_1);
			}
    else if(7 == m_CommonFourNum.currentSel)
    {
        if(m_CommonFourNum.value_show_2>0)m_CommonFourNum.value_show_2--;
        else  m_CommonFourNum.value_show_2 = 9;
        EDIT_SetValue(m_CommonFourNum.hEdit2,m_CommonFourNum.value_show_2);		
		}
    else if(8 == m_CommonFourNum.currentSel)
    {
        if(m_CommonFourNum.value_show_3>0)m_CommonFourNum.value_show_3--;
        else  m_CommonFourNum.value_show_3 = 9;
        EDIT_SetValue(m_CommonFourNum.hEdit3,m_CommonFourNum.value_show_3);			
			}
    else if(9 == m_CommonFourNum.currentSel)
    {
			        if(m_CommonFourNum.value_show_4>0)m_CommonFourNum.value_show_4--;
        else  m_CommonFourNum.value_show_4 = 9;
        EDIT_SetValue(m_CommonFourNum.hEdit4,m_CommonFourNum.value_show_4);
			}
    m_value = m_CommonFourNum.value_show_1*1000 + m_CommonFourNum.value_show_2*100 + m_CommonFourNum.value_show_3*10+m_CommonFourNum.value_show_4;
    PROGBAR_SetValue(m_CommonFourNum.hProg,m_value);
}
static void WinFourNumberShowStyle(void)
{
    m_CommonFourNum.cTimerCnt++;
	if(6 == m_CommonFourNum.currentSel)
	{
	    if(m_CommonFourNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonFourNum.hEdit1);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonFourNum.hEdit1,m_CommonFourNum.value_show_1,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(7 == m_CommonFourNum.currentSel)
	{
	    if(m_CommonFourNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonFourNum.hEdit2);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonFourNum.hEdit2,m_CommonFourNum.value_show_2,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(8 == m_CommonFourNum.currentSel)
	{
	    if(m_CommonFourNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonFourNum.hEdit3);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonFourNum.hEdit3,m_CommonFourNum.value_show_3,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(9 == m_CommonFourNum.currentSel)
	{
	    if(m_CommonFourNum.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_CommonFourNum.hEdit4);
	    }
		else
		{
			EDIT_SetDecMode(m_CommonFourNum.hEdit4,m_CommonFourNum.value_show_4,0,9,0,GUI_EDIT_NORMAL);
		}

	}

}
static void _WinComFourNumCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
		switch (pMsg->MsgId)
    {
			  case WM_TIMER:
        WM_RestartTimer(pMsg->Data.v, 1000);
		WinFourNumberShowStyle();
        break;
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinComFourNumKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinComFourNumKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinComFourNumKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinComFourNumCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;
    unsigned short   m_max = *((unsigned short *)pMenu->data->menuattri);
    unsigned short   m_setvalue = *((unsigned short *)pMenu->data->menusel);
    unsigned char    i = 0;
    if (NULL == pTitle) pTitle = "";
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
		memcpy(strShow,pTitle,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_CommonFourNum.hFrame, 0);        
	 hWin = WM_GetFirstChild(m_CommonFourNum.hFrame);
  GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	m_CommonFourNum.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_CommonFourNum.hImage_CB_1,&bmComBack_1);	
	m_CommonFourNum.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_CommonFourNum.hImage_CB_2,&bmComBack_2);
		#if 1
		m_CommonFourNum.hButtonEdit1   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+20-6-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonFourNum.hButtonEdit1,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonFourNum.hButtonEdit1,1);
	  m_CommonFourNum.hButtonEdit2   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+70-6-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonFourNum.hButtonEdit2,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonFourNum.hButtonEdit2,0);
	  m_CommonFourNum.hButtonEdit3   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+120-6-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonFourNum.hButtonEdit3,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonFourNum.hButtonEdit3,0);
	  m_CommonFourNum.hButtonEdit4   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+170-6-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_CommonFourNum.hButtonEdit4,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_CommonFourNum.hButtonEdit4,0);
		#endif
		
		#if 1
	  m_CommonFourNum.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+10-8, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CommonFourNum.hEdit1     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+20-8      , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonFourNum.hEdit2     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+70-8   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonFourNum.hEdit3     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+120-8   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonFourNum.hEdit4     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+170-8   , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_CommonFourNum.hProg      = PROGBAR_CreateAsChild( DEBUG_X_OFFSET+PER_CM_OFFSET+30-8 , DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60, 162+2,19+2 , hWin,  NULL, WM_CF_SHOW);
    m_CommonFourNum.hTextMin   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CommonFourNum.hTextMax   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+160-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+30, 60, 20, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_CommonFourNum.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+13-8, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+50, 180, 52, hWin, WM_CF_SHOW, NULL, NULL, NULL);  
		#endif 
		header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_CommonFourNum.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
#if 1
	     hWin = m_CommonFourNum.hEdit1;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonFourNum.value_show_1 = m_setvalue/1000;
    EDIT_SetDecMode(hWin,m_CommonFourNum.value_show_1,0,9,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);  
		  hWin = m_CommonFourNum.hEdit2;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonFourNum.value_show_2 = (m_setvalue%1000)/100;
    EDIT_SetDecMode(hWin,m_CommonFourNum.value_show_2,0,9,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    hWin = m_CommonFourNum.hEdit3;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonFourNum.value_show_3 = ((m_setvalue%1000)%100)/10;
    EDIT_SetDecMode(hWin,m_CommonFourNum.value_show_3,0,9,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    hWin = m_CommonFourNum.hEdit4;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_CommonFourNum.value_show_4 = ((m_setvalue%1000)%100)%10;
    EDIT_SetDecMode(hWin,m_CommonFourNum.value_show_4,0,9,0,GUI_EDIT_SUPPRESS_LEADING_ZEROES);   
	 #endif

		#if 1
		 hWin = m_CommonFourNum.hProg;
    PROGBAR_SetText(hWin,"");
    PROGBAR_SetMinMax(hWin,0,m_max);
    PROGBAR_SetValue(hWin,m_setvalue);
		#endif
		#if 1
		    StrShowClear();
    enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
    hWin = m_CommonFourNum.hTextMin;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    enc_unicode_to_utf8_str(pContentEn,strShow,STRSHOWBUF_SIZE);
    hWin = m_CommonFourNum.hTextMax;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
		#endif
    hWin = m_CommonFourNum.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 6);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
		LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw3);
	  LISTBOX_SetSel(hWin, -1);
	#if 1
	    for(i=0;i<INFO_MENU_SAVE_NUM;i++)
    {
        StrShowClear();
        if(LANGUAGE_CN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_CN[i],strShow,STRSHOWBUF_SIZE);
        }
        else if(LANGUAGE_EN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_EN[i],strShow,STRSHOWBUF_SIZE);
        }
        LISTBOX_AddString(hWin, strShow);
    }
    m_CommonFourNum.max       = m_max;
    mp_return_value_four_num = (unsigned short *)pMenu->data->menusel;

	m_CommonFourNum.hTimer = WM_CreateTimer(WM_HBKWIN,0,1000,0);

    WM_SetCallback(WM_HBKWIN, _WinComFourNumCallback);
    WM_SetFocus(WM_HBKWIN);
	#endif
}


static void _WinComFourNumDestroy(void *p)
{
    m_return_value_four_num = m_CommonFourNum.value_show_1*1000 + m_CommonFourNum.value_show_2*100 + m_CommonFourNum.value_show_3*10+m_CommonFourNum.value_show_4;
    if(m_return_value_four_num > m_CommonFourNum.max ) m_return_value_four_num = m_CommonFourNum.max;
		WM_DeleteWindow(m_CommonFourNum.hImage_CB_1);    
		WM_DeleteWindow(m_CommonFourNum.hImage_CB_2);    
		WM_DeleteWindow(m_CommonFourNum.hTextHead);      
		WM_DeleteWindow(m_CommonFourNum.hEdit1);  
		WM_DeleteWindow(m_CommonFourNum.hEdit2);         
		WM_DeleteWindow(m_CommonFourNum.hEdit3);  
		WM_DeleteWindow(m_CommonFourNum.hEdit4);         
		WM_DeleteWindow(m_CommonFourNum.hProg);          
		WM_DeleteWindow(m_CommonFourNum.hTextMin);       
		WM_DeleteWindow(m_CommonFourNum.hTextMax);       
		WM_DeleteWindow(m_CommonFourNum.hList);          
		WM_DeleteWindow(m_CommonFourNum.hImageBack);     
		WM_DeleteWindow(m_CommonFourNum.hButtonEdit1);   
		WM_DeleteWindow(m_CommonFourNum.hButtonEdit2);   
		WM_DeleteWindow(m_CommonFourNum.hButtonEdit3);   
		WM_DeleteWindow(m_CommonFourNum.hButtonEdit4);   
	WM_DeleteTimer(m_CommonFourNum.hTimer); 
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_CommonFourNum, 0, sizeof(m_CommonFourNum));
}

void _WinComFourNumInterface(void *val)
{
    *((unsigned short *)mp_return_value_four_num) = m_return_value_four_num;
}


WIN_INFO_TYPE g_WinComFourNumMenu = {                        
    &m_CommonFourNum.hFrame,
    _WinComFourNumCreate,
    _WinComFourNumDestroy
};


typedef struct {
    GUI_HWIN  hFrame;
		GUI_HWIN hImage_CB_1;         
		GUI_HWIN hImage_CB_2;         
    GUI_HWIN  hBtnRtn;            
    GUI_HWIN  hText1;             
    GUI_HWIN  hText2;             
    GUI_HWIN  hText3;             
    GUI_HWIN  hText4;             
    GUI_HWIN  hText5;             
		GUI_HWIN  hImage;             
    unsigned char selIndex;       
}WIN_FIRST_SET_END_POSITION_MENU;
static WIN_FIRST_SET_END_POSITION_MENU m_SetEndPosMenu = {0};                        
void _WinFirstSetEndMenuKeyEnter(void )
{
    int id=0;
    if(m_SetEndPosMenu.selIndex == 0)
    {
        WIN_Exit(0);
    }
    else if(m_SetEndPosMenu.selIndex == 1)
    {
        id = 0;
        WIN_Enter(&id);
    }
    else if(m_SetEndPosMenu.selIndex == 2)
    {
        id = 1;
        WIN_Enter(&id);
    }
}

void _WinFirstSetEndMenuKeyDown(void)
{
     if(m_SetEndPosMenu.selIndex == 0)
     {
         m_SetEndPosMenu.selIndex = 1;
         BUTTON_SetPressed(m_SetEndPosMenu.hBtnRtn,0);
         TEXT_SetBkColor(m_SetEndPosMenu.hText3,GUI_ORANGE);
     }
     else if(m_SetEndPosMenu.selIndex == 1)
     {
         m_SetEndPosMenu.selIndex = 2;
         TEXT_SetBkColor(m_SetEndPosMenu.hText3,GUI_WHITE);
         TEXT_SetBkColor(m_SetEndPosMenu.hText4,GUI_ORANGE);
     }
     else if(m_SetEndPosMenu.selIndex == 2)
     {
         m_SetEndPosMenu.selIndex = 0;
         BUTTON_SetPressed(m_SetEndPosMenu.hBtnRtn,1);
         TEXT_SetBkColor(m_SetEndPosMenu.hText4,GUI_WHITE);
     }
}

void _WinFirstSetEndMenuKeyUp(void)
{
    if(m_SetEndPosMenu.selIndex == 0)
    {
        m_SetEndPosMenu.selIndex = 2;
        BUTTON_SetPressed(m_SetEndPosMenu.hBtnRtn,0);
        TEXT_SetBkColor(m_SetEndPosMenu.hText4,GUI_ORANGE);
    }
    else if(m_SetEndPosMenu.selIndex == 1)
    {
        m_SetEndPosMenu.selIndex = 0;
        BUTTON_SetPressed(m_SetEndPosMenu.hBtnRtn,1);
        TEXT_SetBkColor(m_SetEndPosMenu.hText3,GUI_WHITE);
    }
    else if(m_SetEndPosMenu.selIndex == 2)
    {
        m_SetEndPosMenu.selIndex = 1;
        TEXT_SetBkColor(m_SetEndPosMenu.hText3,GUI_ORANGE);
        TEXT_SetBkColor(m_SetEndPosMenu.hText4,GUI_WHITE);
    }
}

static void _WinFirstSetEndMenuCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinFirstSetEndMenuKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinFirstSetEndMenuKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinFirstSetEndMenuKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

extern char flag_reset_encoder;
static void _WinFirstSetEndMenuCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];    
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;
GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    if (NULL == pTitle) pTitle = "";
flag_reset_encoder=0;
	encoder.Set_Ready=0;
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
    FRAMEWIN_SetFont(m_SetEndPosMenu.hFrame, &GUI_Fontsong16all);  
		#if 1       
	m_SetEndPosMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_SetEndPosMenu.hImage_CB_1,&bmComBack_1);
	m_SetEndPosMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_SetEndPosMenu.hImage_CB_2,&bmComBack_2);
    #endif
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_SetEndPosMenu.hFrame, 0);             
    hWin = WM_GetFirstChild(m_SetEndPosMenu.hFrame);  
		m_SetEndPosMenu.hText1     = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+23, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SetEndPosMenu.hText2     = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+23, DEBUG_Y_OFFSET+23*2, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SetEndPosMenu.hText3     = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+23*4, PER_CM_OFFSET*4.5   , 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SetEndPosMenu.hText4     = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+23*6, PER_CM_OFFSET*4.5   , 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SetEndPosMenu.hText5     = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+46, DEBUG_Y_OFFSET+23*7, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
		 hWin = WM_GetFirstChild(m_SetEndPosMenu.hFrame);            
    m_SetEndPosMenu.hBtnRtn    = BUTTON_CreateAsChild(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, 40, 22,hWin,NULL, WM_CF_SHOW);    
    hWin = m_SetEndPosMenu.hBtnRtn;		
		BUTTON_SetSkin(hWin,SKIN_Btn_Btn);
		BUTTON_SetPressed(hWin,1);

		header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+41, DEBUG_Y_OFFSET,184-20,23);
    hWin = m_SetEndPosMenu.hText1;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
		DrawGradientH_PointWhite(50,35,270,35);
    StrShowClear();
    enc_unicode_to_utf8_str(menuEndPos1,strShow,STRSHOWBUF_SIZE);
    hWin = m_SetEndPosMenu.hText2;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);

		DrawGradientH_color(50,84,270,94,GUI_WHITE,GUI_BLUE);
    StrShowClear();
    enc_unicode_to_utf8_str(menuEndPos2,strShow,STRSHOWBUF_SIZE);
    hWin = m_SetEndPosMenu.hText3;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_VCENTER|TEXT_CF_LEFT);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);

		 DrawGradientH_PointWhite(50,135,270,135);
     StrShowClear();
    enc_unicode_to_utf8_str(menuEndPos3,strShow,STRSHOWBUF_SIZE);
    hWin = m_SetEndPosMenu.hText4;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_VCENTER|TEXT_CF_LEFT);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);

     StrShowClear();
    enc_unicode_to_utf8_str(menuEndPos4,strShow,STRSHOWBUF_SIZE);
    hWin = m_SetEndPosMenu.hText5;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);		
		DrawGradientH_PointWhite(50,220,270,220);
    m_SetEndPosMenu.selIndex = 0;
    WM_SetCallback(WM_HBKWIN, _WinFirstSetEndMenuCallback);
    WM_SetFocus(WM_HBKWIN);
}

static void _WinFirstSetEndMenuDestroy(void *p)
{
		WM_DeleteWindow(m_SetEndPosMenu.hImage_CB_1);        
		WM_DeleteWindow(m_SetEndPosMenu.hImage_CB_2);        
    WM_DeleteWindow(m_SetEndPosMenu.hBtnRtn);            
    WM_DeleteWindow(m_SetEndPosMenu.hText1);             
    WM_DeleteWindow(m_SetEndPosMenu.hText2);             
    WM_DeleteWindow(m_SetEndPosMenu.hText3);             
    WM_DeleteWindow(m_SetEndPosMenu.hText4);             
    WM_DeleteWindow(m_SetEndPosMenu.hText5);             
		WM_DeleteWindow(m_SetEndPosMenu.hImage);             
    WM_SetCallback(WM_HBKWIN, NULL);
}

void _WinFirstSetEndMenuInterface(void *val)
{

}


WIN_INFO_TYPE g_WinFirstSetEndMenu = {                         
    &m_SetEndPosMenu.hFrame,
    _WinFirstSetEndMenuCreate,
    _WinFirstSetEndMenuDestroy
};

typedef struct {
    GUI_HWIN  hFrame; 
    GUI_HWIN  hBtnRtn;          
    GUI_HWIN  hTextHead;        
    GUI_HWIN  hTextNote;        
    GUI_HWIN  hList;            
}WIN_SEL_END_POSITION_MENU;
static WIN_SEL_END_POSITION_MENU m_SelEndPosMenu = {0};                        
void _WinSelEndMenuKeyEnter(void )
{
    int id = LISTBOX_GetSel(m_SelEndPosMenu.hList);
    if(BUTTON_IsPressed( m_SelEndPosMenu.hBtnRtn))
    {
        WIN_Exit(0);
    }
    else
    {
        WIN_Enter(&id);
    }
}

void _WinSelEndMenuKeyDown(void)
{
    char curIndex=LISTBOX_GetSel(m_SelEndPosMenu.hList);
    if(BUTTON_IsPressed( m_SelEndPosMenu.hBtnRtn))
    {
        BUTTON_SetPressed(m_SelEndPosMenu.hBtnRtn,0);
        LISTBOX_SetBkColor(m_SelEndPosMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        LISTBOX_SetSel(m_SelEndPosMenu.hList,0);
    }
    else if(curIndex == 0)
    {
        LISTBOX_SetSel(m_SelEndPosMenu.hList,1);
    }
    else if(curIndex == 1)
    {
        BUTTON_SetPressed(m_SelEndPosMenu.hBtnRtn,1);
        LISTBOX_SetSel(m_SelEndPosMenu.hList,1);
        LISTBOX_SetBkColor(m_SelEndPosMenu.hList,LISTBOX_CI_SEL      , GUI_WHITE);
    }
}

void _WinSelEndMenuKeyUp(void)
{
    char curIndex=LISTBOX_GetSel(m_SelEndPosMenu.hList);
    if(BUTTON_IsPressed( m_SelEndPosMenu.hBtnRtn))
    {
        BUTTON_SetPressed(m_SelEndPosMenu.hBtnRtn,0);
        LISTBOX_SetBkColor(m_SelEndPosMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        LISTBOX_SetSel(m_SelEndPosMenu.hList,1);
    }
    else if(curIndex == 0)
    {
        BUTTON_SetPressed(m_SelEndPosMenu.hBtnRtn,1);
        LISTBOX_SetBkColor(m_SelEndPosMenu.hList,LISTBOX_CI_SEL      , GUI_WHITE);
        LISTBOX_SetSel(m_SelEndPosMenu.hList,1);
    }
    else if(curIndex == 1)
    {
        LISTBOX_SetSel(m_SelEndPosMenu.hList,0);
    }
}

static void _WinSelEndMenuCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinSelEndMenuKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinSelEndMenuKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinSelEndMenuKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinSelEndMenuCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];    
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;

    if (NULL == pTitle) pTitle = "";
flag_reset_encoder=0;
	encoder.set_end_ok=0;
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);

    m_SelEndPosMenu.hFrame = FRAMEWIN_CreateAsChild(0, 0, LCD_HSIZE+3, LCD_VSIZE+3 ,
                                    WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);
		FRAMEWIN_SetClientColor(m_SelEndPosMenu.hFrame,GUI_WHITE);
    FRAMEWIN_SetFont(m_SelEndPosMenu.hFrame, &GUI_Fontsong16all);  
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_SelEndPosMenu.hFrame, 0);           
    hWin = WM_GetFirstChild(m_SelEndPosMenu.hFrame);             
    m_SelEndPosMenu.hBtnRtn    = BUTTON_CreateAsChild(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, 23, 23,hWin,NULL, WM_CF_SHOW);
    m_SelEndPosMenu.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+23, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SelEndPosMenu.hTextNote  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+23*3, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_SelEndPosMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23*6, PER_CM_OFFSET*4.5, PER_CM_OFFSET*5, hWin, WM_CF_SHOW, NULL, NULL,NULL);
    hWin = m_SelEndPosMenu.hBtnRtn;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED,&bmbackUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,&bmbackSel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmbackUnsel,0,0);
    BUTTON_SetPressed(hWin,1);
    hWin = m_SelEndPosMenu.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    StrShowClear();
    if(LANGUAGE_CN==g_LanguageIndex) enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN==g_LanguageIndex) enc_unicode_to_utf8_str(pContentEn,strShow,STRSHOWBUF_SIZE);
    hWin = m_SelEndPosMenu.hTextNote;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetText(hWin, strShow);
    hWin = m_SelEndPosMenu.hList;
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

    StrShowClear();
    enc_unicode_to_utf8_str(menuCharOpen,strShow,STRSHOWBUF_SIZE);
    LISTBOX_AddString(hWin, strShow);
    LISTBOX_SetItemSel(hWin,0,0);
    StrShowClear();
    enc_unicode_to_utf8_str(menuCharClose,strShow,STRSHOWBUF_SIZE);
    LISTBOX_AddString(hWin, strShow);
    LISTBOX_SetItemSel(hWin,1,0);

    WM_SetCallback(WM_HBKWIN, _WinSelEndMenuCallback);
    WM_SetFocus(WM_HBKWIN);
}

static void _WinSelEndMenuDestroy(void *p)
{
    WM_DeleteWindow(m_SelEndPosMenu.hBtnRtn);  
    WM_DeleteWindow(m_SelEndPosMenu.hTextHead);
    WM_DeleteWindow(m_SelEndPosMenu.hTextNote);
    WM_DeleteWindow(m_SelEndPosMenu.hList);    
    WM_SetCallback(WM_HBKWIN, NULL);
}

void _WinSelEndMenuInterface(void *val)
{

}


WIN_INFO_TYPE g_WinSelEndPosMenu = {                      
    &m_SelEndPosMenu.hFrame,
    _WinSelEndMenuCreate,
    _WinSelEndMenuDestroy
};

typedef struct {
			GUI_HWIN hFrame;        
			GUI_HWIN hImage_CB_1;   
			GUI_HWIN hImage_CB_2;   
			GUI_HWIN hBtnRtn;       
			GUI_HWIN hBtnLeft;      
			GUI_HWIN hBtnRight;     
			GUI_HWIN hTextHeader;   
			GUI_HWIN hTextInfo;     
			GUI_HWIN hTextHelp;     
			GUI_HWIN hTextEnter;    
			GUI_HWIN hMsg;          
			GUI_HWIN hImage;        
			GUI_HWIN hImage1;       
			GUI_HWIN hImage_left;   
			GUI_HWIN hImage_right;  
			WM_HTIMER hTimer;       
			unsigned char selIndex;
			unsigned short *pSetState;
			unsigned short *pGetState;
			unsigned char cnt;
			char *pOpen;
			char *pClose;
}ENDPOS_OPERATION_TYPE;

static ENDPOS_OPERATION_TYPE m_WinEndPosOp = {0};     
void _WinEndPosOpKeyDown(void)
{
#if 1
	motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
	motorset.stop=20;
    if(m_WinEndPosOp.selIndex==2)
    {
        BUTTON_SetPressed(m_WinEndPosOp.hBtnRtn,0);
        BUTTON_SetPressed(m_WinEndPosOp.hBtnLeft,1);
        m_WinEndPosOp.selIndex = 3;
        return ;
    }
    else if(m_WinEndPosOp.selIndex==3)  
    {
        BUTTON_SetPressed(m_WinEndPosOp.hBtnLeft,0);
        BUTTON_SetPressed(m_WinEndPosOp.hBtnRight,1);
        m_WinEndPosOp.selIndex = 4;
        return ;
    }
    else if(m_WinEndPosOp.selIndex==4)  
    {
         m_WinEndPosOp.selIndex = 0;
         BUTTON_SetPressed(m_WinEndPosOp.hBtnRight,0);
         TEXT_SetBkColor(m_WinEndPosOp.hTextHelp,GUI_ORANGE);
         return ;		
    }
    else if(m_WinEndPosOp.selIndex==0)  
    {
				#if 1
			if(set_end.liju==0)
			{
				 m_WinEndPosOp.selIndex=1;
				 TEXT_SetBkColor(m_WinEndPosOp.hTextHelp,GUI_WHITE);
				 TEXT_SetBkColor(m_WinEndPosOp.hTextEnter,GUI_ORANGE);
				 return ;
			}else
			if(set_end.liju==1)
			{
				TEXT_SetBkColor(m_WinEndPosOp.hTextEnter,GUI_WHITE);
				TEXT_SetBkColor(m_WinEndPosOp.hTextHelp,GUI_WHITE);
       BUTTON_SetPressed(m_WinEndPosOp.hBtnRtn,1);
       m_WinEndPosOp.selIndex = 2;
       return ;
			}
			#endif
    }
    else if(m_WinEndPosOp.selIndex==1) 
    {
       TEXT_SetBkColor(m_WinEndPosOp.hTextEnter,GUI_WHITE);
       BUTTON_SetPressed(m_WinEndPosOp.hBtnRtn,1);
       m_WinEndPosOp.selIndex = 2;
       return ;
    }
#endif
}

void _WinEndPosOpKeyUp(void)
{
#if 1
	motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
	motorset.stop=19;
    if(m_WinEndPosOp.selIndex==2)
    {
			if(set_end.liju==0)
			{
        TEXT_SetBkColor(m_WinEndPosOp.hTextEnter,GUI_ORANGE);
        BUTTON_SetPressed(m_WinEndPosOp.hBtnRtn,0);
        m_WinEndPosOp.selIndex = 1;
        return ;
			}else
			if(set_end.liju==1)
			{
				TEXT_SetBkColor(m_WinEndPosOp.hTextEnter,GUI_WHITE);
				 TEXT_SetBkColor(m_WinEndPosOp.hTextHelp,GUI_ORANGE);
				BUTTON_SetPressed(m_WinEndPosOp.hBtnRtn,0);
				 m_WinEndPosOp.selIndex = 0;
				 return ;
			}
    }
    else if(m_WinEndPosOp.selIndex==3)   
    {
        BUTTON_SetPressed(m_WinEndPosOp.hBtnLeft,0);
        BUTTON_SetPressed(m_WinEndPosOp.hBtnRtn,1);
        m_WinEndPosOp.selIndex = 2;
        return ;
    }
    else if(m_WinEndPosOp.selIndex==4)  
    {
         m_WinEndPosOp.selIndex = 3;
         BUTTON_SetPressed(m_WinEndPosOp.hBtnRight,0);
         BUTTON_SetPressed(m_WinEndPosOp.hBtnLeft,1);
         return ;
    }
    else if(m_WinEndPosOp.selIndex==0) 
    {
       m_WinEndPosOp.selIndex=4;
       TEXT_SetBkColor(m_WinEndPosOp.hTextHelp,GUI_WHITE);
       BUTTON_SetPressed(m_WinEndPosOp.hBtnRight,1);
       return ;
    }
    else if(m_WinEndPosOp.selIndex==1)   
    {
       TEXT_SetBkColor(m_WinEndPosOp.hTextEnter,GUI_WHITE);
       TEXT_SetBkColor(m_WinEndPosOp.hTextHelp,GUI_ORANGE);
       m_WinEndPosOp.selIndex = 0;
       return ;
    }
#endif
}



extern void Restart_Encoder(int set);
void _WinEndPosOpKeyEnter(void)                  
{
    int id = m_WinEndPosOp.selIndex;
    if(timer.flag_3sTAB1==1)
	{
		set_end.handle_stop=0;   
	}else
	{
		set_end.handle_stop=1;   
	}
	timer.flag_3sTAB1_start=0;
    if(m_WinEndPosOp.selIndex==0)            
    {
        WIN_Enter(&id);
        return;
    }
    else if(m_WinEndPosOp.selIndex==1)     
    {
        flag_reset_encoder=1;
        if(encoder.dir_flag==2)
        {
            set_end.flag_open=1;
            powerboard.current_close = powerboard.current_up;
        }else
        if(encoder.dir_flag==1)
        {
            set_end.flag_close=1;
            powerboard.current_open = powerboard.current_up;
        }
        return;	
    }
    else if(m_WinEndPosOp.selIndex==2)            
    {
        WIN_Exit(0);
        return;
    }
    else if(m_WinEndPosOp.selIndex==3)        
    {
        SPEED_Stand=dataStructInterface.speed_close;
        TORQUE_Stand=dataStructInterface.moment_close;
        (*m_WinEndPosOp.pClose) = 0x5a;
        if(BUTTON_IsPressed(m_WinEndPosOp.hBtnLeft))
        {
            if(set_end.handle_stop==0)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
                motorset_s=6;
            }else
            if(set_end.handle_stop==1)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                motorset.stop=18;
            }
        }else
        {
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
            motorset.stop=18;
        }
    }
    else if(m_WinEndPosOp.selIndex==4)      
    {
        SPEED_Stand=dataStructInterface.speed_open;
        TORQUE_Stand=dataStructInterface.moment_open;
        (*m_WinEndPosOp.pOpen) = 0x2a;
        if(BUTTON_IsPressed(m_WinEndPosOp.hBtnRight))
        {
            if(set_end.handle_stop==0)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
                motorset_n=6;
            }else
            if(set_end.handle_stop==1)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                motorset.stop=17;
            }
        }else
        {
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
            motorset.stop=16;
        }
    }
}

void _WinEndPosOpKeyTAB()
{
	timer.flag_3sTAB1_start=1;
}

void  _WinEndPosOpKeyENTER_BEF()
{
	if(BUTTON_IsPressed(m_WinEndPosOp.hBtnLeft))
    {
        SPEED_Stand=dataStructInterface.speed_close;
        TORQUE_Stand=dataStructInterface.moment_close;
        if(flag_stop_button_left==0)
        {
            flag_estop=0;
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
            motorset_s=5;
            GUI_Delay(10);
            WM_DisableWindow(m_WinEndPosOp.hBtnLeft);
            GUI_Delay(10);
            BUTTON_SetPressed(m_WinEndPosOp.hBtnLeft,1);
            WM_EnableWindow(m_WinEndPosOp.hBtnLeft);
            flag_stop_button_left=1;
        }
        else if(flag_stop_button_left==1)
        {
            if(set_end.handle_stop==1)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_s; 
                motorset_s=4;
            }else
            {
                flag_stop_button_left=0;
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;  
                motorset.stop=15;
            }
        }		
    }
    else if(BUTTON_IsPressed(m_WinEndPosOp.hBtnRight))
    {
        SPEED_Stand=dataStructInterface.speed_open;
        TORQUE_Stand=dataStructInterface.moment_open;
        flag_estop=0;
        if(set_end.handle_stop==1)
        {
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;  	
            motorset_n=5;
        }
        else if(set_end.handle_stop==0)
        {
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_n; 
            motorset_n=4;
        }
        GUI_Delay(10);
        WM_DisableWindow(m_WinEndPosOp.hBtnRight);
        GUI_Delay(10);
        BUTTON_SetPressed(m_WinEndPosOp.hBtnRight,1);
        WM_EnableWindow(m_WinEndPosOp.hBtnRight);			
    }
}
static void _WinEndPosOpCallback_Refesh()
{
	if(dataStructInterface.closeDir ==0)  //顺时针
    {
        if(encoder.dir_flag==2)  //关方向
        {
            encoder.set_first=1;
        }
        else if(encoder.dir_flag==1)  //开方向
        {
            encoder.set_first=2;
        }
    }else
    if(dataStructInterface.closeDir ==1)  //逆时针
    {
        if(encoder.dir_flag==2)  //关方向
        {
            encoder.set_first=3;
        }
        else if(encoder.dir_flag==1)  //开方向
        {
            encoder.set_first=4;
        }
    }	
				
    #if 1
    if(encoder.dir_flag==2) 
    {
        if(dataStructInterface.openOffMode==1)
        {
            if(set_end.flag_liju==1)
            {
                set_end.liju=0;
            }else
            if(set_end.flag_liju==0)
            {
                set_end.liju=1;
            }
            
        }else
        if(dataStructInterface.openOffMode==0)
        {
            set_end.liju=0;
        }
    }else
    if(encoder.dir_flag==1) 
    {
        if(dataStructInterface.closeOffMode==1)
        {
            if(set_end.flag_liju==1)
            {
                set_end.liju=0;
            }else
            if(set_end.flag_liju==0)
            {
                set_end.liju=1;
            }
        }else
        if(dataStructInterface.closeOffMode==0)
        {
            set_end.liju=0;
        }
    }
    #endif
}

static void _WinEndPosOpCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_TIMER:
        WM_RestartTimer(pMsg->Data.v, 100);
		_WinEndPosOpCallback_Refesh();
		#if 1
		if(flag_reset_encoder==1)
        {
            m_WinEndPosOp.cnt++;
            if(m_WinEndPosOp.cnt>5)
            {
                if(flag_reset_encoder==1)
               {
                    id = 1;
                    WIN_Enter(&id);
                }
            }
        }
		#endif
        break;
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
            case GUI_KEY_DOWN:
                _WinEndPosOpKeyDown();
                break;
            case GUI_KEY_UP:
                _WinEndPosOpKeyUp();
                break;
            case GUI_KEY_ENTER:
                _WinEndPosOpKeyEnter();
                break;
            case GUI_KEY_TAB:
                _WinEndPosOpKeyTAB();
                break;
            case GUI_KEY_ENTER_BEF:
                _WinEndPosOpKeyENTER_BEF();
                break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}
static void _WinEndPosOpCreate(void *p)
{
    unsigned int i=0;
	MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
	const char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    char numShow[8];
    GUI_HWIN        hWin        = 0;
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    GUI_AA_SetFactor(MAG);
    motorset.end_setok=0;
	encoder.set_end_ok=0;
    set_end.flag_setend=1;
    if (NULL == pTitle) pTitle = "";
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);

		if(encoder.Set_Ready==0)
		{
			if(dataStructInterface.closeDir ==0)
			{
			motorset.DIR=1;
			}else
			if(dataStructInterface.closeDir ==1)
			{
			motorset.DIR=2;
			}	
			motorset.DIR_set_flag=1;
		}
	#if 1     
	m_WinEndPosOp.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_WinEndPosOp.hImage_CB_1,&bmComBack_1);
	
	m_WinEndPosOp.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_WinEndPosOp.hImage_CB_2,&bmComBack_2);
    #endif
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_WinEndPosOp.hFrame, 0);           
    hWin = WM_GetFirstChild(m_WinEndPosOp.hFrame);           
    m_WinEndPosOp.hTextHeader= TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+23, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    hWin = WM_GetFirstChild(m_WinEndPosOp.hFrame);            
    m_WinEndPosOp.hBtnRtn    = BUTTON_CreateAsChild(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, 40, 22,hWin,NULL, WM_CF_SHOW);    
    hWin = m_WinEndPosOp.hBtnRtn;		
    BUTTON_SetSkin(hWin,SKIN_Btn_Btn);
    BUTTON_SetPressed(hWin,0);

	if(pMenu->data->menunum==1)  //设置末端位置--开
    {
        encoder.dir_flag=2;
    }
    else if(pMenu->data->menunum==2)  //设置末端位置--关
    {
        encoder.dir_flag=1;
    }
    
    header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+41, DEBUG_Y_OFFSET,184-20,23);
    hWin = m_WinEndPosOp.hTextHeader;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
		
    DrawGradientH_PointWhite(50,35,270,35);
    GUI_SetColor(GUI_BLACK);	
    GUI_SetPenSize(1);	
    GUI_DrawLine(70,107,252,107);	
    GUI_DrawLine(70,140,252,140);
		
		
    hWin = WM_GetFirstChild(m_WinEndPosOp.hFrame);
    m_WinEndPosOp.hBtnRight  = BUTTON_CreateAsChild(DEBUG_X_OFFSET+250-4, 95, 59, 60,hWin,NULL, WM_CF_SHOW);
    m_WinEndPosOp.hBtnLeft   = BUTTON_CreateAsChild(4,95 ,59, 60,hWin,NULL, WM_CF_SHOW);
    hWin = m_WinEndPosOp.hBtnLeft;
    BUTTON_SetSkin(hWin,SKIN_DriverLeft_Button_Return);
    if(pMenu->data->menunum==1)  //设置末端位置第一层，光标固定在右边
    {
        BUTTON_SetPressed(hWin,0);
    }
    else if(pMenu->data->menunum==2)  //设置末端位置第二层，光标固定在左边
    {
        BUTTON_SetPressed(hWin,1);
        m_WinEndPosOp.selIndex=3;
    }

    hWin = m_WinEndPosOp.hBtnRight;
    BUTTON_SetSkin(hWin,SKIN_DriverRight_Button_Return);
    if(pMenu->data->menunum==1)  //设置末端位置第一层，光标固定在右边
    {
        BUTTON_SetPressed(hWin,1);
        m_WinEndPosOp.selIndex=4;
    }
    else if(pMenu->data->menunum==2)  //设置末端位置第二层，光标固定在左边
    {
        BUTTON_SetPressed(hWin,0);
    }
    m_WinEndPosOp.hImage1 = IMAGE_CreateEx(3,80,320,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);	
    #if 1		
        if(dataStructInterface.closeOffMode==1)
		{
			m_WinEndPosOp.hImage_left = IMAGE_CreateEx(-2,77+5+2,70,77,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
			IMAGE_SetBitmap(m_WinEndPosOp.hImage_left,&bmliju_left);
		}else
		{
			m_WinEndPosOp.hImage_left = IMAGE_CreateEx(-2+4,78+2+2+6,67,71,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
			IMAGE_SetBitmap(m_WinEndPosOp.hImage_left,&bmxingcheng_left);
		}	
		if(dataStructInterface.openOffMode==1)
		{
			m_WinEndPosOp.hImage_right = IMAGE_CreateEx(244,76+5+2,76,81,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);	
			IMAGE_SetBitmap(m_WinEndPosOp.hImage_right,&bmliju_right);
		}else
		{
			m_WinEndPosOp.hImage_right = IMAGE_CreateEx(245+1+6-4,78+2+2+7,67,71,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);	
			IMAGE_SetBitmap(m_WinEndPosOp.hImage_right,&bmxingcheng_right);
		}
    #endif
    hWin = m_WinEndPosOp.hFrame;
    m_WinEndPosOp.hTextInfo  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+23*2, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_VCENTER , NULL, " ");
    m_WinEndPosOp.hTextHelp  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+23*8-2, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_VCENTER , NULL, " ");
    m_WinEndPosOp.hTextEnter = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+23*9, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_VCENTER , NULL, " ");
    StrShowClear();
    if(pMenu->data->menunum==1)
    {
        if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str(menuCharSetEndPosCn_Open,strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str(menuCharSetEndPosEn_Open,strShow,STRSHOWBUF_SIZE);
    }
    else if(pMenu->data->menunum==2)
    {
        if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str(menuCharSetEndPosCn_Close,strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str(menuCharSetEndPosCn_Close,strShow,STRSHOWBUF_SIZE);
    }
    hWin = m_WinEndPosOp.hTextInfo;
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetText(hWin, strShow);

    DrawGradientH_PointWhite(50,183,270,183);
    DrawGradientH_PointWhite(50,210,270,210);
    StrShowClear();
    if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str(menuCharHelpCn,strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str(menuCharHelpEn,strShow,STRSHOWBUF_SIZE);
    hWin = m_WinEndPosOp.hTextHelp;
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetText(hWin, strShow);

    StrShowClear();
    if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str(menuCharEnterEndPosCn,strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str(menuCharEnterEndPosEn,strShow,STRSHOWBUF_SIZE);
    hWin = m_WinEndPosOp.hTextEnter;
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetText(hWin, strShow);

    m_WinEndPosOp.pOpen  = (char *)pMenu->data->menutitleCn;
    m_WinEndPosOp.pClose = (char *)pMenu->data->menutitleEn;
    m_WinEndPosOp.pSetState = pMenu->data->menuattri;
    m_WinEndPosOp.pGetState = pMenu->data->menusel;
    m_WinEndPosOp.cnt    = 0;

    m_WinEndPosOp.hTimer = WM_CreateTimer(WM_HBKWIN,0,1000,0);

    WM_SetCallback(WM_HBKWIN,_WinEndPosOpCallback);
    WM_SetFocus(WM_HBKWIN);
}



static void _WinEndPosOpDestroy(void *p)
{
			WM_DeleteWindow(m_WinEndPosOp.hImage_CB_1);           
			WM_DeleteWindow(m_WinEndPosOp.hImage_CB_2);           
			WM_DeleteWindow(m_WinEndPosOp.hBtnRtn);               
			WM_DeleteWindow(m_WinEndPosOp.hBtnLeft);              
			WM_DeleteWindow(m_WinEndPosOp.hBtnRight);             
			WM_DeleteWindow(m_WinEndPosOp.hTextHeader);           
			WM_DeleteWindow(m_WinEndPosOp.hTextInfo);             
			WM_DeleteWindow(m_WinEndPosOp.hTextHelp);             
			WM_DeleteWindow(m_WinEndPosOp.hTextEnter);            
			WM_DeleteWindow(m_WinEndPosOp.hMsg);                  
			WM_DeleteWindow(m_WinEndPosOp.hImage);                
			WM_DeleteWindow(m_WinEndPosOp.hImage1);               
			WM_DeleteWindow(m_WinEndPosOp.hImage_left);           
			WM_DeleteWindow(m_WinEndPosOp.hImage_right);          
	WM_DeleteTimer(m_WinEndPosOp.hTimer); 
    WM_SetCallback(WM_HBKWIN,NULL);
    memset(&m_WinEndPosOp, 0, sizeof(m_WinEndPosOp));

}


void _WinEndPosOpInterface(void *val)
{

}


WIN_INFO_TYPE g_WinEndPosOp = {  //设置第一步
    &m_WinEndPosOp.hFrame,
    _WinEndPosOpCreate,
    _WinEndPosOpDestroy,
};

typedef struct {
    GUI_HWIN hFrame;       

    GUI_HWIN hImage_CB_1;  
    GUI_HWIN hImage_CB_2;  
    GUI_HWIN hBtnRtn;      
    GUI_HWIN hBtnLeft;     
    GUI_HWIN hBtnRight;    
    GUI_HWIN hTextHeader;  
    GUI_HWIN hTextInfo;    
    GUI_HWIN hTextFeedNum; 
    GUI_HWIN hTextFeedBack;
    GUI_HWIN hTextHelp;    
    GUI_HWIN hTextEnter;   
    GUI_HWIN hImage;       
    GUI_HWIN hImage1;      
    GUI_HWIN hImage_left;  
    GUI_HWIN hImage_right; 
    unsigned char selIndex; 
    unsigned short *pSetState;
    unsigned short *pGetState;
    char *pOpen;
    char *pClose;
    WM_HTIMER hTimer;
}ENDPOS_OPERATION_TYPE_T;

static ENDPOS_OPERATION_TYPE_T m_WinEndPosOpT2 = {0};    
void _WinEndPosOpT2KeyDown(void)
{
#if 1
	motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
	motorset.stop=14;

if(*m_WinEndPosOpT2.pGetState==0x5a)
{
    if(m_WinEndPosOpT2.selIndex==1)
    {
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRtn,0);
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnLeft,1);
        m_WinEndPosOpT2.selIndex = 2;
        return ;
    }
    else if(m_WinEndPosOpT2.selIndex==2)
    {
			
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnLeft,0);
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRight,1);
        m_WinEndPosOpT2.selIndex = 3;
        return ;
			
    }
    else if(m_WinEndPosOpT2.selIndex==3)  
    {
			if(key_mlx90363.flag_runerror==1)
			{
				m_WinEndPosOpT2.selIndex=1;
				BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRight,0);
				BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRtn,1);
                TEXT_SetBkColor(m_WinEndPosOpT2.hTextEnter,GUI_WHITE);
			}else
			{
				m_WinEndPosOpT2.selIndex=0;
				BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRtn,0);
				BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRight,0);
				TEXT_SetBkColor(m_WinEndPosOpT2.hTextEnter,GUI_ORANGE);
				return ;
			}		
    }
    else if(m_WinEndPosOpT2.selIndex==0)
    {
       m_WinEndPosOpT2.selIndex=1;
       BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRtn,1);
       TEXT_SetBkColor(m_WinEndPosOpT2.hTextEnter,GUI_WHITE);
       return ;
    }
}
else
{
    if(m_WinEndPosOpT2.selIndex==1)
    {
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRtn,0);
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnLeft,1);
        m_WinEndPosOpT2.selIndex = 2;
        return ;
    }
    else if(m_WinEndPosOpT2.selIndex==2)
    {
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnLeft,0);
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRight,1);
        m_WinEndPosOpT2.selIndex = 3;
        return ;
    }
    else if(m_WinEndPosOpT2.selIndex==3)
    {
         m_WinEndPosOpT2.selIndex = 1;
         BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRight,0);
         BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRtn,1);
         return ;
    }
}
#endif
}

void _WinEndPosOpT2KeyUp(void)
{
#if 1
if(*m_WinEndPosOpT2.pGetState==0x5a)
{
	motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
	motorset.stop=13;
    if(m_WinEndPosOpT2.selIndex==1)
    {
			if(key_mlx90363.flag_runerror==1)
			{
				BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRtn,0);
				BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRight,1);
				 TEXT_SetBkColor(m_WinEndPosOpT2.hTextEnter,GUI_WHITE);
				m_WinEndPosOpT2.selIndex = 3;
        return ;
			}else
			{
			TEXT_SetBkColor(m_WinEndPosOpT2.hTextEnter,GUI_ORANGE);
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRtn,0);
        m_WinEndPosOpT2.selIndex = 0;
        return ;
			}
    }
    else if(m_WinEndPosOpT2.selIndex==0)
    {
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRight,1);
        TEXT_SetBkColor(m_WinEndPosOpT2.hTextEnter,GUI_WHITE);
        m_WinEndPosOpT2.selIndex = 3;
        return ;
    }
    else if(m_WinEndPosOpT2.selIndex==2)
    {
         m_WinEndPosOpT2.selIndex = 1;
         BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRtn,1);
         BUTTON_SetPressed(m_WinEndPosOpT2.hBtnLeft,0);
         return ;
    }
    else if(m_WinEndPosOpT2.selIndex==3)
    {
			
       m_WinEndPosOpT2.selIndex=2;
       BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRight,0);
         BUTTON_SetPressed(m_WinEndPosOpT2.hBtnLeft,1);
       return ;
    }
}
else
{
    if(m_WinEndPosOpT2.selIndex==1)
    {
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRight,1);
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRtn,0);
        m_WinEndPosOpT2.selIndex = 3;
        return ;
    }
    else if(m_WinEndPosOpT2.selIndex==2)
    {
         m_WinEndPosOpT2.selIndex = 1;
         BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRtn,1);
         BUTTON_SetPressed(m_WinEndPosOpT2.hBtnLeft,0);
         return ;
    }
    else if(m_WinEndPosOpT2.selIndex==3)
    {
       m_WinEndPosOpT2.selIndex=2;
       BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRight,0);
         BUTTON_SetPressed(m_WinEndPosOpT2.hBtnLeft,1);
       return ;
    }
}
#endif
}


void _WinEndPosOpT2KeyEnter(void)
{
	int id = m_WinEndPosOpT2.selIndex;
    #if 1
	if(timer.flag_3sTAB2==1)
	{
		set_end.handle_stopT2=0;   
	}else
	{
		set_end.handle_stopT2=1;   
	}
	timer.flag_3sTAB2_start=0;
	#endif
    
    if(m_WinEndPosOpT2.selIndex==0)  
    {
        data_figures.READ_ALL_903=key_mlx90363.Read_all;
        eeprom.flag_90363=1;
        if(encoder.dir_flag==2)
        {
            powerboard.current_open = powerboard.current_up;
        }else
        if(encoder.dir_flag==1)
        {
            powerboard.current_close = powerboard.current_up;
        }
        flash_flag.all_move=1;
        flash_flag.all_move1=1;
        flash_flag.all_move2=1;
        flash_flag.all_move3=1;
        flash_flag.all_move4=1;
        motorset.end_setok=0;
        flag_stop_button_left=0;
        WIN_Enter(&id);
			
        return;
    }
    else if(m_WinEndPosOpT2.selIndex==1)    
    {
        WIN_Exit(0);
        return;
    }
    else if(m_WinEndPosOpT2.selIndex==2)  
    {
        SPEED_Stand=dataStructInterface.speed_close;
        TORQUE_Stand=dataStructInterface.moment_close;
        (*m_WinEndPosOpT2.pClose) = 0x5a;
        if(BUTTON_IsPressed(m_WinEndPosOpT2.hBtnLeft))
        {
            #if 1
            if(set_end.handle_stopT2==0)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
                motorset_s=3;
            }else
            if(set_end.handle_stopT2==1)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                motorset.stop=12;
            }
					
            #endif
        }else
        {
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
            motorset.stop=11;
        }					
    }
    else if(m_WinEndPosOpT2.selIndex==3)   
    {
        SPEED_Stand=dataStructInterface.speed_open;
        TORQUE_Stand=dataStructInterface.moment_open;
        (*m_WinEndPosOpT2.pOpen) = 0x5a;
        if(BUTTON_IsPressed(m_WinEndPosOpT2.hBtnRight))
        {
            #if 1
            if(set_end.handle_stopT2==0)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
                motorset_n=3;
            }else
            if(set_end.handle_stopT2==1)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                motorset.stop=10;
            }				
            #endif
        }else
        {
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
            motorset.stop=9;
        }
    }
}

void _WinEndPosOpT2KeyTAB()
{
	timer.flag_3sTAB2_start=1;
}

void _WinEndPosOpT2KeyENTER_BEF()
{
	if(encoder.SET_read==1 )
	{
		encoder.dufangxianng_set_flag=1;
		encoder.SET_read=0;
	}
	if(BUTTON_IsPressed(m_WinEndPosOpT2.hBtnLeft))
    {
        if(encoder.set_flag==0)
        {
            if((encoder.set_first==1)||(encoder.set_first==3))  
            {
                encoder.set_ok=1;				
            }else
            if((encoder.set_first==2)||(encoder.set_first==4))  
            {
                encoder.set_ok=0;
            }
            encoder.set_flag=1;
        }
        SPEED_Stand=dataStructInterface.speed_close;
        TORQUE_Stand=dataStructInterface.moment_close;
        if(flag_stop_button_left==0)
        {
            flag_estop=0;
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
            motorset_s=2;
            GUI_Delay(10);
            WM_DisableWindow(m_WinEndPosOpT2.hBtnLeft);
            GUI_Delay(10);
            BUTTON_SetPressed(m_WinEndPosOpT2.hBtnLeft,1);
            WM_EnableWindow(m_WinEndPosOpT2.hBtnLeft);
            flag_stop_button_left=1;
        }else
        if(flag_stop_button_left==1)
        {
            if(set_end.handle_stopT2==1)
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_s; 
                motorset_s=1;
            }else
            {
                flag_stop_button_left=0;
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t; 
                motorset.stop=8;
            }
        }		
    }
    else if(BUTTON_IsPressed(m_WinEndPosOpT2.hBtnRight))
    {
        if(encoder.set_flag==0)
        {
            if((encoder.set_first==1)||(encoder.set_first==3)) 
            {
                encoder.set_ok=0;
            }else
            if((encoder.set_first==2)||(encoder.set_first==4)) 
            {
                encoder.set_ok=1;		
            }
            encoder.set_flag=1;
        }			
        SPEED_Stand=dataStructInterface.speed_open;
        TORQUE_Stand=dataStructInterface.moment_open;
        flag_estop=0;
        if(set_end.handle_stopT2==1)
        {
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;  
            motorset_n=2;			
        }else
        if(set_end.handle_stopT2==0)
        {
            motorset.DIR_MOTOR=motorset.DIR_MOTOR_n; 
            motorset_n=1;
        }
        GUI_Delay(10);
        WM_DisableWindow(m_WinEndPosOpT2.hBtnRight);
        GUI_Delay(10);
        BUTTON_SetPressed(m_WinEndPosOpT2.hBtnRight,1);
        WM_EnableWindow(m_WinEndPosOpT2.hBtnRight);			
    }
}

static void _WinEndPosOpT2Refresh()
{
	set_end.OffMode=0;
	if(set_end.flag_openOffMode==1)
	{
		set_end.OffMode=1;
	}
	if(set_end.flag_openOffMode==2)
	{
		set_end.OffMode=2;
	}
	if(set_end.flag_closeOffMode==1)
	{
		set_end.OffMode=1;
	}
	if(set_end.flag_closeOffMode==2)
	{
		set_end.OffMode=2;
	}
    #if 1			
    if(encoder.dir_flag==2)  
	{
		if(dataStructInterface.closeOffMode==1)
		{
			if(set_end.flag_liju==1)
			{
				set_end.liju=0;
				set_end.liju2=1;
			}else
			if(set_end.flag_liju==0)
			{
				set_end.liju=1;
				set_end.liju2=0;
			}							
		}else
		if(dataStructInterface.closeOffMode==0)
		{
			set_end.liju=0;
			set_end.liju2=0;
		}
	}else
	if(encoder.dir_flag==1)  
	{
		if(dataStructInterface.openOffMode==1)
		{
			if(set_end.flag_liju==1)
			{
				set_end.liju=0;
				set_end.liju2=1;
			}else
			if(set_end.flag_liju==0)
			{
				set_end.liju=1;
				set_end.liju2=0;
			}
		}else
		if(dataStructInterface.openOffMode==0)
		{
			set_end.liju=0;
			set_end.liju2=0;
		}
	}
    #endif
}

static void _WinEndPosOpT2Callback_Refesh()
{
	char numShow[8];
	if((key_mlx90363.ssi_m==0)&&(key_mlx90363.ssi_s==0))
	{
		motorset.end_setok=1;
	}else
	{
		sprintf(numShow,"%1d.%1d",0,0);
		TEXT_SetText(m_WinEndPosOpT2.hTextFeedNum, numShow);	
	}
	if(motorset.end_setok==1)
	{
            if(encoder.set_ok==1)
			{
				sprintf(numShow,"%1d.%1d",ssi_m,ssi_s);
				if(key_mlx90363.ssi_s>1)
				{
					if(encoder.dufangxiang==1)
					{
						encoder.dufangxiang=0;
						encoder.dufangxianng_flag=1;
						encoder.Read_old=key_mlx90363.Read_now;
					}
				}
				if(encoder.dufangxianng_flag==1)
				{
					if((encoder.Read_old&0x08000000)==((key_mlx90363.Read_now)&0x08000000))
					{
						encoder.set_ok=1;
					}else
					{
						encoder.set_ok=0;
					}
				}
			}
            else if(encoder.set_ok==0)
			{
					if((key_mlx90363.ssi_m==0)&&(key_mlx90363.ssi_s==0))
					{
						sprintf(numShow,"%1d.%1d",key_mlx90363.ssi_m,key_mlx90363.ssi_s);
					}else
					{
						sprintf(numShow,"-%1d.%1d",key_mlx90363.ssi_m,key_mlx90363.ssi_s);
					}
					if(key_mlx90363.ssi_s>1)
					{
						if(encoder.dufangxiang==1)
						{
							encoder.dufangxiang=0;
							encoder.dufangxianng_flag=1;
							encoder.Read_old=0x0FFFFFFF-key_mlx90363.Read_now;
						}
					}
					if(encoder.dufangxianng_flag==1)
					{
						if((encoder.Read_old&0x08000000)==((key_mlx90363.Read_now)&0x08000000))
						{
							encoder.set_ok=1;
						}else
						{
							encoder.set_ok=0;
						}
					}
			}
		}
	TEXT_SetText(m_WinEndPosOpT2.hTextFeedNum, numShow);
}

void _WinEndPosOpT2Callback_Refesh2(void)
{
    if(set_end.liju2==1)
	{
		TEXT_SetText(m_WinEndPosOpT2.hTextHelp, "力矩关断");
		#if 1
		key_mlx90363.flag_runerror=0;
		#endif
	}
    else if(set_end.liju2==0)
	{
        if((key_mlx90363.ssi_m<1)&&(key_mlx90363.ssi_s<5))
		{
			set_end.flag_open=0;
			set_end.flag_close=0;
			TEXT_SetText(m_WinEndPosOpT2.hTextHelp, "设定无效范围");
			key_mlx90363.flag_runerror=1;				
		}else
		{
			if(encoder.set_ok==1)
			{
				if((dataStructInterface.closeOffMode==0)&&(encoder.dir_flag==2))
				{
					TEXT_SetText(m_WinEndPosOpT2.hTextHelp, "设定有效范围");
					key_mlx90363.flag_runerror=0;
				}else
				if((dataStructInterface.openOffMode==0)&&(encoder.dir_flag==1))
				{
					TEXT_SetText(m_WinEndPosOpT2.hTextHelp, "设定有效范围");
					key_mlx90363.flag_runerror=0;
				}else
				if((dataStructInterface.openOffMode==1)&&(encoder.dir_flag==1))
				{
					TEXT_SetText(m_WinEndPosOpT2.hTextHelp, "设定无效范围");
					key_mlx90363.flag_runerror=1;	
				}else
				if((dataStructInterface.closeOffMode==1)&&(encoder.dir_flag==2))
				{
					TEXT_SetText(m_WinEndPosOpT2.hTextHelp, "设定无效范围");
					key_mlx90363.flag_runerror=1;	
				}
			}else
			{
				TEXT_SetText(m_WinEndPosOpT2.hTextHelp, "设定无效范围");
				key_mlx90363.flag_runerror=1;
			}
		}
	}
}
static void _WinEndPosOpT2Callback(WM_MESSAGE * pMsg)
{
    int     id = 0;
    char numShow[8];
    switch (pMsg->MsgId)
    {
    case WM_TIMER:
        WM_RestartTimer(pMsg->Data.v, 100);
        flag_reset_encoder=0;
        _WinEndPosOpT2Callback_Refesh();
        #if 1
        TEXT_SetFont(m_WinEndPosOpT2.hTextHelp,&GUI_Fontsong16all);
        GUI_UC_SetEncodeUTF8();
		_WinEndPosOpT2Refresh();
		_WinEndPosOpT2Callback_Refesh2();
        #endif
        break;
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
            case GUI_KEY_DOWN:
                _WinEndPosOpT2KeyDown();
                break;
            case GUI_KEY_UP:
                _WinEndPosOpT2KeyUp();
                break;
            case GUI_KEY_ENTER:
                _WinEndPosOpT2KeyEnter();
                break;
            case GUI_KEY_TAB:
                _WinEndPosOpT2KeyTAB();
                break;
            case GUI_KEY_ENTER_BEF:
                _WinEndPosOpT2KeyENTER_BEF();
                break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}
static void _WinEndPosOpT2Create(void *p)
{
    unsigned int i=0;
	MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    char numShow[8];
    GUI_HWIN        hWin        = 0;

    GUI_SetBkColor(GUI_WHITE);     
    GUI_Clear();
    GUI_AA_SetFactor(MAG);
		encoder.SET_read=1;
	encoder.set_end_ok=1;
	set_end.flag_liju=0;
    if(pMenu->data->menunum==1)
    {			
    }else
    if(pMenu->data->menunum==2)
    {			
    }
    if (NULL == pTitle) pTitle = "";
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
    #if 1     
	m_WinEndPosOpT2.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_WinEndPosOpT2.hImage_CB_1,&bmComBack_1);	
	m_WinEndPosOpT2.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_WinEndPosOpT2.hImage_CB_2,&bmComBack_2);
    #endif
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_WinEndPosOpT2.hFrame, 0);           
    hWin = WM_GetFirstChild(m_WinEndPosOpT2.hFrame);
    m_WinEndPosOpT2.hTextHeader= TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+23, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
	
    hWin = WM_GetFirstChild(m_WinEndPosOpT2.hFrame);           
    m_WinEndPosOpT2.hBtnRtn    = BUTTON_CreateAsChild(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, 40, 22,hWin,NULL, WM_CF_SHOW);    
    hWin = m_WinEndPosOpT2.hBtnRtn;		
    BUTTON_SetSkin(hWin,SKIN_Btn_Btn);
    BUTTON_SetPressed(hWin,0);

    DrawGradientH_PointWhite(50,35,270,35);
    GUI_SetColor(GUI_BLACK);	
    GUI_SetPenSize(1);	
    GUI_DrawLine(70,107,252,107);	
    GUI_DrawLine(70,140,252,140);
		
    header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+41, DEBUG_Y_OFFSET,184-20,23);
    hWin = m_WinEndPosOpT2.hTextHeader;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);

    hWin = WM_GetFirstChild(m_WinEndPosOpT2.hFrame);
    m_WinEndPosOpT2.hBtnRight  = BUTTON_CreateAsChild(DEBUG_X_OFFSET+250-4, 95, 59, 60,hWin,NULL, WM_CF_SHOW);
    m_WinEndPosOpT2.hBtnLeft   = BUTTON_CreateAsChild(4,95 ,59, 60,hWin,NULL, WM_CF_SHOW);
    hWin = m_WinEndPosOpT2.hBtnLeft;
    BUTTON_SetSkin(hWin,SKIN_DriverLeft_Button_Return);
    if(pMenu->data->menunum==1)
    {  
        BUTTON_SetPressed(hWin,1);
        m_WinEndPosOpT2.selIndex=2;
    }else
    if(pMenu->data->menunum==2)
    {
        BUTTON_SetPressed(hWin,0);
    }
    hWin = m_WinEndPosOpT2.hBtnRight;
    BUTTON_SetSkin(hWin,SKIN_DriverRight_Button_Return);
    BUTTON_SetPressed(hWin,1);
	if(pMenu->data->menunum==1)
    {
        BUTTON_SetPressed(hWin,0);			
    }else
    if(pMenu->data->menunum==2)
    {
        BUTTON_SetPressed(hWin,1);
        m_WinEndPosOpT2.selIndex=3;
    }
    m_WinEndPosOpT2.hImage1 = IMAGE_CreateEx(3,80,320,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
		
    #if 1
		
    if(dataStructInterface.closeOffMode==1)
    {
        m_WinEndPosOpT2.hImage_left = IMAGE_CreateEx(-2,77+7,70,77,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_WinEndPosOpT2.hImage_left,&bmliju_left);
    }else
    {
        m_WinEndPosOpT2.hImage_left = IMAGE_CreateEx(-2+4,78+2+2+6,67,71,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
        IMAGE_SetBitmap(m_WinEndPosOpT2.hImage_left,&bmxingcheng_left);
    }
		
    if(dataStructInterface.openOffMode==1)
    {
        m_WinEndPosOpT2.hImage_right = IMAGE_CreateEx(244,76+7,76,81,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);	
        IMAGE_SetBitmap(m_WinEndPosOpT2.hImage_right,&bmliju_right);
    }else
    {
        m_WinEndPosOpT2.hImage_right = IMAGE_CreateEx(245+1+6-4,78+2+2+8,67,71,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);	
        IMAGE_SetBitmap(m_WinEndPosOpT2.hImage_right,&bmxingcheng_right);
    }
    #endif
    hWin = m_WinEndPosOpT2.hFrame;
    m_WinEndPosOpT2.hTextInfo     = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+23*2, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_VCENTER , NULL, " ");
    m_WinEndPosOpT2.hTextFeedNum  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET*1.5 , DEBUG_Y_OFFSET+23*5-8, PER_CM_OFFSET*1, 23, hWin, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_VCENTER , NULL, " ");
    m_WinEndPosOpT2.hTextFeedBack = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET*2.5 , DEBUG_Y_OFFSET+23*5-8, PER_CM_OFFSET*3-23, 23, hWin, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_VCENTER , NULL, " ");
    m_WinEndPosOpT2.hTextHelp     = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+23*7, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_VCENTER , NULL, " ");
    m_WinEndPosOpT2.hTextEnter    = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+23*9, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_VCENTER , NULL, " ");

    StrShowClear();
    if(pMenu->data->menunum==1)
    {
        if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str((const char *)menuCharSetEndPosCn_Close,strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str((const char *) menuCharSetEndPosEn_Close,strShow,STRSHOWBUF_SIZE);
    }else
    if(pMenu->data->menunum==2)
    {
        if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str((const char *)menuCharSetEndPosCn_Open,strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str((const char *) menuCharSetEndPosEn_Open,strShow,STRSHOWBUF_SIZE);
    }
    hWin = m_WinEndPosOpT2.hTextInfo;
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetText(hWin, strShow);
    StrShowClear();		
		sprintf(numShow,"%1d.%1d",0,0);
    hWin = m_WinEndPosOpT2.hTextFeedNum;
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetText(hWin, numShow);
		
    StrShowClear();
    if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str((const char *)menuCharSetDataEndPosCn,strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str((const char *)menuCharSetDataEndPosEn,strShow,STRSHOWBUF_SIZE);
    hWin = m_WinEndPosOpT2.hTextFeedBack;
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetText(hWin, strShow);

    StrShowClear();
    if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str((const char *)menuCharSetRangeEndPosCn,strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str((const char *)menuCharSetRangeEndPosEn,strShow,STRSHOWBUF_SIZE);
    hWin = m_WinEndPosOpT2.hTextHelp;
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetText(hWin, strShow);

    DrawGradientH_PointWhite(50,200,270,200);
    StrShowClear();
    if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str((const char *)menuCharEnterEndPosCn,strShow,STRSHOWBUF_SIZE);
    else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str((const char *)menuCharEnterEndPosEn,strShow,STRSHOWBUF_SIZE);
    hWin = m_WinEndPosOpT2.hTextEnter;
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetText(hWin, strShow);

    m_WinEndPosOpT2.pOpen  = (char *)pMenu->data->menutitleCn;
    m_WinEndPosOpT2.pClose = (char *)pMenu->data->menutitleEn;
    m_WinEndPosOpT2.pSetState = pMenu->data->menuattri;
		
    m_WinEndPosOpT2.pGetState = pMenu->data->menusel;
    sprintf(numShow,"%1d.%1d",0,0);
    TEXT_SetText(m_WinEndPosOpT2.hTextFeedNum, numShow);
		
    *m_WinEndPosOpT2.pGetState=0x5a;
    m_WinEndPosOpT2.hTimer = WM_CreateTimer(WM_HBKWIN,0,100,0);

    WM_SetCallback(WM_HBKWIN,_WinEndPosOpT2Callback);
    WM_SetFocus(WM_HBKWIN);
}



static void _WinEndPosOpT2Destroy(void *p)
{
    WM_DeleteTimer(m_WinEndPosOpT2.hTimer);
	
		WM_DeleteWindow(m_WinEndPosOpT2.hImage_CB_1);   
		WM_DeleteWindow(m_WinEndPosOpT2.hImage_CB_2);   
		WM_DeleteWindow(m_WinEndPosOpT2.hBtnRtn);       
		WM_DeleteWindow(m_WinEndPosOpT2.hBtnLeft);      
		WM_DeleteWindow(m_WinEndPosOpT2.hBtnRight);     
		WM_DeleteWindow(m_WinEndPosOpT2.hTextHeader);   
		WM_DeleteWindow(m_WinEndPosOpT2.hTextInfo);     
		WM_DeleteWindow(m_WinEndPosOpT2.hTextFeedNum);  
		WM_DeleteWindow(m_WinEndPosOpT2.hTextFeedBack); 
		WM_DeleteWindow(m_WinEndPosOpT2.hTextHelp);     
		WM_DeleteWindow(m_WinEndPosOpT2.hTextEnter);    
		WM_DeleteWindow(m_WinEndPosOpT2.hImage);        
		WM_DeleteWindow(m_WinEndPosOpT2.hImage1);       
		WM_DeleteWindow(m_WinEndPosOpT2.hImage_left);   
		WM_DeleteWindow(m_WinEndPosOpT2.hImage_right);  
		
    WM_SetCallback(WM_HBKWIN,NULL);
    memset(&m_WinEndPosOpT2, 0, sizeof(m_WinEndPosOpT2));
}

void _WinEndPosOpT2Interface(void *val)
{

}


WIN_INFO_TYPE g_WinEndPosOpT2 = {  //设置第二步
    &m_WinEndPosOpT2.hFrame,
    _WinEndPosOpT2Create,
    _WinEndPosOpT2Destroy,
};


typedef struct {
    GUI_HWIN  hFrame;
		GUI_HWIN hImage_CB_1;             
		GUI_HWIN hImage_CB_2;             
    GUI_HWIN  hTextHead;              
    GUI_HWIN  hEdit1;         
    GUI_HWIN  hEdit2;                 
    GUI_HWIN  hEdit3;    
    GUI_HWIN  hEdit4;                 
    GUI_HWIN  hTextExp;               
    GUI_HWIN  hList;                  
	  GUI_HWIN  hImageBack;             
		GUI_HWIN  hButtonEdit1;           
		GUI_HWIN  hButtonEdit2;           
		GUI_HWIN  hButtonEdit3;           
		GUI_HWIN  hButtonEdit4;           
    unsigned char currentSel;         
    unsigned char value_show_1;       
    unsigned char value_show_2;       
    unsigned char value_show_3;       
    unsigned char value_show_4;       
	GUI_HWIN hTimer;
	unsigned char cTimerCnt;
}WIN_USER_PASSWORD_INPUT_TYPE;
static WIN_USER_PASSWORD_INPUT_TYPE m_UserPasswordInput ;                     
 unsigned short *mp_rt_password_input;
 unsigned short  m_rt_password_input;
extern unsigned short reall;
void _WinPasswordInputKeyEnter(void )
{
    unsigned short m_value=0;
	char str[MAX_INFO_CHAR];
    if(0 == m_UserPasswordInput.currentSel)
    {
        m_UserPasswordInput.currentSel = 6;
		EDIT_SetTextColor(m_UserPasswordInput.hEdit1,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(1 == m_UserPasswordInput.currentSel)
    {
        m_UserPasswordInput.currentSel = 7;
		EDIT_SetTextColor(m_UserPasswordInput.hEdit2,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(2 == m_UserPasswordInput.currentSel)
    {
        m_UserPasswordInput.currentSel = 8;
		EDIT_SetTextColor(m_UserPasswordInput.hEdit3,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(3 == m_UserPasswordInput.currentSel)
    {
        m_UserPasswordInput.currentSel = 9;
		EDIT_SetTextColor(m_UserPasswordInput.hEdit4,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(4 == m_UserPasswordInput.currentSel)  
    {
        m_rt_password_input = m_UserPasswordInput.value_show_1*1000 + m_UserPasswordInput.value_show_2*100 + m_UserPasswordInput.value_show_3*10+m_UserPasswordInput.value_show_4;			
        reall=m_rt_password_input;
        if(m_rt_password_input == *((unsigned short *)mp_rt_password_input) )
        {
            g_authority = g_authority_bak;
            _InterDataRefresh();
					#if 1
					if(dataStructInterface.Frame_SN==1)
					{
						menuMainSettings[3]=0;
						flag_figures.user=1; 
					}else
					if(dataStructInterface.Frame_SN==2)
					{
						menuMainSettings[3]=0;
						flag_figures.user=2;  
					}else
					if(dataStructInterface.Frame_SN==3)
					{
						flag_figures.user=3;  
					}else
					if(dataStructInterface.Frame_SN==4)
					{
						flag_figures.user=4;  
					}else
					if(dataStructInterface.Frame_SN==5)
					{
						flag_figures.user=5; 
					}
            switch(flag_figures.user)
            {                      
			case 1: {sprintf(str,"                     操作员 ");
							strcpy(menuUserManagCn[1],str);
							strcpy(menuUserManagEn[1],str);
				menuMainSettings[3]=0;  //专家模式下设定主菜单下第三个控件，即“末端位置”灰色不可选
							}break;
			                     
			case 2: {sprintf(str,"                       监察");
							strcpy(menuUserManagCn[1],str);
							strcpy(menuUserManagEn[1],str);
                menuMainSettings[3]=0;
							}break;
			                     
			case 3: {sprintf(str,"                       专家");
							strcpy(menuUserManagCn[1],str);
							strcpy(menuUserManagEn[1],str);
				menuMainSettings[3]=1;  //专家模式下设定主菜单下第三个控件，即“末端位置”可选
							}break;
			                    
			case 4: {sprintf(str,"                       服务");
							strcpy(menuUserManagCn[1],str);
							strcpy(menuUserManagEn[1],str);
							}break;
			                     
			case 5: {sprintf(str,"                   工厂服务");
							strcpy(menuUserManagCn[1],str);
							strcpy(menuUserManagEn[1],str);
							}break;
            default: break;
            }
            #endif
            
            /*WIN_Exit(0);
            WIN_Exit(0);*/
            WIN_Exit_Lv(2);
        }
        else
        {
            WIN_Exit(0);
        }
    }
    else if(5 == m_UserPasswordInput.currentSel)  
    {
        WIN_Exit(0);
    }
    else if(6 == m_UserPasswordInput.currentSel)
    {		
        #if 1
        EDIT_SetTextColor(m_UserPasswordInput.hEdit1,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_UserPasswordInput.hEdit2,EDIT_CI_ENABELD,GUI_ORANGE);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit1,0);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit2,1);
        m_UserPasswordInput.currentSel = 7;
		EDIT_SetDecMode(m_UserPasswordInput.hEdit1,m_UserPasswordInput.value_show_1,0,9,0,GUI_EDIT_NORMAL);
        #endif
    }
    else if(7 == m_UserPasswordInput.currentSel)
    {			
        #if 1
        EDIT_SetTextColor(m_UserPasswordInput.hEdit2,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_UserPasswordInput.hEdit3,EDIT_CI_ENABELD,GUI_ORANGE);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit2,0);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit3,1);
        m_UserPasswordInput.currentSel = 8;
		EDIT_SetDecMode(m_UserPasswordInput.hEdit2,m_UserPasswordInput.value_show_2,0,9,0,GUI_EDIT_NORMAL);
        #endif
    }
    else if(8 == m_UserPasswordInput.currentSel)
    {	
        #if 1
        EDIT_SetTextColor(m_UserPasswordInput.hEdit3,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_UserPasswordInput.hEdit4,EDIT_CI_ENABELD,GUI_ORANGE);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit3,0);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit4,1);
        m_UserPasswordInput.currentSel = 9;
		EDIT_SetDecMode(m_UserPasswordInput.hEdit3,m_UserPasswordInput.value_show_3,0,9,0,GUI_EDIT_NORMAL);
        #endif
    }
    else if(9 == m_UserPasswordInput.currentSel)
    {
        #if 1
        EDIT_SetTextColor(m_UserPasswordInput.hEdit4,EDIT_CI_ENABELD,GUI_BLUE);
        LISTBOX_SetSel(m_UserPasswordInput.hList,0);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit4,0);
        m_UserPasswordInput.currentSel = 4;
		EDIT_SetDecMode(m_UserPasswordInput.hEdit4,m_UserPasswordInput.value_show_4,0,9,0,GUI_EDIT_NORMAL);
        #endif
    }
}


void _WinPasswordInputKeyDown(void)
{
    unsigned short m_value=0;
    if(0 == m_UserPasswordInput.currentSel)
    {
        BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit1,0);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit2,1);
        m_UserPasswordInput.currentSel = 1;
    }
    else if(1 == m_UserPasswordInput.currentSel)
    {
        BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit2,0);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit3,1);
        m_UserPasswordInput.currentSel = 2;
    }
    else if(2 == m_UserPasswordInput.currentSel)
    {
        BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit3,0);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit4,1);
        m_UserPasswordInput.currentSel = 3;
    }
    else if(3 == m_UserPasswordInput.currentSel)
    {
        BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit4,0);
        LISTBOX_SetBkColor(m_UserPasswordInput.hList,LISTBOX_CI_SEL ,GUI_ORANGE);
        LISTBOX_SetSel(m_UserPasswordInput.hList,0);
        m_UserPasswordInput.currentSel = 4;
    }
     else if(4 == m_UserPasswordInput.currentSel)
    {
        LISTBOX_SetSel(m_UserPasswordInput.hList,1);
        m_UserPasswordInput.currentSel = 5;
    }
    else if(5 == m_UserPasswordInput.currentSel)
    {
        LISTBOX_SetSel(m_UserPasswordInput.hList,-1);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit1,1);
        m_UserPasswordInput.currentSel = 0;
    }
    else if(6 == m_UserPasswordInput.currentSel)
    {
        m_UserPasswordInput.value_show_1++;
        if(m_UserPasswordInput.value_show_1>9) m_UserPasswordInput.value_show_1 = 0;
        EDIT_SetValue(m_UserPasswordInput.hEdit1,m_UserPasswordInput.value_show_1);
    }
    else if(7 == m_UserPasswordInput.currentSel)
    {	
        #if 1
        m_UserPasswordInput.value_show_2++;
        if(m_UserPasswordInput.value_show_2>9) m_UserPasswordInput.value_show_2 = 0;
        EDIT_SetValue(m_UserPasswordInput.hEdit2,m_UserPasswordInput.value_show_2);   
        #endif
    }
    else if(8 == m_UserPasswordInput.currentSel)
    {			
        #if 1
        m_UserPasswordInput.value_show_3++;
        if(m_UserPasswordInput.value_show_3>9) m_UserPasswordInput.value_show_3 = 0;
        EDIT_SetValue(m_UserPasswordInput.hEdit3,m_UserPasswordInput.value_show_3);   
        #endif
    }
    else if(9 == m_UserPasswordInput.currentSel)
    {
        #if 1
        m_UserPasswordInput.value_show_4++;
        if(m_UserPasswordInput.value_show_4>9) m_UserPasswordInput.value_show_4 = 0;
        EDIT_SetValue(m_UserPasswordInput.hEdit4,m_UserPasswordInput.value_show_4);    
        #endif			
    }
}

void _WinPasswordInputKeyUp(void)
{
    unsigned short m_value=0;
    if(0 == m_UserPasswordInput.currentSel)
    {
        BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit1,0);
        LISTBOX_SetSel(m_UserPasswordInput.hList,1);
        m_UserPasswordInput.currentSel = 5;
    }
    else if(1 == m_UserPasswordInput.currentSel)
    {
        BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit1,1);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit2,0);
        m_UserPasswordInput.currentSel = 0;
    }
    else if(2 == m_UserPasswordInput.currentSel)
    {
        BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit2,1);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit3,0);
        m_UserPasswordInput.currentSel = 1;
    }
    else if(3 == m_UserPasswordInput.currentSel)
    {
        BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit4,0);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit3,1);
        m_UserPasswordInput.currentSel = 2;
    }
     else if(4 == m_UserPasswordInput.currentSel)
    {
        LISTBOX_SetSel(m_UserPasswordInput.hList,-1);
		BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit4,1);
        m_UserPasswordInput.currentSel = 3;
    }
    else if(5 == m_UserPasswordInput.currentSel)
    {
        LISTBOX_SetSel(m_UserPasswordInput.hList,0);
        m_UserPasswordInput.currentSel = 4;
    }
    else if(6 == m_UserPasswordInput.currentSel)
    {
        if(m_UserPasswordInput.value_show_1>0)m_UserPasswordInput.value_show_1--;
        else  m_UserPasswordInput.value_show_1 = 9;
        EDIT_SetValue(m_UserPasswordInput.hEdit1,m_UserPasswordInput.value_show_1);
    }
    else if(7 == m_UserPasswordInput.currentSel)
    {
        if(m_UserPasswordInput.value_show_2>0)m_UserPasswordInput.value_show_2--;
        else  m_UserPasswordInput.value_show_2 = 9;
        EDIT_SetValue(m_UserPasswordInput.hEdit2,m_UserPasswordInput.value_show_2);
			}
    else if(8 == m_UserPasswordInput.currentSel)
    {
        if(m_UserPasswordInput.value_show_3>0)m_UserPasswordInput.value_show_3--;
        else  m_UserPasswordInput.value_show_3 = 9;
        EDIT_SetValue(m_UserPasswordInput.hEdit3,m_UserPasswordInput.value_show_3);
    }
    else if(9 == m_UserPasswordInput.currentSel)
    {
        if(m_UserPasswordInput.value_show_4>0)m_UserPasswordInput.value_show_4--;
        else  m_UserPasswordInput.value_show_4 = 9;
        EDIT_SetValue(m_UserPasswordInput.hEdit4,m_UserPasswordInput.value_show_4);		
    }
}

static void WinPasswordNumberShowStyle(void)
{
    m_UserPasswordInput.cTimerCnt++;
	if(6 == m_UserPasswordInput.currentSel)
	{
	    if(m_UserPasswordInput.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_UserPasswordInput.hEdit1);
	    }
		else
		{
			EDIT_SetDecMode(m_UserPasswordInput.hEdit1,m_UserPasswordInput.value_show_1,0,9,0,GUI_EDIT_NORMAL);
		}
	}
	else if(7 == m_UserPasswordInput.currentSel)
	{
	    if(m_UserPasswordInput.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_UserPasswordInput.hEdit2);
	    }
		else
		{
			EDIT_SetDecMode(m_UserPasswordInput.hEdit2,m_UserPasswordInput.value_show_2,0,9,0,GUI_EDIT_NORMAL);
		}
	}
	else if(8 == m_UserPasswordInput.currentSel)
	{
	    if(m_UserPasswordInput.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_UserPasswordInput.hEdit3);
	    }
		else
		{
			EDIT_SetDecMode(m_UserPasswordInput.hEdit3,m_UserPasswordInput.value_show_3,0,9,0,GUI_EDIT_NORMAL);
		}
	}
	else if(9 == m_UserPasswordInput.currentSel)
	{
	    if(m_UserPasswordInput.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_UserPasswordInput.hEdit4);
	    }
		else
		{
			EDIT_SetDecMode(m_UserPasswordInput.hEdit4,m_UserPasswordInput.value_show_4,0,9,0,GUI_EDIT_NORMAL);
		}
	}
}
static void _WinPasswordInputCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
    switch (pMsg->MsgId)
    {
        case WM_TIMER:
            WM_RestartTimer(pMsg->Data.v, 1000);
            WinPasswordNumberShowStyle();
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
            {
                case GUI_KEY_UP:
                    _WinPasswordInputKeyUp();
                    break;
                case GUI_KEY_DOWN:
                    _WinPasswordInputKeyDown();
                    break;
                case GUI_KEY_ENTER:
                    _WinPasswordInputKeyEnter();
                    break;
            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}

static void _WinPasswordInputCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);
    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    const char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;
    unsigned char    i = 0;
		mp_rt_password_input = (unsigned short *)pMenu->data->menusel;
	dataStructInterface.Frame_SN=pMenu->data->SN;
    if (NULL == pTitle) pTitle = "";
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_UserPasswordInput.hFrame, 0);            

    hWin = WM_GetFirstChild(m_UserPasswordInput.hFrame);          
		    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
#if 1      
	m_UserPasswordInput.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_UserPasswordInput.hImage_CB_1,&bmComBack_1);
	
	m_UserPasswordInput.hImage_CB_2 = IMAGE_CreateEx(259,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_UserPasswordInput.hImage_CB_2,&bmComBack_2);
    #endif
#if 1
    m_UserPasswordInput.hButtonEdit1   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+20-6-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_UserPasswordInput.hButtonEdit1,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit1,1);
	m_UserPasswordInput.hButtonEdit2   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+70-6-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_UserPasswordInput.hButtonEdit2,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit2,0);
	m_UserPasswordInput.hButtonEdit3   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+120-6-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_UserPasswordInput.hButtonEdit3,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit3,0);
	m_UserPasswordInput.hButtonEdit4   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+170-6-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_UserPasswordInput.hButtonEdit4,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_UserPasswordInput.hButtonEdit4,0);

    m_UserPasswordInput.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+10-6, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_UserPasswordInput.hEdit1     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+20-6   , DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_UserPasswordInput.hEdit2     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+70-6   , DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_UserPasswordInput.hEdit3     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+120-6   , DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_UserPasswordInput.hEdit4     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+170-6   , DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_UserPasswordInput.hTextExp   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET-6   , DEBUG_Y_OFFSET+PER_CM_OFFSET  , PER_CM_OFFSET*4.5, PER_CM_OFFSET*1, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_UserPasswordInput.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+13-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+50, 180, 52, hWin, WM_CF_SHOW, NULL, NULL, NULL);
   
#endif
#if 1
header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+10-6, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
hWin = m_UserPasswordInput.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
#endif
#if 1
	hWin = m_UserPasswordInput.hEdit1;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_UserPasswordInput.value_show_1 = 0;
    EDIT_SetDecMode(hWin,m_UserPasswordInput.value_show_1,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_UserPasswordInput.hEdit2;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_UserPasswordInput.value_show_2 = 0;
    EDIT_SetDecMode(hWin,m_UserPasswordInput.value_show_2,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_UserPasswordInput.hEdit3;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_UserPasswordInput.value_show_3 = 0;
    EDIT_SetDecMode(hWin,m_UserPasswordInput.value_show_3,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_UserPasswordInput.hEdit4;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_UserPasswordInput.value_show_4 = 0;
    EDIT_SetDecMode(hWin,m_UserPasswordInput.value_show_4,0,9,0,GUI_EDIT_NORMAL);
#endif
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
    hWin = m_UserPasswordInput.hTextExp;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_TOP);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetWrapMode(hWin,GUI_WRAPMODE_CHAR);
    TEXT_SetText(hWin, strShow);
#if 1
  hWin = m_UserPasswordInput.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 6);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
	LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw3);
	LISTBOX_SetSel(hWin, -1);
#endif
    for(i=0;i<INFO_MENU_SAVE_NUM;i++)
    {
        StrShowClear();
        if(LANGUAGE_CN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_CN[i],strShow,STRSHOWBUF_SIZE);
        }
        else if(LANGUAGE_EN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_EN[i],strShow,STRSHOWBUF_SIZE);
        }
        LISTBOX_AddString(hWin, strShow);
    }
    mp_rt_password_input= (unsigned short *)pMenu->data->menusel;
	m_UserPasswordInput.hTimer = WM_CreateTimer(WM_HBKWIN,0,1000,0);
   
    WM_SetCallback(WM_HBKWIN, _WinPasswordInputCallback);
    WM_SetFocus(WM_HBKWIN);
}

static void _WinPasswordInputDestroy(void *p)
{
    m_rt_password_input = m_UserPasswordInput.value_show_1*1000 + m_UserPasswordInput.value_show_2*100 + m_UserPasswordInput.value_show_3*10+m_UserPasswordInput.value_show_4;

		WM_DeleteWindow(m_UserPasswordInput.hImage_CB_1);        
		WM_DeleteWindow(m_UserPasswordInput.hImage_CB_2);        
    WM_DeleteWindow(m_UserPasswordInput.hTextHead);          
    WM_DeleteWindow(m_UserPasswordInput.hEdit1);   
    WM_DeleteWindow(m_UserPasswordInput.hEdit2);             
    WM_DeleteWindow(m_UserPasswordInput.hEdit3);  
    WM_DeleteWindow(m_UserPasswordInput.hEdit4);             
    WM_DeleteWindow(m_UserPasswordInput.hTextExp);           
    WM_DeleteWindow(m_UserPasswordInput.hList);              
	  WM_DeleteWindow(m_UserPasswordInput.hImageBack);         
		WM_DeleteWindow(m_UserPasswordInput.hButtonEdit1);       
		WM_DeleteWindow(m_UserPasswordInput.hButtonEdit2);       
		WM_DeleteWindow(m_UserPasswordInput.hButtonEdit3);       
		WM_DeleteWindow(m_UserPasswordInput.hButtonEdit4);       
    WM_DeleteWindow(m_UserPasswordInput.currentSel);         
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_UserPasswordInput, 0, sizeof(m_UserPasswordInput));
}
void _WinPasswordInputInterface(void *val)
{
    *((unsigned short *)mp_rt_password_input) = m_rt_password_input;
}


WIN_INFO_TYPE g_WinPasswordInput = {                       
    &m_UserPasswordInput.hFrame,
    _WinPasswordInputCreate,
    _WinPasswordInputDestroy
};
typedef struct {
    GUI_HWIN  hFrame;  
    GUI_HWIN hImage_CB_1;                         
    GUI_HWIN hImage_CB_2;                         
    GUI_HWIN  hText;                              
    GUI_HWIN  hList;                              
    GUI_HWIN  hImageBack;                         
    GUI_HWIN  hChkBox[MAX_ITEAM_PER_PAGE];        
}COMMON_USERMANAGE_MENU_TYPE;
static COMMON_USERMANAGE_MENU_TYPE m_CommonUserManageMenu = {0};                        

MENU_INFO_ITEM  *pWinCommonUserManageMenu;
void _WinCommonUserManageKeyEnter(void )
{
    unsigned char i=0;
    unsigned char j=0;
    unsigned char sel=0;
    int id =0;
    for(i=0,j=0;i< pWinCommonUserManageMenu->data->menunum; i++)
    {
        if(0 == LISTBOX_GetItemDisabled(m_CommonUserManageMenu.hList,i) )
        {
            if(i == LISTBOX_GetSel(m_CommonUserManageMenu.hList) )
            {
                sel = j;
                break;
            }
            j++;
        }
    }
    _InterDataRefresh();
    if(sel > *(pWinCommonUserManageMenu->data->menusel) )
    {
        id = sel;
        g_authority_bak = sel;
        WIN_Enter(&id);
    }
    else if(sel==0)
    {
        *(pWinCommonUserManageMenu->data->menusel) = sel;
        _InterDataRefresh();
        WIN_Exit(0);
    }
    else
    {
        *(pWinCommonUserManageMenu->data->menusel) = sel;
        _InterDataRefresh();
        if(sel!=3)
        {
            menuMainSettings[3]=0;
        }
        g_authority = sel;
        flag_figures.user=sel;
        WIN_Exit(0);
    }
}

void _WinCommonUserManageKeyDown(void )
{
    char curIndex=0;
    char curIndexDisable=0;
    char NumItems = LISTBOX_GetNumItems(m_CommonUserManageMenu.hList);

    curIndex = LISTBOX_GetSel(m_CommonUserManageMenu.hList);
    curIndex++;
    if(curIndex == LISTBOX_GetNumItems(m_CommonUserManageMenu.hList) )
    {
        curIndex = 0;
        curIndexDisable = LISTBOX_GetItemDisabled(m_CommonUserManageMenu.hList,curIndex);
        while(curIndexDisable)
        {
            LISTBOX_SetItemDisabled(m_CommonUserManageMenu.hList,curIndex,0);
            LISTBOX_SetSel(m_CommonUserManageMenu.hList,curIndex);
            LISTBOX_SetItemDisabled(m_CommonUserManageMenu.hList,curIndex,1);
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_CommonUserManageMenu.hList,curIndex);
        }
        LISTBOX_SetSel(m_CommonUserManageMenu.hList,curIndex);

    }
    else
    {
        curIndexDisable = LISTBOX_GetItemDisabled(m_CommonUserManageMenu.hList,curIndex);
        while(curIndexDisable)
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_CommonUserManageMenu.hList,curIndex);
        }
        LISTBOX_SetSel(m_CommonUserManageMenu.hList,curIndex);
    }
}

void _WinCommonUserManageKeyUp(void)
{
    char curIndex =0;
    char curIndexDisable =0;
    char curLen= LISTBOX_GetNumItems(m_CommonUserManageMenu.hList);

    curIndex = LISTBOX_GetSel(m_CommonUserManageMenu.hList);
    if(curIndex>0)
    {
        curIndex--;
        curIndexDisable = LISTBOX_GetItemDisabled(m_CommonUserManageMenu.hList,curIndex);
        while(curIndexDisable)
        {
            if(curIndex>0)
            {
                curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CommonUserManageMenu.hList,curIndex);
            }
            else
            {
                curIndex = curLen - 1;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CommonUserManageMenu.hList,curIndex);
            }
        }
    }
    else
    {
        curIndex = curLen - 1;
        curIndexDisable = LISTBOX_GetItemDisabled(m_CommonUserManageMenu.hList,curIndex);
        while(curIndexDisable)
        {
            if(curIndex>0)
            {
                curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CommonUserManageMenu.hList,curIndex);
            }
            else
            {
                curIndex = curLen - 1;
                curIndexDisable = LISTBOX_GetItemDisabled(m_CommonUserManageMenu.hList,curIndex);
            }
        }
    }
    LISTBOX_SetSel(m_CommonUserManageMenu.hList,curIndex);
}

static void _WinCommonUserManageCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinCommonUserManageKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinCommonUserManageKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinCommonUserManageKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}
static void _WinCommonUserManageCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    short           j           = 0;
    short           maxIteam    = 0;
    short           headIndex   = 0;
    short           curSel      = 0;
    char            *pBuffter   = g_LCDBuff;
    const char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;
    unsigned char    m_content_num = 0;
    pWinCommonUserManageMenu = p;

    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
     GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
	hWin = WM_HBKWIN;
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_CommonUserManageMenu.hFrame, 0);       
    hWin = WM_GetFirstChild(m_CommonUserManageMenu.hFrame);      
    m_CommonUserManageMenu.hText      = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    if(pMenu->data->menunum <= MAX_ITEAM_PER_PAGE)
        m_CommonUserManageMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23+10, PER_CM_OFFSET*4.5, PER_CM_OFFSET*4, hWin, WM_CF_SHOW, NULL, NULL,NULL);
    else
        m_CommonUserManageMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23+10, PER_CM_OFFSET*4.5+11, PER_CM_OFFSET*4, hWin, WM_CF_SHOW, NULL, NULL,NULL);
    #if 1
		header_txt( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
		  hWin = m_CommonUserManageMenu.hText;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
#endif
		#if 1
    hWin = m_CommonUserManageMenu.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 7);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
		LISTBOX_SetSel(hWin,-1);
    LISTBOX_SetAutoScrollV(hWin,0);
	LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw5);
#endif
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

    for(i=0,j=0;i<pMenu->data->menunum;i++)
    {
        if(MENU_SETTING_CONTENT == pMenu->data->menuattri[i])
        {
            if(j == *(pMenu->data->menusel) )
            {
                LISTBOX_SetSel(hWin,i);
                curSel = i;
            }
            j++;
        }
    }
    m_content_num = j;
		
		
			#if 1  
	m_CommonUserManageMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_CommonUserManageMenu.hImage_CB_1,&bmComBack_1);
	
	m_CommonUserManageMenu.hImage_CB_2 = IMAGE_CreateEx(259,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_CommonUserManageMenu.hImage_CB_2,&bmComBack_2);
	#endif


    WM_SetCallback(WM_HBKWIN, _WinCommonUserManageCallback);
    WM_SetFocus(WM_HBKWIN);
}

void _WinCommonUserManageFresh(void *p)
{
    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    short           j           = 0;
    short           maxIteam    = 0;
    short           headIndex   = 0;
    short           curSel      = 0;
		SCROLLBAR_Handle hScrollV = WM_GetDialogItem(hWin, GUI_ID_VSCROLL);
    for( i=0;i<MAX_ITEAM_PER_PAGE;i++) WM_DeleteWindow(m_CommonUserManageMenu.hChkBox[i] );

    hWin = m_CommonUserManageMenu.hList;
    for(i=0,j=0;i<pMenu->data->menunum;i++)
    {
        if(MENU_SETTING_CONTENT == pMenu->data->menuattri[i])
        {
            if(j == *(pMenu->data->menusel) )
            {
                curSel = i;
                break;
            }
            j++;
        }
    }
   
    i=SCROLLBAR_GetNumItems(hScrollV);
    headIndex=SCROLLBAR_GetValue(hScrollV);
    hWin = WM_GetFirstChild(m_CommonUserManageMenu.hFrame);   
    if(headIndex+MAX_ITEAM_PER_PAGE < pMenu->data->menunum) maxIteam = headIndex+MAX_ITEAM_PER_PAGE;
    else maxIteam = pMenu->data->menunum;
    for(i=headIndex,j=0;i< maxIteam; i++)
    {
       if(MENU_SETTING_CONTENT == pMenu->data->menuattri[i])
       {
            m_CommonUserManageMenu.hChkBox[j]    = CHECKBOX_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+PER_CM_OFFSET*4.5-23,DEBUG_Y_OFFSET+23+10+1+25*(i-headIndex),18,18,hWin,WM_CF_SHOW,NULL,NULL);
            if(curSel == i)
            {
                CHECKBOX_SetState(m_CommonUserManageMenu.hChkBox[j],1);
            }
            j++;
       }
    }
}

static void _WinCommonUserManageDestroy(void *p)
{
    unsigned char index = 0;
		WM_DeleteWindow(m_CommonUserManageMenu.hImage_CB_1);                        
		WM_DeleteWindow(m_CommonUserManageMenu.hImage_CB_2);                        
    WM_DeleteWindow(m_CommonUserManageMenu.hText);                              
    WM_DeleteWindow(m_CommonUserManageMenu.hList);                              
	  WM_DeleteWindow(m_CommonUserManageMenu.hImageBack);    
    for( ;index<MAX_ITEAM_PER_PAGE;index++) WM_DeleteWindow(m_CommonUserManageMenu.hChkBox[index] );  
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_CommonUserManageMenu, 0, sizeof(m_CommonUserManageMenu));
}

void _WinCommonUserManageInterface(void *val)
{
}


WIN_INFO_TYPE g_WinCommonUserManageMenu = {                      
    &m_CommonUserManageMenu.hFrame,
    _WinCommonUserManageCreate,
    _WinCommonUserManageDestroy
};

#if 1
typedef struct {
    GUI_HWIN  hFrame;  
		GUI_HWIN hImage_CB_1;      
		GUI_HWIN hImage_CB_2;      
    GUI_HWIN  hTextHead;       
    GUI_HWIN  hEdit1;          
    GUI_HWIN  hEdit2;          
    GUI_HWIN  hEdit3;          
    GUI_HWIN  hEdit4;          
    GUI_HWIN  hTextExp;        
    GUI_HWIN  hList;           
		GUI_HWIN  hImageBack;      
		GUI_HWIN  hButtonEdit1;    
		GUI_HWIN  hButtonEdit2;    
		GUI_HWIN  hButtonEdit3;    
		GUI_HWIN  hButtonEdit4;    
    unsigned char currentSel;  
    unsigned char value_show_1;
    unsigned char value_show_2;
    unsigned char value_show_3;
    unsigned char value_show_4;
	GUI_HWIN hTimer;
	unsigned char cTimerCnt;
}WIN_USER_PASSWORD_CHANGE_TYPE;
static WIN_USER_PASSWORD_CHANGE_TYPE m_UserPasswordChange = {0};                       
static unsigned short *mp_rt_password_change=0;
static unsigned short  m_rt_password_change=0;

void _WinPasswordChangeKeyEnter(void )
{
    unsigned short m_value=0;
	GUI_HWIN  hFrame2;
	GUI_HWIN  hImage;
    if(0 == m_UserPasswordChange.currentSel)
    {
        m_UserPasswordChange.currentSel = 6;
		EDIT_SetTextColor(m_UserPasswordChange.hEdit1,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(1 == m_UserPasswordChange.currentSel)
    {
        m_UserPasswordChange.currentSel = 7;
		EDIT_SetTextColor(m_UserPasswordChange.hEdit2,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(2 == m_UserPasswordChange.currentSel)
    {
        m_UserPasswordChange.currentSel = 8;
		EDIT_SetTextColor(m_UserPasswordChange.hEdit3,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(3 == m_UserPasswordChange.currentSel)
    {
        m_UserPasswordChange.currentSel = 9;
		EDIT_SetTextColor(m_UserPasswordChange.hEdit4,EDIT_CI_ENABELD,GUI_ORANGE);
    }
    else if(4 == m_UserPasswordChange.currentSel)
    {
        m_rt_password_change = m_UserPasswordChange.value_show_1*1000 + m_UserPasswordChange.value_show_2*100 + m_UserPasswordChange.value_show_3*10+m_UserPasswordChange.value_show_4;
				if(dataStructInterface.Frame_SN==1) 
				{
						password.g_password_handle=m_rt_password_change;
						eeprom.flag_g_password_handle=1;
				}
				if(dataStructInterface.Frame_SN==2) 
				{
						password.g_password_viewer=m_rt_password_change;
						eeprom.flag_g_password_viewer=1;
				}
				if(dataStructInterface.Frame_SN==3) 
				{
						password.g_password_expert=m_rt_password_change;
						eeprom.flag_g_password_expert=1;
				}
				if(dataStructInterface.Frame_SN==4) 
				{
						password.g_password_service=m_rt_password_change;
						eeprom.flag_g_password_service=1;
				}
				if(dataStructInterface.Frame_SN==5) 
				{
						password.g_password_factroy=m_rt_password_change;
						eeprom.flag_g_password_factroy=1;
				}
			WIN_Exit(1);
    }
    else if(5 == m_UserPasswordChange.currentSel)
    {
        WIN_Exit(0);
    }
    else if(6 == m_UserPasswordChange.currentSel)
    {
        EDIT_SetTextColor(m_UserPasswordChange.hEdit1,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_UserPasswordChange.hEdit2,EDIT_CI_ENABELD,GUI_ORANGE);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit1,0);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit2,1);
        m_UserPasswordChange.currentSel = 7;
		EDIT_SetDecMode(m_UserPasswordChange.hEdit1,m_UserPasswordChange.value_show_1,0,9,0,GUI_EDIT_NORMAL);
    }
    else if(7 == m_UserPasswordChange.currentSel)
    {
        EDIT_SetTextColor(m_UserPasswordChange.hEdit2,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_UserPasswordChange.hEdit3,EDIT_CI_ENABELD,GUI_ORANGE);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit2,0);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit3,1);
        m_UserPasswordChange.currentSel = 8;
		EDIT_SetDecMode(m_UserPasswordChange.hEdit2,m_UserPasswordChange.value_show_2,0,9,0,GUI_EDIT_NORMAL);
    }
     else if(8 == m_UserPasswordChange.currentSel)
    {
        EDIT_SetTextColor(m_UserPasswordChange.hEdit3,EDIT_CI_ENABELD,GUI_BLUE);
        EDIT_SetTextColor(m_UserPasswordChange.hEdit4,EDIT_CI_ENABELD,GUI_ORANGE);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit3,0);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit4,1);
        m_UserPasswordChange.currentSel = 9;
		EDIT_SetDecMode(m_UserPasswordChange.hEdit3,m_UserPasswordChange.value_show_3,0,9,0,GUI_EDIT_NORMAL);
    }
    else if(9 == m_UserPasswordChange.currentSel)
    {
        EDIT_SetTextColor(m_UserPasswordChange.hEdit4,EDIT_CI_ENABELD,GUI_BLUE);
        LISTBOX_SetSel(m_UserPasswordChange.hList,0);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit4,0);
        m_UserPasswordChange.currentSel = 4;
		EDIT_SetDecMode(m_UserPasswordChange.hEdit4,m_UserPasswordChange.value_show_4,0,9,0,GUI_EDIT_NORMAL);
    }
}

void _WinPasswordChangeKeyDown(void)
{
    unsigned short m_value=0;
    if(0 == m_UserPasswordChange.currentSel)
    {
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit1,0);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit2,1);
        m_UserPasswordChange.currentSel = 1;
    }
    else if(1 == m_UserPasswordChange.currentSel)
    {
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit2,0);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit3,1);
        m_UserPasswordChange.currentSel = 2;
    }
    else if(2 == m_UserPasswordChange.currentSel)
    {
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit3,0);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit4,1);
        m_UserPasswordChange.currentSel = 3;
    }
    else if(3 == m_UserPasswordChange.currentSel)
    {
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit4,0);
        LISTBOX_SetBkColor(m_UserPasswordChange.hList,LISTBOX_CI_SEL ,GUI_ORANGE);
        LISTBOX_SetSel(m_UserPasswordChange.hList,0);
        m_UserPasswordChange.currentSel = 4;
    }
     else if(4 == m_UserPasswordChange.currentSel)
    {
        LISTBOX_SetSel(m_UserPasswordChange.hList,1);
        m_UserPasswordChange.currentSel = 5;
    }
    else if(5 == m_UserPasswordChange.currentSel)
    {
        LISTBOX_SetSel(m_UserPasswordChange.hList,-1);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit1,1);
        m_UserPasswordChange.currentSel = 0;
    }
    else if(6 == m_UserPasswordChange.currentSel)
    {
        m_UserPasswordChange.value_show_1++;
        if(m_UserPasswordChange.value_show_1>9) m_UserPasswordChange.value_show_1 = 0;
        EDIT_SetValue(m_UserPasswordChange.hEdit1,m_UserPasswordChange.value_show_1);
    }
    else if(7 == m_UserPasswordChange.currentSel)
    {
        m_UserPasswordChange.value_show_2++;
        if(m_UserPasswordChange.value_show_2>9) m_UserPasswordChange.value_show_2 = 0;
        EDIT_SetValue(m_UserPasswordChange.hEdit2,m_UserPasswordChange.value_show_2);
    }
    else if(8 == m_UserPasswordChange.currentSel)
    {
        m_UserPasswordChange.value_show_3++;
        if(m_UserPasswordChange.value_show_3>9) m_UserPasswordChange.value_show_3 = 0;
        EDIT_SetValue(m_UserPasswordChange.hEdit3,m_UserPasswordChange.value_show_3);
    }
    else if(9 == m_UserPasswordChange.currentSel)
    {
        m_UserPasswordChange.value_show_4++;
        if(m_UserPasswordChange.value_show_4>9) m_UserPasswordChange.value_show_4 = 0;
        EDIT_SetValue(m_UserPasswordChange.hEdit4,m_UserPasswordChange.value_show_4);
    }
}

void _WinPasswordChangeKeyUp(void)
{
    unsigned short m_value=0;
    if(0 == m_UserPasswordChange.currentSel)
    {
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit1,0);
        LISTBOX_SetSel(m_UserPasswordChange.hList,1);
        m_UserPasswordChange.currentSel = 5;
    }
    else if(1 == m_UserPasswordChange.currentSel)
    {
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit1,1);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit2,0);
        m_UserPasswordChange.currentSel = 0;
    }
    else if(2 == m_UserPasswordChange.currentSel)
    {
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit2,1);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit3,0);
        m_UserPasswordChange.currentSel = 1;
    }
    else if(3 == m_UserPasswordChange.currentSel)
    {
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit4,0);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit3,1);
        m_UserPasswordChange.currentSel = 2;
    }
     else if(4 == m_UserPasswordChange.currentSel)
    {
        LISTBOX_SetSel(m_UserPasswordChange.hList,-1);
		BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit4,1);
        m_UserPasswordChange.currentSel = 3;
    }
    else if(5 == m_UserPasswordChange.currentSel)
    {
        LISTBOX_SetSel(m_UserPasswordChange.hList,0);
        m_UserPasswordChange.currentSel = 4;
    }
    else if(6 == m_UserPasswordChange.currentSel)
    {
        if(m_UserPasswordChange.value_show_1>0)m_UserPasswordChange.value_show_1--;
        else  m_UserPasswordChange.value_show_1 = 9;
        EDIT_SetValue(m_UserPasswordChange.hEdit1,m_UserPasswordChange.value_show_1);
    }
    else if(7 == m_UserPasswordChange.currentSel)
    {
        if(m_UserPasswordChange.value_show_2>0)m_UserPasswordChange.value_show_2--;
        else  m_UserPasswordChange.value_show_2 = 9;
        EDIT_SetValue(m_UserPasswordChange.hEdit2,m_UserPasswordChange.value_show_2);
    }
    else if(8 == m_UserPasswordChange.currentSel)
    {
        if(m_UserPasswordChange.value_show_3>0)m_UserPasswordChange.value_show_3--;
        else  m_UserPasswordChange.value_show_3 = 9;
        EDIT_SetValue(m_UserPasswordChange.hEdit3,m_UserPasswordChange.value_show_3);
    }
    else if(9 == m_UserPasswordChange.currentSel)
    {
        if(m_UserPasswordChange.value_show_4>0)m_UserPasswordChange.value_show_4--;
        else  m_UserPasswordChange.value_show_4 = 9;
        EDIT_SetValue(m_UserPasswordChange.hEdit4,m_UserPasswordChange.value_show_4);
    }
}

static void WinPasswordNumberChangeShowStyle(void)
{
    m_UserPasswordChange.cTimerCnt++;
	if(6 == m_UserPasswordChange.currentSel)
	{
	    if(m_UserPasswordChange.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_UserPasswordChange.hEdit1);
	    }
		else
		{
			EDIT_SetDecMode(m_UserPasswordChange.hEdit1,m_UserPasswordChange.value_show_1,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(7 == m_UserPasswordChange.currentSel)
	{
	    if(m_UserPasswordChange.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_UserPasswordChange.hEdit2);
	    }
		else
		{
			EDIT_SetDecMode(m_UserPasswordChange.hEdit2,m_UserPasswordChange.value_show_2,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(8 == m_UserPasswordChange.currentSel)
	{
	    if(m_UserPasswordChange.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_UserPasswordChange.hEdit3);
	    }
		else
		{
			EDIT_SetDecMode(m_UserPasswordChange.hEdit3,m_UserPasswordChange.value_show_3,0,9,0,GUI_EDIT_NORMAL);
		}

	}
	else if(9 == m_UserPasswordChange.currentSel)
	{
	    if(m_UserPasswordChange.cTimerCnt%2)
	    {
			EDIT_SetTextMode(m_UserPasswordChange.hEdit4);
	    }
		else
		{
			EDIT_SetDecMode(m_UserPasswordChange.hEdit4,m_UserPasswordChange.value_show_4,0,9,0,GUI_EDIT_NORMAL);
		}

	}
}

static void _WinPasswordChangeCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;
    switch (pMsg->MsgId)
    {
    case WM_TIMER:
        WM_RestartTimer(pMsg->Data.v, 1000);
		WinPasswordNumberChangeShowStyle();
        break;
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinPasswordChangeKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinPasswordChangeKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinPasswordChangeKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}


static void _WinPasswordChangeCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    const char      *pTitle     = pMenu->data->title[g_LanguageIndex];
   const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;
	
    unsigned char    i = 0;
dataStructInterface.PASSWORD=* pMenu->data->menusel;
	dataStructInterface.Frame_SN=pMenu->data->SN;
    if (NULL == pTitle) pTitle = "";
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
    FRAMEWIN_SetTitleVis(m_UserPasswordChange.hFrame, 0);
    hWin = WM_GetFirstChild(m_UserPasswordChange.hFrame);
    GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_EnableAlpha(1);
#if 1       
	m_UserPasswordChange.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_UserPasswordChange.hImage_CB_1,&bmComBack_1);	
	m_UserPasswordChange.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_UserPasswordChange.hImage_CB_2,&bmComBack_2);
    #endif
    m_UserPasswordChange.hButtonEdit1   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+20-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_UserPasswordChange.hButtonEdit1,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit1,1);
	m_UserPasswordChange.hButtonEdit2   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+70-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_UserPasswordChange.hButtonEdit2,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit2,0);
	m_UserPasswordChange.hButtonEdit3   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+120-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_UserPasswordChange.hButtonEdit3,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit3,0);
	m_UserPasswordChange.hButtonEdit4   = BUTTON_CreateEx(DEBUG_X_OFFSET+PER_CM_OFFSET+170-6, DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5-5, 42, 51,hWin,WM_CF_SHOW |WM_CF_HASTRANS,NULL, NULL);
    BUTTON_SetSkin(m_UserPasswordChange.hButtonEdit4,SKIN_NUMBER_Button);
    BUTTON_SetPressed(m_UserPasswordChange.hButtonEdit4,0);
    m_UserPasswordChange.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_UserPasswordChange.hEdit1     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+20   , DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_UserPasswordChange.hEdit2     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+70   , DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_UserPasswordChange.hEdit3     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+120   , DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_UserPasswordChange.hEdit4     = EDIT_CreateEx   ( DEBUG_X_OFFSET+PER_CM_OFFSET+170   , DEBUG_Y_OFFSET+PER_CM_OFFSET*2.5, 30, 40, hWin, WM_CF_SHOW, NULL , NULL, 1);
    m_UserPasswordChange.hTextExp   = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET   , DEBUG_Y_OFFSET+PER_CM_OFFSET  , PER_CM_OFFSET*4.5, PER_CM_OFFSET*1, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_UserPasswordChange.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+13, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+50, 180, 52, hWin, WM_CF_SHOW, NULL, NULL, NULL);
    header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_UserPasswordChange.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);
    hWin = m_UserPasswordChange.hEdit1;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_UserPasswordChange.value_show_1 = (*(unsigned short *)pMenu->data->menusel)/1000;
    EDIT_SetDecMode(hWin,m_UserPasswordChange.value_show_1,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_UserPasswordChange.hEdit2;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_UserPasswordChange.value_show_2 = ((*(unsigned short *)pMenu->data->menusel)%1000)/100;
    EDIT_SetDecMode(hWin,m_UserPasswordChange.value_show_2,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_UserPasswordChange.hEdit3;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_UserPasswordChange.value_show_3 = (((*(unsigned short *)pMenu->data->menusel)%1000)%100)/10;
    EDIT_SetDecMode(hWin,m_UserPasswordChange.value_show_3,0,9,0,GUI_EDIT_NORMAL);
    hWin = m_UserPasswordChange.hEdit4;
    EDIT_SetFont(hWin,&GUI_Fontsong33);
    GUI_UC_SetEncodeUTF8();
    EDIT_SetTextColor(hWin,EDIT_CI_ENABELD,GUI_BLUE);
    EDIT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    m_UserPasswordChange.value_show_4 = (((*(unsigned short *)pMenu->data->menusel)%1000)%100)%10;
    EDIT_SetDecMode(hWin,m_UserPasswordChange.value_show_4,0,9,0,GUI_EDIT_NORMAL);

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
    hWin = m_UserPasswordChange.hTextExp;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_WHITE);
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_TOP);
    TEXT_SetTextColor(hWin,GUI_BLACK);
    TEXT_SetWrapMode(hWin,GUI_WRAPMODE_CHAR);
    TEXT_SetText(hWin, strShow);

    hWin = m_UserPasswordChange.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 6);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
	LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw3);
	LISTBOX_SetSel(hWin, -1);

    for(i=0;i<INFO_MENU_SAVE_NUM;i++)
    {
        StrShowClear();
        if(LANGUAGE_CN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_CN[i],strShow,STRSHOWBUF_SIZE);
        }
        else if(LANGUAGE_EN == g_LanguageIndex)
        {
            enc_unicode_to_utf8_str(info_menu_save_EN[i],strShow,STRSHOWBUF_SIZE);
        }
        LISTBOX_AddString(hWin, strShow);
    }
    mp_rt_password_change = (unsigned short *)pMenu->data->menusel;

	m_UserPasswordChange.hTimer = WM_CreateTimer(WM_HBKWIN,0,1000,0);

    WM_SetCallback(WM_HBKWIN, _WinPasswordChangeCallback);
    WM_SetFocus(WM_HBKWIN);
}

static void _WinPasswordChangeDestroy(void *p)
{
    m_rt_password_change = m_UserPasswordChange.value_show_1*1000 + m_UserPasswordChange.value_show_2*100 + m_UserPasswordChange.value_show_3*10+m_UserPasswordChange.value_show_4;	
		WM_DeleteWindow(m_UserPasswordChange.hImage_CB_1);    
		WM_DeleteWindow(m_UserPasswordChange.hImage_CB_2);    
    WM_DeleteWindow(m_UserPasswordChange.hTextHead);      
    WM_DeleteWindow(m_UserPasswordChange.hEdit1);         
    WM_DeleteWindow(m_UserPasswordChange.hEdit2);         
    WM_DeleteWindow(m_UserPasswordChange.hEdit3);         
    WM_DeleteWindow(m_UserPasswordChange.hEdit4);         
    WM_DeleteWindow(m_UserPasswordChange.hTextExp);       
    WM_DeleteWindow(m_UserPasswordChange.hList);          
		WM_DeleteWindow(m_UserPasswordChange.hImageBack);     
		WM_DeleteWindow(m_UserPasswordChange.hButtonEdit1);   
		WM_DeleteWindow(m_UserPasswordChange.hButtonEdit2);   
		WM_DeleteWindow(m_UserPasswordChange.hButtonEdit3);   
		WM_DeleteWindow(m_UserPasswordChange.hButtonEdit4);   
	WM_DeleteTimer(m_UserPasswordChange.hTimer);
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_UserPasswordChange, 0, sizeof(m_UserPasswordChange));
}

void _WinPasswordChangeInterface(void *val)
{
    *((unsigned short *)mp_rt_password_change) = m_rt_password_change;
}


WIN_INFO_TYPE g_WinPasswordChange = {                        
    &m_UserPasswordChange.hFrame,
    _WinPasswordChangeCreate,
    _WinPasswordChangeDestroy
};
#endif



typedef struct {
    GUI_HWIN  hFrame;
    GUI_HWIN hImage_CB_1;       
    GUI_HWIN hImage_CB_2;       
    GUI_HWIN  hTextHead;        
    GUI_HWIN  hList;            
    GUI_HWIN  hImageBack;       
	GUI_HWIN  hSetOK;             
}WIN_ENDPOS_SETOK_TYPE;
static WIN_ENDPOS_SETOK_TYPE m_EndPosSetOK = {0};                         
void _WinEndPosSetOkKeyEnter(void )
{
	if(encoder.dir_flag == 2)  //末端位置--开--关末端位置设置成功--关灯常亮
	{
		set_end.flag_close=1;
	}
    else if(encoder.dir_flag == 1)  //末端位置--关--开末端位置设置成功--开灯常亮
	{
		set_end.flag_open=1;
	}
	encoder.set_flag=0;
	flag_reset_encoder=0;
	encoder.Set2EE_flag=1;
    set_end.flag_setend=0;
	encoder.set_end_ok=1;
    WIN_Exit_Lv(5);
	/*原先的实现，加上WIN_Exit中执行两次GUI_Exec1()，会造成退出界面的时候闪屏*/
    /*WIN_Exit(0);
	set_end.flag_setend=0;
	encoder.set_end_ok=1;
	WIN_Exit(0);
	set_end.flag_setend=0;
	encoder.set_end_ok=1;
	WIN_Exit(0);
    set_end.flag_setend=0;
	encoder.set_end_ok=1;
	WIN_Exit(0);
    set_end.flag_setend=0;
	encoder.set_end_ok=1;
	WIN_Exit(0);*/
    
    
}

void _WinEndPosSetOkKeyDown(void)
{

}

void _WinEndPosSetOkKeyUp(void)
{

}

static void _WinEndPosSetOkCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinEndPosSetOkKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinEndPosSetOkKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinEndPosSetOkKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinEndPosSetOkCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    char            *pBuffter   = g_LCDBuff;
    const  char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    const    char            *pContentCn = pMenu->data->menutitleCn;
    const  char            *pContentEn = pMenu->data->menutitleEn;
    GUI_RECT rFocus;
    
	#if 1
	GUI_SetBkColor(GUI_WHITE);     
    GUI_Clear();
	#endif
    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	encoder.Read_old_set=encoder.Read_old&0x08000000;
    if((encoder.set_first==1)&&(encoder.Read_old_set==0x08000000))  //key_mlx90363.Read_now为全F
    {
        flag_reset_encoder=1;
        encoder.num=1;
    }		
    if((encoder.set_first==1)&&(encoder.Read_old_set==0x00000000))  //key_mlx90363.Read_now为全0
    {
        encoder.num=2;
    }
    if((encoder.set_first==2)&&(encoder.Read_old_set==0x08000000))
    {
        encoder.num=3;
    }
    if((encoder.set_first==2)&&(encoder.Read_old_set==0x00000000))
    {
        encoder.num=4;
    }
    if((encoder.set_first==3)&&(encoder.Read_old_set==0x08000000))
    {
        flag_reset_encoder=1;
        encoder.num=5;
    }
    if((encoder.set_first==3)&&(encoder.Read_old_set==0x00000000))
    {
        encoder.num=6;
    }
    if((encoder.set_first==4)&&(encoder.Read_old_set==0x08000000))
    {
        encoder.num=7;
    }
    if((encoder.set_first==4)&&(encoder.Read_old_set==0x00000000))
    {
        encoder.num=8;
    }
	encoder.Set_Ready=1;
	
    data_figures.READ_ALL_903=key_mlx90363.Read_all;
	
    m_EndPosSetOK.hFrame = WM_HBKWIN;
    hWin = m_EndPosSetOK.hFrame;
    
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    GUI_EnableAlpha(1);
    #if 1      
	m_EndPosSetOK.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EndPosSetOK.hImage_CB_1,&bmComBack_1);
	m_EndPosSetOK.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EndPosSetOK.hImage_CB_2,&bmComBack_2);
    #endif
	m_EndPosSetOK.hSetOK = IMAGE_CreateEx(130,60,59,55,hWin,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
    IMAGE_SetBitmap(m_EndPosSetOK.hSetOK,&bmset_ok);
    GUI_SetColor(GUI_DARKGREEN);
    GUI_SetPenSize(3);   
    rFocus.x0 = PER_CM_OFFSET+10;
    rFocus.y0 = 40;
    rFocus.x1 = PER_CM_OFFSET+10+PER_CM_OFFSET*4.5;
    rFocus.y1 = 145;
    GUI_AA_DrawRoundedRectEx(&rFocus,10);
    GUI_SetFont(&GUI_Fontsong16all);
    GUI_SetColor(GUI_BLACK);
    GUI_DispStringAt("末端位置设置成功!", PER_CM_OFFSET+20+20+10 , 125);
#if 1
    m_EndPosSetOK.hTextHead  = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EndPosSetOK.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+13, DEBUG_Y_OFFSET+PER_CM_OFFSET*1.5+60+50, 180, 26, hWin, WM_CF_SHOW, NULL, NULL, NULL);

    header_txt(56, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5, 23);
    hWin = m_EndPosSetOK.hTextHead;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);

    hWin = m_EndPosSetOK.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 6);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw3);
    LISTBOX_SetSel(hWin, 0);

    StrShowClear();
    enc_unicode_to_utf8_str(info_menu_ok[0],strShow,STRSHOWBUF_SIZE);
    LISTBOX_AddString(hWin, strShow);

#endif   
    WM_SetCallback(WM_HBKWIN, _WinEndPosSetOkCallback);
    WM_SetFocus(WM_HBKWIN);
}

static void _WinEndPosSetOkDestroy(void *p)
{
    WM_DeleteWindow(m_EndPosSetOK.hImage_CB_1);      
    WM_DeleteWindow(m_EndPosSetOK.hImage_CB_2);      
    WM_DeleteWindow(m_EndPosSetOK.hTextHead);        
    WM_DeleteWindow(m_EndPosSetOK.hList);            
    WM_DeleteWindow(m_EndPosSetOK.hImageBack);       
    WM_DeleteWindow(m_EndPosSetOK.hSetOK);           
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_EndPosSetOK, 0, sizeof(m_EndPosSetOK));
}

WIN_INFO_TYPE g_WinEndPosSetOkMenu = {                       
    &m_EndPosSetOK.hFrame,
    _WinEndPosSetOkCreate,
    _WinEndPosSetOkDestroy
};



typedef struct {
    GUI_HWIN hFrame;
		GUI_HWIN hImage_CB_1;        
		GUI_HWIN hImage_CB_2;        
    GUI_HWIN hBtnRtn;            
    GUI_HWIN hText;              
    GUI_HWIN hList;              
	  GUI_HWIN hImageBack;         
	  GUI_HWIN hListEnter;         
	  char menuFlag;
}ENDPOS_PARA_MENU_TYPE;
static ENDPOS_PARA_MENU_TYPE m_EndPosParaMenu = {0};                         
void _WinEndPosParaMenuKeyDown(void )
{
    char curIndex=0;
    char curIndexDisable=0;

    curIndexDisable = LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,curIndex);
    if(BUTTON_IsPressed(m_EndPosParaMenu.hBtnRtn))
    {
        BUTTON_SetPressed(m_EndPosParaMenu.hBtnRtn,0);
        if(LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,curIndex))
        {
            LISTBOX_SetItemDisabled(m_EndPosParaMenu.hList,curIndex,0);
            LISTBOX_SetSel(m_EndPosParaMenu.hList,curIndex);
            LISTBOX_SetItemDisabled(m_EndPosParaMenu.hList,curIndex,1);
        }
        while(curIndexDisable) 
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,curIndex);
        }
        LISTBOX_SetSel(m_EndPosParaMenu.hList,curIndex);
    }
    else if(-1 != LISTBOX_GetSel(m_EndPosParaMenu.hList))
    {
        curIndex = LISTBOX_GetSel(m_EndPosParaMenu.hList);
        curIndexDisable = LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,curIndex);
        if(curIndex == (LISTBOX_GetNumItems(m_EndPosParaMenu.hList)-1) ) 
        {
            LISTBOX_SetSel(m_EndPosParaMenu.hListEnter,0);
			      LISTBOX_SetSel(m_EndPosParaMenu.hList,-1);
        }
        else
        {
            curIndex++;
            curIndexDisable = LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,curIndex);
            while(curIndexDisable)
            {
                if(curIndex == (LISTBOX_GetNumItems(m_EndPosParaMenu.hList)-1) ) 
                {
                    LISTBOX_SetSel(m_EndPosParaMenu.hListEnter,0);
					          LISTBOX_SetSel(m_EndPosParaMenu.hList,-1);
                    return ;
                }
                curIndex++;
                curIndexDisable = LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,curIndex);
            }
            LISTBOX_SetSel(m_EndPosParaMenu.hList,curIndex);
        }
    }
    else if(-1 != LISTBOX_GetSel(m_EndPosParaMenu.hListEnter))
    {
        LISTBOX_SetSel(m_EndPosParaMenu.hListEnter,-1);
        BUTTON_SetPressed(m_EndPosParaMenu.hBtnRtn,1);
    }
}

void _WinEndPosParaMenuKeyUp(void)
{
    char curIndex =0;
    char curIndexDisable =0;
    char curLen= LISTBOX_GetNumItems(m_EndPosParaMenu.hList);

    curIndex = curLen-1;
    curIndexDisable = LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,curIndex);
    if(-1 != LISTBOX_GetSel(m_EndPosParaMenu.hListEnter))
    {
        LISTBOX_SetSel(m_EndPosParaMenu.hListEnter,-1);
        while(curIndexDisable)
        {
            if(curIndex>0)
            {
                curIndex--;
                curIndexDisable = LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,curIndex);
            }
            else break;
        }
        LISTBOX_SetSel(m_EndPosParaMenu.hList,curIndex);
    }
    else if(BUTTON_IsPressed(m_EndPosParaMenu.hBtnRtn))//·µ»ؼ﻿
    {
        BUTTON_SetPressed(m_EndPosParaMenu.hBtnRtn,0);
        LISTBOX_SetSel(m_EndPosParaMenu.hListEnter,0);
    }
    else if(-1 != LISTBOX_GetSel(m_EndPosParaMenu.hList))
    {
        curIndex = LISTBOX_GetSel(m_EndPosParaMenu.hList);
        curIndexDisable = LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,curIndex);
        if(curIndex>0)
        {
            curIndex--;
            curIndexDisable = LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,curIndex);
            while(curIndexDisable)
            {
                if(curIndex>0)
                {
                    curIndex--;
                    curIndexDisable = LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,curIndex);
                }
                else
                {
                    BUTTON_SetPressed(m_EndPosParaMenu.hBtnRtn,1);
					          LISTBOX_SetSel(m_EndPosParaMenu.hList,-1);
                    break;
                }
            }
        }
        else
        {
            BUTTON_SetPressed(m_EndPosParaMenu.hBtnRtn,1);
			      LISTBOX_SetSel(m_EndPosParaMenu.hList,-1);
			      return ;
        }
        LISTBOX_SetSel(m_EndPosParaMenu.hList,curIndex);
    }
}

void _WinEndPosParaMenuKeyEnter(void)
{
    int id = 0;
    int i=0;
    int j=0;
    if(BUTTON_IsPressed(m_EndPosParaMenu.hBtnRtn))
    {
        WIN_Exit(0);
    }
    else if(-1 != LISTBOX_GetSel(m_EndPosParaMenu.hListEnter))
    {
        if(m_EndPosParaMenu.menuFlag==MENU2_ENDPOS_PARA_NUM)
        {
            id = 0;
    	  	/*WIN_Exit(0);
    	  	WIN_Exit(0);*/
            WIN_Exit_Lv(2);
    	  	WIN_Enter(&id);
        }
        else
        {
            id = 4;
            WIN_Enter(&id);
        }   	  
    }
    else
    {
        while(i<LISTBOX_GetNumItems(m_EndPosParaMenu.hList))
        {
            if(0==LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,i))
            {
                if(i==LISTBOX_GetSel(m_EndPosParaMenu.hList))
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

static void _WinEndPosParaMenuCallback(WM_MESSAGE * pMsg)
{
    int     id = 0;

    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
        case GUI_KEY_UP:
            _WinEndPosParaMenuKeyUp();
            break;
        case GUI_KEY_DOWN:
            _WinEndPosParaMenuKeyDown();
            break;
        case GUI_KEY_ENTER:
            _WinEndPosParaMenuKeyEnter();
            break;
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}

static void _WinEndPosParaMenuCreate(void *p)
{
    static int      bufSize     = sizeof(g_LCDBuff);

    MENU_INFO_ITEM  *pMenu      = (MENU_INFO_ITEM *)p;
    GUI_HWIN        hWin        = 0;
    short           val         = 0;
    short           i           = 0;
    char            *pBuffter   = g_LCDBuff;
    const char      *pTitle     = pMenu->data->title[g_LanguageIndex];
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;
	dataStructInterface.Frame_SN=pMenu->data->SN;
	#if 1
	GUI_SetBkColor(GUI_WHITE);      
    GUI_Clear();
	#endif
    if (NULL == pTitle) pTitle = "";

    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
	_WinMomentCloseRefesh();
	_WinMomentOpenRefresh();
	_WinSpeedCloseRefresh();
    _WinSpeedOpenRefresh ();

    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    GUI_EnableAlpha(1);

#if 1      
	m_EndPosParaMenu.hImage_CB_1 = IMAGE_CreateEx(0,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EndPosParaMenu.hImage_CB_1,&bmComBack_1);
	
	m_EndPosParaMenu.hImage_CB_2 = IMAGE_CreateEx(260,0,60,240,WM_HBKWIN,WM_CF_SHOW,IMAGE_CF_ALPHA,NULL);
	IMAGE_SetBitmap(m_EndPosParaMenu.hImage_CB_2,&bmComBack_2);
    #endif
    m_EndPosParaMenu.hText     = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+23+10, DEBUG_Y_OFFSET, PER_CM_OFFSET*4.5-23, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    m_EndPosParaMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+35, DEBUG_Y_OFFSET+23+10,                      250, PER_CM_OFFSET*3.5, hWin, WM_CF_SHOW|WM_CF_HASTRANS, NULL, NULL,NULL);
    m_EndPosParaMenu.hListEnter = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET+10+10, DEBUG_Y_OFFSET+23+10+PER_CM_OFFSET*3.5+10, 180, 26, hWin, WM_CF_SHOW|WM_CF_HASTRANS, NULL, NULL,NULL);

    hWin = WM_GetFirstChild(m_EndPosParaMenu.hFrame);            
    m_EndPosParaMenu.hBtnRtn    = BUTTON_CreateAsChild(DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET, 40, 22,hWin,NULL, WM_CF_SHOW);    
    hWin = m_EndPosParaMenu.hBtnRtn;		
    BUTTON_SetSkin(hWin,SKIN_Btn_Btn);
    BUTTON_SetPressed(hWin,1);

    header_txt(DEBUG_X_OFFSET+PER_CM_OFFSET+41, DEBUG_Y_OFFSET,184-20,23);
    hWin = m_EndPosParaMenu.hText;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
    TEXT_SetText(hWin, strShow);

    hWin = m_EndPosParaMenu.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 7);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_DISABLED , GUI_TRANSPARENT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SEL      , GUI_TRANSPARENT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SELFOCUS , GUI_TRANSPARENT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_UNSEL    , GUI_TRANSPARENT);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_DISABLED , GUI_BLUE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SEL      , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SELFOCUS , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_UNSEL    , GUI_BLACK);
    LISTBOX_SetSel(hWin,-1);
    LISTBOX_SetAutoScrollV(hWin,0);
    LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw51);

    for(i=0;i<pMenu->data->menunum;i++)
    {
    	memset(strShow,0,sizeof(strShow));
        if(LANGUAGE_CN == g_LanguageIndex) enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) enc_unicode_to_utf8_str(pContentEn,strShow,STRSHOWBUF_SIZE);
        pContentCn += MAX_INFO_CHAR;
        pContentEn += MAX_INFO_CHAR;
        if(MENU_SETTING_DISAPP == pMenu->data->menuattri[i]) continue;
        LISTBOX_AddString(hWin, strShow);
        if(MENU_SETTING_TITLE == pMenu->data->menuattri[i]) LISTBOX_SetItemDisabled(hWin,i,1);
    }
    m_EndPosParaMenu.menuFlag = pMenu->data->menunum;


    hWin = m_EndPosParaMenu.hListEnter;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);
    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 6);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetOwnerDraw(hWin, _WinCommonMenuListOwnerDraw3);
    LISTBOX_SetSel(hWin, -1);
    StrShowClear();
    enc_unicode_to_utf8_str(info_menu_continue[0],strShow,STRSHOWBUF_SIZE);
    LISTBOX_AddString(hWin, strShow);

    WM_SetCallback(WM_HBKWIN, _WinEndPosParaMenuCallback);
}

static void _WinEndPosParaMenuDestroy(void *p)
{
		WM_DeleteWindow(m_EndPosParaMenu.hImage_CB_1);         
		WM_DeleteWindow(m_EndPosParaMenu.hImage_CB_2);         
    WM_DeleteWindow(m_EndPosParaMenu.hBtnRtn);             
    WM_DeleteWindow(m_EndPosParaMenu.hText);               
    WM_DeleteWindow(m_EndPosParaMenu.hList);               
	  WM_DeleteWindow(m_EndPosParaMenu.hImageBack);          
	  WM_DeleteWindow(m_EndPosParaMenu.hListEnter);          
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_EndPosParaMenu, 0, sizeof(m_EndPosParaMenu));
}

void _WinEndPosParaMenuInterface(void *val)
{
    int sel = *(int *)val;
    int i=0;
    int j=0;

    if(sel == 100 )  
    {
        return ;
    }
    else             
    {
        if (m_EndPosParaMenu.hList == 0) return;

        if ((sel < (int)LISTBOX_GetNumItems(m_EndPosParaMenu.hList)) && (sel >= 0)&& (sel < 4))
        {
            LISTBOX_SetSel(m_EndPosParaMenu.hListEnter, -1);
            BUTTON_SetPressed(m_EndPosParaMenu.hBtnRtn,0);
            while(i<LISTBOX_GetNumItems(m_EndPosParaMenu.hList))
            {
                if(0==LISTBOX_GetItemDisabled(m_EndPosParaMenu.hList,i))
                {
                    if(j==sel)
                    {
                        LISTBOX_SetBkColor(m_EndPosParaMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
                        LISTBOX_SetSel(m_EndPosParaMenu.hList, i);
                        break;
                    }
                    j++;
                }
                i++;
            }
        }
        else 
        {
        	BUTTON_SetPressed(m_EndPosParaMenu.hBtnRtn,0);
        	LISTBOX_SetSel(m_EndPosParaMenu.hListEnter, 0);
        }
    }
}


WIN_INFO_TYPE g_WinEndPosParaMenu = {                        
    &m_EndPosParaMenu.hFrame,
    _WinEndPosParaMenuCreate,
    _WinEndPosParaMenuDestroy
};


static int _GetItemSizeY_CommonList3(WM_HWIN hWin, int ItemIndex) {
  int DistY;
  DistY = GUI_GetFontDistY()+ 8+18-16-4;
  return DistY;
}

static void DrawGradientV_PointWhite(int x0, int y0, int x1, int y1)
{
  int y_mid = (y1-y0)/2+y0;
  GUI_DrawGradientV(x0,y0,x0,y_mid ,GUI_WHITE,GUI_BLACK);
  GUI_DrawGradientV(x0,y_mid+1,x1,y1,GUI_BLACK,GUI_WHITE);
}
int _WinCommonMenuListOwnerDraw00(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN hWin;
  int     Index;

  hWin     = pDrawItemInfo->hWin;
  Index    = pDrawItemInfo->ItemIndex;
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    return _GetItemSizeX_CommonList(hWin, Index);
  case WIDGET_ITEM_GET_YSIZE:
    return _GetItemSizeY_CommonList3(hWin, Index);
  case WIDGET_ITEM_DRAW:
    {
      int   Sel;
      int   YSize;
      int   FontDistY;
      int   IsDisabled;
      int   IsSelected;
      int   ColorIndex;
      char  acBuffer[100];
			int   FontDistX;
			GUI_RECT rFocus;
			GUI_RECT rFocus2;
     
      IsDisabled = LISTBOX_GetItemDisabled(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex);
      IsSelected = LISTBOX_GetItemSel(hWin, Index);

      Sel        = LISTBOX_GetSel(hWin);
      YSize      = _GetItemSizeY_CommonList(hWin, Index);

      memset(acBuffer,0,100);
      GUI_SetBkColor(GUI_WHITE);  
      LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex, acBuffer, sizeof(acBuffer));
			GUI_Clear();
      if(pDrawItemInfo->ItemIndex == 0)
      {
          DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0, pDrawItemInfo->x0+190, pDrawItemInfo->y0);
					DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25-4, pDrawItemInfo->x0+190, pDrawItemInfo->y0+25-4);
			}else
	  	{
					DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25-4, pDrawItemInfo->x0+190, pDrawItemInfo->y0+25-4);
	  	}
			
      GUI_SetColor(GUI_ORANGE);
      if (Sel==1)
			{
				rFocus.x0  = pDrawItemInfo->x0;
				rFocus.x1  = pDrawItemInfo->x0+80+26-5;
				rFocus2.x0 = pDrawItemInfo->x0+76+26-5;
				rFocus2.x1 = pDrawItemInfo->x0+84+26-5;
			}else
			 if (Sel==2)
			{
				rFocus.x0  = pDrawItemInfo->x0;
				rFocus.x1  = pDrawItemInfo->x0+125+20;
				rFocus2.x0 = pDrawItemInfo->x0+121+20;
				rFocus2.x1 = pDrawItemInfo->x0+129+20;
			}else
			{
				rFocus.x0 = pDrawItemInfo->x0;
				rFocus.x1 = pDrawItemInfo->x0+184;
			}
			
      rFocus.y0 = pDrawItemInfo->y0+1+2-1;     
      rFocus.y1 = pDrawItemInfo->y0+25-1-2-3;
			rFocus2.y0 = pDrawItemInfo->y0+1+2-1;      
      rFocus2.y1 = pDrawItemInfo->y0+25-1-2-3;
			
      if (pDrawItemInfo->ItemIndex == Sel)
      {
				if(Sel==0)
				{
					GUI_SetColor(GUI_ORANGE);
					GUI_AA_FillRoundedRectEx(&rFocus, 4);
					GUI_SetColor(GUI_WHITE);
					GUI_AA_FillCircle(rFocus.x0-2,rFocus.y0,10);
					GUI_AA_FillCircle(rFocus.x1+2,rFocus.y0,10);
					
				}else
				if(Sel==1)
				{
					GUI_SetColor(GUI_ORANGE);
					GUI_AA_FillRoundedRectEx(&rFocus, 4);
					GUI_SetColor(GUI_WHITE);
					GUI_AA_FillRoundedRectEx(&rFocus2, 4);
					
				}else
				if(Sel==2)
				{
					GUI_SetColor(GUI_ORANGE);
					GUI_AA_FillRoundedRectEx(&rFocus, 4);
					GUI_SetColor(GUI_WHITE);
					GUI_AA_FillRoundedRectEx(&rFocus2, 4);
				}else
				{
					GUI_SetColor(GUI_ORANGE);
					GUI_AA_FillRoundedRectEx(&rFocus, 4);
				}
				
      }else
			{
			}

		

			GUI_SetTextMode(GUI_TM_TRANS);
      FontDistY  = GUI_GetFontDistY();

			GUI_SetColor(GUI_BLACK);
			FontDistX = pDrawItemInfo->x0+1;

      GUI_DispStringAt(acBuffer, FontDistX , pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
    }
    break;
  default:
    return LISTBOX_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}


int _WinCommonMenuListOwnerDraw3(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN hWin;
  int     Index;

  hWin     = pDrawItemInfo->hWin;
  Index    = pDrawItemInfo->ItemIndex;
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    return _GetItemSizeX_CommonList(hWin, Index);
  case WIDGET_ITEM_GET_YSIZE:
    return _GetItemSizeY_CommonList4(hWin, Index);
  case WIDGET_ITEM_DRAW:
#if 1
    {
      int   Sel;
      int   YSize;
      int   FontDistY;
      int   IsDisabled;
      int   IsSelected;
      int   ColorIndex;
      char  acBuffer[100];
	  int   FontDistX;
GUI_RECT rFocus;
      IsDisabled = LISTBOX_GetItemDisabled(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex);
      IsSelected = LISTBOX_GetItemSel(hWin, Index);

      Sel        = LISTBOX_GetSel(hWin);
      YSize      = _GetItemSizeY_CommonList(hWin, Index);

      memset(acBuffer,0,100);
      GUI_SetBkColor(GUI_WHITE);
      GUI_SetColor  (GUI_WHITE);
      LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex, acBuffer, sizeof(acBuffer));
			GUI_Clear();
      if(pDrawItemInfo->ItemIndex == 0)
      {
          DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0, pDrawItemInfo->x0+180, pDrawItemInfo->y0);
					DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+180, pDrawItemInfo->y0+25);
			}else
	  	{
					DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+180, pDrawItemInfo->y0+25);
	  	}
			GUI_SetColor(GUI_ORANGE);

      
			rFocus.x0 = pDrawItemInfo->x0;
      rFocus.y0 = pDrawItemInfo->y0+1+2;
      rFocus.x1 = pDrawItemInfo->x0+180;
      rFocus.y1 = pDrawItemInfo->y0+25-1-2;
      if (pDrawItemInfo->ItemIndex == Sel)
      {
          GUI_AA_FillRoundedRectEx(&rFocus, 4);
      }

	  GUI_SetTextMode(GUI_TM_TRANS);
      FontDistY  = GUI_GetFontDistY();

	  GUI_SetColor(GUI_BLACK);
	  FontDistX = pDrawItemInfo->x0+1;

      GUI_DispStringAt(acBuffer, FontDistX , pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
    }
#endif // 0
    break;
  default:
    return LISTBOX_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}
int _WinCommonMenuListOwnerDraw4(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN hWin;
  int     Index;

  hWin     = pDrawItemInfo->hWin;
  Index    = pDrawItemInfo->ItemIndex;
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    return _GetItemSizeX_CommonList(hWin, Index);
  case WIDGET_ITEM_GET_YSIZE:
    return _GetItemSizeY_CommonList4(hWin, Index);
  case WIDGET_ITEM_DRAW:
#if 1
    {
      int   Sel;
      int   YSize;
      int   FontDistY;
      int   IsDisabled;
      int   IsSelected;
      int   ColorIndex;
      char  acBuffer[100];
	  int   FontDistX;
GUI_RECT rFocus;
      IsDisabled = LISTBOX_GetItemDisabled(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex);
      IsSelected = LISTBOX_GetItemSel(hWin, Index);

      Sel        = LISTBOX_GetSel(hWin);
      YSize      = _GetItemSizeY_CommonList(hWin, Index);
		 	if(IsSelected)
	  {
			GUI_SetColor(GUI_WHITE);
	  }
	  else
	  {
	    GUI_SetColor(GUI_ORANGE);
	  }
      memset(acBuffer,0,100);
      GUI_SetBkColor(GUI_WHITE);
      GUI_SetColor  (GUI_WHITE);
      LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex, acBuffer, sizeof(acBuffer));

      if(pDrawItemInfo->ItemIndex == 0)
        {
          DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0, pDrawItemInfo->x0+248, pDrawItemInfo->y0);
	  	  DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248, pDrawItemInfo->y0+25);
      	}
	  else
	  	{
	  	  DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248, pDrawItemInfo->y0+25);
	  	}

	  DrawGradientV_PointWhite(pDrawItemInfo->x0    ,pDrawItemInfo->y0,pDrawItemInfo->x0    ,pDrawItemInfo->y0+25);
	  DrawGradientV_PointWhite(pDrawItemInfo->x0+248,pDrawItemInfo->y0,pDrawItemInfo->x0+248,pDrawItemInfo->y0+25);

      GUI_SetColor(GUI_ORANGE);

      
      rFocus.x0 = pDrawItemInfo->x0+1;
      rFocus.y0 = pDrawItemInfo->y0+1+2;
      rFocus.x1 = pDrawItemInfo->x0+248-1;
      rFocus.y1 = pDrawItemInfo->y0+25-1-2;
      if (pDrawItemInfo->ItemIndex == Sel)
      {
          GUI_AA_FillRoundedRectEx(&rFocus, 4);
      }
			else
			{
				GUI_SetColor(GUI_WHITE);
				GUI_AA_FillRoundedRectEx(&rFocus, 4);
			}

	  GUI_SetTextMode(GUI_TM_TRANS);
      FontDistY  = GUI_GetFontDistY();

			  if(IsDisabled)
	  {
	    GUI_SetColor(GUI_GRAY);
		FontDistX = pDrawItemInfo->x0+1;
	  }
	  else
	  {
	    GUI_SetColor(GUI_BLACK);
	    FontDistX = pDrawItemInfo->x0+1;
	  }

      GUI_DispStringAt(acBuffer, FontDistX , pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
    }
#endif // 0
    break;
  default:
    return LISTBOX_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}

int _WinCommonMenuListOwnerDraw5(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN hWin;
  int     Index;

  hWin     = pDrawItemInfo->hWin;
  Index    = pDrawItemInfo->ItemIndex;
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    return _GetItemSizeX_CommonList(hWin, Index);
  case WIDGET_ITEM_GET_YSIZE:
    return _GetItemSizeY_CommonList4(hWin, Index);
  case WIDGET_ITEM_DRAW:
#if 1
    {
      int   Sel;
      int   YSize;
      int   FontDistY;
      int   IsDisabled;
      int   IsSelected;
      int   ColorIndex;
      char  acBuffer[100];
	  int   FontDistX;
		GUI_RECT rFocus;
      IsDisabled = LISTBOX_GetItemDisabled(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex);
      IsSelected = LISTBOX_GetItemSel(hWin, Index);

      Sel        = LISTBOX_GetSel(hWin);
      YSize      = _GetItemSizeY_CommonList(hWin, Index);

      memset(acBuffer,0,100);
      GUI_SetBkColor(GUI_WHITE);
      GUI_SetColor  (GUI_WHITE);
      LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex, acBuffer, sizeof(acBuffer));
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == 0)
        {
          if(IsDisabled)
          {
            DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0, pDrawItemInfo->x0+203, pDrawItemInfo->y0);
	    	DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+203, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0    ,pDrawItemInfo->y0,pDrawItemInfo->x0    ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+203,pDrawItemInfo->y0,pDrawItemInfo->x0+203,pDrawItemInfo->y0+25);
          }
		  else
		  {
		    DrawGradientH_PointWhite(pDrawItemInfo->x0+12, pDrawItemInfo->y0, pDrawItemInfo->x0+203, pDrawItemInfo->y0);
	    	DrawGradientH_PointWhite(pDrawItemInfo->x0+12, pDrawItemInfo->y0+25, pDrawItemInfo->x0+203, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0+12 ,pDrawItemInfo->y0,pDrawItemInfo->x0+12 ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+203,pDrawItemInfo->y0,pDrawItemInfo->x0+203,pDrawItemInfo->y0+25);
		  }
      	}
	  else
	  	{
	  	  if(IsDisabled)
          {
	    	DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0    ,pDrawItemInfo->y0,pDrawItemInfo->x0    ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+203,pDrawItemInfo->y0,pDrawItemInfo->x0+203,pDrawItemInfo->y0+25);
          }
		  else
		  {
		    DrawGradientH_PointWhite(pDrawItemInfo->x0+12, pDrawItemInfo->y0+25, pDrawItemInfo->x0+203, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0+12 ,pDrawItemInfo->y0,pDrawItemInfo->x0+12 ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+203,pDrawItemInfo->y0,pDrawItemInfo->x0+203,pDrawItemInfo->y0+25);
		  }
	  	}

			

      GUI_SetColor(GUI_ORANGE);

      
      rFocus.x0 = pDrawItemInfo->x0+1+12;
      rFocus.y0 = pDrawItemInfo->y0+1+2-2;
      rFocus.x1 = pDrawItemInfo->x0+203;
      rFocus.y1 = pDrawItemInfo->y0+25-1-2+1;
      if (pDrawItemInfo->ItemIndex == Sel)
      {
          GUI_AA_FillRoundedRectEx(&rFocus, 4);
      }

	  GUI_SetTextMode(GUI_TM_TRANS);
      FontDistY  = GUI_GetFontDistY();

      if(IsDisabled)
	  {
	    GUI_SetColor(GUI_BLUE);
		FontDistX = pDrawItemInfo->x0+1;
	  }
	  else
	  {
	    GUI_SetColor(GUI_BLACK);
	    FontDistX = pDrawItemInfo->x0+1+12;
	  }
	  
      GUI_DispStringAt(acBuffer, FontDistX , pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
   

			#if 1
			  if (pDrawItemInfo->ItemIndex == Sel)
      {
          GUI_DrawBitmap(&bmiteam_sel, FontDistX+166 , pDrawItemInfo->y0 + 1) ;
      }
			else if(!IsDisabled)
			{
					GUI_DrawBitmap(&bmiteam_unsel, FontDistX+166 , pDrawItemInfo->y0 + 1) ;
			}
			 if (pDrawItemInfo->ItemIndex == 1)
      {
          GUI_DrawBitmap(&bmuser_watcher, FontDistX+1 , pDrawItemInfo->y0 + 1) ;
      }
	  else if (pDrawItemInfo->ItemIndex == 3)
      {
          GUI_DrawBitmap(&bmuser_hander, FontDistX+1 , pDrawItemInfo->y0 + 1) ;
      }
	  else if (pDrawItemInfo->ItemIndex == 4)
      {
          GUI_DrawBitmap(&bmuser_monitor, FontDistX+1 , pDrawItemInfo->y0 + 1) ;
      }
	  else if (pDrawItemInfo->ItemIndex == 5)
      {
          GUI_DrawBitmap(&bmuser_expert, FontDistX+1 , pDrawItemInfo->y0 + 1) ;
      }
	  else if (pDrawItemInfo->ItemIndex == 6)
      {
          GUI_DrawBitmap(&bmuser_service, FontDistX+1 , pDrawItemInfo->y0 + 1) ;
      }
	  else if (pDrawItemInfo->ItemIndex == 7)
      {
          GUI_DrawBitmap(&bmuser_factory, FontDistX+1 , pDrawItemInfo->y0 + 1) ;
      }
			#endif


		}
#endif // 0
    break;
  default:
    return LISTBOX_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}

int _WinCommonMenuListOwnerDraw6(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN hWin;
  int     Index;

  hWin     = pDrawItemInfo->hWin;
  Index    = pDrawItemInfo->ItemIndex;
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    return _GetItemSizeX_CommonList(hWin, Index);
  case WIDGET_ITEM_GET_YSIZE:
    return _GetItemSizeY_CommonList4(hWin, Index);
  case WIDGET_ITEM_DRAW:
#if 1
    {
      int   Sel;
      int   YSize;
      int   FontDistY;
      int   IsDisabled;
      int   IsSelected;
      int   ColorIndex;
      char  acBuffer[100];
	  int   FontDistX;
GUI_RECT rFocus;
      IsDisabled = LISTBOX_GetItemDisabled(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex);
      IsSelected = LISTBOX_GetItemSel(hWin, Index);

      Sel        = LISTBOX_GetSel(hWin);
      YSize      = _GetItemSizeY_CommonList(hWin, Index);
		 	if(IsSelected)
	  {
			GUI_SetColor(GUI_WHITE);
	  }
	  else
	  {
	    GUI_SetColor(GUI_ORANGE);
	  }
      memset(acBuffer,0,100);
      GUI_SetBkColor(GUI_WHITE);
      GUI_SetColor  (GUI_WHITE);
      LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex, acBuffer, sizeof(acBuffer));

      if(pDrawItemInfo->ItemIndex == 0)
        {
          DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0);
	  	  DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0+25);
      	}
	  else
	  	{
	  	  DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0+25);
	  	}

	  DrawGradientV_PointWhite(pDrawItemInfo->x0    ,pDrawItemInfo->y0,pDrawItemInfo->x0    ,pDrawItemInfo->y0+25);
	  DrawGradientV_PointWhite(pDrawItemInfo->x0+248-10,pDrawItemInfo->y0,pDrawItemInfo->x0+248-10,pDrawItemInfo->y0+25);

      GUI_SetColor(GUI_ORANGE);

      
      rFocus.x0 = pDrawItemInfo->x0+1;
      rFocus.y0 = pDrawItemInfo->y0+1+2;
      rFocus.x1 = pDrawItemInfo->x0+248-1-10;
      rFocus.y1 = pDrawItemInfo->y0+25-1-2;
      if (pDrawItemInfo->ItemIndex == Sel)
      {
          GUI_AA_FillRoundedRectEx(&rFocus, 4);
      }
			else
			{
				GUI_SetColor(GUI_WHITE);
				GUI_AA_FillRoundedRectEx(&rFocus, 4);
			}

	  GUI_SetTextMode(GUI_TM_TRANS);
      FontDistY  = GUI_GetFontDistY();

			  if(IsDisabled)
	  {
	    GUI_SetColor(GUI_GRAY);
		FontDistX = pDrawItemInfo->x0+1;
	  }
	  else
	  {
	    GUI_SetColor(GUI_BLACK);
	    FontDistX = pDrawItemInfo->x0+1;
	  }

      GUI_DispStringAt(acBuffer, FontDistX , pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
    }
#endif // 0
    break;
  default:
    return LISTBOX_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}

static int _GetItemSizeY_CommonList4(WM_HWIN hWin, int ItemIndex) {
  int DistY;
  DistY = GUI_GetFontDistY()+ 8+18-16;
  return DistY;
}
int _WinCommonMenuListOwnerDraw50(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN hWin;
  int     Index;

  hWin     = pDrawItemInfo->hWin;
  Index    = pDrawItemInfo->ItemIndex;
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    return _GetItemSizeX_CommonList(hWin, Index);
  case WIDGET_ITEM_GET_YSIZE:
    return _GetItemSizeY_CommonList4(hWin, Index);
  case WIDGET_ITEM_DRAW:
#if 1
    {
      int   Sel;
      int   YSize;
      int   FontDistY;
      int   IsDisabled;
      int   IsSelected;
      int   ColorIndex;
      char  acBuffer[100];
	  int   FontDistX;
		GUI_RECT rFocus;
      IsDisabled = LISTBOX_GetItemDisabled(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex);
      IsSelected = LISTBOX_GetItemSel(hWin, Index);

      Sel        = LISTBOX_GetSel(hWin);
      YSize      = _GetItemSizeY_CommonList(hWin, Index);

      memset(acBuffer,0,100);
      GUI_SetBkColor(GUI_WHITE);
      GUI_SetColor  (GUI_WHITE);
      LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex, acBuffer, sizeof(acBuffer));
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == 0)
        {
          if(IsDisabled)
          {
            DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0);
	    	DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0    ,pDrawItemInfo->y0,pDrawItemInfo->x0    ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+248-10,pDrawItemInfo->y0,pDrawItemInfo->x0+248-10,pDrawItemInfo->y0+25);
          }
		  else
		  {
		    DrawGradientH_PointWhite(pDrawItemInfo->x0+12, pDrawItemInfo->y0, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0);
	    	DrawGradientH_PointWhite(pDrawItemInfo->x0+12, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0+12 ,pDrawItemInfo->y0,pDrawItemInfo->x0+12 ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+248-10,pDrawItemInfo->y0,pDrawItemInfo->x0+248-10,pDrawItemInfo->y0+25);
		  }
      	}
	  else
	  	{
	  	  if(IsDisabled)
          {
	    	DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0    ,pDrawItemInfo->y0,pDrawItemInfo->x0    ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+248-10,pDrawItemInfo->y0,pDrawItemInfo->x0+248-10,pDrawItemInfo->y0+25);
          }
		  else
		  {
		    DrawGradientH_PointWhite(pDrawItemInfo->x0+12, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0+12 ,pDrawItemInfo->y0,pDrawItemInfo->x0+12 ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+248-10,pDrawItemInfo->y0,pDrawItemInfo->x0+248-10,pDrawItemInfo->y0+25);
		  }
	  	}

			

      GUI_SetColor(GUI_ORANGE);

      
      rFocus.x0 = pDrawItemInfo->x0+1+12;
      rFocus.y0 = pDrawItemInfo->y0+1+2;
      rFocus.x1 = pDrawItemInfo->x0+248-10-1;
      rFocus.y1 = pDrawItemInfo->y0+25-1-2;
      if (pDrawItemInfo->ItemIndex == Sel)
      {
          GUI_AA_FillRoundedRectEx(&rFocus, 4);
      }

	  GUI_SetTextMode(GUI_TM_TRANS);
      FontDistY  = GUI_GetFontDistY();

      if(IsDisabled)
	  {
	    GUI_SetColor(GUI_BLUE);
		FontDistX = pDrawItemInfo->x0+1;
	  }
	  else
	  {
	    GUI_SetColor(GUI_BLACK);
	    FontDistX = pDrawItemInfo->x0+1+12;
	  }
	  
      GUI_DispStringAt(acBuffer, FontDistX , pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
			if(dataStructInterface.Frame_SN==9)
			{				
			 if (pDrawItemInfo->ItemIndex == 3)
				{
						GUI_DrawBitmap(&bmlist_close, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
				if (pDrawItemInfo->ItemIndex == 4)
				{
						GUI_DrawBitmap(&bmlist_open, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
					 if (pDrawItemInfo->ItemIndex == 10)
				{
						GUI_DrawBitmap(&bmlist_close, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
				if (pDrawItemInfo->ItemIndex == 11)
				{
						GUI_DrawBitmap(&bmlist_open, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
			}
			if(dataStructInterface.Frame_SN==13)
			{				
			 if (pDrawItemInfo->ItemIndex == 3)
				{
						GUI_DrawBitmap(&bmlist_close, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
				if (pDrawItemInfo->ItemIndex == 4)
				{
						GUI_DrawBitmap(&bmlist_open, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
					 if (pDrawItemInfo->ItemIndex == 6)
				{
						GUI_DrawBitmap(&bmlist_close, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
				if (pDrawItemInfo->ItemIndex == 7)
				{
						GUI_DrawBitmap(&bmlist_open, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
					 if (pDrawItemInfo->ItemIndex == 9)
				{
						GUI_DrawBitmap(&bmlist_close, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
				if (pDrawItemInfo->ItemIndex == 10)
				{
						GUI_DrawBitmap(&bmlist_open, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
					 if (pDrawItemInfo->ItemIndex == 12)
				{
						GUI_DrawBitmap(&bmlist_close, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
				if (pDrawItemInfo->ItemIndex == 13)
				{
						GUI_DrawBitmap(&bmlist_open, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
			}
		}
#endif // 0
    break;
  default:
    return LISTBOX_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}

int _WinCommonMenuListOwnerDraw51(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN hWin;
  int     Index;

  hWin     = pDrawItemInfo->hWin;
  Index    = pDrawItemInfo->ItemIndex;
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    return _GetItemSizeX_CommonList(hWin, Index);
  case WIDGET_ITEM_GET_YSIZE:
    return _GetItemSizeY_CommonList4(hWin, Index);
  case WIDGET_ITEM_DRAW:
#if 1
    {
      int   Sel;
      int   YSize;
      int   FontDistY;
      int   IsDisabled;
      int   IsSelected;
      int   ColorIndex;
      char  acBuffer[100];
	  int   FontDistX;
		GUI_RECT rFocus;
      IsDisabled = LISTBOX_GetItemDisabled(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex);
      IsSelected = LISTBOX_GetItemSel(hWin, Index);

      Sel        = LISTBOX_GetSel(hWin);
      YSize      = _GetItemSizeY_CommonList(hWin, Index);

      memset(acBuffer,0,100);
      GUI_SetBkColor(GUI_WHITE);
      GUI_SetColor  (GUI_WHITE);
      LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex, acBuffer, sizeof(acBuffer));
	  GUI_Clear();
      if(pDrawItemInfo->ItemIndex == 0)
        {
          if(IsDisabled)
          {
            DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0);
	    	DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0    ,pDrawItemInfo->y0,pDrawItemInfo->x0    ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+248-10,pDrawItemInfo->y0,pDrawItemInfo->x0+248-10,pDrawItemInfo->y0+25);
          }
		  else
		  {
		    DrawGradientH_PointWhite(pDrawItemInfo->x0+12, pDrawItemInfo->y0, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0);
	    	DrawGradientH_PointWhite(pDrawItemInfo->x0+12, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0+12 ,pDrawItemInfo->y0,pDrawItemInfo->x0+12 ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+248-10,pDrawItemInfo->y0,pDrawItemInfo->x0+248-10,pDrawItemInfo->y0+25);
		  }
      	}
	  else
	  	{
	  	  if(IsDisabled)
          {
	    	DrawGradientH_PointWhite(pDrawItemInfo->x0, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0    ,pDrawItemInfo->y0,pDrawItemInfo->x0    ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+248-10,pDrawItemInfo->y0,pDrawItemInfo->x0+248-10,pDrawItemInfo->y0+25);
          }
		  else
		  {
		    DrawGradientH_PointWhite(pDrawItemInfo->x0+12, pDrawItemInfo->y0+25, pDrawItemInfo->x0+248-10, pDrawItemInfo->y0+25);

			DrawGradientV_PointWhite(pDrawItemInfo->x0+12 ,pDrawItemInfo->y0,pDrawItemInfo->x0+12 ,pDrawItemInfo->y0+25);
	        DrawGradientV_PointWhite(pDrawItemInfo->x0+248-10,pDrawItemInfo->y0,pDrawItemInfo->x0+248-10,pDrawItemInfo->y0+25);
		  }
	  	}

			

      GUI_SetColor(GUI_ORANGE);

      
      rFocus.x0 = pDrawItemInfo->x0+1+12;
      rFocus.y0 = pDrawItemInfo->y0+1+2;
      rFocus.x1 = pDrawItemInfo->x0+248-10-1;
      rFocus.y1 = pDrawItemInfo->y0+25-1-2;
      if (pDrawItemInfo->ItemIndex == Sel)
      {
          GUI_AA_FillRoundedRectEx(&rFocus, 4);
      }

	  GUI_SetTextMode(GUI_TM_TRANS);
      FontDistY  = GUI_GetFontDistY();

      if(IsDisabled)
	  {
	    GUI_SetColor(GUI_BLUE);
		FontDistX = pDrawItemInfo->x0+1;
	  }
	  else
	  {
	    GUI_SetColor(GUI_BLACK);
	    FontDistX = pDrawItemInfo->x0+1+12;
	  }
	  
      GUI_DispStringAt(acBuffer, FontDistX , pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
			if(dataStructInterface.Frame_SN==1)
			{				
			 if (pDrawItemInfo->ItemIndex == 3)
				{
						GUI_DrawBitmap(&bmlist_close, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
				if (pDrawItemInfo->ItemIndex == 4)
				{
						GUI_DrawBitmap(&bmlist_open, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
			}
			if(dataStructInterface.Frame_SN==2)
			{				
			 if (pDrawItemInfo->ItemIndex == 1)
				{
						GUI_DrawBitmap(&bmlist_close, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
				if (pDrawItemInfo->ItemIndex == 2)
				{
						GUI_DrawBitmap(&bmlist_open, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
					 if (pDrawItemInfo->ItemIndex == 4)
				{
						GUI_DrawBitmap(&bmlist_close, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
				if (pDrawItemInfo->ItemIndex == 5)
				{
						GUI_DrawBitmap(&bmlist_open, FontDistX+1 , pDrawItemInfo->y0 + 2) ;
				}
			
			}
		}
#endif // 0
    break;
  default:
    return LISTBOX_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}


static int _WinCommonSelectListOwnerDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN hWin;
  int     Index;

  hWin     = pDrawItemInfo->hWin;
  Index    = pDrawItemInfo->ItemIndex;
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    return _GetItemSizeX_CommonList(hWin, Index);
  case WIDGET_ITEM_GET_YSIZE:
    return _GetItemSizeY_CommonList(hWin, Index);
  case WIDGET_ITEM_DRAW:
#if 1
    {
      int   Sel;
      int   YSize;
      int   FontDistY;
      int   IsDisabled;
      int   IsSelected;
      int   ColorIndex;
      char  acBuffer[100];
	  int   FontDistX;
GUI_RECT rFocus;
      IsDisabled = LISTBOX_GetItemDisabled(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex);
      IsSelected = LISTBOX_GetItemSel(hWin, Index);

      Sel        = LISTBOX_GetSel(hWin);
      YSize      = _GetItemSizeY_CommonList(hWin, Index);

      memset(acBuffer,0,100);
      GUI_SetBkColor(GUI_WHITE);
      GUI_SetColor  (GUI_WHITE);
      LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex, acBuffer, sizeof(acBuffer));
	  GUI_Clear();

      if(pDrawItemInfo->ItemIndex == 0)
        {
	  	  if(IsDisabled)
	  	  {
	  	  }
		  else
		  {
		  }
      	}
	  else
	  	{
	  	  if(IsDisabled)
	  	  {
	  	  }
		  else
		  {
		  }
      	}

      GUI_SetColor(GUI_ORANGE);

      
      rFocus.x0 = pDrawItemInfo->x0+1+10;
      rFocus.y0 = pDrawItemInfo->y0+1;
      rFocus.x1 = pDrawItemInfo->x0+1+10+189;
      rFocus.y1 = pDrawItemInfo->y0 + 21;
      if (pDrawItemInfo->ItemIndex == Sel)
      {
          GUI_AA_FillRoundedRectEx(&rFocus, 4);
      }

	  GUI_SetTextMode(GUI_TM_TRANS);
      FontDistY  = GUI_GetFontDistY();
	  if(IsDisabled)
	  {
	    GUI_SetColor(GUI_BLUE);
		FontDistX = pDrawItemInfo->x0+1;
	  }
	  else
	  {
	    GUI_SetColor(GUI_BLACK);
		FontDistX = pDrawItemInfo->x0+11;
	  }
      GUI_DispStringAt(acBuffer, FontDistX , pDrawItemInfo->y0 + (YSize - FontDistY) / 2);

      if (pDrawItemInfo->ItemIndex == Sel)
      {
      }
	  else if(!IsDisabled)
	  {
	  }
    }
#endif // 0
    break;
  default:
    return LISTBOX_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}













void header_txt(int x0,int y0,int longx,int longy)
{
	GUI_RECT rFocus;
	GUI_SetColor(0x00FF901E);
	
	rFocus.x0 = x0;
	rFocus.y0 = y0;
	rFocus.x1 = x0+longx;
	rFocus.y1 = y0+longy;
	GUI_AA_FillRoundedRectEx(&rFocus, 4);
	GUI_SetColor(GUI_BLACK);
	
}

