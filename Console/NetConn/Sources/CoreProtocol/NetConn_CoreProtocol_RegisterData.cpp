/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_CoreProtocol_RegisterData.cpp
* 
* @class      NETCONN_COREPROTOCOL_REGISTERDATA
* @brief      Net Connection Core Protocol Register Data class
* @ingroup    DATAIO
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

#include "NetConn_CoreProtocol_RegisterData.h"

#include "XSystem.h"

#include "HashSHA2.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_COREPROTOCOL_REGISTERDATA::NETCONN_COREPROTOCOL_REGISTERDATA()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_COREPROTOCOL_REGISTERDATA::NETCONN_COREPROTOCOL_REGISTERDATA()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_COREPROTOCOL_REGISTERDATA::~NETCONN_COREPROTOCOL_REGISTERDATA()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_COREPROTOCOL_REGISTERDATA::~NETCONN_COREPROTOCOL_REGISTERDATA()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_COREPROTOCOL_REGISTERDATA::InitializeData(bool isserver)
* @brief      Initialize data.
* @ingroup    EXAMPLES
*
* @param[in]  isserver : true when the connection manager works as server; false when it works as client.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COREPROTOCOL_REGISTERDATA::InitializeData(bool isserver)
{
  bool status = DIOCOREPROTOCOL_REGISTERDATA::InitializeData(isserver);

  if(isserver)
    {      
      group    = _L("Main Group");
      subgroup = _L("Sub Group");
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* NETCONN_COREPROTOCOL_REGISTERDATA::GetGroup()
* @brief      Gets the group.
* @ingroup    EXAMPLES
*
* @return     XSTRING* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* NETCONN_COREPROTOCOL_REGISTERDATA::GetGroup()
{
  return &group;
}
    

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* NETCONN_COREPROTOCOL_REGISTERDATA::GetSubGroup()
* @brief      Gets the sub group.
* @ingroup    EXAMPLES
*
* @return     XSTRING* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* NETCONN_COREPROTOCOL_REGISTERDATA::GetSubGroup()
{
  return &subgroup;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_COREPROTOCOL_REGISTERDATA::Serialize()
* @brief      Serializes the object data.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COREPROTOCOL_REGISTERDATA::Serialize()
{ 
  bool status = DIOCOREPROTOCOL_REGISTERDATA::Serialize();

  Primitive_Add<XSTRING*>(&group   , NETCONN_COREPROTOCOL_REGISTERDATA_HEADER_VAR_GROUP);  
  Primitive_Add<XSTRING*>(&subgroup, NETCONN_COREPROTOCOL_REGISTERDATA_HEADER_VAR_SUBGROUP);  

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_COREPROTOCOL_REGISTERDATA::Deserialize()
* @brief      Deserializes the object data.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COREPROTOCOL_REGISTERDATA::Deserialize()
{   
  bool status = DIOCOREPROTOCOL_REGISTERDATA::Deserialize();

  Primitive_Extract<XSTRING>(group   , NETCONN_COREPROTOCOL_REGISTERDATA_HEADER_VAR_GROUP);
  Primitive_Extract<XSTRING>(subgroup, NETCONN_COREPROTOCOL_REGISTERDATA_HEADER_VAR_SUBGROUP);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN_COREPROTOCOL_REGISTERDATA::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN_COREPROTOCOL_REGISTERDATA::Clean()
{
}




