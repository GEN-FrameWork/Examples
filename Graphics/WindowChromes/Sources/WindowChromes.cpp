/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       WindowChromes.cpp
* 
* @class      WINDOWCHROMES
* @brief      Graphics UI Options Example class
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

#include "WindowChromes.h"

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
#include "XThreadCollected.h"
#include "XThread.h"
#include "XTrace.h"

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

#include "GRP2DCanvas.h"
#include "GRP2DPath.h"
#include "GRPScreenCFGChromes.h"
#include "GRPScreen.h"
#include "GRPViewPort.h"
#include "GRPBitmapFile.h"
#include "GRPBitmapFileJPG.h"
#include "GRPVideoFileAVI.h"
#include "GRPVectorFile.h"
#include "GRPXEvent.h"

#include "INPManager.h"

#include "UI_XEvent.h"
#include "UI_Manager.h"
#include "UI_Element.h"
#include "UI_Element_Animation.h"
#include "UI_Element_Option.h"
#include "UI_Element_Menu.h"
#include "UI_Element_ListBox.h"
#include "UI_Element_Button.h"
#include "UI_Element_ProgressBar.h"
#include "UI_Element_ProgressRadial.h"
#include "UI_Element_ProgressImage.h"
#include "UI_SkinCanvas.h"

#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#include "WindowChromes_CFG.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(WINDOWCHROMES, canvas2d)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         WINDOWCHROMES::WINDOWCHROMES()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
WINDOWCHROMES::WINDOWCHROMES() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         WINDOWCHROMES::~WINDOWCHROMES()
* @brief      Destructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
WINDOWCHROMES::~WINDOWCHROMES()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES::InitFSMachine()
{
  if(!AddState( WINDOWCHROMES_XFSMSTATE_NONE           ,
                WINDOWCHROMES_XFSMEVENT_INI            , WINDOWCHROMES_XFSMSTATE_INI          ,
                WINDOWCHROMES_XFSMEVENT_END            , WINDOWCHROMES_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( WINDOWCHROMES_XFSMSTATE_INI            ,
                WINDOWCHROMES_XFSMEVENT_NONE           , WINDOWCHROMES_XFSMSTATE_NONE         ,
                WINDOWCHROMES_XFSMEVENT_END            , WINDOWCHROMES_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( WINDOWCHROMES_XFSMSTATE_END            ,
                WINDOWCHROMES_XFSMEVENT_NONE           , WINDOWCHROMES_XFSMSTATE_NONE         ,
                WINDOWCHROMES_XFSMEVENT_INI            , WINDOWCHROMES_XFSMSTATE_INI          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  bool    status = false;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  Application_GetName()->Set(APPLICATION_NAMEAPP);

  SetInitOptions(APPFLOWGRAPHICS_INIOPTION_CREATEMAINSCREEN | APPFLOWGRAPHICS_INIOPTION_SHOWMAINSCREEN | APPFLOWGRAPHICS_INIOPTION_INPUT);

  //--------------------------------------------------------------------------------------------------

  // ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  // ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, APPFLOW_DEFAULT_DIRECTORY_GRAPHICS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_FONTS, APPFLOW_DEFAULT_DIRECTORY_FONTS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_UI_LAYOUTS, APPFLOW_DEFAULT_DIRECTORY_UI_LAYOUTS);


  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------

  xtimer = GEN_XFACTORY.CreateTimer();
  if(!xtimer) return false;


  //--------------------------------------------------------------------------------------

  xrand = GEN_XFACTORY.CreateRand();
  if(!xrand) return false;

  xrand->Ini();  

  //--------------------------------------------------------------------------------------
  
  { XPATH xpath;
    
    GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
    xpath.Slash_Add();
    xpath.Add(APPLICATION_NAMEFILE);
    xpath.Add(XTRANSLATION_NAMEFILEEXT);    

    if(!GEN_XTRANSLATION.Ini(xpath))
      {
        return false;
      }

    GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_ENG);
  }

  //--------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG);

  //--------------------------------------------------------------------------------------

  SetEvent(WINDOWCHROMES_XFSMEVENT_INI);

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[WINDOWCHROMES_BUTTON_UP]      = inpdevice->GetButton(INPBUTTON_ID_UP);
      button[WINDOWCHROMES_BUTTON_DOWN]    = inpdevice->GetButton(INPBUTTON_ID_DOWN);
      button[WINDOWCHROMES_BUTTON_LEFT]    = inpdevice->GetButton(INPBUTTON_ID_LEFT);
      button[WINDOWCHROMES_BUTTON_RIGHT]   = inpdevice->GetButton(INPBUTTON_ID_RIGHT);
      button[WINDOWCHROMES_BUTTON_SPACE]   = inpdevice->GetButton(INPBUTTON_ID_SPACE);
      button[WINDOWCHROMES_BUTTON_ESC]     = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[WINDOWCHROMES_BUTTON_F1]      = inpdevice->GetButton(INPBUTTON_ID_F1);
      button[WINDOWCHROMES_BUTTON_F2]      = inpdevice->GetButton(INPBUTTON_ID_F2);
      button[WINDOWCHROMES_BUTTON_F5]      = inpdevice->GetButton(INPBUTTON_ID_F5);
      button[WINDOWCHROMES_BUTTON_F9]      = inpdevice->GetButton(INPBUTTON_ID_F9);
      button[WINDOWCHROMES_BUTTON_MINUS]   = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_MINUS);
      button[WINDOWCHROMES_BUTTON_PLUS]    = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_PLUS);

      button[WINDOWCHROMES_BUTTON_MOUSE]   = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[WINDOWCHROMES_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[WINDOWCHROMES_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }

  //--------------------------------------------------------------------------------------

  if(!Ini_UserInterface(true)) return false;

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES::AppProc_Update()
{
  if(GetEvent()==WINDOWCHROMES_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case WINDOWCHROMES_XFSMSTATE_NONE       : break;

          case WINDOWCHROMES_XFSMSTATE_INI        : UpdateInput();
                                                    DrawFrame();
                                                    GetMainScreen()->UpdateViewports();
                                                    break;

          case WINDOWCHROMES_XFSMSTATE_END        : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<WINDOWCHROMES_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case WINDOWCHROMES_XFSMSTATE_NONE    : break;

              case WINDOWCHROMES_XFSMSTATE_INI     : break;

              case WINDOWCHROMES_XFSMSTATE_END     : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetCurrentState(WINDOWCHROMES_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------
  
  Ini_UserInterface(false);

  //--------------------------------------------------------------------------------------
  
  if(vectorfile)
    {
      GEN_DELETE vectorfile;
      vectorfile = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(testbmp)
    {
      delete testbmp;
      testbmp = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(xrand)
    {
      GEN_XFACTORY.DeleteRand(xrand);
      xrand = NULL;  
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
* @fn         bool WINDOWCHROMES::UpdateInput()
* @brief      Updates the application input state.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES::UpdateInput()
{
   int  width  = GetMainScreen()->GetWidth();
   int  height = GetMainScreen()->GetHeight();

  if(cursor)    
    {  
    
      if(cursor->GetMotion()->IsReadyToTest(50))
        {
          cursor->GetMotion()->InvertYAxis(height);

          GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOTION, cursor->GetMotion());

          cursor->GetMotion()->Reset();
        }

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
              GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE, cursor_x, cursor_y);
            }

          if(button[WINDOWCHROMES_BUTTON_MOUSE]->IsPressedWithRelease())
            {
              GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION, cursor_x, cursor_y);   

              cursor->GetMotion()->Reset();       
            }

          if(button[WINDOWCHROMES_BUTTON_TOUCHSCREEN])
            {             
              if(button[WINDOWCHROMES_BUTTON_TOUCHSCREEN]->IsPressed())
                {             
                  GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE, cursor_x, cursor_y);
                  GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION, cursor_x, cursor_y);          

                  cursor->GetMotion()->Reset();
                }
            }
      }
    }


  for(int c=0; c<WINDOWCHROMES_BUTTON_MOUSE; c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  
                  case WINDOWCHROMES_BUTTON_F1        : break;

                  case WINDOWCHROMES_BUTTON_F2        : break;
                            
                  case WINDOWCHROMES_BUTTON_F5        : Ini_UserInterface(false);
                                                        Ini_UserInterface(true);                      
                                                        break;

                  case WINDOWCHROMES_BUTTON_F9        : break;

                  case WINDOWCHROMES_BUTTON_ESC       : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                        break;
                }
            }

          if(button[c]->IsPressed())
            {
              switch(c)
                {
                  case WINDOWCHROMES_BUTTON_UP        : 
                  case WINDOWCHROMES_BUTTON_DOWN      : break;    

                  case WINDOWCHROMES_BUTTON_LEFT      : break;
                  case WINDOWCHROMES_BUTTON_RIGHT     : break;
                  case WINDOWCHROMES_BUTTON_SPACE     : break;
                  
                }
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES::Ini_Graphics(GRPSCREEN* screen)
* @brief      Initializes the graphics subsystem.
* @ingroup    EXAMPLES
*
* @param[in]  screen : Screen where the graphics or user interface resources are created.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES::Ini_Graphics(GRPSCREEN* screen)
{
  screen->SetWidth(1024);
  screen->SetHeight(768);


  UserInterface_CFGChromes(screen);

  //screen->Styles_Set(GRPSCREENSTYLE_TRANSPARENT);
  //screen->Styles_Set(GRPSCREENSTYLE_FULLSCREEN);
  
  screen->GetTitle()->Set(__L("Window Chromes"));  
  screen->SetDesktopScreenSelected(GRPSCREENTYPE_DESKTOP_MAIN);

  GetMainScreen()->CreateViewport(GRPVIEWPORT_ID_MAIN, 0.0f, 0.0f, (float)screen->GetWidth(), (float)screen->GetHeight(), 0, 0, (screen->GetWidth()), (screen->GetHeight()));

  //--------------------------------------------------------------------------------------

  XPATH pathvf;
 
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, pathvf);
  pathvf.Slash_Add();
  pathvf.Add(__L("tiger.svg"));
  
  vectorfile = GRPVECTORFILE::CreateInstance(pathvf);
  if(vectorfile)
    {
      vectorfile->Load();      
    }
                                          
  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES::Ini_UserInterface(bool on)
* @brief      Initializes or ends the user interface.
* @ingroup    EXAMPLES
*
* @param[in]  on : true to enable the operation; false to disable it.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES::Ini_UserInterface(bool on)
{  
  if(!on)
    { 
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
  xpath.Add(__L("example/example.xml"));
    
  if(!GEN_USERINTERFACE.Load(xpath, screen, 0)) 
    {
      return false;
    }

  GEN_USERINTERFACE.SubscribeInputEvents(true);
  GEN_USERINTERFACE.SubscribeOutputEvents(true, this, &GEN_USERINTERFACE.GetInstance());   

  GEN_USERINTERFACE.Layout_PutBackground();

  GEN_USERINTERFACE.Elements_SetToRedraw();


  canvas->CreateRebuildArea(325.0+50, 200.0, 250.0 + 75, 250.0 + 75);   
        
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES::DrawFrame()
* @brief      Draws the current frame.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES::DrawFrame()
{
  GRP2DCOLOR_RGBA8  colorblack(0, 0, 0);
  GRP2DCOLOR_RGBA8  colorwhite(255, 255, 255);
  GRP2DCOLOR_RGBA8  colorred(255, 0, 0);
  GRP2DCOLOR_RGBA8  colorgreen(0, 255, 0);
  GRP2DCOLOR_RGBA8  colorblue(0, 0, 255);
  GRP2DCOLOR_RGBA8  colorgray(10, 10, 10, 150);

  GRPSCREEN*     screen    = NULL;
  GRPVIEWPORT*   viewport  = NULL;
  GRP2DCANVAS*   canvas    = NULL;
  int            width     = 0;
  int            height    = 0;


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

  width  = screen->GetWidth();
  height = screen->GetHeight();

  canvas->ReleaseDrawFramerate();   

  canvas->RebuildAllAreas();

  //--------------------------------------------------------------------------------------

  
  static double zoom   = 0; //(double)xrand->Between(1, 75);
  static bool   invert = false;

  if(!invert) zoom += 1.0; else zoom -= 1.0;
  
  if(zoom >= 75)  invert = !invert;
  if(zoom < 0)    invert = !invert;  

  

   if(vectorfile)
    {        
      vectorfile_render.Render(vectorfile, canvas, 325.0+50, 200.0, 250.0 + zoom, 250.0 + zoom);   

      //vectorfile_render.RenderCached(vectorfile, canvas, 30.0, 30.0, canvas->GetWidth()-130, canvas->GetHeight()-30);   
    }
  
  //--------------------------------------------------------------------------------------

  canvas->DrawFramerate(screen, 6, 750);

  //--------------------------------------------------------------------------------------

  GEN_USERINTERFACE.Elements_RebuildDrawAreas();
  
  GEN_USERINTERFACE.Update(); 

  //--------------------------------------------------------------------------------------

  

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES::UserInterface_ElementSelected(UI_ELEMENT* element)
* @brief      Processes the selected user interface element.
* @ingroup    EXAMPLES
*
* @param[in]  element : User interface element to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES::UserInterface_ElementSelected(UI_ELEMENT* element)
{
  if(!element) return false;

  switch(element->GetChromeRole())
    {
      case UI_ELEMENT_CHROMEROLE_ICON     : break;

      case UI_ELEMENT_CHROMEROLE_MINIMIZE : if(GetMainScreen()) GetMainScreen()->Minimize(true);
                                            break;

      case UI_ELEMENT_CHROMEROLE_MAXIMIZE : if(GetMainScreen()) GetMainScreen()->Maximize(true);
                                            break;

      case UI_ELEMENT_CHROMEROLE_CLOSE    : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                            break;

      default                             : break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
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
bool WINDOWCHROMES::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
{
  if(!element_text)   return false;
  if(!maskvalue)      return false;
  if(!maskresolved)   return false;

 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool WINDOWCHROMES::UserInterface_CFGChromes(GRPSCREEN* screen)
* @brief      user interface  CFGchromes
* @ingroup    
* 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES::UserInterface_CFGChromes(GRPSCREEN* screen)
{
  GRPSCREENCFGCHROMES cfgchromes;

  #ifdef GRP_SCREEN_CUSTOMCHROMES_ACTIVE

  /*
  XPATH xpath;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_UI_LAYOUTS, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("chrome/chrome.xml"));
  //xpath.Add(__L("chrome.zip"));


  cfgchromes.SetCustomLayoutFile(xpath.Get());
  cfgchromes.SetCustomLayoutName(__L("chrome"));
  */

  cfgchromes.SetCustomAutoHide(1);

  #else

  cfgchromes.SetNativeCaptionActive(true);
  cfgchromes.SetNativeIconActive(false);
  cfgchromes.SetNativeTitleActive(false);
 
  cfgchromes.SetNativeMinimizeActive(true);
  cfgchromes.SetNativeMaximizeActive(false);
  cfgchromes.SetNativeCloseActive(true);  

  #endif

  cfgchromes.SetResizeActive(false);

  screen->SetCFGChromes(cfgchromes);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void WINDOWCHROMES::HandleEvent_UserInterface(UI_XEVENT* event)
* @brief      Handles user interface events.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void WINDOWCHROMES::HandleEvent_UserInterface(UI_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case  UI_XEVENT_TYPE_OUTPUT_SELECTED        : { UI_ELEMENT* element = event->GetElement();
                                                      if(element) UserInterface_ElementSelected(element);                                                      
                                                    }
                                                    break;

      case UI_XEVENT_TYPE_OUTPUT_TEXTTOCHANGE     : { UI_ELEMENT_TEXT* element_text = (UI_ELEMENT_TEXT*)event->GetElement();
                                                      XSTRING          maskvalue;
                                                    
                                                      if(UserInterface_ChangeLiteralText(element_text, event->GetMaskTextValue(), event->GetMaskTextResolved()))
                                                        {
                                                        
                                                        }
                                                    } 
                                                    break;

      case UI_XEVENT_TYPE_OUTPUT_CHANGECONTENTS   : { 
                                                    }
                                                    break;
      
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void WINDOWCHROMES::HandleEvent_Graphics(GRPXEVENT* event)
* @brief      Handles graphics events.
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void WINDOWCHROMES::HandleEvent_Graphics(GRPXEVENT* event)
{
  switch(event->GetEventType())
    {
      case GRPXEVENT_TYPE_SCREEN_CREATING   : { GRPSCREEN* screen  = event->GetScreen();
                                                if(!screen) break;
                                                                                              
                                                Ini_Graphics(screen);                                         
                                              }
                                              break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void WINDOWCHROMES::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void WINDOWCHROMES::HandleEvent(XEVENT* xevent)
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
* @fn         void WINDOWCHROMES::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void WINDOWCHROMES::Clean()
{
  xtimer       = NULL;
  xrand        = NULL;

  for(int c=0; c<WINDOWCHROMES_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }
  
  testbmp     = NULL;    

  vectorfile  = NULL;  
}