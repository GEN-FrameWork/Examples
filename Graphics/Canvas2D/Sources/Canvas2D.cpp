/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Canvas2D.cpp
* 
* @class      CANVAS2D
* @brief      Graphics Canvas 2D Example class
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

#include "Canvas2D.h"

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
#include "GRPXEvent.h"

#include "INPManager.h"

#if SND_ACTIVE
  
  #include "SNDFactory_XEvent.h"
  #include "SNDItem.h"
  #include "SNDFactory.h"

#endif

#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#include "Canvas2D_CFG.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(CANVAS2D, canvas2d)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D::CANVAS2D()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
CANVAS2D::CANVAS2D() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D::~CANVAS2D()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
CANVAS2D::~CANVAS2D()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::InitFSMachine()
{
  if(!AddState( CANVAS2D_XFSMSTATE_NONE           ,
                CANVAS2D_XFSMEVENT_INI            , CANVAS2D_XFSMSTATE_INI          ,
                CANVAS2D_XFSMEVENT_END            , CANVAS2D_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( CANVAS2D_XFSMSTATE_INI            ,
                CANVAS2D_XFSMEVENT_NONE           , CANVAS2D_XFSMSTATE_NONE         ,
                CANVAS2D_XFSMEVENT_END            , CANVAS2D_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( CANVAS2D_XFSMSTATE_END            ,
                CANVAS2D_XFSMEVENT_NONE           , CANVAS2D_XFSMSTATE_NONE         ,
                CANVAS2D_XFSMEVENT_INI            , CANVAS2D_XFSMSTATE_INI          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::AppProc_Ini()
{
  XSTRING   string;
  XSTRING   stringresult;

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
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_SOUNDS, APPFLOW_DEFAULT_DIRECTORY_SOUNDS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_FONTS, APPFLOW_DEFAULT_DIRECTORY_FONTS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_UI_LAYOUTS, APPFLOW_DEFAULT_DIRECTORY_UI_LAYOUTS);


  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  rand = GEN_XFACTORY.CreateRand();
  if(!rand) 
    {
      return false;
    }

  //--------------------------------------------------------------------------------------

  xtimer = GEN_XFACTORY.CreateTimer();
  if(!xtimer) 
    {
      return false;
    }

  //--------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), SCRIPTS_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);

  //--------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG);

  //--------------------------------------------------------------------------------------

  SetEvent(CANVAS2D_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[CANVAS2D_BUTTON_UP]      = inpdevice->GetButton(INPBUTTON_ID_UP);
      button[CANVAS2D_BUTTON_DOWN]    = inpdevice->GetButton(INPBUTTON_ID_DOWN);
      button[CANVAS2D_BUTTON_LEFT]    = inpdevice->GetButton(INPBUTTON_ID_LEFT);
      button[CANVAS2D_BUTTON_RIGHT]   = inpdevice->GetButton(INPBUTTON_ID_RIGHT);
      button[CANVAS2D_BUTTON_SPACE]   = inpdevice->GetButton(INPBUTTON_ID_SPACE);
      button[CANVAS2D_BUTTON_ESC]     = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[CANVAS2D_BUTTON_MOUSE]   = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[CANVAS2D_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[CANVAS2D_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }  

  //--------------------------------------------------------------------------------

  GRPVIEWPORT*  viewport = NULL;
  GRP2DCANVAS*  canvas   = NULL;

  viewport = GetMainScreen()->GetViewport(0);
  if(viewport) canvas =   viewport->GetCanvas();

  if(canvas)
    {
      XPATH xpath;

      if(backgroundbmp) 
        {
          canvas->PutBitmapNoAlpha(0, -(backgroundbmp->GetHeight() - 768.0f), backgroundbmp);
        }

      canvas->RasterFont_Select(__L("verdana18"));

      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_FONTS, xpath);   
      xpath.Slash_Add();
      xpath.Add(__L("Augusta.ttf"));
     
      canvas->Vectorfont_GetConfig()->SetHeight(40.0f);
      canvas->VectorFont_Load(xpath);
    }

  //--------------------------------------------------------------------------------

  #if SND_ACTIVE

  { XPATH xpathsounds;
    XPATH xpath;
    GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SOUNDS, xpathsounds);   
    xpathsounds.Slash_Add();

    xpath = xpathsounds;
    xpath.Add(__L("greensleeves.ogg"));

    backgroundsound = GEN_SNDFACTORY.CreateItem(xpath);
    if(backgroundsound)
      {        
        GEN_SNDFACTORY.Sound_Play(backgroundsound, &playCFGsound, SNDFACTORY_INLOOP); 
        GEN_SNDFACTORY.Sound_SetVolume(backgroundsound, 25);
      }

    xpath = xpathsounds;
    xpath.Add(__L("armour-walking1.ogg"));
    armorwalkingsounds[0] = GEN_SNDFACTORY.CreateItem(xpath);
   
    xpath = xpathsounds;
    xpath.Add(__L("armour-walking2.ogg"));
    armorwalkingsounds[1] = GEN_SNDFACTORY.CreateItem(xpath);
     
    SubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_INI, &GEN_SNDFACTORY.GetInstance());
    SubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_PLAY, &GEN_SNDFACTORY.GetInstance());
    SubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_PAUSE , &GEN_SNDFACTORY.GetInstance());
    SubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_STOP, &GEN_SNDFACTORY.GetInstance());
    SubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_END, &GEN_SNDFACTORY.GetInstance());
  }

  #endif

  //--------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::AppProc_Update()
{
  if(GetEvent()==CANVAS2D_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case CANVAS2D_XFSMSTATE_NONE      : break;

          case CANVAS2D_XFSMSTATE_INI       : { 
                                                UpdateInput();

                                                DrawFrame();

                                                GetMainScreen()->UpdateViewports();
                                              }
                                              break;

          case CANVAS2D_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<CANVAS2D_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case CANVAS2D_XFSMSTATE_NONE  : break;

              case CANVAS2D_XFSMSTATE_INI   : break;

              case CANVAS2D_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetCurrentState(CANVAS2D_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------
 
  #if SND_ACTIVE

  UnSubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_INI, &GEN_SNDFACTORY.GetInstance());
  UnSubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_PLAY, &GEN_SNDFACTORY.GetInstance());
  UnSubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_PAUSE , &GEN_SNDFACTORY.GetInstance());
  UnSubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_STOP, &GEN_SNDFACTORY.GetInstance());
  UnSubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_END, &GEN_SNDFACTORY.GetInstance());
 
  GEN_SNDFACTORY.Sound_StopAll();

  GEN_SNDFACTORY.DeleteAllItems();

  #endif

  //--------------------------------------------------------------------------------------

  if(backgroundbmp)
    {
      delete backgroundbmp;
      backgroundbmp = NULL;
    }

  for(XDWORD c=0; c<2; c++)
    {
      if(charactersecuence[c])
        {
          delete charactersecuence[c];
          charactersecuence[c] = NULL;
        }
    }

  //--------------------------------------------------------------------------------------

  if(xtimer)
    {
      GEN_XFACTORY.DeleteTimer(xtimer);
      xtimer = NULL;
    }

  if(rand)
    {
      GEN_XFACTORY.DeleteRand(rand);
      rand = NULL;
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
* @fn         bool CANVAS2D::UpdateInput()
* @brief      Updates the application input state.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::UpdateInput()
{
  if(cursor)
    {     
      if(cursor->GetMotion()->IsReadyToTest())
        {
          INPCURSORMOTION_DIR motiondir = cursor->GetMotion()->GetDirectionByAngle(true);
          if(motiondir != INPCURSORMOTION_DIR_UNKNOWN)
            {
              switch(motiondir)
                {
                  case INPCURSORMOTION_DIR_DOWN       :
                  case INPCURSORMOTION_DIR_RIGHTUP    : makeaction = __L("WALK NORTH");
                                                        break;

                  case INPCURSORMOTION_DIR_RIGHT      :
                  case INPCURSORMOTION_DIR_LEFTUP     : makeaction = __L("WALK WEST" );
                                                        break;

                  case INPCURSORMOTION_DIR_LEFT       :
                  case INPCURSORMOTION_DIR_RIGHTDOWN  : makeaction = __L("WALK EAST" );
                                                        break;

                  case INPCURSORMOTION_DIR_UP         :
                  case INPCURSORMOTION_DIR_LEFTDOWN   : makeaction = __L("WALK SOUTH");
                                                        break;

                                          default     : break;
                }

              cursor->GetMotion()->Reset();
            }
        }
    }


  for(int c=0;c<CANVAS2D_BUTTON_MAX;c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  case CANVAS2D_BUTTON_ESC      : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                  break;
                }
            }

          if(button[c]->IsPressed())
            {
              switch(c)
                {
                  case CANVAS2D_BUTTON_UP     : makeaction = __L("WALK NORTH");   break;
                  case CANVAS2D_BUTTON_DOWN   : makeaction = __L("WALK SOUTH");   break;
                  case CANVAS2D_BUTTON_LEFT   : makeaction = __L("WALK WEST" );   break;
                  case CANVAS2D_BUTTON_RIGHT  : makeaction = __L("WALK EAST" );   break;

                  case CANVAS2D_BUTTON_SPACE  : break;
                }
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D::Ini_Graphics(GRPSCREEN* screen)
* @brief      Initializes the graphics subsystem.
* @ingroup    EXAMPLES
*
* @param[in]  screen : Screen where the graphics or user interface resources are created.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::Ini_Graphics(GRPSCREEN* screen)
{  
  XPATH           xpath;
  GRPBITMAPFILE*  bitmapfile;
  bool            status;  


  //--------------------------------------------------------------------------------------

  UserInterface_CFGChromes(screen); 

  //--------------------------------------------------------------------------------------

  bitmapfile = GEN_NEW GRPBITMAPFILE();
  if(!bitmapfile) return false;

  if(!backgroundbmp)
    {
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
      xpath.Slash_Add();
      xpath.Add(__L("background.jpg"));

      backgroundbmp = bitmapfile->Load(xpath, GetMainScreen()->GetMode());
      if(!backgroundbmp) return false;
    }
  
  //--------------------------------------------------------------------------------------  
    
  if(!charactersecuence[0])
    {
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
      xpath.Slash_Add();
      xpath.Add(__L("gigolord_walk0"));

      bitmapfile->SetPath(xpath);

      charactersecuence[0] = bitmapfile->LoadSequence(__L("LF-WxWalk_01%02d.png"), 1);
      charactersecuence[1] = charactersecuence[0]->Copy();

      charactersecuence[1]->Flip(true);

      if(charactersecuence[0]) 
        {
          charactersecuence[0]->Play();      
        }

      if(charactersecuence[1]) 
        {
          charactersecuence[1]->Play();      
        }
    }

  delete bitmapfile;

  //--------------------------------------------------------------------------------------

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Main Screen: Width %d, height %d"), screen->GetWidth(), screen->GetHeight());

  
  screen->SetPosition(GRPPROPERTYMODE_SCREEN_CENTER, GRPPROPERTYMODE_SCREEN_CENTER);
  screen->SetWidth(1024);
  screen->SetHeight(768);
  
  screen->GetTitle()->Set(__L("Canvas 2D"));
  
  screen->SetDesktopScreenSelected(GRPSCREENTYPE_DESKTOP_SCREEN1);

  status = screen->CreateViewport(APPLICATION_GUI_MAIN_VIEWPORT_ID, 0.0f, 0.0f, (float)screen->GetWidth(), (float)screen->GetHeight(), 0, 0, (backgroundbmp->GetWidth()), (backgroundbmp->GetHeight()));


  /*
  #ifndef ANDROID 
  if(backgroundbmp)
    {
      screen->SetWidth(1080);
      screen->SetHeight(backgroundbmp->GetHeight());
    }
   else
    {
      screen->SetHeight(1024);
      screen->SetHeight(768);
    } 

  GetMainScreen()->CreateViewport(GRPVIEWPORT_ID_MAIN , 0.0f, 0.0f, (float)screen->GetWidth(), (float)screen->GetHeight(),  0,  0, (backgroundbmp->GetWidth()) , (backgroundbmp->GetHeight()));
  #else

  screen->SetWidth(1024);
  screen->SetHeight(768);  
 
  #endif 
  */
 
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D::DrawStep(GRP2DCANVAS* canvas, int x, int y, bool type)
* @brief      Draws a step on the canvas.
* @ingroup    EXAMPLES
*
* @param[in]  canvas : Canvas used to draw the graphical element.
* @param[in]  x : Horizontal coordinate.
* @param[in]  y : Vertical coordinate.
* @param[in]  type : Type value used by the operation.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::DrawStep(GRP2DCANVAS* canvas, int x, int y, bool type)
{
  GRP2DCOLOR_RGBA8 color(80, 80, 80);
  
  for(int c=0; c<rand->Between(7, 15); c++)
    {      
      for(int d=0; d<rand->Between(1, 6); d++)
        {       
          if(rand->Between(0, 1))
            {
              int _x = x + 52 + c + (type?3:5);
              int _y = y - 18 - (type?0:5);

              _y += rand->Between(0, 2);
              _y -= rand->Between(0, 2);
            
              canvas->PutBlendPixel(_x, _y, &color, rand->Between(1, 10)); 
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D::DrawShadow(GRP2DCANVAS* canvas, int x, int y)
* @brief      Draws a shadow on the canvas.
* @ingroup    EXAMPLES
*
* @param[in]  canvas : Canvas used to draw the graphical element.
* @param[in]  x : Horizontal coordinate.
* @param[in]  y : Vertical coordinate.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::DrawShadow(GRP2DCANVAS* canvas, int x, int y)
{
  GRP2DCOLOR_RGBA8  colorshadow(10, 10, 10, 30);

  canvas->SetLineWidth(0.0f);
  canvas->SetFillColor(&colorshadow);
  
  canvas->Ellipse(x + 75, y + 130, 40, 8, true);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D::DrawFrame()
* @brief      Draws the current frame.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::DrawFrame()
{
  if(!GetMainScreen())
    {
      return false;
    }

  GRP2DCOLOR_RGBA8  colorwhite(255, 255, 255);
  GRP2DCOLOR_RGBA8  coloryellow(255, 255, 0);
  GRP2DCOLOR_RGBA8  colorgray(10, 10, 10, 150);
  
  GRPVIEWPORT*      viewport                = NULL;
  GRP2DCANVAS*        canvas                  = NULL;
  static int        scrollposx              = 680;

  int               width                   = GetMainScreen()->GetWidth();
  int               height                  = GetMainScreen()->GetHeight();  

  static int        x                       = 1600;
  static int        y                       = height - 180;
  static bool       tofront                 = true;
  static int        scrollstep              = 0;
  static int        nupdates                = 0;

  int               indexcharactersequence  = tofront?0:1;

  viewport = GetMainScreen()->GetViewport(0);
  if(viewport) 
    {
      canvas =   viewport->GetCanvas();
    }

  if(!canvas) 
    {
      return false;
    }
  
  rand->Ini();

  canvas->ReleaseDrawFramerate();       
  
  if(makeaction.Compare(__L("WALK WEST" ), true))   
    { 
      scrollposx++; 
    }

  if(makeaction.Compare(__L("WALK EAST" ), true))   
    { 
      scrollposx--;
    }
     
  if(!makeaction.IsEmpty())
    {
      scrollstep++;

      if(scrollstep > 20)
        {
          scrollstep = 0;
          makeaction.Empty();
        }
    }

  if(scrollposx < 0)
    {
      scrollposx = 0;      
      makeaction.Empty();
    }

  viewport->SetCanvasPosition((float)scrollposx, 0);

  scrollposx = (int)viewport->GetCanvasPositionX();

  canvas->RebuildAllAreas();
  canvas->DeleteAllRebuildAreas();

  #if SND_ACTIVE

  if(charactersecuence[indexcharactersequence]->GetActualFrameIndex() == 4)  
    {    
      if(armorwalkingsounds[0]->GetStatus() != SNDITEM_STATUS_PLAY)         
        {
          playCFGsound.SetVolume(10);
          GEN_SNDFACTORY.Sound_Play(armorwalkingsounds[0], &playCFGsound, 1); 
        }   
      
      DrawStep(canvas, x, y + charactersecuence[indexcharactersequence]->GetActualFrame()->GetBitmap()->GetHeight(), false);
    }
  
  if(charactersecuence[indexcharactersequence]->GetActualFrameIndex() == 17)  
    {    
      if(armorwalkingsounds[1]->GetStatus() != SNDITEM_STATUS_PLAY)        
        {
          playCFGsound.SetVolume(10);
          GEN_SNDFACTORY.Sound_Play(armorwalkingsounds[1], &playCFGsound, 1);         
        }      

      DrawStep(canvas, x, y + charactersecuence[indexcharactersequence]->GetActualFrame()->GetBitmap()->GetHeight(), true);
    }

  #endif  

  canvas->CreateRebuildArea(x, y, charactersecuence[indexcharactersequence]->GetActualFrame()->GetBitmap()->GetWidth() + 15, charactersecuence[0]->GetActualFrame()->GetBitmap()->GetHeight() + 15);
  
  DrawShadow(canvas, x, y);
 
  canvas->PutBitmapFrame(x, y, charactersecuence[indexcharactersequence]->GetActualFrame());


  if(xtimer->GetMeasureMilliSeconds() > 30)
    {
      charactersecuence[indexcharactersequence]->Update();
      xtimer->Reset();

      if(tofront)
        {
          x -= 4;
          if(x < 670) 
            {
              tofront = !tofront;
            }
        }
       else 
        {
          x += 4;
          if(x > 1600) 
            {
              tofront = !tofront;
            }
        }
    }

  int pos_signboard = (width - 570) / 2;

  canvas->CreateRebuildArea(scrollposx + pos_signboard, 50, scrollposx + pos_signboard + 570 , 150);

  canvas->SetLineWidth(1.5f);
  canvas->SetLineColor(&colorwhite);
  canvas->SetFillColor(&colorgray);

  canvas->RoundRect(scrollposx + pos_signboard, 50, scrollposx + pos_signboard + 570, 150, 20, true);

  canvas->Vectorfont_GetConfig()->SetColor(&coloryellow);
  canvas->VectorFont_Printf(scrollposx + pos_signboard + 20, 90, __L("Once upon a time,"));
  canvas->VectorFont_Printf(scrollposx + pos_signboard + 90, 130, __L("in a kingdom far, far away... "));
  
  canvas->DrawFramerate(GetMainScreen(), scrollposx + 10, 30);

  nupdates++;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CANVAS2D::UserInterface_CFGChromes(GRPSCREEN* screen)
* @brief      user interface  CFGchromes
* @ingroup    
* 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::UserInterface_CFGChromes(GRPSCREEN* screen)
{
  GRPSCREENCFGCHROMES cfgchromes;

  #ifdef GRP_SCREEN_CUSTOMCHROMES_ACTIVE

  //cfgchromes.SetCustomAutoHide(500);

  #else

  cfgchromes.SetNativeCaptionActive(true);
  cfgchromes.SetNativeIconActive(false);
  cfgchromes.SetNativeTitleActive(true); 
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
* @fn         void CANVAS2D::HandleEvent_Graphics(GRPXEVENT* event)
* @brief      Handles graphics events.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void CANVAS2D::HandleEvent_Graphics(GRPXEVENT* event)
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
* @fn         void CANVAS2D::HandleEvent_Sound(SNDFACTORY_XEVENT* event)
* @brief      Handle event sound.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void CANVAS2D::HandleEvent_Sound(SNDFACTORY_XEVENT* event)
{  
  #if SND_ACTIVE
  switch(event->GetEventType())
    {
      case SNDFACTORY_XEVENT_TYPE_SOUND_INI     : 
      case SNDFACTORY_XEVENT_TYPE_SOUND_PLAY    : 
      case SNDFACTORY_XEVENT_TYPE_SOUND_PAUSE   : 
      case SNDFACTORY_XEVENT_TYPE_SOUND_STOP    : 
      case SNDFACTORY_XEVENT_TYPE_SOUND_END     : { XSTRING  typestr;
                                                    XSTRING  statusstr;
                                                    XSTRING* ID;  
                                                    
                                                    event->GetItem()->GetType(typestr);
                                                    event->GetItem()->GetStatus(statusstr);
                                                    ID = event->GetItem()->GetID();      

                                                    //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Sound] [%08X] %s (%s) -> %s"), event->GetItem(), typestr.Get(), ID->Get(), statusstr.Get());    
                                                  } 
                                                  break;
    } 
  
  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void CANVAS2D::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void CANVAS2D::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_GRAPHICS         : { GRPXEVENT* event = (GRPXEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_Graphics(event);
                                          }
                                          break;

      case XEVENT_TYPE_SOUND            : { SNDFACTORY_XEVENT* event = (SNDFACTORY_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_Sound(event);
                                          }
                                          break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void CANVAS2D::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void CANVAS2D::Clean()
{
  rand                        = NULL;
  xtimer                      = NULL;

  for(int c=0; c<CANVAS2D_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }

  cursor                      = NULL;

  backgroundbmp               = NULL;
  charactersecuence[0]        = NULL;
  charactersecuence[1]        = NULL;

  #if SND_ACTIVE

  backgroundsound             = NULL;
  armorwalkingsounds[0]       = NULL;
  armorwalkingsounds[1]       = NULL;

  #endif
}


