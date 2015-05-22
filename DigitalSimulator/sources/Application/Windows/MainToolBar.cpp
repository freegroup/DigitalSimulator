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

#include "stdafx.h"
#include "MainToolBar.h"
#include "Application\Debug\LogManager.h"
#include "Application\i18n\ResourceTranslater.h"


int CMainToolBar::m_nBarNumber = 0;


// for determining version of COMCTL32.DLL
#define VERSION_WIN4        MAKELONG(0, 4)
#define VERSION_IE3         MAKELONG(70, 4)
#define VERSION_IE4         MAKELONG(71, 4)
#define VERSION_IE401       MAKELONG(72, 4)
#define VERSION_IE5			 MAKELONG(80, 5)
#define VERSION_IE5_2000    MAKELONG(81, 5)

struct AFX_DLLVERSIONINFO
{
	DWORD cbSize;
	DWORD dwMajorVersion;                   // Major version
	DWORD dwMinorVersion;                   // Minor version
	DWORD dwBuildNumber;                    // Build number
	DWORD dwPlatformID;                     // DLLVER_PLATFORM_*
};

typedef HRESULT (CALLBACK* AFX_DLLGETVERSIONPROC)(AFX_DLLVERSIONINFO *);

static int _ComCtlVersion = -1;

static DWORD AFXAPI _GetComCtlVersion()
{
	PROC_TRACE;

	// return cached version if already determined...
	if (_ComCtlVersion != -1)
		return _ComCtlVersion;
	
	// otherwise determine comctl32.dll version via DllGetVersion
	HINSTANCE hInst = ::GetModuleHandleA("COMCTL32.DLL");
	ASSERT(hInst != NULL);
	AFX_DLLGETVERSIONPROC pfn;
	pfn = (AFX_DLLGETVERSIONPROC)GetProcAddress(hInst, "DllGetVersion");
	DWORD dwVersion = VERSION_WIN4;
	if (pfn != NULL)
	{
		AFX_DLLVERSIONINFO dvi;
		memset(&dvi, 0, sizeof(dvi));
		dvi.cbSize = sizeof(dvi);
		HRESULT hr = (*pfn)(&dvi);
		if (SUCCEEDED(hr))
		{
			ASSERT(dvi.dwMajorVersion <= 0xFFFF);
			ASSERT(dvi.dwMinorVersion <= 0xFFFF);
			dwVersion = MAKELONG(dvi.dwMinorVersion, dvi.dwMajorVersion);
		}
	}
	_ComCtlVersion = dwVersion;
	return dwVersion;
}

CMainToolBar::CMainToolBar()
{
	PROC_TRACE;

   m_pControls		 = NULL;
	m_pDropButtons	 = NULL;		// list of drop-down buttons
	m_bShowDropdownArrowWhenVertical = FALSE;
	m_bHideChildWndOnVertical=TRUE;

	++m_nBarNumber;
	CWinApp  *pApp = AfxGetApp();
	ASSERT_VALID(pApp);
	m_strValueName.Format( _T("ToolBarEx%d"), m_nBarNumber );
	m_strSubKey.Format( _T("Software\\%s\\%s\\Settings"),
		pApp->m_pszRegistryKey, pApp->m_pszProfileName );
}


CMainToolBar::~CMainToolBar()
{
	PROC_TRACE;

   while (m_pDropButtons)
	{
		CDropDownButtonInfo* pnext = m_pDropButtons->pNext;
		delete m_pDropButtons;
		m_pDropButtons = pnext;
	}

	if( m_pControls ) 
	{
		for( POSITION pos = m_pControls->GetHeadPosition() ; pos ; ) 
		{
			delete m_pControls->GetNext(pos);
		}

		delete m_pControls;
	}

}


BEGIN_MESSAGE_MAP(CMainToolBar, CToolBar)
	//{{AFX_MSG_MAP(CToolBar)
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TBN_DROPDOWN,		 OnToolBarBtnDropDown)
	ON_NOTIFY_REFLECT(TBN_BEGINADJUST,	 OnToolBarBeginAdjust)
	ON_NOTIFY_REFLECT(TBN_CUSTHELP,		 OnToolBarCustomHelp)
	ON_NOTIFY_REFLECT(TBN_ENDADJUST,	 OnToolBarEndAdjust)
	ON_NOTIFY_REFLECT(TBN_GETBUTTONINFO, OnToolBarGetButtonInfo)
	ON_NOTIFY_REFLECT(TBN_QUERYDELETE,	 OnToolBarQueryDelete)
	ON_NOTIFY_REFLECT(TBN_QUERYINSERT,	 OnToolBarQueryInsert)
	ON_NOTIFY_REFLECT(TBN_RESET,		 OnToolBarReset)
	ON_NOTIFY_REFLECT(TBN_TOOLBARCHANGE, OnToolBarChange)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainToolBar message handlers

