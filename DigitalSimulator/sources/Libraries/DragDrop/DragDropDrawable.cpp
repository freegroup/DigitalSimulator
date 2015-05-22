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
#include "defines.h"

#include "DragDropapp.h"      // for pen and brush cache access
#include "DragDropClientapp.h"
#include "DragDropDrawable.h"

IMPLEMENT_SERIAL(DragDropDrawable, DragDropObject, 2)

//----------------------------------------------------------------------------
DragDropDrawable::DragDropDrawable(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   Init();
}

//----------------------------------------------------------------------------
DragDropDrawable::DragDropDrawable(CRect* pRect) : inherited(pRect){
//----------------------------------------------------------------------------
	PROC_TRACE;

   Init();
} 

//----------------------------------------------------------------------------
DragDropDrawable::DragDropDrawable(CPoint location, CSize size) : inherited(location, size){
//----------------------------------------------------------------------------
	PROC_TRACE;

   Init();
} 

//----------------------------------------------------------------------------
void DragDropDrawable::Init(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_wStockPen = BLACK_PEN;
    m_wPenStyle = PS_SOLID;
    m_wPenWidth = 0;
    m_colorPen = CDragDropApp::GetPaletteIndexBlack(); //black
    
    m_wStockBrush = WHITE_BRUSH;
    m_colorBrush = CDragDropApp::GetPaletteIndexWhite(); //white
}


//----------------------------------------------------------------------------
DragDropObject* DragDropDrawable::Clone() const{   
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited* pObject = inherited::Clone();
   ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropDrawable)));                  
   DragDropDrawable* pDrawable =(DragDropDrawable*) pObject;

    pDrawable->m_wStockPen = m_wStockPen;   
    pDrawable->m_wPenStyle = m_wPenStyle;   
    pDrawable->m_wPenWidth = m_wPenWidth;   
    pDrawable->m_colorPen = m_colorPen; 
    pDrawable->m_wStockBrush = m_wStockBrush;   
    pDrawable->m_colorBrush = m_colorBrush; 

    return pObject;
}

//----------------------------------------------------------------------------
BOOL DragDropDrawable::paint(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!isVisible()) 
       return TRUE;


    CPen *pPen, *pOldPen;
    PreparePen(pDC, pPen, pOldPen);

   
    CBrush *pBrush, *pOldBrush;
    PrepareBrush(pDC, pBrush, pOldBrush);
                   
                   
    pDC->Rectangle(m_boundingRect);

    
    PostPen(pDC, pPen, pOldPen);  
    PostBrush(pDC, pBrush, pOldBrush);
        
    return TRUE;
}

//----------------------------------------------------------------------------
void DragDropDrawable::PreparePen(CDC* pDC, CPen*& pPen, CPen*& pOldPen) {   
//----------------------------------------------------------------------------
	PROC_TRACE;

   pPen = CDragDropApp::AllocPen(m_wStockPen);
   if (pPen == NULL) 
      return;
       

   if (m_wStockPen == DragDropNoStock) {
      if (!pPen->CreatePen(m_wPenStyle, m_wPenWidth, m_colorPen))     {
          CDragDropApp::DeallocPen(pPen, m_wStockPen);  // create failed
          pOldPen = NULL;
          return;
      }
   }           
   pOldPen = pDC->SelectObject(pPen);
}

//----------------------------------------------------------------------------
void DragDropDrawable::PostPen(CDC* pDC, CPen* pPen, CPen* pOldPen) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!pPen)
       return;
    
   if (m_wStockPen == DragDropNoStock)  {
       pDC->SelectObject(pOldPen);
       CDragDropApp::DeallocPen(pPen, m_wStockPen);
   }
}

//----------------------------------------------------------------------------
void DragDropDrawable::PrepareBrush(CDC* pDC, CBrush*& pBrush, CBrush*& pOldBrush) {
//----------------------------------------------------------------------------
	PROC_TRACE;

    pBrush = CDragDropApp::AllocBrush(m_wStockBrush);
    if (pBrush == NULL) 
       return;

    if (m_wStockBrush == DragDropNoStock) {
        if (!pBrush->CreateSolidBrush(m_colorBrush))  {
            CDragDropApp::DeallocBrush(pBrush, m_wStockBrush);
            pOldBrush = NULL;
            return;
        }
    }       
    pOldBrush = pDC->SelectObject(pBrush);
}


