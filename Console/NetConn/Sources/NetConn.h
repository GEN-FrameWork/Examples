/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn.h
* 
* @class      NETCONN
* @brief      Net Connection class (DIOCoreProtocol example)
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

#include "NetConn_CoreProtocol_Response.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


enum NETCONNXFSMEVENTS
{
  NETCONN_XFSMEVENT_NONE                 = 0 ,
  NETCONN_XFSMEVENT_INI                      ,
  NETCONN_XFSMEVENT_UPDATE                   ,
  NETCONN_XFSMEVENT_END                      ,

  NETCONN_LASTEVENT
};


enum NETCONNXFSMSTATES
{
  NETCONN_XFSMSTATE_NONE                 = 0 ,
  NETCONN_XFSMSTATE_INI                      ,
  NETCONN_XFSMSTATE_UPDATE                   ,
  NETCONN_XFSMSTATE_END                      ,

  NETCONN_LASTSTATE
};


enum NETCONNTASKID
{
  NETCONNTASKID_UNKNOWN                  = 0 ,
  NETCONNTASKID_CHECKINTERNETCONNECTION      ,
  NETCONNTASKID_CHECKMEMORYSTATUS            ,
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       _L("Net Conn")
#define APPLICATION_NAMEFILE                      _L("netconn")

#define APPLICATION_OWNER                         _L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2024



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class DIOINTERNET;
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERNETCONNECTION;
class DIOSCRAPERWEBPUBLICIP;
class DIOSCRAPERWEBGEOLOCATIONIP;
class DIOSCRAPERWEBUSERAGENTID;
class DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT;
class APPFLOWINTERNETSERVICES;
class NETCONN_COREPROTOCOL_CONNECTIONSMANAGER;
class NETCONN_AGENTSTATE;
class NETCONN_TESTUPDATECLASS;

class NETCONN : public APPFLOWCONSOLE, public XOBSERVER, public XFSMACHINE
{
  public:
                                                NETCONN                                       ();
    virtual                                    ~NETCONN                                       ();

    bool                                        InitFSMachine                                 ();

    bool                                        AppProc_Ini                                   ();
    bool                                        AppProc_FirstUpdate                           ();
    bool                                        AppProc_Update                                ();
    bool                                        AppProc_End                                   ();

    static bool                                 IsServer                                      ();      

    bool                                        KeyValidSecuences                             (int key); 

    NETCONN_AGENTSTATE*                         GetAgentState                                 ();    
    NETCONN_TESTUPDATECLASS*                    GetTestUpdateClass                            (); 

    bool                                        Show_TestUpdateClass                          ();
    bool                                        Show_ConnectionsStatus                        ();
    bool                                        Show_AllStatus                                ();

  private:

    void                                        HandleEvent_CoreProtocolConnectionManager     (DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event);    
    void                                        HandleEvent                                   (XEVENT* xevent);

    void                                        Clean                                         ();

    XTIMER*                                     xtimerupdateconsole;
    XMUTEX*                                     xmutexshowallstatus;    

    bool                                        modeserver;   

    NETCONN_COREPROTOCOL_CONNECTIONSMANAGER*    connectionsmanager; 
    NETCONN_COREPROTOCOL_RESPONSE               response;

    NETCONN_AGENTSTATE*                         agentstate;
    NETCONN_TESTUPDATECLASS*                    testupdateclass;
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

extern NETCONN* netconn;



