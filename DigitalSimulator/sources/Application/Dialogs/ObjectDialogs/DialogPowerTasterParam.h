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

#ifndef AFX_DIALOGPOWERTASTERPARAM_H__0BC89E92_0ECB_11D3_B6CF_000629C18114__INCLUDED_
#define AFX_DIALOGPOWERTASTERPARAM_H__0BC89E92_0ECB_11D3_B6CF_000629C18114__INCLUDED_
#pragma warning(disable : 4786)


#include "Application\Dialogs\generic\SnapDialog.h"
#include "Application\Controls\ShadeButton\ShadeButton.h"
#include "Application\Controls\ImageStatic\TransparentImageStatic.h"

class CDialog;
class CElectricNode;
class CElectricNode::CElectricNodeDokument;


class CDialogPowerTasterParam : public CSnapDialog{
   typedef CSnapDialog inherited;

// Konstruktion
public:
	CDialogPowerTasterParam(CWnd* pParent,
                    CElectricNode::CElectricNodeDokument& data);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDialogPowerTasterParam)
	enum { IDD = IDD_POWERTASTER_PARAM };
	CTransparentImageStatic	m_image2;
	CTransparentImageStatic	m_image1;
	CxShadeButton	m_okButton;
	CxShadeButton	m_cancelButton;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDialogPowerTasterParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
   virtual char * const GetClassName(){return "CDialogPowerTasterParam";};
protected:
   CElectricNode::CElectricNodeDokument& m_data;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogPowerTasterParam)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGPOWERTASTERPARAM_H__0BC89E92_0ECB_11D3_B6CF_000629C18114__INCLUDED_
