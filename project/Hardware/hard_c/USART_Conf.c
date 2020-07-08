#include "USART_Conf.h"
#include "torque.h"
#include "datafigures.h"
#include "DataInterface.h"
#include "test_UART0.h"

__IO FlagStatus TxIntStat;
#define __BUF_RESET(bufidx)         (bufidx=0)



extern uint16_t current_up;
extern uint16_t Current_BASE;
extern uint16_t flag_6ms,flag_10ms;
extern volatile uint8_t flag_send,flag_ready2;
extern volatile uint8_t flag_receive;
uint8_t flag_start=1;
uint8_t flag_ok=0; 
uint8_t buffer3_ALL[16];
uint8_t buffer0_ALL[6];
uint8_t buffer3[8];
uint8_t Buffer_Down[8]={0};
uint8_t flag_step1=0;
uint8_t	flag_step2=0;
uint8_t	flag_step3=0;
uint8_t	flag_step4=0;
uint8_t	flag_step=1;
uint8_t flag_allstart1=0;
uint8_t flag_allstart2=0;
uint8_t flag_allstart3=0;
uint8_t TEST_tail_C=0x5A;
uint16_t MOTOR_Speed_OPEN=0xE015;
uint16_t MOTOR_Speed_CLOSE=0xE015;
uint16_t MOTOR_Speed=0xE015;
uint16_t MOTOR_Torque_OPEN=0x0065;
uint16_t MOTOR_Torque_CLOSE=0x0065;
uint16_t MOTOR_Torque=0x0065;
uint16_t Null=0x00;
uint16_t TURN=0xab;
uint16_t CheckSum_H=0xa1;
uint16_t CheckSum_L=0xa2;
#define TEST_tail_H  TEST_tail_C
uint8_t TEST_tail_L=0xA5;
uint8_t TEST_ID=0x01;
uint8_t TEST_ID_VC=0X04;
uint8_t TEST_DATA_A=0x00; 
uint8_t TEST_DATA_B=0x00;
uint8_t TEST_DATA_C=0x00; 
uint8_t TEST_DATA_D=0x00;
uint8_t DIR_MOTOR=3; 
uint8_t DIR_Send;
		

typedef struct __UsartSend
{
    uint8_t		TURN;
    uint8_t 	Speed_H;
	uint8_t 	Speed_L;
	uint8_t		Torque_H;
    uint8_t		Torque_L; 
    uint8_t		Null;
    uint8_t		CheckSum_H;
    uint8_t		CheckSum_L;
}Send_Message3;

typedef struct __Usart0Send
{
    uint8_t		tail_H;
	uint8_t 	tail_L;
	uint8_t 	OP;
	uint8_t		ID;
    uint8_t		DATA_A; 
    uint8_t		DATA_B;
	uint8_t		DATA_C; 
    uint8_t		DATA_D;
}Send_Message0;


void UART_IntErr(uint8_t bLSErrType)
{
    uint8_t test;
    while (1) 
	{
        test = bLSErrType;
        test = test;
    }
}


UART3_RING_BUFFER_T rb3;  
__IO FlagStatus TxIntStat;

void UART3_IRQHandler(void);
void TIMER0_IRQHandler(void);
void Init_UART3(void);

void PowerSend( uint8_t *txbuf, uint8_t buflen);

UART3_RING_BUFFER_T rb3;


void UART3_IRQHandler(void)
{
	uint8_t res;
	static uint8_t cnt;	
	while(1)
	{
		if (!(LPC_USART3->LSR & UART_LSR_RDR)) 
		{
			break;
		} else
		{
			res=UART_ReceiveByte(LPC_USART3);
			buffer3_ALL[cnt++]=res;
			if(cnt>15)
			{
				cnt=0;
			}
		}
	}
}



