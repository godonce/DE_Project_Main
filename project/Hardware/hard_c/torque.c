#include "torque.h"
#include "datafigures.h"
#include "DataInterface.h"


/****************************************通信协议*********************************************
******上板(控制板)***********************下板(电源板)*****************************************
*     无                                 00 00 00 00 00 00 00 00                             *
*     无                                 1E XX 00 XX FF 25 5A 4E                             *
*     25 7F F5 58 F5 AA 67 D4            16 FD 00 00 9A 25 C4 42 16 FD 00 00 9A 25 C4 42     *
*     4A 00 00 00 00 00 0E 71            80 FE 00 00 9A 25 9D 74 00 FB 00 00 94 25 4A D4     *
*     48 00 00 00 00 03 4F 92            80 FE 00 00 9A 25 9D 74 00 FB 00 00 94 25 4A D4     *
*     44 XX XX XX XX 03 4F 92            81 FE 00 00 9A 25 9D 74 01 FB 00 00 94 25 4A D4     *
*     4C XX XX XX XX 03 4F 92            81 FE 00 00 9A 25 9D 74 01 FB 00 00 94 25 4A D4     *
*********************************************************************************************/

/****************************************上板协议内容*****************************************
******上板数据字节***********************含义*************************************************
*     1                                  4C反转 44正转 48停                                  *
*     2/3                                转速                                                *
*     4/5                                转矩                                                *
*     6                                  无                                                  *
*     7/8                                校验码                                              *
*********************************************************************************************/

/****************************************下板协议内容*****************************************
******下板数据字节***********************含义*************************************************
*     1                                  16通信握手 81正/反转 80停止 88过流 82过压           *
*     2                                  电流低位                                            *
*     3                                  无                                                  *
*     4                                  电流高位                                            *
*     5                                  电压低位                                            *
*     6                                  电压高位                                            *
*     7/8                                校验码                                              *
*********************************************************************************************/

uint16_t SPEED_RUN;
uint16_t TORQUE_RUN;
uint16_t SPEED_END;
uint16_t TORQUE_END;
uint16_t Current_STOP; 
uint16_t current_up;
uint16_t Current_BASE;
uint16_t SPEED_ADD;
uint16_t SPEED_DEC;
uint16_t TORQUE_ADD;
uint16_t TORQUE_DEC;
uint16_t SPEED_send=0;
uint16_t TORQUE_send=0;
uint8_t MOTOR_DIR;
extern uint8_t  buffer3[8];
extern uint8_t  buffer3_ALL[16];
extern uint8_t  flag_start;
extern uint8_t  flag_step1;
extern uint8_t  flag_step2;
extern uint8_t  flag_step3;
extern uint8_t  flag_step4;
extern uint8_t  flag_step;
extern uint8_t  flag_allstart1;
extern uint8_t  flag_allstart2;
extern uint8_t  flag_allstart3;
extern uint8_t  flag_ok; 
extern uint8_t  DIR_MOTOR ;
extern uint8_t  DIR_Send;
extern uint16_t flag_u25;
extern uint16_t flag_u4a;
extern uint8_t  is_endpos;

void check_hand()
{
	uint16_t  check_F,check_B;
	int i=0;
	for(i=0;i<9;i++)
	{
		buffer3[0]=buffer3_ALL[i+0];
		buffer3[1]=buffer3_ALL[i+1];
		buffer3[2]=buffer3_ALL[i+2];
		buffer3[3]=buffer3_ALL[i+3];
		buffer3[4]=buffer3_ALL[i+4];
		buffer3[5]=buffer3_ALL[i+5];
		buffer3[6]=buffer3_ALL[i+6];
		buffer3[7]=buffer3_ALL[i+7];
		check_B=(buffer3[6]<<8)+(buffer3[7]);
		check_F=CRC_Compute(buffer3,6);
		if(check_B==check_F)
		{
			current_up=(buffer3[3]<<8)+buffer3[1];
			powerboard.current_up=current_up;
			powerboard.voltage=(buffer3[5]<<8)+buffer3[4];
			powerboard.lcd_voltage=((887-((float)(powerboard.voltage&0x03ff))))/1.5;
			powerboard.lcd_current=((current_up*1.0)+256)/282.6;
			break;  
		}else
		{
            powerboard.USB_ERROR=1;
		}
	}
	
	if(check_B==check_F)
	{
		if((buffer3[0]==0x1E)||(buffer3[0]==0x00)||(buffer3[0]==0x10))
		{
			if(flag_start==1)
			{
                flag_step1=1;  
                flag_step2=0;
                flag_step3=0;
			}else
			{
				flag_step=1;
			}
			powerboard.USB_ERROR=0;
		}else
		if((buffer3[0]==0x16)||(buffer3[0]==0x80)||(buffer3[0]==0x00))
		{
			powerboard.USB_ERROR=0;
			if(flag_u25>4)
			{
				if(flag_ok==1)
				{
                    flag_step1=0;
                    flag_step2=1;   
                    flag_step3=0;
				}
				else
				{
					flag_step=1;
				}
			}else
			{
                flag_step1=1; 
                flag_step2=0;
                flag_step3=0;
			}
			if(uart3.ready_4A>56)
			{
				if((buffer3[0]==0x80)||(buffer3[0]==0x00))
				{
					flag_step1=0;   
                    flag_step2=0;
                    flag_step3=1;
				}
			}
		}else
        if((buffer3[0]==0x81)||(buffer3[0]==0x01)||(buffer3[0]==0x84)||(buffer3[0]==0x04)||(buffer3[0]==0x85)||(buffer3[0]==0x05))
		{
			
            flag_step1=0;   
            flag_step2=0;
            flag_step3=1;    
            powerboard.USB_ERROR=0;
		}
		else
		{
			powerboard.USB_ERROR=1;
		}
	}
}

uint16_t RISE_TIME;
uint16_t DOWN_TIME;
uint16_t SPEED_Stand;
uint16_t TORQUE_Stand;
float ABC,ABD,ABE,ABF;
extern uint16_t EE13_SPEED_RUN[7];
void changetorque(uint8_t dir)
{
	
				if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_t)
				{
					#if 1
					DIR_Send=0x48;
					SPEED_send=0;
					TORQUE_send=0;
					motorset.flag_start_num=0;
					motorset.flag_start=1;
					#endif
				}else
				{
					if(motorset.flag_start==1)
					{
						motorset.flag_start=0;
						SPEED_send=SPEED_RUN*motorset.torque_min;						
					}
					
					if(motorset.DIR==2)
					{
						
							if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
							{
								{
									DIR_Send=0x44;
									flag_figures.blockstop=0;
								}
							}else
							if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
							{
								{
									DIR_Send=0x4C;
									flag_figures.blockstop=0;
								}
							}
						}else
					if(motorset.DIR==1)
					{
							if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
							{
								{
									DIR_Send=0x4C;
									flag_figures.blockstop=0;
								}
							}else
							if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
							{
								{
									DIR_Send=0x44;
									flag_figures.blockstop=0;
								}
							}
						}
							if(dir==1)  //加速
							{
									if(((SPEED_send<(SPEED_RUN))||(TORQUE_send<(TORQUE_RUN)))&&(motorset.flag_start==0))  
									{
										SPEED_send=SPEED_send+SPEED_ADD;
										TORQUE_send=TORQUE_send+TORQUE_ADD;	
									}else
									{
										if(motorset.flag_start==1)
										{
                                            motorset.flag_start_num++;
										}
										if(motorset.flag_start_num>20)  
										{											
                                            motorset.flag_start=1;
                                            SPEED_send=SPEED_RUN;
											TORQUE_send=(uint16_t)(TORQUE_RUN*motorset.torque_max);
										}else
										{
											motorset.flag_start=0;
											SPEED_send=SPEED_RUN;
											TORQUE_send=TORQUE_RUN;
										}
									}	
								
							}else
							if(dir==3)  //稳定运行
							{
									if(((SPEED_send>(SPEED_RUN))||(TORQUE_send>(TORQUE_RUN)))&&(motorset.flag_start==0))
									{
										SPEED_send=SPEED_send-SPEED_DEC;
										TORQUE_send=TORQUE_send-TORQUE_DEC;
									}else
									{
										motorset.flag_start=1;
										SPEED_send=SPEED_RUN;
										TORQUE_send=TORQUE_RUN;
									}	
							
							}else
							if(dir==2)  //停机降速
							{
								{
									DIR_Send=0x48;
									motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
									motorset.stop=5;
									DIR_MOTOR=3;
									SPEED_send=0;
									TORQUE_send=0;
								}	
							}else
							if(dir==4)  //堵转
							{
									if(((SPEED_send>(EE13_SPEED_RUN[0])))&&(motorset.flag_start==0))
									{
										SPEED_send=SPEED_send-8;
										TORQUE_send=TORQUE_RUN;
									}else
									{
									}							
							}
				}	
}



char flag_estop=0;         



#ifdef  CE12
			 uint16_t  SPEED_Stand_C[7] = {       5,       7,       10,      14,       20,       28,        40};
			 uint16_t  TORQUE_Stand_C[8]= {       18,       24,       30,      36,       42,       48,        54,      60};
static uint16_t  CE12_SPEED_RUN[7]= {   0x03E8,   0x0514,   0x0640,  0x0898,   0x0BB8,   0x0FA0,    0x14E0};
static uint16_t  CE12_RISE_TIME[7]= {       52,       56,       64,     76,      88,      102,       126};
static uint16_t  CE12_DOWN_TIME[7]= {       40,       48,       63,      64,       85,      112,       156};
static uint16_t  CE12_SPEED_END[7]= {   0x0000,   0x0000,   0x0000,  0x0000,   0x0000,   0x0000,    0x0000};
static float     CE12_torque_a[7]=  {  -0.5296,  -0.7196,  -0.7196,  -0.7827-0.1,  -0.7831, -0.7196, -5.3757};
static float     CE12_torque_b[7]=  {   168.63,   186.92,   197.59,   218.24,   237.59, 258.03,   592.51};
static float     CE12_torque_c[7]=  {   3780.6+2000,   4148.6+2000,   4596.6+2000,   5563.4+2000,   7017.1+2000, 8863.2+2000,   7508.6+2000};
//static float     CE12_current_a[7]= {   0.0157,   0.0157,        0,        0,        0,      0,        0};
//static float     CE12_current_b[7]= {   4.1062,   4.1062,   2.7857,   3.4782,   4.5238, 5.4762,   4.7857};
//static float     CE12_current_c[7]= {    70000,   100000,       70,   72.476,     88.5,   91.4,    148.8};

