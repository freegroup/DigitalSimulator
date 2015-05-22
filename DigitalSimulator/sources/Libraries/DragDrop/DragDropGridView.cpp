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
#include "DragDropGridView.h"  
#include "DragDropHandle.h"  

IMPLEMENT_DYNCREATE(DragDropGridView, DragDropView)

BEGIN_MESSAGE_MAP(DragDropGridView, DragDropView)
    //{{AFX_MSG_MAP(DragDropGridView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
DragDropGridView::DragDropGridView(){
//----------------------------------------------------------------------------
	PROC_TRACE;


   int nUnit = Metrics::getPixelsPerUnit();
   int nScale = nUnit/100;

   m_pointGridOrigin = DragDropGridOrigin;
   m_nGridWidthLoMM  = DragDropGridWidth  * nScale;
   m_nGridHeightLoMM = DragDropGridHeight * nScale;
   m_nGridSkewLoMM   = DragDropGridSkew;
   m_GridStyle       = GridInvisible;
   m_nObjectSpot     = DragDropGridObjectSpot;
   m_snapMove        = NoSnap;     
   m_snapResize      = NoSnap;
   m_pStartPoints    = NULL;     
   m_gridColor       = RGB(0,0,0);
}

//----------------------------------------------------------------------------
DragDropGridView::~DragDropGridView(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}    

//----------------------------------------------------------------------------
void DragDropGridView::SetGridOrigin(CPoint pointOrigin){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_pointGridOrigin != pointOrigin){
       m_pointGridOrigin = pointOrigin; 
       Invalidate(TRUE);
   }
}

//----------------------------------------------------------------------------
CPoint DragDropGridView::GetGridOrigin() const {
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pointGridOrigin;
}


//----------------------------------------------------------------------------
void DragDropGridView::SetGridWidth(int nWidth){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_nGridWidthLoMM != nWidth){
      m_nGridWidthLoMM = nWidth; 
      Invalidate(TRUE);
   }
}

//----------------------------------------------------------------------------
int DragDropGridView::GetGridWidth() const {
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_nGridWidthLoMM;
}


//----------------------------------------------------------------------------
void DragDropGridView::SetGridHeight(int nHeight){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_nGridHeightLoMM != nHeight){
      m_nGridHeightLoMM = nHeight; 
      Invalidate(TRUE);
   }
}

//----------------------------------------------------------------------------
int DragDropGridView::GetGridHeight() const {
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_nGridHeightLoMM;
}


//----------------------------------------------------------------------------
void DragDropGridView::SetGridSkew(int nHeight){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_nGridSkewLoMM != nHeight){
        m_nGridSkewLoMM = nHeight; 
        Invalidate(TRUE);
    }
}

//----------------------------------------------------------------------------
int DragDropGridView::GetGridSkew() const {
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_nGridSkewLoMM;
}


//----------------------------------------------------------------------------
CPoint DragDropGridView::GetGridLocation(int nRow, int nCol){
//----------------------------------------------------------------------------
	PROC_TRACE;

    int nColSkew = 0;
    if ((nCol & 1) == 1) 
       nColSkew = m_nGridSkewLoMM;

    int x = m_pointGridOrigin.x + nCol*m_nGridWidthLoMM;
    int y = m_pointGridOrigin.y + nColSkew - nRow*m_nGridHeightLoMM;

    return (CPoint(x,y));
}

//----------------------------------------------------------------------------
void DragDropGridView::SetGridStyle(GridStyle styleCode){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_GridStyle != styleCode) {
        m_GridStyle = styleCode; 
        Invalidate(TRUE);
    }
}

//----------------------------------------------------------------------------
DragDropGridView::GridStyle DragDropGridView::GetGridStyle() const {
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_GridStyle;
}


//----------------------------------------------------------------------------
void DragDropGridView::SetObjectSpot(DragDropObject::SpotNumber nSpot){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_nObjectSpot != nSpot){
      m_nObjectSpot = nSpot; 
   }
}

//----------------------------------------------------------------------------
DragDropObject::SpotNumber DragDropGridView::GetObjectSpot() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_nObjectSpot;
}

//----------------------------------------------------------------------------
void DragDropGridView::SetSnapMove(AutoSnap snapCode){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_snapMove != snapCode){
      m_snapMove = snapCode; 
   }
}

