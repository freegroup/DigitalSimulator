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

#include "DialogDDEOutputParam.h"
#include <typeinfo.h>

BEGIN_MESSAGE_MAP(CDialogDDEParamWizard, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogDDEParamWizard)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CDialogDDEParamWizard::CDialogDDEParamWizard(CWnd* pParent /*=NULL*/)
   : inherited(CDialogDDEParamWizard::IDD, pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogDDEParamWizard)
	//}}AFX_DATA_INIT
	iCurIdx = -1;
	csTitle = TRANSLATE("DDE Wizard");
}

//----------------------------------------------------------------------------
CDialogDDEParamWizard::~CDialogDDEParamWizard(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	pPages.RemoveAll();
	csText.RemoveAll();
	csIds.RemoveAll();
}

//----------------------------------------------------------------------------
void CDialogDDEParamWizard::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDDEParamWizard)
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_BACK, m_backButton);
	DDX_Control(pDX, IDC_HEADER, m_headerStatic);
	DDX_Control(pDX, IDC_ITEM_STATIC, m_itemStatic);
	DDX_Control(pDX, IDC_TOPIC_STATIC, m_topicStatic);
	DDX_Control(pDX, IDC_SERVER_STATIC, m_serverStatic);
	DDX_Control(pDX, IDC_WIZARD_BITMAP, m_wizardBitmap);
	DDX_Control(pDX, IDC_STATIC_PALETTE, m_wndFrame);
	//}}AFX_DATA_MAP
}


//----------------------------------------------------------------------------
BOOL CDialogDDEParamWizard::OnInitDialog() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnInitDialog();
   TRANSLATE_DIALOG_ITEM(IDC_HEADER);
   TRANSLATE_DIALOG_ITEM(IDC_PARAMFRAME_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_SERVERHEADER_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_TOPICHEADER_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_ITEMHEADER_STATIC);
	
   m_okButton.SetShaded();
   m_backButton.SetShaded();
   m_cancelButton.SetShaded();

	if (pPages.GetSize() > 0)
	{
		CRect rc;
		m_wndFrame.GetWindowRect(rc);
		ScreenToClient(rc);
		for (int t = 0; t < pPages.GetSize(); t++)
		{
			CDialog * pDlg1 = GetDialog(t);
			if (pDlg1)
			{
				pDlg1->Create(csIds.GetAt(t), this);
				pDlg1->SetWindowPos(0,rc.left+3, rc.top+3, rc.Width()-6, rc.Height()-6, SWP_NOZORDER);
			}			
		}
		SetCurSel(0);
	}
	SetWindowText(csTitle);
   TRANSLATE_DIALOG_ITEM(IDC_BACK);
   TRANSLATE_DIALOG_ITEM(IDCANCEL);

	if (pPages.GetSize() > 1) 
      TRANSLATE_DIALOG_ITEM(IDOK)
	else 
      TRANSLATE_DIALOG_ITEM(IDOK)

   GetDlgItem(IDC_BACK)->EnableWindow(FALSE);
   
   SetServer(m_server);
   SetTopic(m_topic);
   SetItem(m_item);

   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

//----------------------------------------------------------------------------
void CDialogDDEParamWizard::OnCancel() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	ClosePages();
	
	inherited::OnCancel();
}

//----------------------------------------------------------------------------
void CDialogDDEParamWizard::OnOK() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (iCurIdx < pPages.GetSize() - 1) 	{
      if(iCurIdx==0) {
     		SetCurSel(1);
      }
      else if(iCurIdx==1){
          if(m_server == DDE_STRING_SERVER_EXCEL){
              SetCurSel(2);
          }
          else if(m_server == DDE_STRING_SERVER_EASYPORT){
              SetCurSel(3);
          }
          else if(m_server == DDE_STRING_SERVER_COSIVIS){
              SetCurSel(4);
          }
          else{
              SetCurSel(5);
          }
      }
      else if(iCurIdx==2){
              SetCurSel(6);
      }
      else if(iCurIdx==3){
              SetCurSel(6);
      }
      else if(iCurIdx==4){
              SetCurSel(6);
      }
      else if(iCurIdx==5){
              SetCurSel(6);
      }
      else {
    		SetCurSel(iCurIdx+1);
      }
		if (iCurIdx == pPages.GetSize() - 1) 
         SET_DIALOG_ITEM(IDOK,"COMMON.BUTTON.DONE");
		GetDlgItem(IDC_BACK)->EnableWindow(TRUE);
	}
	else{
		for (int t = 0; t < pPages.GetSize(); t++){
			CDialog * pDlg1 = GetDialog(t);
			if (pDlg1) {
				pDlg1->UpdateData();
			}
		}
		ClosePages();
		CDialog::OnOK();
	}
}

