#ifndef _MICROSDL_EX_H_
#define _MICROSDL_EX_H_

// =======================================================================
// microSDL library (extensions)
// - Calvin Hass
// - http://www.impulseadventure.com/elec/microsdl-sdl-gui.html
//
// - Version 0.5.1    (2016/11/16)
// =======================================================================

// Extended element definitions
// - This file extends the core microSDL functionality with
//   additional widget types

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


// Extended element data structures
// - These data structures are maintained in the microSDL_tsElem
//   structure via the pXData pointer

  
  
// ============================================================================
// Extended Element: Gauge
// ============================================================================

/// Extended data for Gauge element
typedef struct {
  int             nGaugeMin;    ///< Minimum control value
  int             nGaugeMax;    ///< Maximum control value
  int             nGaugeVal;    ///< Current control value
  microSDL_Color  colGauge;     ///< Color of gauge fill bar
  bool            bGaugeVert;   ///< Vertical if true, else Horizontal
} microSDL_tsXGauge;


///
/// Create a Gauge Element
/// - Draws a horizontal or vertical box with a filled region
///   corresponding to the proportion that nVal represents
///   between nMin and nMax.
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nElemId:     Element ID to assign (0..32767 or MSDL_ID_AUTO to autogen)
/// \param[in]  nPage:       Page ID to attach element to
/// \param[in]  pXData:      Ptr to extended element data structure
/// \param[in]  rElem:       Rectangle coordinates defining gauge size
/// \param[in]  nMin:        Minimum value of gauge for nVal comparison
/// \param[in]  nMax:        Maximum value of gauge for nVal comparison
/// \param[in]  colGauge:    Color to fill the gauge with
/// \param[in]  bVert:       Flag to indicate vertical vs horizontal action
///                (true = vertical, false = horizontal)
///
/// \return Pointer to Element or NULL if failure
///
microSDL_tsElem* microSDL_ElemXGaugeCreate(microSDL_tsGui* pGui,int nElemId,int nPage,
  microSDL_tsXGauge* pXData,microSDL_Rect rElem,int nMin,int nMax,int nVal,microSDL_Color colGauge,bool bVert);

///
/// Update a Gauge element's current value
/// - Note that min & max values are assigned in create()
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  nVal:        New value to show in gauge
///
/// \return none
///
void microSDL_ElemXGaugeUpdate(microSDL_tsElem* pElem,int nVal);

///
/// Draw a gauge element on the screen
/// - Called from microSDL_ElemDraw()
///
/// \param[in]  pvGui:       Void ptr to GUI (typecast to microSDL_tsGui*)
/// \param[in]  pvElem:      Void ptr to Element (typecast to microSDL_tsElem*)
///
/// \return true if success, false otherwise
///
bool microSDL_ElemXGaugeDraw(void* pvGui,void* pvElem);



// ============================================================================
// Extended Element: Checkbox
// ============================================================================

/// Checkbox drawing style
typedef enum {
  MSDLX_CHECKBOX_STYLE_BOX,                 ///< Inner box
  MSDLX_CHECKBOX_STYLE_X,                   ///< Crossed
  MSDLX_CHECKBOX_STYLE_ROUND,               ///< Circular
} microSDL_teXCheckboxStyle;

/// Extended data for Checkbox element
typedef struct {
  microSDL_tsGui*             pGui;         ///< Ptr to GUI (for radio group control)
  bool                        bRadio;       ///< Radio-button operation if true
  microSDL_teXCheckboxStyle   nStyle;       ///< Drawing style for element
  bool                        bChecked;     ///< Indicates if it is selected (checked)
  microSDL_Color              colCheck;     ///< Color of checked inner fill
} microSDL_tsXCheckbox;


///
/// Create a Checkbox Element
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nElemId:     Element ID to assign (0..32767 or MSDL_ID_AUTO to autogen)
/// \param[in]  nPage:       Page ID to attach element to
/// \param[in]  pXData:      Ptr to extended element data structure
/// \param[in]  rElem:       Rectangle coordinates defining checkbox size
/// \param[in]  bRadio:      Radio-button functionality if true
/// \param[in]  nStyle:      Drawing style for checkbox / radio button
/// \param[in]  colCheck:    Color for inner fill when checked
/// \param[in]  bChecked:    Default state
///
/// \return Element pointer or NULL if failure
///
microSDL_tsElem* microSDL_ElemXCheckboxCreate(microSDL_tsGui* pGui,int nElemId,int nPage,
  microSDL_tsXCheckbox* pXData,microSDL_Rect rElem,bool bRadio,
  microSDL_teXCheckboxStyle nStyle,microSDL_Color colCheck,bool bChecked);


