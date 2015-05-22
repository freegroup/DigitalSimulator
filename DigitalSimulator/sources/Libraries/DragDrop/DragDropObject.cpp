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
#include "DragDropObject.h"
#include "DragDropDocument.h"
#include "DragDropSelection.h"
#include "DragDropView.h"

CRect   DragDropObject::m_rectPrevBounding;  // previous size, position (Used in OnUpdate)

IMPLEMENT_SERIAL(DragDropObject, CObject, 2)

//----------------------------------------------------------------------------
DragDropObject::DragDropObject(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_pView       = NULL;
   m_pParentArea = NULL;
   m_pDocument   = NULL;
}

//----------------------------------------------------------------------------
DragDropObject::DragDropObject(CRect* pRect){
//----------------------------------------------------------------------------
	PROC_TRACE;

   Init(pRect);
}

//----------------------------------------------------------------------------
DragDropObject::DragDropObject(CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // creates a null-sized object at point
   CRect rect(point.x, point.y, point.x, point.y); 
   Init(&rect);
}

//----------------------------------------------------------------------------
DragDropObject::DragDropObject(CPoint location, CSize size){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CRect rect(location.x, location.y,location.x + size.cx, location.y - size.cy); 
   Init (&rect);
}

//----------------------------------------------------------------------------
void DragDropObject::Init (CRect* pRect){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pRect !=NULL);

   m_boundingRect.CopyRect(pRect);
   m_wFlags = flagVisible | flagSelectable | flagDraggable | flagResizable;
   m_pParentArea = NULL;
   m_pDocument   = NULL;
   m_pView       = NULL;
}

//----------------------------------------------------------------------------
DragDropObject::~DragDropObject(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    // Make sure the object is not still a part of a document
     
    if (m_pDocument) 
       m_pDocument->RemoveObject(this);
    if (m_pView)     
       m_pView->RemoveObject(this);
}

//----------------------------------------------------------------------------
DragDropObject* DragDropObject::Clone() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   CRuntimeClass* objClass = GetRuntimeClass();

    assert(objClass != NULL);
    if(objClass ==NULL)
       return NULL;

    DragDropObject* pObject =(DragDropObject*)objClass->CreateObject(); 

    assert(pObject != NULL);
    if(pObject ==NULL)
       return NULL;

    pObject->m_boundingRect.CopyRect(m_boundingRect);
    pObject->m_wFlags      = m_wFlags;
    pObject->m_pDocument   = NULL;
    pObject->m_pView       = NULL;
    pObject->m_pParentArea = NULL; 
    return pObject;
}
 

//----------------------------------------------------------------------------
BOOL DragDropObject::isVisible() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return (m_wFlags & flagVisible);
}

//---------------------------------------------------------------------------- 
BOOL DragDropObject::paint(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pDC != NULL);
   if(pDC==NULL)
      return FALSE;

   CPen pen;


   if (!pen.CreatePen(PS_SOLID, 1, RGB(255,0,0)))
     return FALSE;   

   CPen* pOldPen = pDC->SelectObject(&pen);
   pDC->Rectangle(m_boundingRect);    
   pDC->MoveTo(m_boundingRect.TopLeft());
   pDC->LineTo(m_boundingRect.BottomRight());
   pDC->MoveTo(m_boundingRect.right, m_boundingRect.top);
   pDC->LineTo(m_boundingRect.left, m_boundingRect.bottom);
   pDC->SelectObject(pOldPen);

   return TRUE;
}

//----------------------------------------------------------------------------
void DragDropObject::GeometryChange(CRect* pRectPrevious){
//----------------------------------------------------------------------------
	PROC_TRACE;
 	if (m_pDocument) m_pDocument->SetModifiedFlag();
}

//----------------------------------------------------------------------------
void DragDropObject::GeometryChangeChild(DragDropObject* pChildObject){
//----------------------------------------------------------------------------
	PROC_TRACE;
  	if (m_pDocument) m_pDocument->SetModifiedFlag();
}