static float     CE12_current_a[7]= {   0.0157,   0.0157,   0.0405,   0.0058,    0.0076,      0.0157,        1};
static float     CE12_current_b[7]= {   4.1062,   4.1062,    -0.0784,   3.0625,    2.8909,      4.1062,   4.1062};
static float     CE12_current_c[7]= {    70000,   100000,   244.41,       50,    21.25,       61000,    61000};
int CE12_voltage[7][8]={
														{7100,8150,9150,10032,11032,12132,13200,14300},
														{8400,9600,10600,11600,12600,13800,15400,16500},
														{0x4040,0x4040,0x4040,0x4040,0x4040,0x4040,0x4040,0x4040},
														{0x4040,0x4040,0x4040,0x4040,0x4040,0x4040,0x4040,0x4040},
														{0x4040,0x4040,0x4040,0x4040,0x4040,0x4040,0x4040,0x4040},
														{0x4040,0x4040,0x4040,0x4040,0x4040,0x4040,0x4040,0x4040},
														{0x4040,0x4040,0x4040,0x4040,0x4040,0x4040,0x4040,0x4040},
													};
void choice_speed_line()
{
	float torque_cl;
	float current_cl;
	float torque_a,torque_b,torque_c;
	float current_a,current_b,current_c;
	float torque_test;
	switch(SPEED_Stand)
	{
		
		case 5:
					{
						SPEED_RUN = RUN_SPEED_05;//CE12_SPEED_RUN[0];
						RISE_TIME = CE12_RISE_TIME[0];			
						SPEED_END = CE12_SPEED_END[0];
						torque_a  = CE12_torque_a[0];
						torque_b  = CE12_torque_b[0];
						torque_c  = CE12_torque_c[0];
						current_a = CE12_current_a[0];
						current_b = CE12_current_b[0];
						current_c = CE12_current_c[0];
						TORQUE_END=0x1C00;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= CE12_voltage[0][0];  break;
							case 24: torque_test= CE12_voltage[0][1];  break;
							case 30: torque_test= CE12_voltage[0][2];  break;
							case 36: torque_test= CE12_voltage[0][3];  break;
							case 42: torque_test= CE12_voltage[0][4];  break;
							case 48: torque_test= CE12_voltage[0][5];  break;
							case 54: torque_test= CE12_voltage[0][6];  break;
							case 60: torque_test= CE12_voltage[0][7];  break;
								default: break;
								
						}
					}
						break;
		case 7:
					{
						SPEED_RUN = RUN_SPEED_07;//CE12_SPEED_RUN[1];
						RISE_TIME = CE12_RISE_TIME[1];			
						SPEED_END = CE12_SPEED_END[1];
						torque_a  = CE12_torque_a[1];
						torque_b  = CE12_torque_b[1];
						torque_c  = CE12_torque_c[1];
						current_a = CE12_current_a[1];
						current_b = CE12_current_b[1];
						current_c = CE12_current_c[1];
						TORQUE_END=0x1C00;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= CE12_voltage[1][0];  break;
							case 24: torque_test= CE12_voltage[1][1];  break;
							case 30: torque_test= CE12_voltage[1][2];  break;
							case 36: torque_test= CE12_voltage[1][3];  break;
							case 42: torque_test= CE12_voltage[1][4];  break;
							case 48: torque_test= CE12_voltage[1][5];  break;
							case 54: torque_test= CE12_voltage[1][6];  break;
							case 60: torque_test= CE12_voltage[1][7];  break;
								default: break;
								
						}
					}
						break;
		case 10: // y = 0.0405x2 - 0.0784x + 244.41
					{
						SPEED_RUN = RUN_SPEED_07;//CE12_SPEED_RUN[2];
						RISE_TIME = CE12_RISE_TIME[2];			
						SPEED_END = CE12_SPEED_END[2];
						torque_a  = CE12_torque_a[2];
						torque_b  = CE12_torque_b[2];
						torque_c  = CE12_torque_c[2];
						current_a = CE12_current_a[2];
						current_b = CE12_current_b[2];
						current_c = CE12_current_c[2];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= CE12_voltage[2][0];  break;
							case 24: torque_test= CE12_voltage[2][1];  break;
							case 30: torque_test= CE12_voltage[2][2];  break;
							case 36: torque_test= CE12_voltage[2][3];  break;
							case 42: torque_test= CE12_voltage[2][4];  break;
							case 48: torque_test= CE12_voltage[2][5];  break;
							case 54: torque_test= CE12_voltage[2][6];  break;
							case 60: torque_test= CE12_voltage[2][7];  break;
								default: break;
								
						}
					}
						break;
		case 14:
					{
						SPEED_RUN = RUN_SPEED_14;//CE12_SPEED_RUN[3];
						RISE_TIME = CE12_RISE_TIME[3];			
						SPEED_END = CE12_SPEED_END[3];
						torque_a  = CE12_torque_a[3];
						torque_b  = CE12_torque_b[3];
						torque_c  = CE12_torque_c[3];
						current_a = CE12_current_a[3];
						current_b = CE12_current_b[3];
						current_c = CE12_current_c[3];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= CE12_voltage[3][0];  break;
							case 24: torque_test= CE12_voltage[3][1];  break;
							case 30: torque_test= CE12_voltage[3][2];  break;
							case 36: torque_test= CE12_voltage[3][3];  break;
							case 42: torque_test= CE12_voltage[3][4];  break;
							case 48: torque_test= CE12_voltage[3][5];  break;
							case 54: torque_test= CE12_voltage[3][6];  break;
							case 60: torque_test= CE12_voltage[3][7];  break;
								default: break;
								
						}
					}
						break;
		case 20:  //y = 0.0076x2 + 2.8909x + 211.25
					{
						SPEED_RUN = RUN_SPEED_20;//CE12_SPEED_RUN[4];
						RISE_TIME = CE12_RISE_TIME[4];			
						SPEED_END = CE12_SPEED_END[4];
						torque_a  = CE12_torque_a[4];
						torque_b  = CE12_torque_b[4];
						torque_c  = CE12_torque_c[4];
						current_a = CE12_current_a[4];
						current_b = CE12_current_b[4];
						current_c = CE12_current_c[4];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= CE12_voltage[4][0];  break;
							case 24: torque_test= CE12_voltage[4][1];  break;
							case 30: torque_test= CE12_voltage[4][2];  break;
							case 36: torque_test= CE12_voltage[4][3];  break;
							case 42: torque_test= CE12_voltage[4][4];  break;
							case 48: torque_test= CE12_voltage[4][5];  break;
							case 54: torque_test= CE12_voltage[4][6];  break;
							case 60: torque_test= CE12_voltage[4][7];  break;
								default: break;
								
						}
						
					}
						break;
		case 28:
					{
						SPEED_RUN = RUN_SPEED_28;//CE12_SPEED_RUN[5];
						RISE_TIME = CE12_RISE_TIME[5];			
						SPEED_END = CE12_SPEED_END[5];
						torque_a  = CE12_torque_a[5];
						torque_b  = CE12_torque_b[5];
						torque_c  = CE12_torque_c[5];
						current_a = CE12_current_a[5];
						current_b = CE12_current_b[5];
						current_c = CE12_current_c[5];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= CE12_voltage[5][0];  break;
							case 24: torque_test= CE12_voltage[5][1];  break;
							case 30: torque_test= CE12_voltage[5][2];  break;
							case 36: torque_test= CE12_voltage[5][3];  break;
							case 42: torque_test= CE12_voltage[5][4];  break;
							case 48: torque_test= CE12_voltage[5][5];  break;
							case 54: torque_test= CE12_voltage[5][6];  break;
							case 60: torque_test= CE12_voltage[5][7];  break;
								default: break;
								
						}
						//Current_STOP=500;
					}
						break;
		case 40:
					{
						SPEED_RUN = RUN_SPEED_40;//CE12_SPEED_RUN[6];
						RISE_TIME = CE12_RISE_TIME[6];			
						SPEED_END = CE12_SPEED_END[6];
						torque_a  = CE12_torque_a[6];
						torque_b  = CE12_torque_b[6];
						torque_c  = CE12_torque_c[6];
						current_a = CE12_current_a[6];
						current_b = CE12_current_b[6];
						current_c = CE12_current_c[6];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= CE12_voltage[6][0];  break;
							case 24: torque_test= CE12_voltage[6][1];  break;
							case 30: torque_test= CE12_voltage[6][2];  break;
							case 36: torque_test= CE12_voltage[6][3];  break;
							case 42: torque_test= CE12_voltage[6][4];  break;
							case 48: torque_test= CE12_voltage[6][5];  break;
							case 54: torque_test= CE12_voltage[6][6];  break;
							case 60: torque_test= CE12_voltage[6][7];  break;
								default: break;
								
						}
					}
						break;
		default: break;
			
	}
	

	
	ABC=(current_a*(float )TORQUE_Stand*(float )TORQUE_Stand);
	ABD=(current_b*(float )TORQUE_Stand);
	ABE=current_c;
	Current_STOP=ABC+ABD+ABE;
//	Current_STOP=current_cl;//60;//(uint16_t)current_cl;	
	torque_cl=((torque_a*TORQUE_Stand*TORQUE_Stand)+(torque_b*TORQUE_Stand)+ torque_c);
	//torque_cl=torque_test;
	if (torque_cl>23744)
	{
		TORQUE_RUN=23744;
	}
	TORQUE_RUN=(uint16_t)torque_cl;
	SPEED_ADD=(float)SPEED_RUN/RISE_TIME;
	TORQUE_ADD=(float)TORQUE_RUN/RISE_TIME;
}


uint16_t Current_UP;
int changeDIR(void)
{
	RC(current_up);
	if(Current_BASE<190)//160
	{
		Current_BASE=160;//140
	}
		if(motorset.flag_run==0)
		{
				if(((current_up)&0x0FFF)>0xffff)//Current_BASE  0xffff
				{							
							set_end.asdadd=1;
								if(SPEED_Stand>=SPEED_Stand_C[4])  //2
								{
									SPEED_Stand=SPEED_Stand_C[2];//1
									motorset.flag_run=1;
									motorset.flag_run_jiangsu=1;
									return 3;
								}else
								if(SPEED_Stand==SPEED_Stand_C[2])//1
								{
									motorset.flag_run_jiangsu=0;
										motorset.DIR_MOTOR_old=motorset.DIR_MOTOR;
										Current_UP=current_up;
									motorset.stop1=3;
									if(set_end.flag_setend==1)
									{
										flag_estop=0;	
										if(dataStructInterface.closeOffMode==1)//liju
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
											{
												set_end.flag_closeOffMode=1;
											}
										}else  //xingcheng
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
											{
												set_end.flag_closeOffMode=2;
											}
										}
										if(dataStructInterface.openOffMode==1)//liju
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
											{
												set_end.flag_openOffMode=1;
											}
										}else   //xingcheng
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
											{
												set_end.flag_openOffMode=2;
											}
										}
									}else
									if(set_end.flag_setend==0)
									{
											if(motorset.DIR_MOTOR_old==motorset.DIR_MOTOR_n)
											{
												set_end.flag_move_right=1;
												set_end.flag_move_left=0;
											}	else
											if(motorset.DIR_MOTOR_old==motorset.DIR_MOTOR_s)
											{
												set_end.flag_move_left=1;
												set_end.flag_move_right=0;
											}
											flag_estop=1;		
									}											
										return 2;		
								}
				}
				else
				{
					//set_end.asdadd=0;
					set_end.flag_closeOffMode=0;
					set_end.flag_openOffMode=0;
					if(flag_estop==1)
					{
					
					}else
					{
						flag_estop=0;
						return 1;
					}	
				}
		}
	
}


