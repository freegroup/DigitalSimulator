#include "stdafx.h"

#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"


#include "DialogUnlockDocument.h"


BEGIN_MESSAGE_MAP(CDialogUnlockDocument, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogUnlockDocument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CDialogUnlockDocument::CDialogUnlockDocument(CWnd* pParent /*=NULL*/)
	: inherited(CDialogUnlockDocument::IDD, pParent)
{
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogUnlockDocument)
	m_passwd = _T("");
	//}}AFX_DATA_INIT
}


void CDialogUnlockDocument::DoDataExchange(CDataExchange* pDX){
	PROC_TRACE;


	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogUnlockDocument)
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Text(pDX, IDC_PASSWD_EDIT, m_passwd);
	//}}AFX_DATA_MAP
}

BOOL CDialogUnlockDocument::OnInitDialog(){
	PROC_TRACE;


	inherited::OnInitDialog();

	
   TRANSLATE_DIALOG_ITEM(IDC_PASSWD_STATIC);
   TRANSLATE_DIALOG_ITEM(IDOK);
   TRANSLATE_DIALOG_ITEM(IDCANCEL);
   SetWindowText(TRANSLATE("Dokument aufschlieﬂen"));

   m_okButton.SetShaded();
   m_cancelButton.SetShaded();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
