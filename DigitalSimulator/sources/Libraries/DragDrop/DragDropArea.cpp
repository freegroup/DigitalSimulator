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
#include "DragDrop.h"
#include "defines.h"
#include <assert.h>

#include "DragDropArea.h"
#include "DragDropDocument.h"
static BOOL bGrowArea = TRUE;


IMPLEMENT_SERIAL(DragDropArea, DragDropObject, 2)

//----------------------------------------------------------------------------
DragDropArea::DragDropArea() : inherited(CPoint(0,0)){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_bGrabChildSelection = TRUE;
	m_bShrinkToFitPending = TRUE;
}


//----------------------------------------------------------------------------
DragDropArea::~DragDropArea(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Delete all of the Area's children.
    // Note that delete will be recursive if there is an inner Area.
    while (!m_oblistObjects.IsEmpty()){
        DragDropObject* pObject = (DragDropObject*) m_oblistObjects.RemoveHead();
        DragDropDocument* pDoc  = pObject->GetDocument();

        if (pDoc) {
           pDoc->UpdateAllViews(NULL, Update_Delete, pObject);
        }


        // pObject->SetDocument(NULL);  Wird sonst nicht von dem Document entfernt!!

        
        delete pObject;
    }   
}

//----------------------------------------------------------------------------                                                 
DragDropObject* DragDropArea::Clone() const{   
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pObject = inherited::Clone();
    ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropArea)));                  
    DragDropArea* pArea =(DragDropArea*) pObject;

    pArea->m_bGrabChildSelection = m_bGrabChildSelection;
    
    for (POSITION pos = GetFirstChildPos(); pos != NULL; ) {
        DragDropObject* pObject = GetNextChild(pos);
        DragDropObject* pNewObj = pObject->Clone();
        pArea->AddChildAtTail(pNewObj);
    }

    return pObject;
}

//----------------------------------------------------------------------------
POSITION DragDropArea::GetFirstChildPos() const{
//----------------------------------------------------------------------------
	PROC_TRACE;


   return m_oblistObjects.GetHeadPosition();
}


//----------------------------------------------------------------------------
DragDropObject* DragDropArea::GetNextChild(POSITION& pos) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return(DragDropObject*)m_oblistObjects.GetNext(pos);  
}


//----------------------------------------------------------------------------
POSITION DragDropArea::AddChildAtHead(DragDropObject* pObject, BOOL bForceFirstDraw) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    pObject->m_pParentArea = this;        
    POSITION pos = m_oblistObjects.AddHead(pObject);
    pObject->SetDocument(GetDocument());    // set child document to same as Area document
    GeometryChangeChild(pObject);           // snap the area to the children
    if (bForceFirstDraw) pObject->SetUpdateNeeded(TRUE);
    return pos;
}


//----------------------------------------------------------------------------
POSITION DragDropArea::AddChildAtTail(DragDropObject* pObject, BOOL bForceFirstDraw) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    pObject->m_pParentArea = this;
    POSITION pos = m_oblistObjects.AddTail(pObject);
    pObject->SetDocument(GetDocument());    // set child document to same as Area document
    GeometryChangeChild(pObject);           // snap the area to the children
    if (bForceFirstDraw) pObject->SetUpdateNeeded(TRUE);
    return pos;                                                  
}

//----------------------------------------------------------------------------
void DragDropArea::SetDocument(DragDropDocument* pDocument){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::SetDocument(pDocument);    // Fill in Area's document
    
   for (POSITION pos = GetFirstChildPos(); pos != NULL; ) {
      DragDropObject* pObject = GetNextChild(pos);
		// If we are setting document to NULL, then let the views know this is happening
		if (pDocument == NULL) {
			DragDropDocument* pDoc = pObject->GetDocument();
			if (pDoc) pDoc->UpdateAllViews(NULL, Update_Delete, pObject);
		}
        pObject->SetDocument(pDocument);
    }
}

