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
#include "Application\DigitalSimulatorApp.h"
#include "SizingTabCtrlBar.h"
#include <assert.h>

// true color image list
//
static void ReplaceBackgroundColor (CBitmap& ioBM);
static void MakeToolbarImageList (UINT inBitmapID,  CImageList&	outImageList);
static const int	kImageWidth (19);
static const int	kImageHeight (19);
static const int	kNumImages (10);
static const UINT	kToolBarBitDepth (ILC_COLOR24);
static const RGBTRIPLE	kBackgroundColor = {192, 192, 192};


BEGIN_MESSAGE_MAP(CSizingTabCtrlBar, CSizingControlBar)
	//{{AFX_MSG_MAP(CSizingTabCtrlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDI_TABCTRLBAR, OnTabSelChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CSizingTabCtrlBar::CSizingTabCtrlBar(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_nActiveTab  = -1;
   m_pActiveView = NULL;
   m_pFrame      = NULL;
}

//----------------------------------------------------------------------------
CSizingTabCtrlBar::~CSizingTabCtrlBar(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   while(!m_views.IsEmpty())	{
		TCB_ITEM *pMember=m_views.RemoveHead();
		delete pMember;
	}
}

//----------------------------------------------------------------------------
int CSizingTabCtrlBar::OnCreate(LPCREATESTRUCT lpCreateStruct) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (inherited::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect(0,0,100,100);

	//Create the Tab Control
	m_tabctrl.Create(   WS_VISIBLE 
                     | WS_CHILD   
                     | TCS_MULTILINE  
                     | TCS_BOTTOM, 
		              rect, this, IDI_TABCTRLBAR);

   ::MakeToolbarImageList (IDB_TAB_CTRL, m_images);
	m_tabctrl.SetImageList(&m_images);
	m_tabctrl.SetItemSize(CSize(22,22));

	CFont *font = CFont::FromHandle((HFONT)::GetStockObject(SYSTEM_FONT));
	m_tabctrl.SetFont(font);
	
	return 0;
}

//----------------------------------------------------------------------------
void CSizingTabCtrlBar::OnSize(UINT nType, int cx, int cy) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::OnSize(nType, cx, cy);


   CRect rc;
	
   //????? Ich hasse hart codierte Zahlen!!!!
   //
	int bottom = (IsHorz() || IsFloating()) ? cy - 6 : cy - 8;


   // TabControl anpassen
   //
   m_tabctrl.MoveWindow(3, 3, cx - 3, bottom);

   try
   {

      if(m_pFrame!=NULL && m_pFrame->IsKindOf(RUNTIME_CLASS(CFrameWnd)))   
      {
         // Frame anpassen
         //
         m_pFrame->MoveWindow(3,3,cx-3,bottom- (6+(22.0*m_tabctrl.GetRowCount())));

         // Die Views an den Frame anpassen
         //
         m_pFrame->GetClientRect(&rc);
	      CWnd *pWnd;
         for (POSITION pos=m_views.GetHeadPosition(); pos; m_views.GetNext(pos))
         {
            pWnd=m_views.GetAt(pos)->pWnd;
            pWnd->MoveWindow(rc.TopLeft().x, rc.TopLeft().y, rc.Width(), rc.Height());
         } 
      }
   }
   catch(...)
   {
         // some exception on win2000 .....don't known any bug fix at the moment
         #pragma TODO("Exection in win2000 during minimize the application....find the reason.")
   }
}


