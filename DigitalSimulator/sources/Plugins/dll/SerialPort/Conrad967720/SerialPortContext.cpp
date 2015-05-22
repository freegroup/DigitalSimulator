/* NO WARRANTY
 *
 *    BECAUSE THE PROGRAM IS IN THE PUBLIC DOMAIN, THERE IS NO
 *    WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE
 *    LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE AUTHORS
 *    AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT
 *    WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *    BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 *    AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS TO
 *    THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD
 *    THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL
 *    NECESSARY SERVICING, REPAIR OR CORRECTION.
 *
 *    IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN
 *    WRITING WILL ANY AUTHOR, OR ANY OTHER PARTY WHO MAY MODIFY
 *    AND/OR REDISTRIBUTE THE PROGRAM, BE LIABLE TO YOU FOR DAMAGES,
 *    INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 *    DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE PROGRAM
 *    (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING
 *    RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES
 *    OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
 *    PROGRAMS), EVEN IF SUCH AUTHOR OR OTHER PARTY HAS BEEN ADVISED
 *    OF THE POSSIBILITY OF SUCH DAMAGES.
 */

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <iomanip>


#include "../stdafx.h"
#include "SerialPortContext.hpp"


#include "DialogOption.h"


// Nicht entfernen!!!!!!
// wird für die Initialisierung der MFC-Klassen benoetigt.
//
CWinApp theApp;

#define LINKAGE		__declspec(dllexport)


//----------------------------------------------------------------------------
extern "C" bool LINKAGE cf_create_interface(const char *iid,IPluginBase **iface){
//----------------------------------------------------------------------------

	*iface = NULL;

	SerialPortContext *ptr;

	try	{
		ptr = new SerialPortContext;

      ptr->QueryInterface(iid, iface);
		ptr->Destroy();
	}
	catch(...){
		(*iface )  = NULL;
	}

	return (*iface ) != NULL;
}

//----------------------------------------------------------------------------
SerialPortContext::SerialPortContext(void) {
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   m_serielPort= new CSerialPort;
   m_refCount  = 1;

   // BEGIN_TODO
   //
   m_portNr    = -1;
   m_deviceNr  = 0;
   // END_TODO
}


//----------------------------------------------------------------------------
bool SerialPortContext::QueryInterface(const char *iid, IPluginBase **iface){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   *iface = NULL;

	if (::strcmp(iid, "IPluginInfo") == 0)
		*iface = static_cast<IPluginInfo*>(this);
	else if (::strcmp(iid, "IOutputContext") == 0)
		*iface = static_cast<IOutputContext*>(this);
	else if (::strcmp(iid, "IPluginBase") == 0)
		*iface = static_cast<IPluginInfo*>(this);

	if (*iface != NULL)
		m_refCount++;

	return *iface != NULL;
}

//----------------------------------------------------------------------------
void SerialPortContext::Destroy(void){
//----------------------------------------------------------------------------
  AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	if (--m_refCount == 0){
      delete m_serielPort;
      m_serielPort = NULL;
		delete this;
	}
}


//----------------------------------------------------------------------------
int SerialPortContext::write(char value){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   if(m_serielPort != NULL){
      // BEGIN_TODO
      //
      char buf[100];
	   buf[0] = 1;
	   buf[1] = m_deviceNr;
	   buf[2] = 0;
	   buf[3] = 1 ^ 1 ^ 0 ;
      m_serielPort->write(buf,4);

	   buf[0] = 3;
	   buf[1] = m_deviceNr;
	   buf[2] = value;
	   buf[3] = 3 ^ m_deviceNr ^ value ;

      m_serielPort->write(buf,4);
      // END_TODO
      return 1;
   }
   TRACE("Error: m_serielPort == NULL  in  SerialPortContext::write(char value)\n");
   return 0;

}


//----------------------------------------------------------------------------
char SerialPortContext::read(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // Conrad-Interface has no input feature
   // .....no interface returnd in QueryInterface(....)
   return 0;
}

//----------------------------------------------------------------------------
void SerialPortContext::getKey(char * buffer,long size){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(buffer == NULL || size == 0)
      return;

   // BEGIN_TODO
   //
   strncpy(buffer, "Conrad Elektronik Seriel Relaiskarte",size);
   // END_TODO
}

