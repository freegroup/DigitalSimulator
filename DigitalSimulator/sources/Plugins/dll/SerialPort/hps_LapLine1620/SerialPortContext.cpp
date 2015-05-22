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
#include "SerialPort.h"


#include "DialogOption.h"


// Nicht entfernen!!!!!!
// wird für die Initialisierung der MFC-Klassen benoetigt.
//
CWinApp theApp;

#define LINKAGE		__declspec(dllexport)
CSerialPort*   SerialPortContext::m_ports[10];
bool           SerialPortContext::m_isInit    = false;


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

   m_refCount  = 1;
   m_portNr    = -1;
   if(m_isInit == false){ // cut and past or make a loop  ;-)
      m_ports[0] = NULL;  // only to confuse....
      m_ports[1] = NULL;
      m_ports[2] = NULL;
      m_ports[3] = NULL;
      m_ports[4] = NULL;
      m_ports[5] = NULL;
      m_ports[6] = NULL;
      m_ports[7] = NULL;
      m_ports[8] = NULL;
      m_ports[9] = NULL;
      m_isInit   = true;
   }
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
	else if (::strcmp(iid, "IInputContext") == 0)
		*iface = static_cast<IInputContext*>(this);
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
      if(m_portNr >=0 && m_ports[m_portNr]!= NULL){
         delete m_ports[m_portNr];
         m_ports[m_portNr] = NULL;
      }
		delete this;
	}
}


//----------------------------------------------------------------------------
int SerialPortContext::write(char value){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   if(m_ports[m_portNr] != NULL){
      // BEGIN_TODO
      //
      m_ports[m_portNr]->SetDTR();
      Sleep(5);

      for (int i= 0; i<8 ;i++)
      {
         if(value & 0x01)
         {
            m_ports[m_portNr]->SetBreak();
            m_ports[m_portNr]->ClearRTS();
            m_ports[m_portNr]->SetRTS();
//            TRACE("1");
         }
         else
         {
            m_ports[m_portNr]->ClearBreak();
            m_ports[m_portNr]->ClearRTS();
            m_ports[m_portNr]->SetRTS();
//            TRACE("0");
         }
         value = value >>1;
         Sleep(2);

      }

      TRACE("\n");
      Sleep(5);
      m_ports[m_portNr]->ClearDTR();
//      m_ports[m_portNr]->SetBreak();
      // END_TODO
      return 1;
   }

   return 0;
}

//----------------------------------------------------------------------------
char SerialPortContext::read(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(m_portNr >=0 && m_ports[m_portNr] != NULL){
      // BEGIN_TODO
      //
      char result = 0;

      // Daten in das interne Register der Karte laden
      //
      m_ports[m_portNr]->ClearRTS();
      m_ports[m_portNr]->SetRTS();
      Sleep(20);

      result = result << 1;
      result = result + m_ports[m_portNr]->GetDSR();
      // 
      for(int i=0 ;i<7; i++)
      {
         m_ports[m_portNr]->ClearBreak();
         m_ports[m_portNr]->SetBreak();
         result = result << 1;
         result = result + m_ports[m_portNr]->GetDSR();
      }


      m_ports[m_portNr]->ClearRTS();
      return result;
      // END_TODO
   }
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
   strncpy(buffer, "hps-Systemtechnik LAPLine 1620 Interface",size);
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
   strncpy(buffer, "LAPLine1620",size);
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
   strncpy(buffer, "hps Systemtechnik",size);
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
   strncpy(buffer, "http://www.hps-Systemtechnik.com",size);
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
   strncpy(buffer, "0.9",size);
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
      sprintf(buffer, "LAPLine1620 on COM %d",m_portNr);
   else
      sprintf(buffer, "LAPLine1620 with no free COM-port");
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
   sprintf(buffer,"Port=%d",m_portNr);
   // END_TODO
}

//----------------------------------------------------------------------------
void  SerialPortContext::Set(const char *buffer){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   if(buffer == NULL)
      return;
   strcpy(m_tmpParam,buffer);
   // BEGIN_TODO
   //
   sscanf(buffer,"Port=%d",&m_portNr);
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

   if(m_portNr>0){
      delete m_ports[m_portNr];
      m_ports[m_portNr]=NULL;
   }
}

//----------------------------------------------------------------------------
void  SerialPortContext::DoOption(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   CDialogOption dlg;
   
   // BEGIN_TODO
   //
   dlg.m_portNr    = m_portNr;
   if(dlg.DoModal()==IDOK && dlg.m_portNr>=0 && dlg.m_portNr<=5){
      m_portNr= dlg.m_portNr;
   }
   // END_TODO
}


//----------------------------------------------------------------------------
void SerialPortContext::Init(int port){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   if(m_ports[port]== NULL){
      m_ports[port] = new CSerialPort;
      // BEGIN_TODO
      //
      m_ports[port]->Open(port);
      if(m_ports[port]->IsOpen()==TRUE){
         m_portNr    = port;
         Get(m_tmpParam,sizeof(m_tmpParam)-1);
      }
      else{
         delete m_ports[port];
         m_ports[port] = NULL;
      }
      // 
      // END TODO
   }

}
