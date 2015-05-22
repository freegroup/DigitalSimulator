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

#ifndef _DRAGDROPEDIT_H_
#define _DRAGDROPEDIT_H_

#include "DragDrop.h"

class DragDropText;
          

class DragDropTextEdit : public CEdit{ 
    typedef CEdit inherited ;
public:
    DragDropTextEdit();
    DragDropTextEdit(const CString& pString, BOOL bAlwaysFit, DragDropText* pGoTextObject);
    virtual ~DragDropTextEdit();  

    virtual BOOL          Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CFont* pFont, CPoint cursorSP);
    virtual DragDropText* GetTextObject() {return m_textObject;} 
    
    afx_msg void OnEnUpdate();

protected:
    CPoint      m_ptUpperLeftDP;        // upper left relative to parent (in DP)
    CPoint      m_ptOriginDP;           // origin (left, center or right) (in DP)
    CPoint      m_ptCursorSP;           // location of mouse click that started this in screen points
    DragDropText*    m_textObject;       // Related Text Object
    CFont*      m_pOldFont;             // previous font
    CFont*      m_pFont;
    CString     m_strInitial;           // Initial String.
    int         m_nAlign;               // one of 'enum TextAlign' from go.h
    BOOL        m_bMultiline;           // multiline control
    BOOL        m_bAlwaysFitExactly;    // always fit editing rectangle to size needed
    BOOL        m_bFontSetupDone;       
    DWORD       m_dwStyle;
    UINT        m_lLastKey; 

    //{{AFX_MSG(DragDropTextEdit)
    afx_msg void OnChar (UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnPaint();
    afx_msg void OnSetFocus(CWnd* pWnd);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    DECLARE_DYNCREATE(DragDropTextEdit)
};
 
#endif
