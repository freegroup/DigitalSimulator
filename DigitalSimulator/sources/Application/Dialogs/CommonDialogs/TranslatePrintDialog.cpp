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
#include <dlgs.h>

#include "Application\DigitalSimulatorApp.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"

#include "TranslatePrintDialog.h"


UINT APIENTRY CTranslatePrintDialogPrintHookProc( HWND hdlg,UINT uiMsg,WPARAM wParam, LPARAM lParam ){
	PROC_TRACE;

   LPNMHDR pnmh;
   pnmh = (LPNMHDR) lParam;

   switch (uiMsg)    {
     case WM_INITDIALOG:
          char buffer[100];
          SetDlgItemText(hdlg,IDOK,TRANSLATE("Ok"));
          SetDlgItemText(hdlg,IDCANCEL,TRANSLATE("Abbruch"));
          SetDlgItemText(hdlg,grp4,TRANSLATE("Drucker"));
          SetDlgItemText(hdlg,stc6,TRANSLATE("&Name"));
          SetDlgItemText(hdlg,psh2,TRANSLATE("&Eigenschaften"));
          SetDlgItemText(hdlg,stc8,TRANSLATE("Status:"));
          SetDlgItemText(hdlg,stc7,TRANSLATE("Typ:"));
          SetDlgItemText(hdlg,stc10,TRANSLATE("Standort:"));
          SetDlgItemText(hdlg,stc9,TRANSLATE("Kommentar:"));
          SetDlgItemText(hdlg,chx1,TRANSLATE("Ausgabe in &Datei"));
          SetDlgItemText(hdlg,grp1,TRANSLATE("Druckbereich"));
          SetDlgItemText(hdlg,rad1,TRANSLATE("Alle"));
          SetDlgItemText(hdlg,rad3,TRANSLATE("Seiten"));
          SetDlgItemText(hdlg,rad2,TRANSLATE("&Markierung"));
          SetDlgItemText(hdlg,stc2,TRANSLATE("von:"));
          SetDlgItemText(hdlg,stc3,TRANSLATE("bis:"));
          SetDlgItemText(hdlg,grp2,TRANSLATE("Exemplare"));
          SetDlgItemText(hdlg,stc5,TRANSLATE("An&zahl der Exemplare:"));
          SetDlgItemText(hdlg,chx2,TRANSLATE("S&ortieren"));
          GetWindowText(hdlg,buffer,sizeof(buffer)-1);
          SetWindowText(hdlg,TRANSLATE(buffer));
   }
   return 0;
}

 /////////////////////////////////////////////////////////////////////////////
// CTranslatePrintDialog

IMPLEMENT_DYNAMIC(CTranslatePrintDialog, CPrintDialog)

CTranslatePrintDialog::CTranslatePrintDialog(BOOL bPrintSetupOnly, DWORD dwFlags, CWnd* pParentWnd) :
	CPrintDialog(bPrintSetupOnly, dwFlags, pParentWnd)
{
	PROC_TRACE;

    m_pd.Flags |= PD_ENABLEPRINTHOOK;
    m_pd.lpfnPrintHook = CTranslatePrintDialogPrintHookProc;          
}
