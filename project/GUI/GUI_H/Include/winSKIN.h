#ifndef winSKIN_H        /* Avoid multiple inclusion  */
#define winSKIN_H
#include "widget.h"
#include "LISTBOX.h"
#include "BUTTON.h"
#include "string.h"

extern GUI_CONST_STORAGE GUI_BITMAP bmiteam_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmiteam_unsel;
extern GUI_CONST_STORAGE GUI_BITMAP bmuser_watcher;
extern GUI_CONST_STORAGE GUI_BITMAP bmuser_monitor;
extern GUI_CONST_STORAGE GUI_BITMAP bmuser_hander;
extern GUI_CONST_STORAGE GUI_BITMAP bmuser_factory;
extern GUI_CONST_STORAGE GUI_BITMAP bmuser_service;
extern GUI_CONST_STORAGE GUI_BITMAP bmuser_expert;



int _WinCommonMenuListOwnerDraw50(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) ;
int _WinCommonMenuListOwnerDraw00(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_DriverRight_Button_Return2(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);






#if 0
int _WinCommonMenuListOwnerDraw6(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
#endif
#endif