//----------------------------------------------------------------------------
DragDropGridView::AutoSnap DragDropGridView::GetSnapMove() const {
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_snapMove;
}


//----------------------------------------------------------------------------
void DragDropGridView::SetSnapResize(AutoSnap snapCode){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_snapResize != snapCode){
      m_snapResize = snapCode; 
   }
}

//----------------------------------------------------------------------------
DragDropGridView::AutoSnap DragDropGridView::GetSnapResize() const {
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_snapResize;
}

//----------------------------------------------------------------------------
void DragDropGridView::SnapObject(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SnapObject(pObject, m_nObjectSpot);
}

//----------------------------------------------------------------------------
void DragDropGridView::SnapObject(DragDropObject* pObject, DragDropObject::SpotNumber nSpot){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CPoint pointNearest = CalcNearestGridPosition(pObject->GetSpotLocation(nSpot));
   pObject->SetSpotLocation(nSpot, pointNearest);
}

//----------------------------------------------------------------------------
void DragDropGridView::SnapAllObjects(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SnapAllObjects(m_nObjectSpot);
}

//----------------------------------------------------------------------------
void DragDropGridView::SnapAllObjects(DragDropObject::SpotNumber nSpot){
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropDocument* pDocument = GetDocument();

   for (POSITION pos = pDocument->GetFirstObjectPos(); pos != NULL; )  {
        DragDropObject* pObject = pDocument->GetNextObjectAtTop(pos);
        // Handles are not realy a part of the object
        //
        if (pObject->IsKindOf(RUNTIME_CLASS(DragDropHandle))) 
           continue;
        SnapObject(pObject, nSpot);
    }   
}

//----------------------------------------------------------------------------
void DragDropGridView::DoDrawBackgroundDecoration(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

    inherited::DoDrawBackgroundDecoration(pDC);

    
    int nUnit = Metrics::getPixelsPerUnit(); 
    int nScale = nUnit/100;

    switch (m_GridStyle) {
        case GridDot:
            DrawGridPoints(3*nScale, pDC);
            break;
        case GridCross:
            DrawGridPoints(8*nScale, pDC);
            break;
        case GridLine:
//            if (m_nGridSkewLoMM == 0)
                DrawGridLines(pDC);
//            else
//                DrawGridPoints(15*nScale, pDC);
            break;
    }
}


//----------------------------------------------------------------------------
BOOL DragDropGridView::DrawGridPoints(int nRadius, CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropDocument* pDocument = GetDocument();

    // Get the invalidated rectangle of the view 
    // or the clipping region of the printer DC.

    CRect rectClip;
    pDC->GetClipBox(&rectClip);

    CPen penSolidBlack;

    penSolidBlack.CreatePen(PS_SOLID, 1,m_gridColor);

    CPen* pOldPen = pDC->SelectObject(&penSolidBlack);
    
    // Draw all grid points, row by row.
    
    int     nOriginX = m_pointGridOrigin.x;
    int     nOriginY = m_pointGridOrigin.y;
    CSize   sizeDoc = pDocument->GetDocumentSize();
    
    for (int nCol=0; (nOriginX + nCol*m_nGridWidthLoMM) < sizeDoc.cx; nCol++) {
        int nColSkew = 0;
        if ((nCol & 1) == 1) nColSkew = m_nGridSkewLoMM;

        for (int nRow = 0; (nOriginY + nColSkew - nRow*m_nGridHeightLoMM) > -sizeDoc.cy; nRow++){
            // Calculate the coordinates of the grid point rectangle.

            int nCrossLeft = nOriginX + nCol*m_nGridWidthLoMM - nRadius;
            int nCrossRight = nOriginX + nCol*m_nGridWidthLoMM + nRadius;
            int nCrossTop = nOriginY + nColSkew - nRow*m_nGridHeightLoMM + nRadius;
            int nCrossBottom = nOriginY + nColSkew - nRow*m_nGridHeightLoMM - nRadius;

            // Skip grid points that are outside the clipping rectangle.

            if (nCrossTop < rectClip.bottom) continue;
            if (nCrossBottom > rectClip.top) continue;
            if (nCrossLeft > rectClip.right) continue;
            if (nCrossRight < rectClip.left) continue;
            
            // Draw the vertical stroke ("|").

            pDC->MoveTo((nOriginX + nCol*m_nGridWidthLoMM), nCrossTop);
            pDC->LineTo((nOriginX + nCol*m_nGridWidthLoMM), nCrossBottom);
            
            // Draw the horizontal stroke ("-").

            pDC->MoveTo(nCrossLeft, (nOriginY + nColSkew - nRow*m_nGridHeightLoMM));
            pDC->LineTo(nCrossRight, (nOriginY + nColSkew - nRow*m_nGridHeightLoMM));
        }
    }

    
    if (pOldPen) 
       pDC->SelectObject(pOldPen);
        
    return TRUE;
}


