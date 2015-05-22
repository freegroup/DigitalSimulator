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
#include "afxpriv.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\Objects\buildin\digital\ElectricPort.h"
#include "Application\Debug\LogManager.h"
#include "Application\i18n\ResourceTranslater.h"

#include "ObjectDockingControlBarView.h"

#pragma warning(disable : 4786)
//#include <set>
#include <vector>
#include <algorithm>

using namespace std ;

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
CString CObjectDockingControlBarView::s_paletteFileToOpen="";

IMPLEMENT_DYNCREATE(CObjectDockingControlBarView, DragDropView)

BEGIN_MESSAGE_MAP(CObjectDockingControlBarView, DragDropView)
	//{{AFX_MSG_MAP(CObjectDockingControlBarView)
	ON_WM_SIZE()
    ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_PALETTE, OnEditPalette)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PALETTE, OnUpdateEditPalette)
	ON_COMMAND(ID_PALETTE_AUTOLAYOUT, OnPaletteAutolayout)
	ON_UPDATE_COMMAND_UI(ID_PALETTE_AUTOLAYOUT, OnUpdatePaletteAutolayout)
	//}}AFX_MSG_MAP
   ON_MESSAGE(WM_HELPHITTEST, OnHelpHitTest)
   ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CObjectDockingControlBarView::CObjectDockingControlBarView(){
//----------------------------------------------------------------------------
	PROC_TRACE;
}

//----------------------------------------------------------------------------
CObjectDockingControlBarView::~CObjectDockingControlBarView(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
int CObjectDockingControlBarView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (inherited::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Initialisierung darf nicht in den Konstruktor gelegt werden
   // da einige  Funktionen 'Invalidate()' aufrufen und im Konmstruktor
   // noch keine gültiger Eintrag in der VirtuellenTabelle vorhanden ist
   // (DEBUG Assert)
   //
   OnInitialUpdate();
	return 0;
}

//----------------------------------------------------------------------------
void CObjectDockingControlBarView::OnContextMenu(CWnd*, CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   UINT           menuId = IDR_POPUP_PALETTE;
   CClientDC      dc(this);
   CPoint pointLP = point;

   ScreenToClient(&pointLP);
   OnPrepareDC(&dc);
   dc.DPtoLP(&pointLP);

   
	CMenu menu;
	VERIFY(menu.LoadMenu(menuId));

	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
	  pWndPopupOwner = pWndPopupOwner->GetParent();
	CMenu* pPopup = menu.GetSubMenu(0);
	assert(pPopup != NULL);
	TRANSLATE(pPopup);

	// Show the menu!
	s_paletteFileToOpen = this->GetDocument()->GetPathName();
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);

}


//----------------------------------------------------------------------------
LRESULT CObjectDockingControlBarView::OnHelpHitTest(WPARAM, LPARAM lParam){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT_VALID(this);

   CPoint  p2(LOWORD(lParam),HIWORD(lParam));
   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.DPtoLP(&p2);

   DragDropObject* obj = DoPickInDocument(&dc, p2, TRUE);
   if(obj)
      return obj->GetHelpId();
   return 0;
}

//----------------------------------------------------------------------------
void CObjectDockingControlBarView::OnLButtonDblClk(UINT nFlags, CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
}

//----------------------------------------------------------------------------
void CObjectDockingControlBarView::TranslateGUI(){
//----------------------------------------------------------------------------
	PROC_TRACE;
}


