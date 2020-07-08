
#if 0
#ifndef WIN_H_INCLUDED
#define WIN_H_INCLUDED

#include <stdio.h>



//支持语言的种类
#define LANGUAGE_NUM            2
//GUI 公共buffter大小
#define LCD_BUFFTER_SIZE        512

#define _WIN32_                 //windows环境
//#define _UCOS_X_              //ucos环境
//#define _OS_LINUX_            //linux环境

//winapi接口 使用测试代码
#define _WINAPI_TEST_

//Debug模式 主要用于打印信息
#define _DEBUG_


/******************************不可修改****************************************/
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

/******************************类型声明****************************************/
typedef void FunCBType(void *);             //回调函数类型
typedef int FunIntInt(int);

//窗口切换中间变量
typedef struct {
    int         id;                         //子窗口ID
    union {                                 //子窗口返回的变量
        const void* p;
        int v;
    }data;
}WIN_RETURN_TYPE;

//窗口信息 窗口建立及销毁
typedef const struct{
    void            *hWin;                  //窗口句柄
    FunCBType       *create;                //窗口建立
    FunCBType       *destroy;               //窗口回收
}WIN_INFO_TYPE;

//每个窗口节点所包含的信息
typedef const struct {
     char      *title[LANGUAGE_NUM];   //窗口标题                //0502   WY
    WIN_INFO_TYPE   *win;                   //窗口信息
    FunCBType       *enter;                 //窗口进入回调函数
    FunCBType       *exit;                  //窗口退出回调函数
    unsigned char    menunum;
    char            *menutitleCn;
    char            *menutitleEn;
    unsigned char   *menuattri;
}MENU_INFO_TYPE;


typedef volatile struct {
    int         active;             //活动标记
    union {
        int     val;
        char    ch;
        char    * const pCh;
        void    * const pVal;
    }D;
}WIN_INTERFACE_t;



typedef int FunString(int, char *);

#define DATA_TYPE MENU_INFO_TYPE
#include "WIN_Tree.h"                       //树相关操作
typedef ELEMENT MENU_INFO_ITEM;


extern char   g_LCDBuff[LCD_BUFFTER_SIZE];

// 0)英语   1)中文
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
    unsigned char    menunum;               //界面参数个数
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