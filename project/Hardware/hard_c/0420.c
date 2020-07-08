#include "0420.h"
#include "SPI.h"
#include "Handler.h"
#include  "datafigures.h"
#include "DataInterface.h"
#include  "define.h"
#include "USB_MAIN.h"


void Init_Analog(void)
{
		SSP_CFG_Type SSP_ConfigStruct;
		scu_pinmux(SSP0_SCK_PORT, SSP0_SCK_PORT_PIN, MD_PLN_FAST, SSP0_SCK_PORT_FUNC);  
		scu_pinmux(SSP0_MOSI_PORT, SSP0_MOSI_PORT_PIN, MD_PLN_FAST, SSP0_MOSI_PORT_FUNC);  
		scu_pinmux(SSP0_MISO_PORT,SSP0_MISO_PORT_PIN, MD_PLN_FAST, SSP0_MISO_PORT_FUNC); 
		scu_pinmux(EN_AI1_PORT, EN_AI1_PORT_PIN, MD_PDN,  EN_AI1_PORT_FUNC);      
		GPIO_SetDir(EN_AI1_GPIO,(1 << EN_AI1_GPIO_PIN), 1);  
		scu_pinmux(EN_AO1_PORT, EN_AO1_PORT_PIN, MD_PDN, EN_AO1_PORT_FUNC);       
		GPIO_SetDir(EN_AO1_GPIO,(1 << EN_AO1_GPIO), 1); 
	
		SSP_ConfigStructInit(&SSP_ConfigStruct);
		SSP_Init(LPC_SSP0, &SSP_ConfigStruct);
		SSP_Cmd(LPC_SSP0, ENABLE);

		GPIO_SetValue(EN_AI1_GPIO,(1<<EN_AI1_GPIO_PIN));
		GPIO_SetValue(EN_AO1_GPIO,(1<<EN_AO1_GPIO_PIN));
}
void c_entry_AO1(int dac )
{
    int i=0;
    float A_;
    float U_;
    float o420_L,o420_H,o420_UP,o420_DOWN;
    float o420_k,o420_b;
    int o420_flag;
    int A_123;
    float A_1;
    float A_a;
    float A_x;
    float A_y;
	uint16_t  U_IN,U_OUT;
	uint8_t U_OUT_H,U_OUT_L;
	A_=10;
    
	Init_EESPI0_ADDA_EN();
	if(ai_o420.flag_O_0020==1)
	{
		ai_o420.flag_O_0420=0;
		o420_k=0.2;
		o420_b=0;
	}else
	if(ai_o420.flag_O_0420==1)
	{
		ai_o420.flag_O_0020=0;
		o420_k=0.16;
		o420_b=4;
	}
		if(ai_o420.flag_O_up==1)
	{
			ai_o420.flag_O_down=0;
		o420_flag=1;
	}else
	if(ai_o420.flag_O_down==1)
	{
		ai_o420.flag_O_up=0;
		o420_b=20;
		o420_flag=-1;
	}	
	if(dac>10000)
	{dac=0;}else
	if(dac>1000)
	{dac=1000;}
	if(encoder.num==6)
	{
		if(dac<-1000)
		{
			dac=1000;
		}
	}
	A_=o420_flag*o420_k*((float)(dac/10.0))+o420_b;
	#if 1
	A_1=A_;
	A_123=(A_*10);
	A_x=A_123/10;
	A_y=A_123%10;
	A_a=A_x+(A_y*0.1);
	ai_o420.AO_0420_UI=A_a;
	#endif
	if((ai_o420.AO_0420_UI<=4))
	{
		ai_o420.AO_0420_UI=4;
	}else
	if((ai_o420.AO_0420_UI>=20))
	{
		ai_o420.AO_0420_UI=20;
	}
    
    /*输出模拟量调整*/
	U_=(((float)((ai_o420.G0420_OUT_slope-ai_o420.G0420_OUT_offset)/16.0)/1000.0)*(ai_o420.AO_0420_UI-4)+(float)(ai_o420.G0420_OUT_offset/10000.0))/5;

	U_IN=(U_*4095);
	U_OUT=((U_IN <<2)&0x3FFC);
	U_OUT_H=(U_OUT&0xFF00)>>8;
	U_OUT_L=(U_OUT&0x00FF);
	#if 1
	states_spi0(AO1_spi_init);
	#endif
	Delay();
	SPI0_ReadWrite(U_OUT_H);
	SPI0_ReadWrite(U_OUT_L);
	#if 1
	states_spi0(close_spi_init);
    Delay();
	#endif
}

