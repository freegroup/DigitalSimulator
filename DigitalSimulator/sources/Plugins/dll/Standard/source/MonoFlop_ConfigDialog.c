// ConfigDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "context.h"
#include "ConfigDialog.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CConfigDialog 

CConfigDialog::CConfigDialog(CWnd* pParent /*=NULL*/)
	: inherited(CConfigDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDialog)
	m_unit = -1;
	m_value = 0;
	m_trigger = -1;
	//}}AFX_DATA_INIT
   
}


void CConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDialog)
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_TRIGGER_COMBO, m_triggerCombo);
	DDX_Control(pDX, IDC_VALUE_EDIT, m_valueEdit);
	DDX_Control(pDX, IDC_UNIT_COMBO, m_unitCombo);
	DDX_CBIndex(pDX, IDC_UNIT_COMBO, m_unit);
	DDX_Text(pDX, IDC_VALUE_EDIT, m_value);
	DDV_MinMaxLong(pDX, m_value, 0, LONG_MAX);
	DDX_CBIndex(pDX, IDC_TRIGGER_COMBO, m_trigger);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDialog, CSnapDialog)
	//{{AFX_MSG_MAP(CConfigDialog)
	ON_EN_CHANGE(IDC_VALUE_EDIT, OnChangeValueEdit)
	ON_CBN_SELCHANGE(IDC_UNIT_COMBO, OnSelchangeUnitCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CConfigDialog 

//----------------------------------------------------------------------------
BOOL CConfigDialog::OnInitDialog() {
//----------------------------------------------------------------------------

	inherited::OnInitDialog();
	
   m_okButton.SetShaded();
   m_cancelButton.SetShaded();

   m_triggerCombo.AddString("positiv");
   m_triggerCombo.AddString("negative");

  	m_unitCombo.AddString("milli seconds");
	m_unitCombo.AddString("seconds");
	m_unitCombo.AddString("minutes");

   m_unitCombo.SetCurSel(m_unit);
   m_triggerCombo.SetCurSel(m_trigger);

   CString valueString ;
   valueString.Format("%d",m_value);
   m_valueEdit.SetWindowText(valueString);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

//----------------------------------------------------------------------------
void CConfigDialog::OnChangeValueEdit() {
//----------------------------------------------------------------------------

   CheckTimeInterval();
}

//----------------------------------------------------------------------------
void CConfigDialog::OnSelchangeUnitCombo() {
//----------------------------------------------------------------------------

	CheckTimeInterval();
}

//----------------------------------------------------------------------------
void CConfigDialog::CheckTimeInterval() {
//----------------------------------------------------------------------------
   
   UpdateData();
   
   if((m_unit==0) && (m_value<55))
      m_valueEdit.SetWindowText("55");
}
