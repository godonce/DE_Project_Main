#include "test.h"
char CRCArray[] =
	{
	0x00, 0x2F, 0x5E, 0x71, 0xBC, 0x93, 0xE2, 0xCD, 0x57, 0x78, 0x09, 0x26,
	0xEB, 0xC4, 0xB5, 0x9A, 0xAE, 0x81, 0xF0, 0xDF, 0x12, 0x3D, 0x4C, 0x63,
	0xF9, 0xD6, 0xA7, 0x88, 0x45, 0x6A, 0x1B, 0x34, 0x73, 0x5C, 0x2D, 0x02,
	0xCF, 0xE0, 0x91, 0xBE, 0x24, 0x0B, 0x7A, 0x55, 0x98, 0xB7, 0xC6, 0xE9,
	0xDD, 0xF2, 0x83, 0xAC, 0x61, 0x4E, 0x3F, 0x10, 0x8A, 0xA5, 0xD4, 0xFB,
	0x36, 0x19, 0x68, 0x47, 0xE6, 0xC9, 0xB8, 0x97, 0x5A, 0x75, 0x04, 0x2B,
	0xB1, 0x9E, 0xEF, 0xC0, 0x0D, 0x22, 0x53, 0x7C, 0x48, 0x67, 0x16, 0x39,
	0xF4, 0xDB, 0xAA, 0x85, 0x1F, 0x30, 0x41, 0x6E, 0xA3, 0x8C, 0xFD, 0xD2,
	0x95, 0xBA, 0xCB, 0xE4, 0x29, 0x06, 0x77, 0x58, 0xC2, 0xED, 0x9C, 0xB3,
	0x7E, 0x51, 0x20, 0x0F, 0x3B, 0x14, 0x65, 0x4A, 0x87, 0xA8, 0xD9, 0xF6,
	0x6C, 0x43, 0x32, 0x1D, 0xD0, 0xFF, 0x8E, 0xA1, 0xE3, 0xCC, 0xBD, 0x92,
	0x5F, 0x70, 0x01, 0x2E, 0xB4, 0x9B, 0xEA, 0xC5, 0x08, 0x27, 0x56, 0x79,
	0x4D, 0x62, 0x13, 0x3C, 0xF1, 0xDE, 0xAF, 0x80, 0x1A, 0x35, 0x44, 0x6B,
	0xA6, 0x89, 0xF8, 0xD7, 0x90, 0xBF, 0xCE, 0xE1, 0x2C, 0x03, 0x72, 0x5D,
	0xC7, 0xE8, 0x99, 0xB6, 0x7B, 0x54, 0x25, 0x0A, 0x3E, 0x11, 0x60, 0x4F,
	0x82, 0xAD, 0xDC, 0xF3, 0x69, 0x46, 0x37, 0x18, 0xD5, 0xFA, 0x8B, 0xA4,
	0x05, 0x2A, 0x5B, 0x74, 0xB9, 0x96, 0xE7, 0xC8, 0x52, 0x7D, 0x0C, 0x23,
	0xEE, 0xC1, 0xB0, 0x9F, 0xAB, 0x84, 0xF5, 0xDA, 0x17, 0x38, 0x49, 0x66,
	0xFC, 0xD3, 0xA2, 0x8D, 0x40, 0x6F, 0x1E, 0x31, 0x76, 0x59, 0x28, 0x07,
	0xCA, 0xE5, 0x94, 0xBB, 0x21, 0x0E, 0x7F, 0x50, 0x9D, 0xB2, 0xC3, 0xEC,
	0xD8, 0xF7, 0x86, 0xA9, 0x64, 0x4B, 0x3A, 0x15, 0x8F, 0xA0, 0xD1, 0xFE,
	0x33, 0x1C, 0x6D, 0x42 
};

