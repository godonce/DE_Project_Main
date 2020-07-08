#include "temperature.h"

#define _ADC_INT                ADC_ADINTEN0
#define _ADC_CHANNEL            ADC_CHANNEL_1
#define DMA_SIZE                1
uint32_t adc_value;
GPDMA_Channel_CFG_Type GPDMACfg;

__IO uint32_t Channel0_TC;

__IO uint32_t Channel0_Err;
void DMA_IRQHandler (void)
{
	if (GPDMA_IntGetStatus(GPDMA_STAT_INT, 1)){
		if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, 1)){
			GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, 1);
				Channel0_TC++;
		}
		if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, 1)){
			GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, 1);
			Channel0_Err++;
		}
	}
}

void Init_DMA(void)
{
	
  LPC_SCU_Type *p;
	
	ADC_Init(LPC_ADC0, 200000, 10);
  ADC_IntConfig(LPC_ADC0,_ADC_INT, ENABLE);
  ADC_ChannelCmd(LPC_ADC0,_ADC_CHANNEL, ENABLE);
		NVIC_DisableIRQ(DMA_IRQn);
	NVIC_SetPriority(DMA_IRQn, ((0x02<<3)|0x02));
  GPDMA_Init();
  GPDMACfg.ChannelNum = 1;
  GPDMACfg.SrcMemAddr = 0;
  GPDMACfg.DstMemAddr = (uint32_t) &adc_value;
  GPDMACfg.TransferSize = DMA_SIZE;
  GPDMACfg.TransferWidth = 0;
  GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA;
  GPDMACfg.SrcConn = GPDMA_CONN_ADC_0;
  GPDMACfg.DstConn = 0;
  GPDMACfg.DMALLI = 0;
  GPDMA_Setup(&GPDMACfg);
	
}

int ADC_temperature()
{
	int tmp;
	int back_adc=0;
		GPDMA_ChannelCmd(1, ENABLE);
		ADC_StartCmd(LPC_ADC0,ADC_START_NOW);
	back_adc=ADC_ChannelGetData(LPC_ADC0,1);
	GPDMA_ChannelCmd(1, ENABLE);
		GPDMA_Setup(&GPDMACfg);
	return back_adc;
}

