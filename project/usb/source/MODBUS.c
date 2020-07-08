#include "MODBUS.h"
void MODBUS_READ(void);
uint32_t USB_WriteEP(uint32_t EPNum, uint8_t *pData, uint32_t cnt);
void MODBUS_SEND_S(char *dat);
void MODBUS_SEND(char dat);
unsigned char Read_buf_modbus[20];
unsigned char Send_buf_modbus[40];
char *BUFF;
extern char i;
int Read_cnt;

int Send_BUF(char *dat)
{
	char i=0;
	 while( (*dat)!='\0' )   
	{
		Send_buf_modbus[i+5]=*dat;
		dat++;
		 i++;
	}
	return i+5;
}

///--------------------------------------------------P1_READ---------------------------------------///
void MODBUS_READ_P1()
{
	switch (Read_buf_modbus[4])
	{
		case 1:	 P1.Label="1";		                             MODBUS_SEND_S(P1.Label);                        break;
		case 2:	 P1.Pro_Name="2SA7011-2CD01-4";	               MODBUS_SEND_S(P1.Pro_Name);                     break;
		case 3:	 P1.Dat="3";			                             MODBUS_SEND_S(P1.Dat);                          break;
		case 4:	 P1.Time="4";			                             MODBUS_SEND_S(P1.Time);                         break;
		case 5:	 P1.Version_Nb="5";		                         MODBUS_SEND_S(P1.Version_Nb);                   break;
		case 6:	 P1.Source="6";		                             MODBUS_SEND_S(P1.Source);                       break;
		case 7:	 P1.Modle_Nb="7";		                           MODBUS_SEND_S(P1.Modle_Nb);                     break;
		case 8:	 P1.Sequence_Nb="8";		                       MODBUS_SEND_S(P1.Sequence_Nb);                  break;
		case 9:	 P1.First_Sequence_Nb="9";	                   MODBUS_SEND_S(P1.First_Sequence_Nb);            break;
		case 10: P1.Gear_Ratio="10";		                       MODBUS_SEND_S(P1.Gear_Ratio);                   break;	
		case 11: P1.Explain="2SA7011-2CD01-4SASCED";		       MODBUS_SEND_S(P1.Explain);	                     break;
		case 12: P1.Type="12";				                         MODBUS_SEND_S(P1.Type);                         break;	
		case 13: P1.Quality_Gu="13";		                       MODBUS_SEND_S(P1.Quality_Gu);                   break;		
		case 14: P1.Firmware_Version="14";		                 MODBUS_SEND_S(P1.Firmware_Version);	           break;		
		case 15: P1.Position_Control="15";		                 MODBUS_SEND_S(P1.Position_Control);	           break;
		case 16: P1.Process_Control="16";			                 MODBUS_SEND_S(P1.Process_Control);		           break;
		case 17: P1.Velocity_Curve="17";			                 MODBUS_SEND_S(P1.Velocity_Curve);	             break;	
		case 18: P1.Stroke_Segment="18";			                 MODBUS_SEND_S(P1.Stroke_Segment);	             break;	
		case 19: P1.External_Analog="19";			                 MODBUS_SEND_S(P1.External_Analog);	             break;
		case 20: P1.Split_Functionality="20";		               MODBUS_SEND_S(P1.Split_Functionality);	         break;
		default:   MODBUS_SEND(0);            break;
    break;		
	}	
}
///--------------------------------------------------P1_READ---------------------------------------///


///--------------------------------------------------P2_READ---------------------------------------///
void MODBUS_READ_P2()
{
	
	    switch (Read_buf_modbus[4])
	 {
		case 1:  P2.Label="1";	                        MODBUS_SEND_S(P2.Label);                 break;
		case 2:	 P2.Close_Direction=2;	                MODBUS_SEND(P2.Close_Direction);         break;
		case 3:  P2.Gearbox_Model=2;	                  MODBUS_SEND(P2.Gearbox_Model);           break;
		case 4:  P2.Type=2;		                          MODBUS_SEND(P2.Type);                    break;
		case 5:	 P2.Reduction_Ratio="2";                MODBUS_SEND_S(P2.Reduction_Ratio);       break;
		case 6:  P2.Moment_Amplifier="3";               MODBUS_SEND_S(P2.Moment_Amplifier);      break;
		case 7:	 P2.Output_Torque_MAX="4";	            MODBUS_SEND_S(P2.Output_Torque_MAX);     break;
		case 8:	 P2.Input_Rev_MAX="5";                  MODBUS_SEND_S(P2.Input_Rev_MAX);         break;
		case 9:  P2.Travel="6";	                        MODBUS_SEND_S(P2.Travel);                break;
		case 10: P2.Signal_Gear_Set="7";		            MODBUS_SEND_S(P2.Signal_Gear_Set);       break;
		case 11: P2.Close_Speed=2;				              MODBUS_SEND(P2.Close_Speed);             break;
		case 12: P2.Open_Speed=2;				                MODBUS_SEND(P2.Open_Speed);              break;
		case 13: P2.Exigency_Close_Speed=2;				      MODBUS_SEND(P2.Exigency_Close_Speed);    break;
		case 14: P2.Exigency_Open_Speed=2;				      MODBUS_SEND(P2.Exigency_Open_Speed);     break;
		case 15: P2.Moment_Close=2;					            MODBUS_SEND(P2.Moment_Close);            break;
		case 16: P2.Moment_Open=2;					            MODBUS_SEND(P2.Moment_Open);             break;
		case 17: P2.Close_Tip_Range="8";		            MODBUS_SEND_S(P2.Close_Tip_Range);       break;
		case 18: P2.Open_Tip_Range="9";		              MODBUS_SEND_S(P2.Open_Tip_Range);        break;
		case 19: P2.Close_Modle=2;					            MODBUS_SEND(P2.Close_Modle);             break;
		case 20: P2.Open_Modle=2;					              MODBUS_SEND(P2.Open_Modle);              break;
		default:   MODBUS_SEND(0);            break;
		 break;
	 }		 

}
///--------------------------------------------------P2_READ---------------------------------------///

