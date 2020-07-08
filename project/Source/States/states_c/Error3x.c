#include "Error3x.h"
#include  "datafigures.h"
char Error_31(void)
{
	if(encoder.set_end_ok==0)
	{
		return 1;
	}else
	if(encoder.set_end_ok==1)
	{
		return 0;
	}
}

char Error_32(void)
{
	if((ai_o420.input_error==1)&&(ai_o420.flag_mode4==1)&&(ledstates.remote==1))
	{return 1;}else
		{return 0;}
}
char Error_33(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_34(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_35(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_36(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_37(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_38(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}
char Error_39(void)
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

char Error_30(void)
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

