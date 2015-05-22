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

#if !defined(AFX_DIALOGPLUGINOBJECTOPTIONS_H__73F45317_5197_11D4_B5B8_C3F4DAE247BA__INCLUDED_)
#define AFX_DIALOGPLUGINOBJECTOPTIONS_H__73F45317_5197_11D4_B5B8_C3F4DAE247BA__INCLUDED_

#include "Application\Controls\URLStatic\URLStatic.h"
#include "Application\Controls\MailStatic\MailLink.h"
#include "Application\Dialogs\generic\SnapDialog.h"
#include "Application\Controls\ShadeButton\ShadeButton.h"
#include "Application\Controls\ImageStatic\TransparentImageStatic.h"
#include "Application\Controls\NumSpin\NumSpinCtrl.h"
#include "Application\Controls\NumSpin\NumEdit.h"

class CDialogPluginObjectOptions : public CSnapDialog
{
   typedef CSnapDialog inherited;

public:
	CDialogPluginObjectOptions(CWnd* pParent,
                    CElectricNode::CElectricNodeDokument& data);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDialogPluginObjectOptions)
	enum { IDD = IDD_PLUGIN_OBJECT_OPTIONS };
	CTransparentImageStatic	m_image;
	CxShadeButton	m_okButton;
	CxShadeButton	m_cancelButton;
	CTransparentImageStatic   	m_imageStatic;
	CNumSpinCtrl	   m_outputSpin;
	CNumSpinCtrl	   m_inputSpin;
	CNumEdit	         m_outputEdit;
	CNumEdit	         m_inputEdit;
	CStatic	         m_version;
	CHyperLink	      m_url;
	CMailLink	      m_email;
	CStatic	         m_developer;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDialogPluginObjectOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
   CElectricNode::CElectricNodeDokument& m_data;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogPluginObjectOptions)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOGPLUGINOBJECTOPTIONS_H__73F45317_5197_11D4_B5B8_C3F4DAE247BA__INCLUDED_