//----------------------------------------------------------------------------
BOOL DragDropGridView::DrawGridLines(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropDocument* pDocument = GetDocument();

    CRect rectClip;
    CPen  pen;
    pDC->GetClipBox(&rectClip);

    pen.CreatePen(PS_SOLID, 1,m_gridColor);
  
    CPen* pOldPen = pDC->SelectObject(&pen);
    COLORREF oldColor = pDC->SetBkColor(pDocument->GetPaperColor() );

    int     nOriginX = m_pointGridOrigin.x;
    int     nOriginY = m_pointGridOrigin.y;
    CSize   sizeDoc  = pDocument->GetDocumentSize();

    // Draw vertical lines, limited by the clipping rectangle.
    
    for (int nCol=0; (nOriginX + nCol*m_nGridWidthLoMM) < sizeDoc.cx; nCol++) {
        if ((nOriginX + nCol*m_nGridWidthLoMM) < rectClip.left) 
           continue;
        if ((nOriginX + nCol*m_nGridWidthLoMM) > rectClip.right) 
           break;

        pDC->MoveTo((nOriginX + nCol*m_nGridWidthLoMM), __min(nOriginY, rectClip.top));
        pDC->LineTo((nOriginX + nCol*m_nGridWidthLoMM), __max(-sizeDoc.cy, rectClip.bottom));
    }
    
    // Draw horizontal lines, limited by the clipping rectangle.

    for (int nRow = 0; (nOriginY - nRow*m_nGridHeightLoMM) > -sizeDoc.cy; nRow++) {
        if ((nOriginY - nRow*m_nGridHeightLoMM) > rectClip.top) 
           continue;
        if ((nOriginY - nRow*m_nGridHeightLoMM) < rectClip.bottom) 
           break;
        
        pDC->MoveTo(__max(nOriginX, rectClip.left), (nOriginY - nRow*m_nGridHeightLoMM));
        pDC->LineTo(__min(sizeDoc.cx, rectClip.right), (nOriginY - nRow*m_nGridHeightLoMM));
    }

    // Restore the previous pen.
    
    if (pOldPen) 
       pDC->SelectObject(pOldPen);

    pDC->SetBkColor(oldColor);   
    return TRUE;
}


//----------------------------------------------------------------------------
void DragDropGridView::MoveSelection(CSize sizeOffset, CPoint pointLP, int nEvent){
//----------------------------------------------------------------------------
	PROC_TRACE;

   BOOL bSnapJump     = (nEvent == WM_MOUSEMOVE) && (m_snapMove == SnapJump);
    BOOL bSnapJumpDone = (nEvent == WM_LBUTTONUP) && (m_snapMove == SnapJump);
    BOOL bSaveJumpStart;
    BOOL bSnapAfter    = (nEvent == WM_LBUTTONUP) && (m_snapMove != NoSnap);
    
    // SnapJump Initialization
    
    if (bSnapJump)
       if (bSaveJumpStart = (m_pStartPoints == NULL))
            m_pStartPoints = new POINT[m_pSelection->GetSelectedCount()];
    
    // Move the selected objects, one at a time.    

    POSITION pos = m_pSelection->GetFirstSelectedPos();

    for (int obj = 0; pos != NULL; obj++) {
        DragDropObject* pObject = m_pSelection->GetNextSelected(pos);

        if (pObject->IsDraggable()){
            if (!bSnapJump){
                pObject->SetLocationOffset(pObject->GetTopLeft(), sizeOffset);
                if (bSnapAfter) 
                   SnapObject(pObject);
            }
            else {
                CPoint  pointBefore = pObject->GetSpotLocation(m_nObjectSpot);
                if (bSaveJumpStart){
                    m_pStartPoints[obj].x = pointBefore.x;
                    m_pStartPoints[obj].y = pointBefore.y;
                }
                CSize   sizeTotalOffset = pointLP - m_pointMouseDown;
                CPoint  pointSpotOffset(m_pStartPoints[obj].x + sizeTotalOffset.cx,
                                        m_pStartPoints[obj].y + sizeTotalOffset.cy);
                CPoint  pointAfter = CalcNearestGridPosition(pointSpotOffset);
                if (pointAfter != pointBefore)
                    pObject->SetSpotLocation(m_nObjectSpot, pointAfter);
            }            
        }
    }    
    if (bSnapJumpDone) {
        delete m_pStartPoints;
        m_pStartPoints = NULL;
    }
}

