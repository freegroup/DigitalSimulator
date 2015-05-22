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
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"

#include "DialogDDESelectApplication.h"
#include "DialogDDEOutputParam.h"

BEGIN_MESSAGE_MAP(CDialogDDESelectApplication, CDialog)
	//{{AFX_MSG_MAP(CDialogDDESelectApplication)
	ON_BN_CLICKED(IDC_COSIVIS_RADIO, OnRadioCosivis)
	ON_BN_CLICKED(IDC_EXCEL_RADIO, OnRadioExcel)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_UNKNOWN_RADIO, OnUnknownRadio)
	ON_EN_CHANGE(IDC_EIGENER_DDE_SERVER_EDIT, OnChangeEigenerDdeServerEdit)
	ON_BN_CLICKED(IDC_EASYPORT_RADIO, OnEasyportRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
CDialogDDESelectApplication::CDialogDDESelectApplication(CDialogDDEParamWizard* pParent )
   : inherited(CDialogDDESelectApplication::IDD,(CWnd*) pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogDDESelectApplication)
		// HINWEIS: Der Klassen-Assistent fügt hier ElementInitialisierung ein
	//}}AFX_DATA_INIT
    m_parent =pParent;
}


//----------------------------------------------------------------------------
void CDialogDDESelectApplication::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDDESelectApplication)
	DDX_Control(pDX, IDC_EIGENER_DDE_SERVER_EDIT, m_ddeServerEdit);
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
void CDialogDDESelectApplication::OnRadioCosivis() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_parent->SetBitmap(IDB_CONNECT_COSIVIS);
	m_parent->SetServer(DDE_STRING_SERVER_COSIVIS);
   m_ddeServerEdit.EnableWindow(FALSE);
   CheckNextButton();
}

//----------------------------------------------------------------------------
void CDialogDDESelectApplication::OnRadioExcel() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_parent->SetBitmap(IDB_CONNECT_EXCEL);
   m_parent->SetServer(DDE_STRING_SERVER_EXCEL);
   m_ddeServerEdit.EnableWindow(FALSE);
   CheckNextButton();
}

//----------------------------------------------------------------------------
void CDialogDDESelectApplication::OnEasyportRadio() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_parent->SetBitmap(IDB_CONNECT_EASYPORT);
   m_parent->SetServer(DDE_STRING_SERVER_EASYPORT);	
   m_ddeServerEdit.EnableWindow(FALSE);
   CheckNextButton();
}

//----------------------------------------------------------------------------
void CDialogDDESelectApplication::OnShowWindow(BOOL bShow, UINT nStatus) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnShowWindow(bShow, nStatus);

   TRANSLATE_DIALOG_ITEM(IDC_EXCEL_RADIO);
   TRANSLATE_DIALOG_ITEM(IDC_EASYPORT_RADIO);
   TRANSLATE_DIALOG_ITEM(IDC_COSIVIS_RADIO);

	CString server = m_parent->GetServer();

   if(server == DDE_STRING_SERVER_EXCEL)
   {
       CheckRadioButton(IDC_EXCEL_RADIO,IDC_UNKNOWN_RADIO,IDC_EXCEL_RADIO);
       OnRadioExcel();
   }
   else if(server == DDE_STRING_SERVER_COSIVIS)
   {
       CheckRadioButton(IDC_EXCEL_RADIO,IDC_UNKNOWN_RADIO,IDC_COSIVIS_RADIO);
       OnRadioCosivis();
   }
   else if(server == DDE_STRING_SERVER_EASYPORT)
   {
       CheckRadioButton(IDC_EXCEL_RADIO,IDC_UNKNOWN_RADIO,IDC_EASYPORT_RADIO);
       OnEasyportRadio();
   }
   else 
   {
       CheckRadioButton(IDC_EXCEL_RADIO,IDC_UNKNOWN_RADIO,IDC_UNKNOWN_RADIO);
       OnUnknownRadio();
   }

	
}

//----------------------------------------------------------------------------
void CDialogDDESelectApplication::OnUnknownRadio() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   CString tmp;
   m_ddeServerEdit.GetWindowText(tmp);
   m_ddeServerEdit.EnableWindow(TRUE);
	m_parent->SetServer(tmp);
	m_parent->SetBitmap(IDB_CONNECT_UNKNOWN);
   CheckNextButton();
}

//----------------------------------------------------------------------------
void CDialogDDESelectApplication::OnChangeEigenerDdeServerEdit() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// sendet diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
	// überschrieben wird, um die EM_SETEVENTMASK-Nachricht an das Steuerelement
	// mit dem ENM_CHANGE-Attribut ORed in die Maske lParam zu senden.
	
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
   CString tmp;
   m_ddeServerEdit.GetWindowText(tmp);
	m_parent->SetServer(tmp);
   CheckNextButton();
	
}

//----------------------------------------------------------------------------
void CDialogDDESelectApplication::CheckNextButton(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_parent->SetNextState(!m_parent->GetServer().IsEmpty());
}

