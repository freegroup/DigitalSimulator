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

#include "DragDropGridView.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Debug\LogManager.h"
#include "utils/global_defines.h"
#include "Application\Controls\SplashScreen\SplashScreen.h"
#include "Application\Dialogs\DialogOsziOptions.h"
#include "Application\Windows\Palette\ObjectDockingControlBar.h"
#include "Application\Objects\plugin\Java\JavaPluginManager.h"
#include "Application\JavaBinding\ApplicationProxyWrapper.h"

#include "MainFrm.h"
#include <vector>

static const int	kImageWidth  (28);
static const int	kImageHeight (28);
static const int	kNumImages   (21);

static const UINT	kToolBarBitDepth (ILC_COLOR24);
// this color will be treated as transparent in the loaded bitmaps --
// in other words, any pixel of this color will be set at runtime to
// the user's button color. The Visual Studio toolbar editor defaults
// to 192, 192, 192 (light gray).
static const RGBTRIPLE	kBackgroundColor = {192, 192, 192};

void ReplaceBackgroundColor (CBitmap& ioBM);
void MakeToolbarImageList (UINT inBitmapID,  CImageList&	outImageList);


IMPLEMENT_DYNAMIC(CMainFrame, DragDropMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, DragDropMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_OBJECT_BAR, OnViewObjectBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OBJECT_BAR, OnUpdateViewObjectBar)
	ON_COMMAND(ID_VIEW_OSZI_BAR, OnViewOsziBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OSZI_BAR, OnUpdateViewOsziBar)
	ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateViewToolBar)
	ON_COMMAND(ID_EIGENSCHAFTEN_OSZILOSKOPE, OnOptionsOsziloskope)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FULLSCREEN, OnFullScreen)
	ON_UPDATE_COMMAND_UI(ID_FULLSCREEN, OnUpdateFullScreen)
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_WM_WINDOWPOSCHANGING()
	ON_COMMAND(ID_OPTIONS_TOOLBAR, OnOptionsToolbar)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_TOOLBAR, OnUpdateOptionsToolbar)
	//}}AFX_MSG_MAP
	// Globale Hilfebefehle
	// for the tools plugin
	ON_UPDATE_COMMAND_UI(ID_POPUP_toolStart,   OnUpdateTools)
	ON_COMMAND_RANGE( ID_POPUP_toolStart, ID_POPUP_toolEnd, OnTools )

   // for the dialogs plugins
	ON_UPDATE_COMMAND_UI(ID_POPUP_dialogStart,   OnUpdateDialogs)
	ON_COMMAND_RANGE( ID_POPUP_dialogStart, ID_POPUP_dialogEnd, OnDialogs )

   ON_COMMAND(ID_HELP_FINDER, DragDropMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, DragDropMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, DragDropMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, DragDropMDIFrameWnd::OnHelpFinder)
//   ON_FREE_MESSAGE()
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CMainFrame Nachrichten-Handler
//----------------------------------------------------------------------------
CMainFrame::CMainFrame(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_languageNotifyee.setListener(this);
   m_bFullScreenMode= false;
 	m_nYOffset = 10;
	m_nXOffset = 10;
}


