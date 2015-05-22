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
#include "DragDrop.h"
#include "DragDropObject.h"
#include "DragDropText.h"
#include "DragDropDocument.h"
#include "DragDropMetafile.h"
#include "DragDropLink.h"

#include "Application\Debug\LogManager.h"

#include "Application\Dialogs\ObjectDialogs\DialogSecondaryObjectOptions.h"
#include "Application\Objects\buildin\digital\ElectricPortLink.h"
#include "Application\Objects\buildin\digital\ElectricNode.h"
#include "Application\Objects\buildin\digital\ElectricNodeContext.h"


IMPLEMENT_SERIAL(CElectricNode, DragDropArea, 1)
const  CElectricNode::m_version = 3;


//----------------------------------------------------------------------------
CElectricNode::CElectricNode(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_data.pOwner = this;

   m_pContext  = NULL;
}

//----------------------------------------------------------------------------
CElectricNode::CElectricNode(CString key){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_data.pOwner   = this;
   m_data.key = key;
   m_pContext = CElectricNodeContext::GetContext(m_data.key);
   m_pContext->Initialize(m_data);
}

//----------------------------------------------------------------------------
CElectricNode::~CElectricNode(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_pContext){
      // it is possible that the context has copy
      // a pointer from a strukt/class in the param buffer.
      // Give the context a chance to delete/free this pointer
      // The param pointer itself will be deleted from the
      // context.
      //
      m_pContext->CleanupParam(m_data);
   }

   // The DragDrop-children will be deleted by DragDropArea Cleanup
   //
}


//----------------------------------------------------------------------------
void CElectricNode::OnTimerStart(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   m_pContext->OnStartCalculate(m_data);
}


//----------------------------------------------------------------------------
void CElectricNode::OnTimerEnd(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   m_pContext->OnStopCalculate(m_data);
}

//----------------------------------------------------------------------------
BOOL CElectricNode::paint(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Falls der context sich nicht selber zeichnen kann
   // z.B Buildin Objekte, werden diese durch die Engine
   // gezeichnet.
   //......Plugins können sich selber zeichen und benötigen nicht
   // immer das generischen zeichnen.....es wreden dann keine Ports
   // gezeichnet. Dies muß dann der Context auch selbst erledigen
   //
   if(!m_pContext->paint( m_data,pDC)){
      // generic painting from the DragDrop objects
      //
      inherited::paint(pDC);
   }

   return TRUE;
}

//----------------------------------------------------------------------------
DragDropObject* CElectricNode::Clone() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   // nicht Clone der Basisklasse aufrufen!!!! es sollen nicht die 
   // Arrayelemente mit kopiert werden
   //
   DragDropObject* pObj = DragDropObject::Clone();    
   ASSERT(pObj->IsKindOf(RUNTIME_CLASS(CElectricNode)));                  
   CElectricNode *pNode =(CElectricNode*) pObj ;

   pNode->m_bGrabChildSelection = m_bGrabChildSelection;   // from DragDropArea
   pNode->m_data.inCount        = m_data.inCount;
   pNode->m_data.outCount       = m_data.outCount ;
   pNode->m_data.param = new char[m_pContext->GetParamCount()];
   memcpy(pNode->m_data.param,m_data.param,m_pContext->GetParamCount());
   pNode->m_data.location       = GetLocation();
   pNode->m_data.key       = m_data.key;
   pNode->m_pContext            = m_pContext;
   pNode->m_pContext->Initialize(pNode->m_data);
   
   return pNode;
}


//----------------------------------------------------------------------------
CString CElectricNode::GetDescriptionText(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   return m_pContext->GetDescriptionText();
}

//----------------------------------------------------------------------------
CString CElectricNode::GetKey()const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_data.key;
}

//----------------------------------------------------------------------------
CString CElectricNode::GetName()const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pContext->GetName();
}

//----------------------------------------------------------------------------
CString CElectricNode::GetVersion()const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pContext->GetVersion();
}

//----------------------------------------------------------------------------
CString CElectricNode::GetGroup()const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   return m_pContext->GetGroup();
}

//----------------------------------------------------------------------------
CString CElectricNode::GetMetaNameSuffix(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   return m_pContext->GetMetaNameSuffix(m_data);
}

//----------------------------------------------------------------------------
long CElectricNode::GetContextMenuId(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   return m_pContext->GetContextMenuId();
}


//----------------------------------------------------------------------------
void CElectricNode::DoCalculate(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   m_pContext->DoCalculate(m_data);
}


