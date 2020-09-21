#include "MLX90363.h"
#include "SPI.h"
#include "Handler.h"
#include "math.h"
#include  "datafigures.h"
#define PI 3.1415926
#define RAD 180
#define Q_one 1
#define Q_two 2
#define Q_THR 3
#define Q_FOU 4
int DEGREE_OLD;  //ԭ�ȽǶ�
char key_old;    //����״̬
char u8_spi_read_buffer[8],u8_spi_write_buffer[8];
char u8_SPI_ReadWrite_buffer[8];
float X_sq_old,Y_sq_old;  //ԭ��XYλ��

void Init_MLX90363(void)
{
		SSP_CFG_Type SSP_ConfigStruct;
		scu_pinmux(0x1, 19, MD_PLN_FAST, FUNC1); 
		scu_pinmux(0x0,  0, MD_PLN_FAST, FUNC1); 
		scu_pinmux(0x0,  1, MD_PLN_FAST, FUNC1); 
		scu_pinmux(0xE, 15, MD_PDN,      FUNC4); 

		GPIO_SetDir(MLX_GPIO,(1 << MLX_GPIO_PIN), 1); 
		SSP_ConfigStructInit_mlx90363(&SSP_ConfigStruct);
		SSP_Init(LPC_SSP1, &SSP_ConfigStruct);
		SSP_Cmd(LPC_SSP1, ENABLE);
		GPIO_SetValue(MLX_GPIO,(1<<MLX_GPIO_PIN));
}

#if 1
void c_entry_mlx_I(void)
{
    int i=0;
	int quadrant=0;
    float degree,degree_new;
    float X,Y,Z;
	float X_now,Y_now,Z_now;
	float X_sq,Y_sq,Z_sq;
		u8_spi_write_buffer[0] = 0x00;
		u8_spi_write_buffer[1] = 0x00;
		u8_spi_write_buffer[2] = 0xFF;
		u8_spi_write_buffer[3] = 0xFF;
		u8_spi_write_buffer[4] = 0x00;
		u8_spi_write_buffer[5] = 0x00;
		u8_spi_write_buffer[6] = 0x53;
		u8_spi_write_buffer[7] =ComputeCRC(0x00,0x00,0xFF,0xFF,0x00, 0x00, 0x53);
		GPIO_ClearValue(MLX_GPIO,(1<<MLX_GPIO_PIN));
		wait_ms(20);
		for ( i = 0; i < 8; i++)
		{
			u8_spi_read_buffer[i] = SPI1_ReadWrite(u8_spi_write_buffer[i]);
		}
		GPIO_SetValue(MLX_GPIO,(1<<MLX_GPIO_PIN));
        wait_ms(200);
		wait_ms(200);
		wait_ms(200);
		wait_ms(200);
		wait_ms(200);
		wait_ms(200);
		wait_ms(200);
		wait_ms(200);
		wait_ms(200);
		wait_ms(200);
		wait_ms(200);
		wait_ms(200);
		wait_ms(200);
		u8_spi_write_buffer[0] = 0x00;
		u8_spi_write_buffer[1] = 0x00;
		u8_spi_write_buffer[2] = 0xAA;
		u8_spi_write_buffer[3] = 0xAA;
		u8_spi_write_buffer[4] = 0x00;
		u8_spi_write_buffer[5] = 0x00;
		u8_spi_write_buffer[6] = 0xD0;
		u8_spi_write_buffer[7] = 0xAB;

		GPIO_ClearValue(MLX_GPIO,(1<<MLX_GPIO_PIN));
		for ( i = 0; i < 8; i++)
		{
			u8_spi_read_buffer[i] = SPI1_ReadWrite(u8_spi_write_buffer[i]);
		}
		X_sq=(int16_t)((((u8_spi_read_buffer[1]<<8)|u8_spi_read_buffer[0])<<2)&0xFFFF);
		Y_sq=(int16_t)((((u8_spi_read_buffer[3]<<8)|u8_spi_read_buffer[2])<<2)&0xFFFF);
		GPIO_SetValue(MLX_GPIO,(1<<MLX_GPIO_PIN));
		degree=(atan2(Y_sq,X_sq)*RAD)/PI;

        DEGREE_OLD=degree;
		
		X_sq_old =X_sq;
		Y_sq_old =Y_sq;
	
}

char flag_key_enter_bef=0;
char flag_key_tab=0;
char flag_key_escape=0;
char flag_key_enter=0;

