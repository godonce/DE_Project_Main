#include "DataInterface.h"
#include "stdio.h"
#include "string.h"   //0427

DATASTRUCTINTERFACE dataStructInterface;

volatile char   g_deviceState  = 0;
//主界面的焦点   为0表示焦点在text上   1表示焦点在list上
volatile char   g_mainMenuFocus  = 0;
//操作界面的焦点   为0表示焦点在text上   1表示焦点在list上
volatile char   g_hdlMenuFocus  = 1;
//权限
volatile char   g_authority  = 1;

/*******************************************************************************
* Function Name :_InterDataRefresh
* Description   :更新接口数据
* Input         :void
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
void _InterDataRefresh(void)
{
    dataStructInterface.stateOpen    = 1 ;
    dataStructInterface.stateClose   = 0 ;
    dataStructInterface.stateMid     = 0 ;
    dataStructInterface.numMid1      = 98;
    //dataStructInterface.numMid2      = 8 ;
    dataStructInterface.IndexWinMainInfo = 5;
    dataStructInterface.numFault = 3;
    dataStructInterface.indexDeviceState = 2;
    dataStructInterface.indexFaultNum[0] = 0;
    dataStructInterface.indexFaultNum[1] = 3;
    dataStructInterface.indexFaultNum[2] = 4;
    dataStructInterface.helpExpIndex     = 0;
    dataStructInterface.helpMethodIndex  = 1;

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
}


/*******************************************************************************
* Function Name :GetExpInfoPtr
* Description   :更新接口数据
* Input         :void
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
char * GetExpInfoPtr(unsigned char index,char LanguageIndex)
{
    char *ptr;            //add const ???????? 0428
    if(LANGUAGE_CN == LanguageIndex)
    {
        switch(index)
        {
            case 0: ptr = exp_cn_content0;
            break;
            case 1: ptr = exp_cn_content1;
            break;
            case 2: ptr = exp_cn_content2;
            break;
            case 3: ptr = exp_cn_content3;
            break;
            case 4: ptr = exp_cn_content4;
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

/*******************************************************************************
* Function Name :GetHandleInfoPtr
* Description   :更新接口数据
* Input         :void
* Output        :void
* Other         :
* Date          :2018/04/17
*******************************************************************************/
char * GetHandleInfoPtr(unsigned char index,char LanguageIndex)
{
    char *ptr;
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

 char infoWinMainCN[MAX_FAULT_TEXT_NUM][MAX_INFO_CHAR]={
"00 信息查看错误",
"01 运行操作报告异常",
"02 报告查询",
"03 定值整定参数",
"04 测控参数",
"05 adi blackdsp系列",
"06 发电厂电气部分",
"07 深圳瑞闪光电科技"
};

 char infoWinMainEN[MAX_FAULT_TEXT_NUM][MAX_INFO_CHAR]={
"00 information Err0",
"01 information Err1",
"02 information Err2",
"03 information Err3",
"04 information Err4",
"05 adi blackdsp",
"06 information Err5",
"07 information Err6"
};

 char infoWinMainList0CN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"就地参数",
"        持续结点",
"        关闭"
};

 char infoWinMainList0EN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"local para",
"        Cont node",
"        off"
};

 char infoWinMainListCN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"控制模式",
"语言",
"主菜单"
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


char exp_cn_content0[]={"\
                         \
                         \
          解释1:         \
执行机构准备好，可以操作 \
"};

char exp_cn_content1[]={"\
                         \
                         \
          解释2:         \
执行机构准备好，可以操作 \
"};

char exp_cn_content2[]={"\
                         \
                         \
          解释3:         \
执行机构准备好，可以操作 \
"};
char exp_cn_content3[]={"\
                         \
                         \
          解释4:         \
执行机构准备好，可以操作 \
"};

 char exp_cn_content4[]={"\
                         \
                         \
          解释5:         \
执行机构准备好，可以操作 \
"};

 char exp_en_content0[]={"\
                         \
                         \
          explan1:       \
执行机构准备好，可以操作 \
"};

 char exp_en_content1[]={"\
                         \
                         \
          explan2:       \
执行机构准备好，可以操作 \
"};

 char exp_en_content2[]={"\
                         \
                         \
          explan3:       \
执行机构准备好，可以操作 \
"};

 char exp_en_content3[]={"\
                         \
                         \
          explan4:       \
执行机构准备好，可以操作 \
"};

 char exp_en_content4[]={"\
                         \
                         \
          explan5:       \
执行机构准备好，可以操作 \
"};

 char handle_cn_content0[]={"\
     可能的处理方法1:    \
增大或减小电流，检查接线 \
                         \
                         \
"};

 char handle_cn_content1[]={"\
     可能的处理方法2:    \
增大或减小电流，检查接线 \
                         \
                         \
"};

 char handle_cn_content2[]={"\
     可能的处理方法3:    \
增大或减小电流，检查接线 \
                         \
                         \
"};

 char handle_cn_content3[]={"\
     可能的处理方法4:    \
增大或减小电流，检查接线 \
                         \
                         \
"};

 char handle_cn_content4[]={"\
     可能的处理方法5:    \
增大或减小电流，检查接线 \
                         \
                         \
"};


 char handle_en_content0[]={"\
          method1:       \
增大或减小电流，检查接线 \
                         \
                         \
"};

 char handle_en_content1[]={"\
          method2:       \
增大或减小电流，检查接线 \
                         \
                         \
"};

 char handle_en_content2[]={"\
          method3:       \
增大或减小电流，检查接线 \
                         \
                         \
"};

 char handle_en_content3[]={"\
          method4:       \
增大或减小电流，检查接线 \
                         \
                         \
"};

 char handle_en_content4[]={"\
          method5:       \
增大或减小电流，检查接线 \
                         \
                         \
"};


 char menuMainCn[MAIN_MENU_NUM][MAX_INFO_CHAR]={
"用户管理                 ",
"观察                     ",
"诊断                     ",
"末端位置                 ",
"参数                     ",
"力矩曲线                 ",
"与系统有关的设定         "
};

 char menuMainEn[MAIN_MENU_NUM][MAX_INFO_CHAR]={
"user management          ",
"E观察                    ",
"E诊断                    ",
"E末端位置                ",
"E参数                    ",
"E力矩曲线                ",
"E与系统有关的设定        "
};


char menuUserManagCn[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"当前用户                 ",
"                   操作员",
"管理                     ",
"                 更改密码"
};

char menuUserManagEn[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"Current user             ",
"                    handl",
"manage                   ",
"          Change password"
};

char menuUserManagCnBak[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"当前用户                 ",
"                   操作员",
"管理                     ",
"                 更改密码"
};

char menuUserManagEnBak[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"Current user             ",
"                    handl",
"manage                   ",
"          Change password"
};

unsigned char menuUserManagSettings[MENU_USER_MANAG_NUM]={MENU_SETTING_TITLE,MENU_SETTING_CONTENT,MENU_SETTING_TITLE,MENU_SETTING_CONTENT};


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

unsigned char menuCurUserSettings[MENU_CUR_USER_NUM]={MENU_SETTING_TITLE,
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