///--------------------------------------------------P3_READ---------------------------------------///
void MODBUS_READ_P3()
{
	  switch(Read_buf_modbus[4])
	{
		case 1:  P3.Label="1";	                     MODBUS_SEND_S(P3.Label);                 break;
		case 2:  P3.Input_on_off=2;                  MODBUS_SEND(P3.Input_on_off);           break;
		case 3:	 P3.Input_Exigency=2;                MODBUS_SEND(P3.Input_Exigency);         break;
		case 4:	 P3.Input_Modle=2;	                 MODBUS_SEND(P3.Input_Modle);            break;
		case 5:	 P3.Type_Remote_Control=2;           MODBUS_SEND(P3.Type_Remote_Control);    break;
		case 6:	 P3.Remote_Rechoose=2;	             MODBUS_SEND(P3.Remote_Rechoose);        break;
		case 7:  P3.AI1_Range=2;                     MODBUS_SEND(P3.AI1_Range);              break;
		case 8:	 P3.AI1_Slope=2;                     MODBUS_SEND(P3.AI1_Slope);              break;
		case 9:	 P3.AI2_Range=2;	                   MODBUS_SEND(P3.AI2_Range);              break;
		case 10:	 P3.AI2_Slope=2;                     MODBUS_SEND(P3.AI2_Slope);              break;
		case 11: P3.Floor_Level="2";                 MODBUS_SEND_S(P3.Floor_Level);          break;
		case 12: P3.Upper_Level="3";	               MODBUS_SEND_S(P3.Upper_Level);          break;
		case 13: P3.DCS=2;	                         MODBUS_SEND(P3.DCS);                    break;
		case 14: P3.Actual_Position=2;	             MODBUS_SEND(P3.Actual_Position);        break;
		case 15: P3.Output_1=2;	                     MODBUS_SEND(P3.Output_1);               break;
		case 16: P3.Output_2=2;	                     MODBUS_SEND(P3.Output_2);               break;
		case 17: P3.Output_3=2;	                     MODBUS_SEND(P3.Output_3);               break;
		case 18: P3.Output_4=2;	                     MODBUS_SEND(P3.Output_4);               break;
		case 19: P3.Output_5=2;	                     MODBUS_SEND(P3.Output_5);               break;
		case 20: P3.Output_6=2;	                     MODBUS_SEND(P3.Output_6);               break;
		case 21: P3.Output_7=2;	                     MODBUS_SEND(P3.Output_7);               break;
		case 22: P3.Output_8=2;	                     MODBUS_SEND(P3.Output_8);               break;
		case 23: P3.State_1=2;	                     MODBUS_SEND(P3.State_1);                break;
		case 24: P3.State_2=2;	                     MODBUS_SEND(P3.State_2);                break;
		case 25: P3.State_3=2;	                     MODBUS_SEND(P3.State_3);                break;
		case 26: P3.State_4=2;	                     MODBUS_SEND(P3.State_4);                break;	
		case 27: P3.State_5=2;	                     MODBUS_SEND(P3.State_5);                break;
		case 28: P3.State_6=2;	                     MODBUS_SEND(P3.State_6);                break;
		case 29: P3.State_7=2;		                   MODBUS_SEND(P3.State_7);                break;
		case 30: P3.State_8=2;		                   MODBUS_SEND(P3.State_8);                break;
		case 31: P3.AO1_Output=2;		                 MODBUS_SEND(P3.AO1_Output);             break;
		case 32: P3.AO1_Range=2;		                 MODBUS_SEND(P3.AO1_Range);              break;
		case 33: P3.AO1_Slope=2;	                   MODBUS_SEND(P3.AO1_Slope);              break;
		case 34: P3.AO2_Output=2;	                   MODBUS_SEND(P3.AO2_Output);             break;
		case 35: P3.AO2_Range=2;	                   MODBUS_SEND(P3.AO2_Range);              break;
		case 36: P3.AO2_Slope=2;	                   MODBUS_SEND(P3.AO2_Slope);              break;
		case 37: P3.Middle_Close="4";	               MODBUS_SEND_S(P3.Middle_Close);         break;
		case 38: P3.Middle_Open="5";		             MODBUS_SEND_S(P3.Middle_Open);          break;
	  default:   MODBUS_SEND(0);            break;	
		break;
	}
}
///--------------------------------------------------P3_READ---------------------------------------///

///--------------------------------------------------P4_READ---------------------------------------///
void MODBUS_READ_P4()
{
		switch(Read_buf_modbus[4])
 {
	 case 1:	P4.Label="1";                          MODBUS_SEND_S(P4.Label);                 break;
	 case 2:	P4.Motor_T_Warn="2";                   MODBUS_SEND_S(P4.Motor_T_Warn);          break;
	 case 3:	P4.Motor_P_Heater="3";                 MODBUS_SEND_S(P4.Motor_P_Heater);        break;
	 case 4:	P4.Motor_Heater=2;                     MODBUS_SEND(P4.Motor_Heater);            break;
	 case 5:	P4.Remote_Control_E=2;                 MODBUS_SEND(P4.Remote_Control_E);        break;
	 case 6:	P4.Urgency_Location="4";               MODBUS_SEND_S(P4.Urgency_Location);      break;
	 case 7:	P4.Fasten=2;                           MODBUS_SEND(P4.Fasten);                  break;
	 case 8:	P4.Retries_Cnt=2;                      MODBUS_SEND(P4.Retries_Cnt);             break;
	 case 9:	P4.Switch_Cnt="5";                     MODBUS_SEND_S(P4.Switch_Cnt);            break;
	 case 10:	P4.Close_Cnt="6";                      MODBUS_SEND_S(P4.Close_Cnt);             break;
	 case 11:	P4.Motor_Operation="7";                MODBUS_SEND_S(P4.Motor_Operation);	      break;
	 default:   MODBUS_SEND(0);            break;
	break;
 }

}
///--------------------------------------------------P4_READ---------------------------------------///

///--------------------------------------------------P5_READ---------------------------------------///
void MODBUS_READ_P5()
{
	   switch(Read_buf_modbus[4])
 {
	case 1:   P5.Label="1254";                   MODBUS_SEND_S(P5.Label);                break;
	case 2:   P5.Language=3;                  MODBUS_SEND(P5.Language);                break;
	case 3:		P5.NVRotate=1;                  MODBUS_SEND(P5.NVRotate);                break;
	case 4:		P5.Screen_Standby=5;            MODBUS_SEND(P5.Screen_Standby);          break;
	case 5:   P5.Standby_Time="1";            MODBUS_SEND_S(P5.Standby_Time);          break;
  case 6:		P5.Brake_DC="2";                MODBUS_SEND_S(P5.Brake_DC);              break;
  case 7:		P5.UP_Time="3";                 MODBUS_SEND_S(P5.UP_Time);               break;
  case 8:		P5.Dead_Band_Min="4";           MODBUS_SEND_S(P5.Dead_Band_Min);         break;
  case 9:		P5.Dead_Band_Max="5";           MODBUS_SEND_S(P5.Dead_Band_Max);         break;
  case 10:	P5.P_C_Time=1;                  MODBUS_SEND(P5.P_C_Time);                break;
  case 11:	P5.Default_Close="6";           MODBUS_SEND_S(P5.Default_Close);         break;
  case 12:	P5.Default_Open="7";            MODBUS_SEND_S(P5.Default_Open);          break;
  case 13:	P5.User_Defined_Close="8";      MODBUS_SEND_S(P5.User_Defined_Close);    break;
  case 14:	P5.User_Defined_Open="9";       MODBUS_SEND_S(P5.User_Defined_Open);     break;	
  case 15:  P5.Delay_Time="10";             MODBUS_SEND_S(P5.Delay_Time);            break;
  case 16:	P5.Installation_Component="11"; MODBUS_SEND_S(P5.Installation_Component);break;
  case 17:	P5.Terminal_RPM=3;              MODBUS_SEND(P5.Terminal_RPM);            break;
  case 18:	P5.Receipt_Time="12";           MODBUS_SEND_S(P5.Receipt_Time);          break;
  case 19:	P5.User_Function_Code="13";     MODBUS_SEND_S(P5.User_Function_Code);    break;
  case 20:	P5.Parameter_1="14";            MODBUS_SEND_S(P5.Parameter_1);           break;
  case 21:	P5.Parameter_2="15";            MODBUS_SEND_S(P5.Parameter_2);           break;
  case 22:	P5.Parameter_3="16";            MODBUS_SEND_S(P5.Parameter_3);           break;
  case 23:	P5.Parameter_4="17";            MODBUS_SEND_S(P5.Parameter_4);           break;
  case 24:	P5.Limiting_Voltage_DC=2;       MODBUS_SEND(P5.Limiting_Voltage_DC);     break;
  case 25:  P5.Run_Time=2;                  MODBUS_SEND(P5.Run_Time);                break;
  case 26:  P5.Bluetooth=2;                 MODBUS_SEND(P5.Bluetooth);               break;
  case 27:  P5.Torque_Flange=4;             MODBUS_SEND(P5.Torque_Flange);	         break;
	default:   MODBUS_SEND(0);            break;
	break;
 }



}