//----------------------------------------------------------------------------
void DragDropObject::SetUpdateNeeded(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_pDocument && !SuspendUpdates()){
        if (m_pParentArea == NULL || !m_pParentArea->IsSuspendChildUpdates()) {
            SetClearOnUpdate(bFlag);
            if (!m_pDocument->UpdatesSuspended()) 
               m_pDocument->UpdateAllViews(NULL, Update_Object, this);
        }
    }
    else if (m_pView !=NULL){
        SetClearOnUpdate(bFlag);
        m_pView->OnUpdate(NULL, Update_Object, this);
    }
  
}

//----------------------------------------------------------------------------
BOOL DragDropObject::PtInObject(CClientDC* pDC, CPoint ptToCheckLP, CPoint ptToCheckDP){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CRect rectNode = GetBoundingRect();
           
    if (ptToCheckLP.y > rectNode.top)    return FALSE;
    if (ptToCheckLP.y < rectNode.bottom) return FALSE;
    if (ptToCheckLP.x < rectNode.left)   return FALSE;
    if (ptToCheckLP.x > rectNode.right)  return FALSE;
            
    return TRUE;

//	return rectNode.PtInRect(ptToCheckLP);
}

//----------------------------------------------------------------------------
void DragDropObject::SetBoundingRect(int nLeft, int nTop, int nRight, int nBottom){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if ((m_boundingRect.left   == nLeft) &&
      (m_boundingRect.top     == nTop)	 &&
      (m_boundingRect.right   == nRight) &&
      (m_boundingRect.bottom  == nBottom))	return;	// hasn't changed - no-op    

   assert(nTop >= nBottom);
   assert(nRight >= nLeft);
	
   m_rectPrevBounding = m_boundingRect;  // save old one
   SetPrevRectValid(TRUE);
   m_boundingRect.left   = nLeft;
   m_boundingRect.top    = nTop;
   m_boundingRect.right  = nRight;
   m_boundingRect.bottom = nBottom;
    
   SetUpdateNeeded(FALSE);   
   SetPrevRectValid(FALSE);
    
   GeometryChange(&m_rectPrevBounding);            // Give object a chance to do what it must
    
   if (m_pParentArea) 
      m_pParentArea->GeometryChangeChild(this);

   if (m_pDocument) m_pDocument->SetModifiedFlag();
}                                                                            

//----------------------------------------------------------------------------
void DragDropObject::SetBoundingRectForce(int nLeft, int nTop, int nRight, int nBottom){
//----------------------------------------------------------------------------
	PROC_TRACE;

    assert(nTop >= nBottom);
    assert(nRight >= nLeft);
	
    // this form of SetBoundingRect is not for normal use.  it does none of the
    // DoCalculate necessary to keep the screen up to date.
    m_boundingRect.left   = nLeft;
    m_boundingRect.top    = nTop;
    m_boundingRect.right  = nRight;
    m_boundingRect.bottom = nBottom;    
    
}


//----------------------------------------------------------------------------
void DragDropObject::SetBoundingRect(CRect* pRect){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pRect !=NULL);

   SetBoundingRect(pRect->left, pRect->top, pRect->right, pRect->bottom);
}


//----------------------------------------------------------------------------
void DragDropObject::SetBoundingRect(CPoint loc, CSize size){
//----------------------------------------------------------------------------
	PROC_TRACE;

    SetBoundingRect(loc.x, loc.y, loc.x + size.cx, loc.y - size.cy);
}


