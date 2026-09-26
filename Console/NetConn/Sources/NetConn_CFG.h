/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_CFG.h
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

#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPFlowCFG.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define NETCONN_CFG_SECTION_GENERAL                           __L("general")

#define NETCONN_CFG_SECTION_CONNECTION                        __L("connection")
#define NETCONN_CFG_CONNECTION_ISSERVER                       __L("isserver")
#define NETCONN_CFG_CONNECTION_TRANSPORTTYPE                  __L("transporttype")
#define NETCONN_CFG_CONNECTION_TRANSPORTCONFIG                __L("transportconfig")

#define NETCONN_APPFLOW_CFG_DEFAULT_REMARK_COLUMN             98

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class NETCONN_CFG : public APPFLOWCFG
{
  public:

    static bool                     GetIsInstanced                    ();
    static NETCONN_CFG&             GetInstance                       (bool ini = true);
    static bool                     DelInstance                       ();

    bool                            DoVariableMapping                 (); 
    bool                            DoDefault                         ();

    bool                            Connection_IsServer               ();  
    XSTRING*                        Connection_GetTransportType       ();
    XSTRING*                        Connection_GetTransportConfig     ();
   
  private:
                                    NETCONN_CFG                       (XCHAR* namefile);
                                    NETCONN_CFG                       (NETCONN_CFG const&);        
    virtual                        ~NETCONN_CFG                       ();

    void                            operator =                        (NETCONN_CFG const&);        


    void                            Clean                             ();

    static NETCONN_CFG*             instance;

    bool                            connection_isserver;  
    XSTRING                         connection_transporttype;
    XSTRING                         connection_transportconfig;
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





