#ifndef __MODBUS_H__
#define __MODBUS_H__
#include "lpc_types.h"

typedef struct   
{
	char *Label;                        //执行机构标签号
	char *Pro_Name;                     //项目名称
	char *Dat;                          //日期
	char *Time;                         //时间
	char *Version_Nb;                   //版本                    
	char *Source;                      //来源
	char *Modle_Nb;                     //型号
	char *Sequence_Nb;                  //序列号
	char *First_Sequence_Nb;            //原始序列号
	char *Gear_Ratio;                   //信号齿轮单元的比率的设定
	char *Explain;                      //说明
	char *Type;                         //类型
	char *Quality_Gu;                   //电机质保
	char *Firmware_Version;             //固件版本
	char *Position_Control;             //位置控制
	char *Process_Control;              //过程控制
	char *Velocity_Curve;               //速度曲线功能
	char *Stroke_Segment;               //行程分段
	char *External_Analog;              //外部模拟给定
	char *Split_Functionality;          //比例拆分给定
}p1;
p1 P1;


typedef struct   
{
	char *Label;                        //执行机构标签号
	char Close_Direction;               //关方向 1顺时针 2逆时针
	char Gearbox_Model;                 //1-没有附加的齿轮箱  2-多回转齿轮箱  3-部分回转齿轮箱  4-线性单元
	char Type;                          //类型  1-用户自定义  2-*LF12.1
	char *Reduction_Ratio;              //减速比                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
  char *Moment_Amplifier;             //力矩放大系数     
	char *Output_Torque_MAX;            //最大输出力矩     
	char *Input_Rev_MAX;                //最大输入转速  
	char *Travel;                       //行程    
	char *Signal_Gear_Set;              //信号齿轮设置      
  char  Close_Speed;	                //关速度  5  7 10 14 20 28 40
	char  Open_Speed;	                  //开速度  5  7 10 14 20 28 40
	char  Exigency_Close_Speed;	        //紧急关速度  5  7 10 14 20 28 40
	char  Exigency_Open_Speed;	        //紧急关速度  5  7 10 14 20 28 40
	char  Moment_Close;	                //关力矩  9 12 15 18 21 24 27 30
	char  Moment_Open;	                //开力矩  9 12 15 18 21 24 27 30
	char *Close_Tip_Range;              //关末端位置范围  
	char *Open_Tip_Range;               //开末端位置范围
	char  Close_Modle;                  //关模式   1-行程关断  2-力矩关断
	char  Open_Modle;                   //开模式   1-行程关断  2-力矩关断
}p2;
p2 P2;

