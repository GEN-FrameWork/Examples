/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       MemCtrlExample.h
* 
* @class      MEMCTRLEXAMPLE
* @brief      Memory Control Example
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

#include "XBuffer.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define APPLICATION_VERSION                   0
#define APPLICATION_SUBVERSION                0
#define APPLICATION_SUBVERSIONERR             1

#define APPLICATION_NAMEAPP                   __L("Memory Ctrl Example")
#define APPLICATION_NAMEFILE                  __L("memctrlexample")

#define APPLICATION_OWNER                     __L("GEN Framework")

#define APPLICATION_YEAROFCREATION            2023



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class MEMCTRLEXAMPLE
{
  public:
                        MEMCTRLEXAMPLE        ();
    virtual            ~MEMCTRLEXAMPLE        ();

  private:

    void                Clean                 ();
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/






