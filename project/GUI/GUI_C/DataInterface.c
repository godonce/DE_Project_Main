#include "DataInterface.h"
#include  "datafigures.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"  
#pragma  diag_suppress 870  
DATASTRUCTINTERFACE dataStructInterface;
extern unsigned char ssi_m,ssi_s;
extern uint8_t DIR_MOTOR  ; 
unsigned char   g_deviceState  ;
volatile char   g_mainMenuFocus  = 0;
volatile char   g_hdlMenuFocus  = 1;
volatile short  g_authority  = AUTHRITY_OPERATOR;  //临时调整，方便测试。默认上电为专家模式，之前为1

volatile char   g_authority_bak;
volatile unsigned short   g_max_percentage  = 25;
volatile unsigned short   g_percentage_100  = 100;
volatile unsigned short   g_temp_155  = 155;
volatile unsigned short   g_data_30000  = 30000;
volatile unsigned short   g_data_20000  = 20000;
volatile unsigned short   g_data_2500  = 2500;
volatile unsigned short   g_data_20  = 20;
volatile unsigned short   g_data_250  = 250;
volatile unsigned short   g_data_36  = 36;
volatile unsigned short   g_data_240  = 240;
volatile unsigned short   g_data_6553  = 6553;
volatile unsigned short   g_data_255  = 255;
volatile unsigned short   g_password_handle  = 1;
volatile unsigned short   g_password_viewer  = 9041;
volatile unsigned short   g_password_expert  = 9044;
volatile unsigned short   g_password_service  = 9045;
volatile unsigned short   g_password_factroy  = 9046;





extern char flag_reset_encoder;
extern uint16_t SPEED_Stand;
extern uint16_t TORQUE_Stand;
void _InterDataInit(void)
{
    dataStructInterface.stateOpen    = 0 ;
    dataStructInterface.stateClose   = 0 ;
    dataStructInterface.stateMid     = 1 ;
    dataStructInterface.IndexWinMainInfo = 5;
    dataStructInterface.numFault = 3;
    dataStructInterface.indexDeviceState = 2;
    dataStructInterface.helpExpIndex[0]  = 0;
    dataStructInterface.helpMethodIndex[0]= 0;
    dataStructInterface.closeDir        = (eeprom.closeDir != 0xff) ? eeprom.closeDir : 0; //首次烧写默认关方向为顺时针
    dataStructInterface.speed_close     = (eeprom.speed_close != 0xff) ? eeprom.speed_close : rang1; //首次烧写默认转速最小档位
    dataStructInterface.speed_open      = (eeprom.speed_open != 0xff) ? eeprom.speed_open : rang1;   //首次烧写默认转速最小档位
    dataStructInterface.endPosClose     = (eeprom.endPosClose != 0xff) ? eeprom.endPosClose : END_POS_CLOSE_MIN;//首次烧写默认关末端范围为0-2
	dataStructInterface.endPosOpen      = (eeprom.endPosOpen != 0xff) ? eeprom.endPosOpen : END_POS_OPEN_MAX;//首次烧写默认开末端范围为98-100
    dataStructInterface.moment_close    = (eeprom.moment_close != 0xff) ? eeprom.moment_close : MOMENT_MIN;//首次烧写默认转矩最小档位
    dataStructInterface.moment_open     = (eeprom.moment_open != 0xff) ? eeprom.moment_open : MOMENT_MIN;  //首次烧写默认转矩最小档位
    dataStructInterface.openOffMode     = (eeprom.openOffMode != 0xff) ? eeprom.openOffMode : 0;//首次烧写默认行程关断
	dataStructInterface.closeOffMode    = (eeprom.closeOffMode != 0xff) ? eeprom.closeOffMode : 0;//首次烧写默认行程关断
    dataStructInterface.moment_overtimes = 1;
	dataStructInterface.emg_speed_close  = (eeprom.emg_speed_close != 0xff) ? eeprom.emg_speed_close : rang4;  //紧急关速度，首次烧写默认rang4
	dataStructInterface.emg_speed_open   = (eeprom.emg_speed_open != 0xff) ? eeprom.emg_speed_open : rang4;   //紧急开速度，首次烧写默认rang4
    dataStructInterface.gearType         = 0;
    dataStructInterface.ctrlMode         = (eeprom.ctrlMode != 0xff) ? eeprom.ctrlMode : 3;  //控制模式，首次烧写默认为模拟量位置控制
    dataStructInterface.rmtChoose        = (eeprom.rmtChoose != 0xff) ? eeprom.rmtChoose : 0;  //远程再选择，仅显示用，默认为无效
    dataStructInterface.krInput          = eeprom.krInput_save;     //开关量输入，常开/闭节点，默认值暂不处理
    dataStructInterface.emgInput         = eeprom.emgInput;         //安全--紧急输入，常开/闭节点，默认值暂不处理
		
    strcpy(menuUserManagCn[1],userNameCn[g_authority]);
    strcpy(menuUserManagEn[1],userNameEn[g_authority]);
    if(AUTHRITY_OBSERVER == g_authority)
    {
        strcpy(menuUserManagCn[2],"                         ");
        strcpy(menuUserManagCn[3],"                         ");
        strcpy(menuUserManagEn[2],"                         ");
        strcpy(menuUserManagEn[3],"                         ");
        menuUserManagSettings[3] = MENU_SETTING_TITLE;
    }
    else
    {
        strcpy(menuUserManagCn[2],menuUserManagCnBak[2]);
        strcpy(menuUserManagCn[3],menuUserManagCnBak[3]);
        strcpy(menuUserManagEn[2],menuUserManagCnBak[2]);
        strcpy(menuUserManagEn[3],menuUserManagCnBak[3]);
        menuUserManagSettings[3] = MENU_SETTING_CONTENT;
    }
    
    dataStructInterface.krOutputSel1[1]=eeprom.out1;
    dataStructInterface.krOutputSel1[2]=eeprom.out2;
    dataStructInterface.krOutputSel1[3]=eeprom.out3;
    dataStructInterface.krOutputSel1[4]=eeprom.out4;
    dataStructInterface.krOutputSel1[5]=eeprom.out5;
    dataStructInterface.krOutputSel1[6]=eeprom.out6;
    dataStructInterface.krOutputSel1[7]=eeprom.out7;
    dataStructInterface.krOutputSel1[8]=eeprom.out8;
		
    dataStructInterface.krOutputSel2[1]=eeprom.out_of_1;
    dataStructInterface.krOutputSel2[2]=eeprom.out_of_2;
    dataStructInterface.krOutputSel2[3]=eeprom.out_of_3;
    dataStructInterface.krOutputSel2[4]=eeprom.out_of_4;
    dataStructInterface.krOutputSel2[5]=eeprom.out_of_5;
    dataStructInterface.krOutputSel2[6]=eeprom.out_of_6;
    dataStructInterface.krOutputSel2[7]=eeprom.out_of_7;
    dataStructInterface.krOutputSel2[8]=eeprom.out_of_8;
    if(dataStructInterface.closeDir ==0)
    {
        motorset.DIR=1;
    }else
    if(dataStructInterface.closeDir ==1)
    {
        motorset.DIR=2;
    }
}