//----------------------------------------------------------------------------
void CDialogDDEParamWizard::OnBack() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (iCurIdx > 0){
       if(iCurIdx == 5){
           SetCurSel(1);
       }
       else if(iCurIdx== 4 ){
           SetCurSel(1);
       }
       else if(iCurIdx== 3){
           SetCurSel(1);
       }
       else if(iCurIdx== 2){
           SetCurSel(1);
       }
       else if(iCurIdx== 1){
           SetCurSel(0);
       }
       else if(iCurIdx== 6){
          if(m_server == DDE_STRING_SERVER_EXCEL){
              SetCurSel(2);
          }
          else if(m_server == DDE_STRING_SERVER_EASYPORT){
              SetCurSel(3);
          }
          else if(m_server == DDE_STRING_SERVER_COSIVIS){
              SetCurSel(4);
          }
          else{
              SetCurSel(5);
          }
       }
		if (iCurIdx != pPages.GetSize() - 1) 
         SET_DIALOG_ITEM(IDOK,"COMMON.BUTTON.NEXT");
	}
   if (iCurIdx <= 0) {
       GetDlgItem(IDC_BACK)->EnableWindow(FALSE);
       GetDlgItem(IDOK)->EnableWindow(TRUE);
   }
	
}
//----------------------------------------------------------------------------
void CDialogDDEParamWizard::AddPage(const char * cText, CDialog * pDlg, const UINT id){
//----------------------------------------------------------------------------
	PROC_TRACE;

	pPages.Add((void *) pDlg);
	csText.Add(CString(cText));
	csIds.Add(id);
}

//----------------------------------------------------------------------------
void CDialogDDEParamWizard::SetCurSel(const int idx){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (iCurIdx >= 0)
	{
		CDialog * pDlg1 = GetDialog(iCurIdx);
		if (pDlg1) 
		{
			if (!pDlg1->UpdateData()) return;
			pDlg1->ShowWindow(SW_HIDE);
		}
	}
	iCurIdx = idx;
	CDialog * pDlg2 = GetDialog(iCurIdx);
	if (pDlg2) 
	{
		pDlg2->ShowWindow(SW_SHOW);
		m_headerStatic.SetWindowText(csText[iCurIdx]);
	}
}

//----------------------------------------------------------------------------
void CDialogDDEParamWizard::ClosePages(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	for (int t = 0; t < pPages.GetSize(); t++)
	{
		CDialog * pDlg1 = GetDialog(iCurIdx);
		if (pDlg1) pDlg1->DestroyWindow();
	}
}

//----------------------------------------------------------------------------
CDialog * CDialogDDEParamWizard::GetDialog(const int idx){
//----------------------------------------------------------------------------
	PROC_TRACE;

	ASSERT(idx >= 0 && idx < pPages.GetSize());
	return (CDialog *) pPages.GetAt(idx);
}

//----------------------------------------------------------------------------
void CDialogDDEParamWizard::SetBitmap(UINT resId){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_bmp.DeleteObject();
   m_bmp.LoadBitmap(resId);
   m_wizardBitmap.SetBitmap((HBITMAP)m_bmp);
   Invalidate();
}

//----------------------------------------------------------------------------
void CDialogDDEParamWizard::SetServer(CString server){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_server = server;
    SetDlgItemText(IDC_SERVER_STATIC,m_server);
};

//----------------------------------------------------------------------------
void CDialogDDEParamWizard::SetTopic(CString topic){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_topic = topic;
    SetDlgItemText(IDC_TOPIC_STATIC,m_topic);
};

//----------------------------------------------------------------------------
void CDialogDDEParamWizard::SetItem(CString item){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_item = item;
    SetDlgItemText(IDC_ITEM_STATIC,m_item);
};

//----------------------------------------------------------------------------
void CDialogDDEParamWizard::SetNextState(bool state){
//----------------------------------------------------------------------------
	PROC_TRACE;

		GetDlgItem(IDOK)->EnableWindow(state);
}
