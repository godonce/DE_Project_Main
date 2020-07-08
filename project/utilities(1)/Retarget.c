/*----------------------------------------------------------------------------
 * Name:    Retarget.c
 * Purpose: 'Retarget' layer for target-dependent low level functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <rt_misc.h>
#include "Serial.h"
#include "SEGGER_RTT.h"

#pragma import(__use_no_semihosting_swi)



struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


int fputc(int c, FILE *f) {
#ifndef __RTT
    return (SER_PutChar(c));
#else
    SEGGER_RTT_Write(0, &c, 1);
    return (c);
#endif
}


int fgetc(FILE *f) {
#ifndef __RTT
  return (SER_GetChar());
#else
    return (SEGGER_RTT_WaitKey());
#endif
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int c) {
#ifndef __RTT
    return (SER_PutChar(c));
#else
    SEGGER_RTT_Write(0, &c, 1);
#endif
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}
