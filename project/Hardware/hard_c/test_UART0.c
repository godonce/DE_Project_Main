#include "test_UART0.h"
#include  "datafigures.h"
uint8_t buffer0[8];
extern uint8_t buffer0_ALL[6];
void check_test(void)
{
	int i=0;
	for(i=0;i<9;i++)
	{
		buffer0[0]=buffer0_ALL[i+0];
		buffer0[1]=buffer0_ALL[i+1];
		buffer0[2]=buffer0_ALL[i+2];
		buffer0[3]=buffer0_ALL[i+3];
		buffer0[4]=buffer0_ALL[i+4];
		buffer0[5]=buffer0_ALL[i+5];
		buffer0[6]=buffer0_ALL[i+6];
		buffer0[7]=buffer0_ALL[i+7];
		if(buffer0[0]==0xA5)
		{
			if(buffer0[1]==0x5A)
			{			
				break;
			}
		}
	}
}
	
void c_entry_uart0_encoder (void) 
{
	uint8_t buffer0_buf[8];
		buffer0_buf[0]=buffer0_ALL[5];
		buffer0_buf[1]=buffer0_ALL[0];
		buffer0_buf[2]=buffer0_ALL[1];
		buffer0_buf[3]=buffer0_ALL[2];
		buffer0_buf[4]=buffer0_ALL[3];
		buffer0_buf[5]=buffer0_ALL[4];
	
	encoder.ssi_m=(buffer0_buf[0]<<16)+(buffer0_buf[1]<<8)+(buffer0_buf[2]);
	encoder.ssi_s=(buffer0_buf[3]<<16)+(buffer0_buf[4]<<8)+(buffer0_buf[5]);
}

