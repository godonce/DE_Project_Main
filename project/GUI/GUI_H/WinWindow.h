
#if 0
#ifndef WINWINDOW_H_INCLUDED
#define WINWINDOW_H_INCLUDED

#include "WIN.h"






extern WIN_INFO_TYPE g_MainWin;
/******************************普通级窗口**************************************/
extern WIN_INFO_TYPE g_ListBoxShowMainInfo;
extern WIN_INFO_TYPE g_ListBox;
extern WIN_INFO_TYPE g_ListView;
extern WIN_INFO_TYPE g_WinShowHelpInfo;
extern WIN_INFO_TYPE g_WinLocalOp;
extern WIN_INFO_TYPE g_WinMainMenu;
extern WIN_INFO_TYPE g_WinCommonMenu;
extern WIN_INFO_TYPE g_WinCurUserMenu;
extern WIN_INFO_TYPE g_WinFirstSetEndMenu;
extern WIN_INFO_TYPE g_WinSelEndPosMenu;
extern WIN_INFO_TYPE g_WinEndPosOp;
extern WIN_INFO_TYPE g_WinEndPosOpT2;
extern WIN_INFO_TYPE g_WinPasswordInput;
extern WIN_INFO_TYPE g_WinCommonUserManageMenu;
extern WIN_INFO_TYPE g_WinPasswordChange;
extern WIN_INFO_TYPE g_WinEndPosSetOkMenu;
extern WIN_INFO_TYPE g_WinEndPosParaMenu;

void StrShowClear(void);

void ListBoxInterface(void *val);
void ListViewInterface(void *val);

void _MainWinKeyDown(void);
void _MainWinKeyUp(void);
void _MainWinKeyEnter(void);
void _MainWinShowRefresh(void);
void _MainWinInterface(void *val);

void _ListBoxShowMainInfoKeyDown(void);
void _ListBoxShowMainInfoKeyUp(void);
void _ListBoxShowMainInfoKeyEnter(void);
void  ListBoxShowMainInfoInterface(void *val);

void _WinMainMenuKeyUp(void);
void _WinMainMenuKeyDown(void );
void _WinMainMenuInterface(void *val);

void _WinCommonMenuKeyDown(void );
void _WinCommonMenuKeyUp(void );
void _WinCommonMenuKeyEnter(void);
void _WinCommonMenuInterface(void *val);

void _WinCurUserKeyUp(void);
void _WinCurUserKeyDown(void);
void _WinCurUserKeyEnter(void);
void _WinCurUserInterface(void *val);

void _voidFun(void);

#endif // WINWINDOW_H_INCLUDED

#endif
#if 1

#ifndef WINWINDOW_H_INCLUDED
#define WINWINDOW_H_INCLUDED

#include "WIN.h"
//#include "Encoder.h"





extern WIN_INFO_TYPE g_MainWin;
/******************************普通级窗口**************************************/
extern WIN_INFO_TYPE g_ListBoxShowMainInfo;
extern WIN_INFO_TYPE g_ListBox;
extern WIN_INFO_TYPE g_ListView;
extern WIN_INFO_TYPE g_WinShowHelpInfo;
extern WIN_INFO_TYPE g_WinLocalOp;
extern WIN_INFO_TYPE g_WinMainMenu;
extern WIN_INFO_TYPE g_WinCommonMenu;
extern WIN_INFO_TYPE g_WinCurUserMenu;
extern WIN_INFO_TYPE g_WinFirstSetEndMenu;
extern WIN_INFO_TYPE g_WinSelEndPosMenu;
extern WIN_INFO_TYPE g_WinEndPosOp;
extern WIN_INFO_TYPE g_WinEndPosOpT2;
extern WIN_INFO_TYPE g_WinPasswordInput;
extern WIN_INFO_TYPE g_WinCommonUserManageMenu;
extern WIN_INFO_TYPE g_WinPasswordChange;
extern WIN_INFO_TYPE g_WinEndPosSetOkMenu;
extern WIN_INFO_TYPE g_WinEndPosParaMenu;

void _WinPasswordChangeInterface(void *val);
void _WinEndPosParaMenuInterface(void *val);

void StrShowClear(void);

void ListBoxInterface(void *val);
void ListViewInterface(void *val);

void _MainWinKeyDown(void);
void _MainWinKeyUp(void);
void _MainWinKeyEnter(void);
void _MainWinShowRefresh(void);
void _MainWinInterface(void *val);

void _ListBoxShowMainInfoKeyDown(void);
void _ListBoxShowMainInfoKeyUp(void);
void _ListBoxShowMainInfoKeyEnter(void);
void  ListBoxShowMainInfoInterface(void *val);

void _WinMainMenuKeyUp(void);
void _WinMainMenuKeyDown(void );
void _WinMainMenuInterface(void *val);

void _WinCommonMenuKeyDown(void );
void _WinCommonMenuKeyUp(void );
void _WinCommonMenuKeyEnter(void);
void _WinCommonMenuInterface(void *val);

void _WinPasswordInputInterface(void *val);

void _WinCurUserKeyUp(void);
void _WinCurUserKeyDown(void);
void _WinCurUserKeyEnter(void);
void _WinCurUserInterface(void *val);

void _voidFun(void);


void _WinPercentageKeyDown(void);
void _WinPercentageKeyUp(void);
void _WinPercentageKeyEnter(void);
void _WinPercentageInterface(void *val);


void _WinComThreeNumKeyDown(void);
void _WinComThreeNumKeyUp(void);
void _WinComThreeNumKeyEnter(void);
void _WinComThreeNumInterface(void *val);

void _WinComFiveNumKeyDown(void);
void _WinComFiveNumKeyUp(void);
void _WinComFiveNumKeyEnter(void);
void _WinComFiveNumInterface(void *val);

void _WinComFourNumKeyDown(void);
void _WinComFourNumKeyUp(void);
void _WinComFourNumKeyEnter(void);
void _WinComFourNumInterface(void *val);

void _WinPasswordInputInterface(void *val);

void _WinCommonUserManageKeyDown(void );
void _WinCommonUserManageKeyUp(void );
void _WinCommonUserManageKeyEnter(void);
void _WinCommonUserManageInterface(void *val);
void _WinCommonUserManageFresh(void *p);


void _WinMomentCloseRefesh (void);
void _WinMomentOpenRefresh (void);
void _WinEndPosCloseRefresh(void);
void _WinEndPosOpenRefresh (void);
void _WinOverMomentTimesRefresh(void);
void _WinSpeedCloseRefresh(void);
void _WinSpeedOpenRefresh  (void);
void _WinEmgSpeedCloseRefresh(void);
void __WinEmgSpeedOpenRefresh(void);
void _WinEmergencyPosKeyRefresh(void );

#endif // WINWINDOW_H_INCLUDED


#endif
