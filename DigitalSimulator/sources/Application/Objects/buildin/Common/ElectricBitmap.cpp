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
#include "DragDropView.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\Dialogs\CommonDialogs\BmpFileDialog.h"

#include "ElectricBitmap.h"

IMPLEMENT_SERIAL(CElectricBitmap, DragDropArea, 1)
const  CElectricBitmap::m_version = 1;

//-----------------------------------------------------------------------------
CElectricBitmap::CElectricBitmap(){
//-----------------------------------------------------------------------------
	PROC_TRACE;

}


//-----------------------------------------------------------------------------
CElectricBitmap::CElectricBitmap(CPoint position){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropBitmap *bitmap = new DragDropBitmap(position, CSize(100,100));
   bitmap->SetResource("DEFAULTBITMAP",70,70);
   bitmap->SetSelectable(FALSE);
   AddChildAtTail(bitmap);
}


//-----------------------------------------------------------------------------
CElectricBitmap::~CElectricBitmap(){
//-----------------------------------------------------------------------------
	PROC_TRACE;

}


//-----------------------------------------------------------------------------
DragDropObject* CElectricBitmap::Clone() const{   
//-----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pNode =inherited::Clone();
   assert(pNode->IsKindOf(RUNTIME_CLASS(CElectricBitmap)));                  

   return pNode;
}

//----------------------------------------------------------------------------
BOOL CElectricBitmap::DoLButtonDblClk(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return DoOption();
}


//-----------------------------------------------------------------------------
BOOL CElectricBitmap::DoOption(){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   CBmpDialog  dlg;
   if(dlg.DoModal()==IDOK){
        POSITION    p= GetFirstChildPos();
        while(p){
            delete GetNextChild(p);
        }
        DragDropBitmap *bitmap = new DragDropBitmap(GetLocation(), CSize(100,100));
        if(TRUE==  bitmap->SetFileName(dlg.GetPathName())){
           // Das Bitmap konnte aus der Datei eingelesen werden
           // ... es ist nichts weiter zu tun - zur Zeit
           //
        }
        else{
           // Das Bitmap konnte nicht einwandfrei eingelesen werden
           // Es wird ein default-Bitmap aus den Recourcen genommen
           //
           bitmap->SetResource("CORRUPTBITMAP",70,70);
        }
        bitmap->SetSelectable(FALSE);
        AddChildAtHead(bitmap);
        return TRUE;

   }
   return FALSE;
}

//-----------------------------------------------------------------------------
BOOL CElectricBitmap::DoExtendedOption(){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   
   return FALSE;
}

//----------------------------------------------------------------------------
void CElectricBitmap::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

   if (ar.IsStoring()){
      ar << m_version;
   }
   else{
      int version;
      ar >> version;

      switch (version){
      case 1:
          break;
      default:
          LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
          break;
      }
   }
}