//----------------------------------------------------------------------------
void SerialPortContext::getDeviceName(char * buffer,long size){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(buffer == NULL || size == 0)
      return;

   // BEGIN_TODO
   //
   strncpy(buffer, "Seriel Relaiskarte",size);
   // END_TODO
}

//----------------------------------------------------------------------------
void SerialPortContext::getProducerName(char * buffer,long size){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(buffer == NULL || size == 0)
      return;

   // BEGIN_TODO
   //
   strncpy(buffer, "Conrad-Elektronik",size);
   // END_TODO
}

//----------------------------------------------------------------------------
void SerialPortContext::getProducerURL(char * buffer,long size){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(buffer == NULL || size == 0)
      return;

   // BEGIN_TODO
   //
   strncpy(buffer, "http://www.conrad-elektronik.de",size);
   // END_TODO
}


//----------------------------------------------------------------------------
void SerialPortContext::getProgrammerName(char * buffer,long size){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(buffer == NULL || size == 0)
      return;

   // BEGIN_TODO
   //
   strncpy(buffer, "Andreas Herz",size);
   // END_TODO
}


//----------------------------------------------------------------------------
void SerialPortContext::getProgrammerURL(char * buffer,long size){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(buffer == NULL || size == 0)
      return;

   // BEGIN_TODO
   //
   strncpy(buffer, "http://www.FreeGroup.de",size);
   // END_TODO
}


//----------------------------------------------------------------------------
void SerialPortContext::getVersion(char * buffer,long size){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(buffer == NULL || size == 0)
      return;

   // BEGIN_TODO
   //
   strncpy(buffer, "1.2",size);
   // END_TODO
}

//----------------------------------------------------------------------------
void SerialPortContext::getLabel(char * buffer,long size){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(buffer == NULL || size == 0)
      return;

   // BEGIN_TODO
   //
   if(m_portNr >=0 )
      sprintf(buffer, "Conrad-Elek. 967720 on COM %d",m_portNr);
   else
      sprintf(buffer, "Conrad-Elek. 967720 with no free port");
   // END_TODO
}

//----------------------------------------------------------------------------
int SerialPortContext::getPort(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   return m_portNr;
}

//----------------------------------------------------------------------------
void SerialPortContext::Get(char * buffer,long size){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(buffer == NULL || size == 0)
      return;

   // BEGIN_TODO
   //
   sprintf(buffer,"Port=%d Device=%d",m_portNr, m_deviceNr);
   // END_TODO
}

//----------------------------------------------------------------------------
void    SerialPortContext::Set(const char *buffer){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(buffer == NULL)
      return;

   // BEGIN_TODO
   //
   strcpy(m_tmpParam,buffer);
   sscanf(buffer,"Port=%d Device=%d",&m_portNr, &m_deviceNr);
   // END_TODO
}


//----------------------------------------------------------------------------
void SerialPortContext::onStart(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   if(m_portNr > 0 ){
      Init(m_portNr);
   }
}


//----------------------------------------------------------------------------
void SerialPortContext::onStop(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   Get(m_tmpParam,sizeof(m_tmpParam)-1);
   delete m_serielPort;
   m_serielPort = NULL;
}


//----------------------------------------------------------------------------
void    SerialPortContext::DoOption(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   CDialogOption dlg;
   
   // BEGIN_TODO
   //
   dlg.m_portNr    = m_portNr;
   dlg.m_geraeteID = m_deviceNr;
   if(dlg.DoModal()==IDOK && dlg.m_portNr>=0 && dlg.m_portNr<=5){
     m_deviceNr  = dlg.m_geraeteID;
     m_portNr    = dlg.m_portNr;
   }
   // END_TODO
}

//----------------------------------------------------------------------------
void SerialPortContext::Init(int port){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   if (m_serielPort!=NULL)
      delete m_serielPort;
   m_serielPort = new CSerialPort;
   m_portNr    = port;
   // BEGIN_TODO
   //
   if(m_serielPort->Init(port)== TRUE){
   // END_TODO
      m_serielPort->startMonitoring();
   }
   else{
      TRACE(_T("ERROR SerialPortContext::Init failed\n"));
      delete m_serielPort;
      m_serielPort = NULL;

   }
   Get(m_tmpParam,sizeof(m_tmpParam)-1);
}
