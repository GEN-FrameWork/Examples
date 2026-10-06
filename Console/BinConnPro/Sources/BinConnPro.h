/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro.h
*
* @class      BINCONNPRO
* @brief      Example Binary Connexion Protocol class
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
*---------------------------------------------------------------------------------------------------------------------*/

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

enum BINCONNPROXFSMEVENTS
{
  BINCONNPRO_XFSMEVENT_NONE                 = 0 ,
  BINCONNPRO_XFSMEVENT_INI                      ,
  BINCONNPRO_XFSMEVENT_END                      ,

  BINCONNPRO_LASTEVENT
};


enum BINCONNPROXFSMSTATES
{
  BINCONNPRO_XFSMSTATE_NONE                 = 0 ,
  BINCONNPRO_XFSMSTATE_INI                      ,
  BINCONNPRO_XFSMSTATE_END                      ,

  BINCONNPRO_LASTSTATE
};


enum BINCONNPROTASKID
{
  BINCONNPROTASKID_UNKNOWN                  = 0 ,
  BINCONNPROTASKID_CHECKINTERNETCONNECTION      ,
  BINCONNPROTASKID_CHECKMEMORYSTATUS            ,
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       _L("Binary Connexion Protocol")
#define APPLICATION_NAMEFILE                      _L("binconnpro")

#define APPLICATION_OWNER                         _L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2018



#define BINCONNPRO_OPENSEARCHPROTOCOLCONNECTION   if(connectionsmanager)                                                                                                              \
                                                    {                                                                                                                                 \
                                                      for(int c=0; c<connectionsmanager->ProtocolConnections_GetNAvailable(); c++)                                                    \
                                                        {                                                                                                                             \
                                                          DIOPROTOCOL_CONNECTION* _protocolconnection = connectionsmanager->ProtocolConnections_Get(c);                                \
                                                          if(_protocolconnection)                                                                                                     \
                                                            {                                                                                                                         \
                                                              BINCONNPRO_PROTOCOL* _protocol = (BINCONNPRO_PROTOCOL*)_protocolconnection->GetDIOProtocol();                           \
                                                              if(_protocol)                                                                                                           \
                                                                {                                                                                                                     \
                                                                  BINCONNPRO_APPLICATIONDATA* _applicationdata = (BINCONNPRO_APPLICATIONDATA*)_protocol->GetApplicationData();        \
                                                                  if(_applicationdata)                                                                                                \
                                                                    {


#define BINCONNPRO_CLOSESEARCHPROTOCOLCONNECTION                    } \
                                                                }     \
                                                            }         \
                                                        }             \
                                                    }

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
class DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT;
class APPFLOWINTERNETSERVICES;
class BINCONNPRO_PROTOCOL;
class BINCONNPRO_APPLICATIONDATA;
class BINCONNPRO_CONNECTIONSMANAGER;

class BINCONNPRO : public APPFLOWCONSOLE, public XOBSERVER, public XFSMACHINE
{
  public:
                                    BINCONNPRO                              ();
    virtual                        ~BINCONNPRO                              ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();

    bool                            KeyValidSecuences                       (int key);

    bool                            Show_ConnectionsStatus                  ();
    bool                            Show_DeviceConnectedStatus              ();
    bool                            Show_AllStatus                          ();

  private:

    bool                            InitializeProtocolConnectionServer      (BINCONNPRO_PROTOCOL* protocol, BINCONNPRO_APPLICATIONDATA* applicationdata);
    bool                            InitializeProtocolConnectionClient      (BINCONNPRO_PROTOCOL* protocol, BINCONNPRO_APPLICATIONDATA* applicationdata);

    void                            HandleEvent_ServerProtocolConnections   (DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event);
    void                            HandleEvent_ClientProtocolConnections   (DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);

    void                            Clean                                   ();

    XTIMER*                         xtimerupdateconsole;
    XMUTEX*                         xmutexshowallstatus;    

    bool                            modeserver;
    BINCONNPRO_CONNECTIONSMANAGER*  connectionsmanager;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/


