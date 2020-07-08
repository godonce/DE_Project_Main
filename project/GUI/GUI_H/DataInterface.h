
#if 0
#ifndef _DATA_INTERFACE_H_
#define _DATA_INTERFACE_H_

//有多少种类设备状态
#define DEVICE_STATE_NUM    3
#define DEVICE_STATE_LOCAL  0
#define DEVICE_STATE_REMOTE 1
#define DEVICE_STATE_OFF    2
#define WINMAIN_LIST_NUM    4

#define MAIN_MENU_FOCUS_TEXT 0
#define MAIN_MENU_FOCUS_LIST 1

#define LANGUAGE_CN 0
#define LANGUAGE_EN 1

#define STRSHOWBUF_SIZE 128


#define DEBUG_X_OFFSET 20
#define DEBUG_Y_OFFSET 5
#define PER_CM_OFFSET  46

#define MAX_FAULT_NUM 6

#define MAX_FAULT_TEXT_NUM 52

//每个字符串的最大字符数
#define MAX_INFO_CHAR 26

//有多少钟状态显示
#define DEVICE_STATE_INFO_NUM    10
//有多少标题信息显示
#define DEVICE_TITLE_INFO_NUM    20
//主菜单的数目
#define MAIN_MENU_NUM 7

//用户管理菜单的数目
#define MENU_USER_MANAG_NUM   4
#define MENU_SETTING_TITLE    0
#define MENU_SETTING_CONTENT  1

#define MENU_CUR_USER_NUM 8

#define AUTHRITY_NUM          6
#define AUTHRITY_OBSERVER     0
#define AUTHRITY_OPERATOR     1
#define AUTHRITY_INSPECTOR    2
#define AUTHRITY_EXPERT       3
#define AUTHRITY_SERVICE      4
#define AUTHRITY_FACTORY      5

#if 0
typedef struct
{
	unsigned char stateOpen;                     //阀门的状态 开
	unsigned char stateClose;                    //阀门的状态 关
	unsigned char stateMid;                      //阀门的状态 中间态
	unsigned char numMid1;                       //阀门的打开比例数字1
	unsigned char numMid2;                       //阀门的打开比例数字2
	unsigned char IndexWinMainInfo;              //主界面错误信息的index
	unsigned char numFault;                      //当前有多少条错误信息
	unsigned char indexDeviceState;              //装置状态显示信息的序号
	unsigned char indexFaultNum[MAX_FAULT_NUM];  //装置状态显示信息的序号
    unsigned char helpExpIndex;                  //信息查看栏显示的错误信息
    unsigned char helpMethodIndex;               //信息查看栏显示的错误信息
}DATASTRUCTINTERFACE;
#endif

#ifdef  CE12
enum speed_close_open{rang1=05,rang2=07,rang3=10,rang4=14,rang5=20,rang6=28,rang7=40};
#endif

