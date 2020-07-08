/**
  ******************************************************************************
  * <h2><center>&copy; COPYRIGHT 2013 Embest Tech. Co., Ltd.</center></h2>
  * @file    nandflash_k9f1g08u0a.c
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-February-2013
  * @brief   This c file contains all functions support for Nand Flash 
  *          SamSung K9F1G08U0A
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Embest SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
  * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
  * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  */ 
#include "lpc43xx_libcfg.h"  
#include "nandflash_k9f1g08u0a.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_cgu.h"
#include "lpc43xx_gpio.h"


/** @defgroup Public variable
* @{
*/
uint8_t InvalidBlockTable[NANDFLASH_NUMOF_BLOCK];
/**
* @}
*/ 


/**
* @brief  Initialize external NAND FLASH memory
* @param  None
* @retval None
*/
void NandFlash_Init(void)
{
  uint32_t i;
  
  /*
    Init DATA Pin D0-D7 P1_7-----P1_14
  */                
  scu_pinmux(0x1,  7,  (MD_PLN_FAST), FUNC3);  /* P1_7: D0  */
  scu_pinmux(0x1,  8,  (MD_PLN_FAST), FUNC3);  /* P1_8: D1  */
  scu_pinmux(0x1,  9,  (MD_PLN_FAST), FUNC3);  /* P1_9: D2  */
  scu_pinmux(0x1,  10, (MD_PLN_FAST), FUNC3);  /* P1_10: D3 */
  scu_pinmux(0x1,  11, (MD_PLN_FAST), FUNC3);  /* P1_11: D4 */
  scu_pinmux(0x1,  12, (MD_PLN_FAST), FUNC3);  /* P1_12: D5 */
  scu_pinmux(0x1,  13, (MD_PLN_FAST), FUNC3);  /* P1_13: D6 */
  scu_pinmux(0x1,  14, (MD_PLN_FAST), FUNC3);  /* P1_14: D7 */
  /*
    Init ADDR Pin A16-A17  PD15-PD16
  */
  scu_pinmux(0xD,  16, (MD_PLN_FAST), FUNC2);  /* Pd_16: A16 */
  scu_pinmux(0xD,  15, (MD_PLN_FAST), FUNC2);  /* Pd_15: A17 */
                
  /*
    Init Control Pin
  */
  scu_pinmux(0x1, 3, MD_PLN_FAST, FUNC3); /* EMC_nOE */
  scu_pinmux(0x1, 6, MD_PLN_FAST, FUNC3); /* EMC_nWE */  
  scu_pinmux(0x1, 5, MD_PLN_FAST, FUNC3); /* EMC_nCS0*/

  /*
    Init RYD Pin
  */
  scu_pinmux(NANDFLASH_RDY_PORT, NANDFLASH_RDY_PIN, PUP_ENABLE | INBUF_ENABLE, FUNC4);

  /* Set up EMC Controller */
  /* 
   set
   ByteLane = 1; low level activate
   DataWidth = 8; DataWith = 8bit
   ExtendedWait = 0; no delay wait
   PageMode = 0;
  */
  LPC_EMC->STATICCONFIG0 = 0x80;
  
  /* set WAITWEN CCLK = 2 */
  LPC_EMC->STATICWAITWEN0 = 2;

  /* set WAITOEN CCLK = 2 */
  LPC_EMC->STATICWAITOEN0 = 2;

  LPC_EMC->STATICWAITWR0 = 0xf;  
  
  LPC_EMC->STATICWAITRD0 = 0xf;  
  
  LPC_EMC->STATICWAITTURN0 = 0xf;  
  
  LPC_EMC->STATICWAITPAG0 = 0xf;
  
  /* assume all blocks are valid to begin with */
  for ( i = 0; i < NANDFLASH_NUMOF_BLOCK; i++ ) {
    InvalidBlockTable[i] = 0;
  }

  return;
}

/**
* @brief  NandFlash_WaitForReady
* @param  None
* @retval None
*/
NANDFLASH_STATUS_TypeDef NandFlash_WaitForReady(uint32_t timeout)
{
  uint32_t tmp;
  do {
    tmp = GPIO_ReadValue(NANDFLASH_RDY_GPIO_PORT) & (1 << NANDFLASH_RDY_GPIO_PIN);
  } while (!tmp); /* from low to high once */
  
  return NANDFLASH_STATUS_SUCCESS;
}

