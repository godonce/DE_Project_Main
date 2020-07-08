#include "com_torque.h"
#include "stdint.h"
#include  "datafigures.h"
extern unsigned char Read_buf_modbus[20];
extern unsigned char Send_buf_modbus[40];
unsigned char com_torque_BUF[8];
extern uint16_t SPEED_Stand;
extern uint16_t TORQUE_Stand;

short READ_torque_remote(void)
{
	short value;
	value=(com_torque_BUF[7]<<8)+com_torque_BUF[6];	
	return value;

}
void m_torque_Read(void)
{
	int i;
	int j;
	
	for(i=0;i<8;i++)
	{
		if((Read_buf_modbus[i]==0xa5)&&(Read_buf_modbus[i+1]==0x5a))
		{
			for(j=0;j<8;j++)
			{
				com_torque_BUF[0+j]=Read_buf_modbus[i+j];
			}
		}
	}

	if((com_torque_BUF[0]==0xa5)&&(com_torque_BUF[1]==0x5a))
	{
		
		if(com_torque_BUF[2]==0x20)   //  0x30 com_0420  0x40 com_torque_voltage  0x50 com_torque_current
		{
			switch(com_torque_BUF[3])
			{
				case 1:	SPEED_Stand=READ_torque_remote(); break;
				case 2:	TORQUE_Stand=READ_torque_remote(); break;
				case 3:	SPEED_Stand=READ_torque_remote(); break;
				case 4:	TORQUE_Stand=READ_torque_remote(); break;
				default:              break;
				break;
			}
		}
		if(com_torque_BUF[2]==0x40)   //  0x30 com_0420  0x40 com_torque_voltage  0x50 com_torque_current
		{
			switch(com_torque_BUF[3])
			{
				case  1:	 usb_torque_vol.T1_1=READ_torque_remote();break;
				case  2:	 usb_torque_vol.T1_2=READ_torque_remote();break;
				case  3:	 usb_torque_vol.T1_3=READ_torque_remote();break;
				case  4:	 usb_torque_vol.T1_4=READ_torque_remote();break;
				case  5:	 usb_torque_vol.T1_5=READ_torque_remote();break;
				case  6:	 usb_torque_vol.T1_6=READ_torque_remote();break;
				case  7:	 usb_torque_vol.T1_7=READ_torque_remote();break;
				case  8:	 usb_torque_vol.T1_8=READ_torque_remote();break;
				case  9:	 usb_torque_vol.T2_1=READ_torque_remote();break;
				case 10:	 usb_torque_vol.T2_2=READ_torque_remote();break;
				case 11:	 usb_torque_vol.T2_3=READ_torque_remote();break;
				case 12:	 usb_torque_vol.T2_4=READ_torque_remote();break;
				case 13:	 usb_torque_vol.T2_5=READ_torque_remote();break;
				case 14:	 usb_torque_vol.T2_6=READ_torque_remote();break;
				case 15:	 usb_torque_vol.T2_7=READ_torque_remote();break;
				case 16:	 usb_torque_vol.T2_8=READ_torque_remote();break;
				case 17:	 usb_torque_vol.T3_1=READ_torque_remote();break;
				case 18:	 usb_torque_vol.T3_2=READ_torque_remote();break;
				case 19:	 usb_torque_vol.T3_3=READ_torque_remote();break;
				case 20:	 usb_torque_vol.T3_4=READ_torque_remote();break;
				case 21:	 usb_torque_vol.T3_5=READ_torque_remote();break;
				case 22:	 usb_torque_vol.T3_6=READ_torque_remote();break;
				case 23:	 usb_torque_vol.T3_7=READ_torque_remote();break;
				case 24:	 usb_torque_vol.T3_8=READ_torque_remote();break;
				case 25:	 usb_torque_vol.T4_1=READ_torque_remote();break;
				case 26:	 usb_torque_vol.T4_2=READ_torque_remote();break;
				case 27:	 usb_torque_vol.T4_3=READ_torque_remote();break;
				case 28:	 usb_torque_vol.T4_4=READ_torque_remote();break;
				case 29:	 usb_torque_vol.T4_5=READ_torque_remote();break;
				case 30:	 usb_torque_vol.T4_6=READ_torque_remote();break;
				case 31:	 usb_torque_vol.T4_7=READ_torque_remote();break;
				case 32:	 usb_torque_vol.T4_8=READ_torque_remote();break;
				case 33:	 usb_torque_vol.T5_1=READ_torque_remote();break;
				case 34:	 usb_torque_vol.T5_2=READ_torque_remote();break;
				case 35:	 usb_torque_vol.T5_3=READ_torque_remote();break;
				case 36:	 usb_torque_vol.T5_4=READ_torque_remote();break;
				case 37:	 usb_torque_vol.T5_5=READ_torque_remote();break;
				case 38:	 usb_torque_vol.T5_6=READ_torque_remote();break;
				case 39:	 usb_torque_vol.T5_7=READ_torque_remote();break;
				case 40:	 usb_torque_vol.T5_8=READ_torque_remote();break;
				case 41:	 usb_torque_vol.T6_1=READ_torque_remote();break;
				case 42:	 usb_torque_vol.T6_2=READ_torque_remote();break;
				case 43:	 usb_torque_vol.T6_3=READ_torque_remote();break;
				case 44:	 usb_torque_vol.T6_4=READ_torque_remote();break;
				case 45:	 usb_torque_vol.T6_5=READ_torque_remote();break;
				case 46:	 usb_torque_vol.T6_6=READ_torque_remote();break;
				case 47:	 usb_torque_vol.T6_7=READ_torque_remote();break;
				case 48:	 usb_torque_vol.T6_8=READ_torque_remote();break;
				case 49:	 usb_torque_vol.T7_1=READ_torque_remote();break;
				case 50:	 usb_torque_vol.T7_2=READ_torque_remote();break;
				case 51:	 usb_torque_vol.T7_3=READ_torque_remote();break;
				case 52:	 usb_torque_vol.T7_4=READ_torque_remote();break;
				case 53:	 usb_torque_vol.T7_5=READ_torque_remote();break;
				case 54:	 usb_torque_vol.T7_6=READ_torque_remote();break;
				case 55:	 usb_torque_vol.T7_7=READ_torque_remote();break;
				case 56:	 usb_torque_vol.T7_8=READ_torque_remote();break;

				default:              break;
				break;
			}
		}
		
		if(com_torque_BUF[2]==0x50)   //  0x30 com_0420  0x40 com_torque_voltage  0x50 com_torque_current
		{
			switch(com_torque_BUF[3])
			{
				case  1:	 usb_torque_cur.T1_1=READ_torque_remote();break;
				case  2:	 usb_torque_cur.T1_2=READ_torque_remote();break;
				case  3:	 usb_torque_cur.T1_3=READ_torque_remote();break;
				case  4:	 usb_torque_cur.T1_4=READ_torque_remote();break;
				case  5:	 usb_torque_cur.T1_5=READ_torque_remote();break;
				case  6:	 usb_torque_cur.T1_6=READ_torque_remote();break;
				case  7:	 usb_torque_cur.T1_7=READ_torque_remote();break;
				case  8:	 usb_torque_cur.T1_8=READ_torque_remote();break;
				case  9:	 usb_torque_cur.T2_1=READ_torque_remote();break;
				case 10:	 usb_torque_cur.T2_2=READ_torque_remote();break;
				case 11:	 usb_torque_cur.T2_3=READ_torque_remote();break;
				case 12:	 usb_torque_cur.T2_4=READ_torque_remote();break;
				case 13:	 usb_torque_cur.T2_5=READ_torque_remote();break;
				case 14:	 usb_torque_cur.T2_6=READ_torque_remote();break;
				case 15:	 usb_torque_cur.T2_7=READ_torque_remote();break;
				case 16:	 usb_torque_cur.T2_8=READ_torque_remote();break;
				case 17:	 usb_torque_cur.T3_1=READ_torque_remote();break;
				case 18:	 usb_torque_cur.T3_2=READ_torque_remote();break;
				case 19:	 usb_torque_cur.T3_3=READ_torque_remote();break;
				case 20:	 usb_torque_cur.T3_4=READ_torque_remote();break;
				case 21:	 usb_torque_cur.T3_5=READ_torque_remote();break;
				case 22:	 usb_torque_cur.T3_6=READ_torque_remote();break;
				case 23:	 usb_torque_cur.T3_7=READ_torque_remote();break;
				case 24:	 usb_torque_cur.T3_8=READ_torque_remote();break;
				case 25:	 usb_torque_cur.T4_1=READ_torque_remote();break;
				case 26:	 usb_torque_cur.T4_2=READ_torque_remote();break;
				case 27:	 usb_torque_cur.T4_3=READ_torque_remote();break;
				case 28:	 usb_torque_cur.T4_4=READ_torque_remote();break;
				case 29:	 usb_torque_cur.T4_5=READ_torque_remote();break;
				case 30:	 usb_torque_cur.T4_6=READ_torque_remote();break;
				case 31:	 usb_torque_cur.T4_7=READ_torque_remote();break;
				case 32:	 usb_torque_cur.T4_8=READ_torque_remote();break;
				case 33:	 usb_torque_cur.T5_1=READ_torque_remote();break;
				case 34:	 usb_torque_cur.T5_2=READ_torque_remote();break;
				case 35:	 usb_torque_cur.T5_3=READ_torque_remote();break;
				case 36:	 usb_torque_cur.T5_4=READ_torque_remote();break;
				case 37:	 usb_torque_cur.T5_5=READ_torque_remote();break;
				case 38:	 usb_torque_cur.T5_6=READ_torque_remote();break;
				case 39:	 usb_torque_cur.T5_7=READ_torque_remote();break;
				case 40:	 usb_torque_cur.T5_8=READ_torque_remote();break;
				case 41:	 usb_torque_cur.T6_1=READ_torque_remote();break;
				case 42:	 usb_torque_cur.T6_2=READ_torque_remote();break;
				case 43:	 usb_torque_cur.T6_3=READ_torque_remote();break;
				case 44:	 usb_torque_cur.T6_4=READ_torque_remote();break;
				case 45:	 usb_torque_cur.T6_5=READ_torque_remote();break;
				case 46:	 usb_torque_cur.T6_6=READ_torque_remote();break;
				case 47:	 usb_torque_cur.T6_7=READ_torque_remote();break;
				case 48:	 usb_torque_cur.T6_8=READ_torque_remote();break;
				case 49:	 usb_torque_cur.T7_1=READ_torque_remote();break;
				case 50:	 usb_torque_cur.T7_2=READ_torque_remote();break;
				case 51:	 usb_torque_cur.T7_3=READ_torque_remote();break;
				case 52:	 usb_torque_cur.T7_4=READ_torque_remote();break;
				case 53:	 usb_torque_cur.T7_5=READ_torque_remote();break;
				case 54:	 usb_torque_cur.T7_6=READ_torque_remote();break;
				case 55:	 usb_torque_cur.T7_7=READ_torque_remote();break;
				case 56:	 usb_torque_cur.T7_8=READ_torque_remote();break;

				default:              break;
				break;
			}
		}

	}

	
}