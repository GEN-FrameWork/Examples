/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_CFG.cpp
* 
* @class      NETCONN_CFG
* @brief      Net Connection CFG class (DIOCoreProtocol example)
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

#include "NetConn_CFG.h"

#include "XLog.h"

#include "NetConn.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

NETCONN_CFG* NETCONN_CFG::instance = NULL;



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_CFG::GetIsInstanced()
* @brief      Checks if the singleton instance is created.
* @ingroup    EXAMPLES
*
* @return     bool : true if the condition is met; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CFG& NETCONN_CFG::GetInstance(bool ini)
* @brief      Gets the singleton instance.
* @ingroup    EXAMPLES
*
* @param[in]  ini : true to initialize configuration from file; false to use the current values.
*
* @return     NETCONN_CFG& : Reference to the requested object.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_CFG& NETCONN_CFG::GetInstance(bool ini)
{
  if(!instance) instance = GEN_NEW NETCONN_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_CFG::DelInstance()
* @brief      Deletes the singleton instance.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CFG::DelInstance()
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
* @fn         bool NETCONN_CFG::DoVariableMapping()
* @brief      Maps configuration variables.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }

  //-----------------------------------------------------
  // Connection

  AddValue(XFILECFG_VALUETYPE_BOOLEAN, NETCONN_CFG_SECTION_CONNECTION, NETCONN_CFG_CONNECTION_ISSERVER, &connection_isserver, __L("Is server active"), APPFLOW_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING, NETCONN_CFG_SECTION_CONNECTION, NETCONN_CFG_CONNECTION_TRANSPORTTYPE, &connection_transporttype, __L("Transport type"), APPFLOW_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING, NETCONN_CFG_SECTION_CONNECTION, NETCONN_CFG_CONNECTION_TRANSPORTCONFIG, &connection_transportconfig, __L("Transport config"), APPFLOW_CFG_DEFAULT_REMARK_COLUMN);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_CFG::DoDefault()
* @brief      Loads default configuration values.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CFG::DoDefault()
{
  if(!APPFLOWCFG::DoDefault()) 
    {
      return false;
    }

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01

  //------------------------------------------------------------------------------

  connection_isserver         = true;  
  connection_transporttype    = __L("TCPIP");
  connection_transportconfig  = __L("192.168.1.3:1234");

  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_CFG::Connection_IsServer()
* @brief      Connection is server.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CFG::Connection_IsServer()
{
  return connection_isserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* NETCONN_CFG::Connection_GetTransportType()
* @brief      Connection get transport type.
* @ingroup    EXAMPLES
*
* @return     XSTRING* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* NETCONN_CFG::Connection_GetTransportType()
{
  return &connection_transporttype;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* NETCONN_CFG::Connection_GetTransportConfig()
* @brief      Connection get transport config.
* @ingroup    EXAMPLES
*
* @return     XSTRING* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* NETCONN_CFG::Connection_GetTransportConfig()
{
  return &connection_transportconfig;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CFG::NETCONN_CFG(XCHAR* namefile)
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @param[in]  namefile : Configuration file name.
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_CFG::NETCONN_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

 if(namefile)
   {
     Ini<NETCONN_CFG>();
   }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CFG::~NETCONN_CFG()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_CFG::~NETCONN_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN_CFG::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN_CFG::Clean()
{
  connection_isserver         = false;  
  connection_transporttype    = __L("");
  connection_transportconfig  = __L("");
}



