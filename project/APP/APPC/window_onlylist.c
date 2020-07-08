#include "WinWindow_onlylist.h"

#if 1 

/******************************????????**************************************/
typedef struct {
    GUI_HWIN hFrame;
    GUI_HWIN hBtnRtn;
    GUI_HWIN hBtnHome;
    GUI_HWIN hText;
    GUI_HWIN hList;
		WM_HTIMER hTimer;
	
}COMMON_MENU_TYPE;
static COMMON_MENU_TYPE m_CommonMenu = {0};                         //????????

/*******************************************************************************
* Function Name :_WinCommonMenuKeyDown
* Description   :????????????
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
    if(BUTTON_IsPressed(m_CommonMenu.hBtnRtn))//??????
    {
        BUTTON_SetPressed(m_CommonMenu.hBtnRtn,0);
        BUTTON_SetPressed(m_CommonMenu.hBtnHome,1);
    }
    else if(BUTTON_IsPressed(m_CommonMenu.hBtnHome))//Home???
    {
        BUTTON_SetPressed(m_CommonMenu.hBtnHome,0);
        if(LISTBOX_GetItemDisabled(m_CommonMenu.hList,curIndex))
        {
            LISTBOX_SetItemDisabled(m_CommonMenu.hList,curIndex,0);
            LISTBOX_SetSel(m_CommonMenu.hList,curIndex);
            LISTBOX_SetItemDisabled(m_CommonMenu.hList,curIndex,1);
        }
        LISTBOX_SetBkColor(m_CommonMenu.hList,LISTBOX_CI_SEL      , GUI_ORANGE);
        while(curIndexDisable)  //?????????B????
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
        if(curIndex == (LISTBOX_GetNumItems(m_CommonMenu.hList)-1) ) //?List??????
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
                if(curIndex == (LISTBOX_GetNumItems(m_CommonMenu.hList)-1) ) //?List??????
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
* Description   :????????????
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
    if(BUTTON_IsPressed(m_CommonMenu.hBtnRtn))//??????
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
    else if(BUTTON_IsPressed(m_CommonMenu.hBtnHome))//??????
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
* Description   :????????????
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
    if(BUTTON_IsPressed(m_CommonMenu.hBtnRtn))//??????
    {
        WIN_Exit(0);
    }
    else if(BUTTON_IsPressed(m_CommonMenu.hBtnHome))//??????
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
* Description   :?????nput         :WM_MESSAGE * pMsg
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
int kkk;
void _WinCommonMenuRefresh()
{
		char str[MAX_INFO_CHAR];

	if(dataStructInterface.Frame_SN==10)
	{
		switch(flag_figures.user)
		{
			case 1: {sprintf(str,"                    ??? ");
							strcpy(menuUserManagCn[1],str);
							strcpy(menuUserManagEn[1],str);
							LISTBOX_SetString(m_CommonMenu.hList,str,1);
							}break;
			case 2: {sprintf(str,"                         ??");
							strcpy(menuUserManagCn[1],str);
							strcpy(menuUserManagEn[1],str);
							LISTBOX_SetString(m_CommonMenu.hList,str,1);
							}break;
			case 3: {sprintf(str,"                         ??");
							strcpy(menuUserManagCn[1],str);
							strcpy(menuUserManagEn[1],str);
							LISTBOX_SetString(m_CommonMenu.hList,str,1);
							}break;
			case 4: {sprintf(str,"                         ??");
							strcpy(menuUserManagCn[1],str);
							strcpy(menuUserManagEn[1],str);
							LISTBOX_SetString(m_CommonMenu.hList,str,1);
							}break;
			case 5: {sprintf(str,"                      ????");
							strcpy(menuUserManagCn[1],str);
							strcpy(menuUserManagEn[1],str);
							LISTBOX_SetString(m_CommonMenu.hList,str,1);
							}break;
			 default: break;
		}
	}else
	if(dataStructInterface.Frame_SN==11)
	{
		if(dataStructInterface.emgInput==0)
		{
			sprintf(str,"            ????(NC) ");
			strcpy(menuSaftyCn[1],str);
			strcpy(menuSaftyEn[1],str);
			LISTBOX_SetString(m_CommonMenu.hList,str,1);
		}else
		if(dataStructInterface.emgInput==1)
		{
			sprintf(str,"            ????(NO) ");
			strcpy(menuSaftyCn[1],str);
			strcpy(menuSaftyEn[1],str);
			LISTBOX_SetString(m_CommonMenu.hList,str,1);
		}
		sprintf(str," ?              %d rpm ",dataStructInterface.emg_speed_close);             
		strcpy(menuDiagnoseCn[3],str);
		strcpy(menuDiagnoseEn[3],str);
		LISTBOX_SetString(m_CommonMenu.hList,str,3);
		if(dataStructInterface.emgCtlSrcFault==0)
		{
			sprintf(str,"         ???“??”?? ");
			strcpy(menuSaftyCn[8],str);
			strcpy(menuSaftyEn[8],str);
			LISTBOX_SetString(m_CommonMenu.hList,str,8);
		}else
		if(dataStructInterface.emgCtlSrcFault==1)
		{
			sprintf(str,"                ???? ");
			strcpy(menuSaftyCn[8],str);
			strcpy(menuSaftyEn[8],str);
			LISTBOX_SetString(m_CommonMenu.hList,str,8);
		}
		
	}else
	if(dataStructInterface.Frame_SN==12)
	{
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

	}else
	if (dataStructInterface.Frame_SN==20)
	{
	sprintf(str," ????        %d ",0);
	strcpy(menuDiagnoseCn[1],str);
	strcpy(menuDiagnoseEn[1],str);
	LISTBOX_SetString(m_CommonMenu.hList,str,1);
	
	sprintf(str," ????(?/??)     %d  ",1);
	strcpy(menuDiagnoseCn[2],str);
	strcpy(menuDiagnoseEn[2],str);
	LISTBOX_SetString(m_CommonMenu.hList,str,2);
	
	sprintf(str," ??????          %d  ",2);
	strcpy(menuDiagnoseCn[3],str);
	strcpy(menuDiagnoseEn[3],str);
	LISTBOX_SetString(m_CommonMenu.hList,str,3);
	
	sprintf(str," ??????          %d  ",3);
	strcpy(menuDiagnoseCn[4],str);
	strcpy(menuDiagnoseEn[4],str);
	LISTBOX_SetString(m_CommonMenu.hList,str,4);
	
	sprintf(str," ???????        %d  ",4);
	strcpy(menuDiagnoseCn[5],str);
	strcpy(menuDiagnoseEn[5],str);
	LISTBOX_SetString(m_CommonMenu.hList,str,5);
	
	sprintf(str," ?????????    %d  ",5);
	strcpy(menuDiagnoseCn[6],str);
	strcpy(menuDiagnoseEn[6],str);
	LISTBOX_SetString(m_CommonMenu.hList,str,6);
	
	sprintf(str," ????/??         %d  ",6);
	strcpy(menuDiagnoseCn[7],str);
	strcpy(menuDiagnoseEn[7],str);
	LISTBOX_SetString(m_CommonMenu.hList,str,7);
	
		sprintf(str," ????          %d  ",7);
	strcpy(menuDiagnoseCn[9],str);
	strcpy(menuDiagnoseEn[9],str);
	LISTBOX_SetString(m_CommonMenu.hList,str,9);
	
	sprintf(str," ??????       %d  ",8);
	strcpy(menuDiagnoseCn[10],str);
	strcpy(menuDiagnoseEn[10],str);
	LISTBOX_SetString(m_CommonMenu.hList,str,10);
	
	sprintf(str," ???????     %d  ",9);
	strcpy(menuDiagnoseCn[11],str);
	strcpy(menuDiagnoseEn[11],str);
	LISTBOX_SetString(m_CommonMenu.hList,str,11);

	sprintf(str,"      ??  ");
 strcpy(menuDiagnoseCn[13],str);
 strcpy(menuDiagnoseEn[13],str);
 LISTBOX_SetString(m_CommonMenu.hList,str,13);
}else
	if(dataStructInterface.Frame_SN==22)
	{
		  if(0 == dataStructInterface.closeDir)
    {
				sprintf(str,"                  ??? ");
        strcpy(menuVavleParaCn[1],str);
        strcpy(menuVavleParaEn[1],str);
				LISTBOX_SetString(m_CommonMenu.hList,str,1);
    }
    else if(1 == dataStructInterface.closeDir)
    {
				sprintf(str,"                  ??? ");
        strcpy(menuVavleParaCn[1],str);
        strcpy(menuVavleParaEn[1],str);
				LISTBOX_SetString(m_CommonMenu.hList,str,1);
    }
		#if 1
			/**********************************??******************************************/
			sprintf(str," ?       %dNm ",(int)dataStructInterface.moment_close);//dataStructInterface.moment_close);
			strcpy(menuVavleParaCn[9],str);
			strcpy(menuVavleParaEn[9],str);
			LISTBOX_SetString(m_CommonMenu.hList,str,9);
			sprintf(str," ?     %dNm ",(int)dataStructInterface.moment_open);
			strcpy(menuVavleParaCn[10],str);
			strcpy(menuVavleParaEn[10],str);
			LISTBOX_SetString(m_CommonMenu.hList,str,10);
		#endif
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
				WM_RestartTimer(pMsg->Data.v, 1000);
