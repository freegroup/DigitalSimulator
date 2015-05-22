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

#if !defined(AFX_ELECTRICBITMAP_H__91749581_B5CB_11D2_9A15_0080C7304F8F__INCLUDED_)
#define AFX_ELECTRICBITMAP_H__91749581_B5CB_11D2_9A15_0080C7304F8F__INCLUDED_
#pragma warning(disable : 4786)


#include "DragDropArea.h"
#include "DragDropBitmap.h"

#include "Application\i18n\ResourceTranslater.h"

class CElectricBitmap : public DragDropArea{
   typedef DragDropArea inherited;

public:
	CElectricBitmap();
	CElectricBitmap(CPoint position);

	virtual ~CElectricBitmap();

   virtual DragDropObject*  Clone() const;
   virtual long        GetContextMenuId(){return IDR_POPUP_BITMAP_OBJECT;};
   virtual long        GetHelpId(){return OBJ_BITMAP;};
   virtual BOOL        DoOption();
	virtual BOOL        DoExtendedOption();
   virtual CString     GetDescriptionText(){return TRANSLATE("Bitmap Beschreibung");};
   virtual BOOL        DoLButtonDblClk(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual CString     GetGroup()const{return CString("Utils");};
   virtual CString     GetMetaName(){return "Bitmap";};

   virtual void        Serialize(CArchive& ar);


   virtual char * const GetClassName(){return "CElectricBitmap";};
private:
   static const int m_version ;
   DECLARE_SERIAL(CElectricBitmap)
};

#endif // !defined(AFX_ELECTRICBITMAP_H__91749581_B5CB_11D2_9A15_0080C7304F8F__INCLUDED_)
