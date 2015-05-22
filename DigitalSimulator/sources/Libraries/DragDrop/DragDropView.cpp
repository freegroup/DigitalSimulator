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
#include "DragDropApp.h"
#include "DragDropClientApp.h"
#include "math.h"

#include "DragDropview.h"
#include "DragDrophandle.h"   
#include "DragDroptext.h"
#include "DragDropedit.h"
#include "DragDroparea.h"
#include "DragDroprect.h"
#include "DragDropport.h"
#include <assert.h>


static int nScrollAmount = 20;
static const int SCALE_MAX = 1000;


IMPLEMENT_DYNCREATE(DragDropView, CScrollView)


BEGIN_MESSAGE_MAP(DragDropView, CScrollView)
    //{{AFX_MSG_MAP(DragDropView)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDBLCLK()
    ON_MESSAGE(WM_DOREFRESH, OnDoRefresh)
    ON_WM_SIZE()
    ON_WM_SYSCOLORCHANGE()
    ON_WM_TIMER()
    ON_WM_CREATE()
 	 ON_WM_KEYDOWN()
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
    ON_EN_UPDATE(IDC_TEXTEDIT, OnEnUpdate)
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
DragDropView::DragDropView(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_pCurrentObject    = NULL;
    m_bInitialized      = FALSE;
    m_pointermode       = PointerModeNone;
    m_iScale            = 100/*Prozent*/;
    m_nClearHandleCount = 0;   
    m_pSelection        = new DragDropSelection();
    m_pDragObject       = new DragDropRectangle (CPoint (0,0), CSize(100,100));
    m_pTempLink         = NULL;   
    m_pTempPortMM       = NULL; 
    m_pTempPortMD       = NULL;  
    m_pLastSnapToPort   = NULL;
    m_pEditText         = NULL;
    m_bAbortInputAction = FALSE; 
    m_nNewControlID     = 2000;   
    m_nGdiBatchLimit    = 25;    
    m_pHandleRight      = NULL;
    m_pHandleBottom     = NULL;
    m_pGrayRight        = NULL;
    m_pGrayBottom       = NULL;
    m_hMagnifyCursor    = NULL;
    m_pMouseOverObject  = NULL;

    m_pSelection->SetView(this);    
    m_pDragObject->SetStockBrush(HOLLOW_BRUSH);
}

//----------------------------------------------------------------------------
DragDropView::~DragDropView(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_pSelection != NULL) 
       delete m_pSelection;
    m_pSelection = NULL;
    
    delete m_pDragObject;
    m_pDragObject = NULL;

    DeleteContents();
                        
    m_pHandleRight  = NULL;
    m_pHandleBottom = NULL;
    m_pGrayRight    = NULL;
    m_pGrayBottom   = NULL;
}   
 
//----------------------------------------------------------------------------
int DragDropView::OnCreate(LPCREATESTRUCT lpCreateStruct){
//----------------------------------------------------------------------------
	PROC_TRACE;


   if (inherited::OnCreate(lpCreateStruct) == -1)
        return -1;

	// avoid flicker on resize - needs to be in frame too
   //
	DWORD dwStyle = ::GetClassLong(m_hWnd, GCL_STYLE);
	::SetClassLong(m_hWnd, GCL_STYLE, dwStyle & ~(CS_HREDRAW | CS_VREDRAW));

   
    return 0;
}

//----------------------------------------------------------------------------
void DragDropView::DeleteContents(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   while (!m_oblistObjects.IsEmpty()){
        DragDropObject* pObject =(DragDropObject*)m_oblistObjects.RemoveHead();
        delete pObject;
    }
}

//----------------------------------------------------------------------------
void DragDropView::CloseView(){
//----------------------------------------------------------------------------
	PROC_TRACE;


    GetParent()->SendMessage(WM_CLOSE);
}

//----------------------------------------------------------------------------
void DragDropView::OnUpdate(CView* view, LPARAM flag, CObject* pHint){
//----------------------------------------------------------------------------
	PROC_TRACE;
    
    if (!GetSafeHwnd()) 
       return; // not safe if deleting view

    CClientDC dc(this);
    
    DragDropDocument* pDocument = GetDocument();

    switch (flag) {
        case Update_Selection:
            return;


        case Update_ClearSelectionHandles:
            // the counter here will be 1 if a drag is in progress, and we know
            // the handles are already turned off anyway.
            if (m_nClearHandleCount == 0) m_pSelection->ClearSelectionHandles((DragDropObject*)pHint);
            return;
            
        case Update_RestoreSelectionHandles:
            // the counter here will be 1 if a drag is in progress, and we know
            // the handles are already turned off anyway.
            if (m_nClearHandleCount == 0) m_pSelection->RestoreSelectionHandles((DragDropObject*)pHint);
            return;

        case Update_Delete:
            // when an object is being deleted, first, we must make sure it has no selection handles
            
            m_pSelection->ClearSelection((DragDropObject*)pHint);            
            if (pHint == m_pCurrentObject) m_pCurrentObject = NULL;
            
            if (m_pEditText)    // if text is being edited...
            {
                DragDropObject* pText = (DragDropObject*)m_pEditText->GetTextObject(); // cast down to object to avoid gotext.h
                ASSERT(pText);
                if (pText == pHint) m_pEditText = NULL; // if text object is being deleted, exit edit mode
            }    

            // then fall through the Update_Object code so that it will be erased...
            
        case  Update_Object:
        {
            if (!m_bInitialized){
                TRACE(_T("DragDropView::OnInitialUpdate has not been called\n"));
                return;
            }

            ASSERT(pHint->IsKindOf(RUNTIME_CLASS(DragDropObject)));
                // The hint is that a node as been added (or changed).
                // So, invalidate its rectangle.
            DragDropObject* pObject =(DragDropObject*)pHint;
            OnPrepareDC(&dc);
            
            CRect rect = pObject->GetBoundingRect();
            dc.LPtoDP(&rect);
            // the conversion to pixels may have resulted in a too-small rectangle, we
            // need to "adjust" the rectangle.  Note: these are DP coordinates.
            rect.top = rect.top - 1;        // make box 1 pixel taller
            rect.bottom = rect.bottom + 1;  // and 1 pixel lower
            rect.left = rect.left - 1;      // make box 1 pixel wider to left
            rect.right = rect.right + 1;    // and 1 pixel wider to right
            
            InvalidateRect(&rect, FALSE); //dbl //no need to clear area if double buffering...
            
                
            if (pObject->IsPrevRectValid()) {
                rect = pObject->GetPrevBoundingRect();                      
                dc.LPtoDP(&rect);
                rect.top = rect.top - 1;        // make box 1 pixel taller
                rect.bottom = rect.bottom + 1;  // and 1 pixel lower
                rect.left = rect.left - 1;      // make box 1 pixel wider to left
                rect.right = rect.right + 1;    // and 1 pixel wider to right
                InvalidateRect(rect, FALSE); 
            }     
                    
            return;
        }
        case  Refresh_Display:
            assert(m_hWnd);     // Assert that the window exists.
            Invalidate(TRUE);
            return;
        case  Update_New_Document_Size:  
            NewDocSize();   // New Document size
            return;
        case  Update_Window:
            UpdateWindow();   // do draw NOW!
            return;
        
    } // end switch
}

//----------------------------------------------------------------------------
void DragDropView::OnInitialUpdate(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    SetScale(m_iScale); 
    m_bInitialized = TRUE;
    
    ViewHandles(); 

    CPoint Pixel(100,100);
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(&Pixel);
    m_sizePixelLP.cx = Pixel.x;
    m_sizePixelLP.cy = Pixel.y;
}                   

//----------------------------------------------------------------------------
void DragDropView::ViewHandles(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void DragDropView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo){
//----------------------------------------------------------------------------
	PROC_TRACE;

    inherited::OnPrepareDC(pDC, pInfo) ;

    DragDropAppMixIn::OnPrepareDC(pDC, pInfo, m_iScale);


    // save whether this is a print preview or not.    
    if (pInfo != NULL) {
        m_bPrintPreview = pInfo->m_bPreview;                 
    }
    else {
        m_bPrintPreview = FALSE;
    }    

} 

//----------------------------------------------------------------------------
void DragDropView::NewDocSize(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetScale(GetScale());   
}


//----------------------------------------------------------------------------
void DragDropView::SetScale(int percent, float clientRectFactor){
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropDocument* pDoc = GetDocument() ;  
    BOOL bRedraw = (percent != m_iScale);

    percent = max(pDoc->MinScale(), percent);  // don't get too small
    percent = min(pDoc->MaxScale(), percent);  // or too big

   
    m_logPixelsPerUnit = pDoc->GetUnitSize() ;
    //The document and lines sizes are cx*units and cy*units
    CSize sizeDoc =  pDoc->GetDocumentSize() ;
    CSize sizeDocLine = pDoc->GetDocumentLineSize() ;
    
    {   
        CSize szRes = Metrics::getPixelsPerCM();
        m_fdevPixelsPerUnit_x = (float)szRes.cx;
        m_fdevPixelsPerUnit_y = (float)szRes.cy;   
    
        // By default we would like to have 1*unit == 1 centimeter when
        // the iScale is 100
        // if the iScale is 200 then 1* unit == 2 cm and so on...
        // Convert sizeDoc from logical size to centimeters.
     
        m_iScale = percent ;           
        
        // compute MAX scale based on biggest allowable doc size of 30000 (only on Win 95) 2Gb on NT

        long cx = max(sizeDoc.cx, m_logPixelsPerUnit*10);  // handle docs smaller than a unit
        long maxScale = (long)(1.0 / ((LONG)(cx / m_logPixelsPerUnit) *
                             m_fdevPixelsPerUnit_x / 100 / pDoc->MaxDoc()));
        if (m_iScale > maxScale && maxScale < pDoc->MaxScale()) {
            TRACE(_T("DragDropView::SetScale. X scale forced to %d, requested value was %d\n"),
                  m_iScale, maxScale);
            m_iScale = maxScale;
        }
        // now do Y
        long cy = max(sizeDoc.cy, m_logPixelsPerUnit*10);  // handle docs smaller than a unit
        maxScale = (long)(1.0 / ((LONG)(cy / m_logPixelsPerUnit) *
                             m_fdevPixelsPerUnit_y / 100 / pDoc->MaxDoc()));
        if (m_iScale > maxScale && maxScale < pDoc->MaxScale()) {
            TRACE(_T("DragDropView::SetScale. Y scale forced to %d, requested value was %d\n"),
                  m_iScale, maxScale);
            m_iScale = maxScale;
        }

        sizeDoc.cx =  (int) ((LONG)(sizeDoc.cx / m_logPixelsPerUnit) *
                             m_fdevPixelsPerUnit_x * m_iScale / 100 );
        sizeDoc.cy =  (int) ((LONG)(sizeDoc.cy / m_logPixelsPerUnit) *
                             m_fdevPixelsPerUnit_y * m_iScale / 100 ); 
        sizeDocLine.cx =  (int) ((LONG)(sizeDocLine.cx / m_logPixelsPerUnit) *
                                 m_fdevPixelsPerUnit_x * m_iScale / 100 );
        sizeDocLine.cy =  (int) ((LONG)(sizeDocLine.cy / m_logPixelsPerUnit) *
                                 m_fdevPixelsPerUnit_y * m_iScale / 100 ); 
    }
    
    CRect clientRect;
    GetClientRect(&clientRect);
    CSize sizeDocPage((int) (clientRect.right * clientRectFactor), 
                      (int) (clientRect.bottom * clientRectFactor));

    CSize sizeDocLineZoom((int) (clientRect.right * (1.0-clientRectFactor)), 
                      (int) (clientRect.bottom * (1.0-clientRectFactor)));
    if (percent != 100) sizeDocLine = sizeDocLineZoom;
    SetScrollSizes( MM_TEXT, sizeDoc, sizeDocPage, sizeDocLine) ;
    ViewHandles();

    // The following pair of handles calls will re-scale any existing selection handles 

    if (bRedraw) {
        // only redraw if scale has really changed.
        ClearSelectionHandles();
        RestoreSelectionHandles();
        CDragDropApp* theapp = (CDragDropApp*)AfxGetApp();    
        Invalidate(FALSE); // don't erase if double buffering
    }
} 

