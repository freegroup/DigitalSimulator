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

#include "DragDropstdafx.h"
#include "DragDropApp.h"
#include "DragDropClientApp.h"   // for palette colors
#include "DragDropDocument.h"
#include "DragDropObject.h"
#include "DragDropArea.h"
#include "DragDropLayout.h"
#include "DragDropPort.h" 

IMPLEMENT_DYNCREATE(DragDropDocument, CDocument)

BEGIN_MESSAGE_MAP(DragDropDocument, CDocument)
    //{{AFX_MSG_MAP(DragDropDocument)
    ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
DragDropDocument::DragDropDocument(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   Init();
}

//----------------------------------------------------------------------------
DragDropDocument::~DragDropDocument(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

/*
//----------------------------------------------------------------------------
BOOL DragDropDocument::OnNewDocument(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (!inherited::OnNewDocument())
        return FALSE;

    return TRUE;
}


//----------------------------------------------------------------------------
BOOL DragDropDocument::OnOpenDocument(LPCTSTR pPathName){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (!inherited::OnOpenDocument(pPathName))
        return FALSE;
    return TRUE;
}
*/

//----------------------------------------------------------------------------
void DragDropDocument::Init(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_nUnit = Metrics::getPixelsPerUnit(); 

    SetDocumentSize     (CSize(21*m_nUnit,28*m_nUnit));       // 21 cm X 27 cm (sort of 8.5 x 11)
    SetMinSize          (CSize(21*m_nUnit/2,28*m_nUnit/2));   // half of the default size in default minimum
    SetDocumentLineSize (CSize (3*m_nUnit, 3*m_nUnit));       // 3 cm default scroll by line
                         
    m_paperColor = CDragDropApp::GetPaletteIndex (::GetSysColor (COLOR_WINDOW));
    m_bUseSystemPaperColor = TRUE;  // as long as this is true, window color should track Control Panel setting.

    m_pCurrentDrawView = NULL;
    m_bSuspendUpdates  = FALSE;
    
    OSVERSIONINFO info;
    info.dwOSVersionInfoSize = sizeof(info);
  	 GetVersionEx(&info);

    BOOL nt = (info.dwPlatformId == VER_PLATFORM_WIN32_NT);
    m_nMaxDoc   = 32000;
    m_nMinScale = 5;
    m_nMaxScale = 1000;

    if (nt) {
        m_nMaxDoc   = (DWORD)0x7FFFFFFF;
        m_nMinScale = 2;
        m_nMaxScale = 5000;
    }

}                         

//----------------------------------------------------------------------------
void DragDropDocument::GrowDocument(int cx, int cy){
//----------------------------------------------------------------------------
	PROC_TRACE;

	BOOL bGrow = FALSE;
	CSize szDoc = GetDocumentSize();

	if (szDoc.cx < cx) {
		szDoc.cx = cx + m_nUnit;
		bGrow = TRUE;
	}
	if (szDoc.cy < cy) {
		szDoc.cy = cy + m_nUnit;
		bGrow = TRUE;
	}

	if (bGrow) {
		SetDocumentSize(szDoc);
		UpdateAllViews(NULL, Update_New_Document_Size, NULL);
	}
}

//----------------------------------------------------------------------------
void DragDropDocument::SetPaperColor(COLORREF color){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_paperColor = CDragDropApp::GetPaletteIndex (color);
    m_bUseSystemPaperColor = FALSE;  // as long as this is true, window color should track Control Panel setting.    
    UpdateAllViews(NULL, Refresh_Display, NULL);    
}

//----------------------------------------------------------------------------
void DragDropDocument::OnSysColorChange(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_bUseSystemPaperColor) {
        m_paperColor = CDragDropApp::GetPaletteIndex (::GetSysColor (COLOR_WINDOW));
	     UpdateAllViews(NULL, Refresh_Display, NULL);    
    }
}    


