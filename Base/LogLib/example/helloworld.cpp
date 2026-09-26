/**-------------------------------------------------------------------------------------------------------------------
*
* @file       helloworld.cpp
*
* @class      HELLOWORLD_CI
* @brief      Hello World Continuous Integration
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


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "helloworld.h"

#include <stdio.h>


#include "MainLibrary.h"
#include "XLog.h"



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/




/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int main()
* @brief      Application entry point.
* @ingroup    EXAMPLES
*
* @return     int : Process exit code.
*
*---------------------------------------------------------------------------------------------------------------------*/
int main()
{
  bool status;

  LIBRARY_Ini();

  status = GEN_XLOG.Ini(__L("helloword.log"), __L("helloword"), true);
  if(status)
    {       
  
      GEN_XLOG.SetLimit(XLOGTYPELIMIT_SIZE, 3000*1000, 10);
      GEN_XLOG.SetFilters(__L("GENERIC"), 0x000F);
      GEN_XLOG.SetBackup(true, 10, true);       
  
      GEN_XLOG.AddEntry(XLOGLEVEL_INFO, __L("GENERIC"), false, __L("Hello World!"));
        
      GEN_XLOG.End();
    }


  LIBRARY_End();
  
  return status;
}

