/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       MiniWebServer.cpp
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "MiniWebServer.h"

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
#include "XPathsManager.h"
#include "XFileTXT.h"
#include "XFileCSV.h"
#include "XFileXML.h"
#include "XFileJSON.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"
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
#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"
#include "DIOWebServer_XEvent.h"
#include "DIODynDNS_Manager.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "APPFlowBase.h"
#include "APPFlowLog.h"
#include "APPFlowInternetServices.h"
#include "APPFlowWebServer.h"
#include "APPFlowExtended.h"

#include "MiniWebServer_CFG.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(MINIWEBSERVER, miniwebserver)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MINIWEBSERVER::MINIWEBSERVER()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
MINIWEBSERVER::MINIWEBSERVER() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MINIWEBSERVER::~MINIWEBSERVER()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
MINIWEBSERVER::~MINIWEBSERVER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MINIWEBSERVER::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::InitFSMachine()
{
  if(!AddState( MINIWEBSERVER_XFSMSTATE_NONE            ,
                MINIWEBSERVER_XFSMEVENT_INI             , MINIWEBSERVER_XFSMSTATE_INI           ,
                MINIWEBSERVER_XFSMEVENT_END             , MINIWEBSERVER_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( MINIWEBSERVER_XFSMSTATE_INI             ,
                MINIWEBSERVER_XFSMEVENT_NONE            , MINIWEBSERVER_XFSMSTATE_NONE          ,
                MINIWEBSERVER_XFSMEVENT_END             , MINIWEBSERVER_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( MINIWEBSERVER_XFSMSTATE_END             ,
                MINIWEBSERVER_XFSMEVENT_NONE            , MINIWEBSERVER_XFSMSTATE_NONE          ,
                MINIWEBSERVER_XFSMEVENT_INI             , MINIWEBSERVER_XFSMSTATE_INI           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MINIWEBSERVER::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  Application_GetName()->Set(APPLICATION_NAMEAPP);

  //--------------------------------------------------------------------------------------------------

  // ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  // ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_WEB, APPFLOW_DEFAULT_DIRECTORY_WEB);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_CERTIFICATES, APPFLOW_DEFAULT_DIRECTORY_CERTIFICATES);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------------------

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  //--------------------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), MINIWEBSERVER_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);

  //--------------------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG, this);

  //--------------------------------------------------------------------------------------------------

  SetEvent(MINIWEBSERVER_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MINIWEBSERVER::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::AppProc_FirstUpdate()
{
  XSTRING string;   
  XSTRING string2;
  XSTRING stringresult;
  bool    status = false;

  //--------------------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;

  //--------------------------------------------------------------------------------------------------

  status = false;

  if(APPFLOW_CFG.WebServer_GetPort())
    {
      string2.Format(__L("Inicializando Web Server "));
      
      #ifdef DIO_STREAMTLS_ACTIVE
      string2.AddFormat(__L(" %s"), (APPFLOW_CFG.WebServer_IsTLS()?__L(" (TLS)"):__L("")));     
      #endif
      
      string.Format(APPFLOWCONSOLE_DEFAULT_MESSAGEMASK, string2.Get());
      
      console->PrintMessage(string.Get(), 1, true, false);

      appwebserver = GEN_NEW APPFLOWWEBSERVER();
      if(appwebserver) status = true;

      if(status) status = appwebserver->Ini(&APPFLOW_CFG, true, false, false);

      stringresult = (status)?__L("Ok."):__L("ERROR!");
      console->PrintMessage(stringresult.Get(), 0, false, true);

      if(status)
        {
          SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST, (XSUBJECT *)appwebserver);
          SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE, (XSUBJECT *)appwebserver);
          SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE, (XSUBJECT *)appwebserver);
          SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST_ENDPOINT, (XSUBJECT *)appwebserver);

          apirest = GEN_NEW MINIWEBSERVER_APIREST(this);
          if(!apirest) return false;
        }

      APPFLOW_LOG_ENTRY((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR, APPFLOW_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());
    }

  //--------------------------------------------------------------------------------------------------

  status = false;

  string2.Format(__L("Inicializando Web Socket "));
      
  #ifdef DIO_STREAMTLS_ACTIVE
  string2.AddFormat(__L(" %s"), (APPFLOW_CFG.WebServer_IsTLS()?__L(" (WSS)"):__L("")));     
  #endif

  string.Format(APPFLOWCONSOLE_DEFAULT_MESSAGEMASK, string2.Get());

  console->PrintMessage(string.Get(), 1, true, false);

  appwebsocket = GEN_NEW APPFLOWWEBSERVER();
  if(appwebsocket) status = true;

  if(status) status = appwebsocket->Ini(&APPFLOW_CFG, 17009, APPFLOW_CFG.WebServer_GetTimeoutToServerPage(), APPFLOW_CFG.WebServer_GetLocalAddress());

  stringresult = (status)?__L("Ok."):__L("ERROR!");
  console->PrintMessage(stringresult.Get(), 0, false, true);

  if(status)
    {
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST, (XSUBJECT *)appwebsocket);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE, (XSUBJECT *)appwebsocket);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE, (XSUBJECT *)appwebsocket);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED, (XSUBJECT *)appwebsocket);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA, (XSUBJECT *)appwebsocket);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED , (XSUBJECT *)appwebsocket);
    }

  APPFLOW_LOG_ENTRY((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR, APPFLOW_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());

  console->PrintMessage(__L(" "), 0, false, true);
  console->WaitKey(__L(" Pulsa una tecla para continuar... (%d)"), 1, false, 5);

  //--------------------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MINIWEBSERVER::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::AppProc_Update()
{
  if(GetEvent()==MINIWEBSERVER_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case MINIWEBSERVER_XFSMSTATE_NONE       : break;

          case MINIWEBSERVER_XFSMSTATE_INI        : if(GetExitType() == APPFLOWBASE_EXITTYPE_UNKNOWN)
                                                      {
                                                        if(xtimerupdateconsole)
                                                          {
                                                            if(xtimerupdateconsole->GetMeasureSeconds() >= 1)
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

          case MINIWEBSERVER_XFSMSTATE_END        : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<MINIWEBSERVER_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case MINIWEBSERVER_XFSMSTATE_NONE   : break;

              case MINIWEBSERVER_XFSMSTATE_INI    : break;

              case MINIWEBSERVER_XFSMSTATE_END    : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MINIWEBSERVER::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetEvent(MINIWEBSERVER_XFSMEVENT_END);

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

  if(appwebserver)
    {
      string.Format(APPFLOWCONSOLE_DEFAULT_MESSAGEMASK, __L("Desactivando servidor web"));
      console->PrintMessage(string.Get(), 1, true, false);

      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST, (XSUBJECT *)appwebserver);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE, (XSUBJECT *)appwebserver);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE, (XSUBJECT *)appwebserver);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST_ENDPOINT, (XSUBJECT *)appwebserver);

      delete appwebserver;
      appwebserver = NULL;

      stringresult = __L("Ok.");

      console->PrintMessage(stringresult.Get(), 0, false, true);
      XLOG::GetInstance().AddEntry(XLOGLEVEL_INFO, APPFLOW_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s") , string.Get(), stringresult.Get());
    }

  if(apirest)
    {
      delete apirest;
      apirest = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(appwebsocket)
    {
      string.Format(APPFLOWCONSOLE_DEFAULT_MESSAGEMASK, __L("Desactivando WebSocket"));
      console->PrintMessage(string.Get(), 1, true, false);

      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST, (XSUBJECT *)appwebsocket);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE, (XSUBJECT *)appwebsocket);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE, (XSUBJECT *)appwebsocket);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED, (XSUBJECT *)appwebsocket);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA, (XSUBJECT *)appwebsocket);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED, (XSUBJECT *)appwebsocket);

      delete appwebsocket;
      appwebsocket = NULL;

      stringresult = __L("Ok.");

      console->PrintMessage(stringresult.Get(), 0, false, true);
      XLOG::GetInstance().AddEntry(XLOGLEVEL_INFO, APPFLOW_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s") , string.Get(), stringresult.Get());
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
* @fn         bool MINIWEBSERVER::KeyValidSecuences(int key)
* @brief      Processes valid key sequences.
* @ingroup    EXAMPLES
*
* @param[in]  key : Key code to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::KeyValidSecuences(int key)
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
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MINIWEBSERVER::Show_WebServerConfig()
* @brief      Shows web server configuration.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::Show_WebServerConfig()
{
  XSTRING string;
  XSTRING string2;

  string.Format(__L("Web Server"));
  string2.Empty();
  Show_Line(string, string2);

  string.Format(__L("Port"));
  string2.Format(__L("%d"), appwebserver->GetWebServer()->GetPort());
  Show_Line(string, string2);

  string.Format(__L("Acceso Autenticado"));
  string2.Format(__L("%s"), appwebserver->GetIsAuthenticatedAccess()?__L("Si"):__L("No"));
  Show_Line(string, string2);


  string.Format(__L("Plugin(s) Activo(s)"));
  XDWORD nplugins = appwebserver->GetWebServer()->GetPluginsManager()->Plugins_GetNPlugins();
  string2.Format(__L("%d "), appwebserver->GetWebServer()->GetPluginsManager()->Plugins_GetNPlugins());

  for(XDWORD c=0; c<nplugins; c++)
    {
      DIOWEBSERVER_PLUGIN* plugin = appwebserver->GetWebServer()->GetPluginsManager()->Plugins_Get(c);
      if(plugin) string2.AddFormat(__L("[%s] "), plugin->GetName()->Get());
    }

  Show_Line(string, string2);


  string.Format(__L("Solo sirve API Rest"));
  string2.Format(__L("%s"), appwebserver->GetIsApiRestOnly()?__L("Si"):__L("No"));
  Show_Line(string, string2);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MINIWEBSERVER::Show_WebSocketConfig()
* @brief      Shows web socket configuration.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::Show_WebSocketConfig()
{
  if(!appwebsocket)                   return false;
  if(!appwebsocket->GetWebServer())   return false;

  XSTRING string;
  XSTRING string2;

  string.Format(__L("WebSocket"));
  string2.Empty();
  Show_Line(string, string2);

  string.Format(__L("Port"));
  string2.Format(__L("%d"), appwebsocket->GetWebServer()->GetPort());
  Show_Line(string, string2);


  int nconnections_active = 0;

  DIOWEBSERVER_CONNECTION* connection;

  connection = appwebsocket->GetWebServer()->Websocket_GetConnection();
  while(connection)
    {
      nconnections_active++;
      connection = appwebsocket->GetWebServer()->Websocket_GetNextConnection();
    }

  string.Format(__L("Conexiones activas"));
  string2.Format(__L("[%d]"), nconnections_active);
  Show_Line(string, string2);

  if(nconnections_active)
    {
      connection = appwebsocket->GetWebServer()->Websocket_GetConnection();
      while(connection)
        {
          string.Empty();
          string2.Format(__L("Ver. %2d - Protocol \"%s\" - [%s]"), connection->GetRequest()->WebSocket_GetVersion(), connection->GetRequest()->WebSocket_GetProtocol()->Get(), connection->GetRequest()->GetResource()->Get());
          Show_Line(string, string2);

          connection = appwebsocket->GetWebServer()->Websocket_GetNextConnection();
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MINIWEBSERVER::Show_AllStatus()
* @brief      Shows all status information.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::Show_AllStatus()
{
  console->Clear();

  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  APPFLOW_EXTENDED.ShowAll();

  if(Show_WebServerConfig())       console->PrintMessage(__L(""), 0, false, true);
  if(Show_WebSocketConfig())       console->PrintMessage(__L(""), 0, false, true);

  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MINIWEBSERVER::HandleEvent_WebServer(DIOWEBSERVER_XEVENT* event)
* @brief      Handle event web server.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MINIWEBSERVER::HandleEvent_WebServer(DIOWEBSERVER_XEVENT* event)
{
  if(!event) return;

  switch(event->GetEventType())
    {
      case DIOWEBSERVER_XEVENT_TYPE_REQUEST               : event->SetStatus(false);
                                                            break;

      case DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE        : event->SetIsRequestAuthenticate(true);
                                                            break;

      case DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE     : event->SetIsRequestAuthenticate(true);
                                                            break;

      case DIOWEBSERVER_XEVENT_TYPE_REQUEST_ENDPOINT      : apirest->ResolveEndPoint(event);                                                            
                                                            break;

      case DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED   : // Accepted connection
                                                            event->SetStatus(true);
                                                            break;

      case DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA    : { event->GetServer()->Websocket_Ping(__L("cucu..."));
                                                              event->GetServer()->Websocket_Write(__L("Hello word!"));
                                                            }
                                                          break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MINIWEBSERVER::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MINIWEBSERVER::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_WEBSERVER       : { DIOWEBSERVER_XEVENT* event = (DIOWEBSERVER_XEVENT*)xevent;
                                           if(!event) return;

                                           HandleEvent_WebServer(event);
                                         }
                                        break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MINIWEBSERVER::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MINIWEBSERVER::Clean()
{
  xtimerupdateconsole       = NULL;

  xmutexshowallstatus       = NULL;
  
  appwebserver              = NULL;
  apirest                   = NULL;
  appwebsocket              = NULL;
}



