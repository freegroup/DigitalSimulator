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
#include "DragDropapp.h"
#include "DragDropClientApp.h"
#include "DragDropSelection.h"
#include "DragDropDocument.h"
#include "DragDropView.h"
#include "DragDropHandle.h"

IMPLEMENT_DYNCREATE(DragDropSelection, CObject)

//----------------------------------------------------------------------------
DragDropSelection::DragDropSelection(){ 
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_pView = NULL; 
} 

//----------------------------------------------------------------------------
DragDropSelection::~DragDropSelection(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void DragDropSelection::SetView(DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_pView = pView;    
}   

//----------------------------------------------------------------------------
DragDropObject* DragDropSelection::SelectObject(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(pObject==NULL) return NULL;

   // First clear old selection
   ClearSelection();
    
   // tell object it has been selected, and allow that object to "redirect" the
   // selection by returning a different object 
    
   pObject = pObject->RedirectSelection();

   // Make this object the first item in the list
   m_oblistSelectedObjects.AddHead(pObject);

	// tell the object it has gained selection
	pObject->GainedSelection(this);     // new selection
    // if the user deleted the select object, return NULL
   if (m_oblistSelectedObjects.GetCount() == 0)
       pObject = NULL;
   
   return pObject;
}

//----------------------------------------------------------------------------
DragDropObject* DragDropSelection::ExtendSelection(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pObject != NULL);
   if(pObject==NULL) return NULL;

   //if object is already in selection, no-op
   if (IsInSelection (pObject)) return pObject;
    
   // tell object it has been selected, and allow that object to "redirect" the
   // selection by returning a different object 
    
   pObject = pObject->RedirectSelection();
   
   // do not change the primary selection
   m_oblistSelectedObjects.AddTail(pObject);

	// tell the object it has gained selection
   pObject->GainedSelection(this);     // new selection
   // if the user deleted the selected object, return NULL
   if (m_oblistSelectedObjects.GetCount() == 0) 
        pObject = NULL;

   return pObject;
}

//----------------------------------------------------------------------------
void DragDropSelection::ToggleSelection(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pObject != NULL);
   if(pObject==NULL) return ;
   
   DragDropObject* pPrimary = PrimarySelection();  
    
   pObject = pObject->RedirectSelection();

// If object is already in selection remove it
   POSITION pos;
   if (pos = m_oblistSelectedObjects.Find(pObject)){
        m_oblistSelectedObjects.RemoveAt(pos);   
        pObject->LostSelection(this);
        
        // it's possible we just removed the primary selection.  if so,
        // we need to notify the new primary to change its handles   
        
        if (pObject == pPrimary) {
            pPrimary = PrimarySelection();          // get the new one
            if (pPrimary == NULL) return;           // selection went empty
            pPrimary->LostSelection(this);          // tell it to lose old handles
            pPrimary->GainedSelection(this);        // and grab new ones.
        }
        return; 
    }
    
    // otherwise, add it, but do not change the primary selection
    m_oblistSelectedObjects.AddTail(pObject);
    
    pObject->GainedSelection(this);     // new selection
}


//----------------------------------------------------------------------------
DragDropObject* DragDropSelection::PrimarySelection() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_oblistSelectedObjects.IsEmpty())
        return NULL;
    else
        return(DragDropObject*) m_oblistSelectedObjects.GetHead();
}


//----------------------------------------------------------------------------
POSITION DragDropSelection::GetFirstSelectedPos(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_oblistSelectedObjects.GetHeadPosition();
}


//----------------------------------------------------------------------------
DragDropObject* DragDropSelection::GetNextSelected(POSITION& pos){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(pos == NULL)
      return NULL;

   return(DragDropObject*)m_oblistSelectedObjects.GetNext(pos);
}



//----------------------------------------------------------------------------
void DragDropSelection::ClearSelection(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_oblistSelectedObjects.IsEmpty()) 
       return;

    if (pObject == NULL){
        while (!m_oblistSelectedObjects.IsEmpty()) {
            DragDropObject* pObj =(DragDropObject*) m_oblistSelectedObjects.RemoveHead(); 
            pObj->LostSelection(this);
        }
    }
    else{
        POSITION pos;
        if (pos = m_oblistSelectedObjects.Find(pObject))    // is the object in the selection list?
        {
            m_oblistSelectedObjects.RemoveAt(pos);
            pObject->LostSelection(this);       
        }    
    }
}

