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

#include "DragDropText.h"
#include "DragDropDocument.h"
#include "DragDropSelection.h"
#include "DragDropEdit.h"
#include "DragDropView.h"

int DragDropText::m_nScaleNoDraw = 10;
int DragDropText::m_nScaleFakeDraw = 40;

IMPLEMENT_SERIAL(DragDropText, DragDropObject, 2)


//----------------------------------------------------------------------------
DragDropText::DragDropText(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_pTextEdit     = NULL;
   m_pFontEditText = NULL;
   m_pEditView     = NULL;
   m_nEscapement   = 0;
   SetIgnoreGeometryChange(FALSE);
}

DragDropText::DragDropText(CPoint location, CSize size, LPCTSTR pString, 
        LPCTSTR pFaceName, int nWeight, BOOL bUnderline, 
        BOOL bItalic, int nAlignment, BOOL bMultiLine, BOOL bEditable) : DragDropObject(location, size)
{       
    Init (pString, pFaceName, nWeight, bUnderline, bItalic, nAlignment, bMultiLine, bEditable);
    
    // The height of size is used for the height of a single line.

    m_nHeightLine = size.cy;            // set the height of a single line

    // Single line: Width must be zero.
    
    if (!bMultiLine && size.cx != 0) {
        TRACE(_T("DragDropText::DragDropText, single line text should be created with width=0\n"));
        size.cx = 0;
    }

    // Multi-line: Width is the maximum width of a single line.
    //      A zero width indicates that there is no maximum.

    m_nWidthLine = size.cx;             // width of a line
    
    // Set the bounding rectangle for all lines of the Text object.

    Measure();    
}                                        


CString DragDropText::DefaultFaceName = _T("Arial");

void DragDropText::Init (LPCTSTR pString, LPCTSTR pFaceName, int nWeight,
        BOOL bUnderline, BOOL bItalic, int nAlignment,
        BOOL bMultiLine, BOOL bEditable)
{       
    m_sString = (pString ? pString : _T(""));
    m_nWeight = nWeight;
    m_nAlignment = nAlignment;
    m_nEscapement = 0;
    
    m_wTextFlags = 0;
    if (bUnderline) m_wTextFlags = m_wTextFlags | flagUnderline;
    if (bItalic)    m_wTextFlags = m_wTextFlags | flagItalic;
    if (bMultiLine) m_wTextFlags = m_wTextFlags | flagMultiLine;
    if (bEditable)  m_wTextFlags = m_wTextFlags | flagEditable;
        
    if (pFaceName && (pFaceName[0] != _T('\0')))
        m_sFaceName = pFaceName;
    else
        m_sFaceName = DragDropText::DefaultFaceName;

    m_clrText = NULL;   // default is black
    m_clrBack = NULL;   // default is white
    m_nBkMode = OPAQUE; // use the Windows default

    m_pTextEdit = NULL;
    m_pFontEditText = NULL;
    m_pEditView = NULL;
}                                        


//----------------------------------------------------------------------------          
DragDropText::~DragDropText() {
//----------------------------------------------------------------------------
	PROC_TRACE;
   delete m_pFontEditText;
   m_pFontEditText = NULL;                 
    
   // need to tell all of the views that any active edits should be shut down.
    
   delete m_pTextEdit;
   m_pTextEdit = NULL;
   m_pEditView = NULL;
} 

//----------------------------------------------------------------------------
DragDropObject* DragDropText::Clone() const{   
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pObject = inherited::Clone();   
    ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropText)));                  
    DragDropText* pText =(DragDropText*) pObject;

    pText->m_sString       = m_sString;
    pText->m_nWeight       = m_nWeight;
    pText->m_nHeightLine   = m_nHeightLine;    
    pText->m_nWidthLine    = m_nWidthLine;
    pText->m_nAlignment    = m_nAlignment;
    pText->m_wTextFlags    = m_wTextFlags;
    pText->m_sFaceName     = m_sFaceName;
    pText->m_clrText       = m_clrText;
    pText->m_clrBack       = m_clrBack;
    pText->m_nBkMode       = m_nBkMode;
    pText->m_pTextEdit     = NULL;
    pText->m_pFontEditText = NULL;
    pText->m_pEditView     = NULL;
    return pObject;
}