///--------------------------------------------------P5_READ---------------------------------------///

///--------------------------------------------------P6_READ---------------------------------------///
void MODBUS_READ_P6()
{
   switch(Read_buf_modbus[4])
 {
	 case 1:  P6.KP_Controller="2";              MODBUS_SEND_S(P6.KP_Controller);              break;
	 case 2:  P6.KI_Time="3";                    MODBUS_SEND_S(P6.KI_Time);                    break;
	 case 3:	P6.Fixed_Value="4";                MODBUS_SEND_S(P6.Fixed_Value);                break;
	 case 4:  P6.Site_1="5";                     MODBUS_SEND_S(P6.Site_1);                     break;
	 case 5:  P6.Site_2="6";                     MODBUS_SEND_S(P6.Site_2);                     break;
	 case 6:  P6.Electricity_1="7";              MODBUS_SEND_S(P6.Electricity_1);              break;
	 case 7:  P6.Electricity_2="8";              MODBUS_SEND_S(P6.Electricity_2);              break;
	 case 8: 	P6.Local_Operating_Speed_1=2;      MODBUS_SEND(P6.Local_Operating_Speed_1);      break;
	 case 9:  P6.Remote_Control_Speed_1=2;       MODBUS_SEND(P6.Remote_Control_Speed_1);       break;
	 case 10: P6.Input_speed=2;                  MODBUS_SEND(P6.Input_speed);                  break;
	 case 11: P6.Start_0="9";	                   MODBUS_SEND_S(P6.Start_0);                    break;
	 case 12: P6.Start_1="10";                   MODBUS_SEND_S(P6.Start_1);                    break;
	 case 13: P6.Start_2="11";                   MODBUS_SEND_S(P6.Start_2);                    break;
	 case 14:	P6.Start_3="12";	                 MODBUS_SEND_S(P6.Start_3);                    break;
	 case 15: P6.Start_4="13";                   MODBUS_SEND_S(P6.Start_4);                    break;
	 case 16: P6.Start_5="14";                   MODBUS_SEND_S(P6.Start_5);                    break;
	 case 17:	P6.Start_6="15";                   MODBUS_SEND_S(P6.Start_6);                    break;
	 case 18:	P6.Start_7="16";                   MODBUS_SEND_S(P6.Start_7);                    break;
	 case 19: P6.Start_8="17";                   MODBUS_SEND_S(P6.Start_8);                    break;
   case 20:	P6.Start_9="18";                   MODBUS_SEND_S(P6.Start_9);                    break;
   case 21:	P6.Start_10="19";                  MODBUS_SEND_S(P6.Start_10);                   break;
   case 22:	P6.Preset_Time_0="20";             MODBUS_SEND_S(P6.Preset_Time_0);              break;
   case 23:	P6.Preset_Time_1="21";             MODBUS_SEND_S(P6.Preset_Time_1);              break;
   case 24:	P6.Preset_Time_2="22";             MODBUS_SEND_S(P6.Preset_Time_2);              break;
   case 25:	P6.Preset_Time_3="23";             MODBUS_SEND_S(P6.Preset_Time_3);              break;
   case 26:	P6.Preset_Time_4="24";             MODBUS_SEND_S(P6.Preset_Time_4);              break;
   case 27:	P6.Preset_Time_5="25";             MODBUS_SEND_S(P6.Preset_Time_5);              break;
   case 28:	P6.Preset_Time_6="26";	           MODBUS_SEND_S(P6.Preset_Time_6);              break;
   case 29:	P6.Preset_Time_7="27";             MODBUS_SEND_S(P6.Preset_Time_7);              break;
   case 30: P6.Preset_Time_8="28";             MODBUS_SEND_S(P6.Preset_Time_8);              break;
   case 31:	P6.Preset_Time_9="29";             MODBUS_SEND_S(P6.Preset_Time_9);	             break;
   case 32:	P6.Preset_Time_10="30";            MODBUS_SEND_S(P6.Preset_Time_10);             break;
   case 33:	P6.Total_Time_1="31";	             MODBUS_SEND_S(P6.Total_Time_1);               break;
   case 34:	P6.Total_Time_2="32";              MODBUS_SEND_S(P6.Total_Time_2);               break;
   case 35:	P6.Total_Time_3="33";              MODBUS_SEND_S(P6.Total_Time_3);               break;
   case 36:	P6.Total_Time_4="34";	             MODBUS_SEND_S(P6.Total_Time_4);               break;
   case 37:	P6.Total_Time_5="35";              MODBUS_SEND_S(P6.Total_Time_5);               break;
   case 38:	P6.Total_Time_6="36";              MODBUS_SEND_S(P6.Total_Time_6);               break;
   case 39:	P6.Total_Time_7="37";              MODBUS_SEND_S(P6.Total_Time_7);               break;
   case 40:	P6.Total_Time_8="38";              MODBUS_SEND_S(P6.Total_Time_8);               break;
   case 41:	P6.Total_Time_9="39";              MODBUS_SEND_S(P6.Total_Time_9);               break;
   case 42:	P6.Total_Time_10="40";	           MODBUS_SEND_S(P6.Total_Time_10);              break;
   case 43: P6.Local_Operating_Speed_2=1;      MODBUS_SEND(P6.Local_Operating_Speed_2);      break;
   case 44: P6.Remote_Control_Speed_2=1;	     MODBUS_SEND(P6.Remote_Control_Speed_2);       break;
   case 45:	P6.Emergency_Speed=1;	             MODBUS_SEND(P6.Emergency_Speed);              break;
   case 46: P6.Emergency_Curve="41";           MODBUS_SEND_S(P6.Emergency_Curve);            break;
   case 47: P6.Positioning_Time=1;             MODBUS_SEND(P6.Positioning_Time);             break;
   case 48:	P6.Velocity_Curve_1="42";          MODBUS_SEND_S(P6.Velocity_Curve_1);           break;
   case 49:	P6.Velocity_Curve_2="43";	         MODBUS_SEND_S(P6.Velocity_Curve_2);           break;
   case 50: P6.Velocity_Curve_3="44";          MODBUS_SEND_S(P6.Velocity_Curve_3);           break;
   case 51: P6.Velocity_Curve_4="45";          MODBUS_SEND_S(P6.Velocity_Curve_4);           break;
   case 52: P6.Velocity_Curve_5="46";          MODBUS_SEND_S(P6.Velocity_Curve_5);           break;
   case 53: P6.Velocity_Curve_6="47";          MODBUS_SEND_S(P6.Velocity_Curve_6);           break;
   case 54: P6.Velocity_Curve_7="48";          MODBUS_SEND_S(P6.Velocity_Curve_7);           break;
   case 55:	P6.Velocity_Curve_8="49";	         MODBUS_SEND_S(P6.Velocity_Curve_8);           break;
   case 56: P6.Velocity_Curve_9="50";          MODBUS_SEND_S(P6.Velocity_Curve_9);           break;
   case 57: P6.Velocity_Curve_10="51";	       MODBUS_SEND_S(P6.Velocity_Curve_10);          break;
   case 58: P6.Outputspeed_1=1;                MODBUS_SEND(P6.Outputspeed_1);                break;
   case 59: P6.Outputspeed_2=1;                MODBUS_SEND(P6.Outputspeed_2);                break;
   case 60: P6.Outputspeed_3=1;                MODBUS_SEND(P6.Outputspeed_3);                break;
	 case 61:	P6.Outputspeed_4=1;                MODBUS_SEND(P6.Outputspeed_4);                break;
	 case 62:	P6.Outputspeed_5=1;                MODBUS_SEND(P6.Outputspeed_5);                break;
	 case 63:	P6.Outputspeed_6=1;                MODBUS_SEND(P6.Outputspeed_6);                break;
	 case 64:	P6.Outputspeed_7=1;                MODBUS_SEND(P6.Outputspeed_7);                break;
	 case 65:	P6.Outputspeed_8=1;	               MODBUS_SEND(P6.Outputspeed_8);                break;
	 case 66:	P6.Outputspeed_9=1;                MODBUS_SEND(P6.Outputspeed_9);                break;
	 case 67:	P6.Outputspeed_10=1;               MODBUS_SEND(P6.Outputspeed_10);               break;
	 case 68: P6.Local_Operating_Speed_3=1;      MODBUS_SEND(P6.Local_Operating_Speed_3);      break;
	 case 69:	P6.Remote_Control_Speed_3=1;       MODBUS_SEND(P6.Remote_Control_Speed_3);	     break; 
	 default:   MODBUS_SEND(0);            break;
	break;
 }
}