//----------------------------------------------------------------------------
void DragDropSelection::ClearSelectionHandles(DragDropObject* pObj){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (pObj) {
		pObj->HideSelectionHandles(this);
	}
	else {
		for (POSITION pos = GetFirstSelectedPos(); pos != NULL;){
			DragDropObject* pObject = GetNextSelected(pos);
			pObject->HideSelectionHandles(this);
		}
   }
}

//----------------------------------------------------------------------------}
void DragDropSelection::RestoreSelectionHandles(DragDropObject* pObj){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (pObj) {
        // don't randomly restore handles to object without verifying it is in the selection
        if (IsInSelection (pObj)) {
		    pObj->ShowSelectionHandles(this);
        }
	}
	else {
		for (POSITION pos = GetFirstSelectedPos(); pos != NULL;){
			DragDropObject* pObject = GetNextSelected(pos);
			pObject->ShowSelectionHandles(this);
		}
	}
}

//----------------------------------------------------------------------------
void DragDropSelection::DeleteObjects(){
//----------------------------------------------------------------------------
	PROC_TRACE;
    
    while (!m_oblistSelectedObjects.IsEmpty()) {
       // FIXME: casting auf basisklasse nicht besonders gut bei einem delete
       //
       delete /*(DragDropObject*)*/m_oblistSelectedObjects.GetHead();
    }
}

//----------------------------------------------------------------------------    
BOOL DragDropSelection::IsDraggable(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_oblistSelectedObjects.IsEmpty())
        return FALSE;

//**todo run down all the list of selected nodes...

    DragDropObject* pObject =(DragDropObject*)m_oblistSelectedObjects.GetHead();  //** just use list head for now
    return pObject->IsDraggable();      
}

//----------------------------------------------------------------------------
BOOL DragDropSelection::IsInSelection (DragDropObject* pObject){   
//----------------------------------------------------------------------------
	PROC_TRACE;

   //if object is in selection, return TRUE
   if (pObject == NULL)
       return FALSE;
   if (m_oblistSelectedObjects.Find(pObject))
       return TRUE;

   DragDropObject* pObjectR = pObject->RedirectSelection();
    
   if ((pObjectR != pObject) && m_oblistSelectedObjects.Find(pObjectR)) {
       return TRUE;    
   }    

   return FALSE;
}

//----------------------------------------------------------------------------
POSITION DragDropSelection::GetFirstHandlePos(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_oblistHandleObjects.GetHeadPosition();
}

//----------------------------------------------------------------------------
DragDropHandle* DragDropSelection::GetNextHandle(POSITION& pos){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return(DragDropHandle*)m_oblistHandleObjects.GetNext(pos);
}

//----------------------------------------------------------------------------
void DragDropSelection::CreateBoundingHandle (DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CRect rect = pObject->GetBoundingRect();
    rect.InflateRect(5, -5);
    DragDropHandle* pHandle = CDragDropApp::AllocHandle();   // attempt alloc from free list
    if (pHandle){
        pHandle->SetBoundingRect(&rect);                // set the rectangle
        pHandle->SetCursor(CM::ARROW);  // set the cursor
    }    
    else 
        pHandle = new DragDropHandle(&rect);         // alloc failed, create new
    
    pHandle->SetSelectable(FALSE);      // avoid anyone grabbing this highlight rectangle
    pHandle->SetHandleType (NoHandle);  
    pHandle->SetHandleFor (pObject);
    
    pHandle->SetStockPen(DragDropNoStock);    // force non-stock Pen
    COLORREF color;
    if (PrimarySelection() == pObject)
        color = CDragDropApp::GetPrimarySelectionColor();
    else        
        color = CDragDropApp::GetSecondarySelectionColor();
        
    pHandle->SetPenColor(color);
    pHandle->SetPenWidth(4);
    pHandle->SetStockBrush (HOLLOW_BRUSH);  // let the object show through
   
    AddHandle (pHandle);    
}

