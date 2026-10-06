/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetCapture.h
* 
* @class      NETCAPTURE
* @brief      Net Capture Example class
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

#include "APPFlowConsole.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum NETCAPTUREXFSMEVENTS
{
  NETCAPTURE_XFSMEVENT_NONE                = 0 ,
  NETCAPTURE_XFSMEVENT_INI                     ,
  NETCAPTURE_XFSMEVENT_UPDATE                  ,
  NETCAPTURE_XFSMEVENT_END                     ,

  NETCAPTURE_LASTEVENT
};


enum NETCAPTUREXFSMSTATES
{
  NETCAPTURE_XFSMSTATE_NONE                = 0 ,
  NETCAPTURE_XFSMSTATE_INI                     ,
  NETCAPTURE_XFSMSTATE_UPDATE                  ,
  NETCAPTURE_XFSMSTATE_END                     ,

  NETCAPTURE_LASTSTATE
};

#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       _L("Net Capture")
#define APPLICATION_NAMEFILE                      _L("netcapture")

#define APPLICATION_OWNER                         _L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2024

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIMER;
class XMUTEX;
class NETCAPTURE_CFG;
class NETCAPTURE_SNIFFER;

class NETCAPTURE : public APPFLOWCONSOLE, public XFSMACHINE
{
  public:
                                    NETCAPTURE                  ();
    virtual                        ~NETCAPTURE                  ();

    bool                            InitFSMachine               ();

    bool                            AppProc_Ini                 ();
    bool                            AppProc_FirstUpdate         ();
    bool                            AppProc_Update              ();
    bool                            AppProc_LastUpdate          ();
    bool                            AppProc_End                 ();

    bool                            KeyValidSecuences           (int key);
    
    bool                            Show_AppStatus              ();
    bool                            Show_AllStatus              ();

  private:
    
    void                            HandleEvent                 (XEVENT* xevent);  

    void                            Clean                       ();

    XTIMER*                         xtimerupdateconsole;  
    XMUTEX*                         xmutexshowallstatus;    

    NETCAPTURE_SNIFFER*             sniffer;  
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





