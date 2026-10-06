/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_TestUpdateClass.h
* 
* @class      NETCONN_TESTUPDATECLASS
* @brief      Net Conn Test Update Class
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

#include "XString.h"
#include "XSerializable.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define NETCONN_TESTUPDATECLASS_NUMBER_STR    _L("number") 
#define NETCONN_TESTUPDATECLASS_STRING_STR    _L("string")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class NETCONN_TESTUPDATECLASS : public XSERIALIZABLE
{
  public:
                    NETCONN_TESTUPDATECLASS           ();
    virtual        ~NETCONN_TESTUPDATECLASS           ();

    XDWORD          GetNumber                         ();
    void            SetNumber                         (XDWORD number);

    XSTRING*        GetString                         ();

    bool            Update                            ();  
  
    bool            Serialize                         ();    
    bool            Deserialize                       ();  

  private:
  
    void            Clean                             ();

    XDWORD          number;
    XSTRING         string;
};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/