void _InterDataRefresh(void)
{
    char str[MAX_INFO_CHAR];
    
    //专家-就地模式，设定主菜单下第三个控件，即“末端位置”可选/设定参数菜单下“阀门参数/控制参数”可选
    if((DEVICE_STATE_LOCAL == g_deviceState) && (3 == flag_figures.user)) 
    {
        menuMainSettings[3] = MENU_SETTING_CONTENT;
        menuParaSet[1]      = MENU_SETTING_CONTENT;
        menuParaSet[2]      = MENU_SETTING_CONTENT;
    }
    else
    {
        menuMainSettings[3] = MENU_SETTING_TITLE;
        menuParaSet[1]      = MENU_SETTING_TITLE;
        menuParaSet[2]      = MENU_SETTING_TITLE;
    }
	                 
    sprintf(str,"                  %d rpm ",dataStructInterface.speed_close );
    strcpy(menuObStatusCn[1],str);
    switch(flag_figures.user)
    {                           
        case 1: {sprintf(str,"                     操作员");
                        strcpy(menuUserManagCn[1],str);
                        strcpy(menuUserManagEn[1],str);
                        }break;
                             
        case 2: {sprintf(str,"                       监察");
                        strcpy(menuUserManagCn[1],str);
                        strcpy(menuUserManagEn[1],str);
                        }break;
                             
        case 3: {sprintf(str,"                       专家");
                        strcpy(menuUserManagCn[1],str);
                        strcpy(menuUserManagEn[1],str);
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
    
                
    sprintf(str,"                     %d  ",states.Coils_temp);
    strcpy(menuObStatusCn[6],str);
    strcpy(menuObStatusEn[6],str);
                    
    sprintf(str,"                     %d ",states.Ele_temp);
    strcpy(menuObStatusCn[8],str);
    strcpy(menuObStatusEn[8],str);
    
    sprintf(str," 定位              %d.%d %% ",key_mlx90363.Integer_3,key_mlx90363.decimal_3);
    strcpy(menuObStatusCn[13],str);
    strcpy(menuObStatusEn[13],str);
                
    sprintf(str,"                   %.1f A ",powerboard.lcd_current);
    strcpy(menuObStatusCn[17],str);
    strcpy(menuObStatusEn[17],str);
                    
    sprintf(str,"                   %d V ",(int)powerboard.lcd_voltage);
    strcpy(menuObStatusCn[19],str);
    strcpy(menuObStatusEn[19],str);
    
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
    if(ai_o420.flag_mode1==1)
    {
        sprintf(str,"       持续节点 ");
        strcpy(infoWinMainList0CN[1],str);
        strcpy(infoWinMainList0EN[1],str);
    }else
    if(ai_o420.flag_mode2==1)
    {
        sprintf(str,"       脉冲节点 ");
        strcpy(infoWinMainList0CN[1],str);
        strcpy(infoWinMainList0EN[1],str);
    }else
    if(ai_o420.flag_mode3==1)
    {
        sprintf(str,"       比例控制 ");
        strcpy(infoWinMainList0CN[1],str);
        strcpy(infoWinMainList0EN[1],str);
    }else
    if(ai_o420.flag_mode4==1)
    {
        sprintf(str,"       位置控制器 ");
        strcpy(infoWinMainList0CN[1],str);
        strcpy(infoWinMainList0EN[1],str);
    }
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
    if(dataStructInterface.showDirect==1)
    {                       
        sprintf(str,"                   180度 ");
        strcpy(menuParaSysShowDirCn[1],str);
        strcpy(menuParaSysShowDirEn[1],str);
    }else
    if(dataStructInterface.showDirect==0)
    {    			
        sprintf(str,"                     0度 ");
        strcpy(menuParaSysShowDirCn[1],str);
        strcpy(menuParaSysShowDirEn[1],str);
    }
                
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

}


const char * GetExpInfoPtr(unsigned char index,char LanguageIndex)
{
		const char *ptr;
    if(LANGUAGE_CN == LanguageIndex)
    {
        switch(index)
        {
            case 0: ptr=exp_cn_content0;
            break;
            case 1: ptr=exp_cn_content1;
            break;
            case 2: ptr=exp_cn_content2;
            break;
            case 3: ptr=exp_cn_content3;
            break;
            case 4: ptr=exp_cn_content4;
            break;
            default: ;
        }
    }
    else if(LANGUAGE_EN == LanguageIndex)
    {
        switch(index)
        {
            case 0: ptr=exp_en_content0;
            break;
            case 1: ptr=exp_en_content1;
            break;
            case 2: ptr=exp_en_content2;
            break;
            case 3: ptr=exp_en_content3;
            break;
            case 4: ptr=exp_en_content4;
            break;
            default: ;
        }
    }
    return ptr;
}

const char * GetHandleInfoPtr(unsigned char index,char LanguageIndex)
{
    const char *ptr;
    if(LANGUAGE_CN == LanguageIndex)
    {
        switch(index)
        {
            case 0: ptr=handle_cn_content0;
            break;
            case 1: ptr=handle_cn_content1;
            break;
            case 2: ptr=handle_cn_content2;
            break;
            case 3: ptr=handle_cn_content3;
            break;
            case 4: ptr=handle_cn_content4;
            break;
            default: ;
        }
    }
    else if(LANGUAGE_EN == LanguageIndex)
    {
        switch(index)
        {
            case 0: ptr=handle_en_content0;
            break;
            case 1: ptr=handle_en_content1;
            break;
            case 2: ptr=handle_en_content2;
            break;
            case 3: ptr=handle_en_content3;
            break;
            case 4: ptr=handle_en_content4;
            break;
            default: ;
        }
    }

    return ptr;
}

const char infoWinMainCN[MAX_FAULT_TEXT_NUM][MAX_INFO_CHAR]={
"准备好",//查看错误
"01 手动操作",
"02 紧急操作", //"02 报告查询",
"03 运行中卡住",//"03 定值整定参数",
"04 就地操作禁止",//04 测控参数",
"05 远程调试",//"05 adi blackdsp系列",
"06 ",//"06 发电厂电气部分",
"07 ",
"08 ",
"09 ",
"10 ",
"11 电机过热",
"12 高电压",
"13 低电压",
"14 电源供电错误",
"15 ",
"16 ",
"17 ",
"18 ",
"19 ",
"20 ",
"21 运行时间故障",
"22 ",
"23 ",
"24 ",
"25 ",
"26 ",
"27 ",
"28 ",
"29 ",
"30 ",
"31 设定末端位置",
"32 模拟量输入通道1故障",
"33 总线故障",
"34 无信号-位置保持",
"35 无信号-紧急位置",
"36 保持实际过程值位置",
"37 移动到固定的设定值",
"38 模拟量输入通道2故障",
"39 现场总线FO故障",
"40 ",
"41 电机测温回路开路",
"42 电位器开路",
"43 绝对编码器开路",
"44 超出末端位置范围",
"45 传感器无静态信号",
"46 模拟量附加模块",
"47 ",
"48 模拟量输出2故障",
"49 模拟量输出2无信号",
"50 硬件故障",
"51 变频器故障",
"52 ",
"53 ",
"54 ",
"55 ",
"56 ",
"57 ",
"58 ",
"59 ",
"60 蓝牙故障",
"61 电子单元测温故障",
"62 位置编码器故障",
"63 "
};

const char infoWinMainEN[MAX_FAULT_TEXT_NUM][MAX_INFO_CHAR]={
"00 information Err0",
"01 information Err1",
"02 information Err2",
"03 information Err3",
"04 information Err4",
"05 adi blackdsp",
"06 information Err5",
"07 information Err6",
"08 ",
"09 ",
"10 ",
"11 ",
"12 ",
"13 ",
"14 ",
"15 ",
"16 ",
"17 ",
"18 ",
"19 ",
"20 ",
"21 ",
"22 ",
"23 ",
"24 ",
"25 ",
"26 ",
"27 ",
"28 ",
"29 ",
"30 ",
"31 ",
"32 ",
"33 ",
"34 ",
"35 ",
"36 ",
"37 ",
"38 ",
"39 ",
"40 ",
"41 ",
"42 ",
"43 ",
"44 ",
"45 ",
"46 ",
"47 ",
"48 ",
"49 ",
"50 ",
"51 变频器故障",
"52 ",
"53 ",
"54 ",
"55 ",
"56 ",
"57 ",
"58 ",
"59 ",
"60 ",
"61 ",
"62 ",
"63"
};

char infoWinMainList0CN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"  就地参数",
"        持续结点",
"        关闭"
};


 char infoWinMainList0EN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"local para",
"        Cont node",
"        off"
};

 char infoWinMainListCN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"  控制模式",
"  语言",
"  主菜单"
};

char infoWinMainListEN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"ctrl mod",
"language",
"main menu"
};

 char infoDeviceStateCN[DEVICE_STATE_INFO_NUM][MAX_INFO_CHAR]={
"               装置准备好",
"           装置没有准备好",
"             装置出现故障"
};

char infoDeviceStateEN[DEVICE_STATE_INFO_NUM][MAX_INFO_CHAR]={
"             device ready",
"         device not ready",
"             device error"
};

char infoTitleCN[DEVICE_TITLE_INFO_NUM][MAX_INFO_CHAR]={
"执行机构",
"装置故障"
};

char infoTitleEN[DEVICE_TITLE_INFO_NUM][MAX_INFO_CHAR]={
"actuator",
"plant failure"
};


const char exp_cn_content0[]={"\
                         \
                         \
          解释1:         \
执行机构准备好，可以操作 \
"};

const char exp_cn_content1[]={"\
                         \
                         \
          解释2:         \
执行机构准备好，可以操作 \
"};

const char exp_cn_content2[]={"\
                         \
                         \
   解释3:         \
执行机构准备好，可以操作 \
"};

const char exp_cn_content3[]={"\
                         \
                         \
          解释4:         \
执行机构准备好，可以操作 \
"};

const char exp_cn_content4[]={"\
                         \
                         \
          解释5:         \
执行机构准备好，可以操作 \
"};

const char exp_en_content0[]={"\
                         \
                         \
          explan1:       \
执行机构准备好，可以操作 \
"};

const char exp_en_content1[]={"\
                         \
                         \
          explan2:       \
执行机构准备好，可以操作 \
"};

const char exp_en_content2[]={"\
                         \
                         \
          explan3:       \
执行机构准备好，可以操作 \
"};

const char exp_en_content3[]={"\
                         \
                         \
          explan4:       \
执行机构准备好，可以操作 \
"};

const char exp_en_content4[]={"\
                         \
                         \
          explan5:       \
执行机构准备好，可以操作 \
"};

const char handle_cn_content0[]={"\
     可能的处理方法1:    \
增大或减小电流，检查接线 \
                         \
                         \
"};

