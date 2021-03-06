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
#include "Application\Debug\LogManager.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Dialogs\ObjectDialogs\DialogSerielOutOption.h"
#include "Application\Objects\plugin\DLL\SerialPort\SerialPluginManager.h"

#include "SerialOutNode.h"


IMPLEMENT_SERIAL(CSerialOutNode, DragDropArea, 1)
const  CSerialOutNode::m_version = 1;

//----------------------------------------------------------------------------
CSerialOutNode::CSerialOutNode(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetResizable(FALSE);
   m_contextInfo   = NULL;
   m_outputContext = NULL;
   m_label         = NULL;
   m_icon          = NULL;
}


//----------------------------------------------------------------------------
CSerialOutNode::CSerialOutNode(CPoint position){
//----------------------------------------------------------------------------
	PROC_TRACE;

   int    loop;
   CSize size(150,0);

   m_icon = NULL;

 	CString name=WMF_PATH("obj_serielout.wmf");

   // create the image for the DragDrop object
   //
	m_icon = new DragDropMetaFile(position,size,name, TRUE);
   m_icon->SetSelectable(FALSE);
   AddChildAtHead(m_icon); 

   // create the labe text for the object
   //
   CPoint botleft = m_icon->GetSpotLocation(DragDropObject::spotBottomCenter);
   m_label = new DragDropText(CPoint(botleft.x, botleft.y-10), 
                          CSize(0,40), "",DragDropText::DefaultFaceName,
                          FW_NORMAL, FALSE, FALSE, TextTopMiddle);
   m_label->SetTextColor(RGB(0,0,0));
   m_label->SetBkMode(TRANSPARENT);
   m_label->SetSelectable(FALSE);
   AddChildAtTail(m_label);


   CElectricPort *m_tmpPort;
   for( loop=0; loop<8;loop++)   {
      m_tmpPort = new CElectricPort(position, PSLeft, PSLeft);
      m_tmpPort->Init(); 
      AddChildAtTail(m_tmpPort);
      m_ports.Add(m_tmpPort);
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
   SetResizable(FALSE);
   m_contextInfo   = NULL;
   m_outputContext = NULL;

   updateLabel();
}

//----------------------------------------------------------------------------
CSerialOutNode::~CSerialOutNode(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if( m_contextInfo != NULL){
      m_contextInfo->Destroy();
      m_contextInfo=NULL;
   }

   if( m_outputContext != NULL){
      m_outputContext->Destroy();
      m_outputContext=NULL;
   }

   // will bee deleted by the DragDropArray
   //
   // m_icon
   // m_label
}


//----------------------------------------------------------------------------
DragDropObject* CSerialOutNode::Clone() const{   
//----------------------------------------------------------------------------
	PROC_TRACE;

   CSerialOutNode* pNode = (CSerialOutNode*)inherited::Clone();
   POSITION p= pNode->GetFirstChildPos() ;
   pNode->m_icon                = (DragDropMetaFile*)pNode->GetNextChild(p);
   pNode->m_label               = (DragDropText*)pNode->GetNextChild(p);
   pNode->m_contextInfo         = NULL; 
   pNode->m_outputContext       = NULL; 

   while( p) {
     pNode->m_ports.Add(pNode->GetNextChild(p));
   }
       
   pNode->updateLabel();
   return pNode;
}


//----------------------------------------------------------------------------
void CSerialOutNode::DoCalculate(){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   if(m_outputContext!=NULL){
      char value =   (m_ports[0]->IsHigh()?1:0) 
                  + (m_ports[1]->IsHigh()?2:0) 
                  + (m_ports[2]->IsHigh()?4:0)
                  + (m_ports[3]->IsHigh()?8:0)
                  + (m_ports[4]->IsHigh()?16:0)
                  + (m_ports[5]->IsHigh()?32:0)
                  + (m_ports[6]->IsHigh()?64:0)
                  + (m_ports[7]->IsHigh()?128:0);

      m_outputContext->write(value);
   }
   else{
   }
}


//----------------------------------------------------------------------------
BOOL CSerialOutNode::DoOption(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_contextInfo != NULL){
       m_contextInfo->DoOption();
       updateLabel();
   }
   return TRUE;
}