///
/// Get a Checkbox element's current state
///
/// \param[in]  pElem:       Pointer to Element
///
/// \return Current state
///
bool microSDL_ElemXCheckboxGetState(microSDL_tsElem* pElem);


///
/// Set a Checkbox element's current state
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  bChecked:    New state
///
/// \return none
///
void microSDL_ElemXCheckboxSetState(microSDL_tsElem* pElem,bool bChecked);

///
/// Find the checkbox within a group that has been checked
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nGroupId:    Group ID to search
///
/// \return Element Ptr or NULL if none checked
///
microSDL_tsElem* microSDL_ElemXCheckboxFindChecked(microSDL_tsGui* pGui,int nGroupId);

///
/// Toggle a Checkbox element's current state
///
/// \param[in]  pElem:       Pointer to Element
///
/// \return none
///
void microSDL_ElemXCheckboxToggleState(microSDL_tsElem* pElem);


///
/// Draw a Checkbox element on the screen
/// - Called from microSDL_ElemDraw()
///
/// \param[in]  pvGui:       Void ptr to GUI (typecast to microSDL_tsGui*)
/// \param[in]  pvElem:      Void ptr to Element (typecast to microSDL_tsElem*)
///
/// \return true if success, false otherwise
///
bool microSDL_ElemXCheckboxDraw(void* pvGui,void* pvElem);

///
/// Handle touch events to Checkbox element
/// - Called from microSDL_NotifyElemTouch()
///
/// \param[in]  pvGui:       Void ptr to GUI (typecast to microSDL_tsGui*)
/// \param[in]  pvElem:      Void ptr to Element (typecast to microSDL_tsElem*)
/// \param[in]  eTouch:      Touch event type
/// \param[in]  nRelX:       Touch X coord relative to element
/// \param[in]  nRelY:       Touch Y coord relative to element
///
/// \return true if success, false otherwise
///
bool microSDL_ElemXCheckboxTouch(void* pvGui,void* pvElem,microSDL_teTouch eTouch,int nRelX,int nRelY);


// ============================================================================
// Extended Element: Slider
// ============================================================================

/// Extended data for Slider element
typedef struct {
  // Config
  bool            bVert;          ///< Orientation: true if vertical, else horizontal
  int             nThumbSz;       ///< Size of the thumb control
  int             nPosMin;        ///< Minimum position value of the slider
  int             nPosMax;        ///< Maximum position value of the slider
  // Style config
  unsigned        nTickDiv;       ///< Style: number of tickmark divisions (0 for none)
  int             nTickLen;       ///< Style: length of tickmarks
  microSDL_Color  colTick;        ///< Style: color of ticks
  bool            bTrim;          ///< Style: show a trim color
  microSDL_Color  colTrim;        ///< Style: color of trim
  // State
  int             nPos;           ///< Current position value of the slider
} microSDL_tsXSlider;


///
/// Create a Slider Element
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nElemId:     Element ID to assign (0..32767 or MSDL_ID_AUTO to autogen)
/// \param[in]  nPage:       Page ID to attach element to
/// \param[in]  pXData:      Ptr to extended element data structure
/// \param[in]  rElem:       Rectangle coordinates defining checkbox size
/// \param[in]  nPosMin:     Minimum position value
/// \param[in]  nPosMax:     Maximum position value
/// \param[in]  nPos:        Starting position value
/// \param[in]  nThumbSz:    Size of the thumb control
/// \param[in]  bVert:       Orientation (true for vertical)
///
/// \return Element pointer or NULL if failure
///
microSDL_tsElem* microSDL_ElemXSliderCreate(microSDL_tsGui* pGui,int nElemId,int nPage,
  microSDL_tsXSlider* pXData,microSDL_Rect rElem,int nPosMin,int nPosMax,int nPos,
  unsigned nThumbSz,bool bVert);


///
/// Set a Slider element's current position
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  bTrim:       Show a colored trim?
/// \param[in]  colTrim:     Color of trim
/// \param[in]  nTickDiv:    Number of tick divisions to show (0 for none)
/// \param[in]  nTickLen:    Length of tickmarks
/// \param[in]  colTick:     Color of ticks
///
/// \return none
///
void microSDL_ElemXSliderSetStyle(microSDL_tsElem* pElem,
        bool bTrim,microSDL_Color colTrim,unsigned nTickDiv,
        int nTickLen,microSDL_Color colTick);


///
/// Get a Slider element's current position
///
/// \param[in]  pElem:       Pointer to Element
///
/// \return Current slider position
///
int microSDL_ElemXSliderGetPos(microSDL_tsElem* pElem);


///
/// Set a Slider element's current position
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  nPos:        New position value
///
/// \return none
///
void microSDL_ElemXSliderSetPos(microSDL_tsElem* pElem,int nPos);