const char handle_cn_content1[]={"\
     可能的处理方法2:    \
增大或减小电流，检查接线 \
                         \
                         \
"};

const char handle_cn_content2[]={"\
     可能的处理方法3:    \
增大或减小电流，检查接线 \
                         \
                         \
"};

const char handle_cn_content3[]={"\
     可能的处理方法4:    \
增大或减小电流，检查接线 \
                         \
                         \
"};

const char handle_cn_content4[]={"\
     可能的处理方法5:    \
增大或减小电流，检查接线 \
                         \
                         \
"};


const char handle_en_content0[]={"\
          method1:       \
增大或减小电流，检查接线 \
                         \
                         \
"};

const char handle_en_content1[]={"\
          method2:       \
增大或减小电流，检查接线 \
                         \
                         \
"};

const char handle_en_content2[]={"\
          method3:       \
增大或减小电流，检查接线 \
                         \
                         \
"};

const char handle_en_content3[]={"\
          method4:       \
增大或减小电流，检查接线 \
                         \
                         \
"};

const char handle_en_content4[]={"\
          method5:       \
增大或减小电流，检查接线 \
                         \
                         \
"};


 char menuMainCn[MAIN_MENU_NUM][MAX_INFO_CHAR]={
"用户管理",
"观察",
"诊断",
"末端位置                 ",
"参数                     ",
"力矩曲线                 ",
"与系统有关的设定         "
};

 char menuMainEn[MAIN_MENU_NUM][MAX_INFO_CHAR]={
"user management",
"E观察                    ",
"E诊断                    ",
"E末端位置                ",
"E参数                    ",
"E力矩曲线                ",
"E与系统有关的设定        "
};
 
unsigned short menuMainSettings[MAIN_MENU_NUM]={MENU_SETTING_CONTENT,
                                                MENU_SETTING_CONTENT,
                                                MENU_SETTING_CONTENT,
                                                MENU_SETTING_TITLE, 
                                                MENU_SETTING_CONTENT,
                                                MENU_SETTING_CONTENT,
                                                MENU_SETTING_CONTENT};



char menuUserManagCn[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"当前用户            ",
"              操作员",
"管理/更改密码                ",
"             更改密码"
};

char menuUserManagEn[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"Current user             ",
"                    handl",
"manage                   ",
"          Change password"
};

char menuUserManagCnBak[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"当  前  用  户                 ",
"                     操作员",
"管理                           ",
"                   更改密码"
};

char menuUserManagEnBak[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"Current user             ",
"                    handl",
"manage                   ",
"          Change password"
};

unsigned short menuUserManagSettings[MENU_USER_MANAG_NUM]={MENU_SETTING_TITLE,MENU_SETTING_CONTENT,MENU_SETTING_TITLE,MENU_SETTING_CONTENT};


 char menuCurUserCn[MENU_CUR_USER_NUM][MAX_INFO_CHAR]={
"退出                     ",
"  观察员                 ",
"切换用户至               ",
"  操作员                 ",
"  监察员                 ",
"  专家                   ",
"  服务                   ",
"  工厂服务               "
};

 char menuCurUserEn[MENU_CUR_USER_NUM][MAX_INFO_CHAR]={
"exit                     ",
"  观察员                 ",
"切换用户至               ",
"  操作员                 ",
"  监察员                 ",
"  专家                   ",
"  服务                   ",
"  工厂服务               "
};

unsigned short menuCurUserSettings[MENU_CUR_USER_NUM]={MENU_SETTING_TITLE,
                                                      MENU_SETTING_CONTENT,
                                                      MENU_SETTING_TITLE,
                                                      MENU_SETTING_CONTENT,
                                                      MENU_SETTING_CONTENT,
                                                      MENU_SETTING_CONTENT,
                                                      MENU_SETTING_CONTENT,
                                                      MENU_SETTING_CONTENT};

char userNameCn[AUTHRITY_NUM][MAX_INFO_CHAR]={
"                   观察员",
"                   操作员",
"                   监察员",
"                     专家",
"                     服务",
"                 工厂服务"
};

char userNameEn[AUTHRITY_NUM][MAX_INFO_CHAR]={
"                  E观察员",
"                  E操作员",
"                  E监察员",
"                    E专家",
"                    E服务",
"                E工厂服务"
};


char menu_test_sel_cn[][MAX_INFO_CHAR]={
"退出                     ",
"  观察员                 ",
"切换用户至               ",
"  操作员                 ",
"  监察员                 ",
"  专家                   ",
"  服务                   ",
"  工厂服务               ",
"  工厂服务2              ",
"  工厂服务3              "
};

char menu_test_sel_en[][MAX_INFO_CHAR]={
"exit                     ",
"  观察员                 ",
"切换用户至               ",
"  操作员                 ",
"  监察员                 ",
"  专家                   ",
"  服务                   ",
"  工厂服务               ",
"  工厂服务2              ",
"  工厂服务3              "
};

unsigned short menu_test_sel_settings[]={MENU_SETTING_TITLE,
                                        MENU_SETTING_CONTENT,
                                        MENU_SETTING_TITLE,
                                        MENU_SETTING_CONTENT,
                                        MENU_SETTING_CONTENT,
                                        MENU_SETTING_CONTENT,
                                        MENU_SETTING_CONTENT,
                                        MENU_SETTING_CONTENT,
                                        MENU_SETTING_CONTENT,
                                        MENU_SETTING_CONTENT};

char menu_test_sel_cn2[][MAX_INFO_CHAR]={
"  退出                   ",
"  观察员                 ",
"  切换用户至             ",
"  操作员                 ",
"  监察员                 "
};

char menu_test_sel_en2[][MAX_INFO_CHAR]={
"  exit                   ",
"  观察员                 ",
"  切换用户至             ",
"  操作员                 ",
"  监察员                 "
};

unsigned short menu_test_sel_settings2[]={MENU_SETTING_CONTENT,
                                        MENU_SETTING_CONTENT,
                                        MENU_SETTING_CONTENT,
                                        MENU_SETTING_CONTENT,
                                        MENU_SETTING_CONTENT};

 char info_menu_save_CN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"          保存           ",
"          取消           "
};

 char info_menu_save_EN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"          Save           ",
"         Cancel          "
};



char menuObCn[MENU_OB_SET_NUM][MAX_INFO_CHAR]={
"电子单元铭牌             ",
"输入和输出               ",
"状态                     "
};

char menuObEn[MENU_OB_SET_NUM][MAX_INFO_CHAR]={
"电子单元铭牌E            ",
"输入和输出E              ",
"状态E                    "
};

unsigned short menuObSet[MENU_OB_SET_NUM]={MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT};


char menuObNamePlateCn[MENU_OB_NAMEPLATE_NUM][MAX_INFO_CHAR]={
"标签                     ",
"                    Motor",
"型号                     ",
"       2SA7321-5EE00-4BB4",
"设备                     ",
"序列号                   ",
"            6800190926103"
};

char menuObNamePlateEn[MENU_OB_NAMEPLATE_NUM][MAX_INFO_CHAR]={
"E标签                    ",
"                    Motor",
"E型号                    ",
"       2SA7321-5EE00-4BB4",
"E设备                    ",
"E序列号                  ",
"            6800190926103"
};

unsigned short menuObNamePlateSet[MENU_OB_NAMEPLATE_NUM]={MENU_SETTING_TITLE,
	                                                       MENU_SETTING_CONTENT,
	                                                       MENU_SETTING_TITLE,
                                                         MENU_SETTING_CONTENT,
                                                         MENU_SETTING_CONTENT,
                                                         MENU_SETTING_TITLE,
                                                         MENU_SETTING_CONTENT};

char menuObPlateDeviceCn[MENU_OB_NAMEPLATE_DEVICE_NUM][MAX_INFO_CHAR]={
"                   SIPOS7",
"           多回转执行机构",
"                   步进型",
"最小关断力矩      37.5 Nm",
"最大关断力矩       125 Nm",
"法兰型号    ISO 5210:F10 ",
"    输入输出类型:B3型轴承",
"最小转速           20 rpm",
"最大转速          160 rpm",
"供电电源:3~ 380 - 480 VAC",
"       非侵入式位置编码器",
" 不带机械式就地位置指示器",
"       不带机阀杆保护套管",
"                   专业型",
"                 继电器板",
"               位置控制器",
"                 圆形插头"
};

char menuObPlateDeviceEn[MENU_OB_NAMEPLATE_DEVICE_NUM][MAX_INFO_CHAR]={
"                   SIPOS7",
"           多回转执行机构",
"                   步进型",
"最小关断力矩      37.5 Nm",
"最大关断力矩       125 Nm",
"法兰型号    ISO 5210:F10 ",
"    输入输出类型:B3型轴承",
"最小转速           20 rpm",
"最大转速          160 rpm",
"供电电源:3~ 380 - 480 VAC",
"       非侵入式位置编码器",
" 不带机械式就地位置指示器",
"       不带机阀杆保护套管",
"                   专业型",
"                 继电器板",
"               位置控制器",
"                 圆形插头"
};

