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

#include "stdafx.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Dialogs\ObjectDialogs\DialogDDEOUTParamWizard.h"
#include "Application\Dialogs\ObjectDialogs\DialogDDEParam.h"

#include "ddenode.h"
#include "DDEOuputNode.h"


IMPLEMENT_SERIAL(CDDEOuputNode, CDDENode, 1);
const  CDDEOuputNode::m_version = 1;

//----------------------------------------------------------------------------
CDDEOuputNode::CDDEOuputNode(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_pDDEConversation = NULL;
   m_icon             = NULL;
   m_hasError         = false;
}

//----------------------------------------------------------------------------
CDDEOuputNode::CDDEOuputNode(CPoint position){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CSize  size(150,0);
   int    loop;
	CString name=WMF_PATH("obj_ddeout.wmf");

	m_icon = new DragDropMetaFile(position,size,name, TRUE);
   m_icon->SetSelectable(FALSE);
   AddChildAtHead(m_icon); 

	m_pDDEConversation= NULL;

   CElectricPort *tmpPort;
   for( loop=0; loop<8;loop++)   {
      tmpPort = new CElectricPort(position, PSLeft, PSLeft);
      tmpPort->Init(); 
      AddChildAtTail(tmpPort);
      m_ports.Add(tmpPort);
   }

   for(loop=0 ;loop <m_ports.GetSize() ; loop++)   {
      m_ports[loop]->SetInverter(false);
      m_ports[loop]->SetInput(true);
      m_ports[loop]->SetOutput(false);
   }

   long elements      = m_ports.GetSize();
   CPoint  topLeft    = m_icon->GetBoundingRect().TopLeft();

   float   yOffset = m_icon->GetBoundingRect().Height() / (float)(elements+1);

   for(loop=0 ;loop <elements ; loop++){
      int xPos = topLeft.x;
      int yPos = (int)(topLeft.y+(yOffset*(loop+1)));

      m_ports[loop]->SetSpotLocation(DragDropObject::spotRightCenter,xPos,yPos);
   }
}

//----------------------------------------------------------------------------
CDDEOuputNode::~CDDEOuputNode(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if(m_pDDEConversation!=NULL)
       m_pDDEConversation->Terminate();
}

//----------------------------------------------------------------------------
void CDDEOuputNode::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

    inherited::Serialize(ar);

    if (ar.IsStoring()){
       ar << m_version;

    }
    else{
       int version;
       ar >> version;

       switch (version){
       case 1:
           SetDDE(m_server,m_topic,m_item);
           break;
       default:
           LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
           break;
       }
    }
}

//----------------------------------------------------------------------------
long CDDEOuputNode::GetContextMenuId(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_hasError==true)
      return IDR_POPUP_DDEOUT_ERROR_OBJECT;

   return IDR_POPUP_DDEOUT_OBJECT;
}


//----------------------------------------------------------------------------
void CDDEOuputNode::DoCalculate(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_pDDEConversation!=NULL){
      char buffer[20];
      int value =   (m_ports[0]->IsHigh()?1:0) 
                  + (m_ports[1]->IsHigh()?2:0) 
                  + (m_ports[2]->IsHigh()?4:0)
                  + (m_ports[3]->IsHigh()?8:0)
                  + (m_ports[4]->IsHigh()?16:0)
                  + (m_ports[5]->IsHigh()?32:0)
                  + (m_ports[6]->IsHigh()?64:0)
                  + (m_ports[7]->IsHigh()?128:0);
	   sprintf(buffer,"%d",value);

      if(!m_pDDEConversation->Poke(CF_TEXT,(LPCSTR)m_item,(void*)(const char*)buffer,strlen(buffer)+1)){
         if(m_hasError==false)
  	         m_icon->SetMetaFileName(WMF_PATH("obj_ddeout_error.wmf"));
         m_hasError = true;
         // try to reconnect to the DDE-Server
         //
         SetDDE(m_server,m_topic,m_item);
      }
      else{
         if(m_hasError==true)
  	         m_icon->SetMetaFileName(WMF_PATH("obj_ddeout.wmf"));
         m_hasError = false;
      }
   }
   else{
      if(m_hasError==false)
  	      m_icon->SetMetaFileName(WMF_PATH("obj_ddeout_error.wmf"));
      m_hasError = true;
   }

}

//----------------------------------------------------------------------------
BOOL CDDEOuputNode::SetDDE(CString server, CString topic, CString item){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_server  = server;
	m_topic   = topic;
	m_item    = item;

   if(m_pDDEConversation==NULL){
      m_pDDEConversation = new CDDEConv(&m_DDEServer);
      ASSERT(m_pDDEConversation!=NULL);
      m_pDDEConversation->AddRef();
   }
   else{
      m_pDDEConversation->Terminate();
   }

   // Versuchen eine Verbindung zu dem DDE-Server aufzubauen
   // und das Bitmap entsprechen setzten (ok/nicht ok)
   if (!m_pDDEConversation->ConnectTo((LPCSTR)m_server, (LPCSTR)m_topic)){
    	  m_icon->SetMetaFileName(WMF_PATH("obj_ddeout_error.wmf"));
        m_hasError = true;
        return FALSE;
   }
   else {
    	  m_icon->SetMetaFileName(WMF_PATH("obj_ddeout.wmf"));
   }

   m_hasError = false;

	return TRUE;
}


//----------------------------------------------------------------------------
BOOL CDDEOuputNode::DoExtendedOption(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CDialogDDEOUTParamWizard d;

	d.m_server= m_server;
	d.m_topic = m_topic;
	d.m_item  = m_item;

	if(d.DoModal()==IDOK){
		SetDDE(d.GetServer(),d.GetTopic(),d.GetItem());
      return TRUE;
	}
   return FALSE;
}

//----------------------------------------------------------------------------
BOOL CDDEOuputNode::DoOption(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CDialogDDEParam d;

	d.m_server= m_server;
	d.m_topic = m_topic;
	d.m_item  = m_item;

   if(d.DoModal()==IDOK){
		SetDDE(d.m_server,d.m_topic,d.m_item);
      return TRUE;
	}
   return FALSE;
}