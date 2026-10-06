/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Canvas2DDisplay.cpp
* 
* @class      CANVAS2DDISPLAY
* @brief      Canvas 2D Display example class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "Canvas2DDisplay.h"

#include <stdio.h>

#include "VersionFrameWork.h"

#include "XFactory.h"
#include "XSleep.h"
#include "XRand.h"
#include "XTrace.h"

#include "DIOFactory.h"
#include "DIOGPIO.h"
#include "DIOStreamUARTConfig.h"
#include "DIOStreamUART.h"
#include "DIOStreamUSBConfig.h"
#include "DIOStreamUSB.h"
#include "DIOStreamI2CConfig.h"
#include "DIOStreamI2C.h"
#include "DIOStreamSPIConfig.h"
#include "DIOStreamSPI.h"
#include "DIOGPIO.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(CANVAS2DDISPLAY, uart_usb)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2DDISPLAY::CANVAS2DDISPLAY()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
CANVAS2DDISPLAY::CANVAS2DDISPLAY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2DDISPLAY::~CANVAS2DDISPLAY()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
CANVAS2DDISPLAY::~CANVAS2DDISPLAY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2DDISPLAY::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2DDISPLAY::AppProc_Ini()
{
  XSTRING string;

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  string = APPLICATION_NAMEAPP;
  XTRACE_SETAPPLICATIONNAME(string);
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);

  #ifdef MICROCONTROLLER
    XTRACE_SETTARGET(0, XTRACE_TYPE_SPECIAL , XTRACE_DEFAULT_SPECIALAIM);
  #else
    XTRACE_SETTARGET(0, XTRACE_TYPE_NET, GEN_XTRACE_NET_DEFAULT_01);
  #endif

  XTRACE_PRINTCOLOR(1, _L("Start Application"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2DDISPLAY::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2DDISPLAY::AppProc_FirstUpdate()
{
  //Test_DIOStreamI2C();
  Test_DIOStreamSPI();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2DDISPLAY::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2DDISPLAY::AppProc_Update()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2DDISPLAY::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2DDISPLAY::AppProc_End()
{

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2DDISPLAY::Test_DIOStreamI2C()
* @brief      Runs the I2C stream test.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2DDISPLAY::Test_DIOStreamI2C()
{
  //----------------------------------------------------------------------------

  /*
  DIOI2COLEDSCREENSSD1306* screenOLEDSSD1306 = GEN_NEW DIOI2COLEDSCREENSSD1306();
  if(!screenOLEDSSD1306) return false;

  if(screenOLEDSSD1306->Ini(1, 0x78, 10))
    {
      XTRACE_PRINTCOLOR(2, _L("Connect I2C device... Ok!"));

      screenOLEDSSD1306->End();

    } else XTRACE_PRINTCOLOR(2,_L("Error to connect I2C device..."));

  */

  //----------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2DDISPLAY::Test_DIOStreamSPI()
* @brief      Runs the SPI stream test.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2DDISPLAY::Test_DIOStreamSPI()
{
  bool status = false;

  /*
  //----------------------------------------------------------------------------

  DIOGPIO* diogpio = GEN_DIOFACTORY.CreateGPIO();
  if(diogpio)
    {
      if(diogpio->Ini())
        {
          DIOSPILCDSCREENPCF8833* lcdscreen = GEN_NEW DIOSPILCDSCREENPCF8833();
          if(lcdscreen)
            {
              lcdscreen->SetDIOGPIO(diogpio);
              lcdscreen->SetResetPinsGroup(DIOGPIO_PINSGROUP_A);
              lcdscreen->SetResetPin(TEST_PINLCD_RESET);

              status  = lcdscreen->Ini(1, 0, 10);
              XTRACE_PRINTCOLOR(1, _L("Send screen INI   : %s "), status?_L("Ok!"):_L("Error!"));
              if(status)
                {

                  //status = lcdscreen->Clear(DIOSPILCDSCREENPHILIPSPCF8833_RED);
                  //XDEBUG_PRINTCOLOR(1, _L("Send screen Clean : %s "), status?_L("Ok!"):_L("Error!"));

                  //GEN_XSLEEP.Seconds(1);
                  if(status)
                    {
                      //status = lcdscreen->Clear(DIOSPILCDSCREENPHILIPSPCF8833_GREEN);
                      //XDEBUG_PRINTCOLOR(1, _L("Send screen Clean : %s "), status?_L("Ok!"):_L("Error!"));

                      //GEN_XSLEEP.Seconds(1);

                      if(status)
                        {
                          //status = lcdscreen->Clear(DIOSPILCDSCREENPHILIPSPCF8833_BLUE);
                          //XDEBUG_PRINTCOLOR(1, _L("Send screen Clean : %s "), status?_L("Ok!"):_L("Error!"));

                          //GEN_XSLEEP.Seconds(1);
                          XRAND*  rnd = GEN_XFACTORY.CreateRand();
                          if(rnd)
                            {
                              for(int y=0; y< lcdscreen->GetHeight(); y++)
                                {
                                  for(int x=0; x< lcdscreen->GetWidth(); x++)
                                    {
                                       lcdscreen->PutPixel(x , y, rnd->Between(0,65535));
                                    }
                                }

                               GEN_XFACTORY.DeleteRand(rnd);
                            }



                          XWORD*  buffer = NULL;
                          XRAND*  rnd = GEN_XFACTORY.CreateRand();

                          if(rnd)
                            {
                              XDEBUG_PRINTCOLOR(1, _L("Create Random..."));

                              buffer = GEN_NEW XWORD[lcdscreen->GetNPixels()];
                              if(buffer)
                                {
                                  XDEBUG_PRINTCOLOR(1, _L("Create Buffer Random..."));

                                  int nframes = 0;

                                  while(nframes<100)
                                    {
                                      for(XDWORD c=0; c<lcdscreen->GetNPixels(); c++)
                                        {
                                          buffer[c] = 23; //rnd->Between(0,65535);
                                        }

                                      lcdscreen->Update((XBYTE*)buffer);
                                      XDEBUG_PRINTCOLOR(1, _L("Send screen Update: %05d  %s    "), nframes,  status?_L("Ok!"):_L("Error!"));

                                      nframes++;
                                   }

                                } else XDEBUG_PRINTCOLOR(1, _L("Error Create Buffer Random..."));

                              delete buffer;

                           } else XDEBUG_PRINTCOLOR(1, _L("Error Create Random..."));

                         GEN_XFACTORY.DeleteRand(rnd);



                      }


                    }

                  lcdscreen->End();
                }

              delete lcdscreen;
            }

          diogpio->End();
        }

      GEN_DIOFACTORY.DeleteGPIO(diogpio);
    }

  //----------------------------------------------------------------------------
  */
  /*
  DIOGPIO* diogpio = DIOFACTORY::GetInstance().CreateGPIO();
  if(diogpio)
    {
      if(diogpio->Ini())
        {
          DIOSPIOLEDSCREENSSD1331*  oledscreenSSD1331 = GEN_NEW DIOSPIOLEDSCREENSSD1331();
          if(oledscreenSSD1331)
            {
              oledscreenSSD1331->SetDIOGPIO(diogpio);

              oledscreenSSD1331->SetResetPin(SCREEN_PIN_RESET, SCREEN_GRP_RESET);
              oledscreenSSD1331->SetDCPin(SCREEN_PIN_DC, SCREEN_GRP_DC);

              status  =  oledscreenSSD1331->Ini(1, 0, 3);
              XTRACE_PRINTCOLOR((status?1:4), _L("Send screen INI   : %s \n"), (status?_L("Ok!"):_L("Error!")));
              if(status)
                {
                  while(1)
                    {
                      status = oledscreenSSD1331->Clear(DIOSPIOLEDSCREENSSD1331_COLOR_RED);
                      GEN_XSLEEP.Seconds(1);

                      status = oledscreenSSD1331->Clear(DIOSPIOLEDSCREENSSD1331_COLOR_GREEN);
                      GEN_XSLEEP.Seconds(1);

                      status = oledscreenSSD1331->Clear(DIOSPIOLEDSCREENSSD1331_COLOR_BLUE);
                      GEN_XSLEEP.Seconds(1);
                    }
                }

              oledscreenSSD1331->End();
              delete oledscreenSSD1331;
            }

          diogpio->End();
        }

      DIOFACTORY::GetInstance().DeleteGPIO(diogpio);

      return true;
    }
  */

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void CANVAS2DDISPLAY::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void CANVAS2DDISPLAY::Clean()
{

}