#ifdef  DE13
enum speed_close_open{rang1=10,rang2=14,rang3=20,rang4=28,rang5=40,rang6=56,rang7=80};
#endif
#ifdef  EE13
enum speed_close_open{rang1=20,rang2=28,rang3=40,rang4=56,rang5=80,rang6=112,rang7=160};
#endif
#if 1
typedef struct
{
	unsigned char stateOpen;                     //????? ?
	unsigned char stateClose;                    //????? ?
	unsigned char stateMid;                      //????? ???
	unsigned char numMid1;                       //?????????1
	unsigned char numMid2;                       //?????????2
	unsigned char IndexWinMainInfo;              //????????index
	unsigned char numFault;                      //??????????
	unsigned char indexDeviceState;              //???????????
	unsigned char indexFaultNum[MAX_FAULT_NUM];  //???????????
	unsigned char helpExpIndex[MAX_FAULT_NUM];                  //????????????
	unsigned char helpMethodIndex[MAX_FAULT_NUM];               //????????????
	enum speed_close_open speed_close;               //????
	enum speed_close_open speed_open;               //????
	unsigned char endPosClose;                  //????????
	unsigned char endPosOpen;                   //????????
	float moment_close;
	float moment_open;
	char moment_overtimes;              //???????
	  int/*unsigned char*/ emergency_pos;
  char ObNamePlateLable[MAX_INFO_CHAR];
  char ObNamePlateModel[MAX_INFO_CHAR];
  char ObNamePlateSerial[MAX_INFO_CHAR];
  unsigned short gearType;                //??????
	unsigned short gearType_old;                //??????
  unsigned char closeDir;                //???
  unsigned short closeOffMode;               //?????
  unsigned short openOffMode;                //?????
  unsigned char ctrlMode;                //????
	//unsigned char ctrlMode1;                //????
  unsigned short rmtChoose;                //????
  unsigned short krInput;                  //?????
  unsigned short modeInput;
  unsigned short anologInput;             //???????
  unsigned short anologInputRange;             //???????
  unsigned short krOutputSel1[8+1];                  //?????
  unsigned short krOutputSel2[8+1];                  //?????
  unsigned short anologOutputSel1;             //???????
  unsigned short anologOutputSel2;             //???????
  unsigned short anologOutputSel3;             //???????
  enum speed_close_open emg_speed_close;      //????-?
  enum speed_close_open emg_speed_open;       //????-?
  unsigned short emgInput;                     //????
  unsigned short emgCtlSrcFault;               //???????
  unsigned short softfunPosCtlSetPoint;        //???????
  unsigned short softfunDeadmin;               //?????
  unsigned short softfunDeadmax;               //?????
  unsigned short softfunRatioCtrl;             //????
  unsigned short speInstall;                   //????
  unsigned short speMidPtOff;               //?????
  unsigned short speMidPtOn;               //?????
  unsigned short speMotroHeat;               //????
  unsigned short speOverHeat;               //??????
  unsigned short speMotroOverHeatPro;               //??????
  unsigned short MotorOnOffTimes;               //??????
  unsigned short MomentOnOffTimes;               //??????
  unsigned short MotorRunHours;               //??????
  unsigned short speExaData;               //??????
  unsigned short speFunFasten;               //????
  unsigned short speUpperTimer;               //????
  unsigned short speDCBraking;               //????
  unsigned short spePowerOffDelay;               //????
  unsigned short speFlangeSel;               //??
  unsigned short speLowerThreshold;          //LowerThreshold
  unsigned short speUpperThreshold;          //UpperThreshold
  unsigned short speTestOperation;               //TestOperation
  unsigned short speRuntimeClose;               //??????
  unsigned short spePauseClose;               //??????
  unsigned short speRuntimeOpen;               //??????
  unsigned short spePauseOpen;               //??????
  unsigned short  speLimitionVoltage;      
  unsigned short  speRuntimeMonitoring;     
  unsigned short  speEndPoSpeed;   
  unsigned short  speAutom;   
  unsigned short  speDCSAcceptance;  

  char Open_SetEndPosOpen;
  char Open_SetEndPosClose;	
	unsigned short Open_SetEndPosState;
  unsigned short Open_GetEndPosState;
  char EndPosStateNum1;
  char EndPosStateNum2;
  char Open_SetEndPosOpenT2;
  char Open_SetEndPosCloseT2;
  unsigned short Open_SetEndPosStateT2;
  unsigned short Open_GetEndPosStateT2;
	char close_SetEndPosOpen;
  char close_SetEndPosClose;
  unsigned short close_SetEndPosState;
  unsigned short close_GetEndPosState;
  char close_SetEndPosOpenT2;
  char close_SetEndPosCloseT2;
  unsigned short close_SetEndPosStateT2;
  unsigned short close_GetEndPosStateT2;
	unsigned short  showDirect;
	
	unsigned short  Frame_SN;
	unsigned short  Select_SN;
	
	  char Close_SetEndPosOpenT2;
  char Close_SetEndPosCloseT2;
  unsigned short Close_SetEndPosStateT2;
  unsigned short Close_GetEndPosStateT2;
	unsigned short bluetooth_status;
}DATASTRUCTINTERFACE;
#endif

void _InterDataRefresh(void);
char * GetExpInfoPtr(unsigned char index,char LanguageIndex);
char * GetHandleInfoPtr(unsigned char index,char LanguageIndex);

extern  char infoWinMainCN[][MAX_INFO_CHAR];
extern  char infoWinMainEN[][MAX_INFO_CHAR];
extern  char infoWinMainList0CN[][MAX_INFO_CHAR];
extern  char infoWinMainList0EN[][MAX_INFO_CHAR];
extern  char infoWinMainListCN[][MAX_INFO_CHAR];
extern  char infoWinMainListEN[][MAX_INFO_CHAR];
extern  char infoDeviceStateCN[][MAX_INFO_CHAR];
extern  char infoDeviceStateEN[][MAX_INFO_CHAR];
extern  char infoTitleCN[][MAX_INFO_CHAR];
extern  char infoTitleEN[][MAX_INFO_CHAR];

extern  char exp_cn_content0[];
extern  char exp_cn_content1[];
extern  char exp_cn_content2[];
extern  char exp_cn_content3[];
extern  char exp_cn_content4[];
extern  char exp_en_content0[];
extern  char exp_en_content1[];
extern  char exp_en_content2[];
extern  char exp_en_content3[];
extern  char exp_en_content4[];
extern  char handle_cn_content0[];
extern  char handle_cn_content1[];
extern  char handle_cn_content2[];
extern  char handle_cn_content3[];
extern  char handle_cn_content4[];
extern  char handle_en_content0[];
extern  char handle_en_content1[];
extern  char handle_en_content2[];
extern  char handle_en_content3[];
extern  char handle_en_content4[];

extern  char menuMainCn[][MAX_INFO_CHAR];
extern  char menuMainEn[][MAX_INFO_CHAR];

extern char menuUserManagCn[][MAX_INFO_CHAR];
extern char menuUserManagEn[][MAX_INFO_CHAR];
extern unsigned char menuUserManagSettings[];
extern char menuUserManagCnBak[][MAX_INFO_CHAR];
extern char menuUserManagEnBak[][MAX_INFO_CHAR];

extern char menuCurUserCn[][MAX_INFO_CHAR];
extern char menuCurUserEn[][MAX_INFO_CHAR];
extern unsigned char menuCurUserSettings[];

extern char userNameCn[][MAX_INFO_CHAR];
extern char userNameEn[][MAX_INFO_CHAR];

extern DATASTRUCTINTERFACE dataStructInterface;
extern volatile char   g_deviceState;
extern volatile char   g_mainMenuFocus;
extern volatile char   g_hdlMenuFocus;
extern volatile char   g_authority ;

#endif


#endif


#if 1

