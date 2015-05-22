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
#include "DialogDDEOUTCosivisProperties.h"

#define DDEOUT_TOPIC_COSIVIS        "IOPanel"
#define DDEOUT_ITEM_COSIVIS_AKTOR   "MAB.1.0.0"
#define DDEOUT_ITEM_COSIVIS_PANEL   "MAB.1.0.1"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogDDEOUTCosivisProperties 


CDialogDDEOUTCosivisProperties::CDialogDDEOUTCosivisProperties(CDialogDDEParamWizard* pParent /*=NULL*/)
	: CDialog(CDialogDDEOUTCosivisProperties::IDD,(CWnd*) pParent)
{
	//{{AFX_DATA_INIT(CDialogDDEOUTCosivisProperties)
		// HINWEIS: Der Klassen-Assistent fügt hier ElementInitialisierung ein
	//}}AFX_DATA_INIT
    m_parent =pParent;
}


void CDialogDDEOUTCosivisProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDDEOUTCosivisProperties)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogDDEOUTCosivisProperties, CDialog)
	//{{AFX_MSG_MAP(CDialogDDEOUTCosivisProperties)
	ON_BN_CLICKED(IDC_AKTOREN_RADIO, OnAktorenRadio)
	ON_BN_CLICKED(IDC_PANEL_RADIO, OnPanelRadio)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDialogDDEOUTCosivisProperties 
void CDialogDDEOUTCosivisProperties::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
   TRANSLATE_DIALOG_ITEM(IDC_AKTOREN_RADIO);
   TRANSLATE_DIALOG_ITEM(IDC_PANEL_RADIO);

	if(bShow==TRUE) {
       m_parent->SetBitmap(IDB_DDEOUT_PROPERTIES_COSIVIS);
      if(m_parent->GetItem()==DDEOUT_ITEM_COSIVIS_AKTOR){
          CheckDlgButton(IDC_AKTOREN_RADIO,1);
          OnAktorenRadio();
      }
      else {
          CheckDlgButton(IDC_PANEL_RADIO, 1);
          OnPanelRadio();
      }
    	CheckNextButton();
   }
	
}

void CDialogDDEOUTCosivisProperties::OnAktorenRadio() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
   m_parent->SetTopic(DDEOUT_TOPIC_COSIVIS);	
   m_parent->SetItem(DDEOUT_ITEM_COSIVIS_AKTOR);	
	
}

void CDialogDDEOUTCosivisProperties::OnPanelRadio() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
   m_parent->SetTopic(DDEOUT_TOPIC_COSIVIS);	
   m_parent->SetItem(DDEOUT_ITEM_COSIVIS_PANEL);	
	
}


void CDialogDDEOUTCosivisProperties::CheckNextButton()
{

}
