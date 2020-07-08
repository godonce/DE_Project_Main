

#include "GUI.h"
#include "lcd.h"


#define GUI_NUMBYTES  1024*1024*4
#define GUI_BLOCKSIZE 0x80000

#define LCD_GUI_RAM_BASE  (U32)(LCD_VRAM_BASE_ADDR+(1024*1024*2))


void GUI_X_Config(void) {

  GUI_ALLOC_AssignMemory((void*)LCD_GUI_RAM_BASE, GUI_NUMBYTES);
  GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);

  GUI_SetDefaultFont(GUI_FONT_6X8);
}

