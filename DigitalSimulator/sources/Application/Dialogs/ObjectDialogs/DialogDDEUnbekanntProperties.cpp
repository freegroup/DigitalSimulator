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

#include "DialogDDEUnbekanntProperties.h"
#include "DialogDDEOutputParam.h"

BEGIN_MESSAGE_MAP(CDialogDDEUnbekanntProperties, CDialog)
	//{{AFX_MSG_MAP(CDialogDDEUnbekanntProperties)
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_ITEM_EDIT, OnChangeItemEdit)
	ON_EN_CHANGE(IDC_TOPIC_EDIT, OnChangeTopicEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
CDialogDDEUnbekanntProperties::CDialogDDEUnbekanntProperties(CDialogDDEParamWizard* pParent /*=NULL*/)
   : inherited(CDialogDDEUnbekanntProperties::IDD,(CWnd*)  pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogDDEUnbekanntProperties)
	m_item = _T("");
	m_topic = _T("");
	//}}AFX_DATA_INIT
    m_parent =pParent;
}


//----------------------------------------------------------------------------
void CDialogDDEUnbekanntProperties::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDDEUnbekanntProperties)
	DDX_Text(pDX, IDC_ITEM_EDIT, m_item);
	DDX_Text(pDX, IDC_TOPIC_EDIT, m_topic);
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
void CDialogDDEUnbekanntProperties::OnShowWindow(BOOL bShow, UINT nStatus) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
   TRANSLATE_DIALOG_ITEM(IDC_TOPIC_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_ITEM_STATIC);

	if(bShow==TRUE)   {
      m_parent->SetBitmap(IDB_DDE_PROPERTIES_UNKNOWN);
   	CheckNextButton();
      SetDDEValues();
   }
}

//----------------------------------------------------------------------------
void CDialogDDEUnbekanntProperties::OnChangeItemEdit(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// sendet diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
	// überschrieben wird, um die EM_SETEVENTMASK-Nachricht an das Steuerelement
	// mit dem ENM_CHANGE-Attribut ORed in die Maske lParam zu senden.
	
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CheckNextButton();
	SetDDEValues();
}

//----------------------------------------------------------------------------
void CDialogDDEUnbekanntProperties::OnChangeTopicEdit(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// sendet diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
	// überschrieben wird, um die EM_SETEVENTMASK-Nachricht an das Steuerelement
	// mit dem ENM_CHANGE-Attribut ORed in die Maske lParam zu senden.
	
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CheckNextButton();
	SetDDEValues();
}

//----------------------------------------------------------------------------
void CDialogDDEUnbekanntProperties::CheckNextButton(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	UpdateData();
   if(  (m_topic.IsEmpty() == TRUE)
      ||(m_item.IsEmpty()  == TRUE)){
      m_parent->SetNextState(FALSE);
   }
   else{
      m_parent->SetNextState(TRUE);
   }
}

//----------------------------------------------------------------------------
void CDialogDDEUnbekanntProperties::SetDDEValues(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    UpdateData();
    m_parent->SetItem(m_item);
    m_parent->SetTopic(m_topic);
}
