/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_System.cpp
* 
* @class      UI_SYSTEM
* @brief      Graphics UI System Monitor Example class
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

#include "UI_System.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "UI_StyleSheet.h"

#include "VersionFrameWork.h"

#include "XPath.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XFactory.h"
#include "XDir.h"
#include "XString.h"
#include "XSystem.h"
#include "XLog.h"
#include "XConsole.h"
#include "XFileXML.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XThread.h"
#include "XTrace.h"
#include "XDiagLog.h"                        // TEMPORARY diagnostic-only, see XDiagLog.h -- remove with it

#include "DIOFactory.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"
#include "DIOPublicInternetIP.h"

#include "GRP2DCanvas.h"
#include "GRPScreenCFGChromes.h"
#include "GRPScreen.h"
#include "GRPViewPort.h"
#include "GRPXEvent.h"
#include "INPManager.h"

#include "UI_XEvent.h"
#include "UI_Manager.h"
#include "UI_Layout.h"
#include "UI_Element.h"
#include "UI_Element_Text.h"
#include "UI_Element_Form.h"
#include "UI_Element_Button.h"
#include "UI_Element_ProgressBar.h"
#include "UI_Element_ProgressRadial.h"
#include "UI_Element_ProgressImage.h"
#include "UI_Element_StatisticsChart.h"
#include "UI_SkinCanvas.h"

