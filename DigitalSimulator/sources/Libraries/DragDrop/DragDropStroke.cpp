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
#include "DragDropStroke.h"
#include "DragDropSelection.h"

IMPLEMENT_SERIAL(DragDropStroke, DragDropDrawable, 2)

//----------------------------------------------------------------------------
DragDropStroke::DragDropStroke(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_bChangingBoundingRect = FALSE;
	m_lastHitSegment        = -1;
   m_highlighted           = false;
   m_selected             = false;
}


//----------------------------------------------------------------------------
DragDropStroke::DragDropStroke(UINT nPenWidth) : DragDropDrawable(CPoint (0,0), CSize(0,0)){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetPenWidth (nPenWidth);
   m_nHighlightWidth = 0;               // default, no highlight
   m_lHighlightColor = RGB(0,255,0);    // bright green
   m_bChangingBoundingRect = FALSE;
	m_lastHitSegment        = -1;
   m_highlighted           = false;
   m_selected              = false;
}


//----------------------------------------------------------------------------
void DragDropStroke::GeometryChange(CRect* pRectPrevious){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // recalculate all the points after a drag operation.  
   // Note, DragDropLink should never go through here...
   //
   if (!m_bChangingBoundingRect)  {
       CPoint ptNew = GetLocation();
       CPoint ptPrev = pRectPrevious->TopLeft();
       CSize sizeOffset = (ptNew - ptPrev);
        
       for (int i=0; i < NumPoints(); i++) {  
           SetPointX(i, GetPoint(i)+sizeOffset);
       }
   }
}


//----------------------------------------------------------------------------
DragDropObject* DragDropStroke::Clone() const{                     
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pObject = inherited::Clone();

    ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropStroke)));                  
    DragDropStroke* pStroke =(DragDropStroke*) pObject;

    pStroke->m_bChangingBoundingRect = m_bChangingBoundingRect;
    pStroke->m_nHighlightWidth = m_nHighlightWidth;
    pStroke->m_lHighlightColor = m_lHighlightColor;

    pStroke->m_dwaPoints.RemoveAll();
    for (int i=0; i < m_dwaPoints.GetSize(); i++) {  
        pStroke->m_dwaPoints.Add(m_dwaPoints.GetAt(i));
    }

    return pObject;
}


//----------------------------------------------------------------------------
void DragDropStroke::AddPoint(CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_dwaPoints.Add(point.x);
   m_dwaPoints.Add(point.y);
}

//----------------------------------------------------------------------------
void DragDropStroke::InsertPoint(long i, CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_dwaPoints.InsertAt(i*2  , point.x);
   m_dwaPoints.InsertAt(i*2+1, point.y);
}

//----------------------------------------------------------------------------
void DragDropStroke::SetPoint(int i, CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_dwaPoints.SetAt(i*2,   point.x);
   m_dwaPoints.SetAt(i*2+1, point.y);
    
   FinishStroke();  // An expensive way but easy to set the bounding rectangle...
}

//----------------------------------------------------------------------------
void DragDropStroke::SetPointX(int i, CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_dwaPoints.SetAt(i*2,   point.x);
   m_dwaPoints.SetAt(i*2+1, point.y);
}

//----------------------------------------------------------------------------
CPoint DragDropStroke::GetPoint(int i) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    return CPoint(m_dwaPoints[i*2], m_dwaPoints[i*2+1]); 
}

//----------------------------------------------------------------------------
int DragDropStroke::NumPoints() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_dwaPoints.GetSize()/2;
}

//----------------------------------------------------------------------------
BOOL DragDropStroke::paint(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // draw highlight if the m_highlight' flag is set
   //
   if (m_highlighted || m_selected) {
      #pragma TODO("CPen nicht jedesmal neu erzeugen. Besser dies zu einem Member der Klasse machen!!!!" )
      CPen penHiLight;
      if (!penHiLight.CreatePen(PS_SOLID, m_nHighlightWidth, m_lHighlightColor))
         return FALSE;
      CPen* pOldPen = pDC->SelectObject(&penHiLight);
      pDC->MoveTo(GetPoint(0));
      for (int i=1; i < NumPoints(); i++){
         pDC->LineTo(GetPoint(i));
      }
      pDC->SelectObject(pOldPen);
   }

    ////////////////////////////////////////////////////////
    // Normal draw
    ////////////////////////////////////////////////////////
    CPen *pPen, *pOldPen;
    PreparePen(pDC, pPen, pOldPen);

    pDC->MoveTo(GetPoint(0));
    for (int i=1; i < NumPoints(); i++){
        pDC->LineTo(GetPoint(i));
    }
    PostPen(pDC, pPen, pOldPen);   

    return TRUE;
}

