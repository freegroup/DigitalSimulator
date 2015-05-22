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

#ifndef _DRAGDROPOBJECT_H_
#define _DRAGDROPOBJECT_H_

#include "DragDrop.h"
class DragDropArea;
class DragDropDocument;
class DragDropSelection;
class DragDropView;
class DragDropAnchor;
          
class DragDropObject : public CObject{
    typedef CObject inherited ;

public:
   enum SpotNumber {       // Alignment spots:
      spotCenter = 0,     //    center of an object (common to all classes)
      spotTopLeft,        //    Start at top left and number corners
      spotTopCenter,      //       and midpoints in clockwise order.
      spotTopRight,
      spotRightCenter,    // Note: Derived classes may redefine all spot
      spotBottomRight,    //    numbers other than zero (0).
      spotBottomCenter,
      spotBottomLeft,
      spotLeftCenter 
   };

   DragDropObject();
   DragDropObject(CRect* pRect);
   DragDropObject(CPoint point);
   DragDropObject(CPoint location, CSize size);
   virtual ~DragDropObject();

   virtual void Serialize(CArchive& ar);

   virtual CPoint GetSpotLocation(SpotNumber nSpot);
   virtual void SetLocation(CPoint pPoint);
   virtual void SetLocation(int x, int y);
   virtual void SetLocationOffset(CPoint pPoint, CSize pOffset);
   virtual void SetLocationOffset(CPoint pPoint, int cx, int cy);
   virtual void SetLocationOffset(int x, int y, int cx, int cy);
   virtual void SetSpotLocation(SpotNumber nThisSpot, CPoint point);
   virtual void SetSpotLocation(SpotNumber nThisSpot, DragDropObject* pOtherObject, 
                      SpotNumber nOtherSpot);
   virtual void SetSpotLocation(SpotNumber nThisSpot, int x, int y);
   virtual void SetSpotLocationOffset(SpotNumber nThisSpot, CPoint point, int cx, int cy);
   virtual void SetSpotLocationOffset(SpotNumber nThisSpot, DragDropObject* pOtherObject, 
                            SpotNumber nOtherSpot, int cx, int cy);
   virtual void SetSpotLocationOffset(SpotNumber nThisSpot, int x, int y, int cx, int cy);
   virtual CRect& GetPrevBoundingRect() { return DragDropObject::m_rectPrevBounding; }
   virtual CPoint& GetPrevLocation() { return DragDropObject::m_rectPrevBounding.TopLeft(); }
   virtual int GetPrevWidth() { return  abs(DragDropObject::m_rectPrevBounding.right -
                                  DragDropObject::m_rectPrevBounding.left); }
   virtual int GetPrevHeight() { return abs(DragDropObject::m_rectPrevBounding.bottom - 
                                  DragDropObject::m_rectPrevBounding.top); } 

   virtual BOOL PtInObject(CClientDC* pDC, CPoint ptToCheckLP, CPoint ptToCheckDP);

   virtual void SetUpdateNeeded(BOOL bFlag);   //** should be Update() or UpdateView();
       
   void SetVisible(BOOL bFlag);
   virtual BOOL isVisible() const ;
   void SetSelectable(BOOL bFlag);
   const BOOL IsSelectable() const {return ((m_wFlags & flagSelectable) != 0);}
   void SetDraggable(BOOL bFlag);
   const BOOL IsDraggable() const {return ((m_wFlags & flagDraggable) != 0);}
   void SetResizable(BOOL bFlag);
   const BOOL IsResizable() const {return ((m_wFlags & flagResizable) != 0);}
   void SetPrevRectValid(BOOL bFlag);
   const BOOL IsPrevRectValid() const {return ((m_wFlags & flagPrevRectValid) != 0);}
   void SetSuspendChildUpdates(BOOL bFlag);
   const BOOL IsSuspendChildUpdates() const {return ((m_wFlags & flagSuspendChildUpdates) != 0);}
   void SetClearOnUpdate(BOOL bFlag);
   const BOOL IsClearOnUpdate() const {return ((m_wFlags & flagClearOnUpdate) != 0);}
   void Set4ResizeHandles(BOOL bFlag);
   const BOOL Is4ResizeHandles() const {return ((m_wFlags & flag4ResizeHandles) != 0);}
   void SetSuspendUpdates(BOOL bFlag);
   const BOOL SuspendUpdates() const {return ((m_wFlags & flagSuspendUpdates) != 0);}
   void SetNonStandardMove(BOOL bFlag);
   const BOOL IsNonStandardMove() const {return ((m_wFlags & flagNonStandardMove) != 0);}
   void SetNoLayout(BOOL bFlag);
   const BOOL IsNoLayout() const {return ((m_wFlags & flagNoLayout) != 0);}
   virtual void SetDocument(DragDropDocument* pDocument) {m_pDocument = pDocument;} 
   virtual DragDropDocument* GetDocument() {return m_pDocument;}    // owner document, NULL before object added to a document   
   virtual DragDropObject* GetParent() { return m_pParentArea;}     // parent of object when in DragDropArea Heirarchy
   virtual void    SetBoundingRectForce(int nLeft, int nTop, int nRight, int nBottom);
   virtual void    SetBoundingRect(CRect* pRect);
   virtual void    SetBoundingRect(int nLeft, int nTop, int nRight, int nBottom);
   virtual void    SetBoundingRect(CPoint loc, CSize size);
   virtual CRect   GetBoundingRect() { return m_boundingRect; }
   virtual CSize   GetSize() const { return CSize(abs(m_boundingRect.right - m_boundingRect.left),
                                  abs(m_boundingRect.bottom - m_boundingRect.top)); }
   virtual void    SetSize(CSize pSize);
   virtual void    SetSize(int cx, int cy);       // width, height in "int" form
   virtual int     GetWidth() { return  abs(m_boundingRect.right - m_boundingRect.left); }
   virtual int     GetHeight() { return abs(m_boundingRect.bottom - m_boundingRect.top); }