#ifndef _DATA_INTERFACE_H_
#define _DATA_INTERFACE_H_
#include "WIN.h"
//?????????
#define DEVICE_STATE_NUM    3
#define DEVICE_STATE_LOCAL  0
#define DEVICE_STATE_REMOTE 1
#define DEVICE_STATE_OFF    2
#define WINMAIN_LIST_NUM    4

#define MAIN_MENU_FOCUS_TEXT 0
#define MAIN_MENU_FOCUS_LIST 1

#define LANGUAGE_CN 0
#define LANGUAGE_EN 1

#define STRSHOWBUF_SIZE 128


#define DEBUG_X_OFFSET 10
#define DEBUG_Y_OFFSET 5
#define PER_CM_OFFSET  46

#define MAX_FAULT_NUM 64

#define MAX_FAULT_TEXT_NUM 64//52

//???????????
#define MAX_INFO_CHAR 50                                                  //WY 2018.08.01

//????????
#define DEVICE_STATE_INFO_NUM    10
//?????????
#define DEVICE_TITLE_INFO_NUM    20
//??????
#define MAIN_MENU_NUM 7

//?????????
#define MENU_USER_MANAG_NUM   4
#define MENU_SETTING_TITLE    0
#define MENU_SETTING_CONTENT  1
#define MENU_SETTING_DISAPP   2

#define MENU_CUR_USER_NUM 8

#define AUTHRITY_NUM          6
#define AUTHRITY_OBSERVER     0
#define AUTHRITY_OPERATOR     1
#define AUTHRITY_INSPECTOR    2
#define AUTHRITY_EXPERT       3
#define AUTHRITY_SERVICE      4
#define AUTHRITY_FACTORY      5

#define MENU_CUR_USER_NUM_2 10

#define MENU_CUR_USER_NUM_3 5

#define MAX_ITEAM_PER_PAGE   8

#ifdef  CE12
#define SPEED_MIN   5//20
#define SPEED_MAX 40//160

#define MOMENT_MIN  18//37.5
#define MOMENT_MAX  60//125
#define MOMENT_STEP 6//12.5
#endif

#ifdef  DE13
#define SPEED_MIN   10//20
#define SPEED_MAX 80//160
#define MOMENT_MIN  18//37.5
#define MOMENT_MAX  60//125
#define MOMENT_STEP 6//12.5
#endif
#ifdef  EE13
#define SPEED_MIN   20//20
#define SPEED_MAX 160//160
#define MOMENT_MIN  18//37.5
#define MOMENT_MAX  60//125
#define MOMENT_STEP 6//12.5
#endif


#define END_POS_CLOSE_MIN 2
#define END_POS_CLOSE_MAX 20

#define END_POS_OPEN_MIN 80
#define END_POS_OPEN_MAX 98

#define MOMENT_OVERTIMES_MIN 0
#define MOMENT_OVERTIMES_MAX 5

#define INFO_MENU_SAVE_NUM   2

#define MENU_OB_SET_NUM        3
#define MENU_OB_NAMEPLATE_NUM  7
#define MENU_OB_NAMEPLATE_DEVICE_NUM 17
#define MENU_OB_INOUTPUT_NUM   3
#define MENU_OB_KRINPUT_NUM    5
#define MENU_OB_KROUTPUT_NUM   8
#define MENU_OB_ANALOG_NUM     2
#define MENU_OB_STATUS_NUM     20
#define MENU_DIAGNOSE_NUM      15
#define MENU_PARA_NUM          6
#define MENU_GEAR_NUM          2
#define MENU_GEAR_TYPE_NUM     4
#define MENU_VAVLE_PARA_NUM    16
#define MENU_CLOSE_DIR_NUM     2
#define MENU_OFF_MODE_NUM      2
#define MENU_CTRL_SYS_PARA_NUM 17
#define MENU_CTRL_MODE_NUM     6
#define MENU_SAFTY_PARA_NUM    9
#define MENU_REMOTE_CHOSE_NUM  6
#define MENU_KR_INPUT_NUM      2
#define MENU_MODE_INPUT_NUM    3
#define MENU_ANOLOG_INPUT_NUM  2
#define MENU_ANOLOG_INPUT_AI1_NUM  2
#define MENU_KR_OUTPUT_NUM    24
#define MENU_KROUTPUT_SEL1_NUM 22
#define MENU_KROUTPUT_SEL2_NUM 2
#define MENU_ANOOUTPUT_SEL1_NUM 2
#define MENU_ANOOUTPUT_SEL2_NUM 2
#define MENU_ANOOUTPUT_SEL3_NUM 2
#define MENU_SAFTY_INPUT_NUM    2
#define MENU_SAFTY_CTLSRC_FAULT_NUM    2
#define MENU_SOFTFUN_NUM        3
#define MENU_SOFTFUN_ACT_NUM    8  //??????
#define MENU_SOFTFUN_POSCTL_NUM 5  //?????
#define MENU_SOFTFUN_POSCTL_SETPOINT_NUM 4
#define MENU_SOFTFUN_RATIOCTL_NUM 8
#define SEL_SOFTFUN_RATIOCTL_NUM 3
#define MENU_SPEPARA_NUM         46
#define SEL_SPE_STALL_NUM 2
#define SEL_MOTOR_HEAT_NUM 2
#define SEL_FLANGE_NUM 3
#define SEL_COMMON_OPENCLOSE_NUM 2
#define SEL_END_POSITION_SPEED_NUM 3
#define SET_END_POSITION_MENU_NUM 2
#define MENU_PARA_WITH_SYS_NUM 3
#define MENU_PARA_WITH_SYS_SHOW_NUM 2
#define MENU_PARA_WITH_SYS_SHOW_DIR_NUM 2
#define MENU_BLUETOOTH_STATUE_NUM 2
#define MENU_BLUETOOTH_SEL_NUM 3
#define MENU1_ENDPOS_PARA_NUM 5
#define MENU2_ENDPOS_PARA_NUM 6

