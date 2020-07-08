#include "EEPROM.h"
#include  "datafigures.h"
#include "DataInterface.h"

char eeprom_buffer[5];
char eeprom_read[5];

char WRITE_READ_EEPROM(char function,short address,char data)
{
	int i=0;
	unsigned short retdata;
	short  test1,test2,test3;
	Init_EESPI0_EN();
	{
	states_EEPROM();
	}
	states_spi0(1);
	eeprom_buffer[0]=function;
	eeprom_buffer[1] = (address/256)&0xFF;
	eeprom_buffer[2] = (address%256)&0xFF;
	eeprom_buffer[3] = (data)&0xFF;


	for(i=0;i<4;i++)
	{
		eeprom_read[i]=SPI0_ReadWrite(eeprom_buffer[i]);
	}
	states_spi0(0);
	Delay();
	retdata=eeprom_read[3]&0xFFFF;
	return retdata;
}


int states_EEPROM(void)
{
	int i=0;
	int retdata;
	states_spi0(1);
	SPI0_ReadWrite(EEProm_writeenable);
	SPI0_ReadWrite(EEProm_readregistor);	
	SPI0_ReadWrite(EEProm_writeregister);
	Delay();
	states_spi0(0);
	Delay();
}

/*
void set_eeprom(void)
{				
    eeprom.speed_open=0x28;   write_to_eeprom.flag_speed_open= 1;
	eeprom.test1=0x14;        write_to_eeprom.flag_test1        	= 1;
	eeprom.speed_close=0x28;  write_to_eeprom.flag_speed_close  	= 1;
	eeprom.test2=0x14;        write_to_eeprom.flag_test2        	= 1;
	eeprom.moment_close=0x1E;  write_to_eeprom.flag_moment_close 	= 1;
	eeprom.test3=0x24;         write_to_eeprom.flag_test3        	= 1;
	eeprom.moment_open=0x1E;   write_to_eeprom.flag_moment_open  	= 1;
	eeprom.test4=0x2A;         write_to_eeprom.flag_test4        	= 1;
	eeprom.dir_flag=0x02;      write_to_eeprom.flag_dir_flag     	= 1;
	eeprom.openOffMode=0x00;   write_to_eeprom.flag_openOffMode  	= 1;
	eeprom.closeOffMode=0x00;  write_to_eeprom.flag_closeOffMode 	= 1;
	data_figures.READ_ALL_903=20*4096;
	dataStructInterface.endPosClose=0x02;   write_to_eeprom.flag_ctrlMode     	= 1;
	dataStructInterface.endPosOpen=0x62;    write_to_eeprom.flag_closeDir     	= 1;
	g_deviceState=0;
	eeprom.ctrlMode=0x03;
	eeprom.closeDir=0x00;
	eeprom.out1=0x00FF;
	eeprom.out2=0x00FF;
	eeprom.out3=0x00FF;
	eeprom.out4=0x00FF;
	eeprom.out5=0x00FF;
	eeprom.out6=0x00FF;
	eeprom.out7=0x00FF;
	eeprom.out8=0x00FF;
	eeprom.out_of_1=0x00FF;
	eeprom.out_of_2=0x00FF;
	eeprom.out_of_3=0x00FF;
	eeprom.out_of_4=0x00FF;
	eeprom.out_of_5=0x00FF;
	eeprom.out_of_6=0x00FF;
	eeprom.out_of_7=0x00FF;
	eeprom.out_of_8=0x0000;	
}*/


