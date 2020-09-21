#ifndef _DATA_figures_H_
#define _DATA_figures_H_

#include "stdio.h"
#include "stdint.h"
#include "string.h"  
//#define YELLOW_1  (0x28000000+(1024*1024*10))
//#define liju_left       	(0x28000000+(1024*1024*10))
//#define xingcheng_left  	(0x28000000+(1024*1024*11))
//#define liju_right   			(0x28000000+(1024*1024*12))
//#define  xingcheng_right 	(0x28000000+(1024*1024*13))
//#define NationalFlag     	(0x28000000+(1024*1024*14))
//#define LocalNoSelected  	(0x28000000+(1024*1024*15))
//#define LocalSelected    	(0x28000000+(1024*1024*17))
//#define RemoteNoSelected 	(0x28000000+(1024*1024*18))
//#define RemoteSelected   	(0x28000000+(1024*1024*20))
//#define OffNoSelected    	(0x28000000+(1024*1024*21))
//#define OffSelected      	(0x28000000+(1024*1024*22))
//#define backSel           (0x28000000+(1024*1024*23))
//#define backUnsel         (0x28000000+(1024*1024*24))
//#define homeSel           (0x28000000+(1024*1024*25))
//#define homeUnsel         (0x28000000+(1024*1024*26))
//#define home_unsel        (0x28000000+(1024*1024*27))
//#define home_sel          (0x28000000+(1024*1024*28))
//#define Shu_Blue          (0x28000000+(1024*1024*29))
//#define Shu_Orn           (0x28000000+(1024*1024*30))
//#define close_brow        (0x28000000+(1024*1024*31))
//#define close_blue        (0x28000000+(1024*1024*32))
//#define open_blue         (0x28000000+(1024*1024*33))
//#define open_brow         (0x28000000+(1024*1024*34))

#define liju_left       	(0x28000000+(1024*1024*10)+0x00000000)
#define xingcheng_left  	(0x28000000+(1024*1024*10)+0x00010000)
#define liju_right   			(0x28000000+(1024*1024*10)+0x00020000)
#define  xingcheng_right 	(0x28000000+(1024*1024*10)+0x00030000)
#define NationalFlag     	(0x28000000+(1024*1024*10)+0x00040000)
#define LocalNoSelected  	(0x28000000+(1024*1024*10)+0x00050000)
#define LocalSelected    	(0x28000000+(1024*1024*10)+0x00060000)
#define RemoteNoSelected 	(0x28000000+(1024*1024*10)+0x00070000)
#define RemoteSelected   	(0x28000000+(1024*1024*10)+0x00080000)
#define OffNoSelected    	(0x28000000+(1024*1024*10)+0x00090000)
#define OffSelected      	(0x28000000+(1024*1024*10)+0x000A0000)
#define backSel           (0x28000000+(1024*1024*10)+0x000B0000)
#define backUnsel         (0x28000000+(1024*1024*10)+0x000C0000)
#define homeSel           (0x28000000+(1024*1024*10)+0x000D0000)
#define homeUnsel         (0x28000000+(1024*1024*10)+0x000E0000)
#define home_unsel        (0x28000000+(1024*1024*10)+0x000F0000)
#define home_sel          (0x28000000+(1024*1024*10)+0x00100000)
#define Shu_Blue          (0x28000000+(1024*1024*10)+0x00110000)
#define Shu_Orn           (0x28000000+(1024*1024*10)+0x00120000)
#define close_brow        (0x28000000+(1024*1024*10)+0x00130000)
#define close_blue        (0x28000000+(1024*1024*10)+0x00140000)
#define open_blue         (0x28000000+(1024*1024*10)+0x00150000)
#define open_brow         (0x28000000+(1024*1024*10)+0x00160000)

