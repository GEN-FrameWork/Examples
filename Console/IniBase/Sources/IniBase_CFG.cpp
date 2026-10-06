/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       IniBase_CFG.cpp
* 
* @class      INIBASE_CFG
* @brief      Ini Base (Start to make GEN_NEW APP) (CFG class)
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

#include "IniBase_CFG.h"

#include "XLog.h"

#include "IniBase.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

INIBASE_CFG* INIBASE_CFG::instance = NULL;



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INIBASE_CFG::GetIsInstanced()
* @brief      Checks if the singleton instance is created.
* @ingroup    EXAMPLES
*
* @return     bool : true if the condition is met; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INIBASE_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INIBASE_CFG& INIBASE_CFG::GetInstance(bool ini)
* @brief      Gets the singleton instance.
* @ingroup    EXAMPLES
*
* @param[in]  ini : true to initialize configuration from file; false to use the current values.
*
* @return     INIBASE_CFG& : Reference to the requested object.
*
*---------------------------------------------------------------------------------------------------------------------*/
INIBASE_CFG& INIBASE_CFG::GetInstance(bool ini)
{
  if(!instance) instance = GEN_NEW INIBASE_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INIBASE_CFG::DelInstance()
* @brief      Deletes the singleton instance.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INIBASE_CFG::DelInstance()
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
* @fn         bool INIBASE_CFG::DoVariableMapping()
* @brief      Maps configuration variables.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INIBASE_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }

  //-----------------------------------------------------
  // Connection

  //AddValue(XFILECFG_VALUETYPE_BOOLEAN   , INIBASE_CFG_SECTION_CONNECTION        , INIBASE_CFG_CONNECTION_ISSERVER                , &connection_isserver                                 , _L("Is server active")                                                                 , APPFLOW_CFG_DEFAULT_REMARK_COLUMN);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INIBASE_CFG::DoDefault()
* @brief      Loads default configuration values.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INIBASE_CFG::DoDefault()
{
  if(!APPFLOWCFG::DoDefault()) 
    {
      return false;
    }

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01
  
  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INIBASE_CFG::INIBASE_CFG(XCHAR* namefile)
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @param[in]  namefile : Configuration file name.
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
INIBASE_CFG::INIBASE_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

 if(namefile)
   {
     Ini<INIBASE_CFG>();
   }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INIBASE_CFG::~INIBASE_CFG()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
INIBASE_CFG::~INIBASE_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INIBASE_CFG::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INIBASE_CFG::Clean()
{

}



