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

#include "DragDroprect.h"


IMPLEMENT_SERIAL(DragDropRectangle, DragDropDrawable, 2)


//----------------------------------------------------------------------------
DragDropRectangle::DragDropRectangle(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DragDropRectangle::DragDropRectangle(CRect* pRect) :inherited(pRect){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DragDropRectangle::DragDropRectangle(CPoint location, CSize size) : inherited (location, size){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DragDropRectangle::~DragDropRectangle() {
//----------------------------------------------------------------------------
	PROC_TRACE;

}    

//----------------------------------------------------------------------------                                                 
DragDropObject* DragDropRectangle::Clone() const{   
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pObject = inherited::Clone();
   ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropRectangle)));                  
   DragDropRectangle* pDrawable =(DragDropRectangle*) pObject;

   return pObject;
}

//----------------------------------------------------------------------------
BOOL DragDropRectangle::paint(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;
    
   assert(pDC != NULL);

   if (!isVisible()) 
      return TRUE;
   CPen *pPen, *pOldPen;
   PreparePen(pDC, pPen, pOldPen);

   CBrush *pBrush, *pOldBrush;
   PrepareBrush(pDC, pBrush, pOldBrush);
             
   pDC->Rectangle(m_boundingRect);

   PostPen(pDC, pPen, pOldPen);  
   PostBrush(pDC, pBrush, pOldBrush);
  
   return TRUE;
   }