//----------------------------------------------------------------------------
void DragDropGridView::CancelMoveSelection(){
//----------------------------------------------------------------------------
	PROC_TRACE;
    
    if (m_snapMove == SnapJump) {
        delete m_pStartPoints;
        m_pStartPoints = NULL;
    }
}


//----------------------------------------------------------------------------
void DragDropGridView::HandleResizing(CClientDC* pDC, CPoint pPoint, int nEvent){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   if ((m_pCurrentObject == NULL) || (!m_pCurrentObject->IsResizable()))
    return;

   if (((nEvent == WM_MOUSEMOVE) && (m_snapResize == SnapJump)) ||
     ((nEvent == WM_LBUTTONUP) && (m_snapResize != NoSnap)))
   {
      switch (m_handlesHit){
         case TopLeft:
         case TopRight:
         case BottomLeft:
         case BottomRight:
             SnapPointHorizontal(pPoint);
             SnapPointVertical(pPoint);
             break;
         case TopMiddle:
         case BottomMiddle:
             SnapPointVertical(pPoint);
             break;
         case SideLeft:
         case SideRight:
             SnapPointHorizontal(pPoint);
             break;
      }
   }
   inherited::HandleResizing(pDC, pPoint, nEvent);
}

//----------------------------------------------------------------------------
CPoint DragDropGridView::CalcNearestGridPosition(CPoint pointSpot){
//----------------------------------------------------------------------------
	PROC_TRACE;

   UINT nRow, nColumn;
    
    return CalcNearestGridPosition(pointSpot, nRow, nColumn);
}

//----------------------------------------------------------------------------
CPoint DragDropGridView::CalcNearestGridPosition(CPoint pointSpot, UINT& rnRow, UINT& rnColumn){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Determine the four nearest grid points:
    //
    //    A +
    //              + C
    //
    //           *            "*" is the Object Spot
    //    B +
    //              + D
    
    UINT nColAB, nColCD, nRowA, nRowB, nRowC, nRowD;
    
    CalcNearestColumns(pointSpot, nColAB, nColCD);
    CalcNearestRows(pointSpot, nColAB, nRowA, nRowB);
    CalcNearestRows(pointSpot, nColCD, nRowC, nRowD);
    
    // Use the Pythagorean Theorem to pick the nearest point.
    
    int nABx = m_pointGridOrigin.x + ((int)nColAB * m_nGridWidthLoMM);
    int nAy  = m_pointGridOrigin.y + (((int)nColAB & 1) * m_nGridSkewLoMM) - ((int)nRowA * m_nGridHeightLoMM);
    int nBy  = m_pointGridOrigin.y + (((int)nColAB & 1) * m_nGridSkewLoMM) - ((int)nRowB * m_nGridHeightLoMM);
    int nCDx = m_pointGridOrigin.x + ((int)nColCD * m_nGridWidthLoMM);
    int nCy  = m_pointGridOrigin.y + (((int)nColCD & 1) * m_nGridSkewLoMM) - ((int)nRowC * m_nGridHeightLoMM);
    int nDy  = m_pointGridOrigin.y + (((int)nColCD & 1) * m_nGridSkewLoMM) - ((int)nRowD * m_nGridHeightLoMM);
    
    float fABcx    = (float)pointSpot.x - (float)nABx;     // Convert to float before multiplication.
    float fAcy     = -(float)pointSpot.y - (-(float)nAy);
    float fSpotToA = fABcx * fABcx + fAcy * fAcy;
    float fBcy     = -(float)nBy - (-(float)pointSpot.y);
    float fSpotToB = fABcx * fABcx + fBcy * fBcy;
    float fCDcx    = (float)nCDx - (float)pointSpot.x;
    float fCcy     = -(float)pointSpot.y - (-(float)nCy);
    float fSpotToC = fCDcx * fCDcx + fCcy * fCcy;
    float fDcy     = -(float)nDy - (-(float)pointSpot.y);
    float fSpotToD = fCDcx * fCDcx + fDcy * fDcy;
    
    float nShortest = __min(fSpotToA, __min(fSpotToB, __min(fSpotToC, fSpotToD)));
   
    CPoint pointNearest;
    
    if (fSpotToA == nShortest){
        rnRow = nRowA;
        rnColumn = nColAB;
        pointNearest.x = nABx;
        pointNearest.y = nAy;
    }
    else{
        if (fSpotToB == nShortest){
            rnRow = nRowB;
            rnColumn = nColAB;
            pointNearest.x = nABx;
            pointNearest.y = nBy;
        }
        else {
            if (fSpotToC == nShortest){
                rnRow = nRowC;
                rnColumn = nColCD;
                pointNearest.x = nCDx;
                pointNearest.y = nCy;
            }
            else{
                rnRow = nRowD;
                rnColumn = nColCD;
                pointNearest.x = nCDx;
                pointNearest.y = nDy;
            }
        }
    }
    return (pointNearest);    
}