//----------------------------------------------------------------------------
BOOL CSizingTabCtrlBar::AddView(CString label, CRuntimeClass *pViewClass, CCreateContext *pContext, BOOL withImage){	
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT_VALID(this);
	assert(pViewClass != NULL);
	assert(pViewClass->IsDerivedFrom(RUNTIME_CLASS(CWnd)));
	assert(AfxIsValidAddress(pViewClass, sizeof(CRuntimeClass), FALSE));

    // Create The Frame
    //
    if(m_pFrame==NULL)
      if(!CreateFrame())
         return FALSE;

	CWnd* pWnd;
	TRY{
		pWnd = (CWnd*)pViewClass->CreateObject();
		if (pWnd == NULL)
			AfxThrowMemoryException();
	}
	CATCH_ALL(e){
		TRACE("Out of memory creating a view.\n");
		// Note: DELETE_EXCEPTION(e) not required
		return FALSE;
	}
	END_CATCH_ALL
		
   ASSERT_KINDOF(CWnd, pWnd);
	ASSERT(pWnd->m_hWnd == NULL);       // not yet created
	
   DWORD dwStyle=AFX_WS_DEFAULT_VIEW;

   CRect rect;
	// Create with the right size and position
	if (!pWnd->Create(NULL, NULL, dwStyle, rect, m_pFrame, 0, pContext)){
		TRACE("Warning: couldn't create client pane for view.\n");
		// pWnd will be cleaned up by PostNcDestroy
		return FALSE;
	}

   m_pActiveView = (CView*) pWnd;

	TCB_ITEM *pMember=new TCB_ITEM;
	pMember->pWnd=pWnd;
	strcpy(pMember->szLabel, (LPCSTR)label);
	m_views.AddTail(pMember);

	int nViews = m_views.GetCount();
	if (nViews!=1)	{
		pWnd->EnableWindow(FALSE);
		pWnd->ShowWindow(SW_HIDE);
	}
	else	{
		((CFrameWnd *)GetParent())->SetActiveView((CView *)m_pActiveView);
      m_nActiveTab = 0;
   }

 
	// TODO: Add your specialized code here and/or call the base class
	
  	TC_ITEM tci;
   tci.pszText = pMember->szLabel;
   if(withImage == TRUE){
	   tci.mask = TCIF_TEXT | TCIF_IMAGE;
	   tci.iImage = nViews-1;
   }
   else{
	   tci.mask = TCIF_TEXT;
   }
   m_tabctrl.InsertItem(nViews, &tci);

   GetWindowRect(rect);
   OnSize(SIZE_RESTORED,rect.Width(),rect.Height());
   return TRUE;
}


//----------------------------------------------------------------------------
void CSizingTabCtrlBar::RemoveAllViews(){
//----------------------------------------------------------------------------

	while(m_views.GetCount()!=0)
	{
		RemoveView(0);
	}
}

//----------------------------------------------------------------------------
void CSizingTabCtrlBar::RemoveView(int nView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT_VALID(this);
	assert(nView >= 0);

   // Sind ueberhaupt so viele Views enthalten
   //
   if(nView >=m_views.GetCount())
      return;


   CView *pView = GetView(nView);


	// remove the page from internal list
   //
   m_tabctrl.DeleteItem(nView);
	m_views.RemoveAt(m_views.FindIndex(nView));
   // 
   //delete pView; 


   if(nView <= m_nActiveTab)
      m_nActiveTab--;

   if(nView>0){
      SetActiveView(nView-1);
   }
   else if(m_views.GetCount()!=0){
      SetActiveView(0);
   }
   else if(m_views.GetCount()<=0){
	  ((CFrameWnd *)GetParent())->SetActiveView(NULL);
      m_pActiveView = NULL;
      m_nActiveTab  = -1;
   }

   CRect rect;
   GetWindowRect(rect);
   OnSize(SIZE_RESTORED,rect.Width(),rect.Height());

   delete pView; 
}

//----------------------------------------------------------------------------
void CSizingTabCtrlBar::RemoveView(CView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT_VALID(this);
	ASSERT_VALID(pView);

	// remove the page from internal list
   int num=0;
	for (POSITION pos=m_views.GetHeadPosition(); pos; m_views.GetNext(pos)){
		TCB_ITEM *pMember=m_views.GetAt(pos);
      if (pMember->pWnd == pView){
         RemoveView(num);
			break;
		}
      num++;
   }
}


//----------------------------------------------------------------------------
void CSizingTabCtrlBar::OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult){
//----------------------------------------------------------------------------
	PROC_TRACE;

   int sel= m_tabctrl.GetCurSel();
   if(sel >=0)
      SetActiveView(sel);
}