short c_entry_AI1(void)
{
	char AI_write_buffer[2];
	char AI_read_buffer[2]={0};
	int i;
	float AI1_voltage;
	short AI1_voltage_H,AI1_voltage_L,AI1_voltage_all;
	float AI1_V;
	AI_write_buffer[0] = 0xC6;
	AI_write_buffer[1] = 0x83;
	Init_EESPI0_ADDA_EN();
	states_spi0(AI1_spi_init);
	Delay();
    for (i = 0; i < 2; i++)
    {
        AI_read_buffer[i] = SPI0_ReadWrite(AI_write_buffer[i]);
    }
	states_spi0(close_spi_init);
    Delay();
    AI1_voltage_H = AI_read_buffer[0] << 8;
    AI1_voltage_L =  AI_read_buffer[1];
    AI1_voltage_all=(AI1_voltage_H+AI1_voltage_L)&0xffff;
    AI1_voltage_all=AI1_voltage_all>>4;		
    return AI1_voltage_all;
	}

extern uint8_t DIR_MOTOR; 
	
extern char motorset_stop;
extern char motorset_n;
extern char motorset_s;
	#if 1
extern	char flag_estop;
void remote_control(void)
{
	float o420_I_L,o420_I_H,o420_I_UP,o420_I_DOWN;
	float o420_I_k,o420_I_b;
	int o420_I_flag;
	int B_0;
	int B_1;
	int B_2;
	int B_3;
	char num_remote;
	float asdafaf;
	#if 1

	if(remote_conntrol.AI1_read >=0)
	{
        /*输入模拟量调整*/
        ai_o420.AI_0420=(float)(remote_conntrol.AI1_read-ai_o420.G0420_offset)*(16.0/((ai_o420.G0420_slope-ai_o420.G0420_offset)*1.0))+4;
		B_0=ai_o420.AI_0420*10;
		B_1=B_0/10;
		B_2=B_0%10;
		ai_o420.AI_0420_UI=(B_1+B_2*0.1);
	}
	#endif
	if(ai_o420.flag_I_up==1)
	{
		ai_o420.flag_I_down=0;
		o420_I_flag=1;
		o420_I_b=-25;
	}else
	if(ai_o420.flag_I_down==1)
	{
		ai_o420.flag_I_up=0;
		o420_I_flag=-1;
		o420_I_b=125;
	}	
	if(ai_o420.flag_I_0020==1)
	{
		ai_o420.flag_I_0420=0;
		o420_I_k=5;
		o420_I_b=0;
	}else
	if(ai_o420.flag_I_0420==1)
	{
		ai_o420.flag_I_0020=0;
		o420_I_k=6.25;
	}
	if((ai_o420.AI_0420>3.6)&&(ai_o420.AI_0420<21))
	{
        ai_o420.input_error=0;
	}else
	{
		ai_o420.input_error=1;
	}
	ai_o420.send_motor = (o420_I_flag*o420_I_k*ai_o420.AI_0420)+o420_I_b;
    
    //该参数原先是10，考虑分转速档调节，转速比较低的时候，调小以减小死区。目前EE13，28转速档调到6就会有问题了
    if((dataStructInterface.speed_open == rang1) || (dataStructInterface.speed_open == rang2))  //低转速档特殊处理（目前只考虑开速度，待优化）
    {
        data_figures.analog_H = 7;  //三方检测的系数是4.5
    }
    else
    {
        data_figures.analog_H = 8;    //三方检测的系数是8
    }
	  
	remote_mode();
	num_remote=remote_ctr();
	if(ledstates.remote==1)
	{
		if(flag_figures.KEYEme==1)
        {
            if(remote_conntrol.EME_Flag==0) 
            {
                remote_conntrol.KEYEme=1;
            }else
            {
                remote_conntrol.KEYEme=0;
            }				
        }
        else if(flag_figures.KEYEme==0)
        {
            if(remote_conntrol.EME_Flag==1) 
            {
                remote_conntrol.KEYEme=1;
            }	else
            {
                remote_conntrol.KEYEme=0;
            }	
        }
        
		if(remote_conntrol.KEYEme==1)
		{
			ledstates.EME=1;
			if(((key_mlx90363.READ_run)<(remote_conntrol.emergency_pos_H))&&((key_mlx90363.READ_run)>(remote_conntrol.emergency_pos_L)))
            {
                motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
            }else
            if((key_mlx90363.READ_run)>(remote_conntrol.emergency_pos_H))
            {
                if(motorset.DIR==1)
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
                    motorset_s=24; 
                }else
                if(motorset.DIR==2)
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
                    motorset_s=23;
                }
            }else
            if((key_mlx90363.READ_run)<(remote_conntrol.emergency_pos_L))
            {
                if(motorset.DIR==1)
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
                    motorset_n=22;
                }else
                if(motorset.DIR==2)
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
                    motorset_n=21;
                }
            }
		}
        else
		{
            if(ai_o420.flag_mode1==1)  //开关量持续节点控制
            {
                if(num_remote==1)
                {
                    if(flag_figures.KEYOpen==1)
                    {
                        if(flag_estop==1)
                        {
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;	
                            ai_o420.flag_run_right_cx=1;
                            if(ai_o420.flag_run_left_cx==1)
                            {
                                flag_estop=0;
                                ai_o420.flag_run_right_cx=0;
                                ai_o420.flag_run_left_cx=0;
                            }
                        }
                        if(ai_o420.flag_run_right_cx==1)
                        {
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;	
                        }else
                        {
                            if(motorset.DIR==1)
                            {
                                motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
                                motorset_n=20;
                            }else
                            if(motorset.DIR==2)
                            {
                                motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
                                motorset_n=19;
                            }
                        }
                    }
                    
					if(flag_figures.KEYClose==1)
                    {
                        if(flag_estop==1)
                        {
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;	
                            ai_o420.flag_run_left_cx=1;
                            if(ai_o420.flag_run_right_cx==1)
                            {
                                flag_estop=0;
                                ai_o420.flag_run_left_cx=0;
                                ai_o420.flag_run_right_cx=0;
                            }
                        }
                        if(ai_o420.flag_run_left_cx==1)
                        {
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;	
                        }else
                        {
                            if(motorset.DIR==1)
                            {
                                motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
                                motorset_s=22;
                            }else
                            if(motorset.DIR==2)
                            {
                                motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
                                motorset_s=21;
                            }
                        }
                    }
                    
                    if(flag_figures.KEYStop==1)
                    {
                        motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                        motorset.stop=6;
                        remote_conntrol.KEYEme=0;
                    }
                    
                    if(flag_figures.KEYMod==1)
                    {
                        motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                    }
                }
                else
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                }
            }
            else if(ai_o420.flag_mode2==1)  //开关量脉冲节点控制
            {
                if(ledstates.EME==1)
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                    ledstates.EME=0;
                }
                
				if(flag_figures.KEYOpen==1)
                {
                    if(flag_estop==1)
					{
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;	
						ai_o420.flag_run_right_mc=1;
						if(ai_o420.flag_run_left_mc==1)
						{
							flag_estop=0;
							ai_o420.flag_run_right_mc=0;
							ai_o420.flag_run_left_mc=0;
						}
					}
					if(ai_o420.flag_run_right_mc==1)
					{
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;	
					}
                    else
                    {	
                        if(motorset.DIR==1)
                        {
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
                            motorset_n=18;
                        }else
                        if(motorset.DIR==2)
                        {
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
                            motorset_n=17;
                        }
                    }
                    remote_conntrol.KEYEme=0;
                }
                
                if(flag_figures.KEYClose==1)
                {
                    if(flag_estop==1)
					{
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;	
						ai_o420.flag_run_left_mc=1;
						if(ai_o420.flag_run_right_mc==1)
						{
							flag_estop=0;
							ai_o420.flag_run_right_mc=0;
							ai_o420.flag_run_left_mc=0;
						}
					}
					if(ai_o420.flag_run_left_mc==1)
					{
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;	
					}
                    else
                    {
                        if(motorset.DIR==1)
                        {
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
                            motorset_s=20;
                        }else
                        if(motorset.DIR==2)
                        {
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
                            motorset_s=19;
                        }
                    }
                    remote_conntrol.KEYEme=0;
                }
                
                if(flag_figures.KEYStop==1)
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                }

                if(flag_figures.KEYMod==1)
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                    remote_conntrol.KEYEme=0;
                }	
            }
            else if(ai_o420.flag_mode3==1)  //开关量比例控制
            {
                //暂未实现
            }
            else if(ai_o420.flag_mode4==1)  //模拟量位置控制
            {
                if(ai_o420.input_error==1)
                {
                    motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                }
                else
                {
                    if(remote_conntrol.AI1_read >=0)
                    {
                        if((encoder.num==6)||(encoder.num==2))
						{
							ai_o420.send_motor=100-ai_o420.send_motor;
						}
						
                        /****************************************死区控制*********************************************************
                        *模拟量输入动作区<----精度控制量----编码器位置----精度控制量---->模拟量输入动作区*
                        *********************************************************************************************************/
						if((ai_o420.send_motor*10)>=((key_mlx90363.READ_run)+(data_figures.analog_H)))  
						{
							#if 1																
							if(flag_estop==1)
							{
								motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;	
								ai_o420.flag_run_left=1;
								if(ai_o420.flag_run_right==1)
								{
									flag_estop=0;
									ai_o420.flag_run_right=0;
									ai_o420.flag_run_left=0;
								}
							}									
							if(ai_o420.flag_run_left==1)
							{
								motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;										
							}else
							#endif
							{
								flag_estop=0;
                                ai_o420.flag_run_right = 0;  //20200702只要反向稍微动一点，正向堵转解开
								if((encoder.num==3)||(encoder.num==1)||(encoder.num==4)||(encoder.num==6))
								{
									if(motorset.DIR==1)
									{
										motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
										motorset_n=16;
									}else
									if(motorset.DIR==2)
									{
										motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
										motorset_s=18;
									}
								}else
								if((encoder.num==2)||(encoder.num==5)||(encoder.num==7)||(encoder.num==8))
								{
									if(motorset.DIR==1)
									{
										motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
										motorset_s=17; 
									}else
									if(motorset.DIR==2)
									{
										motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
										motorset_n=15;
									}
								}
							}
						}
                        else if((ai_o420.send_motor*10)<=((key_mlx90363.READ_run)-(data_figures.analog_H)))  //X<=Y-10
						{
							#if 1														
							if(flag_estop==1)
							{
								motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;	
								ai_o420.flag_run_right=1;
								if(ai_o420.flag_run_left==1)
								{
									flag_estop=0;
									ai_o420.flag_run_right=0;
									ai_o420.flag_run_left=0;
								}
							}
							
							if(ai_o420.flag_run_right==1)
							{
								motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
							}else
							#endif
							{
								flag_estop=0;
                                ai_o420.flag_run_left = 0;  //20200702只要反向稍微动一点，正向堵转解开
								if((encoder.num==3)||(encoder.num==1)||(encoder.num==4)||(encoder.num==6))
								{
									if(motorset.DIR==1)
									{
										motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
										motorset_s=16;
									}else
									if(motorset.DIR==2)
									{
										motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
										motorset_n=14;
									}
								}else
								if((encoder.num==2)||(encoder.num==5)||(encoder.num==7)||(encoder.num==8))
								{
									if(motorset.DIR==1)
									{
										motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
										motorset_n=13;  
									}else
									if(motorset.DIR==2)
									{
										motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
										motorset_s=15;
									}
								}
							}
						}
                        else if((((ai_o420.send_motor*10)<(key_mlx90363.READ_run + data_figures.analog_H))&&((ai_o420.send_motor*10)>(key_mlx90363.READ_run - data_figures.analog_H))))
                        //原来万工的处理，不知道为什么不与上面判断条件保持一致，修改之后正常
						//if((((ai_o420.send_motor*10)<((key_mlx90363.READ_run)*1.02/*1.02*/))&&((ai_o420.send_motor*10)>((key_mlx90363.READ_run)*0.96/*0.92*/))))  
						{
							motorset.l0420_num++;
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
							motorset.stop=7;
						}							
                    }
                }
            }				
        }
	}	
}
#endif

