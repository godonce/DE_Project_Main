#include "SPIFI.h"

/* ∫Í,”√”⁄∂®“Âw25x32µƒ∆¨—°“˝Ω≈ */
#define SPI_FLASH_CS_LOW()       GPIO_ClearValue(5,1<<11)
#define SPI_FLASH_CS_HIGH()      GPIO_SetValue(5,1<<11)		//cs as high
#define BUFFER_SIZE			0x40   //0x40
/************************** PRIVATE VARIABLES *************************/
uint8_t menu1[] =
"********************************************************************************\n\r"
"Hello NXP Semiconductors \n\r"
"SSP demo \n\r"
"\t - MCU: LPC18xx \n\r"
"\t - Core: ARM Cortex-M3 \n\r"
"\t - Communicate via: UART3 - 115200bps \n\r"
" This example uses SSP in SPI mode as master to communicate with an SSP Flash device \n\r"
" Read and write SPI Flash\n\r"
"********************************************************************************\n\r";
uint8_t menu2[] = "Demo terminated! \n\r";

// SSP Configuration structure variable
SSP_CFG_Type SSP_ConfigStruct;

// Tx buffer
uint8_t Tx_Buf[BUFFER_SIZE];

// Rx buffer
uint8_t Rx_Buf[BUFFER_SIZE];

/************************** PRIVATE FUNCTIONS *************************/
void print_menu(void);
void Buffer_Init(void);
void Error_Loop(void);
void Buffer_Verify(void);


/*********************************************************************************************************
** Function name     : ssp_init
** Descriptions      : Inialize ssp controller
** Input parameters  : none
** Output parameters : none
** Returned value    : none
*********************************************************************************************************/


/*******************************************************************************
* Function Name  : ssp_xfer_byte
* Description    : Send one byte then recv one byte of response
* Input          : - byte_s: byte_s
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static uint8_t ssp_xfer_byte (uint8_t byte_s)
{
	uint8_t byte_r;

	while (LPC_SSP0->SR & (1 << 4) /*BSY*/); 	/* Wait for transfer to finish */
	LPC_SSP0->DR = byte_s;
	while (LPC_SSP0->SR & (1 << 4) /*BSY*/); 	/* Wait for transfer to finish */
	while( !( LPC_SSP0->SR & ( 1 << 2 ) ) );	/* Wait untill the Rx FIFO is not empty */
	byte_r = LPC_SSP0->DR;
	
	return byte_r;                                      /* Return received value */
}


/*********************************************************************************************************
** Function name     : W25X10_ReadStatus
** Descriptions      : Read the state register in the flash memory
** Input parameters  : none
** Output parameters : The value of the state register
** Returned value    : none
*********************************************************************************************************/
uint8_t flash_read_status ( void )
{
	uint8_t status;

	SPI_FLASH_CS_LOW();				 								    /* —°÷–SPI Flash                */
	ssp_xfer_byte(0x05);					        
	status = ssp_xfer_byte(0xff);				        
	SPI_FLASH_CS_HIGH();	    									    /* P0.2--1,CS = 1  Õ∑≈SPI Flash */
	return status;											    /* Return Reg 1's Content		*/
}

/*********************************************************************************************************
** Function name     : flash_write_enable
** Descriptions      : Enable the flash memory to write
** Input parameters  : none
** Output parameters : none
** Returned value    : none
*********************************************************************************************************/
static void flash_write_enable (void)
{
	///while (flash_read_status() & 0x01 != 0x00);                         /* Wait for flash free          */
	while ((flash_read_status() & 0x01) != 0x00);  
	SPI_FLASH_CS_LOW();				 									    /* P0.2--0,CS = 0 —°÷–SPI Flash */

	ssp_xfer_byte(0x06);

	SPI_FLASH_CS_HIGH();													    /* P0.2--1,CS = 1  Õ∑≈SPI Flash */
	///while (flash_read_status() & 0x01 != 0x00);  
	while ((flash_read_status() & 0x03) != 0x02);                         /* Wait for operation complete  */
}