typedef struct   
{
	char *Label;                        //执行机构标签号
	char Input_on_off;                  //开关量输入  1-常开  2-常闭
	char Input_Exigency;                //紧急输入    1-常开  2-常闭
	char Input_Modle;                   //模式输入    1-无功能  2-切换锁定就地/远程  3-运行电动操作  4-运行就地操作
  char Type_Remote_Control;           //远端控制类型 1-开关量：持续接点控制  2-开关量：脉冲接点控制
	char Remote_Rechoose;               //远控再选择   1-不起作用
	char AI1_Range;                     //范围1   1-0~20MA  2-4~20MA
	char AI1_Slope;                     //斜坡1   1-上升    2-下降
	char AI2_Range;                     //范围2   1-空
	char AI2_Slope;                     //斜坡2   1-空
	char *Floor_Level;                  //下限
  char *Upper_Level;                  //上限
	char  DCS;                          //DCS给定值  1 -无
 	char  Actual_Position ;             //实际位置值 1-实际值=位置
  char  Output_1 ;                    //输出1    1-未用  2-开方向末端位置 3-关方向末端位置 4-关方向出现力矩关断 5-开方向出现力矩关断 6-关或开方向出现力矩关断 7-故障  8-闪烁 9-准备好 10-准备好+远程 11-就地 12-关中间接点 13-开中间接点 14-电机过热故障 15-电机温度报警 16-维护 17-关方向运行 18-开方向运行  19-运行指示器“打开/关闭”  20-闪烁+全关位置 21-闪烁+全开位置 22-关方向达到行程末端位置 23-开方向达到行程末端位置
	char  Output_2 ;                    //输出2    1-未用  2-开方向末端位置 3-关方向末端位置 4-关方向出现力矩关断 5-开方向出现力矩关断 6-关或开方向出现力矩关断 7-故障  8-闪烁 9-准备好 10-准备好+远程 11-就地 12-关中间接点 13-开中间接点 14-电机过热故障 15-电机温度报警 16-维护 17-关方向运行 18-开方向运行  19-运行指示器“打开/关闭”  20-闪烁+全关位置 21-闪烁+全开位置 22-关方向达到行程末端位置 23-开方向达到行程末端位置
	char  Output_3 ;                    //输出3    1-未用  2-开方向末端位置 3-关方向末端位置 4-关方向出现力矩关断 5-开方向出现力矩关断 6-关或开方向出现力矩关断 7-故障  8-闪烁 9-准备好 10-准备好+远程 11-就地 12-关中间接点 13-开中间接点 14-电机过热故障 15-电机温度报警 16-维护 17-关方向运行 18-开方向运行  19-运行指示器“打开/关闭”  20-闪烁+全关位置 21-闪烁+全开位置 22-关方向达到行程末端位置 23-开方向达到行程末端位置
	char  Output_4 ;                    //输出4    1-未用  2-开方向末端位置 3-关方向末端位置 4-关方向出现力矩关断 5-开方向出现力矩关断 6-关或开方向出现力矩关断 7-故障  8-闪烁 9-准备好 10-准备好+远程 11-就地 12-关中间接点 13-开中间接点 14-电机过热故障 15-电机温度报警 16-维护 17-关方向运行 18-开方向运行  19-运行指示器“打开/关闭”  20-闪烁+全关位置 21-闪烁+全开位置 22-关方向达到行程末端位置 23-开方向达到行程末端位置
	char  Output_5 ;                    //输出5    1-未用  2-开方向末端位置 3-关方向末端位置 4-关方向出现力矩关断 5-开方向出现力矩关断 6-关或开方向出现力矩关断 7-故障  8-闪烁 9-准备好 10-准备好+远程 11-就地 12-关中间接点 13-开中间接点 14-电机过热故障 15-电机温度报警 16-维护 17-关方向运行 18-开方向运行  19-运行指示器“打开/关闭”  20-闪烁+全关位置 21-闪烁+全开位置 22-关方向达到行程末端位置 23-开方向达到行程末端位置
  char  Output_6 ;                    //输出6    1-未用  2-开方向末端位置 3-关方向末端位置 4-关方向出现力矩关断 5-开方向出现力矩关断 6-关或开方向出现力矩关断 7-故障  8-闪烁 9-准备好 10-准备好+远程 11-就地 12-关中间接点 13-开中间接点 14-电机过热故障 15-电机温度报警 16-维护 17-关方向运行 18-开方向运行  19-运行指示器“打开/关闭”  20-闪烁+全关位置 21-闪烁+全开位置 22-关方向达到行程末端位置 23-开方向达到行程末端位置
	char  Output_7 ;                    //输出7    1-未用  2-开方向末端位置 3-关方向末端位置 4-关方向出现力矩关断 5-开方向出现力矩关断 6-关或开方向出现力矩关断 7-故障  8-闪烁 9-准备好 10-准备好+远程 11-就地 12-关中间接点 13-开中间接点 14-电机过热故障 15-电机温度报警 16-维护 17-关方向运行 18-开方向运行  19-运行指示器“打开/关闭”  20-闪烁+全关位置 21-闪烁+全开位置 22-关方向达到行程末端位置 23-开方向达到行程末端位置
	char  Output_8 ;                    //输出8    1-未用  2-开方向末端位置 3-关方向末端位置 4-关方向出现力矩关断 5-开方向出现力矩关断 6-关或开方向出现力矩关断 7-故障  8-闪烁 9-准备好 10-准备好+远程 11-就地 12-关中间接点 13-开中间接点 14-电机过热故障 15-电机温度报警 16-维护 17-关方向运行 18-开方向运行  19-运行指示器“打开/关闭”  20-闪烁+全关位置 21-闪烁+全开位置 22-关方向达到行程末端位置 23-开方向达到行程末端位置
	char  State_1 ;                     //状态值1  1-常开  2-常闭
	char  State_2 ;                     //状态值2  1-常开  2-常闭
	char  State_3 ;                     //状态值3  1-常开  2-常闭
	char  State_4 ;                     //状态值4  1-常开  2-常闭
	char  State_5 ;                     //状态值5  1-常开  2-常闭
	char  State_6 ;                     //状态值6  1-常开  2-常闭
	char  State_7 ;                     //状态值7  1-常开  2-常闭
	char  State_8 ;                     //状态值8  1-常开  2-常闭
	char  AO1_Output;                   //AO1输出值   1-实际位置值
	char  AO1_Range;                    //A01 范围1   1-0~20MA  2-4~20MA
	char  AO1_Slope;                    //A01斜坡1   1-上升    2-下降
  char  AO2_Output;                   //AO2输出值   1-空
	char  AO2_Range;                    //A02 范围1   1-空
	char  AO2_Slope;                    //A02斜坡1   1-空
	char *Middle_Close;                 //关中间位置
  char *Middle_Open;                  //开中间位置
}p3;
p3 P3;



