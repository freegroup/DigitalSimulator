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

#include "DDEAdviceConv.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Dialogs\ObjectDialogs\DialogDDEINParamWizard.h"
#include "Application\Dialogs\ObjectDialogs\DialogDDEParam.h"

#include "DDEInputNode.h"

IMPLEMENT_SERIAL(CDDEInputNode, CDDENode, 1);
const  CDDEInputNode::m_version = 1;

//----------------------------------------------------------------------------
CDDEInputNode::CDDEInputNode(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_pDDEConversation = NULL;
   m_icon             = NULL;
   m_hasError         = false;
}


//----------------------------------------------------------------------------
CDDEInputNode::CDDEInputNode(CPoint position){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CSize  size(150,0);
   int    loop;
	CString name=WMF_PATH("obj_ddein.wmf");

	m_icon = new DragDropMetaFile(position,size,name, TRUE);
   m_icon->SetSelectable(FALSE);
   AddChildAtHead(m_icon); 

	m_pDDEConversation= NULL;

   CElectricPort *tmpPort;
   for( loop=0; loop<8;loop++){
      tmpPort = new CElectricPort(position, PSRight, PSRight);
      tmpPort->Init(); 
      AddChildAtTail(tmpPort);
      m_ports.Add(tmpPort);
   }

   for(loop=0 ;loop <m_ports.GetSize() ; loop++){
      m_ports[loop]->SetInverter(false);
      m_ports[loop]->SetInput(false);
      m_ports[loop]->SetOutput(true);
   }

   long elements      = m_ports.GetSize();
   CPoint  topLeft    = m_icon->GetBoundingRect().TopLeft();
   CPoint  bottomRight= m_icon->GetBoundingRect().BottomRight();

   float   yOffset = m_icon->GetBoundingRect().Height() / (float)(elements+1);

   for(loop=0 ;loop <elements ; loop++){
      int xPos = bottomRight.x;
      int yPos = (int)(topLeft.y+(yOffset*(loop+1)));

      m_ports[loop]->SetSpotLocation(DragDropObject::spotLeftCenter,xPos,yPos);
   }
}


//----------------------------------------------------------------------------
CDDEInputNode::~CDDEInputNode(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if(m_pDDEConversation!=NULL)
       m_pDDEConversation->Terminate();
}

//----------------------------------------------------------------------------
void CDDEInputNode::Serialize(CArchive& ar){
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
void  CDDEInputNode::AdviseStopped(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	  m_icon->SetMetaFileName(WMF_PATH("obj_ddein_error.wmf"));
     m_hasError=true;
}


//----------------------------------------------------------------------------
void CDDEInputNode::AdviseData(int value){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_ports.GetSize() >8 );

   m_ports[0]->SetValue(value & 1   ? CLogicValue::High:CLogicValue::Low);
   m_ports[1]->SetValue(value & 2   ? CLogicValue::High:CLogicValue::Low);
   m_ports[2]->SetValue(value & 4   ? CLogicValue::High:CLogicValue::Low);
   m_ports[3]->SetValue(value & 8   ? CLogicValue::High:CLogicValue::Low);
   m_ports[4]->SetValue(value & 16  ? CLogicValue::High:CLogicValue::Low);
   m_ports[5]->SetValue(value & 32  ? CLogicValue::High:CLogicValue::Low);
   m_ports[6]->SetValue(value & 64  ? CLogicValue::High:CLogicValue::Low);
   m_ports[7]->SetValue(value & 128 ? CLogicValue::High:CLogicValue::Low);
}


//----------------------------------------------------------------------------
BOOL CDDEInputNode::SetDDE(CString server, CString topic, CString item){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_server  = server;
	m_topic   = topic;
	m_item    = item;

   if(m_pDDEConversation==NULL){
      m_pDDEConversation = new CDDEAdviceConv(&m_DDEServer,this);
      ASSERT(m_pDDEConversation!=NULL);
      m_pDDEConversation->AddRef();
   }
   else{
      // Alte Verbindung abbrechen
      // 
      m_pDDEConversation->Terminate();
   }

   if (!m_pDDEConversation->ConnectTo((LPCSTR)m_server, (LPCSTR)m_topic)) {
    	  m_icon->SetMetaFileName(WMF_PATH("obj_ddein_error.wmf"));
        m_hasError = true;
        return FALSE;
   }
   else {
        m_pDDEConversation->Advise((LPCSTR)m_item);
    	  m_icon->SetMetaFileName(WMF_PATH("obj_ddein.wmf"));
   }

   m_hasError = false;
	return TRUE;
}


//----------------------------------------------------------------------------
void CDDEInputNode::DoCalculate(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_hasError==true)
      SetDDE(m_server,m_topic,m_item);
}


//----------------------------------------------------------------------------
BOOL CDDEInputNode::DoExtendedOption(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CDialogDDEINParamWizard d;

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
long CDDEInputNode::GetContextMenuId(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_hasError==true)
      return IDR_POPUP_DDEIN_ERROR_OBJECT;

   return IDR_POPUP_DDEIN_OBJECT;
}


//----------------------------------------------------------------------------
BOOL CDDEInputNode::DoOption(){
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