//----------------------------------------------------------------------------
CPoint DragDropObject::GetSpotLocation(DragDropObject::SpotNumber nSpot){
//----------------------------------------------------------------------------
	PROC_TRACE;

    assert((nSpot >= spotCenter) && (nSpot <= spotLeftCenter));

    // This default implementation assumes that the object is rectangular,
    // with spots numbered as follows (see SpotNumbers enum):
    //
    //      1   2   3
    //
    //      8   0   4
    //
    //      7   6   5
    
    CPoint  pointSpot;
    CPoint  pointTopLeft = GetTopLeft();
    
    switch (nSpot) {
        case spotCenter:        // 0
            pointSpot.x = pointTopLeft.x + (GetWidth()/2);
            pointSpot.y = pointTopLeft.y - (GetHeight()/2);
            break;
            
        case spotTopLeft:       // 1
            pointSpot = pointTopLeft;
            break;
            
        case spotTopCenter:     // 2
            pointSpot.x = pointTopLeft.x + (GetWidth()/2);
            pointSpot.y = pointTopLeft.y;
            break;
            
        case spotTopRight:      // 3
            pointSpot.x = pointTopLeft.x + GetWidth();
            pointSpot.y = pointTopLeft.y;
            break;
            
        case spotRightCenter:   // 4
            pointSpot.x = pointTopLeft.x + GetWidth();
            pointSpot.y = pointTopLeft.y - (GetHeight()/2);
            break;
            
        case spotBottomRight:   // 5
            pointSpot.x = pointTopLeft.x + GetWidth();
            pointSpot.y = pointTopLeft.y - GetHeight();
            break;
            
        case spotBottomCenter:  // 6
            pointSpot.x = pointTopLeft.x + (GetWidth()/2);
            pointSpot.y = pointTopLeft.y - GetHeight();
            break;
            
        case spotBottomLeft:    // 7
            pointSpot.x = pointTopLeft.x;
            pointSpot.y = pointTopLeft.y - GetHeight();
            break;
            
        case spotLeftCenter:    // 8
            pointSpot.x = pointTopLeft.x;
            pointSpot.y = pointTopLeft.y - (GetHeight()/2);
            break;
    }
    
    return pointSpot;
}

//-----------------------------------------------------------------------------
void DragDropObject::SetLocation(CPoint pPoint)
//-----------------------------------------------------------------------------
{
    SetLocation(pPoint.x, pPoint.y);
}

//-----------------------------------------------------------------------------
void DragDropObject::SetLocation(int x, int y){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   CSize sizeThis = GetSize();
   SetBoundingRect(x, y, x + sizeThis.cx, y - sizeThis.cy);
}                                        

//-----------------------------------------------------------------------------
void DragDropObject::SetLocationOffset(CPoint pPoint, CSize pOffset){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   SetLocationOffset(pPoint.x, pPoint.y, pOffset.cx, pOffset.cy);
}


//-----------------------------------------------------------------------------
void DragDropObject::SetLocationOffset(CPoint pPoint, int cx, int cy){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   SetLocationOffset(pPoint.x, pPoint.y, cx, cy);
}     


//-----------------------------------------------------------------------------
void DragDropObject::SetLocationOffset(int x, int y, int cx, int cy){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   CSize sizeThis = GetSize();
   int nLeft   = x + cx;
   int nTop    = y + cy;
   SetBoundingRect(nLeft, nTop, nLeft + sizeThis.cx, nTop - sizeThis.cy);
}         

//-----------------------------------------------------------------------------
void DragDropObject::SetSpotLocation(SpotNumber nThisSpot, CPoint point){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   SetSpotLocationOffset(nThisSpot, point.x, point.y, 0, 0);
}


//-----------------------------------------------------------------------------
void DragDropObject::SetSpotLocation(SpotNumber nThisSpot, DragDropObject* pOtherObject,
                                SpotNumber nOtherSpot){
//-----------------------------------------------------------------------------
     CPoint pointOtherSpot = pOtherObject->GetSpotLocation(nOtherSpot);
     
     SetSpotLocationOffset(nThisSpot, pointOtherSpot.x, pointOtherSpot.y,  0, 0);
}


//-----------------------------------------------------------------------------
void DragDropObject::SetSpotLocation(SpotNumber nThisSpot, int x, int y){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   SetSpotLocationOffset(nThisSpot, x, y,  0, 0);
}

//-----------------------------------------------------------------------------
void DragDropObject::SetSpotLocationOffset(SpotNumber nThisSpot, CPoint point,
                                      int cx, int cy){
//-----------------------------------------------------------------------------
     SetSpotLocationOffset(nThisSpot, point.x, point.y, cx, cy);
}


//-----------------------------------------------------------------------------
void DragDropObject::SetSpotLocationOffset(SpotNumber nThisSpot, DragDropObject* pOtherObject,
                                      SpotNumber nOtherSpot, int cx, int cy){
//-----------------------------------------------------------------------------
   assert(pOtherObject != NULL);
   
   CPoint pointOtherSpot = pOtherObject->GetSpotLocation(nOtherSpot);
     
   SetSpotLocationOffset(nThisSpot, pointOtherSpot.x, pointOtherSpot.y, cx, cy);
}


