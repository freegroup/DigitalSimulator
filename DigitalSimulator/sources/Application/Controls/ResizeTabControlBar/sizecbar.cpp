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
#include "afxpriv.h"    // for CDockContext
#include "sizecbar.h"
#include "resource.h"
#include "assert.h"
#include "Application\Debug\LogManager.h"



BEGIN_MESSAGE_MAP(CSizingControlBar, CControlBar)
    //{{AFX_MSG_MAP(CSizingControlBar)
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_SETCURSOR()
    ON_WM_WINDOWPOSCHANGED()
    ON_WM_NCPAINT()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_NCHITTEST()
    ON_WM_NCCALCSIZE()
    ON_WM_LBUTTONDOWN()
    ON_WM_CAPTURECHANGED()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
CSizingControlBar::CSizingControlBar(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_sizeMin = CSize(32, 32);
   m_sizeHorz = CSize(200, 200);
   m_sizeVert = CSize(200, 200);
   m_sizeFloat = CSize(200, 200);
   m_bTracking = FALSE;
   m_bInRecalcNC = FALSE;
   m_cxEdge = 6;
}

//----------------------------------------------------------------------------
CSizingControlBar::~CSizingControlBar(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}


//----------------------------------------------------------------------------
void CSizingControlBar::OnUpdateCmdUI(class CFrameWnd *pTarget, int bDisableIfNoHndler){
//----------------------------------------------------------------------------
	PROC_TRACE;

    UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

//----------------------------------------------------------------------------
BOOL CSizingControlBar::Create(CWnd* pParentWnd, CSize sizeDefault, UINT nID, DWORD dwStyle) {
//----------------------------------------------------------------------------
	PROC_TRACE;


   ASSERT_VALID(pParentWnd);   // must have a parent
    ASSERT (!((dwStyle & CBRS_SIZE_FIXED) && (dwStyle & CBRS_SIZE_DYNAMIC)));

    // save the style
    m_dwStyle = dwStyle & CBRS_ALL;

    dwStyle &= ~CBRS_ALL;
    dwStyle |= CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;

    m_sizeHorz = sizeDefault;
    m_sizeVert = sizeDefault;
    m_sizeFloat = sizeDefault;

    CString wndclass = AfxRegisterWndClass(CS_DBLCLKS, LoadCursor(NULL, IDC_ARROW),
        CreateSolidBrush(GetSysColor(COLOR_BTNFACE)), 0);

    if (!CWnd::Create(wndclass, NULL, dwStyle, CRect(0,0,0,0),
        pParentWnd, nID))
        return FALSE;

    return TRUE;
}

//----------------------------------------------------------------------------
CSize CSizingControlBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert (m_pDockSite != NULL);
   assert (m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP) != NULL);

   CRect rc;

    m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP)->GetWindowRect(rc);
    int nHorzDockBarWidth = bStretch ? 32767 : rc.Width() + 4;
    m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT)->GetWindowRect(rc);
    int nVertDockBarHeight = bStretch ? 32767 : rc.Height() + 4;

    if (bHorz)
        return CSize(nHorzDockBarWidth, m_sizeHorz.cy);
    else
        return CSize(m_sizeVert.cx, nVertDockBarHeight);
}

//----------------------------------------------------------------------------
CSize CSizingControlBar::CalcDynamicLayout(int nLength, DWORD dwMode){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (dwMode & (LM_HORZDOCK | LM_VERTDOCK))
        return CControlBar::CalcDynamicLayout(nLength,dwMode);

    if (dwMode & LM_MRUWIDTH)
        return m_sizeFloat;

    if (dwMode & LM_COMMIT)    {
        m_sizeFloat.cx = nLength;
        return m_sizeFloat;
    }

    if (dwMode & LM_LENGTHY)
        return CSize(m_sizeFloat.cx,
            m_sizeFloat.cy = max(m_sizeMin.cy, nLength));
    else
        return CSize(max(m_sizeMin.cx, nLength), m_sizeFloat.cy);
}

//----------------------------------------------------------------------------
void CSizingControlBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    assert(GetParent()!=NULL);

    CControlBar::OnWindowPosChanged(lpwndpos);

    if (m_bInRecalcNC) return;

    // Find on which side are we docked
    UINT nDockBarID = GetParent()->GetDlgCtrlID();

    // Return if dropped at same location
    if (nDockBarID == m_nDockBarID // no docking side change
        && (lpwndpos->flags & SWP_NOSIZE) // no size change
        && ((m_dwStyle & CBRS_BORDER_ANY) != CBRS_BORDER_ANY))
        return; 

    m_nDockBarID = nDockBarID;

    // Force recalc the non-client area
    m_bInRecalcNC = TRUE;
    SetWindowPos(NULL, 0, 0, 0, 0,
        SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER |
        SWP_NOACTIVATE | SWP_FRAMECHANGED);
    m_bInRecalcNC = FALSE;
}