//----------------------------------------------------------------------------
void CSizingTabCtrlBar::SetLabel(CView* view, CString label){
//----------------------------------------------------------------------------
	PROC_TRACE;

   TC_ITEM tci;

   int num=0;
	for (POSITION pos=m_views.GetHeadPosition(); pos; m_views.GetNext(pos)){
		TCB_ITEM *pMember=m_views.GetAt(pos);
      if (pMember->pWnd == view){
	      tci.mask    = TCIF_TEXT;
	      tci.pszText = (char*)(LPCSTR)label;
         m_tabctrl.SetItem(num, &tci);
			break;
		}
      num++;
    }
}

//----------------------------------------------------------------------------
void CSizingTabCtrlBar::SetActiveView(int nNewTab){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT_VALID(this);
	assert(nNewTab >= 0);

   // nothing to do
   //
   if( nNewTab == m_nActiveTab)
      return ;

	if (nNewTab >=0 )	{
        TCB_ITEM *newMember=m_views.GetAt(m_views.FindIndex(nNewTab));
        TCB_ITEM *oldMember=NULL;
		
        if (m_nActiveTab!=-1)        {
            oldMember=m_views.GetAt(m_views.FindIndex(m_nActiveTab));
            oldMember->pWnd->EnableWindow(FALSE);
            oldMember->pWnd->ShowWindow(SW_HIDE);
        }
        newMember->pWnd->EnableWindow(TRUE);
        newMember->pWnd->ShowWindow(SW_SHOW);
        newMember->pWnd->SetFocus();

        m_pActiveView = (CView *)newMember->pWnd;
		  ((CFrameWnd *)GetParent())->SetActiveView(m_pActiveView);

        m_nActiveTab = nNewTab;
		  // select the tab (if tab programmatically changed)
		  m_tabctrl.SetCurSel(m_nActiveTab);
    }
}


//----------------------------------------------------------------------------
void CSizingTabCtrlBar::SetActiveView(CView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT_VALID(this);
	ASSERT_VALID(pView);

   // tsts... should never happen
   //
   if(pView == NULL)
      return;

   int num=0;
	for (POSITION pos=m_views.GetHeadPosition(); pos; m_views.GetNext(pos)){
		TCB_ITEM *pMember=m_views.GetAt(pos);
      if (pMember->pWnd == pView){
         SetActiveView(num);
			break;
		}
      num++;
    }
}



//----------------------------------------------------------------------------
CView* CSizingTabCtrlBar::GetActiveView(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pActiveView;
}


//----------------------------------------------------------------------------
CView* CSizingTabCtrlBar::GetView(int nView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT_VALID(this);
	ASSERT(nView >= 0);

	if (nView!=-1)	{
        TCB_ITEM *pMember=m_views.GetAt(m_views.FindIndex(nView));
		return (CView*)pMember->pWnd;
	}
	else
		return NULL;
}


//----------------------------------------------------------------------------
BOOL CSizingTabCtrlBar::CreateFrame(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CRuntimeClass* pClass = RUNTIME_CLASS(CFrameWnd);
   ASSERT(pClass);
   m_pFrame = (CFrameWnd*)pClass->CreateObject();
   ASSERT(m_pFrame);
   CCreateContext context;

   context.m_pCurrentFrame   = NULL;
   context.m_pCurrentDoc     = NULL;
   context.m_pNewViewClass   = NULL;
   context.m_pNewDocTemplate = NULL;

   CRect rect;
   if(!m_pFrame->Create(NULL,NULL,AFX_WS_DEFAULT_VIEW,rect,this,NULL,0,&context))
      return FALSE;

   m_pFrame->InitialUpdateFrame(NULL,TRUE);
   return TRUE;
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
  if (pixels [i].rgbtBlue == 189 
  && pixels [i].rgbtGreen == 189 
  && pixels [i].rgbtRed == 189)
  {
   pixels [i] = userBackgroundColor;
  }
 }
}

// create an image list for the specified BMP resource
static void	MakeToolbarImageList (UINT inBitmapID,
                                  CImageList&	outImageList)
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