//----------------------------------------------------------------------------
DragDropHandle* DragDropSelection::CreateResizeHandle (DragDropObject* pObject, int x, int y, int nHandleType, BOOL bFilled){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CPoint loc; 
   CSize size;

   // To avoid round off errors that cause handles to be slightly different sizes,
   // do all of the bounding rect calculations in Pixels (DP), then convert to Logical (LP)

   CClientDC dc(m_pView);
   m_pView->OnPrepareDC(&dc);
   CPoint point(x,y);
   dc.LPtoDP(&point);
   CRect rect (point.x-2, point.y-2, point.x+3, point.y+3);  // use "3" in second point because of the way rectangles draw
   dc.DPtoLP(&rect);   // convert pixels to logical
   loc.x = rect.left;
   loc.y = rect.top;
   size.cx = rect.right-rect.left;
   size.cy = abs(rect.bottom-rect.top);

   CM::Type cursor = CM::ARROW;
   CM::Type cursors[9] = {
      CM::SIZE,
      CM::SIZENWSE,
      CM::SIZENS,
      CM::SIZENESW,
      CM::SIZEWE,
      CM::SIZENWSE,
      CM::SIZENS,
      CM::SIZENESW,
      CM::SIZEWE
   };

   if (nHandleType <= 9) 
      cursor = cursors[nHandleType];

   CDragDropApp* pApp = (CDragDropApp*)AfxGetApp(); 
   DragDropHandle* pHandle = pApp->AllocHandle();   // attempt alloc from free list
   if (pHandle)
   {
     pHandle->SetBoundingRect(loc, size);   // set the rectangle
     pHandle->SetCursor(cursor);            // set the cursor
   }    
   else 
     pHandle = new DragDropHandle(loc, size, cursor);

   pHandle->SetHandleFor (pObject);
   pHandle->SetHandleType (nHandleType);

   if (nHandleType == NoHandle)
     pHandle->SetSelectable(FALSE);      // avoid anyone grabbing this non-resize handle
   else
     pHandle->SetSelectable(TRUE);       // allow grabbing this resize handle    

   pHandle->SetPenColor(pApp->GetPaletteIndexBlack()); // make sure it is black pen (free list might be anything)
   pHandle->SetPenWidth(1);

   if (bFilled)  {
     pHandle->SetStockBrush(DragDropNoStock);  // force non-stock brush
     COLORREF color;
     CDragDropApp* pApp = (CDragDropApp*)AfxGetApp(); 
     if (PrimarySelection() == pObject)
         color = pApp->GetPrimarySelectionColor();
     else        
         color = pApp->GetSecondarySelectionColor();
      
     pHandle->SetBrushColor(color);
   }       
   else
     pHandle->SetStockBrush (HOLLOW_BRUSH);  // let the object show through

   AddHandle (pHandle);

   return pHandle;
}

//----------------------------------------------------------------------------
void DragDropSelection::AddHandle (DragDropHandle* pHandle){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_oblistHandleObjects.AddHead(pHandle);
   m_pView->AddObjectAtTail(pHandle);
}


//----------------------------------------------------------------------------
void DragDropSelection::DeleteHandles (DragDropObject* pObject){    
//----------------------------------------------------------------------------
	PROC_TRACE;

   POSITION oldpos;
    for (POSITION pos = GetFirstHandlePos(); pos != NULL; )
    {
        oldpos = pos;
        DragDropHandle* pHandle = GetNextHandle(pos);
        if (pHandle->GetHandleFor() == pObject) 
        {
             m_oblistHandleObjects.RemoveAt(oldpos);    // pull it out of list
             //DragDropDocument* pDocument = ((DragDropView*)m_pView)->GetDocument();
             CDragDropApp* pApp = (CDragDropApp*)AfxGetApp(); 
             m_pView->RemoveObject(pHandle);          // and delete it
             pApp->DeallocHandle(pHandle);
        }
    }
}

//----------------------------------------------------------------------------
void DragDropSelection::HideHandles (DragDropObject* pObject){    
//----------------------------------------------------------------------------
	PROC_TRACE;

   POSITION oldpos;
    for (POSITION pos = GetFirstHandlePos(); pos != NULL; )
    {
        oldpos = pos;
        DragDropHandle* pHandle = GetNextHandle(pos);
        if (pHandle->GetHandleFor() == pObject) pHandle->SetVisible(FALSE);
    }
}

//----------------------------------------------------------------------------
void DragDropSelection::ShowHandles (DragDropObject* pObject){    
//----------------------------------------------------------------------------
	PROC_TRACE;

   POSITION oldpos;
   for (POSITION pos = GetFirstHandlePos(); pos != NULL; )
    {
        oldpos = pos;
        DragDropHandle* pHandle = GetNextHandle(pos);
        if (pHandle->GetHandleFor() == pObject) pHandle->SetVisible(TRUE);
    }
}