void UART3_Init(void)
{
	UART_CFG_Type UARTConfigStruct;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	scu_pinmux(0xF ,2 , MD_PDN, FUNC1); 	                    
	scu_pinmux(0xF ,3 , MD_PLN|MD_EZI|MD_ZI, FUNC1); 	        
	UART_ConfigStructInit3(&UARTConfigStruct);
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	UART_Init((LPC_USARTn_Type *)LPC_USART3, &UARTConfigStruct);
	UART_FIFOConfig((LPC_USARTn_Type *)LPC_USART3, &UARTFIFOConfigStruct);
	UART_TxCmd((LPC_USARTn_Type *)LPC_USART3, ENABLE);
    UART_IntConfig((LPC_USARTn_Type *)LPC_USART3, UART_INTCFG_RBR, ENABLE);
    UART_IntConfig((LPC_USARTn_Type *)LPC_USART3, UART_INTCFG_RLS, ENABLE);
	NVIC_SetPriority(USART3_IRQn, ((0x01<<3)|0x01));
    NVIC_EnableIRQ( USART3_IRQn);  
}



void PowerSend( uint8_t *txbuf, uint8_t buflen)
{
		uint32_t bToSend, bSent,  fifo_cnt;
	uint8_t *pChar = txbuf;
		bToSend = buflen;
	while(1)
	{
		if (!(LPC_USART3->LSR & UART_LSR_THRE))
		{
				break;
		}
		fifo_cnt = UART_TX_FIFO_SIZE;
		while (fifo_cnt && bToSend) 
		{
		UART_SendByte(LPC_USART3, (*pChar++));
		bToSend--;
		fifo_cnt--;
		bSent++;
		}
		
	}
}	

Send_Message3 USART3_Send;
extern uint16_t SPEED_END;
extern uint16_t TORQUE_END;
extern uint16_t SPEED_send;
extern uint16_t TORQUE_send;
extern uint16_t Current_STOP;
uint16_t flag_u25=0;
uint16_t flag_u4a=0;
extern uint16_t SPEED_Stand;
extern uint16_t TORQUE_Stand;
extern uint16_t SPEED_Stand_C[7];
extern uint16_t TORQUE_Stand_C[8];
extern char flag_estop;

uint8_t  is_endpos = 0;  //判断是否处于末端位置

