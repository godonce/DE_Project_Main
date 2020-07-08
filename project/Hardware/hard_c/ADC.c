#include "ADC.h"
#include "SPI.h"
#include "Handler.h"
#include  "datafigures.h"
char u8_adc_read_buffer[8],u8_adc_write_buffer[8];
volatile float f32_adc_degrees;
volatile int u16_adc_lsb,u16_adc;
const float f32_ad = 1.0;

void Init_ADC(void)
{
		SSP_CFG_Type SSP_ConfigStruct;
		scu_pinmux(0x3, 0, MD_PLN_FAST, FUNC4);  
		scu_pinmux(0x9, 1, MD_PLN_FAST, FUNC7);  
		scu_pinmux(0x9, 2, MD_PLN_FAST, FUNC7);  
		scu_pinmux(0xE, 1, MD_PDN,      FUNC4);  
		GPIO_SetDir(ADC_GPIO,(1 << ADC_GPIO_PIN), 1);  		
		SSP_ConfigStructInit(&SSP_ConfigStruct);
		SSP_Init(LPC_SSP0, &SSP_ConfigStruct);
		SSP_Cmd(LPC_SSP0, ENABLE);
	states_spi0(close_spi_init);
}
float c_entry_ADC(void)
{
		int i;
	u8_adc_write_buffer[0] = 0xC6;
		u8_adc_write_buffer[1] = 0x83;
	states_spi0(AI1_spi_init);
		for (i = 0; i < 2; i++)
		{
			u8_adc_read_buffer[i] = SPI0_ReadWrite(u8_adc_write_buffer[i]);
		}
	states_spi0(close_spi_init);
		Delay();
		wait_ms(10);	
		u16_adc_lsb = (u8_adc_read_buffer[1] & 0x0F) << 8;
		u16_adc_lsb = u16_adc_lsb + u8_adc_read_buffer[0];
		u16_adc_lsb = u16_adc_lsb>>4;
		u16_adc=u16_adc_lsb*f32_ad;
		f32_adc_degrees = (u16_adc)/4096;
		f32_adc_degrees=f32_adc_degrees*3.3;
		return f32_adc_degrees;
	}

