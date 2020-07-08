#include "DataInterface.h"
#include "stdio.h"
#include "string.h"   //0427

DATASTRUCTINTERFACE dataStructInterface;

volatile char   g_deviceState  = 0;
//������Ľ���   Ϊ0��ʾ������text��   1��ʾ������list��
volatile char   g_mainMenuFocus  = 0;
//��������Ľ���   Ϊ0��ʾ������text��   1��ʾ������list��
volatile char   g_hdlMenuFocus  = 1;
//Ȩ��
volatile char   g_authority  = 1;

/*******************************************************************************
* Function Name :_InterDataRefresh
* Description   :���½ӿ�����
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
* Description   :���½ӿ�����
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
* Description   :���½ӿ�����
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
"00 ��Ϣ�鿴����",
"01 ���в��������쳣",
"02 �����ѯ",
"03 ��ֵ��������",
"04 ��ز���",
"05 adi blackdspϵ��",
"06 ���糧��������",
"07 �����������Ƽ�"
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
"�͵ز���",
"        �������",
"        �ر�"
};

 char infoWinMainList0EN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"local para",
"        Cont node",
"        off"
};

 char infoWinMainListCN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"����ģʽ",
"����",
"���˵�"
};

 char infoWinMainListEN[DEVICE_STATE_NUM][MAX_INFO_CHAR]={
"ctrl mod",
"language",
"main menu"
};

 char infoDeviceStateCN[DEVICE_STATE_INFO_NUM][MAX_INFO_CHAR]={
"               װ��׼����",
"           װ��û��׼����",
"             װ�ó��ֹ���"
};

 char infoDeviceStateEN[DEVICE_STATE_INFO_NUM][MAX_INFO_CHAR]={
"             device ready",
"         device not ready",
"             device error"
};

 char infoTitleCN[DEVICE_TITLE_INFO_NUM][MAX_INFO_CHAR]={
"ִ�л���",
"װ�ù���"
};

 char infoTitleEN[DEVICE_TITLE_INFO_NUM][MAX_INFO_CHAR]={
"actuator",
"plant failure"
};


char exp_cn_content0[]={"\
                         \
                         \
          ����1:         \
ִ�л���׼���ã����Բ��� \
"};

char exp_cn_content1[]={"\
                         \
                         \
          ����2:         \
ִ�л���׼���ã����Բ��� \
"};

char exp_cn_content2[]={"\
                         \
                         \
          ����3:         \
ִ�л���׼���ã����Բ��� \
"};
char exp_cn_content3[]={"\
                         \
                         \
          ����4:         \
ִ�л���׼���ã����Բ��� \
"};

 char exp_cn_content4[]={"\
                         \
                         \
          ����5:         \
ִ�л���׼���ã����Բ��� \
"};

 char exp_en_content0[]={"\
                         \
                         \
          explan1:       \
ִ�л���׼���ã����Բ��� \
"};

 char exp_en_content1[]={"\
                         \
                         \
          explan2:       \
ִ�л���׼���ã����Բ��� \
"};

 char exp_en_content2[]={"\
                         \
                         \
          explan3:       \
ִ�л���׼���ã����Բ��� \
"};

 char exp_en_content3[]={"\
                         \
                         \
          explan4:       \
ִ�л���׼���ã����Բ��� \
"};

 char exp_en_content4[]={"\
                         \
                         \
          explan5:       \
ִ�л���׼���ã����Բ��� \
"};

 char handle_cn_content0[]={"\
     ���ܵĴ�����1:    \
������С������������ \
                         \
                         \
"};

 char handle_cn_content1[]={"\
     ���ܵĴ�����2:    \
������С������������ \
                         \
                         \
"};

 char handle_cn_content2[]={"\
     ���ܵĴ�����3:    \
������С������������ \
                         \
                         \
"};

 char handle_cn_content3[]={"\
     ���ܵĴ�����4:    \
������С������������ \
                         \
                         \
"};

 char handle_cn_content4[]={"\
     ���ܵĴ�����5:    \
������С������������ \
                         \
                         \
"};


 char handle_en_content0[]={"\
          method1:       \
������С������������ \
                         \
                         \
"};

 char handle_en_content1[]={"\
          method2:       \
������С������������ \
                         \
                         \
"};

 char handle_en_content2[]={"\
          method3:       \
������С������������ \
                         \
                         \
"};

 char handle_en_content3[]={"\
          method4:       \
������С������������ \
                         \
                         \
"};

 char handle_en_content4[]={"\
          method5:       \
������С������������ \
                         \
                         \
"};


 char menuMainCn[MAIN_MENU_NUM][MAX_INFO_CHAR]={
"�û�����                 ",
"�۲�                     ",
"���                     ",
"ĩ��λ��                 ",
"����                     ",
"��������                 ",
"��ϵͳ�йص��趨         "
};

 char menuMainEn[MAIN_MENU_NUM][MAX_INFO_CHAR]={
"user management          ",
"E�۲�                    ",
"E���                    ",
"Eĩ��λ��                ",
"E����                    ",
"E��������                ",
"E��ϵͳ�йص��趨        "
};


char menuUserManagCn[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"��ǰ�û�                 ",
"                   ����Ա",
"����                     ",
"                 ��������"
};

char menuUserManagEn[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"Current user             ",
"                    handl",
"manage                   ",
"          Change password"
};

char menuUserManagCnBak[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"��ǰ�û�                 ",
"                   ����Ա",
"����                     ",
"                 ��������"
};

char menuUserManagEnBak[MENU_USER_MANAG_NUM][MAX_INFO_CHAR]={
"Current user             ",
"                    handl",
"manage                   ",
"          Change password"
};

unsigned char menuUserManagSettings[MENU_USER_MANAG_NUM]={MENU_SETTING_TITLE,MENU_SETTING_CONTENT,MENU_SETTING_TITLE,MENU_SETTING_CONTENT};


char menuCurUserCn[MENU_CUR_USER_NUM][MAX_INFO_CHAR]={
"�˳�                     ",
"  �۲�Ա                 ",
"�л��û���               ",
"  ����Ա                 ",
"  ���Ա                 ",
"  ר��                   ",
"  ����                   ",
"  ��������               "
};

char menuCurUserEn[MENU_CUR_USER_NUM][MAX_INFO_CHAR]={
"exit                     ",
"  �۲�Ա                 ",
"�л��û���               ",
"  ����Ա                 ",
"  ���Ա                 ",
"  ר��                   ",
"  ����                   ",
"  ��������               "
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
"                   �۲�Ա",
"                   ����Ա",
"                   ���Ա",
"                     ר��",
"                     ����",
"                 ��������"
};

char userNameEn[AUTHRITY_NUM][MAX_INFO_CHAR]={
"                  E�۲�Ա",
"                  E����Ա",
"                  E���Ա",
"                    Eר��",
"                    E����",
"                E��������"
};



