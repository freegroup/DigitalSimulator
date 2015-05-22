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

#include "DialogDDEOUTParamWizard.h"
#include "DialogDDEOUTEasyPortProperties.h"


#define DDEOUT_TOPIC_EASYPORT       "IOPanel"
#define DDEOUT_ITEM_EASYPORT        "MAB.%d.0.%d"
#define DDEOUT_ITEM_EASYPORT_LEN    (strlen(DDEOUT_ITEM_EASYPORT)-2)

BEGIN_MESSAGE_MAP(CDialogDDEOUTEasyPortProperties, CDialog)
	//{{AFX_MSG_MAP(CDialogDDEOUTEasyPortProperties)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_OUTPORT1_RADIO, OnOutport1Radio)
	ON_BN_CLICKED(IDC_OUTPORT2_RADIO, OnOutport2Radio)
	ON_CBN_SELCHANGE(IDC_DEVICE_COMBO, OnSelchangeDeviceCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CDialogDDEOUTEasyPortProperties::CDialogDDEOUTEasyPortProperties(CDialogDDEParamWizard* pParent /*=NULL*/)
   : CDialog(CDialogDDEOUTEasyPortProperties::IDD,(CWnd*) pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogDDEOUTEasyPortProperties)
	m_deviceId = _T("");
	//}}AFX_DATA_INIT
    m_parent =pParent;
}


//----------------------------------------------------------------------------
void CDialogDDEOUTEasyPortProperties::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDDEOUTEasyPortProperties)
	DDX_Control(pDX, IDC_DEVICE_COMBO, m_deviceIdCombo);
	DDX_CBString(pDX, IDC_DEVICE_COMBO, m_deviceId);
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
void CDialogDDEOUTEasyPortProperties::OnShowWindow(BOOL bShow, UINT nStatus) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnShowWindow(bShow, nStatus);
	
   TRANSLATE_DIALOG_ITEM(IDC_DEVICEID_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_OUTPORT1_RADIO);
   TRANSLATE_DIALOG_ITEM(IDC_OUTPORT2_RADIO);

   if(bShow==TRUE) {
      m_parent->SetBitmap(IDB_DDEOUT_PROPERTIES_EASYPORT);
      CheckItem();
      CheckNextButton();
   }
	
}

//----------------------------------------------------------------------------
void CDialogDDEOUTEasyPortProperties::OnOutport1Radio() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   char buffer[100];
   
   sprintf(buffer,DDEOUT_ITEM_EASYPORT,m_deviceIdCombo.GetCurSel()+1,0);
   m_parent->SetTopic(DDEOUT_TOPIC_EASYPORT);
   m_parent->SetItem(buffer);
}

//----------------------------------------------------------------------------
void CDialogDDEOUTEasyPortProperties::OnOutport2Radio() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   char buffer[100];
   
   sprintf(buffer,DDEOUT_ITEM_EASYPORT,m_deviceIdCombo.GetCurSel()+1,1);
   m_parent->SetTopic(DDEOUT_TOPIC_EASYPORT);
   m_parent->SetItem(buffer);
	
}


//----------------------------------------------------------------------------
void CDialogDDEOUTEasyPortProperties::CheckItem(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CString tmp = m_parent->GetItem();

   if(tmp.GetLength() != DDEOUT_ITEM_EASYPORT_LEN){
      CheckDlgButton(IDC_OUTPORT1_RADIO,1);
      m_deviceIdCombo.SetCurSel(0);
      OnOutport1Radio();
   }
   else {
      if(CB_ERR ==m_deviceIdCombo.SetCurSel(tmp.GetAt(4)-'1')){
         m_deviceIdCombo.SetCurSel(0);
      }

      if(tmp.GetAt(DDEOUT_ITEM_EASYPORT_LEN-1)== '0'){
         CheckDlgButton(IDC_OUTPORT1_RADIO,1);
         OnOutport1Radio();
      }
      else{
         CheckDlgButton(IDC_OUTPORT2_RADIO,1);
         OnOutport2Radio();
      }
   }

}


//----------------------------------------------------------------------------
void CDialogDDEOUTEasyPortProperties::CheckNextButton(){
//----------------------------------------------------------------------------
	PROC_TRACE;


}

//----------------------------------------------------------------------------
void CDialogDDEOUTEasyPortProperties::OnSelchangeDeviceCombo() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   char buffer[100];

   if(IsDlgButtonChecked(IDC_OUTPORT1_RADIO))
      sprintf(buffer,DDEOUT_ITEM_EASYPORT,m_deviceIdCombo.GetCurSel()+1,0);
   else
      sprintf(buffer,DDEOUT_ITEM_EASYPORT,m_deviceIdCombo.GetCurSel()+1,1);
   m_parent->SetTopic(DDEOUT_TOPIC_EASYPORT);
   m_parent->SetItem(buffer);
}
