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

#ifndef _DRAGDROPVIEW_H_
#define _DRAGDROPVIEW_H_

#include "DragDrop.h" 
#include "DragDropDocument.h"
#include "DragDropobject.h"
#include "DragDropLink.h"
#include "DragDropSelection.h"

#define IDC_TEXTEDIT 999


class DragDropTextEdit;
class DragDropRectangle;
class DragDropPort;


class DragDropView : public CScrollView{
    typedef CScrollView inherited ;
    
public:
    virtual DragDropDocument* GetDocument();


    virtual CSize  GetPixelSize() {return m_sizePixelLP;}
    virtual void   OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL); //ISO (made public for DragDropText. right thing?)
    virtual void   PopToTop();
    
protected:
    DragDropView();
    virtual ~DragDropView();
    CObList m_oblistObjects;            // Public?
    float   m_fdevPixelsPerUnit_x ; //ISO Number of device pixels in a centimeter 
    float   m_fdevPixelsPerUnit_y ;  
    int     m_logPixelsPerUnit ;      //ISO Number of logical pixels per centimeter    
    int     m_iScale ;                //ISO Scale factor as a percent

    DragDropObject*  m_pCurrentObject;     // Current Object
    DragDropObject*  m_pMouseOverObject;   // Current Object under the mouse
    CPoint      m_pointMouseDown;   // pt where mouse button went down
    CPoint      m_pointMouseMove;   // pt where mouse button last moved
    CSize       m_offsetMove;       // offset from mouse down point to object's top left.
    DragDropSelection* m_pSelection;     // selected Objects

    DragDropLink*    m_pTempLink;        // temporary Link for Link creation drawing
    DragDropPort*    m_pTempPortMM;      // temporary Port for Link creation drawing-mouse move
    DragDropPort*    m_pTempPortMD;      // temporary Port for Link creation drawing-mouse down
    DragDropPort*    m_pLastSnapToPort;  // Port that Link "snapped" to on last mouse move 
    CRect            m_rectXOR;          // temporary rect for XOR drawing

    int m_handlesHit;        // enumerated constants ("int" because we can't extend enum's in derived classes...)
    
    enum PointerMode {
      PointerModeNone, 
      PointerModeSelection, 
      PointerModeResize, 
      PointerModeMove,
      PointerModeClone,
      PointerModeCreateLink,
      PointerModeCreateLinkFrom, 
      PointerModeDragBoxSelection, 
      PointerModeObjectSpecific,
      PointerModeButton,
    }m_pointermode; 

    BOOL        m_bInitialized;     // OnInitialUpdate has been called
    int         m_nClearHandleCount;        

    // printing attributes
    int         m_nPagesWide;   
    int         m_nPagesHigh;
    int         m_nWidthLoMM;
    int         m_nHeightLoMM;
    BOOL        m_bPrintPreview;

    // drag -n- drop attributes
    BOOL               m_bDirtyDropView;
    BOOL               m_bFirstMouseMove;
    DragDropView      *m_pViewDirty;
    DragDropRectangle *m_pDragObject;
    CPoint             m_PtDirty;
    UINT               m_nLButtonDownFlags;

    // text editing hooks
    DragDropTextEdit  *m_pEditText;
    BOOL               m_bAbortInputAction;
    
    // Graphics performance knobs
    DWORD              m_nGdiBatchLimit;

    DragDropHandle    *m_pHandleRight;
    DragDropHandle    *m_pHandleBottom;
    DragDropRectangle *m_pGrayRight;
    DragDropRectangle *m_pGrayBottom;
	 HCURSOR		        m_hMagnifyCursor;

    CSize       m_sizePixelLP;
    
    BOOL        m_bInsideButton;
    

    class SaveRestoreDC{
    protected:
       int m_context;
       CDC* m_pDC;
    public:
       SaveRestoreDC(CDC* pDC){
         m_context = pDC->SaveDC();
         m_pDC     = pDC;
       };
       ~SaveRestoreDC(){
          m_pDC->RestoreDC(m_context);
       };
    };

public:

    virtual POSITION AddObjectAtHead(DragDropObject* pObject); 
    virtual POSITION AddObjectAtTail(DragDropObject* pObject);

    virtual POSITION GetFirstObjectPos() const;
    virtual DragDropObject* GetNextObject(POSITION& pos) const;

    virtual void RemoveObject(DragDropObject* pObject);
      
    virtual DragDropObject* PickInView(CClientDC* pDC, CPoint ptToCheckLP, BOOL bSelectableOnly);

protected:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view 
    virtual void DoDrawBackgroundDecoration(CDC* pDC);  // overridden to draw things like grids 
    virtual void DoDrawDocumentObjects(DragDropDocument* pDocument, CRect rectClip, CDC* pDrawDC);
    virtual void DoDrawViewObjects(CRect rectClip, CDC* pDrawDC);
    virtual void OnInitialUpdate();

    virtual void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
    virtual DragDropObject* DoPickInDocument(CClientDC* pDC, CPoint ptToCheckLP, BOOL bSelectableOnly);

    // Activation
    virtual void OnActivateView(BOOL bActivate, CView* pActivateView,
                    CView* pDeactiveView);
    virtual void DragDropView::OnClickOnBackground(CPoint point);

// Implementation