void SortIntoList(DragDropObject* pFile, vector<DragDropObject*>& list)
{
	// Find a place to start and stop.  In my case, I had to maintain 
	// an iterator that tracked the begining of the section that was 
	// not BMP files (iEnd was NOT guaranteed to be the absolute end 
	// of the list), but for this example, it's not neccesary.
	vector<DragDropObject*>::iterator iBegin  = list.begin();
	vector<DragDropObject*>::iterator iEnd    = list.end();
	vector<DragDropObject*>::iterator iSorter = iBegin;
	int                steps   = list.size();

	// Find a place to put the file. The list is sorted in descending 
	// date order.
	while (iBegin != iEnd)
	{
	  // start with the iterator at the current beginninf of the list
	  iSorter = iBegin;
	  // find the middle
	  steps = (int)(steps / 2);
	  // move the iterator to the middle
	  for (int i = 0; i < steps; i++)
	  {
		 ++iSorter;
	  }
	  // if the date of the file being inserted is earlier or equal 
	  // to the date of the ciurrent iterator position
	  if (pFile->GetKey() >=((*iSorter)->GetKey()))
	  {
		 // change the beginning of the list to the current  
		 // iterator position
		 iBegin = iSorter;
		 // if we didn't move at all, and if we aren't at the  
		 // end of the list,  move the beginning one more step.
		 if (steps == 0 && iBegin != iEnd)
		 {
			++iBegin;
		 }
		 // we need to do it this way because eventually, you just 
		 // run out of "steps" (it's equal to 0), and the routine 
		 // would just sit there on the same iterator forever.  If 
		 // it gets to this point, it's safe to assume that simply 
		 // moving the iterator one more step in the appropriate 
		 // direction will locate the correct insertion point.
	  }
	  else
	  {
		 iEnd = iSorter;
		 if (steps == 0 && iEnd != iBegin)
		 {
			--iEnd;
		 }
	  }
	}
	iSorter = iEnd;
	list.insert(iSorter, pFile);
}



//----------------------------------------------------------------------------
void CObjectDockingControlBarView::OnSize(UINT nType, int cx, int cy) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	DragDropView::OnSize(nType, cx, cy);

	if(GET_PARAMETER("PaletteAutolayout")=="true")
	{
	   vector<DragDropObject*>           objCollection;
	   vector<DragDropObject*>::iterator theIterator;

	   int x = 10;
	   int y = -10;
	   int new_y=-10;
	   DragDropObject   *obj  = NULL;
	   DragDropDocument *pDoc = GetDocument();

	   pDoc->SetDocumentSize(CSize(cx*2,cy+10));

	   // Alle Toplevelobjekte in einem Set sammeln
	   //
	   for( POSITION pos = pDoc->GetFirstObjectPos(); pos != NULL; ){
		  obj = pDoc->GetNextObject( pos );
		  if(obj->GetParent()==NULL){
			  SortIntoList(obj, objCollection);
		  }
	   }


  		theIterator = objCollection.begin();
	   while(theIterator != objCollection.end()){
		  if(x > (cx*2.5+20)){
			 x =10;
			 y= new_y;
		  }
		  (*theIterator)->SetLocation(CPoint(x,y));
		  x = x + (*theIterator)->GetBoundingRect().Width()+30;
		  new_y = min(new_y,y-abs((*theIterator)->GetBoundingRect().Height())-30);
		  theIterator++;
	   }
	}
}


//----------------------------------------------------------------------------
void CObjectDockingControlBarView::OnEditPalette() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	// TODO: Add your command handler code here
//	LogManager::log(LogManager::debug1,(char*)(LPCSTR)("Filename: "+ s_paletteFileToOpen));
	((DigitalSimulatorApp*)AfxGetApp())->OpenDocumentFile(s_paletteFileToOpen);
}

//----------------------------------------------------------------------------
void CObjectDockingControlBarView::OnUpdateEditPalette(CCmdUI* pCmdUI){
//----------------------------------------------------------------------------
	PROC_TRACE;

	// TODO: Add your command update UI handler code here
	
}


//----------------------------------------------------------------------------
void CObjectDockingControlBarView::OnPaletteAutolayout(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CString param = GET_PARAMETER("PaletteAutolayout");
	SET_PARAMETER("PaletteAutolayout",param=="true"?"false":"true");
}


//----------------------------------------------------------------------------
void CObjectDockingControlBarView::OnUpdatePaletteAutolayout(CCmdUI* pCmdUI){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CString param = GET_PARAMETER("PaletteAutolayout");
	//SET_PARAMETER("PaletteAutolayout",param=="true"?"false":"true");
	pCmdUI->SetCheck(param=="true");
}
