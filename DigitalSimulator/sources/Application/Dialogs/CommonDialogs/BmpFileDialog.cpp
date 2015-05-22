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
#include "resource.h"       // Hauptsymbole
#include "BmpFileDialog.h"

#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"

// In order to ease use, these values have been hard coded in bmpdlg.rc
// This avoids the need for another header file.

#define IDC_PREVIEW         (5000)
#define IDC_PREVIEWBTN	    (5001)	
#define IDC_WIDTH           (5002)
#define IDC_HEIGHT          (5003)
#define IDC_DEPTH           (5004)
#define IDC_FSIZE           (5005)
#define IDC_SHOWPREVIEW     (5006)

HBITMAP CBmpDialog::hpreview      = NULL;
BOOL    CBmpDialog::m_showpreview = TRUE;

// Proprietary Hook function for open dialog

UINT APIENTRY OFNHookProc( HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam )
{
	PROC_TRACE;

    
LPDRAWITEMSTRUCT lpdis;
BITMAP bm;
LPNMHDR pnmh;
char filename[1024],str[255];
int height,height2,width,width2;
NMHDR nmh;
    
    switch (uiMsg)
    {
        case WM_COMMAND:
            
            if (LOWORD(wParam) == IDC_SHOWPREVIEW)
            {
                CBmpDialog::m_showpreview = IsDlgButtonChecked(hdlg,IDC_SHOWPREVIEW);

                SetDlgItemText(hdlg,IDC_PREVIEWBTN,"juhu");
                if (!CBmpDialog::m_showpreview)
                {                    
                    if (CBmpDialog::hpreview)
                        DeleteObject(CBmpDialog::hpreview);

                    CBmpDialog::hpreview = NULL;

                    HWND wnd = GetDlgItem(hdlg,IDC_PREVIEWBTN);

                    InvalidateRect(wnd,NULL,TRUE);    

                    SetDlgItemText(hdlg,IDC_WIDTH,"");
                    SetDlgItemText(hdlg,IDC_HEIGHT,"");
                    SetDlgItemText(hdlg,IDC_DEPTH,"");
                    SetDlgItemText(hdlg,IDC_FSIZE,"");

                }
                else
                {
                    
                    nmh.code = CDN_SELCHANGE;

                    OFNHookProc(hdlg, WM_NOTIFY, 0, (LPARAM)&nmh);
                }
            }

            break;

        case WM_DRAWITEM:

            if (CBmpDialog::hpreview)
            {
                lpdis = (LPDRAWITEMSTRUCT)lParam;
                        
                GetObject(CBmpDialog::hpreview,sizeof(BITMAP),&bm);

                CPoint size(bm.bmWidth,bm.bmHeight);
                                                
                HDC dcmem = CreateCompatibleDC(lpdis->hDC);
      
                HBITMAP old = (HBITMAP)SelectObject(dcmem,CBmpDialog::hpreview);

                if (bm.bmWidth > bm.bmHeight)
                {

                    height = lpdis->rcItem.bottom - lpdis->rcItem.top;

                    float ratio = (float)bm.bmHeight/(float)bm.bmWidth;                 
                    
                    lpdis->rcItem.bottom  = (long) (lpdis->rcItem.top + (lpdis->rcItem.right-lpdis->rcItem.left)*ratio);

                    height2 = (height - (lpdis->rcItem.bottom - lpdis->rcItem.top))/2;

                    lpdis->rcItem.top += height2;
                    lpdis->rcItem.bottom += height2;

                }
                else
                {

                    width = lpdis->rcItem.right - lpdis->rcItem.left;

                    float ratio = (float)bm.bmWidth/(float)bm.bmHeight;                 
                    
                    lpdis->rcItem.right  = (long) (lpdis->rcItem.left + (lpdis->rcItem.bottom-lpdis->rcItem.top)*ratio);

                    width2 = (width - (lpdis->rcItem.right - lpdis->rcItem.left))/2;

                    lpdis->rcItem.left += width2;
                    lpdis->rcItem.right += width2;

                }
                    
                StretchBlt(lpdis->hDC,lpdis->rcItem.left,lpdis->rcItem.top,lpdis->rcItem.right-lpdis->rcItem.left,lpdis->rcItem.bottom-lpdis->rcItem.top,dcmem,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);

                SelectObject(dcmem,old);

                DeleteDC(dcmem);
            }

            break;

        case WM_NOTIFY:
        
            pnmh = (LPNMHDR) lParam;

            if (pnmh->code == CDN_FILEOK)
            {
                if (CBmpDialog::hpreview)
                        DeleteObject(CBmpDialog::hpreview);

                // This avoids an assert

                _AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	            pThreadState->m_pAlternateWndInit = NULL;
                return 0;
            }


            if (pnmh->code ==  CDN_INITDONE)
            {
               char buffer[200];
               if (CBmpDialog::hpreview)
                    DeleteObject(CBmpDialog::hpreview);

                CheckDlgButton(hdlg,IDC_SHOWPREVIEW,CBmpDialog::m_showpreview);
                SetDlgItemText(GetParent(hdlg),IDOK,TRANSLATE("Ok"));
                SetDlgItemText(GetParent(hdlg),IDCANCEL,TRANSLATE("Abbruch"));
                SetDlgItemText(GetParent(hdlg),1090,TRANSLATE("Dateiname:"));
                SetDlgItemText(GetParent(hdlg),1089,TRANSLATE("Dateitypen:"));
                SetDlgItemText(GetParent(hdlg),1091,TRANSLATE("&Suchen in:"));
                SetDlgItemText(hdlg,IDC_PREVIEW_STATIC,TRANSLATE("Vorschau"));
                SetDlgItemText(hdlg,IDC_SHOWPREVIEW,TRANSLATE("Vorschau anzeigen"));
                GetWindowText(GetParent(hdlg),buffer,sizeof(buffer)-1);
                SetWindowText(GetParent(hdlg),TRANSLATE(buffer));
                return 0;
            }

            if (pnmh->code == CDN_SELCHANGE)
            {

                if (!IsDlgButtonChecked(hdlg,IDC_SHOWPREVIEW))
                {                
                    if (CBmpDialog::hpreview)
                        DeleteObject(CBmpDialog::hpreview);

                    CBmpDialog::hpreview = NULL;

                    return 0;
                }
                
                SendMessage(GetParent(hdlg),CDM_GETFILEPATH ,1024,(LPARAM)filename);                

                if (CBmpDialog::hpreview)
                    DeleteObject(CBmpDialog::hpreview);
               
                CBmpDialog::hpreview = (HBITMAP)LoadImage(AfxGetInstanceHandle(),filename,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);

                HWND wnd = GetDlgItem(hdlg,IDC_PREVIEWBTN);

                InvalidateRect(wnd,NULL,TRUE);

                if (CBmpDialog::hpreview) {
                    GetObject(CBmpDialog::hpreview,sizeof(BITMAP),&bm);
        
                    wsprintf(str,TRANSLATE("Breite: %d Bildpunkte"),bm.bmWidth);
                    SetDlgItemText(hdlg,IDC_WIDTH,str);

                    wsprintf(str,TRANSLATE("H�he: %d Bildpunkte"),bm.bmHeight);
                    SetDlgItemText(hdlg,IDC_HEIGHT,str);
                    
                    switch (bm.bmBitsPixel) {
                        case 1:
                            SetDlgItemText(hdlg,IDC_DEPTH,TRANSLATE("2 Farben (monocromatisch)"));
                            break;
                        case 4:
                            SetDlgItemText(hdlg,IDC_DEPTH,TRANSLATE("16 Farben"));
                            break;
                            SetDlgItemText(hdlg,IDC_DEPTH,TRANSLATE("256 Farben"));
                            break;
                        case 16:
                            SetDlgItemText(hdlg,IDC_DEPTH,TRANSLATE("65536 Farben"));
                            break;
                        case 24:
                            SetDlgItemText(hdlg,IDC_DEPTH,TRANSLATE("16 Millionen Farben"));
                            break;

                        default:
                            SetDlgItemText(hdlg,IDC_DEPTH,"-");

                    }

                    OFSTRUCT o;

                    HFILE f = OpenFile(filename,&o,OF_READ);

                    wsprintf(str,TRANSLATE("Gr�sse: %ld Kb"),GetFileSize((HANDLE)f,NULL)/1024);

                    SetDlgItemText(hdlg,IDC_FSIZE,str);
                    
                    _lclose(f);


                }
                else {
                    SetDlgItemText(hdlg,IDC_WIDTH,"");
                    SetDlgItemText(hdlg,IDC_HEIGHT,"");
                    SetDlgItemText(hdlg,IDC_DEPTH,"");
                    SetDlgItemText(hdlg,IDC_FSIZE,"");
                }
            }
    }
    return 0;
}



IMPLEMENT_DYNAMIC(CBmpDialog, CFileDialog)



BEGIN_MESSAGE_MAP(CBmpDialog, CFileDialog)
	//{{AFX_MSG_MAP(CBmpDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CBmpDialog::CBmpDialog(BOOL bOpenFileDialog, 
                       LPCTSTR lpszDefExt, 
                       LPCTSTR lpszFileName,
                       LPCTSTR lpstrInitialDir ,
		                 DWORD dwFlags, 
                       LPCTSTR lpszFilter, 
                       CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	PROC_TRACE;


    m_ofn.lpstrFilter = "Bitmaps (*.bmp)\0*.bmp\0"\
                        "All Files (*.*)\0*.*\0\0";                            

    m_ofn.Flags |= (OFN_HIDEREADONLY |OFN_ENABLEHOOK| OFN_EXPLORER  |OFN_ENABLETEMPLATE);
    m_ofn.lpstrInitialDir = lpstrInitialDir;
    m_ofn.hInstance       = AfxGetInstanceHandle();
    m_ofn.lpTemplateName  = MAKEINTRESOURCE(IDC_PREVIEW);
    m_ofn.lpfnHook        = OFNHookProc;          
}