#ifdef  CE12
enum speed_close_open{rang1=05,rang2=07,rang3=10,rang4=14,rang5=20,rang6=28,rang7=40};
#endif

#ifdef  DE13
enum speed_close_open{rang1=10,rang2=14,rang3=20,rang4=28,rang5=40,rang6=56,rang7=80};
#endif
#ifdef  EE13
enum speed_close_open{rang1=20,rang2=28,rang3=40,rang4=56,rang5=80,rang6=112,rang7=160};
#endif
typedef struct
{
	unsigned char stateOpen;                     //????? ?
	unsigned char stateClose;                    //????? ?
	unsigned char stateMid;                      //????? ???
	unsigned char numMid1;                       //?????????1
	unsigned char numMid2;                       //?????????2
	unsigned char IndexWinMainInfo;              //????????index
	unsigned char numFault;                      //??????????
	unsigned char indexDeviceState;              //???????????
	unsigned char indexFaultNum[MAX_FAULT_NUM];  //???????????
	unsigned char helpExpIndex[MAX_FAULT_NUM];                  //????????????
	unsigned char helpMethodIndex[MAX_FAULT_NUM];               //????????????
	enum speed_close_open speed_close;               //????
	enum speed_close_open speed_open;               //????
	unsigned char endPosClose;                  //????????
	unsigned char endPosOpen;                   //????????
	float moment_close;
	float moment_open;
	char moment_overtimes;              //???????
    int/*unsigned char*/ emergency_pos;
    char ObNamePlateLable[MAX_INFO_CHAR];
    char ObNamePlateModel[MAX_INFO_CHAR];
    char ObNamePlateSerial[MAX_INFO_CHAR];
    unsigned short gearType;                //??????
    unsigned short gearType_old;                //??????
    unsigned char closeDir;                //???
    unsigned short closeOffMode;               //?????
    unsigned short openOffMode;                //?????
    unsigned char ctrlMode;                //????
	//unsigned char ctrlMode1;                //????
    unsigned short rmtChoose;                //????
    unsigned short krInput;                  //?????
    unsigned short modeInput;
    unsigned short anologInput;             //???????
    unsigned short anologInputRange;             //???????
    unsigned short krOutputSel1[8+1];                  //?????
    unsigned short krOutputSel2[8+1];                  //?????
    unsigned short anologOutputSel1;             //???????
    unsigned short anologOutputSel2;             //???????
    unsigned short anologOutputSel3;             //???????
    enum speed_close_open emg_speed_close;      //????-?
    enum speed_close_open emg_speed_open;       //????-?
    unsigned short emgInput;                     //????
    unsigned short emgCtlSrcFault;               //???????
    unsigned short softfunPosCtlSetPoint;        //???????
    unsigned short softfunDeadmin;               //?????
    unsigned short softfunDeadmax;               //?????
    unsigned short softfunRatioCtrl;             //????
    unsigned short speInstall;                   //????
    unsigned short speMidPtOff;               //?????
    unsigned short speMidPtOn;               //?????
    unsigned short speMotroHeat;               //????
    unsigned short speOverHeat;               //??????
    unsigned short speMotroOverHeatPro;               //??????
    unsigned short MotorOnOffTimes;               //??????
    unsigned short MomentOnOffTimes;               //??????
    unsigned short MotorRunHours;               //??????
    unsigned short speExaData;               //??????
    unsigned short speFunFasten;               //????
    unsigned short speUpperTimer;               //????
    unsigned short speDCBraking;               //????
    unsigned short spePowerOffDelay;               //????
    unsigned short speFlangeSel;               //??
    unsigned short speLowerThreshold;          //LowerThreshold
    unsigned short speUpperThreshold;          //UpperThreshold
    unsigned short speTestOperation;               //TestOperation
    unsigned short speRuntimeClose;               //??????
    unsigned short spePauseClose;               //??????
    unsigned short speRuntimeOpen;               //??????
    unsigned short spePauseOpen;               //??????
    unsigned short  speLimitionVoltage;      
    unsigned short  speRuntimeMonitoring;     
    unsigned short  speEndPoSpeed;   
    unsigned short  speAutom;   
    unsigned short  speDCSAcceptance;
    char Open_SetEndPosOpen;
    char Open_SetEndPosClose;	
    unsigned short Open_SetEndPosState;
    unsigned short Open_GetEndPosState;
    char EndPosStateNum1;
    char EndPosStateNum2;
    char Open_SetEndPosOpenT2;
    char Open_SetEndPosCloseT2;
    unsigned short Open_SetEndPosStateT2;
    unsigned short Open_GetEndPosStateT2;
    char close_SetEndPosOpen;
    char close_SetEndPosClose;
    unsigned short close_SetEndPosState;
    unsigned short close_GetEndPosState;
    char close_SetEndPosOpenT2;
    char close_SetEndPosCloseT2;
    unsigned short close_SetEndPosStateT2;
    unsigned short close_GetEndPosStateT2;
    unsigned short  showDirect;
	
    unsigned short  Frame_SN;
    unsigned short  Select_SN;
    unsigned short  PASSWORD;
    unsigned short  menunum;
	
    char Close_SetEndPosOpenT2;
    char Close_SetEndPosCloseT2;
    unsigned short Close_SetEndPosStateT2;
    unsigned short Close_GetEndPosStateT2;
    unsigned short bluetooth_status;
}DATASTRUCTINTERFACE;