#endif


#ifdef  DE13

uint16_t  SPEED_Stand_C[7]= {       10,       14,       20,      28,       40,       56,        80};
uint16_t  TORQUE_Stand_C[8]={       18,       24,       30,      36,       42,       48,        54,      60};
static uint16_t DE13_SPEED_RUN[7]= {   0x0640,   0x0898,   0x0BB8,  0x0FA0,   0x15E0,   0x1E14,    0x2AF8};
static uint16_t DE13_RISE_TIME[7]= {       65,       75,       88,     103,      130,      165,       219};
static uint16_t DE13_DOWN_TIME[7]= {       40,       48,       63,      64,       85,      112,       156};
static uint16_t DE13_SPEED_END[7]= {   0x0000,   0x0000,   0x0000,  0x0000,   0x0000,   0x0000,    0x0000};
static float     DE13_torque_a[7]= {  -0.6455,  -0.7831,  -0.8148,  -0.836,  -0.7937,  -0.7725,    6.4762};
static float     DE13_torque_b[7]= {   148.25,      168,      180,  192.57,   207.81,   231.81,   -159.24};
static float     DE13_torque_c[7]= {   3191.9+200,     4199+200,   4173.3+200,  5303.2+200,   7180.6+200,   9568.4+200,     19141+200};
static float    DE13_current_a[7]= {   0.0046,       0 ,  -0.0055,  -0.005,  -0.0056,  -0.0086,         0};
static float    DE13_current_b[7]= {   3.7421,   3.4091,   6.3522,  7.1607,   8.3631,   10.726,   6.0321};
static float    DE13_current_c[7]= {   88.143,   70.119,    74.22,   91.46,    129.2,   110.38,   284.36};
int DE13_voltage[7][8]={
														{  8004,  9004,  10000,  10500,  11500,  12500, 13500,14000},
														{0x1010,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010},
														{0x1010,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010},
														{ 10800,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010},
														{0x1010,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010},
														{0x1010,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010},
														{0x1010,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010,0x1010},
													};
int DE13_current[7][8]={
														{0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010},
														{0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010},
														{0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010},
														{0x00ff,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010},
														{0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010},
														{0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010},
														{0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010},
													};
void choice_speed_line()
{
	float torque_cl;
	float current_cl;
	float torque_a,torque_b,torque_c;
	float current_a,current_b,current_c;
	float torque_test,current_test;
	int i;
	switch(SPEED_Stand)
	{
		
		case 10:
					{
						SPEED_RUN=DE13_SPEED_RUN[0];
						RISE_TIME=DE13_RISE_TIME[0];
						DOWN_TIME=DE13_DOWN_TIME[0];
						SPEED_END=DE13_SPEED_END[0];
						torque_a = DE13_torque_a[0];
						torque_b = DE13_torque_b[0];
						torque_c = DE13_torque_c[0];
						current_a=DE13_current_a[0];
						current_b=DE13_current_b[0];
						current_c=DE13_current_c[0];
						TORQUE_END=0x1C00;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= DE13_voltage[0][0]; current_test= DE13_current[0][0];break;
							case 24: torque_test= DE13_voltage[0][1]; current_test= DE13_current[0][1]; break;
							case 30: torque_test= DE13_voltage[0][2]; current_test= DE13_current[0][2]; break;
							case 36: torque_test= DE13_voltage[0][3]; current_test= DE13_current[0][3]; break;
							case 42: torque_test= DE13_voltage[0][4]; current_test= DE13_current[0][4]; break;
							case 48: torque_test= DE13_voltage[0][5]; current_test= DE13_current[0][5]; break;
							case 54: torque_test= DE13_voltage[0][6]; current_test= DE13_current[0][6]; break;
							case 60: torque_test= DE13_voltage[0][7]; current_test= DE13_current[0][7]; break;
								default: break;
								
						}
					}
						break;
		case 14:
					{
						SPEED_RUN=DE13_SPEED_RUN[1];
						RISE_TIME=DE13_RISE_TIME[1];
						DOWN_TIME=DE13_DOWN_TIME[1];
						SPEED_END=DE13_SPEED_END[1];
						torque_a = DE13_torque_a[1];
						torque_b = DE13_torque_b[1];
						torque_c = DE13_torque_c[1];
						current_a=DE13_current_a[1];
						current_b=DE13_current_b[1];
						current_c=DE13_current_c[1];
						TORQUE_END=0x1C00;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= DE13_voltage[1][0]; current_test= DE13_current[0][0]; break;
							case 24: torque_test= DE13_voltage[1][1]; current_test= DE13_current[0][1]; break;
							case 30: torque_test= DE13_voltage[1][2]; current_test= DE13_current[0][2]; break;
							case 36: torque_test= DE13_voltage[1][3]; current_test= DE13_current[0][3]; break;
							case 42: torque_test= DE13_voltage[1][4]; current_test= DE13_current[0][4]; break;
							case 48: torque_test= DE13_voltage[1][5]; current_test= DE13_current[0][5]; break;
							case 54: torque_test= DE13_voltage[1][6]; current_test= DE13_current[0][6]; break;
							case 60: torque_test= DE13_voltage[1][7]; current_test= DE13_current[0][7]; break;
								default: break;
								
						}
					}
						break;
		case 20:
					{
						SPEED_RUN=DE13_SPEED_RUN[2];
						RISE_TIME=DE13_RISE_TIME[2];
						DOWN_TIME=DE13_DOWN_TIME[2];
						SPEED_END=DE13_SPEED_END[2];
						torque_a = DE13_torque_a[2];
						torque_b = DE13_torque_b[2];
						torque_c = DE13_torque_c[2];
						current_a=DE13_current_a[2];
						current_b=DE13_current_b[2];
						current_c=DE13_current_c[2];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= DE13_voltage[2][0]; current_test= DE13_current[0][0]; break;
							case 24: torque_test= DE13_voltage[2][1]; current_test= DE13_current[0][1]; break;
							case 30: torque_test= DE13_voltage[2][2]; current_test= DE13_current[0][2]; break;
							case 36: torque_test= DE13_voltage[2][3]; current_test= DE13_current[0][3]; break;
							case 42: torque_test= DE13_voltage[2][4]; current_test= DE13_current[0][4]; break;
							case 48: torque_test= DE13_voltage[2][5]; current_test= DE13_current[0][5]; break;
							case 54: torque_test= DE13_voltage[2][6]; current_test= DE13_current[0][6]; break;
							case 60: torque_test= DE13_voltage[2][7]; current_test= DE13_current[0][7]; break;
								default: break;
								
						}
					}
						break;
		case 28:
					{
						SPEED_RUN=DE13_SPEED_RUN[3];
						RISE_TIME=DE13_RISE_TIME[3];
						DOWN_TIME=DE13_DOWN_TIME[3];
						SPEED_END=DE13_SPEED_END[3];
						torque_a = DE13_torque_a[3];
						torque_b = DE13_torque_b[3];
						torque_c = DE13_torque_c[3];
						current_a=DE13_current_a[3];
						current_b=DE13_current_b[3];
						current_c=DE13_current_c[3];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= DE13_voltage[3][0]; current_test= DE13_current[0][0]; break;
							case 24: torque_test= DE13_voltage[3][1]; current_test= DE13_current[0][1]; break;
							case 30: torque_test= DE13_voltage[3][2]; current_test= DE13_current[0][2]; break;
							case 36: torque_test= DE13_voltage[3][3]; current_test= DE13_current[0][3]; break;
							case 42: torque_test= DE13_voltage[3][4]; current_test= DE13_current[0][4]; break;
							case 48: torque_test= DE13_voltage[3][5]; current_test= DE13_current[0][5]; break;
							case 54: torque_test= DE13_voltage[3][6]; current_test= DE13_current[0][6]; break;
							case 60: torque_test= DE13_voltage[3][7]; current_test= DE13_current[0][7]; break;
								default: break;
								
						}
					}
						break;
		case 40:
					{
						SPEED_RUN=DE13_SPEED_RUN[4];
						RISE_TIME=DE13_RISE_TIME[4];
						DOWN_TIME=DE13_DOWN_TIME[4];
						SPEED_END=DE13_SPEED_END[4];
						torque_a = DE13_torque_a[4];
						torque_b = DE13_torque_b[4];
						torque_c = DE13_torque_c[4];
						current_a=DE13_current_a[4];
						current_b=DE13_current_b[4];
						current_c=DE13_current_c[4];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= DE13_voltage[4][0]; current_test= DE13_current[0][0]; break;
							case 24: torque_test= DE13_voltage[4][1]; current_test= DE13_current[0][1]; break;
							case 30: torque_test= DE13_voltage[4][2]; current_test= DE13_current[0][2]; break;
							case 36: torque_test= DE13_voltage[4][3]; current_test= DE13_current[0][3]; break;
							case 42: torque_test= DE13_voltage[4][4]; current_test= DE13_current[0][4]; break;
							case 48: torque_test= DE13_voltage[4][5]; current_test= DE13_current[0][5]; break;
							case 54: torque_test= DE13_voltage[4][6]; current_test= DE13_current[0][6]; break;
							case 60: torque_test= DE13_voltage[4][7]; current_test= DE13_current[0][7]; break;
								default: break;
								
						}
						
					}
						break;
		case 56:
					{
						SPEED_RUN=DE13_SPEED_RUN[5];
						RISE_TIME=DE13_RISE_TIME[5];
						DOWN_TIME=DE13_DOWN_TIME[5];
						SPEED_END=DE13_SPEED_END[5];
//						torque_cl=((-0.7196*TORQUE_Stand*TORQUE_Stand)+(258.03*TORQUE_Stand)+ 8863.2);
						torque_a = DE13_torque_a[5];
						torque_b = DE13_torque_b[5];
						torque_c = DE13_torque_c[5];
						current_a=DE13_current_a[5];
						current_b=DE13_current_b[5];
						current_c=DE13_current_c[5];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= DE13_voltage[5][0]; current_test= DE13_current[0][0]; break;
							case 24: torque_test= DE13_voltage[5][1]; current_test= DE13_current[0][1]; break;
							case 30: torque_test= DE13_voltage[5][2]; current_test= DE13_current[0][2]; break;
							case 36: torque_test= DE13_voltage[5][3]; current_test= DE13_current[0][3]; break;
							case 42: torque_test= DE13_voltage[5][4]; current_test= DE13_current[0][4]; break;
							case 48: torque_test= DE13_voltage[5][5]; current_test= DE13_current[0][5]; break;
							case 54: torque_test= DE13_voltage[5][6]; current_test= DE13_current[0][6]; break;
							case 60: torque_test= DE13_voltage[5][7]; current_test= DE13_current[0][7]; break;
								default: break;
								
						}
						//Current_STOP=500;
					}
						break;
		case 80:
					{
						SPEED_RUN=DE13_SPEED_RUN[6];
						RISE_TIME=DE13_RISE_TIME[6];
						DOWN_TIME=DE13_DOWN_TIME[6];
						SPEED_END=DE13_SPEED_END[6];
						torque_a = DE13_torque_a[6];
						torque_b = DE13_torque_b[6];
						torque_c = DE13_torque_c[6];
						current_a=DE13_current_a[6];
						current_b=DE13_current_b[6];
						current_c=DE13_current_c[6];
						TORQUE_RUN=0x2F40;//RUN_TORQUE_18;
						TORQUE_END=0x1C00;//END_TORQUE_18;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= DE13_voltage[6][0]; current_test= DE13_current[0][0]; break;
							case 24: torque_test= DE13_voltage[6][1]; current_test= DE13_current[0][1]; break;
							case 30: torque_test= DE13_voltage[6][2]; current_test= DE13_current[0][2]; break;
							case 36: torque_test= DE13_voltage[6][3]; current_test= DE13_current[0][3]; break;
							case 42: torque_test= DE13_voltage[6][4]; current_test= DE13_current[0][4]; break;
							case 48: torque_test= DE13_voltage[6][5]; current_test= DE13_current[0][5]; break;
							case 54: torque_test= DE13_voltage[6][6]; current_test= DE13_current[0][6]; break;
							case 60: torque_test= DE13_voltage[6][7]; current_test= DE13_current[0][7]; break;
								default: break;
								
						}
					}
						break;
		default: break;
			
	}
	
	ABC=(current_a*(float )TORQUE_Stand*(float )TORQUE_Stand);
	ABD=(current_b*(float )TORQUE_Stand);
	ABE=current_c;
	Current_STOP=ABC+ABD+ABE;

	//Current_STOP=current_test;
	torque_cl=((torque_a*TORQUE_Stand*TORQUE_Stand)+(torque_b*TORQUE_Stand)+ torque_c);
	//torque_cl=torque_test;
	for(i=1;i<7;i++)
	{
		if(SPEED_Stand==SPEED_Stand_C[i])
		{
			SPEED_DEC=(float)(SPEED_Stand_C[i]-SPEED_Stand_C[i-1])/DOWN_TIME;
		}
	}
	TORQUE_RUN=(uint16_t)torque_cl;
	//#ifdef TEST_ST
	if (torque_cl>23808)
	{
		TORQUE_RUN=23808;
	}
	//#endif
	SPEED_ADD=(float)SPEED_RUN/RISE_TIME;
	TORQUE_ADD=(float)TORQUE_RUN/RISE_TIME;
}