//----------------------------------------------------------------------------
void DragDropText::MeasureAndUpdateHandles(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (Measure()){ 
      if (!m_pTextEdit) {                 
         // the size has changed, erase and redraw selection handles at new location
         if (m_pDocument && !m_pDocument->UpdatesSuspended()) {
            m_pDocument->UpdateAllViews(NULL, Update_ClearSelectionHandles, NULL);
            m_pDocument->UpdateAllViews(NULL, Update_RestoreSelectionHandles, NULL);
         }
      }   
   }
}

//----------------------------------------------------------------------------
BOOL DragDropText::Measure(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC dc(AfxGetApp()->m_pMainWnd);
    
   // If we can get the View and use its OnPrepareDC, Try to set it up...
    
   DragDropView* pView;
   if (m_pDocument) 
      pView = m_pDocument->GetCurrentDrawView();
   else 
      pView = m_pView;
   
   if (pView != NULL) {
       pView->OnPrepareDC(&dc);
   }
   else {
       DragDropAppMixIn::OnPrepareDC(&dc, NULL, 100);
   }

   return Measure(&dc);        
}

//----------------------------------------------------------------------------
BOOL DragDropText::Measure(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   LOGFONT lf;
    PrepareLogfont(lf);
    CFont font;
    font.CreateFontIndirect(&lf);
    CFont* pOldFont = pDC->SelectObject(&font);
    if (!pOldFont) TRACE0("DragDropText: Error doing SelectObject on Font\n");
        
    m_sString = GetString();    //GetString() is an over-ridable function, cache result

    BOOL bChanged = FALSE;
    if (IsMultiLine()){
        CRect rect = GetBoundingRect();
        
        // Use DrawText to measure the rectangle
        int format = DT_CALCRECT | DT_NOPREFIX; // DT_NOCLIP?
        int nAlignmentPoint;
        
        switch (m_nAlignment) {
            case TextTopLeft:
                format = format | DT_LEFT;              // left align
                break;    
            case TextTopMiddle:
                nAlignmentPoint = rect.left + rect.Width()/2;
                format = format | DT_CENTER;                    // center align
                break;
            case TextTopRight:
                nAlignmentPoint = rect.right;                
                format = format | DT_RIGHT;                     // right align
                break;
        } //switch

        if (m_nWidthLine > 0){
            format |= DT_WORDBREAK;
            rect.right = rect.left + m_nWidthLine;  // set the max width
        }    
        
        int rectleft = rect.left;
        int rectright = rect.right;
        
        pDC->DrawText(m_sString, m_sString.GetLength(), &rect, format); 
        rect.right = rect.right + (rect.right/100 + 1); 
        
        if (m_sString.GetLength() == 0) 
           rect.bottom = rect.top;

        if (abs(rect.Height()) != GetHeight() || abs(rect.Width()) != GetWidth()){
            if (m_nWidthLine > 0){   
                if (rect.left > rectleft) 
                   rect.left = rectleft;
                if (rect.right < rectright) 
                   rect.right = rectright;
            } // if
            SetIgnoreGeometryChange(TRUE);
            SetBoundingRect(&rect);
            SetIgnoreGeometryChange(FALSE);
            bChanged = TRUE;
        }     
        
    }
    else{
        CSize size = pDC->GetOutputTextExtent(m_sString, m_sString.GetLength());
        
        if (GetWidth() != size.cx){
            SetSize(size);         // Width has changed, update the bounding box        
            bChanged = TRUE;        // return value for function
        }                                                  
    }
    
    pDC->SelectObject(pOldFont);
    
    return bChanged;
}