//////////////////////////////////////////////////////////////////////
// 1999 Kirk Stowell - Inserts a control into the toolbar at the given button id.
//
CWnd* CMainToolBar::InsertControl( CRuntimeClass* pClass, LPCTSTR lpszWindowName, CRect& rect, UINT nID, DWORD dwStyle )
{
	PROC_TRACE;

   CWnd *pCtrl = NULL;
	
		if( pClass->IsDerivedFrom( RUNTIME_CLASS( CComboBox )))	// CComboBox control.
	{
		pCtrl = new CComboBox;

		ASSERT_VALID( pCtrl );

		if(((CComboBox*)pCtrl)->Create( WS_CHILD|WS_VISIBLE|dwStyle, rect, this, nID ) == FALSE )
		{
			delete pCtrl;
			return NULL;
		}
	}
	else if( pClass->IsDerivedFrom( RUNTIME_CLASS( CEdit )))		// CEdit control.
	{
		pCtrl = new CEdit;

		ASSERT_VALID( pCtrl );

		if(((CEdit*)pCtrl)->Create( WS_CHILD|WS_VISIBLE|dwStyle, rect, this, nID ) == FALSE )
		{
			delete pCtrl;
			return NULL;
		}
	}
	else if( pClass->IsDerivedFrom( RUNTIME_CLASS( CButton )))		// CButton control.
	{
		pCtrl = new CButton;

		ASSERT_VALID( pCtrl );

		if(((CButton*)pCtrl)->Create( lpszWindowName, WS_CHILD|WS_VISIBLE|dwStyle, rect, this, nID ) == FALSE )
		{
			delete pCtrl;
			return NULL;
		}
	}
	else if( pClass->IsDerivedFrom( RUNTIME_CLASS( CWnd )))			// CWnd object.
	{
		pCtrl = new CWnd;
		
		ASSERT_VALID( pCtrl );

#ifdef _UNICODE
		TCHAR szClassName[ 256 ];

		MultiByteToWideChar( CP_ACP,
							 MB_PRECOMPOSED,
							 pClass->m_lpszClassName,
							 -1,
							 szClassName,
							 255 );

		if(((CWnd*)pCtrl)->Create( szClassName, lpszWindowName, WS_CHILD|WS_VISIBLE|dwStyle, rect, this, nID ) == FALSE )
		{
			delete pCtrl;
			return NULL;
		}
#else
		if(((CWnd*)pCtrl)->Create( pClass->m_lpszClassName, lpszWindowName, WS_CHILD|WS_VISIBLE|dwStyle, rect, this, nID ) == FALSE )
		{
			delete pCtrl;
			return NULL;
		}
#endif
	}
	else															// An invalid object was passed in
	{
		ASSERT( FALSE );
		return NULL;
	}

	// if our object list has not been allocated, do it now...
	if( m_pControls == NULL )
	{
		m_pControls = new CObList();
		ASSERT( m_pControls );
	}

	// we have to remember this control, so we can delete it later
	m_pControls->AddTail( pCtrl );

	return InsertControl( pCtrl, rect, nID );
}

CWnd* CMainToolBar::InsertControl(CWnd* pCtrl, CRect & rect, UINT nID)
{
	PROC_TRACE;

   ASSERT_VALID( pCtrl );

	// make sure the id is valid, and set the button 
	// style for a seperator.
	int nIndex = CommandToIndex( nID ) ;
	if (nIndex>-1)
	{
		ASSERT( nIndex >= 0 );
		SetButtonInfo( nIndex, nID, TBBS_SEPARATOR, rect.Width());
		// insert the control into the toolbar.
		GetItemRect( nIndex, &rect );
		pCtrl->SetWindowPos(0, rect.left, rect.top, 0, 0,
			SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOCOPYBITS );
		pCtrl->SetFont( GetFont( ));

		BOOL bVert = (m_dwStyle & CBRS_ORIENT_VERT) != 0;

		if (bVert && m_bHideChildWndOnVertical)
		{
		   	int nState=GetToolBarCtrl().GetState(nIndex);
		   	GetToolBarCtrl().SetState(nID,(nState | TBSTATE_HIDDEN));
			pCtrl->ShowWindow( SW_HIDE );
		}
		else
		{
		   	int nState=GetToolBarCtrl().GetState(nIndex);
		   	GetToolBarCtrl().SetState(nIndex,(nState & ~TBSTATE_HIDDEN));
			pCtrl->ShowWindow( SW_SHOW );
		}

	}
	else
	{
		pCtrl->ShowWindow( SW_HIDE);
	}
	return pCtrl;
}

