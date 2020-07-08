#include "States_Error.h"


int Error(void)
{
	static uint16_t ERROR1=0;
	char test[64]={0};
	int i,j;
	#if 1
	test[12]=Overvo1tage();
	test[13]=Undervo1tage();
	
	
	
	#endif
	for(i=0;i<64;i++)
	{
		ERROR1=ERROR1<<1;
		if(test[i]==1)
		{
			ERROR1++;
		}else
		{
			ERROR1=ERROR1;
		}
	}
	
	
	return ERROR1;
}
char Undervo1tage()
{
	
	return 1;
}

char Overvo1tage()
{
	
	return 0;
}


