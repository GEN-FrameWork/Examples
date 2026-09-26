/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetCapture.cpp
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


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "NetCapture.h"

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
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XConsole.h"
#include "XThread.h"
#include "XTrace.h"
#include "XObserver.h"
#include "XProcessManager.h"

#include "DIOPCap.h"
#include "DIOPCap_Filters.h"

#include "APPFlowCFG.h"
#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#include "NetCapture_CFG.h"
#include "NetCapture_Sniffer.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(NETCAPTURE, netcapture)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCAPTURE::NETCAPTURE()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCAPTURE::NETCAPTURE() : XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCAPTURE::~NETCAPTURE()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCAPTURE::~NETCAPTURE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCAPTURE::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE::InitFSMachine()
{ 
  
  if(!AddState( NETCAPTURE_XFSMSTATE_NONE            ,
                NETCAPTURE_XFSMEVENT_INI             , NETCAPTURE_XFSMSTATE_INI           ,
                NETCAPTURE_XFSMEVENT_END             , NETCAPTURE_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( NETCAPTURE_XFSMSTATE_INI             ,
                NETCAPTURE_XFSMEVENT_UPDATE          , NETCAPTURE_XFSMSTATE_UPDATE        ,
                NETCAPTURE_XFSMEVENT_END             , NETCAPTURE_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if (!AddState(NETCAPTURE_XFSMSTATE_UPDATE,
                NETCAPTURE_XFSMEVENT_END             , NETCAPTURE_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if(!AddState( NETCAPTURE_XFSMSTATE_END             ,
                NETCAPTURE_XFSMEVENT_NONE            , NETCAPTURE_XFSMSTATE_NONE          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCAPTURE::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  
  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  Application_GetName()->Set(APPLICATION_NAMEAPP);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, APPFLOW_DEFAULT_DIRECTORY_SCRIPTS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, APPFLOW_DEFAULT_DIRECTORY_GRAPHICS);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  //--------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS
  
  //--------------------------------------------------------------------------------------

    
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), APPLICATION_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
    
  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);
  
  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG, this);

  //--------------------------------------------------------------------------------------

  SetEvent(NETCAPTURE_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCAPTURE::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;

  //--------------------------------------------------------------------------------------

  sniffer =  GEN_NEW NETCAPTURE_SNIFFER();
  if(!sniffer)
    {
      return false;
    }

  sniffer->Capture_Ini();

  DIOPCAP_FILTERS* filters = sniffer->GetDIOPCap()->GetFilters();
  if(filters)
    {
      // filters->Entrys_Add(__L("DNS"), DIOPCAPPROTOCOL_TYPE_UDP | DIOPCAPPROTOCOL_TYPE_TCP, 1, 53);
    }
      
  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCAPTURE::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE::AppProc_Update()
{
  if(GetEvent()==NETCAPTURE_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case NETCAPTURE_XFSMSTATE_NONE        : break;

          case NETCAPTURE_XFSMSTATE_INI         : SetEvent(NETCAPTURE_XFSMEVENT_UPDATE);
                                                  break;

          case NETCAPTURE_XFSMSTATE_UPDATE      : if(GetExitType() == APPFLOWBASE_EXITTYPE_UNKNOWN)
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

          case NETCAPTURE_XFSMSTATE_END         : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                  break;

        }
    }
   else //  New event
    {
      if(GetEvent()<NETCAPTURE_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case NETCAPTURE_XFSMSTATE_NONE    : break;

              case NETCAPTURE_XFSMSTATE_INI     : SetEvent(NETCAPTURE_XFSMEVENT_UPDATE);
                                                  break;

              case NETCAPTURE_XFSMSTATE_UPDATE  : break;

              case NETCAPTURE_XFSMSTATE_END     : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCAPTURE::AppProc_LastUpdate()
* @brief      Executes the last application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE::AppProc_LastUpdate()
{
  if(sniffer)
    {
      sniffer->Capture_End();

      delete sniffer;
      sniffer = NULL;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCAPTURE::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetEvent(NETCAPTURE_XFSMEVENT_END);

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
* @fn         bool NETCAPTURE::KeyValidSecuences(int key)
* @brief      Processes valid key sequences.
* @ingroup    EXAMPLES
*
* @param[in]  key : Key code to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE::KeyValidSecuences(int key)
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

      case 'R'  : break;

      case 'S'  : break;

    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCAPTURE::Show_AllStatus()
* @brief      Shows all status information.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE::Show_AllStatus()
{  
  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  APPFLOW_EXTENDED.ShowAll();
  
  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCAPTURE::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCAPTURE::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  /*
  switch(xevent->GetEventFamily())
    {
       case XEVENT_TYPE_SCRIPT     : { SCRIPT_XEVENT* event = (SCRIPT_XEVENT*)xevent;
                                       if(!event) return;

                                       HandleEvent_Script(event);
                                     }
                                     break; 
    }
  */
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCAPTURE::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCAPTURE::Clean()
{
  xtimerupdateconsole         = NULL;
  xmutexshowallstatus         = NULL;

  sniffer                     = NULL;
}



