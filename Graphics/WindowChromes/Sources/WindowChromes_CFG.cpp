/**-------------------------------------------------------------------------------------------------------------------
*
* @file       WindowChromes_CFG.cpp
*
* @class      WINDOWCHROMES_CFG
* @brief      GEN UI Options Config Example class
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XLog.h"

#include "WindowChromes.h"

#include "WindowChromes_CFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

WINDOWCHROMES_CFG* WINDOWCHROMES_CFG::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES_CFG::GetIsInstanced()
* @brief      Checks if the singleton instance is created.
* @ingroup    EXAMPLES
*
* @return     bool : true if the condition is met; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         WINDOWCHROMES_CFG& WINDOWCHROMES_CFG::GetInstance(bool ini)
* @brief      Gets the singleton instance.
* @ingroup    EXAMPLES
*
* @param[in]  ini : true to initialize configuration from file; false to use the current values.
*
* @return     WINDOWCHROMES_CFG& : Reference to the requested object.
*
*---------------------------------------------------------------------------------------------------------------------*/
WINDOWCHROMES_CFG& WINDOWCHROMES_CFG::GetInstance(bool ini)
{
  if(!instance) instance = GEN_NEW WINDOWCHROMES_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES_CFG::DelInstance()
* @brief      Deletes the singleton instance.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES_CFG::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES_CFG::DoVariableMapping()
* @brief      Maps configuration variables.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWCHROMES_CFG::DoDefault()
* @brief      Loads default configuration values.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWCHROMES_CFG::DoDefault()
{
  if(!APPFLOWCFG::DoDefault()) 
    {
      return false;
    }

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01
  
  //------------------------------------------------------------------------------

  log_isactive                            = true;
  log_backupisactive                      = true;
  log_backupmaxfiles                      = 10;
  log_backupiscompress                    = true;

  log_activesectionsID.Empty();

  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_INITIATION;
  log_activesectionsID                  += _L(",");
  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_GENERIC;
  log_activesectionsID                  += _L(",");
  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_STATUSAPP;
  log_activesectionsID                  += _L(",");
  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_ENDING;

  log_levelmask                         = XLOGLEVEL_ALL;
  log_maxsize                           = 3000;
  log_reductionpercent                  = 10;

  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         WINDOWCHROMES_CFG::WINDOWCHROMES_CFG(XCHAR* namefile)
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @param[in]  namefile : Configuration file name.
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
WINDOWCHROMES_CFG::WINDOWCHROMES_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

  if(namefile)
    {
      Ini<WINDOWCHROMES_CFG>();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         WINDOWCHROMES_CFG::~WINDOWCHROMES_CFG()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
WINDOWCHROMES_CFG::~WINDOWCHROMES_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void WINDOWCHROMES_CFG::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void WINDOWCHROMES_CFG::Clean()
{

}



