/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn.cpp
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "NetConn.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "VersionFrameWork.h"

#include "XPath.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XFactory.h"
#include "XRand.h"
#include "XDir.h"
#include "XString.h"
#include "XSystem.h"
#include "XLog.h"
#include "XConsole.h"
#include "XFileTXT.h"
#include "XFileCSV.h"
#include "XFileXML.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XScheduler.h"
#include "XScheduler_XEvent.h"
#include "XConsole.h"
#include "XThread.h"
#include "XTrace.h"
#include "XObserver.h"

#include "HashMD5.h"

#include "DIOFactory.h"
#include "DIOStreamCipher.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"
#include "DIOCoreProtocol_Connection.h"
#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "DIOCoreProtocol_ConnectionsManager_XEvent.h"

#include "APPFlowLog.h"
#include "APPFlowInternetServices.h"
#include "APPFlowExtended.h"

#include "NetConn_CFG.h"
#include "NetConn_CoreProtocol.h"
#include "NetConn_CoreProtocol_Connection.h"
#include "NetConn_CoreProtocol_ConnectionsManager.h"
#include "NetConn_CoreProtocol_Response.h"

#include "NetConn_AgentState.h"
#include "NetConn_TestUpdateClass.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(NETCONN, netconn)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN::NETCONN()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN::NETCONN() : XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN::~NETCONN()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN::~NETCONN()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::InitFSMachine()
{
  if(!AddState( NETCONN_XFSMSTATE_NONE            ,
                NETCONN_XFSMEVENT_INI             , NETCONN_XFSMSTATE_INI             ,
                NETCONN_XFSMEVENT_END             , NETCONN_XFSMSTATE_END             ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( NETCONN_XFSMSTATE_INI             ,
                NETCONN_XFSMEVENT_UPDATE          , NETCONN_XFSMSTATE_UPDATE          ,
                NETCONN_XFSMEVENT_END             , NETCONN_XFSMSTATE_END             ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( NETCONN_XFSMSTATE_UPDATE          ,                
                NETCONN_XFSMEVENT_END             , NETCONN_XFSMSTATE_END             ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( NETCONN_XFSMSTATE_END             ,
                NETCONN_XFSMEVENT_NONE            , NETCONN_XFSMSTATE_NONE            ,
                NETCONN_XFSMEVENT_INI             , NETCONN_XFSMSTATE_INI             ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::AppProc_Ini()
{  
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status = false;

  //-------------------------------------------------------------------------------------------------
 
  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk(); 

 //--------------------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), NETCONN_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_ENG);

  //--------------------------------------------------------------------------------------------------

  if(GetExecParams())
    {
      XSTRING* param = (XSTRING*)GetExecParams()->Get(0);
      if(param)
        {
          modeserver = APPFLOW_CFG.Connection_IsServer();

          if(!param->Compare(__L("SERVER"), true))  
            {
              modeserver = true;
            }

          if(!param->Compare(__L("CLIENT"), true))  
            {
              modeserver = false;
            }
        }
    }

  //--------------------------------------------------------------------------------------------------

  Application_GetName()->AddFormat(__L("%s %s"), APPLICATION_NAMEAPP, modeserver?__L("Server"):__L("Client")); 

  GEN_SET_VERSION(Application_GetName()->Get(), APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)
  
  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------------------

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  //--------------------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG, this);

  //--------------------------------------------------------------------------------------------------

  SetEvent(NETCONN_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::AppProc_FirstUpdate()
{
  XSTRING string;
  XSTRING stringresult;
  bool    status = false;

  //--------------------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;
  
  //--------------------------------------------------------------------------------------------------

  if(!modeserver)
    {
      agentstate = GEN_NEW NETCONN_AGENTSTATE();
      if(agentstate)
        {
          agentstate->Update();          
        }

      testupdateclass = GEN_NEW NETCONN_TESTUPDATECLASS();
      if(testupdateclass)
        {
          testupdateclass->Update();
        }
    }

  //--------------------------------------------------------------------------------------------------

  connectionsmanager = GEN_NEW NETCONN_COREPROTOCOL_CONNECTIONSMANAGER();
  if(connectionsmanager)
    {
      if(!connectionsmanager->Ini(modeserver))
        {
          return false;
        }

      SubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_COMMANDRESPONSE , connectionsmanager);     
      SubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_UPDATECLASS     , connectionsmanager);     
      SubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_ASKUPDATECLASS  , connectionsmanager);     
    }

  //--------------------------------------------------------------------------------------------------
  
  //console->PrintMessage(__L(" "), 0, false, true);
  //console->WaitKey(__L("  Pulsa una tecla para continuar... (%d)"), 1, false, 5);

  //--------------------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::AppProc_Update()
{
  if(GetEvent()==NETCONN_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case NETCONN_XFSMSTATE_NONE       : break;

          case NETCONN_XFSMSTATE_INI        : break;

          case NETCONN_XFSMSTATE_UPDATE     : if(GetExitType() == APPFLOWBASE_EXITTYPE_UNKNOWN)
                                                {
                                                  if(xtimerupdateconsole)
                                                    {
                                                      if(xtimerupdateconsole->GetMeasureMilliSeconds() >= 100)
                                                        {
                                                          Show_AllStatus();
                                                          xtimerupdateconsole->Reset(); 
                                                        }

                                                      if(console->KBHit())
                                                        {
                                                          int key = console->GetChar();
                                                          KeyValidSecuences(key);
                                                        }
                                                    }
                                                }
                                             break;

          case NETCONN_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<NETCONN_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case NETCONN_XFSMSTATE_NONE   : break;

              case NETCONN_XFSMSTATE_INI    : SetEvent(NETCONN_XFSMEVENT_UPDATE);
                                              break;

              case NETCONN_XFSMSTATE_UPDATE : break;

              case NETCONN_XFSMSTATE_END    : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;


  //--------------------------------------------------------------------------------------

  SetEvent(NETCONN_XFSMEVENT_END);

  //--------------------------------------------------------------------------------------

  if(connectionsmanager)
    {
      UnSubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_COMMANDRESPONSE , connectionsmanager);
      UnSubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_UPDATECLASS     , connectionsmanager);
      UnSubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_ASKUPDATECLASS  , connectionsmanager);
      
      connectionsmanager->End();
      delete connectionsmanager;
      connectionsmanager = NULL;        
    }

  //--------------------------------------------------------------------------------------

  if(xmutexshowallstatus)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexshowallstatus);
      xmutexshowallstatus = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(xtimerupdateconsole)
    {
      GEN_XFACTORY.DeleteTimer(xtimerupdateconsole);
      xtimerupdateconsole = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(!modeserver)
    {      
      if(agentstate)
        {
          delete agentstate;
          agentstate = NULL;  
        }

      if(testupdateclass)
        {
          delete testupdateclass;
          testupdateclass = NULL;
        }
    }

  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPEnd();
  APPFLOW_EXTENDED.DelInstance();  
  APPFLOW_CFG.DelInstance();

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::IsServer()
* @brief      Checks if the application is running as server.
* @ingroup    EXAMPLES
*
* @return     bool : true if the condition is met; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::IsServer()
{
  return netconn->modeserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::KeyValidSecuences(int key)
* @brief      Processes valid key sequences.
* @ingroup    EXAMPLES
*
* @param[in]  key : Key code to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::KeyValidSecuences(int key)
{
  XCHAR character = (XCHAR)key;

  if((character<32) || (character>127)) character = __C('?');
  APPFLOW_LOG_ENTRY(XLOGLEVEL_WARNING, APPFLOW_CFG_LOG_SECTIONID_STATUSAPP, false, __L("Key pressed: 0x%02X [%c]"), key, character);

  console->Printf(__L("\r \r"));

  switch(key)
    {
      case 0x1B : // ESC Exit application
                  SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                  break;

      case 'T'  : if(connectionsmanager)
                    { 
                      DIOCOREPROTOCOL_CONNECTION* connection = connectionsmanager->Connections_Get((XDWORD)0);
                      XSTRING                     result;
                      bool                        status;

                      if(!connection)
                        {
                          break;
                        }

                      status = connection->Command_Do(NETCONN_COREPROTOCOL_COMMAND_TYPE_GETVERSION, result, 10);
                      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[NetConn Command Get version] Result: \"%s\""), status?result.Get():__L("Error!"));                        
                    }
                  break;

      case 'Y'  : if(connectionsmanager && modeserver)
                    { 
                      DIOCOREPROTOCOL_CONNECTION* connection = connectionsmanager->Connections_Get((XDWORD)0);
                      XSTRING                     result;
                      bool                        status;

                      if(!connection)
                        {
                          break;
                        }

                      status = connection->Command_Do(NETCONN_COREPROTOCOL_COMMAND_TYPE_OTHERCOMMAND, result, 10);
                      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[NetConn Command Other command] Result: \"%s\""), status?result.Get():__L("Error!"));
                    }
                  break;


      case 'U'  : if(connectionsmanager)
                    { 
                      NETCONN_COREPROTOCOL_CONNECTION*  connection  = (NETCONN_COREPROTOCOL_CONNECTION*)connectionsmanager->Connections_Get((XDWORD)0);                                                                
                      bool                              status      = false;
  
                      if(!connection)
                        {
                          break;
                        }

                      status = connection->UpdateClass_Do(__L("testupdateclass"), connection->GetTestUpdateClass(), 10);                                            
                      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[NetConn Update class Test Update Class Client->Server] Result: \"%s\""), status?__L("Ok"):__L("Error!"));
                    }
                  break;

      case 'A'  : if(connectionsmanager)
                    { 
                      NETCONN_COREPROTOCOL_CONNECTION*  connection  = (NETCONN_COREPROTOCOL_CONNECTION*)connectionsmanager->Connections_Get((XDWORD)0);                                                                
                      bool                              status      = false;

                      if(!connection)
                        {
                          break;
                        }
                        
                      status = connection->UpdateClass_DoAsk(__L("testupdateclass"), connection->GetTestUpdateClass(), 10);                                            
                      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[NetConn Update class Test Update Class Server Ask Client] Result: \"%s\""), status?__L("Ok"):__L("Error!"));
                    }
                  break;

   
      case 'O'  : if(connectionsmanager && !modeserver)
                    { 
                      NETCONN_COREPROTOCOL_CONNECTION*  connection  = (NETCONN_COREPROTOCOL_CONNECTION*)connectionsmanager->Connections_Get((XDWORD)0);                                                                
                      bool                              status      = false;

                      if(!connection)
                        {
                          break;
                        }

                      status = connection->GetTestUpdateClass()->Update();                                            
                      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[NetConn Update class Test Update Class Client->Server] Result: \"%s\""), status?__L("Ok"):__L("Error!"));
                    }
                  break;

      case 'D'  : if(connectionsmanager)
                    { 
                      NETCONN_COREPROTOCOL_CONNECTION*  connection  = (NETCONN_COREPROTOCOL_CONNECTION*)connectionsmanager->Connections_Get((XDWORD)0);  
                      bool                              status      = true;
  
                      if(!connection)
                        {
                          break;
                        }

                      status = connection->Disconnect();
                                                      
                      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[NetConn Command Disconnected] Result: \"%s\""), status?__L("Ok!"):__L("Error!"));
                    }
                  break;



    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_AGENTSTATE* NETCONN::GetAgentState()
