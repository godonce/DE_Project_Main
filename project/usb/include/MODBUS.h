#ifndef __MODBUS_H__
#define __MODBUS_H__
#include "lpc_types.h"

typedef struct   
{
	char *Label;                        //ִ�л�����ǩ��
	char *Pro_Name;                     //��Ŀ����
	char *Dat;                          //����
	char *Time;                         //ʱ��
	char *Version_Nb;                   //�汾                    
	char *Source;                      //��Դ
	char *Modle_Nb;                     //�ͺ�
	char *Sequence_Nb;                  //���к�
	char *First_Sequence_Nb;            //ԭʼ���к�
	char *Gear_Ratio;                   //�źų��ֵ�Ԫ�ı��ʵ��趨
	char *Explain;                      //˵��
	char *Type;                         //����
	char *Quality_Gu;                   //����ʱ�
	char *Firmware_Version;             //�̼��汾
	char *Position_Control;             //λ�ÿ���
	char *Process_Control;              //���̿���
	char *Velocity_Curve;               //�ٶ����߹���
	char *Stroke_Segment;               //�г̷ֶ�
	char *External_Analog;              //�ⲿģ�����
	char *Split_Functionality;          //������ָ���
}p1;
p1 P1;


typedef struct   
{
	char *Label;                        //ִ�л�����ǩ��
	char Close_Direction;               //�ط��� 1˳ʱ�� 2��ʱ��
	char Gearbox_Model;                 //1-û�и��ӵĳ�����  2-���ת������  3-���ֻ�ת������  4-���Ե�Ԫ
	char Type;                          //����  1-�û��Զ���  2-*LF12.1
	char *Reduction_Ratio;              //���ٱ�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
  char *Moment_Amplifier;             //���طŴ�ϵ��     
	char *Output_Torque_MAX;            //����������     
	char *Input_Rev_MAX;                //�������ת��  
	char *Travel;                       //�г�    
	char *Signal_Gear_Set;              //�źų�������      
  char  Close_Speed;	                //���ٶ�  5  7 10 14 20 28 40
	char  Open_Speed;	                  //���ٶ�  5  7 10 14 20 28 40
	char  Exigency_Close_Speed;	        //�������ٶ�  5  7 10 14 20 28 40
	char  Exigency_Open_Speed;	        //�������ٶ�  5  7 10 14 20 28 40
	char  Moment_Close;	                //������  9 12 15 18 21 24 27 30
	char  Moment_Open;	                //������  9 12 15 18 21 24 27 30
	char *Close_Tip_Range;              //��ĩ��λ�÷�Χ  
	char *Open_Tip_Range;               //��ĩ��λ�÷�Χ
	char  Close_Modle;                  //��ģʽ   1-�г̹ض�  2-���عض�
	char  Open_Modle;                   //��ģʽ   1-�г̹ض�  2-���عض�
}p2;
p2 P2;

