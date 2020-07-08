#include "Error4x.h"
#include  "datafigures.h"
extern float ADC_TEMP1;
char Error_41(void)
{
	if(data_figures.TEMP_MOTOR>=3.3)
	{
		return 1;
	}else
	{
		return 0;
	}
}
char Error_42(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_43(void)
{
	if(((data_figures.READ_ALL)&0x0FFFFFFF)==posital_uncon)
	{
		return 1;
	}else
	{
		return 0;
	}
}
char Error_44(void)
{
	if(data_figures.READ_ALL>data_figures.READ_ALL_903)
	{
		return 0;
	}else
	{
		return 0;
	}
}
char Error_45(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_46(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}

char Error_48(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_49(void)
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
char Error_40(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}


char Error_47(void)
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
