#include "stdafx.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"

#include "DialogLockDocument.h"


BEGIN_MESSAGE_MAP(CDialogLockDocument, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogLockDocument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CDialogLockDocument::CDialogLockDocument(CWnd* pParent /*=NULL*/)
	: inherited(CDialogLockDocument::IDD, pParent)
{
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogLockDocument)
	m_passwd1 = _T("");
	m_passwd2 = _T("");
	//}}AFX_DATA_INIT
}


void CDialogLockDocument::DoDataExchange(CDataExchange* pDX)
{
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogLockDocument)
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Text(pDX, IDC_PASSWD1_EDIT, m_passwd1);
	DDX_Text(pDX, IDC_PASSWD2_EDIT, m_passwd2);
	//}}AFX_DATA_MAP
}



void CDialogLockDocument::OnOK(){
	PROC_TRACE;


   UpdateData();
   if(m_passwd1 != m_passwd2)
   {
      TRANSLATE_DIALOG_ITEM(IDC_WARNING_STATIC);
      m_passwd1 = "";
      m_passwd2 = "";
      UpdateData(FALSE);
   }
   else
   {
      inherited::OnOK();
   }
}

BOOL CDialogLockDocument::OnInitDialog() {
	PROC_TRACE;

	inherited::OnInitDialog();
	
   TRANSLATE_DIALOG_ITEM(IDC_PASSWD1_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_PASSWD2_STATIC);
   TRANSLATE_DIALOG_ITEM(IDOK);
   TRANSLATE_DIALOG_ITEM(IDCANCEL);

   SetWindowText(TRANSLATE("COMMON.DIALOGHEADER.LOCKDOCUMENT"));

   m_okButton.SetShaded();
   m_cancelButton.SetShaded();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
