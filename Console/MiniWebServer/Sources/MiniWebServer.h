/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       MiniWebServer.h
* 
* @class      MINIWEBSERVER
* @brief      Example Mini Web Server class
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

#include "DIOStream.h"
#include "DIOURL.h"

#include "APPFlowConsole.h"

#include "MiniWebServer_APIRest.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum MINIWEBSERVERXFSMEVENTS
{
  MINIWEBSERVER_XFSMEVENT_NONE                  = 0 ,
  MINIWEBSERVER_XFSMEVENT_INI                       ,
  MINIWEBSERVER_XFSMEVENT_END                       ,

  MINIWEBSERVER_LASTEVENT
};


enum MINIWEBSERVERXFSMSTATES
{
  MINIWEBSERVER_XFSMSTATE_NONE                  = 0 ,
  MINIWEBSERVER_XFSMSTATE_INI                       ,
  MINIWEBSERVER_XFSMSTATE_END                       ,

  MINIWEBSERVER_LASTSTATE
};


enum MINIWEBSERVERTASKID
{
  MINIWEBSERVER_TASKID_UNKNOWN                  = 0 ,
  MINIWEBSERVER_TASKID_CHECKMEMORYSTATUS
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       NL("Mini Web Server")
#define APPLICATION_NAMEFILE                      NL("miniwebserver")

#define APPLICATION_OWNER                         NL("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2018



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class DIOWEBSERVER_XEVENT;
class APPFLOWINTERNETSERVICES;
class APPFLOWWEBSERVER;

class MINIWEBSERVER : public APPFLOWCONSOLE, public XOBSERVER, public XFSMACHINE
{
  public:
                                    MINIWEBSERVER                           ();
    virtual                        ~MINIWEBSERVER                           ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();

    bool                            KeyValidSecuences                       (int key);
   
    bool                            Show_WebServerConfig                    ();
    bool                            Show_WebSocketConfig                    ();

    bool                            Show_AllStatus                          ();

  private:

    void                            HandleEvent_WebServer                   (DIOWEBSERVER_XEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);

    void                            Clean                                   ();

    XTIMER*                         xtimerupdateconsole;
    XMUTEX*                         xmutexshowallstatus;

    APPFLOWWEBSERVER*               appwebserver;
    MINIWEBSERVER_APIREST*          apirest;
    APPFLOWWEBSERVER*               appwebsocket;
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