typedef struct   
{
	char *Label;                        //ִ�л�����ǩ��
	char Input_on_off;                  //����������  1-����  2-����
	char Input_Exigency;                //��������    1-����  2-����
	char Input_Modle;                   //ģʽ����    1-�޹���  2-�л������͵�/Զ��  3-���е綯����  4-���о͵ز���
  char Type_Remote_Control;           //Զ�˿������� 1-�������������ӵ����  2-������������ӵ����
	char Remote_Rechoose;               //Զ����ѡ��   1-��������
	char AI1_Range;                     //��Χ1   1-0~20MA  2-4~20MA
	char AI1_Slope;                     //б��1   1-����    2-�½�
	char AI2_Range;                     //��Χ2   1-��
	char AI2_Slope;                     //б��2   1-��
	char *Floor_Level;                  //����
  char *Upper_Level;                  //����
	char  DCS;                          //DCS����ֵ  1 -��
 	char  Actual_Position ;             //ʵ��λ��ֵ 1-ʵ��ֵ=λ��
  char  Output_1 ;                    //���1    1-δ��  2-������ĩ��λ�� 3-�ط���ĩ��λ�� 4-�ط���������عض� 5-������������عض� 6-�ػ򿪷���������عض� 7-����  8-��˸ 9-׼���� 10-׼����+Զ�� 11-�͵� 12-���м�ӵ� 13-���м�ӵ� 14-������ȹ��� 15-����¶ȱ��� 16-ά�� 17-�ط������� 18-����������  19-����ָʾ������/�رա�  20-��˸+ȫ��λ�� 21-��˸+ȫ��λ�� 22-�ط���ﵽ�г�ĩ��λ�� 23-������ﵽ�г�ĩ��λ��
	char  Output_2 ;                    //���2    1-δ��  2-������ĩ��λ�� 3-�ط���ĩ��λ�� 4-�ط���������عض� 5-������������عض� 6-�ػ򿪷���������عض� 7-����  8-��˸ 9-׼���� 10-׼����+Զ�� 11-�͵� 12-���м�ӵ� 13-���м�ӵ� 14-������ȹ��� 15-����¶ȱ��� 16-ά�� 17-�ط������� 18-����������  19-����ָʾ������/�رա�  20-��˸+ȫ��λ�� 21-��˸+ȫ��λ�� 22-�ط���ﵽ�г�ĩ��λ�� 23-������ﵽ�г�ĩ��λ��
	char  Output_3 ;                    //���3    1-δ��  2-������ĩ��λ�� 3-�ط���ĩ��λ�� 4-�ط���������عض� 5-������������عض� 6-�ػ򿪷���������عض� 7-����  8-��˸ 9-׼���� 10-׼����+Զ�� 11-�͵� 12-���м�ӵ� 13-���м�ӵ� 14-������ȹ��� 15-����¶ȱ��� 16-ά�� 17-�ط������� 18-����������  19-����ָʾ������/�رա�  20-��˸+ȫ��λ�� 21-��˸+ȫ��λ�� 22-�ط���ﵽ�г�ĩ��λ�� 23-������ﵽ�г�ĩ��λ��
	char  Output_4 ;                    //���4    1-δ��  2-������ĩ��λ�� 3-�ط���ĩ��λ�� 4-�ط���������عض� 5-������������عض� 6-�ػ򿪷���������عض� 7-����  8-��˸ 9-׼���� 10-׼����+Զ�� 11-�͵� 12-���м�ӵ� 13-���м�ӵ� 14-������ȹ��� 15-����¶ȱ��� 16-ά�� 17-�ط������� 18-����������  19-����ָʾ������/�رա�  20-��˸+ȫ��λ�� 21-��˸+ȫ��λ�� 22-�ط���ﵽ�г�ĩ��λ�� 23-������ﵽ�г�ĩ��λ��
	char  Output_5 ;                    //���5    1-δ��  2-������ĩ��λ�� 3-�ط���ĩ��λ�� 4-�ط���������عض� 5-������������عض� 6-�ػ򿪷���������عض� 7-����  8-��˸ 9-׼���� 10-׼����+Զ�� 11-�͵� 12-���м�ӵ� 13-���м�ӵ� 14-������ȹ��� 15-����¶ȱ��� 16-ά�� 17-�ط������� 18-����������  19-����ָʾ������/�رա�  20-��˸+ȫ��λ�� 21-��˸+ȫ��λ�� 22-�ط���ﵽ�г�ĩ��λ�� 23-������ﵽ�г�ĩ��λ��
  char  Output_6 ;                    //���6    1-δ��  2-������ĩ��λ�� 3-�ط���ĩ��λ�� 4-�ط���������عض� 5-������������عض� 6-�ػ򿪷���������عض� 7-����  8-��˸ 9-׼���� 10-׼����+Զ�� 11-�͵� 12-���м�ӵ� 13-���м�ӵ� 14-������ȹ��� 15-����¶ȱ��� 16-ά�� 17-�ط������� 18-����������  19-����ָʾ������/�رա�  20-��˸+ȫ��λ�� 21-��˸+ȫ��λ�� 22-�ط���ﵽ�г�ĩ��λ�� 23-������ﵽ�г�ĩ��λ��
	char  Output_7 ;                    //���7    1-δ��  2-������ĩ��λ�� 3-�ط���ĩ��λ�� 4-�ط���������عض� 5-������������عض� 6-�ػ򿪷���������عض� 7-����  8-��˸ 9-׼���� 10-׼����+Զ�� 11-�͵� 12-���м�ӵ� 13-���м�ӵ� 14-������ȹ��� 15-����¶ȱ��� 16-ά�� 17-�ط������� 18-����������  19-����ָʾ������/�رա�  20-��˸+ȫ��λ�� 21-��˸+ȫ��λ�� 22-�ط���ﵽ�г�ĩ��λ�� 23-������ﵽ�г�ĩ��λ��
	char  Output_8 ;                    //���8    1-δ��  2-������ĩ��λ�� 3-�ط���ĩ��λ�� 4-�ط���������عض� 5-������������عض� 6-�ػ򿪷���������عض� 7-����  8-��˸ 9-׼���� 10-׼����+Զ�� 11-�͵� 12-���м�ӵ� 13-���м�ӵ� 14-������ȹ��� 15-����¶ȱ��� 16-ά�� 17-�ط������� 18-����������  19-����ָʾ������/�رա�  20-��˸+ȫ��λ�� 21-��˸+ȫ��λ�� 22-�ط���ﵽ�г�ĩ��λ�� 23-������ﵽ�г�ĩ��λ��
	char  State_1 ;                     //״ֵ̬1  1-����  2-����
	char  State_2 ;                     //״ֵ̬2  1-����  2-����
	char  State_3 ;                     //״ֵ̬3  1-����  2-����
	char  State_4 ;                     //״ֵ̬4  1-����  2-����
	char  State_5 ;                     //״ֵ̬5  1-����  2-����
	char  State_6 ;                     //״ֵ̬6  1-����  2-����
	char  State_7 ;                     //״ֵ̬7  1-����  2-����
	char  State_8 ;                     //״ֵ̬8  1-����  2-����
	char  AO1_Output;                   //AO1���ֵ   1-ʵ��λ��ֵ
	char  AO1_Range;                    //A01 ��Χ1   1-0~20MA  2-4~20MA
	char  AO1_Slope;                    //A01б��1   1-����    2-�½�
  char  AO2_Output;                   //AO2���ֵ   1-��
	char  AO2_Range;                    //A02 ��Χ1   1-��
	char  AO2_Slope;                    //A02б��1   1-��
	char *Middle_Close;                 //���м�λ��
  char *Middle_Open;                  //���м�λ��
}p3;
p3 P3;



