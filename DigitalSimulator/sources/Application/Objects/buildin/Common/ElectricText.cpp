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

#include "stdafx.h"
#include <assert.h>

#include "DragDropDocument.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\Dialogs\CommonDialogs\CustomFontDialog.h"

#include "ElectricText.h"

IMPLEMENT_SERIAL(CElectricText, DragDropText, 1)
const  CElectricText::m_version = 1;

//----------------------------------------------------------------------------
CElectricText::CElectricText(CPoint location, CSize size, LPCTSTR pString, 
            LPCTSTR pFaceName,int nWeight, BOOL bUnderline , 
            BOOL bItalic , int nAlignment, 
            BOOL bMultiLine, BOOL bEditable)
 : DragDropText(location,size,pString,pFaceName, nWeight,bUnderline, bItalic,
           nAlignment,bMultiLine, bEditable)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   SetEditable(TRUE);
}


//----------------------------------------------------------------------------
CElectricText::~CElectricText(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DragDropObject* CElectricText::Clone() const{   
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject *t= inherited::Clone();
   assert(t!=NULL);
   assert(t->IsKindOf(RUNTIME_CLASS(CElectricText)));
   ((CElectricText*)t)->SetBkMode(TRANSPARENT);

   // beschissenes Layout während dem Schreiben
   //
   //((CElectricText*)t)->SetMultiLine(TRUE);
   return t;
}

/*
//----------------------------------------------------------------------------
void DragDropText::PrepareLogfont(LOGFONT& lf){
//----------------------------------------------------------------------------
	PROC_TRACE;

   memset (&lf, 0, sizeof(LOGFONT));
    lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;  // ?
    lf.lfQuality = DRAFT_QUALITY; 
    lf.lfHeight = m_nHeightLine;             // Edit Text creation assumes this is the only item that MM_ matters 
    lf.lfWeight = m_nWeight;
    lf.lfUnderline = IsUnderline();
    lf.lfItalic = IsItalic();
    lf.lfEscapement = m_nEscapement;
    lf.lfOrientation = m_nEscapement;
    _tcscpy(lf.lfFaceName, m_sFaceName);
} 
*/

//----------------------------------------------------------------------------
BOOL CElectricText::DoOption(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   LOGFONT font;
/*
   font.lfHeight       = GetLineHeight(); 
   font.lfWidth        = GetLineWidth(); 
   font.lfEscapement   = 0; 
   font.lfOrientation  = 0; 
   font.lfWeight       = GetWeight(); 
   font.lfItalic       = IsItalic();; 
   font.lfUnderline    = IsUnderline(); 
   font.lfStrikeOut    = FALSE; 
   font.lfCharSet      = 0; 
   font.lfOutPrecision = 0; 
   font.lfClipPrecision = 0; 
   font.lfQuality      = 0; 
   font.lfPitchAndFamily = 0; 
   strncpy(font.lfFaceName,(LPCSTR)GetFaceName(),LF_FACESIZE); 
*/  
   PrepareLogfont(font);
   CCustomFontDialog dlg(&font);
   dlg.SetSampleText(GetString());
   dlg.SetTextColor(GetTextColor());
   if(dlg.DoModal()==IDOK){
       SetItalic(font.lfItalic);
       SetUnderline(font.lfUnderline);
       SetLineHeight(font.lfHeight);
       SetLineWidth(font.lfWidth);
       SetWeight(font.lfWeight);
       TRACE("font.lfWeight=%d ",font.lfWeight);
       SetTextColor(dlg.GetTextColor());
       SetFaceName(font.lfFaceName);
    	 if (m_pDocument) 
          m_pDocument->SetModifiedFlag();
       return TRUE;
   }
   return FALSE;
}

//----------------------------------------------------------------------------
BOOL CElectricText::DoExtendedOption(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return FALSE;
}

//----------------------------------------------------------------------------
void CElectricText::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

   if (ar.IsStoring()){
       ar << m_version;

    }
    else{
       int version;
       ar >> version;

       switch (version){
       case 1:
           break;
       default:
           LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
           break;
       }
    }
}
