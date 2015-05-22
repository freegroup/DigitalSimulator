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

#ifndef _DRAGDROPSELECTION_H_
#define _DRAGDROPSELECTION_H_

#include "DragDropObject.h"
#include "DragDropDocument.h"

class DragDropView;  //forward declaration

class DragDropHandle;

class DragDropSelection : public CObject{
    typedef CObject inherited ;

public:
    // Constructors and destructors
    DragDropSelection();
    virtual ~DragDropSelection();

    // Operations
public:
    virtual void SetView(DragDropView* pView);
    virtual DragDropView* GetView() {return m_pView;}

    virtual int GetSelectedCount() const {return m_oblistSelectedObjects.GetCount();}
    virtual POSITION GetFirstSelectedPos();
    virtual DragDropObject* GetNextSelected(POSITION& pos);

    virtual void ClearSelection(DragDropObject* pObject = NULL); 
    
    virtual void ClearSelectionHandles(DragDropObject* pObj = NULL);   
    virtual void RestoreSelectionHandles(DragDropObject* pObj = NULL); 
    
    virtual void DeleteObjects();
    
    virtual DragDropObject* SelectObject(DragDropObject* pObject);    // const pObject??
    virtual DragDropObject* ExtendSelection(DragDropObject* pObject);
    virtual void ToggleSelection(DragDropObject* pObject);

    virtual DragDropObject* PrimarySelection() const;

    virtual BOOL IsDraggable();
    virtual BOOL IsEmpty() {return m_oblistSelectedObjects.IsEmpty() ;}
    virtual BOOL IsInSelection (DragDropObject* pObject);    // const pObject??


    virtual POSITION GetFirstHandlePos();
    virtual DragDropHandle* GetNextHandle(POSITION& pos);

    virtual void CreateBoundingHandle (DragDropObject* pObject);
    virtual DragDropHandle* CreateResizeHandle (DragDropObject* pObject, int x, int y, int nHandleType, BOOL bFilled);
    virtual void DeleteHandles (DragDropObject* pObject);
    virtual void AddHandle (DragDropHandle* pHandle);

    virtual void HideHandles (DragDropObject* pObject); 
    virtual void ShowHandles (DragDropObject* pObject); 

private:
    CObList m_oblistSelectedObjects;
    CObList m_oblistHandleObjects;
    DragDropView*    m_pView;
    
    DECLARE_DYNCREATE(DragDropSelection)
};


#endif
