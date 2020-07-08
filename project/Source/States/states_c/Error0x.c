#include "Error0x.h"
#include "hand.h"
#include "DataInterface.h"
#include <includes.h>

char Error_00(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}


char Error_01(void)
{ 
	int manualmode;
	manualmode=handdetection();
	if(manualmode==1)
	{
		return 0;
	}else
	{
		if(manualmode==0)
		{
			OSTimeDly(50);
			if(manualmode==0)
			{
				return 1;
			}else
			{
				return 0;
			}
		}
	}
}


char Error_02(void)
{
int chazhi;	
	if(remote_conntrol.KEYEme==1)
	{
		chazhi =abs(chazhi);
		return 1;
	}else
	{
		return 0;
	}
}
char Error_03(void)
{
	if(flag_figures.blockstop==1)
	{		
		states_error.blockednum++;
		return 1;
	}else
	{
		return 0;
	}
}
char Error_04(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_05(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}

#if 1
char Error_06(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_07(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_08(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_09(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}

#endif
