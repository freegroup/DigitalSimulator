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

#ifndef _DRAGDROPAREA_H_
#define _DRAGDROPAREA_H_

#include "DragDropobject.h"
class DragDropArea : public DragDropObject{
   typedef DragDropObject inherited;

public:
    DragDropArea();
    virtual ~DragDropArea();

    virtual BOOL paint(CDC* pDC);
    virtual DragDropObject* PickInArea(CClientDC* pDC, CPoint ptToCheckLP, BOOL bSelectableOnly);
    
    virtual void SetGrabChildSelection(BOOL bFlag) {m_bGrabChildSelection = bFlag;}
    virtual BOOL GetGrabChildSelection() {return m_bGrabChildSelection;}
                                                                    
    virtual POSITION AddChildAtHead(DragDropObject* pObject, BOOL bForceFirstDraw = TRUE); 
    virtual POSITION AddChildAtTail(DragDropObject* pObject, BOOL bForceFirstDraw = TRUE);

    virtual POSITION GetFirstChildPos() const;
    virtual DragDropObject* GetNextChild(POSITION& pos) const;

    virtual void SendObjectToBack(DragDropObject* pObject);
    virtual void BringObjectToFront(DragDropObject* pObject);

    virtual BOOL ShrinkToFit();
    virtual void Serialize(CArchive& ar);

    CObList m_oblistObjects;        
    virtual DragDropObject* Clone() const;   
protected:
    virtual void GeometryChange(CRect* pRectPrevious);   
    virtual void GeometryChangeChild(DragDropObject* pChildObject);
    virtual void SetDocument(DragDropDocument* pDocument); 
    virtual BOOL ValidateChildRect(DragDropObject* pChildObject);

    BOOL    m_bGrabChildSelection; 
 	 BOOL	   m_bShrinkToFitPending;

    DECLARE_SERIAL(DragDropArea)
};


#endif