typedef struct   
{
	char *Label;                        //执行机构标签号
	char *Motor_T_Warn;                 //电机报警温度 
	char *Motor_P_Heater;               //电机过热保护
  char Motor_Heater;                  //电机加热 1-关  2-开
	char Remote_Control_E;              //远控型号故障 1-保持原位  2-运行到“紧急”位置  3-执行最后一个指令
	char *Urgency_Location;             //紧急位置
  char Fasten ;                       //关紧 1-关  2-开
	char Retries_Cnt ;                  //过力矩故障后的重试次数 0 1 2 3 4 5
	char *Switch_Cnt;                   //开关次数 	
	char *Close_Cnt;                    //力矩关断次数 	
	char *Motor_Operation;              //电机运行 	
}p4;
p4 P4;

typedef struct   
{
	char *Label; 
	char Language;                      //显示屏语   1-德语 2-法语 3-西班牙语 4-意大利语 5-波兰语 6-捷克语 7-瑞典语 8-荷兰语 9-葡萄牙语 10-芬兰语 11-中文 12-英语 13-俄语 14-丹麦语 15-土耳其语 16-罗马尼亚语 17-阿拉伯语 18-斯洛伐克语 19-希腊语 20-巴西语 21-日语 22-埃及语 23-保加利亚语 24-印地语 25-朝鲜语 26-克罗地亚 27-挪威语 28-斯洛文尼亚语 29-匈牙利语 30-泰国语                                              
	char NVRotate;                      //显示屏显示方向  1-0 2-90 3-180  
	char Screen_Standby ;               //待机屏幕   1-标准 2-位置 3-位置+填充 4-位置+进度条+状态 5-快速切换到就地    
  char *Standby_Time;                 //待机时间 
	char *Brake_DC;                     //直流制动
	char *UP_Time;                      //上升时间
  char *Dead_Band_Min ;               //死区最小
	char *Dead_Band_Max ;               //死区最大
	char  P_C_Time;                     //比例控制的时间 	1-自检
	char *Default_Close;                //默认关 	
	char *Default_Open;                 //默认开 	
	char *User_Defined_Close;           //用户自定义关   // 67997292
	char *User_Defined_Open;	          //用户自定义开
	char *Delay_Time;	                  //延时时间
	char *Installation_Component;       //安装组件
	char Terminal_RPM;                  //终端转速    1-正常  2-快速启动 3-快速启动/停止
	char *Receipt_Time;                 //接受时间
	char *User_Function_Code;           //用户功能代码
	char *Parameter_1;                  //参数1
	char *Parameter_2;                  //参数2
	char *Parameter_3;                  //参数3
	char *Parameter_4;                  //参数4
	char Limiting_Voltage_DC;           //限制直流电压  1-开  2-关
	char Run_Time;                      //限制直流电压  1-开  2-关
  char Bluetooth;                     //蓝牙  1-是  2-否
  char Torque_Flange;                 //扭矩测量法兰  1-不可用  2-模拟输入端AI1 3-120Nm（10.1，2SX7100-6A）  4-500Nm（14.5，2SX7100-6B） 5-1000Nm（16.1，2SX7100-6C）
}p5;
p5 P5;


