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

#include "DragDropstdafx.h"
#include "DragDrop.h"
#include "DragDropApp.h"
#include "DragDropClientApp.h"

#include "DragDrophandle.h"

IMPLEMENT_SERIAL(DragDropHandle, DragDropRectangle, 2)


//----------------------------------------------------------------------------
DragDropHandle::DragDropHandle(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}


//----------------------------------------------------------------------------
DragDropHandle::DragDropHandle(CRect* pRect, CM::Type  nCursor) : inherited(pRect){
//----------------------------------------------------------------------------
	PROC_TRACE;

   Init(nCursor);
} 


//----------------------------------------------------------------------------
DragDropHandle::DragDropHandle(CPoint location, CSize size,CM::Type nCursor) : inherited(location, size){
//----------------------------------------------------------------------------
	PROC_TRACE;

   Init(nCursor);
} 



//----------------------------------------------------------------------------
void DragDropHandle::Init(CM::Type  nCursor){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_pHandleFor    = NULL;
   SetSelectable (FALSE);
   m_nHandleCursor = nCursor;
}   

//----------------------------------------------------------------------------                                                 
DragDropHandle::~DragDropHandle() {
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DragDropObject* DragDropHandle::Clone() const{   
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pObject = inherited::Clone();      // call the base class to create the object
   ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropHandle)));                  
    DragDropHandle* pHandle =(DragDropHandle*) pObject;
    
    return pObject;
}

//----------------------------------------------------------------------------
BOOL DragDropHandle::DoUncapturedMouseMove(UINT nFlags, CPoint pointDP,   CPoint pointLP, CClientDC* pDC, DragDropView* pView){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CM::set(m_nHandleCursor);     
   return TRUE;
}
