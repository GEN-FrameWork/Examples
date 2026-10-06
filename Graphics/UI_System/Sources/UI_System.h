/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_System.h
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

#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "DIOCheckInternetConnection.h"

#include "APPFlowGraphics.h"

#include "GRP2DVectorFileRenderAGG.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum UI_SYSTEMXFSMEVENTS
{
  UI_SYSTEM_XFSMEVENT_NONE                  = 0 ,
  UI_SYSTEM_XFSMEVENT_INI                       ,
  UI_SYSTEM_XFSMEVENT_END                       ,

  UI_SYSTEM_LASTEVENT
};


enum UI_SYSTEMXFSMSTATES
{
  UI_SYSTEM_XFSMSTATE_NONE                  = 0 ,
  UI_SYSTEM_XFSMSTATE_INI                       ,
  UI_SYSTEM_XFSMSTATE_END                       ,

  UI_SYSTEM_LASTSTATE
};


enum UI_SYSTEMTASKID
{
  UI_SYSTEMTASKID_UNKNOWN                   = 0 ,
  UI_SYSTEMTASKID_UPDATEHARDWAREINFO            ,
};


enum UI_SYSTEM_SECTIONID
{
  UI_SYSTEM_SECTIONID_RESUMEN               = 0 ,
  UI_SYSTEM_SECTIONID_CPU                       ,
  UI_SYSTEM_SECTIONID_MEMORIA                   ,
  UI_SYSTEM_SECTIONID_RED                       ,
  UI_SYSTEM_SECTIONID_DISCO                     ,
  UI_SYSTEM_SECTIONID_PROCESOS                  ,
  UI_SYSTEM_SECTIONID_ALERTAS                   ,
  UI_SYSTEM_SECTIONID_CONFIGURACION             ,

  UI_SYSTEM_SECTIONID_MAX
};


enum UI_SYSTEM_BUTTONS
{
  UI_SYSTEM_BUTTON_ESC                      = 0 ,
  UI_SYSTEM_BUTTON_F5                           ,
  UI_SYSTEM_BUTTON_ZOOM_IN                      ,
  UI_SYSTEM_BUTTON_ZOOM_OUT                     ,
  UI_SYSTEM_BUTTON_ZOOM_OUT_MINUS               ,

  UI_SYSTEM_BUTTON_MOUSE                        ,

  UI_SYSTEM_BUTTON_TOUCHSCREEN                  ,

  UI_SYSTEM_BUTTON_MAX
};


#define XTHREADGROUPID_UI_SYSTEM_DRAWFRAME        XTHREADGROUPID_APPOWNER + 100
#define XTHREADGROUPID_UI_SYSTEM_HARDWAREINFO     static_cast<XTHREADGROUPID>(XTHREADGROUPID_APPOWNER + 101)

#define APPLICATION_VERSION                       2
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       _L("UI_System")
#define APPLICATION_NAMEFILE                      _L("ui_system")

#define APPLICATION_OWNER                         _L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2026


#define UI_SYSTEM_HARDWAREINFO_UPDATEPERIOD_SECONDS         1
#define UI_SYSTEM_CHART_REBUILD_PERIOD_SECONDS            2
#define UI_SYSTEM_DISK_SLOT_MAX                           16

#define UI_SYSTEM_CPUHISTORY_MAX                          30
#define UI_SYSTEM_RAMHISTORY_MAX                          30


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XTHREAD;
class XMUTEX;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class DIOINTERNET;
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERNETCONNECTION;
class GRPBITMAPSECUENCE;
class GRPXEVENT;
class GRPBITMAP;
class GRPBITMAPSEQUENCE;
class GRPVECTORFILESVG;
class INPBUTTON;
class INPCURSOR;
class UI_XEVENT;
class UI_ELEMENT;
class UI_ELEMENT_TEXT;
class UI_SYSTEM_CFG;

class UI_SYSTEM : public APPFLOWGRAPHICS, public XFSMACHINE
{
  public:
                                    UI_SYSTEM                               ();
    virtual                        ~UI_SYSTEM                               ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();
   
  private:
    
    bool                            UpdateInput                             ();

    bool                            Ini_Graphics                            (GRPSCREEN* screen);
    bool                            Ini_UserInterface                       (bool on);

    bool                            DrawFrame                               ();

    static void                     ThreadFunction_UpdateHardwareInfo       (void* param);

    bool                            HardwareInfo_Compute                    (bool forced);
    bool                            HardwareInfo_Apply                      ();
    bool                            HardwareInfo_RequestForced              ();

