/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Message.h
* 
* @class      UI_MESSAGE
* @brief      Graphics UI Message Example class
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



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum UI_MESSAGEXFSMEVENTS
{
  UI_MESSAGE_XFSMEVENT_NONE                 = 0 ,
  UI_MESSAGE_XFSMEVENT_INI                      ,
  UI_MESSAGE_XFSMEVENT_END                      ,

  UI_MESSAGE_LASTEVENT
};


enum UI_MESSAGEXFSMSTATES
{
  UI_MESSAGE_XFSMSTATE_NONE                 = 0 ,
  UI_MESSAGE_XFSMSTATE_INI                      ,
  UI_MESSAGE_XFSMSTATE_END                      ,

  UI_MESSAGE_LASTSTATE
};


enum UI_MESSAGETASKID
{
  UI_MESSAGETASKID_UNKNOWN                  = 0 ,
  UI_MESSAGETASKID_CHECKMEMORYSTATUS            ,
};


enum UI_MESSAGE_BUTTONS
{
  UI_MESSAGE_BUTTON_UP                      = 0 ,
  UI_MESSAGE_BUTTON_DOWN                        ,
  UI_MESSAGE_BUTTON_LEFT                        ,
  UI_MESSAGE_BUTTON_RIGHT                       ,
  UI_MESSAGE_BUTTON_SPACE                       ,
  UI_MESSAGE_BUTTON_ESC                         ,
  UI_MESSAGE_BUTTON_F1                          ,
  UI_MESSAGE_BUTTON_F2                          ,
  UI_MESSAGE_BUTTON_F5                          ,
  UI_MESSAGE_BUTTON_F9                          ,
  UI_MESSAGE_BUTTON_PLUS                        ,
  UI_MESSAGE_BUTTON_MINUS                       ,

  UI_MESSAGE_BUTTON_MOUSE                       ,

  UI_MESSAGE_BUTTON_TOUCHSCREEN                 ,

  UI_MESSAGE_BUTTON_MAX
};




#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 1

#define APPLICATION_NAMEAPP                       __L("UI_Message")
#define APPLICATION_NAMEFILE                      __L("ui_message")

#define APPLICATION_OWNER                         __L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2018

#define XTHREADGROUPID_UI_MESSAGE_DRAWFRAME       XTHREADGROUPID_APPOWNER + 100

#define APPLICATION_GUI_MESSAGE_VIEWPORT_ID       __L("message_viewport")



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
class INPBUTTON;
class INPCURSOR;
class UI_XEVENT;
class UI_ELEMENT;
class UI_ELEMENT_TEXT;
class GRPXEVENT;
class GRPBITMAP;
class GRPBITMAPSEQUENCE;
class UI_MESSAGE_CFG;

class UI_MESSAGE : public APPFLOWGRAPHICS, public XFSMACHINE
{
  public:
                                    UI_MESSAGE                              ();
    virtual                        ~UI_MESSAGE                              ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();
   
  private:
    
    bool                            UpdateInput                             ();

    bool                            Ini_Graphics                            (GRPSCREEN* screen);
    bool                            Ini_Canvas                              (GRPSCREEN* screen);
    bool                            Ini_UserInterface                       (bool on);

    bool                            DrawFrame                               ();

    bool                            UserInterface_ElementSelected           (UI_ELEMENT* element);
    bool                            UserInterface_ChangeLiteralText         (UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresult);

    void                            HandleEvent_UserInterface               (UI_XEVENT* event);
    void                            HandleEvent_Graphics                    (GRPXEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);
    
    void                            Clean                                   ();

    XTIMER*                         xtimer;

    XRAND*                          xrand;

    INPBUTTON*                      button[UI_MESSAGE_BUTTON_MAX];
    INPCURSOR*                      cursor;

    bool                            exitmessage;

    XSTRING                         makeaction;
    
    GRPBITMAP*                      testbmp;
};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