//----------------------------------------------------------------------------
BOOL DragDropArea::ValidateChildRect(DragDropObject* pChildObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (!bGrowArea) 
       return TRUE;    // if not growing, then this test won't be valid
                                    // (not a good thing, but we know that...)

    CRect rectArea = GetBoundingRect();
    CRect rectChild = pChildObject->GetBoundingRect();
    
    if (rectChild.left < rectArea.left)     return FALSE;
    if (rectChild.right > rectArea.right)   return FALSE;
    if (rectChild.top > rectArea.top)       return FALSE;
    if (rectChild.bottom < rectArea.bottom) return FALSE;
    return TRUE;
}                 


//----------------------------------------------------------------------------
DragDropObject* DragDropArea::PickInArea(CClientDC* pDC, CPoint ptToCheckLP, BOOL bSelectableOnly){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CPoint ptToCheckDP;
    ptToCheckDP.x = ptToCheckLP.x;
    ptToCheckDP.y = ptToCheckLP.y;
    
    pDC->LPtoDP(&ptToCheckDP);  // PtInObject needs both LP and DP.

    for (POSITION pos = m_oblistObjects.GetTailPosition(); pos != NULL; ) {
        DragDropObject* pObject =(DragDropObject*) m_oblistObjects.GetPrev(pos);

        if (!pObject->isVisible())
           continue;
        if (!pObject->PtInObject(pDC, ptToCheckLP, ptToCheckDP))
           continue;
        if (pObject->IsKindOf(RUNTIME_CLASS(DragDropArea))){
            DragDropArea* pArea = (DragDropArea*) pObject;
            DragDropObject* pObjectInArea = pArea->PickInArea(pDC, ptToCheckLP, bSelectableOnly);
    
            if (pObjectInArea != NULL) 
               return pObjectInArea;
        }
        if (!bSelectableOnly) 
           return pObject;
        if (pObject->IsSelectable())
            return pObject;
        else{
            while (pObject->m_pParentArea){
                pObject = pObject->m_pParentArea;
                ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropArea)));

                if (((DragDropArea*) pObject)->m_bGrabChildSelection) 
                   return pObject;
            }
        }           
    }
    return NULL;
}


//----------------------------------------------------------------------------
void DragDropArea::GeometryChange(CRect* pRectPrevious){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_oblistObjects.IsEmpty()) 
       return;
    
    SuspendChildUpdates();

    
    int pw = abs(pRectPrevious->Width());
    int ph = abs(pRectPrevious->Height());
    CPoint oldxy, newxy;
    CSize deltaxy;
    oldxy = pRectPrevious->TopLeft();
    newxy = GetTopLeft();
    deltaxy = newxy - oldxy;  
    
    if (pw == GetWidth() && ph == GetHeight()) {
        POSITION pos;
        CPoint ptLoc;
        for (pos = GetFirstChildPos(); pos != NULL;) {
            DragDropObject* pObject =(DragDropObject*) GetNextChild(pos);
            CRect rect = pObject->GetBoundingRect();
            pObject->SetBoundingRect (rect.left + deltaxy.cx, rect.top + deltaxy.cy,
                                           rect.right + deltaxy.cx, rect.bottom + deltaxy.cy);
        }
        ResumeChildUpdates();
        return;
    }
    
    float xGrow, yGrow, xOffset, yOffset;
    xGrow = yGrow = 1.0F;
    xOffset = yOffset = 0.0F;    // depends on child position
    
    // calculate the growth in X and Y as a percentage
    
    if (pw != 0) xGrow = (float)GetWidth() / (float)pw;
    if (ph != 0) yGrow = (float)GetHeight() / (float)ph;

    POSITION pos;
    for (pos = GetFirstChildPos(); pos != NULL;) {
        DragDropObject* pObject =(DragDropObject*) GetNextChild(pos);
        CPoint loc = pObject->GetTopLeft();
        int w = pObject->GetWidth();
        int h = pObject->GetHeight();
        loc.x = newxy.x + int(float(abs(loc.x - oldxy.x)) * xGrow );
        loc.y = newxy.y - int(float(abs(loc.y - oldxy.y)) * yGrow );
        
        if (pObject->IsResizable()){
            w = int(xGrow * w);
            h = int(yGrow * h);
        }
        pObject->SetBoundingRect (loc.x, loc.y, loc.x + w, loc.y - h);
    }
    ResumeChildUpdates();
	ShrinkToFit();
}   