//----------------------------------------------------------------------------
CElectricPort*    CSerialOutNode::GetInput(int index){
//----------------------------------------------------------------------------
   PROC_TRACE;

   return m_ports[index];
}


//----------------------------------------------------------------------------
long CSerialOutNode::GetInputCount(){
//----------------------------------------------------------------------------
   PROC_TRACE;

   return m_ports.GetSize();
}



//----------------------------------------------------------------------------
BOOL CSerialOutNode::DoExtendedOption(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CDialogSerielOutOption d;
   char buffer[200];

   if(m_contextInfo != NULL){
      m_contextInfo->getKey(buffer,sizeof(buffer)-1);
      d.m_pluginKey = CString(buffer);
   }

	if(d.DoModal()==IDOK){
      // Altes Interface zerstoeren und neues anlegen
      //
      if(m_contextInfo != NULL){
         m_contextInfo->getKey(buffer,sizeof(buffer)-1);
         // Falls der neu gew�hlte Typ von Interface der gleiche wie der
         // bestehende ist muss man nichts tun
         //
         if(CString(buffer) == d.m_pluginKey)
            return FALSE;

         // das bestehende Interface zerst�ren
         //
         m_contextInfo->Destroy();
      }
      m_contextInfo   = (IPluginInfo*)SerialPluginManager::createInstance(d.m_pluginKey,"IPluginInfo");
      m_contextInfo->QueryInterface("IOutputContext",(IPluginBase**)&m_outputContext);
      return DoOption();
	}
   return FALSE;
}

//----------------------------------------------------------------------------
void CSerialOutNode::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

    inherited::Serialize(ar);
    m_ports.Serialize(ar);

    if (ar.IsStoring()){
       ar << m_version;

       char key[200]   = "";
       char param[200] = "";

       if(m_contextInfo != NULL){
          m_contextInfo->getKey(key,sizeof(key)-1);
          m_contextInfo->Get(param,sizeof(param)-1);
       }
       ar << m_icon;
       ar << m_label;
       ar << CString(key);
       ar << CString(param);
    }
    else{
       int version;
       ar >> version;

       switch (version){
       case 1:
          {
          CString key;
          CString param;
          ar >> m_icon;
          ar >> m_label;
          ar >> key;
          ar >> param;
          m_contextInfo = (IPluginInfo*)SerialPluginManager::createInstance(key,"IPluginInfo");
          if(m_contextInfo != NULL){
              m_contextInfo->Set((LPCSTR)param);
              m_contextInfo->QueryInterface("IOutputContext",(IPluginBase**)&m_outputContext);
          }
          m_icon->SetMetaFileName(WMF_PATH("obj_serielout.wmf"));
          updateLabel();
          }
          break;
       default:
           LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
          break;
       }
    }
}

//----------------------------------------------------------------------------
void CSerialOutNode::updateLabel(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_label != NULL && m_contextInfo!= NULL){
      char buffer[200];
      m_contextInfo->getLabel(buffer, sizeof(buffer)-1);
      m_label->SetString(buffer);
   }
   else if(m_label != NULL){
      m_label->SetString("- no PlugIn selected -");
   }
   else{
      // urgs
   }
}


//----------------------------------------------------------------------------
void CSerialOutNode::OnTimerStart(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_contextInfo != NULL){
      m_contextInfo->onStart();
    //  updateLabel(); -> Error......aber keine Ahnung warum
   }
}


//----------------------------------------------------------------------------
void CSerialOutNode::OnTimerEnd(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_contextInfo != NULL){
      m_contextInfo->onStop();
    //  updateLabel(); -> Error......aber keine Ahnung warum
   }
}