/*********************************************************************************************************
** Function name     : flash_read_id
** Descriptions      : Get flash IDcode
** Input parameters  : none
** Output parameters : Flash IDcode
** Returned value    : Flash IDcode
*********************************************************************************************************/
uint16_t flash_read_id (void)
{
	uint16_t IDcode;

	SPI_FLASH_CS_LOW();				 									    /* P0.2--0,CS = 0 —°÷–SPI Flash */
	ssp_xfer_byte(0x90);
	ssp_xfer_byte(0x00);
	ssp_xfer_byte(0x00);
	ssp_xfer_byte(0x00);
    IDcode = (ssp_xfer_byte(0xff) << 8) | ssp_xfer_byte(0xff);
	SPI_FLASH_CS_HIGH();													    /* P0.2--1,CS = 1  Õ∑≈SPI Flash */

	return IDcode; 												   
}

/*********************************************************************************************************
** Function name     : flash_read_data
** Descriptions      : Read flash memory 
** Input parameters  : RAddr    -- the start address to read
** Output parameters : buf      -- the buffer to receive the read data
**                     RLength	-- the length of the data to read
** Returned value    : The operation result. 1 -- sucess, 0 -- false
*********************************************************************************************************/
uint8_t flash_read_data (uint32_t RAddr, uint8_t *buf, uint32_t RLength)
{
	uint8_t Temp;
	uint32_t i;

	if (RLength == 0)
	{
		return 0;
	}

	/*
	 *	Check the state register. If it's busy , wait until it's free
	 */
	while(1)														
	{														
		Temp = flash_read_status( );								
		Temp &= 0x01;											
		if(Temp == 0x00)									
			break;									
		for(i=0; i<10; i++);						
	}

	SPI_FLASH_CS_LOW();				 									    /* P0.2--0,CS = 0 —°÷–SPI Flash */
	ssp_xfer_byte(0x03);
	ssp_xfer_byte((RAddr & 0xFF0000) >> 16);
	ssp_xfer_byte((RAddr & 0x00FF00) >> 8);
	ssp_xfer_byte((RAddr & 0x0000FF));
	for (i=0; i<RLength; i++)
	{
		buf[i] = ssp_xfer_byte(0xff);
	}
	SPI_FLASH_CS_HIGH();													    /* P0.2--1,CS = 1  Õ∑≈SPI Flash */

	return 1;
}


/*********************************************************************************************************
** Function name     : flash_write_sector
** Descriptions      : Write flash memory , just in one page memory 
** Input parameters  : WAddr    -- the start address to write
** Output parameters : buf      -- the buffer to write the data
**                     RLength	-- the length of the data to write
** Returned value    : The operation result. 1 -- sucess, 0 -- false
*********************************************************************************************************/
uint8_t flash_write_sector (uint32_t WAddr, uint8_t *buf, uint32_t WLength)
{
	uint32_t i;

	if (WLength == 0)
	{
		return 0;
	}

	flash_write_enable();												    /* Write enable                 */


	SPI_FLASH_CS_LOW();				 									    /* P0.2--0,CS = 0 —°÷–SPI Flash */
	ssp_xfer_byte(0x02);
	ssp_xfer_byte((WAddr & 0xFF0000) >> 16);
	ssp_xfer_byte((WAddr & 0x00FF00) >> 8);
	ssp_xfer_byte((WAddr & 0x0000FF));
	for (i=0; i<WLength; i++)
	{
		ssp_xfer_byte(buf[i]);	
	}
	SPI_FLASH_CS_HIGH();													    /* P0.2--1,CS = 1  Õ∑≈SPI Flash */

	///while (flash_read_status() & 0x01 != 0x00);
	while ((flash_read_status() & 0x01 )!= 0x00);

	return 1;
}

/*********************************************************************************************************
** Function name     : flash_write_data
** Descriptions      : Write flash memory ,not just in one page memory 
** Input parameters  : WAddr    -- the start address to write
** Output parameters : buf      -- the buffer to write the data
**                     RLength	-- the length of the data to write
** Returned value    : The operation result. 1 -- sucess, 0 -- false
*********************************************************************************************************/							
uint8_t flash_write_data (uint32_t WAddr, uint8_t *buf, uint32_t WLength)
{
	uint32_t dealer, remainder;
	uint32_t i, addr, len = 0;

	if (WLength == 0)
	{
		return 0;
	}

	remainder = WAddr % W25X32_PAGE_SIZE;

	/*
	 * Write the data not enough to one page memory
	 */
	if (remainder != 0)
	{
		len = W25X32_PAGE_SIZE - remainder;
		if (len < WLength)
		{
			flash_write_sector(WAddr, buf, len);
		} else
		{
			flash_write_sector(WAddr, buf, WLength);
			return 1;
		}
	}
	
	/*
	 * Calculate the rest data, then write several packets with whole page memory
	 */
	remainder = (WLength - len) % W25X32_PAGE_SIZE;
	dealer    = (WLength - len) / W25X32_PAGE_SIZE;
	for (i=0; i<dealer; i++)
	{
		addr = len + (i * W25X32_PAGE_SIZE);
		flash_write_sector(WAddr+addr, (uint8_t *)&buf[addr], W25X32_PAGE_SIZE);
	}
	
	/*
	 * Write the last data that not enough to one page memory
	 */
	if (remainder != 0)
	{
		addr = len + (i * W25X32_PAGE_SIZE);
		flash_write_sector(WAddr+addr, (uint8_t *)&buf[addr], remainder);
	}												
	
	return 1;
}