//----------------------------------------------------------------------------
void DragDropView::SetScaleToFit(int nMinScale){
//----------------------------------------------------------------------------
	PROC_TRACE;


    ASSERT(nMinScale > 5);
    DragDropDocument* pDoc = GetDocument() ;  
    
    m_logPixelsPerUnit = pDoc->GetUnitSize() ;
    CSize sizeDoc =  pDoc->GetMinLayoutSize() ;

    CSize szRes = Metrics::getPixelsPerCM();

    CRect rect;
    GetClientRect(&rect); 
    GetWindowRect(&rect);
    CSize sizeView(rect.right-rect.left, rect.bottom-rect.top);

    int xScale = ((sizeView.cx / szRes.cx) * m_logPixelsPerUnit * 100)  / sizeDoc.cx;
    int yScale = ((sizeView.cy / szRes.cy) * m_logPixelsPerUnit * 100)  / sizeDoc.cy;
    
    int nScale = min(xScale, yScale); 

    if (pDoc->IsEmpty()) nScale = 100;
    
    ScrollToPosition(CPoint(0,0)); 

    SetScale(max(nScale, nMinScale));

}

//----------------------------------------------------------------------------
void DragDropView::SetScaleToShowWholeDoc(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    DragDropDocument* pDoc = GetDocument() ;  
    
    m_logPixelsPerUnit = pDoc->GetUnitSize() ;
    CSize sizeDoc =  pDoc->GetDocumentSize();

    CRect rect(0,0,sizeDoc.cx,-sizeDoc.cy);
    ZoomToRect(&rect);

}



//----------------------------------------------------------------------------
void DragDropView::ZoomToRect(CRect* rectZoom){
//----------------------------------------------------------------------------
	PROC_TRACE;

    DragDropDocument* pDoc = GetDocument();
    m_logPixelsPerUnit = pDoc->GetUnitSize() ;

    CPoint ptTopLeft = rectZoom->TopLeft();  
    rectZoom->NormalizeRect();
    CSize sizeDoc = rectZoom->Size();
    sizeDoc.cx = max(1, sizeDoc.cx); 
    sizeDoc.cy = max(1, sizeDoc.cy);

    CSize szRes = Metrics::getPixelsPerCM();

    CRect rect;
    GetClientRect(&rect);
    CSize sizeView(rect.right, rect.bottom);

    int xScale = ((sizeView.cx / szRes.cx) * m_logPixelsPerUnit * 100)  / sizeDoc.cx;
    int yScale = ((sizeView.cy / szRes.cy) * m_logPixelsPerUnit * 100)  / sizeDoc.cy;
    
    int nScale = min(xScale, yScale); 

    SetScale(max(nScale, 5));

    ScrollToPoint(ptTopLeft);
}

//----------------------------------------------------------------------------
void DragDropView::ZoomToSelection(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_pSelection->IsEmpty()) 
       return;

    CRect rectZoom(m_pSelection->PrimarySelection()->GetBoundingRect());
    for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ){
        DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
        CRect rect = pObject->GetBoundingRect();
        if (rect.left < rectZoom.left)     
           rectZoom.left = rect.left;
        if (rect.right > rectZoom.right)   
           rectZoom.right = rect.right;
        if (rect.top > rectZoom.top)       
           rectZoom.top = rect.top;
        if (rect.bottom < rectZoom.bottom) 
           rectZoom.bottom = rect.bottom;
    }
    
    ZoomToRect(&rectZoom);
}



//----------------------------------------------------------------------------
void DragDropView::OnDraw(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;
    
   DragDropDocument *pDocument = GetDocument();

   pDocument->SetCurrentDrawView(this);

   // Get the invalidated rectangle of the view, or in the case
   // of printing, the clipping region of the printer dc.
   CRect rectClip;
   pDC->GetClipBox(&rectClip);

   int nSavedBMdc = -1;    

   CDC      dc;              
   CDC*     pDrawDC = pDC;   
   CBitmap  bitmap;       
   CBitmap* pOldBitmap;  
   CRect    rectDP  = rectClip;

   pDC->LPtoDP(&rectDP);
   //dbl...                                                
   // Can't double buffer if printing, or if a text edit operation is in 
   // progress, since the bitmap write will occlude the text edit window (for unknown reasons).
   if (!pDC->IsPrinting() && TRUE && !m_pEditText){
        if (dc.CreateCompatibleDC(pDC)){
            nSavedBMdc = dc.SaveDC();

            if (bitmap.CreateCompatibleBitmap(pDC, rectDP.Width(), rectDP.Height())){
                OnPrepareDC(&dc, NULL);
                pDrawDC = &dc;
                
                //offset origin
                dc.OffsetViewportOrg(-rectDP.left, -rectDP.top);
                pOldBitmap = dc.SelectObject(&bitmap);
                dc.SetBrushOrg(rectDP.left % 8, rectDP.top % 8);
                dc.IntersectClipRect(rectClip);
            }
        }
        
        CBrush brush;
        if (!brush.CreateSolidBrush(pDocument->GetPaperColor())){
            if (nSavedBMdc != -1) 
               dc.RestoreDC(nSavedBMdc);
            TRACE0("CDragDropView::OnDraw Create bg brush failed\n");
            pDocument->SetCurrentDrawView(NULL);
            return;
        }
        brush.UnrealizeObject();  // needed because of SetBrushOrg
        pDrawDC->FillRect(rectClip, &brush);    // fill with paper color
    }
    //..dbl
    // Now the bitmap (or view if no double buffering) is filled with the appropriate 
    // background color, giving a derived class a chance to scribble in it (e.g., grid marks).
    
    DoDrawBackgroundDecoration(pDrawDC);
       
    CDragDropApp::InvalidateStockCache();  // invalidate Pen/Brush cache
    
    // Draw the Objects in the Document and then the Objects in the View.
    {
      SaveRestoreDC srDC(pDrawDC);

      DoDrawDocumentObjects(pDocument, rectClip, pDrawDC);
      DoDrawViewObjects(rectClip, pDrawDC);
    }

    if (pDrawDC != pDC){
        SaveRestoreDC srDC(pDC);
        pDC->SetViewportOrg(0,0);
        pDC->SetWindowOrg(0,0);
        pDC->SetMapMode(MM_TEXT);
        dc.SetViewportOrg(0,0);
        dc.SetWindowOrg(0,0);
        dc.SetMapMode(MM_TEXT);
        pDC->BitBlt(rectDP.left, rectDP.top, rectDP.Width(), rectDP.Height(), &dc, 0, 0, SRCCOPY);
        dc.SelectObject(pOldBitmap);
    }                                 
                                 
    if (nSavedBMdc != -1) 
       dc.RestoreDC(nSavedBMdc);

    if (m_pEditText) {
        m_pEditText->Invalidate();
    }

    pDocument->SetCurrentDrawView(NULL);
}


//----------------------------------------------------------------------------/////////////////////////////////////////////////////////////////////////////
void DragDropView::DoDrawDocumentObjects(DragDropDocument* pDocument, CRect rectClip, CDC* pDrawDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   for (POSITION pos = pDocument->GetFirstObjectPos(); pos != NULL; ) {
        DragDropObject* pObject = (DragDropObject*) pDocument->GetNextObjectAtTop(pos);
        if(pObject != NULL){
           CRect rectNode = pObject->GetBoundingRect();

           // Skip an Object that does not intersect the View clipping rectangle.
        
           if (rectNode.top < rectClip.bottom) 
              continue;
           if (rectNode.bottom > rectClip.top) 
              continue;
           if (rectNode.left > rectClip.right) 
              continue;
           if (rectNode.right < rectClip.left) 
              continue;
        
           pObject->paint(pDrawDC);
        }
        else{
           TRACE0("Warning: unerwarteter NULL-Pointer in DragDropView::DoDrawDocumentObjects\n");
        }
    }
}

//----------------------------------------------------------------------------
void DragDropView::DoDrawBackgroundDecoration(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;
 
}

//----------------------------------------------------------------------------
void DragDropView::DoDrawViewObjects(CRect rectClip, CDC* pDrawDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   for (POSITION pos = GetFirstObjectPos(); pos != NULL; ){
        DragDropObject* pObject = (DragDropObject*) GetNextObject(pos);
        CRect rectNode = pObject->GetBoundingRect();

        if (rectNode.top < rectClip.bottom) 
           continue;
        if (rectNode.bottom > rectClip.top) 
           continue;
        if (rectNode.left > rectClip.right) 
           continue;
        if (rectNode.right < rectClip.left) 
           continue;

        pObject->paint(pDrawDC);
    }
}


//----------------------------------------------------------------------------
LRESULT DragDropView::OnDoRefresh(WPARAM wParam, LPARAM lParam){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT(m_hWnd);     // Assert that the window exists.
   Invalidate(TRUE);
   return 0L;
}

//----------------------------------------------------------------------------
void DragDropView::OnSysColorChange(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ViewHandles();    // update color of out-of-bounds area.
   GetDocument()->OnSysColorChange();  // tell document that this is happening
}

