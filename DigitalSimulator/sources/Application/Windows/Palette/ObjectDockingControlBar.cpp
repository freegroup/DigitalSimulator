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
#pragma warning(disable : 4786)

#include "stdafx.h"
#include <stdio.h>
#include <io.h>
#include <time.h>
#include <vector>
#include <CString>
#include <algorithm>

#include "DragDropGridView.h"

#include "Application\Debug\LogManager.h"
#include "Application\DigitalSimulatorApp.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Windows\Workplace\DigitalTraineeStudioDoc.h"

#include "DockingPaletteDoc.h"
#include "ObjectDockingControlBar.h"

using namespace std;



BEGIN_MESSAGE_MAP(CObjectDockingControlBar, CSizingTabCtrlBar)
	//{{AFX_MSG_MAP(CObjectDockingControlBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CObjectDockingControlBar::CObjectDockingControlBar(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_languageNotifyee.setListener(this);
	m_documentReloadNotifyee.setListener(this);
	m_paletteAutolayoutNotifyee.setListener(this);
}


//----------------------------------------------------------------------------
CObjectDockingControlBar::~CObjectDockingControlBar(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}


//----------------------------------------------------------------------------
void CObjectDockingControlBar::AddAllPaletteFiles(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   LM::log(LM::info,"Initialize the DragDrop palette");
   LM::log(LM::info,"------------------------------");

   struct _finddata_t c_file;
   long hFile;
   vector<CString> files;
   vector<CString>::iterator it ;

   CString     palettePath=PALETTE_PATH("");

   /* Find first .gop file in current directory */
   if( (hFile = _findfirst( (palettePath+"*.gop"), &c_file )) == -1L ){
	  CString msg = CString("No palette found in [")+ palettePath+"*.gop" + "]";
      AfxMessageBox( msg);
   }
   else {
      files.push_back(palettePath+c_file.name);

      /* Find the rest of the files */
      while( _findnext( hFile, &c_file ) == 0 ){
		files.push_back(palettePath+c_file.name);
      }

      _findclose( hFile );
	  sort(files.begin(), files.end());
      for(it = files.begin(); it != files.end(); it++)
         AddPaletteFile((*it));
   }
}


//----------------------------------------------------------------------------
BOOL CObjectDockingControlBar::AddPaletteFile(CString fileName){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CObjectDockingControlBarView* view = GetViewByPath(fileName);
	if(view!=NULL)
	{
		view->GetDocument()->OnOpenDocument(fileName);
		CRect clientRect;
		view->GetClientRect(&clientRect);
		view->SendMessage(WM_SIZE, clientRect.Height(), clientRect.Width());
		return TRUE;
	}
	
   LM::log(LM::info,"loading palette file '%s'",(LPCSTR)fileName);

   CCreateContext context;
   CString t =fileName;
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];

   _splitpath( (LPCSTR)fileName, drive, dir, fname, ext );
 
   CRuntimeClass* pClass =  RUNTIME_CLASS(CDockingPaletteDoc);
	context.m_pCurrentDoc = (DragDropDocument*)pClass->CreateObject();
   CDockingPaletteDoc* newDoc =(CDockingPaletteDoc*)context.m_pCurrentDoc;

   if (context.m_pCurrentDoc != NULL)
   {
	   context.m_pCurrentDoc->SetPathName(fileName,FALSE);	
	   context.m_pNewDocTemplate = context.m_pCurrentDoc->GetDocTemplate();
   }

   CString paneName = TRANSLATE(fname);
   AddView(paneName, RUNTIME_CLASS(CObjectDockingControlBarView),&context,TRUE);

   view=(CObjectDockingControlBarView*)GetActiveView();

   #pragma TODO("prüfen wann OnInitialUpdate aufgerufen werden sollte")
   /*
   if(view!=NULL)
      view->OnInitialUpdate();
   */

   ((CDockingPaletteDoc*)context.m_pCurrentDoc)->OnOpenDocument(fileName,fname);
   
   return TRUE;
}

//----------------------------------------------------------------------------
void CObjectDockingControlBar::UpdateLabels(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   TC_ITEM tci;

   int num=0;
	for (POSITION pos=m_views.GetHeadPosition(); pos; m_views.GetNext(pos))
	{
	   TCB_ITEM *pMember=m_views.GetAt(pos);
      CObjectDockingControlBarView *view = (CObjectDockingControlBarView*)pMember->pWnd;

	   tci.mask    = TCIF_TEXT;
	   tci.pszText = (char*)(LPCSTR)TRANSLATE(((CDockingPaletteDoc*)view->GetDocument())->GetDocumentName());
      m_tabctrl.SetItem(num, &tci);
      num++;
    }

	// the size of the labels has been changed - it is neccessary to relayout the objekt bar
	//
	CRect rect;
    GetWindowRect(rect);
    OnSize(SIZE_RESTORED,rect.Width(),rect.Height());
}


//----------------------------------------------------------------------------
CObjectDockingControlBarView* CObjectDockingControlBar::GetViewByPath(CString filename){
//----------------------------------------------------------------------------
	PROC_TRACE;

	for (POSITION pos=m_views.GetHeadPosition(); pos; m_views.GetNext(pos))
	{
	   TCB_ITEM *pMember=m_views.GetAt(pos);
       CObjectDockingControlBarView *view = (CObjectDockingControlBarView*)pMember->pWnd;

	   if(((CDockingPaletteDoc*)view->GetDocument())->GetPathName()==filename)
		return view;
    }
	return NULL;
}
