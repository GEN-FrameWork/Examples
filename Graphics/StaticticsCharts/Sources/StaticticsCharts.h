/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       StaticticsCharts.h
* 
* @class      STATICTICSCHARTS
* @brief      Graphics Statistics Charts Example class
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
#include "XVector.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "APPFlowGraphics.h"

#include "GRP2DVectorFileRenderAGG.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum STATICTICSCHARTSXFSMEVENTS
{
  STATICTICSCHARTS_XFSMEVENT_NONE                 = 0 ,
  STATICTICSCHARTS_XFSMEVENT_INI                      ,
  STATICTICSCHARTS_XFSMEVENT_END                      ,

  STATICTICSCHARTS_LASTEVENT
};


enum STATICTICSCHARTSXFSMSTATES
{
  STATICTICSCHARTS_XFSMSTATE_NONE                 = 0 ,
  STATICTICSCHARTS_XFSMSTATE_INI                      ,
  STATICTICSCHARTS_XFSMSTATE_END                      ,

  STATICTICSCHARTS_LASTSTATE
};


enum STATICTICSCHARTSTASKID
{
  STATICTICSCHARTSTASKID_UNKNOWN                  = 0 ,
  STATICTICSCHARTSTASKID_CHECKMEMORYSTATUS            ,
};


enum STATICTICSCHARTS_BUTTONS
{
  STATICTICSCHARTS_BUTTON_UP                      = 0 ,
  STATICTICSCHARTS_BUTTON_DOWN                        ,
  STATICTICSCHARTS_BUTTON_LEFT                        ,
  STATICTICSCHARTS_BUTTON_RIGHT                       ,
  STATICTICSCHARTS_BUTTON_SPACE                       ,
  STATICTICSCHARTS_BUTTON_ESC                         ,
  STATICTICSCHARTS_BUTTON_F1                          ,
  STATICTICSCHARTS_BUTTON_F2                          ,
  STATICTICSCHARTS_BUTTON_F5                          ,
  STATICTICSCHARTS_BUTTON_F9                          ,
  STATICTICSCHARTS_BUTTON_PLUS                        ,
  STATICTICSCHARTS_BUTTON_MINUS                       ,

  STATICTICSCHARTS_BUTTON_MOUSE                       ,

  STATICTICSCHARTS_BUTTON_TOUCHSCREEN                 ,

  STATICTICSCHARTS_BUTTON_MAX
};


#define XTHREADGROUPID_STATICTICSCHARTS_DRAWFRAME       XTHREADGROUPID_APPOWNER + 100

#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 1

#define APPLICATION_NAMEAPP                       __L("StaticticsCharts")
#define APPLICATION_NAMEFILE                      __L("staticticscharts")

#define APPLICATION_OWNER                         __L("EndoraSoft")

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
class STATICTICSCHARTS_CFG;

class STATICTICSCHARTS : public APPFLOWGRAPHICS, public XFSMACHINE
{
  public:
                                    STATICTICSCHARTS                              ();
    virtual                        ~STATICTICSCHARTS                              ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();
   
  private:
    
    bool                            UpdateInput                             ();

    bool                            Ini_StaticticCharts                     ();   
    bool                            Ini_Graphics                            (GRPSCREEN* screen);
    bool                            Ini_UserInterface                       (bool on);  


    bool                            DrawFrame                               ();

    bool                            UserInterface_CFGChromes                (GRPSCREEN* screen);

    void                            HandleEvent_UserInterface               (UI_XEVENT* event);
    void                            HandleEvent_Graphics                    (GRPXEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);
    
    void                            Clean                                   ();

    XTIMER*                         xtimer;

    XRAND*                          xrand;

    INPBUTTON*                      button[STATICTICSCHARTS_BUTTON_MAX];
    INPCURSOR*                      cursor;
    
    XDWORD                          indexchart;

    GRPBITMAP*                      backgroundbmp;
    XVECTOR<GRPVECTORFILE*>         vectorfiles; 
    GRP2DVECTORFILERENDERAGG        vectorfile_render;

};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





