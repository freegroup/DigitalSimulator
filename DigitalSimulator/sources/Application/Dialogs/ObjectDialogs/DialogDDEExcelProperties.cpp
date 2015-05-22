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

#include "DialogDDEExcelProperties.h"
#include "DialogDDEOutputParam.h"
#include "Application\Dialogs\CommonDialogs\TranslateFileDialog.h"

BEGIN_MESSAGE_MAP(CDialogDDEExcelProperties, CDialog)
	//{{AFX_MSG_MAP(CDialogDDEExcelProperties)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_FILE_SELECT_BUTTON, OnFileSelectButton)
	ON_EN_CHANGE(IDC_COLUMN_EDIT, OnChangeColumnEdit)
	ON_EN_CHANGE(IDC_ROW_EDIT, OnChangeRowEdit)
	ON_EN_CHANGE(IDC_FILE_NAME_EDIT, OnChangeFileNameEdit)
	ON_EN_CHANGE(IDC_FOLDER_PAGE_EDIT, OnChangeFolderPageEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//----------------------------------------------------------------------------
CDialogDDEExcelProperties::CDialogDDEExcelProperties(CDialogDDEParamWizard* pParent): CDialog(CDialogDDEExcelProperties::IDD,(CWnd*)  pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogDDEExcelProperties)
	m_column   = _T("");
	m_fileName = _T("");
	m_folder   = _T("");
	m_row      = _T("");
	//}}AFX_DATA_INIT
    m_parent =pParent;
}


//----------------------------------------------------------------------------
void CDialogDDEExcelProperties::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDDEExcelProperties)
	DDX_Text(pDX, IDC_COLUMN_EDIT, m_column);
	DDX_Text(pDX, IDC_FILE_NAME_EDIT, m_fileName);
	DDX_Text(pDX, IDC_FOLDER_PAGE_EDIT, m_folder);
	DDX_Text(pDX, IDC_ROW_EDIT, m_row);
	//}}AFX_DATA_MAP
}


//----------------------------------------------------------------------------
void CDialogDDEExcelProperties::OnShowWindow(BOOL bShow, UINT nStatus) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
   TRANSLATE_DIALOG_ITEM(IDC_FILE_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_TABLE_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_ROW_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_COLUMN_STATIC);

   
   if(bShow==TRUE)
   {
       CheckNextButton();
       m_parent->SetBitmap(IDB_DDE_PROPERTIES_EXCEL);
       SetDDEValues();
   }
	
}

//----------------------------------------------------------------------------
void CDialogDDEExcelProperties::OnFileSelectButton() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CTranslateFileDialog  dlg(TRUE,"",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Excel Files (*.xls)|*.xls|All Files(*.*)|*.*||",this);
   if(dlg.DoModal()==IDOK){
      m_fileName = dlg.GetFileName();
      UpdateData(FALSE);
      CheckNextButton();
      SetDDEValues();
   }
}

//----------------------------------------------------------------------------
BOOL CDialogDDEExcelProperties::OnInitDialog() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
   char buffer1[200];
   char *p=buffer1;

   sprintf(buffer1,"%s",(LPCSTR)m_parent->GetTopic());

   if(p) {
      while(*p){
         if(*p == ']'){
            p++;
            break;
         }
         if(*p!='[' )
            m_fileName = m_fileName + CString(*p);
         p++;
      }
      while(*p){
         m_folder = m_folder + CString(*p);
         p++;
      }
   }

   sprintf(buffer1,"%s",(LPCSTR)m_parent->GetItem());
   p=buffer1;

   if(p) {
      while(*p){
         if(*p == 'S'){
            p++;
            break;
         }
         if(isdigit(*p) )
            m_row = m_row + CString(*p);
         p++;
      }
      while(*p){
         if(isdigit(*p))
            m_column = m_column + CString(*p);
         else
            break;
         p++;
      }
   }


   UpdateData(FALSE);

   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

//----------------------------------------------------------------------------
void CDialogDDEExcelProperties::SetDDEValues(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   char topic[200];
   char item[200];
   
   sprintf(topic,"[%s]%s",m_fileName, m_folder);
   sprintf(item,"Z%sS%s", m_row, m_column);

   m_parent->SetTopic(topic);
   m_parent->SetItem(item);
}

//----------------------------------------------------------------------------
void CDialogDDEExcelProperties::OnChangeColumnEdit() {
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
void CDialogDDEExcelProperties::OnChangeRowEdit() {
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
void CDialogDDEExcelProperties::OnChangeFileNameEdit(){
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
void CDialogDDEExcelProperties::OnChangeFolderPageEdit() {
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
void CDialogDDEExcelProperties::CheckNextButton(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	UpdateData();
   if(  (m_fileName.IsEmpty() == TRUE)
      ||(m_folder.IsEmpty()   == TRUE)
      ||(m_column.IsEmpty()   == TRUE)
      ||(m_row.IsEmpty()      == TRUE)){
      m_parent->SetNextState(FALSE);
   }
   else{
      m_parent->SetNextState(TRUE);
   }
}
