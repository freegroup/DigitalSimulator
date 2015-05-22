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
#include "DialogDDEINEndPage.h"
#include "DialogDDEOutputParam.h"


BEGIN_MESSAGE_MAP(CDialogDDEINEndPage, CDialog)
	//{{AFX_MSG_MAP(CDialogDDEINEndPage)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CDialogDDEINEndPage::CDialogDDEINEndPage(CDialogDDEParamWizard* pParent /*=NULL*/):CDialog(CDialogDDEINEndPage::IDD,(CWnd*) pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogDDEINEndPage)
		// HINWEIS: Der Klassen-Assistent fügt hier ElementInitialisierung ein
	//}}AFX_DATA_INIT
   m_parent = pParent;
}


//----------------------------------------------------------------------------
void CDialogDDEINEndPage::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDDEINEndPage)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
void CDialogDDEINEndPage::OnShowWindow(BOOL bShow, UINT nStatus) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnShowWindow(bShow, nStatus);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	if(bShow==TRUE) {
      m_parent->SetBitmap(IDB_DDEIN_END_PAGE);
   }
	
}