//----------------------------------------------------------------------------
void DragDropDocument::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

    SuspendUpdates();

    if (ar.IsStoring())    {
        ar << m_sizeDocument; 
    }
    else{
        ar >> m_sizeDocument;
    }
    m_oblistObjects.Serialize(ar);
    
    ResumeUpdates();
    UpdateAllViews(NULL, Refresh_Display, NULL);    
}



//----------------------------------------------------------------------------
void DragDropDocument::OnEditClearAll(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    DeleteContents();
    SetModifiedFlag();
    UpdateAllViews(NULL, Refresh_Display, NULL);    
}                                   

//----------------------------------------------------------------------------
void DragDropDocument::OnUpdateEditClearAll(CCmdUI* pCmdUI){
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(!m_oblistObjects.IsEmpty()); 
}


//----------------------------------------------------------------------------
POSITION DragDropDocument::AddObjectAtHead(DragDropObject* pObject, BOOL bForceFirstDraw){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(pObject->GetDocument() == NULL);

    
    pObject->m_pParentArea = NULL;
    
    POSITION pos = m_oblistObjects.AddHead(pObject);

    pObject->SetDocument(this); 
    SetModifiedFlag();
    if (bForceFirstDraw) 
       pObject->SetUpdateNeeded(FALSE);
    return pos;
}

//----------------------------------------------------------------------------
POSITION DragDropDocument::AddObjectAtTail(DragDropObject* pObject, BOOL bForceFirstDraw){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pObject->GetDocument() == NULL);

   pObject->m_pParentArea = NULL;
                                        
   POSITION pos = m_oblistObjects.AddTail(pObject);

   pObject->SetDocument(this); 
    
   SetModifiedFlag();

   if (bForceFirstDraw) 
      pObject->SetUpdateNeeded(FALSE);
    
   return pos;
}


//----------------------------------------------------------------------------
POSITION DragDropDocument::GetFirstObjectPos() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_oblistObjects.GetHeadPosition();
}


//----------------------------------------------------------------------------
DragDropObject* DragDropDocument::GetNextObjectAtTop(POSITION& pos) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return(DragDropObject*)m_oblistObjects.GetNext(pos); 
}                                    

//----------------------------------------------------------------------------
DragDropObject* DragDropDocument::GetNextObject(POSITION& pos) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   //  This routine is still used in DragDropView by the code that finds valid links
//  between ports.  The use of this routine isn't recommended, using the GetNextObjectAtTop
//  and using recursion with DragDropAreas is the preferred method.

    DragDropObject *pObject, *pParent;
                                
    // Note that the GetAt returns "data" from the CNode structure in CObList.
    // Since this is walking a tree, the document's m_oblistObjects isn't the right
    // list to use, but it DoCalculates...
    
    pObject =(DragDropObject*) m_oblistObjects.GetAt(pos);       // Fetch object pointer from pos
    ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropObject)));
    
    // There are 4 cases to consider here for return value of 'pos'
    // 1: 'pos' points to a DragDropArea with children              
    //      - return the head of the the Area's object list
    // 2: 'pos' points to an object in a list, and is not at the end of the list
    //      - simply return the next one in the list
    // 3: same as 2, except pos is at end of list   
    //      - return the next in the parent's list
    // 4: same as 3, except no parent.
    //      - return NULL, done with traversal
    
    
    if (pObject->IsKindOf(RUNTIME_CLASS(DragDropArea))) {
        DragDropArea* pArea =(DragDropArea*) pObject; // cast pointer
        if (!pArea->m_oblistObjects.IsEmpty()) {
            pos = pArea->m_oblistObjects.GetHeadPosition();
            return pObject;                       
        } // end of case 1 above
    }
    
    pParent = pObject->m_pParentArea;       // Fetch the parent
    DragDropObject* pObject2;                // pObject2 only for debug ASSERT below
    if (pParent != NULL) {
        ASSERT(pParent->IsKindOf(RUNTIME_CLASS(DragDropArea)));
        DragDropArea* pArea =(DragDropArea*) pObject;
        pObject2 =(DragDropObject*) pArea->m_oblistObjects.GetNext(pos);
    }
    else
        pObject2 =(DragDropObject*) m_oblistObjects.GetNext(pos);    // use documents list

    ASSERT(pObject == pObject2);
    
    // if pos != NULL now, we're all done.  Otherwise, we must look for valid
    // place to leave 'pos', up the tree somewhere.
    
    DragDropObject* pObjectX = pObject;
    while (pos == NULL) {
        pParent = pObjectX->m_pParentArea;      // Fetch the parent
        if (pParent != NULL) {      
            ASSERT(pParent->IsKindOf(RUNTIME_CLASS(DragDropArea)));
            DragDropArea* pArea =(DragDropArea*) pParent;
            pos = pArea->m_oblistObjects.Find(pObjectX);
            ASSERT(pos != NULL);        // better not be null...
            pArea->m_oblistObjects.GetNext(pos);        // update pos
            pObjectX = pParent;         // walk up a level        
        }
        else {
            pos = m_oblistObjects.Find(pObjectX);   // back to Document's list
            ASSERT(pos != NULL);            // better not be null...
            m_oblistObjects.GetNext(pos);       // update pos
            return pObject;                 // no can't go up the tree more.  pos=NULL is valid here
        }               
    }
    
    return pObject; // return current object
}

