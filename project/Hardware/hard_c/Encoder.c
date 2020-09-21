#include "Encoder.h"
#include "datafigures.h"
#include "USART_Conf.h"
                                                  
void Init_Encoder(void)
{
    scu_pinmux(0x0A ,1 , MD_PDN, FUNC0);
    GPIO_SetDir(4,(1<<8), 1);
	scu_pinmux(0x0A ,2 , MD_EZI, FUNC0);
    GPIO_SetDir(4,(1<<9), 0);
    SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000); 
    GPIO_SetValue(4,(1<<8));
}


void Restart_Encoder_Init(void)
{
	scu_pinmux(Restart_Encoder_PORT ,Restart_Encoder_PORT_PIN , MD_EZI, Restart_Encoder_PORT_FUNC);
    GPIO_SetDir(Restart_Encoder_GPIO,(1<<Restart_Encoder_GPIO_PIN), 1);


    SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000);
	
	GPIO_ClearValue(Restart_Encoder_GPIO,(1<<Restart_Encoder_GPIO_PIN));
	
}

void Restart_Encoder(int set)
{
	if(set==0)
	{
		GPIO_ClearValue(Restart_Encoder_GPIO,(1<<Restart_Encoder_GPIO_PIN));
	}else
	if(set==1)
	{
		GPIO_SetValue(Restart_Encoder_GPIO,(1<<Restart_Encoder_GPIO_PIN));
	}
}



int graytobinary(uint32_t graycode)
{
	int gray[32];
	int binary[32];
	int i,j;
	uint32_t binarycode;
	
	for(i=0;i<32;i++)
	{
		gray[i]=graycode%2;
		graycode=graycode>>1;
	}
	binary[31]=gray[31];
	
	for(j=30;j>=0;j--)
	{
		binary[j]=binary[j+1]^gray[j];	
		binarycode=(binarycode<<1)+binary[j];
	}
	binarycode=binarycode&0x0FFFFFFF;
	return binarycode;
	
}

void UART2_IRQHandler(void)
{
    uint8_t res;
	static uint8_t cnt0;	
	uint32_t timeOut;
	while(1)
	{
		if (!(LPC_USART2->LSR & UART_LSR_RDR)) 
		{
			break;
		} else
		{
            res=UART_ReceiveByte(LPC_USART2);
			encoder.RX_Timeout=0;
			if(encoder.RX_timeout_buf==0)
			{
                uart2.buffer2_ALL[cnt0++]=res;
				encoder.RX_Timeout_flag=1;
			}else
			{
				cnt0=0;
			}
					
					if(cnt0>6)
					{
						cnt0=0;
					}
		}
	}
}

void c_entry_uart2_encoder (void) 
{
    uint8_t buffer0_buf[8];
    buffer0_buf[0]=0x00;
    buffer0_buf[1]=uart2.buffer2_ALL[0];
    buffer0_buf[2]=uart2.buffer2_ALL[1];
    buffer0_buf[3]=uart2.buffer2_ALL[2];
    buffer0_buf[4]=uart2.buffer2_ALL[3];
    buffer0_buf[5]=uart2.buffer2_ALL[4];
	
	encoder.ssi_m=(buffer0_buf[0]<<16)+(buffer0_buf[1]<<8)+(buffer0_buf[2]);
	encoder.ssi_s=(buffer0_buf[3]<<16)+(buffer0_buf[4]<<8)+(buffer0_buf[5]);
}
void UART2_Init(void)
{
	UART_CFG_Type UARTConfigStruct;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	scu_pinmux(0xA ,2 , MD_PLN|MD_EZI|MD_ZI, FUNC3); 	        
	UART_ConfigStructInit0(&UARTConfigStruct);
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	UART_Init((LPC_USARTn_Type *)LPC_USART2, &UARTConfigStruct);
	UART_FIFOConfig((LPC_USARTn_Type *)LPC_USART2, &UARTFIFOConfigStruct);
	UART_TxCmd((LPC_USARTn_Type *)LPC_USART2, ENABLE);
    UART_IntConfig((LPC_USARTn_Type *)LPC_USART2, UART_INTCFG_RBR, ENABLE);
    UART_IntConfig((LPC_USARTn_Type *)LPC_USART2, UART_INTCFG_RLS, ENABLE);

	NVIC_SetPriority(USART2_IRQn, ((0x03<<3)|0x01)); 
    NVIC_EnableIRQ( USART2_IRQn); 

}