///--------------------------------------------------P6_READ---------------------------------------///

///--------------------------------------------------P7_READ---------------------------------------///
void MODBUS_READ_P7()
{
		switch(Read_buf_modbus[4])
	{
		case 1:	P7.Data_1="1";	MODBUS_SEND_S(P7.Data_1);   break;
		case 2:	P7.Data_2="2";  MODBUS_SEND_S(P7.Data_2);   break;
		case 3:	P7.Data_3="3";	MODBUS_SEND_S(P7.Data_3);   break;
		case 4:	P7.Colour=1;    MODBUS_SEND(P7.Colour);     break;
		default:   MODBUS_SEND(0);            break;
		break;
	}
}

///--------------------------------------------------P7_READ---------------------------------------///

///--------------------------------------------------P8_READ---------------------------------------///
void MODBUS_READ_P8()
{
	switch(Read_buf_modbus[4])
	{
		case 1:	  P8.Control_Mode="1";	             MODBUS_SEND_S(P8.Control_Mode);                      break;
		case 2:	  P8.Control_Command="2";	           MODBUS_SEND_S(P8.Control_Command);                   break;
		case 3:	  P8.Actual_Speed="3";	             MODBUS_SEND_S(P8.Actual_Speed);                      break;
		case 4:	  P8.Cutoff="4";	                   MODBUS_SEND_S(P8.Cutoff);                            break;
		case 5:	  P8.Indirect_points_Close="5";	     MODBUS_SEND_S(P8.Indirect_points_Close);             break;
		case 6:	  P8.Indirect_points_Open="6";	     MODBUS_SEND_S(P8.Indirect_points_Open);              break;
		case 7:	  P8.Misdeed="7";	                   MODBUS_SEND_S(P8.Misdeed);                           break;
		case 8:	  P8.Given_Value="8";	               MODBUS_SEND_S(P8.Given_Value);                       break;
		case 9:	  P8.Actual_Value="9";	             MODBUS_SEND_S(P8.Actual_Value);                      break;
		case 10:	P8.Actual_Process_Value="10";	     MODBUS_SEND_S(P8.Actual_Process_Value);              break;
		case 11:	P8.Motor_Temperature="11";	       MODBUS_SEND_S(P8.Motor_Temperature);                 break;
		case 12:	P8.Temperature_Alarm="12";	       MODBUS_SEND_S(P8.Temperature_Alarm);                 break;
		case 13:	P8.Bus_Voltage_DC="13";	           MODBUS_SEND_S(P8.Bus_Voltage_DC);                    break;
		case 14:	P8.Motor_Current="14";	           MODBUS_SEND_S(P8.Motor_Current);                     break;
		case 15:	P8.AI1="15";	                     MODBUS_SEND_S(P8.AI1);                               break;
		case 16:	P8.Close="16";	                   MODBUS_SEND_S(P8.Close);                             break;
		case 17:	P8.Open="17";	                     MODBUS_SEND_S(P8.Open);                              break;
		case 18:	P8.Stop="18";	                     MODBUS_SEND_S(P8.Stop);                              break;
		case 19:	P8.Urgency="19";	                 MODBUS_SEND_S(P8.Urgency);                           break;
		case 20:	P8.Mode="20";	                     MODBUS_SEND_S(P8.Mode);                              break;
		case 21:	P8.Current_Value="21";	           MODBUS_SEND_S(P8.Current_Value);                     break;
		case 22:	P8.Offset="22";	                   MODBUS_SEND_S(P8.Offset);                            break;
		default:   MODBUS_SEND(0);            break;
		 break; 
	}
}

///--------------------------------------------------P8_READ---------------------------------------///

///--------------------------------------------------P9_READ---------------------------------------///
void MODBUS_READ_P9()
{
	switch(Read_buf_modbus[4])
	{
		case 1:	    P9.Label="xxx";	                       MODBUS_SEND_S(P9.Label);                      break;
		case 2:	    P9.Open_Cnt_1="1";	                 MODBUS_SEND_S(P9.Open_Cnt_1);                      break;
		case 3:	    P9.Open_Frequency_1="2";	           MODBUS_SEND_S(P9.Open_Frequency_1);                break;
		case 4:	    P9.Torque_Close_Cnt="3";	           MODBUS_SEND_S(P9.Torque_Close_Cnt);                break;
		case 5:	    P9.Journey_Close_Cnt="4";	           MODBUS_SEND_S(P9.Journey_Close_Cnt);               break;
		case 6:	    P9.Moto_Runtimes_1="5";	             MODBUS_SEND_S(P9.Moto_Runtimes_1);                 break;
		case 7:	    P9.Circuit_Wafer_Runtimes="6";	     MODBUS_SEND_S(P9.Circuit_Wafer_Runtimes);          break;
		case 8:	    P9.Operating_Frequency="7";	         MODBUS_SEND_S(P9.Operating_Frequency);             break;
		case 9:	    P9.Open_Cnt_2="8";	                 MODBUS_SEND_S(P9.Open_Cnt_2);                      break;
		case 10:	  P9.Open_Frequency_2="9";	           MODBUS_SEND_S(P9.Open_Frequency_2);                break;
		case 11:	  P9.Moto_Runtimes_2="10";	           MODBUS_SEND_S(P9.Moto_Runtimes_2);                 break;
		case 12:	  P9.Maintenance_valve="11";	         MODBUS_SEND_S(P9.Maintenance_valve);               break;
		default:   MODBUS_SEND(0);            break;
		 break; 
	}
}
///--------------------------------------------------P9_READ---------------------------------------///