unsigned short menuObPlateDeviceSet[MENU_OB_NAMEPLATE_DEVICE_NUM]={MENU_SETTING_CONTENT,
	                                                                MENU_SETTING_CONTENT,
	                                                                MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT,
                                                                  MENU_SETTING_CONTENT};

char menuObInOutPutCn[MENU_OB_INOUTPUT_NUM][MAX_INFO_CHAR]={
"开关量输入               ",
"开关量输出               ",
"模拟量输入，输出         "
};

char menuObInOutPutEn[MENU_OB_INOUTPUT_NUM][MAX_INFO_CHAR]={
"开关量输入E              ",
"开关量输出E              ",
"模拟量输入，输出E        "
};

unsigned short menuObInOutPutSet[MENU_OB_INOUTPUT_NUM]={MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT};


char 	menuObKrInputCn[MENU_OB_KRINPUT_NUM][MAX_INFO_CHAR]={
"开关量输入信号 关     低1",
"开关量输入信号 开     低1",
"开关量输入信号 停     低1",
"开关量输入信号 紧急   低1",
"开关量输入信号 模式   低1"
};
char menuObKrInputCn_L1[MENU_OB_KRINPUT_NUM][MAX_INFO_CHAR]={
"开关量输入信号 关     低1",
"开关量输入信号 开     低1",
"开关量输入信号 停     低1",
"开关量输入信号 紧急   低1",
"开关量输入信号 模式   低1"
};
char menuObKrInputCn_H1[MENU_OB_KRINPUT_NUM][MAX_INFO_CHAR]={
"开关量输入信号 关     高3",
"开关量输入信号 开     高3",
"开关量输入信号 停     高3",
"开关量输入信号 紧急   高3",
"开关量输入信号 模式   高3"
};

char menuObKrInputEn[MENU_OB_KRINPUT_NUM][MAX_INFO_CHAR]={
"开关量输入信号 关     低 ",
"开关量输入信号 开     低 ",
"开关量输入信号 停     低 ",
"开关量输入信号 紧急   低 ",
"开关量输入信号 模式   低 "
};

unsigned short menuObKrInputSet[MENU_OB_KRINPUT_NUM]={MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT};


char menuObKrOutputCn[MENU_OB_KROUTPUT_NUM][MAX_INFO_CHAR]={
"输出1                 低 ",
"输出2                 高 ",
"输出3                 低 ",
"输出4                 高 ",
"输出5                 低 ",
"输出6                 高 ",
"输出7                 低 ",
"输出8                 高 "
};

char menuObKrOutputEn[MENU_OB_KROUTPUT_NUM][MAX_INFO_CHAR]={
"输出1E                低 ",
"输出2E                高 ",
"输出3E                低 ",
"输出4E                高 ",
"输出5E                低 ",
"输出6E                高 ",
"输出7E                低 ",
"输出8E                高 "
};

unsigned short menuObKrOutputSet[MENU_OB_KROUTPUT_NUM]={MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT};

char menuObAnalogCn[MENU_OB_ANALOG_NUM][MAX_INFO_CHAR]={
"模拟量输入AI1     0.0 mA ",
"模拟量输出AO1     3.9 mA "
};

char menuObAnalogEn[MENU_OB_ANALOG_NUM][MAX_INFO_CHAR]={
"E模拟量输入AI1    0.0 mA ",
"E模拟量输出AO1    3.9 mA "
};

unsigned short menuObAnalogSet[MENU_OB_ANALOG_NUM]={MENU_SETTING_CONTENT,
                                          MENU_SETTING_CONTENT};

char menuObStatusCn[MENU_OB_STATUS_NUM][MAX_INFO_CHAR]={
"当前速度                 ",
"                   0 rpm ",
"力矩开关动作             ",
"                    无效 ",
"                    无效 ",
"电机温度                 ",
"                     31  ",
"电子单元温度             ",
"                     40  ",
"中间节点                 ",
"                  有效 ",
"                  无效 ",
"实际值                   ",
" 定位              0.0 % ",
"电机质保                 ",
"                    可用 ",
"电机电流                 ",
"                   0.0 A ",
"直流母线电压             ",
"                   544 V "
};

char menuObStatusEn[MENU_OB_STATUS_NUM][MAX_INFO_CHAR]={
"当前速度                 ",
"                   0 rpm ",
"力矩开关动作             ",
"                    无效 ",
"                    无效 ",
"电机温度                 ",
"                     31  ",
"电子单元温度             ",
"                     40  ",
"中间节点                 ",
"                    有效 ",
"                    无效 ",
"实际值                   ",
" 定位              0.0 % ",
"电机质保                 ",
"                    可用 ",
"电机电流                 ",
"                   0.0 A ",
"直流母线电压             ",
"                   544 V "
};

unsigned short menuObStatusSet[MENU_OB_STATUS_NUM]={MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT};


char menuDiagnoseCn[MENU_DIAGNOSE_NUM][MAX_INFO_CHAR]={
"执行机构运行数据         ",
" 开关次数              0 ",
" 开关频率(次/小时)     0 ",
" 力矩关断次数          0 ",
" 行程关断次数          0 ",
" 电机运行小时数        0 ",
" 电子单元运行小时数    0 ",
" 运行时间/小时         0 ",
"阀门维护权限             ",
" 开关次数              0 ",
" 力矩关断次数          0 ",
" 电机运行小时数        0 ",
"阀门维护                 ",
"                   不需要",
"复位维护信号             "
};

char menuDiagnoseEn[MENU_DIAGNOSE_NUM][MAX_INFO_CHAR]={
"执行机构运行数据E        ",
" 开关次数             35 ",
" 开关频率(次/小时)     0 ",
" 力矩关断次数          0 ",
" 行程关断次数          0 ",
" 电机运行小时数        0 ",
" 电子单元运行小时数    0 ",
" 运行时间/小时         0 ",
"阀门维护权限             ",
" 开关次数          30028 ",
" 力矩关断次数       3007 ",
" 电机运行小时数     2500 ",
"阀门维护                 ",
"                   不需要",
"复位维护信号             "
};

unsigned short menuDiagnoseSet[MENU_DIAGNOSE_NUM]={MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };

char menuParaCn[MENU_PARA_NUM][MAX_INFO_CHAR]={
"外配齿轮箱               ",
"与阀门有关参数           ",
"与控制系统有关参数       ",
"安全                     ",
"软件功能                 ",
"特殊参数                 "
};

char menuParaEn[MENU_PARA_NUM][MAX_INFO_CHAR]={
"外配齿轮箱               ",
"与阀门有关参数           ",
"与控制系统有关参数       ",
"安全                     ",
"软件功能                 ",
"特殊参数                 "
};

unsigned short menuParaSet[MENU_PARA_NUM]={MENU_SETTING_CONTENT,
                                           MENU_SETTING_TITLE,
                                           MENU_SETTING_TITLE,
                                           MENU_SETTING_CONTENT,
                                           MENU_SETTING_CONTENT,
                                           MENU_SETTING_CONTENT,
                                           };

char menuGearCn[MENU_GEAR_NUM][MAX_INFO_CHAR]={
"Gear type                ",
" No additional gear      "
};

char menuGearEn[MENU_GEAR_NUM][MAX_INFO_CHAR]={
"Gear type                ",
" No additional gear      "
};

unsigned short menuGearSet[MENU_GEAR_NUM]={MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT
                                                   };

char menuGearTypeCn[MENU_GEAR_TYPE_NUM][MAX_INFO_CHAR]={
" No additional gear      ",
" Rotary gear             ",
" Part turn               ",
" Linear                  "
};

char menuGearTypeEn[MENU_GEAR_TYPE_NUM][MAX_INFO_CHAR]={
" No additional gear      ",
" Rotary gear             ",
" Part turn               ",
" Linear                  "
};

unsigned short menuGearTypeSet[MENU_GEAR_TYPE_NUM]={MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };

char menuVavleParaCn[MENU_VAVLE_PARA_NUM][MAX_INFO_CHAR]={
"关方向                   ",
"                  逆时针 ",
"转速                     ",
"                 160 rpm ",
"                  20 rpm ",
"关断模式                 ",
"            行程关断模式 ",
"            行程关断模式 ",
"关断力矩                 ",
"                  112 Nm ",
"                 37.5 Nm ",
"末端位置范围             ",
"                 0 - 2 % ",
"              98 - 100 % ",
"过力矩后的重试次数       ",
" 重试次数            3 x "
};

char menuVavleParaEn[MENU_VAVLE_PARA_NUM][MAX_INFO_CHAR]={
"关方向                   ",
"                  逆时针 ",
"转速                     ",
"                 160 rpm ",
"                  20 rpm ",
"关断模式                 ",
"            行程关断模式 ",
"            行程关断模式 ",
"关断力矩                 ",
"                  112 Nm ",
"                 37.5 Nm ",
"末端位置范围             ",
"                 0 - 2 % ",
"              98 - 100 % ",
"过力矩后的重试次数       ",
" 重试次数            3 x "
};

