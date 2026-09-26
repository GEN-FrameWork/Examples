/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetCapture_Sniffer.h
* 
* @class      NETCAPTURE_SNIFFER
* @brief      Net Capture Sniffer class
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

#include "XVector.h"
#include "XBuffer.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTHREAD;
class DIOPCAP;

class NETCAPTURE_FRAME
{
  public:
                                          NETCAPTURE_FRAME              ();
    virtual                              ~NETCAPTURE_FRAME              ();

    bool                                  IsSend                        ();  
    void                                  SetIsSend                     (bool issend);  

    XBUFFER*                              GetPayLoadBuffer              ();

  private:

    void                                  Clean                         ();

    bool                                  issend;  
    XBUFFER                               payloadbuffer;

};

class NETCAPTURE_SNIFFER
{
  public:
                                          NETCAPTURE_SNIFFER            ();
    virtual                              ~NETCAPTURE_SNIFFER            ();

    bool                                  Capture_Ini                   ();
    bool                                  Capture_Manager               ();  
    bool                                  Capture_End                   ();

    DIOPCAP*                              GetDIOPCap                    ();
    
    bool                                  Sniffer_Add                   (bool issend, XBYTE* framedata, XDWORD framesize);
    NETCAPTURE_FRAME*                     Sniffer_Get                   (int index); 
    bool                                  Sniffer_Del                   (int index);
    bool                                  Sniffer_DelAll                ();
    XVECTOR<NETCAPTURE_FRAME*>*           Sniffer_Get                   (); 
    bool                                  Sniffer_Interpreter           (NETCAPTURE_FRAME* pulsarframe); 

    
  private:

    void                                  Clean                         ();
    
    static void                           ThreadRunFunctionSniffer      (void* param);
    static void                           ThreadRunFunctionManager      (void* param);

    DIOPCAP*                              diopcap; 
    XTHREAD*                              threadsniffer;
    XTHREAD*                              threadmanager;
    XMUTEX*                               framesmutex;    
    XVECTOR<NETCAPTURE_FRAME*>            frames;

};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/






