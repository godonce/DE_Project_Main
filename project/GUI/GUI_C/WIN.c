
#include <string.h>
#include "GUI.h"

#include "WIN.h"
#include "WIN_Context.h"
#include "WinWindow.h"
#include "Dialog.h"
#include "LISTVIEW.h"
#include "HEADER.h"

#include "DataInterface.h"
#include  "datafigures.h"
extern void _WinLocalOpInterface(void *val);
extern void _WinCommonSelectInterface(void *val);
extern WIN_INFO_TYPE g_WinSpeedCloseMenu;
extern WIN_INFO_TYPE g_WinSpeedOpenMenu;
extern WIN_INFO_TYPE g_WinEndPosCloseMenu;
extern WIN_INFO_TYPE g_WinEndPosOpenMenu;
extern WIN_INFO_TYPE g_WinMomentCloseMenu ;
extern WIN_INFO_TYPE g_WinMomentOpenMenu;
extern WIN_INFO_TYPE g_WinOverMomentTimesMenu;
extern WIN_INFO_TYPE g_WinEmgSpeedCloseMenu;
extern WIN_INFO_TYPE g_WinEmgSpeedOpenMenu;
extern WIN_INFO_TYPE g_WinPercentageMenu;
extern void _WinPercentageInterface(void *val);
extern WIN_INFO_TYPE g_WinComThreeNumMenu;
extern void _WinComThreeNumInterface(void *val);
extern WIN_INFO_TYPE g_WinComFiveNumMenu;
extern void _WinComFiveNumInterface(void *val);
extern WIN_INFO_TYPE g_WinComFourNumMenu;
extern WIN_INFO_TYPE g_WinEmergencyPosMenu;
extern void _WinComFourNumInterface(void *val);



extern WIN_INFO_TYPE g_WinCommonSelectMenu ;

char        g_LCDBuff[LCD_BUFFTER_SIZE]     = {0};
volatile char   g_LanguageIndex             = 0;


static WIN_INTERFACE_t  m_KeyValue          = {0};

unsigned short test_select = 7;

unsigned short test_select2 = 2;
void WIN_KeyBoard(int key)
{
    m_KeyValue.D.val    = key;
    m_KeyValue.active   = 1;
}


void _DataRefresh(void)
{
    if (m_KeyValue.active)
    {
        m_KeyValue.active   = 0;

        if (m_KeyValue.D.val == GUI_KEY_SPACE)
        {
        }
        else
        {
           WM_SetFocus(WM_HBKWIN);
            GUI_SendKeyMsg(m_KeyValue.D.val, 1);
        }
    }
}

MENU_INFO_TYPE m_MainWinInfo = {     
    {"", ""},
    &g_MainWin,
    _MainWinInterface,
    _voidFun
};

MENU_INFO_TYPE m_MenuStateShowInfo = {   
    {"状态", "DeviceState"},
    &g_ListBoxShowMainInfo,
    ListBoxShowMainInfoInterface
};

MENU_INFO_TYPE m_MenuHelpShowInfo1 = {   
    {"帮助", "Help"},
    &g_WinShowHelpInfo,
    _voidFun,
    _voidFun,
		0,
};

MENU_INFO_TYPE m_MenuHelpShowInfo2 = {   
    {"帮助", "Help"},
    &g_WinShowHelpInfo,
    _voidFun,
    _voidFun,
    1,
};

static MENU_INFO_TYPE m_MenuHelpShowInfo3 = {    
    {"帮助", "Help"},
    &g_WinShowHelpInfo,
    _voidFun,
    _voidFun,
    2,
};

static MENU_INFO_TYPE m_MenuHelpShowInfo4 = {   
    {"帮助", "Help"},
    &g_WinShowHelpInfo,
    _voidFun,
    _voidFun,
    3,
};

static MENU_INFO_TYPE m_MenuHelpShowInfo5 = {    
    {"帮助", "Help"},
    &g_WinShowHelpInfo,
    _voidFun,
    _voidFun,
    4,
};

static MENU_INFO_TYPE m_MenuHelpShowInfo6 = {       
    {"帮助", "Help"},
    &g_WinShowHelpInfo,
    _voidFun,
    _voidFun,
    5,
};


static MENU_INFO_TYPE m_MenuLocalOp = {   
    {"就地操作 ", "Local Operation"},
    &g_WinLocalOp,
    _WinLocalOpInterface
};

static MENU_INFO_TYPE m_MenuLanguage = {
    {"语言", "Language"}
};


static MENU_INFO_TYPE m_MainMenuInfo = {  
    {"主菜单", "Main menu"},
    &g_WinMainMenu,
    _WinMainMenuInterface,
		0,
		0
};

static MENU_INFO_TYPE m_UserManagInfo = {   
    {"用户管理", "user management"},
    &g_WinCommonMenu,    
    _WinCommonMenuInterface,
    _voidFun,
    MENU_USER_MANAG_NUM,
    menuUserManagCn[0],
    menuUserManagEn[0],
    menuUserManagSettings,
		0,
		1
};

static MENU_INFO_TYPE m_CurUserInfo2 = {            
    {"当前用户", "Current user"},
    &g_WinCommonUserManageMenu,
    _WinCommonUserManageInterface,
    _voidFun,
    MENU_CUR_USER_NUM,
    menuCurUserCn[0],
    menuCurUserEn[0],
    menuCurUserSettings,
    &g_authority
};
static MENU_INFO_TYPE m_WinPasswordInputHandle = {     
    {"密码确认", "Password Input"},
    &g_WinPasswordInput,
    _voidFun,
    _WinPasswordInputInterface,
    0,
    convert_user_to_handler_cn,
    convert_user_to_handler_en,
    NULL,
    &password.g_password_handle,
		1
};

static MENU_INFO_TYPE m_WinPasswordInputViewer = {         
    {"密码确认", "Password Input"},
    &g_WinPasswordInput,
    _voidFun,
    _WinPasswordInputInterface,
    0,
    convert_user_to_viewer_cn,
    convert_user_to_viewer_en,
    NULL,
    &password.g_password_viewer,
		2
};

static MENU_INFO_TYPE m_WinPasswordInputExpert = {          
    {"密码确认", "Password Input"},
    &g_WinPasswordInput,
    _voidFun,
    _WinPasswordInputInterface,
    0,
    convert_user_to_expert_cn,
    convert_user_to_expert_en,
    NULL,
    &password.g_password_expert,
		3
};

static MENU_INFO_TYPE m_WinPasswordInputService = {      
    {"密码确认", "Password Input"},
    &g_WinPasswordInput,
    _voidFun,
    _WinPasswordInputInterface,
    0,
    convert_user_to_service_cn,
    convert_user_to_service_en,
    NULL,
    &password.g_password_service,
		4
};

static MENU_INFO_TYPE m_WinPasswordInputFactroy = {      
    {"密码确认", "Password Input"},
    &g_WinPasswordInput,
    _voidFun,
    _WinPasswordInputInterface,
    0,
    convert_user_to_factroy_cn,
    convert_user_to_factroy_en,
    NULL,
    &password.g_password_factroy,
		5
};

static MENU_INFO_TYPE m_MenuObserve = {        
    {"观察", "Observe"},
    &g_WinCommonMenu,    
    _WinCommonMenuInterface,
    _voidFun,
    MENU_OB_SET_NUM,
    menuObCn[0],
    menuObEn[0],
    menuObSet
};

