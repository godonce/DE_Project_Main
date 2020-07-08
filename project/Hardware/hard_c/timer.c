#include "timer.h"
#include  "datafigures.h"
#include "Encoder.h"
uint8_t a=0;
volatile char  f=0;
uint8_t flag_read=1;
uint32_t read_data=0;
extern volatile uint32_t READ_ALL;
extern int flag_TAB_3s;
extern int flag_TAB_3s_start;
int flag_TAB_3s_num;

void TIMER0_IRQHandler(void)
{	

  if (TIM_GetIntStatus(LPC_TIMER0, TIM_MR0_INT)== SET) 
	{
		TIM_ClearIntPending(LPC_TIMER0, TIM_MR0_INT); 
		a++;
		f++;
	}
		if((a<58))
		{
				if(a%2==0)
				{
					GPIO_SetValue(4,(1<<8));
				}
				if(a%2==1)
				{
					GPIO_ClearValue(4,(1<<8));
					read_data=read_data<<1;
					if(flag_read==1)
					{
						if(GPIO_ReadValue(0x4)&(1<<9))
						{
							read_data++;
						}else
						{
							read_data=read_data;
						}
					}	
			}
		}
			else
			if(a<68&&a>=58)
			{
				
				data_figures.READ_timer=read_data&0xFFFFFFF;
				GPIO_SetValue(4,(1<<8));
				flag_read=0;
			}else
			if(a==68)
			{
				GPIO_SetValue(4,(1<<8));
				a=0;
				flag_read=1;
	}
}
TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct ;
void Timer0_Init(void)             
{
  TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
  TIM_ConfigStruct.PrescaleValue	= 2;

  TIM_MatchConfigStruct.MatchChannel = 0;
  TIM_MatchConfigStruct.IntOnMatch   = TRUE;
  TIM_MatchConfigStruct.ResetOnMatch = TRUE;
  TIM_MatchConfigStruct.StopOnMatch  = FALSE;
  TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_TOGGLE;
  TIM_MatchConfigStruct.MatchValue   = 1;

  TIM_Init(LPC_TIMER0, TIM_TIMER_MODE,&TIM_ConfigStruct);
  TIM_ConfigMatch(LPC_TIMER0,&TIM_MatchConfigStruct);

  NVIC_SetPriority(TIMER0_IRQn, ((0x03<<3)|0x01));
  NVIC_EnableIRQ(TIMER0_IRQn);
  TIM_Cmd(LPC_TIMER0,ENABLE);
	
}



uint16_t flag_6ms,flag_10ms;
volatile uint8_t flag_receive;
volatile uint8_t flag_send,flag_ready2;
void TIMER1_IRQHandler(void)           
{	
  if (TIM_GetIntStatus(LPC_TIMER1, TIM_MR1_INT)== SET) 
	{
		TIM_ClearIntPending(LPC_TIMER1, TIM_MR1_INT); 
		flag_6ms++;
		flag_10ms++;
        encoder.RX_Timeout++;
		if((flag_6ms>600))  
		{
			flag_6ms=0;
			flag_send=1;
			flag_ready2=1;
		}	
		if(flag_10ms>100)
		{
			flag_10ms=0;
			flag_receive=1;
		}
		if(encoder.RX_Timeout>20)
		{
			encoder.RX_timeout_buf=1;
		}else
		{
			encoder.RX_timeout_buf=0;
		}		
	}
}


TIM_TIMERCFG_Type TIM1_ConfigStruct;
TIM_MATCHCFG_Type TIM1_MatchConfigStruct ;
void Init_Timer1(void)
{
  TIM1_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
  TIM1_ConfigStruct.PrescaleValue	= 10;//100;
  TIM1_MatchConfigStruct.MatchChannel = 1;
  TIM1_MatchConfigStruct.IntOnMatch   = TRUE;
  TIM1_MatchConfigStruct.ResetOnMatch = TRUE;
  TIM1_MatchConfigStruct.StopOnMatch  = FALSE;
  TIM1_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_TOGGLE;
  TIM1_MatchConfigStruct.MatchValue   =1;

  TIM_Init(LPC_TIMER1, TIM_TIMER_MODE,&TIM1_ConfigStruct);
  TIM_ConfigMatch(LPC_TIMER1,&TIM1_MatchConfigStruct);
	TIM_Cmd(LPC_TIMER1,ENABLE);
  NVIC_SetPriority(TIMER1_IRQn, ((0x02<<3)|0x01));
  NVIC_EnableIRQ(TIMER1_IRQn);
}