//----------------------------------------------------------------------------
void DragDropText::PrepareLogfont(LOGFONT& lf){
//----------------------------------------------------------------------------
	PROC_TRACE;

   memset (&lf, 0, sizeof(LOGFONT));
    lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;  // ?
    lf.lfQuality = DRAFT_QUALITY; 
    lf.lfHeight = m_nHeightLine;             // Edit Text creation assumes this is the only item that MM_ matters 
    lf.lfWeight = m_nWeight;
    lf.lfUnderline = IsUnderline();
    lf.lfItalic = IsItalic();
    lf.lfEscapement = m_nEscapement;
    lf.lfOrientation = m_nEscapement;
    _tcscpy(lf.lfFaceName, m_sFaceName);
} 


//----------------------------------------------------------------------------
void DragDropText::GeometryChange(CRect* pRectPrevious){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (IsIgnoreGeometryChange()) 
       return;
   if (GetHeight() != abs(pRectPrevious->Height())) {
      Measure(); 
   }
 	if (m_pDocument) m_pDocument->SetModifiedFlag();
}

//---------------------------------------------------------------------------- 
BOOL DragDropText::paint(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!isVisible()) 
       return TRUE;

	DragDropView* pView;
	if (m_pDocument) pView = m_pDocument->GetCurrentDrawView();
	else pView = m_pView;
	int nScale =100;
	if (pView) nScale = pView->GetScale();

	if (nScale < m_nScaleNoDraw) return TRUE;    //NoDraw: don't draw at really small scales

    COLORREF clrOldBack, clrOldText;
	if (nScale < m_nScaleFakeDraw && m_nHeightLine < 100) {
        if (m_clrText) clrOldText = pDC->SetTextColor(m_clrText);
		pDC->MoveTo(GetSpotLocation(spotLeftCenter));
		pDC->LineTo(GetSpotLocation(spotRightCenter));
        if (m_clrText) pDC->SetTextColor(clrOldText);
		return TRUE;
	}
 
    LOGFONT lf;
    PrepareLogfont(lf);

    if (pDC->IsPrinting())  
    {
        // printed text always seems a little bigger than it should be...
        lf.lfHeight = lf.lfHeight/10*9; // 90% of height?                         
    }

    CFont font;
    if (!font.CreateFontIndirect(&lf)) 	
	{
		TRACE0("Failed to create font\n");
		return FALSE;      // fail to create
	}
    CFont* pOldFont = pDC->SelectObject(&font);  
	if (!pOldFont) 
	{
		TRACE0("Failed to select font\n");
		return FALSE;      // fail to create
	}

    if (GetString() != m_sString) 
        Measure(pDC);   // check to see if override has changed value

    // If we're zoomed, we may need to pick a smaller font to make it fit the rectangle...
    if (IsMultiLine())
    {
    }
    else
    {
        int nWidth = GetWidth();
        for (int i = 1; i < 10; i++) {
            CSize size = pDC->GetOutputTextExtent(m_sString, m_sString.GetLength());
            if (size.cx <= nWidth) break;
            lf.lfHeight = lf.lfHeight - 1;
			pDC->SelectObject(pOldFont);    
            VERIFY(font.DeleteObject( ));
		    if (!font.CreateFontIndirect(&lf)) 	
			{
			    TRACE0("Failed to create font (2)\n");
			    return FALSE;      // fail to create
			}
            pOldFont = pDC->SelectObject(&font);  
			if (!pOldFont) 
			{
			    TRACE0("Failed to select font (2)\n");
		        return FALSE;      // fail to create
			}
        }
    }

	// output the string here...

    int nOldBkMode;
    if (m_nBkMode != OPAQUE) nOldBkMode = pDC->SetBkMode(m_nBkMode);
    if (!pDC->IsPrinting())  {
        if (m_clrBack) clrOldBack = pDC->SetBkColor(m_clrBack);
        if (m_clrText) clrOldText = pDC->SetTextColor(m_clrText);
    }
    if (IsMultiLine())
    {
        CRect rect = GetBoundingRect();
        
        // Use DrawText to output multilines
        int format;
        if (m_nWidthLine > 0) 
            format = DT_NOCLIP | DT_NOPREFIX ; 
        else
            format = DT_NOCLIP | DT_NOPREFIX | DT_WORDBREAK;
        
        switch (m_nAlignment) {
            case TextTopLeft:
                format = format | DT_LEFT;              // left align
                break;    
            case TextTopMiddle:
                 format = format | DT_CENTER;           // center align
                break;
            case TextTopRight:
                format = format | DT_RIGHT;             // right align
                break;
        } //switch

       pDC->DrawText(m_sString, m_sString.GetLength(), &rect, format);
    }
    else
    {
        pDC->ExtTextOut(m_boundingRect.left, m_boundingRect.top, 
            ETO_CLIPPED, m_boundingRect, m_sString, m_sString.GetLength(), NULL);
    }   

    if (m_nBkMode != OPAQUE) pDC->SetBkMode(nOldBkMode);
    if (!pDC->IsPrinting())  {
        if (m_clrBack) pDC->SetBkColor(clrOldBack);
        if (m_clrText) pDC->SetTextColor(clrOldText);
    }
    pDC->SelectObject(pOldFont);    
    return TRUE;
}

