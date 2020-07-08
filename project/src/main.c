#include "LPC43xx.h"
#include <includes.h>
#include "USART_Conf.h"
#include "Encoder.h"
#include "mlx90363.h"
#include "Handler.h"
#include "USART_Conf.h"
#include "DataInterface.h"
#include "WIN_Context.h"
#include "DIALOG.h"
#include "timer.h"
#include "Extern.h"
#include "0420.h"
#include "torque.h"
#include  "datafigures.h"
#include "SPI.h"
#include "EEPROM.h"
#include "states.h"
#include "temperature.h"
#include "Error0x.h"
#include "Error1x.h"
#include "Error2x.h"
#include "Error3x.h"
#include "Error4x.h"
#include "Error5x.h"
#include "Error6x.h"
#include  "datafigures.h"
#include "hand.h"
#include "TIME.h"
#include "lpc43xx_mcpwm.h"
#include "FLASH.h"
#include "USB_MAIN.h"
#include "SEGGER_RTT.h"
#include "test_UART0.h"
#pragma  diag_suppress 870
#pragma  diag_suppress 177 

unsigned char ssi_m,ssi_s;
char tset_key;
static  OS_STK         App_TaskStartStk[APP_TASK_START_STK_SIZE];
static  OS_STK         App_TaskGUIStk[APP_TASK_GUI_STK_SIZE];
static  OS_STK         App_TaskTouchStk[APP_TASK_Touch_STK_SIZE];
static  OS_STK         App_TaskStatesStk[APP_TASK_States_STK_SIZE];
static  OS_STK         App_TaskUARTStk[APP_TASK_UART_STK_SIZE];
static  OS_STK         App_TaskUART0Stk[APP_TASK_UART0_STK_SIZE];
static  OS_STK         App_TaskUART2Stk[APP_TASK_UART2_STK_SIZE];


static  void  App_TaskStart        (void    *p_arg);
static  void  App_TaskGUI          (void    *p_arg);
static  void  App_TaskTouch        (void    *p_arg);
static  void  App_TaskStates       (void    *p_arg);
static  void  App_TaskUART         (void    *p_arg);
static  void  App_TaskUART0         (void    *p_arg);
static  void  App_TaskUART2         (void    *p_arg);

extern void WIN_WindowsTreeInit(void);
extern void WIN_ContextInit(void);
extern void backgroundmbit();
extern void Lcd_drive_Init(void);
extern void Lcd_drive_Init(void);
extern void Main1Task(void);
extern WM_HWIN WindowMainCreat(void); 
extern void _DataRefresh(void);
extern void WIN_KeyBoard(int key);
extern void _MainWinShowDataRefresh();
extern void Init_MLX90363(void);
extern void c_entry_mlx_I(void);
extern void Init_EESPI0(void);
extern void Init_ADC(void);

extern float c_entry_ADC(void);
char flag_reset_encoder;

char motorset_stop;
char motorset_n;
char motorset_s;


extern char test005_1;
extern char test005_2;
extern char test005_3;
extern char test005_4;