/*********************************************************************************************************
** Function name     : flash_all_erase
** Descriptions      : Erase the whole flash 
** Input parameters  : None
** Output parameters : None
** Returned value    : The operation result. 1 -- sucess, 0 -- false
*********************************************************************************************************/
uint8_t flash_whole_erase( void )
{
	flash_write_enable();												    /* Write enable                 */
	
	SPI_FLASH_CS_LOW();				 									    /* P0.2--0,CS = 0 —°÷–SPI Flash */
 	ssp_xfer_byte(0xC7);
	SPI_FLASH_CS_HIGH();													    /* P0.2--1,CS = 1  Õ∑≈SPI Flash */

	///while (flash_read_status() & 0x01 != 0x00);	                        /* Wait for the flash free      */
   while ((flash_read_status() & 0x01 )!= 0x00);	 
	return 1;
}

/*********************************************************************************************************
** Function name     : flash_block_erase
** Descriptions      : Block erase 
** Input parameters  : addr -- block address
** Output parameters : None
** Returned value    : The operation result. 1 -- sucess, 0 -- false
*********************************************************************************************************/
uint8_t flash_block_erase (uint32_t addr)
{
	flash_write_enable();												    /* Write enable                 */
	
	SPI_FLASH_CS_LOW();				 									    /* P0.2--0,CS = 0 —°÷–SPI Flash */
	ssp_xfer_byte(0xD8);
	ssp_xfer_byte((addr & 0xFF0000) >> 16);
	ssp_xfer_byte((addr & 0x00FF00) >> 8);
	ssp_xfer_byte(addr & 0x0000FF);
 	SPI_FLASH_CS_HIGH();													    /* P0.2--1,CS = 1  Õ∑≈SPI Flash */

	///while (flash_read_status() & 0x01 != 0x00);					        /* Wait for the flash free      */
  while ((flash_read_status() & 0x01 )!= 0x00); 
	return 1;
}

/*********************************************************************************************************
** Function name     : flash_sector_erase
** Descriptions      : Sector erase 
** Input parameters  : addr -- sector address
** Output parameters : None
** Returned value    : The operation result. 1 -- sucess, 0 -- false
*********************************************************************************************************/
uint8_t flash_sector_erase (uint32_t addr)
{
	flash_write_enable();												    /* Write enable                 */
	
	SPI_FLASH_CS_LOW();				 									    /* P0.2--0,CS = 0 —°÷–SPI Flash */
	ssp_xfer_byte(0x20);
	ssp_xfer_byte((addr & 0xFF0000) >> 16);
	ssp_xfer_byte((addr & 0x00FF00) >> 8);
	ssp_xfer_byte(addr & 0x0000FF);
 	SPI_FLASH_CS_HIGH();													    /* P0.2--1,CS = 1  Õ∑≈SPI Flash */

	///while (flash_read_status() & 0x01 != 0x00);							/* Wait for the flash free      */
  while ((flash_read_status() & 0x01 )!= 0x00);	  
	return 1;
}


/*********************************************************************************************************
** Function name     : flash_sel_erases
** Descriptions      : Erase the selected flash 
** Input parameters  : startSec -- start sector	number
**                     endSec   -- end sector number
** Output parameters : None
** Returned value    : The operation result. 1 -- sucess, 0 -- false
*********************************************************************************************************/
uint8_t flash_sel_erases (uint32_t startSec, uint32_t endSec)
{
	uint32_t i;

	for (i=startSec; i<=endSec; i++)
	{
		flash_sector_erase(i * W25X32_SECTOR_SIZE);
	}

	return(1);
}