BOOL CMainToolBar::AddDropDownButton(UINT nIDButton, UINT nIDMenu,BOOL bArrow)
{
	PROC_TRACE;

   ASSERT_VALID(this);
	
	CDropDownButtonInfo* pb = FindDropDownButtonInfo(nIDButton);

	if (!pb) 
	{
		pb = new CDropDownButtonInfo;
		ASSERT(pb);
		pb->pNext = m_pDropButtons;
		m_pDropButtons = pb;
	}

	pb->idButton = nIDButton;
	pb->idMenu   = nIDMenu;
	
	int iButton = CommandToIndex(nIDButton);
	
	DWORD dwStyle = GetButtonStyle(iButton);
	dwStyle |= TBSTYLE_DROPDOWN;
	SetButtonStyle(iButton, dwStyle);								

	if (bArrow)
		GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);

	
	return TRUE;
}

CMainToolBar::CDropDownButtonInfo* CMainToolBar::FindDropDownButtonInfo(UINT nID)
{
	PROC_TRACE;

   for (CDropDownButtonInfo* pb = m_pDropButtons; pb; pb = pb->pNext) 
	{
		if (pb->idButton == nID)
			return pb;
	}
	return NULL;
}

void CMainToolBar::OnToolBarBtnDropDown(NMHDR* pNMHDR, LRESULT* pRes)
{
	PROC_TRACE;

   UNUSED_ALWAYS( pRes );
	
	const NMTOOLBAR& nmtb = *(NMTOOLBAR*)pNMHDR;
	
	// get location of button
	CRect rc;
	GetToolBarCtrl().GetRect(nmtb.iItem, rc);
	ClientToScreen(&rc);
	
	// call virtual function to display dropdown menu
	OnDropDownButtonInfo(nmtb, nmtb.iItem, rc);
}

void CMainToolBar::OnDropDownButtonInfo(const NMTOOLBAR& nmtb, UINT nID, CRect rc)
{
	PROC_TRACE;

   UNUSED_ALWAYS( nID );

	CDropDownButtonInfo* pb = FindDropDownButtonInfo(nmtb.iItem);
	if (pb && pb->idMenu) {
		
		// load and display popup menu
		CMenu menu;
		VERIFY(menu.LoadMenu(pb->idMenu));
		CMenu* pPopup = (CMenu*)menu.GetSubMenu(0);
		ASSERT(pPopup);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,
			rc.left, rc.bottom, AfxGetMainWnd(), &rc);
	}
}


// This function saves the state (visible buttons, toolbar position, etc.)
// of the toolbar, using the registry key provided to the Create(...) function.
void CMainToolBar::SaveState()
{
	PROC_TRACE;

   // if there is an associated registry subkey
	if (m_strSubKey.GetLength())
	{
		// save the toolbar state to the registry
		GetToolBarCtrl().SaveState( HKEY_CURRENT_USER, m_strSubKey, m_strValueName );
	}
}

// This function restores the state (visible buttons, toolbar position, etc.)
// of the toolbar, using the registry key provided to the Create(...) function.
void CMainToolBar::RestoreState()
{
	PROC_TRACE;

	// if there is an associated registry subkey
	if (m_strSubKey.GetLength())
	{
		// restore the toolbar state from the registry
		GetToolBarCtrl().RestoreState( HKEY_CURRENT_USER, m_strSubKey, m_strValueName );
	}

	//position the child windows
	PositionControls();
}

// This function is called when the user begins dragging a toolbar
// button or when the customization dialog is being populated with
// toolbar information.  Basically, *pResult should be populated with
// your answer to the question, "is the user allowed to delete this
// button?".
void CMainToolBar::OnToolBarQueryDelete(NMHDR *pNMHDR, LRESULT *pResult)
{
	PROC_TRACE;

   UNUSED_ALWAYS( pNMHDR );

	*pResult = TRUE;

}

// This function is called when the user begins dragging a toolbar
// button or when the customization dialog is being populated with
// toolbar information.  Basically, *pResult should be populated with
// your answer to the question, "is the user allowed to insert a
// button to the left of this one?".
void CMainToolBar::OnToolBarQueryInsert(NMHDR *pNMHDR, LRESULT *pResult)
{
	PROC_TRACE;

   UNUSED_ALWAYS( pNMHDR );

			*pResult = TRUE;

}

// This function is called whenever the user makes a change to the
// layout of the toolbar.  Calling the mainframe's RecalcLayout forces
// the toolbar to repaint itself.
void CMainToolBar::OnToolBarChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	PROC_TRACE;

   UNUSED_ALWAYS( pNMHDR );
	UNUSED_ALWAYS( pResult );


	PositionControls();
	// force the frame window to recalculate the size
	GetParentFrame()->RecalcLayout();
	OnIdleUpdateCmdUI(TRUE, 0L);

}


