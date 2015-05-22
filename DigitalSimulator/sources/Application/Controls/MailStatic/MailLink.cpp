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
#include "MailLink.h"
#include "imapi.h"

#define TOOLTIP_ID 1

BEGIN_MESSAGE_MAP(CMailLink, CStatic)
    //{{AFX_MSG_MAP(CMailLink)
    ON_CONTROL_REFLECT(STN_CLICKED, OnClicked)
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_SETCURSOR()
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
CMailLink::CMailLink(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_hLinkCursor       = NULL;                 // No cursor as yet
    m_crLinkColour      = RGB(  0,   0, 238);   // Blue
    m_crVisitedColour   = RGB( 85,  26, 139);   // Purple
    m_crHoverColour     = ::GetSysColor(COLOR_HIGHLIGHT);
    m_bOverControl      = FALSE;                // Cursor not yet over control
    m_bVisited          = FALSE;                // Hasn't been visited yet.
    m_bUnderline        = TRUE;                 // Underline the link?
    m_bAdjustToFit      = TRUE;                 // Resize the window to fit the text?
    m_receiver.Empty();
    m_subject.Empty();
    m_body.Empty();
}

//----------------------------------------------------------------------------
CMailLink::~CMailLink(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_Font.DeleteObject();

   if (m_hLinkCursor != NULL) {
       ::DestroyCursor(m_hLinkCursor);
       m_hLinkCursor = NULL;
   }
}


//----------------------------------------------------------------------------
BOOL CMailLink::PretranslateMessage(MSG* pMsg) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}

//----------------------------------------------------------------------------
void CMailLink::OnClicked(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CIMapi mail;
   CString subject;

   if(m_subjectPrefix != "")
        subject= m_subjectPrefix + ": " + m_subject;
   else
        subject= m_subject;

   mail.Subject(subject);
   mail.To(m_receiver);

   if(!mail.Send()){
       AfxMessageBox("Mail konnte nicht gesendet werden", MB_ICONEXCLAMATION | MB_OK);
   }

   SetVisited();                        // Repaint to show visited colour
}

//----------------------------------------------------------------------------
HBRUSH CMailLink::CtlColor(CDC* pDC, UINT nCtlColor) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(nCtlColor == CTLCOLOR_STATIC);

    if (m_bOverControl)
        pDC->SetTextColor(m_crHoverColour);
    else if (m_bVisited)
        pDC->SetTextColor(m_crVisitedColour);
    else
        pDC->SetTextColor(m_crLinkColour);

    // transparent text.
    pDC->SetBkMode(TRANSPARENT);
    return (HBRUSH)GetStockObject(NULL_BRUSH);
}

//----------------------------------------------------------------------------
void CMailLink::OnMouseMove(UINT nFlags, CPoint point) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    CStatic::OnMouseMove(nFlags, point);

    if (m_bOverControl)        // Cursor is currently over control
    {
        CRect rect;
        GetClientRect(rect);

        if (!rect.PtInRect(point))
        {
            m_bOverControl = FALSE;
            ReleaseCapture();
            RedrawWindow();
            return;
        }
    }
    else                      // Cursor has just moved over control
    {
        m_bOverControl = TRUE;
        RedrawWindow();
        SetCapture();
    }
}

//----------------------------------------------------------------------------
BOOL CMailLink::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_hLinkCursor)
    {
        ::SetCursor(m_hLinkCursor);
        return TRUE;
    }
    return FALSE;
}

//----------------------------------------------------------------------------
void CMailLink::PreSubclassWindow() {
//----------------------------------------------------------------------------
	PROC_TRACE;

    // We want to get mouse clicks via STN_CLICKED
    DWORD dwStyle = GetStyle();
    ::SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);
    
    // Set the subject as the window text
    if (m_subject.IsEmpty())
        GetWindowText(m_subject);

    // Check that the window text isn't empty. If it is, set it as the URL.
    CString strWndText;
    GetWindowText(strWndText);
    if (strWndText.IsEmpty()) {
        ASSERT(!m_subject.IsEmpty());    // Window and URL both NULL. DUH!
        SetWindowText(m_subject);
    }

    // Create the font
    LOGFONT lf;
    GetFont()->GetLogFont(&lf);
    lf.lfUnderline = m_bUnderline;
    m_Font.CreateFontIndirect(&lf);
    SetFont(&m_Font);

    PositionWindow();        // Adjust size of window to fit URL if necessary
    SetDefaultCursor();      // Try and load up a "hand" cursor

    // Create the tooltip
    CRect rect; 
    GetClientRect(rect);
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(this, m_subject, rect, TOOLTIP_ID);

    CStatic::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CMailLink operations

//----------------------------------------------------------------------------
void CMailLink::SetReceiver(CString receiver){
//----------------------------------------------------------------------------
	PROC_TRACE;


    m_receiver = receiver;
    PositionWindow();
}


//----------------------------------------------------------------------------
void CMailLink::SetSubject(CString subject){
//----------------------------------------------------------------------------
	PROC_TRACE;


    m_subject = subject;
    PositionWindow();
}

//----------------------------------------------------------------------------
void CMailLink::SetSubjectPrefix(CString prefix){
//----------------------------------------------------------------------------
	PROC_TRACE;


    m_subjectPrefix = prefix;
}