void read_eeprom(void)
{
	eeprom.speed_open=WRITE_READ_EEPROM(0x03,1,0x00)&0xff;
	Delay();
	eeprom.test1=WRITE_READ_EEPROM(0x03,2,0x00)&0xff;
	Delay();
	eeprom.speed_close=WRITE_READ_EEPROM(0x03,3,0x00)&0xff;
	Delay();
	eeprom.test2=WRITE_READ_EEPROM(0x03,4,0x00)&0xff;
	Delay();
	eeprom.moment_close=WRITE_READ_EEPROM(0x03,5,0x00)&0xff;
	Delay();
	eeprom.test3=WRITE_READ_EEPROM(0x03,6,0x00)&0xff;
	Delay();
	eeprom.moment_open=WRITE_READ_EEPROM(0x03,7,0x00)&0xff;
	Delay();
	eeprom.test4=WRITE_READ_EEPROM(0x03,8,0x00)&0xff;
	Delay();
	eeprom.dir_flag=WRITE_READ_EEPROM(0x03,9,0x00)&0xff;
	Delay();
	eeprom.openOffMode=WRITE_READ_EEPROM(0x03,11,0x00)&0xff;
	Delay();
	eeprom.closeOffMode=WRITE_READ_EEPROM(0x03,13,0x00)&0xff;
	Delay();
	data_figures.READ_ALL_903_1=(WRITE_READ_EEPROM(0x03,20,0x00)<<24)+
                                (WRITE_READ_EEPROM(0x03,21,0x00)<<16)+
                                (WRITE_READ_EEPROM(0x03,22,0x00)<<8)+
                                (WRITE_READ_EEPROM(0x03,23,0x00));
	data_figures.READ_ALL_903=data_figures.READ_ALL_903_1;
	Delay();
	eeprom.endPosClose=WRITE_READ_EEPROM(0x03,32,0x00)&0xff;
	Delay();
	eeprom.endPosOpen=WRITE_READ_EEPROM(0x03,34,0x00)&0xff;
	Delay();
    
    //目测没用
	g_deviceState=WRITE_READ_EEPROM(0x03,36,0x00)&0xff;
	if((g_deviceState!=0)&&(g_deviceState!=1)&&(g_deviceState!=2)&&(g_deviceState!=3)&&(g_deviceState!=4))
	{
		g_deviceState=0;
	}
	Delay();
    //
    
	eeprom.ctrlMode=WRITE_READ_EEPROM(0x03,37,0x00)&0xff;
	Delay();
	eeprom.closeDir=WRITE_READ_EEPROM(0x03,50,0x00)&0xff;
	Delay();
	eeprom.out1=WRITE_READ_EEPROM(0x03,60,0x00)&0xff;
	ext_IO.eep_TEST_of1=eeprom.out1;
	Delay();
	eeprom.out2=WRITE_READ_EEPROM(0x03,62,0x00)&0xff;
	ext_IO.eep_TEST_of2=eeprom.out2;
	Delay();
	eeprom.out3=WRITE_READ_EEPROM(0x03,64,0x00)&0xff;
	ext_IO.eep_TEST_of3=eeprom.out3;
	Delay();
	eeprom.out4=WRITE_READ_EEPROM(0x03,66,0x00)&0xff;
	ext_IO.eep_TEST_of4=eeprom.out4;
	Delay();
	eeprom.out5=WRITE_READ_EEPROM(0x03,68,0x00)&0xff;
	ext_IO.eep_TEST_of5=eeprom.out5;
	Delay();
	eeprom.out6=WRITE_READ_EEPROM(0x03,70,0x00)&0xff;
	ext_IO.eep_TEST_of6=eeprom.out6;
	Delay();
	eeprom.out7=WRITE_READ_EEPROM(0x03,72,0x00)&0xff;
	ext_IO.eep_TEST_of7=eeprom.out7;
	Delay();
	eeprom.out8=WRITE_READ_EEPROM(0x03,74,0x00)&0xff;
	ext_IO.eep_TEST_of8=eeprom.out8;
	Delay();
	#if 1
	eeprom.out_of_1=WRITE_READ_EEPROM(0x03,76,0x00)&0xff;
	ext_IO.eep_TEST2_of1=eeprom.out_of_1;
	Delay();
	eeprom.out_of_2=WRITE_READ_EEPROM(0x03,78,0x00)&0xff;
	ext_IO.eep_TEST2_of2=eeprom.out_of_2;
	Delay();
	eeprom.out_of_3=WRITE_READ_EEPROM(0x03,80,0x00)&0xff;
	ext_IO.eep_TEST2_of3=eeprom.out_of_3;
	Delay();
	eeprom.out_of_4=WRITE_READ_EEPROM(0x03,82,0x00)&0xff;
	ext_IO.eep_TEST2_of4=eeprom.out_of_4;
	Delay();
	eeprom.out_of_5=WRITE_READ_EEPROM(0x03,84,0x00)&0xff;
	ext_IO.eep_TEST2_of5=eeprom.out_of_5;
	Delay();
	eeprom.out_of_6=WRITE_READ_EEPROM(0x03,86,0x00)&0xff;
	ext_IO.eep_TEST2_of6=eeprom.out_of_6;
	Delay();
	eeprom.out_of_7=WRITE_READ_EEPROM(0x03,88,0x00)&0xff;
	ext_IO.eep_TEST2_of7=eeprom.out_of_7;
	Delay();
	eeprom.out_of_8=WRITE_READ_EEPROM(0x03,90,0x00)&0xff;
	ext_IO.eep_TEST2_of8=eeprom.out_of_8;
	Delay();
	#endif
	encoder.num=WRITE_READ_EEPROM(0x03,94,0x00)&0xff;
	Delay();
	motorset.DIR=WRITE_READ_EEPROM(0x03,96,0x00)&0xff;
	Delay();
	dataStructInterface.emergency_pos=WRITE_READ_EEPROM(0x03,98,0x00)&0xff;
	dataStructInterface.emergency_pos=dataStructInterface.emergency_pos/*+1*/;
	if(dataStructInterface.emergency_pos>100)
	{dataStructInterface.emergency_pos=0;}
	Delay();
	eeprom.emg_speed_close=WRITE_READ_EEPROM(0x03,110,0x00)&0xff;
	Delay();
	eeprom.emg_speed_open=WRITE_READ_EEPROM(0x03,112,0x00)&0xff;
	Delay();
    
    //ai_o420.G0420_slope=1815;   //20200701三方检测精度
    //ai_o420.G0420_slope=2002;     //20200702自家测试检测精度
    ai_o420.G0420_slope=1988;     //20200706自家老板子检测精度
	Delay();
    //ai_o420.G0420_offset=365;   //20200701三方检测精度
    //ai_o420.G0420_offset=400;     //20200702自家测试检测精度
    ai_o420.G0420_offset=397;     //20200706自家老板子检测精度
	Delay();
    //ai_o420.G0420_OUT_slope=17600;  //20200701三方检测精度
    //ai_o420.G0420_OUT_slope=16932;    //20200702自家测试检测精度
    ai_o420.G0420_OUT_slope=17122;    //20200706自家老板子检测精度
	Delay();
    //ai_o420.G0420_OUT_offset=14300;  //20200701三方检测精度
    //ai_o420.G0420_OUT_offset=13560;    //20200702自家测试检测精度
    ai_o420.G0420_OUT_offset=13795;    //20200706自家老板子检测精度
	Delay();
	dataStructInterface.showDirect=WRITE_READ_EEPROM(0x03,122,0x00)&0xff;
	Delay();
	
	password.g_password_handle=((WRITE_READ_EEPROM(0x03,124,0x00)&0xff)<<8)+(WRITE_READ_EEPROM(0x03,126,0x00)&0xff);
	Delay();				
	password.g_password_viewer=((WRITE_READ_EEPROM(0x03,128,0x00)&0xff)<<8)+(WRITE_READ_EEPROM(0x03,130,0x00)&0xff);	
	Delay();				
	password.g_password_expert=((WRITE_READ_EEPROM(0x03,132,0x00)&0xff)<<8)+(WRITE_READ_EEPROM(0x03,134,0x00)&0xff);	
	Delay();				
	password.g_password_service=((WRITE_READ_EEPROM(0x03,136,0x00)&0xff)<<8)+(WRITE_READ_EEPROM(0x03,138,0x00)&0xff);
	Delay();				
	password.g_password_factroy=((WRITE_READ_EEPROM(0x03,140,0x00)&0xff)<<8)+(WRITE_READ_EEPROM(0x03,142,0x00)&0xff);
	Delay();
	
	if(password.g_password_handle==0xFFFF)
	{
		password.g_password_handle=9044;
	}
	if(password.g_password_viewer==0xFFFF)
	{
		password.g_password_viewer=9044;
	}
	#if 1
	if(password.g_password_expert==0xFFFF)
	{
		password.g_password_expert=9044;
	}
	#endif
	if(password.g_password_service==0xFFFF)
	{
		password.g_password_service=9999;
	}
	if(password.g_password_factroy==0xFFFF)
	{
		password.g_password_factroy=9999;
	}
	Delay();
	g_deviceState=WRITE_READ_EEPROM(0x03,144,0x00)&0xff;
	if(g_deviceState==0xff)
	{
		g_deviceState=0;
	}
	Delay();
	eeprom.krInput_save=WRITE_READ_EEPROM(0x03,146,0x00)&0xff;
	if(eeprom.krInput_save==0xff)
	{
		eeprom.krInput_save=0;
	}
	Delay();
	eeprom.rmtChoose=WRITE_READ_EEPROM(0x03,148,0x00)&0xff;
	if(eeprom.rmtChoose==0xff)
	{
		eeprom.rmtChoose=0;
	}
	Delay();
	eeprom.emgInput=WRITE_READ_EEPROM(0x03,150,0x00)&0xff;
	if(eeprom.emgInput==0xff)
	{
		eeprom.emgInput=0;
	}
	Delay();
}

