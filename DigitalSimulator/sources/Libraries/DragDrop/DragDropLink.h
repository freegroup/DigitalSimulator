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

#ifndef _DRAGDROPLINK_H_
#define _DRAGDROPLINK_H_
#include "DragDropobject.h" 
#include "DragDropstroke.h"

class CStroke;
class DragDropPort;

class DragDropLink : public DragDropStroke{
    typedef DragDropStroke inherited ;
public:
    DragDropLink();
    DragDropLink(DragDropPort* pFrom, DragDropPort* pTo);
    virtual ~DragDropLink();
    virtual BOOL paint(CDC* pDC);
    
    virtual DragDropPort* GetFromPort() {return m_pFrom;}
    virtual DragDropPort* GetToPort() {return m_pTo;}

    virtual void GainedSelection(DragDropSelection* pSelection);
    virtual BOOL HandleResizing(CClientDC* pDC, DragDropView* pView, CRect* pRect, CPoint pPoint, 
        int nHandleHit, int nEvent, 
        int nMinWidth = MIN_OBJECT_ON_RESIZE, int nMinHeight = MIN_OBJECT_ON_RESIZE);  
                                                          
    virtual void AutoStroke();
    virtual void PortChange();
    virtual void PortMarkedDelete();
    virtual void Serialize(CArchive& ar);
    virtual CString GetMetaName(){return "Link";};
    
protected:
    DragDropPort*    m_pFrom;    
    DragDropPort*    m_pTo;       
    virtual int GetFirstPickPoint();
    virtual int GetLastPickPoint();
    virtual void Unlink();
    DECLARE_SERIAL(DragDropLink)
};

#endif 
