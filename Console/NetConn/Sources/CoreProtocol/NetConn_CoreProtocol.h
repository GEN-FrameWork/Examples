/**-------------------------------------------------------------------------------------------------------------------
*
* @file       NetConn_CoreProtocol.h
*
* @class      NETCONN_COREPROTOCOL
* @brief      Net Connection Core Protocol class (DIOCoreProtocol example)
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

#pragma once

/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_CoreProtocol.h
* 
* @class      NETCONN_COREPROTOCOL
* @brief      Net Connection Core Protocol class (DIOCoreProtocol example)
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

#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOCoreProtocol.h"

#include "CipherAES.h"

 

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define NETCONN_COREPROTOCOL_AUTHENTICATION_INI       { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F }
#define NETCONN_COREPROTOCOL_AUTHENTICATION_KEY       { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 }
#define NETCONN_COREPROTOCOL_MAXCHALLANGE             64
#define NETCONN_COREPROTOCOL_VERSION                  1
#define NETCONN_COREPROTOCOL_SUBVERSION               0

enum NETCONN_COREPROTOCOL_COMMAND_TYPE
{
  NETCONN_COREPROTOCOL_COMMAND_TYPE_GETVERSION         = DIOCOREPROTOCOL_COMMAND_TYPE_LASTINTERNAL ,
  NETCONN_COREPROTOCOL_COMMAND_TYPE_OTHERCOMMAND                                                   ,
};


#define NETCONN_COREPROTOCOL_COMMAND_TYPE_STRING_GETVERSION       _L("getversion")
#define NETCONN_COREPROTOCOL_COMMAND_TYPE_STRING_OTHERCOMMAND     _L("othercommand")



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOCOREPROTOCOL_CFG; 
class DIOSTREAM;

class NETCONN_COREPROTOCOL : public DIOCOREPROTOCOL
{
  public:
                       NETCONN_COREPROTOCOL                 (DIOCOREPROTOCOL_CFG* protocolCFG, DIOSTREAM* diostream);
    virtual           ~NETCONN_COREPROTOCOL                 ();

    bool               GenerateAuthenticationChallenge      (XBUFFER& autentication_challange);
    bool               GenerateAuthenticationResponse       (XBUFFER& autentication_challange, XBUFFER& autentication_response);
    
  private:

    void               Clean                                ();

    CIPHERAES          cipherAES; 
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/






