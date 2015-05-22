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

#ifndef _ELECTRICPORTLINK_H_
#define _ELECTRICPORTLINK_H_
#pragma warning(disable : 4786)


// libraries
#include "DragDrop.h"
#include "DragDropPort.h"
#include "DragDropDocument.h"
#include "DragDropBitmap.h"
#include "DragDropObject.h" 
#include "DragDropStroke.h"
#include "DragDropLink.h"
#include "ElectricPort.h"

// 
#include "Application\Windows\Oszi\OsziStroke.h"
#include "Application\Objects\buildin\digital\ViewPoint.h"


class CElectricPortLink : public DragDropLink{
   typedef DragDropLink inherited;

public:
   CElectricPortLink();
   CElectricPortLink(DragDropPort* pFrom, DragDropPort* pTo);
   virtual ~CElectricPortLink();


   virtual CString     GetDescriptionText();
   virtual long        GetHelpId();
   virtual long        GetContextMenuId();
	virtual BOOL        DoOption();
	virtual BOOL        DoExtendedOption();
   virtual CLogicValue GetValue();

   virtual CPoint GetArrowToAnchorPt();
   virtual CPoint GetArrowFromAnchorPt();
   virtual void AutoStroke();

   virtual void GainedSelection(DragDropSelection* pSelection);                                                          
   virtual void LostSelection(DragDropSelection* pSelection);
  	virtual void DoCalculate();
   virtual int  GetFirstPickPoint();
   virtual int  GetLastPickPoint();

   virtual void         SetOsziStroke(COsziStroke* stroke);
   virtual COsziStroke* GetOsziStroke(){return m_osziStroke;};
   virtual void         SetOsziStrokeString(const CString& label);

   virtual void Serialize(CArchive& ar);
   virtual void RemoveLastHitSegment();
   virtual void InsertLastHitSegment();
   virtual BOOL canRemoveLastHitSegment();

   virtual char * const GetClassName(){return "CElectricPortLink";};
protected:
   CViewPoint   *m_viewPoint;
   COsziStroke  *m_osziStroke;
   bool          m_routingHasChanged;

   virtual void  FullAutoStroke();
   virtual void  HalfAutoStroke();
   virtual void  LayoutViewPointImage();
   virtual void  LayoutSplitPointImage();

   virtual BOOL HandleResizing(CClientDC *pDC,
                               DragDropView   *pView, 
                               CRect     *pRect, 
                               CPoint     pPoint, 
                               int        nHandleHit, 
                               int        nEvent, 
                               int        nMinWidth = MIN_OBJECT_ON_RESIZE, 
                               int        nMinHeight = MIN_OBJECT_ON_RESIZE);  

    DECLARE_SERIAL(CElectricPortLink)

private:
   static const int m_version ;

   CLogicValue m_currentValue;
};

#endif 
