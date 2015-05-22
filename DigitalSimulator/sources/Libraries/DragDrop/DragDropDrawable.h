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

#ifndef _DRAGDROPDRAWABLE_H_
#define _DRAGDROPDRAWABLE_H_

#include "DragDropobject.h"


class DragDropDrawable : public DragDropObject{
   typedef DragDropObject inherited;
public:
    DragDropDrawable();
    DragDropDrawable(CRect* pRect);
    DragDropDrawable(CPoint location, CSize size);
    
    virtual int SetPenStyle(int nPenStyle); 
    virtual int SetPenWidth(int nPenWidth);
    virtual COLORREF SetPenColor(COLORREF penColor);
    
    virtual int GetStockPen() { return (int)m_wStockPen; }  
    virtual int GetPenStyle() { return (int)m_wPenStyle; }  
    virtual int GetPenWidth() { return (int)m_wPenWidth; }
    virtual COLORREF GetPenColor() { return m_colorPen; }

    virtual int SetStockBrush(int nStockBrush);
    virtual COLORREF SetBrushColor(COLORREF brushColor);
    
    virtual int GetStockBrush() {return (int)m_wStockBrush; } 
    virtual COLORREF GetBrushColor() { return m_colorBrush; }
    virtual int SetStockPen(int nStockPen);
    virtual BOOL paint(CDC* pDC);

    virtual void Serialize(CArchive& ar);
    virtual DragDropObject* Clone() const; 

protected:


    WORD m_wStockPen;               // One of NULL, BLACK_PEN, NULL_PEN, WHITE_PEN
    WORD m_wPenStyle;               // pen Style for border
    WORD m_wPenWidth;               // pen Width for border
    WORD m_wStockBrush;         // One of NULL, BLACK_BRUSH, DKGRAY_BRUSH, HOLLOW_BRUSH, LTGRAY_BRUSH, 
                                // NULL_BRUSH, or WHITE_BRUSH

    COLORREF m_colorPen;        // pen Color for border
    COLORREF m_colorBrush;      // Color for CreateSolidBrush

    
    virtual void PreparePen(CDC* pDC, CPen*& pPen, CPen*& pOldPen);  //new, should obsolete above routines soon
    virtual void PostPen(CDC* pDC, CPen* pPen, CPen* pOldPen);
    virtual void PrepareBrush(CDC* pDC, CBrush*& pBrush, CBrush*& pOldBrush); 
    virtual void PostBrush(CDC* pDC, CBrush* pBrush, CBrush* pOldBrush);

private:
    void Init();
    DECLARE_SERIAL(DragDropDrawable)
};

#endif 