#define user_service     (0x28000000+(1024*1024*10)+0x00170000)
#define user_expert      (0x28000000+(1024*1024*10)+0x00180000)
#define user_watcher     (0x28000000+(1024*1024*10)+0x00190000)
#define user_monitor     (0x28000000+(1024*1024*10)+0x001a0000)
#define user_hander      (0x28000000+(1024*1024*10)+0x001b0000)
#define user_factory     (0x28000000+(1024*1024*10)+0x001c0000)
#define iteam_sel        (0x28000000+(1024*1024*10)+0x001d0000)
#define iteam_unsel      (0x28000000+(1024*1024*10)+0x001e0000)
#define drive_quan       (0x28000000+(1024*1024*10)+0x001f0000)
#define left_back_unsel  (0x28000000+(1024*1024*10)+0x00200000)
#define left_back_sel    (0x28000000+(1024*1024*10)+0x00210000)
#define right_home_unsel  (0x28000000+(1024*1024*10)+0x00220000)
#define right_home_sel    (0x28000000+(1024*1024*10)+0x00230000)
#define list_open    (0x28000000+(1024*1024*10)+0x00240000)
#define list_close    (0x28000000+(1024*1024*10)+0x00250000)
#define rect_orange_2num    (0x28000000+(1024*1024*10)+0x00260000)
#define rect_orange_3num    (0x28000000+(1024*1024*10)+0x00270000)
#define rect_orange_5num    (0x28000000+(1024*1024*10)+0x00280000)
#define acclose    (0x28000000+(1024*1024*10)+0x00290000)
#define acopen    (0x28000000+(1024*1024*10)+0x002a0000)
#define acqwe    (0x28000000+(1024*1024*10)+0x002b0000)
#define acqwer    (0x28000000+(1024*1024*10)+0x002c0000)
#define PHOTO_set_ok    (0x28000000+(1024*1024*10)+0x002d0000)
#if 0
uint32_t _acuser_service []
uint32_t _acuser_expert  []
uint32_t _acuser_watcher []
uint32_t _acuser_monitor []
uint32_t _acuser_hander  []
uint32_t _acuser_factory []
uint32_t _aciteam_sel    []
uint32_t _aciteam_unsel  []

#endif



#define DE_GUI_BLUE_OC        0xFFBF00
#define DE_GUI_YELL_OC        0x0000A5FF//0x00C9EE

#define EEP_spi_init  1
#define AI1_spi_init  2
#define AO1_spi_init  3
#define close_spi_init 0

#define EEProm_writeenable    0x06
#define EEProm_writedisable   0x04
#define EEProm_readregistor   0x05
#define EEProm_writeregister  0x01
#define EEProm_readmemory     0x03
#define EEProm_writememory    0x02



#if 0

#define DEBUG_X_OFFSET  10

#endif

//#define VO1tage_MIN   5//20
//#define VO1tage_MAX   5//20
//#define MAX_States_NUM 64

#define posital_uncon   0x0FFFFFFF

typedef struct
{
	unsigned char stateOpen;                     //????? ?
	uint16_t vo1tage;
	uint32_t READ_ALL_903;    //全部
	uint32_t READ_ALL_903_1;    //全部
	uint32_t READ_ALL;
	uint32_t READ_timer;
	uint32_t READ_ALL_old;
	uint32_t READ_ALL_new;
	uint32_t AI1_low;
	uint32_t AI1_high;
	uint32_t AI1_read;
	uint32_t Integer;
	uint32_t decimal;
	uint32_t read;
	uint32_t Integer_1;
	uint32_t decimal_1;
	uint32_t Integer_2;
	uint32_t decimal_2;
	uint32_t Integer_3;
	uint32_t decimal_3;
	uint32_t READ_run;
	float READ_run_1;
	float TEMP_MOTOR;
	float analog;
	float analog_H;
	float analog_L;
	float encoder;
//uint32_t READ_timer1;
//uint32_t READ_timer2;
//float READ_timer3;
 
}DATA_FIGURES;

typedef struct
{
	//int flag_enter;
	
	uint64_t Read_now;
	uint64_t Read_all;
	float READ_timer3;
	char Run_dir;
	char Run_dir_old;
	char flag_runerror;
	uint32_t Integer_1;
	uint32_t decimal_1;
	uint64_t Integer_2;
	uint64_t decimal_2;
	uint32_t Integer_3;
	uint32_t decimal_3;
	uint32_t READ_run;
	uint64_t ssi_m;
	//uint32_t ssi_s;
	unsigned char  ssi_s;
	int/*float*/ READ_run_1;	
	int/*float*/ READ_run_1_old;
	char READ_run_jianflag;
	
	
	float abs_old;
	float abs_now;
	float abs_cha1;
	float abs_cha2;
	float abs_cha3;
	float degree;
	char enter_flag;
	char step;
	#if 0
	float X;
	float Y;
	float Z;
	#endif
	float sq_old;
	float sq_now;
}KEY;

