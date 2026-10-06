/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UI_System_CFG.h
*
* @class      UI_SYSTEM_CFG
* @brief      GEN UI System Config Example class
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

#define UI_SYSTEMCFG_SECTIONGENERAL    _L("general")
#define UI_SYSTEMCFG_UISCALE           _L("uiscale")
#define UI_SYSTEMCFG_UISCALE_AUTOFIT   _L("uiscale_autofit")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class UI_SYSTEM_CFG : public APPFLOWCFG
{
  public:

    static bool                     GetIsInstanced                          ();
    static UI_SYSTEM_CFG&           GetInstance                             (bool ini = true);
    static bool                     DelInstance                             ();

    bool                            DoVariableMapping                       (); 
    bool                            DoDefault                               ();  

    float                           GetUIScale                              ();
    void                            SetUIScale                              (float scale);

    bool                            GetUIScaleAutofit                       ();
    void                            SetUIScaleAutofit                       (bool autofit);

  private:
                                    UI_SYSTEM_CFG                           (XCHAR* namefile);
                                    UI_SYSTEM_CFG                           (UI_SYSTEM_CFG const&);        
    virtual                        ~UI_SYSTEM_CFG                           ();

    void                            operator =                              (UI_SYSTEM_CFG const&);       

    void                            Clean                                   ();

    static UI_SYSTEM_CFG*           instance;

    float                           uiscale;
    bool                            uiscale_autofit;
};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/


