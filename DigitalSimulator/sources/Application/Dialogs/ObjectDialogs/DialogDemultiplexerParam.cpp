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
#include "math.h"
#include "stdafx.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Objects\buildin\digital\ElectricNode.h"
#include "Application\Objects\buildin\digital\context\ElectricNodeContextDemultiplexer.h"

#include "DialogDemultiplexerParam.h"


BEGIN_MESSAGE_MAP(CDialogDemultiplexerParam, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogDemultiplexerParam)
	ON_EN_CHANGE(IDC_ADDRESS_COUNT_EDIT, OnChangeAddressCountEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDialogDemultiplexerParam::CDialogDemultiplexerParam(CWnd* pParent,CElectricNode::CElectricNodeDokument& data)
	: inherited(CDialogDemultiplexerParam::IDD, pParent),
     m_data(data)
{
	//{{AFX_DATA_INIT(CDialogDemultiplexerParam)
	m_addressCount = 0;
	m_outputCount = 0;
	//}}AFX_DATA_INIT
}


//----------------------------------------------------------------------------
void CDialogDemultiplexerParam::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDemultiplexerParam)
	DDX_Control(pDX, IDC_IMAGE_STATIC, m_image);
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_OUTPUT_COUNT_EDIT, m_outputEdit);
	DDX_Control(pDX, IDC_ADDRESS_COUNT_SPIN, m_countSpin);
	DDX_Control(pDX, IDC_ADDRESS_COUNT_EDIT, m_countEdit);
	DDX_Text(pDX, IDC_ADDRESS_COUNT_EDIT, m_addressCount);
	DDX_Text(pDX, IDC_OUTPUT_COUNT_EDIT, m_outputCount);
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
BOOL CDialogDemultiplexerParam::OnInitDialog() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnInitDialog();
	
	// TODO: Zus�tzliche Initialisierung hier einf�gen
   TRANSLATE_DIALOG_ITEM(IDOK);	
   TRANSLATE_DIALOG_ITEM(IDCANCEL);	
   TRANSLATE_DIALOG_ITEM(IDC_ADDRESS_STATIC);	
   TRANSLATE_DIALOG_ITEM(IDC_OUTPUT_STATIC);	
   SetWindowText(TRANSLATE("Demultiplexer Grundeinstellungen"));
	
   m_okButton.SetShaded();
   m_cancelButton.SetShaded();

   CSize   inRange;
   CSize   outRange;

   inRange   = m_data.pOwner->GetInputCountRange();
   outRange  = m_data.pOwner->GetOutputCountRange();

   m_countSpin.SetBuddy(&m_countEdit);
	m_countSpin.SetRange(1,4);
   m_countSpin.SetPos(max(m_data.param[CElectricNodeContextDemultiplexer::addressCount],1));
   m_countSpin.SetPos(min(m_data.param[CElectricNodeContextDemultiplexer::addressCount],4));

   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}


//----------------------------------------------------------------------------
void CDialogDemultiplexerParam::OnChangeAddressCountEdit() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   static lastPos =0;

   char buffer[100];
   sprintf(buffer,"%d", (int)pow(2,m_countSpin.GetPos()));
   m_outputEdit.SetWindowText(buffer);
}

//----------------------------------------------------------------------------
void CDialogDemultiplexerParam::OnOK() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	UpdateData();

   m_data.outCount  = m_outputCount;
   m_data.inCount   = 1 + m_addressCount;

   inherited::OnOK();
}
