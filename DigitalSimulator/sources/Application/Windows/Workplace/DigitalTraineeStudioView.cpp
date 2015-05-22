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
#include <io.h>
#include "stdafx.h"
#include "afxpriv.h"

// libraries/png/
#include "PNGImageDC.h"
// libraries/crypro/
#include "SHA.h"
// libraries/jni/
#include "ProxyArray.h"

#include "utils\HelpIds.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\Objects\buildin\common\ElectricText.h"
#include "Application\Objects\buildin\common\ElectricBitmap.h"
#include "Application\Windows\MainFrm.h"
#include "Application\Windows\Oszi\OsziView.h"
#include "Application\Windows\Workplace\DigitalTraineeStudioView.h"
#include "Application\Dialogs\CommonDialogs\TranslatePrintDialog.h"
#include "Application\Windows\ChildFrm.h"
#include "Application\Objects\buildin\digital\DDENode.h"
#include "Application\Objects\buildin\digital\DDEOuputNode.h"
#include "Application\Objects\buildin\digital\DDEInputNode.h"
#include "Application\Objects\plugin\DLL\SerialPort\SerialOutNode.h"
#include "Application\Objects\plugin\DLL\SerialPort\SerialInNode.h"
#include "Application\Dialogs\Export\DialogExport.h"
#include "Application\Dialogs\DocumentLock\DialogLockDocument.h"
#include "Application\Dialogs\DocumentLock\DialogUnlockDocument.h"

#include "Application\Objects\plugin\java\JavaPluginManager.h"
#include "Application\JavaBinding\ApplicationProxyWrapper.h"

// Default object position
const int SIMULATION_TIMER        = 1;
const int SIMULATION_RECORD_TIMER = 2;

//const int iOriginCx = 100;      // default origin
//const int iOriginCy = -100;
//const int iOriginOffsetX = 10;
//const int iOriginOffsetY = -10;

//#define DIGITAL_OBJ "DigitalSimulatorObject"
CDigitalTraineeStudioView* CDigitalTraineeStudioView::s_activeView=NULL;
long CDigitalTraineeStudioView::s_counter=1;

using namespace de::freegroup::jnipp;

IMPLEMENT_DYNCREATE(CDigitalTraineeStudioView, DragDropGridView)

BEGIN_MESSAGE_MAP(CDigitalTraineeStudioView, DragDropGridView)
	//{{AFX_MSG_MAP(CDigitalTraineeStudioView)
	ON_COMMAND(ID_INSERT_OBJECT, OnInsertObject)
	ON_COMMAND(ID_ALIGN_DOWN, OnAlignDown)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_DOWN, OnUpdateAlignDown)
	ON_COMMAND(ID_ALIGN_LEFT, OnAlignLeft)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_LEFT, OnUpdateAlignLeft)
	ON_COMMAND(ID_ALIGN_RIGHT, OnAlignRight)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_RIGHT, OnUpdateAlignRight)
	ON_COMMAND(ID_ALIGN_UP, OnAlignUp)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_UP, OnUpdateAlignUp)
	ON_COMMAND(ID_GRID, OnGrid)
	ON_UPDATE_COMMAND_UI(ID_GRID, OnUpdateGrid)
	ON_UPDATE_COMMAND_UI(ID_SET_GRID, OnUpdateSetGrid)
	ON_COMMAND(ID_START_SIMULATION, OnStartSimulation)
	ON_COMMAND(ID_ZOOM_DECREASE, OnZoomDecrease)
	ON_COMMAND(ID_ZOOM_FIT, OnZoomFit)
	ON_COMMAND(ID_ZOOM_INCREASE, OnZoomIncrease)
	ON_COMMAND(ID_ZOOM_STANDARD, OnZoomStandard)
	ON_WM_TIMER()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_OBJECT_OPTION, OnObjectOption)
	ON_COMMAND(ID_OBJECT_EXTENDED_OPTION, OnObjectExtendedOption)
	ON_UPDATE_COMMAND_UI(ID_START_SIMULATION, OnUpdateStartSimulation)
	ON_WM_CREATE()
	ON_COMMAND(ID_OBJECT_TO_BACK, OnObjectToBack)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_TO_BACK, OnUpdateObjectToBack)
	ON_COMMAND(ID_OBJECT_TO_FRONT, OnObjectToFront)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_TO_FRONT, OnUpdateObjectToFront)
	ON_WM_DESTROY()
	ON_COMMAND(ID_INSERT_REMOVE_VIEWPOINT, OnInsertRemoveViewPoint)
	ON_UPDATE_COMMAND_UI(ID_INSERT_REMOVE_VIEWPOINT, OnUpdateInsertRemoveViewPoint)
	ON_COMMAND(ID_REMOVE_STROKE_SEGMENT, OnRemoveStrokeSegment)
	ON_UPDATE_COMMAND_UI(ID_REMOVE_STROKE_SEGMENT, OnUpdateRemoveStrokeSegment)
	ON_COMMAND(ID_INSERT_STROKE_SEGMENT, OnInsertStrokeSegment)
	ON_UPDATE_COMMAND_UI(ID_INSERT_STROKE_SEGMENT, OnUpdateInsertStrokeSegment)
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_OBJECT_BASICS, OnObjectBasics)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_BASICS, OnUpdateObjectBasics)
	ON_WM_HELPINFO()
	ON_UPDATE_COMMAND_UI(ID_OBJECT_HELP, OnUpdateObjectHelp)
	ON_WM_LBUTTONDBLCLK()
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateFileClose)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_DATEI_EXPORT, OnUpdateDateiExport)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_COMMAND(ID_START_SIMULATION_RECORD, OnStartSimulationRecord)
	ON_UPDATE_COMMAND_UI(ID_START_SIMULATION_RECORD, OnUpdateStartSimulationRecord)
	ON_COMMAND(ID_PROTECT_DOCUMENT, OnProtectDocument)
	ON_UPDATE_COMMAND_UI(ID_PROTECT_DOCUMENT, OnUpdateProtectDocument)
	ON_COMMAND(ID_CONNECTOR_FLYOVER, OnConnectorFlyover)
	ON_UPDATE_COMMAND_UI(ID_CONNECTOR_FLYOVER, OnUpdateConnectorFlyover)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_CUT, OnUpdateEditCut)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_INSERT_OBJECT, OnInsertObject)
	ON_COMMAND(ID_DATEI_EXPORT_JNI, OnDateiExportJni)
	ON_UPDATE_COMMAND_UI(ID_DATEI_EXPORT_JNI, OnUpdateDateiExportJni)
	ON_COMMAND(ID_OBJECT_HELP, OnObjectHelp)
	ON_COMMAND(ID_SET_GRID, OnGrid)
	ON_COMMAND(ID_OBJECT_CUT, OnEditCut)
	ON_COMMAND(ID_OSZI_PRINT, OnOsziPrint)
	ON_UPDATE_COMMAND_UI(ID_OSZI_PRINT, OnUpdateOsziPrint)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_WM_CONTEXTMENU()
	ON_MESSAGE(WM_HELPHITTEST, OnHelpHitTest)
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CDigitalTraineeStudioView::CDigitalTraineeStudioView(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_gridXNotifyee.setListener(this);
	m_gridYNotifyee.setListener(this);
	m_gridNotifyee.setListener(this);
	m_gridStyleNotifyee.setListener(this);
   m_connectorFlyoverNotifyee.setListener(this);

   m_osziView = NULL;

   useConnectorFlyover     = (GET_PARAMETER("ConnectorFlyover")).CompareNoCase("true")==0?true:false;
   isRunningNormalMode     = false;
	isRunningAVIMode        = false;
   m_flyoverLink           = NULL;
   m_lastInsertedObjectTyp = "OBJ_AND";
}

