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

#include "DialogVoteForTheFuture.h"


#define MAILADDRESS   _T("A.Herz@FreeGroup.de")
#define PREFIX        _T("DigitalSimulator")
#define TIMEOUT_TIMER 12

BEGIN_MESSAGE_MAP(CDialogVoteForTheFuture, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogVoteForTheFuture)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CDialogVoteForTheFuture::CDialogVoteForTheFuture(CWnd* pParent /*=NULL*/)
	: inherited(CDialogVoteForTheFuture::IDD, pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogVoteForTheFuture)
		// HINWEIS: Der Klassen-Assistent fügt hier ElementInitialisierung ein
	//}}AFX_DATA_INIT
}


//----------------------------------------------------------------------------
void CDialogVoteForTheFuture::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------

	inherited::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CDialogVoteForTheFuture)
	DDX_Control(pDX, IDC_IMAGE_STATIC, m_image);
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDC_VOTE_7, m_vote7);
	DDX_Control(pDX, IDC_VOTE_6, m_vote6);
	DDX_Control(pDX, IDC_VOTE_4, m_vote4);
	DDX_Control(pDX, IDC_VOTE_3, m_vote3);
	DDX_Control(pDX, IDC_VOTE_1, m_vote1);
	//}}AFX_DATA_MAP
}




//----------------------------------------------------------------------------
BOOL CDialogVoteForTheFuture::OnInitDialog() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
   TRANSLATE_DIALOG_ITEM(IDC_FUTURE);
   TRANSLATE_DIALOG_ITEM(IDC_VOTE_1);
   TRANSLATE_DIALOG_ITEM(IDC_VOTE_2);
   TRANSLATE_DIALOG_ITEM(IDC_VOTE_3);
   TRANSLATE_DIALOG_ITEM(IDC_VOTE_4);
   TRANSLATE_DIALOG_ITEM(IDC_VOTE_5);
   TRANSLATE_DIALOG_ITEM(IDC_VOTE_6);
   TRANSLATE_DIALOG_ITEM(IDC_VOTE_7);
   TRANSLATE_DIALOG_ITEM(IDOK);
 
   m_okButton.SetShaded();
   
   m_vote1.SetReceiver(MAILADDRESS);
   m_vote1.SetSubjectPrefix(PREFIX);
	m_vote1.SetUnderline(FALSE);

//	m_vote2.SetReceiver(MAILADDRESS);
// m_vote2.SetSubjectPrefix(PREFIX);
//	m_vote2.SetUnderline(FALSE);
	
	m_vote3.SetReceiver(MAILADDRESS);
   m_vote3.SetSubjectPrefix(PREFIX);
	m_vote3.SetUnderline(FALSE);
	
	m_vote4.SetReceiver(MAILADDRESS);
   m_vote4.SetSubjectPrefix(PREFIX);
	m_vote4.SetUnderline(FALSE);
	
//	m_vote5.SetReceiver(MAILADDRESS);
// m_vote5.SetSubjectPrefix(PREFIX);
//	m_vote5.SetUnderline(FALSE);
	
	m_vote6.SetReceiver(MAILADDRESS);
   m_vote6.SetSubjectPrefix(PREFIX);
	m_vote6.SetUnderline(FALSE);
	
	m_vote7.SetReceiver(MAILADDRESS);
   m_vote7.SetSubjectPrefix(PREFIX);
	m_vote7.SetUnderline(FALSE);
	
   SetTimer(TIMEOUT_TIMER,15000,NULL); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

//----------------------------------------------------------------------------
void CDialogVoteForTheFuture::OnTimer(UINT nIDEvent) {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(nIDEvent ==TIMEOUT_TIMER){
      KillTimer(TIMEOUT_TIMER);
      SendMessage(WM_CLOSE);
   }
	inherited::OnTimer(nIDEvent);
}
