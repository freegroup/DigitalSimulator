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
#include "DDENode.h"

IMPLEMENT_SERIAL(CDDENode, DragDropArea, 1)

bool       CDDENode::m_isInitilized=false;
CDDEServer CDDENode::m_DDEServer;
const  CDDENode::m_version = 1;

//----------------------------------------------------------------------------
CDDENode::CDDENode(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if(m_isInitilized==false){
      if (!m_DDEServer.Create(AfxGetAppName())) {
			AfxMessageBox("Failed to Initialize DDE server ");
		}
		m_isInitilized = true;
	}
   SetResizable(FALSE);
}

//----------------------------------------------------------------------------
CDDENode::~CDDENode(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}


//----------------------------------------------------------------------------
DragDropObject* CDDENode::Clone() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pObj = inherited::Clone();
   ASSERT(pObj->IsKindOf(RUNTIME_CLASS(CDDENode)));                  
   CDDENode *pNode =(CDDENode*) pObj ;

   // aus den geclonten Kindern die Icons 
   // herausfiltern
   //
   POSITION p= pNode->GetFirstChildPos() ;
   if(p){
      pObj = pNode->GetNextChild(p);
      // das erste Kind muss das Metafile sein....
      //
      ASSERT(pObj->IsKindOf(RUNTIME_CLASS(DragDropMetaFile)));                  
      pNode->m_icon = (DragDropMetaFile*)pObj;
      // ...alles was danach kommt sind die Ports
      //
      while( p) {
         pNode->m_ports.Add(pNode->GetNextChild(p));
      }
   }
   else{
    TRACE("Warning: leere Collection in CDDENode::Clone()\n");
   }

   pNode->m_server = m_server;
   pNode->m_topic  = m_topic;
   pNode->m_item   = m_item;
 
   return pNode;
}


//----------------------------------------------------------------------------
void CDDENode::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

    inherited::Serialize(ar);

    m_ports.Serialize(ar);

    if (ar.IsStoring()){
        ar << m_version;

        ar << m_server;
        ar << m_topic;
        ar << m_item;
        ar << m_icon;
    }
    else{
       int version;
       ar >> version;

       switch (version){
       case 1:
           ar >> m_server;
           ar >> m_topic;
           ar >> m_item;
           ar >> m_icon;
           break;
       default:
           LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
           break;
       }
    }
}