typedef struct   
{
	char *Label;                        //ִ�л�����ǩ��
	char *Motor_T_Warn;                 //��������¶� 
	char *Motor_P_Heater;               //������ȱ���
  char Motor_Heater;                  //������� 1-��  2-��
	char Remote_Control_E;              //Զ���ͺŹ��� 1-����ԭλ  2-���е���������λ��  3-ִ�����һ��ָ��
	char *Urgency_Location;             //����λ��
  char Fasten ;                       //�ؽ� 1-��  2-��
	char Retries_Cnt ;                  //�����ع��Ϻ�����Դ��� 0 1 2 3 4 5
	char *Switch_Cnt;                   //���ش��� 	
	char *Close_Cnt;                    //���عضϴ��� 	
	char *Motor_Operation;              //������� 	
}p4;
p4 P4;

typedef struct   
{
	char *Label; 
	char Language;                      //��ʾ����   1-���� 2-���� 3-�������� 4-������� 5-������ 6-�ݿ��� 7-����� 8-������ 9-�������� 10-������ 11-���� 12-Ӣ�� 13-���� 14-������ 15-�������� 16-���������� 17-�������� 18-˹�工���� 19-ϣ���� 20-������ 21-���� 22-������ 23-���������� 24-ӡ���� 25-������ 26-���޵��� 27-Ų���� 28-˹���������� 29-�������� 30-̩����                                              
	char NVRotate;                      //��ʾ����ʾ����  1-0 2-90 3-180  
	char Screen_Standby ;               //������Ļ   1-��׼ 2-λ�� 3-λ��+��� 4-λ��+������+״̬ 5-�����л����͵�    
  char *Standby_Time;                 //����ʱ�� 
	char *Brake_DC;                     //ֱ���ƶ�
	char *UP_Time;                      //����ʱ��
  char *Dead_Band_Min ;               //������С
	char *Dead_Band_Max ;               //�������
	char  P_C_Time;                     //�������Ƶ�ʱ�� 	1-�Լ�
	char *Default_Close;                //Ĭ�Ϲ� 	
	char *Default_Open;                 //Ĭ�Ͽ� 	
	char *User_Defined_Close;           //�û��Զ����   // 67997292
	char *User_Defined_Open;	          //�û��Զ��忪
	char *Delay_Time;	                  //��ʱʱ��
	char *Installation_Component;       //��װ���
	char Terminal_RPM;                  //�ն�ת��    1-����  2-�������� 3-��������/ֹͣ
	char *Receipt_Time;                 //����ʱ��
	char *User_Function_Code;           //�û����ܴ���
	char *Parameter_1;                  //����1
	char *Parameter_2;                  //����2
	char *Parameter_3;                  //����3
	char *Parameter_4;                  //����4
	char Limiting_Voltage_DC;           //����ֱ����ѹ  1-��  2-��
	char Run_Time;                      //����ֱ����ѹ  1-��  2-��
  char Bluetooth;                     //����  1-��  2-��
  char Torque_Flange;                 //Ť�ز�������  1-������  2-ģ�������AI1 3-120Nm��10.1��2SX7100-6A��  4-500Nm��14.5��2SX7100-6B�� 5-1000Nm��16.1��2SX7100-6C��
}p5;
p5 P5;