char test005_1=0xda;
char test005_2=0xdb;
char test005_3=0xdc;
char test005_4=0xdd;
char save_end_num;

/*void set_write_eeprom(void)
{
	int i;
				
	if(write_to_eeprom.flag_speed_open   	== 1)
	{
	WRITE_READ_EEPROM(0x02,1,dataStructInterface.speed_open);
		write_to_eeprom.flag_speed_open   	=0;
	}
	if(eeprom.flag_speed_close==1)
	{
		WRITE_READ_EEPROM(0x02,3,dataStructInterface.speed_close);
		eeprom.flag_speed_close=0;
	}
}*/

void write_eeprom(void)
{
	int i;
	if(eeprom.flag_speed_open==1)
	{
        WRITE_READ_EEPROM(0x02,1,dataStructInterface.speed_open);
        if(save_end_num>20)
		{
			eeprom.flag_speed_open=0;
			save_end_num=0;
		}				
	}
	if(eeprom.flag_speed_close==1)
	{
		WRITE_READ_EEPROM(0x02,3,dataStructInterface.speed_close);
		eeprom.flag_speed_close=0;
	}
	if(eeprom.flag_moment_close==1)
	{
		WRITE_READ_EEPROM(0x02,5,dataStructInterface.moment_close);
		eeprom.flag_moment_close=0;
	}
	if(eeprom.flag_moment_open==1)
	{
        WRITE_READ_EEPROM(0x02,7,dataStructInterface.moment_open);
		eeprom.flag_moment_open=0;
	}
	if(eeprom.flag_90363==1)
	{
		WRITE_READ_EEPROM(0x02,9,encoder.dir_flag);
		eeprom.flag_90363=0;
	}
	if(eeprom.flag_closeOffMode==1)
	{
		if(eeprom.flag_UI_closeOffMode==1)
		{
			WRITE_READ_EEPROM(0x02,13,1);
		}else
		if(eeprom.flag_UI_closeOffMode==0)
		{
			WRITE_READ_EEPROM(0x02,13,0);
		}					
		eeprom.flag_closeOffMode=0;
	}
	if(eeprom.flag_openOffMode==1)
	{
		if(eeprom.flag_UI_openOffMode==0)
		{
            WRITE_READ_EEPROM(0x02,11,0);
		}else
		if(eeprom.flag_UI_openOffMode==1)
		{
            WRITE_READ_EEPROM(0x02,11,1);
		}
		eeprom.flag_openOffMode=0;
	}
    test005_1=((data_figures.READ_ALL_903&0x0f000000)>>24)&0x00ff;
    test005_2=((data_figures.READ_ALL_903&0x00ff0000)>>16)&0x00ff;
    test005_3=((data_figures.READ_ALL_903&0x0000ff00)>>8)&0x00ff;
    test005_4=((data_figures.READ_ALL_903&0x000000ff))&0x00ff;				
	if(flash_flag.all_move==1)
	{
		WRITE_READ_EEPROM(0x02,20,test005_1);	
		WRITE_READ_EEPROM(0x02,21,test005_2);	
		WRITE_READ_EEPROM(0x02,22,test005_3);	
		WRITE_READ_EEPROM(0x02,23,test005_4);	
		
		save_end_num++;
		if(save_end_num>20)
		{
			flash_flag.all_move=0;
			save_end_num=0;
		}
	}
	if(eeprom.flag_endPosClose==1)
	{
		WRITE_READ_EEPROM(0x02,32,dataStructInterface.endPosClose);	
		eeprom.flag_endPosClose=0;
	}
	if(eeprom.flag_endPosOpen==1)
	{
		WRITE_READ_EEPROM(0x02,34,dataStructInterface.endPosOpen);
		save_end_num++;
		if(save_end_num>20)
		{
			eeprom.flag_endPosOpen=0;
			save_end_num=0;
		}
		
	}
	if(eeprom.flag_ctrlMode==1)
	{
		WRITE_READ_EEPROM(0x02,37,eeprom.ctrlMode_save);
		eeprom.flag_ctrlMode=0;
	}
	if(eeprom.flag_closeDir==1)
	{
		WRITE_READ_EEPROM(0x02,50,eeprom.closeDir_save);
		eeprom.flag_closeDir=0;
	}
	
	if(ext_IO.eep_save_out1==1)
	{
		WRITE_READ_EEPROM(0x02,60,ext_IO.eep_TEST_of1);
		ext_IO.eep_save_out1=0;
	}
	if(ext_IO.eep_save_out2==1)
	{
		WRITE_READ_EEPROM(0x02,62,ext_IO.eep_TEST_of2);
		ext_IO.eep_save_out2=0;
	}
	if(ext_IO.eep_save_out3==1)
	{
		WRITE_READ_EEPROM(0x02,64,ext_IO.eep_TEST_of3);
		ext_IO.eep_save_out3=0;
	}
	if(ext_IO.eep_save_out4==1)
	{
		WRITE_READ_EEPROM(0x02,66,ext_IO.eep_TEST_of4);
		ext_IO.eep_save_out4=0;
	}
	if(ext_IO.eep_save_out5==1)
	{
		WRITE_READ_EEPROM(0x02,68,ext_IO.eep_TEST_of5);
		ext_IO.eep_save_out5=0;
	}
	if(ext_IO.eep_save_out6==1)
	{
		WRITE_READ_EEPROM(0x02,70,ext_IO.eep_TEST_of6);
		ext_IO.eep_save_out6=0;
	}
	if(ext_IO.eep_save_out7==1)
	{
		WRITE_READ_EEPROM(0x02,72,ext_IO.eep_TEST_of7);
		ext_IO.eep_save_out7=0;
	}
	if(ext_IO.eep_save_out8==1)
	{
		WRITE_READ_EEPROM(0x02,74,ext_IO.eep_TEST_of8);
		ext_IO.eep_save_out8=0;
	}
	
	if(ext_IO.eep_save_of1==1)
	{
		WRITE_READ_EEPROM(0x02,76,ext_IO.eep_TEST2_of1);
		ext_IO.eep_save_of1=0;
	}
	if(ext_IO.eep_save_of2==1)
	{
		WRITE_READ_EEPROM(0x02,78,ext_IO.eep_TEST2_of2);
		ext_IO.eep_save_of2=0;
	}
	if(ext_IO.eep_save_of3==1)
	{
		WRITE_READ_EEPROM(0x02,80,ext_IO.eep_TEST2_of3);
		ext_IO.eep_save_of3=0;
	}
	if(ext_IO.eep_save_of4==1)
	{
		WRITE_READ_EEPROM(0x02,82,ext_IO.eep_TEST2_of4);
		ext_IO.eep_save_of4=0;
	}
	if(ext_IO.eep_save_of5==1)
	{
		WRITE_READ_EEPROM(0x02,84,ext_IO.eep_TEST2_of5);
		ext_IO.eep_save_of5=0;
	}
	if(ext_IO.eep_save_of6==1)
	{
		WRITE_READ_EEPROM(0x02,86,ext_IO.eep_TEST2_of6);
		ext_IO.eep_save_of6=0;
	}
	if(ext_IO.eep_save_of7==1)
	{
		WRITE_READ_EEPROM(0x02,88,ext_IO.eep_TEST2_of7);
		ext_IO.eep_save_of7=0;
	}
	if(ext_IO.eep_save_of8==1)
	{
		WRITE_READ_EEPROM(0x02,90,ext_IO.eep_TEST2_of8);
		ext_IO.eep_save_of8=0;
	}
	if(encoder.Set2EE_flag==1)
	{
		WRITE_READ_EEPROM(0x02,94,encoder.num);
		encoder.Set2EE_flag=0;
	}
	if(motorset.DIR_set_flag==1)
	{
		WRITE_READ_EEPROM(0x02,96,motorset.DIR);
		motorset.DIR_set_flag=0;
	}
	if(eeprom.Save_eme_pos==1)
	{
		WRITE_READ_EEPROM(0x02,98,(dataStructInterface.emergency_pos/*-1*/));
		eeprom.Save_eme_pos=0;
	}
	if(eeprom.Save_emg_speed_close_flag==1)
	{
		WRITE_READ_EEPROM(0x02,110,eeprom.emg_speed_close_ee);					
        save_end_num++;
		if(save_end_num>20)
		{
			eeprom.Save_emg_speed_close_flag=0;
			save_end_num=0;
		}
	}

	if(eeprom.Save_emg_speed_open_flag==1)
	{
		WRITE_READ_EEPROM(0x02,112,eeprom.emg_speed_open_ee);
        save_end_num++;
		if(save_end_num>20)
		{
			eeprom.Save_emg_speed_open_flag=0;
			save_end_num=0;
		}
	}
	if(ai_o420.flag_save0420_s==1)
	{
		WRITE_READ_EEPROM(0x02,113,(ai_o420.G0420_slope/256)&0xFF);
		WRITE_READ_EEPROM(0x02,114,(ai_o420.G0420_slope%256)&0xFF);
		Delay();
		save_end_num++;
		if(save_end_num>20)
		{
			ai_o420.flag_save0420_s=0;
            ai_o420.flag_save0420_o=1;
			save_end_num=0;
		}
	}
	if(ai_o420.flag_save0420_o==1)
	{
		WRITE_READ_EEPROM(0x02,115,(ai_o420.G0420_offset/256)&0xFF);
		WRITE_READ_EEPROM(0x02,116,(ai_o420.G0420_offset%256)&0xFF);
		Delay();
		save_end_num++;
		if(save_end_num>20)
		{
			ai_o420.flag_save0420_o=0;
            ai_o420.flag_save0420_o_s=1;
			save_end_num=0;
		}
	}
	if(ai_o420.flag_save0420_o_s==1)
	{
		WRITE_READ_EEPROM(0x02,117,(ai_o420.G0420_OUT_slope/256)&0xFF);
		WRITE_READ_EEPROM(0x02,118,(ai_o420.G0420_OUT_slope%256)&0xFF);
		Delay();
		save_end_num++;
		if(save_end_num>20)
		{
			ai_o420.flag_save0420_o_s=0;
            ai_o420.flag_save0420_o_o=1;
			save_end_num=0;
		}
	}
	if(ai_o420.flag_save0420_o_o==1)
	{																					
		WRITE_READ_EEPROM(0x02,119,(ai_o420.G0420_OUT_offset/256)&0xFF);
		WRITE_READ_EEPROM(0x02,120,(ai_o420.G0420_OUT_offset%256)&0xFF);
		Delay();
		save_end_num++;
		if(save_end_num>20)
		{
			ai_o420.flag_save0420_o_o=0;
			save_end_num=0;
		}
	}
	if(eeprom.showDirect==1)
	{
		WRITE_READ_EEPROM(0x02,122,(dataStructInterface.showDirect)&0xFF);
		eeprom.showDirect=0;
	}
    if(eeprom.flag_g_password_handle==1)
	{					
		WRITE_READ_EEPROM(0x02,124,(password.g_password_handle/256)&0xFF);
		WRITE_READ_EEPROM(0x02,126,(password.g_password_handle%256)&0xFF);
		save_end_num++;
		if(save_end_num>20)
		{
			eeprom.flag_g_password_handle=0;
			save_end_num=0;
		}
	}
	
    if(eeprom.flag_g_password_viewer==1)
	{					
		WRITE_READ_EEPROM(0x02,128,(password.g_password_viewer/256)&0xFF);
		WRITE_READ_EEPROM(0x02,130,(password.g_password_viewer%256)&0xFF);
		save_end_num++;
		if(save_end_num>20)
		{
			eeprom.flag_g_password_viewer=0;
			save_end_num=0;
		}
	}			
    if(eeprom.flag_g_password_expert==1)
	{					
		WRITE_READ_EEPROM(0x02,132,(password.g_password_expert/256)&0xFF);
		WRITE_READ_EEPROM(0x02,134,(password.g_password_expert%256)&0xFF);
		save_end_num++;
		if(save_end_num>20)
		{
			eeprom.flag_g_password_expert=0;
			save_end_num=0;
		}
	}
	
    if(eeprom.flag_g_password_service==1)
	{					
		WRITE_READ_EEPROM(0x02,136,(password.g_password_service/256)&0xFF);
		WRITE_READ_EEPROM(0x02,138,(password.g_password_service%256)&0xFF);
		save_end_num++;
		if(save_end_num>20)
		{
			eeprom.flag_g_password_service=0;
			save_end_num=0;
		}
	}
	
    if(eeprom.flag_g_password_factroy==1)
	{					
		WRITE_READ_EEPROM(0x02,140,(password.g_password_factroy/256)&0xFF);
		WRITE_READ_EEPROM(0x02,142,(password.g_password_factroy%256)&0xFF);
		save_end_num++;
		if(save_end_num>20)
		{
			eeprom.flag_g_password_factroy=0;
			save_end_num=0;
		}
	}
    if(eeprom.g_deviceState_flag==1)
	{					
		WRITE_READ_EEPROM(0x02,144,(g_deviceState)&0xFF);
		eeprom.g_deviceState_flag=0;
	}
	if(eeprom.flag_krInput==1)
	{					
		WRITE_READ_EEPROM(0x02,146,(eeprom.krInput_save)&0xFF);
		save_end_num++;
        if(save_end_num>20)
		{
			eeprom.flag_krInput=0;
			save_end_num=0;
		}
	}
	
    if(eeprom.flag_rmtChoose==1)
	{					
		WRITE_READ_EEPROM(0x02,148,(eeprom.rmtChoose)&0xFF);
		save_end_num++;
        if(save_end_num>20)
		{
			eeprom.flag_rmtChoose=0;
			save_end_num=0;
		}
	}
	
    if(eeprom.flag_emgInput==1)
	{					
		WRITE_READ_EEPROM(0x02,150,(eeprom.emgInput)&0xFF);
		save_end_num++;
        if(save_end_num>20)
		{
			eeprom.flag_emgInput=0;
			save_end_num=0;
		}
	}
}