//----------------------------------------------------------------------------
BOOL CSizingControlBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {
//----------------------------------------------------------------------------
	PROC_TRACE;


   if ((nHitTest != HTSIZE) || m_bTracking)
        return CControlBar::OnSetCursor(pWnd, nHitTest, message);

    if (IsHorz())
        SetCursor(LoadCursor(NULL, IDC_SIZENS));
    else
        SetCursor(LoadCursor(NULL, IDC_SIZEWE));
    return TRUE;
}

//----------------------------------------------------------------------------
void CSizingControlBar::OnLButtonUp(UINT nFlags, CPoint point) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (!m_bTracking)
        CControlBar::OnLButtonUp(nFlags, point);
    else {
        ClientToWnd(point);
        StopTracking(TRUE);
    }
}

//----------------------------------------------------------------------------
void CSizingControlBar::OnMouseMove(UINT nFlags, CPoint point) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (IsFloating() || !m_bTracking) {
        CControlBar::OnMouseMove(nFlags, point);
        return;
    }

    CPoint cpt = m_rectTracker.CenterPoint();

    ClientToWnd(point);

    if (IsHorz())    {
        if (cpt.y != point.y){
            OnInvertTracker(m_rectTracker);
            m_rectTracker.OffsetRect(0, point.y - cpt.y);
            OnInvertTracker(m_rectTracker);
        }
    }
    else  {
        if (cpt.x != point.x){
            OnInvertTracker(m_rectTracker);
            m_rectTracker.OffsetRect(point.x - cpt.x, 0);
            OnInvertTracker(m_rectTracker);
        }
    }
}

//----------------------------------------------------------------------------
void CSizingControlBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    assert(lpncsp != NULL);

    // Compute the rectangle of the mobile edge

    GetWindowRect(m_rectBorder);
    m_rectBorder = CRect(0, 0, m_rectBorder.Width(), m_rectBorder.Height());
    
    DWORD dwBorderStyle = m_dwStyle | CBRS_BORDER_ANY;

    switch(m_nDockBarID)    {

    case AFX_IDW_DOCKBAR_TOP:
        dwBorderStyle &= ~CBRS_BORDER_BOTTOM;
        lpncsp->rgrc[0].bottom += -m_cxEdge;
        m_rectBorder.top = m_rectBorder.bottom - m_cxEdge;
        break;
    case AFX_IDW_DOCKBAR_BOTTOM:
        dwBorderStyle &= ~CBRS_BORDER_TOP;
        lpncsp->rgrc[0].top += m_cxEdge;
        m_rectBorder.bottom = m_rectBorder.top + m_cxEdge;
        break;
    case AFX_IDW_DOCKBAR_LEFT:
        dwBorderStyle &= ~CBRS_BORDER_RIGHT;
        lpncsp->rgrc[0].right += -m_cxEdge;
        m_rectBorder.left = m_rectBorder.right - m_cxEdge;
        break;
    case AFX_IDW_DOCKBAR_RIGHT:
        dwBorderStyle &= ~CBRS_BORDER_LEFT;
        lpncsp->rgrc[0].left += m_cxEdge;
        m_rectBorder.right = m_rectBorder.left + m_cxEdge;
        break;
    default:
        m_rectBorder.SetRectEmpty();
        break;
    }

    SetBarStyle(dwBorderStyle);
}

//----------------------------------------------------------------------------
void CSizingControlBar::OnNcPaint() {
//----------------------------------------------------------------------------
	PROC_TRACE;

    EraseNonClient();

//    CDC *windowDC = GetWindowDC();
//    assert (windowDC != NULL);

//    windowDC->Draw3dRect(m_rectBorder, GetSysColor(COLOR_BTNHIGHLIGHT),
//                    GetSysColor(COLOR_BTNSHADOW));
//    ReleaseDC(windowDC);
}

//----------------------------------------------------------------------------
void CSizingControlBar::OnNcLButtonDown(UINT nHitTest, CPoint point) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_bTracking) return;

    if ((nHitTest == HTSIZE) && !IsFloating())
        StartTracking();
    else    
        CControlBar::OnNcLButtonDown(nHitTest, point);
}

//----------------------------------------------------------------------------
UINT CSizingControlBar::OnNcHitTest(CPoint point) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (IsFloating())
        return CControlBar::OnNcHitTest(point);

    CRect rc;
    GetWindowRect(rc);
    point.Offset(-rc.left, -rc.top);
    if (m_rectBorder.PtInRect(point))
        return HTSIZE;
    else
        return CControlBar::OnNcHitTest(point);
}

//----------------------------------------------------------------------------
void CSizingControlBar::OnLButtonDown(UINT nFlags, CPoint point) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    // only start dragging if clicked in "void" space
    if (m_pDockBar != NULL){
        assert(m_pDockContext != NULL);

        // start the drag
        ClientToScreen(&point);
        m_pDockContext->StartDrag(point);
    }
    else {
        CWnd::OnLButtonDown(nFlags, point);
    }
}

