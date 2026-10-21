/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Options.cpp
* 
* @class      UI_OPTIONS
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

#include "UI_Options.h"

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
#include "UI_Element_StatisticsChart.h"
#include "UI_Element_Form.h"
#include "UI_SkinCanvas.h"

#include "UI_CSSParser.h"
#include "UI_StyleSheet.h"


#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#include "UI_Options_CFG.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(UI_OPTIONS, canvas2d)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS::UI_OPTIONS()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_OPTIONS::UI_OPTIONS() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS::~UI_OPTIONS()
* @brief      Destructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_OPTIONS::~UI_OPTIONS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::InitFSMachine()
{
  if(!AddState( UI_OPTIONS_XFSMSTATE_NONE           ,
                UI_OPTIONS_XFSMEVENT_INI            , UI_OPTIONS_XFSMSTATE_INI          ,
                UI_OPTIONS_XFSMEVENT_END            , UI_OPTIONS_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_OPTIONS_XFSMSTATE_INI            ,
                UI_OPTIONS_XFSMEVENT_NONE           , UI_OPTIONS_XFSMSTATE_NONE         ,
                UI_OPTIONS_XFSMEVENT_END            , UI_OPTIONS_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_OPTIONS_XFSMSTATE_END            ,
                UI_OPTIONS_XFSMEVENT_NONE           , UI_OPTIONS_XFSMSTATE_NONE         ,
                UI_OPTIONS_XFSMEVENT_INI            , UI_OPTIONS_XFSMSTATE_INI          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::AppProc_Ini()
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

  SetEvent(UI_OPTIONS_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[UI_OPTIONS_BUTTON_UP]      = inpdevice->GetButton(INPBUTTON_ID_UP);
      button[UI_OPTIONS_BUTTON_DOWN]    = inpdevice->GetButton(INPBUTTON_ID_DOWN);
      button[UI_OPTIONS_BUTTON_LEFT]    = inpdevice->GetButton(INPBUTTON_ID_LEFT);
      button[UI_OPTIONS_BUTTON_RIGHT]   = inpdevice->GetButton(INPBUTTON_ID_RIGHT);
      button[UI_OPTIONS_BUTTON_SPACE]   = inpdevice->GetButton(INPBUTTON_ID_SPACE);
      button[UI_OPTIONS_BUTTON_ESC]     = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[UI_OPTIONS_BUTTON_F1]      = inpdevice->GetButton(INPBUTTON_ID_F1);
      button[UI_OPTIONS_BUTTON_F2]      = inpdevice->GetButton(INPBUTTON_ID_F2);
      button[UI_OPTIONS_BUTTON_F5]      = inpdevice->GetButton(INPBUTTON_ID_F5);
      button[UI_OPTIONS_BUTTON_F9]      = inpdevice->GetButton(INPBUTTON_ID_F9);
      button[UI_OPTIONS_BUTTON_MINUS]   = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_MINUS);
      button[UI_OPTIONS_BUTTON_PLUS]    = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_PLUS);

      button[UI_OPTIONS_BUTTON_MOUSE]   = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[UI_OPTIONS_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[UI_OPTIONS_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }

  //--------------------------------------------------------------------------------------

  if(!Ini_UserInterface(true)) return false;

  //--------------------------------------------------------------------------------------
  
  xrand  = GEN_XFACTORY.CreateRand();
  if(!xrand)  return false;

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::AppProc_Update()
{
  if(GetEvent()==UI_OPTIONS_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case UI_OPTIONS_XFSMSTATE_NONE      : break;

          case UI_OPTIONS_XFSMSTATE_INI       : UpdateInput();
                                                DrawFrame();
                                                GetMainScreen()->UpdateViewports();
                                                break;

          case UI_OPTIONS_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<UI_OPTIONS_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case UI_OPTIONS_XFSMSTATE_NONE  : break;

              case UI_OPTIONS_XFSMSTATE_INI   : break;

              case UI_OPTIONS_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetCurrentState(UI_OPTIONS_XFSMSTATE_END);

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
* @fn         bool UI_OPTIONS::UpdateInput()
* @brief      Updates the application input state.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::UpdateInput()
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

              if(button[UI_OPTIONS_BUTTON_MOUSE]->IsPressedWithRelease())
                {
                  GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION, cursor_x, cursor_y);   

                  cursor->GetMotion()->Reset();       
                }
    
              if(button[UI_OPTIONS_BUTTON_TOUCHSCREEN])
                {             
                  if(button[UI_OPTIONS_BUTTON_TOUCHSCREEN]->IsPressed())
                    {             
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE, cursor_x, cursor_y);
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION, cursor_x, cursor_y);          

                      cursor->GetMotion()->Reset();
                    }
                }
            }
        }
    }


  for(int c=0; c<UI_OPTIONS_BUTTON_MOUSE; c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  
                  case UI_OPTIONS_BUTTON_F1       : { UI_ELEMENT_PROGRESSBAR* element_progressbar = (UI_ELEMENT_PROGRESSBAR*)GEN_USERINTERFACE.Element_Get(NL("progressbar0"), UI_ELEMENT_TYPE_PROGRESSBAR);
                                                      if(element_progressbar) 
                                                        { 
                                                          float level = element_progressbar->GetLevel();
                                                          level++;
                                                          if(level > 100.0f) level = 100.0f;
                                                          element_progressbar->SetLevel(level);
                                                          GEN_USERINTERFACE.Elements_SetToRedraw(element_progressbar); 
                                                        }

                                                      UI_ELEMENT_PROGRESS_RADIAL* element_progressradial = (UI_ELEMENT_PROGRESS_RADIAL*)GEN_USERINTERFACE.Element_Get(NL("progressbar1"), UI_ELEMENT_TYPE_PROGRESSRADIAL);
                                                      if(element_progressradial) 
                                                        { 
                                                          float level = element_progressradial->GetLevel();
                                                          level++;
                                                          if(level > 100.0f) level = 100.0f;
                                                          element_progressradial->SetLevel(level);
                                                          GEN_USERINTERFACE.Elements_SetToRedraw(element_progressradial); 
                                                        }

                                                      UI_ELEMENT_PROGRESS_IMAGE* element_progressimage = (UI_ELEMENT_PROGRESS_IMAGE*)GEN_USERINTERFACE.Element_Get(NL("temp_bar"), UI_ELEMENT_TYPE_PROGRESSIMAGE);
                                                      if(element_progressimage) 
                                                        { 
                                                          float level = element_progressimage->GetLevel();
                                                          level++;
                                                          if(level > 100.0f) level = 100.0f;
                                                          element_progressimage->SetLevel(level);
                                                          GEN_USERINTERFACE.Elements_SetToRedraw(element_progressimage); 
                                                        }
                                                    }
                                                    break;

                  case UI_OPTIONS_BUTTON_F2       : { UI_ELEMENT_PROGRESSBAR* element_progressbar = (UI_ELEMENT_PROGRESSBAR*)GEN_USERINTERFACE.Element_Get(NL("progressbar0"), UI_ELEMENT_TYPE_PROGRESSBAR);
                                                      if(element_progressbar) 
                                                        { 
                                                          float level = element_progressbar->GetLevel();
                                                          level--;
                                                          if(level < 0.0f) level = 0.0f;
                                                          element_progressbar->SetLevel(level);
                                                          GEN_USERINTERFACE.Elements_SetToRedraw(element_progressbar); 
                                                        }

                                                      UI_ELEMENT_PROGRESS_RADIAL* element_progressradial = (UI_ELEMENT_PROGRESS_RADIAL*)GEN_USERINTERFACE.Element_Get(NL("progressbar1"), UI_ELEMENT_TYPE_PROGRESSRADIAL);
                                                      if(element_progressradial) 
                                                        { 
                                                          float level = element_progressradial->GetLevel();
                                                          level--;
                                                          if(level < 0.0f) level = 0.0f;
                                                          element_progressradial->SetLevel(level);
                                                          GEN_USERINTERFACE.Elements_SetToRedraw(element_progressradial); 
                                                        }

                                                      UI_ELEMENT_PROGRESS_IMAGE* element_progressimage = (UI_ELEMENT_PROGRESS_IMAGE*)GEN_USERINTERFACE.Element_Get(NL("temp_bar"), UI_ELEMENT_TYPE_PROGRESSIMAGE);
                                                      if(element_progressimage) 
                                                        { 
                                                          float level = element_progressimage->GetLevel();
                                                          level--;
                                                          if(level < 0.0f) level = 0.0f;
                                                          element_progressimage->SetLevel(level);
                                                          GEN_USERINTERFACE.Elements_SetToRedraw(element_progressimage); 
                                                        }
                                                    }
                                                    break;
                            
                  case UI_OPTIONS_BUTTON_F5       : Ini_UserInterface(false);
                                                    Ini_UserInterface(true);                      
                                                    break;

                  case UI_OPTIONS_BUTTON_F9       : { 
                                                      /*  
                                                      static bool on = false;

                                                      UI_ELEMENT_ANIMATION* element = (UI_ELEMENT_ANIMATION*)GEN_USERINTERFACE.GetElement(NL("image"), UI_ELEMENT_TYPE_ANIMATION);
                                                      if(element) element->SetVisible(on);      

                                                      on = !on;
                                                      */ 

                                                      // UnitTest_AVIVideoWrite();
                                                    }
                                                    break;

                  case UI_OPTIONS_BUTTON_ESC      : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                    break;
                }
            }

          if(button[c]->IsPressed())
            {
              switch(c)
                {
                  case UI_OPTIONS_BUTTON_UP     : 
                  case UI_OPTIONS_BUTTON_DOWN   : { UI_ELEMENT_MENU* element_menu = (UI_ELEMENT_MENU*)GEN_USERINTERFACE.Element_Get(NL("nav_menu"), UI_ELEMENT_TYPE_MENU);
                                                    if(element_menu) 
                                                      {                                                                                                                         
                                                        UI_PROPERTY_SCROLLEABLE* property_scrolleable = dynamic_cast<UI_PROPERTY_SCROLLEABLE*>(element_menu);
                                                        if(property_scrolleable) 
                                                          {
                                                            property_scrolleable->Scroll_SetStep(UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL, ((c==UI_OPTIONS_BUTTON_DOWN)?1:-1));   
                                                            GEN_USERINTERFACE.Elements_SetToRedraw(element_menu);                                                                                                                 
                                                          }
                                                      }
                                                  }
                                                  break;    

                  case UI_OPTIONS_BUTTON_LEFT   : makeaction = NL("WALK WEST" );   break;
                  case UI_OPTIONS_BUTTON_RIGHT  : makeaction = NL("WALK EAST" );   break;
                  case UI_OPTIONS_BUTTON_SPACE  : break;
                  
                }
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::Ini_Graphics(GRPSCREEN* screen)
* @brief      Initializes the graphics subsystem.
* @ingroup    EXAMPLES
*
* @param[in]  screen : Screen where the graphics or user interface resources are created.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::Ini_Graphics(GRPSCREEN* screen)
{

  //--------------------------------------------------------------------------------------

  screen->SetWidth(1024);
  screen->SetHeight(576);

  //screen->Styles_Set(GRPSCREENSTYLE_TRANSPARENT);
  //screen->Styles_Set(GRPSCREENSTYLE_FULLSCREEN);
  
  screen->GetTitle()->Set(NL("User Interface Canvas"));  
  screen->SetDesktopScreenSelected(GRPSCREENTYPE_DESKTOP_MAIN);

  //--------------------------------------------------------------------------------------

  UserInterface_CFGChromes(screen); 

  //--------------------------------------------------------------------------------------

  GetMainScreen()->CreateViewport(GRPVIEWPORT_ID_MAIN, 0.0f, 0.0f, (float)screen->GetWidth(), (float)screen->GetHeight(), 0, 0, (screen->GetWidth()), (screen->GetHeight()));

  //--------------------------------------------------------------------------------------

  
  XPATH pathvf;
 
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, pathvf);
  pathvf.Slash_Add();

  //pathvf.Add(NL("test_render.svg"));                 
  //pathvf.Add(NL("tiger.svg"));
  //pathvf.Add(NL("test_use.svg"));
  //pathvf.Add(NL("test_gradient.svg"));
  //pathvf.Add(NL("test_text.svg"));
  //pathvf.Add(NL("test_block1.svg"));
  //pathvf.Add(NL("test_stroke.svg"));
  //pathvf.Add(NL("thermometer.svg"));
  //pathvf.Add(NL("icon_close_activated.svg"));
 
  //pathvf.Add(NL("cube.dxf"));  
  //pathvf.Add(NL("bridge.dxf"));
  //pathvf.Add(NL("compass.dxf"));
  //pathvf.Add(NL("harley-davidson.dxf"));
  //pathvf.Add(NL("plate_120x80.dxf"));
  //pathvf.Add(NL("plate_120x80_mtext_test.dxf"));

  //--------------------------------------------------------------------------------------

  /*
  vectorfile = GRPVECTORFILE::CreateInstance(pathvf);
  if(vectorfile)
    {
      vectorfile->Load();      
    }
  */
   
  //-----------------------------------------------------------------------
  /*
  vectorfile = GRPVECTORFILE::CreateInstance(GRPVECTORFILETYPE_SVG);
  if(vectorfile)
    {
      XFILETXT* file = new XFILETXT();
      if(file) 
        {
          if(file->Open(pathvf))
            {
              XSTRING content;

              file->ReadAllFile();

              file->GetAllInOneLine(content);

              vectorfile->Load(content);

              file->Close();            
            }
          }
    }
  */
  //--------------------------------------------------------------------------------------

                                          
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::Ini_UserInterface(bool on)
* @brief      Initializes or ends the user interface.
* @ingroup    EXAMPLES
*
* @param[in]  on : true to enable the operation; false to disable it.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::Ini_UserInterface(bool on)
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
  xpath.Add(NL("example/example.xml"));
    
  if(!GEN_USERINTERFACE.Load(xpath, screen, 0)) 
    {
      return false;
    }

  GEN_USERINTERFACE.SubscribeInputEvents(true);
  GEN_USERINTERFACE.SubscribeOutputEvents(true, this, &GEN_USERINTERFACE.GetInstance());   


  GEN_USERINTERFACE.CreaterVirtualKeyboard(GEN_USERINTERFACE.Layouts_Get(NL("example")), screen);   

  GEN_USERINTERFACE.Layout_PutBackground();

  GEN_USERINTERFACE.Elements_SetToRedraw();

  // Nav / galleries: exclusive gray highlight (no red select ring — that left ghost underlines).
  {
    XCHAR* nav_rows[] = { NL("nav_1"), NL("nav_2"), NL("nav_3"), NL("nav_4"), NL("nav_5"), NL("nav_6") };
    UI_ELEMENT* nav_sel = GEN_USERINTERFACE.Element_Get(NL("nav_3"), UI_ELEMENT_TYPE_BUTTON);
    UserInterface_SelectExclusiveRow(nav_rows, 6, nav_sel, NULL);

    XCHAR* gal_rows[] = { NL("gal_1"), NL("gal_2"), NL("gal_3"), NL("gal_4"), NL("gal_5") };
    UI_ELEMENT* gal_sel = GEN_USERINTERFACE.Element_Get(NL("gal_1"), UI_ELEMENT_TYPE_BUTTON);
    UserInterface_SelectExclusiveRow(gal_rows, 5, gal_sel, NULL);
  }

  // --- RIGHT: recent activity chart (slate) -----------------------------------------------------
  UI_ELEMENT_STATISTICSCHART* demo_chart = (UI_ELEMENT_STATISTICSCHART*)GEN_USERINTERFACE.Element_Get(NL("demo_chart"), UI_ELEMENT_TYPE_STATISTICSCHART);
  if(demo_chart)
    {
      float samples[] = { 28.0f, 42.0f, 35.0f, 58.0f, 50.0f, 72.0f, 64.0f, 80.0f, 55.0f, 68.0f };
      demo_chart->SetChartType(UI_ELEMENT_STATISTICSCHART_TYPE_LINES);
      demo_chart->SetTitle(NL(""));
      demo_chart->SetSerieFromSamples(NL("Actividad"), samples, (int)(sizeof(samples)/sizeof(samples[0])), 96, 125, 139);
      demo_chart->SetNeedsRebuild(true);
      GEN_USERINTERFACE.Elements_SetToRedraw(demo_chart);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::DrawFrame()
* @brief      Draws the current frame.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::DrawFrame()
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

  // Minimized / WM_SIZE recreate leaves a 1x1 (or empty) buffer — skip the frame so ReleaseDrawFramerate
  // and UI paint do not run against a half-rebuilt AGG canvas (raster glyph m_font was NULL → AV).
  if((width < 32) || (height < 32))
    {
      return true;
    }

  canvas->ReleaseDrawFramerate();  
 
  canvas->RebuildAllAreas();

  //--------------------------------------------------------------------------------------

  
  // Keep framerate off the footer chrome / button strip (was overlapping the frame edge).
  canvas->DrawFramerate(screen, (double)(screen->GetWidth() - 88), 14.0);

  //--------------------------------------------------------------------------------------

  GEN_USERINTERFACE.Elements_RebuildDrawAreas();
  
  GEN_USERINTERFACE.Update(); 

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::UserInterface_SelectExclusiveRow(XCHAR** rownames, XDWORD nrows, UI_ELEMENT* selected, XCHAR* chevronname)
* @brief      One gray highlight among sibling list buttons. Optional chevronname unused (kept for call sites).
* @ingroup    EXAMPLES
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::UserInterface_SelectExclusiveRow(XCHAR** rownames, XDWORD nrows, UI_ELEMENT* selected, XCHAR* chevronname)
{
  if(!rownames || !nrows) return false;

  (void)chevronname;

  static XCHAR* nav_labels[] = { NL("1. Inicio"), NL("2. Nuevo Galeria"), NL("3. Abrir Galeria"), NL("4. Editar Galeria"), NL("5. Exportar XML"), NL("6. Configuracion") };

  bool anychanged = false;
  UI_ELEMENT* listfather = NULL;

  for(XDWORD i = 0; i < nrows; i++)
    {
      UI_ELEMENT_BUTTON* row = (UI_ELEMENT_BUTTON*)GEN_USERINTERFACE.Element_Get(rownames[i], UI_ELEMENT_TYPE_BUTTON);
      if(!row) continue;

      if(!listfather) listfather = row->GetFather();

      bool on = ((UI_ELEMENT*)row == selected);
      // Prior selection wash (opaque light blue). Used so we only dirty when highlight actually flips.
      // 220,236,250 ≈ prior 220,228,232 lightened ~25% and tinted azul claro (no red select ring).
      bool was_on = (row->GetBackgroundColor()->GetAlpha() == 255) &&
                    (row->GetBackgroundColor()->GetRed()   == 220) &&
                    (row->GetBackgroundColor()->GetGreen() == 236) &&
                    (row->GetBackgroundColor()->GetBlue()  == 250);
      bool changed = (on != was_on);

      if(on)
        {
          // Selection wash (opaque light blue).
          row->GetBackgroundColor()->SetFromString(NL("220,236,250,255"));
          // Keep framework select latch off so Draw_Option does not paint the default red ring.
          row->SetSelected(false);
        }
       else
        {
          // Opaque white so DrawBackgroundColor / option erase clears prior selection + glyph ink.
          // (Alpha 0 left old gray/text stacked on hover redraws.)
          row->GetBackgroundColor()->SetFromString(NL("255,255,255,255"));
          row->SetSelected(false);
        }

      // Nav rows: mark selection with trailing '>' in the label (avoids orphan chevron animation).
      if((nrows == 6) && (i < 6) && row->Get_UIText())
        {
          XSTRING label = nav_labels[i];
          if(on) label.Add(NL("   >"));

          UI_ELEMENT_TEXT* tx = row->Get_UIText();
          if(tx->GetText()->Compare(label.Get(), true))
            {
              UI_LAYOUT* layout = row->GetLayout();
              if(layout && layout->GetSkin() && (layout->GetSkin()->GetDrawMode() == UI_SKIN_DRAWMODE_CANVAS))
                {
                  ((UI_SKINCANVAS*)layout->GetSkin())->PrepareTextContentChange(tx);
                }
              tx->GetText()->Set(label.Get());
              changed = true;
            }
        }

      // Discard TEXT/ANIM backdrops without restore so the new wash is re-captured (avoids white punch
      // into gray on filenames AND icons). Nav rows may be compose children of frame_nav — dirty the
      // father form so Draw_Form repaints them. Gallery rows are layout-root siblings — dirty each row.
      if(changed)
        {
          anychanged = true;
          UI_LAYOUT* layout = row->GetLayout();
          if(layout && layout->GetSkin() && (layout->GetSkin()->GetDrawMode() == UI_SKIN_DRAWMODE_CANVAS))
            {
              UI_SKINCANVAS* skin = (UI_SKINCANVAS*)layout->GetSkin();
              for(XDWORD c=0; c<row->GetComposeElements()->GetSize(); c++)
                {
                  UI_ELEMENT* sub = row->GetComposeElements()->Get(c);
                  if(!sub) continue;
                  if(sub->GetType() == UI_ELEMENT_TYPE_TEXT)      skin->DiscardTextBackdrop(sub);
                  if(sub->GetType() == UI_ELEMENT_TYPE_ANIMATION) skin->DiscardAnimBackdrop(sub);
                }
            }

          if(!row->GetFather()) GEN_USERINTERFACE.Elements_SetToRedraw(row, true);
        }
    }

  if(anychanged && listfather) GEN_USERINTERFACE.Elements_SetToRedraw(listfather, true);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::UserInterface_ElementSelected(UI_ELEMENT* element)
* @brief      Processes the selected user interface element.
* @ingroup    EXAMPLES
*
* @param[in]  element : User interface element to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::UserInterface_ElementSelected(UI_ELEMENT* element)
{
  if(!element) return false;


  switch(element->GetChromeRole())
    {
      case UI_ELEMENT_CHROMEROLE_ICON     : break;

      case UI_ELEMENT_CHROMEROLE_MINIMIZE : if(GetMainScreen()) GetMainScreen()->Minimize(true);
                                            break;

      case UI_ELEMENT_CHROMEROLE_LANGUAGE :
                                            #ifdef XTRANSLATION_ACTIVE
                                            if(GEN_XTRANSLATION.IsInitialized() && GEN_XTRANSLATION.SetActual_Next())
                                              {
                                                // Layouts_ApplyTranslations restores rebuild/composition caches
                                                // (no full Layout_PutBackground — that wiped ListBoxMenu/edit under
                                                // chrome auto-hide) then re-resolves #[TRANSLATE_N].
                                                GEN_USERINTERFACE.Layouts_ApplyTranslations();
                                                #ifdef APPFLOW_CFG_GENERAL_ACTIVE
                                                APPFLOW_CFG.Language_PersistActual();
                                                #endif
                                              }
                                            #endif
                                            break;

      case UI_ELEMENT_CHROMEROLE_MAXIMIZE : if(GetMainScreen()) GetMainScreen()->Maximize(true);
                                            break;

      case UI_ELEMENT_CHROMEROLE_CLOSE    : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                            break;

      default                             : break;
    }




  XSTRING elementname;

  elementname = element->GetName()->Get();

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, NL("UI Element [%s]: Selected! "), element->GetName()->Get());

  // Left menus: exclusive gray row (standalone buttons do not clear siblings).
  if(elementname.Find(NL("nav_"), true) == 0)
    {
      XCHAR* nav_rows[] = { NL("nav_1"), NL("nav_2"), NL("nav_3"), NL("nav_4"), NL("nav_5"), NL("nav_6") };
      UserInterface_SelectExclusiveRow(nav_rows, 6, element, NULL);
    }

  if(elementname.Find(NL("gal_"), true) == 0)
    {
      XCHAR* gal_rows[] = { NL("gal_1"), NL("gal_2"), NL("gal_3"), NL("gal_4"), NL("gal_5") };
      UserInterface_SelectExclusiveRow(gal_rows, 5, element, NULL);
    }

  if(!elementname.Compare(NL("chk_enabled"), true))
    {
      UI_ELEMENT* hint = GEN_USERINTERFACE.Element_Get(NL("hint_text"), UI_ELEMENT_TYPE_TEXT);
      if(hint)
        {
          hint->SetVisible(!hint->IsVisible());
          GEN_USERINTERFACE.Elements_SetToRedraw(hint);
        }
    }

  if(!elementname.Compare(NL("btn_nuevo"), true)   ||
     !elementname.Compare(NL("btn_guardar"), true) ||
     !elementname.Compare(NL("btn_ejecutar"), true)||
     !elementname.Compare(NL("btn_exportar"), true))
    {
      UI_ELEMENT_TEXT* status = (UI_ELEMENT_TEXT*)GEN_USERINTERFACE.Element_Get(NL("status_text"), UI_ELEMENT_TYPE_TEXT);
      if(status)
        {
          // Force live STATUS mask refresh on next ChangeTextElementValue tick via makeaction tag.
          makeaction = elementname;
        }
    }

  // Footer "Cerrar" — quit the application (click may select the button or a child ic/tx).
  {
    UI_ELEMENT* walk = element;
    while(walk)
      {
        if(walk->GetName() && !walk->GetName()->Compare(NL("btn_cerrar"), true))
          {
            SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
            break;
          }
        walk = walk->GetFather();
      }
  }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
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
bool UI_OPTIONS::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
{
  if(!element_text)   return false;
  if(!maskvalue)      return false;
  if(!maskresolved)   return false;

  if(!maskvalue->Compare(NL("VERSION"), true))
    {
      maskresolved->Format(NL("%d.%d.%d"), APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
      if(APPLICATION_VERSION < 1) maskresolved->AddFormat(NL(" Beta"));
    }

  if(!maskvalue->Compare(NL("STATUS"), true))
    {
      if(!makeaction.IsEmpty())
        {
          maskresolved->Format(NL("%s"), makeaction.Get());
        }
       else
        {
          maskresolved->Set(NL("LISTO"));
        }
    }

  if(!maskvalue->Compare(NL("USER"), true))
    {
      maskresolved->Set(NL("Usuario: Tecnico · Perfil: Editor"));
    }

  if(!maskvalue->Compare(NL("TEST_TAG"), true))
    {
      maskresolved->Set(NL("masks"));
    }

  if(!maskvalue->Compare(NL("TEST_COUNTER"), true))
    {
      static int counter = 0;
      maskresolved->Format(NL("%d"), counter);
      counter++;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_OPTIONS::UserInterface_CFGChromes(GRPSCREEN* screen)
* @brief      user interface  CFGchromes
* @ingroup    
* 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::UserInterface_CFGChromes(GRPSCREEN* screen)
{
  GRPSCREENCFGCHROMES cfgchromes;

  #ifdef GRP_SCREEN_CUSTOMCHROMES_ACTIVE

  // defaultwindowschromes.zip: invisible caption strip (no icons) for drag only.
  // Keep auto-hide off so the transparent band stays hit-testable.
  cfgchromes.SetCustomAutoHide(0);

  #else

  cfgchromes.SetNativeCaptionActive(true);
  cfgchromes.SetNativeIconActive(false);
  cfgchromes.SetNativeTitleActive(false); 
  cfgchromes.SetNativeMinimizeActive(false);
  cfgchromes.SetNativeMaximizeActive(false);
  cfgchromes.SetNativeCloseActive(true);  

  #endif

  // Fixed-size demo window — no thick frame / user resize.
  cfgchromes.SetResizeActive(false);

  screen->SetCFGChromes(cfgchromes);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::UnitTest_AVIVideoWrite()
* @brief      Runs the AVI video write unit test.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::UnitTest_AVIVideoWrite()
{  
  // -------------------------------------------------------------------------------
  // Write AVI 

  XPATH               xpath;
  XVECTOR<XBUFFER*>   dataimgs;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
  xpath.Slash_Add();
  
  XFILE* fileimg = GEN_XFACTORY.Create_File();
  if(fileimg)  
    {
      XPATH xpath_img;  
      XPATH name_img;  

      for(int c=1; c<150; c++)  
        {
          XBUFFER*  dataimg = NULL;
          dataimg = GEN_NEW XBUFFER();
          if(dataimg)
            {
              xpath_img = xpath;

              name_img.Format(NL("frames/ezgif-frame-%03d.jpg"), c);
              xpath_img += name_img;

              if(fileimg->Open(xpath_img))
                { 
                  dataimg->Resize((XDWORD)fileimg->GetSize());

                  fileimg->Read(dataimg->Get(), dataimg->GetSize());

                  fileimg->Close();

                  dataimgs.Add(dataimg);        
                } 
               else 
                { 
                  delete dataimg;
                  break;  
                }         
     
             } 
            else 
             {  
                break;
             }
         }
                                                              
       GEN_XFACTORY.Delete_File(fileimg);      
    }

  GRPVIDEOFILEAVI* xfileAVI;
                                                      
  xfileAVI = GEN_NEW GRPVIDEOFILEAVI();
  if(!xfileAVI) return false;                                         
                     
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
  xpath.Slash_Add();
  xpath.Add(NL("prueba.avi"));

  GRPVIDEOFILE_PROPERTYS propertys;

  propertys.width     = 480;
  propertys.height    = 480;
  propertys.codecstr  = NL("MJPG");

  if(xfileAVI->Create(xpath.Get(), propertys))
    {      
      for(int c=0; c<dataimgs.GetSize(); c++)
        {         
          xfileAVI->AddFrame(dataimgs.Get(c)->Get(), dataimgs.Get(c)->GetSize());  
        }

      xfileAVI->Close();
    }

  delete xfileAVI;                                                      

  dataimgs.DeleteContents();
  dataimgs.DeleteAll();  
     
  /*              
  // -------------------------------------------------------------------------------
  // Read AVI 
                                                                                                                                               
  xfileAVI = GEN_NEW GRPVIDEOFILEAVI();
  if(!xfileAVI) return false;

  if(xfileAVI->Open(xpath.Get()))
    {           
      GRPBITMAPFILEJPG  jpg;

      for(int c=0; c<xfileAVI->GetPropertys()->nframes; c++)           
        {
          XDWORD sizeframe  = 0;
          XBYTE* data       = xfileAVI->GetDataFrame(c, sizeframe); 

          GRPBITMAP* bitmap = jpg.CreateBitmapFromBuffer(data, sizeframe, GetMainScreen()->GetMode());
          if(bitmap) 
            {
              GRPSCREEN*   screen   = NULL;
              GRPVIEWPORT* viewport = NULL;
              GRP2DCANVAS*   canvas   = NULL;  

              screen   = GetMainScreen();
              if(!screen) return false;

              viewport = screen->GetViewport(0);
              if(viewport) canvas = viewport->GetCanvas();
              if(!canvas) return false;
  
              canvas->PutBitmap(10,300, bitmap);      

              delete bitmap;       
            } 

          GEN_DELETE_ARRAY data;
        }
                                                              
      xfileAVI->Close();
    }

  delete xfileAVI;
  */
                                                      
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_OPTIONS::HandleEvent_UserInterface(UI_XEVENT* event)
* @brief      Handles user interface events.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_OPTIONS::HandleEvent_UserInterface(UI_XEVENT* event)
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

      case UI_XEVENT_TYPE_OUTPUT_CHANGECONTENTS   : { int a=0;
                                                      a++;

                                                    }
                                                    break;
      
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_OPTIONS::HandleEvent_Graphics(GRPXEVENT* event)
* @brief      Handles graphics events.
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_OPTIONS::HandleEvent_Graphics(GRPXEVENT* event)
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
* @fn         void UI_OPTIONS::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_OPTIONS::HandleEvent(XEVENT* xevent)
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
* @fn         void UI_OPTIONS::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_OPTIONS::Clean()
{
  xtimer       = NULL;
  xrand        = NULL;

  for(int c=0; c<UI_OPTIONS_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }
  
  testbmp     = NULL;    

  vectorfile  = NULL;  
}