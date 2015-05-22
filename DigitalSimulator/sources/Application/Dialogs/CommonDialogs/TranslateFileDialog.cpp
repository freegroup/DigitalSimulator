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
#include "Application\DigitalSimulatorApp.h"
#include "TranslateFileDialog.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"

// Proprietary Hook function for open dialog

UINT APIENTRY CTranslateFileDialogOFNHookProc( HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam )
{
	PROC_TRACE;

   LPNMHDR pnmh;
   pnmh = (LPNMHDR) lParam;

   switch (uiMsg)    {
        case WM_NOTIFY:
        
            if (pnmh->code == CDN_FILEOK) {
                // This avoids an assert
                _AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	            pThreadState->m_pAlternateWndInit = NULL;
               return 0;
            }
         if (pnmh->code ==  CDN_INITDONE)      {
             char buffer[100];
             SetDlgItemText(GetParent(hdlg),psh14,TRANSLATE("Netz&werk"));
             SetDlgItemText(GetParent(hdlg),chx1,TRANSLATE("Schreibgeschützt"));
             SetDlgItemText(GetParent(hdlg),pshHelp,TRANSLATE("&Hilfe"));
             SetDlgItemText(GetParent(hdlg),IDOK,TRANSLATE("Ok"));
             SetDlgItemText(GetParent(hdlg),IDCANCEL,TRANSLATE("Abbruch"));
             SetDlgItemText(GetParent(hdlg),stc3,TRANSLATE("Dateiname:"));
             SetDlgItemText(GetParent(hdlg),stc2,TRANSLATE("Dateitypen:"));
             SetDlgItemText(GetParent(hdlg),stc4,TRANSLATE("&Suchen in:"));
             GetWindowText(GetParent(hdlg),buffer,sizeof(buffer)-1);
             SetWindowText(GetParent(hdlg),TRANSLATE(buffer));
             return 0;
         }
   }
   return 0;
}

IMPLEMENT_DYNAMIC(CTranslateFileDialog, CFileDialog)

CTranslateFileDialog::CTranslateFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	PROC_TRACE;

    m_ofn.Flags |= (OFN_HIDEREADONLY |OFN_ENABLEHOOK| OFN_EXPLORER );

    m_ofn.hInstance = AfxGetInstanceHandle();
    m_ofn.lpfnHook = CTranslateFileDialogOFNHookProc;          
}