void _InterDataInit(void);
void _InterDataRefresh(void);
const char * GetExpInfoPtr(unsigned char index,char LanguageIndex);
const char * GetHandleInfoPtr(unsigned char index,char LanguageIndex);

extern const char infoWinMainCN[][MAX_INFO_CHAR];
extern const char infoWinMainEN[][MAX_INFO_CHAR];
extern char infoWinMainList0CN[][MAX_INFO_CHAR];
extern  char infoWinMainList0EN[][MAX_INFO_CHAR];
extern  char infoWinMain_remote[4][MAX_INFO_CHAR];
extern  char infoWinMainListCN[][MAX_INFO_CHAR];
extern  char infoWinMainListEN[][MAX_INFO_CHAR];
extern  char infoDeviceStateCN[][MAX_INFO_CHAR];
extern  char infoDeviceStateEN[][MAX_INFO_CHAR];
extern  char infoTitleCN[][MAX_INFO_CHAR];
extern  char infoTitleEN[][MAX_INFO_CHAR];
extern  char info_menu_save_CN[][MAX_INFO_CHAR];
extern  char info_menu_save_EN[][MAX_INFO_CHAR];

extern const char exp_cn_content0[];
extern const char exp_cn_content1[];
extern const char exp_cn_content2[];
extern const char exp_cn_content3[];
extern const char exp_cn_content4[];
extern const char exp_en_content0[];
extern const char exp_en_content1[];
extern const char exp_en_content2[];
extern const char exp_en_content3[];
extern const char exp_en_content4[];
extern const char handle_cn_content0[];
extern const char handle_cn_content1[];
extern const char handle_cn_content2[];
extern const char handle_cn_content3[];
extern const char handle_cn_content4[];
extern const char handle_en_content0[];
extern const char handle_en_content1[];
extern const char handle_en_content2[];
extern const char handle_en_content3[];
extern const char handle_en_content4[];

extern  char menuMainCn[][MAX_INFO_CHAR];
extern  char menuMainEn[][MAX_INFO_CHAR];
extern unsigned short menuMainSettings[];
	

extern char menuUserManagCn[][MAX_INFO_CHAR];
extern char menuUserManagEn[][MAX_INFO_CHAR];
extern unsigned short menuUserManagSettings[];
extern char menuUserManagCnBak[][MAX_INFO_CHAR];
extern char menuUserManagEnBak[][MAX_INFO_CHAR];

extern  char menuCurUserCn[][MAX_INFO_CHAR];
extern  char menuCurUserEn[][MAX_INFO_CHAR];
extern unsigned short menuCurUserSettings[];

extern char userNameCn[][MAX_INFO_CHAR];
extern char userNameEn[][MAX_INFO_CHAR];

extern char menu_test_sel_cn[][MAX_INFO_CHAR];
extern char menu_test_sel_en[][MAX_INFO_CHAR];
extern unsigned short menu_test_sel_settings[];

extern char menu_test_sel_cn2[][MAX_INFO_CHAR];
extern char menu_test_sel_en2[][MAX_INFO_CHAR];
extern unsigned short menu_test_sel_settings2[];

extern DATASTRUCTINTERFACE dataStructInterface;
extern  char   g_deviceState;
extern volatile char   g_mainMenuFocus;
extern volatile char   g_hdlMenuFocus;
extern volatile short   g_authority ;
extern volatile unsigned short   g_max_percentage;
extern volatile unsigned short   g_percentage_100;
extern volatile unsigned short   g_temp_155;
extern volatile unsigned short   g_data_30000;
extern volatile unsigned short   g_data_20000;
extern volatile unsigned short   g_data_2500;
extern volatile unsigned short    g_data_20;
extern volatile unsigned short    g_data_250;
extern volatile unsigned short    g_data_36;
extern volatile unsigned short    g_data_240;
extern volatile unsigned short    g_data_255;
extern volatile unsigned short    g_data_6553;
extern volatile unsigned short   g_password_handle;
extern volatile unsigned short   g_password_viewer;
extern volatile unsigned short   g_password_expert;
extern volatile unsigned short   g_password_service;
extern volatile unsigned short   g_password_factroy;



extern char menuObCn[][MAX_INFO_CHAR];
extern char menuObEn[][MAX_INFO_CHAR];
extern unsigned short menuObSet[];

extern char menuObNamePlateCn[][MAX_INFO_CHAR];
extern char menuObNamePlateEn[][MAX_INFO_CHAR];
extern unsigned short menuObNamePlateSet[];

extern char menuObPlateDeviceEn[][MAX_INFO_CHAR];
extern char menuObPlateDeviceCn[][MAX_INFO_CHAR];
extern unsigned short menuObPlateDeviceSet[];

extern char menuObInOutPutCn[][MAX_INFO_CHAR];
extern char menuObInOutPutEn[][MAX_INFO_CHAR];
extern unsigned short menuObInOutPutSet[];

