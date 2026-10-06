/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       WindowChromes.h
* 
* @class      WINDOWCHROMES
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

enum WINDOWCHROMESXFSMEVENTS
{
  WINDOWCHROMES_XFSMEVENT_NONE                 = 0 ,
  WINDOWCHROMES_XFSMEVENT_INI                      ,
  WINDOWCHROMES_XFSMEVENT_END                      ,

  WINDOWCHROMES_LASTEVENT
};


enum WINDOWCHROMESXFSMSTATES
{
  WINDOWCHROMES_XFSMSTATE_NONE                 = 0 ,
  WINDOWCHROMES_XFSMSTATE_INI                      ,
  WINDOWCHROMES_XFSMSTATE_END                      ,

  WINDOWCHROMES_LASTSTATE
};


enum WINDOWCHROMESTASKID
{
  WINDOWCHROMESTASKID_UNKNOWN                  = 0 ,
  WINDOWCHROMESTASKID_CHECKMEMORYSTATUS            ,
};


enum WINDOWCHROMES_BUTTONS
{
  WINDOWCHROMES_BUTTON_UP                      = 0 ,
  WINDOWCHROMES_BUTTON_DOWN                        ,
  WINDOWCHROMES_BUTTON_LEFT                        ,
  WINDOWCHROMES_BUTTON_RIGHT                       ,
  WINDOWCHROMES_BUTTON_SPACE                       ,
  WINDOWCHROMES_BUTTON_ESC                         ,
  WINDOWCHROMES_BUTTON_F1                          ,
  WINDOWCHROMES_BUTTON_F2                          ,
  WINDOWCHROMES_BUTTON_F5                          ,
  WINDOWCHROMES_BUTTON_F9                          ,
  WINDOWCHROMES_BUTTON_PLUS                        ,
  WINDOWCHROMES_BUTTON_MINUS                       ,

  WINDOWCHROMES_BUTTON_MOUSE                       ,

  WINDOWCHROMES_BUTTON_TOUCHSCREEN                 ,

  WINDOWCHROMES_BUTTON_MAX
};


#define XTHREADGROUPID_WINDOWCHROMES_DRAWFRAME       XTHREADGROUPID_APPOWNER + 100

#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 1

#define APPLICATION_NAMEAPP                       _L("WindowChromes")
#define APPLICATION_NAMEFILE                      _L("windowchromes")

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
class WINDOWCHROMES_CFG;

class WINDOWCHROMES : public APPFLOWGRAPHICS, public XFSMACHINE
{
  public:
                                    WINDOWCHROMES                              ();
    virtual                        ~WINDOWCHROMES                              ();

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

    void                            HandleEvent_UserInterface               (UI_XEVENT* event);
    void                            HandleEvent_Graphics                    (GRPXEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);
    
    void                            Clean                                   ();

    XTIMER*                         xtimer;

    XRAND*                          xrand;

    INPBUTTON*                      button[WINDOWCHROMES_BUTTON_MAX];
    INPCURSOR*                      cursor;

    XSTRING                         makeaction;

    GRPVECTORFILE*                  vectorfile; 
    GRP2DVECTORFILERENDERAGG        vectorfile_render;
    
    GRPBITMAP*                      testbmp;

};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