///--------------------------------------------------PA_READ---------------------------------------///
void MODBUS_READ_PA()
{
	switch(Read_buf_modbus[4])
	{
		case 1:  PA.MODBUS_Address_1="1";	                 MODBUS_SEND_S(PA.MODBUS_Address_1);                      break;
		case 2:	 PA.MODBUS_Address_2="2";	                 MODBUS_SEND_S(PA.MODBUS_Address_2);                      break;
		case 3:	 PA.Baud_Rate_1=1;	                       MODBUS_SEND(PA.Baud_Rate_1);                             break;
		case 4:	 PA.Baud_Rate_2=1;	                       MODBUS_SEND(PA.Baud_Rate_2);                             break; 
		case 5:	 PA.Check_Code_1=1;	                       MODBUS_SEND(PA.Check_Code_1);                            break;
		case 6:	 PA.Check_Code_2=1;	                       MODBUS_SEND(PA.Check_Code_2);                            break; 
		case 7:  PA.Monitoring_Time_1="3";	               MODBUS_SEND_S(PA.Monitoring_Time_1);                     break;
		case 8:	 PA.Monitoring_Time_2="4";	               MODBUS_SEND_S(PA.Monitoring_Time_2);                     break;
		case 9:  PA.PROFIBUS_Address_1="5";	               MODBUS_SEND_S(PA.PROFIBUS_Address_1);                    break;
		case 10: PA.PROFIBUS_Address_2="6";	               MODBUS_SEND_S(PA.PROFIBUS_Address_2);                    break;
		case 11: PA.PZD3=1;	                               MODBUS_SEND(PA.PZD3);                                    break;
		case 12: PA.PZD4=1;	                               MODBUS_SEND(PA.PZD4);                                    break; 
		case 13: PA.PZD5=1;	                               MODBUS_SEND(PA.PZD5);                                    break;
		case 14: PA.PZD6=1;	                               MODBUS_SEND(PA.PZD6);                                    break; 
		case 15: PA.HART_Address="7";	                     MODBUS_SEND_S(PA.HART_Address);                          break;
		case 16: PA.HART_Time="8";	                       MODBUS_SEND_S(PA.HART_Time);                             break;
		case 17: PA.Bus_Work_Channel="9";	                 MODBUS_SEND_S(PA.Bus_Work_Channel);                      break;
		case 18: PA.Bus_Channel_1="10";	                   MODBUS_SEND_S(PA.Bus_Channel_1);                         break;
		case 19: PA.Bus_Channel_1_Status="11";	           MODBUS_SEND_S(PA.Bus_Channel_1_Status);                  break;
		case 20: PA.Bus_Channel_2="12";	                   MODBUS_SEND_S(PA.Bus_Channel_2);                         break;
		case 21: PA.Bus_Channel_2_Status="13";	           MODBUS_SEND_S(PA.Bus_Channel_2_Status);                  break;
		case 22: PA.CTC_Type="14";	                       MODBUS_SEND_S(PA.CTC_Type);                              break;
		case 23: PA.CTC_Status_1="15";	                   MODBUS_SEND_S(PA.CTC_Status_1);                          break;
		case 24: PA.CTC_Status_2="16";	                   MODBUS_SEND_S(PA.CTC_Status_2);                          break;
		case 25: PA.Keep_Output_Time="17";	               MODBUS_SEND_S(PA.Keep_Output_Time);                      break;
		case 26: PA.TS_Status_1="18";	                     MODBUS_SEND_S(PA.TS_Status_1);                           break;
		case 27: PA.TS_Status_2="19";	                     MODBUS_SEND_S(PA.TS_Status_2);                           break;
		case 28: PA.Timestamp=1;	                         MODBUS_SEND(PA.Timestamp);                               break;
		default:   MODBUS_SEND(0);            break;
	  break; 
	}
}


///--------------------------------------------------PA_READ---------------------------------------///

///--------------------------------------------------PB_READ---------------------------------------///
void MODBUS_READ_PB()
{
	switch(Read_buf_modbus[4])
	{
		case 2:  PB.Tab_Control_1=1;	                         MODBUS_SEND(PB.Tab_Control_1);                            break;
		case 3:  PB.Tab_Control_2=1;	                         MODBUS_SEND(PB.Tab_Control_2);                            break;
    case 4:  PB.Tab_Control_3=1;	                         MODBUS_SEND(PB.Tab_Control_3);                            break;
		case 5:  PB.Tab_Control_4=1;	                         MODBUS_SEND(PB.Tab_Control_4);                            break;
		case 6:  PB.Tab_Control_5=1;	                         MODBUS_SEND(PB.Tab_Control_5);                            break;
		case 7:  PB.Trouble1="1";	                             MODBUS_SEND_S(PB.Trouble1);                               break;
		case 8:  PB.Trouble2="2";		                           MODBUS_SEND_S(PB.Trouble2);                               break;
    case 9:  PB.Trouble3="3";		                           MODBUS_SEND_S(PB.Trouble3);                               break;
		//case 10: PB.Trouble4="4";		                           MODBUS_SEND_S(PB.Trouble4);                               break;
		//case 11: PB.Trouble5="5";	                             MODBUS_SEND_S(PB.Trouble5);                               break;
		default:             break;
		break;
	}
}	
///--------------------------------------------------PB_READ---------------------------------------///








///----------------------------------Write------------------///
char BIT_BUFF()
{
	char sum;
	char len=0;
	len=Read_buf_modbus[5]<<8|Read_buf_modbus[6];
	for( i=0;i<len;i++)
	{
		sum=Read_buf_modbus[i+7];
	}
  return sum;
}		

char* MODBUS_READ_STR()
{
	char str[50];
	char *sum;
	char len=0;
  len=Read_buf_modbus[5];
	for( i=0;i<len;i++)
	{
		str[i]=Read_buf_modbus[i+7];
	}
	sum=str;
	return sum;
}
///--------------------------------------------------P1_WRITE---------------------------------------///
void MODBUS_WRITE_P1()
{
	switch (Read_buf_modbus[4])
	{
		case 1:	 P1.Label=BUFF;		                 break;
		case 2:	 P1.Pro_Name=BUFF;	               break;
		case 3:	 P1.Dat=BUFF;                      break;
		case 4:	 P1.Time=BUFF;                     break;
		case 5:	 P1.Version_Nb=BUFF;               break;
		case 6:	 P1.Source=BUFF;		               break;
		case 7:	 P1.Modle_Nb=BUFF;			           break;
		case 8:	 P1.Sequence_Nb=BUFF;			         break;
		case 9:	 P1.First_Sequence_Nb=BUFF;		     break;
		case 10: P1.Gear_Ratio=BUFF;		           break;	
		case 11: P1.Explain=BUFF;			             break;
		case 12: P1.Type=BUFF;					           break;	
		case 13: P1.Quality_Gu=BUFF;			         break;		
		case 14: P1.Firmware_Version=BUFF;			   break;		
		case 15: P1.Position_Control=BUFF;			   break;
		case 16: P1.Process_Control=BUFF;			     break;
		case 17: P1.Velocity_Curve=BUFF;				   break;	
		case 18: P1.Stroke_Segment=BUFF;				   break;	
		case 19: P1.External_Analog=BUFF;				   break;
		case 20: P1.Split_Functionality=BUFF;			 break;
		default:              break;
    break;		
	}	
}
///--------------------------------------------------P1_WRITE---------------------------------------///


///--------------------------------------------------P2_WRITE---------------------------------------///
void MODBUS_WRITE_P2()
{
	
	    switch (Read_buf_modbus[4])
	 {
		case 1:  P2.Label=BUFF;	                        break;
		case 2:	 P2.Close_Direction=BIT_BUFF();	          break;
		case 3:  P2.Gearbox_Model=BIT_BUFF();	            break;
		case 4:  P2.Type=BIT_BUFF();		                  break;
		case 5:	 P2.Reduction_Ratio=BUFF;               break;
		case 6:  P2.Moment_Amplifier=BUFF;              break;
		case 7:	 P2.Output_Torque_MAX=BUFF;	            break;
		case 8:	 P2.Input_Rev_MAX=BUFF;                 break;
		case 9:  P2.Travel=BUFF;	                      break;
		case 10: P2.Signal_Gear_Set=BUFF;		            break;
		case 11: P2.Close_Speed=BIT_BUFF();				        break;
		case 12: P2.Open_Speed=BIT_BUFF();				        break;
		case 13: P2.Exigency_Close_Speed=BIT_BUFF();			break;
		case 14: P2.Exigency_Open_Speed=BIT_BUFF();				break;
		case 15: P2.Moment_Close=BIT_BUFF();					    break;
		case 16: P2.Moment_Open=BIT_BUFF();					      break;
		case 17: P2.Close_Tip_Range=BUFF;		            break;
		case 18: P2.Open_Tip_Range=BUFF;		            break;
		case 19: P2.Close_Modle=BIT_BUFF();					      break;
		case 20: P2.Open_Modle=BIT_BUFF();					      break;
		 	 default:              break;
		 break;
	 }		 

}
///--------------------------------------------------P2_WRITE---------------------------------------///