//----------------------------------------------------------------------------
void DragDropDrawable::PostBrush(CDC* pDC, CBrush* pBrush, CBrush* pOldBrush) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!pBrush) 
       return;
    if (m_wStockBrush == DragDropNoStock) {
        pDC->SelectObject(pOldBrush); // a non-stock brush, select the previous (stock) brush back
        CDragDropApp::DeallocBrush(pBrush, m_wStockBrush);
    }
    else ASSERT(TRUE);
}

//----------------------------------------------------------------------------
int DragDropDrawable::SetStockPen(int nStockPen) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_wStockPen == (WORD)nStockPen) 
       return m_wStockPen;

    ASSERT ((nStockPen >= WHITE_PEN && nStockPen <= NULL_PEN) || nStockPen == DragDropNoStock);
    int tmp = m_wStockPen;
    SetUpdateNeeded(TRUE);
    m_wStockPen = nStockPen;
    return tmp;
}

//----------------------------------------------------------------------------
int DragDropDrawable::SetPenStyle(int nPenStyle) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_wPenStyle == (WORD)nPenStyle) 
      return m_wPenStyle; // if not really a change...

    int tmp = m_wPenStyle;
    SetUpdateNeeded(TRUE);
    m_wPenStyle = nPenStyle;
    if (m_wPenWidth > 1) m_wPenStyle = PS_INSIDEFRAME;  // to avoid overspilling bounding rect
    return tmp;
}

//----------------------------------------------------------------------------
int DragDropDrawable::SetPenWidth(int nPenWidth) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_wPenWidth == (WORD)nPenWidth)
      return m_wPenWidth; // if not really a change...

    int tmp = m_wPenWidth;
    SetUpdateNeeded(TRUE);
    m_wPenWidth = nPenWidth;
    
    if (m_wPenWidth > 1) SetPenStyle(PS_INSIDEFRAME);   // to avoid overspilling bounding rect
    return tmp;
}

//----------------------------------------------------------------------------
COLORREF DragDropDrawable::SetPenColor(COLORREF penColor){                                                  
//----------------------------------------------------------------------------
	PROC_TRACE;

   COLORREF color2 = CDragDropApp::GetPaletteIndex(penColor); 
   if (m_colorPen == color2) 
       return m_colorPen;  

   SetUpdateNeeded(TRUE);

   COLORREF tmp = m_colorPen;
   m_colorPen = color2; 
   return tmp;
}

//----------------------------------------------------------------------------
int DragDropDrawable::SetStockBrush(int nStockBrush) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_wStockBrush == (WORD)nStockBrush)
      return m_wStockBrush;   // if not really a change...

    ASSERT ((nStockBrush >= WHITE_BRUSH && nStockBrush <= NULL_BRUSH) || nStockBrush == DragDropNoStock);

    int tmp = m_wStockBrush;
    SetUpdateNeeded(TRUE);
    m_wStockBrush = nStockBrush;
    return tmp;
}

//----------------------------------------------------------------------------
COLORREF DragDropDrawable::SetBrushColor(COLORREF brushColor){                                                  
//----------------------------------------------------------------------------
	PROC_TRACE;

   COLORREF color2 = CDragDropApp::GetPaletteIndex(brushColor);
   if (m_colorBrush == color2) 
       return m_colorBrush;    // if not really a change...

    COLORREF tmp = m_colorBrush;
    SetUpdateNeeded(TRUE);
    m_colorBrush = color2;
    return tmp;
}


//----------------------------------------------------------------------------
void DragDropDrawable::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

    if (ar.IsStoring()){
        ARC_WORD(m_wStockPen);
        ARC_WORD(m_wPenStyle);
        ARC_WORD(m_wPenWidth);
        ar << m_colorPen;
        ARC_WORD(m_wStockBrush);
        ar << m_colorBrush;
    }
    else {
        DEARC_WORD(m_wStockPen);
        DEARC_WORD(m_wPenStyle);
        DEARC_WORD(m_wPenWidth);
        ar >> m_colorPen;
        DEARC_WORD(m_wStockBrush);
        ar >> m_colorBrush;
    }
}
                             