void c_entry_uart3(void)
{
    static int abc=1;	
	abc=changeDIR();
    changetorque(abc);	
	if((flag_allstart1==1)&&(flag_allstart2==1)&&(flag_allstart3==1))
	{	
		flag_start=0;
		#if 1
		if(set_end.flag_setend==0)
		{
			if((key_mlx90363.READ_run_1<(dataStructInterface.endPosClose*10))||(key_mlx90363.READ_run_1>(dataStructInterface.endPosOpen*10)))	
			{
                is_endpos = 1;
                
				#ifdef  EE13
                SPEED_Stand=SPEED_Stand_C[0];
                if(motorset.DIR_MOTOR == motorset.DIR_MOTOR_n)  //20200704上电如果处在末端位置，初始给定转矩档位
                {
                    TORQUE_Stand = dataStructInterface.moment_open; 
                }
                else
                {
                    TORQUE_Stand = dataStructInterface.moment_close;
                }
				#endif
			}else
			{
                is_endpos = 0;
                
				if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
				{
					if(motorset.flag_run==1)
					{
						#ifdef  DE13
						SPEED_Stand=SPEED_Stand_C[1];
						#endif
						#ifdef  EE13
						SPEED_Stand=SPEED_Stand_C[1];
						#endif
						#ifdef  CE12
						SPEED_Stand=SPEED_Stand_C[2];
						#endif
						TORQUE_Stand=dataStructInterface.moment_close;
					}
					else
					{
						if(motorset.flag_run_jiangsu==2)
						{
							SPEED_Stand=SPEED_Stand_C[4];
							TORQUE_Stand=dataStructInterface.moment_close;
						}else
						if(motorset.flag_run_jiangsu==1)
						{
							#ifdef  DE13
							SPEED_Stand=SPEED_Stand_C[1];
							#endif
							#ifdef  EE13
							SPEED_Stand=SPEED_Stand_C[1];
							#endif
							#ifdef  CE12
							SPEED_Stand=SPEED_Stand_C[2];
							#endif
							TORQUE_Stand=dataStructInterface.moment_close;
						}else
						if(motorset.flag_run_jiangsu==0)
						{
							SPEED_Stand=dataStructInterface.speed_close;
							TORQUE_Stand=dataStructInterface.moment_close;
						}
					}
				}else
				if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
				{
					if(motorset.flag_run==1)
					{
						#ifdef  DE13
						SPEED_Stand=SPEED_Stand_C[1];
						#endif
						#ifdef  EE13
						SPEED_Stand=SPEED_Stand_C[1];
						#endif
						#ifdef  CE12
						SPEED_Stand=SPEED_Stand_C[2];
						#endif
						TORQUE_Stand=dataStructInterface.moment_close;
					}else
					{
						if(motorset.flag_run_jiangsu==2)
						{
							SPEED_Stand=SPEED_Stand_C[4];
                            TORQUE_Stand=dataStructInterface.moment_close;
						}else
						if(motorset.flag_run_jiangsu==1)
						{
						#ifdef  DE13
						SPEED_Stand=SPEED_Stand_C[1];
						#endif
						#ifdef  EE13
						SPEED_Stand=SPEED_Stand_C[1];
						#endif
						#ifdef  CE12
						SPEED_Stand=SPEED_Stand_C[2];
						#endif
						TORQUE_Stand=dataStructInterface.moment_close;
						
						}else
						if(motorset.flag_run_jiangsu==0)
						{
							SPEED_Stand=dataStructInterface.speed_open;
							TORQUE_Stand=dataStructInterface.moment_open;
							
						}
					}
				}
			}
			
            if(ledstates.remote==1)
			{
				if(ai_o420.flag_mode4==1)  
				{
					if(((ai_o420.send_motor*10) <= (key_mlx90363.READ_run + 3*data_figures.analog_H)) && 
                       ((ai_o420.send_motor*10) >= (key_mlx90363.READ_run - 3*data_figures.analog_H)))//原来系数为3
					{
                        #ifdef  EE13
						SPEED_Stand=SPEED_Stand_C[0];
                        if(motorset.DIR_MOTOR == motorset.DIR_MOTOR_n)  //20200704上电如果处在非末端位置，初始给定转矩档位
                        {
                            TORQUE_Stand = dataStructInterface.moment_open; 
                        }
                        else
                        {
                            TORQUE_Stand = dataStructInterface.moment_close;
                        }
						#endif
					}
				}
			}
			
			if(	remote_conntrol.KEYEme==1)
			{
				if(((key_mlx90363.READ_run)>(dataStructInterface.emergency_pos*10.5)))
				{
					#ifdef  EE13
					SPEED_Stand=SPEED_Stand_C[4];
					#endif
				}else
				if(((key_mlx90363.READ_run)<(dataStructInterface.emergency_pos*9.5)))
				{
					#ifdef  EE13
					SPEED_Stand=SPEED_Stand_C[4];
					#endif
				}
                else
				{							
					#ifdef  EE13
					SPEED_Stand=SPEED_Stand_C[0];
					#endif
				}
			}
		}
		#endif
        #if 1	
		if(set_end.flag_setend==0)
		{	
            if(motorset.flag_MOTOR_Close==1)
			{
				if(motorset.DIR==1)
				{
					if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
					{
						DIR_Send=0x48;
						SPEED_send=0;
						TORQUE_send=0;
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
						motorset.stop=1;
					}
				}else
				if(motorset.DIR==2)
				{
					if(encoder.num==6)
					{
						if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
						{
                            DIR_Send=0x48;
                            SPEED_send=0;
                            TORQUE_send=0;
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                            motorset.stop=1;
						}
					}else
					{
						if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
						{
							DIR_Send=0x48;
							SPEED_send=0;
							TORQUE_send=0;
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
							motorset.stop=2;
						}
					}
				}
			}
            else if(motorset.flag_MOTOR_Open==1)
			{
				if(motorset.DIR==1)
				{
					if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
					{
						DIR_Send=0x48;
						SPEED_send=0;
						TORQUE_send=0;
						motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
						motorset.stop=3;
					}
				}
                else if(motorset.DIR==2)
				{
					if(encoder.num==6)
					{
						if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_n)
                        {
							DIR_Send=0x48;
							SPEED_send=0;
							TORQUE_send=0;
                            motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
                            motorset.stop=3;
                        }
					}
                    else
					{
						if(motorset.DIR_MOTOR==motorset.DIR_MOTOR_s)
						{
							DIR_Send=0x48;
							SPEED_send=0;
							TORQUE_send=0;
							motorset.DIR_MOTOR=motorset.DIR_MOTOR_t;
							motorset.stop=4;
						}
					}
				}
			}
		}
        #endif
		choice_speed_line();
		abc=changeDIR();
		motorset.stop2=abc;
		changetorque(abc);
		if(flag_send==1)
		{
			abc=changeDIR();
			motorset.stop2=abc;
            changetorque(abc);
			flag_send=0;	
			USART3_Send.TURN=DIR_Send;
			USART3_Send.Speed_H=(SPEED_send&0xff);
			USART3_Send.Speed_L=((SPEED_send/256)&0xff);
			USART3_Send.Torque_H=(TORQUE_send&0xff);
			USART3_Send.Torque_L=((TORQUE_send/256)&0xff);
			USART3_Send.Null=0x03;
            
            /*1.故障处理，下发正转/反转码的时候，即启动阶段设置标志位，在其后的2s内，不针对其电流做堵转判断*/
            /*需要回溯对堵转功能的影响
            if(Buffer_Down[0] != USART3_Send.TURN)
            {
                if(USART3_Send.TURN == 0x48)
                {
                    motorset.flag_run = 2;
                }
                else
                {
                    motorset.flag_run = 1;
                }
            }*/
            
			Buffer_Down[0]=USART3_Send.TURN;
			Buffer_Down[1]=USART3_Send.Speed_H;
			Buffer_Down[2]=USART3_Send.Speed_L;
			Buffer_Down[3]=USART3_Send.Torque_H;
			Buffer_Down[4]=USART3_Send.Torque_L;
			Buffer_Down[5]=USART3_Send.Null;
			Buffer_Down[6]=(CRC_Compute(Buffer_Down,6)/256)&0xFF;
			Buffer_Down[7]=(CRC_Compute(Buffer_Down,6)%256)&0xFF;

			USART3_Send.CheckSum_H=(CRC_Compute(Buffer_Down,6)/256)&0xFF;
			USART3_Send.CheckSum_L=(CRC_Compute(Buffer_Down,6)%256)&0xFF;
			PowerSend((uint8_t *)&USART3_Send,(sizeof(USART3_Send)));	
			key_mlx90363.READ_run_1_old=key_mlx90363.READ_run_1;
		}
		flag_ok=0;
	}else
	{		
		if(flag_send==1)
		{
            flag_send=0;						
            if(flag_step1==1)
            {		
                if(flag_start==1)
                {									
                    if(flag_u25<4)
                    {					
						flag_send=0;
						USART3_Send.TURN=0x25;
						USART3_Send.Speed_H=0x7F;
						USART3_Send.Torque_H=0x58;
						if(flag_u25<2)	
						{
							USART3_Send.Speed_L=0xF5;
							USART3_Send.Torque_L=0xF5;
						}else
						if(flag_u25<4)
						{
							USART3_Send.Speed_L=0xC9;
							USART3_Send.Torque_L=0xC9;
						}
						USART3_Send.Null=0xAA;
                        
						Buffer_Down[0]=USART3_Send.TURN;    
						Buffer_Down[1]=USART3_Send.Speed_H;
						Buffer_Down[2]=USART3_Send.Speed_L;
						Buffer_Down[3]=USART3_Send.Torque_H;
						Buffer_Down[4]=USART3_Send.Torque_L;
						Buffer_Down[5]=USART3_Send.Null;
						Buffer_Down[6]=(CRC_Compute(Buffer_Down,6)/256)&0xFF;
						Buffer_Down[7]=(CRC_Compute(Buffer_Down,6)%256)&0xFF;
						USART3_Send.CheckSum_H=(CRC_Compute(Buffer_Down,6)/256)&0xFF;//0x67;
						USART3_Send.CheckSum_L=(CRC_Compute(Buffer_Down,6)%256)&0xFF;//0xD4;
						PowerSend((uint8_t *)&USART3_Send,(sizeof(USART3_Send)));
						flag_ok=1;
						flag_allstart1=1;
                    }
                }
                flag_u25++;
            }
            else if(flag_step2==1)
            {					
                if(flag_ok==1)
                {
                    USART3_Send.TURN=0x4A;
                    USART3_Send.Speed_H=0x00;
                    USART3_Send.Speed_L=0x00;
                    USART3_Send.Torque_H=0x00;
                    USART3_Send.Torque_L=0x00;
                    USART3_Send.Null=0x00;
                    
                    Buffer_Down[0]=USART3_Send.TURN;
                    Buffer_Down[1]=USART3_Send.Speed_H;
                    Buffer_Down[2]=USART3_Send.Speed_L;
                    Buffer_Down[3]=USART3_Send.Torque_H;
                    Buffer_Down[4]=USART3_Send.Torque_L;
                    Buffer_Down[5]=USART3_Send.Null;
                    Buffer_Down[6]=(CRC_Compute(Buffer_Down,6)/256)&0xFF;
                    Buffer_Down[7]=(CRC_Compute(Buffer_Down,6)%256)&0xFF;
    
                    USART3_Send.CheckSum_H=(CRC_Compute(Buffer_Down,6)/256)&0xFF;//0x67;
                    USART3_Send.CheckSum_L=(CRC_Compute(Buffer_Down,6)%256)&0xFF;//0xD4;
                    PowerSend((uint8_t *)&USART3_Send,(sizeof(USART3_Send)));
                    flag_start=0;
                    flag_allstart2=1;
                }
                uart3.ready_4A++;
            }
            else if(flag_step3==1)
            {	
                flag_start=0;				
                USART3_Send.TURN=0x48;
                USART3_Send.Speed_H=0x00;
                USART3_Send.Speed_L=0x00;
                USART3_Send.Torque_H=0x00;
                USART3_Send.Torque_L=0x00;
                USART3_Send.Null=0x03;
                
                Buffer_Down[0]=USART3_Send.TURN;
                Buffer_Down[1]=USART3_Send.Speed_H;
                Buffer_Down[2]=USART3_Send.Speed_L;
                Buffer_Down[3]=USART3_Send.Torque_H;
                Buffer_Down[4]=USART3_Send.Torque_L;
                Buffer_Down[5]=USART3_Send.Null;
                Buffer_Down[6]=(CRC_Compute(Buffer_Down,6)/256)&0xFF;
                Buffer_Down[7]=(CRC_Compute(Buffer_Down,6)%256)&0xFF;
    
                USART3_Send.CheckSum_H=(CRC_Compute(Buffer_Down,6)/256)&0xFF;//0x67;
                USART3_Send.CheckSum_L=(CRC_Compute(Buffer_Down,6)%256)&0xFF;//0xD4;
                PowerSend((uint8_t *)&USART3_Send,(sizeof(USART3_Send)));	
                flag_ok=0;
                flag_allstart3=1;
            }
		}
	}	
	if(1)
	{
		Current_BASE=(Current_STOP)&0x0FFF;
	}
}