void TIMER2_IRQHandler(void)
{	
	#if 1
  if (TIM_GetIntStatus(LPC_TIMER2, TIM_MR2_INT)== SET) 
	{
		TIM_ClearIntPending(LPC_TIMER2, TIM_MR2_INT); 
		if(encoder.dufangxianng_set_flag==1)
		{
			encoder.dufangxiang_num++;
			if(encoder.dufangxiang_num>2)
			{
				encoder.dufangxiang_num=0;
			}
		}
		if(flag_TAB_3s_start==1)
		{
			flag_TAB_3s_num++;			
			if(flag_TAB_3s_num>10)
			{
				flag_TAB_3s_num=0;
				flag_TAB_3s=1;
			}
		}
		else
		{
			flag_TAB_3s_num=0;
			flag_TAB_3s=0;
		}		
		if(timer.flag_3sTAB1_start==1)
		{
			timer.flag_3sTAB1_num++;			
			if(timer.flag_3sTAB1_num>10)
			{
				timer.flag_3sTAB1_num=0;
				timer.flag_3sTAB1=1;
			}
		}
		else
		{
			timer.flag_3sTAB1_num=0;
			timer.flag_3sTAB1=0;
		}
		
		if(timer.flag_3sTAB2_start==1)
		{
			timer.flag_3sTAB2_num++;			
			if(timer.flag_3sTAB2_num>10)
			{
				timer.flag_3sTAB2_num=0;
				timer.flag_3sTAB2=1;
			}
		}
		else
		{
			timer.flag_3sTAB2_num=0;
			timer.flag_3sTAB2=0;
		}
		
		
		timer.runhhh++;
		if(timer.flag_all_run==1)
		{
			timer.all_run_s++;
			if(timer.all_run_s>10)
			{
				
				timer.flag_all_run_s=1;
				timer.flag_all_run=0;
				timer.all_run_s=0;
			}
		}
		if(timer.flag_coils==1)
		{
			timer.run_coils_num++;
			if(timer.run_coils_num>10)
			{
				timer.flag_coils_run_s=1;
				timer.flag_coils=0;
				timer.run_coils_num=0;
			}
		}
		if(timer.check_run<states_error.run_time_error)
		{
			flag_figures.run_error=1;
		}
		if(lcd.an_flag==1)
		{
			lcd.num++;
			if(lcd.num>=(1000*10))
			{
				lcd.an_set_flag=1;
				lcd.num=0;
			}
		}else
		{
			lcd.an_set_flag=0;
				lcd.num=0;
		}
		
		
		
		if(motorset.flag_run==1)  //堵转判断规避启动2s内大电流
		{
			motorset.currentout_num1++;
			if(motorset.currentout_num1 > 20)  //30
			{
				motorset.flag_run=0;
				motorset.currentout_num1=0;
			}
		}
		
		if(motorset.flag_run==2)  //堵转判断规避停机大电流
		{
			motorset.currentout_num2++;
			if(motorset.currentout_num2 > 5)
			{
				motorset.flag_run=0;
				motorset.currentout_num2=0;
			}
		}
	}
	#endif
}


TIM_TIMERCFG_Type TIM2_ConfigStruct;
TIM_MATCHCFG_Type TIM2_MatchConfigStruct ;
void Init_Timer2(void)    
{
  TIM2_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
  TIM2_ConfigStruct.PrescaleValue	= 100;
  TIM2_MatchConfigStruct.MatchChannel = 2;
  TIM2_MatchConfigStruct.IntOnMatch   = TRUE;
  TIM2_MatchConfigStruct.ResetOnMatch = TRUE;
  TIM2_MatchConfigStruct.StopOnMatch  = FALSE;
  TIM2_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_TOGGLE;
  TIM2_MatchConfigStruct.MatchValue   =1000;

	
  TIM_Init(LPC_TIMER2, TIM_TIMER_MODE,&TIM2_ConfigStruct);
  TIM_ConfigMatch(LPC_TIMER2,&TIM2_MatchConfigStruct);
	TIM_Cmd(LPC_TIMER2,ENABLE);
	NVIC_SetPriority(TIMER2_IRQn, ((0x02<<3)|0x03));
  NVIC_EnableIRQ(TIMER2_IRQn);
	
}



void TIMER3_IRQHandler(void)       
{	
  if (TIM_GetIntStatus(LPC_TIMER3, TIM_MR3_INT)== SET) 
	{
		
	}
}


TIM_TIMERCFG_Type TIM3_ConfigStruct;
TIM_MATCHCFG_Type TIM3_MatchConfigStruct ;
void Init_Timer3(void)
{
  TIM3_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
  TIM3_ConfigStruct.PrescaleValue	= 1000;
  TIM3_MatchConfigStruct.MatchChannel = 0;
  TIM3_MatchConfigStruct.IntOnMatch   = TRUE;
  TIM3_MatchConfigStruct.ResetOnMatch = TRUE;
  TIM3_MatchConfigStruct.StopOnMatch  = FALSE;
  TIM3_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_TOGGLE;
  TIM3_MatchConfigStruct.MatchValue   =1000;

  TIM_Init(LPC_TIMER3, TIM_TIMER_MODE,&TIM3_ConfigStruct);
  TIM_ConfigMatch(LPC_TIMER3,&TIM3_MatchConfigStruct);
	TIM_Cmd(LPC_TIMER3,ENABLE);
  NVIC_SetPriority(TIMER3_IRQn, ((0x03<<3)|0x03));
  NVIC_EnableIRQ(TIMER3_IRQn);
}