//----------------------------------------------------------------------------
BOOL DragDropArea::ShrinkToFit(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_bShrinkToFitPending = FALSE;

    BOOL sizeHasChanged = FALSE;
    //  Shrink the area to enclose its children
    // create a rectangle that will be the actual smallest bounding rectangle
    // for all of the children    
    CRect currentRectArea = GetBoundingRect();
    CRect rectArea;
    POSITION pos;
    pos = GetFirstChildPos();
    if (!pos) 
       return FALSE;
    DragDropObject* pObject =(DragDropObject*) GetNextChild(pos);
    rectArea = pObject->GetBoundingRect();
    
    while (pos) {
        DragDropObject* pObject =(DragDropObject*) GetNextChild(pos);
        assert( pObject != NULL);

        CRect rectChild = pObject->GetBoundingRect();
    
        if (rectChild.left < rectArea.left)
            rectArea.left = rectChild.left;
        if (rectChild.right > rectArea.right)
            rectArea.right = rectChild.right;
        if (rectChild.top > rectArea.top)
            rectArea.top = rectChild.top;
        if (rectChild.bottom < rectArea.bottom)
            rectArea.bottom = rectChild.bottom;
    }
    SetBoundingRectForce(rectArea.left, rectArea.top, rectArea.right, rectArea.bottom);
    if (currentRectArea != rectArea)
        sizeHasChanged = TRUE;

	DragDropDocument* pDoc = GetDocument();
	if (pDoc) {
		pDoc->GrowDocument(rectArea.right, -rectArea.bottom);		
	}

    return sizeHasChanged;
}

//----------------------------------------------------------------------------
void DragDropArea::GeometryChangeChild(DragDropObject* pChildObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_bShrinkToFitPending = TRUE;	

    if (ValidateChildRect(pChildObject)) 
       return;

    ShrinkToFit();
}

//----------------------------------------------------------------------------
BOOL DragDropArea::paint(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_bShrinkToFitPending) 
      ShrinkToFit();

   if (!isVisible()) 
      return TRUE;

             
   for (POSITION pos = GetFirstChildPos(); pos != NULL; ){
      DragDropObject* pObject = GetNextChild(pos);
      pObject->paint(pDC);
   }
  
   return TRUE;
}



//----------------------------------------------------------------------------
void DragDropArea::BringObjectToFront(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;
        
    POSITION pos;  
    if( ( pos = m_oblistObjects.Find(pObject) ) != NULL ){                                        
        m_oblistObjects.RemoveAt(pos);
        m_oblistObjects.AddTail(pObject);
        pObject->SetUpdateNeeded(TRUE);
    }
}

//----------------------------------------------------------------------------
void DragDropArea::SendObjectToBack(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;
        
    POSITION pos;  
    if( ( pos = m_oblistObjects.Find(pObject) ) != NULL ){                                        
        m_oblistObjects.RemoveAt(pos);
        m_oblistObjects.AddHead(pObject);
        pObject->SetUpdateNeeded(TRUE);
    }
}

//----------------------------------------------------------------------------
void DragDropArea::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

    inherited::Serialize(ar);

    if (ar.IsStoring()){
        ARC_BOOL(m_bGrabChildSelection);
        m_oblistObjects.Serialize(ar);
    }
    else    {
        DEARC_BOOL(m_bGrabChildSelection); 
        m_oblistObjects.Serialize(ar);
    }                             

}

