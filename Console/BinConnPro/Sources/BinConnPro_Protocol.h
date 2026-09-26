/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro_Protocol.h
*
* @class      BINCONNPRO_PROTOCOL
* @brief      Example Binary Connexion Protocol Protocol class
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

#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOProtocol.h"
#include "BinConnPro_ApplicationData.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define BINCONNPRO_PROTOCOL_VERSION                       0
#define BINCONNPRO_PROTOCOL_SUBVERSION                      1
#define BINCONNPRO_PROTOCOL_SUBVERSIONERR                 0

#define BINCONNPRO_PROTOCOL_MAXMACHINESIDLIST             250

enum BINCONNPRO_PROTOCOL_CMDTYPE
{
  BINCONNPRO_PROTOCOL_CMDTYPE_NONE                          = DIOPROTOCOL_CMDTYPE_END                 ,

  BINCONNPRO_PROTOCOL_CMDTYPE_GETDEVICETYPEANDID            = BINCONNPRO_PROTOCOL_CMDTYPE_NONE +  100 ,
  BINCONNPRO_PROTOCOL_CMDTYPE_GETCENTERNAME                 = BINCONNPRO_PROTOCOL_CMDTYPE_NONE +  200 ,
  BINCONNPRO_PROTOCOL_CMDTYPE_GETLOCATION                   = BINCONNPRO_PROTOCOL_CMDTYPE_NONE +  300 ,

  BINCONNPRO_PROTOCOL_CMDTYPE_END
};

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class BINCONNPRO_PROTOCOL : public DIOPROTOCOL
{
  public:
                              BINCONNPRO_PROTOCOL               (DIOSTREAM* diostream);
     virtual                 ~BINCONNPRO_PROTOCOL               ();

     bool                     CMD_GetDeviceTypeAndID            (XDWORD& devicetype, XDWORD& deviceID);
     static int               RCV_GetDeviceTypeAndID            (DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param);

     bool                     CMD_GetCenterName                 (XSTRING& centername);
     static int               RCV_GetCenterName                 (DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param);

     bool                     CMD_GetLocation                   (XSTRING& street, XSTRING& city, XSTRING& region, XSTRING& country, XDWORD& postalcode);
     static int               RCV_GetLocation                   (DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param);

  private:

     void                     Clean                             ();
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/