//typedef struct
//{
//	float abs_old;
//	float abs_now;
//	float X;
//	float Y;
//	float Z;
//}TEST_Point;
typedef struct
{
	int Coils_temp;
	int Ele_temp;
	int Coils_temp_old;
	int Ele_temp_old;
	int as;
	int qw;
}STATES;

typedef struct
{
	int check_run;
    int all_run_h;
	int flag_all_run;
	int all_run_s;
	int flag_all_run_s;
	int runhhh;
	int runmill;
	int run_s;
	int run_m;
	int run_h;
	
	int flag_coils;
	int run_coils_num;
	int flag_coils_run_s;
	int run_coils_s;
	int run_coils_m;
	int run_coils_h;
	
	char flag_3sTAB1_start;
	char flag_3sTAB1;
	char flag_3sTAB1_num;
	char flag_3sTAB2_start;
	char flag_3sTAB2;
	char flag_3sTAB2_num;

}Timer;
typedef struct
{
	int blockstop;
	int run_error;
	int set_end_postial;
	int ready;
	int ready_old;
	unsigned char  user;
	int handle_stop;
	int  test;
	int KEYClose;
	int KEYOpen;
	int KEYStop;
	int KEYEme;
	int KEYMod;
		int read_old;
	int run1_100;
	int run0_0;
	int run100_100;
	int datadula2;
	int datadula3;

}FLAG_FIGURES;

typedef struct
{
	unsigned char numStates; 
	unsigned char indexFaultNum[64];
	int num_error;
	int num_error1;
	int num_error2;
	
	
	float   temp_adc;
	int     blockednum;
	float   run_alltime;
	float   run_time_error;
	float    run_error  ;
}Stateserror;


typedef struct
{
	float  power_voltage;
	uint16_t voltage;
	float  lcd_voltage;
	float lcd_current;
	float  lcd_voltage_old;
	float lcd_current_old;
	float  voltage_high;
	float  voltage_low;
	uint16_t speed_send;
	uint16_t current_close;
	uint16_t current_open;
	uint16_t current_up;
	char USB_ERROR;
}PowerBoard;

typedef struct
{
	int local;
	int open;
	int close;
	int remote;
	int off;
	char local_UI;
	char EME;
	char OPEN_remote;
}LEDSTATES;

typedef struct
{
	short AI1_read;
	float emergency_pos_H;
	float emergency_pos_L;
	char KEYEme;
	char EME_Flag;
}REMOTE;


typedef struct
{
	uint32_t all_move ;
	uint32_t all_move1 ;
	uint32_t all_move2 ;
	uint32_t all_move3 ;
	uint32_t all_move4 ;
}FLASH_flag;

typedef struct
{
	int handle_stop;//首次第一次设置
	int handle_stopT2;//首次第二次设置
	int flag_setend;
	int flag_open;
	int flag_close;
	int flag_closeOffMode;
	int flag_openOffMode;
	int closeOffMode;
	int openOffMode;
	int OffMode;
	
	int flag_move_left;
	int flag_move_right;
	int asdadd;
	char  opall;
	char  clall;
	
	char liju;
	char flag_liju;
	char liju2;
	char flag_liju2;
}SET_END;

typedef struct
{
	uint8_t DIR_MOTOR;
	uint8_t DIR_MOTOR_old;
	uint8_t DIR_MOTOR_s ;
	uint8_t DIR_MOTOR_n ;
	uint8_t DIR_MOTOR_t ;
	uint8_t DIR ;
	uint8_t DIR_f ;
	
	unsigned char flag_MOTOR_Run;    //中间运行标志位(介于全开和全关之间)
	unsigned char flag_MOTOR_Close;  //全关标志位
	unsigned char flag_MOTOR_Open;   //全开标志位
	unsigned char end_setok;
	char flag_estop_old; //1129
	char flag_run;   //1129
	char flag_run_jiangsu; //1129 
//	int currentout_num;
	char currentout_num1;//1129
	char currentout_num2;//1129
	char stop;
	char stop1;
	char stop2;
	char DIR_set_flag;
	char local_error;	
	char l0420_num;
	
	unsigned char  flag_start;
	unsigned char  flag_start_num;
	unsigned char  flag_start_start;
	unsigned char  flag_start_set;
	float torque_max;
	float torque_min;
}MOTOR_RUN;

