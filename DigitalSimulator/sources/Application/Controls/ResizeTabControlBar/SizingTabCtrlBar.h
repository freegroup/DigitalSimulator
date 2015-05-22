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

#ifndef AFX_SIZINGTABCTRLBAR_H__3804CCE3_C325_11D1_91F5_B4375BB20A38__INCLUDED_
#define AFX_SIZINGTABCTRLBAR_H__3804CCE3_C325_11D1_91F5_B4375BB20A38__INCLUDED_

// SizingTabCtrlBar.h : Header-Datei
//
#include <CString>
#include <afxtempl.h>
#include "sizecbar.h"

//using namespace std;

typedef struct
{
	CWnd *pWnd;
	char szLabel[32];
}TCB_ITEM;


class CSizingTabCtrlBar : public CSizingControlBar{
    typedef CSizingControlBar inherited ;
public:
	CSizingTabCtrlBar();
    virtual ~CSizingTabCtrlBar();

	void SetActiveView(int nNewTab);
    void SetActiveView(CView* pView);

    void RemoveView(int nView);
	void RemoveView(CView* pView);

	void RemoveAllViews();

	BOOL AddView(CString lpszLabel, CRuntimeClass *pViewClass,  CCreateContext *pContext = NULL, BOOL withImage=FALSE);

    CView* GetActiveView();
	CView* GetView(int nView);
    void SetLabel(CView* view, CString label);

    virtual BOOL CreateFrame();

    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSizingTabCtrlBar)
	//}}AFX_VIRTUAL

    virtual char * const GetClassName(){return "CSizingTabCtrlBar";};
protected:
   CTabCtrl   m_tabctrl;
	CFrameWnd* m_pFrame;
	int        m_nActiveTab;
	CView*     m_pActiveView;
	CImageList m_images;
	CList <TCB_ITEM *,TCB_ITEM *> m_views;

	//{{AFX_MSG(CSizingTabCtrlBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult) ;
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_SIZINGTABCTRLBAR_H__3804CCE3_C325_11D1_91F5_B4375BB20A38__INCLUDED_