* @brief      Gets the agent state object.
* @ingroup    EXAMPLES
*
* @return     NETCONN_AGENTSTATE* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_AGENTSTATE* NETCONN::GetAgentState()
{
  return agentstate;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_TESTUPDATECLASS* NETCONN::GetTestUpdateClass()
* @brief      Gets the test update object.
* @ingroup    EXAMPLES
*
* @return     NETCONN_TESTUPDATECLASS* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_TESTUPDATECLASS* NETCONN::GetTestUpdateClass()
{
  return testupdateclass;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::Show_TestUpdateClass()
* @brief      Shows test update class information.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::Show_TestUpdateClass()
{ 
  XSTRING string;
  XSTRING string2;

  if(!connectionsmanager)
    {
      return false;
    }

  if(modeserver)
    {
      return false;
    }

  string  = __L("Client Data");
  string2.Format(__L("number %d"), GetTestUpdateClass()->GetNumber());   
  Show_Line(string, string2);

  string  = __L("");
  string2.Format(__L("string \"%s\""), GetTestUpdateClass()->GetString()->Get());   
  Show_Line(string, string2);

  console->Printf(__L("\n"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::Show_ConnectionsStatus()
* @brief      Shows connection status information.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::Show_ConnectionsStatus()
{ 
  XSTRING string;
  XSTRING string2;

  if(!connectionsmanager)
    {
      return false;
    }

  DIOCOREPROTOCOL_CFG* protocolCFG = connectionsmanager->GetProtocolCFG();
  if(!protocolCFG)
    {
      return false;
    }

  string  = __L("Connexion mode");
  string2.Format(__L("%s - %s : %s"), protocolCFG->GetIsServer()?__L("Server"):__L("Client"), APPFLOW_CFG.Connection_GetTransportType()->Get(), APPFLOW_CFG.Connection_GetTransportConfig()->Get());

  Show_Line(string, string2);

  if(connectionsmanager)
    {
      if(connectionsmanager->Connections_GetXMutex())
        {
          connectionsmanager->Connections_GetXMutex()->Lock();
        }
   
      for(XDWORD c=0; c<connectionsmanager->Connections_GetAll()->GetSize(); c++)
        {
          NETCONN_COREPROTOCOL_CONNECTION*  connection = (NETCONN_COREPROTOCOL_CONNECTION*)connectionsmanager->Connections_GetAll()->Get(c);
          XSTRING                           connectionID;
          XSTRING                           measurestatus;
          XSTRING                           measurewithoutconnexion;
          XSTRING                           statusstring;

          if(connection)
            {                                                  
              if((connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_READY)        || 
                 (connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_INSTABILITY)  ||    
                 (connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_DISCONNECTED))
                {                      
                  connection->GetXTimerStatus()->GetMeasureString(measurestatus);         
                  connection->GetXTimerWithoutConnexion()->GetMeasureString(measurewithoutconnexion);    
                  connection->Status_GetString(statusstring);                  
                  connection->GetIDConnection()->GetToString(connectionID);

                  if(modeserver)
                    {    
                      if(connection->GetTestUpdateClass())  
                        {
                          if(!c)
                            {
                              console->Printf(__L(" Connexions: \n"));
                            } 

                          string.Format(__L(" %03d %-10s %-20s %-15s %d,\"%s\"\n"), c+1, measurestatus.Get(), connectionID.Get(), statusstring.Get(), connection->GetTestUpdateClass()->GetNumber(), connection->GetTestUpdateClass()->GetString()->Get());   
                          console->Printf(string.Get());
                        }
                    }
                    else 
                    {
                      if(!c)
                        {
                          console->Printf(__L(" Connexions: \n"));
                        } 

                      string.Format(__L(" %03d %-10s %-20s %-15s\n"), c+1, measurestatus.Get(), connectionID.Get(), statusstring.Get());   
                      console->Printf(string.Get());
                    }                              
                }
            }
        }

      console->Printf(__L("\n"));
      
      if(connectionsmanager->Connections_GetXMutex())
        {
          connectionsmanager->Connections_GetXMutex()->UnLock();
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::Show_AllStatus()
* @brief      Shows all status information.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::Show_AllStatus()
{
  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  APPFLOW_EXTENDED.ShowAll();
  
  Show_TestUpdateClass();
  Show_ConnectionsStatus();

  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN::HandleEvent_CoreProtocolConnectionManager(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Handle event core protocol connection manager.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN::HandleEvent_CoreProtocolConnectionManager(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_COMMANDRESPONSE : if(!response.CommandResponse(event))
                                                                              {
                                                                                event->GetContentResponseString()->Format(__L("[Error] Unkown command !!!"));
                                                                              }
                                                                            break;  

      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_UPDATECLASS     :
      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_ASKUPDATECLASS  : if(!response.UpdateClassResponse(event))
                                                                              {
                                                                                event->GetContentResponseString()->Format(__L("[Error] Unkown class !!!"));
                                                                              }                                                                            
                                                                            break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;
  
  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_COREPROTOCOLCONNECTIONSMANAGER   : { DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event = (DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT*)xevent;
                                                            if(!event) return;

                                                            HandleEvent_CoreProtocolConnectionManager(event);
                                                          }
                                                          break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN::Clean()
{
  xtimerupdateconsole         = NULL;
  xmutexshowallstatus         = NULL;

  modeserver                  = false;
 
  connectionsmanager          = NULL; 

  agentstate                  = NULL;
  testupdateclass             = NULL;
}



