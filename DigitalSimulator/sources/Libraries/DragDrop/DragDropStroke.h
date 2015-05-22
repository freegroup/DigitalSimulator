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

#ifndef _DRAGDROPSTROKE_H_
#define _DRAGDROPSTROKE_H_

#include "DragDropDrawable.h"

class DragDropStroke : public DragDropDrawable {
    typedef DragDropDrawable inherited ;
public:
    DragDropStroke();
    DragDropStroke(UINT nPenWidth);

    virtual void SetHighlightWidth(int nWidth);
    virtual int GetHighlightWidth() {return m_nHighlightWidth;}

    virtual void SetSelected(bool flag);
    virtual void SetHighlighted(bool flag);

    virtual void SetHighlightColor(COLORREF rgb);
    virtual COLORREF GetHighlightColor() {return m_lHighlightColor;}


    virtual BOOL PtInObject(CClientDC* pDC, CPoint ptToCheckLP, CPoint ptToCheckDP);
    virtual DragDropObject* Clone() const;
        
protected:

    BOOL                m_bChangingBoundingRect;
    int                 m_nHighlightWidth;
    COLORREF            m_lHighlightColor;
	 long                m_lastHitSegment;         // gibt das Segment an, in dem der letzte Hittest erfolgreich war - oder -1
    bool                m_highlighted;
    bool                m_selected;
    CDWordArray         m_dwaPoints;   // series of connected points  (2 elements for 1 point)

public:
    virtual BOOL paint(CDC* pDC);
    virtual void GeometryChange(CRect* pRectPrevious);      // called when object moved/resized

    virtual BOOL DrawXorObject(CDC* pDC);
    virtual void HighlightXOR(CDC* pDC, CRect* pRect); //??
    virtual void GainedSelection(DragDropSelection* pSelection);                                                          

    virtual BOOL HandleResizing(CClientDC* pDC, DragDropView* pView, CRect* pRect, CPoint pPoint, 
        int nHandleHit, int nEvent, 
        int nMinWidth = MIN_OBJECT_ON_RESIZE, int nMinHeight = MIN_OBJECT_ON_RESIZE);  

    int     NumPoints();
    virtual CPoint  GetStartPoint() {return GetPoint(0); }
    virtual CPoint  GetEndPoint() {return GetPoint(NumPoints()-1); }
    virtual CPoint  GetPoint(int i);
    virtual CString GetMetaName(){return "Stroke";};

    virtual void StartStroke();
    virtual void AddPoint(CPoint point);
    virtual void InsertPoint(long index, CPoint point);
    virtual void RemovePoint(int i) {m_dwaPoints.RemoveAt(i*2,2); }  // Safe? Callers should at least call FinishStroke when done with this.
    virtual void RemoveSegment(int i);
    virtual void FinishStroke();

protected:                 
    virtual void SetPoint(int i, CPoint point);
    virtual void SetPointX(int i, CPoint point);
    virtual int GetFirstPickPoint();
    virtual int GetLastPickPoint();

   
public:
    virtual void Serialize(CArchive& ar);
    DECLARE_SERIAL(DragDropStroke)
};

#endif 
