//
// microSDL GUI Library Examples
// - Calvin Hass
// - http://www.impulseadventure.com/elec/microsdl-sdl-gui.html
// - Example 04: Dynamic content
//   Demonstrates push buttons, checkboxes and slider controls
//

#include "microsdl.h"
#include "microsdl_ex.h"

// Defines for resources
#define FONT_DROID_SANS "/usr/share/fonts/truetype/droid/DroidSans.ttf"

// Enumerations for pages, elements, fonts, images
enum {E_PG_MAIN};
enum {E_ELEM_BOX,E_ELEM_BTN_QUIT,E_ELEM_TXT_COUNT,E_ELEM_PROGRESS,
      E_ELEM_CHECK1,E_ELEM_RADIO1,E_ELEM_RADIO2,E_ELEM_SLIDER,E_ELEM_TXT_SLIDER};
enum {E_FONT_BTN,E_FONT_TXT};
enum {E_GROUP1};

bool                  m_bQuit = false;

// Free-running counter for display
unsigned              m_nCount = 0;

// Instantiate the GUI
#define MAX_FONT      10
microSDL_tsGui        m_gui;
microSDL_tsFont       m_asFont[MAX_FONT];
microSDL_tsXGauge     m_sXGauge;
microSDL_tsXCheckbox  m_asXCheck[3];
microSDL_tsXSlider    m_sXSlider;

#define MAX_PAGE            1
#define MAX_ELEM_PG_MAIN    30
microSDL_tsPage             m_asPage[MAX_PAGE];
microSDL_tsElem             m_asPageElem[MAX_ELEM_PG_MAIN];

#define MAX_STR             100

// Button callbacks
bool CbBtnQuit(void* pvGui,void *pvElem,microSDL_teTouch eTouch,int nX,int nY)
{
  if (eTouch == MSDL_TOUCH_UP_IN) {
    m_bQuit = true;
  }
  return true;
}


// Create page elements
bool InitOverlays()
{
  microSDL_tsElem*  pElem;
  
  microSDL_PageAdd(&m_gui,E_PG_MAIN,m_asPageElem,MAX_ELEM_PG_MAIN);

  
  // Background flat color
  microSDL_SetBkgndColor(&m_gui,MSDL_COL_GRAY_DK);
  
  // Create background box
  pElem = microSDL_ElemCreateBox(&m_gui,E_ELEM_BOX,E_PG_MAIN,(microSDL_Rect){10,50,300,150});
  microSDL_ElemSetCol(pElem,MSDL_COL_WHITE,MSDL_COL_BLACK,MSDL_COL_BLACK);
  
  // Create Quit button with text label
  pElem = microSDL_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_QUIT,E_PG_MAIN,
    (microSDL_Rect){160,80,80,40},"Quit",E_FONT_BTN,&CbBtnQuit);

  // Create counter
  pElem = microSDL_ElemCreateTxt(&m_gui,MSDL_ID_AUTO,E_PG_MAIN,(microSDL_Rect){20,60,50,10},
    "Count:",E_FONT_TXT);
  pElem = microSDL_ElemCreateTxt(&m_gui,E_ELEM_TXT_COUNT,E_PG_MAIN,(microSDL_Rect){80,60,50,10},
    "",E_FONT_TXT);
  microSDL_ElemSetTxtCol(pElem,MSDL_COL_YELLOW);

  // Create progress bar
  pElem = microSDL_ElemCreateTxt(&m_gui,MSDL_ID_AUTO,E_PG_MAIN,(microSDL_Rect){20,80,50,10},
    "Progress:",E_FONT_TXT);
  pElem = microSDL_ElemXGaugeCreate(&m_gui,E_ELEM_PROGRESS,E_PG_MAIN,&m_sXGauge,
    (microSDL_Rect){80,80,50,10},0,100,0,MSDL_COL_GREEN_DK,false);
  
  // Create checkbox 1
  pElem = microSDL_ElemCreateTxt(&m_gui,MSDL_ID_AUTO,E_PG_MAIN,(microSDL_Rect){20,100,20,20},
    "Check1:",E_FONT_TXT);
  pElem = microSDL_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK1,E_PG_MAIN,&m_asXCheck[0],
    (microSDL_Rect){80,100,20,20},false,MSDLX_CHECKBOX_STYLE_X,MSDL_COL_BLUE_LT,false);

  // Create radio 1
  pElem = microSDL_ElemCreateTxt(&m_gui,MSDL_ID_AUTO,E_PG_MAIN,(microSDL_Rect){20,135,20,20},
    "Radio1:",E_FONT_TXT);
  pElem = microSDL_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO1,E_PG_MAIN,&m_asXCheck[1],
    (microSDL_Rect){80,135,20,20},true,MSDLX_CHECKBOX_STYLE_ROUND,MSDL_COL_ORANGE,false);
  microSDL_ElemSetGroup(pElem,E_GROUP1);

  // Create radio 2
  pElem = microSDL_ElemCreateTxt(&m_gui,MSDL_ID_AUTO,E_PG_MAIN,(microSDL_Rect){20,160,20,20},
    "Radio2:",E_FONT_TXT);
  pElem = microSDL_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO2,E_PG_MAIN,&m_asXCheck[2],
    (microSDL_Rect){80,160,20,20},true,MSDLX_CHECKBOX_STYLE_ROUND,MSDL_COL_ORANGE,false);
  microSDL_ElemSetGroup(pElem,E_GROUP1);
    
  // Create slider
  pElem = microSDL_ElemXSliderCreate(&m_gui,E_ELEM_SLIDER,E_PG_MAIN,&m_sXSlider,
    (microSDL_Rect){160,140,100,20},0,100,60,5,false);
  microSDL_ElemXSliderSetStyle(pElem,true,(microSDL_Color){0,0,128},10,
          5,(microSDL_Color){64,64,64});
  pElem = microSDL_ElemCreateTxt(&m_gui,E_ELEM_TXT_SLIDER,E_PG_MAIN,(microSDL_Rect){160,160,60,20},
    "Slider: ???",E_FONT_TXT);

  return true;
}


