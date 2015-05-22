#include "stdafx.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Objects\plugin\DLL\SimpleType\ObjectPluginManager.h"
#include "Application\Objects\plugin\DLL\SimpleType\Context\ElectricNodeContextPluginWrapper.h"

#include "DialogPluginObjectOptions.h"


BEGIN_MESSAGE_MAP(CDialogPluginObjectOptions, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogPluginObjectOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
CDialogPluginObjectOptions::CDialogPluginObjectOptions(CWnd* pParent, CElectricNode::CElectricNodeDokument& data)	
: inherited(CDialogPluginObjectOptions::IDD, pParent),
   m_data(data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   //{{AFX_DATA_INIT(CDialogPluginObjectOptions)
	//}}AFX_DATA_INIT
}


//----------------------------------------------------------------------------
void CDialogPluginObjectOptions::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPluginObjectOptions)
	DDX_Control(pDX, IDC_IMAGE_STATIC, m_image);
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_OUTPUT_COUNT_SPIN, m_outputSpin);
	DDX_Control(pDX, IDC_INPUT_COUNT_SPIN, m_inputSpin);
	DDX_Control(pDX, IDC_OUTPUT_COUNT_EDIT, m_outputEdit);
	DDX_Control(pDX, IDC_INPUT_COUNT_EDIT, m_inputEdit);
	DDX_Control(pDX, IDC_URL,   m_url);
	DDX_Control(pDX, IDC_EMAIL, m_email);
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
BOOL CDialogPluginObjectOptions::OnInitDialog() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnInitDialog();

   TRANSLATE_DIALOG_ITEM(IDC_INPUT_STATIC);	
   TRANSLATE_DIALOG_ITEM(IDC_OUTPUT_STATIC);	
   TRANSLATE_DIALOG_ITEM(IDC_DEVELOPER_STATIC);	
   TRANSLATE_DIALOG_ITEM(IDC_URL_STATIC);	
   TRANSLATE_DIALOG_ITEM(IDC_EMAIL_STATIC);	
   TRANSLATE_DIALOG_ITEM(IDC_VERSION_STATIC);	
   TRANSLATE_DIALOG_ITEM(IDOK);	
   TRANSLATE_DIALOG_ITEM(IDCANCEL);	
	
   m_okButton.SetShaded();
   m_cancelButton.SetShaded();

   CSize   inRange;
   CSize   outRange;

   outRange  = m_data.pOwner->GetOutputCountRange();
	m_outputSpin.SetBuddy(&m_outputEdit);
   m_outputSpin.SetRange(outRange.cx, outRange.cy);
   m_outputSpin.SetPos(max(m_data.outPorts.GetSize(),outRange.cx));
   m_outputSpin.SetPos(min(m_data.outPorts.GetSize(),outRange.cy));
	m_outputSpin.SetDelta(1);
   m_outputSpin.EnableWindow(outRange.cx != outRange.cy);
   m_outputEdit.EnableWindow(outRange.cx != outRange.cy);

   inRange  = m_data.pOwner->GetInputCountRange();
	m_inputSpin.SetBuddy(&m_inputEdit);
	m_inputSpin.SetRange(inRange.cx, inRange.cy);
   m_inputSpin.SetPos(max(m_data.inPorts.GetSize(),inRange.cx));
   m_inputSpin.SetPos(min(m_data.inPorts.GetSize(),inRange.cy));
	m_inputSpin.SetDelta(1);
   m_inputSpin.EnableWindow(inRange.cx != inRange.cy);
   m_inputEdit.EnableWindow(inRange.cx != inRange.cy);

   m_email.SetReceiver("juhu");
   m_email.SetSubject("Question about DigitalSimulator Plugin");
	m_email.SetUnderline(FALSE);

   // Plugindaten beschaffen
   //
   IObjectInfo* obj=(IObjectInfo*)ObjectPluginManager::createInstance(m_data.key, "IObjectInfo");
   if(obj){
      GetDlgItem(IDC_DEVELOPER)->SetWindowText(obj->getProgrammerName());
      GetDlgItem(IDC_URL)->SetWindowText(obj->getProgrammerURL());
      m_url.SetURL(obj->getProgrammerURL());
      GetDlgItem(IDC_EMAIL)->SetWindowText(obj->getProgrammerMail());
      m_email.SetReceiver(obj->getProgrammerMail());
      m_email.SetSubject("Digitalsimulator Object Plugin");
      GetDlgItem(IDC_VERSION)->SetWindowText(obj->getVersion());
      SetWindowText(TRANSLATE("COMMON.DIALOGHEADER.DLLOBJECT")+CString(" [")+ CString(TRANSLATE(obj->getName()))+CString("]"));
      m_email.SetAutoSize();
      m_url.SetAutoSize();
      obj->Destroy();
   }
   else{
      SetWindowText(TRANSLATE("Objektoptionen"));
      TRANSLATE_DIALOG_ITEM(IDC_DEVELOPER);	
      TRANSLATE_DIALOG_ITEM(IDC_URL);	
      TRANSLATE_DIALOG_ITEM(IDC_EMAIL);	
      TRANSLATE_DIALOG_ITEM(IDC_VERSION);	
   }

   return TRUE;
}

//----------------------------------------------------------------------------
void CDialogPluginObjectOptions::OnOK() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_data.inCount  = (int)m_inputSpin.GetPos();
   m_data.outCount = (int)m_outputSpin.GetPos();

   inherited::OnOK();
}