int changeDIR(void)
{
	RC(current_up);
	if(Current_BASE<160)
	{
		Current_BASE=120;//140
	}
		if(motorset.flag_run==0)
		{
				if(((current_up)&0x0FFF)>Current_BASE)//Current_BASE  0xffff
				{							
							set_end.asdadd=1;
								if(SPEED_Stand>=SPEED_Stand_C[2])
								{
									SPEED_Stand=SPEED_Stand_C[1];
									motorset.flag_run=1;
									motorset.flag_run_jiangsu=1;
									return 3;
								}else
								if(SPEED_Stand==SPEED_Stand_C[1])
								{
									motorset.flag_run_jiangsu=0;
										motorset.DIR_MOTOR_old=motorset.DIR_MOTOR;
									//	Current_UP=current_up;
									motorset.stop1=3;
									if(set_end.flag_setend==1)
									{
										flag_estop=0;	
										if(dataStructInterface.closeOffMode==1)//liju
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
											{
												set_end.flag_closeOffMode=1;
											}
										}else  //xingcheng
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
											{
												set_end.flag_closeOffMode=2;
											}
										}
										if(dataStructInterface.openOffMode==1)//liju
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
											{
												set_end.flag_openOffMode=1;
											}
										}else   //xingcheng
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
											{
												set_end.flag_openOffMode=2;
											}
										}
									}else
									if(set_end.flag_setend==0)
									{
											if(motorset.DIR_MOTOR_old==motorset.DIR_MOTOR_n)
											{
												set_end.flag_move_right=1;
												set_end.flag_move_left=0;
											}	else
											if(motorset.DIR_MOTOR_old==motorset.DIR_MOTOR_s)
											{
												set_end.flag_move_left=1;
												set_end.flag_move_right=0;
											}
											flag_estop=1;		
									}											
										return 2;		
								}
				}
				else
				{
					//set_end.asdadd=0;
					set_end.flag_closeOffMode=0;
					set_end.flag_openOffMode=0;
					if(flag_estop==1)
					{
					
					}else
					{
						flag_estop=0;
						return 1;
					}	
				}
		}
	
}
#endif



#ifdef  EE13

uint16_t  SPEED_Stand_C[7]= {       20,       28,       40,      56,       80,       112,        160};
uint16_t  TORQUE_Stand_C[8]={       18,       24,       30,      36,       42,       48,        54,      60};
uint16_t EE13_SPEED_RUN[7]= {   0x0640,   0x0898,   0x0BB8,  0x0FA0,   0x15E0,   0x1E14,    0x2AF8};  //平稳运行下发的转速
static uint16_t EE13_RISE_TIME[7]= {       65,       115/*115 75*/,       88,  400/*103*/,500/*130*/, 500/*165*/, 600/*219*/};  //从停转到稳定转速中间码个数
static uint16_t EE13_DOWN_TIME[7]= {       53,       67,       55,   200/*78*/,300/*116*/, 200/*164*/, 241};  //从稳定到停转转速中间码个数
static uint16_t EE13_SPEED_END[7]= {   0x0000,   0x0000,   0x0000,  0x0000,   0x0000,   0x0000,    0x0000};   
static float    EE13_torque_min[7]={      0.1,      0.6,      0.6,     0.1,      0.1,      0.1,        0.1};
static float    EE13_torque_max[7]={      1.5,      1.5,      1.5,     1.1,      1.1,      1.1,        1.1};
static float     EE13_torque_a[7]= {  -0.7407,  -0.9312,  -1.0476, -1.2381,  -1.6614,  -4.3175,    -4.1481};  //平稳运行下发的转矩A
static float     EE13_torque_b[7]= {   169.78,   199.87,   229.65,  270.41,   344.83,   574.48,  520.44  };   //平稳运行下发的转矩B
static float     EE13_torque_c[7]= {   3525.3,3925.3+300,     4635,    5451,   6616.8,  6272-400,    15456};  //平稳运行下发的转矩C
static float    EE13_current_a[7]= {   0.0587,  -0.0026 ,  0.0909, 0.039,      0.0243,  0.122,        0.1243};//启动阶段的尖峰电流A
static float    EE13_current_b[7]= {   1.3442,    6.0238,  0.1528,  4.2302,   6.5744,   2.5298,   6.746};     //启动阶段的尖峰电流B
static float    EE13_current_c[7]= {   46.577,   -15.405,  82.036,  49.798,    49.411,   154.68,   133.79};   //启动阶段的尖峰电流C
unsigned short EE13_voltage[7][8];
unsigned short EE13_current[7][8];
void Set_DZ(void)
{
	EE13_voltage[0][0]=usb_torque_vol.T1_1;
	EE13_voltage[0][1]=usb_torque_vol.T1_2;
	EE13_voltage[0][2]=usb_torque_vol.T1_3;
	EE13_voltage[0][3]=usb_torque_vol.T1_4;
	EE13_voltage[0][4]=usb_torque_vol.T1_5;
	EE13_voltage[0][5]=usb_torque_vol.T1_6;
	EE13_voltage[0][6]=usb_torque_vol.T1_7;
	EE13_voltage[0][7]=usb_torque_vol.T1_8;
	EE13_voltage[1][0]=usb_torque_vol.T2_1;
	EE13_voltage[1][1]=usb_torque_vol.T2_2;
	EE13_voltage[1][2]=usb_torque_vol.T2_3;
	EE13_voltage[1][3]=usb_torque_vol.T2_4;
	EE13_voltage[1][4]=usb_torque_vol.T2_5;
	EE13_voltage[1][5]=usb_torque_vol.T2_6;
	EE13_voltage[1][6]=usb_torque_vol.T2_7;
	EE13_voltage[1][7]=usb_torque_vol.T2_8;
	EE13_voltage[2][0]=usb_torque_vol.T3_1;
	EE13_voltage[2][1]=usb_torque_vol.T3_2;
	EE13_voltage[2][2]=usb_torque_vol.T3_3;
	EE13_voltage[2][3]=usb_torque_vol.T3_4;
	EE13_voltage[2][4]=usb_torque_vol.T3_5;
	EE13_voltage[2][5]=usb_torque_vol.T3_6;
	EE13_voltage[2][6]=usb_torque_vol.T3_7;
	EE13_voltage[2][7]=usb_torque_vol.T3_8;
	EE13_voltage[3][0]=usb_torque_vol.T4_1;
	EE13_voltage[3][1]=usb_torque_vol.T4_2;
	EE13_voltage[3][2]=usb_torque_vol.T4_3;
	EE13_voltage[3][3]=usb_torque_vol.T4_4;
	EE13_voltage[3][4]=usb_torque_vol.T4_5;
	EE13_voltage[3][5]=usb_torque_vol.T4_6;
	EE13_voltage[3][6]=usb_torque_vol.T4_7;
	EE13_voltage[3][7]=usb_torque_vol.T4_8;
	EE13_voltage[4][0]=usb_torque_vol.T5_1;
	EE13_voltage[4][1]=usb_torque_vol.T5_2;
	EE13_voltage[4][2]=usb_torque_vol.T5_3;
	EE13_voltage[4][3]=usb_torque_vol.T5_4;
	EE13_voltage[4][4]=usb_torque_vol.T5_5;
	EE13_voltage[4][5]=usb_torque_vol.T5_6;
	EE13_voltage[4][6]=usb_torque_vol.T5_7;
	EE13_voltage[4][7]=usb_torque_vol.T5_8;
	EE13_voltage[5][0]=usb_torque_vol.T6_1;
	EE13_voltage[5][1]=usb_torque_vol.T6_2;
	EE13_voltage[5][2]=usb_torque_vol.T6_3;
	EE13_voltage[5][3]=usb_torque_vol.T6_4;
	EE13_voltage[5][4]=usb_torque_vol.T6_5;
	EE13_voltage[5][5]=usb_torque_vol.T6_6;
	EE13_voltage[5][6]=usb_torque_vol.T6_7;
	EE13_voltage[5][7]=usb_torque_vol.T6_8;
	EE13_voltage[6][0]=usb_torque_vol.T7_1;
	EE13_voltage[6][1]=usb_torque_vol.T7_2;
	EE13_voltage[6][2]=usb_torque_vol.T7_3;
	EE13_voltage[6][3]=usb_torque_vol.T7_4;
	EE13_voltage[6][4]=usb_torque_vol.T7_5;
	EE13_voltage[6][5]=usb_torque_vol.T7_6;
	EE13_voltage[6][6]=usb_torque_vol.T7_7;
	EE13_voltage[6][7]=usb_torque_vol.T7_8;
	
	
	EE13_current[0][0]=usb_torque_cur.T1_1;
	EE13_current[0][1]=usb_torque_cur.T1_2;
	EE13_current[0][2]=usb_torque_cur.T1_3;
	EE13_current[0][3]=usb_torque_cur.T1_4;
	EE13_current[0][4]=usb_torque_cur.T1_5;
	EE13_current[0][5]=usb_torque_cur.T1_6;
	EE13_current[0][6]=usb_torque_cur.T1_7;
	EE13_current[0][7]=usb_torque_cur.T1_8;
	EE13_current[1][0]=usb_torque_cur.T2_1;
	EE13_current[1][1]=usb_torque_cur.T2_2;
	EE13_current[1][2]=usb_torque_cur.T2_3;
	EE13_current[1][3]=usb_torque_cur.T2_4;
	EE13_current[1][4]=usb_torque_cur.T2_5;
	EE13_current[1][5]=usb_torque_cur.T2_6;
	EE13_current[1][6]=usb_torque_cur.T2_7;
	EE13_current[1][7]=usb_torque_cur.T2_8;
	EE13_current[2][0]=usb_torque_cur.T3_1;
	EE13_current[2][1]=usb_torque_cur.T3_2;
	EE13_current[2][2]=usb_torque_cur.T3_3;
	EE13_current[2][3]=usb_torque_cur.T3_4;
	EE13_current[2][4]=usb_torque_cur.T3_5;
	EE13_current[2][5]=usb_torque_cur.T3_6;
	EE13_current[2][6]=usb_torque_cur.T3_7;
	EE13_current[2][7]=usb_torque_cur.T3_8;
	EE13_current[3][0]=usb_torque_cur.T4_1;
	EE13_current[3][1]=usb_torque_cur.T4_2;
	EE13_current[3][2]=usb_torque_cur.T4_3;
	EE13_current[3][3]=usb_torque_cur.T4_4;
	EE13_current[3][4]=usb_torque_cur.T4_5;
	EE13_current[3][5]=usb_torque_cur.T4_6;
	EE13_current[3][6]=usb_torque_cur.T4_7;
	EE13_current[3][7]=usb_torque_cur.T4_8;
	EE13_current[4][0]=usb_torque_cur.T5_1;
	EE13_current[4][1]=usb_torque_cur.T5_2;
	EE13_current[4][2]=usb_torque_cur.T5_3;
	EE13_current[4][3]=usb_torque_cur.T5_4;
	EE13_current[4][4]=usb_torque_cur.T5_5;
	EE13_current[4][5]=usb_torque_cur.T5_6;
	EE13_current[4][6]=usb_torque_cur.T5_7;
	EE13_current[4][7]=usb_torque_cur.T5_8;
	EE13_current[5][0]=usb_torque_cur.T6_1;
	EE13_current[5][1]=usb_torque_cur.T6_2;
	EE13_current[5][2]=usb_torque_cur.T6_3;
	EE13_current[5][3]=usb_torque_cur.T6_4;
	EE13_current[5][4]=usb_torque_cur.T6_5;
	EE13_current[5][5]=usb_torque_cur.T6_6;
	EE13_current[5][6]=usb_torque_cur.T6_7;
	EE13_current[5][7]=usb_torque_cur.T6_8;
	EE13_current[6][0]=usb_torque_cur.T7_1;
	EE13_current[6][1]=usb_torque_cur.T7_2;
	EE13_current[6][2]=usb_torque_cur.T7_3;
	EE13_current[6][3]=usb_torque_cur.T7_4;
	EE13_current[6][4]=usb_torque_cur.T7_5;
	EE13_current[6][5]=usb_torque_cur.T7_6;
	EE13_current[6][6]=usb_torque_cur.T7_7;
	EE13_current[6][7]=usb_torque_cur.T7_8;
}

