#include "SDRAM.h"
#include "lpc43xx.h"
#include "lpc_types.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_timer.h"
#include "lpc43xx_cgu.h"
//#include "debug_frmwrk.h"
/************************** PRIVATE DEFINITIONS *************************/
/* SDRAM Address Base for DYCS0*/
#define SDRAM_ADDR_BASE		0x28000000

/* SDRAM refresh time to 16 clock num */
#define EMC_SDRAM_REFRESH(freq,time)  \
  (((uint64_t)((uint64_t)time * freq)/16000000000ull)+1)

/*-------------------------PRIVATE FUNCTIONS------------------------------*/
/*********************************************************************
 * @brief		Calculate EMC Clock from nano second
 * @param[in]	freq - frequency of EMC Clk
 *						frequency is a variable so cannot present this as a macro
 *						because it always be calculated in run-time..
 * @param[in]	time - nano second
 * @return 		None
 **********************************************************************/
uint32_t NS2CLK(uint32_t freq,uint32_t time){
	freq /= 100000;
 return (time*freq/10000);
}

/*********************************************************************
 * @brief		Init the EMC Controller to connect ex SDRAM
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void SDRAM123_Init () {
	uint32_t pclk, temp;
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	
	/* Set up EMC pin */
	scu_pinmux(	2	,	9	,	MD_PLN_FAST	,	2	);	//A0  P2_9
	scu_pinmux(	2	,	10	,	MD_PLN_FAST	,	2	);	//A1  P2_10
	scu_pinmux(	2	,	11	,	MD_PLN_FAST	,	2	);	//A2  P2_11
	scu_pinmux(	2	,	12	,	MD_PLN_FAST	,	2	);	//A3  P2_12
	scu_pinmux(	2	,	13	,	MD_PLN_FAST	,	2	);	//A4  P2_13
	scu_pinmux(	1	,	0	,	MD_PLN_FAST	,	2	);	//A5  P1_0
	scu_pinmux(	1	,	1	,	MD_PLN_FAST	,	2	);	//A6  P1_1
	scu_pinmux(	1	,	2	,	MD_PLN_FAST	,	2	);	//A7  P1_2
	scu_pinmux(	2	,	8	,	MD_PLN_FAST	,	2	);	//A8  P2_8
	scu_pinmux(	2	,	7	,	MD_PLN_FAST	,	2	);	//A9  P2_7
	scu_pinmux(	2	,	6	,	MD_PLN_FAST	,	2	);	//A10 P2_6
	scu_pinmux(	2	,	2	,	MD_PLN_FAST	,	2	);	//A11 P2_2
	scu_pinmux(	2	,	1	,	MD_PLN_FAST	,	2	);	//A12 P2_1
	scu_pinmux(	2	,	0	,	MD_PLN_FAST	,	2	);	//A13 (BA0) P2_0
	scu_pinmux(	6	,	8	,	MD_PLN_FAST	,	2	);	//A14 (BA1)  P6_8
	/*
	scu_pinmux(	1	,	0	,	MD_PLN_FAST	,	2	);	//A14
	scu_pinmux(	1	,	0	,	MD_PLN_FAST	,	2	);	//A15
	scu_pinmux(	1	,	0	,	MD_PLN_FAST	,	2	);	//A16
	scu_pinmux(	1	,	0	,	MD_PLN_FAST	,	2	);	//A17
	scu_pinmux(	1	,	0	,	MD_PLN_FAST	,	2	);	//A18
	scu_pinmux(	1	,	0	,	MD_PLN_FAST	,	2	);	//A19
	scu_pinmux(	1	,	0	,	MD_PLN_FAST	,	2	);	//A20
	scu_pinmux(	1	,	0	,	MD_PLN_FAST	,	2	);	//A21
	scu_pinmux(	1	,	0	,	MD_PLN_FAST	,	2	);	//A22
	scu_pinmux(	1	,	0	,	MD_PLN_FAST	,	2	);	//A23
	*/
	scu_pinmux(	1	,	7	,	MD_PLN_FAST	,	2	);	//D0   P1_7
	scu_pinmux(	1	,	8	,	MD_PLN_FAST	,	2	);	//D1   P1_8
	scu_pinmux(	1	,	9	,	MD_PLN_FAST	,	2	);	//D2   P1_9
	scu_pinmux(	1	,	10	,	MD_PLN_FAST	,	2	);	//D3   P1_10
	scu_pinmux(	1	,	11	,	MD_PLN_FAST	,	2	);	//D4   P1_11
	scu_pinmux(	1	,	12	,	MD_PLN_FAST	,	2	);	//D5   P1_12
	scu_pinmux(	1	,	13	,	MD_PLN_FAST	,	2	);	//D6   P1_13
	scu_pinmux(	1	,	14	,	MD_PLN_FAST	,	2	);	//D7   P1_14
	scu_pinmux(	1	,	15	,	MD_PLN_FAST	,	2	);	//D8   P1_15
	scu_pinmux(	1	,	16	,	MD_PLN_FAST	,	2	);	//D9   P1_16
	scu_pinmux(	1	,	18	,	MD_PLN_FAST	,	2	);	//D10  P1_18
	scu_pinmux(	1	,	20	,	MD_PLN_FAST	,	2	);	//D11  P1_20
	scu_pinmux(	5	,	0	,	MD_PLN_FAST	,	2	);	//D12  P5_0
	scu_pinmux(	5	,	1	,	MD_PLN_FAST	,	2	);	//D13  P5_1
	scu_pinmux(	5	,	2	,	MD_PLN_FAST	,	2	);	//D14  P5_2
	scu_pinmux(	5	,	3	,	MD_PLN_FAST	,	2	);	//D15  P5_3
	scu_pinmux(	13	,	2	,	MD_PLN_FAST	,	2	);	//D16  PD_2
	scu_pinmux(	13	,	3	,	MD_PLN_FAST	,	2	);	//D17  PD_3
	scu_pinmux(	13	,	4	,	MD_PLN_FAST	,	2	);	//D18  PD_4
	scu_pinmux(	13	,	5	,	MD_PLN_FAST	,	2	);	//D19  PD_5
	scu_pinmux(	13	,	6	,	MD_PLN_FAST	,	2	);	//D20  PD_6
	scu_pinmux(	13	,	7	,	MD_PLN_FAST	,	2	);	//D21  PD_7
	scu_pinmux(	13	,	8	,	MD_PLN_FAST	,	2	);	//D22  PD_8
	scu_pinmux(	13	,	9	,	MD_PLN_FAST	,	2	);	//D23  PD_9
	scu_pinmux(	14	,	5	,	MD_PLN_FAST	,	2	);	//D24  PE_5
	scu_pinmux(	14	,	6	,	MD_PLN_FAST	,	2	);	//D25  PE_6
	scu_pinmux(	14	,	7	,	MD_PLN_FAST	,	2	);	//D26  PE_7
	scu_pinmux(	14	,	8	,	MD_PLN_FAST	,	2	);	//D27  PE_8
	scu_pinmux(	14	,	9	,	MD_PLN_FAST	,	2	);	//D28  PE_9
	scu_pinmux(	14	,	10	,	MD_PLN_FAST	,	2	);	//D29  PE_10
	scu_pinmux(	14	,	11	,	MD_PLN_FAST	,	2	);	//D30  PE_11
	scu_pinmux(	14	,	12	,	MD_PLN_FAST	,	2	);	//D31  PE_12
	
	scu_pinmux(	6	,	12	,	MD_PLN_FAST	,	3	); //DQMOUT0   P6_12
	scu_pinmux(	6	,	10	,	MD_PLN_FAST	,	3	); //DQMOUT1   P6_10
	scu_pinmux(	13	,	0	,	MD_PLN_FAST	,	3	); //DQMOUT2   PD_0
	scu_pinmux(	14	,	13	,	MD_PLN_FAST	,	3	); //DQMOUT3   PE_13
	
	scu_pinmux(	6	,	11	,	MD_PLN_FAST	,	3	);//CKE   P6_11
	//scu_pinmux(	1	,	5	,	MD_PLN_FAST	,	3	);	//CLK   CLK1
	scu_pinmux(	1	,	6	,	MD_PLN_FAST	,	3	);	//WE    P1_6
	scu_pinmux(	6	,	9	,	MD_PLN_FAST	,	3	);  //CS    P6_9
	scu_pinmux(	6	,	4	,	MD_PLN_FAST	,	3	);  //CAS   P6_4
	scu_pinmux(	6	,	5	,	MD_PLN_FAST	,	3	);  //RAS   P6_5

	/* Select EMC clock-out */
	LPC_SCU->SFSCLK_0 = MD_PLN_FAST;
	LPC_SCU->SFSCLK_1 = MD_PLN_FAST;
	LPC_SCU->SFSCLK_2 = MD_PLN_FAST;
	LPC_SCU->SFSCLK_3 = MD_PLN_FAST;

	//pclk = CGU_GetPCLKFrequency(CGU_PERIPHERAL_M3CORE);     M3
	pclk = CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE);

	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 1;

	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIMER2, TIM_TIMER_MODE,&TIM_ConfigStruct);

	LPC_EMC->CONTROL 	= 0x00000001;
	LPC_EMC->CONFIG  	= 0x00000000;
	LPC_EMC->DYNAMICCONFIG0    = 1<<14 | 3<<9 | 1<<7; /* 256Mb, 16Mx16, 4 banks, row=12, column=8 */