//----------------------------------------------------------------------------
BOOL DragDropStroke::DrawXorObject(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CPen penStroke;
   if (!penStroke.CreatePen(PS_SOLID, 1/*m_nPenWidth*/, RGB(128,128,128)))
        return FALSE;
   
   CPen* pOldPen = pDC->SelectObject(&penStroke);
   int oldROP = pDC->SetROP2(R2_XORPEN);
   pDC->MoveTo(GetPoint(0));
   for (int i=1; i < NumPoints(); i++){
       pDC->LineTo(GetPoint(i));
   }   
   pDC->SetROP2(oldROP);
   pDC->SelectObject(pOldPen);
   return TRUE;
}

//----------------------------------------------------------------------------
void DragDropStroke::HighlightXOR(CDC* pDC, CRect* pRect){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CPen penStroke;
    if (!penStroke.CreatePen(PS_SOLID, 5/*m_nPenWidth*/, RGB(128,128,128)))
        return;
    CPen* pOldPen = pDC->SelectObject(&penStroke);
    int oldROP = pDC->SetROP2(R2_XORPEN);
    pDC->MoveTo(GetPoint(0));
    for (int i=1; i < NumPoints(); i++)
    {
        pDC->LineTo(GetPoint(i));
    }   
    pDC->SetROP2(oldROP);
    pDC->SelectObject(pOldPen);
}                                                                     


//----------------------------------------------------------------------------
void DragDropStroke::GainedSelection(DragDropSelection* pSelection){
//----------------------------------------------------------------------------
	PROC_TRACE;

   
   if (!IsResizable()) {
       pSelection->CreateBoundingHandle (this);    
       return;
   }
       
   CPoint point;
   for (int i=0; i < NumPoints(); i++) {
       point = GetPoint(i);
       pSelection->CreateResizeHandle (this, point.x, point.y, i + HandlesLast, TRUE);
   }
   
}

//----------------------------------------------------------------------------
BOOL DragDropStroke::HandleResizing(CClientDC* pDC, DragDropView* pView, CRect* pRect, CPoint pPoint, int nHandleHit, int nEvent, int, int){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetPoint (nHandleHit - HandlesLast, pPoint);        // force the point in the Stroke to the new location
   SetUpdateNeeded(TRUE);

   return FALSE;   // let the view draw the XOR'd rectangle    
}



static BOOL bPtOnLine;
static CPoint ptToCheck;
static int n_xslop = 10;    //** these should probably be settable options **
static int n_yslop = 10;

//----------------------------------------------------------------------------
void CALLBACK CheckPoint(int xPos, int yPos, LPSTR lphdc){ 
//----------------------------------------------------------------------------


    if ((abs(ptToCheck.x - xPos) <= n_xslop) && (abs(ptToCheck.y - yPos) <= n_yslop))  bPtOnLine = TRUE;

}

//----------------------------------------------------------------------------
BOOL DragDropStroke::PtInObject(CClientDC* pDC, CPoint ptToCheckLP, CPoint ptToCheckDP){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_lastHitSegment = -1;

    // first, so a bounding box check with the bounding box expanded by "slop"

    // a simple check to see if the point to check
    // is contained within the bounding rectangle for this object.

    CRect rectNode = GetBoundingRect();

    // note that PtInRect only DoCalculates for DP mode
    pDC->LPtoDP(&rectNode);
    rectNode.InflateRect(1,1);  // 1 pixel either way on bounding box check
    CPoint pt;
    pt.x = ptToCheckDP.x;
    pt.y = ptToCheckDP.y;
    if(!rectNode.PtInRect(pt)) return FALSE;
                    

    bPtOnLine = FALSE;
    ptToCheck.x = ptToCheckLP.x;
    ptToCheck.y = ptToCheckLP.y;
    
    FARPROC lpProc;
    lpProc = (FARPROC)CheckPoint;

    // for each segment of the stroke, call LineDDA to get all the points along the line...
        
    int nFirstPoint = GetFirstPickPoint();
    int nLastPoint  = GetLastPickPoint();

    CPoint ptStart = GetPoint(nFirstPoint);
    CPoint ptEnd;
    for (int i=nFirstPoint+1; i < nLastPoint; i++)
    {
        ptEnd = GetPoint(i);
        ::LineDDA(ptStart.x, ptStart.y, ptEnd.x, ptEnd.y, (LINEDDAPROC)lpProc, NULL);
        ptStart = ptEnd;
		if(bPtOnLine ==TRUE){
			m_lastHitSegment = i-1;
			break;
		}
    }   

    return bPtOnLine;
}


//----------------------------------------------------------------------------
int DragDropStroke::GetFirstPickPoint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return 0;
}


//----------------------------------------------------------------------------
int DragDropStroke::GetLastPickPoint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return NumPoints();
}


