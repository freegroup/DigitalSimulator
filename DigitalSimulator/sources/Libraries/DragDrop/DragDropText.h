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

#ifndef _DRAGDROPTEXT_H_
#define _DRAGDROPTEXT_H_

#include "DragDropObject.h"

class DragDropTextEdit; 
class DragDropView;

class DragDropText : public DragDropObject{
    typedef DragDropObject inherited ;
public:
    DragDropText();
    DragDropText(CPoint location, CSize size, LPCTSTR pString, 
            LPCTSTR pFaceName = DefaultFaceName,
            int nWeight = FW_NORMAL, BOOL bUnderline = FALSE, 
            BOOL bItalic = FALSE, int nAlignment = TextTopLeft, 
            BOOL bMultiLine = FALSE, BOOL bEditable = FALSE);
    virtual ~DragDropText();

    static CString DefaultFaceName;
    virtual DragDropObject* Clone() const;
    virtual CString GetMetaName(){return "Text";};
    
protected:

    CString m_sString;          // (archived) string to draw


    int     m_nWeight;          // (archived) weight
    int     m_nHeightLine;      // (archived) Height of one line
    int     m_nWidthLine;       // (archived) Width of one line
    int     m_nAlignment;       // (archived) alignment
    WORD    m_wTextFlags;       // Boolean flags (see flags below)
    int     m_nEscapement;
   
    enum textFlags{
       flagUnderline            = 0x01,         // (archived) underline text
       flagItalic               = 0x02,         // (archived) italic text
       flagMultiLine            = 0x04,         // (archived) multi-line field
       flagEditable             = 0x08,         // (archived) editable text
       flagIgnoreGeometryChange = 0x10        // (not archived)
    }; 

    CString m_sFaceName;        // (archived) facename
    COLORREF m_clrText;         // (archived) default is black
    COLORREF m_clrBack;         // (archived) default is white
    int     m_nBkMode;          // (archived) use the Windows default
    
    DragDropTextEdit*    m_pTextEdit;    // (not archived) pointer to dynamically created edit field
    CFont*  m_pFontEditText;    // (not archived) pointer to font for edit field
    LOGFONT m_FontLOGFONT;      // (not archived)
    DragDropView* m_pEditView;       // (not archived) pointer to view for edit field
    
	static	int m_nScaleNoDraw;
	static	int m_nScaleFakeDraw;

public:
    virtual BOOL paint(CDC* pDC);
    virtual void GeometryChange(CRect* pRectPrevious);      // Object has been moved/resized event
    virtual void GainedSelection(DragDropSelection* pSelection);
    virtual void LostSelection(DragDropSelection* pSelection);
    virtual BOOL DoLButtonDblClk(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
    
    virtual BOOL HandleResizing(CClientDC* pDC, DragDropView* pView, CRect* pRect, CPoint pPoint, 
        int nHandleHit, int nEvent, 
        int nMinWidth = MIN_OBJECT_ON_RESIZE, int nMinHeight = MIN_OBJECT_ON_RESIZE);   

    virtual void SetSize(CSize pSize);
 	 virtual void SetSize(int cx, int cy);       // width, height in "int" form
    
    virtual CPoint GetLocation();
    virtual void SetLocation(int x, int y);
    virtual void SetHeight(int nHeight);  // ?? does this make sense now?

    virtual int SetLineHeight(int nHeight);
    virtual int GetLineHeight() {return m_nHeightLine;}
    
    virtual int SetLineWidth(int nWidth);
    virtual int GetLineWidth() {return m_nWidthLine;}
    
    virtual void SetWeight(int nWeight);
    virtual int GetWeight() {return m_nWeight;}

    virtual void SetAlignment(int nAlignment) {m_nAlignment = nAlignment;}
    virtual int GetAlignment() {return m_nAlignment;}
     
    virtual void SetUnderline(BOOL bFlag);
    virtual const BOOL IsUnderline() const {return ((m_wTextFlags & flagUnderline) != 0);}
 
    virtual void SetItalic(BOOL bFlag);
    virtual const BOOL IsItalic() const {return ((m_wTextFlags & flagItalic) != 0);}

    virtual const BOOL IsMultiLine() const {return ((m_wTextFlags & flagMultiLine) != 0);}

    virtual void SetEditable(BOOL bFlag);
    virtual const BOOL IsEditable() const {return ((m_wTextFlags & flagEditable) != 0);}

    virtual void SetIgnoreGeometryChange(BOOL bFlag);
    virtual const BOOL IsIgnoreGeometryChange() const {return ((m_wTextFlags & flagIgnoreGeometryChange) != 0);}
    
    virtual void SetFaceName(const CString& pName);
    virtual const CString& GetFaceName() {return m_sFaceName; }

    virtual void SetString(const CString& pString);
    virtual const CString& GetString() {return m_sString; }
        
    virtual void SetBkMode(int nBkMode);
    virtual int GetBkMode() {return m_nBkMode;}
    
    virtual void SetTextColor(COLORREF color);
    virtual COLORREF GetTextColor() {return m_clrText;}
    
    virtual void SetBkColor(COLORREF color);
    virtual COLORREF GetBkColor() {return m_clrBack;}
    
    virtual void DoStartEdit(DragDropView* pView, CPoint ptCursorSP);
    virtual void DoEndEdit(DragDropView* pView = NULL);


protected:
    virtual void PrepareLogfont(LOGFONT& lf);       // allows overriding of LOGFONT setup 
    virtual BOOL Measure(CDC* pDC);                         // Calculate size
    virtual BOOL Measure();                                 // Calculate size
    virtual void MeasureAndUpdateHandles();                 // Call Measure and reset Selection Handles

    virtual void SetMultiLine(BOOL bFlag);                  // do not allow client to change this

private:
    virtual void Init (LPCTSTR pString, LPCTSTR pFaceName, int nWeight, BOOL bUnderline, 
        BOOL bItalic, int nAlignment, BOOL bMultiLine, BOOL bEditable);
                    
public:
    virtual void Serialize(CArchive& ar);
    friend class DragDropTextEdit;
    DECLARE_SERIAL(DragDropText)
};

#endif