unsigned short menuVavleParaSet[MENU_VAVLE_PARA_NUM]={MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT
                                                   };


char menuSelCloseDirCn[MENU_CLOSE_DIR_NUM][MAX_INFO_CHAR]={
"顺时针                   ",
"逆时针                   "
};

char menuSelCloseDirEn[MENU_CLOSE_DIR_NUM][MAX_INFO_CHAR]={
"顺时针E                  ",
"逆时针E                  "
};

unsigned short menuSelCloseDirSet[MENU_CLOSE_DIR_NUM]={MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };


char menuSelOffModeCn[MENU_OFF_MODE_NUM][MAX_INFO_CHAR]={
"行程关断模式             ",
"力矩关断模式             "
};

char menuSelOffModeEn[MENU_OFF_MODE_NUM][MAX_INFO_CHAR]={
"行程关断模式             ",
"力矩关断模式             "
};

unsigned short menuSelOffModeSet[MENU_OFF_MODE_NUM]={MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };

char menuCtrlSysParaCn[MENU_CTRL_SYS_PARA_NUM][MAX_INFO_CHAR]={
"控制模式                 ",
"      开关量持续接点控制 ",
"远程再选择               ",
"       模拟量位置控制AI1 ",
"开关量输入               ",
"            常开接点(NO) ",
"Mode Input               ",
"             No Function ",
"模拟量输入AI1            ",
" 斜坡               上升 ",
" 范围          4 - 20 mA ",
"开关量输出               ",
"          开关量输出设置 ",
"模拟量输出AO1            ",
"              实际位置值 ",
" 范围          4 - 20 mA ",
" 斜坡               上升 "
};

char menuCtrlSysParaEn[MENU_CTRL_SYS_PARA_NUM][MAX_INFO_CHAR]={
"控制模式                 ",
"      开关量持续接点控制 ",
"远程再选择               ",
"       模拟量位置控制AI1 ",
"开关量输入               ",
"            常开接点(NO) ",
"Mode Input               ",
"             No Function ",
"模拟量输入AI1            ",
" 斜坡               上升 ",
" 范围          4 - 20 mA ",
"开关量输出               ",
"          开关量输出设置 ",
"模拟量输出AO1            ",
"              实际位置值 ",
" 范围          4 - 20 mA ",
" 斜坡               上升 "
};

unsigned short menuCtrlSysParaSet[MENU_CTRL_SYS_PARA_NUM]={MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };

char menuCtrlModeCn[MENU_CTRL_MODE_NUM][MAX_INFO_CHAR]={
"开关量                   ",
" 持续节点                ",
" 脉冲节点                ",
" 比例控制                ",
"模拟量                   ",
" 位置控制器              "
};

char menuCtrlModeEn[MENU_CTRL_MODE_NUM][MAX_INFO_CHAR]={
"开关量E                  ",
" 持续节点                ",
" 脉冲节点                ",
" 比例控制                ",
"模拟量                   ",
" 位置控制器              "
};

unsigned short menuCtrlModeSet[MENU_CTRL_MODE_NUM]={MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT
                                                   };

char menuRmtChoseCn[MENU_REMOTE_CHOSE_NUM][MAX_INFO_CHAR]={
"无效                     ",
"开关量                   ",
" 持续节点                ",
" 比例节点                ",
"模拟量                   ",
" 位置控制器AI1           "
};

char menuRmtChoseEn[MENU_REMOTE_CHOSE_NUM][MAX_INFO_CHAR]={
"无效E                    ",
"开关量                   ",
" 持续节点                ",
" 比例节点                ",
"模拟量                   ",
" 位置控制器AI1           "
};

unsigned short menuRmtChoseSet[MENU_REMOTE_CHOSE_NUM]={MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT
                                                   };


char menuKrInputCn[MENU_KR_INPUT_NUM][MAX_INFO_CHAR]={
"常闭接点(NC)             ",
"常开接点(NO)             "
};

char menuKrInputEn[MENU_KR_INPUT_NUM][MAX_INFO_CHAR]={
"常闭接点(NC)E            ",
"常开接点(NO)             "
};

unsigned short menuKrInputSet[MENU_KR_INPUT_NUM]={MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };


char menuModeInputCn[MENU_MODE_INPUT_NUM][MAX_INFO_CHAR]={
"Mode input               ",
" No function             ",
" Switchover lock L/R     "
};

char menuModeInputEn[MENU_MODE_INPUT_NUM][MAX_INFO_CHAR]={
"Mode input               ",
" No function             ",
" Switchover lock L/R     "
};

unsigned short menuModeInputSet[MENU_MODE_INPUT_NUM]={MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };

char menuAnologInputCn[MENU_ANOLOG_INPUT_NUM][MAX_INFO_CHAR]={
"上升                     ",
"下降                     "
};

char menuAnologInputEn[MENU_ANOLOG_INPUT_NUM][MAX_INFO_CHAR]={
"上升E                    ",
"下降                     "
};

unsigned short menuAnologInputSet[MENU_ANOLOG_INPUT_NUM]={MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };

char menuAnologInputAI1Cn[MENU_ANOLOG_INPUT_AI1_NUM][MAX_INFO_CHAR]={
"4 - 20 mA                ",
"0 - 20 mA                "
};

char menuAnologInputAI1En[MENU_ANOLOG_INPUT_AI1_NUM][MAX_INFO_CHAR]={
"4 - 20 mA                ",
"0 - 20 mA                "
};

unsigned short menuAnologInputAI1Set[MENU_ANOLOG_INPUT_AI1_NUM]={MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };


char menuKrOutputCn[MENU_KR_OUTPUT_NUM][MAX_INFO_CHAR]={
"输出1                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出2                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出3                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出4                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出5                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出6                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出7                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出8                    ",
"                    闪烁 ",
"            常开接点(NO) "
};

char menuKrOutputEn[MENU_KR_OUTPUT_NUM][MAX_INFO_CHAR]={
"输出1E                   ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出2                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出3                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出4                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出5                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出6                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出7                    ",
"                    闪烁 ",
"            常开接点(NO) ",
"输出8                    ",
"                    闪烁 ",
"            常开接点(NO) "
};
char menuKrOutputSel1Cn_1[MENU_KROUTPUT_SEL1_NUM][MAX_INFO_CHAR]={
"                     未用",
"                     全开",
"                     全关",
"             关方向过力矩",
"             开方向过力矩",
"         开或关方向过力矩",
"                     故障",
"                    闪烁 ",
"                   准备好",
"              准备好+远控",
"                     就地",
"               关中间接点",
"               开中间接点",
"             电机过热故障",
"             电机超温报警",
"             外部电压故障",
"                     维护",
"                   正在关",
"                   正在开",
"Run indication",
"Blinker + endposition CL ",
"Blinker + endposition OP "
};
unsigned short menuKrOutputSet[MENU_KR_OUTPUT_NUM]={MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };


char menuKrOutputSel1Cn[MENU_KROUTPUT_SEL1_NUM][MAX_INFO_CHAR]={
"未用                     ",
"全开                     ",
"全关                     ",
"关方向过力矩             ",
"开方向过力矩             ",
"开或关方向过力矩         ",
"故障                     ",
"闪烁                     ",
"准备好                   ",
"准备好+远控              ",
"就地                     ",
"关中间接点               ",
"开中间接点               ",
"电机过热故障             ",
"电机超温报警             ",
"外部电压故障             ",
"维护                     ",
"正在关                   ",
"正在开                   ",
"Run indication           ",
"Blinker + endposition CL ",
"Blinker + endposition OP "
};

char menuKrOutputSel1En[MENU_KROUTPUT_SEL1_NUM][MAX_INFO_CHAR]={
"未用E                    ",
"全开                     ",
"全关                     ",
"关方向过力矩             ",
"开方向过力矩             ",
"开或关方向过力矩         ",
"综合故障                 ",
"闪烁                     ",
"准备好                   ",
"准备好+远控              ",
"就地                     ",
"关中间接点               ",
"开中间接点               ",
"电机过热故障             ",
"电机温度报警             ",
"外供电源故障             ",
"维护                     ",
"正在关                   ",
"正在开                   ",
"Run indication           ",
"Blinker + endposition CL ",
"Blinker + endposition OP "
};

unsigned short menuKrOutputSel1Set[MENU_KROUTPUT_SEL1_NUM]={MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };

char menuKrOutputSel2Cn_1[MENU_KROUTPUT_SEL2_NUM][MAX_INFO_CHAR]={
"             常闭接点(NC)",
"             常开接点(NO)"
};
char menuKrOutputSel2Cn[MENU_KROUTPUT_SEL2_NUM][MAX_INFO_CHAR]={
"常闭接点(NC)             ",
"常开接点(NO)             "
};

char menuKrOutputSel2En[MENU_KROUTPUT_SEL2_NUM][MAX_INFO_CHAR]={
"常闭接点(NC)E            ",
"常开接点(NO)             "
};

unsigned short menuKrOutputSel2Set[MENU_KROUTPUT_SEL2_NUM]={MENU_SETTING_CONTENT,
                                                           MENU_SETTING_CONTENT
                                                   };

