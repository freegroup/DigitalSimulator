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
#include "SnapDialog.h"

BEGIN_MESSAGE_MAP(CSnapDialog, CBitmapDialog)
	//{{AFX_MSG_MAP(CSnapDialog)
		// NOTE: the ClassWizard will add message map macros here
		ON_WM_WINDOWPOSCHANGING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
CSnapDialog::CSnapDialog(UINT IDD, CWnd* pParent /*=NULL*/)	: inherited(IDD, pParent){
//----------------------------------------------------------------------------

	//{{AFX_DATA_INIT(CSnapDialog)
		// NOTE: the ClassWizard will add member initialization here
	m_nYOffset = 15;
	m_nXOffset = 15;
	//}}AFX_DATA_INIT
}

//----------------------------------------------------------------------------
void CSnapDialog::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSnapDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
void CSnapDialog::OnWindowPosChanging( WINDOWPOS* lpwndpos ){
//----------------------------------------------------------------------------

	CRect	wndRect, trayRect;
	int		leftTaskbar = 0, rightTaskbar = 0, topTaskbar = 0, bottomTaskbar = 0;

	GetWindowRect(&wndRect);

	// Screen resolution
	int screenWidth =	GetSystemMetrics(SM_CXSCREEN); 
	int screenHeight =	GetSystemMetrics(SM_CYSCREEN);

	// Find the taskbar
	CWnd* pWnd = FindWindow(_T("Shell_TrayWnd"), _T(""));
	pWnd->GetWindowRect(&trayRect);

	int wndWidth = wndRect.right - wndRect.left;
	int wndHeight = wndRect.bottom - wndRect.top;

	if(trayRect.top <= 0 && trayRect.left <= 0 && trayRect.right >= screenWidth) {
		// top taskbar
		topTaskbar = trayRect.bottom - trayRect.top;
	}
	else if(trayRect.top > 0 && trayRect.left <= 0) {
		// bottom taskbar
		bottomTaskbar = trayRect.bottom - trayRect.top;
	}
	else if(trayRect.top <= 0 && trayRect.left > 0) {
		// right taskbar
		rightTaskbar = trayRect.right - trayRect.left;
	}
	else {
		// left taskbar
		leftTaskbar = trayRect.right - trayRect.left;
	}

	// Snap to screen border
	// Left border
	if(lpwndpos->x >= -m_nXOffset + leftTaskbar && lpwndpos->x <= leftTaskbar + m_nXOffset) {
		lpwndpos->x = leftTaskbar;
	}

	// Top border
	if(lpwndpos->y >= -m_nYOffset && lpwndpos->y <= topTaskbar + m_nYOffset) {
		lpwndpos->y = topTaskbar;
	}

	// Right border
	if(lpwndpos->x + wndWidth <= screenWidth - rightTaskbar + m_nXOffset && lpwndpos->x + wndWidth >= screenWidth - rightTaskbar - m_nXOffset) {
		lpwndpos->x = screenWidth - rightTaskbar - wndWidth;
	}

	// Bottom border
	if( lpwndpos->y + wndHeight <= screenHeight - bottomTaskbar + m_nYOffset && lpwndpos->y + wndHeight >= screenHeight - bottomTaskbar - m_nYOffset) {
		lpwndpos->y = screenHeight - bottomTaskbar - wndHeight;
	}
}
