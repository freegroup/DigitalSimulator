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
#include <assert.h>
#include "ViewPoint.h"
#include "ElectricPortLink.h"
#include "Application\Debug\LogManager.h"


IMPLEMENT_SERIAL(CViewPoint, DragDropArea, 1)
const  CViewPoint::m_version = 1;


//----------------------------------------------------------------------------
CViewPoint::CViewPoint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_parent = NULL;
}


//----------------------------------------------------------------------------
CViewPoint::CViewPoint(CElectricPortLink* parent, const CPoint &position){
//----------------------------------------------------------------------------
	PROC_TRACE;


   assert (parent != NULL);

   // Bitmap fuer den ViewPoint anlegen
   //
   DragDropBitmap *bitmap = new DragDropBitmap(position, CSize(30,30));
   bitmap->SetResource("VIEWPOINT",12,11);
   bitmap->SetSelectable(FALSE);
   bitmap->SetResizable(FALSE);
   bitmap->SetDraggable(FALSE);
   AddChildAtHead(bitmap);

   // Textlabel fuer den ViePoint anlegen
   // Das Label ist editierbar
   //
   m_text = new CViewPointText(this, position, CSize(40,40));
   m_text->SetSpotLocation(DragDropObject::spotLeftCenter, bitmap, DragDropObject::spotRightCenter);
   AddChildAtHead(m_text);

   
   SetSelectable(FALSE);
   SetResizable(FALSE);
   SetDraggable(FALSE);

   m_parent = parent;
}


//----------------------------------------------------------------------------
CViewPoint::~CViewPoint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
CString CViewPoint::GetDescriptionText(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return TRANSLATE("ViewPoint Beschreibung");
}

//----------------------------------------------------------------------------
const char* CViewPoint::getLabel(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_text == NULL)
      return "unknown";

   return (LPCSTR)m_text->GetString();
}


//----------------------------------------------------------------------------
long CViewPoint::GetHelpId(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return 0;
}


//----------------------------------------------------------------------------
long CViewPoint::GetContextMenuId(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return IDR_POPUP_VIEWPOINT_OBJECT;
}

//----------------------------------------------------------------------------
CLogicValue  CViewPoint::GetValue(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_parent==NULL){
      return CLogicValue(CLogicValue::Low);
   }
   return m_parent->GetValue();
}


//----------------------------------------------------------------------------
void CViewPoint::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

   if (ar.IsStoring()){
       ar << m_version;
       ar << m_text;
       ar << m_parent;
   }
   else{
       int version;
       ar >> version;

       switch (version){
       case 1:
           ar >> m_text;
           ar >> m_parent;
           break;
       default:
           LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
           break;
       }
    }
}


//----------------------------------------------------------------------------
void CViewPoint::SetLabel(const CString& label){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_parent->SetOsziStrokeString(label);
   m_text->SetString(label);
}