//----------------------------------------------------------------------------
CDigitalTraineeStudioView::~CDigitalTraineeStudioView(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	// send an event to the corresponding palette view if an 'gop' file has been edit
	//
	CString path = GetDocument()->GetPathName();
	if((path.GetLength()>4) && (path.Find(".gop")!=-1))
		SET_PARAMETER("PaletteDocumentReload",path);

   // Important to do this in this state!
   // Das Dokument enthaelt eventuell Links mit dazugehoerigen
   // OsziStrokes. Wird erst der View aus der OsziBar geloescht,
   // koennen die OsziStrokes sich nicht mehr aus dem (entfernten) View
   // austragen -> Exception, da die OsziStrokes auf einen geloeschten
   // View zugreifen
   //
   GetDocument()->DeleteContents();

   // uiui.....  ooooohhh FIXME
   //
   m_osziView->SetLinkedView(NULL);
   ((DigitalSimulatorApp*)AfxGetApp())->MainFrame()->OsziBar()->RemoveView(m_osziView);
}


//----------------------------------------------------------------------------
DragDropLink* CDigitalTraineeStudioView::NewLink(DragDropPort* pFrom, DragDropPort* pTo){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pFrom != NULL);
   assert(pTo != NULL);

   if(m_documentProtection != NULL) 
      return NULL;

   CElectricPortLink* pLink = NULL;
   if ( (pFrom->IsKindOf(RUNTIME_CLASS(CElectricPort))) &&
      (pTo->IsKindOf(RUNTIME_CLASS(CElectricPort))) ){
      pLink = new CElectricPortLink(pFrom, pTo);
      pLink->DoCalculate();
   }
   assert(pLink != NULL);
    
   DragDropDocument* pDoc = GetDocument( );
   pDoc->AddObjectAtTail(pLink);
   return (DragDropLink*)pLink;
}


//----------------------------------------------------------------------------
BOOL CDigitalTraineeStudioView::ValidSourcePort(DragDropPort* pFrom){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert (pFrom != NULL);

   if(pFrom == NULL)
      return FALSE;
    
   if ( pFrom->IsKindOf(RUNTIME_CLASS(CElectricPort)) )  {
      CElectricPort *pf = (CElectricPort*)pFrom;
      // Es kann nur 1 Link in einem Inputport enden
      //
      if(pf->IsInput()){
          if( pf->GetLinks()->GetCount()>1){
              return FALSE;
          }
      }
   }

   return TRUE;
}

//----------------------------------------------------------------------------
BOOL CDigitalTraineeStudioView::ValidLink(DragDropPort* pFrom, DragDropPort* pTo){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pFrom != NULL);
   assert(pTo   != NULL);
   
   if( (pFrom == NULL) || (pTo== NULL))
      return FALSE;

   if ( (pFrom->IsKindOf(RUNTIME_CLASS(CElectricPort))) &&
      (pTo->IsKindOf(RUNTIME_CLASS(CElectricPort))) ) {
      CElectricPort *pf = (CElectricPort*)pFrom;
      CElectricPort *pt = (CElectricPort*)pTo;

      if(pf->IsInput()){
          if( pf->GetLinks()->GetCount()>1){
              return FALSE;
          }
      }

      if(pt->IsInput()){
          if( pt->GetLinks()->GetCount()!=0){
              return FALSE;
          }
      }
      return (pf->IsOutput() && pt->IsInput()) || (pf->IsInput() && pt->IsOutput());
   }

   return TRUE;
}

