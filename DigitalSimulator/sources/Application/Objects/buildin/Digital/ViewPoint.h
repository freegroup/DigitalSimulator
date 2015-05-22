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

#if !defined(AFX_VIEWPOINT_H__E9E1F021_EFF7_11D2_898B_004F49031E0C__INCLUDED_)
#define AFX_VIEWPOINT_H__E9E1F021_EFF7_11D2_898B_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "DragDropArea.h"
#include "ViewPointText.h"
#include "LogicValue.h"

class CElectricPortLink;

class CViewPoint  : public DragDropArea
{
   typedef DragDropArea inherited ;
public:
	CViewPoint(CElectricPortLink* parent, const CPoint &position);
	virtual ~CViewPoint();

   virtual void SetLabel(const CString &label);
   virtual void Serialize(CArchive& ar);

   virtual long        GetContextMenuId();
   virtual CString     GetDescriptionText();
   virtual const char* getLabel();
   virtual long        GetHelpId();
   virtual CLogicValue GetValue();

   virtual DragDropObject*  RedirectSelection() {return (DragDropObject*)m_parent;};

   // Possible Error 
   // Funktion wurde überschrieben um der Script Engine die Möglichkeit zu geben
   // auf den Parent ( der Link) eines ViewPoint zuzugreifen. Die kann aber zu einem
   // Konflikt mit GO++ kommen, da diese die selbe Signatur haben.....beobachten des
   // Verhaltens
   //
   virtual DragDropObject*   GetParent() { return (DragDropObject*)m_parent;}     // parent of object when in DragDropArea Heirarchy

   virtual char * const GetClassName(){return "CViewPoint";};
protected:
   CViewPoint();

   CViewPointText    *m_text;
   CElectricPortLink *m_parent;

   DECLARE_SERIAL(CViewPoint)

private:
   static const int m_version ;
};

#endif // !defined(AFX_VIEWPOINT_H__E9E1F021_EFF7_11D2_898B_004F49031E0C__INCLUDED_)