///--------------------------------------------------P3_WRITE---------------------------------------///
void MODBUS_WRITE_P3()
{
	  switch(Read_buf_modbus[4])
	{
		case 1:  P3.Input_on_off=BIT_BUFF();                break;
		case 2:	 P3.Input_Exigency=BIT_BUFF();              break;
		case 3:	 P3.Input_Modle=BIT_BUFF();	                break;
		case 4:	 P3.Type_Remote_Control=BIT_BUFF();         break;
		case 5:	 P3.Remote_Rechoose=BIT_BUFF();	            break;
		case 6:  P3.AI1_Range=BIT_BUFF();                   break;
		case 7:	 P3.AI1_Slope=BIT_BUFF();                   break;
		case 8:	 P3.AI2_Range=BIT_BUFF();	                  break;
		case 9:	 P3.AI2_Slope=BIT_BUFF();                   break;
		case 10: P3.Floor_Level=BUFF;                       break;
		case 11: P3.Upper_Level=BUFF;	                      break;
		case 12: P3.DCS=BIT_BUFF();	                        break;
		case 13: P3.Actual_Position=BIT_BUFF();	            break;
		case 14: P3.Output_1=BIT_BUFF();	                  break;
		case 15: P3.Output_2=BIT_BUFF();	                  break;
		case 16: P3.Output_3=BIT_BUFF();	                  break;
		case 17: P3.Output_4=BIT_BUFF();	                  break;
		case 18: P3.Output_5=BIT_BUFF();	                  break;
		case 19: P3.Output_6=BIT_BUFF();	                  break;
		case 20: P3.Output_7=BIT_BUFF();	                  break;
		case 21: P3.Output_8=BIT_BUFF();	                  break;
		case 22: P3.State_1=BIT_BUFF();	                    break;
		case 23: P3.State_2=BIT_BUFF();	                    break;
		case 24: P3.State_3=BIT_BUFF();	                    break;
		case 25: P3.State_4=BIT_BUFF();	                    break;	
		case 26: P3.State_5=BIT_BUFF();	                    break;
		case 27: P3.State_6=BIT_BUFF();	                    break;
		case 28: P3.State_7=BIT_BUFF();		                  break;
		case 29: P3.State_8=BIT_BUFF();		                  break;
		case 30: P3.AO1_Output=BIT_BUFF();		              break;
		case 31: P3.AO1_Range=BIT_BUFF();		                break;
		case 32: P3.AO1_Slope=BIT_BUFF();	                  break;
		case 33: P3.AO2_Output=BIT_BUFF();	                break;
		case 34: P3.AO2_Range=BIT_BUFF();	                  break;
		case 35: P3.AO2_Slope=BIT_BUFF();	                  break;
		case 36: P3.Middle_Close=BUFF;	                    break;
		case 37: P3.Middle_Open=BUFF;		                    break;
	 default:              break;		
		break;
	}
}
///--------------------------------------------------P3_WRITE---------------------------------------///

///--------------------------------------------------P4_WRITE---------------------------------------///
void MODBUS_WRITE_P4()
{
		switch(Read_buf_modbus[4])
 {
	 case 1:	P4.Label=BUFF;                           break;
	 case 2:	P4.Motor_T_Warn=BUFF;                    break;
	 case 3:	P4.Motor_P_Heater=BUFF;                  break;
	 case 4:	P4.Motor_Heater=BIT_BUFF();              break;
	 case 5:	P4.Remote_Control_E=BIT_BUFF();          break;
	 case 6:	P4.Urgency_Location=BUFF;                break;
	 case 7:	P4.Fasten=BIT_BUFF();                    break;
	 case 8:	P4.Retries_Cnt=BIT_BUFF();               break;
	 case 9:	P4.Switch_Cnt=BUFF;                      break;
	 case 10:	P4.Close_Cnt=BUFF;                       break;
	 case 11:	P4.Motor_Operation=BUFF;                 break;
	 	 default:              break;
	break;
 }

}
///--------------------------------------------------P4_WRITE---------------------------------------///

///--------------------------------------------------P5_WRITE---------------------------------------///
void MODBUS_WRITE_P5()
{
	   switch(Read_buf_modbus[4])
 {
	case 1:   P5.Language=BIT_BUFF();                break;
	case 2:		P5.NVRotate=BIT_BUFF();                break;
	case 3:		P5.Screen_Standby=BIT_BUFF();          break;
	case 4:   P5.Standby_Time=BUFF;                break;
  case 5:		P5.Brake_DC=BUFF;                    break;
  case 6:		P5.UP_Time=BUFF;                     break;
  case 7:		P5.Dead_Band_Min=BUFF;               break;
  case 8:		P5.Dead_Band_Max=BUFF;               break;
  case 9:		P5.P_C_Time=BIT_BUFF();                break;
  case 10:	P5.Default_Close=BUFF;               break;
  case 11:	P5.Default_Open=BUFF;                break;
  case 12:	P5.User_Defined_Close=BUFF;          break;
  case 13:	P5.User_Defined_Open=BUFF;           break;	
  case 14:  P5.Delay_Time=BUFF;                  break;
  case 15:	P5.Installation_Component=BUFF;      break;
  case 16:	P5.Terminal_RPM=BIT_BUFF();            break;
  case 17:	P5.Receipt_Time=BUFF;                break;
  case 18:	P5.User_Function_Code=BUFF;          break;
  case 19:	P5.Parameter_1=BUFF;                 break;
  case 20:	P5.Parameter_2=BUFF;                 break;
  case 21:	P5.Parameter_3=BUFF;                 break;
  case 22:	P5.Parameter_4=BUFF;                 break;
  case 23:	P5.Limiting_Voltage_DC=BIT_BUFF();     break;
  case 24:  P5.Run_Time=BIT_BUFF();                break;
  case 25:  P5.Bluetooth=BIT_BUFF();               break;
  case 26:  P5.Torque_Flange=BIT_BUFF();           break;
		 default:              break;
	break;
 }



}


///--------------------------------------------------P5_WRITE---------------------------------------///