//#define CURRENT_STOP_MIN (EE13_current_a[0]*TORQUE_Stand_C[0]*TORQUE_Stand_C[0]+EE13_current_b[0]*TORQUE_Stand_C[0]+EE13_current_c[0])
uint16_t calCurrentBaseMin(void)
{   
    uint16_t speed_tmp;
    uint16_t gear = 0;
    uint16_t i = 0;
    speed_tmp = (motorset.DIR_MOTOR == motorset.DIR_MOTOR_n) ? dataStructInterface.speed_open : dataStructInterface.speed_close;
    
    for(i = 0;i < 7;i ++)
    {
        if(speed_tmp == SPEED_Stand_C[i])
        {
            gear = i;
        }
    }
    
    return (EE13_current_a[gear]*TORQUE_Stand_C[0]*TORQUE_Stand_C[0]+EE13_current_b[gear]*TORQUE_Stand_C[0]+EE13_current_c[gear]);
}


void choice_speed_line()
{
	float torque_cl;
	float current_cl;
	float torque_a,torque_b,torque_c;
	float current_a,current_b,current_c;
	unsigned short torque_test,current_test;
	int i;
    static uint16_t speed_tmp;
    uint16_t CURRENT_STOP_MIN;
    
	Set_DZ();
	switch(SPEED_Stand)
	{
		case 20:
					{
						SPEED_RUN=EE13_SPEED_RUN[0];
						RISE_TIME=EE13_RISE_TIME[0];
						DOWN_TIME=EE13_DOWN_TIME[0];
						SPEED_END=EE13_SPEED_END[0];
						torque_a = EE13_torque_a[0];
						torque_b = EE13_torque_b[0];
						torque_c = EE13_torque_c[0];
						current_a=EE13_current_a[0];
						current_b=EE13_current_b[0];
						current_c=EE13_current_c[0];
						motorset.torque_max=EE13_torque_max[0];
						motorset.torque_min=EE13_torque_min[0];
						TORQUE_END=0x1C00;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= EE13_voltage[0][0]; current_test= EE13_current[0][0];break;
							case 24: torque_test= EE13_voltage[0][1]; current_test= EE13_current[0][1]; break;
							case 30: torque_test= EE13_voltage[0][2]; current_test= EE13_current[0][2]; current_c=current_c+30;break;
							case 36: torque_test= EE13_voltage[0][3]; current_test= EE13_current[0][3]; break;
							case 42: torque_test= EE13_voltage[0][4]; current_test= EE13_current[0][4]; break;
							case 48: torque_test= EE13_voltage[0][5]; current_test= EE13_current[0][5]; break;
							case 54: torque_test= EE13_voltage[0][6]; current_test= EE13_current[0][6]; break;
							case 60: torque_test= EE13_voltage[0][7]; current_test= EE13_current[0][7]; break;
								default: break;
								
						}
					}
						break;
		case 28:
					{
						SPEED_RUN=EE13_SPEED_RUN[1];
						RISE_TIME=EE13_RISE_TIME[1];
						DOWN_TIME=EE13_DOWN_TIME[1];
						SPEED_END=EE13_SPEED_END[1];
						torque_a = EE13_torque_a[1];
						torque_b = EE13_torque_b[1];
						torque_c = EE13_torque_c[1];
						current_a=EE13_current_a[1];
						current_b=EE13_current_b[1];
						current_c=EE13_current_c[1];
						motorset.torque_max=EE13_torque_max[1];
						motorset.torque_min=EE13_torque_min[1];
						TORQUE_END=0x1C00;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= EE13_voltage[1][0]; current_test= EE13_current[0][0]; break;
							case 24: torque_test= EE13_voltage[1][1]; current_test= EE13_current[0][1]; break;
							case 30: torque_test= EE13_voltage[1][2]; current_test= EE13_current[0][2]; break;
							case 36: torque_test= EE13_voltage[1][3]; current_test= EE13_current[0][3]; break;
							case 42: torque_test= EE13_voltage[1][4]; current_test= EE13_current[0][4]; break;
							case 48: torque_test= EE13_voltage[1][5]; current_test= EE13_current[0][5]; break;
							case 54: torque_test= EE13_voltage[1][6]; current_test= EE13_current[0][6]; break;
							case 60: torque_test= EE13_voltage[1][7]; current_test= EE13_current[0][7]; break;
								default: break;
								
						}
					}
						break;
		case 40:
					{
						SPEED_RUN=EE13_SPEED_RUN[2];
						RISE_TIME=EE13_RISE_TIME[2];
						DOWN_TIME=EE13_DOWN_TIME[2];
						SPEED_END=EE13_SPEED_END[2];
						torque_a = EE13_torque_a[2];
						torque_b = EE13_torque_b[2];
						torque_c = EE13_torque_c[2];
						current_a=EE13_current_a[2];
						current_b=EE13_current_b[2];
						current_c=EE13_current_c[2];
						motorset.torque_max=EE13_torque_max[2];
						motorset.torque_min=EE13_torque_min[2];
						TORQUE_END=0x1C00;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= EE13_voltage[2][0]; current_test= EE13_current[0][0]; break;
							case 24: torque_test= EE13_voltage[2][1]; current_test= EE13_current[0][1]; break;
							case 30: torque_test= EE13_voltage[2][2]; current_test= EE13_current[0][2]; break;
							case 36: torque_test= EE13_voltage[2][3]; current_test= EE13_current[0][3]; break;
							case 42: torque_test= EE13_voltage[2][4]; current_test= EE13_current[0][4]; break;
							case 48: torque_test= EE13_voltage[2][5]; current_test= EE13_current[0][5]; break;
							case 54: torque_test= EE13_voltage[2][6]; current_test= EE13_current[0][6]; break;
							case 60: torque_test= EE13_voltage[2][7]; current_test= EE13_current[0][7]; break;
								default: break;
								
						}
					}
						break;
		case 56:
					{
						SPEED_RUN=EE13_SPEED_RUN[3];
						RISE_TIME=EE13_RISE_TIME[3];
						DOWN_TIME=EE13_DOWN_TIME[3];
						SPEED_END=EE13_SPEED_END[3];
						torque_a = EE13_torque_a[3];
						torque_b = EE13_torque_b[3];
						torque_c = EE13_torque_c[3];
						current_a=EE13_current_a[3];
						current_b=EE13_current_b[3];
						current_c=EE13_current_c[3];
						motorset.torque_max=EE13_torque_max[3];
						motorset.torque_min=EE13_torque_min[3];
						TORQUE_END=0x1C00;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= EE13_voltage[3][0]; current_test= EE13_current[0][0]; break;
							case 24: torque_test= EE13_voltage[3][1]; current_test= EE13_current[0][1]; break;
							case 30: torque_test= EE13_voltage[3][2]; current_test= EE13_current[0][2]; break;
							case 36: torque_test= EE13_voltage[3][3]; current_test= EE13_current[0][3]; break;
							case 42: torque_test= EE13_voltage[3][4]; current_test= EE13_current[0][4]; break;
							case 48: torque_test= EE13_voltage[3][5]; current_test= EE13_current[0][5]; break;
							case 54: torque_test= EE13_voltage[3][6]; current_test= EE13_current[0][6]; break;
							case 60: torque_test= EE13_voltage[3][7]; current_test= EE13_current[0][7]; break;
								default: break;
								
						}
					}
						break;
		case 80:
					{
						SPEED_RUN=EE13_SPEED_RUN[4];
						RISE_TIME=EE13_RISE_TIME[4];
						DOWN_TIME=EE13_DOWN_TIME[4];
						SPEED_END=EE13_SPEED_END[4];
						torque_a = EE13_torque_a[4];
						torque_b = EE13_torque_b[4];
						torque_c = EE13_torque_c[4];
						current_a=EE13_current_a[4];
						current_b=EE13_current_b[4];
						current_c=EE13_current_c[4];
						motorset.torque_max=EE13_torque_max[4];
						motorset.torque_min=EE13_torque_min[4];
						TORQUE_END=0x1C00;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= EE13_voltage[4][0]; current_test= EE13_current[0][0]; break;
							case 24: torque_test= EE13_voltage[4][1]; current_test= EE13_current[0][1]; break;
							case 30: torque_test= EE13_voltage[4][2]; current_test= EE13_current[0][2]; break;
							case 36: torque_test= EE13_voltage[4][3]; current_test= EE13_current[0][3]; break;
							case 42: torque_test= EE13_voltage[4][4]; current_test= EE13_current[0][4]; break;
							case 48: torque_test= EE13_voltage[4][5]; current_test= EE13_current[0][5]; break;
							case 54: torque_test= EE13_voltage[4][6]; current_test= EE13_current[0][6]; break;
							case 60: torque_test= EE13_voltage[4][7]; current_test= EE13_current[0][7]; break;
								default: break;
								
						}
						
					}
						break;
		case 112:
					{
						SPEED_RUN=EE13_SPEED_RUN[5];
						RISE_TIME=EE13_RISE_TIME[5];
						DOWN_TIME=EE13_DOWN_TIME[5];
						SPEED_END=EE13_SPEED_END[5];
						torque_a = EE13_torque_a[5];
						torque_b = EE13_torque_b[5];
						torque_c = EE13_torque_c[5];
						current_a=EE13_current_a[5];
						current_b=EE13_current_b[5];
						current_c=EE13_current_c[5];
						motorset.torque_max=EE13_torque_max[5];
						motorset.torque_min=EE13_torque_min[5];
						TORQUE_END=0x1C00;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= EE13_voltage[5][0]; current_test= EE13_current[0][0]; break;
							case 24: torque_test= EE13_voltage[5][1]; current_test= EE13_current[0][1]; break;
							case 30: torque_test= EE13_voltage[5][2]; current_test= EE13_current[0][2]; break;
							case 36: torque_test= EE13_voltage[5][3]; current_test= EE13_current[0][3]; break;
							case 42: torque_test= EE13_voltage[5][4]; current_test= EE13_current[0][4]; break;
							case 48: torque_test= EE13_voltage[5][5]; current_test= EE13_current[0][5]; break;
							case 54: torque_test= EE13_voltage[5][6]; current_test= EE13_current[0][6]; break;
							case 60: torque_test= EE13_voltage[5][7]; current_test= EE13_current[0][7]; break;
								default: break;
								
						}
					}
						break;
		case 160:
					{
						SPEED_RUN=EE13_SPEED_RUN[6];
						RISE_TIME=EE13_RISE_TIME[6];
						DOWN_TIME=EE13_DOWN_TIME[6];
						SPEED_END=EE13_SPEED_END[6];
						torque_a = EE13_torque_a[6];
						torque_b = EE13_torque_b[6];
						torque_c = EE13_torque_c[6];
						current_a=EE13_current_a[6];
						current_b=EE13_current_b[6];
						current_c=EE13_current_c[6];
						motorset.torque_max=EE13_torque_max[6];
						motorset.torque_min=EE13_torque_min[6];
						TORQUE_RUN=0x2F40;
						TORQUE_END=0x1C00;
						switch(TORQUE_Stand)
						{
							case 18: torque_test= EE13_voltage[6][0]; current_test= EE13_current[0][0]; break;
							case 24: torque_test= EE13_voltage[6][1]; current_test= EE13_current[0][1]; break;
							case 30: torque_test= EE13_voltage[6][2]; current_test= EE13_current[0][2]; break;
							case 36: torque_test= EE13_voltage[6][3]; current_test= EE13_current[0][3]; break;
							case 42: torque_test= EE13_voltage[6][4]; current_test= EE13_current[0][4]; break;
							case 48: torque_test= EE13_voltage[6][5]; current_test= EE13_current[0][5]; break;
							case 54: torque_test= EE13_voltage[6][6]; current_test= EE13_current[0][6]; break;
							case 60: torque_test= EE13_voltage[6][7]; current_test= EE13_current[0][7]; break;
								default: break;
								
						}
					}
						break;
		default: break;
			
	}
	
	ABC = (current_a*(float )TORQUE_Stand*(float )TORQUE_Stand);
	ABD = (current_b*(float )TORQUE_Stand);
	ABE = current_c;
	//Current_STOP=ABC+ABD+ABE;
    CURRENT_STOP_MIN = calCurrentBaseMin();
    Current_STOP=((ABC+ABD+ABE) > CURRENT_STOP_MIN) ? (ABC+ABD+ABE) : CURRENT_STOP_MIN;  //89为EE13电机最低转速转矩档对应的堵转基准电流，转矩转速初始化搞定之后可以删去
	torque_cl=((torque_a*TORQUE_Stand*TORQUE_Stand)+(torque_b*TORQUE_Stand)+ torque_c)+800;
	for(i=1;i<7;i++)
	{
		if(SPEED_Stand==SPEED_Stand_C[i])
		{
			SPEED_DEC=(float)(EE13_SPEED_RUN[i]-EE13_SPEED_RUN[i-1])/DOWN_TIME;
		}
	}
	TORQUE_RUN=(uint16_t)torque_cl;
	SPEED_ADD=(float)(SPEED_RUN)/RISE_TIME;
	TORQUE_ADD=(float)(TORQUE_RUN*(motorset.torque_max-motorset.torque_min))/RISE_TIME;
}