static MENU_INFO_TYPE m_MenuObNamePlate = {        
    {"电子单元铭牌", "NamePlate"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    MENU_OB_NAMEPLATE_NUM,
    menuObNamePlateCn[0],
    menuObNamePlateEn[0],
    menuObNamePlateSet
};

static MENU_INFO_TYPE m_MenuNull = {0};
static MENU_INFO_TYPE m_MenuObNamePlateDevice = {         
    {"设备", "Device"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    MENU_OB_NAMEPLATE_DEVICE_NUM,
    menuObPlateDeviceCn[0],
    menuObPlateDeviceEn[0],
    menuObPlateDeviceSet
};


static MENU_INFO_TYPE m_MenuObInOutPut = {       
    {"输入和输出", "Input Output"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    MENU_OB_INOUTPUT_NUM,
    menuObInOutPutCn[0],
    menuObInOutPutEn[0],
    menuObInOutPutSet,
		0,
		5
};

static MENU_INFO_TYPE m_MenuObKrInPut = {          
    {"开关量输入", "KR Input"},
    &g_WinCommonMenu,    
    _WinCommonMenuInterface,
    _voidFun,
    MENU_OB_KRINPUT_NUM,
    menuObKrInputCn[0],
    menuObKrInputEn[0],
    menuObKrInputSet
};

static MENU_INFO_TYPE m_MenuObKrOutPut = {      
    {"开关量输出", "KR Output"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    MENU_OB_KROUTPUT_NUM,
    menuObKrOutputCn[0],
    menuObKrOutputEn[0],
    menuObKrOutputSet
};

static MENU_INFO_TYPE m_MenuObAnalog = {           
    {"模拟量输入，输出", "Analog Input&Output"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    MENU_OB_ANALOG_NUM,
    menuObAnalogCn[0],
    menuObAnalogEn[0],
    menuObAnalogSet,
		0,
		8
};


static MENU_INFO_TYPE m_MenuObStatus = {       
    {"状态", "Status"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    MENU_OB_STATUS_NUM,
    menuObStatusCn[0],
    menuObStatusEn[0],
    menuObStatusSet,
		0,
		9
};

static MENU_INFO_TYPE m_MenuDiagnose = {              
    {"诊断", "Diagnose"},
    &g_WinCommonMenu,  
    _WinCommonMenuInterface,
    _voidFun,
    MENU_DIAGNOSE_NUM,
    menuDiagnoseCn[0],
    menuDiagnoseEn[0],
    menuDiagnoseSet,
		0,
		10
};

static MENU_INFO_TYPE m_MenuPara = {            
    {"参数", "Para"},
    &g_WinCommonMenu,    
    _WinCommonMenuInterface,
    _voidFun,
    MENU_PARA_NUM,
    menuParaCn[0],
    menuParaEn[0],
    menuParaSet,
		0,
		11
};

static MENU_INFO_TYPE m_MenuGear = {           
    {"外配齿轮箱", "Gear"},
    &g_WinCommonMenu,    
    _WinCommonMenuInterface,
    _voidFun,
    MENU_GEAR_NUM,
    menuGearCn[0],
    menuGearEn[0],
    menuGearSet,
		0,
		12
};


static MENU_INFO_TYPE m_MenuGearType = {      
    {"Gear Type", "Gear Type"},
    &g_WinCommonSelectMenu,   
    _WinCommonSelectInterface,
    _voidFun,
    MENU_GEAR_TYPE_NUM,
    menuGearTypeCn[0],
    menuGearTypeEn[0],
    menuGearTypeSet,
    &dataStructInterface.gearType,
		1
};


static MENU_INFO_TYPE m_MenuVavlePara = {           
    {"与阀门有关参数", "Vavle Para"},
    &g_WinCommonMenu,    
    _WinCommonMenuInterface,
    _voidFun,
    MENU_VAVLE_PARA_NUM,
    menuVavleParaCn[0],
    menuVavleParaEn[0],
    menuVavleParaSet,
		0,
		13
};

static MENU_INFO_TYPE m_MenuCloseDir = {             
    {"关方向", "CloseDir"},       
    &g_WinCommonSelectMenu,      
    _WinCommonSelectInterface,
    _voidFun,
    MENU_CLOSE_DIR_NUM,
    menuSelCloseDirCn[0],
    menuSelCloseDirEn[0],
    menuSelCloseDirSet,
    (unsigned short *)&dataStructInterface.closeDir,
		2
};


static MENU_INFO_TYPE m_WinSpeedClose = {       
    {"转速", "Speed"},
    &g_WinSpeedCloseMenu,
};

static MENU_INFO_TYPE m_WinSpeedOpen = {          
    {"转速", "Speed"},
    &g_WinSpeedOpenMenu,
};

static MENU_INFO_TYPE m_WinOffModeClose = {            
    {"关关断模式", "Close Off Mode"},
    &g_WinCommonSelectMenu,   
    _WinCommonSelectInterface,
    _voidFun,
    MENU_CLOSE_DIR_NUM,
    menuSelOffModeCn[0],
    menuSelOffModeEn[0],
    menuSelOffModeSet,
    &dataStructInterface.closeOffMode,
		3
};

static MENU_INFO_TYPE m_WinOffModeOpen = {            
    {"开关断模式", "Open Off Mode"},
    &g_WinCommonSelectMenu,  
    _WinCommonSelectInterface,
    _voidFun,
    MENU_CLOSE_DIR_NUM,
    menuSelOffModeCn[0],
    menuSelOffModeEn[0],
    menuSelOffModeSet,
    &dataStructInterface.openOffMode,
		4
};


static MENU_INFO_TYPE m_WinEndPosClose = {            
    {"末端位置范围", "EndPos Range"},
    &g_WinEndPosCloseMenu,
};

static MENU_INFO_TYPE m_WinEndPosOpen = {           
    {"末端位置范围", "EndPos Range"},
    &g_WinEndPosOpenMenu,
};

static MENU_INFO_TYPE m_WinMomentPosClose = {           
    {"关断力矩", "Turn off Moment"},
    &g_WinMomentCloseMenu,
};

static MENU_INFO_TYPE m_WinMomentPosOpen = {             
    {"关断力矩", "Turn off Moment"},
    &g_WinMomentOpenMenu,
};

static MENU_INFO_TYPE m_WinOverMomentTimes = {                      
    {"过力矩后的重试次数", "Over Moment Retry Times"},
    &g_WinOverMomentTimesMenu,
};


static MENU_INFO_TYPE m_MenuCtrlSysPara = {           
    {"与控制系统有关参数", "Ctrl Sys Para"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    MENU_CTRL_SYS_PARA_NUM,
    menuCtrlSysParaCn[0],
    menuCtrlSysParaEn[0],
    menuCtrlSysParaSet,
		0,
		14
};

static MENU_INFO_TYPE m_MenuCtrlMode = {              
    {"控制模式", "Ctrl Mode"},
    &g_WinCommonSelectMenu,    
    _WinCommonSelectInterface,
    _voidFun,
    MENU_CTRL_MODE_NUM,
    menuCtrlModeCn[0],
    menuCtrlModeEn[0],
    menuCtrlModeSet,
    (unsigned short *)&dataStructInterface.ctrlMode,
    5
};


static MENU_INFO_TYPE m_MenuRmtChose = {            
    {"远程再选择", "Remote Chose"},
    &g_WinCommonSelectMenu,    
    _WinCommonSelectInterface,
    _voidFun,
    MENU_REMOTE_CHOSE_NUM,
    menuRmtChoseCn[0],
    menuRmtChoseEn[0],
    menuRmtChoseSet,
    &dataStructInterface.rmtChoose,
    6
};


static MENU_INFO_TYPE m_MenuKrInput = {          
    {"开关量输入", "Kr Input"}, 
    &g_WinCommonSelectMenu,         
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KR_INPUT_NUM,
    menuKrInputCn[0],
    menuKrInputEn[0],
    menuKrInputSet,
    &dataStructInterface.krInput,
		7
};


static MENU_INFO_TYPE m_MenuModeInput = {            
    {"Mode Input", "Mode Input"},
    &g_WinCommonSelectMenu,            
    _WinCommonSelectInterface,
    _voidFun,
    MENU_MODE_INPUT_NUM,
    menuModeInputCn[0],
    menuModeInputEn[0],
    menuModeInputSet,
    &dataStructInterface.modeInput,
		8
};


static MENU_INFO_TYPE m_MenuAnologInput = {           
    {"模拟量输入AI1", "AnologInput AI1"},
    &g_WinCommonSelectMenu,     
    _WinCommonSelectInterface,
    _voidFun,
    MENU_ANOLOG_INPUT_NUM,
    menuAnologInputCn[0],
    menuAnologInputEn[0],
    menuAnologInputSet,
    &dataStructInterface.anologInput,
		9
};


static MENU_INFO_TYPE m_MenuAnologInputRange = {          
    {"模拟量输入AI1", "AnologInput AI1"},
    &g_WinCommonSelectMenu,    
    _WinCommonSelectInterface,
    _voidFun,
    MENU_ANOLOG_INPUT_AI1_NUM,
    menuAnologInputAI1Cn[0],
    menuAnologInputAI1En[0],
    menuAnologInputAI1Set,
    &dataStructInterface.anologInputRange,
		10
};

static MENU_INFO_TYPE m_MenuKrOutput = {           
    {"开关量输出", "Kr Output"},
    &g_WinCommonMenu,    
    _WinCommonMenuInterface,
    _voidFun,
    MENU_KR_OUTPUT_NUM,
    menuKrOutputCn[0],
    menuKrOutputEn[0],
    menuKrOutputSet
};


static MENU_INFO_TYPE m_MenuKrOutput1_1 = {             
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,           
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL1_NUM,
    menuKrOutputSel1Cn[0],
    menuKrOutputSel1En[0],
    menuKrOutputSel1Set,
    (unsigned short *)&dataStructInterface.krOutputSel1[0+1],
		11
};

static MENU_INFO_TYPE m_MenuKrOutput1_2 = {                 
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,             
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL2_NUM,
    menuKrOutputSel2Cn[0],
    menuKrOutputSel2En[0],
    menuKrOutputSel2Set,
    (unsigned short *)&dataStructInterface.krOutputSel2[0+1],
		12
};


static MENU_INFO_TYPE m_MenuKrOutput2_1 = {        
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,      
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL1_NUM,
    menuKrOutputSel1Cn[0],
    menuKrOutputSel1En[0],
    menuKrOutputSel1Set,
    (unsigned short *)&dataStructInterface.krOutputSel1[1+1],
		13
};

static MENU_INFO_TYPE m_MenuKrOutput2_2 = {                
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,       
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL2_NUM,
    menuKrOutputSel2Cn[0],
    menuKrOutputSel2En[0],
    menuKrOutputSel2Set,
   (unsigned short *) &dataStructInterface.krOutputSel2[1+1],
		14
		
};


static MENU_INFO_TYPE m_MenuKrOutput3_1 = {            
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,             
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL1_NUM,
    menuKrOutputSel1Cn[0],
    menuKrOutputSel1En[0],
    menuKrOutputSel1Set,
    (unsigned short *)&dataStructInterface.krOutputSel1[2+1],
		15
};

static MENU_INFO_TYPE m_MenuKrOutput3_2 = {              
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,          
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL2_NUM,
    menuKrOutputSel2Cn[0],
    menuKrOutputSel2En[0],
    menuKrOutputSel2Set,
   (unsigned short *)&dataStructInterface.krOutputSel2[2+1],
		16
};

static MENU_INFO_TYPE m_MenuKrOutput4_1 = {                 
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,       
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL1_NUM,
    menuKrOutputSel1Cn[0],
    menuKrOutputSel1En[0],
    menuKrOutputSel1Set,
    (unsigned short *)&dataStructInterface.krOutputSel1[3+1],
		17
};

static MENU_INFO_TYPE m_MenuKrOutput4_2 = {                 
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,        
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL2_NUM,
    menuKrOutputSel2Cn[0],
    menuKrOutputSel2En[0],
    menuKrOutputSel2Set,
    (unsigned short *)&dataStructInterface.krOutputSel2[3+1],
		18
};

static MENU_INFO_TYPE m_MenuKrOutput5_1 = {                  
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,        
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL1_NUM,
    menuKrOutputSel1Cn[0],
    menuKrOutputSel1En[0],
    menuKrOutputSel1Set,
    (unsigned short *)&dataStructInterface.krOutputSel1[4+1],
		19
};

static MENU_INFO_TYPE m_MenuKrOutput5_2 = {                   
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,         
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL2_NUM,
    menuKrOutputSel2Cn[0],
    menuKrOutputSel2En[0],
    menuKrOutputSel2Set,
    (unsigned short *)&dataStructInterface.krOutputSel2[4+1],
		20
};

static MENU_INFO_TYPE m_MenuKrOutput6_1 = {                   
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,                
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL1_NUM,
    menuKrOutputSel1Cn[0],
    menuKrOutputSel1En[0],
    menuKrOutputSel1Set,
    (unsigned short *)&dataStructInterface.krOutputSel1[5+1],
		21
};

static MENU_INFO_TYPE m_MenuKrOutput6_2 = {                
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,             
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL2_NUM,
    menuKrOutputSel2Cn[0],
    menuKrOutputSel2En[0],
    menuKrOutputSel2Set,
    (unsigned short *)&dataStructInterface.krOutputSel2[5+1],
		22
};

static MENU_INFO_TYPE m_MenuKrOutput7_1 = {                  
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,            
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL1_NUM,
    menuKrOutputSel1Cn[0],
    menuKrOutputSel1En[0],
    menuKrOutputSel1Set,
    (unsigned short *)&dataStructInterface.krOutputSel1[6+1],
		23
};

static MENU_INFO_TYPE m_MenuKrOutput7_2 = {                   
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,          
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL2_NUM,
    menuKrOutputSel2Cn[0],
    menuKrOutputSel2En[0],
    menuKrOutputSel2Set,
    (unsigned short *)&dataStructInterface.krOutputSel2[6+1],
		24
};

static MENU_INFO_TYPE m_MenuKrOutput8_1 = {             
    {"输出1", "Output1"},
    &g_WinCommonSelectMenu,           
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL1_NUM,
    menuKrOutputSel1Cn[0],
    menuKrOutputSel1En[0],
    menuKrOutputSel1Set,
    (unsigned short *)&dataStructInterface.krOutputSel1[7+1],
		25
};

static MENU_INFO_TYPE m_MenuKrOutput8_2 = {                      
    {"输出1", "Output1"}, 
    &g_WinCommonSelectMenu,            
    _WinCommonSelectInterface,
    _voidFun,
    MENU_KROUTPUT_SEL2_NUM,
    menuKrOutputSel2Cn[0],
    menuKrOutputSel2En[0],
    menuKrOutputSel2Set,
    (unsigned short *)&dataStructInterface.krOutputSel2[7+1],
		26
};


static MENU_INFO_TYPE m_MenuAOutput1 = {                 
    {"模拟量输出AO1", "Anology Output AO1"},
    &g_WinCommonSelectMenu,      
    _WinCommonSelectInterface,
    _voidFun,
    MENU_ANOOUTPUT_SEL1_NUM,
    menuAnologOutputSel1Cn[0],
    menuAnologOutputSel1En[0],
    menuAnologOutputSel1Set,
    &dataStructInterface.anologOutputSel1,
		27
};

static MENU_INFO_TYPE m_MenuAOutput2 = {                      
    {"模拟量输出AO1", "Anology Output AO1"},
    &g_WinCommonSelectMenu,         
    _WinCommonSelectInterface,
    _voidFun,
    MENU_ANOOUTPUT_SEL2_NUM,
    menuAnologOutputSel2Cn[0],
    menuAnologOutputSel2En[0],
    menuAnologOutputSel2Set,
    &dataStructInterface.anologOutputSel2,
		28
};

static MENU_INFO_TYPE m_MenuAOutput3 = {                       
    {"模拟量输出AO1", "Anology Output AO1"},
    &g_WinCommonSelectMenu,           
    _WinCommonSelectInterface,
    _voidFun,
    MENU_ANOOUTPUT_SEL3_NUM,
    menuAnologOutputSel3Cn[0],
    menuAnologOutputSel3En[0],
    menuAnologOutputSel3Set,
    &dataStructInterface.anologOutputSel3,
		29
};


static MENU_INFO_TYPE m_MenuSafty = {               
    {"安全", "Safty"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    MENU_SAFTY_PARA_NUM,
    menuSaftyCn[0],
    menuSaftyEn[0],
    menuSaftySet,
		0,
		16
};

static MENU_INFO_TYPE m_MenuEmgInput = {           
    {"输出", "Output"},
    &g_WinCommonSelectMenu,         
    _WinCommonSelectInterface,
    _voidFun,
    MENU_SAFTY_INPUT_NUM,
    menuSaftyEmInputCn[0],
    menuSaftyEmInputEn[0],
    menuSaftyEmInputSet,
    &dataStructInterface.emgInput,
		30
};


static MENU_INFO_TYPE m_WinEmgSpeedClose = {        
    {"转速", "Speed"},
    &g_WinEmgSpeedCloseMenu,
};

static MENU_INFO_TYPE m_WinEmgSpeedOpen = {    
    {"转速", "Speed"},
    &g_WinEmgSpeedOpenMenu,
};

static MENU_INFO_TYPE m_MenuEmgCtrlSrcFault = {               
    {"控制源故障", "Ctrl Src Fault"},
    &g_WinCommonSelectMenu,            
    _WinCommonSelectInterface,
    _voidFun,
    MENU_SAFTY_CTLSRC_FAULT_NUM,
    menuSaftyCtlSrcFaultCn[0],
    menuSaftyCtlSrcFaultEn[0],
    menuSaftyCtlSrcFaultSet,
    &dataStructInterface.emgCtlSrcFault,
		31
};


static MENU_INFO_TYPE m_MenuSoftFun = {           
    {"软件功能", "Soft Fun"},
    &g_WinCommonMenu,    
    _WinCommonMenuInterface,
    _voidFun,
    MENU_SOFTFUN_NUM,
    menuSoftFunCn[0],
    menuSoftFunEn[0],
    menuSoftFunSet
};

static MENU_INFO_TYPE m_MenuSoftFunActive = {             
    {"激活软件功能", "Active Soft Fun"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    MENU_SOFTFUN_ACT_NUM,
    menuSoftFunActCn[0],
    menuSoftFunActEn[0],
    menuSoftFunActSet
};

static MENU_INFO_TYPE m_MenuSoftFunPosCtl = {           
    {"位置控制器", "Position ctrl"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    MENU_SOFTFUN_POSCTL_NUM,
    menuSoftFunPosCtlCn[0],
    menuSoftFunPosCtlEn[0],
    menuSoftFunPosCtlSet
};

static MENU_INFO_TYPE m_MenuSoftFunPosCtlSetPoint = {                 
    {"位置控制器", "Position ctrl"},
    &g_WinCommonSelectMenu,           
    _WinCommonSelectInterface,
    _voidFun,
    MENU_SOFTFUN_POSCTL_SETPOINT_NUM,
    menuSoftFunPosCtlSetPointCn[0],
    menuSoftFunPosCtlSetPointEn[0],
    menuSoftFunPosCtlSetPointSet,
    &dataStructInterface.softfunPosCtlSetPoint,
		32
};

static MENU_INFO_TYPE g_WinSoftFunDeadMinMenu = {            
    {"最小", "Min"},
    &g_WinPercentageMenu,
    _voidFun,
    _WinPercentageInterface,
    0,
    menuMinPercentage,
    menuMaxPercentage,
    &g_max_percentage,
    &dataStructInterface.softfunDeadmin
};

static MENU_INFO_TYPE g_WinSoftFunDeadMaxMenu = {       
    {"最大", "Max"},
    &g_WinPercentageMenu,
    _voidFun,
    _WinPercentageInterface,
    0,
    menuMinPercentage,
    menuMaxPercentage,
    &g_max_percentage,
    &dataStructInterface.softfunDeadmax
};

static MENU_INFO_TYPE m_MenuSoftRatioCtl = {           
    {"比例控制", "Ratio Ctl"},
    &g_WinCommonMenu,    
    _WinCommonMenuInterface,
    _voidFun,
    MENU_SOFTFUN_RATIOCTL_NUM,
    menuSoftFunRatioCtlCn[0],
    menuSoftFunRatioCtlEn[0],
    menuSoftFunRatioCtlSet,
};

static MENU_INFO_TYPE m_MenuSoftFunRatioSel = {               
    {"比例控制", "Ratio Ctl"},
    &g_WinCommonSelectMenu,            
    _WinCommonSelectInterface,
    _voidFun,
    SEL_SOFTFUN_RATIOCTL_NUM,
    SelSoftFunRatioCtlCn[0],
    SelSoftFunRatioCtlEn[0],
    SelSoftFunRatioCtlSet,
    &dataStructInterface.softfunRatioCtrl,
		33
};

static MENU_INFO_TYPE m_MenuSpePara = {              
    {"特殊参数", "Spe Para"},
    &g_WinCommonMenu,    
    _WinCommonMenuInterface,
    _voidFun,
    MENU_SPEPARA_NUM,
    menuSpeParaCn[0],
    menuSpeParaEn[0],
    menuSpeParaSet,
    NULL
};

static MENU_INFO_TYPE m_MenuSpeInstallSel = {                
    {"分体安装", "Install"},
    &g_WinCommonSelectMenu,           
    _WinCommonSelectInterface,
    _voidFun,
    SEL_SPE_STALL_NUM,
    SelSpeInstallCn[0],
    SelSpeInstallEn[0],
    SelSpeInstallSet,
    &dataStructInterface.speInstall,
		34
};

static MENU_INFO_TYPE m_MenuSpeMidPtOff = {        
    {"关中间节点", "Mid Pt Off"},
    &g_WinComThreeNumMenu,
    _voidFun,
    _WinComThreeNumInterface,
    0,
    menuPercentage0,
    menuPercentage100,
    &g_percentage_100,
    &dataStructInterface.speMidPtOff
};

static MENU_INFO_TYPE m_MenuSpeMidPtOn = {          
    {"开中间节点", "Mid Pt On"},
    &g_WinComThreeNumMenu,
    _voidFun,
    _WinComThreeNumInterface,
    0,
    menuPercentage0,
    menuPercentage100,
    &g_percentage_100,
    &dataStructInterface.speMidPtOn
};

static MENU_INFO_TYPE m_MenuSpeMotorHeat = {            
    {"电机加热", "Motor Heat"},
    &g_WinCommonSelectMenu,           
    _WinCommonSelectInterface,
    _voidFun,
    SEL_MOTOR_HEAT_NUM,
    SelMotorHeatCn[0],
    SelMotorHeatEn[0],
    SelMotorHeatSet,
    &dataStructInterface.speMotroHeat,
		35
};


static MENU_INFO_TYPE m_MenuSpeOverheatedAlarm = {           
    {"电机过热报警", "Motor Over Heated"},
    &g_WinComThreeNumMenu,
    _voidFun,
    _WinComThreeNumInterface,
    0,
    menuTemp0,
    menuTemp155,
    &g_temp_155,
    &dataStructInterface.speOverHeat
};


static MENU_INFO_TYPE m_MenuSpeOverheatedPro = {            
    {"电机过热保护", "Motor Over Heatd"},
    &g_WinCommonSelectMenu,                
    _WinCommonSelectInterface,
    _voidFun,
    SEL_MOTOR_HEAT_NUM,
    SelMotorHeatCn[0],
    SelMotorHeatEn[0],
    SelMotorHeatSet,
    &dataStructInterface.speMotroOverHeatPro,
		36
};


static MENU_INFO_TYPE m_MenuOnOffTimes = {     
    {"开关次数(以千计)", "TIMES "},
    &g_WinComFiveNumMenu,
    _voidFun,
    _WinComFiveNumInterface,
    0,
    menudata0,
    menudata30000,
    &g_data_30000,
    &dataStructInterface.MotorOnOffTimes
};

static MENU_INFO_TYPE m_MenuMomentOnOffTimes = {        
    {"力矩关断次数", "TIMES "},
    &g_WinComFiveNumMenu,
    _voidFun,
    _WinComFiveNumInterface,
    0,
    menudata0,
    menudata20000,
    &g_data_20000,
    &dataStructInterface.MomentOnOffTimes
};


static MENU_INFO_TYPE m_MotorRunHours = {             
    {"电机运行小时数", "Motor Run Hours"},
    &g_WinComFourNumMenu,
    _voidFun,
    _WinComFourNumInterface,
    0,
    menudata0,
    menudata2500,
    &g_data_2500,
    &dataStructInterface.MotorRunHours
};

static MENU_INFO_TYPE m_SpeExaDataSel = {            
    {"检查维护数据", "Examin data"},
    &g_WinCommonSelectMenu,           
    _WinCommonSelectInterface,
    _voidFun,
    SEL_MOTOR_HEAT_NUM,
    SelMotorHeatCn[0],
    SelMotorHeatEn[0],
    SelMotorHeatSet,
    &dataStructInterface.speExaData,
		37
};


static MENU_INFO_TYPE m_SpeFunFasten = {                
    {"关紧功能", "Fasten"},
    &g_WinCommonSelectMenu,            
    _WinCommonSelectInterface,
    _voidFun,
    SEL_MOTOR_HEAT_NUM,
    SelMotorHeatCn[0],
    SelMotorHeatEn[0],
    SelMotorHeatSet,
    &dataStructInterface.speFunFasten,
		38
};

static MENU_INFO_TYPE g_SpeUpperTimer = {              
    {"上升时间", "Upper Timer"},
    &g_WinPercentageMenu,
    _voidFun,
    _WinPercentageInterface,
    0,
    menuSecondD1,
    menuSecond2D0,
    &g_data_20,
    &dataStructInterface.speUpperTimer
};

static MENU_INFO_TYPE g_SpeDCBraking = {           
    {"直流制动", "DC Braking"},
    &g_WinComThreeNumMenu,
    _voidFun,
    _WinComThreeNumInterface,
    0,
    menuPercentage00,
    menuPercentage250,
    &g_data_250,
    &dataStructInterface.speDCBraking
};

static MENU_INFO_TYPE g_SpePowerOffDelay = {              
    {"断电延迟", "Power Off Delay"},
    &g_WinComThreeNumMenu,
    _voidFun,
    _WinComThreeNumInterface,
    0,
    menuSecond0,
    menuSecond25,
    &g_data_250,
    &dataStructInterface.spePowerOffDelay
};


static MENU_INFO_TYPE g_SpeFlangeSel = {           
    {"带力矩测量的法兰", "Flange Sel"},
    &g_WinCommonSelectMenu,         
    _WinCommonSelectInterface,
    _voidFun,
    SEL_FLANGE_NUM,
    SelFlangeCn[0],
    SelFlangeEn[0],
    SelFlangeSet,
    &dataStructInterface.speFlangeSel,
		39
};

static MENU_INFO_TYPE g_SpeLowerThreshold = {         
    {"Lower Threshold", "Lower Threshold"},
    &g_WinPercentageMenu,
    _voidFun,
    _WinPercentageInterface,
    0,
    menumA0,
    menumA3D6,
    &g_data_36,
    &dataStructInterface.speLowerThreshold
};

static MENU_INFO_TYPE g_SpeUpperThreshold = {          
    {"Upper Threshold", "Upper Threshold"},
    &g_WinComThreeNumMenu,
    _voidFun,
    _WinComThreeNumInterface,
    0,
    menumA22,
    menumA24,
    &g_data_240,
    &dataStructInterface.speUpperThreshold
};

static MENU_INFO_TYPE g_SpeTestOperation = {          
    {"Test Operation", "Test Operation"},
    &g_WinCommonSelectMenu,            
    _WinCommonSelectInterface,
    _voidFun,
    SEL_MOTOR_HEAT_NUM,
    SelMotorHeatCn[0],
    SelMotorHeatEn[0],
    SelMotorHeatSet,
    &dataStructInterface.speTestOperation,
		40
};

static MENU_INFO_TYPE g_SpeRuntimeClose = {            
    {"RuntimeClose", "RuntimeClose"},
    &g_WinComFourNumMenu,
    _voidFun,
    _WinComFourNumInterface,
    0,
    menuSecond0,
    menuSecond6553,
    &g_data_6553,
    &dataStructInterface.speRuntimeClose
};

static MENU_INFO_TYPE g_SpePauseClose = {            
    {"Pause Close", "Pause Close"}, 
    &g_WinComFourNumMenu,
    _voidFun,
    _WinComFourNumInterface,
    0,
    menuSecond0,
    menuSecond6553,
    &g_data_6553,
    &dataStructInterface.spePauseClose
};

static MENU_INFO_TYPE g_SpeRuntimeOpen = {           
    {"Runtime Open", "Runtime Open"},
    &g_WinComFourNumMenu,
    _voidFun,
    _WinComFourNumInterface,
    0,
    menuSecond0,
    menuSecond6553,
    &g_data_6553,
    &dataStructInterface.speRuntimeOpen
};

static MENU_INFO_TYPE g_SpePauseOpen = {            
    {"Pause Open", "Pause Open"},
    &g_WinComFourNumMenu,
    _voidFun,
    _WinComFourNumInterface,
    0,
    menuSecond0,
    menuSecond6553,
    &g_data_6553,
    &dataStructInterface.spePauseOpen
};


static MENU_INFO_TYPE g_SpeLimitionVoltage = {                  
    {"Limition DC-link voltage", "Limition DC-link voltage"},
    &g_WinCommonSelectMenu,             
    _WinCommonSelectInterface,
    _voidFun,
    SEL_COMMON_OPENCLOSE_NUM,
    SelComOpenCloseCn[0],
    SelComOpenCloseEn[0],
    SelComOpenCloseSet,
    &dataStructInterface.speLimitionVoltage,
		41
};

static MENU_INFO_TYPE g_SpeRuntimeMonitoring = {              
    {"Runtime Monitoring", "Runtime Monitoring"},
    &g_WinCommonSelectMenu,              
    _WinCommonSelectInterface,
    _voidFun,
    SEL_COMMON_OPENCLOSE_NUM,
    SelComOpenCloseCn[0],
    SelComOpenCloseEn[0],
    SelComOpenCloseSet,
    &dataStructInterface.speRuntimeMonitoring,
		42
};

static MENU_INFO_TYPE g_SpeEndPositionSpeed = {                    
    {"末端位置速度", "末端位置速度"},
    &g_WinCommonSelectMenu,             
    _WinCommonSelectInterface,
    _voidFun,
    SEL_END_POSITION_SPEED_NUM,
    SelEndPosSpeedCn[0],
    SelEndPosSpeedEn[0],
    SelEndPosSpeedSet,
    &dataStructInterface.speEndPoSpeed,
		43
};

static MENU_INFO_TYPE g_SpeAutom = {              
    {"Autom TL adapt endpos", "Autom TL adapt endpos"},
    &g_WinCommonSelectMenu,              
    _WinCommonSelectInterface,
    _voidFun,
    SEL_COMMON_OPENCLOSE_NUM,
    SelComOpenCloseCn[0],
    SelComOpenCloseEn[0],
    SelComOpenCloseSet,
    &dataStructInterface.speAutom,
		44
};

static MENU_INFO_TYPE g_SpeDCSAcceptance = {             
    {"DCS Acceptance time", "DCS Acceptance time"},
    &g_WinComThreeNumMenu,
    _voidFun,
    _WinComThreeNumInterface,
    0,
    menuSecond0,
    menuSecond25D5,
    &g_data_255,
    &dataStructInterface.speDCSAcceptance
};

static MENU_INFO_TYPE g_MenuParaWithSys = {           
    {"与系统有关的设定", "Para With Sys"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    MENU_PARA_WITH_SYS_NUM,
    menuParaSysCn[0],
    menuParaSysEn[0],
    menuParaSysSet
};


static MENU_INFO_TYPE g_MenuParaWithSysShow = {            
    {"显示", "Show"},
    &g_WinCommonMenu,    
    _WinCommonMenuInterface,
    _voidFun,
    MENU_PARA_WITH_SYS_SHOW_DIR_NUM,
    menuParaSysShowDirCn[0],
    menuParaSysShowDirEn[0],
    menuParaSysShowDirSet,
		0,
		23
};

static MENU_INFO_TYPE g_SelParaWithSysShowDir = {              
    {"显示方向", "Show Dir"},
    &g_WinCommonSelectMenu,     
    _WinCommonSelectInterface,
    _voidFun,
    MENU_PARA_WITH_SYS_SHOW_DIR_NUM,
    selParaSysShowDirCn[0],
    selParaSysShowDirEn[0],
    selParaSysShowDirSet,
    &dataStructInterface.showDirect,
		45
};




static MENU_INFO_TYPE m_PasswordChg = {
    {"密码修改", "Password change"},
};

static MENU_INFO_TYPE m_WinCommonSelectMenu = {                
    {"当前选择", "Current select"},
    &g_WinCommonSelectMenu,           
    _WinCommonSelectInterface,
    _voidFun,
    MENU_CUR_USER_NUM_2,
    menu_test_sel_cn[0],
    menu_test_sel_en[0],
    menu_test_sel_settings,
    &test_select,
		46
};

static MENU_INFO_TYPE m_WinCommonSelectMenu2 = {             
    {"当前选择2", "Current select2"},
    &g_WinCommonSelectMenu,            
    _WinCommonSelectInterface,
    _voidFun,
    MENU_CUR_USER_NUM_3,
    menu_test_sel_cn2[0],
    menu_test_sel_en2[0],
    menu_test_sel_settings2,
    &test_select2,
		47
};


static MENU_INFO_TYPE m_WinEmergencyPos = {            
    {"紧急位置", "Emergency position"},
    &g_WinEmergencyPosMenu,
};

static MENU_INFO_TYPE m_EndPosMenu = {                
    {"末端位置", "end position"}, 
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    SET_END_POSITION_MENU_NUM,
    EndPosMenuCn[0],
    EndPosMenuEn[0],
    EndPosMenuSet
};


static MENU_INFO_TYPE m_FirstSetEndPosMenu = {       
    {"首次设定末端位置", "First Set End Pos"},
    &g_WinFirstSetEndMenu,
    _voidFun
};

static MENU_INFO_TYPE m_SelEndPosMenu = {            
    {"首次设定末端位置", "First Set End Pos"},
    &g_WinSelEndPosMenu,
    _voidFun,
    _voidFun,
    0,
    menuCharSelEndPosCn,
    menuCharSelEndPosEn
};

static MENU_INFO_TYPE m_EndPosOpMenu = {                  
    {"首次设定末端位置", "First Set End Pos"},
    &g_WinEndPosOp,
    _voidFun,
    _voidFun,
    1,
    &dataStructInterface.Open_SetEndPosOpen,
    &dataStructInterface.Open_SetEndPosClose,
    &dataStructInterface.Open_SetEndPosState,
    &dataStructInterface.Open_GetEndPosState
};

static MENU_INFO_TYPE m_EndPosOpMenuT2 = {              
    {"首次设定末端位置", "First Set End Pos"},
    &g_WinEndPosOpT2,
    _voidFun,
    _voidFun,
    1,
    &dataStructInterface.Open_SetEndPosOpenT2,
    &dataStructInterface.Open_SetEndPosCloseT2,
    &dataStructInterface.Open_SetEndPosStateT2,
    &dataStructInterface.Open_GetEndPosStateT2
};


static MENU_INFO_TYPE m_EndPosCloseMenu = {                  
    {"首次设定末端位置", "First Set End Pos"},
    &g_WinEndPosOp,
    _voidFun,
    _voidFun,
    2,
    &dataStructInterface.close_SetEndPosOpen,
    &dataStructInterface.close_SetEndPosClose,
    &dataStructInterface.close_SetEndPosState,
    &dataStructInterface.close_GetEndPosState
};

static MENU_INFO_TYPE m_EndPosCloseMenuT2 = {              
    {"首次设定末端位置", "First Set End Pos"},
    &g_WinEndPosOpT2,
    _voidFun,
    _voidFun,
    2,
    &dataStructInterface.close_SetEndPosOpenT2,
    &dataStructInterface.close_SetEndPosCloseT2,
    &dataStructInterface.close_SetEndPosStateT2,
    &dataStructInterface.close_GetEndPosStateT2
};
#if 1
static MENU_INFO_TYPE m_FrstSelEndPosMenu = {          
    {"首次设定末端位置", "First set end position"},
    &g_WinCommonMenu,   
    _WinCommonMenuInterface,
    _voidFun,
    SET_END_POSITION_MENU_NUM,
    FrstSelEndPosMenuCn[0],
    FrstSelEndPosMenuEn[0],
    FrstSelEndPosMenuSet,
		0,25
};
#endif

static MENU_INFO_TYPE m_ResetEndPosMenu = {              
    {"重新设定末端位置", "Reset set end position"},
    &g_WinCommonMenu,               
    _WinCommonMenuInterface,
    _voidFun,
    SET_END_POSITION_MENU_NUM,
    FrstSelEndPosMenuCn[0],
    FrstSelEndPosMenuEn[0],
    FrstSelEndPosMenuSet
};


static MENU_INFO_TYPE m_ResetEndPosOpMenuT2 = {             
    {"重新设定末端位置", "Reset End Pos"},
    &g_WinEndPosOpT2,
    _voidFun,
    _voidFun,
    0,
    &dataStructInterface.Open_SetEndPosOpenT2,
    &dataStructInterface.Open_SetEndPosCloseT2,
    &dataStructInterface.Open_SetEndPosStateT2,
    &dataStructInterface.Open_GetEndPosStateT2
};

static MENU_INFO_TYPE m_ResetEndPosCloseMenuT2 = {           
    {"重新设定末端位置", "Reset End Pos"},
    &g_WinEndPosOpT2,
    _voidFun,
    _voidFun,
    0,
    &dataStructInterface.Close_SetEndPosOpenT2,
    &dataStructInterface.Close_SetEndPosCloseT2,
    &dataStructInterface.Close_SetEndPosStateT2,
    &dataStructInterface.Close_GetEndPosStateT2
};


#if 1
static MENU_INFO_TYPE m_WinBluetoothStatusMenu = {             
    {"蓝牙模块", "First set end position"},
    &g_WinCommonMenu,                
    _WinCommonMenuInterface,
    _voidFun,
    MENU_BLUETOOTH_STATUE_NUM,
    bluetooth_status_cn[0],
    bluetooth_status_en[0],
    bluetooth_status_Set,
		0,
		27
};


static MENU_INFO_TYPE m_WinBluetoothSelMenu = {                  
    {"蓝牙", "Current select"},
    &g_WinCommonSelectMenu,            
    _WinCommonSelectInterface,
    _voidFun,
    MENU_BLUETOOTH_SEL_NUM,
    bluetooth_sel_cn[0],
    bluetooth_sel_en[0],
    bluetooth_sel_Set,
    &dataStructInterface.bluetooth_status,
		48
};
#endif
#if 1
MENU_INFO_TYPE m_ChgPasswordMenu1 = {            
    {"修改密码", "Change Password"},
    &g_WinCommonMenu,         
    _WinCommonMenuInterface,
    _voidFun,
    3,
    ChgPasswordCn[0],
    ChgPasswordEn[0],
    ChgPasswordSet,
		0,
		28
};

MENU_INFO_TYPE m_ChgPasswordMenu2 = {            
    {"修改密码", "Change Password"},
    &g_WinCommonMenu,        
    _WinCommonMenuInterface,
    _voidFun,
    3,
    ChgPasswordCn[0],
    ChgPasswordEn[0],
    ChgPasswordSet,
		0,
		29
};

MENU_INFO_TYPE m_ChgPasswordMenu3 = {           
    {"修改密码", "Change Password"},
    &g_WinCommonMenu,     
    _WinCommonMenuInterface,
    _voidFun,
    4,
    ChgPasswordCn[0],
    ChgPasswordEn[0],
    ChgPasswordSet,
		0,
		30
};

MENU_INFO_TYPE m_ChgPasswordMenu4 = {              
    {"修改密码", "Change Password"},
    &g_WinCommonMenu,       
    _WinCommonMenuInterface,
    _voidFun,
    5,
    ChgPasswordCn[0],
    ChgPasswordEn[0],
    ChgPasswordSet,
		0,
		31
};

MENU_INFO_TYPE m_ChgPasswordMenu5 = {          
    {"修改密码", "Change Password"},
    &g_WinCommonMenu,          
    _WinCommonMenuInterface,
    _voidFun,
    6,
    ChgPasswordCn[0],
    ChgPasswordEn[0],
    ChgPasswordSet,
		0,
		32
};


MENU_INFO_TYPE *p_ChgPasswordMenu = &m_ChgPasswordMenu1;
void *pChgUserPasswordMenu = NULL;

static MENU_INFO_TYPE m_WinPasswordChangeHandle = {   
    {"更改密码确认", "Password Change"},
    &g_WinPasswordChange,
    _voidFun,
    _WinPasswordChangeInterface,
    0,
    new_password_handler_cn,
    new_password_handler_en,
    NULL,
    &password.g_password_handle,
		1
};

static MENU_INFO_TYPE m_WinPasswordChangeViewer = {  
    {"更改密码确认", "Password Change"},
    &g_WinPasswordChange,
    _voidFun,
    _WinPasswordChangeInterface,
    0,
    new_password_viewer_cn,
    new_password_viewer_en,
    NULL,
    &password.g_password_viewer,
		2
};

static MENU_INFO_TYPE m_WinPasswordChangeExpert = {      
    {"更改密码确认", "Password Change"},
    &g_WinPasswordChange,
    _voidFun,
    _WinPasswordChangeInterface,
    0,
    new_password_expert_cn,
    new_password_expert_en,
    NULL,
    &password.g_password_expert,
		3
};

static MENU_INFO_TYPE m_WinPasswordChangeService = {     
    {"更改密码确认", "Password Change"},
    &g_WinPasswordChange,
    _voidFun,
    _WinPasswordChangeInterface,
    0,
    new_password_service_cn,
    new_password_service_en,
    NULL,
    &password.g_password_service,
		4
};

static MENU_INFO_TYPE m_WinPasswordChangeFactroy = {    
    {"更改密码确认", "Password Change"},
    &g_WinPasswordChange,
    _voidFun,
    _WinPasswordChangeInterface,
    0,
    new_password_factroy_cn,
    new_password_factroy_en,
    NULL,
    &password.g_password_factroy,
		5
};
#endif

static MENU_INFO_TYPE m_EndPosSetOk = {               
    {"首次设定末端位置", "First Set End Pos"},
    &g_WinEndPosSetOkMenu,
};

static MENU_INFO_TYPE m_SetEndPosParaMenu1 = {       
    {"首次设定末端位置", "First Set End Pos"},
    &g_WinEndPosParaMenu,
    _WinEndPosParaMenuInterface,
    _voidFun,
    MENU1_ENDPOS_PARA_NUM,
    menu1EndPosParaCn[0],
    menu1EndPosParaEn[0],
    menu1EndPosParaSet,
		0,
		1
};

static MENU_INFO_TYPE m_SetEndPosParaMenu2 = {         
    {"首次设定末端位置", "First Set End Pos"},
    &g_WinEndPosParaMenu,
    _WinEndPosParaMenuInterface,
    _voidFun,
    MENU2_ENDPOS_PARA_NUM,
    menu2EndPosParaCn[0],
    menu2EndPosParaEn[0],
    menu2EndPosParaSet,
		0,
		2
};


#if 1

void WIN_WindowsTreeInit(void)
{
    void *p = NULL;
    void *pTemp = NULL;
    void *pTemp2 = NULL;
    void *pTemp3 = NULL;

    p = BT_GetDataItem(&m_MainWinInfo);
    BT_InitBiTree(p);   
    BT_AddChild(p, BT_GetDataItem(&m_MenuStateShowInfo), BT_RIGHT);    
    pTemp = p;
    p = BT_GetRightChild(p);  
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo1), BT_RIGHT);

    p = BT_GetRightChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo2), BT_LEFT);

    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo3), BT_LEFT);

    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo4), BT_LEFT);

    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo5), BT_LEFT);

    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo6), BT_LEFT);

    p = pTemp;
    p = BT_GetRightChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuLocalOp), BT_LEFT);     
    p = BT_GetLeftChild(p);  
    BT_AddChild(p, BT_GetDataItem(&m_MenuStateShowInfo), BT_RIGHT);

    p = BT_GetRightChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo1), BT_RIGHT);

    p = BT_GetRightChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo2), BT_LEFT);

    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo3), BT_LEFT);

    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo4), BT_LEFT);

    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo5), BT_LEFT);

    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuHelpShowInfo6), BT_LEFT);

    p = pTemp;
    p = BT_GetRightChild(p);
    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuLanguage), BT_LEFT);     


    p = pTemp;
    p = BT_GetRightChild(p);
    p = BT_GetLeftChild(p);
    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MainMenuInfo), BT_LEFT);      
    p = BT_GetLeftChild(p);
    pTemp = p; 
    BT_AddChild(p, BT_GetDataItem(&m_UserManagInfo), BT_RIGHT);  //用户管理界面
    p = BT_GetRightChild(p);   
    BT_AddChild(p, BT_GetDataItem(&m_CurUserInfo2), BT_RIGHT); //用户管理界面的右子节点，设置为当前用户界面
        p = BT_GetRightChild(p); 
        BT_AddChild(p, BT_GetDataItem(&m_MenuNull), BT_RIGHT);   
        p = BT_GetRightChild(p);
        BT_AddChild(p, BT_GetDataItem(&m_WinPasswordInputHandle), BT_LEFT);   
        p = BT_GetLeftChild(p); 
        BT_AddChild(p, BT_GetDataItem(&m_WinPasswordInputViewer), BT_LEFT);     
        p = BT_GetLeftChild(p); 
        BT_AddChild(p, BT_GetDataItem(&m_WinPasswordInputExpert), BT_LEFT);   
        p = BT_GetLeftChild(p); 
        BT_AddChild(p, BT_GetDataItem(&m_WinPasswordInputService), BT_LEFT);  
        p = BT_GetLeftChild(p);
        BT_AddChild(p, BT_GetDataItem(&m_WinPasswordInputFactroy), BT_LEFT);  