UART0_RING_BUFFER_T rb0;
void UART0_IntReceive(void)
{
  uint8_t tmpc;
  uint32_t rLen;

  while (1) 
	{
    rLen = UART_Receive(LPC_USART0, &tmpc, 1, NONE_BLOCKING);
    if (rLen)
		{
      if (!__BUF_IS_FULL(rb0.rx_head,rb0.rx_tail)){
        rb0.rx[rb0.rx_head] = tmpc;
        __BUF_INCR(rb0.rx_head);
      }
    } else 
		{
      break;
    }
  }
}

uint32_t UART0Send( uint8_t *txbuf, uint8_t buflen)
{
  uint8_t *data = (uint8_t *) txbuf;
  uint32_t bytes = 0;
  UART_IntConfig(LPC_USART0, UART_INTCFG_THRE, DISABLE);
  while ((buflen > 0) && (!__BUF_IS_FULL(rb0.tx_head, rb0.tx_tail))) 
	{
    rb0.tx[rb0.tx_head] = *data;
    data++;
    __BUF_INCR(rb0.tx_head);
    bytes++;
    buflen--;
  }

  if (TxIntStat == RESET) 
	{
    UART0_IntTransmit();
  } else
	{
    
    UART_IntConfig(LPC_USART0, UART_INTCFG_THRE, ENABLE);
  }
  return bytes;
}