typedef struct   
{ 
	char *Label;                        //ִ�л�����ǩ��
	char *KP_Controller;                //����������
	char *KI_Time ;                     //����ʱ�䳣��
  char *Fixed_Value;                  //�̶�����ֵ 
  char *Site_1;                       //λ��1
  char *Site_2;                       //λ��2 
	char *Electricity_1;                //����ֵ1
  char *Electricity_2;                //����ֵ2
	char  Local_Operating_Speed_1;        //�͵ز����ٶ�  1-����"��/��"�ٶ�
	char  Remote_Control_Speed_1;         //Զ���ٶ�  1-��"�����ٶ�"����
	char  Input_speed;                  //�����ٶ�  1--ģ��������1(AI1)
	char *Start_0;                       //��ʼ0 
	char *Start_1;                       //��ʼ1 
	char *Start_2;                       //��ʼ2 
	char *Start_3;                       //��ʼ3 
	char *Start_4;                       //��ʼ4 
	char *Start_5;                       //��ʼ5 
	char *Start_6;                       //��ʼ6 
	char *Start_7;                       //��ʼ7 
	char *Start_8;                       //��ʼ8 
	char *Start_9;                       //��ʼ9 
	char *Start_10;                      //��ʼ10
	char *Preset_Time_0;                 //��λʱ��0
	char *Preset_Time_1;                 //��λʱ��1
	char *Preset_Time_2;                 //��λʱ��2
	char *Preset_Time_3;                 //��λʱ��3
	char *Preset_Time_4;                 //��λʱ��4
	char *Preset_Time_5;                 //��λʱ��5
	char *Preset_Time_6;                 //��λʱ��6
	char *Preset_Time_7;                 //��λʱ��7
	char *Preset_Time_8;                 //��λʱ��8
	char *Preset_Time_9;                 //��λʱ��9
	char *Preset_Time_10;                //��λʱ��10
	char *Total_Time_1;                  //�ܵĶ�λʱ��1
  char *Total_Time_2;                  //�ܵĶ�λʱ��2
	char *Total_Time_3;                  //�ܵĶ�λʱ��3
	char *Total_Time_4;                  //�ܵĶ�λʱ��4
	char *Total_Time_5;                  //�ܵĶ�λʱ��5
	char *Total_Time_6;                  //�ܵĶ�λʱ��6
	char *Total_Time_7;                  //�ܵĶ�λʱ��7
	char *Total_Time_8;                  //�ܵĶ�λʱ��8
	char *Total_Time_9;                  //�ܵĶ�λʱ��9
	char *Total_Time_10;                 //�ܵĶ�λʱ��10
  char  Local_Operating_Speed_2;       //�͵ز����ٶ�2   1-�ɶ�λʱ�����߾���
	char  Remote_Control_Speed_2;        //Զ���ٶ�   1-�ɶ�λʱ�����߾���
	char  Emergency_Speed;               //�����ٶ�   1-������/���ٶ�
	char *Emergency_Curve;               //��������ϵ��
	char  Positioning_Time;               //ִ�л�����λʱ��
	char *Velocity_Curve_1;               //�����ٶ�1
	char *Velocity_Curve_2;               //�����ٶ�2
	char *Velocity_Curve_3;               //�����ٶ�3
	char *Velocity_Curve_4;               //�����ٶ�4
	char *Velocity_Curve_5;               //�����ٶ�5
	char *Velocity_Curve_6;               //�����ٶ�6
	char *Velocity_Curve_7;               //�����ٶ�7
	char *Velocity_Curve_8;               //�����ٶ�8
	char *Velocity_Curve_9;               //�����ٶ�9
	char *Velocity_Curve_10;              //�����ٶ�10
	char  Outputspeed_1;                  //���ת��1  1-5
	char  Outputspeed_2;                  //���ת��2  1-5
	char  Outputspeed_3;                  //���ת��3  1-5
	char  Outputspeed_4;                  //���ת��4  1-5
	char  Outputspeed_5;                  //���ת��5  1-5
	char  Outputspeed_6;                  //���ת��6  1-5
	char  Outputspeed_7;                  //���ת��7  1-5
	char  Outputspeed_8;                  //���ת��8  1-5
	char  Outputspeed_9;                  //���ת��9  1-5
	char  Outputspeed_10;                 //���ת��10 1-5
	char  Local_Operating_Speed_3;        //�͵ز��ٶ�   1-����"��/��"�ٶ�
	char  Remote_Control_Speed_3;         //Զ���ٶ�     1-��"����"����
}p6;
p6 P6;