//---------------------------------------------------------------------------- 
void DragDropDocument::DeleteContents(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   while (!m_oblistObjects.IsEmpty())
    {
        DragDropObject* pObject =(DragDropObject*)m_oblistObjects.RemoveHead();
        delete pObject;     // Area destructor handles areas correctly...
    }
}


//----------------------------------------------------------------------------/////////////////////////////////////////////////////////////////////////////
void DragDropDocument::DeleteObject(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!m_oblistObjects.Find(pObject))
      return;

   RemoveObject(pObject);          // detach object from Document
   delete pObject;                 // and delete the object
}

//----------------------------------------------------------------------------
void DragDropDocument::RemoveObject(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(pObject == NULL)
       return;

    pObject->SetClearOnUpdate(TRUE);
    UpdateAllViews(NULL, Update_Delete, pObject);

    POSITION pos;

    if (pObject->m_pParentArea){
        DragDropArea* pParentArea = (DragDropArea*) pObject->m_pParentArea;
        if (pos = pParentArea->m_oblistObjects.Find(pObject))
            pParentArea->m_oblistObjects.RemoveAt(pos);
    }
    else{
        if (pos = m_oblistObjects.Find(pObject))
            m_oblistObjects.RemoveAt(pos);
    }
    pObject->SetDocument(NULL);
}



//----------------------------------------------------------------------------
DragDropObject* DragDropDocument::PickInDocument(CClientDC* pDC, CPoint ptToCheckLP, BOOL bSelectableOnly){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CPoint ptToCheckDP;
    ptToCheckDP.x = ptToCheckLP.x;
    ptToCheckDP.y = ptToCheckLP.y;
    
    pDC->LPtoDP(&ptToCheckDP);  // PtInObject needs both LP and DP.

    // Iterate thru the Objects at the top level of the Document.

    for (POSITION pos = m_oblistObjects.GetTailPosition(); pos != NULL; ) {
        DragDropObject* obj = (DragDropObject*) m_oblistObjects.GetPrev(pos);
        if(obj != NULL){
           if (!obj->isVisible()) 
              continue;
        
           // Test if the point is within the Object.

           if (!obj->PtInObject(pDC, ptToCheckLP, ptToCheckDP))
              continue;

           // Look for the inner-most object of an Area (visual recursion).
            
           if (obj->IsKindOf(RUNTIME_CLASS(DragDropArea))) {
               DragDropArea* pArea = (DragDropArea*) obj;
               DragDropObject* pObjectInArea = pArea->PickInArea(pDC, ptToCheckLP, bSelectableOnly);
    
               if (pObjectInArea != NULL) 
                  return pObjectInArea;
           }
        
           if (!bSelectableOnly) 
              return obj;
           if (obj->IsSelectable()) 
              return obj;
        }
        else{
           TRACE0("Warning: unerwarteter NULL-Pointer in DragDropDocument::PickInDocument\n");
        }
    }
    
    return NULL;
}