extern char menuObKrInputCn[][MAX_INFO_CHAR];
extern char menuObKrInputCn_L1[][MAX_INFO_CHAR];
extern char menuObKrInputCn_H1[][MAX_INFO_CHAR];
extern char menuObKrInputEn[][MAX_INFO_CHAR];
extern unsigned short menuObKrInputSet[];

extern char menuObKrOutputCn[][MAX_INFO_CHAR];
extern char menuObKrOutputEn[][MAX_INFO_CHAR];
extern unsigned short menuObKrOutputSet[];

extern char menuObAnalogCn[][MAX_INFO_CHAR];
extern char menuObAnalogEn[][MAX_INFO_CHAR];
extern unsigned short menuObAnalogSet[];

extern char menuObStatusCn[][MAX_INFO_CHAR];
extern char menuObStatusEn[][MAX_INFO_CHAR];
extern unsigned short menuObStatusSet[];

extern char menuDiagnoseCn[][MAX_INFO_CHAR];
extern char menuDiagnoseEn[][MAX_INFO_CHAR];
extern unsigned short menuDiagnoseSet[];


extern char menuParaCn[][MAX_INFO_CHAR];
extern char menuParaEn[][MAX_INFO_CHAR];
extern unsigned short menuParaSet[];

extern char menuGearCn[][MAX_INFO_CHAR];
extern char menuGearEn[][MAX_INFO_CHAR];
extern unsigned short menuGearSet[];

extern char menuGearTypeCn[][MAX_INFO_CHAR];
extern char menuGearTypeEn[][MAX_INFO_CHAR];
extern unsigned short menuGearTypeSet[];

extern char menuVavleParaCn[][MAX_INFO_CHAR];
extern char menuVavleParaEn[][MAX_INFO_CHAR];
extern unsigned short menuVavleParaSet[];

extern char menuSelCloseDirCn[][MAX_INFO_CHAR];
extern char menuSelCloseDirEn[][MAX_INFO_CHAR];
extern unsigned short menuSelCloseDirSet[];

extern char menuSelOffModeCn[][MAX_INFO_CHAR];
extern char menuSelOffModeEn[][MAX_INFO_CHAR];
extern unsigned short menuSelOffModeSet[];

extern char menuCtrlSysParaCn[][MAX_INFO_CHAR];
extern char menuCtrlSysParaEn[][MAX_INFO_CHAR];
extern unsigned short menuCtrlSysParaSet[];

extern char menuSaftyCn[][MAX_INFO_CHAR];
extern char menuSaftyEn[][MAX_INFO_CHAR];
extern unsigned short menuSaftySet[];

extern char menuCtrlModeCn[][MAX_INFO_CHAR];
extern char menuCtrlModeEn[][MAX_INFO_CHAR];
extern unsigned short menuCtrlModeSet[];

extern char menuRmtChoseCn[][MAX_INFO_CHAR];
extern char menuRmtChoseEn[][MAX_INFO_CHAR];
extern unsigned short menuRmtChoseSet[];

extern char menuKrInputCn[][MAX_INFO_CHAR];
extern char menuKrInputEn[][MAX_INFO_CHAR];
extern unsigned short menuKrInputSet[];

extern char menuModeInputCn[][MAX_INFO_CHAR];
extern char menuModeInputEn[][MAX_INFO_CHAR];
extern unsigned short menuModeInputSet[];

extern char menuAnologInputCn[][MAX_INFO_CHAR];
extern char menuAnologInputEn[][MAX_INFO_CHAR];
extern unsigned short menuAnologInputSet[];

extern char menuAnologInputAI1Cn[][MAX_INFO_CHAR];
extern char menuAnologInputAI1En[][MAX_INFO_CHAR];
extern unsigned short menuAnologInputAI1Set[];

extern char menuKrOutputCn[][MAX_INFO_CHAR];
extern char menuKrOutputEn[][MAX_INFO_CHAR];
extern unsigned short menuKrOutputSet[];

extern char menuKrOutputSel1Cn_1[][MAX_INFO_CHAR];
extern char menuKrOutputSel1Cn[][MAX_INFO_CHAR];
extern char menuKrOutputSel1En[][MAX_INFO_CHAR];
extern unsigned short menuKrOutputSel1Set[];

extern char menuKrOutputSel2Cn_1[][MAX_INFO_CHAR];
extern char menuKrOutputSel2Cn[][MAX_INFO_CHAR];
extern char menuKrOutputSel2En[][MAX_INFO_CHAR];
extern unsigned short menuKrOutputSel2Set[];

extern char menuAnologOutputSel1Cn[][MAX_INFO_CHAR];
extern char menuAnologOutputSel1En[][MAX_INFO_CHAR];
extern unsigned short menuAnologOutputSel1Set[];

extern char menuAnologOutputSel2Cn[][MAX_INFO_CHAR];
extern char menuAnologOutputSel2En[][MAX_INFO_CHAR];
extern unsigned short menuAnologOutputSel2Set[];

extern char menuAnologOutputSel3Cn[][MAX_INFO_CHAR];
extern char menuAnologOutputSel3En[][MAX_INFO_CHAR];
extern unsigned short menuAnologOutputSel3Set[];

extern char menuSaftyEmInputCn[][MAX_INFO_CHAR];
extern char menuSaftyEmInputEn[][MAX_INFO_CHAR];
extern unsigned short menuSaftyEmInputSet[];

extern char menuSaftyCtlSrcFaultCn[][MAX_INFO_CHAR];
extern char menuSaftyCtlSrcFaultEn[][MAX_INFO_CHAR];
extern unsigned short menuSaftyCtlSrcFaultSet[];