typedef struct   
{ 
	char *Data_1;              //����1
	char *Data_2;              //����2
	char *Data_3;              //����3
	char  Colour;              //��ɫ
}p7;
p7 P7;


typedef struct   
{ 
	char *Control_Mode;                          //��ǰ���Ʒ�ʽ
	char *Control_Command;                       //��������
	char *Actual_Speed;                          //ʵ��ת��/����ʱ��
	char *Cutoff ;                               //�ض�
	char *Indirect_points_Close ;                //���м�ӵ�
	char *Indirect_points_Open ;                 //���м�ӵ�
	char *Misdeed ;                              //������Ϊ
	char *Given_Value ;                          //����ֵλ��
	char *Actual_Value ;                         //ʵ��ֵλ��
	char *Actual_Process_Value ;                 //����ʵ��ֵ
	char *Motor_Temperature ;                    //����¶�
	char *Temperature_Alarm ;                    //������ȱ���
	char *Bus_Voltage_DC ;                       //ֱ��ĸ�ߵ�ѹ
	char *Motor_Current ;                        //�������
	char *AI1 ;                                  //AI1
	char *Close ;                                //��������-��
	char *Open ;                                 //��������-��
	char *Stop ;                                 //��������-ͣ
	char *Urgency ;                              //��������-����
	char *Mode ;                                 //��������-ģʽ
	char *Current_Value ;                        //��ǰ��ֵ
	char *Offset ;                               //ƫ��
}p8;
p8 P8;