#if 1
    p = pTemp;
    p = BT_GetRightChild(p);   
    p = BT_GetRightChild(p);
	pChgUserPasswordMenu = p;
    BT_AddChild(p, BT_GetDataItem(p_ChgPasswordMenu), BT_LEFT);  //用户管理界面的左子节点，设置为改变密码界面
	    p = BT_GetLeftChild(p);
		BT_AddChild(p, BT_GetDataItem(&m_WinPasswordChangeHandle), BT_RIGHT);
		p = BT_GetRightChild(p);
	    BT_AddChild(p, BT_GetDataItem(&m_WinPasswordChangeViewer), BT_LEFT);
		p = BT_GetLeftChild(p);
	    BT_AddChild(p, BT_GetDataItem(&m_WinPasswordChangeExpert), BT_LEFT);
		p = BT_GetLeftChild(p);
	    BT_AddChild(p, BT_GetDataItem(&m_WinPasswordChangeService), BT_LEFT);
		p = BT_GetLeftChild(p);
	    BT_AddChild(p, BT_GetDataItem(&m_WinPasswordChangeFactroy), BT_LEFT);
#endif

    p = pTemp;
    p = BT_GetRightChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuObserve), BT_LEFT);   
        p = BT_GetLeftChild(p);
        pTemp2 = p; 
        BT_AddChild(p, BT_GetDataItem(&m_MenuObNamePlate), BT_RIGHT);  
            p = BT_GetRightChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_MenuNull), BT_RIGHT);

            p = BT_GetRightChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_MenuNull), BT_LEFT);

            p = BT_GetLeftChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_MenuObNamePlateDevice), BT_LEFT); 
        p = pTemp2 ;  
        p = BT_GetRightChild(p);  
        BT_AddChild(p, BT_GetDataItem(&m_MenuObInOutPut), BT_LEFT);

            p = BT_GetLeftChild(p); 
            BT_AddChild(p, BT_GetDataItem(&m_MenuObKrInPut), BT_RIGHT);

            p = BT_GetRightChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuObKrOutPut), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_MenuObAnalog), BT_LEFT);

        p = pTemp2 ;  
        p = BT_GetRightChild(p); 
        p = BT_GetLeftChild(p);   
        BT_AddChild(p, BT_GetDataItem(&m_MenuObStatus), BT_LEFT);


    p = pTemp;
    p = BT_GetRightChild(p);
    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuDiagnose), BT_LEFT);