void remote_EME(void)
{
	if(dataStructInterface.emergency_pos==0)
	{
        remote_conntrol.emergency_pos_H=1*10.2;
        remote_conntrol.emergency_pos_L=1*9.8;
	}else
	{
		remote_conntrol.emergency_pos_H=dataStructInterface.emergency_pos*10.2;
        remote_conntrol.emergency_pos_L=dataStructInterface.emergency_pos*9.8;
	}
		if(flag_figures.KEYEme==1)
			{
				if(remote_conntrol.EME_Flag==0)  
				{
					remote_conntrol.KEYEme=1;
				}else
				{
					remote_conntrol.KEYEme=0;
				}				
			}else
			if(flag_figures.KEYEme==0)
			{
				if(remote_conntrol.EME_Flag==1)  
				{
					remote_conntrol.KEYEme=1;
				}	else
				{
					remote_conntrol.KEYEme=0;
				}	
			}
				if(	remote_conntrol.KEYEme==1)
				{
					#if 1
					if(((key_mlx90363.READ_run)<(remote_conntrol.emergency_pos_H))&&((key_mlx90363.READ_run)>(remote_conntrol.emergency_pos_L)))
					{
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
					}else
					if((key_mlx90363.READ_run)>(remote_conntrol.emergency_pos_H))
					{
						if(motorset.DIR==1)
						{
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
							motorset_s=14;
						}else
						if(motorset.DIR==2)
						{
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
							motorset_n=12;
						}
					}else
					if((key_mlx90363.READ_run)<(remote_conntrol.emergency_pos_L))
					{
						if(motorset.DIR==1)
						{
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
							motorset_n=11;
						}else
						if(motorset.DIR==2)
						{
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
							motorset_s=13;
						}
					}
					#endif
				}else
				{
					if((ledstates.remote==0))
					{
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
					}else
					if(ledstates.remote==1)
					{
						if((flag_figures.KEYOpen!=1)&&(flag_figures.KEYStop!=1)&&(flag_figures.KEYClose!=1))
						{
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
						}
					}
				}
}