//----------------------------------------------------------------------------
void DragDropText::SetString(const CString& pString){                       
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_sString == pString) return;       // no-op if string has not changed
    m_sString = pString;
    MeasureAndUpdateHandles();              // will recompute size
    SetUpdateNeeded(TRUE);                  // Force repaint just in case size was same    
}

//----------------------------------------------------------------------------
void DragDropText::SetHeight(int nHeight){
//----------------------------------------------------------------------------
	PROC_TRACE;

   TRACE0("DragDropText-Error: Don't know how to do SetHeight()\n"); 
}

//----------------------------------------------------------------------------
int DragDropText::SetLineHeight(int nHeight){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (nHeight == m_nHeightLine) return nHeight;   // no-op if no change
    int nPrev = m_nHeightLine;
    m_nHeightLine = nHeight;
    MeasureAndUpdateHandles();              // will recompute size
    return nPrev;
}

//----------------------------------------------------------------------------    
int DragDropText::SetLineWidth(int nWidth){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (nWidth == m_nWidthLine) return nWidth;   // no-op if no change
    int nPrev = m_nWidthLine;
    m_nWidthLine = nWidth;
    MeasureAndUpdateHandles();              // will recompute size
    return nPrev;
}

//----------------------------------------------------------------------------
void DragDropText::SetWeight(int nWeight){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_nWeight == nWeight) return;       // no-op if no change      
    m_nWeight = nWeight;
    MeasureAndUpdateHandles();              // will recompute size
    SetUpdateNeeded(TRUE);                  // Force repaint just in case size was same    
}

//----------------------------------------------------------------------------
void DragDropText::SetFaceName(const CString& pName){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_sFaceName == pName) return;       // no-op if no change      
    m_sFaceName = pName;
    MeasureAndUpdateHandles();              // will recompute size
    SetUpdateNeeded(TRUE);                  // Force repaint just in case size was same    
}

//----------------------------------------------------------------------------
void DragDropText::SetUnderline(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
    {
        if (IsUnderline()) return;         // no-op if already underline (avoids any flash on screen)
        m_wTextFlags = m_wTextFlags | flagUnderline;  // 'OR' in Underline bit
    }
    else
    {
        if (!IsUnderline()) return;           // no-op if already no underline (avoids any flash on screen)
        m_wTextFlags = m_wTextFlags & ~flagUnderline;  // 'AND NOT' Underline
    }
    MeasureAndUpdateHandles();              // will recompute size
    SetUpdateNeeded(TRUE);                  // Force repaint just in case size was same         
}

//----------------------------------------------------------------------------
void DragDropText::SetItalic(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
    {
        if (IsItalic()) return;         // no-op if already Italic (avoids any flash on screen)
        m_wTextFlags = m_wTextFlags | flagItalic;  // 'OR' in Italic bit
    }
    else
    {
        if (!IsItalic()) return;           // no-op if already no Italic (avoids any flash on screen)
        m_wTextFlags = m_wTextFlags & ~flagItalic;  // 'AND NOT' Italic
    }
    MeasureAndUpdateHandles();              // will recompute size
    SetUpdateNeeded(TRUE);                  // Force repaint just in case size was same    
}