//----------------------------------------------------------------------------
void CMailLink::SetBody(CString body){
//----------------------------------------------------------------------------
	PROC_TRACE;


    m_body = body;
    PositionWindow();
}


//----------------------------------------------------------------------------
void CMailLink::SetColours(COLORREF crLinkColour, COLORREF crVisitedColour, COLORREF crHoverColour /* = -1 */) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_crLinkColour    = crLinkColour; 
    m_crVisitedColour = crVisitedColour;

	if (crHoverColour == -1)
		m_crHoverColour = ::GetSysColor(COLOR_HIGHLIGHT);
	else
		m_crHoverColour = crHoverColour;

    if (::IsWindow(m_hWnd))
        Invalidate(); 
}

//----------------------------------------------------------------------------
COLORREF CMailLink::GetLinkColour() const{ 
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_crLinkColour; 
}

//----------------------------------------------------------------------------
COLORREF CMailLink::GetVisitedColour() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_crVisitedColour; 
}

//----------------------------------------------------------------------------
COLORREF CMailLink::GetHoverColour() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_crHoverColour;
}

//----------------------------------------------------------------------------
void CMailLink::SetVisited(BOOL bVisited /* = TRUE */) { 
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_bVisited = bVisited; 

    if (::IsWindow(GetSafeHwnd()))
        Invalidate(); 
}

//----------------------------------------------------------------------------
BOOL CMailLink::GetVisited() const{ 
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_bVisited; 
}

//----------------------------------------------------------------------------
void CMailLink::SetLinkCursor(HCURSOR hCursor){ 
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_hLinkCursor = hCursor;
    if (m_hLinkCursor == NULL)
        SetDefaultCursor();
}

//----------------------------------------------------------------------------
HCURSOR CMailLink::GetLinkCursor() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_hLinkCursor;
}

//----------------------------------------------------------------------------
void CMailLink::SetUnderline(BOOL bUnderline /* = TRUE */){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_bUnderline = bUnderline;

    if (::IsWindow(GetSafeHwnd()))
    {
        LOGFONT lf;
        GetFont()->GetLogFont(&lf);
        lf.lfUnderline = m_bUnderline;

        m_Font.DeleteObject();
        m_Font.CreateFontIndirect(&lf);
        SetFont(&m_Font);

        Invalidate(); 
    }
}

//----------------------------------------------------------------------------
BOOL CMailLink::GetUnderline() const{ 
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_bUnderline; 
}

//----------------------------------------------------------------------------
void CMailLink::SetAutoSize(BOOL bAutoSize /* = TRUE */){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_bAdjustToFit = bAutoSize;

    if (::IsWindow(GetSafeHwnd()))
        PositionWindow();
}

//----------------------------------------------------------------------------
BOOL CMailLink::GetAutoSize() const{ 
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_bAdjustToFit; 
}


// Move and resize the window so that the window is the same size
// as the hyperlink text. This stops the hyperlink cursor being active
// when it is not directly over the text. If the text is left justified
// then the window is merely shrunk, but if it is centred or right
// justified then the window will have to be moved as well.
//
// Suggested by Pål K. Tønder 

//----------------------------------------------------------------------------
void CMailLink::PositionWindow(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (!::IsWindow(GetSafeHwnd()) || !m_bAdjustToFit) 
        return;

    // Get the current window position
    CRect rect;
    GetWindowRect(rect);

    CWnd* pParent = GetParent();
    if (pParent)
        pParent->ScreenToClient(rect);

    // Get the size of the window text
    CString strWndText;
    GetWindowText(strWndText);

    CDC* pDC = GetDC();
    CFont* pOldFont = pDC->SelectObject(&m_Font);
    CSize Extent = pDC->GetTextExtent(strWndText);
    pDC->SelectObject(pOldFont);
    ReleaseDC(pDC);

    // Get the text justification via the window style
    DWORD dwStyle = GetStyle();

    // Recalc the window size and position based on the text justification
    if (dwStyle & SS_CENTERIMAGE)
        rect.DeflateRect(0, (rect.Height() - Extent.cy)/2);
    else
        rect.bottom = rect.top + Extent.cy;

    if (dwStyle & SS_CENTER)   
        rect.DeflateRect((rect.Width() - Extent.cx)/2, 0);
    else if (dwStyle & SS_RIGHT) 
        rect.left  = rect.right - Extent.cx;
    else // SS_LEFT = 0, so we can't test for it explicitly 
        rect.right = rect.left + Extent.cx;

    // Move the window
    SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
}

/////////////////////////////////////////////////////////////////////////////
// CMailLink implementation

// The following appeared in Paul DiLascia's Jan 1998 MSJ articles.
// It loads a "hand" cursor from the winhlp32.exe module
//----------------------------------------------------------------------------
void CMailLink::SetDefaultCursor(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_hLinkCursor == NULL)                // No cursor handle - load our own
    {
        // Get the windows directory
        CString strWndDir;
        GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
        strWndDir.ReleaseBuffer();

        strWndDir += _T("\\winhlp32.exe");
        // This retrieves cursor #106 from winhlp32.exe, which is a hand pointer
        HMODULE hModule = LoadLibrary(strWndDir);
        if (hModule) {
            HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
            if (hHandCursor)
                m_hLinkCursor = CopyCursor(hHandCursor);
        }
        FreeLibrary(hModule);
    }
}

