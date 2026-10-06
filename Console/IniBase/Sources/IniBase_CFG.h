/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       IniBase_CFG.h
* 
* @class      INIBASE_CFG
* @brief      Ini Base (Start to make GEN_NEW APP) (CFG class)
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

#define INIBASE_CFG_SECTION_GENERAL                           _L("general")

#define INIBASE_APPFLOW_CFG_DEFAULT_REMARK_COLUMN             98

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class INIBASE_CFG : public APPFLOWCFG
{
  public:

    static bool                     GetIsInstanced                    ();
    static INIBASE_CFG&             GetInstance                       (bool ini = true);
    static bool                     DelInstance                       ();

    bool                            DoVariableMapping                 (); 
    bool                            DoDefault                         ();

   
  private:
                                    INIBASE_CFG                       (XCHAR* namefile);
                                    INIBASE_CFG                       (INIBASE_CFG const&);        
    virtual                        ~INIBASE_CFG                       ();

    void                            operator =                        (INIBASE_CFG const&);        


    void                            Clean                             ();

    static INIBASE_CFG*             instance;
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





