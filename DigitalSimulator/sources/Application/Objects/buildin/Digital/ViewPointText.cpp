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

#include <assert.h>

#include "stdafx.h"
#include "ViewPointText.h"
#include "ViewPoint.h"
#include <assert.h>
#include "Application\Debug\LogManager.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CViewPointText, DragDropText, 1)
const  CViewPointText::m_version = 1;

CViewPointText::CViewPointText(   CViewPoint* parent,
                                  CPoint location, 
                                  CSize size, 
                                  LPCTSTR pString, 
                                  LPCTSTR pFaceName,
                                  int nWeight, 
                                  BOOL bUnderline , 
                                  BOOL bItalic , 
                                  int nAlignment, 
                                  BOOL bMultiLine, 
                                  BOOL bEditable)
 : DragDropText(location,size,pString,pFaceName, nWeight,bUnderline, bItalic,
 nAlignment,bMultiLine, bEditable) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(parent != NULL);

   SetEditable(TRUE);
   SetSelectable(FALSE);
   SetDraggable(FALSE);
   SetResizable(FALSE);
   SetBkMode(TRANSPARENT);

   m_parent = parent;
}

//----------------------------------------------------------------------------
CViewPointText::CViewPointText(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
CViewPointText::~CViewPointText(){
//----------------------------------------------------------------------------
	PROC_TRACE;


}

//----------------------------------------------------------------------------
void CViewPointText::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

   if (ar.IsStoring()){
       ar << m_version;
       ar << m_parent;
   }
   else{
       int version;
       ar >> version;

       switch (version){
       case 1:
           ar >> m_parent;
           break;
       default:
           LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
           break;
       }
    }
}

//----------------------------------------------------------------------------
void CViewPointText::DoEndEdit(DragDropView* pView /* == NULL */){
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropText::DoEndEdit( pView);
   m_parent->SetLabel(GetString()); // FIXME: is possible to create a endless loop
}
                       