//-----------------------------------------------------------------------------
void DragDropObject::SetSpotLocationOffset(SpotNumber nThisSpot, int x, int y, int cx, int cy){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   CPoint pointThisLocation = GetTopLeft();
   CPoint pointThisSpot = GetSpotLocation(nThisSpot);

   int    nLeft = x + cx - (pointThisSpot.x - pointThisLocation.x);
   int    nTop = y + cy - (pointThisSpot.y - pointThisLocation.y);

   CSize  sizeThis = GetSize();

   SetBoundingRect(nLeft, nTop, nLeft + sizeThis.cx, nTop - sizeThis.cy);
}         

//----------------------------------------------------------------------------
void DragDropObject::SetSize(CSize pSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetSize(pSize.cx, pSize.cy);
}

//----------------------------------------------------------------------------
void DragDropObject::SetSize(int cx, int cy){
//----------------------------------------------------------------------------
	PROC_TRACE;

     SetBoundingRect(m_boundingRect.left, m_boundingRect.top, 
                     m_boundingRect.left + cx, m_boundingRect.top - cy);
}                                                                            


//----------------------------------------------------------------------------
void DragDropObject::SetVisible(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

     if (bFlag){
        if (isVisible()) 
           return;            // no-op if already visible (avoids any flash on screen)
        m_wFlags = m_wFlags | flagVisible;  // 'OR' in Visible bit
        SetUpdateNeeded(FALSE);             // now visible, draw region
     }
     else{
        if (!isVisible()) 
           return;           // no-op if already not visible (avoids any flash on screen)
        m_wFlags = m_wFlags & ~flagVisible; // 'AND NOT' Visible
        SetUpdateNeeded(TRUE);              // now invisible, erase and redraw region
     }
}

//----------------------------------------------------------------------------
void DragDropObject::SetSelectable(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

     if (bFlag)
        m_wFlags = m_wFlags | flagSelectable;   // 'OR' in Selectable bit
     else
        m_wFlags = m_wFlags & ~flagSelectable;  // 'AND NOT' Selectable
}


//----------------------------------------------------------------------------
void DragDropObject::SetResizable(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
        m_wFlags = m_wFlags | flagResizable;    // 'OR' in Resizable bit
     else
        m_wFlags = m_wFlags & ~flagResizable;   // 'AND NOT' Resizable
}

//----------------------------------------------------------------------------
void DragDropObject::SetDraggable(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
        m_wFlags = m_wFlags | flagDraggable;    // 'OR' in Draggable bit
     else
        m_wFlags = m_wFlags & ~flagDraggable;   // 'AND NOT' Draggable
}

//----------------------------------------------------------------------------
void DragDropObject::SetPrevRectValid(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;
   if (bFlag)
      m_wFlags = m_wFlags | flagPrevRectValid;    // 'OR' in PrevRectValid bit
   else
      m_wFlags = m_wFlags & ~flagPrevRectValid;   // 'AND NOT' PrevRectValid
}

//----------------------------------------------------------------------------
void DragDropObject::SetSuspendChildUpdates(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
        m_wFlags = m_wFlags | flagSuspendChildUpdates;  // 'OR' in SuspendChildUpdates bit
     else
        m_wFlags = m_wFlags & ~flagSuspendChildUpdates; // 'AND NOT' SuspendChildUpdates
}

//----------------------------------------------------------------------------
void DragDropObject::SetSuspendUpdates(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
        m_wFlags = m_wFlags | flagSuspendUpdates;  // 'OR' in SuspendUpdates bit
     else {
        m_wFlags = m_wFlags & ~flagSuspendUpdates; // 'AND NOT' SuspendUpdates
        SetUpdateNeeded(FALSE);                     // loss of info here on whether this should be TRUE or FALSE?
     }                                                    //not a problem if double_buffer on...
}

//----------------------------------------------------------------------------
void DragDropObject::SetClearOnUpdate(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
        m_wFlags = m_wFlags | flagClearOnUpdate;    // 'OR' in ClearOnUpdate bit
     else
        m_wFlags = m_wFlags & ~flagClearOnUpdate;   // 'AND NOT' ClearOnUpdate
}