//	pclk = CGU_GetPCLKFrequency(CGU_PERIPHERAL_M3CORE);

	LPC_EMC->DYNAMICRASCAS0    = 0x00000303; /* 1 RAS, 3 CAS latency */
	LPC_EMC->DYNAMICREADCONFIG = 0x00000001; /* Command delayed strategy, using EMCCLKDELAY */

	LPC_EMC->DYNAMICRP         = 2;//NS2CLK(pclk, 20);
	LPC_EMC->DYNAMICRAS        = NS2CLK(pclk, 45);
	LPC_EMC->DYNAMICSREX       = 5;//NS2CLK(pclk, 63);
	LPC_EMC->DYNAMICAPR        = 0x00000001;
	LPC_EMC->DYNAMICDAL        = 0x00000005;
	LPC_EMC->DYNAMICWR         = 3;
	LPC_EMC->DYNAMICRC         = NS2CLK(pclk, 65);
	LPC_EMC->DYNAMICRFC        = NS2CLK(pclk, 66);
	LPC_EMC->DYNAMICXSR        = 5;//NS2CLK(pclk, 67);
	LPC_EMC->DYNAMICRRD        = NS2CLK(pclk, 15);
	LPC_EMC->DYNAMICMRD        = 0x00000003;
  // 	for(i= 200*30; i;i--);
	TIM_Waitus(100);							/* wait 100ms */
	LPC_EMC->DYNAMICCONTROL    = 0x00000183; 	/* Issue NOP command */

	TIM_Waitus(100);							/* wait 200ms */
	LPC_EMC->DYNAMICCONTROL    = 0x00000103; 	/* Issue PALL command */

	LPC_EMC->DYNAMICREFRESH    = 2;				//EMC_SDRAM_REFRESH(pclk,70); /* 46( n * 16 ) -> 32 clock cycles */

	//for(i = 0; i < 0x80; i++);				/* wait 128 AHB clock cycles */
	TIM_Waitus(100);							/* wait 200ms */

	LPC_EMC->DYNAMICREFRESH    = 0x1D; /* ( n * 16 ) -> 736 clock cycles -> 15.330uS at 48MHz <= 15.625uS ( 64ms / 4096 row ) */

	LPC_EMC->DYNAMICCONTROL    = 0x00000083; /* Issue MODE command */

	//Timing for 48/60/72MHZ Bus
	temp = *((volatile uint32_t *)(SDRAM_ADDR_BASE |0x32<<13)); //(3<<4| 3)<<11)); /* 4 burst, 3 CAS latency */
	temp = temp;
	LPC_EMC->DYNAMICCONTROL    = 0x00000000; /* Issue NORMAL command */

	//[re]enable buffers
	LPC_EMC->DYNAMICCONFIG0    |= 1<<19;
}

