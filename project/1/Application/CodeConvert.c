#include "CodeConvert.h"
#include "stdio.h"
//#include "cwchar"     //0428
#include "string.h"
#include "wchar.h"
#include "tchar.h"
//#include "cwctype.h"
//#include "locale.h"
//#include "stdlib.h"
//extern size_t wcslen(const wchar_t * __restrict /*s*/);
unsigned char enc_unicode_to_utf8_str(char *pInput,unsigned char *pOutput, unsigned char lenInput)
{
//    char * pstr = "s科a技b金c智dec";
//    char  dptr[32];
//    char   dptr2[32];
//    wchar_t pwstr[64] = {0};     
//    int len=0;
//    setlocale(LC_ALL, "");
//    mbstowcs(pwstr, pstr, 40);
//    for (i = 0; i < wcslen(pwstr)  ; i++)//wcslen(pwstr)
//    {
//      printf("0x%x ", pwstr[i]);
//      len+=enc_unicode_to_utf8_one(pwstr[i],&strShow[0][len],6);
//      //sprintf(dptr2,"%x%x%x", dptr[0],dptr[1],dptr[2]);
//      //printf("%s ", _apStringA[i]);
//      printf("i=%d len=%d \n",i,len);
//    }
//    printf("\n");
//    printf("%s \n", dptr);
//    printf("%s \n", _apStrings3[0]);
//
//    printf("%d %d %d %d %d \n", dptr[0], dptr[1], dptr[2], dptr[3], dptr[4]);
//    printf("%d %d %d %d %d \n", _apStrings3[0][0], _apStrings3[0][1], _apStrings3[0][2], _apStrings3[0][3], _apStrings3[0][4]);
//
//    for(i=0;i<20;i++) _apStringA[i] = strShow[i];
//    for (i = 0; i < GUI_COUNTOF(_apStringA); i++) {
//        GUI_DispStringAt(_apStringA[i], 70, 20+i*16);
//        GUI_DispNextLine();
//    }
      
    char * pstr = pInput;
    unsigned char * dptr = pOutput;
		int len=0;
		wchar_t pwstr[128] = {0};
    unsigned char i =0;
    if(lenInput > 128) 
			return 0;
    
    
    setlocale(LC_ALL, "");
 /*   mbstowcs(pwstr, pstr, 128);
    for (i = 0; i < wcslen(pwstr)  ; i++)
    {
      len+=enc_unicode_to_utf8_one(pwstr[i],dptr+len,6);
    }*/
    return 1;
}


/*****************************************************************************
 * 将一个字符的Unicode(UCS-2和UCS-4)编码转换成UTF-8编码.
 *
 * 參数:
 *    unic     字符的Unicode编码值
 *    pOutput  指向输出的用于存储UTF8编码值的缓冲区的指针
 *    outsize  pOutput缓冲的大小
 *
 * 返回值:
 *    返回转换后的字符的UTF8编码所占的字节数, 假设出错则返回 0 .
 *
 * 注意:
 *     1. UTF8没有字节序问题, 可是Unicode有字节序要求;
 *        字节序分为大端(Big Endian)和小端(Little Endian)两种;
 *        在Intel处理器中採用小端法表示, 在此採用小端法表示. (低地址存低位)
 *     2. 请保证 pOutput 缓冲区有最少有 6 字节的空间大小!
 ****************************************************************************/
int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,
        int outSize)          
{
    //assert(pOutput != NULL);
    //assert(outSize >= 6);

    if ( unic <= 0x0000007F )
    {
        // * U-00000000 - U-0000007F:  0xxxxxxx
        *pOutput     = (unic & 0x7F);
        return 1;
    }
    else if ( unic >= 0x00000080 && unic <= 0x000007FF )
    {
        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
        *(pOutput+1) = (unic & 0x3F) | 0x80;
        *pOutput     = ((unic >> 6) & 0x1F) | 0xC0;
        return 2;
    }
    else if ( unic >= 0x00000800 && unic <= 0x0000FFFF )
    {
        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
        *(pOutput+2) = (unic & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >>  6) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 12) & 0x0F) | 0xE0;
        return 3;
    }
    else if ( unic >= 0x00010000 && unic <= 0x001FFFFF )
    {
        // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+3) = (unic & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 12) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 18) & 0x07) | 0xF0;
        return 4;
    }
    else if ( unic >= 0x00200000 && unic <= 0x03FFFFFF )
    {
        // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+4) = (unic & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 18) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 24) & 0x03) | 0xF8;
        return 5;
    }
    else if ( unic >= 0x04000000 && unic <= 0x7FFFFFFF )
    {
        // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+5) = (unic & 0x3F) | 0x80;
        *(pOutput+4) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 18) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 24) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 30) & 0x01) | 0xFC;
        return 6;
    }

    return 0;
}
