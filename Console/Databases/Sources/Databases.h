/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Databases.h
* 
* @class      DATABASES
* @brief      Example Databases class
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

#include "DB_SQL_Factory.h"
#include "DB_SQL_Database.h"

#include "APPFlowConsole.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DATABASESXFSMEVENTS
{
  DATABASES_XFSMEVENT_NONE              = 0 ,
  DATABASES_XFSMEVENT_INI                   ,
  DATABASES_XFSMEVENT_END                   ,

  DATABASES_LASTEVENT
};


enum DATABASESXFSMSTATES
{
  DATABASES_XFSMSTATE_NONE              = 0 ,
  DATABASES_XFSMSTATE_INI                   ,
  DATABASES_XFSMSTATE_END                   ,

  DATABASES_LASTSTATE
};


enum DATABASESTASKID
{
  DATABASESTASKID_UNKNOWN                 = 0 ,
  DATABASESTASKID_CHECKMEMORYSTATUS           ,
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("Databases")
#define APPLICATION_NAMEFILE                      __L("databases")

#define APPLICATION_OWNER                         __L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2018

#define DATABASES_TABLE_TEST_NAME                 __L("TableTest")
#define DATABASES_TABLE_MAXFIELDS                 16

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class DIOINTERNET;
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERNETCONNECTION;
class DIOSCRAPERWEBPUBLICIP;
class DIOSCRAPERWEBUSERAGENTID;

class DATABASES : public APPFLOWCONSOLE, public XFSMACHINE
{
  public:
                                    DATABASES                               ();
    virtual                        ~DATABASES                               ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();

    bool                            KeyValidSecuences                       (int key);

    bool                            DataBase_ChangeType                     (DB_SQL_DATABASE_TYPE type);
    bool                            Database_DoTest                         ();

    bool                            Show_AppStatus                          ();
    bool                            Show_DatabasesStatus                    ();
    bool                            Show_AllStatus                          ();

  private:

    void                            HandleEvent                             (XEVENT* xevent);

    void                            Clean                                   ();

    XTIMER*                         xtimerupdateconsole;
    XMUTEX*                         xmutexshowallstatus;

    DB_SQL_DATABASE*                database;
};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