char menuAnologOutputSel1Cn[MENU_ANOOUTPUT_SEL1_NUM][MAX_INFO_CHAR]={
"实际位置值               ",
"实际过程值               "
};

char menuAnologOutputSel1En[MENU_ANOOUTPUT_SEL1_NUM][MAX_INFO_CHAR]={
"实际位置值               ",
"实际过程值E              "
};

unsigned short menuAnologOutputSel1Set[MENU_ANOOUTPUT_SEL1_NUM]={MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };


char menuAnologOutputSel2Cn[MENU_ANOOUTPUT_SEL2_NUM][MAX_INFO_CHAR]={
"4 - 20 mA                ",
"0 - 20 mA                "
};

char menuAnologOutputSel2En[MENU_ANOOUTPUT_SEL2_NUM][MAX_INFO_CHAR]={
"4 - 20 mA                ",
"0 - 20 mA                "
};

unsigned short menuAnologOutputSel2Set[MENU_ANOOUTPUT_SEL2_NUM]={MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };

char menuAnologOutputSel3Cn[MENU_ANOOUTPUT_SEL3_NUM][MAX_INFO_CHAR]={
"上升                     ",
"下降                     "
};

char menuAnologOutputSel3En[MENU_ANOOUTPUT_SEL3_NUM][MAX_INFO_CHAR]={
"上升                     ",
"下降                     "
};

unsigned short menuAnologOutputSel3Set[MENU_ANOOUTPUT_SEL3_NUM]={MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };


char menuSaftyCn[MENU_SAFTY_PARA_NUM][MAX_INFO_CHAR]={
"紧急输入                 ",
"            常开节点(NO) ",
"紧急速度                 ",
" 关               20 rpm ",
" 开               20 rpm ",
"紧急位置                 ",
"                     0 % ",
"控制源故障               ",
"                保持原位 "
};

char menuSaftyEn[MENU_SAFTY_PARA_NUM][MAX_INFO_CHAR]={
"紧急输入E                ",
"            常开节点(NO) ",
"紧急速度                 ",
" 关               20 rpm ",
" 开               20 rpm ",
"紧急位置                 ",
"                     0 % ",
"控制源故障               ",
"                保持原位 "
};

unsigned short menuSaftySet[MENU_SAFTY_PARA_NUM]={MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT
                                                   };


char menuSaftyEmInputCn[MENU_SAFTY_INPUT_NUM][MAX_INFO_CHAR]={
"常闭接点(NC)             ",
"常开接点(NO)             "
};

char menuSaftyEmInputEn[MENU_SAFTY_INPUT_NUM][MAX_INFO_CHAR]={
"常闭接点(NC)E            ",
"常开接点(NO)             "
};

unsigned short menuSaftyEmInputSet[MENU_SAFTY_INPUT_NUM]={MENU_SETTING_CONTENT,
                                                         MENU_SETTING_CONTENT
                                                        };


char menuSaftyCtlSrcFaultCn[MENU_SAFTY_CTLSRC_FAULT_NUM][MAX_INFO_CHAR]={
"保持原位                 ",
"运行到“紧急”位置         "
};

char menuSaftyCtlSrcFaultEn[MENU_SAFTY_CTLSRC_FAULT_NUM][MAX_INFO_CHAR]={
"保持原位                 ",
"运行到“紧急”位置         "
};

unsigned short menuSaftyCtlSrcFaultSet[MENU_SAFTY_CTLSRC_FAULT_NUM]={MENU_SETTING_CONTENT,
                                                         MENU_SETTING_CONTENT
                                                        };


char menuSoftFunCn[MENU_SOFTFUN_NUM][MAX_INFO_CHAR]={
"激活软件功能             ",
"位置控制器               ",
"比例控制                 "
};

char menuSoftFunEn[MENU_SOFTFUN_NUM][MAX_INFO_CHAR]={
"激活软件功能             ",
"位置控制器               ",
"比例控制                 "
};

unsigned short menuSoftFunSet[MENU_SOFTFUN_NUM]={MENU_SETTING_CONTENT,
                                                         MENU_SETTING_CONTENT,
                                                         MENU_SETTING_CONTENT
                                                        };


char menuSoftFunActCn[MENU_SOFTFUN_ACT_NUM][MAX_INFO_CHAR]={
"位置控制器               ",
"                  被激活 ",
"定位时间曲线功能         ",
"                输入密码 ",
"模拟量控制速度功能       ",
"                输入密码 ",
"用户特殊软件功能代码     ",
"                输入密码 "
};

char menuSoftFunActEn[MENU_SOFTFUN_ACT_NUM][MAX_INFO_CHAR]={
"位置控制器E              ",
"                  被激活 ",
"定位时间曲线功能         ",
"                输入密码 ",
"模拟量控制速度功能       ",
"                输入密码 ",
"用户特殊软件功能代码     ",
"                输入密码 "
};

unsigned short menuSoftFunActSet[MENU_SOFTFUN_ACT_NUM]={MENU_SETTING_TITLE,
	                                                       MENU_SETTING_CONTENT,
	                                                       MENU_SETTING_TITLE,
                                                         MENU_SETTING_CONTENT,
                                                         MENU_SETTING_TITLE,
                                                         MENU_SETTING_CONTENT,
                                                         MENU_SETTING_TITLE,
                                                         MENU_SETTING_CONTENT
                                                        };


char menuSoftFunPosCtlCn[MENU_SOFTFUN_POSCTL_NUM][MAX_INFO_CHAR]={
"给定值                   ",
"                    线性 ",
"死区                     ",
"                    最小 ",
"                    最大 "
};

char menuSoftFunPosCtlEn[MENU_SOFTFUN_POSCTL_NUM][MAX_INFO_CHAR]={
"给定值                   ",
"                    线性 ",
"死区                     ",
"                    最小 ",
"                    最大 "
};

unsigned short menuSoftFunPosCtlSet[MENU_SOFTFUN_POSCTL_NUM]={MENU_SETTING_TITLE,
	                                                       MENU_SETTING_CONTENT,
	                                                       MENU_SETTING_TITLE,
                                                         MENU_SETTING_CONTENT,
                                                         MENU_SETTING_CONTENT
                                                        };

char menuSoftFunPosCtlSetPointCn[MENU_SOFTFUN_POSCTL_SETPOINT_NUM][MAX_INFO_CHAR]={
"给定值                   ",
" 线性                    ",
" 等百分比                ",
" 快开                    "
};

char menuSoftFunPosCtlSetPointEn[MENU_SOFTFUN_POSCTL_SETPOINT_NUM][MAX_INFO_CHAR]={
"给定值                   ",
" 线性                    ",
" 等百分比                ",
" 快开                    "
};

unsigned short menuSoftFunPosCtlSetPointSet[MENU_SOFTFUN_POSCTL_SETPOINT_NUM]={MENU_SETTING_TITLE,
	                                                       MENU_SETTING_CONTENT,
                                                         MENU_SETTING_CONTENT,
                                                         MENU_SETTING_CONTENT
                                                        };

unsigned char menuMinPercentage[MAX_INFO_CHAR]="0.0 %";
unsigned char menuMaxPercentage[MAX_INFO_CHAR]="2.5 %";
unsigned char menuPercentage0[MAX_INFO_CHAR]="0.0 %";
unsigned char menuPercentage100[MAX_INFO_CHAR]="100.0 %";
unsigned char menuTemp0[MAX_INFO_CHAR]="0 °C";
unsigned char menuTemp155[MAX_INFO_CHAR]="155 °C";
unsigned char menudata0[MAX_INFO_CHAR]="0";
unsigned char menudata2500[MAX_INFO_CHAR]="2500";
unsigned char menudata20000[MAX_INFO_CHAR]="20000";
unsigned char menudata30000[MAX_INFO_CHAR]="30000";
unsigned char menuSecondD1[MAX_INFO_CHAR]="0.1 秒";
unsigned char menuSecond2D0[MAX_INFO_CHAR]="2 秒";
unsigned char menuPercentage00[MAX_INFO_CHAR]="0 %";
unsigned char menuPercentage250[MAX_INFO_CHAR]="250 %";
unsigned char menuSecond0[MAX_INFO_CHAR]="0 秒";
unsigned char menuSecond25[MAX_INFO_CHAR]="25 秒";
unsigned char menuSecond25D5[MAX_INFO_CHAR]="25.5 秒";
unsigned char menuSecond6553[MAX_INFO_CHAR]="6553 秒";
unsigned char menumA0[MAX_INFO_CHAR]="0 mA";
unsigned char menumA3D6[MAX_INFO_CHAR]="3.6 mA";
unsigned char menumA22[MAX_INFO_CHAR]="22 mA";
unsigned char menumA24[MAX_INFO_CHAR]="24 mA";