extern char menuSoftFunCn[][MAX_INFO_CHAR];
extern char menuSoftFunEn[][MAX_INFO_CHAR];
extern unsigned short menuSoftFunSet[];

extern char menuSoftFunActCn[][MAX_INFO_CHAR];
extern char menuSoftFunActEn[][MAX_INFO_CHAR];
extern unsigned short menuSoftFunActSet[];

extern char menuSoftFunPosCtlCn[][MAX_INFO_CHAR];
extern char menuSoftFunPosCtlEn[][MAX_INFO_CHAR];
extern unsigned short menuSoftFunPosCtlSet[];

extern char menuSoftFunPosCtlSetPointCn[][MAX_INFO_CHAR];
extern char menuSoftFunPosCtlSetPointEn[][MAX_INFO_CHAR];
extern unsigned short menuSoftFunPosCtlSetPointSet[];

extern unsigned char menuMinPercentage[];
extern unsigned char menuMaxPercentage[];
extern unsigned char menuPercentage0[];
extern unsigned char menuPercentage100[];
extern unsigned char menuTemp0[MAX_INFO_CHAR];
extern unsigned char menuTemp155[MAX_INFO_CHAR];
extern unsigned char menudata0[MAX_INFO_CHAR];
extern unsigned char menudata2500[MAX_INFO_CHAR];
extern unsigned char menudata20000[MAX_INFO_CHAR];
extern unsigned char menudata30000[MAX_INFO_CHAR];
extern unsigned char menuSecondD1[MAX_INFO_CHAR];
extern unsigned char menuSecond2D0[MAX_INFO_CHAR];
extern unsigned char menuPercentage00[MAX_INFO_CHAR];
extern unsigned char menuPercentage250[MAX_INFO_CHAR];
extern unsigned char menuSecond0[MAX_INFO_CHAR];
extern unsigned char menuSecond25[MAX_INFO_CHAR];
extern unsigned char menuSecond25D5[MAX_INFO_CHAR];
extern unsigned char menuSecond6553[MAX_INFO_CHAR];
extern unsigned char menumA0[MAX_INFO_CHAR];
extern unsigned char menumA3D6[MAX_INFO_CHAR];
extern unsigned char menumA22[MAX_INFO_CHAR];
extern unsigned char menumA24[MAX_INFO_CHAR];

extern char menuSoftFunRatioCtlCn[][MAX_INFO_CHAR];
extern char menuSoftFunRatioCtlEn[][MAX_INFO_CHAR];
extern unsigned short menuSoftFunRatioCtlSet[];

extern char SelSoftFunRatioCtlCn[][MAX_INFO_CHAR];
extern char SelSoftFunRatioCtlEn[][MAX_INFO_CHAR];
extern unsigned short SelSoftFunRatioCtlSet[];

extern char menuSpeParaCn[][MAX_INFO_CHAR];
extern char menuSpeParaEn[][MAX_INFO_CHAR];
extern unsigned short menuSpeParaSet[];

extern char SelSpeInstallCn[][MAX_INFO_CHAR];
extern char SelSpeInstallEn[][MAX_INFO_CHAR];
extern unsigned short SelSpeInstallSet[];

extern char SelMotorHeatCn[][MAX_INFO_CHAR];
extern char SelMotorHeatEn[][MAX_INFO_CHAR];
extern unsigned short SelMotorHeatSet[];

extern char SelFlangeCn[][MAX_INFO_CHAR];
extern char SelFlangeEn[][MAX_INFO_CHAR];
extern unsigned short SelFlangeSet[];

extern char SelComOpenCloseCn[][MAX_INFO_CHAR];
extern char SelComOpenCloseEn[][MAX_INFO_CHAR];
extern unsigned short SelComOpenCloseSet[];

extern char SelEndPosSpeedCn[][MAX_INFO_CHAR];
extern char SelEndPosSpeedEn[][MAX_INFO_CHAR];
extern unsigned short SelEndPosSpeedSet[];

extern unsigned char menuEndPos1[MAX_INFO_CHAR];
extern unsigned char menuEndPos2[MAX_INFO_CHAR];
extern unsigned char menuEndPos3[MAX_INFO_CHAR];
extern unsigned char menuEndPos4[MAX_INFO_CHAR];
extern unsigned char menuCharClose[MAX_INFO_CHAR];
extern unsigned char menuCharOpen[MAX_INFO_CHAR];
extern unsigned char menuCharSelEndPosCn[MAX_INFO_CHAR];
extern unsigned char menuCharSelEndPosEn[MAX_INFO_CHAR];
extern unsigned char menuCharSetEndPosCn[MAX_INFO_CHAR];
extern unsigned char menuCharSetEndPosEn[MAX_INFO_CHAR];
extern unsigned char menuCharSetEndPosCn_Open[MAX_INFO_CHAR];
extern unsigned char menuCharSetEndPosEn_Open[MAX_INFO_CHAR] ;
extern unsigned char menuCharSetEndPosCn_Close[MAX_INFO_CHAR] ;
extern unsigned char menuCharSetEndPosEn_Close[MAX_INFO_CHAR];
extern unsigned char menuCharHelpCn[MAX_INFO_CHAR];
extern unsigned char menuCharHelpEn[MAX_INFO_CHAR];
extern unsigned char menuCharEnterEndPosCn[MAX_INFO_CHAR];
extern unsigned char menuCharEnterEndPosEn[MAX_INFO_CHAR];
extern unsigned char menuCharSetRangeEndPosCn[MAX_INFO_CHAR];
extern unsigned char menuCharSetRangeEndPosEn[MAX_INFO_CHAR];
extern unsigned char menuCharSetDataEndPosCn[MAX_INFO_CHAR];
extern unsigned char menuCharSetDataEndPosEn[MAX_INFO_CHAR];