//----------------------------------------------------------------------------
void DragDropText::SetEditable(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
    {
        if (IsEditable()) return;         // no-op if already Editable (avoids any flash on screen)
        m_wTextFlags = m_wTextFlags | flagEditable;  // 'OR' in Editable bit
    }
    else
    {
        if (!IsEditable()) return;           // no-op if already no Editable (avoids any flash on screen)
        m_wTextFlags = m_wTextFlags & ~flagEditable;  // 'AND NOT' Editable
    }
    // No Update needed.
}

//----------------------------------------------------------------------------
void DragDropText::SetIgnoreGeometryChange(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
        m_wTextFlags = m_wTextFlags | flagIgnoreGeometryChange;  // 'OR' in IgnoreGeometryChange bit
    else
        m_wTextFlags = m_wTextFlags & ~flagIgnoreGeometryChange;  // 'AND NOT' IgnoreGeometryChange
}

//----------------------------------------------------------------------------
void DragDropText::SetMultiLine(BOOL bFlag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (bFlag)
        m_wTextFlags = m_wTextFlags | flagMultiLine;  // 'OR' in MultiLine bit
    else
        m_wTextFlags = m_wTextFlags & ~flagMultiLine;  // 'AND NOT' MultiLine
}

//----------------------------------------------------------------------------
void DragDropText::SetBkMode(int nBkMode){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT (nBkMode == OPAQUE || nBkMode == TRANSPARENT);
    if (m_nBkMode == nBkMode) return;       // no-op if no change      
    m_nBkMode = nBkMode;
    SetUpdateNeeded(TRUE);                  // Force repaint
}

//----------------------------------------------------------------------------     
void DragDropText::SetTextColor(COLORREF color){
//----------------------------------------------------------------------------
	PROC_TRACE;

    COLORREF color2 = CDragDropApp::GetPaletteIndex(color);
    if (m_clrText == color2) 
       return;
    m_clrText = color2;
    SetUpdateNeeded(TRUE);                  // Force repaint
}

//----------------------------------------------------------------------------    
void DragDropText::SetBkColor(COLORREF color){
//----------------------------------------------------------------------------
	PROC_TRACE;

    COLORREF color2 = CDragDropApp::GetPaletteIndex(color);
    if (m_clrBack == color2) return;
    m_clrBack = color2;
    SetUpdateNeeded(TRUE);                  // Force repaint
}

//----------------------------------------------------------------------------
void DragDropText::GainedSelection(DragDropSelection* pSelection){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // the object has gained selection, it is time to set up resize handles
    // or whatever the object uses as selection highlighting.
    
    // by default, the object has 8 resize handles if resizable or a 
    // colored bounding rect if not.

    if (!IsResizable()) {
        pSelection->CreateBoundingHandle (this);
        return;
    }
       
    int nWidth = GetWidth();
    int nHeight = GetHeight();

    CRect rect = GetBoundingRect();
    
    int x1 = rect.left;
    int x2 = rect.left + (nWidth/2);
    int x3 = rect.right;
    
    int y1 = rect.top;
    int y2 = rect.top - (nHeight/2);
    int y3 = rect.bottom;
    
    pSelection->CreateResizeHandle (this, x1, y1, NoHandle,     FALSE);
    pSelection->CreateResizeHandle (this, x2, y1, TopMiddle,    TRUE);
    pSelection->CreateResizeHandle (this, x3, y1, NoHandle,     FALSE);
    pSelection->CreateResizeHandle (this, x3, y2, NoHandle,     FALSE);
    pSelection->CreateResizeHandle (this, x3, y3, NoHandle,     FALSE);
    pSelection->CreateResizeHandle (this, x2, y3, BottomMiddle, TRUE);
    pSelection->CreateResizeHandle (this, x1, y3, NoHandle,     FALSE);
    pSelection->CreateResizeHandle (this, x1, y2, NoHandle,     FALSE);

    return;
}

//----------------------------------------------------------------------------
void DragDropText::LostSelection(DragDropSelection* pSelection){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::LostSelection(pSelection);
}                                        

