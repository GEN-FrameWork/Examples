/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro_Protocol_Device.cpp
*
* @class      BINCONNPRO_PROTOCOL_DEVICE
* @brief      Example Binary Connexion Protocol Device class
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

#include "BinConnPro_Protocol_Device.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_PROTOCOL_DEVICE::BINCONNPRO_PROTOCOL_DEVICE()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_PROTOCOL_DEVICE::BINCONNPRO_PROTOCOL_DEVICE()
{
  Clean();

   type = BINCONNPRO_PROTOCOL_DEVICETYPE_GENERIC;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_PROTOCOL_DEVICE::~BINCONNPRO_PROTOCOL_DEVICE()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_PROTOCOL_DEVICE::~BINCONNPRO_PROTOCOL_DEVICE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_PROTOCOL_DEVICETYPE BINCONNPRO_PROTOCOL_DEVICE::GetType()
* @brief      Gets the type.
* @ingroup    EXAMPLES
*
* @return     BINCONNPRO_PROTOCOL_DEVICETYPE : Requested value.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_PROTOCOL_DEVICETYPE BINCONNPRO_PROTOCOL_DEVICE::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO_PROTOCOL_DEVICE::SetType(BINCONNPRO_PROTOCOL_DEVICETYPE type)
* @brief      Sets the type.
* @ingroup    EXAMPLES
*
* @param[in]  type : Type value used by the operation.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO_PROTOCOL_DEVICE::SetType(BINCONNPRO_PROTOCOL_DEVICETYPE type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD BINCONNPRO_PROTOCOL_DEVICE::GetID()
* @brief      Gets the id.
* @ingroup    EXAMPLES
*
* @return     XDWORD : Requested value.
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD BINCONNPRO_PROTOCOL_DEVICE::GetID()
{
  return ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO_PROTOCOL_DEVICE::SetID(XDWORD ID)
* @brief      Sets the id.
* @ingroup    EXAMPLES
*
* @param[in]  ID : Id value used by the operation.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO_PROTOCOL_DEVICE::SetID(XDWORD ID)
{
  this->ID = ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_PROTOCOL_DEVICE::GetDeviceTypeInString(XSTRING& typestring)
* @brief      Gets the device type in string.
* @ingroup    EXAMPLES
*
* @param[in]  typestring : Typestring value used by the operation.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_PROTOCOL_DEVICE::GetDeviceTypeInString(XSTRING& typestring)
{
  typestring.Empty();

  switch(type)
    {
      case BINCONNPRO_PROTOCOL_DEVICETYPE_UNKNOWN : typestring = _L("Desconocido");     break;
      case BINCONNPRO_PROTOCOL_DEVICETYPE_GENERIC : typestring = _L("Generic");         break;
                                        default   : return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO_PROTOCOL_DEVICE::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO_PROTOCOL_DEVICE::Clean()
{
  type = BINCONNPRO_PROTOCOL_DEVICETYPE_UNKNOWN;
  ID   = 0;
}