//----------------------------------------------------------------------------    
void DragDropGridView::CalcNearestColumns(CPoint pointSpot, UINT& rnLeftColumn, UINT& rnRightColumn){
//----------------------------------------------------------------------------
	PROC_TRACE;

   int nColumn = (pointSpot.x - m_pointGridOrigin.x) / m_nGridWidthLoMM;
    
    if (nColumn < 0){
        rnLeftColumn = 0;
        rnRightColumn = 0;
    }
    else {
        rnLeftColumn = nColumn;
        rnRightColumn = nColumn + 1;
    }
}

//----------------------------------------------------------------------------
void DragDropGridView::CalcNearestRows(CPoint pointSpot, UINT nColumn, UINT& rnUpperRow, UINT& rnLowerRow){
//----------------------------------------------------------------------------
	PROC_TRACE;

   int nSkew = (int)(nColumn & 1) * m_nGridSkewLoMM;
   int nRow  = (m_pointGridOrigin.y + nSkew - pointSpot.y) / m_nGridHeightLoMM;
    
   if (nRow <= 0){
       rnUpperRow = 0;
       rnLowerRow = 0;
   }
   else{
       rnUpperRow = nRow;
       rnLowerRow = nRow + 1;
   }
}

//----------------------------------------------------------------------------
void DragDropGridView::SnapPointHorizontal(CPoint& pPoint){
//----------------------------------------------------------------------------
	PROC_TRACE;

   UINT nLeftColumn, nRightColumn;
    
    CalcNearestColumns(pPoint, nLeftColumn, nRightColumn);

    int nLeftx  = m_pointGridOrigin.x + (nLeftColumn * m_nGridWidthLoMM);
    int nRightx = m_pointGridOrigin.x + (nRightColumn * m_nGridWidthLoMM);
    
    if (abs(pPoint.x - nLeftx) < abs(pPoint.x - nRightx))
        pPoint.x = nLeftx;
    else    
        pPoint.x = nRightx;
}

//----------------------------------------------------------------------------
void DragDropGridView::SnapPointVertical(CPoint& pPoint){
//----------------------------------------------------------------------------
	PROC_TRACE;

   UINT nUpperRow, nLowerRow;
    
    CalcNearestRows(pPoint, 0, nUpperRow, nLowerRow);

    int nUppery = m_pointGridOrigin.y - (nUpperRow * m_nGridHeightLoMM);
    int nLowery = m_pointGridOrigin.y - (nLowerRow * m_nGridHeightLoMM);
    
    if (abs(pPoint.y - nUppery) < abs(pPoint.y - nLowery))
        pPoint.y = nUppery;
    else    
        pPoint.y = nLowery;
}
