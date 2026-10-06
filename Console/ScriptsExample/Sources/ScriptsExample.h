/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       ScriptsExample.h
* 
* @class      Scripts Example class 
* @brief      Scripts Example 
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

#include "Script_XEvent.h"

#include "APPFlowConsole.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum SCRIPTSEXAMPLEXFSMEVENTS
{
  SCRIPTSEXAMPLE_XFSMEVENT_NONE                = 0 ,
  SCRIPTSEXAMPLE_XFSMEVENT_INI                     ,
  SCRIPTSEXAMPLE_XFSMEVENT_UPDATE                  ,
  SCRIPTSEXAMPLE_XFSMEVENT_END                     ,

  SCRIPTSEXAMPLE_LASTEVENT
};


enum SCRIPTSEXAMPLEXFSMSTATES
{
  SCRIPTSEXAMPLE_XFSMSTATE_NONE                = 0 ,
  SCRIPTSEXAMPLE_XFSMSTATE_INI                     ,
  SCRIPTSEXAMPLE_XFSMSTATE_UPDATE                  ,
  SCRIPTSEXAMPLE_XFSMSTATE_END                     ,

  SCRIPTSEXAMPLE_LASTSTATE
};


enum SCRIPTSEXAMPLETASKID
{
  SCRIPTSEXAMPLETASKID_UNKNOWN                 = 0 ,
  SCRIPTSEXAMPLETASKID_CHECKMEMORYSTATUS           ,
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       _L("Scripts Example")
#define APPLICATION_NAMEFILE                      _L("scriptsexample")

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
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERNETCONNECTION;
class DIOSCRAPERWEBPUBLICIP;
class DIOSCRAPERWEBGEOLOCATIONIP;
class DIOSCRAPERWEBUSERAGENTID;
class GRPBITMAPSECUENCE;
class GRPXEVENT;
class SCRIPT;
class SCRIPTSEXAMPLE_CFG;

class SCRIPTSEXAMPLE : public APPFLOWCONSOLE, public XFSMACHINE
{
  public:
                                    SCRIPTSEXAMPLE                          ();
    virtual                        ~SCRIPTSEXAMPLE                          ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();

    bool                            KeyValidSecuences                       (int key);
   
    bool                            Show_AppStatus                          ();
    bool                            Show_AllStatus                          ();

  private:

    void                            Clean                                   ();

    static void                     AdjustLibraries                         (SCRIPT* script);

    void                            HandleEvent_Script                      (SCRIPT_XEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);

    XTIMER*                         xtimerupdateconsole;
    XTIMER*                         xtimerscriptrun;

    XMUTEX*                         xmutexshowallstatus;
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