//----------------------------------------------------------------------------
BOOL CElectricNode::DoLButtonDblClk(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   // save the position of the mouse for the current context
   //
   m_data.mousePos = pointLP- m_data.location;
   m_pContext->OnLButtonDblClk(m_data);
   return TRUE;
}


//----------------------------------------------------------------------------
BOOL CElectricNode::DoOption(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   m_pContext->onOption(m_data);
   return TRUE;
}


//----------------------------------------------------------------------------
BOOL CElectricNode::DoExtendedOption(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CDialogSecondaryObjectOptions d(NULL,m_data);

   if(d.DoModal()==IDOK) {
      if(d.m_metaNameString != m_data.key){
         m_pContext= CElectricNodeContext::GetContext(d.m_metaNameString);
         m_data.key = d.m_metaNameString;
         // Alten eventuell zu kleinen Speicherbereich löschen
         //
         delete [] m_data.param;
         m_data.param = new char[m_pContext->GetParamCount()];
         memset(m_data.param,0,m_pContext->GetParamCount());
         m_pContext->InitParam(m_data);

         // initialisierung muß sein, da sich eine Ein/Ausgänge verändert
         // haben können. Dies sind nicht vom Kontext abhängig d.h. selber Kontext
         // aber unterschiedeliche Anzahl von Ports möglich
         //
         m_pContext->SetInputCount(m_data , d.m_inputCount);
         m_pContext->SetOutputCount(m_data, d.m_outputCount);
         m_pContext->Initialize(m_data);
      }
      return TRUE;
   }
   return FALSE;
}


//----------------------------------------------------------------------------
BOOL CElectricNode::DoLButtonClick(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   // save the position of the mouse for the current context
   //
   m_data.mousePos = pointLP- m_data.location;

   m_pContext->OnLButtonClick(m_data);
   m_pContext->selectIcon(m_data);
   m_pContext->Layout(m_data);

   return TRUE;
}


//----------------------------------------------------------------------------
BOOL CElectricNode::DoLButtonUp(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   // save the position of the mouse for the current context
   //
   m_data.mousePos = pointLP- m_data.location;
   m_pContext->OnLButtonUp(m_data);
   m_pContext->selectIcon(m_data);
   m_pContext->Layout(m_data);

   return  inherited::DoLButtonUp( nFlags, pointDP, pointLP, pDC, pView);
}


//----------------------------------------------------------------------------
BOOL CElectricNode::DoMouseOverStart(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   // save the position of the mouse for the current context
   //
   m_data.mousePos = pointLP- m_data.location;

   m_pContext->OnMouseOverStart(m_data);
   m_pContext->selectIcon(m_data);
   m_pContext->Layout(m_data);

   return FALSE;
}

//----------------------------------------------------------------------------
BOOL CElectricNode::DoMouseOver(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   // save the position of the mouse for the current context
   //
   m_data.mousePos = pointLP- m_data.location;

   m_pContext->OnMouseOver(m_data);
   m_pContext->selectIcon(m_data);
   m_pContext->Layout(m_data);

   return FALSE;
}


//----------------------------------------------------------------------------
BOOL CElectricNode::DoMouseOverEnd(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // save the position of the mouse for the current context
   //
   m_data.mousePos = pointLP- m_data.location;

   m_pContext->OnMouseOverEnd(m_data);
   m_pContext->selectIcon(m_data);
   m_pContext->Layout(m_data);

   return FALSE;
}


//----------------------------------------------------------------------------
BOOL CElectricNode::DoLButtonDown(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);

   // save the position of the mouse for the current context
   //
   m_data.mousePos = pointLP- m_data.location;

   m_pContext->OnLButtonDown(m_data);
   m_pContext->selectIcon(m_data);
   m_pContext->Layout(m_data);

   return inherited::DoLButtonDown(nFlags, pointDP, pointLP, pDC, pView);
}

//----------------------------------------------------------------------------
void CElectricNode::SetLocation(int x, int y){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   // Das Objekt darf nicht die linke und die obere Kante 
   // überschreiten. Es darf aber so weit recht wie möglich
   // und so weit nach unten wie möglich
   //
   inherited::SetLocation( max(0,x), min(0, y));
}

//----------------------------------------------------------------------------
void CElectricNode::SetBoundingRect(int nLeft, int nTop, int nRight, int nBottom){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Das Objekt darf nicht die linke und die obere Kante 
   // überschreiten. Es darf aber so weit recht wie möglich
   // und so weit nach unten wie möglich
   //
   if(nLeft<0){
      nRight = nRight - nLeft;
      nLeft  = 0;
   }
   if( nTop>0){
      nBottom= nBottom - nTop;
      nTop   = 0;
   }

   inherited::SetBoundingRect(nLeft, nTop, nRight, nBottom);
}