public:
    void InitializeView() {OnInitialUpdate();}
    virtual DragDropSelection* GetSelection()  const; 
    virtual BOOL DropObjectAllowed(DragDropView* pSourceView, DragDropObject* pSourceObject, CPoint
		pPoint) {return TRUE;}
    virtual BOOL DropObject(DragDropView* pSourceView, DragDropObject* pSourceObject, CPoint pPoint, UINT nFlags);
    virtual BOOL DropObjectAnimateDraw(DragDropView* pSourceView, DragDropObject* pSourceObject, CPoint pPoint);
    virtual BOOL DropObjectAnimateClear(DragDropView* pSourceView, DragDropObject* pSourceObject, CPoint pPoint);

    virtual void DoDragSelection(CClientDC* pDC, CPoint pointDP, CPoint point, int nEvent);
    virtual void DoDropSelection(CClientDC* pDC, CPoint pointDP, CPoint point, int nEvent);
    
    virtual void DropFail();

    virtual void ClearSelection();
    void ScrollToPoint(CPoint pointLP);
    virtual void ScrollToObject(DragDropObject* pObject);
    
    virtual void CloseView();

    virtual void SetScale(int percent, float clientRectFactor = 0.8) ;    //ISO
    virtual void SetScaleToFit(int nMinScale = 6);
    virtual void SetScaleToShowWholeDoc();
    virtual int GetScale() {return m_iScale;}  
    virtual BOOL IsPrintPreview() {return m_bPrintPreview;}

    virtual void    ZoomToRect(CRect* rectZoom);
    virtual void    ZoomToSelection();

protected:   
    // Handy helper drawing routines

    virtual void DrawXorRect(CClientDC* pDC, CRect* pRect);
    virtual void DrawXorBox(CClientDC* pDC, CPoint pt1, CPoint pt2, CRect* pRectAspect=NULL);
    virtual void AutoScroll(CPoint pointDP);
    
    // Selection Support

    virtual DragDropPort* PickNearestPort(CClientDC* pDC, CPoint pPoint, int nTolerance = -1);
    virtual void DoSelectionInBox (CRect* rect);   
    virtual void DoMoveSelection(CClientDC* pDC, CPoint pointDP, CPoint pointLP, int nEvent,
                                    BOOL bAutoScroll = TRUE);
      

    virtual void MoveSelection(CSize sizeOffset, CPoint pointLP, int nEvent);
    virtual void CancelMoveSelection() {}
    virtual void GeometryUpdatedSelection();
    virtual void RestoreSelectionHandles(); // restore handles after drag
    virtual void ClearSelectionHandles();   // erase handles for drag

    
    virtual void HandleResizing(CClientDC*, CPoint pPoint, int nEvent);
    virtual DragDropHandle* SelectedHandleTest(CClientDC* pDC, CPoint pPoint);
    
    virtual DragDropPort* PortTest(CClientDC* pDC, CPoint pPoint);

    // Link Creation hooks

    virtual void SetValidPorts();
    virtual void SetValidPorts2();
    virtual BOOL ValidSourcePort(DragDropPort* pFrom) {return TRUE;}  // for override by smarter subclass
    virtual BOOL ValidDestinationPort(DragDropPort* pFrom) {return TRUE;}  // for override by smarter subclass
    virtual BOOL ValidLink(DragDropPort* pFrom, DragDropPort* pTo) {return TRUE;} // for override by smarter subclass
    virtual DragDropLink* NewLink(DragDropPort* pFrom, DragDropPort* pTo);
    virtual void NoNewLink(DragDropPort* pFrom, DragDropPort* pInvalidTo); // for override

    // input handling functions

    virtual void DoLButtonDown(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC);
    virtual void DoLButtonUp(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC);
    virtual void DoMouseMove(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC);
    virtual BOOL DoLButtonDblClk(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC);

    virtual void DoUncapturedMouseMove(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC);
//    virtual void DoSize(UINT nType, int cx, int cy);

    virtual BOOL CancelActionInProgress(UINT nFlags, CPoint pointDP);
    
    // cleanup functions

    virtual void DeleteContents();
    
    // Printing support
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


    virtual void ViewHandles();


    int         m_nNewControlID;  


    DWORD       m_dwLastTick;
    int         m_nScrollDelay;
    UINT        m_nTimerID;

public:
    // text editing hooks

    virtual void SetEditControl(DragDropTextEdit* pEdit);
    virtual DragDropTextEdit* EditControl() {return m_pEditText;}
    virtual int GetTextControlId() {return IDC_TEXTEDIT;}
    virtual BOOL IsEditingTextControl() {return (m_pEditText != NULL);}
    virtual void DoEndEdit();

    virtual int  GetNewControlID();
    virtual void SetBaseControlID(int nBase);

    // coordinate convenience functions
    
    virtual void GetClientRectLP(CRect* pRect);
	 virtual void GetClientRectLPZero(CRect* pRect);
    virtual void GetRectDP(CRect* pRect);
    virtual void ClientToDoc(CPoint &pt);
    virtual void DocToClient(CPoint &pt);
    virtual void ClientToDoc(CRect* rect);
    virtual void DocToClient(CRect* rect);
    virtual void ClientToDoc(CSize &s);
    virtual void DocToClient(CSize &s);


    virtual BOOL StartNewLink(DragDropPort* pPort, CPoint pointLP);

protected:

	// Handle new doc size
	virtual void NewDocSize();


    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
        AFX_CMDHANDLERINFO* pHandlerInfo);

   //{{AFX_MSG(DragDropView)
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point); 
   afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
   afx_msg void OnSysColorChange();
   afx_msg LRESULT OnDoRefresh(WPARAM wParam, LPARAM lParam);  // user message
//   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnTimer(UINT nIDEvent);
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);  
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   //}}AFX_MSG
   afx_msg void OnEnUpdate();
   friend class DragDropHandle;    
   friend class DragDropObject;
   friend class DragDropText;
   DECLARE_DYNCREATE(DragDropView)
   DECLARE_MESSAGE_MAP()
};

inline DragDropDocument* DragDropView::GetDocument()
   { return(DragDropDocument*) m_pDocument; }

#endif
