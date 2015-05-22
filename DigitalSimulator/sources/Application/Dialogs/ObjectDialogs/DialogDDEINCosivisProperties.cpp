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

#include "DialogDDEINCosivisProperties.h"
#include "DialogDDEOutputParam.h"


#define DDEIN_TOPIC_COSIVIS        "IOPanel"
#define DDEIN_ITEM_COSIVIS_MODEL   "DEB.1.0.0"
#define DDEIN_ITEM_COSIVIS_TASTER  "DEB.1.0.1"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogDDECosivisProperties 
BEGIN_MESSAGE_MAP(CDialogDDEINCosivisProperties, CDialog)
	//{{AFX_MSG_MAP(CDialogDDEINCosivisProperties)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_MODEL_RADIO, OnModelRadio)
	ON_BN_CLICKED(IDC_TASTER_RADIO, OnTasterRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//----------------------------------------------------------------------------
CDialogDDEINCosivisProperties::CDialogDDEINCosivisProperties(CDialogDDEParamWizard* pParent)	: CDialog(CDialogDDEINCosivisProperties::IDD,(CWnd*) pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogDDEINCosivisProperties)
	//}}AFX_DATA_INIT
    m_parent =pParent;
}


//----------------------------------------------------------------------------
void CDialogDDEINCosivisProperties::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDDEINCosivisProperties)
	//}}AFX_DATA_MAP
}


//----------------------------------------------------------------------------
void CDialogDDEINCosivisProperties::OnShowWindow(BOOL bShow, UINT nStatus) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::OnShowWindow(bShow, nStatus);
   TRANSLATE_DIALOG_ITEM(IDC_MODEL_RADIO);
   TRANSLATE_DIALOG_ITEM(IDC_TASTER_RADIO);

	if(bShow==TRUE)   {
      m_parent->SetBitmap(IDB_DDEIN_PROPERTIES_COSIVIS);
      if(m_parent->GetItem()==DDEIN_ITEM_COSIVIS_TASTER){
          CheckDlgButton(IDC_TASTER_RADIO,1);
          OnTasterRadio();
      }
      else {
          CheckDlgButton(IDC_MODEL_RADIO, 1);
          OnModelRadio();
      }
    	CheckNextButton();
   }
}

//----------------------------------------------------------------------------
void CDialogDDEINCosivisProperties::CheckNextButton(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_parent->SetNextState(TRUE);
}

//----------------------------------------------------------------------------
void CDialogDDEINCosivisProperties::OnModelRadio() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_parent->SetTopic(DDEIN_TOPIC_COSIVIS);	
	m_parent->SetItem(DDEIN_ITEM_COSIVIS_MODEL);	
}

//----------------------------------------------------------------------------
void CDialogDDEINCosivisProperties::OnTasterRadio() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_parent->SetTopic(DDEIN_TOPIC_COSIVIS);	
   m_parent->SetItem(DDEIN_ITEM_COSIVIS_TASTER);	
	
}