#if 1
void c_entry_Encoder2 (void) 
{
    uint32_t  read_run_tmp = 0;
    
	#ifdef Encnew
	key_mlx90363.Read_now=graytobinary(data_figures.READ_timer&0xFFFFFFF);
	#elif  Encold
	key_mlx90363.Read_now=(encoder.ssi_m<<24)+(encoder.ssi_s&0x00FFFFFF);
	#endif
	if((key_mlx90363.Read_now)&KEY_NOW)  //编码器位于设定的原点处
	{
		encoder.zhengfu_now=0;
		key_mlx90363.Run_dir=0;
		#ifdef Binary
			#ifdef Encnew
			key_mlx90363.Read_all=0xFFFFFFF-data_figures.READ_timer&0xFFFFFFF;
			#elif  Encold
			key_mlx90363.Read_all=0xFFFFFFFFFFFF-key_mlx90363.Read_now&0xFFFFFFFFFFFF;
			#endif
			
		#elif Gray
			#ifdef Encnew
			key_mlx90363.Read_all=0xFFFFFFF-key_mlx90363.Read_now;
			#elif  Encold
			key_mlx90363.Read_all=0x0FFFFFF-key_mlx90363.Read_now;
			#endif			
		#endif
			if(key_mlx90363.Read_all==0xFFFFFFF)
			{
				key_mlx90363.Read_all=0;
			}
			
	}else
	{
		encoder.zhengfu_now=1;
		key_mlx90363.Run_dir=1;
		#ifdef Binary
			#ifdef Encnew
				key_mlx90363.Read_all=data_figures.READ_timer&0xFFFFFFF;
			#elif  Encold
                key_mlx90363.Read_all=key_mlx90363.Read_now&0xFFFFFFFFFFFF;
			#endif
			
		#elif Gray
			#ifdef Encnew
				key_mlx90363.Read_all=key_mlx90363.Read_now;//graytobinary(data_figures.READ_timer&0xFFFFFFF);
			#elif  Encold
				key_mlx90363.Read_all=key_mlx90363.Read_now;
			#endif
			
		#endif
			
	}
	
	key_mlx90363.Integer_2=((key_mlx90363.Read_all*100)/data_figures.READ_ALL_903);
	key_mlx90363.decimal_2=((key_mlx90363.Read_all*1000)/data_figures.READ_ALL_903)-(key_mlx90363.Integer_2*10);
	key_mlx90363.READ_run=(key_mlx90363.Integer_2*10)+key_mlx90363.decimal_2;
    
    /*精度调整不精确，给定20mA有时候会超过量程翻转成4mA，防止计算得到的READ_run_1小于0*/
    read_run_tmp = key_mlx90363.READ_run;
    if(read_run_tmp >= 0 && read_run_tmp <5)
    {
        read_run_tmp = 5;
    }
    else if(read_run_tmp >995)
    {
        read_run_tmp = 995;
    }
    
	key_mlx90363.READ_run_1=(1000.0*(read_run_tmp-5))/990.0;
	key_mlx90363.Integer_3=(int)key_mlx90363.READ_run_1/10;
	key_mlx90363.decimal_3=(int)key_mlx90363.READ_run_1%10;
	key_mlx90363.ssi_m=(key_mlx90363.Read_all/4096);
	key_mlx90363.ssi_s=(key_mlx90363.Read_all%4096)*10/4096;			
				if((key_mlx90363.READ_run>=5)&&(key_mlx90363.READ_run<=995))
				{
					motorset.flag_MOTOR_Run=1;
					motorset.flag_MOTOR_Close=0;
					motorset.flag_MOTOR_Open=0;
				}
                
				if((encoder.num==1)||(encoder.num==4))
				{
					if((key_mlx90363.READ_run>995)&&(key_mlx90363.READ_run<=1200))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=0;
						motorset.flag_MOTOR_Open=1;
					}
					if(((key_mlx90363.READ_run>=0)&&(key_mlx90363.READ_run<5))||(key_mlx90363.Run_dir==0))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=1;
						motorset.flag_MOTOR_Open=0;
					}
				}else
				if(encoder.num==2)
				{
					if((key_mlx90363.READ_run>995)&&(key_mlx90363.READ_run<=1200))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=1;
						motorset.flag_MOTOR_Open=0;
					}
					if(((key_mlx90363.READ_run>=0)&&(key_mlx90363.READ_run<5))||(key_mlx90363.Run_dir==0))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=0;
						motorset.flag_MOTOR_Open=1;
					}
					key_mlx90363.READ_run_1=1000-key_mlx90363.READ_run_1;
					key_mlx90363.Integer_3=99-key_mlx90363.Integer_3;
					key_mlx90363.decimal_3=9-key_mlx90363.decimal_3;  //decimal范围为0-9，这边用10减的话，会使得其范围变为10-1，影响GUI中百分比显示
				}else
				if(encoder.num==3)
				{
					if((key_mlx90363.READ_run>995)&&(key_mlx90363.READ_run<=1200))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=0;
						motorset.flag_MOTOR_Open=1;
					}
					if(((key_mlx90363.READ_run>=0)&&(key_mlx90363.READ_run<5))||(key_mlx90363.Run_dir==1))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=1;
						motorset.flag_MOTOR_Open=0;
					}
				}else
				if(encoder.num==5)  
				{
					if((key_mlx90363.READ_run>995)&&(key_mlx90363.READ_run<=1200))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=1;
						motorset.flag_MOTOR_Open=0;
					}
					if(((key_mlx90363.READ_run>=0)&&(key_mlx90363.READ_run<5))||(key_mlx90363.Run_dir==0))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=0;
						motorset.flag_MOTOR_Open=1;
					}
				}
				else
					if(encoder.num==8)
				{
					if((key_mlx90363.READ_run>995)&&(key_mlx90363.READ_run<=1200))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=1;
						motorset.flag_MOTOR_Open=0;
					}
					if(((key_mlx90363.READ_run>=0)&&(key_mlx90363.READ_run<5))||(key_mlx90363.Run_dir==0))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=0;
						motorset.flag_MOTOR_Open=1;
					}
				}else
				if(encoder.num==6)
				{
					if((key_mlx90363.READ_run>995)&&(key_mlx90363.READ_run<=1200))  
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=1;
						motorset.flag_MOTOR_Open=0;
					}
					if(((key_mlx90363.READ_run>=0)&&(key_mlx90363.READ_run<5))||(key_mlx90363.Run_dir==0))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=0;
						motorset.flag_MOTOR_Open=1;
					}
					
					key_mlx90363.READ_run_1=1000-key_mlx90363.READ_run_1;
					key_mlx90363.Integer_3=99-key_mlx90363.Integer_3;
					key_mlx90363.decimal_3=9-key_mlx90363.decimal_3;  //decimal范围为0-9，这边用10减的话，会使得其范围变为10-1，影响GUI中百分比显示
				}else
				if(encoder.num==7)
				{
					if((key_mlx90363.READ_run>995)&&(key_mlx90363.READ_run<=1200))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=1;
						motorset.flag_MOTOR_Open=0;
					}
					if(((key_mlx90363.READ_run>=0)&&(key_mlx90363.READ_run<5))||(key_mlx90363.Run_dir==1))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=0;
						motorset.flag_MOTOR_Open=1;
					}
				}else
				{
					if((key_mlx90363.READ_run>995)&&(key_mlx90363.READ_run<=1200))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=0;
						motorset.flag_MOTOR_Open=1;
					}
					if(((key_mlx90363.READ_run>=0)&&(key_mlx90363.READ_run<5))||(key_mlx90363.Run_dir==0))
					{
						motorset.flag_MOTOR_Run=0;
						motorset.flag_MOTOR_Close=1;
						motorset.flag_MOTOR_Open=0;
					}
				}

	ssi_m=(key_mlx90363.Read_all/4096);
	ssi_s=(key_mlx90363.Read_all%4096)*10/4096;
	key_mlx90363.ssi_m=(key_mlx90363.Read_all/4096);
	key_mlx90363.ssi_s=(key_mlx90363.Read_all%4096)*10/4096;
}



#endif







