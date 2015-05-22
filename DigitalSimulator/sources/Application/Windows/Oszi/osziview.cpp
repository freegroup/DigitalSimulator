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

// libraries\PNG
#include "PNGImageDC.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\Debug\LogManager.h"
#include "Application\Windows\Workplace\DigitalTraineeStudioView.h"
#include "Application\Dialogs\DialogOsziOptions.h"
#include "Application\Objects\buildin\common\ElectricBitmap.h"

#include "OsziDoc.h"

#include "OsziView.h"


/////////////////////////////////////////////////////////////////////////////
// COsziView
IMPLEMENT_DYNCREATE(COsziView, DragDropGridView)

BEGIN_MESSAGE_MAP(COsziView, DragDropGridView)
	//{{AFX_MSG_MAP(COsziView)
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	ON_COMMAND(ID_OPTIONS, OnOptions)
   ON_COMMAND(ID_OSZIGRID, OnGrid)
   ON_UPDATE_COMMAND_UI(ID_OSZIGRID, OnUpdateGrid)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_DATEI_EXPORT_PNG, OnDateiExportPng)
	//}}AFX_MSG_MAP
   ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



//----------------------------------------------------------------------------
COsziView::COsziView(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_gridNotifyee.setListener(this);
   m_gridXNotifyee.setListener(this);
   m_gridYNotifyee.setListener(this);
   m_fgColorNotifyee.setListener(this);
   m_bgColorNotifyee.setListener(this);
   m_zoomNotifyee.setListener(this);
   m_directionNotifyee.setListener(this);

   m_isInverted = false;
}



//----------------------------------------------------------------------------
COsziView::~COsziView(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
int COsziView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (inherited::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Initialisierung darf nicht in den Konstruktor gelegt werden
   // da einige  Funktionen 'Invalidate()' aufrufen und im Konmstruktor
   // noch keine gültiger Eintrag in der VirtuellenTabelle vorhanden ist
   // (DEBUG Assert)
   //
   m_linkedView = NULL;
   SetGridHeight(max(10,atol(GET_PARAMETER("OsziGridY"))));
   SetGridWidth(max(10,atol(GET_PARAMETER("OsziGridX"))));
   SetGridOrigin(CPoint(0,0));
   SetGridColor((COLORREF)atol(GET_PARAMETER("OsziFgColor")));
   SetSnapMove(SnapJump);

   setGrid(GET_PARAMETER("OsziGrid"));
   SetScale(max(50,atol(GET_PARAMETER("OsziZoom"))));
   
   OnInitialUpdate();
  
	return 0;
}

//----------------------------------------------------------------------------
void COsziView::OnInitialUpdate(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::OnInitialUpdate();
   GetDocument()->SetPaperColor(atoi(GET_PARAMETER("OsziBgColor")));
   GetDocument()->SetDocumentSize(CSize(20000,600));
}

//----------------------------------------------------------------------------
void COsziView::OnOptions(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CDialogOsziOptions dlg;

   dlg.DoModal();
}


//----------------------------------------------------------------------------
void COsziView::OnContextMenu(CWnd*, CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   UINT           menuId = IDR_POPUP_OSZI;
   CClientDC      dc(this);
   CPoint pointLP = point;

   ScreenToClient(&pointLP);

   //keystroke invocation
   if (point.x == -1 && point.y == -1)   {
      CRect rect;
      GetClientRect(rect);
      ClientToScreen(rect);

      point = rect.TopLeft();
      point.Offset(5, 5);
   }

   CMenu menu;
   VERIFY(menu.LoadMenu(menuId));

   CMenu* pPopup = menu.GetSubMenu(0);
   assert(pPopup != NULL);

   TRANSLATE(pPopup);
   pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, GetParent());
}


//----------------------------------------------------------------------------
void COsziView::OnGrid() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(GET_PARAMETER("OsziGrid") == "On"){
      SET_PARAMETER("OsziGrid","Off");
   }
   else{
      SET_PARAMETER("OsziGrid","On");
   }
}

//----------------------------------------------------------------------------
void COsziView::Print(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   OnFilePrint();
}

//----------------------------------------------------------------------------
void COsziView::OnUpdateGrid(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->SetCheck( (GET_PARAMETER("OsziGrid") == "On") ? TRUE :FALSE) ;      
}

//----------------------------------------------------------------------------
void COsziView::SetGridWidth(int value){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::SetGridWidth(max(10,value));
}

//----------------------------------------------------------------------------
void COsziView::SetDirection(const CString& direction){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if(direction == "RIGHT")
	{
        CSize szRes = Metrics::getPixelsPerCM();
        double PixelsPerUnit_x = (double)szRes.cx;
        double PixelsPerUnit_y = (double)szRes.cy;
        int cxx = (int) (-PixelsPerUnit_x * this->GetScale() / 100 ) ;
        int cyy = (int) (-PixelsPerUnit_y * this->GetScale() / 100 ) ;  

	    GetDC()->SetViewportExt(cxx , cyy ) ;
    }
	else
	{
		this->GetDC();
        CSize szRes = Metrics::getPixelsPerCM();
        double PixelsPerUnit_x = (double)szRes.cx;
        double PixelsPerUnit_y = (double)szRes.cy;
        int cxx = (int) (PixelsPerUnit_x * this->GetScale() / 100 ) ;
        int cyy = (int) (-PixelsPerUnit_y * this->GetScale() / 100 ) ;  

	    GetDC()->SetViewportExt(cxx , cyy ) ;
	}
	LogManager::log(LogManager::debug1,(char*)(LPCSTR)("direction: "+direction));
}