//----------------------------------------------------------------------------
void DragDropStroke::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);
   if (ar.IsStoring()){
       m_dwaPoints.Serialize(ar);
       ar << m_nHighlightWidth;
       ar << m_lHighlightColor;
       #pragma TODO("increase the schema number and remove this code.....where can i increase the number??")
       {
       BOOL bPolyBezier=FALSE;
       ar << bPolyBezier;
       }
   }
   else {
       // Loading, different versions of data on disk are possible

       int nVersion = ar.GetObjectSchema();
       switch(nVersion){
       case 3: 
           m_dwaPoints.Serialize(ar);
           m_nHighlightWidth = 0; 
           m_lHighlightColor = RGB(0,0,0);
           break;        
       case 4:
           // read in current version of this object
           m_dwaPoints.Serialize(ar);
           ar >> m_nHighlightWidth;
           ar >> m_lHighlightColor;
           #pragma TODO("increase the schema number and remove this code.....where can i increase the number??")
           {
           BOOL bPolyBezier;
           ar >> bPolyBezier;
           }
           break;        
       default:            
           // schema doesn't match 
			  AfxThrowArchiveException(CArchiveException::badSchema,ar.m_strFileName);
           break;        
      }
    }
}
 

//----------------------------------------------------------------------------
void DragDropStroke::RemoveSegment(int i){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if( (i<0) && (i>NumPoints()-2))
		return;

	RemovePoint(i);   // den linken Punkt loeschen
	RemovePoint(i);   // und den nachgerutschten Punkt auch loeschen
	FinishStroke();
} 
 

//----------------------------------------------------------------------------
void DragDropStroke::StartStroke(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_dwaPoints.RemoveAll();
} 
 

//----------------------------------------------------------------------------/////////////////////////////////////////////////////////////////////////////
void DragDropStroke::FinishStroke(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Calculate the bounding rectangle.  It's needed for smart
   // repainting.
   
   /* SLOW */

   CRect rect;
   rect.SetRectEmpty();
   assert (NumPoints() > 0);
   CPoint point = GetPoint(0);
   rect = CRect(point.x, point.y, point.x, point.y);
   for (int i=1; i < NumPoints(); i++) {
       // If the point lies outside of the accumulated bounding
       // rectangle, then inflate the bounding rect to include it.
       point = GetPoint(i);
       rect.left     = min(rect.left, point.x);
       rect.right    = max(rect.right, point.x);
       rect.top      = max(rect.top, point.y);
       rect.bottom   = min(rect.bottom, point.y);
   }
   // Add the pen width to the bounding rectangle.  This is necessary
   // to account for the width of the stroke when invalidating
   // the screen.
   int nGrow = GetPenWidth();  
   //if (nGrow == 0) nGrow = 1;  // force the rectangle to be a little bigger so
   nGrow = nGrow + 3;            // it doesn't get lost in the noise of Mapping Mode conversions.

   if (m_nHighlightWidth > nGrow) 
      nGrow = m_nHighlightWidth; // use highlight if bigger?

   rect.left   = rect.left  - nGrow;
   rect.right  = rect.right + nGrow;
   rect.top    = rect.top   + nGrow;
   rect.bottom = rect.bottom - nGrow;
    
   m_rectPrevBounding = m_boundingRect;  // save old one
   SetPrevRectValid(TRUE);
   SetBoundingRectForce(rect.left, rect.top, rect.right, rect.bottom);
   SetUpdateNeeded(FALSE);     // False says "do not clear new rectangle on Invalidate
   SetPrevRectValid(FALSE);
}


//----------------------------------------------------------------------------
void DragDropStroke::SetSelected(bool flag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_selected != flag)
   {
      m_selected = flag;
      SetUpdateNeeded(TRUE);  // erase (if getting smaller)
   }
   
}


//----------------------------------------------------------------------------
void DragDropStroke::SetHighlighted(bool flag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_highlighted != flag)
   {
      m_highlighted = flag;
      SetUpdateNeeded(TRUE);  // erase (if getting smaller)
   }
}

//----------------------------------------------------------------------------
void DragDropStroke::SetHighlightWidth(int nWidth){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (nWidth < m_nHighlightWidth) {
        SetUpdateNeeded(TRUE);               // erase (if getting smaller)
    }
    m_nHighlightWidth = nWidth;              // set new width
    if (NumPoints() > 0) 
    {
        FinishStroke();                          // new bounding rect
        SetUpdateNeeded(TRUE);                   // erase and paint again
    }
}

//----------------------------------------------------------------------------
void DragDropStroke::SetHighlightColor(COLORREF rgb){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_lHighlightColor = rgb;
    SetUpdateNeeded(TRUE);                   // erase and paint again
}