extern char EndPosMenuCn[][MAX_INFO_CHAR];
extern char EndPosMenuEn[][MAX_INFO_CHAR];
extern unsigned short EndPosMenuSet[];


extern unsigned char menuEndPos1[MAX_INFO_CHAR];
extern unsigned char menuEndPos2[MAX_INFO_CHAR];
extern unsigned char menuEndPos3[MAX_INFO_CHAR];
extern unsigned char menuEndPos4[MAX_INFO_CHAR];
extern unsigned char menuCharClose[MAX_INFO_CHAR];
extern unsigned char menuCharOpen[MAX_INFO_CHAR];
extern unsigned char menuCharSelEndPosCn[MAX_INFO_CHAR];
extern unsigned char menuCharSelEndPosEn[MAX_INFO_CHAR];
extern unsigned char menuCharSetEndPosCn[MAX_INFO_CHAR];
extern unsigned char menuCharSetEndPosEn[MAX_INFO_CHAR];
extern unsigned char menuCharHelpCn[MAX_INFO_CHAR];
extern unsigned char menuCharHelpEn[MAX_INFO_CHAR];
extern unsigned char menuCharEnterEndPosCn[MAX_INFO_CHAR];
extern unsigned char menuCharEnterEndPosEn[MAX_INFO_CHAR];
extern unsigned char menuCharSetRangeEndPosCn[MAX_INFO_CHAR];
extern unsigned char menuCharSetRangeEndPosEn[MAX_INFO_CHAR];
extern unsigned char menuCharSetDataEndPosCn[MAX_INFO_CHAR];
extern unsigned char menuCharSetDataEndPosEn[MAX_INFO_CHAR];

extern char menuParaSysCn[][MAX_INFO_CHAR];
extern char menuParaSysEn[][MAX_INFO_CHAR];
extern unsigned short menuParaSysSet[];

extern char menuParaSysShowDirCn[][MAX_INFO_CHAR];
extern char menuParaSysShowDirEn[][MAX_INFO_CHAR];
extern unsigned short menuParaSysShowDirSet[];

extern char selParaSysShowDirCn[][MAX_INFO_CHAR];
extern char selParaSysShowDirEn[][MAX_INFO_CHAR];
extern unsigned short selParaSysShowDirSet[];

extern  const char convert_user_to_handler_cn[];
extern  const char convert_user_to_handler_en[];
extern  const char convert_user_to_viewer_cn[];
extern  const char convert_user_to_viewer_en[];
extern  const char convert_user_to_expert_cn[];
extern  const char convert_user_to_expert_en[];
extern  const char convert_user_to_service_cn[];
extern  const char convert_user_to_service_en[];
extern  const char convert_user_to_factroy_cn[];
extern  const char convert_user_to_factroy_en[];

//MENU_INFO_TYPE *m_pUserManagInfo;
//MENU_INFO_TYPE  m_UserManagInfo;
//MENU_INFO_TYPE  m_UserManagInfo2;
//MENU_INFO_TYPE *m_pUserManagInfo;
//MENU_INFO_TYPE  m_UserManagInfo;
//MENU_INFO_TYPE  m_UserManagInfo2;

extern char FrstSelEndPosMenuCn[][MAX_INFO_CHAR];
extern char FrstSelEndPosMenuEn[][MAX_INFO_CHAR];
extern unsigned short FrstSelEndPosMenuSet[];
#if 1
extern const char bluetooth_status_cn[][MAX_INFO_CHAR];
extern const char bluetooth_status_en[][MAX_INFO_CHAR];
extern  unsigned short bluetooth_status_Set[];

extern const char bluetooth_sel_cn[][MAX_INFO_CHAR];
extern const char bluetooth_sel_en[][MAX_INFO_CHAR];
extern  unsigned short bluetooth_sel_Set[];

extern  const char info_menu_ok[1][MAX_INFO_CHAR];
#endif

#if 1
extern const char ChgPasswordCn[][MAX_INFO_CHAR];
extern const char ChgPasswordEn[][MAX_INFO_CHAR];
extern  unsigned short ChgPasswordSet[];

extern const char new_password_handler_cn[];
extern const char new_password_handler_en[];
extern const char new_password_viewer_cn[];
extern const char new_password_viewer_en[];
extern const char new_password_expert_cn[];
extern const char new_password_expert_en[];
extern const char new_password_service_cn[];
extern const char new_password_service_en[];
extern const char new_password_factroy_cn[];
extern const char new_password_factroy_en[];

extern const char info_menu_continue[][MAX_INFO_CHAR];

extern  char menu1EndPosParaCn[][MAX_INFO_CHAR];
extern  char menu1EndPosParaEn[][MAX_INFO_CHAR];
extern unsigned short menu1EndPosParaSet[];

extern  char menu2EndPosParaCn[][MAX_INFO_CHAR];
extern  char menu2EndPosParaEn[][MAX_INFO_CHAR];
extern unsigned short menu2EndPosParaSet[];
#endif

#endif

#endif