//----------------------------------------------------------------------------
void DragDropDocument::BringObjectToFront(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pParent = pObject->m_pParentArea;     

    if (pParent != NULL) {
        ASSERT(pParent->IsKindOf(RUNTIME_CLASS(DragDropArea)));
        DragDropArea* pArea =(DragDropArea*) pParent;
        pArea->BringObjectToFront(pObject);
    }
    else  {
        POSITION pos;  
        if( ( pos = m_oblistObjects.Find(pObject) ) != NULL ) {                                        
            m_oblistObjects.RemoveAt(pos);
            m_oblistObjects.AddTail(pObject);
            pObject->SetUpdateNeeded(TRUE);
        }
    }
}


//----------------------------------------------------------------------------
void DragDropDocument::SendObjectToBack(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;
        
        
    DragDropObject* pParent = pObject->m_pParentArea; 
    if (pParent != NULL) {
        ASSERT(pParent->IsKindOf(RUNTIME_CLASS(DragDropArea)));
        DragDropArea* pArea =(DragDropArea*) pParent;
        pArea->SendObjectToBack(pObject);
    }
    else  {
        POSITION pos;  
        if( ( pos = m_oblistObjects.Find(pObject) ) != NULL ){                                        
            m_oblistObjects.RemoveAt(pos);
            m_oblistObjects.AddHead(pObject);
            pObject->SetUpdateNeeded(TRUE);
        }
    }
}

 

//----------------------------------------------------------------------------
CSize DragDropDocument::GetMinLayoutSize(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CSize size(0,0);
    CRect rect;
    for (POSITION pos = GetFirstObjectPos(); pos != NULL; ){
        DragDropObject* pObject = GetNextObjectAtTop(pos);
        rect = pObject->GetBoundingRect();
        if (rect.bottom < size.cy) size.cy = rect.bottom;
        if (rect.right  > size.cx) size.cx = rect.right;   
    }

    size.cy = abs(size.cy);

    CSize szMin = GetMinSize();

    if (size.cx < szMin.cx) 
       size.cx = szMin.cx;
    if (size.cy < szMin.cy) 
       size.cy = szMin.cy;

    return size;
}

//----------------------------------------------------------------------------
void DragDropDocument::StartAutomation(DragDropObject* pObj){
//----------------------------------------------------------------------------
	PROC_TRACE;

	UpdateAllViews(NULL, Update_ClearSelectionHandles, pObj);
}

//----------------------------------------------------------------------------
void DragDropDocument::EndAutomation(DragDropObject* pObj){
//----------------------------------------------------------------------------
	PROC_TRACE;

	UpdateAllViews(NULL, Update_RestoreSelectionHandles, pObj);
}

//----------------------------------------------------------------------------
void DragDropDocument::UpdateAutomation(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	UpdateAllViews(NULL, Update_Window, NULL);
}


//----------------------------------------------------------------------------
void DragDropDocument::LayoutDiagram(int nDirection,
        int nNodeHeight,
        int nNodeWidth,
        int nSpacePrcnt,
        BOOL bBalanceLayout,
        BOOL bResizeNodes,
        int nHorizOffset,
        int nVertOffset
        ){
//----------------------------------------------------------------------------
   StartAutomation();
	DragDropLayout GoLayout;
   GoLayout.LayoutDiagram(this, nDirection, nNodeHeight, nNodeWidth, nSpacePrcnt,
       bBalanceLayout, bResizeNodes, nHorizOffset, nVertOffset);
	EndAutomation();
}



//----------------------------------------------------------------------------
DragDropPort* DragDropDocument::FromPort(DragDropPort* pPort1, DragDropPort* pPort2){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return pPort1;
}


//----------------------------------------------------------------------------
DragDropPort* DragDropDocument::ToPort(DragDropPort* pPort1, DragDropPort* pPort2){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return pPort2;
}
