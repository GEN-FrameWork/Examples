/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro_Protocol.cpp
*
* @class      BINCONNPRO_PROTOCOL
* @brief      Example Binary Connexion Protocol class
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

#include "XFactory.h"
#include "XVariant.h"

#include "BinConnPro_Protocol.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_PROTOCOL::BINCONNPRO_PROTOCOL(DIOSTREAM* diostream)
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @param[in]  diostream : Stream used by the protocol.
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_PROTOCOL::BINCONNPRO_PROTOCOL(DIOSTREAM* diostream) : DIOPROTOCOL(diostream)
{
  AddCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETDEVICETYPEANDID, __L(""), __L("DD"), RCV_GetDeviceTypeAndID, __L("GetDeviceTypeAndID"));
  AddCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETCENTERNAME, __L(""), __L("S"), RCV_GetCenterName, __L("GetCenterName"));
  AddCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETLOCATION, __L(""), __L("SSSSD"), RCV_GetLocation, __L("GetLocation"));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_PROTOCOL::~BINCONNPRO_PROTOCOL()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_PROTOCOL::~BINCONNPRO_PROTOCOL()
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_PROTOCOL::CMD_GetDeviceTypeAndID(XDWORD& devicetype, XDWORD& deviceID)
* @brief      Sends the get device type and id command.
* @ingroup    EXAMPLES
*
* @param[out]  devicetype : Output device type value.
* @param[out]  deviceID : Output device identifier value.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_PROTOCOL::CMD_GetDeviceTypeAndID(XDWORD& devicetype, XDWORD& deviceID)
{
  DIOPROTOCOL_COMMAND* cmd = GetCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETDEVICETYPEANDID);
  if(!cmd) return false;

  XBUFFER xbuffer;
  bool    result = false;

  if(Command(cmd->GetType(), xbuffer))
    {
      xbuffer.GetWithMask(cmd->GetSOUTMask(), 0, &devicetype, &deviceID);
      result = true;
    }

  SendEventCommand(this, DIOPROTOCOL_DIRECTION_GET, cmd->GetType(), result, NULL, 0);

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int BINCONNPRO_PROTOCOL::RCV_GetDeviceTypeAndID(DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param)
* @brief      Receives the get device type and id command response.
* @ingroup    EXAMPLES
*
* @param[in]  protocol : Protocol instance used by the operation.
* @param[in]  cmd : Protocol command associated with the operation.
* @param[in,out]  xbuffer : Buffer that contains the command data.
* @param[in]  rID : Request identifier associated with the command.
* @param[out]  param : Auxiliary protocol parameter.
*
* @return     int : Requested value.
*
*---------------------------------------------------------------------------------------------------------------------*/
int BINCONNPRO_PROTOCOL::RCV_GetDeviceTypeAndID(DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param)
{
  if(!protocol) return 0;

  BINCONNPRO_APPLICATIONDATA* applicationdata =   (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
  if(!applicationdata) return DIOPROTOCOL_ERRORRECEIVED;

  xbuffer.Delete();

  XDWORD devicetype = (XDWORD)applicationdata->device.GetType();
  XDWORD deviceID   = (XDWORD)applicationdata->device.GetID();

  return xbuffer.AddWithMask(cmd->GetSOUTMask(), devicetype, deviceID);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_PROTOCOL::CMD_GetCenterName(XSTRING& centername)
* @brief      Sends the get center name command.
* @ingroup    EXAMPLES
*
* @param[out]  centername : Output center name value.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_PROTOCOL::CMD_GetCenterName(XSTRING& centername)
{
  DIOPROTOCOL_COMMAND* cmd = GetCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETCENTERNAME);
  if(!cmd) return false;

  XBUFFER xbuffer;
  bool    result = false;

  if(Command(cmd->GetType(), xbuffer))
    {
      xbuffer.GetWithMask(cmd->GetSOUTMask(), 0, &centername);
      result = true;
    }

  SendEventCommand(this, DIOPROTOCOL_DIRECTION_GET, cmd->GetType(), result, NULL, 0);

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int BINCONNPRO_PROTOCOL::RCV_GetCenterName(DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param)
* @brief      Receives the get center name command response.
* @ingroup    EXAMPLES
*
* @param[in]  protocol : Protocol instance used by the operation.
* @param[in]  cmd : Protocol command associated with the operation.
* @param[in,out]  xbuffer : Buffer that contains the command data.
* @param[in]  rID : Request identifier associated with the command.
* @param[out]  param : Auxiliary protocol parameter.
*
* @return     int : Requested value.
*
*---------------------------------------------------------------------------------------------------------------------*/
int BINCONNPRO_PROTOCOL::RCV_GetCenterName(DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param)
{
  if(!protocol) return 0;

  BINCONNPRO_APPLICATIONDATA* applicationdata =   (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
  if(!applicationdata) return DIOPROTOCOL_ERRORRECEIVED;

  xbuffer.Delete();
  return xbuffer.AddWithMask(cmd->GetSOUTMask(), &applicationdata->centername);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_PROTOCOL::CMD_GetLocation(XSTRING& street, XSTRING& city, XSTRING& state, XSTRING& country, XDWORD& postalcode)
* @brief      Sends the get location command.
* @ingroup    EXAMPLES
*
* @param[out]  street : Output street value.
* @param[out]  city : Output city value.
* @param[out]  state : Output state value.
* @param[out]  country : Output country value.
* @param[out]  postalcode : Output postal code value.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_PROTOCOL::CMD_GetLocation(XSTRING& street, XSTRING& city, XSTRING& state, XSTRING& country, XDWORD& postalcode)
{
  DIOPROTOCOL_COMMAND* cmd = GetCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETLOCATION);
  if(!cmd) return false;

  XBUFFER xbuffer;
  bool    result = false;

  if(Command(cmd->GetType(), xbuffer))
    {
      xbuffer.GetWithMask(cmd->GetSOUTMask(), 0, &street, &city, &state, &country, &postalcode);
      result = true;
    }

  SendEventCommand(this, DIOPROTOCOL_DIRECTION_GET, cmd->GetType(), result, NULL, 0);

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int BINCONNPRO_PROTOCOL::RCV_GetLocation(DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param)
* @brief      Receives the get location command response.
* @ingroup    EXAMPLES
*
* @param[in]  protocol : Protocol instance used by the operation.
* @param[in]  cmd : Protocol command associated with the operation.
* @param[in,out]  xbuffer : Buffer that contains the command data.
* @param[in]  rID : Request identifier associated with the command.
* @param[out]  param : Auxiliary protocol parameter.
*
* @return     int : Requested value.
*
*---------------------------------------------------------------------------------------------------------------------*/
int BINCONNPRO_PROTOCOL::RCV_GetLocation(DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param)
{
  if(!protocol) return 0;

  BINCONNPRO_APPLICATIONDATA* applicationdata =   (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
  if(!applicationdata) return DIOPROTOCOL_ERRORRECEIVED;

  xbuffer.Delete();
  return xbuffer.AddWithMask(cmd->GetSOUTMask(), applicationdata->location.GetStreet(), applicationdata->location.GetCity(), applicationdata->location.GetState(), applicationdata->location.GetCountry(), applicationdata->location.GetPostalCode());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO_PROTOCOL::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO_PROTOCOL::Clean()
{

}


