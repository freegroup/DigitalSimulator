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

#include "DialogDDEINEasyPortProperties.h"
#include "DialogDDEOutputParam.h"


#define DDEIN_TOPIC_EASYPORT    "IOPanel"
#define DDEIN_ITEM_EASYPORT     "DEB.%d.0.%d"
#define DDEIN_ITEM_EASYPORT_LEN (strlen(DDEIN_ITEM_EASYPORT)-2)
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogDDEEzDDEProperties 


//----------------------------------------------------------------------------
CDialogDDEINEasyPortProperties::CDialogDDEINEasyPortProperties(CDialogDDEParamWizard* pParent /*=NULL*/) : CDialog(CDialogDDEINEasyPortProperties::IDD,(CWnd*)  pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

   //{{AFX_DATA_INIT(CDialogDDEINEasyPortProperties)
   m_deviceId = _T("");
   //}}AFX_DATA_INIT
    m_parent =pParent;
}


//----------------------------------------------------------------------------
void CDialogDDEINEasyPortProperties::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CDialogDDEINEasyPortProperties)
	DDX_Control(pDX, IDC_DEVICE_COMBO, m_deviceIdCombo);
   DDX_CBString(pDX, IDC_DEVICE_COMBO, m_deviceId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogDDEINEasyPortProperties, CDialog)
   //{{AFX_MSG_MAP(CDialogDDEINEasyPortProperties)
   ON_WM_SHOWWINDOW()
   ON_CBN_SELCHANGE(IDC_DEVICE_COMBO, OnSelchangeDeviceCombo)
   ON_BN_CLICKED(IDC_INPORT1_RADIO, OnInport1Radio)
   ON_BN_CLICKED(IDC_INPORT2_RADIO, OnInport2Radio)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDialogDDEINEasyPortProperties 

//----------------------------------------------------------------------------
void CDialogDDEINEasyPortProperties::OnShowWindow(BOOL bShow, UINT nStatus) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::OnShowWindow(bShow, nStatus);
   
   // TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
   TRANSLATE_DIALOG_ITEM(IDC_DEVICEID_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_INPORT1_RADIO);
   TRANSLATE_DIALOG_ITEM(IDC_INPORT2_RADIO);

   if(bShow==TRUE) {
      m_parent->SetBitmap(IDB_DDEIN_PROPERTIES_EASYPORT);
      CheckItem();
      CheckNextButton();
   }
   
}


//----------------------------------------------------------------------------
void CDialogDDEINEasyPortProperties::CheckNextButton(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_parent->SetNextState(TRUE);
}


//----------------------------------------------------------------------------
void CDialogDDEINEasyPortProperties::OnInport1Radio(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
   char buffer[100];
   
   sprintf(buffer,DDEIN_ITEM_EASYPORT,m_deviceIdCombo.GetCurSel()+1,0);
   m_parent->SetTopic(DDEIN_TOPIC_EASYPORT);
   m_parent->SetItem(buffer);
   
}

//----------------------------------------------------------------------------
void CDialogDDEINEasyPortProperties::OnInport2Radio() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   // TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
   char buffer[100];
   
   sprintf(buffer,DDEIN_ITEM_EASYPORT,m_deviceIdCombo.GetCurSel()+1,1);
   m_parent->SetTopic(DDEIN_TOPIC_EASYPORT);
   m_parent->SetItem(buffer);
}


//----------------------------------------------------------------------------
void CDialogDDEINEasyPortProperties::OnSelchangeDeviceCombo() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   // TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
   char buffer[100];

   if(IsDlgButtonChecked(IDC_INPORT1_RADIO))
      sprintf(buffer,DDEIN_ITEM_EASYPORT,m_deviceIdCombo.GetCurSel()+1,0);
   else
      sprintf(buffer,DDEIN_ITEM_EASYPORT,m_deviceIdCombo.GetCurSel()+1,1);
   m_parent->SetTopic(DDEIN_TOPIC_EASYPORT);
   m_parent->SetItem(buffer);
}


//----------------------------------------------------------------------------
void CDialogDDEINEasyPortProperties::CheckItem(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CString tmp = m_parent->GetItem();

   if(tmp.GetLength() != DDEIN_ITEM_EASYPORT_LEN){
      CheckDlgButton(IDC_INPORT1_RADIO,1);
      m_deviceIdCombo.SetCurSel(0);
      OnInport1Radio();
   }
   else {
      if(CB_ERR ==m_deviceIdCombo.SetCurSel(tmp.GetAt(4)-'1')){
         m_deviceIdCombo.SetCurSel(0);
      }

      if(tmp.GetAt(DDEIN_ITEM_EASYPORT_LEN-1)== '0'){
         CheckDlgButton(IDC_INPORT1_RADIO,1);
         OnInport1Radio();
      }
      else{
         CheckDlgButton(IDC_INPORT2_RADIO,1);
         OnInport2Radio();
      }
   }

}