///--------------------------------------------------P6_WRITE---------------------------------------///
void MODBUS_WRITE_P6()
{
   switch(Read_buf_modbus[4])
 {
	 case 1:  P6.KP_Controller=BUFF;                        break;
	 case 2:  P6.KI_Time=BUFF;                              break;
	 case 3:	P6.Fixed_Value=BUFF;                          break;
	 case 4:  P6.Site_1=BUFF;                               break;
	 case 5:  P6.Site_2=BUFF;                               break;
	 case 6:  P6.Electricity_1=BUFF;                        break;
	 case 7:  P6.Electricity_2=BUFF;                        break;
	 case 8: 	P6.Local_Operating_Speed_1=BIT_BUFF();          break;
	 case 9:  P6.Remote_Control_Speed_1=BIT_BUFF();           break;
	 case 10: P6.Input_speed=BIT_BUFF();                      break;
	 case 11: P6.Start_0=BUFF;	                            break;
	 case 12: P6.Start_1=BUFF;                              break;
	 case 13: P6.Start_2=BUFF;                              break;
	 case 14:	P6.Start_3=BUFF;	                            break;
	 case 15: P6.Start_4=BUFF;                              break;
	 case 16: P6.Start_5=BUFF;                              break;
	 case 17:	P6.Start_6=BUFF;                              break;
	 case 18:	P6.Start_7=BUFF;                              break;
	 case 19: P6.Start_8=BUFF;                              break;
   case 20:	P6.Start_9=BUFF;                              break;
   case 21:	P6.Start_10=BUFF;                             break;
   case 22:	P6.Preset_Time_0=BUFF;                        break;
   case 23:	P6.Preset_Time_1=BUFF;                        break;
   case 24:	P6.Preset_Time_2=BUFF;                        break;
   case 25:	P6.Preset_Time_3=BUFF;                        break;
   case 26:	P6.Preset_Time_4=BUFF;                        break;
   case 27:	P6.Preset_Time_5=BUFF;                        break;
   case 28:	P6.Preset_Time_6=BUFF;	                      break;
   case 29:	P6.Preset_Time_7=BUFF;                        break;
   case 30: P6.Preset_Time_8=BUFF;                        break;
   case 31:	P6.Preset_Time_9=BUFF;          	            break;
   case 32:	P6.Preset_Time_10=BUFF;                       break;
   case 33:	P6.Total_Time_1=BUFF;	                        break;
   case 34:	P6.Total_Time_2=BUFF;                         break;
   case 35:	P6.Total_Time_3=BUFF;                         break;
   case 36:	P6.Total_Time_4=BUFF;	                        break;
   case 37:	P6.Total_Time_5=BUFF;                         break;
   case 38:	P6.Total_Time_6=BUFF;                         break;
   case 39:	P6.Total_Time_7=BUFF;                         break;
   case 40:	P6.Total_Time_8=BUFF;                         break;
   case 41:	P6.Total_Time_9=BUFF;                         break;
   case 42:	P6.Total_Time_10=BUFF;	                      break;
   case 43: P6.Local_Operating_Speed_2=BIT_BUFF();          break;
   case 44: P6.Remote_Control_Speed_2=BIT_BUFF();	          break;
   case 45:	P6.Emergency_Speed=BIT_BUFF();	                break;
   case 46: P6.Emergency_Curve=BUFF;                      break;
   case 47: P6.Positioning_Time=BIT_BUFF();                 break;
   case 48:	P6.Velocity_Curve_1=BUFF;                     break;
   case 49:	P6.Velocity_Curve_2=BUFF;	                    break;
   case 50: P6.Velocity_Curve_3=BUFF;                     break;
   case 51: P6.Velocity_Curve_4=BUFF;                     break;
   case 52: P6.Velocity_Curve_5=BUFF;                     break;
   case 53: P6.Velocity_Curve_6=BUFF;                     break;
   case 54: P6.Velocity_Curve_7=BUFF;                     break;
   case 55:	P6.Velocity_Curve_8=BUFF;	                    break;
   case 56: P6.Velocity_Curve_9=BUFF;                     break;
   case 57: P6.Velocity_Curve_10=BUFF;	                  break;
   case 58: P6.Outputspeed_1=BIT_BUFF();                    break;
   case 59: P6.Outputspeed_2=BIT_BUFF();                    break;
   case 60: P6.Outputspeed_3=BIT_BUFF();                    break;
	 case 61:	P6.Outputspeed_4=BIT_BUFF();                    break;
	 case 62:	P6.Outputspeed_5=BIT_BUFF();                    break;
	 case 63:	P6.Outputspeed_6=BIT_BUFF();                    break;
	 case 64:	P6.Outputspeed_7=BIT_BUFF();                    break;
	 case 65:	P6.Outputspeed_8=BIT_BUFF();	                  break;
	 case 66:	P6.Outputspeed_9=BIT_BUFF();                    break;
	 case 67:	P6.Outputspeed_10=BIT_BUFF();                   break;
	 case 68: P6.Local_Operating_Speed_3=BIT_BUFF();          break;
	 case 69:	P6.Remote_Control_Speed_3=BIT_BUFF();      	    break; 
	 	 default:              break;
	break;
 }
}




///--------------------------------------------------P6_WRITE---------------------------------------///

///--------------------------------------------------P7_WRITE---------------------------------------///
void MODBUS_WRITE_P7()
{
		switch(Read_buf_modbus[4])
	{
		case 1:	P7.Data_1=BUFF;	         break;
		case 2:	P7.Data_2=BUFF;          break;
		case 3:	P7.Data_3=BUFF;	         break;
		case 4:	P7.Colour=BIT_BUFF();      break;
			 default:              break;
		break;
	}
}

///--------------------------------------------------P7_WRITE---------------------------------------///

///--------------------------------------------------P8_WRITE---------------------------------------///
void MODBUS_WRITE_P8()
{
	switch(Read_buf_modbus[4])
	{
		case 1:	  P8.Control_Mode=BUFF;	                         break;
		case 2:	  P8.Control_Command=BUFF;	                     break;
		case 3:	  P8.Actual_Speed=BUFF;	                         break;
		case 4:	  P8.Cutoff=BUFF;	                               break;
		case 5:	  P8.Indirect_points_Close=BUFF;	               break;
		case 6:	  P8.Indirect_points_Open=BUFF;	                 break;
		case 7:	  P8.Misdeed=BUFF;	                             break;
		case 8:	  P8.Given_Value=BUFF;	                         break;
		case 9:	  P8.Actual_Value=BUFF;	                         break;
		case 10:	P8.Actual_Process_Value=BUFF;	                 break;
		case 11:	P8.Motor_Temperature=BUFF;	                   break;
		case 12:	P8.Temperature_Alarm=BUFF;	                   break;
		case 13:	P8.Bus_Voltage_DC=BUFF;	                       break;
		case 14:	P8.Motor_Current=BUFF;	                       break;
		case 15:	P8.AI1=BUFF;	                                 break;
		case 16:	P8.Close=BUFF;	                               break;
		case 17:	P8.Open=BUFF;	                                 break;
		case 18:	P8.Stop=BUFF;	                                 break;
		case 19:	P8.Urgency=BUFF;	                             break;
		case 20:	P8.Mode=BUFF;	                                 break;
		case 21:	P8.Current_Value=BUFF;	                       break;
		case 22:	P8.Offset=BUFF;	                               break;
			 default:              break;
		 break; 
	}
}

///--------------------------------------------------P8_WRITE---------------------------------------///

///--------------------------------------------------P9_WRITE---------------------------------------///
void MODBUS_WRITE_P9()
{
	switch(Read_buf_modbus[4])
	{
		case 1:	    P9.Open_Cnt_1=BUFF;	                          break;
		case 2:	    P9.Open_Frequency_1=BUFF;	                    break;
		case 3:	    P9.Torque_Close_Cnt=BUFF;	                    break;
		case 4:	    P9.Journey_Close_Cnt=BUFF;	                  break;
		case 5:	    P9.Moto_Runtimes_1=BUFF;	                    break;
		case 6:	    P9.Circuit_Wafer_Runtimes=BUFF;	              break;
		case 7:	    P9.Operating_Frequency=BUFF;	                break;
		case 8:	    P9.Open_Cnt_2=BUFF;	                          break;
		case 9:	    P9.Open_Frequency_2=BUFF;	                    break;
		case 10:	  P9.Moto_Runtimes_2=BUFF;	                    break;
		case 11:	  P9.Maintenance_valve=BUFF;	                  break;
			 default:              break;
		 break; 
	}
}
///--------------------------------------------------P9_WRITE---------------------------------------///

