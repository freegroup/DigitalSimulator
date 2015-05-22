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

#if !defined(AFX_ELECTRICTEXT_H__5D5F586A_6A49_11D2_891B_004F49031E0C__INCLUDED_)
#define AFX_ELECTRICTEXT_H__5D5F586A_6A49_11D2_891B_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "DragDrop.h"
#include "DragDropObject.h"
#include "DragDropText.h"
#include "Application\i18n\ResourceTranslater.h"

class CElectricText : public DragDropText{
   typedef DragDropText inherited;

public:
   CElectricText(CPoint location, CSize size, LPCTSTR pString, 
            LPCTSTR pFaceName = DefaultFaceName,
            int nWeight = FW_NORMAL, BOOL bUnderline = FALSE, 
            BOOL bItalic = FALSE, int nAlignment = TextTopLeft, 
            BOOL bMultiLine = FALSE, BOOL bEditable = FALSE);
   CElectricText(){};
	virtual ~CElectricText();

   virtual DragDropObject* Clone() const;

   // Interactive interface
   //
   virtual BOOL        DoExtendedOption();
   virtual BOOL        DoOption();
   virtual long        GetContextMenuId(){return IDR_POPUP_TEXT_OBJECT;};
   virtual CString     GetDescriptionText(){return TRANSLATE("Text Beschreibung");};
   virtual long        GetHelpId()const{return 0;};
   virtual CString     GetGroup(){return CString("Utils");};


   virtual void        Serialize(CArchive& ar);


   virtual char * const GetClassName(){return "CElectricText";};

private:
   static const int m_version ;
   DECLARE_SERIAL(CElectricText)
};

#endif // !defined(AFX_ELECTRICTEXT_H__5D5F586A_6A49_11D2_891B_004F49031E0C__INCLUDED_)