char c_entry_mlx(void)
{
    int i=0;
	int j;
	int quadrant=0;
	int key=8;
	float key_abs_old,key_abs_new;
	int degree;
	int16_t degree_new,degree_diff,degree_diff2;
    float X,Y,Z;
	float X_now1,Y_now1,Z_now1;
	float X_new,Y_new,Z_new;
    float T,S,jiaodu;
	int16_t X_sq,Y_sq;
	

		u8_spi_write_buffer[0] = 0x00;
		u8_spi_write_buffer[1] = 0x00;
		u8_spi_write_buffer[2] = 0xFF;
		u8_spi_write_buffer[3] = 0xFF;
		u8_spi_write_buffer[4] = 0x00;
		u8_spi_write_buffer[5] = 0x00;
		u8_spi_write_buffer[6] = 0x93;
		u8_spi_write_buffer[7] =ComputeCRC(0x00, 0x00,0xFF,0xFF,0x00, 0x00, 0x93);
		GPIO_ClearValue(MLX_GPIO,(1<<MLX_GPIO_PIN));
		for ( i = 0; i < 8; i++)
		{
			u8_spi_read_buffer[i] = SPI1_ReadWrite(u8_spi_write_buffer[i]);
		}
		GPIO_SetValue(MLX_GPIO,(1<<MLX_GPIO_PIN));
		wait_ms(5);
		wait_ms(5);
		u8_spi_write_buffer[0] = 0x00;
		u8_spi_write_buffer[1] = 0x00;
		u8_spi_write_buffer[2] = 0xAA;
		u8_spi_write_buffer[3] = 0xAA;
		u8_spi_write_buffer[4] = 0x00;
		u8_spi_write_buffer[5] = 0x00;
		u8_spi_write_buffer[6] = 0xD0;
		u8_spi_write_buffer[7] = 0xAB;
		GPIO_ClearValue(MLX_GPIO,(1<<MLX_GPIO_PIN));
		for ( i = 0; i < 8; i++)
		{
			u8_spi_read_buffer[i] = SPI1_ReadWrite(u8_spi_write_buffer[i]);
		}
		
		X_sq=(int16_t)((((u8_spi_read_buffer[1]<<8)|u8_spi_read_buffer[0])<<2)&0xFFFF);
		Y_sq=(int16_t)((((u8_spi_read_buffer[3]<<8)|u8_spi_read_buffer[2])<<2)&0xFFFF);
		GPIO_SetValue(MLX_GPIO,(1<<MLX_GPIO_PIN));
		wait_ms(4);
        
        
		degree=(atan2(Y_sq,X_sq)*RAD)/PI;
		degree_diff=degree-DEGREE_OLD;
		if(degree_diff>180)
		{
			degree_new=degree-360;			
		}else
		if(degree_diff<-180)
		{
			degree_new=degree+360;			
		}else
		{
			degree_new=degree;	
		}
		degree_diff2=degree_new-DEGREE_OLD;

        
		if((degree_diff2)>18&&(degree_diff2<180))
		{
			key=KEY_UP;  //17.��ť����ת
		}else
		if((degree_diff2<-18)&&(degree_diff2>-180))
		{
			key=KEY_DOWN;  //19.��ť����ת
		}else
		{
			X_new=X_sq*X_sq+Y_sq*Y_sq;
			Y_new=X_sq_old*X_sq_old+Y_sq_old*Y_sq_old;
			Z_new=abs(X_new-Y_new);
			if((X_new>30000000))
			{
				if(key_old==KEY_ESCAPE)
				{
					key=KEY_ENTER_BEF;  //15.��ţ̌��
					printf("\r\n X_new: %f  key: %d ",X_new,key);
				}else
				{
					key=KEY_TAB;  //9.��ţ̌��
					if(key_old==KEY_TAB)
					{
					
					}else
					{
					printf("\r\n X_new: %f  key: %d ",X_new,key);
					}
				}
			}else
			if((X_new<30000000))
			{
				if((key_old==KEY_ENTER_BEF)||(key_old==KEY_TAB))
				{
					key=KEY_ENTER;  //13.����ȥ����
					printf("\r\n X_new: %f  key: %d ",X_new,key);
				}else
				{
					key=KEY_ESCAPE;  //8.��ţ̌��״̬
				}
			}else
			{
				key=KEY_ESCAPE;
			}
		}
        #if 1
		if(key==KEY_ESCAPE)
		{
			key_old=key;
		}else
		{
			DEGREE_OLD=degree;
			X_sq_old =X_sq;
			Y_sq_old =Y_sq;
			key_old=key;
		}
		#endif
		
return key;		


}





#endif
