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
#include "../stdafx.h"
#include "DialogOption.h"
#include "../SerialPort.h"


BEGIN_MESSAGE_MAP(CDialogOption, CDialog)
	//{{AFX_MSG_MAP(CDialogOption)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CDialogOption::CDialogOption(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogOption::IDD, pParent){
//----------------------------------------------------------------------------
	//{{AFX_DATA_INIT(CDialogOption)
	//}}AFX_DATA_INIT
}


//----------------------------------------------------------------------------
void CDialogOption::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
   CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogOption)
	DDX_Control(pDX, IDC_PORT_COMBO, m_portCombo);
	DDX_Control(pDX, IDC_NO_PORT_AVAILABLE, m_noPortStatic);
	DDX_CBIndex(pDX, IDC_PORT_COMBO, m_portNr);
	//}}AFX_DATA_MAP
}


//----------------------------------------------------------------------------
BOOL CDialogOption::OnInitDialog() {
//----------------------------------------------------------------------------
	CDialog::OnInitDialog();

   // Entrypoint to changee the language
   // ...make a class for language translation (see DigitalSimulator/ResourceTranslator
   //
   SetWindowText("Fischertechnik interface options");
   GetDlgItem(IDC_COM_PORT)->SetWindowText("COM:");	
   GetDlgItem(IDC_NO_PORT_AVAILABLE)->SetWindowText("- no free seriel port available -");	
   GetDlgItem(IDOK)->SetWindowText("Ok");	
   GetDlgItem(IDCANCEL)->SetWindowText("Cancel");	

   m_interfaceBitmap.SubclassDlgItem(IDC_INTERFACE_BITMAP,this);
   m_interfaceBitmap.ReloadBitmap(IDB_INTERFACE);

   int         ownPort = m_portNr;
   CSerialPort port;
   CString     portID;
   int         selection = 0;
   for(int i=1;i<5;i++){
      if(port.Init(i)){
         // Falls der eigene Port in der Liste vorkommt brauch ich diesen
         // spaeter nicht noch einmal eintragen
         //
         if(ownPort==i){
            ownPort=-1;
            selection = i-1;
         }

         // gueltigen Port eintragen
         //
         portID.Format("%d",i);
         m_portCombo.AddString(portID);
      }
   }

   // eigenen Port als eine gueltige Auswahl eintragen
   //
   if(ownPort != -1){
      portID.Format("%d",ownPort);
      m_portCombo.AddString(portID);
   }


   if(m_portCombo.GetCount()){
      m_portCombo.SetCurSel(selection);
      m_noPortStatic.ShowWindow(FALSE);
   }
   else{
      m_portCombo.EnableWindow(FALSE);
      m_noPortStatic.ShowWindow(TRUE);
   }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


//----------------------------------------------------------------------------
void CDialogOption::OnOK() {
//----------------------------------------------------------------------------
	CDialog::OnOK();

   int i = m_portCombo.GetCurSel();

   if(i>=0){
      CString selText;
      m_portCombo.GetLBText( i,selText );
      m_portNr = atoi((LPCSTR)selText);
   }
}
