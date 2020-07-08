
#if 0
#ifndef WIN_H_INCLUDED
#define WIN_H_INCLUDED

#include <stdio.h>



//֧�����Ե�����
#define LANGUAGE_NUM            2
//GUI ����buffter��С
#define LCD_BUFFTER_SIZE        512

#define _WIN32_                 //windows����
//#define _UCOS_X_              //ucos����
//#define _OS_LINUX_            //linux����

//winapi�ӿ� ʹ�ò��Դ���
#define _WINAPI_TEST_

//Debugģʽ ��Ҫ���ڴ�ӡ��Ϣ
#define _DEBUG_


/******************************�����޸�****************************************/
#ifndef NULL
#define NULL                    ((void *)0)
#endif

#ifndef TRUE
#define TRUE                    1
#endif

#ifndef FALSE
#define FALSE                   0
#endif


#define LCD_HSIZE           (320)
#define LCD_VSIZE           (240)

#define LCD_XSIZE           (LCD_HSIZE)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE           (LCD_VSIZE)   /* Y-resolution of LCD, Logical coor. */

/******************************��������****************************************/
typedef void FunCBType(void *);             //�ص���������
typedef int FunIntInt(int);

//�����л��м����
typedef struct {
    int         id;                         //�Ӵ���ID
    union {                                 //�Ӵ��ڷ��صı���
        const void* p;
        int v;
    }data;
}WIN_RETURN_TYPE;

//������Ϣ ���ڽ���������
typedef const struct{
    void            *hWin;                  //���ھ��
    FunCBType       *create;                //���ڽ���
    FunCBType       *destroy;               //���ڻ���
}WIN_INFO_TYPE;

//ÿ�����ڽڵ�����������Ϣ
typedef const struct {
     char      *title[LANGUAGE_NUM];   //���ڱ���                //0502   WY
    WIN_INFO_TYPE   *win;                   //������Ϣ
    FunCBType       *enter;                 //���ڽ���ص�����
    FunCBType       *exit;                  //�����˳��ص�����
    unsigned char    menunum;
    char            *menutitleCn;
    char            *menutitleEn;
    unsigned char   *menuattri;
}MENU_INFO_TYPE;


typedef volatile struct {
    int         active;             //����
    union {
        int     val;
        char    ch;
        char    * const pCh;
        void    * const pVal;
    }D;
}WIN_INTERFACE_t;



typedef int FunString(int, char *);

#define DATA_TYPE MENU_INFO_TYPE
#include "WIN_Tree.h"                       //����ز���
typedef ELEMENT MENU_INFO_ITEM;


extern char   g_LCDBuff[LCD_BUFFTER_SIZE];

// 0)Ӣ��   1)����
extern volatile char   g_LanguageIndex;

void _DataRefresh(void);
void WIN_WindowsTreeInit(void);
#endif // WIN_H_INCLUDED


#endif


#if 1
#ifndef WIN_H_INCLUDED
#define WIN_H_INCLUDED

#include <stdio.h>


//???????
#define LANGUAGE_NUM            2
//GUI ??buffter??
#define LCD_BUFFTER_SIZE        512

#define _WIN32_                 //windows??
//#define _UCOS_X_              //ucos??
//#define _OS_LINUX_            //linux??

//winapi?? ??????
#define _WINAPI_TEST_

//Debug?? ????????
#define _DEBUG_


/******************************????****************************************/
#ifndef NULL
#define NULL                    ((void *)0)
#endif

#ifndef TRUE
#define TRUE                    1
#endif

#ifndef FALSE
#define FALSE                   0
#endif


#define LCD_HSIZE           (320)
#define LCD_VSIZE           (240)

#define LCD_XSIZE           (LCD_HSIZE)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE           (LCD_VSIZE)   /* Y-resolution of LCD, Logical coor. */

/******************************????****************************************/
typedef void FunCBType(void *);             //??????
typedef int FunIntInt(int);

//????????
typedef struct {
    int         id;                         //???ID
    union {                                 //????????
        const void* p;
        int v;
    }data;
}WIN_RETURN_TYPE;

//???? ???????
typedef const struct{
    void            *hWin;                  //????
    FunCBType       *create;                //????
    FunCBType       *destroy;               //????
}WIN_INFO_TYPE;

//????????????
typedef const struct {
    char      *title[LANGUAGE_NUM];   //
    WIN_INFO_TYPE   *win;                   //????
    FunCBType       *enter;                 //????????
    FunCBType       *exit;                  //????????
    unsigned char    menunum;               //�����������
    const char      *menutitleCn;           //???????
    const char      *menutitleEn;           //???????
    unsigned short  *menuattri;             //?????    ???????
    unsigned short  *menusel;               //????????
	unsigned char    SN;
}MENU_INFO_TYPE;


typedef volatile struct {
    int         active;             //????
    union {
        int     val;
        char    ch;
        char    * const pCh;
        void    * const pVal;
    }D;
}WIN_INTERFACE_t;



typedef int FunString(int, char *);

#define DATA_TYPE MENU_INFO_TYPE
#include "WIN_Tree.h"                       //?????
typedef ELEMENT MENU_INFO_ITEM;


extern char   g_LCDBuff[LCD_BUFFTER_SIZE];

// 0)??   1)??
extern volatile char   g_LanguageIndex;

void _DataRefresh(void);

#endif // WIN_H_INCLUDED


#endif