typedef struct   
{ 
	char *Label;                        //执行机构标签号
	char *KP_Controller;                //比例控制器
	char *KI_Time ;                     //积分时间常数
  char *Fixed_Value;                  //固定给定值 
  char *Site_1;                       //位置1
  char *Site_2;                       //位置2 
	char *Electricity_1;                //电流值1
  char *Electricity_2;                //电流值2
	char  Local_Operating_Speed_1;        //就地操作速度  1-正常"开/关"速度
	char  Remote_Control_Speed_1;         //远控速度  1-由"输入速度"决定
	char  Input_speed;                  //输入速度  1--模拟量输入1(AI1)
	char *Start_0;                       //开始0 
	char *Start_1;                       //开始1 
	char *Start_2;                       //开始2 
	char *Start_3;                       //开始3 
	char *Start_4;                       //开始4 
	char *Start_5;                       //开始5 
	char *Start_6;                       //开始6 
	char *Start_7;                       //开始7 
	char *Start_8;                       //开始8 
	char *Start_9;                       //开始9 
	char *Start_10;                      //开始10
	char *Preset_Time_0;                 //定位时间0
	char *Preset_Time_1;                 //定位时间1
	char *Preset_Time_2;                 //定位时间2
	char *Preset_Time_3;                 //定位时间3
	char *Preset_Time_4;                 //定位时间4
	char *Preset_Time_5;                 //定位时间5
	char *Preset_Time_6;                 //定位时间6
	char *Preset_Time_7;                 //定位时间7
	char *Preset_Time_8;                 //定位时间8
	char *Preset_Time_9;                 //定位时间9
	char *Preset_Time_10;                //定位时间10
	char *Total_Time_1;                  //总的定位时间1
  char *Total_Time_2;                  //总的定位时间2
	char *Total_Time_3;                  //总的定位时间3
	char *Total_Time_4;                  //总的定位时间4
	char *Total_Time_5;                  //总的定位时间5
	char *Total_Time_6;                  //总的定位时间6
	char *Total_Time_7;                  //总的定位时间7
	char *Total_Time_8;                  //总的定位时间8
	char *Total_Time_9;                  //总的定位时间9
	char *Total_Time_10;                 //总的定位时间10
  char  Local_Operating_Speed_2;       //就地操作速度2   1-由定位时间曲线决定
	char  Remote_Control_Speed_2;        //远控速度   1-由定位时间曲线决定
	char  Emergency_Speed;               //紧急速度   1-紧急开/关速度
	char *Emergency_Curve;               //紧急曲线系数
	char  Positioning_Time;               //执行机构定位时间
	char *Velocity_Curve_1;               //曲线速度1
	char *Velocity_Curve_2;               //曲线速度2
	char *Velocity_Curve_3;               //曲线速度3
	char *Velocity_Curve_4;               //曲线速度4
	char *Velocity_Curve_5;               //曲线速度5
	char *Velocity_Curve_6;               //曲线速度6
	char *Velocity_Curve_7;               //曲线速度7
	char *Velocity_Curve_8;               //曲线速度8
	char *Velocity_Curve_9;               //曲线速度9
	char *Velocity_Curve_10;              //曲线速度10
	char  Outputspeed_1;                  //输出转速1  1-5
	char  Outputspeed_2;                  //输出转速2  1-5
	char  Outputspeed_3;                  //输出转速3  1-5
	char  Outputspeed_4;                  //输出转速4  1-5
	char  Outputspeed_5;                  //输出转速5  1-5
	char  Outputspeed_6;                  //输出转速6  1-5
	char  Outputspeed_7;                  //输出转速7  1-5
	char  Outputspeed_8;                  //输出转速8  1-5
	char  Outputspeed_9;                  //输出转速9  1-5
	char  Outputspeed_10;                 //输出转速10 1-5
	char  Local_Operating_Speed_3;        //就地操速度   1-正常"开/关"速度
	char  Remote_Control_Speed_3;         //远控速度     1-曲"曲线"决定
}p6;
p6 P6;



typedef struct   
{ 
	char *Data_1;              //数据1
	char *Data_2;              //数据2
	char *Data_3;              //数据3
	char  Colour;              //颜色
}p7;
p7 P7;


