/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       StaticticsCharts.cpp
* 
* @class      STATICTICSCHARTS
* @brief      Graphics Statistics Charts Example class
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

#include "StaticticsCharts.h"

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
#include "GRPScreen.h"
#include "GRPViewPort.h"
#include "GRPBitmapFile.h"
#include "GRPBitmapFileJPG.h"
#include "GRPVideoFileAVI.h"
#include "GRPVectorFile.h"

#include "GRPStatisticsChartColumns.h"
#include "GRPStatisticsChartLines.h"
#include "GRPStatisticsChartArea.h"
#include "GRPStatisticsChartBars.h"
#include "GRPStatisticsChartStackedColumns.h"
#include "GRPStatisticsChartPie.h"          
#include "GRPStatisticsChartColumns3D.h"
#include "GRPStatisticsChartLines3D.h"
#include "GRPStatisticsChartArea3D.h"
#include "GRPStatisticsChartBars3D.h"
#include "GRPStatisticsChartStackedColumns3D.h"
#include "GRPStatisticsChartPie3D.h"
#include "GRPStatisticsChartBuilderSVG.h"

#include "GRPVectorFileSVG.h"
#include "GRPVectorFileSVGObj.h"
#include "GRPXEvent.h"

#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#include "INPManager.h"
#include "INPDevice.h"

#include "UI_XEvent.h"
#include "UI_Manager.h"