/**
* @brief  NandFlash_WaitForBusy
* @param  None
* @retval None
*/
NANDFLASH_STATUS_TypeDef NandFlash_WaitForBusy(void)
{
  uint32_t tmp;
  do {
    tmp = GPIO_ReadValue(NANDFLASH_RDY_GPIO_PORT) & (1 << NANDFLASH_RDY_GPIO_PIN);
  } while (tmp); /* from high to low once */
  
  return NANDFLASH_STATUS_SUCCESS;
}
/**
* @brief  Issue Reset command to NAND FLASH memory
* @param  None
* @retval None
*/
NANDFLASH_STATUS_TypeDef NandFlash_Reset(void)
{
  volatile uint8_t *pCLE;

  /* Reset NAND FLASH  through NAND FLASH command */
  pCLE = K9F1G_CLE;
  *pCLE = K9FXX_RESET;

  NandFlash_WaitForReady(NANDFLASH_TIME_OUT_RESET);
                
  return NANDFLASH_STATUS_SUCCESS;
}

/**
 * @brief  Read status from NAND FLASH memory
 * @param  Cmd command for read operation, should be:
 *           -  K9FXX_BLOCK_PROGRAM_1
 *           -  K9FXX_BLOCK_ERASE_1
 *           -  K9FXX_READ_1
 * @retval  Status
*/
NANDFLASH_STATUS_TypeDef NandFlash_ReadStatus(uint32_t Cmd)
{
  volatile uint8_t *pCLE;
  volatile uint8_t *pDATA;
  uint8_t StatusData;

  pCLE  = K9F1G_CLE;
  pDATA = K9F1G_DATA;

  *pCLE = K9FXX_READ_STATUS;

#if 1
  while ( (*pDATA & 0xC0) != 0xC0 );
#else
  /* Wait until bit 5 and 6 are 1, READY, bit 7 should be 1 too, not protected */
  /* if ready bit not set, it gets stuck here */
  while ( (*pDATA & 0xE0) != 0xE0 );
#endif

  StatusData = *pDATA;

  switch (Cmd)
  {
    case K9FXX_BLOCK_PROGRAM_1:
      if (StatusData & 0x01) {	/* Program failure(1) or pass(0) */
        return(NANDFLASH_STATUS_PROG_ERROR);
      }
      break;
      
    case K9FXX_BLOCK_ERASE_1:
      if (StatusData & 0x01) {	/* Erase failure(1) or pass(0) */
        return(NANDFLASH_STATUS_ERASE_ERROR);
      }                    
      break;            
      
    case K9FXX_READ_1: /* bit 5 and 6, Read busy(0) or ready(1) */
      break;

    default:
      break;
  }
  
  return NANDFLASH_STATUS_SUCCESS;
}

/**
 * @brief  Read ID from external NAND FLASH memory
 * @param  None
 * @retval Status
*/
NANDFLASH_STATUS_TypeDef NandFlash_ReadId(uint8_t *pBuffer)
{
  NANDFLASH_STATUS_TypeDef status;
  volatile uint8_t *pCLE;
  volatile uint8_t *pALE;
  volatile uint8_t *pDATA;
  
  pCLE  = K9F1G_CLE;
  pALE  = K9F1G_ALE;
  pDATA = K9F1G_DATA;

  *pCLE = K9FXX_READ_ID;
  *pALE = 0;

  pBuffer[3] = *pDATA;
  pBuffer[2] = *pDATA;
  pBuffer[0] = *pDATA;
  pBuffer[1] = *pDATA;

  status = NANDFLASH_STATUS_SUCCESS;
	
  return status;
}

/**
 * @brief  Erase the whole NAND FLASH memory block based on the block number
 * @param  blockNum number of block that will be erased, should
 *         be in range: 0 .. 1023
 * @retval status
*/
NANDFLASH_STATUS_TypeDef NandFlash_BlockErase(uint32_t blockNum)
{
  volatile uint8_t *pCLE;
  volatile uint8_t *pALE;
  NANDFLASH_STATUS_TypeDef status;

  pCLE  = K9F1G_CLE;
  pALE  = K9F1G_ALE;

  if (blockNum >= NANDFLASH_NUMOF_BLOCK) {
    return NANDFLASH_STATUS_BLOCK_OUT;
  }
  blockNum = blockNum<<6;

  *pCLE = K9FXX_BLOCK_ERASE_1;
  *pALE = (uint8_t)(blockNum & 0x00FF);        /* column address low */
  *pALE = (uint8_t)((blockNum & 0xFF00) >> 8);	/* column address high */

  *pCLE = K9FXX_BLOCK_ERASE_2; 
  *pCLE = K9FXX_BLOCK_PROGRAM_2;
  status = NandFlash_WaitForReady(NANDFLASH_TIME_OUT_RESET);
   
  if(status == NANDFLASH_STATUS_SUCCESS) { 
    status = NandFlash_ReadStatus(K9FXX_BLOCK_ERASE_1);
  }
   
  return status;	
}