// This function is called when the user initially calls up the toolbar
// customization dialog box.
void CMainToolBar::OnToolBarBeginAdjust(NMHDR *pNMHDR, LRESULT *pResult)
{
	PROC_TRACE;

   UNUSED_ALWAYS( pNMHDR );
	UNUSED_ALWAYS( pResult );
}

// This function is called when the user clicks on the help button on the
// toolbar customization dialog box.
void CMainToolBar::OnToolBarCustomHelp(NMHDR *pNMHDR, LRESULT *pResult)
{
	PROC_TRACE;

	UNUSED_ALWAYS( pNMHDR );
	UNUSED_ALWAYS( pResult );

	TRACE(_T("Help on Customize Toolbar called.\n"));
}

// This function is called when the user dismisses the toolbar customization
// dialog box.
void CMainToolBar::OnToolBarEndAdjust(NMHDR *pNMHDR, LRESULT *pResult)
{
	PROC_TRACE;

	UNUSED_ALWAYS( pNMHDR );
	UNUSED_ALWAYS( pResult );

	// save the state of the toolbar for reinitialization
	SaveState();
}

// This function is called to populate the toolbar customization dialog box
// with information regarding all of the possible toolbar buttons.
void CMainToolBar::OnToolBarGetButtonInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	PROC_TRACE;

	UNUSED_ALWAYS( pResult );

	TBNOTIFY* tbStruct;		// data needed by customize dialog box

	// init the pointer
	tbStruct = (TBNOTIFY *)pNMHDR;

	// if the index is valid
	if ((0 <= tbStruct->iItem) && (tbStruct->iItem < m_ToolBarInfo.GetSize()))
	{
		// copy the stored button structure
		tbStruct->tbButton = m_ToolBarInfo[tbStruct->iItem].tbButton;

		if (GetToolBarCtrl().IsButtonHidden(tbStruct->tbButton.idCommand))
				*pResult = FALSE;



		// copy the text for the button label in the dialog
		strcpy(tbStruct->pszText, m_ToolBarInfo[tbStruct->iItem].btnText);

		// indicate valid data was sent
		*pResult = TRUE;
	}

	// else there is no button for this index
	else
	{
		*pResult = FALSE;
	}
}

// This function is called when the user clicks on the reset button on the
// toolbar customization dialog box.
void CMainToolBar::OnToolBarReset(NMHDR *pNMHDR, LRESULT *pResult)
{
	PROC_TRACE;

	UNUSED_ALWAYS( pNMHDR );
	UNUSED_ALWAYS( pResult );

	// restore the toolbar to the way it was before entering customization
	RestoreState();

	GetParentFrame()->RecalcLayout();
	OnIdleUpdateCmdUI(TRUE, 0L);
	*pResult = TRUE;

}


void CMainToolBar::OnRButtonDown(UINT nFlags, CPoint point) 
{
	PROC_TRACE;

	if( GetToolBarCtrl().GetButtonCount() && m_ToolBarInfo.GetSize())
	{
		CPoint pt( point );
		ClientToScreen( &pt );
		
		// load and display popup menu
		CMenu popupMenu;
		VERIFY(popupMenu.CreatePopupMenu());

		popupMenu.InsertMenu(0, MF_BYPOSITION, ID_CUSTOMIZE_BAR, _T(TRANSLATE("MENU.POPUP.TOOLBAR.CUSTOMIZE")));

		int nResult = popupMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL|TPM_RETURNCMD,pt.x, pt.y, this );
	
		if( nResult == ID_CUSTOMIZE_BAR )
		{
			// open the customization dialog.
			GetToolBarCtrl().Customize();
		}
	}

	else 
	{
		inherited::OnRButtonDown(nFlags, point);
	}
}


void CMainToolBar::SetToolBarInfoForCustomization()
{
	PROC_TRACE;

	 m_ToolBarInfo.RemoveAll();

	 for (int i=0;i<GetToolBarCtrl().GetButtonCount();i++)
	 {
		CToolBarButtonInfo tbButtonInfo;

		GetToolBarCtrl().GetButton(i,&tbButtonInfo.tbButton);
		CString str;
		str.LoadString(tbButtonInfo.tbButton.idCommand);

		int nPos= str.ReverseFind(_T('\n'));
		tbButtonInfo.btnText=str.Right(str.GetLength()-nPos-1);
		 

		m_ToolBarInfo.Add(tbButtonInfo);

	 }

	ModifyStyle(0, CCS_ADJUSTABLE);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Overrides 

int CMainToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	PROC_TRACE;

	if (inherited::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	_GetComCtlVersion();
	ASSERT(_ComCtlVersion>0);


	return 0;
}


void CMainToolBar::OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle)
{
	PROC_TRACE;

	inherited::OnBarStyleChange(dwOldStyle,dwNewStyle);

	PositionControls();
}