#if 1	
	p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_EndPosMenu), BT_LEFT);

        pTemp2 = BT_GetLeftChild(p);           
        BT_AddChild(pTemp2, BT_GetDataItem(&m_FirstSetEndPosMenu), BT_RIGHT);

            pTemp3 = BT_GetRightChild(pTemp2);
            BT_AddChild(pTemp3, BT_GetDataItem(&m_SelEndPosMenu), BT_RIGHT);

                pTemp3 = BT_GetRightChild(pTemp2);
                BT_AddChild(pTemp3, BT_GetDataItem(&m_FrstSelEndPosMenu), BT_RIGHT);

 pTemp3 = BT_GetRightChild(pTemp3);
                BT_AddChild(pTemp3, BT_GetDataItem(&m_SetEndPosParaMenu1), BT_LEFT);
                    pTemp3 = BT_GetLeftChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuCloseDir), BT_RIGHT);
                    pTemp3 = BT_GetRightChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_WinSpeedClose), BT_LEFT);
                    pTemp3 = BT_GetLeftChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_WinSpeedOpen), BT_LEFT);
                    pTemp3 = BT_GetLeftChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuNull), BT_LEFT);
                    pTemp3 = BT_GetLeftChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_SetEndPosParaMenu2), BT_LEFT);
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinOffModeClose), BT_RIGHT);
                        pTemp3 = BT_GetRightChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinOffModeOpen), BT_LEFT);
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinMomentPosClose), BT_LEFT);
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinMomentPosOpen), BT_LEFT);
                    pTemp3 = BT_GetRightChild(pTemp2);
                    pTemp3 = BT_GetRightChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosOpMenu), BT_RIGHT);   
                        pTemp3 = BT_GetRightChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuNull), BT_RIGHT);
                        pTemp3 = BT_GetRightChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosOpMenuT2), BT_LEFT);   //首次设置开末端
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosSetOk), BT_RIGHT);
                pTemp3 = BT_GetRightChild(pTemp2);
                pTemp3 = BT_GetRightChild(pTemp3);
                pTemp3 = BT_GetRightChild(pTemp3);								
                BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosCloseMenu), BT_LEFT);   
												pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuNull), BT_RIGHT);
                        pTemp3 = BT_GetRightChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosCloseMenuT2), BT_LEFT);  //首次设置开末端
												pTemp3 = BT_GetLeftChild(pTemp3);
                            BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosSetOk), BT_RIGHT);
							
				#if 0
				pTemp3 = BT_GetRightChild(pTemp3);
                BT_AddChild(pTemp3, BT_GetDataItem(&m_ResetEndPosMenu), BT_LEFT);
                    pTemp3 = BT_GetLeftChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuCloseDir), BT_RIGHT);
                    pTemp3 = BT_GetRightChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_WinSpeedClose), BT_LEFT);
                    pTemp3 = BT_GetLeftChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_WinSpeedOpen), BT_LEFT);
                    pTemp3 = BT_GetLeftChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuNull), BT_LEFT);
                    pTemp3 = BT_GetLeftChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_SetEndPosParaMenu2), BT_LEFT);
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinOffModeClose), BT_RIGHT);
                        pTemp3 = BT_GetRightChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinOffModeOpen), BT_LEFT);
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinMomentPosClose), BT_LEFT);
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinMomentPosOpen), BT_LEFT);
                    pTemp3 = BT_GetRightChild(pTemp2);
                    pTemp3 = BT_GetRightChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosOpMenu), BT_RIGHT);   //开方向第一次设置
                        pTemp3 = BT_GetRightChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuNull), BT_RIGHT);
                        pTemp3 = BT_GetRightChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosOpMenuT2), BT_LEFT);  //开方向第二次设置
												pTemp3 = BT_GetLeftChild(pTemp3);
                            BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosSetOk), BT_RIGHT);
                pTemp3 = BT_GetRightChild(pTemp2);
                pTemp3 = BT_GetRightChild(pTemp3);
                pTemp3 = BT_GetRightChild(pTemp3);								
                BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosCloseMenu), BT_LEFT);              //关方向第一次设置
                        //pTemp3 = BT_GetRightChild(pTemp3);
												pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuNull), BT_RIGHT);
                        pTemp3 = BT_GetRightChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosCloseMenuT2), BT_LEFT);     //关方向第二次设置
												pTemp3 = BT_GetLeftChild(pTemp3);
                            BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosSetOk), BT_RIGHT);
				#endif
				#if 1
				 pTemp3 = BT_GetRightChild(pTemp2);
                BT_AddChild(pTemp3, BT_GetDataItem(&m_FirstSetEndPosMenu), BT_LEFT);
                
                    pTemp3 = BT_GetLeftChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_ResetEndPosMenu), BT_RIGHT); 
                    
                    pTemp3 = BT_GetRightChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_SetEndPosParaMenu1), BT_LEFT);  
         
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuCloseDir), BT_RIGHT);  
           
                        pTemp3 = BT_GetRightChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinSpeedClose), BT_LEFT);   
           
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinSpeedOpen), BT_LEFT);    
           
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuNull), BT_LEFT);        
           
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_SetEndPosParaMenu2), BT_LEFT);  
           
                            pTemp3 = BT_GetLeftChild(pTemp3);
                            BT_AddChild(pTemp3, BT_GetDataItem(&m_WinOffModeClose), BT_RIGHT);  
           
                            pTemp3 = BT_GetRightChild(pTemp3);
                            BT_AddChild(pTemp3, BT_GetDataItem(&m_WinOffModeOpen), BT_LEFT);    
           
                            pTemp3 = BT_GetLeftChild(pTemp3);
                            BT_AddChild(pTemp3, BT_GetDataItem(&m_WinMomentPosClose), BT_LEFT); 
           
                            pTemp3 = BT_GetLeftChild(pTemp3);
                            BT_AddChild(pTemp3, BT_GetDataItem(&m_WinMomentPosOpen), BT_LEFT);  
                            
                            
                 pTemp3 = BT_GetRightChild(pTemp2);
                 pTemp3 = BT_GetLeftChild(pTemp3);
                 pTemp3 = BT_GetRightChild(pTemp3);
                 BT_AddChild(pTemp3, BT_GetDataItem(&m_ResetEndPosOpMenuT2), BT_RIGHT);  //重新设置开末端
                 
                     pTemp3 = BT_GetRightChild(pTemp3);
				             BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosSetOk), BT_RIGHT);
				             
				         pTemp3 = BT_GetRightChild(pTemp2);
                 pTemp3 = BT_GetLeftChild(pTemp3);
                 pTemp3 = BT_GetRightChild(pTemp3);
                 pTemp3 = BT_GetRightChild(pTemp3);
                 BT_AddChild(pTemp3, BT_GetDataItem(&m_ResetEndPosCloseMenuT2), BT_LEFT);  //重新设置关末端
                 
                     pTemp3 = BT_GetLeftChild(pTemp3);
				             BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosSetOk), BT_RIGHT);
				#endif
						#if 0
				 pTemp3 = BT_GetRightChild(pTemp2);
                BT_AddChild(pTemp3, BT_GetDataItem(&m_FirstSetEndPosMenu), BT_LEFT);
                
                    pTemp3 = BT_GetLeftChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_ResetEndPosMenu), BT_RIGHT); 
                    
                    pTemp3 = BT_GetRightChild(pTemp3);
                    BT_AddChild(pTemp3, BT_GetDataItem(&m_SetEndPosParaMenu1), BT_LEFT);  
         
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuCloseDir), BT_RIGHT);  
           
                        pTemp3 = BT_GetRightChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinSpeedClose), BT_LEFT);   
           
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_WinSpeedOpen), BT_LEFT);    
           
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_MenuNull), BT_LEFT);        
           
                        pTemp3 = BT_GetLeftChild(pTemp3);
                        BT_AddChild(pTemp3, BT_GetDataItem(&m_SetEndPosParaMenu2), BT_LEFT);  
           
                            pTemp3 = BT_GetLeftChild(pTemp3);
                            BT_AddChild(pTemp3, BT_GetDataItem(&m_WinOffModeClose), BT_RIGHT);  
           
                            pTemp3 = BT_GetRightChild(pTemp3);
                            BT_AddChild(pTemp3, BT_GetDataItem(&m_WinOffModeOpen), BT_LEFT);    
           
                            pTemp3 = BT_GetLeftChild(pTemp3);
                            BT_AddChild(pTemp3, BT_GetDataItem(&m_WinMomentPosClose), BT_LEFT); 
           
                            pTemp3 = BT_GetLeftChild(pTemp3);
                            BT_AddChild(pTemp3, BT_GetDataItem(&m_WinMomentPosOpen), BT_LEFT);  
                            
                            
                 pTemp3 = BT_GetRightChild(pTemp2);
                 pTemp3 = BT_GetLeftChild(pTemp3);
                 pTemp3 = BT_GetRightChild(pTemp3);
                 BT_AddChild(pTemp3, BT_GetDataItem(&m_ResetEndPosOpMenuT2), BT_RIGHT);
                 
                     pTemp3 = BT_GetRightChild(pTemp3);
				             BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosSetOk), BT_RIGHT);
				             
				         pTemp3 = BT_GetRightChild(pTemp2);
                 pTemp3 = BT_GetLeftChild(pTemp3);
                 pTemp3 = BT_GetRightChild(pTemp3);
                 pTemp3 = BT_GetRightChild(pTemp3);
                 BT_AddChild(pTemp3, BT_GetDataItem(&m_ResetEndPosCloseMenuT2), BT_LEFT);
                 
                     pTemp3 = BT_GetLeftChild(pTemp3);
				             BT_AddChild(pTemp3, BT_GetDataItem(&m_EndPosSetOk), BT_RIGHT);
				#endif
										#if 0
            pTemp3 = BT_GetRightChild(pTemp2);
			BT_AddChild(pTemp3, BT_GetDataItem(&m_ResetEndPosMenu), BT_LEFT);

			    pTemp3 = BT_GetLeftChild(pTemp3);
				BT_AddChild(pTemp3, BT_GetDataItem(&m_ResetEndPosOpMenuT2), BT_RIGHT);

				pTemp3 = BT_GetRightChild(pTemp3);
				BT_AddChild(pTemp3, BT_GetDataItem(&m_ResetEndPosCloseMenuT2), BT_LEFT);
				#endif
	
				
    #endif
    p = BT_GetLeftChild(p);
    BT_AddChild(p, BT_GetDataItem(&m_MenuPara), BT_LEFT);

        p = BT_GetLeftChild(p);
        pTemp2 = p;           
        BT_AddChild(p, BT_GetDataItem(&m_MenuGear), BT_RIGHT);

            p = BT_GetRightChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_MenuGearType), BT_RIGHT);

        p = pTemp2;              
        p = BT_GetRightChild(p);  
        BT_AddChild(p, BT_GetDataItem(&m_MenuVavlePara), BT_LEFT);

            p = BT_GetLeftChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_MenuCloseDir), BT_RIGHT);

            p = BT_GetRightChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_WinSpeedClose), BT_LEFT);

            p = BT_GetLeftChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_WinSpeedOpen), BT_LEFT);

            p = BT_GetLeftChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_WinOffModeClose), BT_LEFT);

            p = BT_GetLeftChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_WinOffModeOpen), BT_LEFT);

            p = BT_GetLeftChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_WinMomentPosClose), BT_LEFT);

            p = BT_GetLeftChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_WinMomentPosOpen), BT_LEFT);

            p = BT_GetLeftChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_WinEndPosClose), BT_LEFT);

            p = BT_GetLeftChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_WinEndPosOpen), BT_LEFT);

            p = BT_GetLeftChild(p);
            BT_AddChild(p, BT_GetDataItem(&m_WinOverMomentTimes), BT_LEFT);
        p = pTemp2;               
        p = BT_GetRightChild(p);  
        p = BT_GetLeftChild(p);   
        pTemp2 = p;
        BT_AddChild(p, BT_GetDataItem(&m_MenuCtrlSysPara), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_MenuCtrlMode), BT_RIGHT);

            p = BT_GetRightChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuRmtChose), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuKrInput), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuModeInput), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuAnologInput), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuAnologInputRange), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput), BT_LEFT);

                p = BT_GetLeftChild(p);   
                pTemp3 = p ;
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput1_1), BT_RIGHT);

                p = BT_GetRightChild(p);  
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput1_2), BT_LEFT);

                p = BT_GetLeftChild(p);  
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput2_1), BT_LEFT);

                p = BT_GetLeftChild(p);  
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput2_2), BT_LEFT);

                 p = BT_GetLeftChild(p);   
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput3_1), BT_LEFT);

                p = BT_GetLeftChild(p);   
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput3_2), BT_LEFT);

                 p = BT_GetLeftChild(p);  
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput4_1), BT_LEFT);

                p = BT_GetLeftChild(p);   
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput4_2), BT_LEFT);

                 p = BT_GetLeftChild(p);  
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput5_1), BT_LEFT);

                p = BT_GetLeftChild(p);  
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput5_2), BT_LEFT);

                 p = BT_GetLeftChild(p);   
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput6_1), BT_LEFT);

                p = BT_GetLeftChild(p);  
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput6_2), BT_LEFT);

                 p = BT_GetLeftChild(p);   
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput7_1), BT_LEFT);

                p = BT_GetLeftChild(p);   
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput7_2), BT_LEFT);

                 p = BT_GetLeftChild(p);  
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput8_1), BT_LEFT);

                p = BT_GetLeftChild(p);  
                BT_AddChild(p, BT_GetDataItem(&m_MenuKrOutput8_2), BT_LEFT);

            p = pTemp3;
            BT_AddChild(p, BT_GetDataItem(&m_MenuAOutput1), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_MenuAOutput2), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuAOutput3), BT_LEFT);

        p = pTemp2;
        p = BT_GetLeftChild(p);   
        BT_AddChild(p, BT_GetDataItem(&m_MenuSafty), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_MenuEmgInput), BT_RIGHT);

            p = BT_GetRightChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_WinEmgSpeedClose), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_WinEmgSpeedOpen), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_WinEmergencyPos), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuEmgCtrlSrcFault), BT_LEFT);


        p = pTemp2;
        p = BT_GetLeftChild(p);   
        p = BT_GetLeftChild(p);   
        BT_AddChild(p, BT_GetDataItem(&m_MenuSoftFun), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuSoftFunActive), BT_RIGHT);

            p = BT_GetRightChild(p);   
            pTemp3 = p;
            BT_AddChild(p, BT_GetDataItem(&m_MenuSoftFunPosCtl), BT_LEFT);

                p = BT_GetLeftChild(p);   
                BT_AddChild(p, BT_GetDataItem(&m_MenuSoftFunPosCtlSetPoint), BT_RIGHT);

                p = BT_GetRightChild(p);   
                BT_AddChild(p, BT_GetDataItem(&g_WinSoftFunDeadMinMenu), BT_LEFT);

                p = BT_GetLeftChild(p);  
                BT_AddChild(p, BT_GetDataItem(&g_WinSoftFunDeadMaxMenu), BT_LEFT);

            p = pTemp3;
            p = BT_GetLeftChild(p); 
            BT_AddChild(p, BT_GetDataItem(&m_MenuSoftRatioCtl), BT_LEFT);

                p = BT_GetLeftChild(p);   
                BT_AddChild(p, BT_GetDataItem(&m_MenuSoftFunRatioSel), BT_RIGHT);

        p = pTemp2;
        p = BT_GetLeftChild(p);  
        p = BT_GetLeftChild(p);  
        p = BT_GetLeftChild(p);  
        BT_AddChild(p, BT_GetDataItem(&m_MenuSpePara), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuNull), BT_RIGHT);

            p = BT_GetRightChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_MenuSpeInstallSel), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuSpeMidPtOff), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_MenuSpeMidPtOn), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuSpeMotorHeat), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_MenuSpeOverheatedAlarm), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_MenuSpeOverheatedPro), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_MenuOnOffTimes), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_MenuMomentOnOffTimes), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_MotorRunHours), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&m_SpeExaDataSel), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&m_SpeFunFasten), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&g_SpeUpperTimer), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&g_SpeDCBraking), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&g_SpePowerOffDelay), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&g_SpeFlangeSel), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&g_SpeLowerThreshold), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&g_SpeUpperThreshold), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&g_SpeTestOperation), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&g_SpeRuntimeClose), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&g_SpePauseClose), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&g_SpeRuntimeOpen), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&g_SpePauseOpen), BT_LEFT);

            p = BT_GetLeftChild(p);  
            BT_AddChild(p, BT_GetDataItem(&g_SpeLimitionVoltage), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&g_SpeRuntimeMonitoring), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&g_SpeEndPositionSpeed), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&g_SpeAutom), BT_LEFT);

            p = BT_GetLeftChild(p);   
            BT_AddChild(p, BT_GetDataItem(&g_SpeDCSAcceptance), BT_LEFT);

    p = pTemp;
    p = BT_GetRightChild(p);
    p = BT_GetLeftChild(p);
    p = BT_GetLeftChild(p);
    p = BT_GetLeftChild(p);
    p = BT_GetLeftChild(p); 
    BT_AddChild(p, BT_GetDataItem(&m_MenuNull), BT_LEFT);

    p = BT_GetLeftChild(p); 
    BT_AddChild(p, BT_GetDataItem(&g_MenuParaWithSys), BT_LEFT);
#if 1
 pTemp3 =p;
        p = BT_GetLeftChild(p);
        BT_AddChild(p, BT_GetDataItem(&g_MenuParaWithSysShow), BT_RIGHT);

            p = BT_GetRightChild(p);
            BT_AddChild(p, BT_GetDataItem(&g_SelParaWithSysShowDir), BT_RIGHT);   

		p = pTemp3;
		p = BT_GetLeftChild(p);
		p = BT_GetRightChild(p);
		BT_AddChild(p, BT_GetDataItem(&m_MenuNull), BT_LEFT);

		p = BT_GetLeftChild(p);
		BT_AddChild(p, BT_GetDataItem(&m_WinBluetoothStatusMenu), BT_LEFT);

		    p = BT_GetLeftChild(p);
			BT_AddChild(p, BT_GetDataItem(&m_WinBluetoothSelMenu), BT_RIGHT);
      

#endif

}

#endif

