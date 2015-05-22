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
#include "Application\Objects\buildin\digital\ElectricNode.h"
#include "Application\Dialogs\ObjectDialogs\DialogPrimaryObjectOptions.h"

//#include "windowsx.h"

BEGIN_MESSAGE_MAP(CDialogPrimaryObjectOptions, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogPrimaryObjectOptions)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CDialogPrimaryObjectOptions::CDialogPrimaryObjectOptions(CWnd* pParent,CElectricNode::CElectricNodeDokument& data, CRect startRect)
	: inherited(CDialogPrimaryObjectOptions::IDD, pParent),
     m_data(data),
     m_rect(startRect)

{
	//{{AFX_DATA_INIT(CDialogPrimaryObjectOptions)
	//}}AFX_DATA_INIT
}


//----------------------------------------------------------------------------
void CDialogPrimaryObjectOptions::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPrimaryObjectOptions)
	DDX_Control(pDX, IDC_IMAGE_STATIC, m_image);
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_OUTPUT_COUNT_SPIN, m_outputCountSpin);
	DDX_Control(pDX, IDC_INPUT_COUNT_SPIN,  m_inputCountSpin);
	DDX_Control(pDX, IDC_OUTPUT_COUNT_EDIT, m_outputCountEdit);
	DDX_Control(pDX, IDC_INPUT_COUNT_EDIT,  m_inputCountEdit);
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
BOOL CDialogPrimaryObjectOptions::OnInitDialog() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
   TRANSLATE_DIALOG_ITEM(IDC_INPUT_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_OUTPUT_STATIC);
   TRANSLATE_DIALOG_ITEM(IDOK);
   TRANSLATE_DIALOG_ITEM(IDCANCEL);
   SetWindowText(TRANSLATE("COMMON.DIALOGHEADER.COMMONPROPERTIES"));
   
   m_okButton.SetShaded();
   m_cancelButton.SetShaded();

   UpdateGUI();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

//----------------------------------------------------------------------------
void CDialogPrimaryObjectOptions::UpdateGUI(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CSize   inRange;
   CSize   outRange;
   
   outRange  = m_data.pOwner->GetOutputCountRange();
	m_outputCountSpin.SetBuddy(&m_outputCountEdit);
   m_outputCountSpin.SetRange(outRange.cx, outRange.cy);
   m_outputCountSpin.SetPos(max(m_data.outPorts.GetSize(),outRange.cx));
   m_outputCountSpin.SetPos(min(m_data.outPorts.GetSize(),outRange.cy));
	m_outputCountSpin.SetDelta(1);
   m_outputCountSpin.EnableWindow(outRange.cx != outRange.cy);
   m_outputCountEdit.EnableWindow(outRange.cx != outRange.cy);

   inRange  = m_data.pOwner->GetInputCountRange();
	m_inputCountSpin.SetBuddy(&m_inputCountEdit);
	m_inputCountSpin.SetRange(inRange.cx, inRange.cy);
   m_inputCountSpin.SetPos(max(m_data.inPorts.GetSize(),inRange.cx));
   m_inputCountSpin.SetPos(min(m_data.inPorts.GetSize(),inRange.cy));
	m_inputCountSpin.SetDelta(1);
   m_inputCountSpin.EnableWindow(inRange.cx != inRange.cy);
   m_inputCountEdit.EnableWindow(inRange.cx != inRange.cy);
}

//----------------------------------------------------------------------------
void CDialogPrimaryObjectOptions::OnOK() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_data.inCount  = (int)m_inputCountSpin.GetPos();
   m_data.outCount = (int)m_outputCountSpin.GetPos();
	
	inherited::OnOK();
}

//----------------------------------------------------------------------------
int CDialogPrimaryObjectOptions::OnCreate(LPCREATESTRUCT lpCreateStruct) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (inherited::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Speziellen Erstellungscode hier einfügen
   /*
   CRect to(
        lpCreateStruct->x,
        lpCreateStruct->y,
        lpCreateStruct->x+lpCreateStruct->cx,
        lpCreateStruct->y+lpCreateStruct->cy);
   DrawAnimatedRects(m_hWnd,IDANI_CAPTION, m_rect,to);
	*/
	return 0;
}

//----------------------------------------------------------------------------
void CDialogPrimaryObjectOptions::OnDestroy() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	CDialog::OnDestroy();
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
   /*
   CRect from;
   GetWindowRect(from);	
   DrawAnimatedRects(m_hWnd,IDANI_CAPTION, from, m_rect);
   */
}