typedef struct   
{ 
	char *Control_Mode;                          //当前控制方式
	char *Control_Command;                       //控制命令
	char *Actual_Speed;                          //实际转速/给定时间
	char *Cutoff ;                               //关断
	char *Indirect_points_Close ;                //关中间接点
	char *Indirect_points_Open ;                 //开中间接点
	char *Misdeed ;                              //错误行为
	char *Given_Value ;                          //给定值位置
	char *Actual_Value ;                         //实际值位置
	char *Actual_Process_Value ;                 //过程实际值
	char *Motor_Temperature ;                    //电机温度
	char *Temperature_Alarm ;                    //电机过热报警
	char *Bus_Voltage_DC ;                       //直流母线电压
	char *Motor_Current ;                        //电机电流
	char *AI1 ;                                  //AI1
	char *Close ;                                //开关量输-关
	char *Open ;                                 //开关量输-开
	char *Stop ;                                 //开关量输-停
	char *Urgency ;                              //开关量输-紧急
	char *Mode ;                                 //开关量输-模式
	char *Current_Value ;                        //当前数值
	char *Offset ;                               //偏差
}p8;
p8 P8;

typedef struct   
{ 
	char *Label;                                //执行机构标签号
	char *Open_Cnt_1;                          //开关次数
	char *Open_Frequency_1;                    //开关频率
  char *Torque_Close_Cnt;                  //力矩关断次数
	char *Journey_Close_Cnt;                 //行程关断次数
	char *Moto_Runtimes_1;                     //电机运行小时
	char *Circuit_Wafer_Runtimes;            //电子板工作小时数
	char *Operating_Frequency;               //运行频度
	char *Open_Cnt_2;                          //开关次数
  char *Open_Frequency_2;                    //开关频率
	char *Moto_Runtimes_2;                     //电机运行小时
	char *Maintenance_valve;                    //阀门维护
}p9;
p9 P9;


typedef struct   
{
	
	char *MODBUS_Address_1;                          // MODBUS地址1
	char *MODBUS_Address_2;                          // MODBUS地址2
  char  Baud_Rate_1;                               // 波特率1       1-19200
	char  Baud_Rate_2;                               // 波特率2       1-19200
	char  Check_Code_1;                              // 奇偶校验1     1-偶校验，1停止
	char  Check_Code_2;                              // 奇偶校验2     1-偶校验，1停止
	char *Monitoring_Time_1;                         // 监控时间1
	char *Monitoring_Time_2;                         // 监控时间2
	char *PROFIBUS_Address_1;                        // PROFIBUS地址1
	char *PROFIBUS_Address_2;                        // PROFIBUS地址2
	char  PZD3;                                      //  PZD3   1-状态字2（ZSW2）
	char  PZD4;                                      //  PZD4   1-故障信号1
	char  PZD5;                                      //  PZD5   1-故障信号2
	char  PZD6;                                      //  PZD6   1-实际控制方式
	char *HART_Address;                              //  HART地址
	char *HART_Time;                                 //  HART监视时间
	char *Bus_Work_Channel;                          //  总线工作通道
	char *Bus_Channel_1;                             //  总线通道1
	char *Bus_Channel_1_Status;                      //  总线通道1 状态
	char *Bus_Channel_2;                             //  总线通道2
	char *Bus_Channel_2_Status;                      //  总线通道2 状态
	char *CTC_Type;                                  //  沉余类型
	char *CTC_Status_1;                              //  沉余状态1
	char *CTC_Status_2;                              //  沉余状态2
	char *Keep_Output_Time;                          //  保持输出时间
	char *TS_Status_1;                               //  TS状态1
	char *TS_Status_2;                               //  TS状态2
	char  Timestamp;                                 //  时间戳
}pA;
pA PA;


typedef struct   
{ 
	char Tab_Control_1;                          // MODBUS地址1
	char Tab_Control_2;                          //选项卡2
	char Tab_Control_3;                          //选项卡3
	char Tab_Control_4;                          //选项卡4
	char Tab_Control_5;                          //选项卡5
	char *Trouble1;                              //从前故障1
	char *Trouble2;                              //从前故障2
	char *Trouble3;                              //从前故障3
	char *Trouble4;                              //从前故障4
	char *Trouble5;                              //从前故障5
}pB;
pB PB;



void MODBUS_SEND_0420(unsigned short dat);
#endif