///
/// Draw a Slider element on the screen
/// - Called from microSDL_ElemDraw()
///
/// \param[in]  pvGui:       Void ptr to GUI (typecast to microSDL_tsGui*)
/// \param[in]  pvElem:      Void ptr to Element (typecast to microSDL_tsElem*)
///
/// \return true if success, false otherwise
///
bool microSDL_ElemXSliderDraw(void* pvGui,void* pvElem);

///
/// Handle touch events to Slider element
/// - Called from microSDL_NotifyElemTouch()
///
/// \param[in]  pvGui:       Void ptr to GUI (typecast to microSDL_tsGui*)
/// \param[in]  pvElem:      Void ptr to Element (typecast to microSDL_tsElem*)
/// \param[in]  eTouch:      Touch event type
/// \param[in]  nRelX:       Touch X coord relative to element
/// \param[in]  nRelY:       Touch Y coord relative to element
///
/// \return true if success, false otherwise
///
bool microSDL_ElemXSliderTouch(void* pvGui,void* pvElem,microSDL_teTouch eTouch,int nRelX,int nRelY);


// ============================================================================
// Extended Element: SelNum (Number Selector)
// - Demonstration of a compound element consisting of
//   a counter text field along with an increment and
//   decrement button.
// ============================================================================


/// Extended data for SelNum element
typedef struct {

  // Core functionality for SelNum
  int                 nCounter;       ///< Counter for demo purposes
   
  // Internal sub-element members
  microSDL_tsCollect  sCollect;       ///< Collection management for sub-elements
  microSDL_tsElem     asElem[4];      ///< Storage for sub-elements
} microSDL_tsXSelNum;




///
/// Create a SelNum Element
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nElemId:     Element ID to assign (0..32767 or MSDL_ID_AUTO to autogen)
/// \param[in]  nPage:       Page ID to attach element to
/// \param[in]  pXData:      Ptr to extended element data structure
/// \param[in]  rElem:       Rectangle coordinates defining element size
/// \param[in]  nFontId:     Font ID to use for drawing the element
///
/// \return Pointer to Element or NULL if failure
///
microSDL_tsElem* microSDL_ElemXSelNumCreate(microSDL_tsGui* pGui,int nElemId,int nPage,
  microSDL_tsXSelNum* pXData,microSDL_Rect rElem,int nFontId);


///
/// Draw a SelNum element on the screen
/// - Called during redraw
///
/// \param[in]  pvGui:       Void ptr to GUI (typecast to microSDL_tsGui*)
/// \param[in]  pvElem:      Void ptr to Element (typecast to microSDL_tsElem*)
///
/// \return true if success, false otherwise
///
bool microSDL_ElemXSelNumDraw(void* pvGui,void* pvElem);


///
/// Get the current counter associated with SelNum
///
/// \param[in]  pGui:        Ptr to GUI
/// \param[in]  pSelElem:    Ptr to Element
///
/// \return Current counter value
///
int microSDL_ElemXSelNumGetCounter(microSDL_tsGui* pGui,microSDL_tsXSelNum* pSelNum);


///
/// Set the current counter associated with SelNum
///
/// \param[in]  pSelElem:    Ptr to Element
/// \param[in]  nCount:      New counter value
///
/// \return none
///
void microSDL_ElemXSelNumSetCounter(microSDL_tsXSelNum* pSelNum,int nCount);


///
/// Handle a click event within the SelNum
/// - This is called internally by the SelNum touch handler
///
/// \param[in]  pvGui:       Void ptr to GUI (typecast to microSDL_tsGui*)
/// \param[in]  pvElem:      Void ptr to Element (typecast to microSDL_tsElem*)
/// \param[in]  eTouch:      Touch event type
/// \param[in]  nX:          Touch X coord
/// \param[in]  nY:          Touch Y coord
///
/// \return none
///
bool microSDL_ElemXSelNumClick(void* pvGui,void *pvElem,microSDL_teTouch eTouch,int nX,int nY);

///
/// Handle touch (up,down,move) events to SelNum element
/// - Called from microSDL_NotifyElemTouch()
///
/// \param[in]  pvGui:       Void ptr to GUI (typecast to microSDL_tsGui*)
/// \param[in]  pvElem:      Void ptr to Element (typecast to microSDL_tsElem*)
/// \param[in]  eTouch:      Touch event type
/// \param[in]  nRelX:       Touch X coord relative to element
/// \param[in]  nRelY:       Touch Y coord relative to element
///
/// \return true if success, false otherwise
///
bool microSDL_ElemXSelNumTouch(void* pvGui,void* pvElem,microSDL_teTouch eTouch,int nRelX,int nRelY);


// ============================================================================



#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _MICROSDL_EX_H_