///--------------------------------------------------PA_WRITE---------------------------------------///
void MODBUS_WRITE_PA()
{
	switch(Read_buf_modbus[4])
	{
		case 1:  PA.MODBUS_Address_1=BUFF;	                    break;
		case 2:	 PA.MODBUS_Address_2=BUFF;	                    break;
		case 3:	 PA.Baud_Rate_1=BIT_BUFF();	                      break;
		case 4:	 PA.Baud_Rate_2=BIT_BUFF();	                      break; 
		case 5:	 PA.Check_Code_1=BIT_BUFF();	                    break;
		case 6:	 PA.Check_Code_2=BIT_BUFF();	                    break; 
		case 7:  PA.Monitoring_Time_1=BUFF;	                    break;
		case 8:	 PA.Monitoring_Time_2=BUFF;	                    break;
		case 9:  PA.PROFIBUS_Address_1=BUFF;	                  break;
		case 10: PA.PROFIBUS_Address_2=BUFF;	                  break;
		case 11: PA.PZD3=BIT_BUFF();	                            break;
		case 12: PA.PZD4=BIT_BUFF();	                            break; 
		case 13: PA.PZD5=BIT_BUFF();	                            break;
		case 14: PA.PZD6=BIT_BUFF();	                            break; 
		case 15: PA.HART_Address=BUFF;	                        break;
		case 16: PA.HART_Time=BUFF;	                            break;
		case 17: PA.Bus_Work_Channel=BUFF;	                    break;
		case 18: PA.Bus_Channel_1=BUFF;	                        break;
		case 19: PA.Bus_Channel_1_Status=BUFF;	                break;
		case 20: PA.Bus_Channel_2=BUFF;	                        break;
		case 21: PA.Bus_Channel_2_Status=BUFF;	                break;
		case 22: PA.CTC_Type=BUFF;	                            break;
		case 23: PA.CTC_Status_1=BUFF;	                        break;
		case 24: PA.CTC_Status_2=BUFF;	                        break;
		case 25: PA.Keep_Output_Time=BUFF;	                    break;
		case 26: PA.TS_Status_1=BUFF;	                          break;
		case 27: PA.TS_Status_2=BUFF;	                          break;
		case 28: PA.Timestamp=BIT_BUFF();	                        break;
		default:              break;
	  break; 
	}
}


///--------------------------------------------------PA_WRITE---------------------------------------///

///--------------------------------------------------PB_WRITE---------------------------------------///
void MODBUS_WRITE_PB()
{
	switch(Read_buf_modbus[4])
	{
		case 2:  PB.Tab_Control_1=BIT_BUFF();	                    break;
		case 3:  PB.Tab_Control_2=BIT_BUFF();	                    break;
    case 4:  PB.Tab_Control_3=BIT_BUFF();	                    break;
		case 5:  PB.Tab_Control_4=BIT_BUFF();	                    break;
		case 6:  PB.Tab_Control_5=BIT_BUFF();	                    break;
		case 7:  PB.Trouble1=BUFF;	                            break;
		case 8:  PB.Trouble2=BUFF;		                          break;
    case 9:  PB.Trouble3=BUFF;		                          break;
		case 10: PB.Trouble4=BUFF;		                          break;
		case 11: PB.Trouble5=BUFF;	                            break;
			 default:              break;
		break;
	}
}	
///--------------------------------------------------PB_READ---------------------------------------///
void MODBUS_READ()
{
	if(Read_buf_modbus[2]==0x01)   //读操作
	{
		switch(Read_buf_modbus[3])
		{
			case 1:	  MODBUS_READ_P1();break;
			case 2:	  MODBUS_READ_P2();break;
			case 3:	  MODBUS_READ_P3();break;
			case 4:	  MODBUS_READ_P4();break;
			case 5:	  MODBUS_READ_P5();break;
			case 6:	  MODBUS_READ_P6();break;
			case 7:	  MODBUS_READ_P7();break;
			case 8:	  MODBUS_READ_P8();break;
			case 9:	  MODBUS_READ_P9();break;
			case 10:	MODBUS_READ_PA();break;
			case 11:	MODBUS_READ_PB();break;
			default:              break;
			break;
		}
		if(Read_buf_modbus[3]==10&&Read_buf_modbus[4]==0x5d)
		{                 }//按键总线-PC轮询
		if(Read_buf_modbus[3]==8&&Read_buf_modbus[4]==0x5b)
		{                 }//控制加监控-PC轮询
		if(Read_buf_modbus[3]==8&&Read_buf_modbus[4]==0x5c)
		{                 }//控制加监控-PC操作关
		if(Read_buf_modbus[3]==8&&Read_buf_modbus[4]==0x5d)
		{                 }//控制加监控-PC操作开
		if(Read_buf_modbus[3]==8&&Read_buf_modbus[4]==0x5e)
		{                 }//控制加监控-PC操作停
		if(Read_buf_modbus[3]==8&&Read_buf_modbus[4]==0x5f)
		{                 }//控制加监控-PC操作紧急
		if(Read_buf_modbus[3]==8&&Read_buf_modbus[4]==0x60)
		{                 }//控制加监控-PC操作PC就地控制
		if(Read_buf_modbus[3]==9&&Read_buf_modbus[4]==0x5b)
		{                 }//诊断-PC复位维护
		if(Read_buf_modbus[3]==11&&Read_buf_modbus[4]==0x5c)
		{                 }//设备的状态-故障复位
		if(Read_buf_modbus[3]==11&&Read_buf_modbus[4]==0x5d)
		{                 }//设备的状态-轮询
  }
	if(Read_buf_modbus[2]==0x10)   //写操作
	{
		BUFF=MODBUS_READ_STR();
		switch(Read_buf_modbus[3])
		{
			case 1:	  MODBUS_WRITE_P1();break;
			case 2:	  MODBUS_WRITE_P2();break;
			case 3:	  MODBUS_WRITE_P3();break;
			case 4:	  MODBUS_WRITE_P4();break;
			case 5:	  MODBUS_WRITE_P5();break;
			case 6:	  MODBUS_WRITE_P6();break;
			case 7:	  MODBUS_WRITE_P7();break;
			case 8:	  MODBUS_WRITE_P8();break;
			case 9:	  MODBUS_WRITE_P9();break;
			case 10:	MODBUS_WRITE_PA();break;
			case 11:	MODBUS_WRITE_PB();break;
			default:              break;
			break;
		}
	}
	
	
		for( i=0;i<Read_cnt;i++)
			Read_buf_modbus[i]=0;
		Read_cnt=0;
}





void MODBUS_SEND_S(char *dat)
{
	  int len=0;
		Send_buf_modbus[0]=0x01;
		Send_buf_modbus[1]=0xAA;
		Send_buf_modbus[2]=0x01;
		Send_buf_modbus[3]=Read_buf_modbus[3];
		Send_buf_modbus[4]=Read_buf_modbus[4];
    len=Send_BUF(dat);
	  USB_WriteEP (0x82, (unsigned char *)&Send_buf_modbus[0], len);
}


void MODBUS_SEND(char dat)
{
	  int len=0;
		Send_buf_modbus[0]=0x01;
		Send_buf_modbus[1]=0xAA;
		Send_buf_modbus[2]=0x01;
		Send_buf_modbus[3]=Read_buf_modbus[3];
		Send_buf_modbus[4]=Read_buf_modbus[4];
    Send_buf_modbus[5]=dat;
	 USB_WriteEP (0x82, (unsigned char *)&Send_buf_modbus[0], 6);
}