//----------------------------------------------------------------------------
void CElectricNode::GeometryChange(CRect* pRectPrevious){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   inherited::GeometryChange(pRectPrevious);
   m_pContext->OnGeometryChange(m_data);
   m_pContext->selectIcon(m_data);
   m_data.location = m_data.icons[0]->GetLocation();
}

//----------------------------------------------------------------------------
void CElectricNode::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;


   inherited::Serialize(ar);

   m_data.inPorts.Serialize(ar);
   m_data.outPorts.Serialize(ar);
   m_data.icons.Serialize(ar);

   static CDWordArray  param;
   param.Serialize(ar); // ist eigentlich veraltet...kann man aber leider
                        // nicht streichen, da sonst alte Dateien nicht mehr lesbar sind

   if (ar.IsStoring()) {
       // gespeichert wird nur noch Version 3
       //
       ar << m_version;
       ar << m_data.pLabel;
       ar << m_data.key;
       ar << m_data.location;
       ar << m_data.size;
       ar << m_pContext->GetParamCount();
       ar.Write(m_data.param,m_pContext->GetParamCount());
       ar << m_data.logicState.IsHigh();
   }
   else
   {
      int version;
      ar >> version;

      switch (version){
      case 1: // Fileformat Version 1
         {
          // altes parameterformat in das neue konvertieren
          //
          if(param.GetSize()>0){
             if(m_data.param){
                delete[] m_data.param;
                m_data.param = NULL;
             }
             m_data.param = new char[param.GetSize()];
             for(int loop=0; loop< param.GetSize();loop++){
                m_data.param[loop]= param[loop];
             }
          }
          else{
             if(m_data.param){
                delete[] m_data.param;
                m_data.param = NULL;
             }
          }
          ar >> m_data.pLabel;
          ar >> m_data.key;
          ar >> m_data.location;
          ar >> m_data.size;
          m_data.inCount  = m_data.inPorts.GetSize();
          m_data.outCount = m_data.outPorts.GetSize();
         }
          break;
      case 2: // Fileformat Version 2
         {
          DWORD bufferSize;
          ar >> m_data.pLabel;
          ar >> m_data.key;
          ar >> m_data.location;
          ar >> m_data.size;
          ar >> bufferSize;
          // neues parameterformat einlesen
          //
          if(m_data.param){
            delete []m_data.param;
            m_data.param= NULL;
          }
          if(bufferSize>0){
            m_data.param = new char[bufferSize];
            ar.Read(m_data.param,bufferSize);
          }
          m_data.inCount  = m_data.inPorts.GetSize();
          m_data.outCount = m_data.outPorts.GetSize();
         }
          break;
      case 3: // Fileformat Version 3
         {
          DWORD bufferSize;
          BOOL  b;
          ar >> m_data.pLabel;
          ar >> m_data.key;
          ar >> m_data.location;
          ar >> m_data.size;
          ar >> bufferSize;
          // neues parameterformat einlesen
          //
          if(m_data.param){
            delete []m_data.param;
            m_data.param= NULL;
          }
          if(bufferSize>0){
            m_data.param = new char[bufferSize];
            ar.Read(m_data.param,bufferSize);
          }
          ar >> b; m_data.logicState = b?CLogicValue::High: CLogicValue::Low;
          m_data.inCount  = m_data.inPorts.GetSize();
          m_data.outCount = m_data.outPorts.GetSize();
         }
          break;
      default:
          LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
          break;
      }
      m_pContext = CElectricNodeContext::GetContext(m_data.key);
      m_pContext->Initialize(m_data);
   }
}


//----------------------------------------------------------------------------
CSize CElectricNode::GetInputCountRange(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   return m_pContext->GetInputCountRange();
}


//----------------------------------------------------------------------------
CSize CElectricNode::GetOutputCountRange(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   return m_pContext->GetOutputCountRange();
}

//----------------------------------------------------------------------------
long CElectricNode::GetInputCount(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_data.inPorts.GetSize();
}


//----------------------------------------------------------------------------
long CElectricNode::GetOutputCount(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_data.outPorts.GetSize();
}

//----------------------------------------------------------------------------
CElectricPort*    CElectricNode::GetInput(int index){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_data.inPorts[index];
}

//----------------------------------------------------------------------------
CElectricPort*    CElectricNode::GetOutput(int index){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_data.outPorts[index];
}


//----------------------------------------------------------------------------
CRect CElectricNode::GetBoundingRect(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_boundingRect;
}


//----------------------------------------------------------------------------
long  CElectricNode::GetHelpId(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pContext != NULL);
   return m_pContext->GetHelpId();
}