typedef struct
{
	char dir_flag;
	char set_flag;
	char set_first;
	char set_second;
	char set_ok;
	int  Read_old;
	int  Read_old_set;
	char zhengfu_adj;
	char zhengfu_now;
	char dufangxiang;
	char dufangxianng_set_flag;
	char dufangxianng_flag;
	char dufangxiang_num;
	char num;
	char Set_Ready;
	char Set2EE_flag;
	char SET_read;
	char set_end_ok;
	
	
	
	char RX_Timeout;
	char RX_Timeout_flag;
	char RX_timeout_buf;
	uint64_t ssi_m;
	unsigned int ssi_s;
	uint8_t DIR_Send_close;
	uint8_t DIR_Send_open;
}ENCODER;


typedef struct
{
  char flag_I_0020;
	char flag_I_0420;
	char flag_I_up;
	char flag_I_down;
	char flag_O_0020;
	char flag_O_0420;
	char flag_O_up;
	char flag_O_down;
	double AI_0420;
	double AO_0420;
	double AI_0420_old;
	double AO_0420_old;
	double AI_0420_UI;
	double AO_0420_UI;
	double AI_0420_UI_old;
	double AO_0420_UI_old;
	float send_motor;
	char flag_mode1;
	char flag_mode2;
	char flag_mode3;
	char flag_mode4;
	char input_error;
	
	short save_a1;
	short save_a2;
	unsigned char k1;
	unsigned char b1;
	unsigned char k2;
	unsigned char b2;
	unsigned short G0420_offset;
	unsigned short G0420_slope;
	
	unsigned short G0420_OUT_offset;
	unsigned short G0420_OUT_slope;
	char flag_save0420_o;
	char flag_save0420_s;
	char flag_save0420_o_o;
	char flag_save0420_o_s;
	
	char flag_run_right;
	char flag_run_left;
	char flag_run_right_cx;
	char flag_run_left_cx;
	char flag_run_right_mc;
	char flag_run_left_mc;
}I_0420;

typedef struct
{
    char flag_eeprom;
    unsigned char openOffMode;  //开末端位置的关断模式
    char flag_openOffMode;
    char flag_UI_openOffMode;
    unsigned char closeOffMode; //关末端位置的关断模式
    char flag_closeOffMode;
    char flag_UI_closeOffMode;
    unsigned char speed_close;  //关转速
    char flag_speed_close;
    unsigned char speed_open ;  //开转速
    char flag_speed_open ;
    unsigned char moment_close; //关转矩
    char flag_moment_close;
    unsigned char moment_open ; //开转矩
    char flag_moment_open ;
    unsigned char closeDir;     //关方向参数
	unsigned char closeDir_save;
    char flag_90363 ;
    char dir_flag;
    unsigned char ctrlMode;
	unsigned char ctrlMode_save;
    unsigned char endPosClose;
    unsigned char endPosOpen;
	char flag_endPosClose;
	char flag_endPosOpen;
	char flag_ctrlMode;
	char flag_closeDir;
	char flag_IO_O;
	unsigned char out1;    //1129
	unsigned char out2;    //1129
	unsigned char out3;    //1129
	unsigned char out4;    //1129
	unsigned char out5;    //1129
	unsigned char out6;    //1129
	unsigned char out7;    //1129
	unsigned char out8;    //1129
	
	unsigned char out_of_1;  //1129
	unsigned char out_of_2;  //1129
	unsigned char out_of_3;  //1129
	unsigned char out_of_4;  //1129
	unsigned char out_of_5;  //1129
	unsigned char out_of_6;  //1129
	unsigned char out_of_7;  //1129
	unsigned char out_of_8;  //1129
	unsigned char read_all;  //1129
	
    char test1;
    char test2;
    char test3;
    char test4;
    char test5;
//	 char test001;
//	 char test002;
//	 char test003;
//	 char test004;
//	 char test005;
//	 char test006;
//	 char test007;
//	 char test008;
    char CRT1;
    char CRT2;
    char trt1;
    char trt2;
    char CRT;
    char CRT_1;
	 
    char Save_eme_pos;
    char Save_emg_speed_close_flag;
    char Save_emg_speed_open_flag;
    unsigned char emg_speed_close;
    unsigned char emg_speed_open;
    unsigned char emg_speed_close_ee;
    unsigned char emg_speed_open_ee;
    char showDirect;
	 
    char flag_g_password_handle;
    char flag_g_password_viewer;
    char flag_g_password_expert;
    char flag_g_password_service;
    char flag_g_password_factroy;
	 
    char g_password_handle;
    char g_password_viewer;
    char g_password_expert;
    char g_password_service;
    char g_password_factroy;
	 
    char g_deviceState_flag;

    char krInput_save;
    char flag_krInput;
	 
    unsigned char rmtChoose;
    char flag_rmtChoose;
	 
    char emgInput;
    char flag_emgInput;
	
}EEPROM;

