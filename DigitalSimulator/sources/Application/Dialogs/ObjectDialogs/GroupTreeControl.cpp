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
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"

#include "GroupTreeControl.h"
#include "Application\Debug\LogManager.h"


BEGIN_MESSAGE_MAP(CGroupTreeControl, CTreeCtrl)
	//{{AFX_MSG_MAP(CGroupTreeControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CGroupTreeControl::CGroupTreeControl(){
//----------------------------------------------------------------------------
	PROC_TRACE;
}


//----------------------------------------------------------------------------
CGroupTreeControl::~CGroupTreeControl(){
//----------------------------------------------------------------------------
	PROC_TRACE;


}


//----------------------------------------------------------------------------
HTREEITEM CGroupTreeControl::InsertItem(CElectricNodeContext* context){
//----------------------------------------------------------------------------
	PROC_TRACE;


   TV_INSERTSTRUCT item;
   CString group = context->GetGroup();
   CString name  = context->GetName();

   item.hParent      = FindItem(group);
   if(item.hParent==NULL)
         item.hParent= AddGroup(context);

    item.hInsertAfter = TVI_SORT;
	item.item.mask    = TVIF_TEXT | TVIF_PARAM;
	item.item.pszText = (char*)TRANSLATE(name);
//	item.item.lParam  = 1; // 1 für ein Blatt
   HTREEITEM result =  inherited::InsertItem(&item );

   SetItemData(result,(DWORD)context);
   return result;
}


//----------------------------------------------------------------------------
HTREEITEM  CGroupTreeControl::AddGroup(CElectricNodeContext* context){
//----------------------------------------------------------------------------
	PROC_TRACE;

   TV_INSERTSTRUCT item;
   // don't remove this CString text... element
   // In the Tree will be displayed 'yxcvysdfybvhyxhjv'
   // ...released memory
   CString group = context->GetGroup();
   item.hParent      = NULL;
   item.hInsertAfter = TVI_SORT;
   item.item.mask    = TVIF_TEXT | TVIF_PARAM;
//   item.item.lParam  = 0; // 0 für eine Gruppe
   item.item.pszText = (char*)TRANSLATE(group);

   HTREEITEM result =  inherited::InsertItem(&item );

   SetItemData(result,(DWORD)context);
   return result;
}



//----------------------------------------------------------------------------
HTREEITEM CGroupTreeControl::FindItem(CString key){
//----------------------------------------------------------------------------
	PROC_TRACE;

   int lenSearchStr = key.GetLength();
   if( lenSearchStr == 0 ) return NULL;

   HTREEITEM htiCur ;
//   CString sSearch = key;

   htiCur = GetRootItem();


   while( htiCur ){
		if(ItemHasChildren(htiCur)){
			CElectricNodeContext* context =(CElectricNodeContext*) GetItemData( htiCur );
			if(context!=NULL && context->GetGroup()==key)
				return htiCur;
		}
		else{
			CElectricNodeContext* context =(CElectricNodeContext*) GetItemData( htiCur );

			if(context !=NULL && context->GetKey() == key){
				return htiCur;
			}
		}
		htiCur = GetNextItem(htiCur,TVGN_NEXT);
   }

   return NULL;
}