char ComputeCRC(char Byte0, char Byte1, char Byte2, char Byte3,char Byte4, char Byte5, char Byte6)
{
	char CRC = 0xFF;
	CRC = CRCArray[CRC ^ Byte0];             //按位异或
	CRC = CRCArray[CRC ^ Byte1];
	CRC = CRCArray[CRC ^ Byte2];
	CRC = CRCArray[CRC ^ Byte3];
	CRC = CRCArray[CRC ^ Byte4];
	CRC = CRCArray[CRC ^ Byte5];
	CRC = CRCArray[CRC ^ Byte6];
	CRC = ~CRC;
	return CRC;
}
int c_entry_test1(void) 
{
//{
//		int i=0;
//		char u8_spi_read_buffer[8];
//		char u8_SPI_ReadWrite_buffer[8];
//		volatile float f32_alpha_angle_degrees, f32_beta_angle_degrees;
//		volatile int u16_alpha_angle_lsb, u16_beta_angle_lsb;
//		volatile char RByte0, RByte1, RByte2, RByte3, RByte4, RByte5, RByte6, RByte7;
//		char Addr_102A_LSB, Addr_102A_MSB, Addr_1022_LSB, Addr_1022_MSB,Addr_1024_LSB, Addr_1024_MSB;
//		char u8_error_lsb, u8_rollcnt_dec, u8_virtualgain_dec, u8_crc_dec;
//		char u8_pass = 0;
//		const float f32_lsb_to_dec_degrees = 0.02197;
//	
//		SPI_Init(LPC_SSP0);	
//		scu_pinmux(LED2_PORT ,LED2_PIN , MD_PDN, FUNC4);
//		GPIO_SetDir(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN), 0);		
//		
//		//GPIO_ClearValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));
//		GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));			
//		//NTT:初始化磁场传感器	GET1
//		RByte0 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte1 = SPI_ReadWrite(LPC_SSP0,0x01);          //RST=0(byte1[0]=0) reset the rolling counter attached to the regular data packets
//		RByte2 = SPI_ReadWrite(LPC_SSP0,0xFF);          //timeout value (byte2+byte3) 
//		RByte3 = SPI_ReadWrite(LPC_SSP0,0xFF);
//		RByte4 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte5 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte6 = SPI_ReadWrite(LPC_SSP0,0x53);          //GET1(13d)
//		RByte7 = SPI_ReadWrite(LPC_SSP0,ComputeCRC(0x00, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x53));
//		wait_ms(1);		
//	//	GET1-->MemoryRead-->MemoryRead(or DiagDetails)
//	//	GET1-->DiagDetails-->all commands
//		for (i = 0; i <= 1; i++)
//		//while(1)
//		{
//			
//			GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//			RByte0 = SPI_ReadWrite(LPC_SSP0,0x2A);//Memory location 0x102A
//			RByte1 = SPI_ReadWrite(LPC_SSP0,0x10);
//			RByte2 = SPI_ReadWrite(LPC_SSP0,0x00); //Memory location 0x1000
//			RByte3 = SPI_ReadWrite(LPC_SSP0,0x10);
//			RByte4 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte5 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte6 = SPI_ReadWrite(LPC_SSP0,0xC1);     //AFETER get1 IS MemoryRead  0x01  ???
//			RByte7 = SPI_ReadWrite(LPC_SSP0,ComputeCRC(0x2A, 0x10,0X00,/* 0x32,*/ 0x10, 0x00, 0x00, 0xC1));
//			
//			GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//			wait_ms(1);
//		}
//	
//		//Set: MAPXYZ to 0, Enable 3D mode
//		Addr_102A_LSB = (RByte0 & 0xF0) ^ 0x08;
//		Addr_102A_MSB = RByte1;
//		//Set Kalpha to 1.4
//		Addr_1022_LSB = 0x33;
//		Addr_1022_MSB = 0xB3;
//		//Set Kbeta to 1.4
//		Addr_1024_LSB = 0x33;
//		Addr_1024_MSB = 0xB3;
///*		
//		GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//		RByte0 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte1 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte2 = SPI_ReadWrite(LPC_SSP0,0xAA);
//		RByte3 = SPI_ReadWrite(LPC_SSP0,0xAA);
//		RByte4 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte5 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte6 = SPI_ReadWrite(LPC_SSP0,0xD0);               //NOP Command and NOP Answer
//		//RByte7 = SPI_ReadWrite(LPC_SSP0,0xAB); 
//		RByte7 = SPI_ReadWrite(LPC_SSP0,ComputeCRC(0x00, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0xD0));
//		
//		//GPIO_ClearValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));
//		GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//			
//		wait_ms(10);
//		for ( j = 0; j <= 2; j++)
//		{
//			GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));			
//			//MemoryWrite message    EEWrite Message
//			if (u8_pass == 0)
//			{
//				RByte0 = SPI_ReadWrite(LPC_SSP0,0x00);
//				RByte1 = SPI_ReadWrite(LPC_SSP0,0x2A);
//				RByte2 = SPI_ReadWrite(LPC_SSP0,0x45);
//				RByte3 = SPI_ReadWrite(LPC_SSP0,0x8F);
//				RByte4 = SPI_ReadWrite(LPC_SSP0,Addr_102A_LSB);
//				RByte5 = SPI_ReadWrite(LPC_SSP0,Addr_102A_MSB);
//				RByte6 = SPI_ReadWrite(LPC_SSP0,0xC3);                // EEWrite MOSI Message  Table 38
//				RByte7 = SPI_ReadWrite(LPC_SSP0,ComputeCRC(0x00, 0x2A, 0x45, 0x8F, Addr_102A_LSB,Addr_102A_MSB, 0xC3));
//			}else			 
//			if (u8_pass == 1)
//			{
//				RByte0 = SPI_ReadWrite(LPC_SSP0,0x00);
//				RByte1 = SPI_ReadWrite(LPC_SSP0,0x22);
//				RByte2 = SPI_ReadWrite(LPC_SSP0,0xDD);
//				RByte3 = SPI_ReadWrite(LPC_SSP0,0xFB);
//				RByte4 = SPI_ReadWrite(LPC_SSP0,Addr_1022_LSB);
//				RByte5 = SPI_ReadWrite(LPC_SSP0,Addr_1022_MSB);
//				RByte6 = SPI_ReadWrite(LPC_SSP0,0xC3);                // EEWrite MOSI Message  Table 38
//				RByte7 = SPI_ReadWrite(LPC_SSP0,ComputeCRC(0x00, 0x22, 0xDD, 0xFB, Addr_1022_LSB,
//				Addr_1022_MSB, 0xC3));
//			}else 
//			if (u8_pass == 2)
//			{
//				RByte0 = SPI_ReadWrite(LPC_SSP0,0x00);
//				RByte1 = SPI_ReadWrite(LPC_SSP0,0x24);
//				RByte2 = SPI_ReadWrite(LPC_SSP0,0xC9);
//				RByte3 = SPI_ReadWrite(LPC_SSP0,0x9F);
//				RByte4 = SPI_ReadWrite(LPC_SSP0,Addr_1024_LSB);
//				RByte5 = SPI_ReadWrite(LPC_SSP0,Addr_1024_MSB);
//				RByte6 = SPI_ReadWrite(LPC_SSP0,0xC3);                   // EEWrite MOSI Message  Table 38
//				RByte7 = SPI_ReadWrite(LPC_SSP0,ComputeCRC(0x00, 0x24, 0xC9, 0x9F, Addr_1024_LSB,
//				Addr_1024_MSB, 0xC3));
//			}
//			GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//			wait_ms(10); //Transmit readchallenge message, keep result for xor operation
//			GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//			////Message General Structure   EEWrite ReadChallenge MOSI Message
//			RByte0 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte1 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte2 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte3 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte4 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte5 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte6 = SPI_ReadWrite(LPC_SSP0,0xCF);       //EEWrite ReadChallenge MOSI Message   Table 40
//			RByte7 = SPI_ReadWrite(LPC_SSP0,ComputeCRC(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCF));
//			//GPIO_ClearValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));
//			GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//			
//			wait_ms(10);//Transmit readchallenge message, keep result for xor operation
//			GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//			//GPIO_SetValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));	
//			
//			SPI_ReadWrite(LPC_SSP0,0x00);
//			SPI_ReadWrite(LPC_SSP0,0x00);
//			SPI_ReadWrite(LPC_SSP0,RByte2 ^ 0x34);
//			SPI_ReadWrite(LPC_SSP0,RByte3 ^ 0x12);
//			SPI_ReadWrite(LPC_SSP0,~(RByte2 ^ 0x34));
//			SPI_ReadWrite(LPC_SSP0,~(RByte3 ^ 0x12));
//			SPI_ReadWrite(LPC_SSP0,0xC5);                          //Table 42  outtime
//			RByte7 = SPI_ReadWrite(LPC_SSP0,ComputeCRC(0x00, 0x00, RByte2 ^ 0x34, RByte3 ^ 0x12,
//			~(RByte2 ^ 0x34), ~(RByte3 ^ 0x12), 0xC5));
//			//GPIO_ClearValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));
//			GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//			
//			wait_ms(10); //delay for writing EEPROM
//			GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//			
//			RByte0 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte1 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte2 = SPI_ReadWrite(LPC_SSP0,0xAA);
//			RByte3 = SPI_ReadWrite(LPC_SSP0,0xAA);
//			RByte4 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte5 = SPI_ReadWrite(LPC_SSP0,0x00);
//			RByte6 = SPI_ReadWrite(LPC_SSP0,0xD0);            //NOP Table 23
//			RByte7 = SPI_ReadWrite(LPC_SSP0,ComputeCRC(0x00, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0xD0));
//			
//			//GPIO_ClearValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));
//			GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//			
//			u8_pass++;
//		//	printf("Error code (1=success): %02X\r\n", RByte0);
//		}
//		wait_ms(10);
//		GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//		//GPIO_SetValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));	
//		
//		RByte0 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte1 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte2 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte3 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte4 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte5 = SPI_ReadWrite(LPC_SSP0,0x00);
//		RByte6 = SPI_ReadWrite(LPC_SSP0,0xEF);           //reboot  Table 45
//		RByte7 = SPI_ReadWrite(LPC_SSP0,ComputeCRC(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEF));
//		////ss1 = 1;
//		//GPIO_ClearValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));
//		GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//		//wait_ms(30);
//			
//*/
//		while (1)
//		{
//			u8_SPI_ReadWrite_buffer[0] = 0x00;
//			u8_SPI_ReadWrite_buffer[1] = 0x00;
//			u8_SPI_ReadWrite_buffer[2] = 0xFF;
//			u8_SPI_ReadWrite_buffer[3] = 0xFF;
////			u8_SPI_ReadWrite_buffer[0] = 0x26;
////			u8_SPI_ReadWrite_buffer[1] = 0x10;
////			u8_SPI_ReadWrite_buffer[2] = 0x00;
////			u8_SPI_ReadWrite_buffer[3] = 0x10;
//			u8_SPI_ReadWrite_buffer[4] = 0x00;
//			u8_SPI_ReadWrite_buffer[5] = 0x00;
//			u8_SPI_ReadWrite_buffer[6] = 0xD3;//0x53;//0xC1;                 //Table 11  mode=1  GET1 MOSI Message 
//			//u8_SPI_ReadWrite_buffer[7] = 0x0C;
//			u8_SPI_ReadWrite_buffer[7]= ComputeCRC(0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xD3);
//		
//			GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//			//GPIO_SetValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));	
//			
//			for (i = 0; i < 8; i++)
//			{
//				u8_spi_read_buffer[i] = SPI_ReadWrite(LPC_SSP0,u8_SPI_ReadWrite_buffer[i]);
//			}
//			
//u16_alpha_angle_lsb = (u8_spi_read_buffer[1] & 0x3F) << 8;
//			//add LSb of angle
//			u16_alpha_angle_lsb = u16_alpha_angle_lsb + u8_spi_read_buffer[0];
//			//convert to decimal degrees
//			f32_alpha_angle_degrees = u16_alpha_angle_lsb * f32_lsb_to_dec_degrees;
//			//Extract and convert the beta angle to degrees
//			//remove error bits and shift to high byte
//			u16_beta_angle_lsb = (u8_spi_read_buffer[3] & 0x3F) << 8;
//			//add LSb of angle
//			u16_beta_angle_lsb = u16_beta_angle_lsb + u8_spi_read_buffer[2];
//			//convert to decimal degrees
//			f32_beta_angle_degrees = u16_beta_angle_lsb * f32_lsb_to_dec_degrees;
//			//Extract the error bits
//			u8_error_lsb = u8_spi_read_buffer[1] >> 6;
//			//Extract the CRC
//			u8_crc_dec = u8_spi_read_buffer[7];
//			//Extract the virtual gain byte
//			u8_virtualgain_dec = u8_spi_read_buffer[4];
//			//Extract the rolling counter
//			u8_rollcnt_dec = u8_spi_read_buffer[6] & 0x3F;

//	/*		
//			GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//			//GPIO_SetValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));	
//			
//			wait_ms(10);
//			
//			u8_SPI_ReadWrite_buffer[0] = 0x00;
//			u8_SPI_ReadWrite_buffer[1] = 0x00;
//			u8_SPI_ReadWrite_buffer[2] = 0xAA;        //KEY[7:0]
//			u8_SPI_ReadWrite_buffer[3] = 0xAA;        //KEY[15:8]
//			u8_SPI_ReadWrite_buffer[4] = 0x00;
//			u8_SPI_ReadWrite_buffer[5] = 0x00;
//			u8_SPI_ReadWrite_buffer[6] = 0xD0;            //NOP Command and NOP Answer
//			u8_SPI_ReadWrite_buffer[7]= SPI_ReadWrite(LPC_SSP0,ComputeCRC(0x00, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0xD0));
//			
//			GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//			//GPIO_SetValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));	
//			
//			for (i = 0; i < 8; i++)
//			{
//				u8_spi_read_buffer[i] = SPI_ReadWrite(LPC_SSP0,u8_SPI_ReadWrite_buffer[i]);	
//			}
//			GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//			//GPIO_SetValue(EN_GPIO_PORT,(1<<EN_GPIO_PIN));	
//	
//			//Extract and convert the alpha angle to degrees
//			//remove error bits and shift to high byte
//			
//			//Send results to serial port
////			printf("Alpha Angle (LSb): %d\r\n", u16_alpha_angle_lsb);
////			printf("Alpha Angle (Dec): %2.2f\r\n", f32_alpha_angle_degrees);
////			printf("Beta Angle (LSb): %d\r\n", u16_beta_angle_lsb);
////			printf("Beta Angle (Dec): %2.2f\r\n", f32_beta_angle_degrees);
////			printf("Error Bits (Dec): %d\r\n", u8_error_lsb);
////			printf("CRC (Dec): %d\r\n", u8_crc_dec);
////			printf("Virtual Gain (Dec): %d\r\n", u8_virtualgain_dec);
////			printf("Rolling Counter (Dec): %d\r\n", u8_rollcnt_dec);
//			///wait(0.5);
//			*/
//			wait_ms(20);
//			
//		}
		return 0;
}

	
int c_entry_test2(void)
{
//	int i,j;
//	char u8_spi_read_buffer[8];
//	char u8_SPI_ReadWrite_buffer[8];
//volatile	float f32_angle_degrees;
//volatile	unsigned int u16_angle_lsb;
//	char u8_error_lsb;
//	char u8_rollcnt_dec;
//	char u8_virtualgain_dec;
//	char u8_crc_dec;
//	//360 degrees is mapped to 14 bits = 360/2^14 = 0.02197
//	const float f32_lsb_to_dec_degrees = 0.02197;

//	
//	SPI_Init(LPC_SSP0);
//	
//		//scu_pinmux(EN_PORT ,EN_PIN , MD_PDN, FUNC4);
//		//GPIO_SetDir(EN_GPIO_PORT,(1<<EN_GPIO_PIN), 0);	
//		scu_pinmux(LED2_PORT ,LED2_PIN , MD_PDN, FUNC4);
//		GPIO_SetDir(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN), 1);
//	
//	//GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//	GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//		
//	while (1){
//	//issue GET1 message
//	u8_SPI_ReadWrite_buffer[0] = 0x00;
//	u8_SPI_ReadWrite_buffer[1] = 0x00;
//	u8_SPI_ReadWrite_buffer[2] = 0xFF;
//	u8_SPI_ReadWrite_buffer[3] = 0xFF;
//	u8_SPI_ReadWrite_buffer[4] = 0x00;
//	u8_SPI_ReadWrite_buffer[5] = 0x00;
//	u8_SPI_ReadWrite_buffer[6] = 0x13;
//	u8_SPI_ReadWrite_buffer[7] = 0xEA;
//	//ss1 = 0;
//	GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//	//GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//	for ( i = 0; i < 8; i++)
//	{
//		u8_spi_read_buffer[i] = SPI_ReadWrite(LPC_SSP0,u8_SPI_ReadWrite_buffer[i]);
//		
//	}
//	//ss1 = 1;
//	//GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//	GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//	wait_ms(1);
//	//issue NOP message
//	u8_SPI_ReadWrite_buffer[0] = 0x00;
//	u8_SPI_ReadWrite_buffer[1] = 0x00;
//	u8_SPI_ReadWrite_buffer[2] = 0xAA;
//	u8_SPI_ReadWrite_buffer[3] = 0xAA;
//	u8_SPI_ReadWrite_buffer[4] = 0x00;
//	u8_SPI_ReadWrite_buffer[5] = 0x00;
//	u8_SPI_ReadWrite_buffer[6] = 0xD0;
//	u8_SPI_ReadWrite_buffer[7] = 0xAB;
//	//ss1 = 0;
//	GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//	//GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//	for ( i = 0; i < 8; i++){
//	u8_spi_read_buffer[i] = SPI_ReadWrite(LPC_SSP0,u8_SPI_ReadWrite_buffer[i]);
//	}
//	//ss1 = 1;
//	//GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
//	GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
//	
//	//Extract and convert the angle to degrees
//	//remove error bits and shift to high byte
//	u16_angle_lsb = (u8_spi_read_buffer[1] & 0x3F) << 8;
//	//add LSB of angle
//	u16_angle_lsb = u16_angle_lsb + u8_spi_read_buffer[0];
//	//convert to decimal degrees
//	f32_angle_degrees = u16_angle_lsb * f32_lsb_to_dec_degrees;
//	//Extract the error bits
//	u8_error_lsb = u8_spi_read_buffer[1] >> 6;
//	//Extract the CRC
//	u8_crc_dec = u8_spi_read_buffer[7];
//	//Extract the virtual gain byte
//	u8_virtualgain_dec = u8_spi_read_buffer[4];
//	//Extract the rolling counter
//	u8_rollcnt_dec = u8_spi_read_buffer[6] & 0x3F;
//	//Send results to serial port
////	pc.printf("Angle (LSb): %d\r\n", u16_angle_lsb);
////	pc.printf("Angle (Dec): %2.2f\r\n", f32_angle_degrees);
////	pc.printf("Error Bits (Dec): %d\r\n", u8_error_lsb);
////	pc.printf("CRC (Dec): %d\r\n", u8_crc_dec);
////	pc.printf("Virtual Gain (Dec): %d\r\n", u8_virtualgain_dec);
////	pc.printf("Rolling Counter (Dec): %d\r\n", u8_rollcnt_dec);
//	wait_ms(10);
//	}
return 0;
}
