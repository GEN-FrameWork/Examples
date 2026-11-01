/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UI_Console.h
*
* @class      UI_CONSOLE
* @brief      Graphics UI Console Example class
* @ingroup    EXAMPLES
*
* @copyright  EndoraSoft. All rights reserved.
*
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
*
* --------------------------------------------------------------------------------------------------------------------*/

#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"

#include "APPFlowGraphics.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum UI_CONSOLEXFSMEVENTS
{
  UI_CONSOLE_XFSMEVENT_NONE                 = 0 ,
  UI_CONSOLE_XFSMEVENT_INI                      ,
  UI_CONSOLE_XFSMEVENT_END                      ,

  UI_CONSOLE_LASTEVENT
};


enum UI_CONSOLEXFSMSTATES
{
  UI_CONSOLE_XFSMSTATE_NONE                 = 0 ,
  UI_CONSOLE_XFSMSTATE_INI                      ,
  UI_CONSOLE_XFSMSTATE_END                      ,

  UI_CONSOLE_LASTSTATE
};


enum UI_CONSOLE_BUTTONS
{
  UI_CONSOLE_BUTTON_ESC                     = 0 ,
  UI_CONSOLE_BUTTON_A                           ,
  UI_CONSOLE_BUTTON_C                           ,
  UI_CONSOLE_BUTTON_CTRL                        ,
  UI_CONSOLE_BUTTON_SHIFT                       ,
  UI_CONSOLE_BUTTON_MOUSE                       ,
  UI_CONSOLE_BUTTON_TOUCHSCREEN                 ,

  UI_CONSOLE_BUTTON_MAX
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       NL("UI_Console")
#define APPLICATION_NAMEFILE                      NL("ui_console")

#define APPLICATION_OWNER                         NL("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2026

#define APPLICATION_GUI_CONSOLE_VIEWPORT_ID       NL("console_viewport")

// Stress rate: flood the console like a busy XTraceMonitor feed (lines/sec).
#define UI_CONSOLE_DEMO_LINES_PER_SEC             200



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIMER;
class INPBUTTON;
class INPCURSOR;
class UI_XEVENT;
class UI_ELEMENT;
class UI_ELEMENT_TEXT;
class UI_ELEMENT_CONSOLE;
class GRPXEVENT;
class UI_CONSOLE_CFG;

class UI_CONSOLE : public APPFLOWGRAPHICS, public XFSMACHINE
{
  public:
                                    UI_CONSOLE                              ();
    virtual                        ~UI_CONSOLE                              ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();

  private:

    bool                            UpdateInput                             ();
    bool                            UpdateConsoleDemo                       ();

    bool                            Ini_Graphics                            (GRPSCREEN* screen);
    bool                            Ini_Canvas                              (GRPSCREEN* screen);
    bool                            Ini_UserInterface                       (bool on);

    bool                            DrawFrame                               ();

    bool                            Console_Resolve                         ();
    bool                            Console_SeedDemoLines                   ();
    bool                            Console_HandleSelection                 (int cursor_x, int cursor_y, bool shiftdown, bool extending);
    bool                            Console_CopySelection                   ();

    bool                            UserInterface_ElementSelected           (UI_ELEMENT* element);
    bool                            UserInterface_ChangeLiteralText         (UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresult);

    void                            HandleEvent_UserInterface               (UI_XEVENT* event);
    void                            HandleEvent_Graphics                    (GRPXEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);

    void                            Clean                                   ();

    XTIMER*                         xtimer;

    INPBUTTON*                      button[UI_CONSOLE_BUTTON_MAX];
    INPCURSOR*                      cursor;

    UI_ELEMENT_CONSOLE*             consoleelement;

    XDWORD                          demolinecounter;
    XQWORD                          demoline_lastms;

    bool                            selection_dragging;
    XDWORD                          selection_anchor;

    bool                            exitconsole;
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