typedef struct
{
	char			flag_speed_open    ;
	char			flag_test1         ;
	char			flag_speed_close   ;
	char			flag_test2         ;
	char			flag_moment_close  ;
	char			flag_test3         ;
	char			flag_moment_open   ;
	char			flag_test4         ;
	char			flag_dir_flag      ;
	char			flag_openOffMode   ;
	char			flag_closeOffMode  ;
	char			flag_ctrlMode      ;
	char			flag_closeDir      ;
}WRITE_EEPROM;
typedef struct
{
 char flag;
	char an_flag;
	char an_set_flag;
	char an_ming_flag;
	char ming_flag;
	char up_num;
	char down_num;
	uint32_t num;
}LCD;

typedef struct
{
	unsigned int switch_num;
	unsigned int switch_num_old;
}DIAGNOSE;


typedef struct
{
	unsigned char ready_4A;
}USART;

typedef struct
{
	uint8_t buffer2_ALL[6];
}USART2;

typedef struct
{
	char flag_close;
	char flag_open;
}LED;
typedef struct
{
	unsigned char flag_extern0;
	unsigned char flag_extern1;
	unsigned char flag_extern2;
	unsigned char flag_extern3;
	unsigned char flag_extern4;
	unsigned char flag_extern5;
	unsigned char flag_extern6;
	unsigned char flag_extern7;
	unsigned char flag_IO_extern0;
	unsigned char flag_IO_extern1;
	unsigned char flag_IO_extern2;
	unsigned char flag_IO_extern3;
	unsigned char flag_IO_extern4;
	unsigned char flag_IO_extern5;
	unsigned char flag_IO_extern6;
	unsigned char flag_IO_extern7;
	
	
	unsigned char flag_test_extern0;
	unsigned char flag_test_extern1;
	unsigned char flag_test_extern2;
	unsigned char flag_test_extern3;
	unsigned char flag_test_extern4;
	unsigned char flag_test_extern5;
	unsigned char flag_test_extern6;
	unsigned char flag_test_extern7;
	
	unsigned char flag_refresh;
	unsigned char eep_save_out1;
	unsigned char eep_save_out2;
	unsigned char eep_save_out3;
	unsigned char eep_save_out4;
	unsigned char eep_save_out5;
	unsigned char eep_save_out6;
	unsigned char eep_save_out7;
	unsigned char eep_save_out8;
	
	unsigned char eep_save_of1;
	unsigned char eep_save_of2;
	unsigned char eep_save_of3;
	unsigned char eep_save_of4;
	unsigned char eep_save_of5;
	unsigned char eep_save_of6;
	unsigned char eep_save_of7;
	unsigned char eep_save_of8;
	
	unsigned char eep_TEST_of1;
	unsigned char eep_TEST_of2;
	unsigned char eep_TEST_of3;
	unsigned char eep_TEST_of4;
	unsigned char eep_TEST_of5;
	unsigned char eep_TEST_of6;
	unsigned char eep_TEST_of7;
	unsigned char eep_TEST_of8;
	
	unsigned char eep_TEST2_of1;
	unsigned char eep_TEST2_of2;
	unsigned char eep_TEST2_of3;
	unsigned char eep_TEST2_of4;
	unsigned char eep_TEST2_of5;
	unsigned char eep_TEST2_of6;
	unsigned char eep_TEST2_of7;
	unsigned char eep_TEST2_of8;
	
}EXTERN_IO;


typedef struct
{
	uint16_t VOLTAGE[64];
	uint16_t CURRENT[64];
//	uint16_t T1_1;

}USB_0420;

typedef struct
{
		unsigned short   g_password_handle ;
		unsigned short   g_password_viewer ;//10;
		unsigned short   g_password_expert;//100;
		unsigned short   g_password_service ;//0000;
		unsigned short   g_password_factroy ;

}PASS_WORD;