BOOL DragDropText::HandleResizing(CClientDC* pDC, DragDropView* pView, CRect* pRect, CPoint pPoint, 
                             int nHandleHit, int nEvent, int, int){ 
    // Text handles its own resize constraints, since the length and height change
    // together as the height is varied by the user

    CRect beforeRect;
    beforeRect.CopyRect(pRect);

    switch (nHandleHit) {
    case TopMiddle:
        pRect->top = pPoint.y;
        break;  
    case BottomMiddle:
        pRect->bottom = pPoint.y;
        break;  
    }
            
    // Apply minimum size
    
    #define MIN_TEXT_SIZE 12
    
    if ((pRect->top != beforeRect.top)       && ((pRect->Height()) > -MIN_TEXT_SIZE))  
        pRect->top = beforeRect.bottom + MIN_TEXT_SIZE;
    if ((pRect->bottom != beforeRect.bottom) && ((pRect->Height()) > -MIN_TEXT_SIZE))  
        pRect->bottom = beforeRect.top - MIN_TEXT_SIZE;
    
    // Now, measure the extent of the text given the current height...
    
    if (IsMultiLine())
    {
        // the "3" below is a hack to round down a little so a close divide doesn't round off                 
        int nLines = abs(beforeRect.Height())/(m_nHeightLine-3);    // height of rect divided by height of one line 
        if (nLines < 1) nLines = 1;                         // avoid divide by zero
        m_nHeightLine = abs(pRect->Height()) /nLines;       // new height
        
    }
    else // single line
        m_nHeightLine = abs(pRect->Height());     // new height
    
    Measure(pDC);
       
    return FALSE;   
} 

//----------------------------------------------------------------------------
BOOL DragDropText::DoLButtonDblClk(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){                    
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!IsEditable()) return FALSE;    // Indicate that the double-click has not been handled.

    CPoint pt (pointDP);
    pView->ClientToScreen(&pt); 
    DoStartEdit(pView, pt);
    
    return TRUE;     
}

//----------------------------------------------------------------------------
void DragDropText::DoStartEdit(DragDropView* pView, CPoint ptCursorSP){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // first, hind the handles for this object (which should be the selection...)
    pView->ClearSelectionHandles();

    m_pTextEdit = new DragDropTextEdit(m_sString, TRUE, this);
        
    m_pEditView = pView;
    pView->SetEditControl(m_pTextEdit);    // tell the view so messages can be passed here
                            
    CRect rect (GetBoundingRect());                         
    pView->GetRectDP(&rect);
            
    DWORD flags;
    flags = WS_CHILD | WS_VISIBLE | WS_BORDER;
    if (m_nAlignment == TextTopMiddle) flags = flags | ES_CENTER;
    if (m_nAlignment == TextTopRight ) flags = flags | ES_RIGHT;

    PrepareLogfont(m_FontLOGFONT);
    if (IsMultiLine()) {
        flags = flags | ES_MULTILINE | ES_AUTOVSCROLL;
        CRect rectML (0, 0, 0, -m_nHeightLine);     // need a way to covert LP to DP
        pView->GetRectDP(&rectML);
        m_FontLOGFONT.lfHeight = rectML.Height();   // height for this font needs to be DP, not LP
    }    
    else {
        flags = flags | ES_AUTOHSCROLL;
        m_FontLOGFONT.lfHeight = rect.Height();     // height for this font needs to be DP, not LP
    }
    m_pFontEditText = new CFont();
    if (!m_pFontEditText->CreateFontIndirect(&m_FontLOGFONT))
        TRACE0("DragDropText: Error creating font for EditText\n");

    m_pTextEdit->Create ( flags,       
                    rect,
                    pView,
                    pView->GetTextControlId(), 
                    m_pFontEditText,
                    ptCursorSP);
                    
    SetVisible(FALSE);                        

}

