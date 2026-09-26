/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NotAppExample.cpp
* 
* @class      NOTAPPEXAMPLE
* @brief      Not Application Example (simple application without the GEN application class)
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

#include "NotAppExample.h"

#include <stdio.h>

#include "VersionFrameWork.h"

#include "XFactory.h"
#include "XSleep.h"
#include "XTrace.h"

#include "MainProc.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NOTAPPEXAMPLE::NOTAPPEXAMPLE()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NOTAPPEXAMPLE::NOTAPPEXAMPLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NOTAPPEXAMPLE::~NOTAPPEXAMPLE()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NOTAPPEXAMPLE::~NOTAPPEXAMPLE()

{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NOTAPPEXAMPLE::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NOTAPPEXAMPLE::Clean()
{
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool Proc_Main_Ini(MAINPROC* main)
* @brief      Initializes the main process.
* @ingroup    EXAMPLES
*
* @param[in]  main : Main process instance used by the callback.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool Proc_Main_Ini(MAINPROC* main)
{
  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)


  XTRACE_SETAPPLICATIONNAME(APPLICATION_NAMEAPP);
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);

  XTRACE_ADDTARGET(XTRACE_TYPE_NET, GEN_XTRACE_NET_DEFAULT_01);

  XTRACE_CLEARSCREEN;
  XTRACE_CLEARMSGSSTATUS;

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"), GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool Proc_Main_Update(MAINPROC* main)
* @brief      Updates the main process.
* @ingroup    EXAMPLES
*
* @param[in]  main : Main process instance used by the callback.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool Proc_Main_Update(MAINPROC* main)
{
  GEN_XSLEEP.Seconds(3);

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool Proc_Main_End(MAINPROC* main)
* @brief      Ends the main process.
* @ingroup    EXAMPLES
*
* @param[in]  main : Main process instance used by the callback.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool Proc_Main_End(MAINPROC* main)
{
  return true;
}



