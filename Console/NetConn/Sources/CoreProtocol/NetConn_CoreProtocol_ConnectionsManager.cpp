/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_CoreProtocol_ConnectionsManager.cpp
* 
* @class      NETCONN_COREPROTOCOL_CONNECTIONSMANAGER
* @brief      Net Connection Core Protocol Connections Manager class (DIOCoreProtocol example)
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "NetConn_CoreProtocol_ConnectionsManager.h"

#include "XFactory.h"
#include "XPublisher.h"
#include "XRand.h"
#include "XSleep.h"

#include "DIOFactory.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamUARTConfig.h"
#include "DIOStream.h"
#include "DIOCoreProtocol.h"
#include "DIOCoreProtocol_ConnectionsManager_XEvent.h"
#include "DIOCoreProtocol_ConnectionsManager.h"

#include "CipherAES.h"

#include "NetConn_CoreProtocol.h"
#include "NetConn_CoreProtocol_Connection.h"
#include "NetConn_CoreProtocol_RegisterData.h"

#include "NetConn.h"
#include "NetConn_CFG.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::NETCONN_COREPROTOCOL_CONNECTIONSMANAGER()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::NETCONN_COREPROTOCOL_CONNECTIONSMANAGER() 
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::~NETCONN_COREPROTOCOL_CONNECTIONSMANAGER()
* @brief      Destructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::~NETCONN_COREPROTOCOL_CONNECTIONSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::Ini(bool isserver)
* @brief      Ini.
* @ingroup    EXAMPLES
*
* @param[in]  isserver : true when the connection manager works as server; false when it works as client.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::Ini(bool isserver)
{  
  bool status = false;

  // ------------------------------------------------------------------------------------------------------

  protocolCFG.SetIsServer(isserver);  

  protocolCFG.SetIsCipher(true);

  protocolCFG.SetIsCompressHeader(true);
  protocolCFG.SetIsCompressContent(true);

  protocolCFG.SetTimeOutNoResponse(30);
  protocolCFG.SetTimeToEliminateConnectionDisconnect(1);

  // ------------------------------------------------------------------------------------------------------

  if(!APPFLOW_CFG.Connection_GetTransportType()->Compare(__L("TCPIP"), true))
    {
      DIOSTREAMTCPIPCONFIG*  diostreamTCPIPCFG = NULL;
      DIOSTREAM*             diostreamTCPIP    = NULL;
  
      diostreamTCPIPCFG = GEN_NEW DIOSTREAMTCPIPCONFIG();
      if(!diostreamTCPIPCFG)
        {
          return false;
        }

      diostreamTCPIPCFG->SetMode(isserver?DIOSTREAMMODE_SERVERMULTISOCKET:DIOSTREAMMODE_CLIENT);
  
      diostreamTCPIPCFG->SetFromString(APPFLOW_CFG.Connection_GetTransportConfig()->Get());
      if(isserver) diostreamTCPIPCFG->GetRemoteURL()->Set(__L("")); 

      diostreamTCPIP = GEN_DIOFACTORY.CreateStreamIO(diostreamTCPIPCFG);
      if(!diostreamTCPIP) 
        {
          delete diostreamTCPIPCFG;
          return false;
        }

      if(!DIOStream_Add(diostreamTCPIPCFG, diostreamTCPIP))
        {
          delete diostreamTCPIPCFG;
          delete diostreamTCPIP;

          return false;
        }
    }
  
  // ------------------------------------------------------------------------------------------------------

  if(!APPFLOW_CFG.Connection_GetTransportType()->Compare(__L("SERIAL"), true))
    {
      protocolCFG.SetIsEncapsulatedBase64(true);

      protocolCFG.BusMode_Activate(true);

      DIOSTREAMUARTCONFIG*  diostreamUARTCFG = NULL;
      DIOSTREAM*            diostreamUART    = NULL;
  
      diostreamUARTCFG = GEN_NEW DIOSTREAMUARTCONFIG();
      if(!diostreamUARTCFG)
        {
          return false;
        }

      diostreamUARTCFG->SetMode(isserver?DIOSTREAMMODE_SERVER:DIOSTREAMMODE_CLIENT);

      //XSYSTEM_PLATFORM platform = GEN_XSYSTEM.GetPlatform();
      //diostreamUARTCFG->SetFromString(__L("COM3,9600,8,N,1,NONE"));        
      //diostreamUARTCFG->SetFromString(__L("/dev/ttyUSB0,9600,8,N,1,NONE"));  
        
      diostreamUARTCFG->SetFromString(APPFLOW_CFG.Connection_GetTransportConfig()->Get());

      diostreamUART = GEN_DIOFACTORY.CreateStreamIO(diostreamUARTCFG);
      if(!diostreamUART) 
        {
          delete diostreamUARTCFG;
          return false;
        }

      if(!DIOStream_Add(diostreamUARTCFG, diostreamUART))
        {
          delete diostreamUARTCFG;
          delete diostreamUART;

          return false;
        }
    }
  
  // ------------------------------------------------------------------------------------------------------

  status = DIOCOREPROTOCOL_CONNECTIONSMANAGER::Ini(); 

  // ------------------------------------------------------------------------------------------------------

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::End()
* @brief      End.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::End()
{
  bool status =  false;

  status = DIOCOREPROTOCOL_CONNECTIONSMANAGER::End();

  DIOStream_DeleteAll();
    
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCOREPROTOCOL_CONNECTION* NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::CreateConnection()
* @brief      Create connection.
* @ingroup    EXAMPLES
*
* @return     DIOCOREPROTOCOL_CONNECTION* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION* NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::CreateConnection()
{
  NETCONN_COREPROTOCOL_CONNECTION* connection = GEN_NEW NETCONN_COREPROTOCOL_CONNECTION();

  if(NETCONN::IsServer())
    {
      NETCONN_AGENTSTATE* agentstate            = GEN_NEW NETCONN_AGENTSTATE();
      NETCONN_TESTUPDATECLASS* testupdateclass  = GEN_NEW NETCONN_TESTUPDATECLASS();

      if(agentstate) 
        {
          connection->SetAgentState(agentstate);
        }

      if(testupdateclass)  
        {
          connection->SetTestUpdateClass(testupdateclass);
        }
    }
   else
    {
      connection->SetAgentState(netconn->GetAgentState());
      connection->SetTestUpdateClass(netconn->GetTestUpdateClass());
    }

  return connection;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCOREPROTOCOL* NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::CreateProtocol(DIOCOREPROTOCOL_CONNECTION* connection, DIOSTREAM* diostream)
* @brief      Creates a protocol instance.
* @ingroup    EXAMPLES
*
* @param[in]  connection : Connection value used by the operation.
* @param[in]  diostream : Stream used by the protocol.
*
* @return     DIOCOREPROTOCOL* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL* NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::CreateProtocol(DIOCOREPROTOCOL_CONNECTION* connection, DIOSTREAM* diostream)
{
  DIOCOREPROTOCOL* protocol = (DIOCOREPROTOCOL*)GEN_NEW NETCONN_COREPROTOCOL(&protocolCFG, diostream);
  
  if(!protocol)
    {
      return NULL;
    }

  protocol->Commands_Add(NETCONN_COREPROTOCOL_COMMAND_TYPE_GETVERSION, NETCONN_COREPROTOCOL_COMMAND_TYPE_STRING_GETVERSION, DIOCOREPROTOCOL_BIDIRECTIONALITYMODE_BOTH);
  protocol->Commands_Add(NETCONN_COREPROTOCOL_COMMAND_TYPE_OTHERCOMMAND , NETCONN_COREPROTOCOL_COMMAND_TYPE_STRING_OTHERCOMMAND , DIOCOREPROTOCOL_BIDIRECTIONALITYMODE_TOCLIENT);

  NETCONN_COREPROTOCOL_CONNECTION* netconn_connection = (NETCONN_COREPROTOCOL_CONNECTION*)connection;
  if(netconn_connection)
    {   
      protocol->UpdateClass_Add(__L("agentstate"), netconn_connection->GetAgentState(), true, 180);
      protocol->UpdateClass_Add(__L("testupdateclass"), netconn_connection->GetTestUpdateClass(), true, 0, DIOCOREPROTOCOL_UPDATECLASS_FLAG_FORCHANGE);
    }

  return protocol;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::HandleEvent_CoreProtocolConnectionsManager(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Handle event core protocol connections manager.
* @note       INTERNAL  (Only Information)
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::HandleEvent_CoreProtocolConnectionsManager(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  if(!event) 
    {
      return;
    }

  switch(event->GetEventType())
    {
      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CREATECONNECTION  : { DIOCOREPROTOCOL_CONNECTION* connection = event->GetConnection();                                                                                                 
                                                                                if(connection)          
                                                                                  {
                                                                                    if(!connection->GetRegisterData())
                                                                                      {
                                                                                        NETCONN_COREPROTOCOL_REGISTERDATA* registerdata = GEN_NEW NETCONN_COREPROTOCOL_REGISTERDATA();
                                                                                        if(registerdata)
                                                                                          {                                                                                           
                                                                                            connection->SetRegisterData(registerdata);
                                                                                          }
                                                                                      }

                                                                                    XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Net Conn] Create connection"));
                                                                                  }
                                                                              }
                                                                              break;


      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_STATUSCHANGE      : { DIOCOREPROTOCOL_CONNECTION* connection = event->GetConnection();                                                                                                 
                                                                                if(connection)          
                                                                                  {
                                                                                    XSTRING actualstatusstring;
                                                                                    XSTRING nextstatusstring;

                                                                                    connection->Status_GetString(event->GetActualStatus(), actualstatusstring);
                                                                                    connection->Status_GetString(event->GetNextStatus(), nextstatusstring);

                                                                                    XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Net Conn] Change connection status: %s --> %s"), actualstatusstring.Get(), nextstatusstring.Get());
                                                                                  }
                                                                              }
                                                                              break;

      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_READMSG           :
      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG          : { DIOCOREPROTOCOL_CONNECTION* connection = event->GetConnection();                                                                                                 
                                                                                if(connection)          
                                                                                  {
                                                                                    DIOCOREPROTOCOL*         protocol = connection->GetCoreProtocol();
                                                                                    DIOCOREPROTOCOL_MESSAGE* message  = event->GetMsg(); 
                                                                                    if(message && protocol)
                                                                                      {    
                                                                                        DIOCOREPROTOCOL_HEADER* header  = message->GetHeader();
                                                                                        XBUFFER*                content = message->GetContent();

                                                                                        if(protocol && header && content)
                                                                                          {                                                                                            
                                                                                            switch(event->GetEventType())
                                                                                              {
                                                                                                case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_READMSG   : protocol->ShowDebug(false, header, (*content), message->GetSizeAllMessage(), false);        
                                                                                                                                                                break;
    
                                                                                                case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG  : protocol->ShowDebug(true, header, (*content), message->GetSizeAllMessage(), false);  
                                                                                                                                                                break;  
                                                                                              }                                                                                                     
                                                                                          }
                                                                                      }
                                                                                  }

                                                                              }
                                                                              break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN_COREPROTOCOL_CONNECTIONSMANAGER::Clean()
{
  
}



