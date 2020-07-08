#include "TIME.h"
#include  "datafigures.h"


int RUN_ele_time(void)
{
	if(timer.flag_all_run_s==1)
	{
		timer.flag_all_run_s=0;
		timer.run_s++;
		timer.flag_all_run=1;
	}
	if(timer.run_s>60)
	{
		timer.run_s=0;
		timer.run_m++;
	}
	if(timer.run_m>60)
	{
		timer.run_m=0;
		timer.run_h++;
	}
	
}

void RUN_Coils_time(void)
{
	if((motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)||(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n))
	{
		if(timer.flag_coils_run_s==1)
		{
			timer.flag_coils_run_s=0;
			timer.run_coils_s++;
		}
		if(timer.run_coils_s>60)
		{
			timer.run_coils_s=0;
			timer.run_coils_m++;
		}
		if(timer.run_coils_m>60)
		{
			timer.run_coils_m=0;
			timer.run_coils_h++;
		}
		timer.flag_coils=1;
	}
	
}