//----------------------------------------------------------------------------
CMainFrame::~CMainFrame(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void CMainFrame::GetMessageString(UINT nID, CString & rMessage) const {
//----------------------------------------------------------------------------
	PROC_TRACE;

//   CString translation = TRANSLATE(nID);
//   if(atoi((LPCSTR)translation) == nID)
//      rMessage = "";
//   else
//      rMessage = translation;
}

//----------------------------------------------------------------------------
void CMainFrame::TranslateGUI(){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   TRANSLATE(GetMenu());
   DrawMenuBar();
}


//----------------------------------------------------------------------------
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (inherited::OnCreate(lpCreateStruct) == -1)
		return -1;
	

   // init the ToolBar
   //
   if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
       | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
      !m_wndToolBar.LoadToolBar(IDR_MAINFRAME_FREE))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;
   }


   AttachToolbarImages(IDB_TOOLBAR_ENABLE, IDB_TOOLBAR_DISABLE, IDB_TOOLBAR_HOVER);

   EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
   DockControlBar(&m_wndToolBar);
   m_wndToolBar.SetToolBarInfoForCustomization();
   m_wndToolBar.RestoreState();



   // init the ObjectBar (Palette on the left)
   //
 	m_wndObjectBar.Create(this, CSize(300, 150), IDD_OBJECT_BAR);
	m_wndObjectBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);
	m_wndObjectBar.EnableDocking(CBRS_ALIGN_ANY);
    m_wndObjectBar.AddAllPaletteFiles();
	DockControlBar(&m_wndObjectBar, AFX_IDW_DOCKBAR_LEFT);
 
 	m_wndOsziBar.Create(this, CSize(200, 100), IDD_OSZI_BAR);
	m_wndOsziBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);
	m_wndOsziBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndOsziBar, AFX_IDW_DOCKBAR_BOTTOM);

    LoadBarState(VERSION_STRING "/BarState");

    CSplashScreenWnd::ShowSplashScreen(this);

	// restore the visibility of the osziToolbar from the ini-File
	//
	if(GET_PARAMETER("ShowOsziBar")=="FALSE")
		ShowControlBar(&m_wndOsziBar,FALSE,FALSE);
	else
		ShowControlBar(&m_wndOsziBar,TRUE,FALSE);

	// restore the visibility of the object-Toolbar from the ini-File
	//
	if(GET_PARAMETER("ShowObjectBar")=="FALSE")
		ShowControlBar(&m_wndObjectBar,FALSE,FALSE);
	else
		ShowControlBar(&m_wndObjectBar,TRUE,FALSE);

	// restore the visibility of the object-Toolbar from the ini-File
	//
	if(GET_PARAMETER("ShowToolBar")=="FALSE")
		ShowControlBar(&m_wndToolBar,FALSE,FALSE);
	else
		ShowControlBar(&m_wndToolBar,TRUE,FALSE);

   SetWindowText(VERSION_STRING);
   return 0;
}

//----------------------------------------------------------------------------
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs){
//----------------------------------------------------------------------------
	PROC_TRACE;

	cs.style &= ~FWS_ADDTOTITLE;
	return inherited::PreCreateWindow(cs);
}



//----------------------------------------------------------------------------
void CMainFrame::OnSize(UINT nType, int cx, int cy){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnSize(nType, cx, cy);
	
	if (::IsWindow(m_wndObjectBar.GetSafeHwnd()))
      m_wndObjectBar.UpdateWindow();
	if (::IsWindow(m_wndOsziBar.GetSafeHwnd()))
      m_wndOsziBar.UpdateWindow();
	if (::IsWindow(GetSafeHwnd()))
      RecalcLayout();
}

//----------------------------------------------------------------------------
void CMainFrame::OnTools(UINT id){
//----------------------------------------------------------------------------
	PROC_TRACE;
	LM::log(LM::debug1,"Tools Id:%d",id);

	std::vector<CDynamicMenuExtension*> tools= JavaPluginManager::getTools();
	std::vector<CDynamicMenuExtension*>::iterator theIterator;

	theIterator = tools.begin();
	while(theIterator != tools.end()){
		if((*theIterator)->getCurrentMenuCommand()==id){
		   ApplicationProxyWrapper::onToolCall((*theIterator)->getId());
		   return;
		}
		theIterator++;

	}

}

//----------------------------------------------------------------------------
void CMainFrame::OnUpdateTools(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;
	/// search through the current items and remove the appropriate one
	CMenu* menu = pCmdUI->m_pMenu;
	if(menu!=NULL)
	{
		int count = menu->GetMenuItemCount();
		for (int j=ID_POPUP_toolStart; j<ID_POPUP_toolEnd; ++j)
		{
			menu->DeleteMenu (j, MF_BYCOMMAND);
		}

		std::vector<CDynamicMenuExtension*> tools= JavaPluginManager::getTools();
	   std::vector<CDynamicMenuExtension*>::iterator theIterator;

		int i=ID_POPUP_toolStart;
  		theIterator = tools.begin();
	    while(theIterator != tools.end()){
	   		pCmdUI->m_pMenu->InsertMenu(pCmdUI->m_nIndex,	MF_STRING | MF_BYPOSITION,i, TRANSLATE((*theIterator)->getMenuEntry()));
			(*theIterator)->setCurrentMenuCommand(i);
			theIterator++;
			i++;
			pCmdUI->m_nIndex++;
		}
	}
	// update end menu count
	pCmdUI->m_nIndex--; // point to last menu added
	pCmdUI->m_nIndexMax = pCmdUI->m_nIndex;

	pCmdUI->m_bEnableChanged = TRUE;    // all the added items are enabled
}