#include "StaticticsCharts_CFG.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(STATICTICSCHARTS, staticticscharts2d)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         STATICTICSCHARTS::STATICTICSCHARTS()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
STATICTICSCHARTS::STATICTICSCHARTS() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         STATICTICSCHARTS::~STATICTICSCHARTS()
* @brief      Destructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
STATICTICSCHARTS::~STATICTICSCHARTS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool STATICTICSCHARTS::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARTS::InitFSMachine()
{
  if(!AddState( STATICTICSCHARTS_XFSMSTATE_NONE           ,
                STATICTICSCHARTS_XFSMEVENT_INI            , STATICTICSCHARTS_XFSMSTATE_INI          ,
                STATICTICSCHARTS_XFSMEVENT_END            , STATICTICSCHARTS_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( STATICTICSCHARTS_XFSMSTATE_INI            ,
                STATICTICSCHARTS_XFSMEVENT_NONE           , STATICTICSCHARTS_XFSMSTATE_NONE         ,
                STATICTICSCHARTS_XFSMEVENT_END            , STATICTICSCHARTS_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( STATICTICSCHARTS_XFSMSTATE_END            ,
                STATICTICSCHARTS_XFSMEVENT_NONE           , STATICTICSCHARTS_XFSMSTATE_NONE         ,
                STATICTICSCHARTS_XFSMEVENT_INI            , STATICTICSCHARTS_XFSMSTATE_INI          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool STATICTICSCHARTS::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARTS::AppProc_Ini()
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

  SetEvent(STATICTICSCHARTS_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool STATICTICSCHARTS::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARTS::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[STATICTICSCHARTS_BUTTON_UP]      = inpdevice->GetButton(INPBUTTON_ID_UP);
      button[STATICTICSCHARTS_BUTTON_DOWN]    = inpdevice->GetButton(INPBUTTON_ID_DOWN);
      button[STATICTICSCHARTS_BUTTON_LEFT]    = inpdevice->GetButton(INPBUTTON_ID_LEFT);
      button[STATICTICSCHARTS_BUTTON_RIGHT]   = inpdevice->GetButton(INPBUTTON_ID_RIGHT);
      button[STATICTICSCHARTS_BUTTON_SPACE]   = inpdevice->GetButton(INPBUTTON_ID_SPACE);
      button[STATICTICSCHARTS_BUTTON_ESC]     = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[STATICTICSCHARTS_BUTTON_F1]      = inpdevice->GetButton(INPBUTTON_ID_F1);
      button[STATICTICSCHARTS_BUTTON_F2]      = inpdevice->GetButton(INPBUTTON_ID_F2);
      button[STATICTICSCHARTS_BUTTON_F5]      = inpdevice->GetButton(INPBUTTON_ID_F5);
      button[STATICTICSCHARTS_BUTTON_F9]      = inpdevice->GetButton(INPBUTTON_ID_F9);
      button[STATICTICSCHARTS_BUTTON_MINUS]   = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_MINUS);
      button[STATICTICSCHARTS_BUTTON_PLUS]    = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_PLUS);

      button[STATICTICSCHARTS_BUTTON_MOUSE]   = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[STATICTICSCHARTS_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[STATICTICSCHARTS_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }

  //--------------------------------------------------------------------------------------

  if(!Ini_UserInterface(true)) return false;

  //--------------------------------------------------------------------------------------

  GRPVIEWPORT*  viewport = NULL;
  GRP2DCANVAS*  canvas   = NULL;

  viewport = GetMainScreen()->GetViewport(0);
  if(viewport) canvas =   viewport->GetCanvas();

  if(canvas)
    {
      if(backgroundbmp) 
        {
          canvas->PutBitmapNoAlpha(0, 0, backgroundbmp);
        }
    }

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool STATICTICSCHARTS::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARTS::AppProc_Update()
{
  if(GetEvent()==STATICTICSCHARTS_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case STATICTICSCHARTS_XFSMSTATE_NONE      : break;

          case STATICTICSCHARTS_XFSMSTATE_INI       : UpdateInput();
                                                      DrawFrame();
                                                      GetMainScreen()->UpdateViewports();
                                                      break;

          case STATICTICSCHARTS_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<STATICTICSCHARTS_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case STATICTICSCHARTS_XFSMSTATE_NONE  : break;

              case STATICTICSCHARTS_XFSMSTATE_INI   : break;

              case STATICTICSCHARTS_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool STATICTICSCHARTS::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARTS::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetCurrentState(STATICTICSCHARTS_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------
  
  vectorfiles.DeleteContents();
  vectorfiles.DeleteAll();

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

  if(backgroundbmp)
    {
      delete backgroundbmp;
      backgroundbmp = NULL;
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
* @fn         bool STATICTICSCHARTS::UpdateInput()
* @brief      Updates the application input state.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARTS::UpdateInput()
{
   int  width  = GetMainScreen()->GetWidth();
   int  height = GetMainScreen()->GetHeight();

  if(cursor)    
    {  
      if(cursor->GetMotion()->IsReadyToTest(50))
        {
          cursor->GetMotion()->InvertYAxis(height);                 
          
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
                  
                }

              if(button[STATICTICSCHARTS_BUTTON_MOUSE]->IsPressedWithRelease())
                {
                  indexchart+=6;
                  if (indexchart > 23) indexchart = 0;

                  cursor->GetMotion()->Reset();       
                }
    
              if(button[STATICTICSCHARTS_BUTTON_TOUCHSCREEN])
                {             
                  if(button[STATICTICSCHARTS_BUTTON_TOUCHSCREEN]->IsPressed())
                    {  
                      indexchart+=6;
                      if (indexchart > 23) indexchart = 0;

                      cursor->GetMotion()->Reset();
                    }
                }
            }
        }
    }


  for(int c=0; c<STATICTICSCHARTS_BUTTON_MOUSE; c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  case STATICTICSCHARTS_BUTTON_F1     : indexchart+=6;
                                                        if(indexchart > 23) indexchart = 0;

                                                        break;

                  case STATICTICSCHARTS_BUTTON_F2     : break;
                            
                  case STATICTICSCHARTS_BUTTON_F5     : break;

              

                  case STATICTICSCHARTS_BUTTON_ESC    : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                        break;
                }
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool STATICTICSCHARTS::Ini_StaticticCharts()
* @brief      ini  statictic charts
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARTS::Ini_StaticticCharts()
{
  XVECTOR<double> values;
  int             indexvalue = 0;  

  
  vectorfiles.DeleteContents();
  vectorfiles.DeleteAll();


  for(int d=0; d<48; d++)   
    {
      values.Add((double)xrand->Between(10, 80));     
    }

  
  for(int c=0; c<24; c++)
    {
      GRPVECTORFILE* vectorfile = GRPVECTORFILE::CreateInstance(GRPVECTORFILETYPE_SVG);
      if(vectorfile)
        {
          GRPSTATISTICSCHART* chart = NULL;

          switch(c)
            {         
              case  0: chart = new GRPSTATISTICSCHARTCOLUMNS();             break;
              case  1: chart = new GRPSTATISTICSCHARTLINES();               break;
              case  2: chart = new GRPSTATISTICSCHARTAREA();                break;
              case  3: chart = new GRPSTATISTICSCHARTBARS();                break;
              case  4: chart = new GRPSTATISTICSCHARTSTACKEDCOLUMNS();      break;
              case  5: chart = new GRPSTATISTICSCHARTPIE();                 break;  

              case  6: chart = new GRPSTATISTICSCHARTCOLUMNS3D();           break;
              case  7: chart = new GRPSTATISTICSCHARTLINES3D();             break;
              case  8: chart = new GRPSTATISTICSCHARTAREA3D();              break;
              case  9: chart = new GRPSTATISTICSCHARTBARS3D();              break;
              case 10: chart = new GRPSTATISTICSCHARTSTACKEDCOLUMNS3D();    break;
              case 11: chart = new GRPSTATISTICSCHARTPIE3D();               break;  

              case 12: chart = new GRPSTATISTICSCHARTCOLUMNS();             break;
              case 13: chart = new GRPSTATISTICSCHARTLINES();               break;
              case 14: chart = new GRPSTATISTICSCHARTAREA();                break;
              case 15: chart = new GRPSTATISTICSCHARTBARS();                break;
              case 16: chart = new GRPSTATISTICSCHARTSTACKEDCOLUMNS();      break;
              case 17: chart = new GRPSTATISTICSCHARTPIE();                 break;  

              case 18: chart = new GRPSTATISTICSCHARTCOLUMNS3D();           break;
              case 19: chart = new GRPSTATISTICSCHARTLINES3D();             break;
              case 20: chart = new GRPSTATISTICSCHARTAREA3D();              break;
              case 21: chart = new GRPSTATISTICSCHARTBARS3D();              break;
              case 22: chart = new GRPSTATISTICSCHARTSTACKEDCOLUMNS3D();    break;
              case 23: chart = new GRPSTATISTICSCHARTPIE3D();               break;  
            }

          if(chart)
            { 
              GRPSTATISTICSCHARTCONFIG* config = chart->GetConfig();
              if(config)
                {
                  config->SetTitle(__L("Sales by quarter"));

                  config->SetShowValues(true);
         
                  config->SetShowLegend(true);
                  config->SetLegendPosition(GRPSTATISTICSCHARTLEGENDPOSITION_LEFT);
                  config->SetLegendFontSize(12.0);
                  config->SetShowAxisLabels(true);
                  config->SetAxisFontSize(11.0);
                  if(c>11)
                    {
                      GRPSTATISTICSCHARTCOLOR color(255, 255, 255, 175);
                      config->SetBackgroundColor(color);
                    }
                }

              if(!(c%6))
                {
                  indexvalue = 0;
                }
                           
              GRPSTATISTICSCHARTDATA* data = chart->GetData();
              if(data)
                {
                  data->AddCategory(__L("Q1"));
                  data->AddCategory(__L("Q2"));
                  data->AddCategory(__L("Q3"));
                  data->AddCategory(__L("Q4"));
                                
                  GRPSTATISTICSCHARTSERIE* serie2024 = data->AddSerie(__L("2024"));
                  if(serie2024)
                    {
                      for(int e=0; e<4; e++)  
                        {
                          serie2024->AddValue((double)values.Get(indexvalue));  
                          indexvalue++;
                        }                      
                    }

                  GRPSTATISTICSCHARTSERIE* serie2025 = data->AddSerie(__L("2025"));
                  if(serie2025)
                    {
                      for(int e=0; e<4; e++)  
                        {
                          serie2025->AddValue((double)values.Get(indexvalue));  
                          indexvalue++;
                        }                                            
                    }                                    
                }

              GRPSTATISTICSCHARTBUILDERSVG builder;

              if(chart->Generate(builder, 420.0, 420.0) == GRPVECTORFILERESULT_OK)
                {
                  XSTRING content;

                  if(builder.GetResult(content))
                    {
                      vectorfile->Load(content);
                    }
                }

              vectorfiles.Add(vectorfile);    

              delete chart;
            }
        }      
    }

  //--------------------------------------------------------------------------------------

  values.DeleteAll();

  return true;

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool STATICTICSCHARTS::Ini_Graphics(GRPSCREEN* screen)
* @brief      Initializes the graphics subsystem.
* @ingroup    EXAMPLES
*
* @param[in]  screen : Screen where the graphics or user interface resources are created.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARTS::Ini_Graphics(GRPSCREEN* screen)
{

  //--------------------------------------------------------------------------------------

  screen->SetWidth((420*3)+(20*4));
  screen->SetHeight((420*2)+(20*3));

  screen->GetTitle()->Set(__L("Statictics Chars Canvas"));  

  GetMainScreen()->CreateViewport(GRPVIEWPORT_ID_MAIN, 0.0f, 0.0f, (float)screen->GetWidth(), (float)screen->GetHeight(), 0, 0, (screen->GetWidth()), (screen->GetHeight()));

  //--------------------------------------------------------------------------------------

  GRPVIEWPORT*    viewport  = NULL;
  GRP2DCANVAS*    canvas    = NULL;
  int             width     = 0;
  int             height = 0;

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

  XPATH xpath;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("background.jpg"));

  GRPBITMAPFILE   bitmapfile;
  
  backgroundbmp = bitmapfile.Load(xpath, GetMainScreen()->GetMode());
  if(!backgroundbmp) return false;

  
  XPATH pathfont;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_FONTS, pathfont);
  pathfont.Slash_Add();             
  pathfont.Add(__L("Nunito-SemiBold.ttf"));

  canvas->VectorFont_Load(pathfont);

  Ini_StaticticCharts();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool STATICTICSCHARTS::Ini_UserInterface(bool on)
* @brief      ini  user interface
* @ingroup    
* 
* @param[in]  on : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARTS::Ini_UserInterface(bool on)
{  
  if(!on)
    { 
      GEN_USERINTERFACE.SubscribeOutputEvents(false, this, &GEN_USERINTERFACE.GetInstance());
      GEN_USERINTERFACE.SubscribeInputEvents(false);
      GEN_USERINTERFACE.DelInstance();
   
      return true;
    }

  //--------------------------------------------------------------------------------------

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
 
  
  //--------------------------------------------------------------------------------------
  
  UserInterface_CFGChromes(screen); 

  //--------------------------------------------------------------------------------------

  GEN_USERINTERFACE.SubscribeInputEvents(true);
  GEN_USERINTERFACE.SubscribeOutputEvents(true, this, &GEN_USERINTERFACE.GetInstance());   

  GEN_USERINTERFACE.Elements_SetToRedraw();
        
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool STATICTICSCHARTS::DrawFrame()
* @brief      Draws the current frame.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARTS::DrawFrame()
{
  GRP2DCOLOR_RGBA8  colorblack(0, 0, 0);
  GRP2DCOLOR_RGBA8  colorwhite(255, 255, 255);
  GRP2DCOLOR_RGBA8  colorred(255, 0, 0);
  GRP2DCOLOR_RGBA8  colorgreen(0, 255, 0);
  GRP2DCOLOR_RGBA8  colorblue(0, 0, 255);
  GRP2DCOLOR_RGBA8  colorgray(10, 10, 10, 150);

  GRPSCREEN*        screen    = NULL;
  GRPVIEWPORT*      viewport  = NULL;
  GRP2DCANVAS*      canvas    = NULL;
  int               width     = 0;
  int               height    = 0;


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

  width  = screen->GetWidth();
  height = screen->GetHeight();

  //--------------------------------------------------------------------------------------

  if(canvas)
    {
      if(indexchart>11)
        {
          if(backgroundbmp) 
            {
              canvas->PutBitmapNoAlpha(0, 0, backgroundbmp);
            }                    
        }
       else
        {
          canvas->Clear(&colorwhite);  
        }
    }

  //--------------------------------------------------------------------------------------

  for(int c=0; c<6; c++)
    {
      GRPVECTORFILE* vectorfile = vectorfiles.Get(c+indexchart);
      if(vectorfile)
        {
          float x = 20.0 + (c%3) * (420.0 + 20.0);
          float y = 20.0 + (c/3) * (420.0 + 20.0);

          vectorfile_render.RenderCached(vectorfile, canvas, x, y, 420.0, 420.0);    
        }
    }

  //--------------------------------------------------------------------------------------

  GEN_USERINTERFACE.Elements_RebuildDrawAreas();
  
  GEN_USERINTERFACE.Update(); 

  //--------------------------------------------------------------------------------------


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool STATICTICSCHARTS::UserInterface_CFGChromes(GRPSCREEN* screen)
* @brief      user interface  CFGchromes
* @ingroup    
* 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARTS::UserInterface_CFGChromes(GRPSCREEN* screen)
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
* @fn         void STATICTICSCHARTS::HandleEvent_UserInterface(UI_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @ingroup    
* @note       INTERNAL
* 
* @param[in]  event : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void STATICTICSCHARTS::HandleEvent_UserInterface(UI_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case  UI_XEVENT_TYPE_OUTPUT_SELECTED        : break;

      case UI_XEVENT_TYPE_OUTPUT_TEXTTOCHANGE     : break;

      case UI_XEVENT_TYPE_OUTPUT_CHANGECONTENTS   : break;      
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void STATICTICSCHARTS::HandleEvent_Graphics(GRPXEVENT* event)
* @brief      Handles graphics events.
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void STATICTICSCHARTS::HandleEvent_Graphics(GRPXEVENT* event)
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
* @fn         void STATICTICSCHARTS::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void STATICTICSCHARTS::HandleEvent(XEVENT* xevent)
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
* @fn         void STATICTICSCHARTS::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void STATICTICSCHARTS::Clean()
{
  xtimer          = NULL;
  xrand           = NULL;

  indexchart      = 0;
 
  backgroundbmp   = NULL;

  for(int c=0; c<STATICTICSCHARTS_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }  
}