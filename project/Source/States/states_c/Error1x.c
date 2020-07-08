#include "Error1x.h"
#include "hand.h"
#include  "datafigures.h"
extern float ADC_TEMP1;
char Error_11(void)
{
	if(ADC_TEMP1<states_error.temp_adc)
	{
		return 0;
	}else
	{
		return 1;
	}
}

char Error_12(void)
{
	if(powerboard.voltage>300)
	{
		if(powerboard.voltage_high<powerboard.lcd_voltage)
		{
			return 1;
		}else
		{
			return 0;
		}
	}else
	{
		return 0;
	}
}
char Error_13(void)
{
	#if 1
		if(powerboard.voltage_low>powerboard.lcd_voltage)
		{
			return 1;
		}else
		{
			return 0;
		}
	#endif
}
char Error_14(void)
{
	int power_onoff;
	power_onoff=power_on();
	if(power_onoff==1)
	{
		return 0;
	}else
	{
		return 1;
	}
}



#if 1
char Error_10(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}


char Error_15(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}

char Error_16(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}

char Error_17(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}

char Error_18(void)
{
	if(1)
	{
		return 0;
	}else
	{
		return 1;
	}
}

char Error_19(void)
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