/*
//----------------------------------------------------------------------------
void DragDropView::OnSize(UINT nType, int cx, int cy){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Once the View has been fully Initialized, give derived classes access
   // to changes in the View dimensions.

   if (m_bInitialized)
        DoSize(nType, cx, cy);
   else
       inherited::OnSize(nType, cx, cy);
}

//----------------------------------------------------------------------------
void DragDropView::DoSize(UINT nType, int cx, int cy){
//----------------------------------------------------------------------------
	PROC_TRACE;

    inherited::OnSize(nType, cx, cy);

}
*/

//----------------------------------------------------------------------------
void DragDropView::PopToTop(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   GetParentFrame()->BringWindowToTop();
    
}          

//----------------------------------------------------------------------------
void DragDropView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::OnActivateView(bActivate, pActivateView, pDeactiveView);

   DragDropSelection* pSel = GetSelection();
   if(pSel){
      if (bActivate){ 
          for (POSITION pos = pSel->GetFirstSelectedPos(); pos != NULL; ) { 
              DragDropObject* pObj = pSel->GetNextSelected(pos);
              pSel->ShowHandles(pObj);
          }        
      }
      else{ 
          for (POSITION pos = pSel->GetFirstSelectedPos(); pos != NULL; ) { 
              DragDropObject* pObj = pSel->GetNextSelected(pos);
              pSel->HideHandles(pObj);
          }        
      }
   }
}

//----------------------------------------------------------------------------
POSITION DragDropView::GetFirstObjectPos() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_oblistObjects.GetHeadPosition();
}


//----------------------------------------------------------------------------
DragDropObject* DragDropView::GetNextObject(POSITION& pos) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return(DragDropObject*)m_oblistObjects.GetNext(pos);  
}


//----------------------------------------------------------------------------
POSITION DragDropView::AddObjectAtHead(DragDropObject* pObject) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropObject)));
   pObject->m_pView = this;        
   POSITION pos = m_oblistObjects.AddHead(pObject);
   pObject->SetUpdateNeeded(TRUE);
   return pos;
}


//----------------------------------------------------------------------------
POSITION DragDropView::AddObjectAtTail(DragDropObject* pObject) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropObject)));
   pObject->m_pView = this;
   POSITION pos = m_oblistObjects.AddTail(pObject);
   pObject->SetUpdateNeeded(FALSE);            // adding on top in View plane, no need to clear area.
   return pos;                                               
}

//----------------------------------------------------------------------------
void DragDropView::RemoveObject(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_pMouseOverObject = NULL;   // Current Object under the mouse

   pObject->SetClearOnUpdate(TRUE);
   OnUpdate (NULL, Update_Object, pObject);   // only update this view

   POSITION pos;
   if (pObject->m_pParentArea == NULL){
       if (pos = m_oblistObjects.Find(pObject))
           m_oblistObjects.RemoveAt(pos);
   }
   else {
       DragDropArea* pParentArea = (DragDropArea*) pObject->m_pParentArea;
       if (pos = pParentArea->m_oblistObjects.Find(pObject))
           pParentArea->m_oblistObjects.RemoveAt(pos);
       //  can't clear the m_pParentArea here, since a DeleteObject may need this.
    }

    pObject->m_pView = NULL;
}

//----------------------------------------------------------------------------
DragDropObject* DragDropView::PickInView(CClientDC* pDC, CPoint ptToCheckLP, BOOL bSelectableOnly){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CPoint ptToCheckDP;
    ptToCheckDP.x = ptToCheckLP.x;
    ptToCheckDP.y = ptToCheckLP.y;
    
    pDC->LPtoDP(&ptToCheckDP);  // PtInObject needs both LP and DP.

    // Iterate thru the Objects in the View.

    for (POSITION pos = m_oblistObjects.GetTailPosition(); pos != NULL; ){
        DragDropObject* pObject =(DragDropObject*) m_oblistObjects.GetPrev(pos);
        
        // Ignore an invisible Object.
        
        if (!pObject->isVisible()) continue;
        
        // Test if the point is within the Object.

        if (!pObject->PtInObject(pDC, ptToCheckLP, ptToCheckDP)) continue;
            
        // Look for the inner-most object of an Area (visual recursion).
            
        if (pObject->IsKindOf(RUNTIME_CLASS(DragDropArea)))
        {
            DragDropArea* pArea = (DragDropArea*) pObject;
            DragDropObject* pObjectInArea = pArea->PickInArea(pDC, ptToCheckLP, bSelectableOnly);
    
            if (pObjectInArea != NULL) return pObjectInArea;
        }
        
        // Return the identified Object if it is selectable or
        // if the caller doesn't care about selectability.
        
        if (!bSelectableOnly) return pObject;
        if (pObject->IsSelectable()) return pObject;
    }
    
    // Return NULL if no Object is found.

    return NULL;
}

//----------------------------------------------------------------------------
BOOL DragDropView::OnPreparePrinting(CPrintInfo* pInfo){
//----------------------------------------------------------------------------
	PROC_TRACE;
    // default preparation
    return DoPreparePrinting(pInfo);
}

//----------------------------------------------------------------------------
void DragDropView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // add extra Initialization before printing
    // Set length of document based on printer DC
    
    m_nWidthLoMM = pDC->GetDeviceCaps(HORZSIZE) * 10;   // Millimeters * 10
    m_nHeightLoMM = pDC->GetDeviceCaps(VERTSIZE) * 10;
    
    // assume mapping mode in LOMETRIC
    
    DragDropDocument* pDocument = GetDocument();
    CSize szDoc(0,0);

    // instead of simply using GetDocumentSize(), we actually compute the
    // minimum area we need to print from (0,0) to (max-x, max-y)
    
    for (POSITION pos = pDocument->GetFirstObjectPos(); pos != NULL; )
    {
        DragDropObject* pObject =(DragDropObject*) pDocument->GetNextObjectAtTop(pos);
        CRect rectNode = pObject->GetBoundingRect();
        if (rectNode.bottom < szDoc.cy) szDoc.cy = rectNode.bottom;
        if (rectNode.right  > szDoc.cx) szDoc.cx = rectNode.right;   
    }

    m_nPagesWide = (abs(szDoc.cx) / m_nWidthLoMM) + 1;  
    m_nPagesHigh = (abs(szDoc.cy) / m_nHeightLoMM) + 1;
    
    pInfo->SetMaxPage(m_nPagesWide * m_nPagesHigh);
    pInfo->m_nCurPage = 1;                      // Start preview at page 1 
}

//----------------------------------------------------------------------------
void DragDropView::OnPrint(CDC* pDC, CPrintInfo* pInfo){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // pages print out like this...
    //
    //      1   2   3 ... m_nPagesWide
    //      4   5   6
    
        
    int x = ((pInfo->m_nCurPage - 1) % m_nPagesWide) * m_nWidthLoMM;
    int y = -(int)((pInfo->m_nCurPage - 1) / m_nPagesWide) * m_nHeightLoMM;
    CPoint pt(x,y);
    
    pDC->LPtoDP(&pt);
    pDC->SetViewportOrg(-pt.x, -pt.y);      //?? why the negative values?
    
    // do some page decoration
    
    pDC->MoveTo(x,y);       //upper left "-"
    pDC->LineTo(x+50,y);
    pDC->MoveTo(x,y);       //upper left "|"
    pDC->LineTo(x,y-50);
    
    pDC->MoveTo(x+m_nWidthLoMM,y);      //upper right "-"
    pDC->LineTo(x+m_nWidthLoMM-50,y);
    pDC->MoveTo(x+m_nWidthLoMM,y);      //upper right "|"
    pDC->LineTo(x+m_nWidthLoMM,y-50);
    
    pDC->MoveTo(x,y-m_nHeightLoMM+3);       //lower left "-"  (+3 is fudge to avoid falling
    pDC->LineTo(x+50,y-m_nHeightLoMM+3);    //                  off the bottom)
    pDC->MoveTo(x,y-m_nHeightLoMM+3);       //lower left "|"
    pDC->LineTo(x,y+50-m_nHeightLoMM+3);
    
    pDC->MoveTo(x+m_nWidthLoMM,y-m_nHeightLoMM+3);      //lower right "-"
    pDC->LineTo(x+m_nWidthLoMM-50,y-m_nHeightLoMM+3);
    pDC->MoveTo(x+m_nWidthLoMM,y-m_nHeightLoMM+3);      //lower right "|"
    pDC->LineTo(x+m_nWidthLoMM,y+50-m_nHeightLoMM+3);
    
    CString iter;
    iter.Format(_T("%d"), pInfo->m_nCurPage);    // format iteration number
    
    // set up a very small, Arial font
    LOGFONT lf;
    memset (&lf, 0, sizeof(LOGFONT));
    lf.lfHeight = 30; 
    lf.lfWeight = FW_NORMAL;
    CString sFaceName(_T("Arial"));
    _tcscpy(lf.lfFaceName, sFaceName);
    CFont font;
    font.CreateFontIndirect(&lf); 
    
    CFont* pOldFont = pDC->SelectObject(&font);
    int nOldAlign = pDC->SetTextAlign(TA_RIGHT);
    
    BOOL status = pDC->TextOut(x+m_nWidthLoMM-10, y-10, iter);
    pDC->SetTextAlign(nOldAlign);
    pDC->SelectObject(pOldFont);    

    OnDraw(pDC);
}

//----------------------------------------------------------------------------
void DragDropView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/){
//----------------------------------------------------------------------------
	PROC_TRACE;

}



//----------------------------------------------------------------------------
BOOL DragDropView::DropObject(DragDropView* pSourceView, DragDropObject* pSourceObject, CPoint pPoint, UINT nFlags){
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropSelection* pSel = pSourceView->GetSelection();
    
    ScreenToClient(&pPoint);
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(&pPoint);
    
    for (POSITION pos = pSel->GetFirstSelectedPos(); pos != NULL; ) {
        DragDropObject* pCatObject = pSel->GetNextSelected(pos);
        if (pCatObject == NULL) 
           return FALSE;
    
        // must copy root object, not a child that happens to be selected (perhaps via RedirectSelection)
        while (pCatObject->GetParent()) 
           pCatObject = pCatObject->GetParent(); 
        
        DragDropObject* pNewNode = pCatObject->Clone();     
        
        if (!pNewNode) 
           continue; 
        pNewNode->SetSpotLocation(DragDropObject::spotCenter, pPoint.x, pPoint.y); // set real location for drag
        pPoint.x += 70;                                    // offset for cascade if multiple objects.
        pPoint.y -= 70;    
        DragDropDocument* pDocument = GetDocument();
        pDocument->AddObjectAtTail(pNewNode);
    }
    return 0;
}