char menuSoftFunRatioCtlCn[MENU_SOFTFUN_RATIOCTL_NUM][MAX_INFO_CHAR]={
"持续时间                 ",
"                自动检测 ",
"自动检测                 ",
" 开持续时间      30.3 秒 ",
" 关持续时间       4.3 秒 ",
"用户自定义               ",
" 开持续时间       0.0 秒 ",
" 关持续时间       0.0 秒 "
};

char menuSoftFunRatioCtlEn[MENU_SOFTFUN_RATIOCTL_NUM][MAX_INFO_CHAR]={
"持续时间                 ",
"                自动检测 ",
"自动检测                 ",
" 开持续时间      30.3 秒 ",
" 关持续时间       4.3 秒 ",
"用户自定义               ",
" 开持续时间       0.0 秒 ",
" 关持续时间       0.0 秒 "
};

unsigned short menuSoftFunRatioCtlSet[MENU_SOFTFUN_RATIOCTL_NUM]={MENU_SETTING_TITLE,
	                                                       MENU_SETTING_CONTENT,
	                                                       MENU_SETTING_TITLE,
                                                         MENU_SETTING_CONTENT,
                                                         MENU_SETTING_CONTENT,
                                                         MENU_SETTING_TITLE,
                                                         MENU_SETTING_CONTENT,
                                                         MENU_SETTING_CONTENT
                                                        };


char SelSoftFunRatioCtlCn[SEL_SOFTFUN_RATIOCTL_NUM][MAX_INFO_CHAR]={
"持续时间                 ",
" 自动检测                ",
" 用户自定义              "
};

char SelSoftFunRatioCtlEn[SEL_SOFTFUN_RATIOCTL_NUM][MAX_INFO_CHAR]={
"持续时间E                ",
" 自动检测                ",
" 用户自定义              "
};

unsigned short SelSoftFunRatioCtlSet[SEL_SOFTFUN_RATIOCTL_NUM]={MENU_SETTING_TITLE,
	                                                       MENU_SETTING_CONTENT,
                                                         MENU_SETTING_CONTENT
                                                        };

char menuSpeParaCn[MENU_SPEPARA_NUM][MAX_INFO_CHAR]={
"标签                     ",
"                 LMMMMMMM",
"分体安装                 ",
"    没有或长度小于等于10m",
"中间节点                 ",
" 关                   0% ",
" 开                 100% ",
"电机                     ",
" 电机加热           关闭 ",
" 电机过热报警      135 ° ",
" 电机过热保护       打开 ",
"维护间隔                 ",
" 开关次数(以千计)     30 ",
" 力矩关断次数       3000 ",
" 电机运行小时数     2500 ",
"检查维护数据             ",
"                    打开 ",
"关紧功能                 ",
"                    打开 ",
"上升时间                 ",
"                  0.5 秒 ",
"直流制动%                ",
"                     0 % ",
"断电延迟                 ",
"                  6.0 秒 ",
"带力矩测量的法兰         ",
"                  不可用 ",
"Threshold open circuit an",
" Lower threshold  3.6 mA ",
" Upper threshold 21.0 mA ",
"Test operation           ",
" Test operation     关闭 ",
" Runtime CLOSE     30 秒 ",
" Pause CLOSE       90 秒 ",
" Runtime OPEN      30 秒 ",
" Pause OPEN        90 秒 ",
"Limitation DC-link vol   ",
"                    打开 ",
"Runtime monitoring       ",
"                    打开 ",
"末端位置速度             ",
"                  Mormal ",
"Autom TL adapt. end pos  ",
"                    打开 ",
"DCS Acceptance time      ",
"                 25.5 秒 "
};

char menuSpeParaEn[MENU_SPEPARA_NUM][MAX_INFO_CHAR]={
"标签                     ",
"                 LMMMMMMM",
"分体安装                 ",
"    没有或长度小于等于10m",
"中间节点                 ",
" 关                   0% ",
" 开                 100% ",
"电机                     ",
" 电机加热           关闭 ",
" 电机过热报警      135 ° ",
" 电机过热保护       打开 ",
"维护间隔                 ",
" 开关次数(以千计)     30 ",
" 力矩关断次数       3000 ",
" 电机运行小时数     2500 ",
"检查维护数据             ",
"                    打开 ",
"关紧功能                 ",
"                    打开 ",
"上升时间                 ",
"                  0.5 秒 ",
"直流制动%                ",
"                     0 % ",
"断电延迟                 ",
"                  6.0 秒 ",
"带力矩测量的法兰         ",
"                  不可用 ",
"Threshold open circuit an",
" Lower threshold  3.6 mA ",
" Upper threshold 21.0 mA ",
"Test operation           ",
" Test operation     关闭 ",
" Runtime CLOSE     30 秒 ",
" Pause CLOSE       90 秒 ",
" Runtime OPEN      30 秒 ",
" Pause OPEN        90 秒 ",
"Limitation DC-link vol   ",
"                    打开 ",
"Runtime monitoring       ",
"                    打开 ",
"末端位置速度             ",
"                  Mormal ",
"Autom TL adapt. end pos  ",
"                    打开 ",
"DCS Acceptance time      ",
"                 25.5 秒 "
};

unsigned short menuSpeParaSet[MENU_SPEPARA_NUM]={MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
                                                MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
	                                              MENU_SETTING_TITLE,
	                                              MENU_SETTING_CONTENT,
                                                };



char SelSpeInstallCn[SEL_SPE_STALL_NUM][MAX_INFO_CHAR]={
"没有或长度小于等于10m    ",
"大于10m(带滤波器)        "
};

char SelSpeInstallEn[SEL_SPE_STALL_NUM][MAX_INFO_CHAR]={
"没有或长度小于等于10m    ",
"大于10m(带滤波器)        "
};

unsigned short SelSpeInstallSet[SEL_SPE_STALL_NUM]={MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT
                                                  };


char SelMotorHeatCn[SEL_MOTOR_HEAT_NUM][MAX_INFO_CHAR]={
"关闭                     ",
"打开                     "
};

char SelMotorHeatEn[SEL_MOTOR_HEAT_NUM][MAX_INFO_CHAR]={
"关闭                     ",
"打开                     "
};

unsigned short SelMotorHeatSet[SEL_MOTOR_HEAT_NUM]={MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT
                                                  };


char SelFlangeCn[SEL_FLANGE_NUM][MAX_INFO_CHAR]={
"带力矩测量的法兰         ",
" 不可用                  ",
" 模拟量输入AI1           "
};

char SelFlangeEn[SEL_FLANGE_NUM][MAX_INFO_CHAR]={
"带力矩测量的法兰         ",
" 不可用                  ",
" 模拟量输入AI1           "
};

unsigned short SelFlangeSet[SEL_FLANGE_NUM]={MENU_SETTING_TITLE,
	                                             MENU_SETTING_CONTENT,
	                                             MENU_SETTING_CONTENT
                                                  };
                                                  
char SelComOpenCloseCn[SEL_COMMON_OPENCLOSE_NUM][MAX_INFO_CHAR]={
"打开                     ",
"关闭                     "
};

char SelComOpenCloseEn[SEL_COMMON_OPENCLOSE_NUM][MAX_INFO_CHAR]={
"打开                     ",
"关闭                     "
};

unsigned short SelComOpenCloseSet[SEL_COMMON_OPENCLOSE_NUM]={MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT
                                                  };

char SelEndPosSpeedCn[SEL_END_POSITION_SPEED_NUM][MAX_INFO_CHAR]={
"Normal                   ",
"快速启动                 ",
"Quick-Start/Stop         "
};

char SelEndPosSpeedEn[SEL_END_POSITION_SPEED_NUM][MAX_INFO_CHAR]={
"Normal                   ",
"快速启动                 ",
"Quick-Start/Stop         "
};

unsigned short SelEndPosSpeedSet[SEL_END_POSITION_SPEED_NUM]={MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT
                                                  };

char EndPosMenuCn[SET_END_POSITION_MENU_NUM][MAX_INFO_CHAR]={
"首次设置末端位置         ",
"重新设置末端位置         "
};

char EndPosMenuEn[SET_END_POSITION_MENU_NUM][MAX_INFO_CHAR]={
"首次设置末端位置         ",
"重新设置末端位置         "
};

unsigned short EndPosMenuSet[SET_END_POSITION_MENU_NUM]={MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT
                                                  };