   virtual CPoint& GetTopLeft() { return m_boundingRect.TopLeft(); }
   virtual CPoint  GetLocation() const { return m_boundingRect.TopLeft(); }
   virtual void    OnTimerStart(){};
   virtual void    OnTimerEnd(){};
   virtual BOOL    DoOption(){return FALSE;};
   virtual BOOL    DoExtendedOption(){return FALSE;};
   virtual long    GetHelpId(){return 0;};
   virtual CString GetGroup()const {return CString("Generic");};
   virtual CString GetDescriptionText(){ return "CInteractiveInterface";};
   virtual CString GetKey()const{return "DragDropObject";};
   virtual CString GetName()const{return "DragDrop object";};
   virtual CString GetVersion()const{return "1";};
   virtual long    GetContextMenuId(){return 0;};

protected:
        
    static CRect        m_rectPrevBounding; 
    CRect               m_boundingRect; // smallest rect that surrounds all
                                        // of the points in the stroke
                                        // measured in MM_LOMETRIC units
                                        // (0.millimeters, with Y-axis inverted)
    WORD                m_wFlags;       // Boolean flags (see flags below)
   
    enum flags          //  flags
    {
        flagPrevRectValid       = 0x01,         // Previous rectangle valid
        flagVisible             = 0x02,         // object is visible on screen
        flagSelectable          = 0x04,         // can be selected in view 
        flagDraggable           = 0x08,         // can be dragged in view
        flagResizable           = 0x10,         // can be resized
        flagSuspendChildUpdates = 0x20,         // update not needed (not archived)
        flagClearOnUpdate       = 0x40,         // do ERASE on InvalidateRect()
        flag4ResizeHandles      = 0x80,         // only 4 handles on corners when selected
        flagSuspendUpdates      = 0x100,        // don't call UpdateAllViews in SetUpdateNeeded.
        flagNonStandardMove     = 0x200,        // a move doesn't update topleft by offset
        flagNoLayout            = 0x400,        // don't move this object during auto-layout
        flagUserDef1            = 0x800,        // user defined bit, reserved to customers
        flagUnused4             = 0x1000,       // Unused, reserved for future use         
        flagUnused3             = 0x2000,       // Unused, reserved for future use         
        flagUnused2             = 0x4000,       // Unused, reserved for future use         
        flagUnused1             = 0x8000        // Unused, reserved for future use         
    }; 

   DragDropObject*          m_pParentArea;
   DragDropDocument*        m_pDocument;  
   DragDropView*            m_pView;      

   virtual void GeometryChange(CRect* pRectPrevious);      // called when object moved/resized
   virtual void GeometryChangeChild(DragDropObject* pChildObject);
   virtual void GeometryUpdated() {return;}

public:
   virtual DragDropObject* Clone() const;
   virtual BOOL paint(CDC* pDC);
   virtual BOOL HandleResizing(CClientDC* pDC, DragDropView* pView, CRect* pRect, CPoint pPoint, 
                              int nHandleHit, int nEvent, 
                              int nMinWidth = MIN_OBJECT_ON_RESIZE, int nMinHeight = MIN_OBJECT_ON_RESIZE);                                                          
   virtual DragDropObject* RedirectSelection() {return this;};
   virtual void GainedSelection(DragDropSelection* pSelection);                                                          
   virtual void LostSelection(DragDropSelection* pSelection);
   virtual void HideSelectionHandles(DragDropSelection* pSelection);
   virtual void ShowSelectionHandles(DragDropSelection* pSelection);

   virtual BOOL DoUncapturedMouseMove(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL DoMouseOverStart(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL DoMouseOver(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL DoMouseOverEnd(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL DoLButtonClick(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL DoLButtonDblClk(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);

   // support for doing buttons

   virtual BOOL DoLButtonDown(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL DoButtonDownLeave(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL DoButtonDownEnter(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL DoLButtonUp(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);

   virtual void DoCalculate() {}

protected:
   virtual void SuspendChildUpdates() {SetSuspendChildUpdates(TRUE);}
   virtual void ResumeChildUpdates() {SetSuspendChildUpdates(FALSE);}
   virtual void DrawXorRect(CDC* pDC);   

private:
   virtual void Init(CRect* pRect);

   friend class DragDropDocument;   
   friend class DragDropView;       
   friend class DragDropArea;      
   DECLARE_SERIAL(DragDropObject)
};

#endif 
