/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro_ConnectionsManager.h
*
* @class      BINCONNPRO_CONNECTIONSMANAGER
* @brief      Example Binary Connexion Protocol Connexions class
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

#include "XBase.h"

#include "DIOProtocol_ConnectionsManager.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define BINCONNPRO_CONNECTIONSMANAGER_CIPHERPROTOCOL
#define BINCONNPRO_CONNECTIONSMANAGER_LOCALENUMID          0xFAAF0FE0
#define BINCONNPRO_CONNECTIONSMANAGER_LOCALENUMPORT        4150
#define BINCONNPRO_CONNECTIONSMANAGER_PROTOCOLPORTBASE     14560
#define BINCONNPRO_CONNECTIONSMANAGER_PROTOCOLMASKID       0x02000000
#define BINCONNPRO_CONNECTIONSMANAGER_INIKEYENCRIPTION     { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F }
#define BINCONNPRO_CONNECTIONSMANAGER_KEYENCRIPTION        { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 }

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class CIPHER;
class DIOSTREAMUDPLOCALENUMSERVERS;
class DIOPROTOCOL;
class BINCONNPRO_APPLICATIONDATA;


class BINCONNPRO_CONNECTIONSMANAGER : public DIOPROTOCOL_CONNECTIONSMANAGER
{
  public:
                                        BINCONNPRO_CONNECTIONSMANAGER         ();
                                       ~BINCONNPRO_CONNECTIONSMANAGER         ();

    bool                                Ini                                   (bool isserver, bool isenumlocalactive, int port, BINCONNPRO_APPLICATIONDATA* applicationdata);
    int                                 ProtocolConnections_GetNConnected     ();
    DIOPROTOCOL_CONNECTION*             ProtocolConnections_GetByDIOStream    (DIOSTREAM* diostream);
    bool                                End                                   ();

    DIOPROTOCOL*                        CreateProtocol                        ();
    bool                                DeleteProtocol                        (DIOPROTOCOL* protocol);

  private:

    void                                Clean                                 ();


    bool                                isenumlocalactive;
    BINCONNPRO_APPLICATIONDATA*         applicationdata;
    DIOSTREAMUDPLOCALENUMSERVERS*       diostreamudplocalenumservers;
    DIOSTREAMTCPIPCONFIG*               diostreamTCPIPcfg;
};

/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/




