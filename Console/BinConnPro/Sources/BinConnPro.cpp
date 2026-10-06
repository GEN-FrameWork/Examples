/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro.cpp
*
* @class      BINCONNPRO
* @brief      Example Binary Connexion Protocol Device class
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


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

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
#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"
#include "DIOProtocol_ApplicationData.h"
#include "DIOProtocol_ConnectionsManager.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "APPFlowLog.h"
#include "APPFlowInternetServices.h"
#include "APPFlowExtended.h"

#include "BinConnPro_ApplicationData.h"
#include "BinConnPro_ConnectionsManager.h"
#include "BinConnPro_Protocol.h"
#include "BinConnPro_CFG.h"

#include "BinConnPro.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(BINCONNPRO, binconnpro)

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO::BINCONNPRO()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO::BINCONNPRO() :  XFSMACHINE(0)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO::~BINCONNPRO()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO::~BINCONNPRO()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::InitFSMachine()
{
  if(!AddState( BINCONNPRO_XFSMSTATE_NONE           ,
                BINCONNPRO_XFSMEVENT_INI              , BINCONNPRO_XFSMSTATE_INI            ,
                BINCONNPRO_XFSMEVENT_END              , BINCONNPRO_XFSMSTATE_END            ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( BINCONNPRO_XFSMSTATE_INI              ,
                BINCONNPRO_XFSMEVENT_NONE           , BINCONNPRO_XFSMSTATE_NONE         ,
                BINCONNPRO_XFSMEVENT_END              , BINCONNPRO_XFSMSTATE_END            ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( BINCONNPRO_XFSMSTATE_END              ,
                BINCONNPRO_XFSMEVENT_NONE           , BINCONNPRO_XFSMSTATE_NONE         ,
                BINCONNPRO_XFSMEVENT_INI              , BINCONNPRO_XFSMSTATE_INI            ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status = false;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  Application_GetName()->Set(APPLICATION_NAMEAPP);

  //--------------------------------------------------------------------------------------------------

  ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  if(GetExecParams())
    {
      XSTRING* param = (XSTRING*)GetExecParams()->Get(0);
      if(param)
        {
          if(!param->Compare(_L("SERVER"), true))  modeserver = true;
        }
    }

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
  xpath.Create(3 , xpathsection.Get(), BINCONNPRO_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);

  //--------------------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG, this);

  //--------------------------------------------------------------------------------------------------

  SetEvent(BINCONNPRO_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::AppProc_FirstUpdate()
{
  XSTRING string;
  XSTRING stringresult;
  bool    status = false;

  //--------------------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;

  //--------------------------------------------------------------------------------------------------

  if(APPFLOW_CFG.Protocol_IsActive())
    {
      status = true;

      if(modeserver)
             string.Format(APPFLOWCONSOLE_DEFAULT_MESSAGEMASK, _L("Activando conexion servidor"));
        else string.Format(APPFLOWCONSOLE_DEFAULT_MESSAGEMASK, _L("Activando conexion cliente"));

      console->PrintMessage(string.Get(), 1, true, false);

      connectionsmanager = GEN_NEW BINCONNPRO_CONNECTIONSMANAGER();
      if(!connectionsmanager) status = false;

      if(status)
        {
          connectionsmanager->Application_SetVersion(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
          connectionsmanager->Application_GetName()->Set(APPLICATION_NAMEAPP);

          if(modeserver)
            {
              status = connectionsmanager->Ini(modeserver, APPFLOW_CFG.Protocol_IsLocalEnumActive(), APPFLOW_CFG.Protocol_GetPort(), NULL);
              connectionsmanager->TargetURL_Add(_L(""));
            }
           else
            {
              XSTRING* targetstring = APPFLOW_CFG.Protocol_GetTarget();
              if(targetstring) connectionsmanager->TargetURL_Add(targetstring->Get());

              if(connectionsmanager->TargetURL_GetNTargets())
                {
                  connectionsmanager->ProtocolConnections_SetNLimit(connectionsmanager->TargetURL_GetNTargets());
                  status = connectionsmanager->Ini(modeserver, APPFLOW_CFG.Protocol_IsLocalEnumActive(), APPFLOW_CFG.Protocol_GetPort(), NULL);

                } else status = false;
            }
        }

      if(status)
        {
          SubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION    , connectionsmanager);
          SubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL           , connectionsmanager);
          SubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION , connectionsmanager);
        }

      stringresult = (status)?_L("Ok."):_L("ERROR!");
      console->PrintMessage(stringresult.Get(), 0, false, true);

      APPFLOW_LOG_ENTRY((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR, APPFLOW_CFG_LOG_SECTIONID_INITIATION, false, _L("%s: %s") , string.Get(), stringresult.Get());
      if(!status) return false;
    }

  //--------------------------------------------------------------------------------------------------

  console->PrintMessage(_L(" "), 0, false, true);
  console->WaitKey(_L(" Pulsa una tecla para continuar... (%d)"), 1, false, 5);

  //--------------------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::AppProc_Update()
{
  if(GetEvent()==BINCONNPRO_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case BINCONNPRO_XFSMSTATE_NONE      : break;

          case BINCONNPRO_XFSMSTATE_INI       : if(GetExitType() == APPFLOWBASE_EXITTYPE_UNKNOWN)
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

          case BINCONNPRO_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<BINCONNPRO_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case BINCONNPRO_XFSMSTATE_NONE  : break;

              case BINCONNPRO_XFSMSTATE_INI   : break;

              case BINCONNPRO_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetEvent(BINCONNPRO_XFSMEVENT_END);

  //--------------------------------------------------------------------------------------

  if(connectionsmanager)
    {
      if(modeserver)
             string.Format(APPFLOWCONSOLE_DEFAULT_MESSAGEMASK, _L("Desactivando conexion servidor"));
        else string.Format(APPFLOWCONSOLE_DEFAULT_MESSAGEMASK, _L("Desactivando conexion cliente"));

      console->PrintMessage(string.Get(), 1, true, false);

      connectionsmanager->ProtocolConnections_DisconnectAll();

      UnSubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION    , connectionsmanager);
      UnSubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL           , connectionsmanager);
      UnSubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION , connectionsmanager);

      connectionsmanager->End();

      delete connectionsmanager;
      connectionsmanager = NULL;

      stringresult = _L("Ok.");

      console->PrintMessage(stringresult.Get(), 0, false, true);
      APPFLOW_LOG_ENTRY(XLOGLEVEL_INFO, APPFLOW_CFG_LOG_SECTIONID_ENDING, false, _L("%s: %s"), string.Get(), stringresult.Get());
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

  APPFLOW_EXTENDED.APPEnd();
  APPFLOW_EXTENDED.DelInstance();  
  APPFLOW_CFG.DelInstance();


  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::KeyValidSecuences(int key)
* @brief      Processes valid key sequences.
* @ingroup    EXAMPLES
*
* @param[in]  key : Key code to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::KeyValidSecuences(int key)
{
  XCHAR character = (XCHAR)key;

  if((character<32) || (character>127)) character = _C('?');
  APPFLOW_LOG_ENTRY(XLOGLEVEL_WARNING, APPFLOW_CFG_LOG_SECTIONID_STATUSAPP, false, _L("Key pressed: 0x%02X [%c]"), key, character);

  console->Printf(_L("\r \r"));

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
* @fn         bool BINCONNPRO::Show_ConnectionsStatus()
* @brief      Shows connection status information.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::Show_ConnectionsStatus()
{
  XSTRING string;
  XSTRING string2;

  string  = _L("Modo de protocolo");
  if(modeserver)
          string2.Format(_L("Servidor"));
    else  string2.Format(_L("Cliente"));
  Show_Line(string, string2);

  string.Empty();
  string2.Format(_L("Puerto [%d] "), APPFLOW_CFG.Protocol_GetPort());
  Show_Line(string, string2);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::Show_DeviceConnectedStatus()
* @brief      Shows connected device status information.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::Show_DeviceConnectedStatus()
{
  XSTRING string;
  XSTRING string2;

  if(modeserver)
    {
      string  = _L("Dispositivos conectados");

      if(!connectionsmanager->ProtocolConnections_GetNConnected())
        {
          string2 = _L("Ninguno.");

          Show_Line(string, string2);
        }
       else
        {
          Show_Line(string, string2, false);

          string.Empty();
          Show_LineDirect(string, true);

          BINCONNPRO_OPENSEARCHPROTOCOLCONNECTION

          if(_protocol->IsOperational())
            {
              XSTRING IPstring;

              DIOSTREAMCIPHER* diostreamcipher =  (DIOSTREAMCIPHER*)_protocol->GetDIOStream();
              if(diostreamcipher)
                {
                  DIOSTREAMTCPIP* diostreamtcpip = (DIOSTREAMTCPIP*)diostreamcipher->GetDIOStreamBase();
                  if(diostreamtcpip)
                    {
                      DIOIP* remoteIP = diostreamtcpip->GetClientIP();
                      if(remoteIP) remoteIP->GetXString(IPstring);
                    }
                }

              XSTRING typestring;

              _applicationdata->device.GetDeviceTypeInString(typestring);

              string.Format(_L(" %-16s [%8d] %-16s %-18s [%d.%d.%d]"), typestring.Get(), _applicationdata->device.GetID(), IPstring.Get(), _applicationdata->applicationname.Get(), _applicationdata->applicationversion, _applicationdata->applicationsubversion, _applicationdata->applicationsubversionerr);

              Show_LineDirect(string, true);
            }

          BINCONNPRO_CLOSESEARCHPROTOCOLCONNECTION
        }
    }
   else
    {
      string  = _L("Estado dispositivo");

      string2.Empty();

      if(!connectionsmanager->ProtocolConnections_GetNConnected())
        {
          string2 = _L("Desconectado");
        }
       else
        {
          string2 = _L("Conectado");
          if(connectionsmanager->ProtocolConnections_GetFirstConnected())
            {
              if(connectionsmanager->ProtocolConnections_GetFirstConnected()->GetDIOProtocol())
                {
                  DIOSTREAMCIPHER* streamcipher = (DIOSTREAMCIPHER*)connectionsmanager->ProtocolConnections_GetFirstConnected()->GetDIOProtocol()->GetDIOStream();
                  if(streamcipher)
                   {
                     DIOSTREAMTCPIP* streamtcpip = (DIOSTREAMTCPIP*)streamcipher->GetDIOStreamBase();
                     if(streamtcpip)
                       {
                         DIOIP* IP = streamtcpip->GetClientIP();
                         if(IP)
                           {
                             XSTRING IPstring;
                             IP->GetXString(IPstring);

                             string2 += _L(" [");
                             string2 += IPstring.Get();
                             string2 += _L("]");
                           }
                       }
                    }
                }
            }
        }

      Show_Line(string, string2);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::Show_AllStatus()
* @brief      Shows all status information.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::Show_AllStatus()
{
  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  APPFLOW_EXTENDED.ShowAll();

  if(Show_ConnectionsStatus())      console->PrintMessage(_L(""), 0, false, true);
  if(Show_DeviceConnectedStatus())  console->PrintMessage(_L(""), 0, false, true);

  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::InitializeProtocolConnectionServer(BINCONNPRO_PROTOCOL* protocol, BINCONNPRO_APPLICATIONDATA* applicationdata)
* @brief      Initializes a server protocol connection.
* @ingroup    EXAMPLES
*
* @param[in]  protocol : Protocol instance used by the operation.
* @param[in]  applicationdata : Application data associated with the protocol connection.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::InitializeProtocolConnectionServer(BINCONNPRO_PROTOCOL* protocol, BINCONNPRO_APPLICATIONDATA* applicationdata)
{
  XSTRING IPstring;
  bool    status;

  if(protocol->IsConnected())
    {
      DIOSTREAMCIPHER* diostreamcipher =  (DIOSTREAMCIPHER*)protocol->GetDIOStream();
      if(diostreamcipher)
        {
          DIOSTREAMTCPIP* diostreamtcpip = (DIOSTREAMTCPIP*)diostreamcipher->GetDIOStreamBase();
          if(diostreamtcpip)
            {
              DIOIP* remoteIP = diostreamtcpip->GetClientIP();
              if(remoteIP)
                {
                  remoteIP->GetXString(IPstring);
                }
            }
        }
    }

  applicationdata->centername.Set(_L("Test Point"));
  applicationdata->location.GetStreet()->Set(APPFLOW_CFG.Location_GetStreet()->Get());
  applicationdata->location.GetCity()->Set(APPFLOW_CFG.Location_GetCity()->Get());
  applicationdata->location.GetCountry()->Set(APPFLOW_CFG.Location_GetCountry()->Get());
  applicationdata->location.GetState()->Set(APPFLOW_CFG.Location_GetState()->Get());
  applicationdata->location.SetPostalCode(APPFLOW_CFG.Location_GetPostalCode());

  status =  protocol->CMD_GetProtocolVersion(applicationdata->protocolversion, applicationdata->protocolsubversion, applicationdata->protocolsubversionerr);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, _L("Ini Server protocol from %s: Not get version protocol."), IPstring.Get());
      return false;
    }

  if((applicationdata->protocolversion       != BINCONNPRO_PROTOCOL_VERSION)       ||
     (applicationdata->protocolsubversion    != BINCONNPRO_PROTOCOL_SUBVERSION)    ||
     (applicationdata->protocolsubversionerr != BINCONNPRO_PROTOCOL_SUBVERSIONERR))
    {
      XTRACE_PRINTCOLOR(4, _L("Ini Server protocol from %s: Not version protocol valid."), IPstring.Get());
      return false;
    }

  status = protocol->CMD_Application_GetVersion(applicationdata->applicationversion, applicationdata->applicationsubversion, applicationdata->applicationsubversionerr);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, _L("Ini Server protocol from %s: Not get application version."), IPstring.Get());
      return false;
    }

  status =  protocol->CMD_Application_GetName(applicationdata->applicationname);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, _L("Ini Server protocol from %s: Not get application name."), IPstring.Get());
      return false;
    }

  XDWORD devicetype;
  XDWORD deviceID;

  status = protocol->CMD_GetDeviceTypeAndID(devicetype, deviceID);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, _L("Ini Server protocol from %s: Not get machine ID."), IPstring.Get());
      return false;
    }

  applicationdata->device.SetType((BINCONNPRO_PROTOCOL_DEVICETYPE)devicetype);
  applicationdata->device.SetID(deviceID);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::InitializeProtocolConnectionClient(BINCONNPRO_PROTOCOL* protocol, BINCONNPRO_APPLICATIONDATA* applicationdata)
* @brief      Initializes a client protocol connection.
* @ingroup    EXAMPLES
*
* @param[in]  protocol : Protocol instance used by the operation.
* @param[in]  applicationdata : Application data associated with the protocol connection.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::InitializeProtocolConnectionClient(BINCONNPRO_PROTOCOL* protocol, BINCONNPRO_APPLICATIONDATA* applicationdata)
{
  bool status = false;

  status =  protocol->CMD_GetProtocolVersion(applicationdata->protocolversion, applicationdata->protocolsubversion, applicationdata->protocolsubversionerr);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, _L("Ini Client protocol:  Not get version protocol."));
      return false;
    }

  if((applicationdata->protocolversion       != BINCONNPRO_PROTOCOL_VERSION)       ||
     (applicationdata->protocolsubversion    != BINCONNPRO_PROTOCOL_SUBVERSION)    ||
     (applicationdata->protocolsubversionerr != BINCONNPRO_PROTOCOL_SUBVERSIONERR))
    {
      XTRACE_PRINTCOLOR(4, _L("Ini Client protocol:  Not version protocol valid."));
      return false;
    }

  status = protocol->CMD_GetCenterName(applicationdata->centername);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, _L("Ini Client protocol:  Not get center name."));
      return false;
    }

  //XTRACE_SETAPPLICATIONID(applicationdata->centername);

  XSTRING street;
  XSTRING city;
  XSTRING state;
  XSTRING country;
  XDWORD  postalcode = 0;

  status = protocol->CMD_GetLocation(street, city, state, country, postalcode);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, _L("Ini Client protocol:  Not get location."));
      return false;
    }

  applicationdata->location.GetStreet()->Set(street);
  applicationdata->location.GetCity()->Set(city);
  applicationdata->location.GetState()->Set(state);
  applicationdata->location.GetCountry()->Set(country);
  applicationdata->location.SetPostalCode(postalcode);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO::HandleEvent_ServerProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Handles server protocol connection events.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO::HandleEvent_ServerProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION    : break;

      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL           : { DIOPROTOCOL_CONNECTION*  protocolconnection  =  event->GetProtocolConnection();
                                                                                  BINCONNPRO_PROTOCOL*    protocol            =  NULL;
                                                                                  XSTRING                 IPstring;
                                                                                  bool                    status              = false;

                                                                                  if(!protocolconnection)  break;

                                                                                  protocol= (BINCONNPRO_PROTOCOL*)protocolconnection->GetDIOProtocol();
                                                                                  if(!protocol)
                                                                                    {
                                                                                      XTRACE_PRINTCOLOR(4, _L("Ini Server protocol: Not instance protocol."));
                                                                                      break;
                                                                                    }

                                                                                  BINCONNPRO_APPLICATIONDATA* applicationdata = (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
                                                                                  if(!applicationdata)
                                                                                    {
                                                                                      XTRACE_PRINTCOLOR(4, _L("Ini Server protocol from %s: Not instance protocol data."), IPstring.Get());
                                                                                      break;
                                                                                    }

                                                                                  status = InitializeProtocolConnectionServer(protocol, applicationdata);

                                                                                  protocol->SetIsInitialized(status);
                                                                                }
                                                                                break;

      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION :  { DIOPROTOCOL_CONNECTION* protocolconnection = event->GetProtocolConnection();
                                                                                  if(!protocolconnection)  break;

                                                                                  BINCONNPRO_PROTOCOL* protocol = (BINCONNPRO_PROTOCOL*)protocolconnection->GetDIOProtocol();
                                                                                  if(!protocol) break;

                                                                                  BINCONNPRO_APPLICATIONDATA* applicationdata = (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
                                                                                  if(!applicationdata) break;
                                                                                }
                                                                                break;

    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO::HandleEvent_ClientProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Handles client protocol connection events.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO::HandleEvent_ClientProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION       : break;

      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL              : { DIOPROTOCOL_CONNECTION*  protocolconnection = event->GetProtocolConnection();
                                                                                    BINCONNPRO_PROTOCOL*     protocol           = NULL;
                                                                                    bool                     status             = false;

                                                                                    if(protocolconnection) protocol = (BINCONNPRO_PROTOCOL*)protocolconnection->GetDIOProtocol();
                                                                                    if(!protocol) break;

                                                                                    BINCONNPRO_APPLICATIONDATA* applicationdata = (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
                                                                                    if(!applicationdata) break;

                                                                                    status = InitializeProtocolConnectionClient(protocol, applicationdata);

                                                                                    protocol->SetIsInitialized(status);
                                                                                  }
                                                                                  break;

      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION  : { DIOPROTOCOL_CONNECTION* protocolconnection =  event->GetProtocolConnection();
                                                                                  DIOPROTOCOL*            protocol          =  NULL;

                                                                                  if(protocolconnection) protocol =  protocolconnection->GetDIOProtocol();
                                                                                  if(!protocol)  break;
                                                                                }
                                                                                break;

    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {

      case XEVENT_TYPE_PROTOCOLCONNECTIONS     : { DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event = (DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT*)xevent;
                                                  if(!event) return;

                                                  if(modeserver)
                                                         HandleEvent_ServerProtocolConnections(event);
                                                    else HandleEvent_ClientProtocolConnections(event);
                                                }
                                                break;


    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO::Clean()
{
  xtimerupdateconsole         = NULL;

  xmutexshowallstatus         = NULL;

  modeserver                  = false;
  connectionsmanager          = NULL;
}