uint8_t eeprom_buffer1[37];uint8_t eeprom_read1[32];
char *WRITE_READ_EEPROM_PAGE(char function,short address,uint32_t data[4])
{
	int i=0;
	char retdata[5];
	short  test1,test2,test3;
	uint8_t eeprom_send[32];
	{
	states_EEPROM();
	}
	states_spi0(1);
	eeprom_buffer1[ 0] =  function;
	eeprom_buffer1[ 1] = (address/256)&0xFF;
	eeprom_buffer1[ 2] = (address%256)&0xFF;
	eeprom_buffer1[ 3] = eeprom_send[ 0] = ( ((data[0]/65536)/256))&0xFF;       
	eeprom_buffer1[ 4] = eeprom_send[ 1] = ( ((data[0]/65536)%256))&0xFF;       
	eeprom_buffer1[ 5] = eeprom_send[ 2] = ( ((data[0]%65536)/256))&0xFF;       
	eeprom_buffer1[ 6] = eeprom_send[ 3] = ( ((data[0]%65536)%256))&0xFF;       
	eeprom_buffer1[ 7] = eeprom_send[ 4] = (~((data[0]/65536)/256))&0xFF;       
	eeprom_buffer1[ 8] = eeprom_send[ 5] = (~((data[0]/65536)%256))&0xFF;       
	eeprom_buffer1[ 9] = eeprom_send[ 6] = (~((data[0]%65536)/256))&0xFF;       
	eeprom_buffer1[10] = eeprom_send[ 7] = (~((data[0]%65536)%256))&0xFF;       
	eeprom_buffer1[11] = eeprom_send[ 8] = ( ((data[1]/65536)/256))&0xFF;       
	eeprom_buffer1[12] = eeprom_send[ 9] = ( ((data[1]/65536)%256))&0xFF;       
	eeprom_buffer1[13] = eeprom_send[10] = ( ((data[1]%65536)/256))&0xFF;       
	eeprom_buffer1[14] = eeprom_send[11] = ( ((data[1]%65536)%256))&0xFF;       
	eeprom_buffer1[15] = eeprom_send[12] = (~((data[1]/65536)/256))&0xFF;       
	eeprom_buffer1[16] = eeprom_send[13] = (~((data[1]/65536)%256))&0xFF;       
	eeprom_buffer1[17] = eeprom_send[14] = (~((data[1]%65536)/256))&0xFF;       
	eeprom_buffer1[18] = eeprom_send[15] = (~((data[1]%65536)%256))&0xFF;       
	eeprom_buffer1[19] = eeprom_send[16] = ( ((data[2]/65536)/256))&0xFF;       
	eeprom_buffer1[20] = eeprom_send[17] = ( ((data[2]/65536)%256))&0xFF;       
	eeprom_buffer1[21] = eeprom_send[18] = ( ((data[2]%65536)/256))&0xFF;       
	eeprom_buffer1[22] = eeprom_send[19] = ( ((data[2]%65536)%256))&0xFF;       
	eeprom_buffer1[23] = eeprom_send[20] = (~((data[2]/65536)/256))&0xFF;       
	eeprom_buffer1[24] = eeprom_send[21] = (~((data[2]/65536)%256))&0xFF;       
	eeprom_buffer1[25] = eeprom_send[22] = (~((data[2]%65536)/256))&0xFF;      
	eeprom_buffer1[26] = eeprom_send[23] = (~((data[2]%65536)%256))&0xFF;      
	eeprom_buffer1[27] = eeprom_send[24] = ( ((data[3]/65536)/256))&0xFF;      
	eeprom_buffer1[28] = eeprom_send[25] = ( ((data[3]/65536)%256))&0xFF;      
	eeprom_buffer1[29] = eeprom_send[26] = ( ((data[3]%65536)/256))&0xFF;      
	eeprom_buffer1[30] = eeprom_send[27] = ( ((data[3]%65536)%256))&0xFF;      
	eeprom_buffer1[31] = eeprom_send[28] = (~((data[3]/65536)/256))&0xFF;      
	eeprom_buffer1[32] = eeprom_send[29] = (~((data[3]/65536)%256))&0xFF;      
	eeprom_buffer1[33] = eeprom_send[30] = (~((data[3]%65536)/256))&0xFF;      
	eeprom_buffer1[34] = eeprom_send[31] = (~((data[3]%65536)%256))&0xFF;      
	eeprom_buffer1[35] = (CRC_Compute(eeprom_buffer1,32)/256)&0xFF;
	eeprom_buffer1[36] = (CRC_Compute(eeprom_buffer1,32)%256)&0xFF;
	for(i=0;i<37;i++)     
	{                    
		eeprom_read1[i]=SPI0_ReadWrite(eeprom_buffer[i]);
	}
	states_spi0(0);
	Delay();
	retdata[0]=eeprom_read1[0];
	return retdata;
}



