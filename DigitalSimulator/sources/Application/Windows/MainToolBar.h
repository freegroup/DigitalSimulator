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

#if !defined(_TOOLBAREX_H_)
#define _TOOLBAREX_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolBarEx.h : header file
//
#include <afxtempl.h>
////////////////////////////////////////////////////////////////////////////
// I got some pieces of this code from  MSJ Articles of Paul Dilascia
//


/////////////////////////////////////////////////////////////////////////////
// CToolBarEx window

#define ID_CUSTOMIZE_BAR 0xFF



class CMainToolBar : public CToolBar
{
   typedef CToolBar inherited;

protected:
	// Inner structs
		class  CToolBarButtonInfo
	{
	public:
		TBBUTTON		 tbButton;		// information regarding the button
		CString			 btnText;		// text for the button
	};

	// One of these for each drop-down button
	class CDropDownButtonInfo
	{
	public:
		CDropDownButtonInfo * pNext;
		UINT			idButton;		// command ID of button
		UINT			idMenu;			// popup menu to display
	} ;

// Construction
public:
	CMainToolBar();

// Attributes
public:

// Operations
public:

	// this member function is called to insert a control into the toolbar
	// and returns a pointer to the newly inserted control
	//
	CWnd* InsertControl(CRuntimeClass* pClass,LPCTSTR lpszWindowName,CRect& rect,UINT nID,DWORD dwStyle );
	CWnd* InsertControl(CWnd* pCtrl,CRect& rect,UINT nID);
	
	// call to add drop-down buttons
	BOOL AddDropDownButton(UINT nIDButton,UINT nIDMenu,BOOL bArrow=TRUE);
	
	// state functions
	void SaveState();
	void RestoreState();

	//Call this function to set the customization, after you have done the changes to the toolbar.
	void SetToolBarInfoForCustomization();



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainToolBar();
	BOOL		m_bShowDropdownArrowWhenVertical;		// true to display a drop arrow when docked vertical
	BOOL		m_bHideChildWndOnVertical;	// Hide the windows when docked vertical			

	virtual void OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);


	// Generated message map functions
protected:
	void PositionControls();
	CObList*			m_pControls;			// CObject pointer list which contains controls added to the toolbar
	CDropDownButtonInfo*		m_pDropButtons;			// list of dropdown button/menu pairs
	static int			m_nBarNumber;			// used for customization, holds bar number for restoration.
	CString				m_strSubKey;			// used for customization, holds registry subkey name.
	CString				m_strValueName;			// used for customization, holds registry value.
	CArray<CToolBarButtonInfo,CToolBarButtonInfo &> m_ToolBarInfo;


		// Find buttons structure for given ID
	CDropDownButtonInfo * FindDropDownButtonInfo(UINT nID);

	void OnToolBarBtnDropDown(NMHDR* pNMHDR, LRESULT* pRes);
	void OnDropDownButtonInfo(const NMTOOLBAR& nmtb, UINT nID, CRect rc);



	//Chenged Functions
	CSize GetButtonSize(TBBUTTON* pData, int iButton,DWORD dwMode);
	CSize CalcSize(TBBUTTON* pData, int nCount,DWORD dwMode);
	int WrapToolBar(TBBUTTON* pData, int nCount, int nWidth,DWORD dwMode);

	//Copied Functions
	void SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert, DWORD dwMode);
	CSize CalcLayout(DWORD dwMode, int nLength=-1);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);
	void _GetButton(int nIndex, TBBUTTON* pButton) const;
	void _SetButton(int nIndex, TBBUTTON* pButton);



	//{{AFX_MSG(CMainToolBar)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnToolBarQueryDelete(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnToolBarQueryInsert(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnToolBarChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnToolBarBeginAdjust(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnToolBarCustomHelp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnToolBarEndAdjust(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnToolBarGetButtonInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnToolBarReset(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
   
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_TOOLBAREX_H_)