//----------------------------------------------------------------------------
BOOL DragDropView::DropObjectAnimateDraw(DragDropView* pSourceView, DragDropObject* pSourceObject, CPoint pPoint) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   // point is passed in screen coordinates
    ScreenToClient(&pPoint);
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(&pPoint);

    pSourceObject->SetSpotLocation(DragDropObject::spotCenter, pPoint.x, pPoint.y);
    pSourceObject->paint(&dc);
    UpdateWindow();
    
    return TRUE; 
}

//----------------------------------------------------------------------------
BOOL DragDropView::DropObjectAnimateClear(DragDropView* pSourceView, DragDropObject* pSourceObject, CPoint pPoint) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   
    CRect rect = pSourceObject->GetBoundingRect();
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.LPtoDP(&rect);
    // the conversion to pixels may have resulted in a too-small rectangle, we
    // need to "adjust" the rectangle.  Note: these are DP coordinates.
    rect.top = rect.top - 1;        // make box 1 pixel taller
    rect.bottom = rect.bottom + 1;  // and 1 pixel lower
    rect.left = rect.left - 1;      // make box 1 pixel wider to left
    rect.right = rect.right + 1;    // and 1 pixel wider to right
                
    InvalidateRect(&rect, TRUE);    // TRUE forces clear area
    UpdateWindow();                 // force the update to happen now so the DOA_Draw can
                                    // leaves its bits "on top" of the view without
                                    // really being in the document
    return TRUE; 
}




//----------------------------------------------------------------------------
void DragDropView::OnTimer(UINT nIDEvent) {
//----------------------------------------------------------------------------
	PROC_TRACE;

}


//----------------------------------------------------------------------------
DragDropSelection* DragDropView::GetSelection() const {
//----------------------------------------------------------------------------
	PROC_TRACE;
    return m_pSelection;
}

//----------------------------------------------------------------------------
DragDropObject* DragDropView::DoPickInDocument(CClientDC* pDC, CPoint ptToCheckLP, BOOL bSelectableOnly){
//----------------------------------------------------------------------------
	PROC_TRACE;
	assert(GetDocument() != NULL);

    return GetDocument()->PickInDocument(pDC, ptToCheckLP, bSelectableOnly);
}

//----------------------------------------------------------------------------
void DragDropView::DoSelectionInBox (CRect* rect){    
//----------------------------------------------------------------------------
	PROC_TRACE;
    // The default DoSelectionInBox only selects Objects at the Document level
    // (not those within Areas) and only if the are contained completely within 
    // the box. 

    DragDropDocument* pDocument = GetDocument();
    for (POSITION pos = pDocument->GetFirstObjectPos(); pos != NULL; ){
        DragDropObject* pObject = pDocument->GetNextObjectAtTop(pos);   
        BOOL bSelectableChildren = FALSE;
        if (pObject->IsKindOf(RUNTIME_CLASS(DragDropArea))){
            bSelectableChildren = ((DragDropArea*)pObject)->GetGrabChildSelection();
        }
        if (!pObject->IsSelectable() && !bSelectableChildren) continue;
        if (pObject->IsKindOf(RUNTIME_CLASS(DragDropHandle))) continue; // skip handles
        CRect rectNode = pObject->GetBoundingRect();
        // if rectangles to not touch, continue with next object
        
        if ((rectNode.top < rect->top) &&
            (rectNode.bottom > rect->bottom) &&
            (rectNode.left > rect->left) &&
            (rectNode.right < rect->right)) m_pSelection->ExtendSelection(pObject);
    }
}

//----------------------------------------------------------------------------
void DragDropView::ClearSelection(){
//----------------------------------------------------------------------------
	PROC_TRACE;
    m_pSelection->ClearSelection();
}

//----------------------------------------------------------------------------
void DragDropView::RestoreSelectionHandles(){ 
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_nClearHandleCount--; 
    if (m_nClearHandleCount == 0) 
        GetDocument()->UpdateAllViews(NULL, Update_RestoreSelectionHandles, NULL);
}


//----------------------------------------------------------------------------
void DragDropView::ClearSelectionHandles(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_nClearHandleCount == 0) 
        GetDocument()->UpdateAllViews(NULL, Update_ClearSelectionHandles, NULL);
    m_nClearHandleCount++;
    
}

//----------------------------------------------------------------------------
void DragDropView::SetValidPorts(){
//----------------------------------------------------------------------------
	PROC_TRACE;

// A "Link" has just been started by the user, we must set the ValidLink
// state for each port in the document.  This is done once to avoid lots of
// calls to ValidLink.  Then, PickNearestPort can simply ask each port if
// it is a valid port to connect to.

// this loop looks through the object list in the document.  

    DragDropDocument* pDocument = GetDocument();
    for (POSITION pos = pDocument->GetFirstObjectPos(); pos != NULL; ){
        DragDropObject* pObject =(DragDropObject*) pDocument->GetNextObject(pos);
        if (pObject->IsKindOf(RUNTIME_CLASS(DragDropPort))){
            DragDropPort* pPort =(DragDropPort*)pObject;
            pPort->SetValidLink(ValidLink(m_pTempPortMD, pPort));  //  valid from here to there?
        }   
        
    }
}

//----------------------------------------------------------------------------
void DragDropView::SetValidPorts2(){
//----------------------------------------------------------------------------
	PROC_TRACE;

// A "Link" has just been started by the user, we must set the ValidLink
// state for each port in the document.  This is done once to avoid lots of
// calls to ValidLink.  Then, PickNearestPort can simply ask each port if
// it is a valid port to connect to.

// this loop looks through the object list in the document.  

    DragDropDocument* pDocument = GetDocument();
    for (POSITION pos = pDocument->GetFirstObjectPos(); pos != NULL; ){
        DragDropObject* pObject =(DragDropObject*) pDocument->GetNextObject(pos);
        if (pObject->IsKindOf(RUNTIME_CLASS(DragDropPort))){
            DragDropPort* pPort =(DragDropPort*)pObject;
            pPort->SetValidLink(ValidLink(pPort, m_pTempPortMD));  //  valid from here to there?
        }   
        
    }
}


//----------------------------------------------------------------------------
DragDropPort* DragDropView::PickNearestPort(CClientDC* pDC, CPoint pPoint, int nGravity){
//----------------------------------------------------------------------------
	PROC_TRACE;

   int grav = (nGravity == -1) ? Metrics::getPortGravity() : nGravity;

    
    DragDropDocument* pDocument = GetDocument();
    double smallestDist = (double)(grav);
    DragDropPort* pClosestPort = NULL;

    for (POSITION pos = pDocument->GetFirstObjectPos(); pos != NULL; ){
        DragDropObject* pObject =(DragDropObject*) pDocument->GetNextObject(pos);
        if (pObject->IsKindOf(RUNTIME_CLASS(DragDropPort))){
            DragDropPort* pPort =(DragDropPort*)pObject;
            if (pPort->IsValidLink())  // must be valid from here to there...
            {
                CPoint toPoint = pPort->GetToLinkPoint();   // get the spot an 'to' Link connects to
                // now, calculate the distance from the mouse point the this port's point
                double xPart =  pPoint.x - toPoint.x;
                double yPart =  pPoint.y - toPoint.y;
                xPart = xPart * xPart;
                yPart = yPart * yPart;
                double dist = sqrt(xPart + yPart);
                if (dist <= smallestDist) {
                    smallestDist = dist;
                    pClosestPort = pPort;
                }
            }   
        }
    }

   return pClosestPort;
}


//----------------------------------------------------------------------------
DragDropHandle* DragDropView::SelectedHandleTest(CClientDC* pDC, CPoint pPoint){
//----------------------------------------------------------------------------
	PROC_TRACE;
    DragDropHandle* pHandle = NULL;      // return NULL if the object is not a Handle
    
    DragDropObject* pObject = PickInView(pDC, pPoint, TRUE);  // TRUE = selectable objects only
    
    if (pObject && pObject->IsKindOf(RUNTIME_CLASS(DragDropHandle)))
        pHandle = (DragDropHandle*) pObject;

    return pHandle;
}


//----------------------------------------------------------------------------
DragDropPort* DragDropView::PortTest(CClientDC* pDC, CPoint pPoint){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // pPoint is logical coordinates

    DragDropPort* pPort = NULL;      // return NULL if the object is not a Port
    
    DragDropObject* pObject = DoPickInDocument(pDC, pPoint, FALSE); // FALSE = pick anything
    
    // if the object is a Port object, then return a pointer to it
    if (pObject && pObject->IsKindOf(RUNTIME_CLASS(DragDropPort)))
        pPort = (DragDropPort*) pObject;

    return pPort;
}

//----------------------------------------------------------------------------
void DragDropView::ScrollToPoint(CPoint pointLP){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_nMapMode == MM_TEXT){
        DocToClient(pointLP);
        pointLP += GetDeviceScrollPosition(); // offset by current scroll amount
    }

    ScrollToPosition(pointLP);
}


//----------------------------------------------------------------------------
void DragDropView::ScrollToObject(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pObject);

    CRect rect;
    GetClientRectLP(&rect);           // find client window
    CPoint ptCur = rect.TopLeft();
    CSize szMax;
    szMax.cx = rect.right - rect.left;
    szMax.cy = rect.bottom - rect.top;

    rect = pObject->GetBoundingRect(); // re-use rectangle for object

    int yScrollTop = 0;
    int yScrollBot = 0;
    int yScrollAmt = 0;
    
    int xyExtra = 35;

    yScrollTop = rect.top - ptCur.y;    // if negative, object is below top of view
    yScrollBot = rect.bottom - (ptCur.y + szMax.cy);  // if negative, falls off bottom

    if (yScrollTop > 0 || yScrollBot < 0) {  // nothing to do?
        // check for off the top
        if (yScrollTop > 0) yScrollAmt = yScrollTop + xyExtra; // amount to scroll plus a little...
        // check for off the bottom
        if (yScrollBot < 0 && yScrollAmt == 0) {
            yScrollAmt = yScrollBot - xyExtra;
            if (yScrollTop > yScrollAmt) yScrollAmt = yScrollTop + xyExtra;    // oops, can't scroll off top.
        }
    }
    int xScrollLeft = 0;
    int xScrollRight = 0;
    int xScrollAmt = 0;

    xScrollLeft = -(rect.left - ptCur.x);    // if negative, object is below Left of view
    xScrollRight = -(rect.right - (ptCur.x + szMax.cx));  // if negative, falls off right

    if (xScrollLeft > 0 || xScrollRight < 0) {   // nothing to do?
        // check for off the Left
        if (xScrollLeft > 0) xScrollAmt = xScrollLeft + xyExtra; // amount to scroll plus a little...
        // check for off the right
        if (xScrollRight < 0 && xScrollAmt == 0) {
            xScrollAmt = xScrollRight - xyExtra;
            if (xScrollLeft > xScrollAmt) xScrollAmt = xScrollLeft + xyExtra;    // oops, can't scroll off Left.
        }
    }

    if (yScrollAmt == 0 && xScrollAmt == 0) return;

    ptCur.y += yScrollAmt;
    ptCur.x -= xScrollAmt;

    if (m_nMapMode == MM_TEXT)    // if text mode, we need to convert LP to DP
    {
        DocToClient(ptCur);
        ptCur += GetDeviceScrollPosition(); // offset by current scroll amount
    }

    ScrollToPosition(ptCur);
}

