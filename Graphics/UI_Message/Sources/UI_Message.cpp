/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Message.cpp
* 
* @class      UI_MESSAGE
* @brief      Graphics UI Message Example class
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

#include "UI_Message.h"

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
#include "GRPScreen.h"
#include "GRPViewPort.h"
#include "GRPBitmapFile.h"
#include "GRPBitmapFileJPG.h"
#include "GRPVideoFileAVI.h"
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
#include "UI_SkinCanvas.h"

#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#include "UI_Message_CFG.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(UI_MESSAGE, canvas2d)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_MESSAGE::UI_MESSAGE()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_MESSAGE::UI_MESSAGE() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_MESSAGE::~UI_MESSAGE()
* @brief      Destructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_MESSAGE::~UI_MESSAGE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE::InitFSMachine()
{
  if(!AddState( UI_MESSAGE_XFSMSTATE_NONE           ,
                UI_MESSAGE_XFSMEVENT_INI            , UI_MESSAGE_XFSMSTATE_INI          ,
                UI_MESSAGE_XFSMEVENT_END            , UI_MESSAGE_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_MESSAGE_XFSMSTATE_INI            ,
                UI_MESSAGE_XFSMEVENT_NONE           , UI_MESSAGE_XFSMSTATE_NONE         ,
                UI_MESSAGE_XFSMEVENT_END            , UI_MESSAGE_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_MESSAGE_XFSMSTATE_END            ,
                UI_MESSAGE_XFSMEVENT_NONE           , UI_MESSAGE_XFSMSTATE_NONE         ,
                UI_MESSAGE_XFSMEVENT_INI            , UI_MESSAGE_XFSMSTATE_INI          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE::AppProc_Ini()
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

  SetEvent(UI_MESSAGE_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[UI_MESSAGE_BUTTON_UP]      = inpdevice->GetButton(INPBUTTON_ID_UP);
      button[UI_MESSAGE_BUTTON_DOWN]    = inpdevice->GetButton(INPBUTTON_ID_DOWN);
      button[UI_MESSAGE_BUTTON_LEFT]    = inpdevice->GetButton(INPBUTTON_ID_LEFT);
      button[UI_MESSAGE_BUTTON_RIGHT]   = inpdevice->GetButton(INPBUTTON_ID_RIGHT);
      button[UI_MESSAGE_BUTTON_SPACE]   = inpdevice->GetButton(INPBUTTON_ID_SPACE);
      button[UI_MESSAGE_BUTTON_ESC]     = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[UI_MESSAGE_BUTTON_F1]      = inpdevice->GetButton(INPBUTTON_ID_F1);
      button[UI_MESSAGE_BUTTON_F2]      = inpdevice->GetButton(INPBUTTON_ID_F2);
      button[UI_MESSAGE_BUTTON_F5]      = inpdevice->GetButton(INPBUTTON_ID_F5);
      button[UI_MESSAGE_BUTTON_F9]      = inpdevice->GetButton(INPBUTTON_ID_F9);
      button[UI_MESSAGE_BUTTON_MINUS]   = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_MINUS);
      button[UI_MESSAGE_BUTTON_PLUS]    = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_PLUS);

      button[UI_MESSAGE_BUTTON_MOUSE]   = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[UI_MESSAGE_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[UI_MESSAGE_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }

  //--------------------------------------------------------------------------------------

  if(!Ini_UserInterface(true)) 
    {
      return false;
    }

  //--------------------------------------------------------------------------------------
  
  xrand  = GEN_XFACTORY.CreateRand();
  if(!xrand)  
    {
      return false;
    }

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE::AppProc_Update()
{
  if(GetEvent()==UI_MESSAGE_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case UI_MESSAGE_XFSMSTATE_NONE      : break;

          case UI_MESSAGE_XFSMSTATE_INI       : UpdateInput();
                                                DrawFrame();
                                                GetMainScreen()->UpdateViewports();

                                                if(exitmessage)
                                                  {
                                                    SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                    exitmessage = false;
                                                  }

                                                break;

          case UI_MESSAGE_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<UI_MESSAGE_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case UI_MESSAGE_XFSMSTATE_NONE  : break;

              case UI_MESSAGE_XFSMSTATE_INI   : break;

              case UI_MESSAGE_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetCurrentState(UI_MESSAGE_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------
  
  Ini_UserInterface(false);

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
* @fn         bool UI_MESSAGE::UpdateInput()
* @brief      Updates the application input state.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE::UpdateInput()
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
                  GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE, cursor_x, cursor_y);
                }

              if(button[UI_MESSAGE_BUTTON_MOUSE]->IsPressedWithRelease())
                {
                  GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION, cursor_x, cursor_y);   

                  cursor->GetMotion()->Reset();       
                }
    
              if(button[UI_MESSAGE_BUTTON_TOUCHSCREEN])
                {             
                  if(button[UI_MESSAGE_BUTTON_TOUCHSCREEN]->IsPressed())
                    {             
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE, cursor_x, cursor_y);
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION, cursor_x, cursor_y);          

                      cursor->GetMotion()->Reset();
                    }
                }
            }
        }
    }


  for(int c=0; c<UI_MESSAGE_BUTTON_MOUSE; c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  
                  case UI_MESSAGE_BUTTON_F1       : break;
                  
                  case UI_MESSAGE_BUTTON_ESC      : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                    break;
                }
            }          
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE::Ini_Graphics(GRPSCREEN* screen)
* @brief      Initializes the graphics subsystem.
* @ingroup    EXAMPLES
*
* @param[in]  screen : Screen where the graphics or user interface resources are created.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE::Ini_Graphics(GRPSCREEN* screen)
{
  if(!screen)
    {
      return false;
    }
  
  screen->Style_Remove(GRPSCREENSTYLE_DEFAULT);  
  
  //screen->Style_Add(GRPSCREENSTYLE_FULLSCREEN);
  //screen->Style_Add(GRPSCREENSTYLE_FULLSCREEN_ADJUSTRESOLUTION);

  screen->Style_Add(GRPSCREENSTYLE_ONTOP);
  screen->Style_Add(GRPSCREENSTYLE_TRANSPARENT);
  screen->Style_Add(GRPSCREENSTYLE_NOWINDOWICONS);
  screen->Style_Add(GRPSCREENSTYLE_HEIGHTWITHOUTTASKBAR);
  screen->Style_Add(GRPSCREENSTYLE_NOICONTASKBAR);

  screen->GetTitle()->Set(__L("Hola radiola"));  

  screen->SetDesktopScreenSelected(GRPSCREENTYPE_DESKTOP_MAIN);

  screen->SetPosition(100, 100);
  screen->SetWidth(800);
  screen->SetHeight(600);
  
  /*
  bool status = screen->CreateViewport(APPLICATION_GUI_MESSAGE_VIEWPORT_ID  , 0.0f, 0.0f, (float)screen->GetWidth()   , (float)screen->GetHeight()
                                                                            ,    0,    0, screen->GetWidth()          , screen->GetHeight());   
  return status; 
  */
 
  return true;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE::Ini_Canvas(GRPSCREEN* screen)
* @brief      Initializes the canvas resources.
* @ingroup    EXAMPLES
*
* @param[in]  screen : Screen where the graphics or user interface resources are created.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE::Ini_Canvas(GRPSCREEN* screen)
{
  if(!screen)
    {
      return false;
    }
    
  bool status = screen->CreateViewport(APPLICATION_GUI_MESSAGE_VIEWPORT_ID, 0.0f, 0.0f, (float)screen->GetWidth(), (float)screen->GetHeight(), 0, 0, screen->GetWidth(), screen->GetHeight());   
  return status; 
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE::Ini_UserInterface(bool on)
* @brief      Initializes or ends the user interface.
* @ingroup    EXAMPLES
*
* @param[in]  on : true to enable the operation; false to disable it.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE::Ini_UserInterface(bool on)
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
  GRP2DCANVAS*    canvas    = NULL;
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
  xpath.Add(__L("message.zip"));
    

  if(!GEN_USERINTERFACE.Load(xpath, screen, 0)) 
    {
      return false;
    }

 
  GEN_USERINTERFACE.SubscribeInputEvents(true);
  GEN_USERINTERFACE.SubscribeOutputEvents(true, this, &GEN_USERINTERFACE.GetInstance());   
  
  GEN_USERINTERFACE.Elements_SetToRedraw();  

  if(screen->Style_Is(GRPSCREENSTYLE_TRANSPARENT))
    {
      canvas->Buffer_SetToZero();
    }                          
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE::DrawFrame()
* @brief      Draws the current frame.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE::DrawFrame()
{  
  GRPSCREEN*  screen = GetMainScreen();
  if(!screen) return false; 

  GRPVIEWPORT*  viewport  = NULL;
  GRP2DCANVAS*    canvas    = NULL;  
  bool          status    = false;

  if(screen)
    {
      viewport = screen->GetViewport(APPLICATION_GUI_MESSAGE_VIEWPORT_ID);
      if(viewport)
        {
          canvas = viewport->GetCanvas();
          if(canvas)
            {
              status  = true;
            }
        }      
    }

  if(!status)
    {
      return false;
    }
 
  canvas->ReleaseDrawFramerate();

  GEN_USERINTERFACE.Elements_RebuildDrawAreas(__L("message"));  
  GEN_USERINTERFACE.Update();

  canvas->DrawFramerate(screen, 10, 30);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE::UserInterface_ElementSelected(UI_ELEMENT* element)
* @brief      Processes the selected user interface element.
* @ingroup    EXAMPLES
*
* @param[in]  element : User interface element to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE::UserInterface_ElementSelected(UI_ELEMENT* element)
{
  if(!element) return false;

 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
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
bool UI_MESSAGE::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
{
  if(!element_text)   return false;
  if(!maskvalue)      return false;
  if(!maskresolved)   return false;

  if(!maskvalue->Compare(__L("TITLE"), true))
    {
      maskresolved->Set(__L("Esto es una prueba del titulo"));
    }

  if(!maskvalue->Compare(__L("MESSAGE"), true))
    {
      maskresolved->Set(__L("Este es un contenido para un ![COLOR red, 70]mensaje de prueba![END COLOR] y ver si se puede crear correctamente desde la configuracion"));      
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_MESSAGE::HandleEvent_UserInterface(UI_XEVENT* event)
* @brief      Handles user interface events.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_MESSAGE::HandleEvent_UserInterface(UI_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case  UI_XEVENT_TYPE_OUTPUT_SELECTED        : { UI_ELEMENT* element = event->GetElement();
                                                      if(element) 
                                                        {
                                                          if(!element->GetName()->Compare(__L("ok-btn"), true))
                                                            {                                                             
                                                              exitmessage = true;
                                                            }
                                                        }
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
* @fn         void UI_MESSAGE::HandleEvent_Graphics(GRPXEVENT* event)
* @brief      Handles graphics events.
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_MESSAGE::HandleEvent_Graphics(GRPXEVENT* event)
{
  switch(event->GetEventType())
    {
      case GRPXEVENT_TYPE_SCREEN_CREATING         : { GRPSCREEN* screen  = event->GetScreen();
                                                      if(!screen) break;
                                                
                                                      Ini_Graphics(screen);                                         
                                                    }
                                                    break;

      case GRPXEVENT_TYPE_SCREEN_CANVASCREATING   : { GRPSCREEN* screen  = event->GetScreen();
                                                      if(!screen) break;
                                                
                                                      Ini_Canvas(screen);                                         
                                                    }
                                                    break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_MESSAGE::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_MESSAGE::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_GRAPHICS                   : { GRPXEVENT* event = (GRPXEVENT*)xevent;
                                                      if(!event) return;

                                                      HandleEvent_Graphics(event);
                                                    }
                                                    break;

      case XEVENT_TYPE_USERINTERFACE              : { UI_XEVENT* event = (UI_XEVENT*)xevent;
                                                      if(!event) return;

                                                      HandleEvent_UserInterface(event);
                                                    }
                                                    break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_MESSAGE::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_MESSAGE::Clean()
{
  xtimer       = NULL;
  xrand        = NULL;

  for(int c=0; c<UI_MESSAGE_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }
  
  testbmp     = NULL;    

  exitmessage = false;
}



