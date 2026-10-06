/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UI_Message_CFG.cpp
*
* @class      UI_MESSAGE_CFG
* @brief      GEN UI Message Config Example class
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

#include "UI_Message.h"

#include "UI_Message_CFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

UI_MESSAGE_CFG* UI_MESSAGE_CFG::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE_CFG::GetIsInstanced()
* @brief      Checks if the singleton instance is created.
* @ingroup    EXAMPLES
*
* @return     bool : true if the condition is met; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_MESSAGE_CFG& UI_MESSAGE_CFG::GetInstance(bool ini)
* @brief      Gets the singleton instance.
* @ingroup    EXAMPLES
*
* @param[in]  ini : true to initialize configuration from file; false to use the current values.
*
* @return     UI_MESSAGE_CFG& : Reference to the requested object.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_MESSAGE_CFG& UI_MESSAGE_CFG::GetInstance(bool ini)
{
  if(!instance) instance = GEN_NEW UI_MESSAGE_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE_CFG::DelInstance()
* @brief      Deletes the singleton instance.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE_CFG::DelInstance()
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
* @fn         bool UI_MESSAGE_CFG::DoVariableMapping()
* @brief      Maps configuration variables.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_MESSAGE_CFG::DoDefault()
* @brief      Loads default configuration values.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_MESSAGE_CFG::DoDefault()
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
* @fn         UI_MESSAGE_CFG::UI_MESSAGE_CFG(XCHAR* namefile)
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @param[in]  namefile : Configuration file name.
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_MESSAGE_CFG::UI_MESSAGE_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

  if(namefile)
    {
      Ini<UI_MESSAGE_CFG>();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_MESSAGE_CFG::~UI_MESSAGE_CFG()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_MESSAGE_CFG::~UI_MESSAGE_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_MESSAGE_CFG::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_MESSAGE_CFG::Clean()
{

}



