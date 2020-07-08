#ifndef _CODE_CONVERT_H_
#define _CODE_CONVERT_H_

#include "stdio.h"
#include "stdlib.h"
#include "tchar.h"
#include "locale.h"


unsigned char enc_unicode_to_utf8_str(const char *pInput,unsigned char *pOutput, unsigned char lenInput);
int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,int outSize);
void WIN_ContextInit(void);
#endif