    bool                            HardwareInfo_UpdateCPU                  (XSTRING& outtemperature, float& outtemperaturelevel, float& outusagelevel);
    bool                            HardwareInfo_UpdateMemory               (XSTRING& outusedtotal, XSTRING& outused, XSTRING& outtotal, float& outusagelevel);
    bool                            HardwareInfo_UpdateVolumes              (XSTRING* outname, XSTRING* outused, XSTRING* outtotal, float* outusagelevel, int& outcount);
    bool                            HardwareInfo_PublishDiskSlot            ();
    bool                            HardwareInfo_CycleDisk                  (int delta);
    bool                            HardwareInfo_UpdateDateTime             (XSTRING& outdate, XSTRING& outtime);
    bool                            HardwareInfo_UpdateConnection           (bool& outisconnected, XSTRING& outstatus, XSTRING& outquality, XSTRING& outmark, XSTRING& outip, XSTRING& outpublicip);
    bool                            HardwareInfo_UpdateFooter               (XSTRING& outequipo, XSTRING& outso, XSTRING& outuptime);

    bool                            CpuHistoryChart_PushSample              (float cpuusagepercent);
    bool                            HistoryChart_Apply                      (bool forced = false);
    bool                            DashboardSlot_ApplySection              (UI_SYSTEM_SECTIONID sectionID);

    bool                            UserInterface_ElementSelected           (UI_ELEMENT* element);
    bool                            UserInterface_ChangeLiteralText         (UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresult);
    bool                            UserInterface_CFGChromes                (GRPSCREEN* screen);    

    bool                            UserInterface_SelectSection             (UI_SYSTEM_SECTIONID sectionID);
    bool                            UserInterface_AdjustUIScale             (double delta);

    void                            HandleEvent_UserInterface               (UI_XEVENT* event);
    void                            HandleEvent_Graphics                    (GRPXEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);
    
    void                            Clean                                   ();

    XTIMER*                         xtimer;

    INPBUTTON*                      button[UI_SYSTEM_BUTTON_MAX];
    INPCURSOR*                      cursor;

    DIOCHECKINTERNETCONNECTION*     diocheckinternetconnection;

    UI_SYSTEM_SECTIONID             currentsectionID;

    XQWORD                          lastupdatehardwareinfo_second;

    XTHREAD*                        hardwareinfothread;
    XMUTEX*                         hardwareinfomutex;

    bool                            hardwareinfoexiting;                     
    bool                            hardwareinfo_forcenext;                  
    bool                            hardwareinfo_haspending;                 

    float                           cpu_temperaturelevel;                    
    float                           cpu_usagelevel;                          
    float                           ram_usagelevel;
    float                           disk_usagelevel;
    float                           disk_slot_level[UI_SYSTEM_DISK_SLOT_MAX];
    int                             disk_slot_count;
    int                             disk_slot_index;
    bool                            isconnected;                             

    bool                            dashboardloaded;

    XSTRING                         cpu_temperature_str;
    XSTRING                         ram_used_total_str;
    XSTRING                         ram_used_str;
    XSTRING                         ram_total_str;
    XSTRING                         disk_slot_name[UI_SYSTEM_DISK_SLOT_MAX];
    XSTRING                         disk_slot_used[UI_SYSTEM_DISK_SLOT_MAX];
    XSTRING                         disk_slot_total[UI_SYSTEM_DISK_SLOT_MAX];
    XSTRING                         disk_used_str;
    XSTRING                         disk_total_str;
    XSTRING                         disk_caption_str;
    XSTRING                         disk_index_str;
    XSTRING                         system_date_str;
    XSTRING                         system_time_str;
    XSTRING                         connection_status_str;
    XSTRING                         connection_quality_str;
    XSTRING                         connection_mark_str;
    XSTRING                         local_ip_str;
    XSTRING                         public_ip_str;
    XSTRING                         footer_equipo_str;
    XSTRING                         footer_so_str;
    XSTRING                         footer_uptime_str;

    float                           cpuhistory_samples[UI_SYSTEM_CPUHISTORY_MAX];
    int                             cpuhistory_count;
    int                             cpuhistory_write;

    float                           ramhistory_samples[UI_SYSTEM_RAMHISTORY_MAX];
    int                             ramhistory_count;
    int                             ramhistory_write;

    XQWORD                          lastchartrebuild_second;
    bool                            chart_force_rebuild;

};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

