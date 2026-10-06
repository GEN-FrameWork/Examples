/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       ScriptsExample.cpp
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "ScriptsExample.h"

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
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"

#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#ifdef SCRIPT_LIB_CFG_ACTIVE
#include "Script_Lib_CFG.h"
#endif
#include "Script.h"
#include "Script_Language_G.h"
#include "Script_Language_Lua.h"
#include "Script_Language_Javascript.h"
#ifdef SCRIPT_CACHE_ACTIVE
#include "Script_Cache.h"
#endif


#include "ScriptsExample_CFG.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(SCRIPTSEXAMPLE, scriptsexample)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPTSEXAMPLE::SCRIPTSEXAMPLE()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPTSEXAMPLE::SCRIPTSEXAMPLE() : XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPTSEXAMPLE::~SCRIPTSEXAMPLE()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPTSEXAMPLE::~SCRIPTSEXAMPLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPTSEXAMPLE::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPTSEXAMPLE::InitFSMachine()
{
  if(!AddState( SCRIPTSEXAMPLE_XFSMSTATE_NONE            ,
                SCRIPTSEXAMPLE_XFSMEVENT_INI             , SCRIPTSEXAMPLE_XFSMSTATE_INI           ,
                SCRIPTSEXAMPLE_XFSMEVENT_END             , SCRIPTSEXAMPLE_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( SCRIPTSEXAMPLE_XFSMSTATE_INI             ,
                SCRIPTSEXAMPLE_XFSMEVENT_UPDATE          , SCRIPTSEXAMPLE_XFSMSTATE_UPDATE        ,                
                SCRIPTSEXAMPLE_XFSMEVENT_END             , SCRIPTSEXAMPLE_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( SCRIPTSEXAMPLE_XFSMSTATE_UPDATE          ,               
                SCRIPTSEXAMPLE_XFSMEVENT_END             , SCRIPTSEXAMPLE_XFSMSTATE_END           ,                 
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( SCRIPTSEXAMPLE_XFSMSTATE_END             ,
                SCRIPTSEXAMPLE_XFSMEVENT_NONE            , SCRIPTSEXAMPLE_XFSMSTATE_NONE          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPTSEXAMPLE::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPTSEXAMPLE::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  
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
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS , APPFLOW_DEFAULT_DIRECTORY_SCRIPTS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, APPFLOW_DEFAULT_DIRECTORY_GRAPHICS);
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

  SetEvent(SCRIPTSEXAMPLE_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPTSEXAMPLE::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPTSEXAMPLE::AppProc_FirstUpdate()
{

  #ifdef SCRIPT_CACHE_ACTIVE

  XPATH xpath;

  GEN_SCRIPT_CACHE.Cache_DelAll();

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, xpath);

  GEN_SCRIPT_CACHE.Cache_AllDirectory(xpath);
  GEN_SCRIPT_CACHE.Cache_AllList(APPFLOW_CFG.Scripts_GetAll());

  #endif

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;

  xtimerscriptrun = GEN_XFACTORY.CreateTimer();
  if(!xtimerscriptrun) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPTSEXAMPLE::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPTSEXAMPLE::AppProc_Update()
{
  if(GetEvent()==SCRIPTSEXAMPLE_XFSMEVENT_NONE) 
    {
      switch(GetCurrentState())
        {
          case SCRIPTSEXAMPLE_XFSMSTATE_NONE        : break;

          case SCRIPTSEXAMPLE_XFSMSTATE_INI         : break;

          case SCRIPTSEXAMPLE_XFSMSTATE_UPDATE      : if(GetExitType() == APPFLOWBASE_EXITTYPE_UNKNOWN)
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

          case SCRIPTSEXAMPLE_XFSMSTATE_END         : break;

        }
    }
   else 
    {
      if(GetEvent()<SCRIPTSEXAMPLE_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case SCRIPTSEXAMPLE_XFSMSTATE_NONE    : break;

              case SCRIPTSEXAMPLE_XFSMSTATE_INI     : SetEvent(SCRIPTSEXAMPLE_XFSMEVENT_UPDATE);
                                                      break;

              case SCRIPTSEXAMPLE_XFSMSTATE_UPDATE  : break;

              case SCRIPTSEXAMPLE_XFSMSTATE_END     : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPTSEXAMPLE::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPTSEXAMPLE::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  SetEvent(SCRIPTSEXAMPLE_XFSMEVENT_END);

  //--------------------------------------------------------------------------------------

  if(xtimerscriptrun)
    {
      GEN_XFACTORY.DeleteTimer(xtimerscriptrun);
      xtimerscriptrun = NULL;
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
* @fn         bool SCRIPTSEXAMPLE::KeyValidSecuences(int key)
* @brief      Processes valid key sequences.
* @ingroup    EXAMPLES
*
* @param[in]  key : Key code to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPTSEXAMPLE::KeyValidSecuences(int key)
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

      case 'R'  : { if(xtimerscriptrun) xtimerscriptrun->Reset();

                    console->Printf(_L("\r\n"));

                    SCRIPT::LoadScriptAndRun(APPFLOW_CFG.Scripts_GetAll(), SCRIPTSEXAMPLE::AdjustLibraries);

                    XQWORD timereleapsed      =  xtimerscriptrun->GetMeasureMilliSeconds();
                    double timereleapsedfloat = ((double)timereleapsed/(double)1000);

                    XTRACE_PRINTCOLOR(1, _L("Run exec in %d milliseconds (%.2f seconds)."), (XDWORD)timereleapsed, timereleapsedfloat);
                  }
                  break;

      case 'S'  : break;

    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPTSEXAMPLE::Show_AppStatus()
* @brief      Shows application status information.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPTSEXAMPLE::Show_AppStatus()
{
  XSTRING string;
  XSTRING string2;

  XDWORD  total;
  XDWORD  free;

  GEN_XSYSTEM.GetMemoryInfo(total, free);

  string  = _L("Memoria total");
  string2.Format(_L("%d Kb, libre %d Kb (el %d%%)"), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
  Show_Line(string, string2);

  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  if(datetime)
    {
      datetime->Read();

      string  = _L("Fecha ");
      datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TEXTMONTH | XDATETIME_FORMAT_ADDDAYOFWEEK, string2);
      Show_Line(string, string2);

      GEN_XFACTORY.DeleteDateTime(datetime);
    }

  if(xtimerglobal)
    {
      string  = _L("Tiempo de funcionamiento");
      xtimerglobal->GetMeasureString(string2, true);
      Show_Line(string, string2);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPTSEXAMPLE::Show_AllStatus()
* @brief      Shows all status information.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPTSEXAMPLE::Show_AllStatus()
{
  console->Clear();

  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  APPFLOW_EXTENDED.ShowAll();
  
  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPTSEXAMPLE::AdjustLibraries(SCRIPT* script)
* @brief      Adjusts the script libraries.
* @ingroup    EXAMPLES
*
* @param[in]  script : Script instance used to adjust the libraries.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void SCRIPTSEXAMPLE::AdjustLibraries(SCRIPT* script)
{
  #ifdef SCRIPT_LIB_CFG_ACTIVE
  
  SCRIPT_SET_LIB_CFG(script, (XFILECFG*)&APPFLOW_CFG);

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPTSEXAMPLE::HandleEvent_Script(SCRIPT_XEVENT* event)
* @brief      Handle event script.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void SCRIPTSEXAMPLE::HandleEvent_Script(SCRIPT_XEVENT* event)
{
  switch(event->GetEventType())
    {      

      case SCRIPT_XEVENT_TYPE_ERROR    : XTRACE_PRINTCOLOR(4, _L("Script ERROR [%d]: %s line %d -> \"%s\""), event->GetError(), event->GetErrorText()->Get(), event->GetNLine(), event->GetCurrentToken()->Get());
                                         break;

      case SCRIPT_XEVENT_TYPE_BREAK    : XTRACE_PRINTCOLOR(4, _L("Script BREAK: line %d -> \"%s\""), event->GetNLine(), event->GetCurrentToken()->Get());
                                         break;

    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPTSEXAMPLE::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void SCRIPTSEXAMPLE::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
       case XEVENT_TYPE_SCRIPT        : { SCRIPT_XEVENT* event = (SCRIPT_XEVENT*)xevent;
                                          if(!event) return;

                                          HandleEvent_Script(event);
                                        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPTSEXAMPLE::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void SCRIPTSEXAMPLE::Clean()
{
  xtimerupdateconsole         = NULL;
  xtimerscriptrun             = NULL;

  xmutexshowallstatus         = NULL;
}