//----------------------------------------------------------------------------
void DragDropObject::Set4ResizeHandles(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
        m_wFlags = m_wFlags | flag4ResizeHandles;    // 'OR' in 4ResizeHandlese bit
     else
        m_wFlags = m_wFlags & ~flag4ResizeHandles;   // 'AND NOT' 4ResizeHandles
}

//----------------------------------------------------------------------------
void DragDropObject::SetNonStandardMove(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
        m_wFlags = m_wFlags | flagNonStandardMove;    // 'OR' in NonStandardMove bit
     else
        m_wFlags = m_wFlags & ~flagNonStandardMove;   // 'AND NOT' NonStandardMove
}

//----------------------------------------------------------------------------
void DragDropObject::SetNoLayout(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
        m_wFlags = m_wFlags | flagNoLayout;         // 'OR' in NoLayout bit
   else
        m_wFlags = m_wFlags & ~flagNoLayout;        // 'AND NOT' NoLayout
}

//----------------------------------------------------------------------------
BOOL DragDropObject::HandleResizing(CClientDC* pDC, DragDropView* pView, CRect* pRect, 
                                    CPoint pPoint,  int nHandleHit, int nEvent, 
                                    int nMinWidth, int nMinHeight){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pDC != NULL);
   assert(pView != NULL);
   assert(pRect != NULL);
   if(pDC==NULL || pView==NULL || pRect==NULL)
      return FALSE; 

   // Initialize a rectangle...
    CRect beforeRect;
    beforeRect.CopyRect(pRect);
    
    switch (nHandleHit) {
        case TopLeft:
            pRect->left = pPoint.x;
            pRect->top = pPoint.y;
            break;
        case TopMiddle:
            pRect->top = pPoint.y;
            break;  
        case TopRight:
            pRect->right = pPoint.x;
            pRect->top = pPoint.y;
            break;  
        case SideRight:
            pRect->right = pPoint.x;
            break;  
        case BottomRight:
            pRect->right = pPoint.x;
            pRect->bottom = pPoint.y;
            break;  
        case BottomMiddle:
            pRect->bottom = pPoint.y;
            break;  
        case BottomLeft:
            pRect->left = pPoint.x;
            pRect->bottom = pPoint.y;
            break;  
        case SideLeft:
            pRect->left = pPoint.x;
            break;
    }
            
    // Apply minimum size
        
    if ((pRect->left != beforeRect.left)     && ((pRect->Width())  < nMinWidth))  
        pRect->left = beforeRect.right - nMinWidth;
    if ((pRect->right != beforeRect.right)   && ((pRect->Width())  < nMinWidth))  
        pRect->right = beforeRect.left + nMinWidth;
    if ((pRect->top != beforeRect.top)       && ((pRect->Height()) > -nMinHeight))  
        pRect->top = beforeRect.bottom + nMinHeight;
    if ((pRect->bottom != beforeRect.bottom) && ((pRect->Height()) > -nMinHeight))  
    pRect->bottom = beforeRect.top - nMinHeight;
        

    // if this is the Button Up event, set the object to the new size...

    if (nEvent == WM_LBUTTONUP)
        SetBoundingRect(pRect); // the new size

    return TRUE;    // let the view draw the XOR'd rectangle    
}

//----------------------------------------------------------------------------
void DragDropObject::DrawXorRect(CDC* pDC){   
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pDC !=NULL);
   if(pDC==NULL)
      return;

    POINT poly[5];
    CPen penGhost;
    penGhost.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));    // grey ghost
    CPen* pOldPen = pDC->SelectObject(&penGhost);           // save old pen
    int oldROP = pDC->SetROP2(R2_XORPEN);
    CRect rect = m_boundingRect;
    poly[0].x = rect.left;
    poly[0].y = rect.top;
    poly[1].x = rect.right;
    poly[1].y = rect.top;
    poly[2].x = rect.right;
    poly[2].y = rect.bottom;
    poly[3].x = rect.left;
    poly[3].y = rect.bottom;
    poly[4].x = rect.left;
    poly[4].y = rect.top;
    pDC->Polyline(poly, 5);
    pDC->SetROP2(oldROP);
    pDC->SelectObject(pOldPen); 
}

