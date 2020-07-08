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
     char      *title[LANGUAGE_NUM];   //窗口标题
    WIN_INFO_TYPE   *win;                   //窗口信息
    FunCBType       *enter;                 //窗口进入回调函数
    FunCBType       *exit;                  //窗口退出回调函数
    unsigned char    menunum;               //菜单的数量
    const char            *menutitleCn;           //菜单的中文标题
    const char            *menutitleEn;           //菜单的英文标题
    unsigned short   *menuattri;             //标题的属性    是标题还是内容
		unsigned short   *menusel;               //当前选中了第几个
	unsigned char   SN;
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

#endif // WIN_H_INCLUDED

