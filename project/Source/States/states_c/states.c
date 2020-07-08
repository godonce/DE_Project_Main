#include "states.h"
#include  "datafigures.h"
#include "DataInterface.h"
char test[64]={0};
extern uint16_t SPEED_send;
extern float ADC_TEMP1;

int Init_error_data(void)
{
	
	states_error.indexFaultNum[0] =1;
	states_error.numStates =1;
	states_error.temp_adc=3.3;
	powerboard.power_voltage=380;
}

int data_init(void)
{
	int i;
	data_figures.AI1_low=0;
	data_figures.AI1_high=20;
	flag_figures.handle_stop=1;
    data_figures.READ_ALL=key_mlx90363.Read_all;
	data_figures.TEMP_MOTOR=ADC_TEMP1;
	powerboard.speed_send=SPEED_send;
    states.Coils_temp=20;
	states.Ele_temp=22;
	powerboard.lcd_voltage=((887-((float)(powerboard.voltage&0x03ff))))/1.5;
	powerboard.voltage_high=powerboard.power_voltage*1.15;
	powerboard.voltage_low=powerboard.power_voltage*0.7;
		#if 1
	test[0]  =Error_00();
	test[1]  =Error_01();
	test[2]  =Error_02();
	test[3]  =Error_03();
	test[4]  =Error_04();
	test[5]  =Error_05();
	test[6]  =Error_06();
	test[7]  =Error_07();
	test[8]  =Error_08();
	test[9]  =Error_09();
	test[10] =Error_10();
	test[11] =Error_11();
	test[12] =Error_12();
	test[13] =Error_13();
	test[14] =Error_14();
	test[15] =Error_15();
	test[16] =Error_16();
	test[17] =Error_17();
	test[18] =Error_18();
	test[19] =Error_19();
	test[20] =Error_20();
	test[21] =Error_21();
	test[22] =Error_22();
	test[23] =Error_23();
	test[24] =Error_24();
	test[25] =Error_25();
	test[26] =Error_26();
	test[27] =Error_27();
	test[28] =Error_28();
	test[29] =Error_29();
	test[30] =Error_30();
	test[31] =Error_31();
	test[32] =Error_32();
	test[33] =Error_33();
	test[34] =Error_34();
	test[35] =Error_35();
	test[36] =Error_36();
	test[37] =Error_37();
	test[38] =Error_38();
	test[39] =Error_39();
	test[40] =Error_40();
	test[41] =Error_41();
	test[42] =Error_42();
	test[43] =Error_43();
	test[44] =Error_44();
	test[45] =Error_45();
	test[46] =Error_46();
	test[47] =Error_47();
	test[48] =Error_48();
	test[49] =Error_49();
	test[50] =Error_50();
	test[51] =Error_51();
	test[52] =Error_52();
	test[53] =Error_53();
	test[54] =Error_54();
	test[55] =Error_55();
	test[56] =Error_56();
	test[57] =Error_57();
	test[58] =Error_58();
	test[59] =Error_59();
	test[60] =Error_60();
	test[61] =Error_61();
	test[62] =Error_62();
	test[63] =Error_63();
	#endif
}


int Error1(void)
{
	static uint32_t ERROR1=0;
	int i,j;

	for(i=63;i>=32;i--)
	{
		ERROR1=ERROR1<<1;
		if(test[i]==1)
		{
			ERROR1++;
			states_error.num_error1++;
		}else
		{
			ERROR1=ERROR1;
		}
	}	
	return ERROR1;
}


int Error2(void)
{
	static uint32_t ERROR2=0;
	int i,j;

	for(i=31;i>=0;i--)
	{
		ERROR2=ERROR2<<1;
		if(test[i]==1)
		{
			ERROR2++;
			states_error.num_error2++;
		}else
		{
			ERROR2=ERROR2;
		}
	}	
	return ERROR2;
}
#if 1
extern uint8_t DIR_MOTOR  ; 
int Error_out(void)
{
	char i;	
	char j=0;
	char k=1;
	int error=0;
	if(test[31]==1)
	{
		test[44]=0;
	}	
	for(i=1;i<64;i++)
	{
		if(test[i]==1)
		{
			dataStructInterface.indexFaultNum[j]=i;
			dataStructInterface.helpExpIndex[j+1]=i-1;
			dataStructInterface.helpMethodIndex[j+1]=i-1;
			j++;
			k++;
			states_error.num_error++;
			error++;
		}else
		{
			states_error.num_error=states_error.num_error;
			error=error;
		}
	}
	if(error<=0)
	{
		dataStructInterface.numFault=1;
		dataStructInterface.indexFaultNum[0]=0;
		dataStructInterface.helpExpIndex[0]=0;
		dataStructInterface.helpMethodIndex[0]=0;
		flag_figures.ready=0;
	}else
	{
		#if 1
		dataStructInterface.numFault=error;
		flag_figures.ready=1;
		if((test[31]==1))
		{
			if((motorset.local_error==1)||(ledstates.remote==1))
			{
				motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
			}
		}else
		if((test[2]==1))
		{
			if((motorset.local_error==1))
			{
				motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
			}
		}else
		{
		motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
		}
		#endif
	}
	return error;
}
#endif


int out_test[19];
extern char flag_estop;
void Extern_out_test(void)
{	
		if(1)
	{
		out_test[0]=0;
	}else
	{
		out_test[0]=0;
	}
			if(set_end.clall==1)
	{
		out_test[1]=1;
	}else
	{
		out_test[1]=0;
	}
			if(set_end.opall==1)
	{
		out_test[2]=1;
	}else
	{
		out_test[2]=0;
	}
	
		if((set_end.flag_move_right==1)&&(flag_estop==1))
	{
		out_test[3]=1;
	}else
	{
		out_test[3]=0;
	}
	
		if((set_end.flag_move_left==1)&&(flag_estop==1))
	{
		out_test[4]=1;
	}else
	{
		out_test[4]=0;
	}
	if(flag_estop==1)
	{
		out_test[5]=1;
	}else
	{
		out_test[5]=0;
	}
	
	if((Error_out()!=0))
	{
		out_test[6]=1;
	}else
	{
		out_test[6]=0;
	}
	
	if((motorset.DIR_MOTOR!=motorset.DIR_MOTOR_t))
	{
		out_test[7]=1;
	}else
	{
		out_test[7]=0;
	}
	
	if((Error_out()==0))
	{
		out_test[8]=1;
	}else
	{
		out_test[8]=0;
	}
	
	if((ledstates.remote==1)&&(Error_out()==0))
	{
		out_test[9]=1;
	}else
	{
		out_test[9]=0;
	}
	
		if(ledstates.local==1)
	{
		out_test[10]=1;
	}else
	{
		out_test[10]=0;
	}
	
		if(1)
	{
		out_test[11]=0;
	}else
	{
		out_test[11]=0;
	}
	
		if(1)
	{
		out_test[12]=0;
	}else
	{
		out_test[12]=0;
	}
	
	if(1)
	{
		out_test[13]=0;
	}else
	{
		out_test[13]=0;
	}
	
	if(1)
	{
		out_test[14]=0;
	}else
	{
		out_test[14]=0;
	}
	
	if(1)
	{
		out_test[15]=0;
	}else
	{
		out_test[15]=0;
	}
	
	if(1)
	{
		out_test[16]=0;
	}else
	{
		out_test[16]=0;
	}
	
	if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
	{
		out_test[17]=1;
	}else
	{
		out_test[17]=0;
	}
	
	if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
	{
		out_test[18]=1;
	}else
	{
		out_test[18]=0;
	}
	
}



