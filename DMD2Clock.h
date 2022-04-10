/*-- ndak dipakai bikin crash parah --*/
#include <SPI.h>
#include <DMD2.h>
//#include <fonts/SystemFont5x7.h>
#include <fonts/angka6x13.h>
#include <fonts/Font3x5.h>
#include <fonts/Droid_Sans_16.h>
#include <fonts/Droid_Sans_12.h>
//#include <fonts/Droid_Sans_24.h>
//#include <fonts/Arial14.h>
#include <fonts/Arial_Black_16.h>
//#include <fonts/fonts4x7.h>


#define pin_A 16
#define pin_B 12
#define pin_sck 0
#define pin_noe 15
#define panel_width 1
#define panel_height 1

// SETUP DMD
SPIDMD dmd(panel_width, panel_height, pin_noe, pin_A, pin_B,
           pin_sck);  // diarahkan pin GPIO pada nodeMCU
DMD_TextBox box(dmd); // "box" provides a text box to automatically write
// to/scroll the display
