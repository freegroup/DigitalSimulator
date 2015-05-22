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
#include "DialogDividerParam.h"

BEGIN_MESSAGE_MAP(CDialogDividerParam, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogDividerParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
CDialogDividerParam::CDialogDividerParam(CWnd* pParent /*=NULL*/)
	: inherited(CDialogDividerParam::IDD, pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogDividerParam)
	m_faktor = 0;
	//}}AFX_DATA_INIT
}


//----------------------------------------------------------------------------
void CDialogDividerParam::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDividerParam)
	DDX_Control(pDX, IDC_IMAGE_STATIC, m_image);
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Text(pDX, IDC_FAKTOR_EDIT, m_faktor);
	DDV_MinMaxLong(pDX, m_faktor, 1, 10000);
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
BOOL CDialogDividerParam::OnInitDialog() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	UpdateData(FALSE);
   TRANSLATE_DIALOG_ITEM(IDC_FORMEL_STATIC);
   TRANSLATE_DIALOG_ITEM(IDOK);
   TRANSLATE_DIALOG_ITEM(IDCANCEL);
   SetWindowText(TRANSLATE("COMMON.DIALOGHEADER.OBJECTDIVIDER"));

   m_okButton.SetShaded();
   m_cancelButton.SetShaded();

   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