//----------------------------------------------------------------------------
void DragDropView::AutoScroll(CPoint pointDP){
//----------------------------------------------------------------------------
	PROC_TRACE;


    CPoint point = pointDP;

    // get client rectangle of destination window
    CRect rectClient;
    GetClientRect(&rectClient);
    CRect rect = rectClient;

    // hit-test against inset region
    UINT nTimerID = MAKEWORD(-1, -1);
    rect.InflateRect(-20, -20);
    CSplitterWnd* pSplitter = NULL;
    if (rectClient.PtInRect(point) && !rect.PtInRect(point))
    {
        // determine which way to scroll along both X & Y axis
        if (point.x < rect.left)
            nTimerID = MAKEWORD(SB_LINEUP, HIBYTE(nTimerID));
        else if (point.x >= rect.right)
            nTimerID = MAKEWORD(SB_LINEDOWN, HIBYTE(nTimerID));
        if (point.y < rect.top)
            nTimerID = MAKEWORD(LOBYTE(nTimerID), SB_LINEUP);
        else if (point.y >= rect.bottom)
            nTimerID = MAKEWORD(LOBYTE(nTimerID), SB_LINEDOWN);
        ASSERT(nTimerID != MAKEWORD(-1, -1));

        // check for valid scroll first
        BOOL bEnableScroll = FALSE;
            bEnableScroll = OnScroll(nTimerID, 0, FALSE);
        if (!bEnableScroll)
            nTimerID = MAKEWORD(-1, -1);
    }

    // save tick count when timer ID changes
    DWORD dwTick = GetTickCount();
    if (nTimerID != m_nTimerID){
        m_dwLastTick   = dwTick;
        m_nScrollDelay = 10;
    }

    // scroll if necessary
    if (dwTick - m_dwLastTick > (DWORD)m_nScrollDelay){
        OnScroll(nTimerID, 0, TRUE);
        m_dwLastTick   = dwTick;
        m_nScrollDelay = 10;
    }

    m_nTimerID = nTimerID;
}

//----------------------------------------------------------------------------
void DragDropView::DoMoveSelection(CClientDC* pDC, CPoint pointDP, CPoint pointLP, int nEvent,  BOOL bAutoScroll /* = TRUE */){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if(m_pCurrentObject==NULL)
		return;

   CSize offset = pointLP - m_pCurrentObject->GetTopLeft();    // current offset
   offset = offset - m_offsetMove;                             // desired offset
    
    // Check to see if Autoscroll is required...
    
    if (bAutoScroll)
        AutoScroll(pointDP);
    
    // now, if the object hasn't moved off the edge of the document, move it.
    //** note that this operation is based on the object that the mouse went down
    //** on and doesn't account for other objects that are in the selection.
    //
    CSize sizeDoc = GetDocument()->GetDocumentSize();   
    if ((pointLP.x > 0) && (pointLP.y < 0) &&                   // if not off left or top
        (pointLP.x < sizeDoc.cx) && (abs(pointLP.y) < sizeDoc.cy))   // or off right or bottom
    {
        MoveSelection(offset, pointLP, nEvent);
    }
    else if (nEvent == WM_LBUTTONUP)
    {
        // oops, button up and the cursor is outside of the view
        // must "warp" the logical position back into the view
        // so the MoveSelection can be called one last time. This is
        // the only way GridView can "snap" at the end of a move, for example.
        
        if (pointLP.x < 0) pointLP.x = 15;  // off the left
        if (pointLP.y > 0) pointLP.y = -15; // off the top
        if (pointLP.x > sizeDoc.cx) pointLP.x = sizeDoc.cx - 15;        // off the right
        if (abs(pointLP.y) > sizeDoc.cy) pointLP.y = - sizeDoc.cy + 15; // off the bottom
        MoveSelection(offset, pointLP, nEvent);
    }
} 

//----------------------------------------------------------------------------
void DragDropView::MoveSelection(CSize sizeOffset, CPoint pointLP, int nEvent){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // pointLP and nEvent aren't used here, but are provided for overrides.

    for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ) {
        DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
        if (pObject->IsDraggable()) //** need:  && pObject->ParentIsNotSelected() here
            pObject->SetLocationOffset(pObject->GetTopLeft(), sizeOffset);
    }
}

//----------------------------------------------------------------------------
void DragDropView::DoDragSelection(CClientDC* pDC, CPoint pointDP, CPoint pointLP, int nEvent){
//----------------------------------------------------------------------------
	PROC_TRACE;
    
    if (nEvent == WM_LBUTTONUP) {
        DoDropSelection(pDC, pointDP, pointLP, WM_MOUSEMOVE);
        return;
    }

    if (m_bFirstMouseMove) {
        DragDropSelection* pSel = GetSelection();
        DragDropObject* pSourceObject = pSel->PrimarySelection();
        CSize sz = pSourceObject->GetSize();
        m_pDragObject->SetSize(sz); 
        m_bFirstMouseMove = FALSE;  
    }

    CPoint point (pointDP);
    ClientToScreen(&point);
    CWnd* pWin = WindowFromPoint(point);
    CM::Type cursor = CM::NODROP;

    if (m_bDirtyDropView) 
        m_pViewDirty->DropObjectAnimateClear(this, m_pDragObject, m_PtDirty);
    m_bDirtyDropView = FALSE;
    
    if (pWin->IsKindOf(RUNTIME_CLASS(DragDropView))) {
        DragDropView* pView =(DragDropView*) pWin;
        DragDropSelection* pSel = GetSelection();
        DragDropObject* pSourceObject = pSel->PrimarySelection();
        if (pView->DropObjectAllowed(this, pSourceObject, point))  // Let View decide whether a drop is legal
        {
           cursor = CM::ICON;
            if (m_bDirtyDropView = pView->DropObjectAnimateDraw(this, m_pDragObject, point))
            {
               cursor = CM::ARROW; // normal cursor
                m_pViewDirty = pView;
                m_PtDirty = point;
            }
        }
    }
    
    CM::set(cursor);  
}

//----------------------------------------------------------------------------
void DragDropView::DoDropSelection(CClientDC* pDC, CPoint pointDP, CPoint pointLP, int nEvent) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_bDirtyDropView) 
        m_pViewDirty->DropObjectAnimateClear(this, m_pDragObject, m_PtDirty);

    m_bDirtyDropView = FALSE;
    
    CPoint point (pointDP);
    ClientToScreen(&point);
    CWnd* pWin = WindowFromPoint(point);
    if (pWin->IsKindOf(RUNTIME_CLASS(DragDropView)))
    {
        DragDropView* pView =(DragDropView*) pWin;
        DragDropSelection* pSel = GetSelection();
        DragDropObject* pSourceObject = pSel->PrimarySelection();
        if (pView->DropObjectAllowed(this, pSourceObject, point))
            pView->DropObject(this, pSourceObject, point, m_nLButtonDownFlags);
    }
    else
    {
        DropFail(); 
    }

    CM::set(CM::ARROW);
}

//----------------------------------------------------------------------------
void DragDropView::DropFail(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   MessageBeep(MB_ICONASTERISK);   // try MB_ICONASTERISK in place of -1..
}

//----------------------------------------------------------------------------
void DragDropView::GeometryUpdatedSelection(){                                       
//----------------------------------------------------------------------------
	PROC_TRACE;

   
    for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ) {
        DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
        pObject->GeometryUpdated(); 
    }
}


//----------------------------------------------------------------------------
void DragDropView::HandleResizing(CClientDC* pDC, CPoint pPoint, int nEvent){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if ((m_pCurrentObject == NULL) || (!m_pCurrentObject->IsResizable())) 
       return; 
    
    if (nEvent == WM_LBUTTONDOWN) 
       m_rectXOR = m_pCurrentObject->GetBoundingRect();
                                  
    // Initialize a rectangle...
    CRect beforeRect;
    beforeRect.CopyRect(m_rectXOR);


    if (m_pCurrentObject->HandleResizing(pDC, this, &m_rectXOR, pPoint, m_handlesHit, nEvent)) {
        if (nEvent != WM_LBUTTONDOWN)
            DrawXorRect(pDC, &beforeRect);  // erase the old ghost
        if (nEvent != WM_LBUTTONUP)
            DrawXorRect(pDC, &m_rectXOR);   // draw the new ghost
    }
    else UpdateWindow();
}   

//----------------------------------------------------------------------------
void DragDropView::DrawXorRect(CClientDC* pDC, CRect* pRect){   
//----------------------------------------------------------------------------
	PROC_TRACE;

   POINT poly[5];
    CPen penGhost;
    penGhost.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));    // grey ghost
    CPen* pOldPen = pDC->SelectObject(&penGhost);           // save old pen
    int oldROP = pDC->SetROP2(R2_XORPEN);
    poly[0].x = pRect->left;
    poly[0].y = pRect->top;
    poly[1].x = pRect->right;
    poly[1].y = pRect->top;
    poly[2].x = pRect->right;
    poly[2].y = pRect->bottom;
    poly[3].x = pRect->left;
    poly[3].y = pRect->bottom;
    poly[4].x = pRect->left;
    poly[4].y = pRect->top;
    pDC->Polyline(poly, 5);
    pDC->SetROP2(oldROP);
    pDC->SelectObject(pOldPen); 
}