//----------------------------------------------------------------------------
void CSizingControlBar::OnLButtonDblClk(UINT nFlags, CPoint point) {
//----------------------------------------------------------------------------
	PROC_TRACE;


   // only toggle docking if clicked in "void" space
    if (m_pDockBar != NULL) {
        assert(m_pDockContext != NULL);
        // toggle docking
        m_pDockContext->ToggleDocking();
    }
    else {
        inherited::OnLButtonDblClk(nFlags, point);
    }
}

//----------------------------------------------------------------------------
void CSizingControlBar::StartTracking(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    SetCapture();

    // make sure no updates are pending
    RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);
    assert ( m_pDockSite != NULL);
    m_pDockSite->LockWindowUpdate();

    m_ptOld = m_rectBorder.CenterPoint();
    m_bTracking = TRUE;
    
    m_rectTracker = m_rectBorder;
    if (!IsHorz()) m_rectTracker.bottom -= 4;

    OnInvertTracker(m_rectTracker);
}

//----------------------------------------------------------------------------
void CSizingControlBar::OnCaptureChanged(CWnd *pWnd) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_bTracking && pWnd != this)
        StopTracking(FALSE); // cancel tracking

    CControlBar::OnCaptureChanged(pWnd);
}

//----------------------------------------------------------------------------
void CSizingControlBar::StopTracking(BOOL bAccept){
//----------------------------------------------------------------------------
	PROC_TRACE;

    OnInvertTracker(m_rectTracker);
    assert ( m_pDockSite != NULL);

    m_pDockSite->UnlockWindowUpdate();
    m_bTracking = FALSE;
    ReleaseCapture();
    
    if (!bAccept) return;

    int maxsize, minsize, newsize;
    CRect rcc;
    m_pDockSite->GetClientRect(rcc);

    newsize = IsHorz() ? m_sizeHorz.cy : m_sizeVert.cx;
    maxsize = newsize + (IsHorz() ? rcc.Height() : rcc.Width());
    minsize = IsHorz() ? m_sizeMin.cy : m_sizeMin.cx;

    CPoint point = m_rectTracker.CenterPoint();
    switch (m_nDockBarID)
    {
    case AFX_IDW_DOCKBAR_TOP:
        newsize += point.y - m_ptOld.y; break;
    case AFX_IDW_DOCKBAR_BOTTOM:
        newsize += -point.y + m_ptOld.y; break;
    case AFX_IDW_DOCKBAR_LEFT:
        newsize += point.x - m_ptOld.x; break;
    case AFX_IDW_DOCKBAR_RIGHT:
        newsize += -point.x + m_ptOld.x; break;
    }

    newsize = max(minsize, min(maxsize, newsize));

    if (IsHorz())
        m_sizeHorz.cy = newsize;
    else
        m_sizeVert.cx = newsize;

    m_pDockSite->DelayRecalcLayout();
}

//----------------------------------------------------------------------------
void CSizingControlBar::OnInvertTracker(const CRect& rect){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT_VALID(this);
    assert(!rect.IsRectEmpty());
    assert(m_bTracking);
    assert(m_pDockSite != NULL);

    CRect rct = rect, rcc, rcf;
    GetWindowRect(rcc);
    m_pDockSite->GetWindowRect(rcf);

    rct.OffsetRect(rcc.left - rcf.left, rcc.top - rcf.top);
    rct.DeflateRect(1, 1);

    CDC *pDC = m_pDockSite->GetDCEx(NULL,
        DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);

    CBrush* pBrush = CDC::GetHalftoneBrush();
    HBRUSH hOldBrush = NULL;
    if (pBrush != NULL)
        hOldBrush = (HBRUSH)SelectObject(pDC->m_hDC, pBrush->m_hObject);

    pDC->PatBlt(rct.left, rct.top, rct.Width(), rct.Height(), PATINVERT);

    if (hOldBrush != NULL)
        SelectObject(pDC->m_hDC, hOldBrush);

    m_pDockSite->ReleaseDC(pDC);
}

//----------------------------------------------------------------------------
BOOL CSizingControlBar::IsHorz() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return (m_nDockBarID == AFX_IDW_DOCKBAR_TOP ||m_nDockBarID == AFX_IDW_DOCKBAR_BOTTOM);
}

//----------------------------------------------------------------------------
CPoint& CSizingControlBar::ClientToWnd(CPoint& point){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_nDockBarID == AFX_IDW_DOCKBAR_BOTTOM)
        point.y += m_cxEdge;
    else if (m_nDockBarID == AFX_IDW_DOCKBAR_RIGHT)
        point.x += m_cxEdge;

    return point;
}