#define CURRENT_BASE_OFFSET 10 //电流限值增加偏移，以规避启停瞬间的电流冲高，导致误动作堵转。（另外，也可以对下板启停阶段上传电流值加以限制）
int changeDIR(void)
{
	if((motorset.flag_run == 0) && (is_endpos == 0))  //前者用来规避启动2s内的堵转判断，后者用来规避末端位置的堵转判断
	{
		if((((current_up)&0x0fff) > (Current_BASE + CURRENT_BASE_OFFSET)))  //if((((current_up)&0x0fff)>280))
		{
			set_end.asdadd=1;
			if(SPEED_Stand>=SPEED_Stand_C[2])
			{
				SPEED_Stand=SPEED_Stand_C[1];
				motorset.flag_run=1;
				motorset.flag_run_jiangsu=1;
				return 3;
			}
            else if((SPEED_Stand>=SPEED_Stand_C[0])&&(SPEED_Stand<=SPEED_Stand_C[1]))
			{
				motorset.flag_run_jiangsu=0;
				motorset.DIR_MOTOR_old=motorset.DIR_MOTOR;
				motorset.stop1=3;
				if(set_end.flag_setend==1)
				{
					flag_estop=0;
					if(dataStructInterface.closeOffMode==1)
					{
						if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
						{
							set_end.flag_closeOffMode=1;
						}
					}else  
					{
						if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
						{
							set_end.flag_closeOffMode=2;
						}
					}
					if(dataStructInterface.openOffMode==1)//liju
					{
						if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
						{
							set_end.flag_openOffMode=1;
						}
					}else  
					{
						if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
						{
							set_end.flag_openOffMode=2;
						}
					}
					set_end.flag_liju=1;
				}
                else if(set_end.flag_setend==0)
				{
					set_end.flag_liju=0;
					if(motorset.DIR_MOTOR_old==motorset.DIR_MOTOR_n)
					{
						set_end.flag_move_right=1;
						set_end.flag_move_left=0;
					}	else
					if(motorset.DIR_MOTOR_old==motorset.DIR_MOTOR_s)
					{
						set_end.flag_move_left=1;
						set_end.flag_move_right=0;
					}
					flag_estop=1;		
				}											
				return 2;		
			}
        }
        else
        {
            motorset.flag_start=0;
            set_end.flag_closeOffMode=0;
            set_end.flag_openOffMode=0;
            if(flag_estop==1)
            {
            
            }else
            {
                #if 0
				//if(((key_mlx90363.READ_run_1_old-key_mlx90363.READ_run_1)>0)&&(key_mlx90363.READ_run_1<(dataStructInterface.endPosClose*10)))
				if((encoder.num==7)||(encoder.num==6))
				{
                    if(((key_mlx90363.READ_run_1>(dataStructInterface.endPosClose*7)))&&((key_mlx90363.READ_run_1<(dataStructInterface.endPosClose*10)))&&(DIR_Send==0x44))
                    {
                        key_mlx90363.READ_run_jianflag=1;
                        if(set_end.flag_setend==0)
                        {
                            return 4;
                        }else
                        {
                            return 1;
                        }	
				
                    }
                    else if(((key_mlx90363.READ_run_1<(dataStructInterface.endPosOpen*10.5)))&&((key_mlx90363.READ_run_1>(dataStructInterface.endPosOpen*10)))&&(DIR_Send==0x4c))
                    {
                        key_mlx90363.READ_run_jianflag=1;
                        if(set_end.flag_setend==0)
                        {
                            return 4;
                        }
                        else
                        {
                            return 1;
                        }	
                    }
                    else
                    {
                        key_mlx90363.READ_run_jianflag=0;
                        key_mlx90363.READ_run_1_old=key_mlx90363.READ_run_1;
                        flag_estop=0;
                        return 1;
                    }
                }
                else if((encoder.num==1)||(encoder.num==4))
				{
					if((key_mlx90363.READ_run_1>(dataStructInterface.endPosClose*7))&&(key_mlx90363.READ_run_1<(dataStructInterface.endPosClose*10))&&(DIR_Send==0x4c))
					
					{
						key_mlx90363.READ_run_jianflag=1;
						if(set_end.flag_setend==0)
						{
						return 4;
						}else
						{
						return 1;
						}	
					
					}else
					if((key_mlx90363.READ_run_1<(dataStructInterface.endPosOpen*10.5))&&(key_mlx90363.READ_run_1>(dataStructInterface.endPosOpen*10))&&(DIR_Send==0x44))
					{
						key_mlx90363.READ_run_jianflag=1;
						if(set_end.flag_setend==0)
						{
						return 4;
						}else
						{
						return 1;
						}	
					}
					else
					{
						key_mlx90363.READ_run_jianflag=0;
						key_mlx90363.READ_run_1_old=key_mlx90363.READ_run_1;
						flag_estop=0;
						return 1;
					}
				}	else
				if((encoder.num==2)||(encoder.num==3))
				{
					if((key_mlx90363.READ_run_1>(dataStructInterface.endPosClose*7))&&(key_mlx90363.READ_run_1<(dataStructInterface.endPosClose*10))&&(DIR_Send==0x4c))
					
					{
						key_mlx90363.READ_run_jianflag=1;
						if(set_end.flag_setend==0)
						{
						return 4;
						}else
						{
						return 1;
						}	
					
					}else
					if((key_mlx90363.READ_run_1<(dataStructInterface.endPosOpen*10.5))&&(key_mlx90363.READ_run_1>(dataStructInterface.endPosOpen*10))&&(DIR_Send==0x44))
					{
						key_mlx90363.READ_run_jianflag=1;
						if(set_end.flag_setend==0)
						{
						return 4;
						}else
						{
						return 1;
						}	
					}
					else
					{
						key_mlx90363.READ_run_jianflag=0;
						key_mlx90363.READ_run_1_old=key_mlx90363.READ_run_1;
						flag_estop=0;
						return 1;
					}
				}	else
				if((encoder.num==5)||(encoder.num==8))//last
				{
					if((key_mlx90363.READ_run_1>(dataStructInterface.endPosClose*7))&&(key_mlx90363.READ_run_1<(dataStructInterface.endPosClose*10))&&(DIR_Send==0x44))
					
					{
						key_mlx90363.READ_run_jianflag=1;
						if(set_end.flag_setend==0)
						{
						return 4;
						}else
						{
						return 1;
						}	
					
					}else
					if((key_mlx90363.READ_run_1<(dataStructInterface.endPosOpen*10.5))&&(key_mlx90363.READ_run_1>(dataStructInterface.endPosOpen*10))&&(DIR_Send==0x4c))
					{
						key_mlx90363.READ_run_jianflag=1;
						if(set_end.flag_setend==0)
						{
						return 4;
						}else
						{
						return 1;
						}	
					}
					else
					{
						key_mlx90363.READ_run_jianflag=0;
						key_mlx90363.READ_run_1_old=key_mlx90363.READ_run_1;
						flag_estop=0;
						return 1;
					}
				}	
                #endif
			
			
			#if 1
			flag_estop=0;
			return 1;
			
			#endif
			}	
		}
	}
}
#endif





