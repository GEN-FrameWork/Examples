/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_TestUpdateClass.cpp
* 
* @class      NETCONN_TESTUPDATECLASS
* @brief      Net Conn Test Update Class
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

#include "NetConn_TestUpdateClass.h"

#include "XFactory.h"
#include "XRand.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_TESTUPDATECLASS::NETCONN_TESTUPDATECLASS()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_TESTUPDATECLASS::NETCONN_TESTUPDATECLASS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_TESTUPDATECLASS::~NETCONN_TESTUPDATECLASS()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_TESTUPDATECLASS::~NETCONN_TESTUPDATECLASS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD NETCONN_TESTUPDATECLASS::GetNumber()
* @brief      Gets the number.
* @ingroup    EXAMPLES
*
* @return     XDWORD : Requested value.
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD NETCONN_TESTUPDATECLASS::GetNumber()
{
  return number;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN_TESTUPDATECLASS::SetNumber(XDWORD number)
* @brief      Sets the number.
* @ingroup    EXAMPLES
*
* @param[in]  number : Number value to set.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN_TESTUPDATECLASS::SetNumber(XDWORD number)
{
  this->number = number;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* NETCONN_TESTUPDATECLASS::GetString()
* @brief      Gets the string.
* @ingroup    EXAMPLES
*
* @return     XSTRING* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* NETCONN_TESTUPDATECLASS::GetString()
{
  return &string;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_TESTUPDATECLASS::Update()
* @brief      Updates the object data.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_TESTUPDATECLASS::Update()
{
  XRAND* rand = GEN_XFACTORY.CreateRand();
  if(rand)
    {
      rand->Ini();

      number = rand->Between(0, 1024);

      switch(rand->Between(0, 3))
        {              
          case  0 : string = _L("hello, how are you?");    break;
          case  1 : string = _L("hello, Tests 1");         break;
          case  2 : string = _L("hello, Tests 2");         break;
          case  3 : string = _L("hello, Tests 3");         break;        
        }

      GEN_XFACTORY.DeleteRand(rand);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_TESTUPDATECLASS::Serialize()
* @brief      Serializes the object data.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_TESTUPDATECLASS::Serialize()
{
  Primitive_Add<XDWORD>(number    , NETCONN_TESTUPDATECLASS_NUMBER_STR);  
  Primitive_Add<XSTRING*>(&string  , NETCONN_TESTUPDATECLASS_STRING_STR);  

  return true;
}
    

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_TESTUPDATECLASS::Deserialize()
* @brief      Deserializes the object data.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_TESTUPDATECLASS::Deserialize()
{
  Primitive_Extract<XDWORD>(number   , NETCONN_TESTUPDATECLASS_NUMBER_STR);
  Primitive_Extract<XSTRING>(string  , NETCONN_TESTUPDATECLASS_STRING_STR);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN_TESTUPDATECLASS::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN_TESTUPDATECLASS::Clean()
{
  number = 0;  
}




