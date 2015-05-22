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

#if !defined(AFX_OBJECTDOCKINGCONTROLBARVIEW_H__DD910611_9F2C_11D2_8950_004F49031E0C__INCLUDED_)
#define AFX_OBJECTDOCKINGCONTROLBARVIEW_H__DD910611_9F2C_11D2_8950_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "DragDropView.h"
#include "DockingPaletteDoc.h"

class CObjectDockingControlBarView : public DragDropView  {
   typedef DragDropView inherited;

public:
   virtual BOOL ValidLink(DragDropPort* pFrom, DragDropPort* pTo){return FALSE;};
   virtual BOOL ValidSourcePort(DragDropPort* pFrom){return FALSE;};
   virtual BOOL DropObject(DragDropView*, DragDropObject*, CPoint, UINT ){return FALSE;};

   virtual char * const GetClassName(){return "CObjectDockingControlBarView";};

   virtual void TranslateGUI();
protected:
	CObjectDockingControlBarView();
	virtual ~CObjectDockingControlBarView();
    virtual void DoMouseMove(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC){
      DragDropView::DoMouseMove(MK_CONTROL,pointDP,pointLP,pDC);
    }


    static CString s_paletteFileToOpen;

	afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);

	//{{AFX_MSG(CObjectDockingControlBarView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditPalette();
	afx_msg void OnUpdateEditPalette(CCmdUI* pCmdUI);
	afx_msg void OnPaletteAutolayout();
	afx_msg void OnUpdatePaletteAutolayout(CCmdUI* pCmdUI);
	//}}AFX_MSG

    afx_msg void OnContextMenu(CWnd*, CPoint point);

   DECLARE_DYNCREATE(CObjectDockingControlBarView)
   DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_OBJECTDOCKINGCONTROLBARVIEW_H__DD910611_9F2C_11D2_8950_004F49031E0C__INCLUDED_)
