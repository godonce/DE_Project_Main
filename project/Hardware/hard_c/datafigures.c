#include  "datafigures.h"
#include  "define.h"
#include  "assert.h"

EEPROM       eeprom;
WRITE_EEPROM       write_to_eeprom;
KEY          key_mlx90363;
DATA_FIGURES data_figures;
FLAG_FIGURES flag_figures;
Timer        timer;
Stateserror  states_error;
LEDSTATES    ledstates;
PowerBoard   powerboard;
REMOTE       remote_conntrol;
FLASH_flag   flash_flag;
STATES       states;
SET_END      set_end;
MOTOR_RUN    motorset;
LCD          lcd;
USART        uart3;
USART2       uart2;
ENCODER      encoder;
I_0420       ai_o420;
DIAGNOSE     diagnose;
EXTERN_IO    ext_IO;
PASS_WORD password;
LED          led;
USB_0420   usb_0420;
USB_TORQUE_vol usb_torque_vol;
USB_TORQUE_cur usb_torque_cur;

void init_figures(void)
{
	diagnose.switch_num=1;
	diagnose.switch_num_old=1;
}

 void Utf8ToUnicode(char* unicode, char *utf8)
{
    char *pchar = utf8;
    int nBytes = 0;
     
    if (0 == (*utf8 & 0x80)) 
    {
        nBytes = 1;
        unicode[0] = *utf8;
    }
    else
    {
        int i;
        if ( (*utf8 & 0xf0) == 0xe0 ) 
        {
            nBytes  = 3;
            unicode[0] = ((utf8[0] & 0x0f) <<4) + ((utf8[1] & 0x3c) >>2);
            unicode[1] = ((utf8[1] & 0x03) <<6) + (utf8[2] & 0x3f);
        }
        else
        {         
            nBytes = 0;
            unicode[0] = '?';
            return;
        }
    }
 
    return;
}


int UTF8_to_Unicode(char *dst, char *src)
{
    int i = 0, unicode = 0, ii, iii;
    int codeLen = 0;
    
    while ( *src )
    {
        if(0 == (src[0] & 0x80))
        {
            codeLen = 1;
            unicode = src[0];
        }
        else if(0xC0 == (src[0] & 0xE0) && 0x80 == (src[1] & 0xC0))
        {// 双字节
            codeLen = 2;
            unicode = (int)((((int)src[0] & 0x001F) << 6) | ((int)src[1] & 0x003F));
        }
        else if(0xE0 == (src[0] & 0xF0) && 0x80 == (src[1] & 0xC0) && 0x80 == (src[2] & 0xC0))
        {// 三字节
            codeLen = 3;
            ii = (((int)src[0] & 0x000F) << 12);
            iii = (((int)src[1] & 0x003F) << 6);
            unicode = ii|iii|((int)src[2] & 0x003F);
            unicode = (int)((((int)src[0] & 0x000F) << 12) | (((int)src[1] & 0x003F) << 6) | ((int)src[2] & 0x003F));
        }
        else if(0xF0 == (src[0] & 0xF0) && 0x80 == (src[1] & 0xC0) && 0x80 == (src[2] & 0xC0) && 0x80 == (src[3] & 0xC0))
        {// 四字节
            codeLen = 4;
            unicode = (((int)(src[0] & 0x07)) << 18) | (((int)(src[1] & 0x3F)) << 12) | (((int)(src[2] & 0x3F)) << 6) | (src[3] & 0x3F);
        }
        else
        {
            break;
        }
        src += codeLen;
        if (unicode < 0x80)
        {
            if (i == 0 && unicode == 0x20)
            {
                continue;
            }
        }
        i += 2;
        *dst++ = (char)(unicode&0xff);
        *dst++ = (char)((unicode>>8)&0xff);
    } 
    *dst = 0;
    
    return i;
}


 unsigned short UTF8decodeUNICODE(void *d, unsigned char *s, unsigned short len)
{
         unsigned short b_len = 0;
         unsigned short *unicode = ( unsigned short *)d;

        while(len)
        {
                if(!*s)break;
                if(*s >= 0xFC)
                {
                        *unicode  = (s[0] & 0x01) << 30;
                        *unicode |= (s[1] & 0x3f) << 24;
                        *unicode |= (s[2] & 0x3f) << 18;
                        *unicode |= (s[3] & 0x3f) << 12;
                        *unicode |= (s[4] & 0x3f) << 6;
                        *unicode |= (s[5] & 0x3f);
                        unicode++;
                        b_len += 2;
                        len   -= 6;
                        s     += 6;
                }
                else if(*s >= 0xF8)
                {
                        *unicode  = (s[0] & 0x03) << 24;
                        *unicode |= (s[1] & 0x3f) << 18;
                        *unicode |= (s[2] & 0x3f) << 12;
                        *unicode |= (s[3] & 0x3f) << 6;
                        *unicode |= (s[4] & 0x3f);
                        unicode++;
                        b_len += 2;
                        len   -= 5;
                        s     += 5;
                }
                else if(*s >= 0xF0)
                {
                        *unicode  = (s[0] & 0x07) << 18;
                        *unicode |= (s[1] & 0x3f) << 12;
                        *unicode |= (s[2] & 0x3f) << 6;
                        *unicode |= (s[3] & 0x3f);
                        unicode++;
                        b_len += 2;
                        len   -= 4;
                        s     += 4;
                }
                else if(*s >= 0xE0)
                {
                        *unicode  = (s[0] & 0x0F) << 12;
                        *unicode |= (s[1] & 0x3f) << 6;
                        *unicode |= (s[2] & 0x3f);
                        unicode++;
                        b_len += 2;
                        len   -= 3;
                        s     += 3;
                }
                else if(*s >= 0xC0)
                {
                        *unicode  = (s[0] & 0x1F) << 6;
                        *unicode |= (s[1] & 0x3f);
                        unicode++;
                        b_len += 2;
                        len   -= 2;
                        s     += 2;
                }
                else
                {
                        *unicode = s[0];
                        unicode++;
                        b_len += 2;
                        len   -= 1;
                        s     += 1;
                }
        }
        *unicode = 0;

        return b_len;
}

 void Utf8ToUnicode1(char* unicode, char *utf8)
{
    char *pchar = utf8;
    int nBytes = 0;
     
    if (0 == (*utf8 & 0x80)) 
    {
        nBytes = 1;
        unicode[0] = *utf8;
    }
    else
    {
        int i;
 
        if ( (*utf8 & 0xf0) == 0xe0 ) 
        {
            nBytes  = 3;
            unicode[0] = ((utf8[0] & 0x0f) <<4) + ((utf8[1] & 0x3c) >>2);
            unicode[1] = ((utf8[1] & 0x03) <<6) + (utf8[2] & 0x3f);
        }
        else
        {
            
            nBytes = 0;
            unicode[0] = '?';
            return;
        }
    }
 
    return;
}