#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#include "UI_System_CFG.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(UI_SYSTEM, ui_system)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_SYSTEM::UI_SYSTEM()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_SYSTEM::UI_SYSTEM() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_SYSTEM::~UI_SYSTEM()
* @brief      Destructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_SYSTEM::~UI_SYSTEM()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::InitFSMachine()
{
  if(!AddState( UI_SYSTEM_XFSMSTATE_NONE           ,
                UI_SYSTEM_XFSMEVENT_INI            , UI_SYSTEM_XFSMSTATE_INI          ,
                UI_SYSTEM_XFSMEVENT_END            , UI_SYSTEM_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_SYSTEM_XFSMSTATE_INI            ,
                UI_SYSTEM_XFSMEVENT_NONE           , UI_SYSTEM_XFSMSTATE_NONE         ,
                UI_SYSTEM_XFSMEVENT_END            , UI_SYSTEM_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_SYSTEM_XFSMSTATE_END            ,
                UI_SYSTEM_XFSMEVENT_NONE           , UI_SYSTEM_XFSMSTATE_NONE         ,
                UI_SYSTEM_XFSMEVENT_INI            , UI_SYSTEM_XFSMSTATE_INI          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  bool    status = false;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  Application_GetName()->Set(APPLICATION_NAMEAPP);

  SetInitOptions( APPFLOWGRAPHICS_INIOPTION_CREATEMAINSCREEN    |
                  APPFLOWGRAPHICS_INIOPTION_SHOWMAINSCREEN      |
                  APPFLOWGRAPHICS_INIOPTION_INPUT);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS      , APPFLOW_DEFAULT_DIRECTORY_GRAPHICS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_FONTS         , APPFLOW_DEFAULT_DIRECTORY_FONTS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_UI_LAYOUTS    , APPFLOW_DEFAULT_DIRECTORY_UI_LAYOUTS);


  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------

  xtimer = GEN_XFACTORY.CreateTimer();
  if(!xtimer) return false;

  xtimer->Reset();

  //--------------------------------------------------------------------------------------
  // NOTE: GEN does not currently expose the real Operating System boot uptime (there is no
  //       "GetSystemUpTime()" in XSYSTEM), so "xtimer" is used as the running clock for the
  //       "Tiempo de funcionamiento del sistema" card: it measures the time elapsed since this
  //       monitor application started. Swap it for a real OS uptime source (e.g. reading
  //       /proc/uptime on Linux) for the footer FOOTER_UPTIME path when one is available.
  //--------------------------------------------------------------------------------------

  // On Android a blocking Wait inside this ctor (up to N seconds of DNS probes) runs on the
  // NativeActivity start path before the window is ready. Real devices are stricter than
  // BlueStacks about when network/DNS is usable; HardwareInfo already re-checks on its
  // background thread, so skip the sync wait (second ctor arg = false).
  diocheckinternetconnection = GEN_NEW DIOCHECKINTERNETCONNECTION(5, false);

  //--------------------------------------------------------------------------------------

  currentsectionID               = UI_SYSTEM_SECTIONID_RESUMEN;
  lastupdatehardwareinfo_second  = 0;

  //--------------------------------------------------------------------------------------
  // Background hardware-info thread: HardwareInfo_Compute() (see its own note in UI_System.h)
  // is what used to run straight inside AppProc_Update(), in the middle of the render loop --
  // most notably HardwareInfo_UpdateConnection(), which can block on a real network check. It
  // now runs here instead, on its own XTHREAD, so a slow/stalled network check can never delay
  // a rendered frame: AppProc_Update() only ever calls the cheap, non-blocking HardwareInfo_Apply().
  //
  // Created/started only AFTER every field it (or HardwareInfo_Compute()) touches is already in
  // its final initial state above -- lastupdatehardwareinfo_second in particular, since
  // hardwareinfothread->Ini() below can have the background thread calling HardwareInfo_Compute()
  // before this function returns, and that field is read/written under hardwareinfomutex from
  // then on, never again from this (main) thread directly.
  //
  // waityield is set short (200ms) so a HardwareInfo_RequestForced() call (F5) or shutdown is
  // noticed quickly -- HardwareInfo_Compute() still self-throttles to once every
  // UI_SYSTEM_HARDWAREINFO_UPDATEPERIOD_SECONDS internally, exactly as before, so this does not
  // make the actual hardware reads any more frequent than they already were.
  //--------------------------------------------------------------------------------------

  hardwareinfomutex = GEN_XFACTORY.Create_Mutex();
  if(!hardwareinfomutex) return false;

  hardwareinfothread = GEN_XFACTORY.CreateThread(XTHREADGROUPID_UI_SYSTEM_HARDWAREINFO, __L("UI_SYSTEM::HardwareInfo"), ThreadFunction_UpdateHardwareInfo, this);
  if(!hardwareinfothread) return false;

  hardwareinfothread->SetWaitYield(200);
  hardwareinfothread->Ini();

  //--------------------------------------------------------------------------------------
  
  { XPATH xpath;
    
    GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
    xpath.Slash_Add();
    xpath.Add(APPLICATION_NAMEFILE);
    xpath.Add(XTRANSLATION_NAMEFILEEXT);    

    // Missing/unextracted .lng must not abort the whole NativeActivity: on Android assets land
    // under getFilesDir()/assets only after OverturnAssets, and a failed Ini() here used to
    // cascade into CreateMainScreenProcess never running → OnStep STATUS_KO → silent finish.
    if(!GEN_XTRANSLATION.Ini(xpath))
      {
        XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[UI_System] Translation file not loaded: %s"), xpath.Get());
      }
     else
      {
        GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);
      }
  }

  //--------------------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG);

  //--------------------------------------------------------------------------------------------------

  SetEvent(UI_SYSTEM_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[UI_SYSTEM_BUTTON_ESC]            = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[UI_SYSTEM_BUTTON_F5]             = inpdevice->GetButton(INPBUTTON_ID_F5);
      button[UI_SYSTEM_BUTTON_ZOOM_IN]        = inpdevice->GetButton(INPBUTTON_ID_ADD);
      button[UI_SYSTEM_BUTTON_ZOOM_OUT]       = inpdevice->GetButton(INPBUTTON_ID_SUBTRACT);
      button[UI_SYSTEM_BUTTON_ZOOM_OUT_MINUS] = inpdevice->GetButton(INPBUTTON_ID_MINUS);

      button[UI_SYSTEM_BUTTON_MOUSE]    = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[UI_SYSTEM_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[UI_SYSTEM_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }

  //--------------------------------------------------------------------------------------
  // The normal path: Ini_Graphics() already loaded the dashboard, before the window was ever shown
  // (see the note there). This is now just the fallback/retry for a platform where that early attempt
  // did not run or did not succeed -- same failure handling as the original single call site, an app
  // that cannot load its own UI aborts here instead of continuing into a silently blank window.
  //--------------------------------------------------------------------------------------

  if(!dashboardloaded)
    {
      // Same soft-fail idea as translation: aborting FirstUpdate finishes the Android activity
      // with no dialog. Retry once; if assets are still missing keep running with placeholders
      // so logcat can show the real Load() failure instead of a silent exit.
      if(!Ini_UserInterface(true))
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[UI_System] Dashboard load failed in FirstUpdate"));
          dashboardloaded = false;
        }
       else
        {
          dashboardloaded = true;
        }
    }

  //--------------------------------------------------------------------------------------
  // First hardware info population. This used to be a synchronous, forced UpdateHardwareInfo(true)
  // call right here -- deliberately kept out of Ini_Graphics() and left this late specifically
  // because HardwareInfo_UpdateConnection() can block on a real network check (see the note that
  // used to be here, and still applies -- it just moved, see Ini_Graphics()). Now that hardware
  // info runs on its own background thread (started in AppProc_Ini(), already running by the time
  // this executes), that concern is gone: this just raises a flag for it to pick up on its very
  // next tick instead of running the read itself. The dashboard's first rendered frame still shows
  // its authored placeholder values for one or two frames until that first background pass
  // publishes -- same as before, just no longer at the cost of a synchronous block here.
  //--------------------------------------------------------------------------------------

  HardwareInfo_RequestForced();

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::AppProc_Update()
{
  if(GetEvent()==UI_SYSTEM_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case UI_SYSTEM_XFSMSTATE_NONE      : break;

          case UI_SYSTEM_XFSMSTATE_INI       : UpdateInput();
                                               HardwareInfo_Apply();
                                               DrawFrame();
                                               GetMainScreen()->UpdateViewports();
                                               break;

          case UI_SYSTEM_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<UI_SYSTEM_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case UI_SYSTEM_XFSMSTATE_NONE  : break;

              case UI_SYSTEM_XFSMSTATE_INI   : break;

              case UI_SYSTEM_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::AppProc_End()
{
  //--------------------------------------------------------------------------------------
  // Stop the background hardware-info thread FIRST, before anything below it reads (xtimer,
  // diocheckinternetconnection) gets deleted, and before Ini_UserInterface(false) tears down
  // GEN_USERINTERFACE. hardwareinfoexiting is a fast-path guard so a thread tick that fires
  // between this flag being set and End() actually stopping it returns immediately instead of
  // starting one more (unlockable) compute pass; End() itself blocks (via WaitToEnd()) until any
  // pass already in flight has finished, so by the time this block returns the background thread
  // is guaranteed to no longer be touching xtimer/diocheckinternetconnection/hardwareinfomutex.
  //--------------------------------------------------------------------------------------

  hardwareinfoexiting = true;

  if(hardwareinfothread)
    {
      hardwareinfothread->End();
      GEN_XFACTORY.DeleteThread(XTHREADGROUPID_UI_SYSTEM_HARDWAREINFO, hardwareinfothread);

      hardwareinfothread = NULL;
    }

  if(hardwareinfomutex)
    {
      GEN_XFACTORY.Delete_Mutex(hardwareinfomutex);
      hardwareinfomutex = NULL;
    }

  //--------------------------------------------------------------------------------------

  SetCurrentState(UI_SYSTEM_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------

  Ini_UserInterface(false);

  //--------------------------------------------------------------------------------------

  if(diocheckinternetconnection)
    {
      GEN_DELETE diocheckinternetconnection;
      diocheckinternetconnection = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(xtimer)
    {
      GEN_XFACTORY.DeleteTimer(xtimer);
      xtimer = NULL;
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
* @fn         bool UI_SYSTEM::UpdateInput()
* @brief      Updates the application input state.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UpdateInput()
{
   int  height  = GetMainScreen()->GetHeight();

  if(cursor)    
    {  
      if(cursor->GetMotion()->IsReadyToTest(50))
        {
          cursor->GetMotion()->InvertYAxis(height);

          GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOTION, cursor->GetMotion());

          cursor->GetMotion()->Reset();
        }
       else    
        {
          if(cursor->GetMotion()->GetNPoints() < 50)
            {         
              static int   cursor_x       = 0;
              static int   cursor_y       = 0;
              int          now_cursor_x   = (int)cursor->GetX();
              int          now_cursor_y   = (int)height - (int)cursor->GetY();
              bool         changed        = false;

              if(cursor_x != now_cursor_x)  
                { 
                  cursor_x = now_cursor_x;
                  changed  = true;
                }

              if(cursor_y != now_cursor_y)  
                {
                  cursor_y = now_cursor_y;          
                  changed  = true;
                }

              if(changed)
                {
                  GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE,  cursor_x,  cursor_y);
                }

              if(button[UI_SYSTEM_BUTTON_MOUSE]->IsPressedWithRelease())
                {
                  GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION,  cursor_x,  cursor_y);   

                  cursor->GetMotion()->Reset();       
                }
    
              if(button[UI_SYSTEM_BUTTON_TOUCHSCREEN])
                {             
                  if(button[UI_SYSTEM_BUTTON_TOUCHSCREEN]->IsPressed())
                    {             
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE,  cursor_x,  cursor_y);
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION,   cursor_x, cursor_y);          

                      cursor->GetMotion()->Reset();
                    }
                }
            }
        }
    }


  for(int c=0; c<UI_SYSTEM_BUTTON_MOUSE; c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  case UI_SYSTEM_BUTTON_F5    : Ini_UserInterface(false);
                                                Ini_UserInterface(true);
                                                HardwareInfo_RequestForced();
                                                break;

                  case UI_SYSTEM_BUTTON_ZOOM_IN        :
                  case UI_SYSTEM_BUTTON_ZOOM_OUT       :
                  case UI_SYSTEM_BUTTON_ZOOM_OUT_MINUS :
                                                {
                                                  double delta = UI_LAYOUT_UISCALE_STEP;
                                                  if(c != UI_SYSTEM_BUTTON_ZOOM_IN) delta = -UI_LAYOUT_UISCALE_STEP;
                                                  UserInterface_AdjustUIScale(delta);
                                                }
                                                break;

                  case UI_SYSTEM_BUTTON_ESC   : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                break;
                }
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::Ini_Graphics(GRPSCREEN* screen)
* @brief      Initializes the graphics subsystem.
* @ingroup    EXAMPLES
*
* @param[in]  screen : Screen where the graphics or user interface resources are created.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::Ini_Graphics(GRPSCREEN* screen)
{

  //--------------------------------------------------------------------------------------

  screen->SetWidth(1440);
  screen->SetHeight(900);

  screen->GetTitle()->Set(__L("Monitor del Sistema"));  
  screen->SetDesktopScreenSelected(GRPSCREENTYPE_DESKTOP_MAIN);

  //--------------------------------------------------------------------------------------

  UserInterface_CFGChromes(screen);

  //--------------------------------------------------------------------------------------

  GetMainScreen()->CreateViewport(GRPVIEWPORT_ID_MAIN , 0.0f, 0.0f, (float)screen->GetWidth()   , (float)screen->GetHeight(), 0, 0, (screen->GetWidth()), (screen->GetHeight()));

  // Fase 5: allow window growth beyond design for autofit/pillarbox demos (WM_GETMINMAXINFO uses viewport max).
  {
    GRPVIEWPORT* mainvp = GetMainScreen()->GetViewport(0);
    if(mainvp) mainvp->SetMaxSize(3840.0f, 2160.0f);
  }

  //--------------------------------------------------------------------------------------
  // Load the dashboard as early as possible: SCREEN_CREATING (which is what is being handled right
  // now, all the way up the call chain to HandleEvent_Graphics()) fires BEFORE CreateMainScreenProcess()
  // goes on to call mainscreen->Create(show) -- the call that actually maps the native window and makes
  // it visible. Ini_UserInterface() used to run from AppProc_FirstUpdate() instead, which is the first
  // tick of the app's main loop -- by construction AFTER the window was already on screen. Whatever the
  // OS painted in between (an empty/zeroed canvas -- see the GRP2DCANVAS::Buffer_Create() fix -- or,
  // before that fix, whatever was left in the freshly allocated buffer) was visible to the user for the
  // whole time dashboard.xml and its ~30 SVG icons were being parsed and decoded. Doing that same work
  // HERE instead removes essentially all of it from the window the user could watch it happen in: the
  // viewport/canvas this needs already exist (CreateViewport() just above), and nothing else this touches
  // depends on the native window itself.
  //
  // Hardware info population deliberately stays OUT of this early call, and is still requested from
  // AppProc_FirstUpdate() instead (now via HardwareInfo_RequestForced(), no longer a synchronous call --
  // see AppProc_Ini()/AppProc_FirstUpdate()). HardwareInfo_UpdateConnection() can block on a real network
  // check; that used to matter here because the call was synchronous and this runs before the window
  // exists at all. It runs on its own background thread now, so it would technically be safe to request
  // it this early too -- left at AppProc_FirstUpdate() anyway, since nothing here depends on hardware info
  // being ready any sooner and moving it would not change when the first real values actually appear on
  // screen (that is gated by the background thread's own first pass, not by when it is asked to start).
  // The dashboard's first frame simply shows its authored placeholder values for a frame or two, same as
  // it always could between any two periodic refreshes.
  //
  // dashboardloaded records whether this attempt succeeded, so AppProc_FirstUpdate() below does not load
  // it a second time on the normal path, but still retries -- and still aborts startup on failure exactly
  // like the original single call site did -- if this one did not run or did not succeed (a platform whose
  // canvas creation is genuinely deferred past this point would hit that fallback, not a silent blank UI).
  //--------------------------------------------------------------------------------------

  dashboardloaded = Ini_UserInterface(true);

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::Ini_UserInterface(bool on)
* @brief      Initializes or ends the user interface.
* @ingroup    EXAMPLES
*
* @param[in]  on : true to enable the operation; false to disable it.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::Ini_UserInterface(bool on)
{  
  if(!on)
    {
      GRPSCREEN* screen = GetMainScreen();
      if(screen) UnSubscribeEvent(GRPXEVENT_TYPE_SCREEN_CHANGESIZE, screen);

      GEN_USERINTERFACE.SubscribeOutputEvents(false, this, &GEN_USERINTERFACE.GetInstance());
      GEN_USERINTERFACE.SubscribeInputEvents(false);
      GEN_USERINTERFACE.DelInstance();
   
      return true;
    }

  GRPSCREEN*    screen    = NULL;
  GRPVIEWPORT*  viewport  = NULL;
  GRP2DCANVAS*  canvas    = NULL;
  XPATH         xpath;
  
  screen = GetMainScreen();
  if(!screen)   
    {
      return false;
    } 

  viewport = screen->GetViewport(0);
  if(!viewport) 
    {
      return false;
    }

  canvas = viewport->GetCanvas();
  if(!canvas)   
    {
      return false;
    }
 
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_UI_LAYOUTS, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("ui_system/dashboard.xml"));
    
  if(!GEN_USERINTERFACE.Load(xpath, screen, 0)) 
    {
      return false;
    }

  // Fase 1/3/4/5/6 UIScale: design canvas = dashboard authoring size.
  // Priority: GEN_UI_SCALE env (test override, disables autofit) → autofit from window → manual ini scale.
  // Fase 6: min hit-target 44 design px (expand IsWithin only; paint AABB unchanged).
  //
  // Track P / Fase 5.3 Android: keep canvas at design size (Ini_Graphics SetWidth/Height). Fit to the
  // native surface is GLES letterbox + MapWindowToCanvas — NOT UIScale Present. Force scale=1.0 so
  // Windows-style Present stays identity and we never double-letterbox.
  {
    UI_LAYOUT* dashboard = GEN_USERINTERFACE.Layouts_Get(__L("dashboard"));
    if(dashboard)
      {
        dashboard->SetDesignSize(1440, 900);
        dashboard->SetMinHitSize(UI_LAYOUT_MINHITSIZE_DEFAULT);
        if(UI_STYLESHEET* sheet = dashboard->GetStyleSheet())
          {
            sheet->SetMediaViewport(1440, 900);
          }

        bool   useenv     = false;
        double demoscale  = (double)APPFLOW_CFG.GetUIScale();
        bool   doautofit  = APPFLOW_CFG.GetUIScaleAutofit();

        {
          char* envscale = getenv("GEN_UI_SCALE");
          if(envscale && envscale[0])
            {
              demoscale = atof(envscale);
              useenv    = true;
              doautofit = false;
            }
        }

        #ifdef ANDROID
        (void)doautofit;
        (void)useenv;
        // Platform letterbox = autofit. Keep UIScale Present off (scale 1).
        dashboard->SetUIScaleAutofit(true);
        dashboard->SetUIScaleForFit(UI_LAYOUT_UISCALE_DEFAULT);
        GEN_USERINTERFACE.UIScale_PrepareLayout(dashboard);
        if(screen)
          {
            XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[UI_System] Android UIScale=1.0 design=%dx%d (GLES letterbox fits device)"),
                              dashboard->GetDesignWidth(), dashboard->GetDesignHeight());
          }
        #else
        if(doautofit && !useenv)
          {
            GEN_USERINTERFACE.Layouts_ApplyFitUIScale(dashboard);
          }
         else
          {
            GEN_USERINTERFACE.Layouts_SetUIScale(dashboard, demoscale);
          }
        #endif

        SubscribeEvent(GRPXEVENT_TYPE_SCREEN_CHANGESIZE, screen);
      }
  }

  GEN_USERINTERFACE.SubscribeInputEvents(true);
  GEN_USERINTERFACE.SubscribeOutputEvents(true, this, &GEN_USERINTERFACE.GetInstance());   

  GEN_USERINTERFACE.Layout_PutBackground();

  GEN_USERINTERFACE.Elements_SetToRedraw();

  //--------------------------------------------------------------------------------------
  // Reflect the currently selected sidebar section (survives a F5 layout reload).
  //--------------------------------------------------------------------------------------

  UserInterface_SelectSection(currentsectionID);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::DrawFrame()
* @brief      Draws the current frame.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::DrawFrame()
{
  GRPSCREEN*     screen    = NULL;
  GRPVIEWPORT*   viewport  = NULL;
  GRP2DCANVAS*   canvas    = NULL;

  screen = GetMainScreen();
  if(!screen) 
    {
      return false;  
    }

  viewport = screen->GetViewport(0);
  if(!viewport) 
    {
      return false;
    }

  canvas =  viewport->GetCanvas();
  if(!canvas) 
    {
      return false;
    }
 
  //--------------------------------------------------------------------------------------
  // TEMPORARY DIAGNOSTIC INSTRUMENTATION (2026-09) -- see XDiagLog.h. Root-causing a multi-second full-dashboard
  // blank-freeze reported on real hardware/VMs (Windows and Linux) that a sandboxed reconstruction did not fully
  // explain. Times each of the 3 frame phases against XDiagLog's shared wall clock (a real platform XTIMER, NOT
  // clock()/CPU time -- a genuine block/wait must show up here, unlike CPU time, which would hide it). Logs a
  // [SLOWFRAME] line only when this single frame took over 20ms (past a 16.6ms/60fps budget) and a [HEARTBEAT]
  // line once a second regardless, so a stall INSIDE DrawFrame (heartbeats keep coming, frames are just slow) can
  // be told apart from the whole main loop not being called at all (heartbeats themselves stop appearing).
  //--------------------------------------------------------------------------------------

  static XQWORD diag_framecounter    = 0;
  static XQWORD diag_hb_windowstart  = XDIAGLOG_NOWUS();
  static XQWORD diag_hb_frames       = 0;
  static XQWORD diag_hb_maxus        = 0;

  // TEMPORARY diagnostics -- counters defined in UI_Skin.cpp, incremented on every UI_SKIN::Draw() call this
  // frame (recursive: covers every top-level element AND every descendant visited via Draw_Form()/Draw_Menu()
  // etc). Tells us the ACTUAL size of the tree walked per frame and how much of it was visible/dirty, since the
  // existing "update=" timing alone cannot distinguish "few elements, each expensive" from "many elements,
  // walked normally" -- both would show the same total. Extern-declared here rather than in a header since
  // this is throwaway.
  extern XDWORD diagskin_visits;
  extern XDWORD diagskin_visible;
  extern XDWORD diagskin_dirty;
  extern XQWORD diagskin_shadowus;         // UI_SkinCanvas.cpp -- accumulated us inside soft-shadow build+composite
  extern XDWORD diagskin_shadowcalls;      // UI_SkinCanvas.cpp -- how many soft-shadow draws happened this frame
  extern XDWORD diagskin_shadowcachehits;  // UI_SkinCanvas.cpp -- of those, how many reused the cached bitmap (Draw_Form path only)
  extern XDWORD diagskin_shadowcachemiss;  // UI_SkinCanvas.cpp -- of those, how many had to rebuild it

  diagskin_visits          = 0;
  diagskin_visible         = 0;
  diagskin_dirty           = 0;
  diagskin_shadowus         = 0;
  diagskin_shadowcalls      = 0;
  diagskin_shadowcachehits  = 0;
  diagskin_shadowcachemiss  = 0;

  XQWORD diag_t0 = XDIAGLOG_NOWUS();

  //--------------------------------------------------------------------------------------

  canvas->ReleaseDrawFramerate();

  canvas->RebuildAllAreas();

  XQWORD diag_t1 = XDIAGLOG_NOWUS();

  //--------------------------------------------------------------------------------------

  GEN_USERINTERFACE.Elements_RebuildDrawAreas();

  XQWORD diag_t2 = XDIAGLOG_NOWUS();

  GEN_USERINTERFACE.Update();

  XQWORD diag_t3 = XDIAGLOG_NOWUS();

  //--------------------------------------------------------------------------------------
  // Diagnostic bookkeeping -- see note above.
  //--------------------------------------------------------------------------------------

  diag_framecounter++;
  diag_hb_frames++;
  if((diag_t3 - diag_t0) > diag_hb_maxus) diag_hb_maxus = diag_t3 - diag_t0;

  if((diag_t3 - diag_t0) > 20000)
    {
      XDIAGLOG_WRITE("SLOWFRAME", "n=%llu total=%lluus canvasrebuild=%lluus elementsrebuild=%lluus update=%lluus skinvisits=%u skinvisible=%u skindirty=%u shadowcalls=%u shadowus=%llu shadowhits=%u shadowmiss=%u",
                      (unsigned long long)diag_framecounter,
                      (unsigned long long)(diag_t3-diag_t0), (unsigned long long)(diag_t1-diag_t0),
                      (unsigned long long)(diag_t2-diag_t1), (unsigned long long)(diag_t3-diag_t2),
                      (unsigned int)diagskin_visits, (unsigned int)diagskin_visible, (unsigned int)diagskin_dirty,
                      (unsigned int)diagskin_shadowcalls, (unsigned long long)diagskin_shadowus,
                      (unsigned int)diagskin_shadowcachehits, (unsigned int)diagskin_shadowcachemiss);
    }

  if((XDIAGLOG_NOWUS() - diag_hb_windowstart) > 1000000ULL)
    {
      XDIAGLOG_WRITE("HEARTBEAT", "frames_in_window=%llu maxframe=%lluus", (unsigned long long)diag_hb_frames, (unsigned long long)diag_hb_maxus);
      diag_hb_frames      = 0;
      diag_hb_maxus       = 0;
      diag_hb_windowstart = XDIAGLOG_NOWUS();
    }

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_SYSTEM::ThreadFunction_UpdateHardwareInfo(void* param)
* @brief      Background thread entry point: called repeatedly (every hardwareinfothread waityield
*             tick) by GEN's XTHREAD, for as long as the thread is running.
* @note       STATIC. Runs on the background thread, never on the main thread.
* @ingroup    EXAMPLES
*
* @param[in]  param : the UI_SYSTEM instance (passed as the thread's data pointer at creation).
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_SYSTEM::ThreadFunction_UpdateHardwareInfo(void* param)
{
  UI_SYSTEM* uisystem = (UI_SYSTEM*)param;
  if(!uisystem)                      return;
  if(uisystem->hardwareinfoexiting)  return;

  uisystem->HardwareInfo_Compute(false);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_Compute(bool forced)
* @brief      Reads every hardware/system information source and publishes the results for
*             HardwareInfo_Apply() to pick up. This is the direct replacement for what the old
*             UpdateHardwareInfo(bool) did, minus touching GEN_USERINTERFACE/UI_ELEMENT directly.
* @note       Runs ONLY on the background thread (called from ThreadFunction_UpdateHardwareInfo()).
* @ingroup    EXAMPLES
*
* @param[in]  forced : true to ignore the update period and refresh immediately.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_Compute(bool forced)
{
  if(!xtimer)             return false;
  if(!hardwareinfomutex)  return false;

  XQWORD actualsecond = xtimer->GetMeasureSeconds();
  bool   duetorun;

  hardwareinfomutex->Lock();

    if(hardwareinfo_forcenext)
      {
        forced                  = true;
        hardwareinfo_forcenext  = false;
      }

    duetorun = forced || ((actualsecond - lastupdatehardwareinfo_second) >= UI_SYSTEM_HARDWAREINFO_UPDATEPERIOD_SECONDS);

  hardwareinfomutex->UnLock();

  if(!duetorun) return true;

  //--------------------------------------------------------------------------------------
  // Everything below runs UNLOCKED, into local (this call's own stack, background-thread-only)
  // variables: this is exactly the work that used to run straight inside AppProc_Update() and
  // could stall rendering -- most notably HardwareInfo_UpdateConnection(), which can block on a
  // real network check. It is now free to take as long as it needs without the render loop (or
  // HardwareInfo_Apply(), which only ever takes the mutex for the short "publish" block further
  // down) ever waiting on it.
  //--------------------------------------------------------------------------------------

  XSTRING temperaturestr, usedtotalstr, usedstr, totalstr, datestr, timestr;
  XSTRING diskname[UI_SYSTEM_DISK_SLOT_MAX];
  XSTRING diskused[UI_SYSTEM_DISK_SLOT_MAX];
  XSTRING disktotal[UI_SYSTEM_DISK_SLOT_MAX];
  float   disklevel[UI_SYSTEM_DISK_SLOT_MAX];
  int     diskcount = 0;
  XSTRING statusstr, qualitystr, markstr, ipstr, publicipstr;
  XSTRING equipostr, sostr, uptimestr;

  float temperaturelevel = 0.0f;
  float cpuusagelevelnow = 0.0f;
  float ramusagelevelnow = 0.0f;
  bool  isconnectednow   = false;

  for(int s=0; s<UI_SYSTEM_DISK_SLOT_MAX; s++)
    {
      disklevel[s] = 0.0f;
    }

  // TEMPORARY diagnostic-only (see XDiagLog.h): times each source and the mutex re-acquire below, to check
  // empirically whether HardwareInfo_UpdateConnection() (the one documented as able to block on a real network
  // check) or mutex contention with the render thread is actually overlapping with the multi-second blank-freeze
  // under investigation, rather than trusting the "this can never stall rendering" design intent unverified.
  XQWORD diagh_t0 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateCPU(temperaturestr, temperaturelevel, cpuusagelevelnow);
  XQWORD diagh_t1 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateMemory(usedtotalstr, usedstr, totalstr, ramusagelevelnow);
  XQWORD diagh_t2 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateDateTime(datestr, timestr);
  XQWORD diagh_t3 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateVolumes(diskname, diskused, disktotal, disklevel, diskcount);
  XQWORD diagh_t4 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateConnection(isconnectednow, statusstr, qualitystr, markstr, ipstr, publicipstr);
  XQWORD diagh_t5 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateFooter(equipostr, sostr, uptimestr);
  XQWORD diagh_t6 = XDIAGLOG_NOWUS();

  if((diagh_t6 - diagh_t0) > 5000)   // this whole unlocked block took over 5ms
    {
      XDIAGLOG_WRITE("HWINFO", "cpu=%lluus mem=%lluus datetime=%lluus volumes=%lluus connection=%lluus footer=%lluus total=%lluus",
                      (unsigned long long)(diagh_t1-diagh_t0), (unsigned long long)(diagh_t2-diagh_t1),
                      (unsigned long long)(diagh_t3-diagh_t2), (unsigned long long)(diagh_t4-diagh_t3),
                      (unsigned long long)(diagh_t5-diagh_t4), (unsigned long long)(diagh_t6-diagh_t5),
                      (unsigned long long)(diagh_t6-diagh_t0));
    }

  //--------------------------------------------------------------------------------------
  // Publish: the only point where this thread touches the fields the main thread reads
  // (directly in HardwareInfo_Apply(), or via UserInterface_ChangeLiteralText() when
  // GEN_USERINTERFACE resolves a #[MASK] literal during its own redraw). Held just long enough
  // to copy already-computed values -- never around any of the work above.
  //--------------------------------------------------------------------------------------

  { XQWORD diagh_lockwaitstart = XDIAGLOG_NOWUS();
    hardwareinfomutex->Lock();
    XQWORD diagh_lockwaitelapsed = XDIAGLOG_NOWUS() - diagh_lockwaitstart;
    if(diagh_lockwaitelapsed > 5000)   // acquiring the "publish" lock itself took over 5ms -- contention
      {
        XDIAGLOG_WRITE("HWINFO", "publish-lock WAIT elapsed=%lluus (contended by the render thread?)", (unsigned long long)diagh_lockwaitelapsed);
      }
  }

    cpu_temperature_str.Set(temperaturestr.Get());
    ram_used_total_str.Set(usedtotalstr.Get());
    ram_used_str.Set(usedstr.Get());
    ram_total_str.Set(totalstr.Get());
    for(int s=0; s<UI_SYSTEM_DISK_SLOT_MAX; s++)
      {
        disk_slot_name[s].Set(diskname[s].Get());
        disk_slot_used[s].Set(diskused[s].Get());
        disk_slot_total[s].Set(disktotal[s].Get());
        disk_slot_level[s] = disklevel[s];
      }
    disk_slot_count = diskcount;
    if(disk_slot_count <= 0)                          disk_slot_index = 0;
     else if(disk_slot_index >= disk_slot_count)      disk_slot_index = 0;
    HardwareInfo_PublishDiskSlot();
    system_date_str.Set(datestr.Get());
    system_time_str.Set(timestr.Get());
    connection_status_str.Set(statusstr.Get());
    connection_quality_str.Set(qualitystr.Get());
    connection_mark_str.Set(markstr.Get());
    local_ip_str.Set(ipstr.Get());
    public_ip_str.Set(publicipstr.Get());
    footer_equipo_str.Set(equipostr.Get());
    footer_so_str.Set(sostr.Get());
    footer_uptime_str.Set(uptimestr.Get());

    cpu_temperaturelevel = temperaturelevel;
    cpu_usagelevel       = cpuusagelevelnow;
    ram_usagelevel       = ramusagelevelnow;
    isconnected          = isconnectednow;

    // Phase 2 StatisticsChart: keep rings of recent CPU / RAM % for the history card.
    // Mutex is already held for the publish block; do not call CpuHistoryChart_PushSample() here
    // (that helper locks again).
    cpuhistory_samples[cpuhistory_write] = cpuusagelevelnow;
    cpuhistory_write = (cpuhistory_write + 1) % UI_SYSTEM_CPUHISTORY_MAX;
    if(cpuhistory_count < UI_SYSTEM_CPUHISTORY_MAX) cpuhistory_count++;

    ramhistory_samples[ramhistory_write] = ramusagelevelnow;
    ramhistory_write = (ramhistory_write + 1) % UI_SYSTEM_RAMHISTORY_MAX;
    if(ramhistory_count < UI_SYSTEM_RAMHISTORY_MAX) ramhistory_count++;

    lastupdatehardwareinfo_second = actualsecond;
    hardwareinfo_haspending       = true;

  hardwareinfomutex->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_Apply()
* @brief      Pushes whatever HardwareInfo_Compute() last published into the actual UI_ELEMENTs
*             and asks for a redraw. Cheap no-op when nothing changed since the last frame.
* @note       Runs ONLY on the main thread (called from AppProc_Update(), where the old inline
*             UpdateHardwareInfo(false) call used to be). This is the only place in the whole
*             class that still touches UI_ELEMENT/GEN_USERINTERFACE for hardware info.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_Apply()
{
  if(!hardwareinfomutex) return false;

  bool  haspending;
  float temperaturelevel = 0.0f;
  float cpuusagelevelnow = 0.0f;
  float ramusagelevelnow = 0.0f;
  float diskusagelevelnow = 0.0f;
  bool  isconnectednow   = false;

  // TEMPORARY diagnostic-only (see XDiagLog.h): this runs on the MAIN (render) thread -- if acquiring this lock
  // ever takes a long time, that is direct proof of the background hardware-info thread stalling the render
  // loop, regardless of what the design intent says.
  XQWORD diaga_lockwaitstart = XDIAGLOG_NOWUS();

  hardwareinfomutex->Lock();

    { XQWORD diaga_lockwaitelapsed = XDIAGLOG_NOWUS() - diaga_lockwaitstart;
      if(diaga_lockwaitelapsed > 5000)
        {
          XDIAGLOG_WRITE("HWINFO", "MAIN THREAD apply-lock WAIT elapsed=%lluus (render thread stalled by background thread)", (unsigned long long)diaga_lockwaitelapsed);
        }
    }

    haspending = hardwareinfo_haspending;

    if(haspending)
      {
        hardwareinfo_haspending = false;

        temperaturelevel = cpu_temperaturelevel;
        cpuusagelevelnow = cpu_usagelevel;
        ramusagelevelnow = ram_usagelevel;
        diskusagelevelnow = disk_usagelevel;
        isconnectednow   = isconnected;
      }

  hardwareinfomutex->UnLock();

  if(!haspending) return true;                            // nothing new since the last frame

  //--------------------------------------------------------------------------------------
  // From here on this is exactly what UpdateHardwareInfo(false)'s HardwareInfo_UpdateCPU() /
  // _UpdateMemory() / _UpdateConnection() used to do inline, just fed from the values the
  // background thread already computed instead of computing them here. No mutex needed below:
  // this function only ever runs on the main thread.
  //--------------------------------------------------------------------------------------

  UI_ELEMENT_PROGRESS_IMAGE* element_temp = (UI_ELEMENT_PROGRESS_IMAGE*)GEN_USERINTERFACE.Element_Get(__L("cpu_temp_bar"), UI_ELEMENT_TYPE_PROGRESSIMAGE);
  if(element_temp) element_temp->SetLevel(temperaturelevel);

  UI_ELEMENT_PROGRESS_RADIAL* element_cpu = (UI_ELEMENT_PROGRESS_RADIAL*)GEN_USERINTERFACE.Element_Get(__L("cpu_usage_radial"), UI_ELEMENT_TYPE_PROGRESSRADIAL);
  if(element_cpu) element_cpu->SetLevel(cpuusagelevelnow);

  // Phase 2: push samples into the GEN statisticschart widget (throttled; main thread only).
  HistoryChart_Apply(false);

  UI_ELEMENT_PROGRESS_RADIAL* element_radial = (UI_ELEMENT_PROGRESS_RADIAL*)GEN_USERINTERFACE.Element_Get(__L("ram_usage_radial"), UI_ELEMENT_TYPE_PROGRESSRADIAL);
  if(element_radial) element_radial->SetLevel(ramusagelevelnow);

  UI_ELEMENT_PROGRESSBAR* element_bar = (UI_ELEMENT_PROGRESSBAR*)GEN_USERINTERFACE.Element_Get(__L("ram_linear_bar"), UI_ELEMENT_TYPE_PROGRESSBAR);
  if(element_bar) element_bar->SetLevel(ramusagelevelnow);

  UI_ELEMENT_PROGRESS_RADIAL* element_diskradial = (UI_ELEMENT_PROGRESS_RADIAL*)GEN_USERINTERFACE.Element_Get(__L("disk_usage_radial"), UI_ELEMENT_TYPE_PROGRESSRADIAL);
  if(element_diskradial) element_diskradial->SetLevel(diskusagelevelnow);

  UI_ELEMENT_PROGRESSBAR* element_diskbar = (UI_ELEMENT_PROGRESSBAR*)GEN_USERINTERFACE.Element_Get(__L("disk_linear_bar"), UI_ELEMENT_TYPE_PROGRESSBAR);
  if(element_diskbar) element_diskbar->SetLevel(diskusagelevelnow);

  //--------------------------------------------------------------------------------------
  // Status glyph. Two images sit stacked at the same spot in the layout (a green disc with a
  // tick, and a red disc with a cross); only one of them is ever visible. This replaces the
  // previous "recolour a round form" approach, which stopped being visible once Draw_Form
  // started preferring background-color over color for its fill.
  // Must dirty both images (and the badge slot) on every apply: SetVisible alone does not
  // rebuild the area, so switching to offline left an empty slot / missing badge_ko (BlueStacks).
  //--------------------------------------------------------------------------------------

  UI_ELEMENT* element_iconok = GEN_USERINTERFACE.Element_Get(__L("connection_icon_ok"), UI_ELEMENT_TYPE_IMAGE);
  if(element_iconok)
    {
      element_iconok->SetVisible(isconnectednow);
      GEN_USERINTERFACE.Elements_SetToRedraw(element_iconok, false);
    }

  UI_ELEMENT* element_iconko = GEN_USERINTERFACE.Element_Get(__L("connection_icon_ko"), UI_ELEMENT_TYPE_IMAGE);
  if(element_iconko)
    {
      element_iconko->SetVisible(!isconnectednow);
      GEN_USERINTERFACE.Elements_SetToRedraw(element_iconko, false);
    }

  UI_ELEMENT* element_badgeslot = GEN_USERINTERFACE.Element_Get(__L("conn-badge-slot"), UI_ELEMENT_TYPE_FORM);
  if(element_badgeslot) GEN_USERINTERFACE.Elements_SetToRedraw(element_badgeslot, false);

  //--------------------------------------------------------------------------------------
  // The status line follows the same semantics: green when up, red when down.
  //--------------------------------------------------------------------------------------

  UI_ELEMENT_TEXT* element_status = (UI_ELEMENT_TEXT*)GEN_USERINTERFACE.Element_Get(__L("connection_status_text"), UI_ELEMENT_TYPE_TEXT);
  if(element_status) element_status->GetColor()->SetFromString(isconnectednow ? __L("63,185,80") : __L("248,81,73"));

  //--------------------------------------------------------------------------------------
  // Mark only the text leaves whose masks can have changed. The skin's rebuild-area transaction expands
  // this set to every overlapping surface/element before restoring pixels, so the example does not need to
  // know which card happens to be behind each value. Keeping that dependency in the renderer is essential:
  // a future CSS layout can move or restack these elements without changing application code.
  //--------------------------------------------------------------------------------------

  static XCHAR* maskedtextelements[] =
    {
      __L("footer_equipo_text")      ,
      __L("footer_so_text")          ,
      __L("footer_uptime_text")      ,
      __L("cpu_temp_value")          ,
      __L("ram_used")                ,
      __L("ram_total")               ,
      __L("disk_used")               ,
      __L("disk_total")              ,
      __L("disk_caption")            ,
      __L("disk_index")              ,
      __L("system_date")             ,
      __L("system_time")             ,
      __L("connection_status_text")  ,
      __L("connection_quality")      ,
      __L("connection_ip")           ,
      __L("connection_public_ip")    ,
    };

  for(int c=0; c<(int)(sizeof(maskedtextelements)/sizeof(maskedtextelements[0])); c++)
    {
      UI_ELEMENT* element_masked = GEN_USERINTERFACE.Element_Get(maskedtextelements[c], UI_ELEMENT_TYPE_TEXT);
      if(element_masked) GEN_USERINTERFACE.Elements_SetToRedraw(element_masked, false);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::CpuHistoryChart_PushSample(float cpuusagepercent)
* @brief      Appends one CPU usage sample to the history ring (thread-safe).
* @ingroup    EXAMPLES
*
* @param[in]  cpuusagepercent : CPU usage percent 0..100.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::CpuHistoryChart_PushSample(float cpuusagepercent)
{
  if(!hardwareinfomutex) return false;

  hardwareinfomutex->Lock();

    cpuhistory_samples[cpuhistory_write] = cpuusagepercent;
    cpuhistory_write = (cpuhistory_write + 1) % UI_SYSTEM_CPUHISTORY_MAX;
    if(cpuhistory_count < UI_SYSTEM_CPUHISTORY_MAX) cpuhistory_count++;

  hardwareinfomutex->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::DashboardSlot_ApplySection(UI_SYSTEM_SECTIONID sectionID)
* @brief      Swaps the bottom-left slot: Fecha/hora by default; StatisticsChart on CPU / Memoria / Disco.
* @note       MAIN THREAD ONLY.
* @ingroup    EXAMPLES
*
* @param[in]  sectionID : Active sidebar section.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::DashboardSlot_ApplySection(UI_SYSTEM_SECTIONID sectionID)
{
  // Fecha/hora stays visible forever in this slot. CPU / Memoria / Disco overlay the chart on top.
  bool showhistory = ((sectionID == UI_SYSTEM_SECTIONID_CPU)     ||
                      (sectionID == UI_SYSTEM_SECTIONID_MEMORIA) ||
                      (sectionID == UI_SYSTEM_SECTIONID_DISCO));

  UI_ELEMENT* element_datetime = GEN_USERINTERFACE.Element_Get(__L("card_datetime")   , UI_ELEMENT_TYPE_FORM);
  UI_ELEMENT* element_history  = GEN_USERINTERFACE.Element_Get(__L("card_cpu_history"), UI_ELEMENT_TYPE_FORM);

  if(!element_datetime || !element_history) return false;

  // Base layer: never hide Fecha/hora (avoids empty AABB when chart overlay fails or is torn down).
  if(!element_datetime->IsVisible())
    {
      element_datetime->SetVisible(true);
    }
  element_datetime->SetTransitionStateShow(UI_ELEMENT_TRANSITION_STATE_SHOW_NONE);

  if(showhistory)
    {
      element_history->SetVisible(true);
      element_history->SetTransitionStateShow(UI_ELEMENT_TRANSITION_STATE_SHOW_NONE);
      element_history->SetMustReDraw(true);
      GEN_USERINTERFACE.Elements_SetToRedraw(element_history, true);
    }
   else
    {
      // Hide chart without RestoreOnHide (that would stomp the date card). Repaint Fecha/hora instead.
      if(element_history->IsVisible())
        {
          element_history->SetVisible(false);
        }
      element_history->SetMustReDraw(false);
      element_history->SetTransitionStateShow(UI_ELEMENT_TRANSITION_STATE_SHOW_NONE);

      element_datetime->SetMustReDraw(true);
      GEN_USERINTERFACE.Elements_SetToRedraw(element_datetime, true);

      UI_ELEMENT* element_date = GEN_USERINTERFACE.Element_Get(__L("system_date"), UI_ELEMENT_TYPE_TEXT);
      UI_ELEMENT* element_time = GEN_USERINTERFACE.Element_Get(__L("system_time"), UI_ELEMENT_TYPE_TEXT);
      if(element_date) GEN_USERINTERFACE.Elements_SetToRedraw(element_date, false);
      if(element_time) GEN_USERINTERFACE.Elements_SetToRedraw(element_time, false);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HistoryChart_Apply(bool forced)
* @brief      Phase 2: feeds the GEN statisticschart from CPU/RAM rings or disk slots according to
*             the active sidebar section. Throttled to UI_SYSTEM_CHART_REBUILD_PERIOD_SECONDS unless forced
*             (section change). Empty state shows "--" until enough samples exist.
* @note       MAIN THREAD ONLY (touches GEN_USERINTERFACE). Fecha/hora is the default slot card;
*             chart for CPU / Memoria / Disco (never leave the slot empty).
* @ingroup    EXAMPLES
*
* @param[in]  forced : True to bypass the rebuild throttle.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HistoryChart_Apply(bool forced)
{
  #ifndef GRP_STATISTICSCHARS_ACTIVE
  DashboardSlot_ApplySection(currentsectionID);
  return false;
  #else

  if(!hardwareinfomutex) return false;

  DashboardSlot_ApplySection(currentsectionID);

  UI_SYSTEM_SECTIONID section = currentsectionID;
  bool showhistory = ((section == UI_SYSTEM_SECTIONID_CPU)     ||
                      (section == UI_SYSTEM_SECTIONID_MEMORIA) ||
                      (section == UI_SYSTEM_SECTIONID_DISCO));
  if(!showhistory) return true;

  XQWORD actualsecond = 0;
  if(xtimer) actualsecond = xtimer->GetMeasureSeconds();

  hardwareinfomutex->Lock();
    bool force = forced || chart_force_rebuild;
    if((!force) && ((actualsecond - lastchartrebuild_second) < UI_SYSTEM_CHART_REBUILD_PERIOD_SECONDS))
      {
        hardwareinfomutex->UnLock();
        return true;
      }
    chart_force_rebuild = false;
  hardwareinfomutex->UnLock();

  UI_ELEMENT_STATISTICSCHART* element_chart = (UI_ELEMENT_STATISTICSCHART*)GEN_USERINTERFACE.Element_Get(__L("cpu_history_chart"), UI_ELEMENT_TYPE_STATISTICSCHART);
  if(!element_chart) return false;

  UI_ELEMENT_TEXT* element_hdr = (UI_ELEMENT_TEXT*)GEN_USERINTERFACE.Element_Get(__L("cpuhist_hdr_text"), UI_ELEMENT_TYPE_TEXT);
  UI_ELEMENT*      element_empty = GEN_USERINTERFACE.Element_Get(__L("history_empty_text"), UI_ELEMENT_TYPE_TEXT);

  float samples[UI_SYSTEM_CPUHISTORY_MAX];
  int   count = 0;
  int   write = 0;
  bool  isempty = true;

  switch(section)
    {
      case UI_SYSTEM_SECTIONID_MEMORIA :
        {
          if(element_hdr) element_hdr->GetText()->Set(__L("Consumo de memoria"));

          element_chart->SetChartType(UI_ELEMENT_STATISTICSCHART_TYPE_AREA);
          element_chart->SetTitle(__L("RAM %"));
          if(element_chart->GetColor()) element_chart->GetColor()->SetFromString(__L("163,113,247"));

          hardwareinfomutex->Lock();
            count = ramhistory_count;
            write = ramhistory_write;
            for(int c=0; c<count; c++)
              {
                int index = write - count + c;
                if(index < 0) index += UI_SYSTEM_RAMHISTORY_MAX;
                samples[c] = ramhistory_samples[index % UI_SYSTEM_RAMHISTORY_MAX];
              }
          hardwareinfomutex->UnLock();

          if(count >= 2)
            {
              isempty = false;
              element_chart->SetSerieFromSamples(__L("RAM"), samples, count, 163, 113, 247);
            }
           else
            {
              element_chart->ClearData();
            }
        }
        break;

      case UI_SYSTEM_SECTIONID_DISCO :
        {
          if(element_hdr) element_hdr->GetText()->Set(__L("Uso por volumen"));

          element_chart->SetTitle(__L("Disco %"));
          if(element_chart->GetColor()) element_chart->GetColor()->SetFromString(__L("210,153,34"));

          XSTRING labelcopies[UI_SYSTEM_DISK_SLOT_MAX];
          XCHAR*  labels[UI_SYSTEM_DISK_SLOT_MAX];
          float   values[UI_SYSTEM_DISK_SLOT_MAX];
          int     nslots = 0;

          hardwareinfomutex->Lock();
            nslots = disk_slot_count;
            if(nslots > UI_SYSTEM_DISK_SLOT_MAX) nslots = UI_SYSTEM_DISK_SLOT_MAX;
            for(int c=0; c<nslots; c++)
              {
                labelcopies[c].Set(disk_slot_name[c].Get());
                labels[c] = labelcopies[c].Get();
                values[c] = disk_slot_level[c];
              }
          hardwareinfomutex->UnLock();

          if(nslots >= 1)
            {
              isempty = false;
              element_chart->SetColumnsFromValues(__L("Disco"), labels, values, nslots, 210, 153, 34);
            }
           else
            {
              element_chart->ClearData();
            }
        }
        break;

      case UI_SYSTEM_SECTIONID_CPU :
      default :
        {
          if(element_hdr) element_hdr->GetText()->Set(__L("Historico de CPU"));

          element_chart->SetChartType(UI_ELEMENT_STATISTICSCHART_TYPE_LINES);
          element_chart->SetTitle(__L("CPU %"));
          if(element_chart->GetColor()) element_chart->GetColor()->SetFromString(__L("56,139,253"));

          hardwareinfomutex->Lock();
            count = cpuhistory_count;
            write = cpuhistory_write;
            for(int c=0; c<count; c++)
              {
                int index = write - count + c;
                if(index < 0) index += UI_SYSTEM_CPUHISTORY_MAX;
                samples[c] = cpuhistory_samples[index % UI_SYSTEM_CPUHISTORY_MAX];
              }
          hardwareinfomutex->UnLock();

          if(count >= 2)
            {
              isempty = false;
              element_chart->SetSerieFromSamples(__L("CPU"), samples, count, 56, 139, 253);
            }
           else
            {
              element_chart->ClearData();
            }
        }
        break;
    }

  if(element_empty)
    {
      element_empty->SetVisible(isempty);
      GEN_USERINTERFACE.Elements_SetToRedraw(element_empty, false);
    }

  if(element_hdr) GEN_USERINTERFACE.Elements_SetToRedraw(element_hdr, false);

  element_chart->SetMustReDraw(true);
  GEN_USERINTERFACE.Elements_SetToRedraw(element_chart, false);

  hardwareinfomutex->Lock();
    lastchartrebuild_second = actualsecond;
  hardwareinfomutex->UnLock();

  return true;

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_RequestForced()
* @brief      Non-blocking replacement for the old UpdateHardwareInfo(true) call sites (first
*             frame, F5): raises a flag for the background thread to notice on its next tick
*             (within hardwareinfothread's waityield) instead of running the reads synchronously
*             on the caller's thread.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_RequestForced()
{
  if(!hardwareinfomutex) return false;

  hardwareinfomutex->Lock();
    hardwareinfo_forcenext = true;
  hardwareinfomutex->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateCPU(XSTRING& outtemperature, float& outtemperaturelevel, float& outusagelevel)
* @brief      Reads CPU temperature and CPU usage from GEN_XSYSTEM.
* @note       Called from HardwareInfo_Compute(), on the background thread. Writes only into its
*             own output parameters -- no member/UI_ELEMENT access here anymore.
* @ingroup    EXAMPLES
*
* @param[out] outtemperature : formatted "NN", digits only (or "--" if unavailable). The "\u00B0C" unit is a
*             separate, smaller-sizefont static <text> element (cpu_temp_unit) in dashboard.xml -- see the
*             comment there -- so it no longer travels inside this string.
* @param[out] outtemperaturelevel : temperature level for cpu_temp_bar, clamped to [0,100].
* @param[out] outusagelevel : CPU usage percent for cpu_usage_radial, 0 if unavailable.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateCPU(XSTRING& outtemperature, float& outtemperaturelevel, float& outusagelevel)
{
  //--------------------------------------------------------------------------------------
  // CPU Temperature: a real sensor reading on Windows (WMI), Linux (thermal sysfs), and Android
  // (same sysfs interface -- XANDROIDSYSTEM inherits XLINUXSYSTEM's implementation). Some boards/
  // OEM builds still expose no readable thermal zone at all, and microcontroller platforms
  // (ESP32/STM32) have no CPU temperature sensor to read in the first place; GEN_XSYSTEM.
  // GetCPUTemperature() returns 0.0f in every one of those cases, so the value is left as a "--"
  // placeholder instead of showing a fake number.
  //--------------------------------------------------------------------------------------

  float cputemperature = GEN_XSYSTEM.GetCPUTemperature();

  outtemperaturelevel = 0.0f;

  if(cputemperature > 0.0f)
    {
      outtemperature.Format(__L("%d"), (int)(cputemperature + 0.5f));

      outtemperaturelevel = cputemperature;
      if(outtemperaturelevel > 100.0f) outtemperaturelevel = 100.0f;
    }
   else
    {
      outtemperature.Set(__L("--"));
    }

  //--------------------------------------------------------------------------------------
  // CPU Usage (total, real value read from the OS: /proc/stat on Linux, WMI on Windows, ...)
  //--------------------------------------------------------------------------------------

  int cpuusage = GEN_XSYSTEM.GetCPUUsageTotal();

  outusagelevel = (cpuusage != XSYSTEM_CPUUSAGE_ERROR) ? (float)cpuusage : 0.0f;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateMemory(XSTRING& outusedtotal, XSTRING& outused, XSTRING& outtotal, float& outusagelevel)
* @brief      Reads RAM usage from GEN_XSYSTEM.
* @note       Called from HardwareInfo_Compute(), on the background thread. Writes only into its
*             own output parameters -- no member/UI_ELEMENT access here anymore.
* @ingroup    EXAMPLES
*
* @param[out] outusedtotal : formatted "used / total" (legacy single line).
* @param[out] outused : used amount alone ("5.4 GB") for the hierarchical RAM card line.
* @param[out] outtotal : "/ total" suffix ("/ 8.0 GB") muted next to outused in the mockup.
* @param[out] outusagelevel : RAM used percent, for ram_usage_radial and ram_linear_bar.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateMemory(XSTRING& outusedtotal, XSTRING& outused, XSTRING& outtotal, float& outusagelevel)
{
  XDWORD total = 0;
  XDWORD free  = 0;

  outusagelevel = 0.0f;

  if(GEN_XSYSTEM.GetMemoryInfo(total, free) && total)
    {
      XDWORD       used          = total - free;
      double       memorydivisor = 1.0;
      const XCHAR* memoryunit    = __L("KB");

      if(total >= (1024U * 1024U * 1024U))
        {
          memorydivisor = 1024.0 * 1024.0 * 1024.0;
          memoryunit    = __L("TB");
        }
      else if(total >= (1024U * 1024U))
        {
          memorydivisor = 1024.0 * 1024.0;
          memoryunit    = __L("GB");
        }
      else if(total >= 1024U)
        {
          memorydivisor = 1024.0;
          memoryunit    = __L("MB");
        }

      outused.Format(__L("%.1f %s"), (double)used / memorydivisor, memoryunit);
      outtotal.Format(__L("/ %.1f %s"), (double)total / memorydivisor, memoryunit);
      outusedtotal.Format(__L("%s %s"), outused.Get(), outtotal.Get());

      outusagelevel = (float)(((double)used / (double)total) * 100.0);
    }
   else
    {
      outused.Set(__L("--"));
      outtotal.Set(__L("/ --"));
      outusedtotal.Set(__L("-- / --"));
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateDateTime(XSTRING& outdate, XSTRING& outtime)
* @brief      Reads the actual system date and time.
* @note       Called from HardwareInfo_Compute(), on the background thread.
* @ingroup    EXAMPLES
*
* @param[out] outdate : formatted "DD/MM/YYYY".
* @param[out] outtime : formatted "HH:MM:SS".
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateDateTime(XSTRING& outdate, XSTRING& outtime)
{
  XDATETIME* xdatetime = GEN_XFACTORY.CreateDateTime();
  if(!xdatetime) return false;

  xdatetime->Read();

  outdate.Format(__L("%02d/%02d/%04d"), xdatetime->GetDay(),  xdatetime->GetMonth(),   xdatetime->GetYear());
  outtime.Format(__L("%02d:%02d:%02d"), xdatetime->GetHours(), xdatetime->GetMinutes(), xdatetime->GetSeconds());

  GEN_XFACTORY.DeleteDateTime(xdatetime);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateVolumes(XSTRING* outname, XSTRING* outused, XSTRING* outtotal, float* outusagelevel, int& outcount)
* @brief      Enumerates mounted volumes (up to UI_SYSTEM_DISK_SLOT_MAX) for the disk card carousel.
* @note       Prefer fixed (system root first), then removable, then other volumes with capacity.
* @ingroup    EXAMPLES
*
* @param[out] outname : per-slot captions.
* @param[out] outused : per-slot used text.
* @param[out] outtotal : per-slot "/ total" text.
* @param[out] outusagelevel : per-slot used percent.
* @param[out] outcount : number of filled slots.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateVolumes(XSTRING* outname, XSTRING* outused, XSTRING* outtotal, float* outusagelevel, int& outcount)
{
  outcount = 0;

  if(!outname || !outused || !outtotal || !outusagelevel) return false;

  for(int s=0; s<UI_SYSTEM_DISK_SLOT_MAX; s++)
    {
      outname[s].Set(__L("--"));
      outused[s].Set(__L("--"));
      outtotal[s].Set(__L("/ --"));
      outusagelevel[s] = 0.0f;
    }

  XVECTOR<XSYSTEM_VOLUMEINFO*> volumes;

  if(!GEN_XSYSTEM.GetVolumesInfo(volumes) || !volumes.GetSize())
    {
      volumes.DeleteContents();
      return true;
    }

  XVECTOR<XSYSTEM_VOLUMEINFO*> ordered;

  for(int pass=0; pass<4; pass++)
    {
      for(XDWORD c=0; c<volumes.GetSize(); c++)
        {
          XSYSTEM_VOLUMEINFO* volume = volumes.Get(c);
          if(!volume) continue;
          if(!volume->GetTotalBytes()) continue;
          if(ordered.GetSize() >= (XDWORD)UI_SYSTEM_DISK_SLOT_MAX) break;

          XSYSTEM_VOLUME_TYPE type = volume->GetType();
          bool accept = false;

          switch(pass)
            {
              case 0 : if(type == XSYSTEM_VOLUME_TYPE_FIXED)
                         {
                           XSTRING* name = volume->GetName();
                           if(name && name->Get())
                             {
                               if(!name->Compare(__L("/"), true)) accept = true;
                                else if(name->GetSize() >= 2)
                                 {
                                   XCHAR drive = name->Get()[0];
                                   XCHAR colon = name->Get()[1];
                                   if((drive == __C('C') || drive == __C('c')) && colon == __C(':')) accept = true;
                                 }
                             }
                         }
                       break;

              case 1 : if(type == XSYSTEM_VOLUME_TYPE_FIXED) accept = true;
                       break;

              case 2 : if(type == XSYSTEM_VOLUME_TYPE_REMOVABLE) accept = true;
                       break;

              default: accept = true;
                       break;
            }

          if(!accept) continue;

          bool already = false;
          for(XDWORD o=0; o<ordered.GetSize(); o++)
            {
              if(ordered.Get(o) == volume) { already = true; break; }
            }
          if(already) continue;

          ordered.Add(volume);
        }
    }

  for(XDWORD c=0; c<ordered.GetSize() && c<(XDWORD)UI_SYSTEM_DISK_SLOT_MAX; c++)
    {
      XSYSTEM_VOLUMEINFO* volume = ordered.Get(c);
      if(!volume) continue;

      XQWORD totalbytes = volume->GetTotalBytes();
      XQWORD usedbytes  = volume->GetUsedBytes();

      double       divisor = 1.0;
      const XCHAR* unit    = __L("B");

      if(totalbytes >= (1024ULL * 1024ULL * 1024ULL * 1024ULL))
        {
          divisor = 1024.0 * 1024.0 * 1024.0 * 1024.0;
          unit    = __L("TB");
        }
      else if(totalbytes >= (1024ULL * 1024ULL * 1024ULL))
        {
          divisor = 1024.0 * 1024.0 * 1024.0;
          unit    = __L("GB");
        }
      else if(totalbytes >= (1024ULL * 1024ULL))
        {
          divisor = 1024.0 * 1024.0;
          unit    = __L("MB");
        }
      else if(totalbytes >= 1024ULL)
        {
          divisor = 1024.0;
          unit    = __L("KB");
        }

      outused[c].Format(__L("%.1f %s"), (double)usedbytes / divisor, unit);
      outtotal[c].Format(__L("/ %.1f %s"), (double)totalbytes / divisor, unit);
      outusagelevel[c] = volume->GetUsedPercent();

      XSTRING* name  = volume->GetName();
      XSTRING* label = volume->GetLabel();

      if(name && name->GetSize())
        {
          if(label && label->GetSize()) outname[c].Format(__L("%s  %s"), name->Get(), label->Get());
           else                         outname[c].Set(name->Get());
        }
       else
        {
          outname[c].Set(__L("Volumen"));
        }

      outcount++;
    }

  volumes.DeleteContents();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_PublishDiskSlot()
* @brief      Copies the currently selected disk slot into the display strings / level.
* @note       Caller must already hold hardwareinfomutex (Compute publish or CycleDisk).
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_PublishDiskSlot()
{
  if(disk_slot_count <= 0)
    {
      disk_slot_index = 0;
      disk_used_str.Set(__L("--"));
      disk_total_str.Set(__L("/ --"));
      disk_caption_str.Set(__L("Sin volumen"));
      disk_index_str.Set(__L("0 / 0"));
      disk_usagelevel = 0.0f;
      return true;
    }

  if(disk_slot_index < 0 || disk_slot_index >= disk_slot_count) disk_slot_index = 0;

  disk_used_str.Set(disk_slot_used[disk_slot_index].Get());
  disk_total_str.Set(disk_slot_total[disk_slot_index].Get());
  disk_caption_str.Set(disk_slot_name[disk_slot_index].Get());
  disk_usagelevel = disk_slot_level[disk_slot_index];
  disk_index_str.Format(__L("%d / %d"), disk_slot_index + 1, disk_slot_count);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_CycleDisk(int delta)
* @brief      Rotates the disk card to the previous (-1) or next (+1) volume slot.
* @ingroup    EXAMPLES
*
* @param[in]  delta : -1 = left/prev, +1 = right/next.
*
* @return     bool : true if the selection changed (or was republished); otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_CycleDisk(int delta)
{
  if(!hardwareinfomutex) return false;
  if(!delta) return false;

  hardwareinfomutex->Lock();

    if(disk_slot_count <= 0)
      {
        hardwareinfomutex->UnLock();
        return false;
      }

    int next = disk_slot_index + delta;
    while(next < 0)                  next += disk_slot_count;
    while(next >= disk_slot_count)   next -= disk_slot_count;

    disk_slot_index = next;
    HardwareInfo_PublishDiskSlot();
    hardwareinfo_haspending = true;

  hardwareinfomutex->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateConnection(bool& outisconnected, XSTRING& outstatus, XSTRING& outquality, XSTRING& outmark, XSTRING& outip, XSTRING& outpublicip)
* @brief      Checks the internet connection status, its latency, the local IP and the public WAN IP.
* @note       Called from HardwareInfo_Compute(), on the background thread. This is the one most
*             worth having moved off the main thread: diocheckinternetconnection->Check() can
*             block on a real network check, and GEN_DIOPUBLICINTERNETIP.Get() can block on HTTP.
*             No UI_ELEMENT touched here anymore -- outisconnected is what HardwareInfo_Apply()
*             uses to drive the status glyph/colour on the main thread.
* @ingroup    EXAMPLES
*
* @param[out] outisconnected : true if the connection check succeeded.
* @param[out] outstatus : "Conectado" / "Desconectado".
* @param[out] outquality : "Conexi\u00F3n estable" / "Sin conexi\u00F3n".
* @param[out] outmark : "OK" / "--".
* @param[out] outip : formatted "IP: x.x.x.x" (or "IP: --" if unavailable).
* @param[out] outpublicip : formatted "IP P\u00FAblica: x.x.x.x" (or "--" if unavailable).
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateConnection(bool& outisconnected, XSTRING& outstatus, XSTRING& outquality, XSTRING& outmark, XSTRING& outip, XSTRING& outpublicip)
{
  outisconnected = false;

  if(diocheckinternetconnection)
    {
      outisconnected = diocheckinternetconnection->Check();
    }

  // Set to 1 to force the offline card (badge_ko + "Desconectado") on a machine that has WAN,
  // e.g. to match BlueStacks layout. Leave 0 for real DIOCHECKINTERNETCONNECTION results.
  #ifndef UI_SYSTEM_SIMULATE_OFFLINE
  #define UI_SYSTEM_SIMULATE_OFFLINE 0
  #endif
  #if UI_SYSTEM_SIMULATE_OFFLINE
  outisconnected = false;
  #endif

  if(outisconnected)
    {
      outstatus.Set(__L("Conectado"));
      outquality.Set(__L("Conexi\u00F3n estable"));
      outmark.Set(__L("OK"));
    }
   else
    {
      outstatus.Set(__L("Desconectado"));
      outquality.Set(__L("Sin conexi\u00F3n"));
      outmark.Set(__L("--"));
    }

  //--------------------------------------------------------------------------------------
  // Local IP (first active local network device: Ethernet/WiFi/PPP).
  //--------------------------------------------------------------------------------------

  DIOSTREAMIPLOCALENUMDEVICES* enumdevices = (DIOSTREAMIPLOCALENUMDEVICES*)GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_IP_LOCAL);
  if(enumdevices)
    {
      DIOSTREAMDEVICEIP* device = (DIOSTREAMDEVICEIP*)enumdevices->GetFirstActiveDevice();
      if(device)
        {
          XSTRING ipstring;

          device->GetIP()->GetXString(ipstring);

          outip.Format(__L("IP: %s"), ipstring.Get());
        }
       else
        {
          outip.Set(__L("IP: --"));
        }

      GEN_DIOFACTORY.DeleteStreamEnumDevices(enumdevices);
    }
   else
    {
      outip.Set(__L("IP: --"));
    }

  //--------------------------------------------------------------------------------------
  // Public WAN IP via GEN_DIOPUBLICINTERNETIP (ipecho.net). Cached while connected so the
  // background poll does not re-hit HTTP on every HardwareInfo tick.
  //--------------------------------------------------------------------------------------

  outpublicip.Set(__L("IP P\u00FAblica: --"));

  #ifdef DIO_PUBLICINTERNETIP_ACTIVE
  {
    static XSTRING cachedpublicip;
    static bool    havecachedpublicip = false;

    if(!outisconnected)
      {
        havecachedpublicip = false;
        cachedpublicip.Empty();
      }
     else
      {
        if(!havecachedpublicip)
          {
            XSTRING fetched;
            if(GEN_DIOPUBLICINTERNETIP.Get(fetched) && (!fetched.IsEmpty()))
              {
                cachedpublicip.Set(fetched.Get());
                havecachedpublicip = true;
              }
          }

        if(havecachedpublicip)
          {
            outpublicip.Format(__L("IP P\u00FAblica: %s"), cachedpublicip.Get());
          }
      }
  }
  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateFooter(XSTRING& outequipo, XSTRING& outso, XSTRING& outuptime)
* @brief      Builds the status bar literals (equipment name, operative system and uptime summary).
* @note       Called from HardwareInfo_Compute(), on the background thread.
* @ingroup    EXAMPLES
*
* @param[out] outequipo : "Equipo: <domain>" (or "Equipo: --" if unavailable).
* @param[out] outso : "SO: <id>" (or "SO: --" if unavailable).
* @param[out] outuptime : "Uptime del sistema: <measure>".
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateFooter(XSTRING& outequipo, XSTRING& outso, XSTRING& outuptime)
{
  //--------------------------------------------------------------------------------------
  // Equipment name: GEN does not expose the machine hostname on every platform (it is
  // intentionally left out of XSYSTEM::GetOperativeSystemID()), so GetUserAndDomain() is used
  // as a best-effort source and, if it is not available, the field is left as a placeholder.
  //--------------------------------------------------------------------------------------

  XSTRING user;
  XSTRING domain;

  if(GEN_XSYSTEM.GetUserAndDomain(user, domain) && (!domain.IsEmpty()))
    {
      outequipo.Format(__L("Equipo: %s"), domain.Get());
    }
   else
    {
      outequipo.Set(__L("Equipo: --"));                    // TODO: add a real hostname source for this platform
    }

  //--------------------------------------------------------------------------------------

  XSTRING operativesystemID;

  if(GEN_XSYSTEM.GetOperativeSystemID(operativesystemID) && (!operativesystemID.IsEmpty()))
    {
      // Shorten live Windows strings ("Microsoft Windows 11 Pro Build 26200") so the footer can show
      // Equipo | SO | Uptime without the huge fixed gaps the mockup used for short Linux IDs.
      XSTRING soid = operativesystemID;
      if(soid.Find(__L("Microsoft "), true) == 0) soid.DeleteCharacters(0, 10);
      int buildat = soid.Find(__L(" Build"), true);
      if(buildat >= 0) soid.DeleteCharactersToEnd((XDWORD)buildat);
      outso.Format(__L("SO: %s"), soid.Get());
    }
   else
    {
      outso.Set(__L("SO: --"));
    }

  //--------------------------------------------------------------------------------------

  if(xtimer)
    {
      XSTRING measure;

      xtimer->GetMeasureString(measure, true);

      if(!measure.IsEmpty())
            outuptime.Format(__L("Uptime del sistema: %s"), measure.Get());
       else outuptime.Set(__L("Uptime del sistema: 0 segundos"));
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::UserInterface_ElementSelected(UI_ELEMENT* element)
* @brief      Processes the selected user interface element.
* @ingroup    EXAMPLES
*
* @param[in]  element : User interface element to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UserInterface_ElementSelected(UI_ELEMENT* element)
{
  if(!element) return false;


  switch(element->GetChromeRole())
    {
      case UI_ELEMENT_CHROMEROLE_ICON     : break;

      case UI_ELEMENT_CHROMEROLE_MINIMIZE : if(GetMainScreen()) GetMainScreen()->Minimize(true);
                                            break;

      case UI_ELEMENT_CHROMEROLE_MAXIMIZE : { // Toggle grow ↔ restore. Enable autofit so maximize uses the screen.
                                              UI_LAYOUT* dashboard = GEN_USERINTERFACE.Layouts_Get(__L("dashboard"));
                                              if(dashboard && dashboard->IsUIScaleActive())
                                                {
                                                  dashboard->SetUIScaleAutofit(true);
                                                  APPFLOW_CFG.SetUIScaleAutofit(true);
                                                }
                                              if(GetMainScreen())
                                                {
                                                  if(GetMainScreen()->IsClientSizeAtMaximum())
                                                    GetMainScreen()->Maximize(false);
                                                   else
                                                    GetMainScreen()->Maximize(true);
                                                }
                                            }
                                            break;

      case UI_ELEMENT_CHROMEROLE_CLOSE    : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                            break;

      default                             : break;
    }


  XSTRING elementname;

  elementname = element->GetName()->Get();

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("UI Element [%s]: Selected! "), element->GetName()->Get());

  if(!elementname.Compare(__L("nav-resumen-btn")       , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_RESUMEN);
  if(!elementname.Compare(__L("nav-cpu-btn")           , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_CPU);
  if(!elementname.Compare(__L("nav-memoria-btn")       , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_MEMORIA);
  if(!elementname.Compare(__L("nav-red-btn")           , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_RED);
  if(!elementname.Compare(__L("nav-disco-btn")         , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_DISCO);
  if(!elementname.Compare(__L("nav-procesos-btn")      , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_PROCESOS);
  if(!elementname.Compare(__L("nav-alertas-btn")       , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_ALERTAS);
  if(!elementname.Compare(__L("nav-configuracion-btn") , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_CONFIGURACION);

  // Disk carousel buttons (empty hit targets over icons — same idea as nav-*-btn).
  if((!elementname.Compare(__L("disk_prev_btn"), true)))
    {
      HardwareInfo_CycleDisk(-1);
      HardwareInfo_Apply();
    }

  if((!elementname.Compare(__L("disk_next_btn"), true)))
    {
      HardwareInfo_CycleDisk(+1);
      HardwareInfo_Apply();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::UserInterface_SelectSection(UI_SYSTEM_SECTIONID sectionID)
* @brief      Highlights the selected sidebar entry.
* @note       Only the "Resumen" section has real dashboard content for now (it is the section
*             shown in the reference mock-up); the remaining sections are already wired for
*             navigation and are left ready to receive their own content_xxx panel later.
* @ingroup    EXAMPLES
*
* @param[in]  sectionID : Section to select.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UserInterface_SelectSection(UI_SYSTEM_SECTIONID sectionID)
{
  // Official selection path: SetSelected on the hit-target button (CSS :selected wash) and on the nav-row
  // so descendant rules like `form.nav-row:selected .nav-label` restyle the label without C++ color hacks.
  // Legacy nav-*-hl / nav-*-bar overlays are removed from the layout; stylesheet is the source of truth.
  static XCHAR* navbtnnames[UI_SYSTEM_SECTIONID_MAX]    = { __L("nav-resumen-btn")       ,
                                                             __L("nav-cpu-btn")           ,
                                                             __L("nav-memoria-btn")       ,
                                                             __L("nav-red-btn")           ,
                                                             __L("nav-disco-btn")         ,
                                                             __L("nav-procesos-btn")      ,
                                                             __L("nav-alertas-btn")       ,
                                                             __L("nav-configuracion-btn")  };

  static XCHAR* navrownames[UI_SYSTEM_SECTIONID_MAX]    = { __L("nav-resumen-row")       ,
                                                             __L("nav-cpu-row")           ,
                                                             __L("nav-memoria-row")       ,
                                                             __L("nav-red-row")           ,
                                                             __L("nav-disco-row")         ,
                                                             __L("nav-procesos-row")      ,
                                                             __L("nav-alertas-row")       ,
                                                             __L("nav-configuracion-row")  };

  for(int c=0; c<UI_SYSTEM_SECTIONID_MAX; c++)
    {
      bool isactive = (c == (int)sectionID);

      UI_ELEMENT* element_btn = GEN_USERINTERFACE.Element_Get(navbtnnames[c], UI_ELEMENT_TYPE_BUTTON);
      if(element_btn) element_btn->SetSelected(isactive);

      UI_ELEMENT* element_row = GEN_USERINTERFACE.Element_Get(navrownames[c], UI_ELEMENT_TYPE_FORM);
      if(element_row)
        {
          element_row->SetSelected(isactive);
          // Redraw the row (accent + label) only -- not the overlay nav-*-btn. Forcing the buttons to
          // redraw at Ini/SelectSection made them OptionBackdrop-capture before/without nav ink and then
          // keep restoring a blank strip (video: sidebar empty until click).
          GEN_USERINTERFACE.Elements_SetToRedraw(element_row, true);
        }
    }

  currentsectionID = sectionID;

  chart_force_rebuild = true;
  HistoryChart_Apply(true);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::UserInterface_AdjustUIScale(double delta)
* @brief      Fase 4: runtime zoom (+/−). Clamps, reclama paint, persists to ui_system.ini.
* @ingroup    EXAMPLES
*
* @param[in]  delta : Scale step (typically ±UI_LAYOUT_UISCALE_STEP).
*
* @return     bool : true if applied.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UserInterface_AdjustUIScale(double delta)
{
  UI_LAYOUT* dashboard = GEN_USERINTERFACE.Layouts_Get(__L("dashboard"));
  if(!dashboard) return false;

  double next = dashboard->GetUIScale() + delta;
  if(!GEN_USERINTERFACE.Layouts_SetUIScale(dashboard, next)) return false;

  APPFLOW_CFG.SetUIScale((float)dashboard->GetUIScale());
  APPFLOW_CFG.SetUIScaleAutofit(false);
  APPFLOW_CFG.Save();

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[UI_System] UIScale -> %.2f (manual)"), dashboard->GetUIScale());
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
* @brief      Resolves a user interface literal text.
* @ingroup    EXAMPLES
*
* @param[in]  element_text : Text element that contains the literal to resolve.
* @param[in]  maskvalue : Mask value to resolve.
* @param[in]  maskresolved : Resolved mask output value.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
{
  if(!element_text)   return false;
  if(!maskvalue)      return false;
  if(!maskresolved)   return false;

  if(!maskvalue->Compare(__L("APP_VERSION"), true))
    {
      maskresolved->Format(__L("%d.%d.%d"), APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
    }

  //--------------------------------------------------------------------------------------
  // Every field read below is also written by HardwareInfo_Compute(), on the background
  // thread (see the note in UI_System.h) -- this runs on the main thread (called from inside
  // GEN_USERINTERFACE.Update(), during DrawFrame()'s redraw), so it needs the same mutex to
  // avoid reading a string the background thread is mid-Set()/Format() on.
  //--------------------------------------------------------------------------------------

  if(hardwareinfomutex) hardwareinfomutex->Lock();

  if(!maskvalue->Compare(__L("CPU_TEMPERATURE")   , true))  maskresolved->Set(cpu_temperature_str.Get());
  if(!maskvalue->Compare(__L("RAM_USED_TOTAL")    , true))  maskresolved->Set(ram_used_total_str.Get());
  if(!maskvalue->Compare(__L("RAM_USED")          , true))  maskresolved->Set(ram_used_str.Get());
  if(!maskvalue->Compare(__L("RAM_TOTAL")         , true))  maskresolved->Set(ram_total_str.Get());
  if(!maskvalue->Compare(__L("DISK_USED")         , true))  maskresolved->Set(disk_used_str.Get());
  if(!maskvalue->Compare(__L("DISK_TOTAL")        , true))  maskresolved->Set(disk_total_str.Get());
  if(!maskvalue->Compare(__L("DISK_CAPTION")      , true))  maskresolved->Set(disk_caption_str.Get());
  if(!maskvalue->Compare(__L("DISK_INDEX")        , true))  maskresolved->Set(disk_index_str.Get());
  if(!maskvalue->Compare(__L("SYSTEM_DATE")       , true))  maskresolved->Set(system_date_str.Get());
  if(!maskvalue->Compare(__L("SYSTEM_TIME")       , true))  maskresolved->Set(system_time_str.Get());
  if(!maskvalue->Compare(__L("CONNECTION_STATUS") , true))  maskresolved->Set(connection_status_str.Get());
  if(!maskvalue->Compare(__L("CONNECTION_QUALITY"), true))  maskresolved->Set(connection_quality_str.Get());
  if(!maskvalue->Compare(__L("CONNECTION_MARK")   , true))  maskresolved->Set(connection_mark_str.Get());
  if(!maskvalue->Compare(__L("LOCAL_IP")          , true))  maskresolved->Set(local_ip_str.Get());
  if(!maskvalue->Compare(__L("PUBLIC_IP")         , true))  maskresolved->Set(public_ip_str.Get());
  if(!maskvalue->Compare(__L("FOOTER_EQUIPO")     , true))  maskresolved->Set(footer_equipo_str.Get());
  if(!maskvalue->Compare(__L("FOOTER_SO")         , true))  maskresolved->Set(footer_so_str.Get());
  if(!maskvalue->Compare(__L("FOOTER_UPTIME")     , true))  maskresolved->Set(footer_uptime_str.Get());

  if(hardwareinfomutex) hardwareinfomutex->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SYSTEM::UserInterface_CFGChromes(GRPSCREEN* screen)
* @brief      user interface  CFGchromes
* @ingroup    
* 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UserInterface_CFGChromes(GRPSCREEN* screen)
{
  GRPSCREENCFGCHROMES cfgchromes;

  #ifdef GRP_SCREEN_CUSTOMCHROMES_ACTIVE

  //cfgchromes.SetCustomAutoHide(500);

  #else

  cfgchromes.SetNativeCaptionActive(true);
  cfgchromes.SetNativeIconActive(true);
  cfgchromes.SetNativeTitleActive(true); 
  cfgchromes.SetNativeMinimizeActive(true);
  cfgchromes.SetNativeMaximizeActive(true);
  cfgchromes.SetNativeCloseActive(true);  

  #endif

  cfgchromes.SetResizeActive(true);

  screen->SetCFGChromes(cfgchromes);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_SYSTEM::HandleEvent_UserInterface(UI_XEVENT* event)
* @brief      Handles user interface events.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_SYSTEM::HandleEvent_UserInterface(UI_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case  UI_XEVENT_TYPE_OUTPUT_SELECTED        : { UI_ELEMENT* element = event->GetElement();
                                                      if(element) UserInterface_ElementSelected(element);                                                      
                                                    }
                                                    break;

      case UI_XEVENT_TYPE_OUTPUT_TEXTTOCHANGE     : { UI_ELEMENT_TEXT* element_text = (UI_ELEMENT_TEXT*)event->GetElement();

                                                      UserInterface_ChangeLiteralText(element_text, event->GetMaskTextValue(), event->GetMaskTextResolved());
                                                    } 
                                                    break;

      case UI_XEVENT_TYPE_OUTPUT_CHANGECONTENTS   : break;
      
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_SYSTEM::HandleEvent_Graphics(GRPXEVENT* event)
* @brief      Handles graphics events.
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_SYSTEM::HandleEvent_Graphics(GRPXEVENT* event)
{
  switch(event->GetEventType())
    {
      case GRPXEVENT_TYPE_SCREEN_CREATING   : { GRPSCREEN* screen  = event->GetScreen();
                                                if(!screen) break;
                                                                                              
                                                Ini_Graphics(screen);                                         
                                              }
                                              break;

      case GRPXEVENT_TYPE_SCREEN_CHANGESIZE : { GRPSCREEN* screen = event->GetScreen();
                                                if(!screen) break;

                                                // Live resize runs inside Windows' modal drag loop: UpdateSize has
                                                // already recreated empty canvas buffers. Without an immediate UI
                                                // paint here, WM_SIZE's UpdateViewports() presents black until the
                                                // main loop runs again (mouse-up). Also: never Save() the ini on
                                                // every size tick — that stalls the drag.
                                                UI_LAYOUT* dashboard = GEN_USERINTERFACE.Layouts_Get(__L("dashboard"));
                                                if(dashboard && dashboard->IsUIScaleActive())
                                                  {
                                                    #ifdef ANDROID
                                                    // Track P: keep design canvas; GLES letterbox follows the new
                                                    // native surface. Do not ApplyFitUIScale against a resized
                                                    // framebuffer (would fight platform present + MapWindowToCanvas).
                                                    if(screen->GetWidth() != dashboard->GetDesignWidth() ||
                                                       screen->GetHeight() != dashboard->GetDesignHeight())
                                                      {
                                                        screen->SetWidth(dashboard->GetDesignWidth());
                                                        screen->SetHeight(dashboard->GetDesignHeight());
                                                      }
                                                    dashboard->SetUIScaleAutofit(true);
                                                    dashboard->SetUIScaleForFit(UI_LAYOUT_UISCALE_DEFAULT);
                                                    GEN_USERINTERFACE.UIScale_PrepareLayout(dashboard);
                                                    GEN_USERINTERFACE.Update();
                                                    XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[UI_System] Android config: keep design %dx%d UIScale=1.0"),
                                                                      dashboard->GetDesignWidth(), dashboard->GetDesignHeight());
                                                    #else
                                                    if(dashboard->GetUIScaleAutofit())
                                                      {
                                                        GEN_USERINTERFACE.Layouts_ApplyFitUIScale(dashboard);
                                                        APPFLOW_CFG.SetUIScale((float)dashboard->GetUIScale());
                                                        APPFLOW_CFG.SetUIScaleAutofit(true);
                                                      }
                                                     else
                                                      {
                                                        // Manual zoom: still refresh present offsets for the new
                                                        // framebuffer size (letterbox/pillarbox).
                                                        GEN_USERINTERFACE.UIScale_PrepareLayout(dashboard);
                                                      }

                                                    // L.4 re-resolve is NOT called on every size tick: fixed design
                                                    // + autofit means vw/% do not change with the window; calling
                                                    // Layouts_ReresolveStyleLengths here corrupted flex/% positions
                                                    // (progress scale labels, card grid). Use Layouts_SetDesignSize
                                                    // when the authoring viewport itself changes.

                                                    GEN_USERINTERFACE.Update();

                                                    XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[UI_System] UIScale size -> %.2f autofit=%d (%dx%d)"),
                                                                      dashboard->GetUIScale(),
                                                                      dashboard->GetUIScaleAutofit() ? 1 : 0,
                                                                      screen->GetWidth(), screen->GetHeight());
                                                    #endif
                                                  }
                                              }
                                              break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_SYSTEM::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_SYSTEM::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_GRAPHICS       : { GRPXEVENT* event = (GRPXEVENT*)xevent;
                                          if(!event) return;

                                          HandleEvent_Graphics(event);
                                        }
                                        break;

      case XEVENT_TYPE_USERINTERFACE  : { UI_XEVENT* event = (UI_XEVENT*)xevent;
                                          if(!event) return;

                                          HandleEvent_UserInterface(event);
                                        }
                                        break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_SYSTEM::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_SYSTEM::Clean()
{
  xtimer                       = NULL;

  for(int c=0; c<UI_SYSTEM_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }

  cursor                        = NULL;

  diocheckinternetconnection    = NULL;

  currentsectionID               = UI_SYSTEM_SECTIONID_RESUMEN;
  lastupdatehardwareinfo_second  = 0;

  dashboardloaded                = false;

  hardwareinfothread              = NULL;
  hardwareinfomutex               = NULL;

  hardwareinfoexiting             = false;
  hardwareinfo_forcenext          = false;
  hardwareinfo_haspending         = false;

  cpu_temperaturelevel            = 0.0f;
  cpu_usagelevel                  = 0.0f;
  ram_usagelevel                  = 0.0f;
  disk_usagelevel                 = 0.0f;
  disk_slot_count                 = 0;
  disk_slot_index                 = 0;
  isconnected                     = false;

  for(int s=0; s<UI_SYSTEM_DISK_SLOT_MAX; s++)
    {
      disk_slot_level[s] = 0.0f;
      disk_slot_name[s].Empty();
      disk_slot_used[s].Empty();
      disk_slot_total[s].Empty();
    }

  cpuhistory_count                = 0;
  cpuhistory_write                = 0;
  ramhistory_count                = 0;
  ramhistory_write                = 0;
  lastchartrebuild_second         = 0;
  chart_force_rebuild             = true;

  for(int c=0; c<UI_SYSTEM_CPUHISTORY_MAX; c++)
    {
      cpuhistory_samples[c] = 0.0f;
    }

  for(int c=0; c<UI_SYSTEM_RAMHISTORY_MAX; c++)
    {
      ramhistory_samples[c] = 0.0f;
    }

  cpu_temperature_str.Empty();
  ram_used_total_str.Empty();
  ram_used_str.Empty();
  ram_total_str.Empty();
  disk_used_str.Empty();
  disk_total_str.Empty();
  disk_caption_str.Empty();
  disk_index_str.Empty();
  system_date_str.Empty();
  system_time_str.Empty();
  connection_status_str.Empty();
  connection_quality_str.Empty();
  connection_mark_str.Empty();
  local_ip_str.Empty();
  public_ip_str.Empty();
  footer_equipo_str.Empty();
  footer_so_str.Empty();
  footer_uptime_str.Empty();
}
