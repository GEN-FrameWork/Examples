/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Databases_CFG.cpp
* 
* @class      DATABASES_CFG
* @brief      Example Databases Config class
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

#include "Databases_CFG.h"

#include "XLog.h"

#include "Databases.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

DATABASES_CFG* DATABASES_CFG::instance = NULL;



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DATABASES_CFG::GetIsInstanced()
* @brief      Checks if the singleton instance is created.
* @ingroup    EXAMPLES
*
* @return     bool : true if the condition is met; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DATABASES_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DATABASES_CFG& DATABASES_CFG::GetInstance(bool ini)
* @brief      Gets the singleton instance.
* @ingroup    EXAMPLES
*
* @param[in]  ini : true to initialize configuration from file; false to use the current values.
*
* @return     DATABASES_CFG& : Reference to the requested object.
*
*---------------------------------------------------------------------------------------------------------------------*/
DATABASES_CFG& DATABASES_CFG::GetInstance(bool ini)
{
  if(!instance) instance = GEN_NEW DATABASES_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DATABASES_CFG::DelInstance()
* @brief      Deletes the singleton instance.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DATABASES_CFG::DelInstance()
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
* @fn         bool DATABASES_CFG::DoVariableMapping()
* @brief      Maps configuration variables.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DATABASES_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }

  //-----------------------------------------------------
  // DATABASE

  AddValue(XFILECFG_VALUETYPE_STRING, DATABASESCFG_SECTION_DATABASE, DATABASESCFG_DATABASE_URL, &db_URL);
  AddValue(XFILECFG_VALUETYPE_INT, DATABASESCFG_SECTION_DATABASE, DATABASESCFG_DATABASE_PORT, &db_port);
  AddValue(XFILECFG_VALUETYPE_STRING, DATABASESCFG_SECTION_DATABASE, DATABASESCFG_DATABASE_DATABASENAME, &db_databasename);
  AddValue(XFILECFG_VALUETYPE_STRING, DATABASESCFG_SECTION_DATABASE, DATABASESCFG_DATABASE_USER, &db_user);
  AddValue(XFILECFG_VALUETYPE_STRING, DATABASESCFG_SECTION_DATABASE, DATABASESCFG_DATABASE_PASSWORD, &db_password);
  AddValue(XFILECFG_VALUETYPE_INT, DATABASESCFG_SECTION_DATABASE, DATABASESCFG_DATABASE_TIMEOUTCONNECTION, &db_timeoutconnection);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DATABASES_CFG::DoDefault()
* @brief      Loads default configuration values.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DATABASES_CFG::DoDefault()
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

  db_URL                                = _L("");
  db_port                               = 0;
  db_databasename                       = _L("");
  db_user                               = _L("");
  db_password                           = _L("");
  db_timeoutconnection                  = 30;

  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DATABASES_CFG::Database_GetURL()
* @brief      Gets the database url.
* @ingroup    EXAMPLES
*
* @return     XSTRING* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DATABASES_CFG::Database_GetURL()
{
  return &db_URL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DATABASES_CFG::Database_GetPort()
* @brief      Gets the database port.
* @ingroup    EXAMPLES
*
* @return     XDWORD : Requested value.
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DATABASES_CFG::Database_GetPort()
{
  return db_port;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DATABASES_CFG::Database_DatabaseName()
* @brief      Database database name.
* @ingroup    EXAMPLES
*
* @return     XSTRING* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DATABASES_CFG::Database_DatabaseName()
{
  return &db_databasename;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DATABASES_CFG::Database_GetUser()
* @brief      Gets the database user.
* @ingroup    EXAMPLES
*
* @return     XSTRING* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DATABASES_CFG::Database_GetUser()
{
  return &db_user;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DATABASES_CFG::Database_GetPassword()
* @brief      Gets the database password.
* @ingroup    EXAMPLES
*
* @return     XSTRING* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DATABASES_CFG::Database_GetPassword()
{
  return &db_password;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DATABASES_CFG::Database_GetTimeoutConnection()
* @brief      Gets the database timeout connection.
* @ingroup    EXAMPLES
*
* @return     int : Requested value.
*
*---------------------------------------------------------------------------------------------------------------------*/
int DATABASES_CFG::Database_GetTimeoutConnection()
{
  return db_timeoutconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DATABASES_CFG::DATABASES_CFG(XCHAR* namefile)
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @param[in]  namefile : Configuration file name.
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
DATABASES_CFG::DATABASES_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

  if(namefile)
    {
      Ini<DATABASES_CFG>();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DATABASES_CFG::~DATABASES_CFG()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
DATABASES_CFG::~DATABASES_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DATABASES_CFG::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DATABASES_CFG::Clean()
{

}



