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

#ifndef AFX_DIALOGDDEPARAM_H__E59740B1_B6A0_11D2_9A17_0080C7304F8F__INCLUDED_
#define AFX_DIALOGDDEPARAM_H__E59740B1_B6A0_11D2_9A17_0080C7304F8F__INCLUDED_
#pragma warning(disable : 4786)

#include "Application\Dialogs\generic\SnapDialog.h"
#include "Application\Controls\ShadeButton\ShadeButton.h"
#include "Application\Controls\ImageStatic\TransparentImageStatic.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogDDEParam 

class CDialogDDEParam : public CSnapDialog{
   typedef CSnapDialog inherited;

// Konstruktion
public:
	CDialogDDEParam(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDialogDDEParam)
	enum { IDD = IDD_DDE_PARAM };
	CxShadeButton	m_cancelButton;
	CxShadeButton	m_okButton;
	CString	m_item;
	CString	m_server;
	CString	m_topic;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDialogDDEParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
   virtual char * const GetClassName(){return "CDialogDDEParam";};
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogDDEParam)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGDDEPARAM_H__E59740B1_B6A0_11D2_9A17_0080C7304F8F__INCLUDED_