//----------------------------------------------------------------------------
void CMainFrame::OnDialogs(UINT id){
//----------------------------------------------------------------------------
	PROC_TRACE;
	LM::log(LM::debug1,"Dialog Id:%d",id);

	std::vector<CDynamicMenuExtension*> tools= JavaPluginManager::getDialogs();
	std::vector<CDynamicMenuExtension*>::iterator theIterator;

	theIterator = tools.begin();
	while(theIterator != tools.end()){
		if((*theIterator)->getCurrentMenuCommand()==id){
		   ApplicationProxyWrapper::onDialogCall((*theIterator)->getId());
		   return;
		}
		theIterator++;

	}

}

//----------------------------------------------------------------------------
void CMainFrame::OnUpdateDialogs(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;
	/// search through the current items and remove the appropriate one
	CMenu* menu = pCmdUI->m_pMenu;
	if(menu!=NULL)
	{
		int count = menu->GetMenuItemCount();
		for (int j=ID_POPUP_dialogStart; j<ID_POPUP_dialogEnd; ++j)
		{
			menu->DeleteMenu (j, MF_BYCOMMAND);
		}

		std::vector<CDynamicMenuExtension*> dialogs= JavaPluginManager::getDialogs();
      std::vector<CDynamicMenuExtension*>::iterator theIterator;

		int i=ID_POPUP_dialogStart;
  		theIterator = dialogs.begin();
	    while(theIterator != dialogs.end()){
	   	pCmdUI->m_pMenu->InsertMenu(pCmdUI->m_nIndex,	MF_STRING | MF_BYPOSITION,i, TRANSLATE((*theIterator)->getMenuEntry()));
			(*theIterator)->setCurrentMenuCommand(i);
			theIterator++;
			i++;
			pCmdUI->m_nIndex++;
		}
	}
	// update end menu count
	pCmdUI->m_nIndex--; // point to last menu added
	pCmdUI->m_nIndexMax = pCmdUI->m_nIndex;

	pCmdUI->m_bEnableChanged = TRUE;    // all the added items are enabled
}

//----------------------------------------------------------------------------
void CMainFrame::OnViewObjectBar() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	ShowControlBar(&m_wndObjectBar,!m_wndObjectBar.IsWindowVisible(),FALSE);

	// save the state for the next startup of the application
	//
	SET_PARAMETER("ShowObjectBar",m_wndObjectBar.IsWindowVisible()?"TRUE":"FALSE");
}

//----------------------------------------------------------------------------
void CMainFrame::OnUpdateViewObjectBar(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->SetCheck( m_wndObjectBar.IsWindowVisible()) ;      
}


//----------------------------------------------------------------------------
void CMainFrame::OnViewToolBar() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	ShowControlBar(&m_wndToolBar,!m_wndToolBar.IsWindowVisible(),FALSE);

	// save the state for the next startup of the application
	//
	SET_PARAMETER("ShowToolBar",m_wndToolBar.IsWindowVisible()?"TRUE":"FALSE");
}

//----------------------------------------------------------------------------
void CMainFrame::OnUpdateViewToolBar(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->SetCheck( m_wndToolBar.IsWindowVisible()) ;      
}


//----------------------------------------------------------------------------
void CMainFrame::OnViewOsziBar() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	ShowControlBar(&m_wndOsziBar,!m_wndOsziBar.IsWindowVisible(),FALSE);

	// save the state for the next startup of the application
	//
	SET_PARAMETER("ShowOsziBar",m_wndOsziBar.IsWindowVisible()?"TRUE":"FALSE");
}

//----------------------------------------------------------------------------
void CMainFrame::OnUpdateViewOsziBar(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->SetCheck( m_wndOsziBar.IsWindowVisible()) ;      
}



//----------------------------------------------------------------------------
void CMainFrame::RecalcLayout(BOOL bNotify) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::RecalcLayout(bNotify);
	inherited::RecalcLayout(bNotify);
}


//----------------------------------------------------------------------------
void CMainFrame::OnOptionsOsziloskope() {
//----------------------------------------------------------------------------
	PROC_TRACE;


   CDialogOsziOptions dlg;
   dlg.DoModal();
}