//----------------------------------------------------------------------------
void DragDropView::DrawXorBox(CClientDC* pDC, CPoint pt1, CPoint pt2, CRect* pRectAspect){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CRect rect;
    if (pRectAspect) {
        // adjust pt2 based on aspect ratio of input rectangle
        rect.CopyRect(pRectAspect);
        rect.NormalizeRect();
        CSize size = rect.Size();
        if (size.cy == 0) size.cy = 1;  // avoid div by zero (would require 0 size view)
        double aspect = (double)size.cx / size.cy;
        double xFlip = 1.0;
        if (pt2.x > pt1.x) 
           xFlip=-1.0;
        if (pt2.y > pt1.y) {
            pt2.y = long(pt1.y - (xFlip*((pt2.x - pt1.x)) / aspect));
        }
        else {
            pt2.y = long(pt1.y + (xFlip*((pt2.x - pt1.x)) / aspect));
        }
        
    }
    
    rect.left =  min(pt1.x, pt2.x);
    rect.right = max(pt1.x, pt2.x);
    rect.top =   max(pt1.y, pt2.y);
    rect.bottom =  min(pt1.y, pt2.y);
    DrawXorRect(pDC, &rect); 
}

//----------------------------------------------------------------------------
DragDropLink* DragDropView::NewLink(DragDropPort* pFrom, DragDropPort* pTo){
//----------------------------------------------------------------------------
	PROC_TRACE;
    
    DragDropLink* pLink = new DragDropLink(pFrom, pTo);
    
    DragDropDocument* pDocument = GetDocument();
    pDocument->AddObjectAtTail(pLink);
    return pLink;
} 

//----------------------------------------------------------------------------
void DragDropView::NoNewLink(DragDropPort* pFrom, DragDropPort* pInvalidTo){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return;
}

//----------------------------------------------------------------------------
BOOL DragDropView::StartNewLink(DragDropPort* pPort, CPoint pointLP){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!pPort->GetUserCreatedLinks()) 
       return FALSE;       

    BOOL bValidSrc = ValidSourcePort((DragDropPort*)pPort);      // true if valid source
    BOOL bValidDst = ValidDestinationPort((DragDropPort*)pPort); // true if valid destination
    if (bValidSrc || bValidDst){
        SetCapture();
        m_pTempPortMD = pPort;                                      // Port from mouse down pt
        m_pTempPortMM = new DragDropPort(pointLP, -1, PSNone, PSNone);   // will track moving mouse               

        if (bValidSrc) {
            m_pointermode = PointerModeCreateLink;
			if(m_pTempLink!=NULL)
				delete m_pTempLink;
            m_pTempLink = new DragDropLink(m_pTempPortMD, m_pTempPortMM); // link between the two ports
            SetValidPorts();                                // set up the cached values of ValidLink() calls...
        }
        else {
            m_pointermode = PointerModeCreateLinkFrom;
			if(m_pTempLink!=NULL)
				delete m_pTempLink;
            m_pTempLink = new DragDropLink(m_pTempPortMM, m_pTempPortMD);      // link between the two ports
            SetValidPorts2();                               // set up the cached values of ValidLink() calls...
        }
        AddObjectAtTail(m_pTempLink);
        m_pLastSnapToPort = NULL;                       // haven't snapped to port yet
    }
    return (bValidSrc || bValidDst);
}

//----------------------------------------------------------------------------
BOOL DragDropView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo){    
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_pEditText && (pHandlerInfo == NULL) && (nCode == CN_COMMAND)) {
        switch (nID){
            case ID_EDIT_COPY:
                m_pEditText->Copy();    
                return TRUE;
            case ID_EDIT_CUT:
                m_pEditText->Cut();    
                return TRUE;
            case ID_EDIT_PASTE:
                m_pEditText->Paste();    
                return TRUE;
            case ID_EDIT_CLEAR:
                {
                int start, end;
                m_pEditText->GetSel(start, end);
                if (end == start)
                    m_pEditText->SetSel(start, end+1);
                m_pEditText->Clear();
                return TRUE;
                }               
                break;
            case ID_EDIT_UNDO:
                m_pEditText->Undo();    
                return TRUE;
            default:
                break;
        }
    }
    return inherited::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//----------------------------------------------------------------------------
afx_msg void DragDropView::OnEnUpdate(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_pEditText) 
       m_pEditText->OnEnUpdate();
}


//----------------------------------------------------------------------------
void DragDropView::SetEditControl(DragDropTextEdit* pEdit) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_pEditText = pEdit;
   if (!pEdit) {
      m_bAbortInputAction = TRUE;
   }
} 

//----------------------------------------------------------------------------     
void DragDropView::DoEndEdit(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_pEditText){
        DragDropText* pText = m_pEditText->GetTextObject();
        ASSERT(pText);
        pText->DoEndEdit(this);
        m_pEditText = NULL; 
    }
}


//----------------------------------------------------------------------------
int DragDropView::GetNewControlID(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   int val = m_nNewControlID;
   m_nNewControlID++;
   return val;
}

//----------------------------------------------------------------------------
void DragDropView::SetBaseControlID(int nBase){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_nNewControlID = nBase;
}


//----------------------------------------------------------------------------
void DragDropView::GetRectDP(CRect* pRect){
//----------------------------------------------------------------------------
	PROC_TRACE;
    
   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.LPtoDP(pRect);
}

//----------------------------------------------------------------------------
void DragDropView::GetClientRectLPZero(CRect* pRect){
//----------------------------------------------------------------------------
	PROC_TRACE;

   GetClientRectLP(pRect);
    
 
    pRect->right  = pRect->right - pRect->left;
    pRect->left   = 0;
    pRect->bottom = pRect->bottom - pRect->top;
    pRect->top    = 0;
}

//----------------------------------------------------------------------------
void DragDropView::GetClientRectLP(CRect* pRect){
//----------------------------------------------------------------------------
	PROC_TRACE;

   GetClientRect(pRect);
   ClientToDoc(pRect);
}

//----------------------------------------------------------------------------
void DragDropView::OnLButtonDown(UINT nFlags, CPoint point){   
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC dc(this);
   OnPrepareDC(&dc);
   CPoint pointLP = point;
   dc.DPtoLP(&pointLP);
   m_bDirtyDropView = FALSE;   // haven't written in another View yet.
   m_bFirstMouseMove = TRUE;   // next call to MouseMove will be first for this operation
   m_nLButtonDownFlags = nFlags;   // save flags
   m_bAbortInputAction = FALSE;

   DoLButtonDown(nFlags, point, pointLP, &dc);
}

//----------------------------------------------------------------------------    
void DragDropView::DoLButtonDown(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC){   
//----------------------------------------------------------------------------
	PROC_TRACE;
    if (m_bAbortInputAction) return;    // can be set by exit edit mode action

    BOOL bControl = (nFlags & MK_CONTROL) > 0 ? TRUE : FALSE;
    BOOL bShifted = (nFlags & MK_SHIFT)   > 0 ? TRUE : FALSE;


    // end the Edit of an TextObject
    //
    DoEndEdit();

    if (m_nClearHandleCount != 0) {
        // This interlock counter should really be zero here.  The only 
        // time I've seen it wrong is when I hit a breakpoint while dragging an
        // object, but this should trace the error and fix it...
        TRACE0("CDragDropView: LButtonDown with count =/= 0\n");
        m_nClearHandleCount = 0;
    }       

    // Make a decision about what is to be done with this mouse down...
    
    m_pointMouseDown = pointLP; // save for potential drag
    m_pointMouseMove = pointLP; // save for potential drag
    m_nTimerID = MAKEWORD(-1, -1);  // for autoscroll


    DragDropHandle* pHandle = SelectedHandleTest(pDC, pointLP);
    
    if (pHandle != NULL)
    {   // a handle has been grabbed...
        SetCapture();
        m_handlesHit = pHandle->GetHandleType ();                                                   
        m_pCurrentObject = pHandle->GetHandleFor();     // get the object this handle is attached to
        m_pointermode = PointerModeResize;
        ClearSelectionHandles();                // erase handles for drag
        UpdateWindow();                         // Update the windows before drawing XOR box
        HandleResizing(pDC, pointLP, WM_LBUTTONDOWN);
        return;
    }

    // something other than a handle grabbed...
    
    DragDropPort* pPort = PortTest(pDC, pointLP);
    
    if (pPort != NULL){
        if (StartNewLink(pPort, pointLP)) return;
    }

    m_pCurrentObject = DoPickInDocument(pDC, pointLP, TRUE); // TRUE = pick selectable object

    if (m_pCurrentObject != NULL){
        SetCapture();
        // This may be a Fake Button, check to see if the object wants Button protocol
        BOOL bButton = m_pCurrentObject->DoLButtonDown(nFlags, pointDP, pointLP, pDC, this);
        if (bButton){
            m_pointermode = PointerModeButton;
            m_bInsideButton = TRUE;
            UpdateWindow();                     // Must force the update so user sees feedback on quick clicks
        }
        else{
            m_pointermode = PointerModeSelection;
        }
        return;
    }
    else{
        if (!bShifted) ClearSelection();   // mouse down on white space... start drag-selection box
        if (m_bAbortInputAction) return;
        UpdateWindow();     // about to draw in XOR mode, make sure handles are erased before doing this
        SetCapture();
        m_pointermode = PointerModeDragBoxSelection;
        DrawXorBox(pDC, m_pointMouseDown, m_pointMouseMove);         //draw first box
    }
}

//----------------------------------------------------------------------------
void DragDropView::DoUncapturedMouseMove(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return;
}

//----------------------------------------------------------------------------
void DragDropView::OnMouseMove(UINT nFlags, CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CClientDC dc(this);
    OnPrepareDC(&dc);
    CPoint pointLP = point;
    dc.DPtoLP(&pointLP);

    DoMouseMove(nFlags, point, pointLP, &dc);
}