int main(void)
{
	#if 1
    CPU_INT08U  os_err;
    uart3.ready_4A=0;
    ai_o420.flag_O_0020=0;
	ai_o420.flag_O_0420=1;
	ai_o420.flag_O_up=1;
	ai_o420.flag_O_down=0;
	ai_o420.flag_I_0020=0;
	ai_o420.flag_I_0420=1;
	ai_o420.flag_I_up=1;
	ai_o420.flag_I_down=0;
	encoder.dir_flag=2;
	motorset.DIR=1;
	motorset.DIR_MOTOR_s=2;
	motorset.DIR_MOTOR_n=1;
	motorset.DIR_MOTOR_t=3;
	flag_figures.KEYMod=1;
	timer.flag_all_run=1;
	set_end.flag_setend=0;
	eeprom.flag_eeprom=0;
	encoder.set_flag=0;
	encoder.set_end_ok=1;
	motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
	ai_o420.AI_0420_old=0;
	ai_o420.AO_0420_old=0;
	encoder.RX_Timeout=50;
	motorset.flag_start=0;
    SystemInit();
    BSP_IntDisAll();  
	SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
	printf("\r\n%s\t\t%s\r\n", __DATE__, __TIME__);
	OSInit(); 
	
	#if 1
    c_entry_flash_test()	;
	c_entry_flash_READ_TEST(0x00000000,liju_left);
	c_entry_flash_READ_TEST(0x00010000,xingcheng_left);
	c_entry_flash_READ_TEST(0x00020000,liju_right);
	c_entry_flash_READ_TEST(0x00030000,xingcheng_right);
	c_entry_flash_READ_TEST(0x00040000,NationalFlag);
	c_entry_flash_READ_TEST(0x00050000,LocalNoSelected);
	c_entry_flash_READ_TEST(0x00060000,LocalSelected);
	c_entry_flash_READ_TEST(0x00070000,RemoteNoSelected);
	c_entry_flash_READ_TEST(0x00080000,RemoteSelected);
	c_entry_flash_READ_TEST(0x00090000,OffNoSelected);
	c_entry_flash_READ_TEST(0x000A0000,OffSelected);
	c_entry_flash_READ_TEST(0x000B0000,backSel);
	c_entry_flash_READ_TEST(0x000C0000,backUnsel);
	c_entry_flash_READ_TEST(0x000D0000,homeSel);
	c_entry_flash_READ_TEST(0x000E0000,homeUnsel);
	c_entry_flash_READ_TEST(0x000F0000,home_unsel);
	c_entry_flash_READ_TEST(0x00100000,home_sel);
	c_entry_flash_READ_TEST(0x00110000,Shu_Blue);
	c_entry_flash_READ_TEST(0x00120000,Shu_Orn);
	c_entry_flash_READ_TEST(0x00130000,close_brow);
	c_entry_flash_READ_TEST(0x00140000,close_blue);
	c_entry_flash_READ_TEST(0x00150000,open_blue);
	c_entry_flash_READ_TEST(0x00160000,open_brow);

	c_entry_flash_READ_TEST(0x00170000,user_service   );
	c_entry_flash_READ_TEST(0x00180000,user_expert    );
	c_entry_flash_READ_TEST(0x00190000,user_watcher    );
	c_entry_flash_READ_TEST(0x001a0000,user_monitor     );
	c_entry_flash_READ_TEST(0x001b0000,user_hander       );
	c_entry_flash_READ_TEST(0x001c0000,user_factory      );
	c_entry_flash_READ_TEST(0x001d0000,iteam_sel           );
	c_entry_flash_READ_TEST(0x001e0000,iteam_unsel         );
	c_entry_flash_READ_TEST(0x001f0000,drive_quan         );
	c_entry_flash_READ_TEST(0x00200000,left_back_unsel);
	c_entry_flash_READ_TEST(0x00210000,left_back_sel);
	c_entry_flash_READ_TEST(0x00220000,right_home_unsel);
	c_entry_flash_READ_TEST(0x00230000,right_home_sel);
	c_entry_flash_READ_TEST(0x00240000,list_open);
	c_entry_flash_READ_TEST(0x00250000,list_close);
	c_entry_flash_READ_TEST(0x00260000,rect_orange_2num);
	c_entry_flash_READ_TEST(0x00270000,rect_orange_3num);
	c_entry_flash_READ_TEST(0x00280000,rect_orange_5num);
	c_entry_flash_READ_TEST(0x00290000,acclose);
	c_entry_flash_READ_TEST(0x002a0000,acopen);
	c_entry_flash_READ_TEST(0x002b0000,acqwe);
	c_entry_flash_READ_TEST(0x002c0000,acqwer);
	c_entry_flash_READ_TEST(0x002d0000,PHOTO_set_ok);
	FLASH_CS_HIGH();
#endif
	Init_SPI0();
	Init_EESPI0();
	states_spi0(0);
	Init_EESPI0_EN();
	states_EEPROM();
	read_eeprom();
    encoder.dir_flag=eeprom.dir_flag;
    
    os_err = OSTaskCreateExt((void (*)(void *)) App_TaskStart,  
                           (void          * ) 0,
                           (OS_STK        * )&App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
                           (INT8U           ) APP_TASK_START_PRIO,
                           (INT16U          ) APP_TASK_START_PRIO,
                           (OS_STK        * )&App_TaskStartStk[0],
                           (INT32U          ) APP_TASK_START_STK_SIZE,
                           (void          * )0,
                           (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

#if (OS_TASK_NAME_SIZE >= 11)
    OSTaskNameSet(APP_TASK_START_PRIO, (CPU_INT08U *)"Start Task", &os_err);
#endif
    OSStart();  													 
    return (0);
#endif
}


static  void  App_TaskStart (void *p_arg)
{
  CPU_INT08U  os_err;
  (void)p_arg;
  OS_CPU_SysTickInit();                                       

#if (OS_TASK_STAT_EN > 0)
  OSStatInit();                                               
#endif
  os_err = OSTaskCreateExt((void (*)(void *)) App_TaskStates,  
                           (void          * ) 0,
                           (OS_STK        * )&App_TaskStatesStk[APP_TASK_States_STK_SIZE - 1],
                           (INT8U           ) APP_TASK_States_PRIO,
                           (INT16U          ) APP_TASK_States_PRIO,
                           (OS_STK        * )&App_TaskStatesStk[0],
                           (INT32U          ) APP_TASK_States_STK_SIZE,
                           (void          * )0,
                           (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

#if (OS_TASK_NAME_SIZE >= 11)
  OSTaskNameSet(APP_TASK_Touch_PRIO, (CPU_INT08U *)"States Task", &os_err);
#endif
													 
													 
  os_err = OSTaskCreateExt((void (*)(void *)) App_TaskGUI,  
                           (void          * ) 0,
                           (OS_STK        * )&App_TaskGUIStk[APP_TASK_GUI_STK_SIZE - 1],
                           (INT8U           ) APP_TASK_GUI_PRIO,
                           (INT16U          ) APP_TASK_GUI_PRIO,
                           (OS_STK        * )&App_TaskGUIStk[0],
                           (INT32U          ) APP_TASK_GUI_STK_SIZE,
                           (void          * )0,
                           (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

#if (OS_TASK_NAME_SIZE >= 11)
  OSTaskNameSet(APP_TASK_GUI_PRIO, (CPU_INT08U *)"GUI Task", &os_err);
#endif
													 
  os_err = OSTaskCreateExt((void (*)(void *)) App_TaskUART,  
                           (void          * ) 0,
                           (OS_STK        * )&App_TaskUARTStk[APP_TASK_UART_STK_SIZE - 1],
                           (INT8U           ) APP_TASK_UART_PRIO,
                           (INT16U          ) APP_TASK_UART_PRIO,
                           (OS_STK        * )&App_TaskUARTStk[0],
                           (INT32U          ) APP_TASK_UART_STK_SIZE,
                           (void          * )0,
                           (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

#if (OS_TASK_NAME_SIZE >= 11)
  OSTaskNameSet(APP_TASK_UART_PRIO, (CPU_INT08U *)"UART Task", &os_err);
#endif	

													 
  os_err = OSTaskCreateExt((void (*)(void *)) App_TaskUART0,  
                           (void          * ) 0,
                           (OS_STK        * )&App_TaskUART0Stk[APP_TASK_UART0_STK_SIZE - 1],
                           (INT8U           ) APP_TASK_UART0_PRIO,
                           (INT16U          ) APP_TASK_UART0_PRIO,
                           (OS_STK        * )&App_TaskUART0Stk[0],
                           (INT32U          ) APP_TASK_UART0_STK_SIZE,
                           (void          * )0,
                           (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

#if (OS_TASK_NAME_SIZE >= 11)
  OSTaskNameSet(APP_TASK_UART_PRIO, (CPU_INT08U *)"UART0 Task", &os_err);
#endif	
													 
  os_err = OSTaskCreateExt((void (*)(void *)) App_TaskUART2,  
                           (void          * ) 0,
                           (OS_STK        * )&App_TaskUART2Stk[APP_TASK_UART2_STK_SIZE - 1],
                           (INT8U           ) APP_TASK_UART2_PRIO,
                           (INT16U          ) APP_TASK_UART2_PRIO,
                           (OS_STK        * )&App_TaskUART2Stk[0],
                           (INT32U          ) APP_TASK_UART2_STK_SIZE,
                           (void          * )0,
                           (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
#if (OS_TASK_NAME_SIZE >= 11)
  OSTaskNameSet(APP_TASK_UART_PRIO, (CPU_INT08U *)"UART2 Task", &os_err);
#endif														 
													 
 while (1)
	{
    OSTimeDlyHMSM(0, 0, 0, 6);  
  }
  
}
int ADC_temp;
float ADC_TEMP1;
static  void  App_TaskStates (void *p_arg)
{
	#ifdef Encnew
		Init_Encoder();
		Timer0_Init();
	#elif  Encold
		UART2_Init();
	#endif
	Init_States();
	#if 1      
	Init_SPI0();
	Init_EESPI0_ADDA();
	hand_Init();
	#endif
	Init_error_data();
  while (1) 
	{
		data_init();
		#ifdef Encnew	
		#elif  Encold
		c_entry_uart2_encoder();
		#endif
		c_entry_Encoder2();		
		#if 1
		remote_conntrol.AI1_read=c_entry_AI1();
		remote_control();
		c_entry_AO1(key_mlx90363.READ_run_1);
		Error_out();	
		#endif
		OSTimeDlyHMSM(0, 0, 0, 200);
  }
}
extern void Main2Task(void);
static  void  App_TaskGUI (void *p_arg)
{ 
	int key;
    Init_MLX90363();
    Lcd_drive_Init(); 
    GUI_Init();   
    if(dataStructInterface.showDirect==1)
    {        				
        GUI_SetOrientation(GUI_MIRROR_X | GUI_MIRROR_Y);					
    }
    else if(dataStructInterface.showDirect==0)
    {
        GUI_SetOrientation(0);	
    }
    _InterDataInit();	
    WIN_WindowsTreeInit();             
    WIN_ContextInit();
    c_entry_mlx_I();
    while (1)
    { 	
		tset_key=c_entry_mlx();
		if(tset_key==8)
		{
			lcd.an_flag=1;
			if(lcd.an_set_flag==1)
			{
				MCOWM_SetPWM(10);
				flag_figures.user=1; 
				menuMainSettings[3]=0;  
				g_authority=0;
				lcd.an_ming_flag=1;
				lcd.ming_flag=0;
			}		
        }else
        {
			lcd.an_flag=0;
			WM_SetFocus(WM_HBKWIN);
			GUI_SendKeyMsg(tset_key, 1);			
            if(tset_key==GUI_KEY_DOWN)
            {
                lcd.down_num++;
                lcd.up_num=0;
            }
            if(tset_key==GUI_KEY_UP)
            {
                lcd.up_num++;
                lcd.down_num=0;
            }
            if((lcd.down_num>=3)||(lcd.up_num>=3))
            {
                lcd.ming_flag=1;
                lcd.down_num=0;
                lcd.up_num=0;
            }		
			if((tset_key==GUI_KEY_ENTER)||(lcd.ming_flag==1))
			{
				MCOWM_SetPWM(80);
				lcd.an_ming_flag=0;
				lcd.ming_flag=0;
			}			
        }
    _InterDataRefresh();
    GUI_Exec();
    OSTimeDlyHMSM(0, 0, 0, 20); 
    }
}
static uint8_t flag_allstart1;
static uint8_t flag_allstart2;
static uint8_t flag_allstart3;
unsigned short reall=1;



static  void  App_TaskUART (void *p_arg)
{	 
	UART3_Init();	
	Init_Timer1();
	Init_Timer2();
	Init_States();
	while(1)
	{	
		timer.all_run_h=RUN_ele_time();
		RUN_Coils_time();
		check_hand();
		c_entry_uart3();
		OSTimeDlyHMSM(0, 0, 0, 1); 
	}   
}

static  void  App_TaskUART2 (void *p_arg)
{	 
	Init_States();
	Init_DMA();
	while(1)
	{	
		ADC_temp=ADC_temperature();
		OSTimeDly(50);
	}   
}

static  void  App_TaskUART0 (void *p_arg)  //Ö÷Òª¿ØÖÆled
{	 
	UART0_Init();
	USB_init();
	Restart_Encoder_Init();
	Init_States();
	ExternOUT_Init();
	ExternIN_Init();
	ledstates.local=1;
	Init_SPI0();
	Init_EESPI0();	
	while(1)
	{		
		Extern_out();
		#if 1	
		if(ext_IO.flag_refresh==1)
		{
			Extern_out_test();			
			ext_IO.flag_refresh=0;
		}
		Extern_set();
		Extern_set_IO();
		#endif
		Extern_in();
		write_eeprom();
		if(ledstates.local==1)
		{
			c_entry_LOCAL();
			Init_SPI0();
		}else
		if(ledstates.remote==1)
		{
			c_entry_PC();			
		}else
		{
			c_enty_allclose_pc_local();
		}		
	if(set_end.flag_setend==0)
	{	
		if(motorset.flag_MOTOR_Close==1)
		{		
			if((encoder.num==2)||(encoder.num==1)||(encoder.num==4)||(encoder.num==3))	
			{				
				c_entry_OPEN();
				set_end.opall=1;
				set_end.clall=0;
			}else
			if((encoder.num==7)||(encoder.num==8)||(encoder.num==5))	
			{
				c_entry_CLOSE();
				set_end.opall=0;
				set_end.clall=1;
			}else
			{
				c_entry_OPEN();
				set_end.opall=1;
				set_end.clall=0;
			}
		}else	
		if(motorset.flag_MOTOR_Open==1)
		{
			if((encoder.num==2)||(encoder.num==1)||(encoder.num==4)||(encoder.num==3))	
			{
				c_entry_CLOSE();
				set_end.opall=0;
				set_end.clall=1;
			}else
			if((encoder.num==7)||(encoder.num==8)||(encoder.num==5))	
			{
				c_entry_OPEN();
				set_end.opall=1;
				set_end.clall=0;
			}else
			{
				c_entry_CLOSE();
				set_end.opall=0;
				set_end.clall=1;
			}
		}else
		{
			if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_t)
			{
				c_enty_allclose_close_open();
				set_end.opall=0;
				set_end.clall=0;
			}else
			if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
			{
			 RUN_OPEN() ;
				set_end.opall=0;
				set_end.clall=0;
			}else
			if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
			{
				RUN_CLOSE () ;
				set_end.opall=0;
				set_end.clall=0;
			}
		}
	}else
	if(set_end.flag_setend==1)
	{
		if(set_end.flag_open==1)
		{			
			c_entry_OPEN();
		}else	
		if(set_end.flag_close==1)
		{
			c_entry_CLOSE();
		}else
		{
			if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_t)
			{
				c_enty_allclose_close_open();
			}else
			if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
			{
			 RUN_OPEN() ;
			}else
			if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
			{
				RUN_CLOSE () ;
			}
		}
	}
		
		
		
		if(flag_reset_encoder==1)
		{
			Restart_Encoder(1);	
		}else
		if(flag_reset_encoder==0)
		{
			flag_reset_encoder=0;
			Restart_Encoder(0);
		}
		VCOM_Usb2Serial();
		OSTimeDly(6);
	}   
}
static  void  App_TaskTouch (void *p_arg)
{
  while (1) 
	{
    OSTimeDlyHMSM(0, 0, 0, 50);  
  }	  
}

#if (OS_APP_HOOKS_EN > 0)
void  App_TaskCreateHook (OS_TCB *ptcb)
{

}
void  App_TaskDelHook (OS_TCB *ptcb)
{
    (void)ptcb;
}

#if OS_VERSION >= 251
void  App_TaskIdleHook (void)
{
}
#endif
void  App_TaskStatHook (void)
{
}
#if OS_TASK_SW_HOOK_EN > 0
void  App_TaskSwHook (void)
{

}
#endif

#if OS_VERSION >= 204
void  App_TCBInitHook (OS_TCB *ptcb)
{
    (void)ptcb;
}
#endif
#if OS_TIME_TICK_HOOK_EN > 0
void  App_TimeTickHook (void)
{

}
#endif
#endif

#if OS_VERSION >= 289
void  App_TaskReturnHook (OS_TCB  *ptcb)
{
    (void)ptcb;
}
#endif