//     kkk++;
//			if(kkk>100)
//			{kkk=0;}
			_WinCommonMenuRefresh();		
		 GUI_Exec();
        break;
			#endif
			#if 0 
			case WM_TIMER:	
        WM_RestartTimer(pMsg->Data.v, 100);
				//_MainCommonMenuRefresh();
			sprintf(str,"asdafdaf    %3d",123);
			LISTBOX_SetString(m_CommonMenu.hList,str,3);
				GUI_Exec();
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


/*******************************************************************************
* Function Name :_WinCommonMenuCreate
* Description   :????????????
* Input         :void *
* Output        :void
* Other         :
* Date          :2018/04/20
*******************************************************************************/
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
    const char            *pContentCn = pMenu->data->menutitleCn;
    const char            *pContentEn = pMenu->data->menutitleEn;
    if (NULL == pTitle) pTitle = "";
    memset(strShow,0,sizeof(strShow));
    enc_unicode_to_utf8_str(pTitle,strShow,STRSHOWBUF_SIZE);
		dataStructInterface.Frame_SN=pMenu->data->SN;
    //????
  #if 0
		//GUI_DrawBitmap(&bmbackground,50,50);
		GUI_DrawBitmap(&bmbackUnsel,50,50);
	#endif 
    m_CommonMenu.hFrame = FRAMEWIN_CreateAsChild(0, 0, LCD_HSIZE+3, LCD_VSIZE+3 ,WM_HBKWIN, pTitle, NULL, WM_CF_SHOW);
		FRAMEWIN_SetClientColor(m_CommonMenu.hFrame,GUI_WHITE);  
    FRAMEWIN_SetFont(m_CommonMenu.hFrame, &GUI_Fontsong16all);  
    GUI_UC_SetEncodeUTF8();
    FRAMEWIN_SetTitleVis(m_CommonMenu.hFrame, 0);             

    hWin = WM_GetFirstChild(m_CommonMenu.hFrame);             
    //??????

    m_CommonMenu.hBtnRtn   = BUTTON_CreateAsChild(DEBUG_X_OFFSET+150-23, DEBUG_Y_OFFSET, 23, 23,hWin,NULL, WM_CF_SHOW);
    m_CommonMenu.hBtnHome  = BUTTON_CreateAsChild(DEBUG_X_OFFSET+150, DEBUG_Y_OFFSET, 23, 23,hWin,NULL, WM_CF_SHOW);
    m_CommonMenu.hText     = TEXT_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23, PER_CM_OFFSET*4.5, 23, hWin, WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT , NULL, " ");
    if(pMenu->data->menunum < MAX_ITEAM_PER_PAGE)
        m_CommonMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23+23+10, PER_CM_OFFSET*4.5, PER_CM_OFFSET*3.5, hWin, WM_CF_SHOW, NULL, NULL,NULL);
    else
        m_CommonMenu.hList      = LISTBOX_CreateEx( DEBUG_X_OFFSET+PER_CM_OFFSET, DEBUG_Y_OFFSET+23+23+10, PER_CM_OFFSET*4.5+11, PER_CM_OFFSET*3.5, hWin, WM_CF_SHOW, NULL, NULL,NULL);

    hWin = m_CommonMenu.hBtnRtn;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED, &bmbackUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,  &bmbackSel,  0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmbackUnsel,0,0);
    BUTTON_SetPressed(hWin,1);
    
    hWin = m_CommonMenu.hBtnHome;
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_DISABLED, &bmhomeUnsel,0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_PRESSED,  &bmhomeSel,  0,0);
    BUTTON_SetBitmapEx(hWin,BUTTON_BI_UNPRESSED,&bmhomeUnsel,0,0);
    BUTTON_SetPressed(hWin,0);

    hWin = m_CommonMenu.hText;
    TEXT_SetFont(hWin,&GUI_Fontsong16all);
    GUI_UC_SetEncodeUTF8();
    TEXT_SetBkColor(hWin,GUI_BLUE);//GUI_BLUE
    TEXT_SetTextAlign(hWin,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    TEXT_SetTextColor(hWin,GUI_WHITE);
		TEXT_SetText(hWin, strShow);
 
    /**************************LIST???*************************/
    hWin = m_CommonMenu.hList;
    WIDGET_SetEffect(hWin,&WIDGET_Effect_None);

    LISTBOX_SetFont(hWin, &GUI_Fontsong16all);
    LISTBOX_SetItemSpacing(hWin, 7);
    LISTBOX_SetTextAlign(hWin,GUI_TA_VCENTER | GUI_TA_LEFT);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_DISABLED , GUI_WHITE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SEL      , GUI_WHITE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_SELFOCUS , GUI_ORANGE);
    LISTBOX_SetBkColor(hWin,LISTBOX_CI_UNSEL    , GUI_WHITE);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_DISABLED , GUI_BLUE); //GUI_BLUE
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SEL      , GUI_BLACK);//
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_SELFOCUS , GUI_BLACK);
    LISTBOX_SetTextColor(hWin,LISTBOX_CI_UNSEL    , GUI_BLACK);
    LISTBOX_SetAutoScrollV(hWin,1);
    for(i=0;i<pMenu->data->menunum;i++)
    {
				memset(strShow,0,sizeof(strShow));
        if(LANGUAGE_CN == g_LanguageIndex) 
					enc_unicode_to_utf8_str(pContentCn,strShow,STRSHOWBUF_SIZE);
        else if(LANGUAGE_EN == g_LanguageIndex) 
					enc_unicode_to_utf8_str(pContentEn,strShow,STRSHOWBUF_SIZE);
        pContentCn += MAX_INFO_CHAR;
        pContentEn += MAX_INFO_CHAR;
        LISTBOX_AddString(hWin, (char *)strShow);
        if(MENU_SETTING_TITLE == pMenu->data->menuattri[i]) 
					LISTBOX_SetItemDisabled(hWin,i,1);
    }
		m_CommonMenu.hTimer = WM_CreateTimer(WM_HBKWIN,0,1000,0);

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
		WM_DeleteWindow(m_CommonMenu.hTimer);
    WM_SetCallback(WM_HBKWIN, NULL);
    memset(&m_CommonMenu, 0, sizeof(m_CommonMenu));
}

/*******************************************************************************
* Function Name :_WinCommonMenuInterface
* Description   :?????? ???
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

    if(sel == 100 )  //?????????
    {
        return ;
    }
    else             //???????
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


WIN_INFO_TYPE g_WinCommonMenu = {                         //?????
    &m_CommonMenu.hFrame,
    _WinCommonMenuCreate,
    _WinCommonMenuDestroy
};



#endif
/******************************????????**************************************/
