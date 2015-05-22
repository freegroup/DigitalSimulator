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
#include "Application\Objects\buildin\digital\context\ElectricNodeContextTaster.h"

#include "DialogTasterParam.h"


BEGIN_MESSAGE_MAP(CDialogTasterParam, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogTasterParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CDialogTasterParam::CDialogTasterParam(CWnd* pParent,CElectricNode::CElectricNodeDokument& data)
   : inherited(CDialogTasterParam::IDD, pParent),  
   m_data(data){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogTasterParam)
		// HINWEIS: Der Klassen-Assistent fügt hier ElementInitialisierung ein
	//}}AFX_DATA_INIT
}


//----------------------------------------------------------------------------
void CDialogTasterParam::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogTasterParam)
	DDX_Control(pDX, IDC_IMAGE2_STATIC, m_image2);
	DDX_Control(pDX, IDC_IMAGE1_STATIC, m_image1);
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	//}}AFX_DATA_MAP
}


//----------------------------------------------------------------------------
BOOL CDialogTasterParam::OnInitDialog() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
   TRANSLATE_DIALOG_ITEM(IDC_DOWN_RADIO);	
   TRANSLATE_DIALOG_ITEM(IDC_UP_RADIO);	
   TRANSLATE_DIALOG_ITEM(IDOK);	
   TRANSLATE_DIALOG_ITEM(IDCANCEL);	

   m_okButton.SetShaded();
   m_cancelButton.SetShaded();

   SetWindowText(TRANSLATE("Taster Grundeinstellungen"));

   
   if( m_data.param[CElectricNodeContextTaster::DefaultState] == 0){
      ((CButton*)GetDlgItem(IDC_UP_RADIO))->SetCheck(1);
   }
   else{
      ((CButton*)GetDlgItem(IDC_DOWN_RADIO))->SetCheck(1);
   }


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

//----------------------------------------------------------------------------
void CDialogTasterParam::OnOK() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	// TODO: Zusätzliche Prüfung hier einfügen
   if( ((CButton*)GetDlgItem(IDC_DOWN_RADIO))->GetState() == 1 ){
      m_data.param[CElectricNodeContextTaster::DefaultState] = 1;
   }
   else{
      m_data.param[CElectricNodeContextTaster::DefaultState] = 0;
   }
	
	inherited::OnOK();
}
