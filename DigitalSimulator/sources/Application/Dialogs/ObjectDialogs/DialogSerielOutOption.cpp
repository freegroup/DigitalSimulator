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
#include "Application\Objects\plugin\DLL\SerialPort\SerialPluginManager.h"

#include "DialogSerielOutOption.h"

BEGIN_MESSAGE_MAP(CDialogSerielOutOption, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogSerielOutOption)
	ON_CBN_SELCHANGE(IDC_CARD_COMBO, OnSelchangeCardCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CDialogSerielOutOption::CDialogSerielOutOption(CWnd* pParent /*=NULL*/)	
   : inherited(CDialogSerielOutOption::IDD, pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogSerielOutOption)
	m_pluginKey = _T("");
	//}}AFX_DATA_INIT
}


//----------------------------------------------------------------------------
void CDialogSerielOutOption::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSerielOutOption)
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_PRODUCER_URL_STATIC, m_producerURL);
	DDX_Control(pDX, IDC_PROGRAMMER_URL_STATIC, m_programmerURL);
   DDX_Control(pDX, IDC_CARD_COMBO, m_cardCombo);
	DDX_CBString(pDX, IDC_CARD_COMBO, m_pluginKey);
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
BOOL CDialogSerielOutOption::OnInitDialog(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
   SetWindowText(TRANSLATE("Wähle ein PlugIn für das Schreiben auf die serielle Schnittstelle"));
   TRANSLATE_DIALOG_ITEM(IDC_CARD_IDENTIFIER);	
   TRANSLATE_DIALOG_ITEM(IDC_DEVICENAME);	
   TRANSLATE_DIALOG_ITEM(IDC_PRODUCER);	
   TRANSLATE_DIALOG_ITEM(IDC_PRODUCER_URL);	
   TRANSLATE_DIALOG_ITEM(IDC_PLUGINVERSION);	
   TRANSLATE_DIALOG_ITEM(IDC_PROGRAMMER);	
   TRANSLATE_DIALOG_ITEM(IDC_PROGRAMMER_URL);	
   TRANSLATE_DIALOG_ITEM(IDOK);	
   TRANSLATE_DIALOG_ITEM(IDCANCEL);	

   m_okButton.SetShaded();
   m_cancelButton.SetShaded();

   StringArray CStrings;
   CStrings = SerialPluginManager::getOutPlugins();
	
   int selectIndex =0;
   for (int i=0 ;i<CStrings.size();i++){
      m_cardCombo.AddString(CStrings[i]);
      if(CStrings[i]==m_pluginKey)
         selectIndex = i;
   }

   if(m_cardCombo.GetCount() >0)
      m_cardCombo.SetCurSel(selectIndex);
   else
      m_cardCombo.EnableWindow(FALSE);

   OnSelchangeCardCombo();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

//----------------------------------------------------------------------------
void CDialogSerielOutOption::OnSelchangeCardCombo() {
//----------------------------------------------------------------------------
	PROC_TRACE;


	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
   int i = m_cardCombo.GetCurSel();

   if(i>=0){
      CString selText;
      m_cardCombo.GetLBText( i,selText );
      // Interfaces fuer die Verschieden Karten holen und deren Beschreibungen
      // in die Dialogelemente eintragen
      //
      IPluginInfo *in=(IPluginInfo*) SerialPluginManager::createInstance(selText,"IPluginInfo");
      if(in != NULL){
         char buffer[200];
         in->getDeviceName(buffer, sizeof(buffer)-1);
         GetDlgItem(IDC_DEVICENAME_STATIC)->SetWindowText(buffer);

         in->getProducerName(buffer, sizeof(buffer)-1);
         GetDlgItem(IDC_PRODUCERNAME_STATIC)->SetWindowText(buffer);

         in->getProducerURL(buffer, sizeof(buffer)-1);
         GetDlgItem(IDC_PRODUCER_URL_STATIC)->SetWindowText(buffer);
      	m_producerURL.SetURL(buffer);
	      m_producerURL.SetUnderline(FALSE);

         in->getVersion(buffer, sizeof(buffer)-1);
         GetDlgItem(IDC_VERSION_STATIC)->SetWindowText(buffer);

         in->getProgrammerName(buffer, sizeof(buffer)-1);
         GetDlgItem(IDC_PROGRAMMERNAME_STATIC)->SetWindowText(buffer);

         in->getProgrammerURL(buffer, sizeof(buffer)-1);
         GetDlgItem(IDC_PROGRAMMER_URL_STATIC)->SetWindowText(buffer);
      	m_programmerURL.SetURL(buffer);
	      m_programmerURL.SetUnderline(FALSE);

         Invalidate(TRUE);
         in->Destroy();
      }
   }
   else{
   }
	
}
