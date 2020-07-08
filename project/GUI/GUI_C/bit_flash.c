#include <stdlib.h>
#include  "datafigures.h"
#include "GUI.h"
#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


/*zhujiemian*/

extern GUI_CONST_STORAGE GUI_BITMAP bmliju_left;



GUI_CONST_STORAGE GUI_BITMAP bmliju_left = {
  70, // xSize
  77, // ySize
  280, // BytesPerLine
  32, // BitsPerPixel
    (unsigned char *)(uint8_t *)liju_left,   // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmxingcheng_left;

GUI_CONST_STORAGE GUI_BITMAP bmxingcheng_left = {
  67, // xSize
  71, // ySize
  268, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)xingcheng_left,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

extern GUI_CONST_STORAGE GUI_BITMAP bmliju_right;
GUI_CONST_STORAGE GUI_BITMAP bmliju_right = {
  76, // xSize
  81, // ySize
  304, // BytesPerLine
  32, // BitsPerPixel
   (unsigned char *)(uint8_t *)liju_right,   // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

#if 1
extern GUI_CONST_STORAGE GUI_BITMAP bmxingcheng_right;
GUI_CONST_STORAGE GUI_BITMAP bmxingcheng_right = {
  67, // xSize
  71, // ySize
  268, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)xingcheng_right,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

#endif
extern GUI_CONST_STORAGE GUI_BITMAP bmNationalFlag;

GUI_CONST_STORAGE GUI_BITMAP bmNationalFlag = {
  22, // xSize
  16, // ySize
  88, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)NationalFlag,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmLocalNoSelected;

GUI_CONST_STORAGE GUI_BITMAP bmLocalNoSelected = {
  27, // xSize
  20, // ySize
  108, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)LocalNoSelected,   // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

extern GUI_CONST_STORAGE GUI_BITMAP bmLocalSelected;

GUI_CONST_STORAGE GUI_BITMAP bmLocalSelected = {
  27, // xSize
  20, // ySize
  108, // BytesPerLine
  32, // BitsPerPixel
   (unsigned char *)(uint8_t *)LocalSelected,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

extern GUI_CONST_STORAGE GUI_BITMAP bmRemoteNoSelected;
GUI_CONST_STORAGE GUI_BITMAP bmRemoteNoSelected = {
  27, // xSize
  20, // ySize
  108, // BytesPerLine
  32, // BitsPerPixel
   (unsigned char *)(uint8_t *)RemoteNoSelected, // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmRemoteSelected;
GUI_CONST_STORAGE GUI_BITMAP bmRemoteSelected = {
  27, // xSize
  20, // ySize
  108, // BytesPerLine
  32, // BitsPerPixel
   (unsigned char *)(uint8_t *)RemoteSelected,   // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmOffNoSelected;
GUI_CONST_STORAGE GUI_BITMAP bmOffNoSelected = {
  27, // xSize
  20, // ySize
  108, // BytesPerLine
  32, // BitsPerPixel
   (unsigned char *)(uint8_t *)OffNoSelected,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

extern GUI_CONST_STORAGE GUI_BITMAP bmOffSelected;
GUI_CONST_STORAGE GUI_BITMAP bmOffSelected = {
  27, // xSize
  20, // ySize
  108, // BytesPerLine
  32, // BitsPerPixel
   (unsigned char *)(uint8_t *)OffSelected,   // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};



//extern GUI_CONST_STORAGE GUI_BITMAP bmbackSel;

GUI_CONST_STORAGE GUI_BITMAP bmbackSel = {
  40, // xSize
  22, // ySize
  160, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)backSel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmbackUnsel;
GUI_CONST_STORAGE GUI_BITMAP bmbackUnsel = {
  40, // xSize
  22, // ySize
  160, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)backUnsel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};



extern GUI_CONST_STORAGE GUI_BITMAP bmhomeSel;


GUI_CONST_STORAGE GUI_BITMAP bmhomeSel = {
  83, // xSize
  29, // ySize
  332, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)homeSel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

extern GUI_CONST_STORAGE GUI_BITMAP bmhomeUnsel;
GUI_CONST_STORAGE GUI_BITMAP bmhomeUnsel = {
  21, // xSize
  20, // ySize
  84, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)homeUnsel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

extern GUI_CONST_STORAGE GUI_BITMAP bmhome_unsel;

GUI_CONST_STORAGE GUI_BITMAP bmhome_unsel = {
  166, // xSize
  23, // ySize
  664, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)home_unsel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmhome_sel;

GUI_CONST_STORAGE GUI_BITMAP bmhome_sel = {
  166, // xSize
  23, // ySize
  664, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)home_sel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

extern GUI_CONST_STORAGE GUI_BITMAP bmShu_Blue;

GUI_CONST_STORAGE GUI_BITMAP bmShu_Blue = {
  42, // xSize
  51, // ySize
  168, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)Shu_Blue,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmShu_Orn;

GUI_CONST_STORAGE GUI_BITMAP bmShu_Orn = {
  42, // xSize
  51, // ySize
  168, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)Shu_Orn, // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmclose_brow;
GUI_CONST_STORAGE GUI_BITMAP bmclose_brow = {
  59, // xSize
  60, // ySize
  236, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)close_brow,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

extern GUI_CONST_STORAGE GUI_BITMAP bmclose_blue;
GUI_CONST_STORAGE GUI_BITMAP bmclose_blue = {
  59, // xSize
  60, // ySize
  236, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)close_blue,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};



extern GUI_CONST_STORAGE GUI_BITMAP bmopen_blue;
GUI_CONST_STORAGE GUI_BITMAP bmopen_blue = {
  60, // xSize
  62, // ySize
  240, // BytesPerLine
  32, // BitsPerPixel
   (unsigned char *)(uint8_t *)open_blue,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmopen_brow;
GUI_CONST_STORAGE GUI_BITMAP bmopen_brow = {
  60, // xSize
  62, // ySize
  240, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)open_brow,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


#if 1

/*************************** End of file ****************************/
extern GUI_CONST_STORAGE GUI_BITMAP bmuser_service;

GUI_CONST_STORAGE GUI_BITMAP bmuser_service = {
  13, // xSize
  18, // ySize
  52, // BytesPerLine
  32, // BitsPerPixel
	(unsigned char *)(uint8_t *)user_service,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

extern GUI_CONST_STORAGE GUI_BITMAP bmuser_expert;

GUI_CONST_STORAGE GUI_BITMAP bmuser_expert = {
  13, // xSize
  18, // ySize
  52, // BytesPerLine
  32, // BitsPerPixel
	(unsigned char *)(uint8_t *)user_expert,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

/*************************** End of file ****************************/


extern GUI_CONST_STORAGE GUI_BITMAP bmuser_watcher;

GUI_CONST_STORAGE GUI_BITMAP bmuser_watcher = {
  13, // xSize
  18, // ySize
  52, // BytesPerLine
  32, // BitsPerPixel
	(unsigned char *)(uint8_t *)user_watcher,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};
extern GUI_CONST_STORAGE GUI_BITMAP bmuser_monitor;

GUI_CONST_STORAGE GUI_BITMAP bmuser_monitor = {
  13, // xSize
  18, // ySize
  52, // BytesPerLine
  32, // BitsPerPixel
	(unsigned char *)(uint8_t *)user_monitor,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};



extern GUI_CONST_STORAGE GUI_BITMAP bmuser_hander;

GUI_CONST_STORAGE GUI_BITMAP bmuser_hander = {
  13, // xSize
  18, // ySize
  52, // BytesPerLine
  32, // BitsPerPixel
	(unsigned char *)(uint8_t *)user_hander,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

extern GUI_CONST_STORAGE GUI_BITMAP bmuser_factory;

GUI_CONST_STORAGE GUI_BITMAP bmuser_factory = {
  13, // xSize
  18, // ySize
  52, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)user_factory,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};



extern GUI_CONST_STORAGE GUI_BITMAP bmiteam_sel;

GUI_CONST_STORAGE GUI_BITMAP bmiteam_sel = {
  24, // xSize
  21, // ySize
  96, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)iteam_sel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmiteam_unsel;

GUI_CONST_STORAGE GUI_BITMAP bmiteam_unsel = {
  24, // xSize
  21, // ySize
  96, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)iteam_unsel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmdrive_quan;

GUI_CONST_STORAGE GUI_BITMAP bmdrive_quan = {
  59, // xSize
  59, // ySize
  236, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)drive_quan,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};
#endif

#if 1
extern GUI_CONST_STORAGE GUI_BITMAP bmleft_back_unsel;
GUI_CONST_STORAGE GUI_BITMAP bmleft_back_unsel = {
  83, // xSize
  29, // ySize
  332, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)left_back_unsel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};



extern GUI_CONST_STORAGE GUI_BITMAP bmleft_back_sel;
GUI_CONST_STORAGE GUI_BITMAP bmleft_back_sel = {
  83, // xSize
  29, // ySize
  332, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)left_back_sel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

#endif



#if  1

extern GUI_CONST_STORAGE GUI_BITMAP bmright_home_sel;
GUI_CONST_STORAGE GUI_BITMAP bmright_home_sel = {
  83, // xSize
  29, // ySize
  332, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)right_home_sel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

/*************************** End of file ****************************/


extern GUI_CONST_STORAGE GUI_BITMAP bmright_home_unsel;
GUI_CONST_STORAGE GUI_BITMAP bmright_home_unsel = {
  83, // xSize
  29, // ySize
  332, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)right_home_unsel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

#endif


#if 1

extern GUI_CONST_STORAGE GUI_BITMAP bmlist_close;

GUI_CONST_STORAGE GUI_BITMAP bmlist_close = {
  22, // xSize
  18, // ySize
  88, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)list_close,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

/*************************** End of file ****************************/

extern GUI_CONST_STORAGE GUI_BITMAP bmlist_open;

GUI_CONST_STORAGE GUI_BITMAP bmlist_open = {
  22, // xSize
  18, // ySize
  88, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)list_open,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

/*************************** End of file ****************************/



#endif


#if 1
extern GUI_CONST_STORAGE GUI_BITMAP bmrect_orange_2num;
extern GUI_CONST_STORAGE GUI_BITMAP bmrect_orange_3num;
extern GUI_CONST_STORAGE GUI_BITMAP bmrect_orange_5num;
GUI_CONST_STORAGE GUI_BITMAP bmrect_orange_2num = {
  70, // xSize
  51, // ySize
  280, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)rect_orange_2num,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};
GUI_CONST_STORAGE GUI_BITMAP bmrect_orange_3num = {
  70, // xSize
  51, // ySize
  280, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)rect_orange_3num,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};
GUI_CONST_STORAGE GUI_BITMAP bmrect_orange_5num = {
  100, // xSize
  51, // ySize
  400, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)rect_orange_5num,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


#endif

#if 1
extern GUI_CONST_STORAGE GUI_BITMAP bmclose;
extern GUI_CONST_STORAGE GUI_BITMAP bmopen;

GUI_CONST_STORAGE GUI_BITMAP bmclose = {
  32, // xSize
  27, // ySize
  128, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)acclose,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

GUI_CONST_STORAGE GUI_BITMAP bmopen = {
  31, // xSize
  27, // ySize
  124, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)acopen,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};
#endif

#if 1

extern GUI_CONST_STORAGE GUI_BITMAP bmqwe;
extern GUI_CONST_STORAGE GUI_BITMAP bmqwer;

GUI_CONST_STORAGE GUI_BITMAP bmqwe = {
  76, // xSize
  83, // ySize
  304, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)acqwe,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

GUI_CONST_STORAGE GUI_BITMAP bmqwer = {
  76, // xSize
  83, // ySize
  304, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)acqwer,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};


extern GUI_CONST_STORAGE GUI_BITMAP bmset_ok;
GUI_CONST_STORAGE GUI_BITMAP bmset_ok = {
  59, // xSize
  55, // ySize
  236, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)(uint8_t *)PHOTO_set_ok,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

#endif