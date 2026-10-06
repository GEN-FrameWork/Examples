/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Options.h
* 
* @class      UI_OPTIONS
* @brief      Graphics UI Options Example class
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
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "APPFlowGraphics.h"

#include "GRP2DVectorFileRenderAGG.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum UI_OPTIONSXFSMEVENTS
{
  UI_OPTIONS_XFSMEVENT_NONE                 = 0 ,
  UI_OPTIONS_XFSMEVENT_INI                      ,
  UI_OPTIONS_XFSMEVENT_END                      ,

  UI_OPTIONS_LASTEVENT
};


enum UI_OPTIONSXFSMSTATES
{
  UI_OPTIONS_XFSMSTATE_NONE                 = 0 ,
  UI_OPTIONS_XFSMSTATE_INI                      ,
  UI_OPTIONS_XFSMSTATE_END                      ,

  UI_OPTIONS_LASTSTATE
};


enum UI_OPTIONSTASKID
{
  UI_OPTIONSTASKID_UNKNOWN                  = 0 ,
  UI_OPTIONSTASKID_CHECKMEMORYSTATUS            ,
};


enum UI_OPTIONS_BUTTONS
{
  UI_OPTIONS_BUTTON_UP                      = 0 ,
  UI_OPTIONS_BUTTON_DOWN                        ,
  UI_OPTIONS_BUTTON_LEFT                        ,
  UI_OPTIONS_BUTTON_RIGHT                       ,
  UI_OPTIONS_BUTTON_SPACE                       ,
  UI_OPTIONS_BUTTON_ESC                         ,
  UI_OPTIONS_BUTTON_F1                          ,
  UI_OPTIONS_BUTTON_F2                          ,
  UI_OPTIONS_BUTTON_F5                          ,
  UI_OPTIONS_BUTTON_F9                          ,
  UI_OPTIONS_BUTTON_PLUS                        ,
  UI_OPTIONS_BUTTON_MINUS                       ,

  UI_OPTIONS_BUTTON_MOUSE                       ,

  UI_OPTIONS_BUTTON_TOUCHSCREEN                 ,

  UI_OPTIONS_BUTTON_MAX
};


#define XTHREADGROUPID_UI_OPTIONS_DRAWFRAME       XTHREADGROUPID_APPOWNER + 100

#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 1

#define APPLICATION_NAMEAPP                       _L("UI_Options")
#define APPLICATION_NAMEFILE                      _L("ui_options")

#define APPLICATION_OWNER                         _L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2018



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class XRAND;
class DIOINTERNET;
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERNETCONNECTION;
class DIOSCRAPERWEBPUBLICIP;
class DIOSCRAPERWEBGEOLOCATIONIP;
class DIOSCRAPERWEBUSERAGENTID;
class GRPBITMAPSECUENCE;
class GRPXEVENT;
class GRPBITMAP;
class GRPBITMAPSEQUENCE;
class GRPVECTORFILESVG;
class INPBUTTON;
class INPCURSOR;
class UI_XEVENT;
class UI_ELEMENT;
class UI_ELEMENT_TEXT;
class UI_OPTIONS_CFG;

class UI_OPTIONS : public APPFLOWGRAPHICS, public XFSMACHINE
{
  public:
                                    UI_OPTIONS                              ();
    virtual                        ~UI_OPTIONS                              ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();
   
  private:
    
    bool                            UpdateInput                             ();

    bool                            Ini_Graphics                            (GRPSCREEN* screen);
    bool                            Ini_UserInterface                       (bool on);

    bool                            DrawFrame                               ();

    bool                            UserInterface_ElementSelected           (UI_ELEMENT* element);
    bool                            UserInterface_ChangeLiteralText         (UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresult);
    bool                            UserInterface_CFGChromes                (GRPSCREEN* screen);    

    bool                            UnitTest_AVIVideoWrite                  ();

    void                            HandleEvent_UserInterface               (UI_XEVENT* event);
    void                            HandleEvent_Graphics                    (GRPXEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);
    
    void                            Clean                                   ();

    XTIMER*                         xtimer;

    XRAND*                          xrand;

    INPBUTTON*                      button[UI_OPTIONS_BUTTON_MAX];
    INPCURSOR*                      cursor;

    XSTRING                         makeaction;

    GRPVECTORFILE*                  vectorfile; 
    GRP2DVECTORFILERENDERAGG        vectorfile_render;
    
    GRPBITMAP*                      testbmp;

};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