uint32_t UART0Receive( uint8_t *rxbuf, uint8_t buflen)
{
  uint8_t *data = (uint8_t *) rxbuf;
  uint32_t bytes = 0;
  UART_IntConfig(LPC_USART0, UART_INTCFG_RBR, DISABLE);
  while ((buflen > 0) && (!(__BUF_IS_EMPTY(rb0.rx_head, rb0.rx_tail)))) 
	{
    *data = rb0.rx[rb0.rx_tail];
    data++;
    __BUF_INCR(rb0.rx_tail);
    bytes++;
    buflen--;
  }
  UART_IntConfig(LPC_USART0, UART_INTCFG_RBR, ENABLE);

  return bytes;
}

void UART0_IntTransmit(void)
{
  UART_IntConfig(LPC_USART0, UART_INTCFG_THRE, DISABLE);

  while (UART_CheckBusy(LPC_USART0) == SET);

  while (!__BUF_IS_EMPTY(rb0.tx_head,rb0.tx_tail)) 
	{
    if (UART_Send(LPC_USART0, (uint8_t *)&rb0.tx[rb0.tx_tail], 1, NONE_BLOCKING)){
      __BUF_INCR(rb0.tx_tail);
    } else {
      break;
    }
  }
  if (__BUF_IS_EMPTY(rb0.tx_head, rb0.tx_tail)) 
	{
    UART_IntConfig(LPC_USART0, UART_INTCFG_THRE, DISABLE);
    TxIntStat = RESET;
  } else {
    TxIntStat = SET;
    UART_IntConfig(LPC_USART0, UART_INTCFG_THRE, ENABLE);
  }
}

