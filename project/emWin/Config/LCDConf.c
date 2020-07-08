

#include "GUI.h"
#include "GUIDRV_Lin.h"
#include "lcd.h"

#define XSIZE_PHYS                        LCD_WIDTH
#define YSIZE_PHYS                        LCD_HEIGHT

#define VXSIZE_PHYS                       (XSIZE_PHYS)
#define VYSIZE_PHYS                       (YSIZE_PHYS)

#define COLOR_CONVERSION GUICC_888

#define DISPLAY_DRIVER &GUIDRV_Lin_32_API
#define PIXEL_WIDTH                     2

#define VRAM_ADDR    LCD_VRAM_BASE_ADDR


#define NUM_BUFFERS  1 
#define NUM_VSCREENS 1 

#ifndef   VRAM_ADDR
  #define VRAM_ADDR 0 // TBD by customer: This has to be the frame buffer start address
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif
#ifndef   NUM_VSCREENS
  #define NUM_VSCREENS 1
#else
  #if (NUM_VSCREENS <= 0)
    #error At least one screeen needs to be defined!
  #endif
#endif
#if (NUM_VSCREENS > 1) && (NUM_BUFFERS > 1)
  #error Virtual screens and multiple buffers are not allowed!
#endif

#define WIDTH       XSIZE_PHYS  /* Screen Width (in pixels)         */
#define HEIGHT      YSIZE_PHYS  /* Screen Hight (in pixels)         */
    #define TOUCH_LEFT   TOUCH_X_MIN
    #define TOUCH_RIGHT  TOUCH_X_MAX
    #define TOUCH_TOP    TOUCH_Y_MIN
    #define TOUCH_BOTTOM TOUCH_Y_MAX


static void _SetDisplayOrigin(int x, int y) {
  (void)x;
  LPC_LCD->UPBASE = LCD_VRAM_BASE_ADDR + (y * XSIZE_PHYS * PIXEL_WIDTH);  
}

void LCD_X_Config(void) {
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  if (LCD_GetSwapXY()) {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS * NUM_VSCREENS, XSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS * NUM_VSCREENS);
  }
  LCD_SetVRAMAddrEx(0, (void *)VRAM_ADDR);
}

int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;

  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
    LCD_SetSizeEx (XSIZE_PHYS, YSIZE_PHYS, LayerIndex);
    LCD_SetVSizeEx(VXSIZE_PHYS, VYSIZE_PHYS, LayerIndex);
    LCD_SetVRAMAddrEx(LayerIndex, (void*)LCD_VRAM_BASE_ADDR);
    Lcd_drive_Init();
    
    return 0;
  }
  case LCD_X_SETORG: {
    LCD_X_SETORG_INFO * p;
    p = (LCD_X_SETORG_INFO *)pData;
    _SetDisplayOrigin(p->xPos, p->yPos);
    return 0;
  }

  default:
    r = -1;
  }
  return r;
}