//----------------------------------------------------------------------------
void CMainFrame::OnDestroy() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   FullScreenModeOff();
//   SaveWindowPlacement(AfxGetMainWnd(),"MainWindow");
   SaveBarState("DigitalSimulator/BarState");

   inherited::OnDestroy();
}

//----------------------------------------------------------------------------
void CMainFrame::FullScreenModeOn(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	// available only if there is an active doc
	CMDIChildWnd* pChild=MDIGetActive();
	if(!pChild)
      return;

   m_bObjectBarWasVisible=(m_wndObjectBar.IsWindowVisible()!=0);
	m_wndObjectBar.ShowWindow(SW_HIDE);
	m_bOsziBarWasVisible=(m_wndOsziBar.IsWindowVisible()!=0);
	m_wndOsziBar.ShowWindow(SW_HIDE);


   CMenu* oldMenu = GetMenu();
   m_origMenu.Attach(oldMenu->Detach());
   SetMenu((CMenu*)NULL);

   GetWindowRect(&m_mainRect);
	// remove the caption of the mainWnd:
	LONG style=::GetWindowLong(m_hWnd,GWL_STYLE);
	style&=~WS_CAPTION;
	::SetWindowLong(m_hWnd,GWL_STYLE,style);
	int screenx=GetSystemMetrics(SM_CXSCREEN);
	int screeny=GetSystemMetrics(SM_CYSCREEN);
	// resize:
	SetWindowPos(NULL,-4,-4,screenx+8,screeny+8,SWP_NOZORDER);
	style=::GetWindowLong(pChild->m_hWnd,GWL_STYLE);
	m_bChildMax=(style & WS_MAXIMIZE)?true:false;
	// note here: m_bMainMax is not needed since m_hWnd only
	// changed its caption...

	// and maximize the child window
	// it will remove its caption, too.
	pChild->ShowWindow(SW_SHOWMAXIMIZED);
	RecalcLayout();
	m_bFullScreenMode=true;

}

//----------------------------------------------------------------------------
void CMainFrame::FullScreenModeOff(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	// You can use SaveBarState() in OnClose(),
	// so remove the newly added toolbar entirely
	// in order SaveBarState() not
	// to save its state. That is why I used dynamic
	// allocation
	LONG style=::GetWindowLong(m_hWnd,GWL_STYLE);
	style|=WS_CAPTION;
	::SetWindowLong(m_hWnd,GWL_STYLE,style);
	if(m_bObjectBarWasVisible)
		m_wndObjectBar.ShowWindow(SW_SHOW);
	if(m_bOsziBarWasVisible)
		m_wndOsziBar.ShowWindow(SW_SHOW);

   SetMenu(&m_origMenu);
   m_origMenu.Detach();

	MoveWindow(&m_mainRect);
	RecalcLayout();
	CMDIChildWnd* pChild=MDIGetActive();
	// pchild can be NULL if the USER closed all the
	// childs during Full Screen Mode:
	if(pChild){
		if(m_bChildMax)
			MDIMaximize(pChild);
		else MDIRestore(pChild);
	}
	m_bFullScreenMode=false;
}

//----------------------------------------------------------------------------
void CMainFrame::OnFullScreen() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	if(m_bFullScreenMode)
		FullScreenModeOff();
	else 
      FullScreenModeOn();
}

//----------------------------------------------------------------------------
void CMainFrame::OnUpdateFullScreen(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(MDIGetActive()?true:false);	
   pCmdUI->SetCheck(m_bFullScreenMode);	
}

//----------------------------------------------------------------------------
void CMainFrame::OnClose() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(AfxGetApp()->SaveAllModified())
	   inherited::OnClose();
}

//----------------------------------------------------------------------------
void CMainFrame::OnUpdateFilePrint(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(MDIGetActive()?true:false);	
}

//----------------------------------------------------------------------------
void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(MDIGetActive()?true:false);	
}

//----------------------------------------------------------------------------
void CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(MDIGetActive()?true:false);	
}

//----------------------------------------------------------------------------
void CMainFrame::OnUpdateFileSaveAs(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(MDIGetActive()?true:false);	
}


//----------------------------------------------------------------------------
void CMainFrame::OnOptionsToolbar() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_wndToolBar.GetToolBarCtrl().Customize();
}