//----------------------------------------------------------------------------
void DragDropText::DoEndEdit(DragDropView* pView /* == NULL */){
//----------------------------------------------------------------------------
	PROC_TRACE;
                       
    // simply delete the text edit control, and let the destructor set the
    // new string in this DragDropText object

    if (!pView) pView = m_pEditView;                           
    pView->SetEditControl(NULL);    // tell the view we're done

    delete m_pTextEdit; 
    m_pTextEdit = NULL;
    m_pEditView = NULL;
    
    delete m_pFontEditText;
    m_pFontEditText = NULL;
    
    SetVisible(TRUE);     
    pView->RestoreSelectionHandles();
}


//----------------------------------------------------------------------------
void DragDropText::SetSize(CSize pSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetSize(pSize.cx, pSize.cy);
}

//----------------------------------------------------------------------------
void DragDropText::SetSize(int cx, int cy){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetIgnoreGeometryChange(TRUE);
    if (cx == 0) cx = 5;    // force minimum width  ** gross hack, this needs DoCalculate.
    switch (m_nAlignment) {
        case TextTopLeft:   // left align
            SetBoundingRect(m_boundingRect.left, m_boundingRect.top, 
                     m_boundingRect.left + cx, m_boundingRect.top - cy);
            break;  

        case TextTopMiddle: {   // center align
            int nMidpt = m_boundingRect.left + (m_boundingRect.Width()/2);  //use current loc
            int nLeft = nMidpt - (cx/2);
            SetBoundingRect(nLeft, m_boundingRect.top, 
                     nLeft + cx, m_boundingRect.top - cy);
            break;  
            }
        case TextTopRight:  // right align
            SetBoundingRect(m_boundingRect.right - cx, m_boundingRect.top, 
                     m_boundingRect.right, m_boundingRect.top - cy);        
            break;  

        default:
            TRACE0("Invalid Text Alignment in SetSize\n");
            break;
    } //switch
    SetIgnoreGeometryChange(FALSE);

}  

//----------------------------------------------------------------------------
void DragDropText::SetLocation(int x, int y){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CSize size = GetSize();
    switch (m_nAlignment) {
        case TextTopLeft:   // left align
            SetBoundingRect(x, y, x + size.cx, y - size.cy);
            break;  

        case TextTopMiddle: {   // center align
            int nLeft = x - (size.cx/2);
            SetBoundingRect(nLeft, y, nLeft + size.cx, y - size.cy);
            break;  
            }
        case TextTopRight:  // right align
            SetBoundingRect(x - size.cx, y, x, y - size.cy);        
            break;  

        default:
            TRACE0("Invalid Text Alignment in SetLocation\n");
            break;
    }

} 

//----------------------------------------------------------------------------
CPoint DragDropText::GetLocation(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CSize size = GetSize();
    CPoint pt;
    CRect rect = GetBoundingRect();
    pt = rect.TopLeft();
    
    switch (m_nAlignment) {
        case TextTopLeft:   // left align
            // already done
            break;  

        case TextTopMiddle: {   // center align
            pt.x = pt.x + (size.cx/2);
            break;  
            }
        case TextTopRight:  // right align
            pt.x = rect.right;      
            break;  

        default:
            TRACE0("Invalid Text Alignment in GetLocation\n");
            break;
    } //switch
    return pt;
}


//----------------------------------------------------------------------------
void DragDropText::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);
    if (ar.IsStoring()){
        ar << m_sString;
        ar << (WORD) m_nWeight;
        ar << (WORD) m_nAlignment;
        ar << (WORD) m_nHeightLine;
        ar << (WORD) m_nWidthLine;
        ar << (WORD) m_wTextFlags;
        ar << m_sFaceName;      
        ar << m_clrText;
        ar << m_clrBack;
        ar << (WORD) m_nBkMode;
    }
    else{
        ar >> m_sString;
        WORD w;
        ar >> w;
        m_nWeight = w;
        ar >> w;
        m_nAlignment = w;
        ar >> w;
        m_nHeightLine = w;
        ar >> w;
        m_nWidthLine = w;
        ar >> w;
        m_wTextFlags = w;        
        ar >> m_sFaceName;  
        ar >> m_clrText;
        ar >> m_clrBack;
        ar >> w;
        m_nBkMode = w;
    }
}
                             