void remote_mode(void)
{
	if(ledstates.OPEN_remote==1)
	{
        if(DEVICE_STATE_LOCAL == g_deviceState)
        {
            ledstates.local=1;
            ledstates.remote=0;
            ledstates.off=0;
        }else if(DEVICE_STATE_REMOTE == g_deviceState)
        {				
            ledstates.remote=1;
            ledstates.local=0;
            ledstates.off=0;
        }
        else if(DEVICE_STATE_OFF == g_deviceState)
        {				
            ledstates.off=1;
            ledstates.local=0;
            ledstates.remote=0;
        }
        }else
        {
            ledstates.remote=0;
        }
				

}

char remote_ctr(void)
{
	char num=0;
	if(flag_figures.KEYClose==1)
			{
				num++;
			}
			if(flag_figures.KEYOpen==1)
			{
				num++;
			}
			if(flag_figures.KEYStop==1)
			{
				num++;
			}
			if(flag_figures.KEYEme==1)
			{
			num++;
			}
			if(flag_figures.KEYMod==1)
			{
				num++;
			}
			return num;
}


extern unsigned char Read_buf_modbus[20];
extern unsigned char Send_buf_modbus[40];
unsigned char Read_0420_BUF[8];
void m0420_Read(void)
{
	int i;
	int j;
	
	for(i=0;i<8;i++)
	{
		if((Read_buf_modbus[i]==0xa5)&&(Read_buf_modbus[i+1]==0x5a))
		{
			for(j=0;j<8;j++)
			{
				Read_0420_BUF[0+j]=Read_buf_modbus[i+j];
			}
		}
	}

	if((Read_0420_BUF[0]==0xa5)&&(Read_0420_BUF[1]==0x5a))
	{
		if(Read_0420_BUF[2]==0x30)   
		{
			switch(Read_0420_BUF[3])
			{
				case 1:	 ai_o420.G0420_offset=READ_0420_remote();break;
				case 2:	 ai_o420.G0420_slope= READ_0420_remote();break;
				case 3:	 ai_o420.G0420_OUT_offset= READ_0420_remote();break;
				case 4:	 ai_o420.G0420_OUT_slope= READ_0420_remote();break;

				default:              break;
				break;
			}
		}
		if(Read_0420_BUF[2]==0x30)
		{
			if(Read_0420_BUF[3]==0x60)
			{
				ai_o420.flag_save0420_o=1;
			}
		}
	}	
}

short READ_0420_remote(void)
{
	short value;
	value=(Read_0420_BUF[7]<<8)+Read_0420_BUF[6];	
	return value;
}	