void CMainToolBar::PositionControls()
{
	PROC_TRACE;

		//move child windows to correct postion
	BOOL bReCalc=FALSE;
	BOOL bVert = (m_dwStyle & CBRS_ORIENT_VERT) != 0;


	// now we do the position & size in two pass
	
	//Firstly set the size of buttons
	CWnd *pWnd = GetWindow(GW_CHILD);
	while(pWnd)
	{
	  ASSERT_VALID(pWnd);

	  int id =pWnd->GetDlgCtrlID();
	  CRect rt;
	  pWnd->GetWindowRect(rt);

	  ///////////////////////////
	  int nIndex = CommandToIndex( id ) ;
	  if (nIndex>-1)
	  {
		ASSERT( nIndex >= 0 );
		SetButtonInfo( nIndex, id, TBBS_SEPARATOR, rt.Width());

		if (bVert && m_bHideChildWndOnVertical)
		{
		   	int nState=GetToolBarCtrl().GetState(nIndex);
		   	GetToolBarCtrl().HideButton(id,TRUE);
		}
		else
		{
	   		int nState=GetToolBarCtrl().GetState(nIndex);
	   		GetToolBarCtrl().HideButton(id,FALSE);
		}

	  }
	  //////////////////////////
	  if (!bReCalc) bReCalc=TRUE;
	  pWnd=pWnd->GetNextWindow();
	}

	
     // second pass
	//Now place the windows
	pWnd = GetWindow(GW_CHILD);
	while(bReCalc && pWnd)
	{
	  ASSERT_VALID(pWnd);

	  int id =pWnd->GetDlgCtrlID();
	  CRect rect;
		  ///////////////////////////
		// make sure the id is valid, and set the button 
		// style for a seperator.
		int nIndex = CommandToIndex( id ) ;
		if (nIndex>-1)
		{
			ASSERT( nIndex >= 0 );
			// insert the control into the toolbar.
			GetItemRect( nIndex, &rect );
			pWnd->SetWindowPos(0, rect.left, rect.top, 0, 0,
				SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOCOPYBITS );
			pWnd->SetFont( GetFont( ));


			if (bVert && m_bHideChildWndOnVertical)
				pWnd->ShowWindow( SW_HIDE );
			else
				pWnd->ShowWindow( SW_SHOW );

		}
		else
		{
			pWnd->ShowWindow( SW_HIDE);
		}
	  //////////////////////////
	  pWnd=pWnd->GetNextWindow();
	}


	if (bReCalc)
	{
		GetToolBarCtrl().AutoSize();
		m_bDelayedButtonLayout=TRUE;
	}
}


CSize CMainToolBar::GetButtonSize(TBBUTTON* pData, int iButton, DWORD dwMode)
{
	PROC_TRACE;

	ASSERT(_ComCtlVersion > 0);

	// Get the actual size of the button, not what's in m_sizeButton.
	// Make sure to do SendMessage instead of calling MFC's GetItemRect,
	// which has all sorts of bad side-effects! (Go ahead, take a look at it.)
	// 
	CRect rc;
	SendMessage(TB_GETITEMRECT, iButton, (LPARAM)&rc);
	CSize sz = rc.Size();

	// do not allow sepearot to be greater than Button height ( Have to check this)
	sz.cy = min(sz.cy ,HIWORD(GetToolBarCtrl().GetButtonSize()));
	DWORD dwStyle = pData[iButton].fsStyle;
	BOOL bVertDocked=	(!(dwMode&LM_HORZ) && !(dwMode&LM_STRETCH) ) ;


	// special cas  for custom controls
	if (m_bHideChildWndOnVertical)
	{
		if ((dwStyle & TBSTYLE_SEP) && 
				(pData[iButton].idCommand!=0))
		{

			if (bVertDocked)
			{
				sz.cx=sz.cy=0;
			}
			else
			{
		  		 // we will get 0,0 on hidden things
				if (GetToolBarCtrl().IsButtonHidden(pData[iButton].idCommand))
				{
				   CWnd * pWnd =GetDlgItem(pData[iButton].idCommand);

					ASSERT_VALID(pWnd);
					CRect rt;
					pWnd->GetWindowRect(rt);
					sz=rt.Size();
				}

			}
		}
	}  
		////////////////
	// Now must do special case for various versions of comctl32.dll,
	//
	if ((pData[iButton].fsState & TBSTATE_WRAP)) 
	{
		if (dwStyle & TBSTYLE_SEP) 
		{
			CWnd *pWnd =GetDlgItem(pData[iButton].idCommand);

			// Check seperator is child window
			if (!pWnd)
			{
				// this is the last separator in the row (eg vertically docked)
				// fudge the height, and ignore the width. TB_GETITEMRECT will return
				// size = (8 x 22) even for a separator in vertical toolbar
				//
				if (_ComCtlVersion <= VERSION_IE3)
					sz.cy -= 3;		// empircally good fudge factor
				else if (_ComCtlVersion != VERSION_IE4)
					sz.cy = sz.cx;
			
				sz.cx = 0;			// separator takes no width if it's the last one
			}
			else
			{
			  // Do not set value in case of the child window
			  //WE should never get here 
			  ASSERT_VALID(pWnd);
			  ASSERT(FALSE);
			}

		} 

	}
	 // drop down arrow check
	 if ((dwStyle & TBSTYLE_DROPDOWN) && 
		  (bVertDocked) &&	
		   !m_bShowDropdownArrowWhenVertical ) 
	 {
		// ignore width of dropdown
		sz.cx = sz.cy;
	 }








	return sz;
}