#ifdef  CE11

                    //SPEED_Stand= {     10,     14,     20,    28,     40,     56,      80}
static uint16_t DE13_SPEED_RUN[7]= { 0x0640, 0x0898, 0x0BB8,0x0FA0, 0x15E0, 0x1E14,  0x2AF8};
static uint16_t DE13_RISE_TIME[7]= {     65,     75,     88,   103,    130,    165,     219};
static uint16_t DE13_SPEED_END[7]= { 0x0000, 0x0000, 0x0000,0x0000, 0x0000, 0x0000,  0x0000};
static float     DE13_torque_a[7]= {-0.6455,-0.7831,-0.8148,-0.836,-0.7937,-0.7725,  6.4762};
static float     DE13_torque_b[7]= { 148.25,    168,    180,192.57, 207.81, 231.81, -159.24};
static float     DE13_torque_c[7]= { 2561.9,   3299, 4173.3,5303.2, 7180.6, 9568.4,   19141};
static float    DE13_current_a[7]= { 0.0157, 0.0157,      0,     0,      0,      0,       0};
static float    DE13_current_b[7]= { 4.1062, 4.1062, 2.7857,3.4782, 4.5238, 5.4762,  4.7857};
static float    DE13_current_c[7]= {  70000, 100000,     70,72.476,   88.5,   91.4,   148.8};
void choice_speed_line()
{
	float torque_cl;
	float current_cl;
	float torque_a,torque_b,torque_c;
	float current_a,current_b,current_c;
	switch(SPEED_Stand)
	{
		
		case 10:
					{
						SPEED_RUN=DE13_SPEED_RUN[0];
						RISE_TIME=DE13_RISE_TIME[0];
						SPEED_END=DE13_SPEED_END[0];
						torque_a = DE13_torque_a[0];
						torque_b = DE13_torque_b[0];
						torque_c = DE13_torque_c[0];
						current_a=DE13_current_a[0];
						current_b=DE13_current_b[0];
						current_c=DE13_current_c[0];
						TORQUE_END=0x1C00;
					}
						break;
		case 14:
					{
						SPEED_RUN=DE13_SPEED_RUN[1];
						RISE_TIME=DE13_RISE_TIME[1];
						SPEED_END=DE13_SPEED_END[1];
						torque_a = DE13_torque_a[1];
						torque_b = DE13_torque_b[1];
						torque_c = DE13_torque_c[1];
						current_a=DE13_current_a[1];
						current_b=DE13_current_b[1];
						current_c=DE13_current_c[1];
						TORQUE_END=0x1C00;
					}
						break;
		case 20:
					{
						SPEED_RUN=DE13_SPEED_RUN[2];
						RISE_TIME=DE13_RISE_TIME[2];
						SPEED_END=DE13_SPEED_END[2];
						torque_a = DE13_torque_a[2];
						torque_b = DE13_torque_b[2];
						torque_c = DE13_torque_c[2];
						current_a=DE13_current_a[2];
						current_b=DE13_current_b[2];
						current_c=DE13_current_c[2];
						TORQUE_END=0x1C00;//END_TORQUE_18;
					}
						break;
		case 28:
					{
						SPEED_RUN=DE13_SPEED_RUN[3];
						RISE_TIME=DE13_RISE_TIME[3];
						SPEED_END=DE13_SPEED_END[3];
						torque_a = DE13_torque_a[3];
						torque_b = DE13_torque_b[3];
						torque_c = DE13_torque_c[3];
						current_a=DE13_current_a[3];
						current_b=DE13_current_b[3];
						current_c=DE13_current_c[3];
						TORQUE_END=0x1C00;//END_TORQUE_18;
					}
						break;
		case 40:
					{
						SPEED_RUN=DE13_SPEED_RUN[4];
						RISE_TIME=DE13_RISE_TIME[4];
						SPEED_END=DE13_SPEED_END[4];
						torque_a = DE13_torque_a[4];
						torque_b = DE13_torque_b[4];
						torque_c = DE13_torque_c[4];
						current_a=DE13_current_a[4];
						current_b=DE13_current_b[4];
						current_c=DE13_current_c[4];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						
					}
						break;
		case 56:
					{
						SPEED_RUN=DE13_SPEED_RUN[5];
						RISE_TIME=DE13_RISE_TIME[5];
						SPEED_END=DE13_SPEED_END[5];
//						torque_cl=((-0.7196*TORQUE_Stand*TORQUE_Stand)+(258.03*TORQUE_Stand)+ 8863.2);
						torque_a = DE13_torque_a[5];
						torque_b = DE13_torque_b[5];
						torque_c = DE13_torque_c[5];
						current_a=DE13_current_a[5];
						current_b=DE13_current_b[5];
						current_c=DE13_current_c[5];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						//Current_STOP=500;
					}
						break;
		case 80:
					{
						SPEED_RUN=DE13_SPEED_RUN[6];
						RISE_TIME=DE13_RISE_TIME[6];
						SPEED_END=DE13_SPEED_END[6];
						torque_a = DE13_torque_a[6];
						torque_b = DE13_torque_b[6];
						torque_c = DE13_torque_c[6];
						current_a=DE13_current_a[6];
						current_b=DE13_current_b[6];
						current_c=DE13_current_c[6];
						TORQUE_RUN=0x2F40;//RUN_TORQUE_18;
						TORQUE_END=0x1C00;//END_TORQUE_18;
					}
						break;
		default: break;
			
	}
	ABC=(current_a*(float )TORQUE_Stand*(float )TORQUE_Stand);
	ABD=(current_b*(float )TORQUE_Stand);
	ABE=current_c;
	Current_STOP=ABC+ABD+ABE;
//	Current_STOP=current_cl;//60;//(uint16_t)current_cl;	
	torque_cl=((torque_a*TORQUE_Stand*TORQUE_Stand)+(torque_b*TORQUE_Stand)+ torque_c);
	if (torque_cl>23808)
	{
		TORQUE_RUN=23808;
	}
	TORQUE_RUN=(uint16_t)torque_cl;
	SPEED_ADD=(float)SPEED_RUN/RISE_TIME;
	TORQUE_ADD=(float)TORQUE_RUN/RISE_TIME;
}
#endif

#ifdef  DE11

                    //SPEED_Stand= {     10,     14,     20,    28,     40,     56,      80}
static uint16_t DE13_SPEED_RUN[7]= { 0x0640, 0x0898, 0x0BB8,0x0FA0, 0x15E0, 0x1E14,  0x2AF8};
static uint16_t DE13_RISE_TIME[7]= {     65,     75,     88,   103,    130,    165,     219};
static uint16_t DE13_SPEED_END[7]= { 0x0000, 0x0000, 0x0000,0x0000, 0x0000, 0x0000,  0x0000};
static float     DE13_torque_a[7]= {-0.6455,-0.7831,-0.8148,-0.836,-0.7937,-0.7725,  6.4762};
static float     DE13_torque_b[7]= { 148.25,    168,    180,192.57, 207.81, 231.81, -159.24};
static float     DE13_torque_c[7]= { 2561.9,   3299, 4173.3,5303.2, 7180.6, 9568.4,   19141};
static float    DE13_current_a[7]= { 0.0157, 0.0157,      0,     0,      0,      0,       0};
static float    DE13_current_b[7]= { 4.1062, 4.1062, 2.7857,3.4782, 4.5238, 5.4762,  4.7857};
static float    DE13_current_c[7]= {  70000, 100000,     70,72.476,   88.5,   91.4,   148.8};
void choice_speed_line()
{
	float torque_cl;
	float current_cl;
	float torque_a,torque_b,torque_c;
	float current_a,current_b,current_c;
	switch(SPEED_Stand)
	{
		
		case 10:
					{
						SPEED_RUN=DE13_SPEED_RUN[0];
						RISE_TIME=DE13_RISE_TIME[0];
						SPEED_END=DE13_SPEED_END[0];
						torque_a = DE13_torque_a[0];
						torque_b = DE13_torque_b[0];
						torque_c = DE13_torque_c[0];
						current_a=DE13_current_a[0];
						current_b=DE13_current_b[0];
						current_c=DE13_current_c[0];
						TORQUE_END=0x1C00;
					}
						break;
		case 14:
					{
						SPEED_RUN=DE13_SPEED_RUN[1];
						RISE_TIME=DE13_RISE_TIME[1];
						SPEED_END=DE13_SPEED_END[1];
						torque_a = DE13_torque_a[1];
						torque_b = DE13_torque_b[1];
						torque_c = DE13_torque_c[1];
						current_a=DE13_current_a[1];
						current_b=DE13_current_b[1];
						current_c=DE13_current_c[1];
						TORQUE_END=0x1C00;
					}
						break;
		case 20:
					{
						SPEED_RUN=DE13_SPEED_RUN[2];
						RISE_TIME=DE13_RISE_TIME[2];
						SPEED_END=DE13_SPEED_END[2];
						torque_a = DE13_torque_a[2];
						torque_b = DE13_torque_b[2];
						torque_c = DE13_torque_c[2];
						current_a=DE13_current_a[2];
						current_b=DE13_current_b[2];
						current_c=DE13_current_c[2];
						TORQUE_END=0x1C00;//END_TORQUE_18;
					}
						break;
		case 28:
					{
						SPEED_RUN=DE13_SPEED_RUN[3];
						RISE_TIME=DE13_RISE_TIME[3];
						SPEED_END=DE13_SPEED_END[3];
						torque_a = DE13_torque_a[3];
						torque_b = DE13_torque_b[3];
						torque_c = DE13_torque_c[3];
						current_a=DE13_current_a[3];
						current_b=DE13_current_b[3];
						current_c=DE13_current_c[3];
						TORQUE_END=0x1C00;//END_TORQUE_18;
					}
						break;
		case 40:
					{
						SPEED_RUN=DE13_SPEED_RUN[4];
						RISE_TIME=DE13_RISE_TIME[4];
						SPEED_END=DE13_SPEED_END[4];
						torque_a = DE13_torque_a[4];
						torque_b = DE13_torque_b[4];
						torque_c = DE13_torque_c[4];
						current_a=DE13_current_a[4];
						current_b=DE13_current_b[4];
						current_c=DE13_current_c[4];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						
					}
						break;
		case 56:
					{
						SPEED_RUN=DE13_SPEED_RUN[5];
						RISE_TIME=DE13_RISE_TIME[5];
						SPEED_END=DE13_SPEED_END[5];
//						torque_cl=((-0.7196*TORQUE_Stand*TORQUE_Stand)+(258.03*TORQUE_Stand)+ 8863.2);
						torque_a = DE13_torque_a[5];
						torque_b = DE13_torque_b[5];
						torque_c = DE13_torque_c[5];
						current_a=DE13_current_a[5];
						current_b=DE13_current_b[5];
						current_c=DE13_current_c[5];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						//Current_STOP=500;
					}
						break;
		case 80:
					{
						SPEED_RUN=DE13_SPEED_RUN[6];
						RISE_TIME=DE13_RISE_TIME[6];
						SPEED_END=DE13_SPEED_END[6];
						torque_a = DE13_torque_a[6];
						torque_b = DE13_torque_b[6];
						torque_c = DE13_torque_c[6];
						current_a=DE13_current_a[6];
						current_b=DE13_current_b[6];
						current_c=DE13_current_c[6];
						TORQUE_RUN=0x2F40;//RUN_TORQUE_18;
						TORQUE_END=0x1C00;//END_TORQUE_18;
					}
						break;
		default: break;
			
	}
	ABC=(current_a*(float )TORQUE_Stand*(float )TORQUE_Stand);
	ABD=(current_b*(float )TORQUE_Stand);
	ABE=current_c;
	Current_STOP=ABC+ABD+ABE;
//	Current_STOP=current_cl;//60;//(uint16_t)current_cl;	
	torque_cl=((torque_a*TORQUE_Stand*TORQUE_Stand)+(torque_b*TORQUE_Stand)+ torque_c);
	if (torque_cl>23808)
	{
		TORQUE_RUN=23808;
	}
	TORQUE_RUN=(uint16_t)torque_cl;
	SPEED_ADD=(float)SPEED_RUN/RISE_TIME;
	TORQUE_ADD=(float)TORQUE_RUN/RISE_TIME;
}
#endif

