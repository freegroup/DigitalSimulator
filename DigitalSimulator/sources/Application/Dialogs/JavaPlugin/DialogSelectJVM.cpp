#include "stdafx.h"
#include "Application\DigitalSimulatorApp.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"
#include "DialogSelectJVM.h"

BEGIN_MESSAGE_MAP(CDialogSelectJVM, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogSelectJVM)
	ON_LBN_DBLCLK(IDC_JVM_LIST, OnDblclkJvmList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDialogSelectJVM::CDialogSelectJVM(CWnd* pParent /*=NULL*/)
	: inherited(CDialogSelectJVM::IDD, pParent)
{
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogSelectJVM)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDialogSelectJVM::DoDataExchange(CDataExchange* pDX)
{
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSelectJVM)
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_JVM_LIST, m_jvmList);
	//}}AFX_DATA_MAP
}


BOOL CDialogSelectJVM::OnInitDialog() 
{
	PROC_TRACE;

	inherited::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
   TRANSLATE_DIALOG_ITEM(IDOK);
   TRANSLATE_DIALOG_ITEM(IDCANCEL);
   TRANSLATE_DIALOG_ITEM(IDC_JVM_SELECTION_TITLE);
   
   m_okButton.SetShaded();
   m_cancelButton.SetShaded();

   SetWindowText(TRANSLATE("VirtualMachine für die Java Laufzeitumgebung auswählen"));
	
   int size = m_jvms.GetSize();
   while(size--)
   {
      m_jvmList.AddString(m_jvms.ElementAt(size));
   }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDialogSelectJVM::OnDblclkJvmList() 
{
	PROC_TRACE;

   OnOK();
}

void CDialogSelectJVM::OnOK() 
{
	PROC_TRACE;

   if(m_jvmList.GetCurSel()!=LB_ERR )
   {
      m_jvmList.GetText(m_jvmList.GetCurSel(),m_jvm);
   	inherited::OnOK();
   }
   else
   {
      inherited::OnCancel();   
   }

}