////////////////////////////////////////////////////////////

#define CX_OVERLAP  0

CSize CMainToolBar::CalcSize(TBBUTTON* pData, int nCount,DWORD dwMode)
{
	PROC_TRACE;

	ASSERT(pData != NULL && nCount > 0);

	CPoint cur(0,0);
	CSize sizeResult(0,0);
	int cyTallestOnRow = 0;
	int nButtons=0;


	for (int i = 0; i < nCount; i++)
	{

		// also calculate for hidden custom controls
		if (  (pData[i].fsState & TBSTATE_HIDDEN)  &&
			!((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand!=0)))
			continue;

		// Load actual size of button into a local variable
		//
		CSize m_sizeButton = GetButtonSize(pData, i,dwMode);


		// I also changed the logic below to be more correct.
		cyTallestOnRow = max(cyTallestOnRow, m_sizeButton.cy);
		sizeResult.cx = max(cur.x + m_sizeButton.cx, sizeResult.cx);
		sizeResult.cy = max(cur.y + m_sizeButton.cy, sizeResult.cy);

		cur.x += m_sizeButton.cx - CX_OVERLAP;
		if (!(pData[i].fsState & TBSTATE_HIDDEN)) nButtons++;

		if (pData[i].fsState & TBSTATE_WRAP)
		{
			//only seperator is present
			if ((nButtons==1) && (pData[i].fsStyle & TBSTYLE_SEP))
			{
				cyTallestOnRow = HIWORD(GetToolBarCtrl().GetButtonSize());
			}

			cur.x = 0;
			cur.y += cyTallestOnRow;
			cyTallestOnRow = 0;
			if (pData[i].fsStyle & TBSTYLE_SEP)
				cur.y += m_sizeButton.cy;
			 nButtons=0;
		}

	}
	return sizeResult;
}

