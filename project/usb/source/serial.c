
#include "lpc43xx.h"                                   // lpc43xx definitions
#include "lpc_types.h"
#include "serial.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_cgu.h"


/*----------------------------------------------------------------------------
  Defines for ring buffers
 *---------------------------------------------------------------------------*/
#define SER_BUF_SIZE               (128)               // serial buffer in bytes (power 2)
#define SER_BUF_MASK               (SER_BUF_SIZE-1ul)  // buffer size mask

/* Buffer read / write macros */
#define SER_BUF_RESET(serBuf)      (serBuf.rdIdx = serBuf.wrIdx = 0)
#define SER_BUF_WR(serBuf, dataIn) (serBuf.data[SER_BUF_MASK & serBuf.wrIdx++] = (dataIn))
#define SER_BUF_RD(serBuf)         (serBuf.data[SER_BUF_MASK & serBuf.rdIdx++])
#define SER_BUF_EMPTY(serBuf)      (serBuf.rdIdx == serBuf.wrIdx)
#define SER_BUF_FULL(serBuf)       (serBuf.rdIdx == serBuf.wrIdx+1)
#define SER_BUF_COUNT(serBuf)      (SER_BUF_MASK & (serBuf.wrIdx - serBuf.rdIdx))

// buffer type
typedef struct __SER_BUF_T {
  unsigned char data[SER_BUF_SIZE];
  unsigned int wrIdx;
  unsigned int rdIdx;
} SER_BUF_T;

unsigned long          ser_txRestart;                  // NZ if TX restart is required
unsigned short         ser_lineState;                  // ((msr << 8) | (lsr))
SER_BUF_T              ser_out;                        // Serial data buffers
SER_BUF_T              ser_in;

/*----------------------------------------------------------------------------
  open the serial port
 *---------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
  initialize the serial port
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  read data from serial port
 *---------------------------------------------------------------------------*/
int ser_Read (char *buffer, const int *length) 
{
  int bytesToRead, bytesRead;
  /* Read *length bytes, block if *bytes are not avaialable	*/
  bytesToRead = *length;
  bytesToRead = (bytesToRead < (*length)) ? bytesToRead : (*length);
  bytesRead = bytesToRead;

  while (bytesToRead--) {
    while (SER_BUF_EMPTY(ser_in));                     // Block until data is available if none
    *buffer++ = SER_BUF_RD(ser_in);
  }
  return (bytesRead);
}

/*----------------------------------------------------------------------------
  write data to the serial port
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  check if character(s) are available at the serial interface
 *---------------------------------------------------------------------------*/
void ser_AvailChar (int *availChar) 
	{

  *availChar = SER_BUF_COUNT(ser_in);

}

/*----------------------------------------------------------------------------
  read the line state of the serial port
 *---------------------------------------------------------------------------*/
void ser_LineState (unsigned short *lineState) {

  *lineState = ser_lineState;
  ser_lineState = 0;

}

/*----------------------------------------------------------------------------
  serial port 0 interrupt
 *---------------------------------------------------------------------------*/

