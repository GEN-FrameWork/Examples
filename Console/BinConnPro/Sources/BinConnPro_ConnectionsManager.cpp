/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro_ConnectionsManager.cpp
*
* @class      BINCONNPRO_CONNECTIONSMANAGER
* @brief      Example Binary Connexion Protocol Connexions class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#include "XPublisher.h"

#include "DIOFactory.h"
#include "DIOStreamUDPLocalEnumServers.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"
#include "DIOStreamCipher.h"

#include "CipherAES.h"
#include "CipherKeySymmetrical.h"

#include "BinConnPro_ApplicationData.h"
#include "BinConnPro_Protocol.h"

#include "BinConnPro_ConnectionsManager.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::BINCONNPRO_CONNECTIONSMANAGER()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_CONNECTIONSMANAGER::BINCONNPRO_CONNECTIONSMANAGER() : DIOPROTOCOL_CONNECTIONSMANAGER()
{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::~BINCONNPRO_CONNECTIONSMANAGER()
* @brief      Destructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_CONNECTIONSMANAGER::~BINCONNPRO_CONNECTIONSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_CONNECTIONSMANAGER::Ini(bool isserver, bool isenumlocalactive, int port, BINCONNPRO_APPLICATIONDATA* applicationdata)
* @brief      Ini.
* @ingroup    EXAMPLES
*
* @param[in]  isserver : true when the connection manager works as server; false when it works as client.
* @param[in]  isenumlocalactive : true to enable local enumeration; false to disable it.
* @param[in]  port : TCP or UDP port used by the operation.
* @param[in]  applicationdata : Application data associated with the protocol connection.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CONNECTIONSMANAGER::Ini(bool isserver, bool isenumlocalactive, int port, BINCONNPRO_APPLICATIONDATA* applicationdata)
{
  this->applicationdata = applicationdata;

  diostreamTCPIPcfg = GEN_NEW DIOSTREAMTCPIPCONFIG();
  if(!diostreamTCPIPcfg) return false;

  if(isenumlocalactive)
    {
      diostreamudplocalenumservers = GEN_NEW DIOSTREAMUDPLOCALENUMSERVERS();
      if(!diostreamudplocalenumservers)  return false;

      diostreamudplocalenumservers->SetID(BINCONNPRO_CONNECTIONSMANAGER_LOCALENUMID);
      diostreamudplocalenumservers->SetPort(BINCONNPRO_CONNECTIONSMANAGER_LOCALENUMPORT);
      diostreamudplocalenumservers->SetSearchTimeout(3);

      diostreamenumservers = diostreamudplocalenumservers;
    }

  diostreamTCPIPcfg->SetRemotePort(port);

  return DIOPROTOCOL_CONNECTIONSMANAGER::Ini(isserver, diostreamTCPIPcfg, diostreamudplocalenumservers);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int BINCONNPRO_CONNECTIONSMANAGER::ProtocolConnections_GetNConnected()
* @brief      Gets the number of connected protocol connections.
* @ingroup    EXAMPLES
*
* @return     int : Requested value.
*
*---------------------------------------------------------------------------------------------------------------------*/
int BINCONNPRO_CONNECTIONSMANAGER::ProtocolConnections_GetNConnected()
{
  int nprotocolconnectionsON = 0;
  int navailable              = ProtocolConnections_GetNAvailable();

  for(int c=0; c<navailable; c++)
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = ProtocolConnections_Get(c);
      if(protocolconnection)
        {
          BINCONNPRO_PROTOCOL* protocol = (BINCONNPRO_PROTOCOL*)protocolconnection->GetDIOProtocol();
          if(protocol)
            {
              if(protocol->IsInitialized())
                {
                  nprotocolconnectionsON++;
                }
            }
        }
    }

  return nprotocolconnectionsON;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTION* BINCONNPRO_CONNECTIONSMANAGER::ProtocolConnections_GetByDIOStream(DIOSTREAM* diostream)
* @brief      Gets a protocol connection by stream.
* @ingroup    EXAMPLES
*
* @param[in]  diostream : Stream used by the protocol.
*
* @return     DIOPROTOCOL_CONNECTION* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTION* BINCONNPRO_CONNECTIONSMANAGER::ProtocolConnections_GetByDIOStream(DIOSTREAM* diostream)
{
  if(protocolconnections.IsEmpty())  return NULL;

  for(int index=0; index<ProtocolConnections_GetNAvailable(); index++)
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
      if(protocolconnection)
        {
          BINCONNPRO_PROTOCOL* protocol = (BINCONNPRO_PROTOCOL*)protocolconnection->GetDIOProtocol();
          if(protocol)
            {
              DIOSTREAMCIPHER* diostreamcipher = (DIOSTREAMCIPHER*)protocolconnection->GetDIOProtocol()->GetDIOStream();
              if(diostreamcipher)
                {
                  if(diostreamcipher->GetDIOStreamBase() == diostream) return protocolconnection;
                }
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_CONNECTIONSMANAGER::End()
* @brief      End.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CONNECTIONSMANAGER::End()
{
  bool status = DIOPROTOCOL_CONNECTIONSMANAGER::End();

  if(diostreamTCPIPcfg)
    {
      delete diostreamTCPIPcfg;
      diostreamTCPIPcfg = NULL;
    }

  if(diostreamudplocalenumservers)
    {
      delete diostreamudplocalenumservers;
      diostreamudplocalenumservers = NULL;
    }

  return status;
}





#ifdef BINCONNPRO_CONNECTIONSMANAGER_CIPHERPROTOCOL

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL* BINCONNPRO_CONNECTIONSMANAGER::CreateProtocol()
* @brief      Creates a protocol instance.
* @ingroup    EXAMPLES
*
* @return     DIOPROTOCOL* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL* BINCONNPRO_CONNECTIONSMANAGER::CreateProtocol()
{
  CIPHERAES* cipher = GEN_NEW CIPHERAES();
  if(!cipher) return NULL;

  XBYTE inivector[] = BINCONNPRO_CONNECTIONSMANAGER_INIKEYENCRIPTION;
  XBYTE keydata[]   = BINCONNPRO_CONNECTIONSMANAGER_KEYENCRIPTION;

  CIPHERKEYSYMMETRICAL* key = GEN_NEW CIPHERKEYSYMMETRICAL();
  if(!key) return NULL;

  cipher->SetChainingMode(CIPHERCHAININGMODE_CBC);
  cipher->SetPaddingType(XBUFFER_PADDINGTYPE_ZEROS);
  cipher->SetInitVector(inivector, sizeof(inivector));

  key->Set(keydata, sizeof(keydata));

  cipher->SetKey(key);

  DIOSTREAMCIPHER* diostreamcipher = GEN_NEW DIOSTREAMCIPHER(diostreamcfg, cipher);
  if(diostreamcipher)
    {
      DIOSTREAMTCPIP* diostreamTCPIP = (DIOSTREAMTCPIP*)diostreamcipher->GetDIOStreamBase();
      if(diostreamTCPIP)
        {
          diostreamTCPIP->SetEnumServers(diostreamenumservers);

          BINCONNPRO_PROTOCOL* protocol = GEN_NEW BINCONNPRO_PROTOCOL(diostreamcipher);
          if(protocol)
            {
              protocol->SetConnectionsManager(this);
              protocol->SetMaskID(BINCONNPRO_CONNECTIONSMANAGER_PROTOCOLMASKID | (isserver?DIOPROTOCOL_CMDTYPE_ISSERVER:0));
              protocol->SetProtocolVersion(BINCONNPRO_PROTOCOL_VERSION, BINCONNPRO_PROTOCOL_SUBVERSION, BINCONNPRO_PROTOCOL_SUBVERSIONERR);
              protocol->Application_SetVersion(applicationversion, applicationsubversion, applicationsubversionerr);
              protocol->Application_GetName()->Set(applicationname);


              if(isserver)
                      protocol->GetDescription()->Set(__L("EGM Protocol Server"));
                else  protocol->GetDescription()->Set(__L("EGM Protocol Client"));

              if(!applicationdata)
                {
                  BINCONNPRO_APPLICATIONDATA* protocolapplicationdatanew = GEN_NEW BINCONNPRO_APPLICATIONDATA();
                  if(protocolapplicationdatanew)
                    {
                      protocol->SetApplicationData(protocolapplicationdatanew);
                      protocol->SetIsOwnApplicationData(true);
                    }
                }
               else
                {
                  protocol->SetApplicationData(applicationdata);
                  protocol->SetIsOwnApplicationData(false);
                }

              return (DIOPROTOCOL*)protocol;
            }

          diostreamcipher->Close();
          delete diostreamcipher;
        }
    }

  return NULL;
}

#else

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL* BINCONNPRO_CONNECTIONSMANAGER::CreateProtocol()
* @brief      Creates a protocol instance.
* @ingroup    EXAMPLES
*
* @return     DIOPROTOCOL* : Pointer to the requested object; NULL if it is not available.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL* BINCONNPRO_CONNECTIONSMANAGER::CreateProtocol()
{
  DIOSTREAMTCPIP* diostreamTCPIP = (DIOSTREAMTCPIP*)GEN_DIOFACTORY.CreateStreamIO(diostreamcfg);
  if(diostreamTCPIP)
    {
      diostreamTCPIP->SetEnumServers(diostreamenumservers);

      BINCONNPRO_PROTOCOL* protocol = GEN_NEW BINCONNPRO_PROTOCOL(diostreamTCPIP);
      if(protocol)
        {
          protocol->SetMaskID(BINCONNPRO_CONNECTIONSMANAGER_PROTOCOLMASKID | (isserver?DIOPROTOCOL_CMDTYPE_ISSERVER:0));

          if(isserver)
                    protocol->GetDescription()->Set(__L("EGM Protocol Server"));
              else  protocol->GetDescription()->Set(__L("EGM Protocol Client"));

          if(!applicationdata)
              {
                BINCONNPRO_APPLICATIONDATA* protocolapplicationdatanew = GEN_NEW BINCONNPRO_APPLICATIONDATA();
                if(protocolapplicationdatanew)
                  {
                    protocol->SetApplicationData(protocolapplicationdatanew);
                    protocol->SetIsOwnApplicationData(true);
                  }
              }
             else
              {
                protocol->SetApplicationData(applicationdata);
                protocol->SetIsOwnApplicationData(false);
              }

          return (DIOPROTOCOL*)protocol;
        }

      diostreamTCPIP->Close();
      GEN_DIOFACTORY.DeleteStreamIO(diostreamTCPIP);
    }

  return NULL;
}

#endif





#ifdef BINCONNPRO_CONNECTIONSMANAGER_CIPHERPROTOCOL

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_CONNECTIONSMANAGER::DeleteProtocol(DIOPROTOCOL* dioprotocol)
* @brief      Deletes a protocol instance.
* @ingroup    EXAMPLES
*
* @param[in]  dioprotocol : Dioprotocol value used by the operation.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CONNECTIONSMANAGER::DeleteProtocol(DIOPROTOCOL* dioprotocol)
{
  if(!dioprotocol)  return false;

  DIOSTREAMCIPHER*      diostreamcipher = (DIOSTREAMCIPHER*)dioprotocol->GetDIOStream();
  CIPHERAES*            cipher          = (CIPHERAES*)diostreamcipher->GetCipher();
  CIPHERKEYSYMMETRICAL* key             = (CIPHERKEYSYMMETRICAL*)cipher->GetKey();

  if(dioprotocol->IsOwnApplicationData())
    {
      BINCONNPRO_APPLICATIONDATA* applicationdata =  (BINCONNPRO_APPLICATIONDATA*)dioprotocol->GetApplicationData();
      if(applicationdata)
        {
          delete applicationdata;
          dioprotocol->SetApplicationData(NULL);
        }
    }

  if(diostreamcipher) diostreamcipher->Close();

  delete cipher;
  delete key;
  delete dioprotocol;

  delete diostreamcipher;

  return true;
}

#else

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_CONNECTIONSMANAGER::DeleteProtocol(DIOPROTOCOL* dioprotocol)
* @brief      Deletes a protocol instance.
* @ingroup    EXAMPLES
*
* @param[in]  dioprotocol : Dioprotocol value used by the operation.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CONNECTIONSMANAGER::DeleteProtocol(DIOPROTOCOL* dioprotocol)
{
  if(!dioprotocol)  return false;

  DIOSTREAMTCPIP* diostreamTCPIP = (DIOSTREAMTCPIP*)dioprotocol->GetDIOStream();

  if(dioprotocol->IsOwnApplicationData())
    {
      BINCONNPRO_APPLICATIONDATA* applicationdata =  (BINCONNPRO_APPLICATIONDATA*)dioprotocol->GetApplicationData();
      if(applicationdata) delete applicationdata;
    }

  delete dioprotocol;

  if(diostreamTCPIP)
    {
      diostreamTCPIP->Close();
      GEN_DIOFACTORY.DeleteStreamIO(diostreamTCPIP);
    }

  return true;
}

#endif



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO_CONNECTIONSMANAGER::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO_CONNECTIONSMANAGER::Clean()
{
  isenumlocalactive               = false;
  applicationdata                 = NULL;
  diostreamudplocalenumservers    = NULL;
  diostreamTCPIPcfg               = NULL;
}