//----------------------------------------------------------------------------
void COsziView::SetGridHeight(int value){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::SetGridHeight(max(10,value));
}

//----------------------------------------------------------------------------
void COsziView::setGrid(const CString &value){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(value =="On"){
      SetGridStyle(GridLine);
   }
   else {
      SetGridStyle(GridInvisible);
   }
}


//----------------------------------------------------------------------------
void COsziView::SetLinkedView(CDigitalTraineeStudioView *pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_linkedView = pView;
}


//----------------------------------------------------------------------------
void COsziView::RemoveObject(DragDropObject* pObject){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::RemoveObject( pObject);
   SortStrokes();
   if (m_pDocument) m_pDocument->SetModifiedFlag(FALSE);
}


//----------------------------------------------------------------------------
void COsziView::SortStrokes(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   long loop;
   DragDropObject   *obj  = NULL;
   DragDropDocument *pDoc = GetDocument();
   long         newX = 0;
   long         newY = 0;

   CTypedSortableObArray< COsziStroke* > strokeArray;

   for( POSITION pos = pDoc->GetFirstObjectPos(); pos != NULL; ){
      obj = pDoc->GetNextObject( pos );
      if (obj->IsKindOf(RUNTIME_CLASS(COsziStroke)))
         strokeArray.Add((COsziStroke*)obj );
   }

   strokeArray.Sort(COsziStroke::CompBackward);

   long yOffset= GetGridHeight();

   for( loop=0 ;loop <strokeArray.GetSize() ; loop++) {
      newX = 0;
      newY = -(loop*yOffset+2);
      strokeArray[loop]->SetLocation(CPoint(newX,newY));
   }
}


//----------------------------------------------------------------------------
void COsziView::Add(COsziStroke * stroke){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(stroke!= NULL){
      COsziDoc *pDoc    = (COsziDoc*)GetDocument();
      if(pDoc){
         long      counter = pDoc->GetElementCount()/2;
         stroke->SetLocation(CPoint(0,-(counter*GetGridHeight())) );
         pDoc->AddObjectAtTail(stroke);
         // Only to get a notfication if the object will be destroid
         // or removed from the view
         AddObjectAtHead(stroke);
         pDoc->SetDocumentSize(CSize(20000,(counter+1)*GetGridHeight()+10));
      }
   }
}


//----------------------------------------------------------------------------
void COsziView::OnShowWindow(BOOL bShow, UINT nStatus) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnShowWindow(bShow, nStatus);
	
   if( (bShow == TRUE) && (m_linkedView != NULL))
       m_linkedView->PopToTop();
}



//----------------------------------------------------------------------------
void COsziView::OnLButtonDblClk(UINT nFlags, CPoint point) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   OnOptions();
}

//----------------------------------------------------------------------------
void COsziView::OnResetOszi() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   #pragma TODO("Funktion 'OnResetOszi' ist noch fehlerhaft und wird deaktiviert")
   // Die einzelnen Tracelinien liegen danach alle übereinander
   // Der Aufruf dieser Funktion wird verhindert indem der Eintrag
   // im Popupmenu entfernt wird.
   //
   DragDropObject *obj  = NULL;
   COsziDoc       *pDoc = (COsziDoc*)GetDocument();

   for( POSITION pos = pDoc->GetFirstObjectPos(); pos != NULL; ){
      obj = pDoc->GetNextObject( pos );
      if (obj->IsKindOf(RUNTIME_CLASS(COsziStroke))){
         ((COsziStroke*)obj)->StartStroke();
         ((COsziStroke*)obj)->Set(CLogicValue::High);
         ((COsziStroke*)obj)->Set(CLogicValue::Low);
      }
   }
}


void COsziView::OnDateiExportPng() 
{
   static char  *filter   = "PNG Image (*.png)|*.png||";
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char fnameOszi[_MAX_FNAME];
	char ext[_MAX_EXT];

   _splitpath((LPCSTR) m_linkedView->GetDocument()->GetTitle(), drive, dir, fname, ext );

   sprintf(fnameOszi,"Oszi%s",fname);

   CFileDialog  dlg( FALSE, "png",fnameOszi,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter );

   if(dlg.DoModal()==IDOK) 
   {
      CPoint oldPos   = GetScrollPosition();
      float  oldScale = m_iScale;

      ScrollToPosition(CPoint(0,0));
      SetScale(100);

      PNGImageDC dc;
      CString path = dlg.GetPathName();
      GetDocument()->SetMinSize(CSize(10,10));
      int x = GetDocument()->GetMinLayoutSize().cx/3;
      int y = GetDocument()->GetMinLayoutSize().cy/3;
      dc.Create(CSize(x,y));
      OnPrepareDC(&dc,NULL);
      OnDraw(&dc);

      dc.Save(path);

      SetScale(oldScale);
      ScrollToPosition(oldPos);
   }
   else
   {
   }
}