//----------------------------------------------------------------------------
void DragDropObject::GainedSelection(DragDropSelection* pSelection){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pSelection !=NULL);
   if(pSelection==NULL)
      return;

    if (!IsResizable()) {
        pSelection->CreateBoundingHandle (this);
        return;
    }

    int   nWidth  = GetWidth();
    int   nHeight = GetHeight();
    CRect rect    = GetBoundingRect();
    
    int x1 = rect.left;
    int x2 = rect.left + (nWidth/2);
    int x3 = rect.right;
    
    int y1 = rect.top;
    int y2 = rect.top - (nHeight/2);
    int y3 = rect.bottom;
    
    // Create the 4 handles on the outside corners

    pSelection->CreateResizeHandle (this, x1, y1, TopLeft,      TRUE);
    pSelection->CreateResizeHandle (this, x3, y1, TopRight,     TRUE);
    pSelection->CreateResizeHandle (this, x3, y3, BottomRight,  TRUE);
    pSelection->CreateResizeHandle (this, x1, y3, BottomLeft,   TRUE);

    // if desired, create the 4 midpoint handles
    //   (note that if this property is changed while the object 
    //    is selected, the number of handles is not changed.)
    
    if (!Is4ResizeHandles()){
        pSelection->CreateResizeHandle (this, x2, y1, TopMiddle,    TRUE);
        pSelection->CreateResizeHandle (this, x3, y2, SideRight,    TRUE);
        pSelection->CreateResizeHandle (this, x2, y3, BottomMiddle, TRUE);
        pSelection->CreateResizeHandle (this, x1, y2, SideLeft,     TRUE);        
    }

    return;
}

//----------------------------------------------------------------------------
void DragDropObject::LostSelection(DragDropSelection* pSelection){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pSelection !=NULL);
   if(pSelection==NULL)
      return;

   pSelection->DeleteHandles (this);
}

//----------------------------------------------------------------------------
void DragDropObject::HideSelectionHandles(DragDropSelection* pSelection){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pSelection !=NULL);
   if(pSelection==NULL)
      return;

   pSelection->DeleteHandles (this);
}

//----------------------------------------------------------------------------
void DragDropObject::ShowSelectionHandles(DragDropSelection* pSelection){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pSelection !=NULL);
   if(pSelection==NULL)
      return;

   GainedSelection(pSelection);
}


//----------------------------------------------------------------------------
BOOL DragDropObject::DoUncapturedMouseMove(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return FALSE;
}


//----------------------------------------------------------------------------
BOOL DragDropObject::DoMouseOverStart(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return FALSE;
}


//----------------------------------------------------------------------------
BOOL DragDropObject::DoMouseOver(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return FALSE;
}


//----------------------------------------------------------------------------
BOOL DragDropObject::DoMouseOverEnd(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return FALSE;
}

//----------------------------------------------------------------------------
BOOL DragDropObject::DoLButtonClick(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return FALSE;
}

//----------------------------------------------------------------------------
BOOL DragDropObject::DoLButtonDblClk(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return FALSE;
}


//----------------------------------------------------------------------------
BOOL DragDropObject::DoLButtonDown(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return FALSE;
}

//----------------------------------------------------------------------------                    
BOOL DragDropObject::DoButtonDownLeave(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return FALSE;
}

//----------------------------------------------------------------------------                    
BOOL DragDropObject::DoButtonDownEnter(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return FALSE;
}

//----------------------------------------------------------------------------                    
BOOL DragDropObject::DoLButtonUp(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return FALSE;
} 

//----------------------------------------------------------------------------                    
void DragDropObject::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (ar.IsStoring())    {
        ar << m_boundingRect;
        ar << m_wFlags;
        ar << m_pParentArea; 
    }
    else {
        ar >> m_boundingRect;
        ar >> m_wFlags;        
        ar >> m_pParentArea;
        ASSERT(ar.m_pDocument->IsKindOf(RUNTIME_CLASS(DragDropDocument)));
        m_pDocument = (DragDropDocument*)ar.m_pDocument;
    }
}