//----------------------------------------------------------------------------
void CMainFrame::OnUpdateOptionsToolbar(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void CMainFrame::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) {
//----------------------------------------------------------------------------
	PROC_TRACE;

//	DragDropMDIFrameWnd::OnWindowPosChanging(lpwndpos);
	
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



// load the high color toolbar images and attach them to m_wndToolBar
void CMainFrame::AttachToolbarImages (UINT inNormalImageID,
                                      UINT inDisabledImageID,
                                      UINT inHotImageID)
{
	PROC_TRACE;

   CClientDC dc(this);
   if(dc.GetDeviceCaps(BITSPIXEL)>=16){
      LM::log(LM::info,"enable high color toolbar\n");

      // make high-color image lists for each of the bitmaps
      ::MakeToolbarImageList (inNormalImageID, m_ToolbarImages);
      ::MakeToolbarImageList (inDisabledImageID, m_ToolbarImagesDisabled);
      ::MakeToolbarImageList (inHotImageID, m_ToolbarImagesHot);

      // get the toolbar control associated with the CToolbar object
      CToolBarCtrl&	barCtrl = m_wndToolBar.GetToolBarCtrl();

      // attach the image lists to the toolbar control
      barCtrl.SetImageList (&m_ToolbarImages);
      barCtrl.SetDisabledImageList (&m_ToolbarImagesDisabled);
      barCtrl.SetHotImageList (&m_ToolbarImagesHot);
   }
   else{
      LM::log(LM::info,"No high color toolbar possible. color depth to low.\n");
   }
}

// find every pixel of the default background color in the specified
// bitmap and set each one to the user's button color.
static void	ReplaceBackgroundColor (CBitmap& ioBM)
{
 // figure out how many pixels there are in the bitmap
 BITMAP		bmInfo;

 VERIFY (ioBM.GetBitmap (&bmInfo));

 // add support for additional bit depths if you choose
 VERIFY (bmInfo.bmBitsPixel == 24);
 VERIFY (bmInfo.bmWidthBytes == (bmInfo.bmWidth * 3));

 const UINT		numPixels (bmInfo.bmHeight * bmInfo.bmWidth);

 // get a pointer to the pixels
 DIBSECTION  ds;

 VERIFY (ioBM.GetObject (sizeof (DIBSECTION), &ds) == sizeof (DIBSECTION));

 RGBTRIPLE*		pixels = reinterpret_cast<RGBTRIPLE*>(ds.dsBm.bmBits);
 VERIFY (pixels != NULL);

 // get the user's preferred button color from the system
 const COLORREF		buttonColor (::GetSysColor (COLOR_BTNFACE));
 const RGBTRIPLE		userBackgroundColor = {
 GetBValue (buttonColor), GetGValue (buttonColor), GetRValue (buttonColor)};

 // search through the pixels, substituting the user's button
 // color for any pixel that has the magic background color
 for (UINT i = 0; i < numPixels; ++i)
 {
  if (pixels [i].rgbtBlue == kBackgroundColor.rgbtBlue 
  && pixels [i].rgbtGreen == kBackgroundColor.rgbtGreen 
  && pixels [i].rgbtRed == kBackgroundColor.rgbtRed)
  {
   pixels [i] = userBackgroundColor;
  }
 }
}

// create an image list for the specified BMP resource
static void	MakeToolbarImageList (UINT inBitmapID, CImageList&	outImageList)
{
 CBitmap		bm;

 // if we use CBitmap::LoadBitmap() to load the bitmap, the colors
 // will be reduced to the bit depth of the main screen and we won't
 // be able to access the pixels directly. To avoid those problems,
 // we'll load the bitmap as a DIBSection instead and attach the
 // DIBSection to the CBitmap.
 VERIFY (bm.Attach (::LoadImage (::AfxFindResourceHandle(
 MAKEINTRESOURCE (inBitmapID), RT_BITMAP),
 MAKEINTRESOURCE (inBitmapID), IMAGE_BITMAP, 0, 0,
 (LR_DEFAULTSIZE | LR_CREATEDIBSECTION))));

 // replace the specified color in the bitmap with the user's
 // button color
 ::ReplaceBackgroundColor (bm);

 // create a 24 bit image list with the same dimensions and number
 // of buttons as the toolbar
 VERIFY (outImageList.Create (
 kImageWidth, kImageHeight, kToolBarBitDepth, kNumImages, 0));

 // attach the bitmap to the image list
 VERIFY (outImageList.Add (&bm, RGB (0, 0, 0)) != -1);
}
