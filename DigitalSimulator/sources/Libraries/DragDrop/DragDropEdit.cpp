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
#include "DragDropview.h"

#include "DragDropedit.h"
#include "DragDroptext.h"

IMPLEMENT_DYNCREATE(DragDropTextEdit, CEdit)

BEGIN_MESSAGE_MAP(DragDropTextEdit, CEdit)
    //{{AFX_MSG_MAP(DragDropTextEdit)
    //}}AFX_MSG_MAP
    ON_WM_CHAR()
    ON_WM_PAINT()
    ON_WM_SETFOCUS()
END_MESSAGE_MAP()


//----------------------------------------------------------------------------//----------------------------------------------------------------------------
DragDropTextEdit::DragDropTextEdit(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DragDropTextEdit::DragDropTextEdit(const CString& pString, BOOL bAlwaysFit, DragDropText* textObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

    assert(textObject);

    m_bAlwaysFitExactly = bAlwaysFit;
    m_textObject        = textObject;
    m_strInitial        = pString;
    m_pFont             = NULL;
    m_lLastKey          = 0;
}

//----------------------------------------------------------------------------
DragDropTextEdit::~DragDropTextEdit(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_lLastKey == VK_ESCAPE)
       return;

    if(m_textObject && m_hWnd){
       CString string;
       GetWindowText(string);
       m_textObject->SetString(string);
    }

}

//----------------------------------------------------------------------------
BOOL DragDropTextEdit::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CFont* pFont, CPoint cursorSP){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // cursorSP is the mouse cursor in screen points
    m_ptCursorSP = cursorSP;
    
    m_ptUpperLeftDP.x = rect.left;
    m_ptUpperLeftDP.y = rect.top;
    
    m_dwStyle = dwStyle; 
    
    
    m_bMultiline = FALSE;
    if (dwStyle & ES_MULTILINE) m_bMultiline = TRUE;
    dwStyle = dwStyle | ES_MULTILINE;   
    
    m_nAlign = TextTopLeft;
    if (dwStyle & ES_CENTER) m_nAlign = TextTopMiddle;
    if (dwStyle & ES_RIGHT)  m_nAlign = TextTopRight;
    m_ptOriginDP.y = m_ptUpperLeftDP.y;
    switch (m_nAlign)
    {
    case TextTopLeft:
        m_ptOriginDP.x = m_ptUpperLeftDP.x;
        break;
    case TextTopMiddle:
        m_ptOriginDP.x = m_ptUpperLeftDP.x + ((rect.right - rect.left)/2);  // original centerPoint
        break;
    case TextTopRight:
        m_ptOriginDP.x = rect.right;      // original rightPoint
        break;              
    } // end switch
    
    BOOL status = CEdit::Create (dwStyle, rect, pParentWnd, nID);
    if (!status) TRACE0("DragDropTextEdit: Error in Creation\n");
                 
    m_pFont = pFont;             // for some reason, can't just do SetFont() here.
    m_bFontSetupDone = FALSE;
    
    SetWindowText(m_strInitial);                 
    
    return status;
}

//----------------------------------------------------------------------------
afx_msg void DragDropTextEdit::OnPaint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!m_bFontSetupDone)  {
        SetFont(m_pFont);
        OnEnUpdate();               
        m_bFontSetupDone = TRUE;    // only set font first time
        SetFocus();                 // Claim the focus 
        SetSel(0,-1);               // select the whole field
        //ShowCaret();                // just do this once  (position???)
    }   
    CWnd::OnPaint();
}

//----------------------------------------------------------------------------
afx_msg void DragDropTextEdit::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_lLastKey = nChar;

    // if there is an associated GoText, and this is single line, and the
    // user pressed the enter key, call DoEndEdit
    if (m_textObject && ((!m_bMultiline && nChar == VK_RETURN) || (nChar == VK_ESCAPE)))
        m_textObject->DoEndEdit();
    else    
        inherited::OnChar(nChar, nRepCnt, nFlags);
}

//----------------------------------------------------------------------------
afx_msg void DragDropTextEdit::OnSetFocus(CWnd* pWnd){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CPoint pt1 = GetCaretPos();
   CEdit::OnSetFocus(pWnd);    // call the default
   CPoint pt2 = GetCaretPos();
    
   CPoint pt(m_ptCursorSP);    // set the caret position
   ScreenToClient(&pt);
   SetCaretPos (pt);
}

//----------------------------------------------------------------------------
afx_msg void DragDropTextEdit::OnEnUpdate(){                                          
//----------------------------------------------------------------------------
	PROC_TRACE;

    CRect rectEdit;
    GetRect(&rectEdit); 
        
    CDC          *pDC      = GetDC();  
    int           nSavedDC = pDC->SaveDC();       //
    DragDropView *pView    = (DragDropView*)GetParent();
    assert (pView);
    assert (m_pFont);                
    pView->OnPrepareDC(pDC);         

    CFont* pOldFont = pDC->SelectObject(m_pFont);  
    CSize sizeChar =  pDC->GetTextExtent (_T("W"), 1); 
    
    CString string;
    GetWindowText(string);
    m_textObject->SetString(string);  
    CRect rect (m_textObject->GetBoundingRect()); 
    
    pDC->LPtoDP(&rect);
    
    pDC->RestoreDC(nSavedDC);
    ReleaseDC(pDC);                   

    CSize sizeNeeded (0, 0);
    sizeNeeded.cx = rect.Width();
    sizeNeeded.cy = rect.Height();

    CPoint ptNewLoc (m_ptOriginDP);
    if (!m_bMultiline) sizeNeeded.cx = sizeNeeded.cx + sizeChar.cx*2;       // leave room for two more characters   
   
    if (sizeNeeded.cy == 0) sizeNeeded.cy = sizeChar.cy; // make sure it is at least 1 line tall
    switch (m_nAlign){
    case TextTopLeft:
        break;
    case TextTopMiddle:
        ptNewLoc.x = ptNewLoc.x - (sizeNeeded.cx/2);            // Origin minus half needed width
        break;
    case TextTopRight:
        ptNewLoc.x = ptNewLoc.x - sizeNeeded.cx;                // Origin minus needed width
        break;              
    } // end switch
    
        
    if ( m_bAlwaysFitExactly || (sizeNeeded.cx > rectEdit.Width() || sizeNeeded.cy > rectEdit.Height()) ){
        if (m_dwStyle & WS_BORDER){    
            // this will move the window up and over so text doesn't move.
            int nBorderX = ::GetSystemMetrics(SM_CXBORDER) + ::GetSystemMetrics(SM_CXDLGFRAME);
            int nBorderY = ::GetSystemMetrics(SM_CYBORDER) + ::GetSystemMetrics(SM_CYDLGFRAME);
            ptNewLoc.x = ptNewLoc.x - nBorderX + 1;
            ptNewLoc.y = ptNewLoc.y - nBorderY + 1;
            sizeNeeded.cx = sizeNeeded.cx + nBorderX*2;
            sizeNeeded.cy = sizeNeeded.cy + nBorderY*2;
        }
        MoveWindow(ptNewLoc.x, ptNewLoc.y,sizeNeeded.cx, sizeNeeded.cy, TRUE);        // new size, force repaint

        if (m_bFontSetupDone) 
           UpdateWindow();                   // make the repaint happen now                  
    }
}
