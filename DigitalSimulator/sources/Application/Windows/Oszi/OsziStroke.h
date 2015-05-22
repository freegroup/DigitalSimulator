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

#if !defined(AFX_OSZISTROKE_H__F16C9FC1_C80F_11D2_8971_004F49031E0C__INCLUDED_)
#define AFX_OSZISTROKE_H__F16C9FC1_C80F_11D2_8971_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "DragDropStroke.h"
#include "DragDropText.h"

#include "Application\Objects\buildin\digital\LogicValue.h"

class COsziStroke : public DragDropStroke {
   typedef DragDropStroke inherited;
public:
	COsziStroke();
	virtual ~COsziStroke();

   virtual void Set(const CLogicValue& newValue);
   virtual void GainedSelection(DragDropSelection* pSelection);
   virtual BOOL PtInObject(CClientDC* pDC, CPoint ptToCheckLP, CPoint ptToCheckDP);
   virtual void SetDocument(DragDropDocument* pDocument);

   virtual void Serialize(CArchive& ar);

   static int CompBackward(COsziStroke* pFirstObj, COsziStroke* pSecondObj){
       CPoint p1 = pFirstObj->GetTopLeft();
       CPoint p2 = pSecondObj->GetTopLeft();
         
       return p1.y < p2.y;
   }

   virtual void SetLabel(const CString& label);

   virtual void SetLocation(CPoint pPoint);
   virtual void SetLocation(int x, int y);
   virtual void SetLocationOffset(CPoint pPoint, CSize pOffset);
   virtual void SetLocationOffset(CPoint pPoint, int cx, int cy);
   virtual void SetLocationOffset(int x, int y, int cx, int cy);


   virtual void FinishStroke();
   virtual char * const GetClassName(){return "COsziStroke";};
protected:
   virtual void GeometryChange(CRect* pRectPrevious);// called when object moved/resized

   long          m_yOffset;
   long          m_triggerHeight;
   long          m_triggerWidth;
   CLogicValue   m_currentValue;
   DragDropText *m_pLabel;

private:
   static const int m_version ;

   DECLARE_SERIAL(COsziStroke)
};

#endif // !defined(AFX_OSZISTROKE_H__F16C9FC1_C80F_11D2_8971_004F49031E0C__INCLUDED_)