UART0_RING_BUFFER_T enc;
int asdasd;
void UART0_IRQHandler(void)
{
		uint8_t res;
	static uint8_t cnt0;	
	uint32_t timeOut;
	while(1)
	{

		#if 1
		if (!(LPC_USART0->LSR & UART_LSR_RDR)) 
		{
			#if 1
			break;
			
			#endif
		} else
		{
					res=UART_ReceiveByte(LPC_USART0);
			encoder.RX_Timeout=0;
			if(encoder.RX_timeout_buf==0)
			{
					buffer0_ALL[cnt0++]=res;
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
		#endif
	}
}
void UART0_Init(void)
{
	UART_CFG_Type UARTConfigStruct;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	scu_pinmux(0xF ,10 , MD_PDN, FUNC1); 	                     
	scu_pinmux(0xF ,11 , MD_PLN|MD_EZI|MD_ZI, FUNC1); 	       
	UART_ConfigStructInit0(&UARTConfigStruct);
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	UART_Init((LPC_USARTn_Type *)LPC_USART0, &UARTConfigStruct);
	UART_FIFOConfig((LPC_USARTn_Type *)LPC_USART0, &UARTFIFOConfigStruct);
	UART_TxCmd((LPC_USARTn_Type *)LPC_USART0, ENABLE);
  UART_IntConfig((LPC_USARTn_Type *)LPC_USART0, UART_INTCFG_RBR, ENABLE);
  UART_IntConfig((LPC_USARTn_Type *)LPC_USART0, UART_INTCFG_RLS, ENABLE);

	NVIC_SetPriority(USART0_IRQn, ((0x03<<3)|0x01)); //
  NVIC_EnableIRQ( USART0_IRQn); 

}

uint32_t TestSend( uint8_t *txbuf, uint8_t buflen)
{
	uint32_t bToSend, bSent,  fifo_cnt;
	uint8_t *pChar = txbuf;
	bToSend = buflen;
	while(1)
	{
		if (!(LPC_USART0->LSR & UART_LSR_THRE))
		{
				break;
		}
		fifo_cnt = UART_TX_FIFO_SIZE;
		while (fifo_cnt && bToSend) 
		{
		UART_SendByte(LPC_USART0, (*pChar++));
		bToSend--;
		fifo_cnt--;
		bSent++;
		}
		
	}
}
Send_Message0 USART0_Send;
Send_Message0 USART0_Send_VC;
extern uint8_t buffer0[8];
extern uint16_t SPEED_Stand;
extern uint16_t TORQUE_Stand;
void c_entry_uart0 (void) 
{
		uint32_t check_A,check_B,check_C;
		uint16_t test,test2;
		float data;
		check_test();
		USART0_Send.tail_H=TEST_tail_H;
		USART0_Send.tail_L=TEST_tail_L;
		USART0_Send.OP=motorset.DIR_MOTOR;
		USART0_Send.ID=flag_u4a;
		USART0_Send.DATA_A=(Current_STOP/256);
		USART0_Send.DATA_B=(Current_STOP%256)&0xFF;
		USART0_Send.DATA_C=(Current_BASE/256);
		USART0_Send.DATA_D=(Current_BASE%256)&0xFF;
		TestSend((uint8_t *)&USART0_Send,(sizeof(USART0_Send)));
		if(buffer0[0]==0xA5)
		{
			if(buffer0[1]==0x5A)
			{
				test=buffer0[2];
				test2=buffer0[3];
				check_A=(buffer0[4]<<8)+(buffer0[5]);
				check_B=(buffer0[6]<<8)+(buffer0[7]);
				check_C=(check_A<<16)+(check_B);
				data=check_C;
				switch(test)
				{
            case 0x30: 
							{
									switch(test2)
									{
										case 0x01:	motorset.DIR_MOTOR=buffer0[4];
										break;
										case 0x02:	MOTOR_Torque_OPEN=data;
										break;
										case 0x03:	MOTOR_Torque_CLOSE=data;
										break;
										case 0x04:	MOTOR_Speed_CLOSE=data;
										break;
										case 0x05:	MOTOR_Speed_OPEN=data;
										break;
										case 0x06:	MOTOR_Speed=2;
										break;
										case 0x07:	motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
										break;
										case 0x08:	MOTOR_Speed=2;
										break;
										case 0x09:	motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
										break;
										case 0x0a:	MOTOR_Speed=2;
										break;
										default: ;
									}
							}
            break;
            default: ;
				}

			}
	}	
}

void motor_dir(uint8_t DIR)
{
	switch(DIR)
	{
		case 0x01:	motorset.DIR_MOTOR=motorset.DIR_MOTOR_n;
		break;
		case 0x02:	motorset.DIR_MOTOR=motorset.DIR_MOTOR_s;
		break;
		default: ;
	}
}
	