unsigned char menuEndPos1[MAX_INFO_CHAR]="选择首次设定的末端位置";
unsigned char menuEndPos2[MAX_INFO_CHAR]="仅设定末端位置";
unsigned char menuEndPos3[MAX_INFO_CHAR]="完成";
unsigned char menuEndPos4[MAX_INFO_CHAR]="与阀门有关的参数";
unsigned char menuCharClose[MAX_INFO_CHAR]="关";
unsigned char menuCharOpen[MAX_INFO_CHAR] ="开";
unsigned char menuCharSelEndPosCn[MAX_INFO_CHAR] ="选择首次设置的末端位置";
unsigned char menuCharSelEndPosEn[MAX_INFO_CHAR] ="选择首次设置的末端位置";
unsigned char menuCharSetEndPosCn[MAX_INFO_CHAR] ="向末端位置运行";
unsigned char menuCharSetEndPosEn[MAX_INFO_CHAR] ="向末端位置运行";
unsigned char menuCharSetEndPosCn_Open[MAX_INFO_CHAR] ="向开末端位置运行";
unsigned char menuCharSetEndPosEn_Open[MAX_INFO_CHAR] ="向开末端位置运行";
unsigned char menuCharSetEndPosCn_Close[MAX_INFO_CHAR] ="向关末端位置运行";
unsigned char menuCharSetEndPosEn_Close[MAX_INFO_CHAR] ="向关末端位置运行";
unsigned char menuCharHelpCn[MAX_INFO_CHAR] ="帮助";
unsigned char menuCharHelpEn[MAX_INFO_CHAR] ="帮助";
unsigned char menuCharEnterEndPosCn[MAX_INFO_CHAR] ="确认末端位置";
unsigned char menuCharEnterEndPosEn[MAX_INFO_CHAR] ="确认末端位置";
unsigned char menuCharSetRangeEndPosCn[MAX_INFO_CHAR] ="设定有效范围";
unsigned char menuCharSetRangeEndPosEn[MAX_INFO_CHAR] ="设定有效范围";
unsigned char menuCharSetDataEndPosCn[MAX_INFO_CHAR] ="圈/全行程";
unsigned char menuCharSetDataEndPosEn[MAX_INFO_CHAR] ="圈/全行程";

char menuParaSysCn[MENU_PARA_WITH_SYS_NUM][MAX_INFO_CHAR]={
"显示                     ",
"实时时钟                 ",
"蓝牙模块                 "
};

char menuParaSysEn[MENU_PARA_WITH_SYS_NUM][MAX_INFO_CHAR]={
"显示                     ",
"实时时钟                 ",
"蓝牙模块                 "
};

unsigned short menuParaSysSet[MENU_PARA_WITH_SYS_NUM]={MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT
                                                  };

char menuParaSysShowDirCn[MENU_PARA_WITH_SYS_SHOW_NUM][MAX_INFO_CHAR]={
"显示方向                 ",
"                     0度 "
};

char menuParaSysShowDirEn[MENU_PARA_WITH_SYS_SHOW_NUM][MAX_INFO_CHAR]={
"显示方向                 ",
"                     0度 "
};

unsigned short menuParaSysShowDirSet[MENU_PARA_WITH_SYS_SHOW_NUM]={MENU_SETTING_TITLE,
	                                                 MENU_SETTING_CONTENT
                                                  };

char selParaSysShowDirCn[MENU_PARA_WITH_SYS_SHOW_DIR_NUM][MAX_INFO_CHAR]={
"0度                      ",
"180度                    "
};

char selParaSysShowDirEn[MENU_PARA_WITH_SYS_SHOW_DIR_NUM][MAX_INFO_CHAR]={
"0度                      ",
"180度                    "
};

unsigned short selParaSysShowDirSet[MENU_PARA_WITH_SYS_SHOW_DIR_NUM]={MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT
                                                  };

const char convert_user_to_handler_cn[]={"\
        切换用户至       \
          操作员         \
"};

const char convert_user_to_handler_en[]={"\
        切换用户至       \
          操作员         \
"};

const char convert_user_to_viewer_cn[]={"\
        切换用户至       \
          监察员         \
"};

const char convert_user_to_viewer_en[]={"\
        切换用户至       \
          监察员         \
"};

const char convert_user_to_expert_cn[]={"\
        切换用户至       \
          专家           \
"};

const char convert_user_to_expert_en[]={"\
        切换用户至       \
          专家           \
"};

const char convert_user_to_service_cn[]={"\
        切换用户至       \
          服务           \
"};

const char convert_user_to_service_en[]={"\
        切换用户至       \
          服务           \
"};

const char convert_user_to_factroy_cn[]={"\
        切换用户至       \
        工厂服务         \
"};

const char convert_user_to_factroy_en[]={"\
        切换用户至       \
        工厂服务         \
"};
const char new_password_handler_cn[]={"\
          新密码         \
          操作员         \
"};

const char new_password_handler_en[]={"\
          新密码         \
          操作员         \
"};

const char new_password_viewer_cn[]={"\
          新密码         \
          监察员         \
"};

const char new_password_viewer_en[]={"\
          新密码         \
          监察员         \
"};

const char new_password_expert_cn[]={"\
          新密码         \
          专家           \
"};

const char new_password_expert_en[]={"\
          新密码         \
          专家           \
"};

const char new_password_service_cn[]={"\
          新密码         \
          服务           \
"};

const char new_password_service_en[]={"\
          新密码         \
          服务           \
"};

const char new_password_factroy_cn[]={"\
          新密码         \
        工厂服务         \
"};

const char new_password_factroy_en[]={"\
          新密码         \
        工厂服务         \
"};

char FrstSelEndPosMenuCn[SET_END_POSITION_MENU_NUM][MAX_INFO_CHAR]={
"开                       ",
"关                       "
};

char FrstSelEndPosMenuEn[SET_END_POSITION_MENU_NUM][MAX_INFO_CHAR]={
"开                       ",
"关                       "
};

unsigned short FrstSelEndPosMenuSet[SET_END_POSITION_MENU_NUM]={MENU_SETTING_CONTENT,
	                                                 MENU_SETTING_CONTENT
                                                  };
const char ChgPasswordCn[AUTHRITY_NUM][MAX_INFO_CHAR]={
//"观察员                 ",
"操作员                 ",
"监察员                 ",
"专家                   ",
"服务                   ",
"工厂服务               "
};

const char ChgPasswordEn[AUTHRITY_NUM][MAX_INFO_CHAR]={
//" 				 E观察员",
" 				 E操作员",
" 				 E监察员",
" 				   E专家",
" 				   E服务",
" 			   E工厂服务"
};


 unsigned short ChgPasswordSet[AUTHRITY_NUM]={MENU_SETTING_DISAPP,
												  MENU_SETTING_CONTENT,
												  MENU_SETTING_CONTENT,
												  MENU_SETTING_CONTENT,
												  MENU_SETTING_CONTENT,
												  MENU_SETTING_CONTENT
												};


																									
																									
																									
const char bluetooth_status_cn[MENU_BLUETOOTH_STATUE_NUM][MAX_INFO_CHAR]={
"蓝牙                   ",
"                     是"
};

const char bluetooth_status_en[MENU_BLUETOOTH_STATUE_NUM][MAX_INFO_CHAR]={
"蓝牙E 				    ",
"					  是"

};


unsigned short bluetooth_status_Set[MENU_BLUETOOTH_STATUE_NUM]={
	                                              MENU_SETTING_TITLE,
												  MENU_SETTING_CONTENT
												};
#if 1
const char bluetooth_sel_cn[MENU_BLUETOOTH_SEL_NUM][MAX_INFO_CHAR]={
"蓝牙有效 			    ",
"					  是",
"					  否"

};

const char bluetooth_sel_en[MENU_BLUETOOTH_SEL_NUM][MAX_INFO_CHAR]={
"蓝牙E					",
"					  是",
"					  否"
};
#endif
 unsigned short bluetooth_sel_Set[MENU_BLUETOOTH_SEL_NUM]={
												  MENU_SETTING_TITLE,
												  MENU_SETTING_CONTENT,
												  MENU_SETTING_CONTENT
												};
 const char info_menu_ok[1][MAX_INFO_CHAR]={
"           OK            "
};
 const char info_menu_continue[1][MAX_INFO_CHAR]={
"          继续           "
};




char menu1EndPosParaCn[MENU1_ENDPOS_PARA_NUM][MAX_INFO_CHAR]={
"关方向                   ",
"                  逆时针 ",
"转速                     ",
" 关              160 rpm ",
" 开               20 rpm "
};

char menu1EndPosParaEn[MENU1_ENDPOS_PARA_NUM][MAX_INFO_CHAR]={
"关方向                   ",
"                  逆时针 ",
"转速                     ",
" 关              160 rpm ",
" 开               20 rpm "
};

unsigned short menu1EndPosParaSet[MENU1_ENDPOS_PARA_NUM]={MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT
                                                   };
                                                   
                                                   
char menu2EndPosParaCn[MENU2_ENDPOS_PARA_NUM][MAX_INFO_CHAR]={
"关断模式                 ",
" 关         行程关断模式 ",
" 开         行程关断模式 ",
"关断力矩                 ",
" 关               112 Nm ",
" 开              37.5 Nm "
};

char menu2EndPosParaEn[MENU2_ENDPOS_PARA_NUM][MAX_INFO_CHAR]={
"关断模式                 ",
" 关         行程关断模式 ",
" 开         行程关断模式 ",
"关断力矩                 ",
" 关               112 Nm ",
" 开              37.5 Nm "
};

unsigned short menu2EndPosParaSet[MENU2_ENDPOS_PARA_NUM]={
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_TITLE,
                                                   MENU_SETTING_CONTENT,
                                                   MENU_SETTING_CONTENT                                                  
                                                   };
