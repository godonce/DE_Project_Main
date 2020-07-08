

#ifdef WIN32

#include "LCD_SIM.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       SIM_X_Config
*
* Purpose:
*   Called during the initialization process in order to configure
*   the simulator.
*/
void SIM_X_Config() {
  SIM_GUI_SetTransColor(0xff0000);     // Define the transparent color
}


#else

void SIMConf_C(void); // Avoid empty object files
void SIMConf_C(void) {}
#endif

#

/*************************** End of file ****************************/
