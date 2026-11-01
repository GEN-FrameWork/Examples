/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UI_Console.cpp
*
* @class      UI_CONSOLE
* @brief      Graphics UI Console Example class
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

#include "UI_Console.h"

#include "VersionFrameWork.h"

#include "XPath.h"
#include "XTimer.h"
#include "XFactory.h"
#include "XString.h"
#include "XSystem.h"
#include "XLog.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XTrace.h"
#include "XFSMachine.h"

#include "GRP2DCanvas.h"
#include "GRPScreen.h"
#include "GRPViewPort.h"
#include "GRPXEvent.h"

#include "INPManager.h"

#include "UI_XEvent.h"
#include "UI_Manager.h"
#include "UI_Layout.h"
#include "UI_Element.h"
#include "UI_Element_Text.h"
#include "UI_Element_Console.h"
#include "UI_Element_CheckBox.h"
#include "UI_Color.h"

#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#include "UI_Console_CFG.h"
#include "UI_Console_TranslateID.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(UI_CONSOLE, ui_console)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_CONSOLE::UI_CONSOLE()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_CONSOLE::UI_CONSOLE() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_CONSOLE::~UI_CONSOLE()
* @brief      Destructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_CONSOLE::~UI_CONSOLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::InitFSMachine()
{
  if(!AddState( UI_CONSOLE_XFSMSTATE_NONE           ,
                UI_CONSOLE_XFSMEVENT_INI            , UI_CONSOLE_XFSMSTATE_INI          ,
                UI_CONSOLE_XFSMEVENT_END            , UI_CONSOLE_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_CONSOLE_XFSMSTATE_INI            ,
                UI_CONSOLE_XFSMEVENT_NONE           , UI_CONSOLE_XFSMSTATE_NONE         ,
                UI_CONSOLE_XFSMEVENT_END            , UI_CONSOLE_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_CONSOLE_XFSMSTATE_END            ,
                UI_CONSOLE_XFSMEVENT_NONE           , UI_CONSOLE_XFSMSTATE_NONE         ,
                UI_CONSOLE_XFSMEVENT_INI            , UI_CONSOLE_XFSMSTATE_INI          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::AppProc_Ini()
{
  XSTRING string;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  Application_GetName()->Set(APPLICATION_NAMEAPP);

  SetInitOptions(APPFLOWGRAPHICS_INIOPTION_CREATEMAINSCREEN | APPFLOWGRAPHICS_INIOPTION_SHOWMAINSCREEN | APPFLOWGRAPHICS_INIOPTION_INPUT);

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
  }

  //--------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG);

  //--------------------------------------------------------------------------------------

  SetEvent(UI_CONSOLE_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[UI_CONSOLE_BUTTON_ESC]   = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[UI_CONSOLE_BUTTON_A]     = inpdevice->GetButton(INPBUTTON_ID_A);
      button[UI_CONSOLE_BUTTON_C]     = inpdevice->GetButton(INPBUTTON_ID_C);
      button[UI_CONSOLE_BUTTON_CTRL]  = inpdevice->GetButton(INPBUTTON_ID_CONTROL_LEFT);
      button[UI_CONSOLE_BUTTON_SHIFT] = inpdevice->GetButton(INPBUTTON_ID_SHIFT_LEFT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[UI_CONSOLE_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {
      button[UI_CONSOLE_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);
      cursor = inpdevice->GetCursor(0);
    }

  //--------------------------------------------------------------------------------------

  if(!Ini_UserInterface(true))
    {
      return false;
    }

  //--------------------------------------------------------------------------------------

  if(xtimer) xtimer->Reset();
  demoline_lastms = 0;

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::AppProc_Update()
{
  if(GetEvent()==UI_CONSOLE_XFSMEVENT_NONE)
    {
      switch(GetCurrentState())
        {
          case UI_CONSOLE_XFSMSTATE_NONE      : break;

          case UI_CONSOLE_XFSMSTATE_INI       : UpdateInput();
                                                UpdateConsoleDemo();
                                                DrawFrame();
                                                GetMainScreen()->UpdateViewports();

                                                if(exitconsole)
                                                  {
                                                    SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                    exitconsole = false;
                                                  }

                                                break;

          case UI_CONSOLE_XFSMSTATE_END       : break;

        }
    }
   else
    {
      if(GetEvent()<UI_CONSOLE_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case UI_CONSOLE_XFSMSTATE_NONE  : break;

              case UI_CONSOLE_XFSMSTATE_INI   : break;

              case UI_CONSOLE_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::AppProc_End()
{
  //--------------------------------------------------------------------------------------

  SetCurrentState(UI_CONSOLE_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------

  Ini_UserInterface(false);

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
* @fn         bool UI_CONSOLE::UpdateInput()
* @brief      Updates the application input state.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::UpdateInput()
{
  int height = GetMainScreen()->GetHeight();

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

              bool shiftdown = (button[UI_CONSOLE_BUTTON_SHIFT] && button[UI_CONSOLE_BUTTON_SHIFT]->IsPressed());
              bool mouseheld = (button[UI_CONSOLE_BUTTON_MOUSE] && button[UI_CONSOLE_BUTTON_MOUSE]->IsPressed());

              // Shift+drag (or Shift held while moving with button down) extends line selection.
              if(mouseheld && shiftdown)
                {
                  Console_HandleSelection(cursor_x, cursor_y, true, selection_dragging);
                  selection_dragging = true;
                }
               else if(!mouseheld)
                {
                  selection_dragging = false;
                }

              if(button[UI_CONSOLE_BUTTON_MOUSE] && button[UI_CONSOLE_BUTTON_MOUSE]->IsPressedWithRelease())
                {
                  GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION, cursor_x, cursor_y);

                  // Plain click on console selects one line; Shift+click extends.
                  Console_HandleSelection(cursor_x, cursor_y, shiftdown, false);

                  cursor->GetMotion()->Reset();
                }

              if(button[UI_CONSOLE_BUTTON_TOUCHSCREEN])
                {
                  if(button[UI_CONSOLE_BUTTON_TOUCHSCREEN]->IsPressed())
                    {
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE, cursor_x, cursor_y);
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION, cursor_x, cursor_y);

                      cursor->GetMotion()->Reset();
                    }
                }
            }
        }
    }

  if(button[UI_CONSOLE_BUTTON_ESC])
    {
      if(button[UI_CONSOLE_BUTTON_ESC]->IsPressedWithRelease())
        {
          SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
        }
    }

  bool ctrl_down = (button[UI_CONSOLE_BUTTON_CTRL] && button[UI_CONSOLE_BUTTON_CTRL]->IsPressed());

  // A = toggle Autoscroll; Ctrl+A = select all (same key, resolve chord first).
  if(button[UI_CONSOLE_BUTTON_A] && button[UI_CONSOLE_BUTTON_A]->IsPressedWithRelease())
    {
      if(ctrl_down && consoleelement)
        {
          consoleelement->Selection_SelectAll();
          consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_GRAY, NL("Selection: all lines. (Ctrl+A)"));
        }
       else if(consoleelement)
        {
          bool on = !consoleelement->GetAutoscroll();
          consoleelement->SetAutoscroll(on);
          if(on) consoleelement->Scroll_SetFraction(UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL, 1.0f);

          UI_ELEMENT_CHECKBOX* checkbox = (UI_ELEMENT_CHECKBOX*)GEN_USERINTERFACE.Element_Get(NL("autoscroll-chk"), UI_ELEMENT_TYPE_CHECKBOX);
          if(checkbox)
            {
              checkbox->SetStatus(on);
              GEN_USERINTERFACE.Elements_SetToRedraw(checkbox);
            }

          consoleelement->PrintColorf(UI_ELEMENT_CONSOLE_COLOR_GRAY, NL("Autoscroll %s. (key A)"), on ? NL("ON") : NL("OFF"));
          consoleelement->SetMustReDraw(true);
        }
    }

  // Ctrl+C = copy selection (or whole buffer if none).
  if(ctrl_down && button[UI_CONSOLE_BUTTON_C] && button[UI_CONSOLE_BUTTON_C]->IsPressedWithRelease())
    {
      Console_CopySelection();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::UpdateConsoleDemo()
* @brief      Appends periodic demo lines to the graphical console.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::UpdateConsoleDemo()
{
  if(!consoleelement) return false;
  if(!xtimer)         return false;

  // Keep console flag in lockstep with the checkbox (avoids UI/state desync if a click
  // redraws the glyph without delivering OUTPUT_SELECTED to the app).
  UI_ELEMENT_CHECKBOX* checkbox = (UI_ELEMENT_CHECKBOX*)GEN_USERINTERFACE.Element_Get(NL("autoscroll-chk"), UI_ELEMENT_TYPE_CHECKBOX);
  if(checkbox)
    {
      bool on = checkbox->GetStatus();
      if(consoleelement->GetAutoscroll() != on)
        {
          consoleelement->SetAutoscroll(on);
          if(on) consoleelement->Scroll_SetFraction(UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL, 1.0f);
        }
    }

  XQWORD now = xtimer->GetMeasureMilliSeconds();
  if(demoline_lastms == 0)
    {
      demoline_lastms = now;
      return true;
    }

  XQWORD elapsed = now - demoline_lastms;
  if(elapsed == 0) return true;

  // Emit as many lines as the target rate allows for this frame (burst under load).
  XDWORD nlines = (XDWORD)((elapsed * (XQWORD)UI_CONSOLE_DEMO_LINES_PER_SEC) / 1000ULL);
  if(nlines < 1) return true;

  demoline_lastms = now;

  for(XDWORD i=0; i<nlines; i++)
    {
      demolinecounter++;

      XBYTE colorindex = (XBYTE)(UI_ELEMENT_CONSOLE_COLOR_BLUE + ((demolinecounter - 1) % 5));
      consoleelement->PrintColorf(colorindex, NL("[%04d] demo flood  t=%d ms  (+%d/frame)"), demolinecounter, (int)now, (int)nlines);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::Ini_Graphics(GRPSCREEN* screen)
* @brief      Initializes the graphics subsystem.
* @ingroup    EXAMPLES
*
* @param[in]  screen : Screen where the graphics or user interface resources are created.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::Ini_Graphics(GRPSCREEN* screen)
{
  if(!screen)
    {
      return false;
    }

  screen->Style_Remove(GRPSCREENSTYLE_DEFAULT);

  screen->GetTitle()->Set(TL(UI_CONSOLE_TRANSLATEID_UI_CONSOLE_WINDOW_TITLE));

  screen->SetDesktopScreenSelected(GRPSCREENTYPE_DESKTOP_MAIN);

  screen->SetPosition(100, 100);
  screen->SetWidth(900);
  screen->SetHeight(600);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::Ini_Canvas(GRPSCREEN* screen)
* @brief      Initializes the canvas resources.
* @ingroup    EXAMPLES
*
* @param[in]  screen : Screen where the graphics or user interface resources are created.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::Ini_Canvas(GRPSCREEN* screen)
{
  if(!screen)
    {
      return false;
    }

  bool status = screen->CreateViewport(APPLICATION_GUI_CONSOLE_VIEWPORT_ID, 0.0f, 0.0f, (float)screen->GetWidth(), (float)screen->GetHeight(), 0, 0, screen->GetWidth(), screen->GetHeight());
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::Ini_UserInterface(bool on)
* @brief      Initializes or ends the user interface.
* @ingroup    EXAMPLES
*
* @param[in]  on : true to enable the operation; false to disable it.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::Ini_UserInterface(bool on)
{
  if(!on)
    {
      consoleelement = NULL;

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
  xpath.Add(NL("console/console.xml"));

  if(!GEN_USERINTERFACE.Load(xpath, screen, 0))
    {
      return false;
    }

  GEN_USERINTERFACE.SubscribeInputEvents(true);
  GEN_USERINTERFACE.SubscribeOutputEvents(true, this, &GEN_USERINTERFACE.GetInstance());

  GEN_USERINTERFACE.Layout_PutBackground();
  GEN_USERINTERFACE.Elements_SetToRedraw();

  if(!Console_Resolve())
    {
      return false;
    }

  if(!Console_SeedDemoLines())
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::DrawFrame()
* @brief      Draws the current frame.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::DrawFrame()
{
  GRPSCREEN* screen = GetMainScreen();
  if(!screen) return false;

  GRPVIEWPORT* viewport = NULL;
  GRP2DCANVAS* canvas   = NULL;
  bool         status   = false;

  viewport = screen->GetViewport(APPLICATION_GUI_CONSOLE_VIEWPORT_ID);
  if(viewport)
    {
      canvas = viewport->GetCanvas();
      if(canvas)
        {
          status = true;
        }
    }

  if(!status)
    {
      return false;
    }

  if((screen->GetWidth() < 32) || (screen->GetHeight() < 32))
    {
      return true;
    }

  canvas->ReleaseDrawFramerate();

  // Console paints an opaque backdrop when dirty (AddLine/Clear/scroll). Do not force a
  // full rebuild every frame — that remeasured the whole buffer and collapsed FPS under flood.

  GEN_USERINTERFACE.Elements_RebuildDrawAreas(NL("console"));
  GEN_USERINTERFACE.Update();

  canvas->DrawFramerate(screen, 10, 30);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::Console_Resolve()
* @brief      Resolves the layout console element pointer.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::Console_Resolve()
{
  consoleelement = (UI_ELEMENT_CONSOLE*)GEN_USERINTERFACE.Element_Get(NL("log_console"), UI_ELEMENT_TYPE_CONSOLE);
  if(!consoleelement) return false;

  // Keep checkbox in sync with console autoscroll (default ON from layout).
  UI_ELEMENT_CHECKBOX* checkbox = (UI_ELEMENT_CHECKBOX*)GEN_USERINTERFACE.Element_Get(NL("autoscroll-chk"), UI_ELEMENT_TYPE_CHECKBOX);
  if(checkbox)
    {
      bool on = consoleelement->GetAutoscroll();
      checkbox->SetStatus(on);
      GEN_USERINTERFACE.Elements_SetToRedraw(checkbox);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::Console_SeedDemoLines()
* @brief      Seeds initial demo lines into the graphical console.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::Console_SeedDemoLines()
{
  if(!consoleelement) return false;

  consoleelement->Clear();

  consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_GREEN,  NL("UI_ELEMENT_CONSOLE ready."));
  consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_GRAY,   NL("------------------------------------------------"));
  consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_BLUE,   NL("Blue   sample line"));
  consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_GREEN,  NL("Green  sample line"));
  consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_PURPLE, NL("Purple sample line"));
  consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_RED,    NL("Red    sample line"));
  consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_GRAY,   NL("Gray   sample line"));

  UI_COLOR rgb;
  rgb.SetRed(255);
  rgb.SetGreen(170);
  rgb.SetBlue(40);
  rgb.SetAlpha(255);
  rgb.SetValid(true);
  consoleelement->PrintRGB(rgb, NL("RGB    sample line (amber)"));

  consoleelement->Print(NL("Multiline payload:\n  line A\n  line B\n  line C"));
  consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_GRAY,
                             NL("Long line (drag horizontally / scrollbar): ---- this is a deliberately very long console line without word-wrap so horizontal scroll can be exercised end-to-end across the viewport ---- END"));
  consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_BLUE,
                             NL("Tips: Shift+click/drag selects lines | Ctrl+A select all | Ctrl+C or Copiar copies to clipboard"));
  consoleelement->Printf(NL("Flood demo at ~%d lines/sec (XTraceMonitor-style stress)..."), UI_CONSOLE_DEMO_LINES_PER_SEC);

  demolinecounter = 0;
  demoline_lastms = xtimer ? xtimer->GetMeasureMilliSeconds() : 0;

  return true;
}


bool UI_CONSOLE::Console_HandleSelection(int cursor_x, int cursor_y, bool shiftdown, bool extending)
{
  if(!consoleelement) return false;

  XDWORD lineindex = 0;
  if(!consoleelement->HitTestLine(cursor_x, cursor_y, lineindex)) return false;

  if(shiftdown || extending)
    {
      if(!consoleelement->Selection_Has()) selection_anchor = lineindex;
      consoleelement->Selection_Set(selection_anchor, lineindex);
    }
   else
    {
      selection_anchor = lineindex;
      consoleelement->Selection_Set(lineindex, lineindex);
    }

  return true;
}


bool UI_CONSOLE::Console_CopySelection()
{
  if(!consoleelement) return false;

  if(consoleelement->Selection_CopyToClipboard())
    {
      XDWORD first = 0;
      XDWORD last  = 0;
      if(consoleelement->Selection_Get(first, last))
        {
          consoleelement->PrintColorf(UI_ELEMENT_CONSOLE_COLOR_GRAY, NL("Copied lines %d..%d to clipboard."), (int)first, (int)last);
        }
       else
        {
          consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_GRAY, NL("Copied console buffer to clipboard."));
        }
      return true;
    }

  consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_RED, NL("Clipboard copy failed."));
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::UserInterface_ElementSelected(UI_ELEMENT* element)
* @brief      Processes the selected user interface element.
* @ingroup    EXAMPLES
*
* @param[in]  element : User interface element to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_CONSOLE::UserInterface_ElementSelected(UI_ELEMENT* element)
{
  if(!element) return false;

  if(!element->GetName()->Compare(NL("clear-btn"), true))
    {
      if(consoleelement)
        {
          consoleelement->Clear();
          consoleelement->PrintColor(UI_ELEMENT_CONSOLE_COLOR_GRAY, NL("Console cleared."));
          demolinecounter = 0;
          demoline_lastms = xtimer ? xtimer->GetMeasureMilliSeconds() : 0;
        }

      return true;
    }

  if(!element->GetName()->Compare(NL("copy-btn"), true))
    {
      Console_CopySelection();
      return true;
    }

  if(!element->GetName()->Compare(NL("autoscroll-chk"), true))
    {
      UI_ELEMENT_CHECKBOX* checkbox = (UI_ELEMENT_CHECKBOX*)element;
      if(checkbox && consoleelement)
        {
          bool on = checkbox->GetStatus();
          consoleelement->SetAutoscroll(on);
          if(on)
            {
              // Re-engage follow: jump to the live tail immediately.
              consoleelement->Scroll_SetFraction(UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL, 1.0f);
            }
          consoleelement->PrintColorf(UI_ELEMENT_CONSOLE_COLOR_GRAY, NL("Autoscroll %s."), on ? NL("ON") : NL("OFF"));
          consoleelement->SetMustReDraw(true);
        }

      return true;
    }

  if(!element->GetName()->Compare(NL("exit-btn"), true))
    {
      exitconsole = true;
      return true;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_CONSOLE::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
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
bool UI_CONSOLE::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
{
  if(!element_text)   return false;
  if(!maskvalue)      return false;
  if(!maskresolved)   return false;

  if(!maskvalue->Compare(NL("TITLE"), true))
    {
      maskresolved->Set(TL(UI_CONSOLE_TRANSLATEID_UI_CONSOLE_LAYOUT_TITLE));
    }

  if(!maskvalue->Compare(NL("BTN_CLEAR"), true))
    {
      maskresolved->Set(TL(UI_CONSOLE_TRANSLATEID_UI_CONSOLE_BTN_CLEAR));
    }

  if(!maskvalue->Compare(NL("BTN_COPY"), true))
    {
      maskresolved->Set(NL("Copiar"));
    }

  if(!maskvalue->Compare(NL("BTN_EXIT"), true))
    {
      maskresolved->Set(TL(UI_CONSOLE_TRANSLATEID_UI_CONSOLE_BTN_EXIT));
    }

  if(!maskvalue->Compare(NL("CHK_AUTOSCROLL"), true))
    {
      maskresolved->Set(TL(UI_CONSOLE_TRANSLATEID_UI_CONSOLE_CHK_AUTOSCROLL));
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_CONSOLE::HandleEvent_UserInterface(UI_XEVENT* event)
* @brief      Handles user interface events.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_CONSOLE::HandleEvent_UserInterface(UI_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case UI_XEVENT_TYPE_OUTPUT_SELECTED        : { UI_ELEMENT* element = event->GetElement();
                                                     if(element)
                                                       {
                                                         UserInterface_ElementSelected(element);
                                                       }
                                                   }
                                                   break;

      case UI_XEVENT_TYPE_OUTPUT_TEXTTOCHANGE    : { UI_ELEMENT_TEXT* element_text = (UI_ELEMENT_TEXT*)event->GetElement();

                                                     UserInterface_ChangeLiteralText(element_text, event->GetMaskTextValue(), event->GetMaskTextResolved());
                                                   }
                                                   break;

      case UI_XEVENT_TYPE_OUTPUT_CHANGECONTENTS  : break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_CONSOLE::HandleEvent_Graphics(GRPXEVENT* event)
* @brief      Handles graphics events.
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_CONSOLE::HandleEvent_Graphics(GRPXEVENT* event)
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
* @fn         void UI_CONSOLE::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_CONSOLE::HandleEvent(XEVENT* xevent)
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
* @fn         void UI_CONSOLE::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_CONSOLE::Clean()
{
  xtimer             = NULL;
  cursor             = NULL;
  consoleelement     = NULL;
  demolinecounter    = 0;
  demoline_lastms    = 0;
  selection_dragging = false;
  selection_anchor   = 0;
  exitconsole        = false;

  for(int c=0; c<UI_CONSOLE_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }
}