//----------------------------------------------------------------------------
void DragDropView::DoMouseMove(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

    DragDropDocument* pDocument = GetDocument();

    BOOL bControl = (nFlags & MK_CONTROL) > 0 ? TRUE : FALSE;
    BOOL bShifted = (nFlags & MK_SHIFT)   > 0 ? TRUE : FALSE;

    // MouseOver handling for objects
    //
    // mouseOverEnd
    //
    DragDropObject* pObject = DoPickInDocument(pDC, pointLP, FALSE); // FALSE = pick anything
    // get the parent
    while (pObject!=NULL && pObject->GetParent()!=NULL) {
        pObject = pObject->GetParent();
    }

    if(m_pMouseOverObject!=NULL  && m_pMouseOverObject!=pObject)
    {
       m_pMouseOverObject->DoMouseOverEnd(nFlags, pointDP,pointLP, pDC,this);
       m_pMouseOverObject=NULL;
    }
    //
    // mouseOver
    //
    if(m_pMouseOverObject!=NULL && m_pMouseOverObject==pObject)
       m_pMouseOverObject->DoMouseOver(nFlags, pointDP,pointLP,pDC,this);
    //  
    // mouseOverStart
    //
    if(pObject!=NULL && pObject!=m_pMouseOverObject)
    {
       m_pMouseOverObject=pObject;
       m_pMouseOverObject->DoMouseOverStart(nFlags, pointDP,pointLP,pDC,this);
    }


    if (GetCapture() != this) 
    {
        // if there is an object under the mouse, give it a chance to affect the cursor
        DragDropObject* pObject = PickInView(pDC, pointLP, FALSE);   // check view too. FALSE = pick anything
        if (pObject)
            // a view object, don't worry about parent objects here.
            pObject->DoUncapturedMouseMove(nFlags, pointDP, pointLP, pDC, this);
        else {
            pObject = DoPickInDocument(pDC, pointLP, FALSE); // FALSE = pick anything
            if (pObject) 
                while (pObject && !pObject->DoUncapturedMouseMove(nFlags, pointDP, pointLP, pDC, this)) {
                    // object didn't want call, check parent
                    pObject = pObject->GetParent(); // find "root"
                }
            else{
                CM::set(CM::ARROW);
                DoUncapturedMouseMove(nFlags, pointDP, pointLP, pDC);    // call the view's handler if no object found
            }    
        }
		// create link will be aborted because lost of focus
		//
		if(m_pTempLink!=NULL){
		    delete m_pTempLink;
            delete m_pTempPortMM;
            m_pTempLink = NULL;
            m_pTempPortMM = NULL;
		}

        return; // If this window (view) didn't capture the mouse,
                // then the user isn't drawing in this window.
    }
    


    switch (m_pointermode) {  
        case PointerModeSelection:  // check for drag movement
        { 
            if (m_pCurrentObject == NULL)
                break;
            if ((abs(m_pointMouseDown.x - pointLP.x) > 10) |
                (abs(m_pointMouseDown.y - pointLP.y) > 10)) 
            {
                if (bShifted) // if shifted, only add to the selection
                {
                     m_pCurrentObject = m_pSelection->ExtendSelection(m_pCurrentObject);
                }
                else  // if not shifted, only change if object is not in current selection
                {
                    if (!m_pSelection->IsInSelection(m_pCurrentObject))
                        m_pCurrentObject = m_pSelection->SelectObject(m_pCurrentObject);
                }
                // Leave if user deleted object upon selection
                if (m_pCurrentObject == NULL)
                    break;
                m_offsetMove = m_pointMouseDown - m_pCurrentObject->GetTopLeft();
                m_pointermode = PointerModeMove; // and fall thru to move code in case below.
                ClearSelectionHandles();    // erase handles for drag
                UpdateWindow(); // do the Draw NOW, don't wait for Windows to deliver message
                                // Otherwise the update can erase part of the first XOR Box
            }
            else
            {
                break;  
            }
        // NOTE that if mode was just switched to PointerModeMove above, we fall through to the "case" below
        // to move the object.
        }

        case PointerModeMove: 
        {
            if (bControl){
                DoDragSelection(pDC, pointDP, pointLP, WM_MOUSEMOVE);   // start a drag-copy
                m_pointermode = PointerModeClone;                    // change modes
            }
            else {
                DoMoveSelection(pDC, pointDP, pointLP, WM_MOUSEMOVE);
                UpdateWindow(); // do the Draw NOW, don't wait for Windows to deliver message
            }
            if (m_pCurrentObject && m_pCurrentObject->IsNonStandardMove())					// new 8/5/97
				m_offsetMove = pointLP - m_pCurrentObject->GetTopLeft();    // new 8/5/97 to fix moving callouts
            break;          
        }                                   

        case PointerModeClone: 
        {
            DoDragSelection(pDC, pointDP, pointLP, WM_MOUSEMOVE);   // continue a drag-copy
            break;          
        }                                   
                
        case PointerModeResize:
            HandleResizing(pDC, pointLP, WM_MOUSEMOVE);
            break;
                
        case PointerModeCreateLink:
        {
            // Check first to see if Autoscroll is required...
            AutoScroll(pointDP);
            
            // now do gravity snapping.
            DragDropPort* pSnapToPort = PickNearestPort(pDC, pointLP);      //see if there is a port to snap to
            
            if (pSnapToPort) 
            {
                // if the snapToPort is the same as last time, avoid the redraw to minimize flashing
                if (pSnapToPort != m_pLastSnapToPort)
                {   
                    CPoint SnapPt = pSnapToPort->GetToLinkPoint();
                    m_pTempPortMM->SetToSide(pSnapToPort->GetToSide());     // adopt style of snap port
                    m_pTempPortMM->SetLocation(SnapPt);
                }
                m_pLastSnapToPort = pSnapToPort;                            // save the snap-to port
            }
            else  // no port to snap to, simply draw link to mouse location
            {                                                          
                m_pTempPortMM->SetLocation(pointLP);                       // set location of invisible port
                m_pTempPortMM->SetToSide(PSNone);                           // set no snap point
                m_pLastSnapToPort = NULL;                                   // 
            }
            break;
        }

        case PointerModeCreateLinkFrom:    // creating a backwards link (starting at To port)
        {
            // Check first to see if Autoscroll is required...
            AutoScroll(pointDP);
            
            // now do gravity snapping.
            DragDropPort* pSnapToPort = PickNearestPort(pDC, pointLP);      //see if there is a port to snap to
            
            if (pSnapToPort) 
            {
                // if the snapToPort is the same as last time, avoid the redraw to minimize flashing
                if (pSnapToPort != m_pLastSnapToPort)
                {   
                    CPoint SnapPt = pSnapToPort->GetFromLinkPoint();
                    m_pTempPortMM->SetFromSide(pSnapToPort->GetFromSide());     // adopt style of snap port
                    m_pTempPortMM->SetLocation(SnapPt);
                }
                m_pLastSnapToPort = pSnapToPort;                            // save the snap-to port
            }
            else  // no port to snap to, simply draw link to mouse location
            {                                                          
                m_pTempPortMM->SetLocation(pointLP);                       // set location of invisible port
                m_pTempPortMM->SetFromSide(PSNone);                         // set no snap point
                m_pLastSnapToPort = NULL;                                   // 
            }
            break;
        }
            
        case PointerModeDragBoxSelection:
        {
            // doing drag-box selection
            DrawXorBox(pDC, m_pointMouseDown, m_pointMouseMove);         //erase old
            m_pointMouseMove = pointLP;
            DrawXorBox(pDC, m_pointMouseDown, m_pointMouseMove);        // draw new 
            break;
        }

        case PointerModeButton:
        {
            // Must look to see if the cursor has left or entered the button region
            DragDropObject* pObject = DoPickInDocument(pDC, pointLP, TRUE); // TRUE = pick selectable object
            if (!m_pCurrentObject) return;  // WVR added this!!! 30 Apr 96
            if (pObject == m_pCurrentObject)
            {
                // cursor is inside button, deliver Enter if this is new state
                if (!m_bInsideButton) m_pCurrentObject->DoButtonDownEnter(nFlags, pointDP, pointLP, pDC, this);
                UpdateWindow();                     // Must force the update so user sees feedback on quick clicks
                m_bInsideButton = TRUE;
            }
            else
            {
                // cursor is outside button, deliver Leave if this is new state
                if (!m_bInsideButton) m_pCurrentObject->DoButtonDownLeave(nFlags, pointDP, pointLP, pDC, this);
                UpdateWindow();                     // Must force the update so user sees feedback on quick clicks
                m_bInsideButton = FALSE;
            }
        }
        
    } // end switch

    m_pointMouseMove = pointLP; // 
    return;
}


//----------------------------------------------------------------------------///////////////////////////////////////////////////////////////////// ////////
void DragDropView::OnLButtonUp(UINT nFlags, CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CClientDC dc(this);

    // CScrollView changes the viewport origin and mapping mode.
    // It's necessary to convert the point from device coordinates
    // to logical coordinates, such as are stored in the document.
    OnPrepareDC(&dc);  // set up mapping mode and viewport origin
    CPoint pointLP = point;
    dc.DPtoLP(&pointLP);

    // now that we've done the customary setup, call an overridable member to do the DoCalculate...
    
    DoLButtonUp(nFlags, point, pointLP, &dc);
    m_pCurrentObject = NULL; 
}
    