//----------------------------------------------------------------------------
BOOL CDigitalTraineeStudioView::DropObject(DragDropView* pSourceView, DragDropObject* pSourceObject, CPoint pPoint, UINT nFlags){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_documentProtection != NULL) 
      return false;

   return inherited::DropObject(pSourceView, pSourceObject,  pPoint,  nFlags);
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnInsertObject() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropDocument* pDoc = GetDocument();
   assert (pDoc != NULL);
   if(pDoc == NULL)
      return;

   CElectricNode *obj=new CElectricNode(m_lastInsertedObjectTyp);
   obj->SetLocation(m_contextMenuMousePos.x,m_contextMenuMousePos.y);
   pDoc->AddObjectAtTail(obj);
   if(obj->DoExtendedOption())
   {
      m_lastInsertedObjectTyp = obj->GetKey();
   }
   else
   {
      pDoc->DeleteObject(obj);
      pDoc->SetModifiedFlag(FALSE);
   }

   
   //pDoc->UpdateAllViews(NULL, Refresh_Display, NULL);    
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnAlignDown() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject   *pPrimary = m_pSelection->PrimarySelection();
   DragDropDocument *pDoc     = GetDocument();
   assert(pDoc != NULL);
   assert(pPrimary != NULL);
   if((pPrimary == NULL) || (pDoc == NULL))
      return;

   int xLeft = pPrimary->GetTopLeft().x;

   pDoc->StartAutomation();   // will hide selection handles
   for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ) {
       DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
       if (pObject != pPrimary && !pObject->IsNoLayout())
           pObject->SetSpotLocationOffset(DragDropObject::spotBottomLeft, pPrimary, DragDropObject::spotBottomLeft, 
               pObject->GetTopLeft().x - xLeft, 0 );

   }
   pDoc->EndAutomation();  // will show selection handles
   pDoc->SetModifiedFlag();
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateAlignDown(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   int i=0;
   for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ){
     i++;
     if(i==2) break;
     DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
   }
   pCmdUI->Enable((i>1));
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnAlignLeft() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject   *pPrimary = m_pSelection->PrimarySelection();
   DragDropDocument *pDoc     = GetDocument();
   assert (pPrimary != NULL);
   assert (pDoc != NULL);
   if((pPrimary == NULL) || (pDoc == NULL))
      return;

   int yTop = pPrimary->GetTopLeft().y;

   pDoc->StartAutomation();   // will hide selection handles
   for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ) {
        DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
        if (pObject != pPrimary && !pObject->IsNoLayout())
            pObject->SetSpotLocationOffset(DragDropObject::spotTopLeft, pPrimary, DragDropObject::spotTopLeft, 
                  0, pObject->GetTopLeft().y - yTop);

   }
   pDoc->EndAutomation();  // will show selection handles
   pDoc->SetModifiedFlag();
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateAlignLeft(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   int i=0;
   for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ){
     i++;
     if(i==2) break;
     DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
   }
   pCmdUI->Enable(i>1);
   
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnAlignRight() {
//----------------------------------------------------------------------------
	PROC_TRACE;


   DragDropObject   *pPrimary = m_pSelection->PrimarySelection();
   DragDropDocument *pDoc     = GetDocument();
   assert (pPrimary != NULL);
   assert (pDoc != NULL);
   if((pPrimary == NULL) || (pDoc == NULL))
      return;

   int yTop = pPrimary->GetTopLeft().y;

   pDoc->StartAutomation();   // will hide selection handles
   for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ) {
        DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
        if (pObject != pPrimary && !pObject->IsNoLayout())
            pObject->SetSpotLocationOffset(DragDropObject::spotTopRight, pPrimary, DragDropObject::spotTopRight, 
                  0, pObject->GetTopLeft().y - yTop);

   }
   pDoc->EndAutomation();  // will show selection handles
   pDoc->SetModifiedFlag();
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateAlignRight(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pSelection != NULL);
   if(m_pSelection == NULL) {
      pCmdUI->Enable(false);
      return;
   }

   int i=0;
   for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ){
     i++;
     if(i==2) break;
     DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
   }
   pCmdUI->Enable(i>1);
   
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnAlignUp() {
//----------------------------------------------------------------------------
	PROC_TRACE;


   DragDropObject   *pPrimary = m_pSelection->PrimarySelection();
   DragDropDocument *pDoc     = GetDocument();
   assert (pPrimary != NULL);
   assert (pDoc != NULL);
   if((pPrimary == NULL) || (pDoc == NULL))
      return;

   int xLeft = pPrimary->GetTopLeft().x;

   pDoc->StartAutomation();   // will hide selection handles
   for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ){
        DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
        if (pObject != pPrimary && !pObject->IsNoLayout())
            pObject->SetSpotLocationOffset(DragDropObject::spotTopLeft, pPrimary, DragDropObject::spotTopLeft, 
                pObject->GetTopLeft().x - xLeft, 0 );

   }
   pDoc->EndAutomation();  // will show selection handles
   pDoc->SetModifiedFlag();
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateAlignUp(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pSelection != NULL);
   if(m_pSelection == NULL) {
      pCmdUI->Enable(false);
      return;
   }

   int i=0;
   for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ){
     i++;
     if(i==2) break;
     DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
   }
   pCmdUI->Enable(i>1);
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnGrid() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(GET_PARAMETER("Grid") == "On"){
      SET_PARAMETER("Grid","Off");
   }
   else{
      SET_PARAMETER("Grid","On");
   }
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateGrid(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->SetCheck( (GetGridStyle() == GridInvisible) ? FALSE :TRUE) ;      
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateSetGrid(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(IsEditingTextControl()) {
      pCmdUI->Enable(false);
      return;
   }

   pCmdUI->SetCheck( (GetGridStyle() == GridInvisible) ? FALSE :TRUE) ;      
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnStartSimulation() {
//----------------------------------------------------------------------------
	PROC_TRACE;
  
   isRunningNormalMode = !isRunningNormalMode;
   if(isRunningNormalMode == true) 
   {
      for( POSITION pos = GetDocument()->GetFirstObjectPos(); pos != NULL; )
          ((DragDropObject*)GetDocument()->GetNextObject( pos ))->OnTimerStart();
      SetTimer(SIMULATION_TIMER,50,NULL);

   }
   else 
   {
      KillTimer(SIMULATION_TIMER);
      for( POSITION pos = GetDocument()->GetFirstObjectPos(); pos != NULL; )
          ((DragDropObject*)GetDocument()->GetNextObject( pos ))->OnTimerEnd();
   }
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateStartSimulation(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(IsEditingTextControl()) {
      pCmdUI->Enable(false);
      return;
   }
   // Falls ein AVI aufgezeichnet wird, darf die normale
   // simulation nicht gestartet werden
   //
   pCmdUI->Enable(!isRunningAVIMode);

   if(isRunningNormalMode){
      pCmdUI->SetText(TRANSLATE("MENU.POPUP.VIEW.SIMULATION"));
      pCmdUI->SetCheck(1);
   }
   else{
      pCmdUI->SetText(TRANSLATE("MENU.POPUP.VIEW.SIMULATION"));
      pCmdUI->SetCheck(0);
   }
}

#ifdef WITH_AVI
//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnStartSimulationRecord() {
//----------------------------------------------------------------------------
	PROC_TRACE;
  
   isRunningAVIMode = !isRunningAVIMode;
   if(isRunningAVIMode == true) 
   {
      CPoint oldPos   = GetScrollPosition();
      float  oldScale = m_iScale;
      ScrollToPosition(CPoint(0,0));
      SetScale(100);
      PNGImageDC dc;
      GetDocument()->SetMinSize(CSize(10,10));
      int x = GetDocument()->GetMinLayoutSize().cx/3;
      int y = GetDocument()->GetMinLayoutSize().cy/3;
      dc.Create(CSize(x,y));
      OnPrepareDC(&dc,NULL);
      SetScale(oldScale);
      ScrollToPosition(oldPos);

      if(m_aviFile.Open(dc.cBitmap ))
      {
         for( POSITION pos = GetDocument()->GetFirstObjectPos(); pos != NULL; )
             ((DragDropObject*)GetDocument()->GetNextObject( pos ))->OnTimerStart();
         SetTimer(SIMULATION_RECORD_TIMER,50,NULL);
      }
      else
      {
         isRunningAVIMode = false;
      }

   }
   else 
   {
      KillTimer(SIMULATION_RECORD_TIMER);
      m_aviFile.Close();
      for( POSITION pos = GetDocument()->GetFirstObjectPos(); pos != NULL; )
          ((DragDropObject*)GetDocument()->GetNextObject( pos ))->OnTimerEnd();
   }	
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateStartSimulationRecord(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(IsEditingTextControl()) {
      pCmdUI->Enable(false);
      return;
   }


   pCmdUI->Enable(!isRunningNormalMode);

   if(isRunningAVIMode){
      pCmdUI->SetText(TRANSLATE("MENU:POPUP.VIEW.STOPRECORD"));
      pCmdUI->SetCheck(1);
   }
   else{
      pCmdUI->SetText(TRANSLATE("MENU.POPUP.VIEW.STARTRECORD"));
      pCmdUI->SetCheck(0);
   }
}

#endif


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnZoomDecrease() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetScale(GetScale()-10);
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnZoomFit() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(GetDocument() != NULL);

   GetDocument()->SetMinSize(CSize(100,100));    // make sure the doc doesn't have too big a default min size
   SetScaleToFit();

}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnZoomIncrease() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetScale(GetScale()+10);
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnZoomStandard() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetScale(100);
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::SetScale(int percent, float clientRectFactor){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::SetScale(percent, clientRectFactor);
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnTimer(UINT nIDEvent) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   switch(nIDEvent)   {
   case SIMULATION_TIMER:
      {
       assert(GetDocument() != NULL);

       for( POSITION pos = GetDocument()->GetFirstObjectPos(); pos != NULL; )
          ((DragDropObject*)GetDocument()->GetNextObject( pos ))->DoCalculate();
      }
      break;   
   case SIMULATION_RECORD_TIMER:
      {
       assert(GetDocument() != NULL);

       for( POSITION pos = GetDocument()->GetFirstObjectPos(); pos != NULL; )
          ((DragDropObject*)GetDocument()->GetNextObject( pos ))->DoCalculate();

       { // AVI export
         CPoint oldPos   = GetScrollPosition();
         float  oldScale = m_iScale;

         ScrollToPosition(CPoint(0,0));
         SetScale(100);

         PNGImageDC dc;
         GetDocument()->SetMinSize(CSize(10,10));
         int x = GetDocument()->GetMinLayoutSize().cx/3;
         int y = GetDocument()->GetMinLayoutSize().cy/3;
         dc.Create(CSize(x,y));
         OnPrepareDC(&dc,NULL);
         OnDraw(&dc);

         m_aviFile.Add(dc.cBitmap );

         SetScale(oldScale);
         ScrollToPosition(oldPos);
       }
     }
      break;
   default:
      inherited::OnTimer(nIDEvent);
      break;
   }
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnEditCut() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(GetSelection() != NULL);
   assert(GetDocument() != NULL);

//   CopySelectedObjectToClipboard();
   GetSelection()->DeleteObjects();
   GetDocument()->SetModifiedFlag();
   m_flyoverLink=NULL;
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateEditCut(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(!m_pSelection->IsEmpty());
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnContextMenu(CWnd*, CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   UINT           menuId = IDR_POPUP_VIEW;
   // it is running a simulation (without any AVI recording)
   //
   if(isRunningNormalMode == true)
   {
        menuId =IDR_POPUP_VIEW_RUNNING;
   }
   else
   {
      CClientDC      dc(this);
      CPoint pointLP = point;

      ScreenToClient(&pointLP);
      OnPrepareDC(&dc);
      dc.DPtoLP(&pointLP);
      DragDropObject* obj = DoPickInDocument(&dc, pointLP, TRUE); // TRUE = pick selectable object
      m_contextMenuMousePos=pointLP;
      if(obj!=NULL){
         GetSelection()->ClearSelection();
         // nur das Objekt selektieren falls das Dokument keinen
         // Schreibschutz hat
         //
         if( m_documentProtection==NULL )
            GetSelection()->SelectObject(obj);
         menuId = obj->GetContextMenuId();
      }
   }
   // Falls das selektierte Objekt kein Menu hat,
   // braucht auch nichts gemacht werden
   //
   if(menuId<=0)
      return;

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

	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
	  pWndPopupOwner = pWndPopupOwner->GetParent();
	CMenu* pPopup = menu.GetSubMenu(0);
	assert(pPopup != NULL);
	TRANSLATE(pPopup);


	// Show the menu!
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnObjectOption() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropSelection  *s   = GetSelection();
   assert (s != NULL); 
   if(s==NULL) return;

   DragDropObject *obj =  (DragDropObject*)s->PrimarySelection();


   if(obj!=NULL && obj->DoOption()){
      // Recalc the selection handles. It is possible, that the 
      // size of the objact has been changed.
      //
      obj->LostSelection(s);
      obj->GainedSelection(s);
      obj->SetUpdateNeeded(TRUE);
      GetDocument()->SetModifiedFlag();
   }
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnObjectExtendedOption() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropSelection  *s   = GetSelection();
   DragDropObject     *obj = s->PrimarySelection();

   if(obj!=NULL &&  obj->DoExtendedOption()==TRUE) {
      // Recalc the selection handles. It is possible, that the 
      // size of the object has been changed.
      //
      obj->LostSelection(s);
      obj->GainedSelection(s);
      GetDocument()->SetModifiedFlag();
   }
}


//----------------------------------------------------------------------------
bool CDigitalTraineeStudioView::OnObjectHelp() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   POSITION pos=GetSelection()->GetFirstSelectedPos();
   if(pos){
      DragDropObject* obj=GetSelection()->GetNextSelected(pos);
      if(obj!=NULL){
         AfxGetApp()->WinHelp(obj->GetHelpId());
         return TRUE;
      }
   }
   AfxGetApp()->WinHelp(0L, HELP_INDEX);

   return FALSE;
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateObjectHelp(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   POSITION pos=GetSelection()->GetFirstSelectedPos();
   if(pos){
      DragDropObject* obj=GetSelection()->GetNextSelected(pos);
      if(obj!=NULL && obj->GetHelpId()!=OBJ_GENERIC && obj->GetHelpId()>0){
         pCmdUI->Enable(true);
         return;
      }
   }
   pCmdUI->Enable(false);
}

//----------------------------------------------------------------------------
LRESULT CDigitalTraineeStudioView::OnHelpHitTest(WPARAM, LPARAM lParam){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT_VALID(this);

   CPoint  p2(LOWORD(lParam),HIWORD(lParam));
   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.DPtoLP(&p2);

   DragDropObject* obj = DoPickInDocument(&dc, p2, TRUE);
   if(obj !=NULL)
      return obj->GetHelpId();
   return OBJEKTE;
}


//----------------------------------------------------------------------------
int CDigitalTraineeStudioView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (inherited::OnCreate(lpCreateStruct) == -1)
      return -1;
   
   setGrid(GET_PARAMETER("Grid"));
   setGridStyle(GET_PARAMETER("GridStyle"));
   setGridX(atoi(GET_PARAMETER("GridX")));
   setGridY(atoi(GET_PARAMETER("GridY")));


   DragDropDocument* doc   = GetDocument();
   CString    title = "";

   SetGridOrigin(CPoint(0,0));


   if(doc!=NULL)
   {
      title = doc->GetTitle();
      doc->SetMinSize(CSize(100,100));
   }

   #pragma TODO("Furchtbares 'casten'....Code muss besser strukturiert werden")
   // uiui.....  pleeeaaase FIXME
   //
   m_osziView=((DigitalSimulatorApp*)AfxGetApp())->MainFrame()->OsziBar()->AddView(title);
   m_osziView->SetLinkedView(this);
   ((DigitalSimulatorApp*)AfxGetApp())->MainFrame()->OsziBar()->SetActiveView(m_osziView);

   OnInitialUpdate();

   m_toolTip.Create(this);
   m_toolTip.SetOffset(30,30);
   m_toolTip.On(TRUE);

   return 0;
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnObjectToBack() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropDocument* pDoc = GetDocument();
   assert(pDoc != NULL);
   assert(m_pSelection != NULL);
   if((m_pSelection == NULL) || (pDoc == NULL))
      return;

   for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ) {
      DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
      pDoc->SendObjectToBack(pObject);
      pDoc->SetModifiedFlag();
   }
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateObjectToBack(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(!m_pSelection->IsEmpty());
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnObjectToFront() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropDocument* pDoc = GetDocument();
   assert(pDoc != NULL);
   assert(m_pSelection != NULL);
   if((m_pSelection == NULL) || (pDoc == NULL))
      return;

   for (POSITION pos = m_pSelection->GetFirstSelectedPos(); pos != NULL; ) {
      DragDropObject* pObject = m_pSelection->GetNextSelected(pos);
      pDoc->BringObjectToFront(pObject);
      pDoc->SetModifiedFlag();
   }
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateObjectToFront(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(!m_pSelection->IsEmpty());
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::setGridX(const long& xSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetGridWidth(xSize);
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::setGridY(const long& ySize){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetGridHeight(ySize);
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::setConnectorFlyover(const bool& flag){
//----------------------------------------------------------------------------
	PROC_TRACE;

   useConnectorFlyover = flag;
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::setGrid(const CString &value){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(value =="On"){
      setGridStyle(GET_PARAMETER("GridStyle"));
   }
   else {
     SetSnapMove(NoSnap);
     SetGridStyle(GridInvisible);
   }
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::setGridStyle(const CString &style){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(GET_PARAMETER("Grid") == "On"){
      if(style == "Cross"){
		LogManager::log(LogManager::debug1,"setting Grid to type 'CROSS'");
        SetSnapMove(SnapJump);
        SetGridStyle(GridCross);
      }
      else if(style == "Line"){
		LogManager::log(LogManager::debug1,"setting Grid to type 'LINE'");
        SetSnapMove(SnapJump);
        SetGridStyle(GridLine);
      }
      else if(style == "Dot"){
		LogManager::log(LogManager::debug1,"setting Grid to type 'DOT'");
        SetSnapMove(SnapJump);
        SetGridStyle(GridDot);
      }
   }
}




//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnDestroy() {
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   if(isRunningNormalMode ==true){
      KillTimer(SIMULATION_TIMER);
      isRunningNormalMode = false;
   }
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnInsertRemoveViewPoint() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropSelection *s   = GetSelection();
   assert(s != NULL);

   if(s == NULL) 
      return;

   DragDropObject    *obj = (DragDropObject*)s->PrimarySelection();

   if(obj && obj->IsKindOf(RUNTIME_CLASS(CElectricPortLink))){
      CElectricPortLink* link = (CElectricPortLink*)obj;
 
      if(link->GetOsziStroke() == NULL){
         COsziStroke *stroke = new COsziStroke;
         link->SetOsziStroke(stroke);
         m_osziView->Add(stroke);
      }
      else {
         link->SetOsziStroke(NULL);
      }
   }
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateInsertRemoveViewPoint(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   ScopeMutex m(this); // synchronize with other funktions

   DragDropSelection *s   = GetSelection();
   assert(s != NULL);
   if(s== NULL) return;

   DragDropObject    *obj = (DragDropObject*)s->PrimarySelection();

   if(obj && obj->IsKindOf(RUNTIME_CLASS(CElectricPortLink))){
      if(((CElectricPortLink*)obj)->GetOsziStroke() == NULL){
         pCmdUI->SetText(TRANSLATE("MENU.POPUP.LINK.INSERTVIEWPOINT"));
      }
      else {
         pCmdUI->SetText(TRANSLATE("MENU.POPUP.LINK.REMOVEVIEWPOINT"));
      }
   }
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnRemoveStrokeSegment() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   ScopeMutex m(this); // synchronize with other funktions

   DragDropSelection *s   = GetSelection();
   assert(s != NULL);
   if(s== NULL) return;

   DragDropObject    *obj = (DragDropObject*)s->PrimarySelection();

   if(obj && obj->IsKindOf(RUNTIME_CLASS(CElectricPortLink))){
      ((CElectricPortLink*)obj)->RemoveLastHitSegment();
      obj->LostSelection(s);
      obj->GainedSelection(s);
      GetDocument()->SetModifiedFlag();
   }
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateRemoveStrokeSegment(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   ScopeMutex m(this); // synchronize with other funktions

   DragDropSelection *s   = GetSelection();
   assert(s != NULL);
   if(s== NULL) return;

   DragDropObject    *obj = (DragDropObject*)s->PrimarySelection();

   if(obj && obj->IsKindOf(RUNTIME_CLASS(CElectricPortLink))){
      pCmdUI->Enable(((CElectricPortLink*)obj)->canRemoveLastHitSegment());
   }
   else{
      // Darf eigentlich nie passieren
      //
      pCmdUI->Enable(FALSE);
   }
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnInsertStrokeSegment() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropSelection *s   = GetSelection();
   assert(s != NULL);
   if(s== NULL) return;

   DragDropObject    *obj = (DragDropObject*)s->PrimarySelection();

   if(obj && obj->IsKindOf(RUNTIME_CLASS(CElectricPortLink))){
      ((CElectricPortLink*)obj)->InsertLastHitSegment();
      obj->LostSelection(s);
      obj->GainedSelection(s);
      GetDocument()->SetModifiedFlag();
   }
 
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateInsertStrokeSegment(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   pCmdUI->Enable(m_documentProtection==NULL);
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   switch(nChar){
   case VK_DELETE:
      OnEditCut();
      break;
   case VK_F1:
      break;
   default:
	   inherited::OnKeyDown(nChar, nRepCnt, nFlags);
      break;
   }
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnWindowToTop() {
//----------------------------------------------------------------------------
	PROC_TRACE;


   // The active view ist required for the Java part. It is possible to retrieve
   // the circuit data from the external Java Tool/Export/... or other plugins.
   //
   s_activeView = this;

   #pragma TODO("Furchtbares 'casten'.......Code muss besser strukturiert werden")
   ((DigitalSimulatorApp*)AfxGetApp())->MainFrame()->OsziBar()->SetActiveView(m_osziView);
   ((DigitalSimulatorApp*)AfxGetApp())->MainFrame()->OsziBar()->SetLabel(m_osziView,(LPCSTR)GetDocument()->GetTitle());
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnSetFocus(CWnd* pOldWnd) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnSetFocus(pOldWnd);

   if(pOldWnd != this){
      // The active view ist required for the Java part. It is possible to retrieve
      // the circuit data from the external Java Tool/Export/... or other plugins.
      //
      s_activeView = this;

      #pragma TODO("Furchtbares 'casten'....Code muss besser strukturiert werden")
      ((DigitalSimulatorApp*)AfxGetApp())->MainFrame()->OsziBar()->SetActiveView(m_osziView);
      ((DigitalSimulatorApp*)AfxGetApp())->MainFrame()->OsziBar()->SetLabel(m_osziView,(LPCSTR)GetDocument()->GetTitle());
   }
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateDateiExport(CCmdUI* pCmdUI) 
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   pCmdUI->Enable(!IsEditingTextControl());
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnObjectBasics() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropSelection  *s   = GetSelection();
   DragDropObject     *obj = s->PrimarySelection();

   if(obj && obj->IsKindOf(RUNTIME_CLASS(CElectricNode))) {
      CString meta = ((CElectricNode*)obj)->GetKey();   
      AfxGetApp()->OpenDocumentFile((LPCSTR)(BASIC_PATH((meta+".bas"))));
   }
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateObjectBasics(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;


   DragDropSelection  *s   = GetSelection();
   DragDropObject     *obj = s->PrimarySelection();

   if(obj && obj->IsKindOf(RUNTIME_CLASS(CElectricNode))) {
      CString meta = ((CElectricNode*)obj)->GetKey();   
      pCmdUI->Enable(_access(BASIC_PATH((meta+".bas")),00)==0);
   }
	
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	
	inherited::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


//----------------------------------------------------------------------------
BOOL CDigitalTraineeStudioView::OnHelpInfo(HELPINFO* pHelpInfo) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(!OnObjectHelp())
      return inherited::OnHelpInfo(pHelpInfo);
	
	return FALSE;
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnLButtonDblClk(UINT nFlags, CPoint point){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Falls der Simulator sich  im Simulationsmodus befindet können
   // keine Objekt optionen eingestellt werden
   //
   if(isRunningNormalMode == true)
        return;

   inherited::OnLButtonDblClk(nFlags, point);
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateFileClose(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(!IsEditingTextControl());
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateFileNew(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(!IsEditingTextControl());
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateFilePrint(CCmdUI* pCmdUI){
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(!IsEditingTextControl());
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateFileSave(CCmdUI* pCmdUI){
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(!IsEditingTextControl());
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateFileSaveAs(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(!IsEditingTextControl());
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateFileOpen(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(!IsEditingTextControl());
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnEditCopy() {
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateEditCopy(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnEditPaste() {
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateEditPaste(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnMouseMove(UINT nFlags, CPoint point) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT_VALID(this);

   CPoint pOrig = point;
   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.DPtoLP(&point);

   // Is the mouse during an DragDrop action, the tooltip must be canceld. The tooltip
   // fetches the focus and the DragDrop will be aborted after the timeout of the tooltip timer.
   // To see the effect, remove this 2 lines and try to create a link between two ports. 
   // Don't connect the second port, just move the mouse with the connector around the workplace.
   //
   if(m_pointermode!=PointerModeNone)
	   m_toolTip.Stop();


   DragDropObject* obj = DoPickInDocument(&dc, point, TRUE);
   if(obj !=NULL)
   {
      // start tooltip
      //
      m_toolTip.Set(pOrig,TRANSLATE((CString)obj->GetName()));

      // highlight the connector if the user has set the 'flyover' for connectors
      // 
      if(useConnectorFlyover && obj->IsKindOf(RUNTIME_CLASS(DragDropLink)) )
      {
         // deleted the old highlight flag
         //
         if(m_flyoverLink!=NULL)
            m_flyoverLink->SetHighlighted(false);
         // highlight the new connector
         //
         m_flyoverLink = (DragDropLink*)obj;
         m_flyoverLink->SetHighlighted(true);
      }
      else
      {
         if(m_flyoverLink!=NULL)
            m_flyoverLink->SetHighlighted(false);
         m_flyoverLink = NULL;
      }
   }
   else
   {
      if(m_flyoverLink!=NULL)
         m_flyoverLink->SetHighlighted(false);
      m_flyoverLink = NULL;
   }

   if(m_documentProtection!= NULL)
      return;

   inherited::OnMouseMove(nFlags, pOrig);
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::HandleResizing(CClientDC* pDC, CPoint pPoint, int event) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_flyoverLink = NULL;
   inherited::HandleResizing(pDC,pPoint, event);
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnInitialUpdate() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   // try to find the protection or documentation object
   //
   DragDropDocument* doc   = GetDocument();
   m_documentProtection    = NULL;
   m_documentDocumentation = NULL;
   for( POSITION pos = doc->GetFirstObjectPos(); pos != NULL; )
   {
      DragDropObject* obj=(DragDropObject*)doc->GetNextObject( pos );
      if(obj && obj->IsKindOf(RUNTIME_CLASS(DocumentProtection)))
      {
         m_documentProtection = (DocumentProtection*)obj;
        // break;
      }
      else if(obj && obj->IsKindOf(RUNTIME_CLASS(DocumentDocumentation)))
      {
         m_documentDocumentation = (DocumentDocumentation*)obj;
         //break;
      }
   }

   inherited::OnInitialUpdate();
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnPaint() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::OnPaint();
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnProtectDocument() {
//----------------------------------------------------------------------------
	PROC_TRACE;
   DragDropDocument* pDoc = GetDocument();
   assert (pDoc != NULL);

   if(m_documentProtection == NULL) 
   {
      CDialogLockDocument dlg;
      if(dlg.DoModal()==IDOK)
      {
         byte digest[CryptoPP::SHA256::DIGESTSIZE];
         CryptoPP::SHA256 sha;
         sha.CalculateDigest(digest, (const unsigned char*)(LPCSTR)dlg.m_passwd1, strlen((LPCSTR)dlg.m_passwd1));
         m_documentProtection = new  DocumentProtection();
         m_documentProtection->SetDigest(digest,CryptoPP::SHA256::DIGESTSIZE);
         pDoc->AddObjectAtTail(m_documentProtection);
      }
   }
   else 
   {
      CDialogUnlockDocument dlg;
      while(dlg.DoModal()==IDOK)
      {
         CryptoPP::SHA256 sha;
         if(sha.VerifyDigest(m_documentProtection->GetDigest(), (const unsigned char*)(LPCSTR)dlg.m_passwd, strlen((LPCSTR)dlg.m_passwd)))
         {
            pDoc->DeleteObject(m_documentProtection);
            m_documentProtection = NULL;
            break;
         }
      }
   }
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnConnectorFlyover() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   useConnectorFlyover = !useConnectorFlyover;

   if(useConnectorFlyover)
      SET_PARAMETER("ConnectorFlyover","true");
   else
      SET_PARAMETER("ConnectorFlyover","false");
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateConnectorFlyover(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->SetCheck(useConnectorFlyover?1:0);
}



//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateProtectDocument(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->SetCheck(m_documentProtection==NULL?0:1);
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnLButtonDown(UINT nFlags, CPoint point) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::OnLButtonDown(nFlags, point);
   if( m_documentProtection!=NULL )
      GetSelection()->ClearSelection();
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnLButtonUp(UINT nFlags, CPoint point) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::OnLButtonUp(nFlags, point);

	if( m_documentProtection!=NULL)
		GetSelection()->ClearSelection();
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnDateiExportJni() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   CDigitalTraineeStudioDoc* doc = (CDigitalTraineeStudioDoc*)GetDocument();
   assert(doc!=NULL);

   CString xmlDocument = doc->ToXML(SaveTempCircuit(),SaveTempCircuitImage());

   ApplicationProxyWrapper::onExport(JStringHelper((LPCSTR)xmlDocument));
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateDateiExportJni(CCmdUI* pCmdUI) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   pCmdUI->Enable(JavaPluginManager::isOk());
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnOsziPrint() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	// TODO: Add your command handler code here
	m_osziView->Print();
}

//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::OnUpdateOsziPrint(CCmdUI* pCmdUI) 
//----------------------------------------------------------------------------
{
	PROC_TRACE;
	// TODO: Add your command update UI handler code here
	
}

//----------------------------------------------------------------------------
CString CDigitalTraineeStudioView::SaveTempCircuitImage() 
//----------------------------------------------------------------------------
{
	PROC_TRACE;
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
   _splitpath((LPCSTR) GetDocument()->GetTitle(), drive, dir, fname, ext );

   s_counter++;
   // save the image to the temp-path
   //
   CPoint oldPos   = GetScrollPosition();
   float  oldScale = m_iScale;

   ScrollToPosition(CPoint(0,0));
   SetScale(100);

   PNGImageDC dc;
   CString pngPath = "";
   pngPath.Format("%s_%d.png",TEMP_PATH(fname),s_counter);
   GetDocument()->SetMinSize(CSize(10,10));
   int x = GetDocument()->GetMinLayoutSize().cx/3;
   int y = GetDocument()->GetMinLayoutSize().cy/3;
   dc.Create(CSize(x,y));
   OnPrepareDC(&dc,NULL);
   OnDraw(&dc);

   dc.Save(pngPath);

   SetScale(oldScale);
   ScrollToPosition(oldPos);

   return pngPath;	
}

//----------------------------------------------------------------------------
CString CDigitalTraineeStudioView::SaveTempCircuit() 
//----------------------------------------------------------------------------
{
	PROC_TRACE;
	
   // save the simulation file to the temp-path
   //
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
   _splitpath((LPCSTR) GetDocument()->GetTitle(), drive, dir, fname, ext );

   s_counter++;
   CString dsimPath = "";
   dsimPath.Format("%s_%d.dsim",TEMP_PATH(fname),s_counter);
   BOOL isModified = GetDocument()->IsModified();
   GetDocument()->OnSaveDocument(dsimPath);
   GetDocument()->SetModifiedFlag(isModified);
   return dsimPath;
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioView::SetDocumentation(CString docAsXml)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   if(m_documentDocumentation==NULL){
      DragDropDocument* pDoc = GetDocument();
      m_documentDocumentation = new  DocumentDocumentation();
      pDoc->AddObjectAtTail(m_documentDocumentation,FALSE);
   }
   m_documentDocumentation->SetDocumentation(docAsXml);
   GetDocument()->SetModifiedFlag(TRUE);
}

//----------------------------------------------------------------------------
CString CDigitalTraineeStudioView::GetDocumentation()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   if(m_documentDocumentation!=NULL)
      return m_documentDocumentation->GetDocumentation();
   return "";
}