/**
 * @brief   Write a page of program into NAND flash based on the page number, 
 *          write up to 2112 bytes of data at a time.
 * @param   pBuffer   :  pointer to the buffer that contain data will be
 *                       programmed in flash memory 
 *          PageAddr   : number of page that will be programmed.
 *          ByteAddr   : number of byres in the page that will be programmed.
 *          NumToWrite : the number of byte(s) to be write.
 * @retval  NANDFLASH_STATUS_TypeDef
*/
NANDFLASH_STATUS_TypeDef 
NandFlash_PageProgram(uint8_t *pBuffer, uint32_t PageAddr, uint32_t ByteAddr, uint32_t NumToWrite)
{
  volatile uint8_t *pCLE;
  volatile uint8_t *pALE;
  volatile uint8_t *pDATA;
  NANDFLASH_STATUS_TypeDef status;
                
  pCLE  = K9F1G_CLE;
  pALE  = K9F1G_ALE;
  pDATA = K9F1G_DATA;

  if (PageAddr >= NANDFLASH_NUMOF_PAGE) {
    return NANDFLASH_STATUS_PAGE_OUT;
  }

  if ((ByteAddr + NumToWrite) > NANDFLASH_PAGE_FSIZE) {
    return NANDFLASH_STATUS_BYTE_OUT;	
  }
  *pCLE = K9FXX_BLOCK_PROGRAM_1;
  *pALE =  (uint8_t)(ByteAddr & 0xFF);
  *pALE =  (uint8_t)((ByteAddr & 0xF00)>>8);

  *pALE =  (uint8_t)(PageAddr & 0xFF);
  *pALE =  (uint8_t)((PageAddr & 0xFF00)>>8);
  while (NumToWrite--) {
    *pDATA = *pBuffer++;
  }
  *pCLE = K9FXX_BLOCK_PROGRAM_2;

  status = NandFlash_WaitForReady(NANDFLASH_TIME_OUT_PROG);

  if (status == NANDFLASH_STATUS_SUCCESS) {
    status = NandFlash_ReadStatus(K9FXX_BLOCK_PROGRAM_1);
  }
  
  return status;
}


/**
  ******************************************************************************	
  * @brief  Read the whole NAND FLASH memory page based on the page number, 
  *         the data will be stored in the pointer to the buffer.	
  * @param  Buffer : pointer to the buffer that contain data will be read from flash memory 
  *         PageAddr : number of page that will be programmed.
  *         ByteAddr : number of byres in the page that will be programmed.
  *         NumToRead : the number of byte(s) to be read and stored to the buffer
  * @retval NF_STATUS_TypeDef 			
  ******************************************************************************
  */
NANDFLASH_STATUS_TypeDef 
NandFlash_PageRead(uint8_t *pBuffer, uint32_t PageAddr, uint32_t ByteAddr, uint32_t NumToRead)
{
  NANDFLASH_STATUS_TypeDef status;
  volatile uint8_t *pCLE;
  volatile uint8_t *pALE;
  volatile uint8_t *pDATA;
                
  pCLE  = K9F1G_CLE;
  pALE  = K9F1G_ALE;
  pDATA = K9F1G_DATA;  
 	
  if (PageAddr >= NANDFLASH_NUMOF_PAGE) {
    return NANDFLASH_STATUS_PAGE_OUT;	
  }

  if ((ByteAddr + NumToRead) > NANDFLASH_PAGE_FSIZE) {
    return NANDFLASH_STATUS_BYTE_OUT;	
  }

  *pCLE = K9FXX_READ_1;

  *pALE =  (uint8_t)(ByteAddr & 0xFF);
  *pALE =  (uint8_t)((ByteAddr & 0xF00)>>8);

  *pALE =  (uint8_t)(PageAddr & 0xFF);
  *pALE =  (uint8_t)((PageAddr & 0xFF00)>>8);

  *pCLE = K9FXX_READ_2;
  
  NandFlash_WaitForBusy();
  status = NandFlash_WaitForReady(NANDFLASH_TIME_OUT_READ);
  if (status == NANDFLASH_STATUS_SUCCESS) {
    while (NumToRead--) {
      *pBuffer++ = *pDATA;
    }
    status = NandFlash_WaitForReady(NANDFLASH_TIME_OUT_READ);	
  }
  
  return status;
}

/************** COPYRIGHT 2013 Embest Tech. Co., Ltd.*****END OF FILE****/
