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

#ifndef AFX_DIALOGDDEOUTPUTPARAM_H__44039264_A662_11D2_99FE_0080C7304F8F__INCLUDED_
#define AFX_DIALOGDDEOUTPUTPARAM_H__44039264_A662_11D2_99FE_0080C7304F8F__INCLUDED_
#pragma warning(disable : 4786)

#include "Application\Dialogs\generic\SnapDialog.h"
#include "Application\Controls\ShadeButton\ShadeButton.h"
#include "Application\Controls\ImageStatic\TransparentImageStatic.h"

#define DDE_STRING_SERVER_COSIVIS   TRANSLATE("DDE-Server Cosivis")
#define DDE_STRING_SERVER_EXCEL     TRANSLATE("DDE-Server Excel")
#define DDE_STRING_SERVER_EASYPORT  TRANSLATE("DDE-Server EasyPort")


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogDDEParamWizard 

class CDialogDDEParamWizard : public CSnapDialog{
   typedef CSnapDialog inherited;

// Konstruktion
public:
	void SetNextState(bool state);
	virtual void SetBitmap(UINT resId);
   virtual void SetServer(CString server);
   virtual CString GetServer(void){return m_server;};
   virtual void SetTopic(CString topic);
   virtual CString GetTopic(void){return m_topic;};
   virtual void SetItem(CString item);
   virtual CString GetItem(void){return m_item;};

	CDialogDDEParamWizard(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDialogDDEParamWizard();  
	CDialog * GetDialog(const int idx);
	void ClosePages();
	virtual void SetCurSel(const int idx);
	void AddPage(const char * cText, CDialog * pDlg, const UINT id);

   CPtrArray    pPages;
	CStringArray csText;
	CUIntArray   csIds;
	int   	    iCurIdx;
	CString      csTitle;
	CString      m_server;
	CString      m_topic;
	CString      m_item;
   CBitmap      m_bmp;

// Dialogfelddaten
	//{{AFX_DATA(CDialogDDEParamWizard)
	enum { IDD = IDD_DDE_PARAM_WIZARD };
	CxShadeButton	m_okButton;
	CxShadeButton	m_cancelButton;
	CxShadeButton	m_backButton;
	CStatic	m_headerStatic;
	CStatic	m_itemStatic;
	CStatic	m_topicStatic;
	CStatic	m_serverStatic;
	CTransparentImageStatic	m_wizardBitmap;
	CStatic	m_wndFrame;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDialogDDEParamWizard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
   virtual char * const GetClassName(){return "CDialogDDEParamWizard";};
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogDDEParamWizard)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnBack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGDDEOUTPUTPARAM_H__44039264_A662_11D2_99FE_0080C7304F8F__INCLUDED_
