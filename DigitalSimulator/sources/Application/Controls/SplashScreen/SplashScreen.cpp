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
#include "resource.h"  
#include "SplashScreen.h"  
#include "Application\Debug\LogManager.h"


BOOL CSplashScreenWnd::c_bShowSplashWnd;
CSplashScreenWnd* CSplashScreenWnd::c_pSplashWnd;
BEGIN_MESSAGE_MAP(CSplashScreenWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashScreenWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
CSplashScreenWnd::CSplashScreenWnd(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
CSplashScreenWnd::~CSplashScreenWnd(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	// Statischen Fensterzeiger löschen
	ASSERT(c_pSplashWnd == this);
	c_pSplashWnd = NULL;
}


//----------------------------------------------------------------------------
void CSplashScreenWnd::EnableSplashScreen(BOOL bEnable /*= TRUE*/){
//----------------------------------------------------------------------------
	PROC_TRACE;

	c_bShowSplashWnd = bEnable;
}

//----------------------------------------------------------------------------
void CSplashScreenWnd::ShowSplashScreen(CWnd* pParentWnd /*= NULL*/){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (!c_bShowSplashWnd || c_pSplashWnd != NULL)
		return;

	// Neuen Begrüßungsbildschirm reservieren und erstellen
	c_pSplashWnd = new CSplashScreenWnd;
	if (!c_pSplashWnd->Create(pParentWnd))
		delete c_pSplashWnd;
	else
		c_pSplashWnd->UpdateWindow();
}

//----------------------------------------------------------------------------
BOOL CSplashScreenWnd::PretranslateAppMessage(MSG* pMsg){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (c_pSplashWnd == NULL)
		return FALSE;

	// Begrüßungsbildschirm ausblenden, falls eine Tastatur- oder Mausnachricht empfangen wird.
	if (pMsg->message == WM_KEYDOWN ||
	    pMsg->message == WM_SYSKEYDOWN ||
	    pMsg->message == WM_LBUTTONDOWN ||
	    pMsg->message == WM_RBUTTONDOWN ||
	    pMsg->message == WM_MBUTTONDOWN ||
	    pMsg->message == WM_NCLBUTTONDOWN ||
	    pMsg->message == WM_NCRBUTTONDOWN ||
	    pMsg->message == WM_NCMBUTTONDOWN)
	{
		c_pSplashWnd->HideSplashScreen();
		return TRUE;	// Die Nachricht wurde hier behandelt
	}

	return FALSE;	// Die Nachricht wurde nicht behandelt
}

//----------------------------------------------------------------------------
BOOL CSplashScreenWnd::Create(CWnd* pParentWnd /*= NULL*/){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (!m_bitmap.LoadBitmap(IDB_SPLASH_SCREEN))
		return FALSE;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL);
}

//----------------------------------------------------------------------------
void CSplashScreenWnd::HideSplashScreen(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	// Fenster entfernen und Hauptrahmen aktualisieren
	DestroyWindow();
	AfxGetMainWnd()->UpdateWindow();
}

//----------------------------------------------------------------------------
void CSplashScreenWnd::PostNcDestroy(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	delete this;
}

//----------------------------------------------------------------------------
int CSplashScreenWnd::OnCreate(LPCREATESTRUCT lpCreateStruct){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Fenster zentrieren
	CenterWindow();

	// Zeitgeber festlegen, um den Begrüßungsbildschirm zu entfernen.
	SetTimer(1, 1750, NULL);

	return 0;
}

//----------------------------------------------------------------------------
void CSplashScreenWnd::OnPaint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CPaintDC dc(this);

	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(&dc))
		return;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	// Bild zeichnen
	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);
}

//----------------------------------------------------------------------------
void CSplashScreenWnd::OnTimer(UINT nIDEvent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	HideSplashScreen();
}
