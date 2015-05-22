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
#include "Application\Objects\buildin\digital\context\ElectricNodeContextTakt.h"
#include "DialogTaktParam.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogTaktParam 
BEGIN_MESSAGE_MAP(CDialogTaktParam, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogTaktParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CDialogTaktParam::CDialogTaktParam(CWnd* pParent,CElectricNode::CElectricNodeDokument& data)
	: inherited(CDialogTaktParam::IDD, pParent),
     m_data(data)

{
	//{{AFX_DATA_INIT(CDialogTaktParam)
	//}}AFX_DATA_INIT
}


//----------------------------------------------------------------------------
void CDialogTaktParam::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogTaktParam)
	DDX_Control(pDX, IDC_IMAGE_STATIC, m_image);
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_LOW_EDIT, m_lowEdit);
	DDX_Control(pDX, IDC_HIGH_EDIT, m_highEdit);
	DDX_Control(pDX, IDC_LOW_SPIN, m_lowSpin);
	DDX_Control(pDX, IDC_HIGH_SPIN, m_highSpin);
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
BOOL CDialogTaktParam::OnInitDialog() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
   TRANSLATE_DIALOG_ITEM(IDC_HIGHTIME_STATIC);	
   TRANSLATE_DIALOG_ITEM(IDC_LOWTIME_STATIC);	
   TRANSLATE_DIALOG_ITEM(IDOK);	
   TRANSLATE_DIALOG_ITEM(IDCANCEL);	
   SetWindowText(TRANSLATE("COMMON.DIALOGHEADER.OBJECTTAKTDIALOG"));

   m_okButton.SetShaded();
   m_cancelButton.SetShaded();

   m_lowSpin.SetBuddy(&m_lowEdit);
	m_lowSpin.SetRange(1, 100.);
	m_lowSpin.SetPos(max(1,(float)m_data.param[CElectricNodeContextTakt::maxLowTime]));
	m_lowSpin.SetDelta(1);

	m_highSpin.SetBuddy(&m_highEdit);
	m_highSpin.SetRange(1, 100.);
	m_highSpin.SetPos(max(1,(float)m_data.param[CElectricNodeContextTakt::maxHighTime]));
	m_highSpin.SetDelta(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

//----------------------------------------------------------------------------
void CDialogTaktParam::OnOK(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::OnOK();

   m_data.param[CElectricNodeContextTakt::maxLowTime]  = (int)m_lowSpin.GetPos();
   m_data.param[CElectricNodeContextTakt::maxHighTime] = (int)m_highSpin.GetPos();
}