int CMainToolBar::WrapToolBar(TBBUTTON* pData, int nCount, int nWidth, DWORD dwMode)
{
	PROC_TRACE;

	ASSERT(pData != NULL && nCount > 0);

	int nResult = 0;
	int x = 0;
	for (int i = 0; i < nCount; i++)
	{
		pData[i].fsState &= ~TBSTATE_WRAP;

		// also calculate for hidden custom controls
		if (  (pData[i].fsState & TBSTATE_HIDDEN)  &&
			!((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand!=0)))
			continue;

		int dx, dxNext;

		// Load actual size of button into a local variable
		CSize m_sizeButton = GetButtonSize(pData, i,dwMode);

		dx = m_sizeButton.cx;
		dxNext = dx - CX_OVERLAP;

		if (x + dx > nWidth)
		{
			BOOL bFound = FALSE;
			for (int j = i; j >= 0  &&  !(pData[j].fsState & TBSTATE_WRAP); j--)
			{
				// Find last separator that isn't hidden
				// a separator that has a command ID is not
				// a separator, but a custom control.
				if ((pData[j].fsStyle & TBSTYLE_SEP) &&
					(pData[j].idCommand == 0)
					&&	!(pData[j].fsState & TBSTATE_HIDDEN))
				{
					bFound = TRUE; i = j; x = 0;
					pData[j].fsState |= TBSTATE_WRAP;
					nResult++;
					break;
				}
			}
			if (!bFound)
			{
				for (int j = i - 1; j >= 0 && !(pData[j].fsState & TBSTATE_WRAP); j--)
				{
					// Never wrap anything that is hidden,
					// or any custom controls
					if ((pData[j].fsState & TBSTATE_HIDDEN) ||
						((pData[j].fsStyle & TBSTYLE_SEP) &&
						(pData[j].idCommand != 0)))
						continue;

					bFound = TRUE; i = j; x = 0;
					pData[j].fsState |= TBSTATE_WRAP;
					nResult++;
					break;
				}
				if (!bFound)
					x += dxNext;
			}
		}
		else
			x += dxNext;
	}
	return nResult + 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void CMainToolBar::SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert, DWORD dwMode)
{
	PROC_TRACE;

	ASSERT(pData != NULL && nCount > 0);

	if (!bVert)
	{
		int nMin, nMax, nTarget, nCurrent, nMid;

		// Wrap ToolBar as specified
		nMax = nLength;
		nTarget = WrapToolBar(pData, nCount, nMax,dwMode);

		// Wrap ToolBar vertically
		nMin = 0;
		nCurrent = WrapToolBar(pData, nCount, nMin,dwMode);

		if (nCurrent != nTarget)
		{
			while (nMin < nMax)
			{
				nMid = (nMin + nMax) / 2;
				nCurrent = WrapToolBar(pData, nCount, nMid,dwMode);

				if (nCurrent == nTarget)
					nMax = nMid;
				else
				{
					if (nMin == nMid)
					{
						WrapToolBar(pData, nCount, nMax,dwMode);
						break;
					}
					nMin = nMid;
				}
			}
		}
		CSize size = CalcSize(pData, nCount,dwMode);
		WrapToolBar(pData, nCount, size.cx,dwMode);
	}
	else
	{
		CSize sizeMax, sizeMin, sizeMid;

		// Wrap ToolBar vertically
		WrapToolBar(pData, nCount, 0,dwMode);
		sizeMin = CalcSize(pData, nCount,dwMode);

		// Wrap ToolBar horizontally
		WrapToolBar(pData, nCount, 32767,dwMode);
		sizeMax = CalcSize(pData, nCount,dwMode);

		while (sizeMin.cx < sizeMax.cx)
		{
			sizeMid.cx = (sizeMin.cx + sizeMax.cx) / 2;
			WrapToolBar(pData, nCount, sizeMid.cx,dwMode);
			sizeMid = CalcSize(pData, nCount,dwMode);

			if (nLength < sizeMid.cy)
			{
				if (sizeMin == sizeMid)
				{
					WrapToolBar(pData, nCount, sizeMax.cx,dwMode);
					return;
				}
				sizeMin = sizeMid;
			}
			else if (nLength > sizeMid.cy)
				sizeMax = sizeMid;
			else
				return;
		}
	}
}

struct _AFX_CONTROLPOS
{
	int nIndex, nID;
	CRect rectOldPos;
};

