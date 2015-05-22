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

#ifndef _DRAGDROPGRIDVW_H_
#define _DRAGDROPGRIDVW_H_

#include "DragDropobject.h"
#include "DragDropview.h"

const CPoint    DragDropGridOrigin = CPoint(100,-100);
const int       DragDropGridWidth  = 200;
const int       DragDropGridHeight = 200;
const int       DragDropGridSkew   = 0;
const DragDropObject::SpotNumber DragDropGridObjectSpot = DragDropObject::spotTopLeft;


class DragDropGridView : public DragDropView{
    typedef DragDropView inherited ;
    DECLARE_DYNCREATE(DragDropGridView)

public:
    DragDropGridView();
    virtual ~DragDropGridView();

public:
    virtual void    SetGridOrigin(CPoint pointOrigin);
    virtual CPoint  GetGridOrigin() const;

    virtual void    SetGridWidth(int nWidth);
    virtual int     GetGridWidth() const;

    virtual void    SetGridHeight(int nHeight);
    virtual int     GetGridHeight() const;

    virtual void    SetGridSkew(int nHeight);
    virtual int     GetGridSkew() const;
    
    virtual CPoint  GetGridLocation(int nRow, int nCol);

    enum    GridStyle {             // grid visual style:
                    GridInvisible,  //    invisible (default)
                    GridDot,        //    small dots at grid points
                    GridCross,      //    small "+" at grid points
                    GridLine };     //    dotted grid lines

    virtual void      SetGridStyle(GridStyle styleCode);
    virtual GridStyle GetGridStyle() const;

    virtual void    SetObjectSpot(DragDropObject::SpotNumber nSpot);
    virtual DragDropObject::SpotNumber GetObjectSpot() const;

    enum    AutoSnap {              // Automatic snap-to-grid modes:
                    NoSnap,         //    no automatic snap (default)
                    SnapJump,       //    jump from point to point
                    SnapAfter };    //    snap after move (MB-up)

    virtual void     SetSnapMove(AutoSnap snapCode);
    virtual AutoSnap GetSnapMove() const;

    virtual void     SetSnapResize(AutoSnap snapCode);
    virtual AutoSnap GetSnapResize() const;

    virtual void    SnapObject(DragDropObject* pObject);
    virtual void    SnapObject(DragDropObject* pObject, DragDropObject::SpotNumber nSpot);

    virtual void    SnapAllObjects();
    virtual void    SnapAllObjects(DragDropObject::SpotNumber nSpot);

    virtual void    SetGridColor(COLORREF color){m_gridColor=color;};

protected:
    COLORREF    m_gridColor;
private:
    CPoint      m_pointGridOrigin;  // location of "upper left" grid point
    int         m_nGridWidthLoMM;   // grid width
    int         m_nGridHeightLoMM;  // grid height
    int         m_nGridSkewLoMM;    // grid skew -- height delta on even columns
    
    GridStyle   m_GridStyle;        // grid visual style 

    DragDropObject::SpotNumber  m_nObjectSpot;   // object spot to be snapped to the grid

    AutoSnap    m_snapMove;         // Object moving snap-to-grid state
    AutoSnap    m_snapResize;       // Object resizing snap-to-grid state
    
    LPPOINT     m_pStartPoints;     // Object starting locations for SnapJump movement

    // Override parent class to ...
    
protected:
    virtual void DoDrawBackgroundDecoration(CDC* pDC);  // draw grids 
    virtual void MoveSelection(CSize sizeOffset, CPoint pointLP, int nEvent);   // snap moving
    virtual void CancelMoveSelection();   // snap moving
    virtual void HandleResizing(CClientDC*, CPoint pPoint, int nEvent);    // snap resizing

    virtual CPoint CalcNearestGridPosition(CPoint pointSpot);
    virtual CPoint CalcNearestGridPosition(CPoint pointSpot, UINT& rnRow, UINT& rnColumn);
    virtual void CalcNearestColumns(CPoint pointSpot, UINT& rnLeftColumn, UINT& rnRightColumn);
    virtual void CalcNearestRows(CPoint pointSpot, UINT nColumn, UINT& rnUpperRow, UINT& rnLowerRow);

private:    
    virtual BOOL DrawGridPoints(int nRadius, CDC* pDC);
    virtual BOOL DrawGridLines(CDC* pDC);

    virtual void SnapPointHorizontal(CPoint& pPoint);
    virtual void SnapPointVertical(CPoint& pPoint);

protected:
    //{{AFX_MSG(DragDropGridView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

   
#endif 