typedef struct
{
	unsigned short T1_1;
	unsigned short T1_2;
	unsigned short T1_3;
	unsigned short T1_4;
	unsigned short T1_5;
	unsigned short T1_6;
	unsigned short T1_7;
	unsigned short T1_8;
	unsigned short T2_1;
	unsigned short T2_2;
	unsigned short T2_3;
	unsigned short T2_4;
	unsigned short T2_5;
	unsigned short T2_6;
	unsigned short T2_7;
	unsigned short T2_8;
	unsigned short T3_1;
	unsigned short T3_2;
	unsigned short T3_3;
	unsigned short T3_4;
	unsigned short T3_5;
	unsigned short T3_6;
	unsigned short T3_7;
	unsigned short T3_8;
	unsigned short T4_1;
	unsigned short T4_2;
	unsigned short T4_3;
	unsigned short T4_4;
	unsigned short T4_5;
	unsigned short T4_6;
	unsigned short T4_7;
	unsigned short T4_8;
	unsigned short T5_1;
	unsigned short T5_2;
	unsigned short T5_3;
	unsigned short T5_4;
	unsigned short T5_5;
	unsigned short T5_6;
	unsigned short T5_7;
	unsigned short T5_8;
	unsigned short T6_1;
	unsigned short T6_2;
	unsigned short T6_3;
	unsigned short T6_4;
	unsigned short T6_5;
	unsigned short T6_6;
	unsigned short T6_7;
	unsigned short T6_8;
	unsigned short T7_1;
	unsigned short T7_2;
	unsigned short T7_3;
	unsigned short T7_4;
	unsigned short T7_5;
	unsigned short T7_6;
	unsigned short T7_7;
	unsigned short T7_8;

}USB_TORQUE_vol;
typedef struct
{
	unsigned short T1_1;
	unsigned short T1_2;
	unsigned short T1_3;
	unsigned short T1_4;
	unsigned short T1_5;
	unsigned short T1_6;
	unsigned short T1_7;
	unsigned short T1_8;
	unsigned short T2_1;
	unsigned short T2_2;
	unsigned short T2_3;
	unsigned short T2_4;
	unsigned short T2_5;
	unsigned short T2_6;
	unsigned short T2_7;
	unsigned short T2_8;
	unsigned short T3_1;
	unsigned short T3_2;
	unsigned short T3_3;
	unsigned short T3_4;
	unsigned short T3_5;
	unsigned short T3_6;
	unsigned short T3_7;
	unsigned short T3_8;
	unsigned short T4_1;
	unsigned short T4_2;
	unsigned short T4_3;
	unsigned short T4_4;
	unsigned short T4_5;
	unsigned short T4_6;
	unsigned short T4_7;
	unsigned short T4_8;
	unsigned short T5_1;
	unsigned short T5_2;
	unsigned short T5_3;
	unsigned short T5_4;
	unsigned short T5_5;
	unsigned short T5_6;
	unsigned short T5_7;
	unsigned short T5_8;
	unsigned short T6_1;
	unsigned short T6_2;
	unsigned short T6_3;
	unsigned short T6_4;
	unsigned short T6_5;
	unsigned short T6_6;
	unsigned short T6_7;
	unsigned short T6_8;
	unsigned short T7_1;
	unsigned short T7_2;
	unsigned short T7_3;
	unsigned short T7_4;
	unsigned short T7_5;
	unsigned short T7_6;
	unsigned short T7_7;
	unsigned short T7_8;

}USB_TORQUE_cur;
//extern TEST_Point test_point;
extern USB_0420   usb_0420;
extern USB_TORQUE_vol usb_torque_vol;
extern USB_TORQUE_cur usb_torque_cur;
extern LED led;
extern EXTERN_IO    ext_IO;
extern USART  uart3;
extern USART2       uart2;
extern EEPROM eeprom;
extern KEY key_mlx90363;
extern I_0420  ai_o420;
extern STATES  states;
extern DATA_FIGURES data_figures;
extern FLAG_FIGURES flag_figures;
extern Stateserror  states_error;
extern PowerBoard  powerboard;
extern Timer        timer;
extern LEDSTATES        ledstates;
extern REMOTE    remote_conntrol;
extern FLASH_flag    flash_flag;
extern SET_END   set_end;
extern MOTOR_RUN  motorset;
extern ENCODER  encoder;
extern LCD lcd;
extern DIAGNOSE diagnose;
extern WRITE_EEPROM       write_to_eeprom;
extern PASS_WORD password;

int enc_utf8_to_unicode_one1(char* pInput, unsigned long *Unic) ;
 void Utf8ToUnicode(char* unicode, char *utf8);
void Utf8ToUnicode1(char* unicode, char *utf8);
#endif