#ifdef  EE11

                    //SPEED_Stand= {     10,     14,     20,    28,     40,     56,      80}
static uint16_t DE13_SPEED_RUN[7]= { 0x0640, 0x0898, 0x0BB8,0x0FA0, 0x15E0, 0x1E14,  0x2AF8};
static uint16_t DE13_RISE_TIME[7]= {     65,     75,     88,   103,    130,    165,     219};
static uint16_t DE13_SPEED_END[7]= { 0x0000, 0x0000, 0x0000,0x0000, 0x0000, 0x0000,  0x0000};
static float     DE13_torque_a[7]= {-0.6455,-0.7831,-0.8148,-0.836,-0.7937,-0.7725,  6.4762};
static float     DE13_torque_b[7]= { 148.25,    168,    180,192.57, 207.81, 231.81, -159.24};
static float     DE13_torque_c[7]= { 2561.9,   3299, 4173.3,5303.2, 7180.6, 9568.4,   19141};
static float    DE13_current_a[7]= { 0.0157, 0.0157,      0,     0,      0,      0,       0};
static float    DE13_current_b[7]= { 4.1062, 4.1062, 2.7857,3.4782, 4.5238, 5.4762,  4.7857};
static float    DE13_current_c[7]= {  70000, 100000,     70,72.476,   88.5,   91.4,   148.8};
void choice_speed_line()
{
	float torque_cl;
	float current_cl;
	float torque_a,torque_b,torque_c;
	float current_a,current_b,current_c;
	switch(SPEED_Stand)
	{
		
		case 10:
					{
						SPEED_RUN=DE13_SPEED_RUN[0];
						RISE_TIME=DE13_RISE_TIME[0];
						SPEED_END=DE13_SPEED_END[0];
						torque_a = DE13_torque_a[0];
						torque_b = DE13_torque_b[0];
						torque_c = DE13_torque_c[0];
						current_a=DE13_current_a[0];
						current_b=DE13_current_b[0];
						current_c=DE13_current_c[0];
						TORQUE_END=0x1C00;
					}
						break;
		case 14:
					{
						SPEED_RUN=DE13_SPEED_RUN[1];
						RISE_TIME=DE13_RISE_TIME[1];
						SPEED_END=DE13_SPEED_END[1];
						torque_a = DE13_torque_a[1];
						torque_b = DE13_torque_b[1];
						torque_c = DE13_torque_c[1];
						current_a=DE13_current_a[1];
						current_b=DE13_current_b[1];
						current_c=DE13_current_c[1];
						TORQUE_END=0x1C00;
					}
						break;
		case 20:
					{
						SPEED_RUN=DE13_SPEED_RUN[2];
						RISE_TIME=DE13_RISE_TIME[2];
						SPEED_END=DE13_SPEED_END[2];
						torque_a = DE13_torque_a[2];
						torque_b = DE13_torque_b[2];
						torque_c = DE13_torque_c[2];
						current_a=DE13_current_a[2];
						current_b=DE13_current_b[2];
						current_c=DE13_current_c[2];
						TORQUE_END=0x1C00;//END_TORQUE_18;
					}
						break;
		case 28:
					{
						SPEED_RUN=DE13_SPEED_RUN[3];
						RISE_TIME=DE13_RISE_TIME[3];
						SPEED_END=DE13_SPEED_END[3];
						torque_a = DE13_torque_a[3];
						torque_b = DE13_torque_b[3];
						torque_c = DE13_torque_c[3];
						current_a=DE13_current_a[3];
						current_b=DE13_current_b[3];
						current_c=DE13_current_c[3];
						TORQUE_END=0x1C00;//END_TORQUE_18;
					}
						break;
		case 40:
					{
						SPEED_RUN=DE13_SPEED_RUN[4];
						RISE_TIME=DE13_RISE_TIME[4];
						SPEED_END=DE13_SPEED_END[4];
						torque_a = DE13_torque_a[4];
						torque_b = DE13_torque_b[4];
						torque_c = DE13_torque_c[4];
						current_a=DE13_current_a[4];
						current_b=DE13_current_b[4];
						current_c=DE13_current_c[4];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						
					}
						break;
		case 56:
					{
						SPEED_RUN=DE13_SPEED_RUN[5];
						RISE_TIME=DE13_RISE_TIME[5];
						SPEED_END=DE13_SPEED_END[5];
//						torque_cl=((-0.7196*TORQUE_Stand*TORQUE_Stand)+(258.03*TORQUE_Stand)+ 8863.2);
						torque_a = DE13_torque_a[5];
						torque_b = DE13_torque_b[5];
						torque_c = DE13_torque_c[5];
						current_a=DE13_current_a[5];
						current_b=DE13_current_b[5];
						current_c=DE13_current_c[5];
						TORQUE_END=0x1C00;//END_TORQUE_18;
						//Current_STOP=500;
					}
						break;
		case 80:
					{
						SPEED_RUN=DE13_SPEED_RUN[6];
						RISE_TIME=DE13_RISE_TIME[6];
						SPEED_END=DE13_SPEED_END[6];
						torque_a = DE13_torque_a[6];
						torque_b = DE13_torque_b[6];
						torque_c = DE13_torque_c[6];
						current_a=DE13_current_a[6];
						current_b=DE13_current_b[6];
						current_c=DE13_current_c[6];
						TORQUE_RUN=0x2F40;//RUN_TORQUE_18;
						TORQUE_END=0x1C00;//END_TORQUE_18;
					}
						break;
		default: break;
			
	}
	ABC=(current_a*(float )TORQUE_Stand*(float )TORQUE_Stand);
	ABD=(current_b*(float )TORQUE_Stand);
	ABE=current_c;
	Current_STOP=ABC+ABD+ABE;
//	Current_STOP=current_cl;//60;//(uint16_t)current_cl;	
	torque_cl=((torque_a*TORQUE_Stand*TORQUE_Stand)+(torque_b*TORQUE_Stand)+ torque_c);
	if (torque_cl>23808)
	{
		TORQUE_RUN=23808;
	}
	TORQUE_RUN=(uint16_t)torque_cl;
	SPEED_ADD=(float)SPEED_RUN/RISE_TIME;
	TORQUE_ADD=(float)TORQUE_RUN/RISE_TIME;
}
#endif







#if 0
int changeDIR(void)
{
	RC(current_up);
	if(Current_BASE<160)
	{
		Current_BASE=120;//140
	}
		if(motorset.flag_run==0)
		{
				if(((current_up)&0x0FFF)>Current_BASE)//Current_BASE  0xffff
				{							
							set_end.asdadd=1;
								if(SPEED_Stand>=SPEED_Stand_C[2])
								{
									SPEED_Stand=SPEED_Stand_C[1];
									motorset.flag_run=1;
									motorset.flag_run_jiangsu=1;
									return 3;
								}else
								if(SPEED_Stand==SPEED_Stand_C[1])
								{
									motorset.flag_run_jiangsu=0;
                                    motorset.DIR_MOTOR_old=motorset.DIR_MOTOR;
									//	Current_UP=current_up;
									motorset.stop1=3;
									if(set_end.flag_setend==1)
									{
										flag_estop=0;	
										if(dataStructInterface.closeOffMode==1)//liju
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
											{
												set_end.flag_closeOffMode=1;
											}
										}else  //xingcheng
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
											{
												set_end.flag_closeOffMode=2;
											}
										}
										if(dataStructInterface.openOffMode==1)//liju
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
											{
												set_end.flag_openOffMode=1;
											}
										}else   //xingcheng
										{
											if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
											{
												set_end.flag_openOffMode=2;
											}
										}
									}else
									if(set_end.flag_setend==0)
									{
											if(motorset.DIR_MOTOR_old==motorset.DIR_MOTOR_n)
											{
												set_end.flag_move_right=1;
												set_end.flag_move_left=0;
											}	else
											if(motorset.DIR_MOTOR_old==motorset.DIR_MOTOR_s)
											{
												set_end.flag_move_left=1;
												set_end.flag_move_right=0;
											}
											flag_estop=1;		
									}											
										return 2;		
								}
				}
				else
				{
					//set_end.asdadd=0;
					set_end.flag_closeOffMode=0;
					set_end.flag_openOffMode=0;
					if(flag_estop==1)
					{
					
					}else
					{
						flag_estop=0;
						return 1;
					}	
				}
		}
	
}

#endif