CSize CMainToolBar::CalcLayout(DWORD dwMode, int nLength)
{
	PROC_TRACE;

	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));
	if (dwMode & LM_HORZDOCK)
		ASSERT(dwMode & LM_HORZ);

	int nCount;
	TBBUTTON* pData = NULL;
	CSize sizeResult(0,0);

	//BLOCK: Load Buttons
	{
		nCount = DefWindowProc(TB_BUTTONCOUNT, 0, 0);
		if (nCount != 0)
		{
			int i;
			pData = new TBBUTTON[nCount];
			for (i = 0; i < nCount; i++)
				_GetButton(i, &pData[i]);
		}
	}

	if (nCount > 0)
	{
		if (!(m_dwStyle & CBRS_SIZE_FIXED))
		{
			BOOL bDynamic = m_dwStyle & CBRS_SIZE_DYNAMIC;

			if (bDynamic && (dwMode & LM_MRUWIDTH))
				SizeToolBar(pData, nCount, m_nMRUWidth,FALSE,dwMode);
			else if (bDynamic && (dwMode & LM_HORZDOCK))
				SizeToolBar(pData, nCount, 32767,FALSE,dwMode);
			else if (bDynamic && (dwMode & LM_VERTDOCK))
				SizeToolBar(pData, nCount, 0,FALSE,dwMode);
			else if (bDynamic && (nLength != -1))
			{
				CRect rect; rect.SetRectEmpty();
				CalcInsideRect(rect, (dwMode & LM_HORZ));
				BOOL bVert = (dwMode & LM_LENGTHY);
				int nLen = nLength + (bVert ? rect.Height() : rect.Width());

				SizeToolBar(pData, nCount, nLen, bVert,dwMode);
			}
			else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
				SizeToolBar(pData, nCount, m_nMRUWidth,FALSE,dwMode);
			else
				SizeToolBar(pData, nCount, (dwMode & LM_HORZ) ? 32767 : 0,FALSE,dwMode);
		}

		sizeResult = CalcSize(pData, nCount,dwMode);

		if (dwMode & LM_COMMIT)
		{
			_AFX_CONTROLPOS* pControl = NULL;
			int nControlCount = 0;
			BOOL bIsDelayed = m_bDelayedButtonLayout;
			m_bDelayedButtonLayout = FALSE;

			for (int i = 0; i < nCount; i++)
				if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0))
					nControlCount++;

			if (nControlCount > 0)
			{
				pControl = new _AFX_CONTROLPOS[nControlCount];
				nControlCount = 0;

				for(int i = 0; i < nCount; i++)
				{
					if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0))
					{
						pControl[nControlCount].nIndex = i;
						pControl[nControlCount].nID = pData[i].idCommand;

						CRect rect;
						GetItemRect(i, &rect);
						ClientToScreen(&rect);
						pControl[nControlCount].rectOldPos = rect;

						nControlCount++;
					}
				}
			}

			if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
				m_nMRUWidth = sizeResult.cx;
			for (i = 0; i < nCount; i++)
				_SetButton(i, &pData[i]);

			if (nControlCount > 0)
			{
				for (int i = 0; i < nControlCount; i++)
				{
					CWnd* pWnd = GetDlgItem(pControl[i].nID);
					if (pWnd != NULL)
					{
						CRect rect;
						pWnd->GetWindowRect(&rect);
						CPoint pt = rect.TopLeft() - pControl[i].rectOldPos.TopLeft();
						GetItemRect(pControl[i].nIndex, &rect);
						pt = rect.TopLeft() + pt;
						pWnd->SetWindowPos(NULL, pt.x, pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				delete[] pControl;
			}
			m_bDelayedButtonLayout = bIsDelayed;
		}
		delete[] pData;
	}

	//BLOCK: Adjust Margins
	{
		CRect rect; rect.SetRectEmpty();
		CalcInsideRect(rect, (dwMode & LM_HORZ));
		sizeResult.cy -= rect.Height();
		sizeResult.cx -= rect.Width();

		CSize size = CControlBar::CalcFixedLayout((dwMode & LM_STRETCH), (dwMode & LM_HORZ));
		sizeResult.cx = max(sizeResult.cx, size.cx);
		sizeResult.cy = max(sizeResult.cy, size.cy);
	}
	return sizeResult;
}

CSize CMainToolBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	PROC_TRACE;

	DWORD dwMode = bStretch ? LM_STRETCH : 0;
	dwMode |= bHorz ? LM_HORZ : 0;

	return CalcLayout(dwMode);
}

CSize CMainToolBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	PROC_TRACE;

	if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
		((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
	{
		return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZDOCK);
	}
	return CalcLayout(dwMode, nLength);
}

/////////////////////////////////////////////////////////////////////////////
// CMainToolBar attribute access

void CMainToolBar::_GetButton(int nIndex, TBBUTTON* pButton) const
{
	PROC_TRACE;

	CMainToolBar* pBar = (CMainToolBar*)this;
	VERIFY(pBar->DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)pButton));
	// TBSTATE_ENABLED == TBBS_DISABLED so invert it
	pButton->fsState ^= TBSTATE_ENABLED;
}

void CMainToolBar::_SetButton(int nIndex, TBBUTTON* pButton)
{
	PROC_TRACE;

	// get original button state
	TBBUTTON button;
	VERIFY(DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)&button));

	// prepare for old/new button comparsion
	button.bReserved[0] = 0;
	button.bReserved[1] = 0;
	// TBSTATE_ENABLED == TBBS_DISABLED so invert it
	pButton->fsState ^= TBSTATE_ENABLED;
	pButton->bReserved[0] = 0;
	pButton->bReserved[1] = 0;

	// nothing to do if they are the same
	if (memcmp(pButton, &button, sizeof(TBBUTTON)) != 0)
	{
		// don't redraw everything while setting the button
		DWORD dwStyle = GetStyle();
		ModifyStyle(WS_VISIBLE, 0);
		VERIFY(DefWindowProc(TB_DELETEBUTTON, nIndex, 0));
		VERIFY(DefWindowProc(TB_INSERTBUTTON, nIndex, (LPARAM)pButton));
		ModifyStyle(0, dwStyle & WS_VISIBLE);

		// invalidate appropriate parts
		if (((pButton->fsStyle ^ button.fsStyle) & TBSTYLE_SEP) ||
			((pButton->fsStyle & TBSTYLE_SEP) && pButton->iBitmap != button.iBitmap))
		{
			// changing a separator
			Invalidate();
		}
		else
		{
			// invalidate just the button
			CRect rect;
			if (DefWindowProc(TB_GETITEMRECT, nIndex, (LPARAM)&rect))
				InvalidateRect(rect);
		}
	}
}