/*-------------------------PRIVATE FUNCTIONS------------------------------*/
/*********************************************************************//**
 * @brief		Initialize buffer
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void Buffer_Init(void)
{
	uint8_t i;

	for (i = 0; i < BUFFER_SIZE; i++) {
		//Tx_Buf[i] = i;
		Rx_Buf[i] = 0;
	}
}

/*********************************************************************//**
 * @brief		Error Loop (called by Buffer_Verify() if any error)
 * @param[in]	none
 * @return 		None
 **********************************************************************/
void Error_Loop(void)
{
	/* Loop forever */
	while (1);
}


/*********************************************************************//**
 * @brief		Verify buffer
 * @param[in]	none
 * @return 		None
 **********************************************************************/
void Buffer_Verify(void)
{
	uint8_t i;
	uint8_t *src_addr = (uint8_t *) &Tx_Buf[0];
	uint8_t *dest_addr = (uint8_t *) &Rx_Buf[0];

	for ( i = 0; i < BUFFER_SIZE; i++ )
	{
	
		if ( *src_addr++ != *dest_addr++ )
		{
			_DBG_("Verify error");
			/* Call Error Loop */
			Error_Loop();
		}
	}
}


/*********************************************************************//**
 * @brief		Print Welcome menu
 * @param[in]	none
 * @return 		None
 **********************************************************************/
void print_menu(void)
{
	_DBG(menu1);
}

/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************//**
 * @brief		Main SSP program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int c_entry_flash(void)
{
	volatile uint32_t spiid;
	SystemInit();
	CGU_Init();

	/* Initialize debug via UART0
	 * ñ 115200bps
	 * ñ 8 data bit
	 * ñ No parity
	 * ñ 1 stop bit
	 * ñ No flow control
	 */
	debug_frmwrk_init();

	// print welcome screen
	print_menu();

	/* Configure SSP1 pins*/
	scu_pinmux(0x3,8,MD_PLN_FAST,FUNC4);	// P3.8 GPIO5[11] CS 
	GPIO_SetDir(5,1<<11, 1);			   //P3.8 as GPIO5[11]	 ssp_cs pin	  output
	GPIO_SetValue(5,1<<11);		//cs as high	
	
	scu_pinmux(0x3,4,MD_PLN_FAST,FUNC0);	// P3.4 GPIO1[14] #hole need to be output High gpio
    GPIO_SetDir(1,1<<14, 1);			 
	GPIO_SetValue(1,1<<14);		//hold as high
	
	scu_pinmux(0x3,5,MD_PLN_FAST,FUNC0);	// P3.5 GPIO1[15] #WP  need to be output High gpio
	GPIO_SetDir(1,1<<15, 1);			   
	GPIO_SetValue(1,1<<15);		//wp as high

	scu_pinmux(0x3,3,MD_PLN_FAST,FUNC2);	// P3.3 connected to SCL/SCLK	func2=SSP0 SCK0
 	scu_pinmux(0x3,6,MD_PLN_FAST,FUNC5);	// P3.6 connected to nCS		func5=SSP0 MISO0
 	scu_pinmux(0x3,7,MD_PLN_FAST,FUNC5);	// P3.7 connected to SO			func5=SSP0 MOSI0

	// initialize SSP configuration structure to default
	SSP_ConfigStructInit(&SSP_ConfigStruct);
	SSP_ConfigStruct.Mode = SSP_MASTER_MODE;
	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP0, &SSP_ConfigStruct);


	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP0, ENABLE);
	 //SSPInit();
	Buffer_Init();
//	_DBG_("Press '1' to start SPI_Flash Demo...");
//	while (_DG != '1');
while(1)
{
	spiid = flash_read_id();
	//_DBG("\nRead spi flash id :"); 
	//_DBH16(spiid);
	//_DBG("\n\r");
}
//	_DBG("Start to erase sector 0...\n\r");
//	flash_sector_erase (0x000000);

//	_DBG("Start to write data... \n\r");
//	flash_write_sector (0x000000, Tx_Buf, BUFFER_SIZE);
//	
//	_DBG("Start to read data... \n\r");
//	flash_read_data (0x000000, Rx_Buf, BUFFER_SIZE);
//	_DBG("Start to verify data... \n\r");
//	Buffer_Verify();
//	_DBG("Verify complete!");

    /* Loop forever */
   // while(1);
}






