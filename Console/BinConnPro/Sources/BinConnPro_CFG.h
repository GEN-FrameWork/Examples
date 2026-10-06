/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro_CFG.h
*
* @class      BINCONNPRO_CFG
* @brief      BinConnPro Configuration
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

#include "APPFlowCFG.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define BINCONNPRO_CFG_SECTION_PROTOCOL                            _L("protocol")
#define BINCONNPRO_CFG_PROTOCOL_ISACTIVE                           _L("isactive")
#define BINCONNPRO_CFG_PROTOCOL_ISLOCALENUMACTIVE                  _L("islocalenumactive")
#define BINCONNPRO_CFG_PROTOCOL_PORT                               _L("port")
#define BINCONNPRO_CFG_PROTOCOL_TARGET                             _L("target")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class BINCONNPRO_CFG : public APPFLOWCFG
{
  public:

    static bool                     GetIsInstanced                          ();
    static BINCONNPRO_CFG&          GetInstance                             (bool ini = true);
    static bool                     DelInstance                             ();

    bool                            DoVariableMapping                       (); 
    bool                            DoDefault                               ();

    bool                            Protocol_IsActive                       ();
    bool                            Protocol_IsLocalEnumActive              ();
    int                             Protocol_GetPort                        ();
    XSTRING*                        Protocol_GetTarget                      ();

  private:
                                    BINCONNPRO_CFG                          (XCHAR* namefile);
                                    BINCONNPRO_CFG                          (BINCONNPRO_CFG const&);        
    virtual                        ~BINCONNPRO_CFG                          ();

    void                            operator =                              (BINCONNPRO_CFG const&);        


    void                            Clean                                   ();

    static BINCONNPRO_CFG*          instance;

    bool                            protocol_isactive;
    bool                            protocol_islocalenumactive;
    int                             protocol_port;
    XSTRING                         protocol_target;

};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/