typedef struct   
{ 
	char *Label;                                //ִ�л�����ǩ��
	char *Open_Cnt_1;                          //���ش���
	char *Open_Frequency_1;                    //����Ƶ��
  char *Torque_Close_Cnt;                  //���عضϴ���
	char *Journey_Close_Cnt;                 //�г̹ضϴ���
	char *Moto_Runtimes_1;                     //�������Сʱ
	char *Circuit_Wafer_Runtimes;            //���Ӱ幤��Сʱ��
	char *Operating_Frequency;               //����Ƶ��
	char *Open_Cnt_2;                          //���ش���
  char *Open_Frequency_2;                    //����Ƶ��
	char *Moto_Runtimes_2;                     //�������Сʱ
	char *Maintenance_valve;                    //����ά��
}p9;
p9 P9;


typedef struct   
{
	
	char *MODBUS_Address_1;                          // MODBUS��ַ1
	char *MODBUS_Address_2;                          // MODBUS��ַ2
  char  Baud_Rate_1;                               // ������1       1-19200
	char  Baud_Rate_2;                               // ������2       1-19200
	char  Check_Code_1;                              // ��żУ��1     1-żУ�飬1ֹͣ
	char  Check_Code_2;                              // ��żУ��2     1-żУ�飬1ֹͣ
	char *Monitoring_Time_1;                         // ���ʱ��1
	char *Monitoring_Time_2;                         // ���ʱ��2
	char *PROFIBUS_Address_1;                        // PROFIBUS��ַ1
	char *PROFIBUS_Address_2;                        // PROFIBUS��ַ2
	char  PZD3;                                      //  PZD3   1-״̬��2��ZSW2��
	char  PZD4;                                      //  PZD4   1-�����ź�1
	char  PZD5;                                      //  PZD5   1-�����ź�2
	char  PZD6;                                      //  PZD6   1-ʵ�ʿ��Ʒ�ʽ
	char *HART_Address;                              //  HART��ַ
	char *HART_Time;                                 //  HART����ʱ��
	char *Bus_Work_Channel;                          //  ���߹���ͨ��
	char *Bus_Channel_1;                             //  ����ͨ��1
	char *Bus_Channel_1_Status;                      //  ����ͨ��1 ״̬
	char *Bus_Channel_2;                             //  ����ͨ��2
	char *Bus_Channel_2_Status;                      //  ����ͨ��2 ״̬
	char *CTC_Type;                                  //  ��������
	char *CTC_Status_1;                              //  ����״̬1
	char *CTC_Status_2;                              //  ����״̬2
	char *Keep_Output_Time;                          //  �������ʱ��
	char *TS_Status_1;                               //  TS״̬1
	char *TS_Status_2;                               //  TS״̬2
	char  Timestamp;                                 //  ʱ���
}pA;
pA PA;


typedef struct   
{ 
	char Tab_Control_1;                          // MODBUS��ַ1
	char Tab_Control_2;                          //ѡ�2
	char Tab_Control_3;                          //ѡ�3
	char Tab_Control_4;                          //ѡ�4
	char Tab_Control_5;                          //ѡ�5
	char *Trouble1;                              //��ǰ����1
	char *Trouble2;                              //��ǰ����2
	char *Trouble3;                              //��ǰ����3
	char *Trouble4;                              //��ǰ����4
	char *Trouble5;                              //��ǰ����5
}pB;
pB PB;



void MODBUS_SEND_0420(unsigned short dat);
#endif