//----------------------------------------------------------------------------/////////////////////////////////////////////////////////////////////////////
void DragDropView::DoLButtonUp(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;
    // No action is needed if this window (view) didn't capture the mouse.
    
    if (GetCapture() != this)
        return;

    DragDropDocument* pDocument = GetDocument();

    BOOL bControl = (nFlags & MK_CONTROL) > 0 ? TRUE : FALSE;
    BOOL bShifted = (nFlags & MK_SHIFT)   > 0 ? TRUE : FALSE;
    

    switch (m_pointermode) {    
        case PointerModeSelection: {
            if (m_pCurrentObject){
                if (bShifted || bControl)
                    m_pSelection->ToggleSelection(m_pCurrentObject);    
                else
                { // this is a simple "Click" on an object here
                    DragDropObject* pObj = m_pSelection->SelectObject(m_pCurrentObject); 
                    while (pObj && !pObj->DoLButtonClick(nFlags, pointDP, pointLP, pDC, this)) 
                    {
                        // object didn't want call, check parent
                        pObj = pObj->GetParent(); // find "root"
                    }
					// Now, deliver the Button up Event 
					// added from A.H.DoLButtonUp
                    pObj = m_pSelection->SelectObject(m_pCurrentObject); 
                    while (pObj && !pObj->DoLButtonUp(nFlags, pointDP, pointLP, pDC, this)){
                        // object didn't want call, check parent
                        pObj = pObj->GetParent(); // find "root"
                    }
				}
            }                                    
            break;                  
            }
                
        case PointerModeMove: {
            // Now, deliver the Button up Event 
            // added from A.H.DoLButtonUp
            {
               DragDropObject* pObj = m_pSelection->SelectObject(m_pCurrentObject); 
               while (pObj && !pObj->DoLButtonUp(nFlags, pointDP, pointLP, pDC, this)){
                  // object didn't want call, check parent
                  pObj = pObj->GetParent(); // find "root"
               }
            }

            DoMoveSelection(pDC, pointDP, pointLP, WM_LBUTTONUP);
            GeometryUpdatedSelection();
            RestoreSelectionHandles();  // restore handles now that drag is done
            if (m_pCurrentObject && m_pCurrentObject->IsKindOf(RUNTIME_CLASS(DragDropPort)))  // drag port hack
                        ClearSelection();
            break; 
            }

        case PointerModeClone: 
        {
            DoDragSelection(pDC, pointDP, pointLP, WM_LBUTTONUP);   // continue a drag-copy 
            RestoreSelectionHandles();  // restore handles now that copy is done
            break;          
        }                                   
                
        case PointerModeResize:  // resizing
            HandleResizing(pDC, pointLP, WM_LBUTTONUP);
            GeometryUpdatedSelection();
            RestoreSelectionHandles();  // restore handles now that resizing is done
            break;
            
        case PointerModeCreateLink:
        {
            DragDropPort* pFrom = m_pTempPortMD; //new
                        
            delete m_pTempLink;
            delete m_pTempPortMM;
            m_pTempLink = NULL;
            m_pTempPortMM = NULL;
                
            DragDropPort* pTo = PickNearestPort(pDC, pointLP);  // see if there is a port to snap to

            if ((pTo) && (pFrom != pTo)) { 
                m_pCurrentObject = NewLink(pFrom,(DragDropPort*) pTo);
            }
            else {
                // Report that no link was created, but check to see if there
                // might have been an invalid port under the mouse on ButtonUp just
                // in case there is something to do...
                
                DragDropPort* pInvalidToPort = PortTest(pDC, pointLP);               
                
                // pInvalidPort is NULL if anything other than a port at pointLP.
                NoNewLink(pFrom, pInvalidToPort);
            }
            
            break;
        }           
            
        case PointerModeCreateLinkFrom:
        {
            DragDropPort* pTo = m_pTempPortMD;
                        
            delete m_pTempLink;
            delete m_pTempPortMM;
            m_pTempLink = NULL;
            m_pTempPortMM = NULL;
                
            DragDropPort* pFrom = PickNearestPort(pDC, pointLP);  // see if there is a port to snap to

            if ((pFrom) && (pFrom != pTo)) { 
                m_pCurrentObject = NewLink(pFrom, pTo);
            }
            else {
                // Report that no link was created, but check to see if there
                // might have been an invalid port under the mouse on ButtonUp just
                // in case there is something to do...
                
                DragDropPort* pInvalidFromPort = PortTest(pDC, pointLP);               
                
                // pInvalidPort is NULL if anything other than a port at pointLP.
                NoNewLink(pInvalidFromPort, pTo);
            }
            
            break;
        }           
        case PointerModeDragBoxSelection:
        {
            DrawXorBox(pDC, m_pointMouseDown, m_pointMouseMove);         // last erase
            if (m_pointMouseDown != m_pointMouseMove)    // ignore if just a click
            { 
                // have to build a rectangle where left < right and top > bottom.
                int x1 = m_pointMouseDown.x;
                int x2 = m_pointMouseMove.x; 
                int y1 = m_pointMouseDown.y;
                int y2 = m_pointMouseMove.y; 
                CRect rect;
                rect.left = (x1 < x2) ? x1 : x2;
                rect.right = (x1 > x2) ? x1 : x2;
                rect.top = (y1 > y2) ? y1 : y2;
                rect.bottom = (y1 < y2) ? y1 : y2;
                DoSelectionInBox (&rect);
            }
            else
                OnClickOnBackground(m_pointMouseMove);
            break;
        } 

        case PointerModeButton:
        {
            if (m_pCurrentObject == NULL) break;    // button was deleted...

            // Must look to see if the cursor has left or entered the button region
            DragDropObject* pObject = DoPickInDocument(pDC, pointLP, TRUE); // TRUE = pick selectable object
            if (pObject == m_pCurrentObject)
            {
                // cursor is inside button, deliver Enter if this is new state
                if (!m_bInsideButton) m_pCurrentObject->DoButtonDownEnter(nFlags, pointDP, pointLP, pDC, this);
                UpdateWindow();                     // Must force the update so user sees feedback on quick clicks
                m_bInsideButton = TRUE;
            }
            else
            {
                // cursor is outside button, deliver Leasve if this is new state
                if (m_bInsideButton) m_pCurrentObject->DoButtonDownLeave(nFlags, pointDP, pointLP, pDC, this);
                UpdateWindow();                     // Must force the update so user sees feedback on quick clicks
                m_bInsideButton = FALSE;
            }
            // Now, deliver the Button up Event
            if (m_pCurrentObject)
                m_pCurrentObject->DoLButtonUp(nFlags, pointDP, pointLP, pDC, this);
        }
        
    } // end switch             
    
    m_pointermode = PointerModeNone;
    ReleaseCapture();   // Release the mouse capture established at

    return;
}

//----------------------------------------------------------------------------
void DragDropView::OnLButtonDblClk(UINT nFlags, CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC dc(this);

    // CScrollView changes the viewport origin and mapping mode.
    // It's necessary to convert the point from device coordinates
    // to logical coordinates, such as are stored in the document.
    OnPrepareDC(&dc);  // set up mapping mode and viewport origin
    CPoint pointLP = point;
    dc.DPtoLP(&pointLP);

    // now that we've done the customary setup, call an overridable member to do the DoCalculate...
    
    DragDropObject* pObject = DoPickInDocument(&dc, pointLP, FALSE); // FALSE = pick anything           
    
    // end the Edit of an TextObject
    //
    if(pObject)
       DoEndEdit();

    // Climb the Area hierarchy until an Object handles the double-click.
    
    while (pObject){
        if (pObject->DoLButtonDblClk(nFlags, point, pointLP, &dc, this)) 
           return;
        pObject = pObject->m_pParentArea;
    }
    
    // If no Object handled the double-click, give the View a chance.
    
    DoLButtonDblClk(nFlags, point, pointLP, &dc);
}

//----------------------------------------------------------------------------                         
BOOL DragDropView::DoLButtonDblClk(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return FALSE;
}

//----------------------------------------------------------------------------
void DragDropView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   switch (nChar) {
      case VK_PRIOR: {
        SHORT x = GetKeyState(VK_CONTROL);
        if (x & 0x8000)
            OnScroll(MAKEWORD(SB_PAGELEFT, SB_THUMBPOSITION), 0, TRUE);  // horizontal
        else
            OnScroll(MAKEWORD(SB_THUMBPOSITION, SB_PAGEUP), 0, TRUE);  // vertical
        break;
      }
      case VK_NEXT: {
        SHORT x = GetKeyState(VK_CONTROL);
        if (x & 0x8000)
            OnScroll(MAKEWORD(SB_PAGERIGHT, SB_THUMBPOSITION), 0, TRUE);  // horizontal
        else
            OnScroll(MAKEWORD(SB_THUMBPOSITION, SB_PAGEDOWN), 0, TRUE);  // vertical
        break;
      }
      case VK_ESCAPE: {
        CancelActionInProgress(0, CPoint(0, 0));
        break;
      }
      default:
	    inherited::OnKeyDown(nChar, nRepCnt, nFlags);
        break;
    }
}

//----------------------------------------------------------------------------
BOOL DragDropView::CancelActionInProgress(UINT nFlags, CPoint pointDP){
//----------------------------------------------------------------------------
	PROC_TRACE;
    
    if (GetCapture() != this)
        return FALSE;

    CClientDC dc(this);

    // CScrollView changes the viewport origin and mapping mode.
    // It's necessary to convert the point from device coordinates
    // to logical coordinates, such as are stored in the document.
    OnPrepareDC(&dc);  // set up mapping mode and viewport origin
    CPoint pointLP = pointDP;
    dc.DPtoLP(&pointLP);


    switch (m_pointermode) {    
        case PointerModeSelection: {
            break;                  
            }
                
        case PointerModeMove: {
            DoMoveSelection(&dc, pointDP, pointLP, WM_LBUTTONUP);
            GeometryUpdatedSelection();
            RestoreSelectionHandles();  // restore handles now that drag is done
            if (m_pCurrentObject && m_pCurrentObject->IsKindOf(RUNTIME_CLASS(DragDropPort)))  // drag port hack
                        ClearSelection();
            break; 
            }

        case PointerModeClone: 
        {
            DoDragSelection(&dc, pointDP, pointLP, WM_LBUTTONUP);   // continue a drag-copy 
            RestoreSelectionHandles();  // restore handles now that copy is done
            break;          
        }                                   
                
        case PointerModeResize:  // resizing
            HandleResizing(&dc, pointLP, WM_LBUTTONUP);
            GeometryUpdatedSelection();
            RestoreSelectionHandles();  // restore handles now that resizing is done
            break;
            
        case PointerModeCreateLink:
        {
            delete m_pTempLink;
            delete m_pTempPortMM;
            m_pTempLink = NULL;
            m_pTempPortMM = NULL;    
            
            NoNewLink(m_pTempPortMD, NULL);    
            break;
        }           
            
         case PointerModeCreateLinkFrom:
        {
            delete m_pTempLink;
            delete m_pTempPortMM;
            m_pTempLink = NULL;
            m_pTempPortMM = NULL;    
            
            NoNewLink(NULL, m_pTempPortMD);    
            break;
        }           

       case PointerModeDragBoxSelection:
        {
            // doing drag-box selection
            DrawXorBox(&dc, m_pointMouseDown, m_pointMouseMove);         // last erase
            break;
        } 

        case PointerModeButton:
        {
            // deliver Leave if not already outside
            if (m_bInsideButton) m_pCurrentObject->DoButtonDownLeave(nFlags, pointDP, pointLP, &dc, this);
            UpdateWindow();                     // Must force the update so user sees feedback on quick clicks
            m_bInsideButton = FALSE;

            // Now, deliver the Button up Event
            m_pCurrentObject->DoLButtonUp(nFlags, pointDP, pointLP, &dc, this);
        }
        
    } // end switch             
    
    m_pointermode = PointerModeNone;
    ReleaseCapture();   // Release the mouse capture established at
    return TRUE;        // TRUE means an action was cancelled
}


//----------------------------------------------------------------------------
void DragDropView::DocToClient(CPoint& point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.LPtoDP(&point); // convert logical point to device point
}

//----------------------------------------------------------------------------
void DragDropView::ClientToDoc(CPoint& point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.DPtoLP(&point); // convert device point to logical point
}

//----------------------------------------------------------------------------
void DragDropView::DocToClient(CRect* rect){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.LPtoDP(rect); // convert logical point to device point
}

//----------------------------------------------------------------------------
void DragDropView::ClientToDoc(CRect* rect){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.DPtoLP(rect); // convert device point to logical point
}

//----------------------------------------------------------------------------
void DragDropView::DocToClient(CSize& size){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.LPtoDP(&size); // convert logical point to device point
}

//----------------------------------------------------------------------------
void DragDropView::ClientToDoc(CSize& size){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.DPtoLP(&size); // convert device point to logical point
}



//----------------------------------------------------------------------------
void DragDropView::OnClickOnBackground(CPoint point){ 
//----------------------------------------------------------------------------
	PROC_TRACE;

}