int main( int argc, char* args[] )
{
  bool                bOk = true;
  char                acTxt[100];

  // -----------------------------------
  // Initialize

  microSDL_InitEnv(&m_gui);

  // Initialize the collection
  if (!microSDL_Init(&m_gui,m_asPage,MAX_PAGE,m_asFont,MAX_FONT,NULL,0)) { exit(1); }
  

  microSDL_InitTs(&m_gui,"/dev/input/touchscreen");

  // Load Fonts
  bOk = microSDL_FontAdd(&m_gui,E_FONT_BTN,FONT_DROID_SANS,12);
  if (!bOk) { fprintf(stderr,"ERROR: FontAdd failed\n"); exit(1); }
  bOk = microSDL_FontAdd(&m_gui,E_FONT_TXT,FONT_DROID_SANS,10);
  if (!bOk) { fprintf(stderr,"ERROR: FontAdd failed\n"); exit(1); }


  // -----------------------------------
  // Start display
  InitOverlays();

  // Start up display on main page
  microSDL_SetPageCur(&m_gui,E_PG_MAIN);

  // Save some element references for quick access
  microSDL_tsElem*  pElemCnt        = microSDL_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_COUNT);
  microSDL_tsElem*  pElemProgress   = microSDL_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_PROGRESS);
  microSDL_tsElem*  pElemSlider     = microSDL_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_SLIDER);
  microSDL_tsElem*  pElemSliderTxt  = microSDL_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_SLIDER);

  // -----------------------------------
  // Main event loop
  
  m_bQuit = false;
  while (!m_bQuit) {

    // General counter
    m_nCount++;

    // -----------------------------------

    // Update elements on active page
    snprintf(acTxt,MAX_STR,"%u",m_nCount);
    microSDL_ElemSetTxtStr(pElemCnt,acTxt);

    microSDL_ElemXGaugeUpdate(pElemProgress,((m_nCount/200)%100));
    
    // TODO: Replace with Slider callback
    int nPos = microSDL_ElemXSliderGetPos(pElemSlider);  
    snprintf(acTxt,MAX_STR,"Slider: %u",nPos);
    microSDL_ElemSetTxtStr(pElemSliderTxt,acTxt);
    
    // Periodically call microSDL update function    
    microSDL_Update(&m_gui);

  } // bQuit

  // Read checkbox state
  // - Either read individual checkboxes
  //   bool bCheck = microSDL_ElemXCheckboxGetState(&m_gui,E_ELEM_CHECK1);
  // - Or find one in the group that was checked (eg. for radio buttons)
  //   microSDL_tsElem* pElem = microSDL_ElemXCheckboxFindChecked(&m_gui,MSDL_GROUP_ID_NONE);

  // -----------------------------------
  // Close down display

  microSDL_Quit(&m_gui);

  return 0;
}

