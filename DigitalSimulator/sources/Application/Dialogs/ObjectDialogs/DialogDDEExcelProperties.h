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

#ifndef AFX_DIALOGDDEEXCELPROPERTIES_H__68E79D71_AF9E_11D2_9A09_0080C7304F8F__INCLUDED_
#define AFX_DIALOGDDEEXCELPROPERTIES_H__68E79D71_AF9E_11D2_9A09_0080C7304F8F__INCLUDED_
#pragma warning(disable : 4786)

#include "Application\Dialogs\generic\SnapDialog.h"
#include "Application\Controls\ShadeButton\ShadeButton.h"
#include "Application\Controls\ImageStatic\TransparentImageStatic.h"
class CDialogDDEParamWizard;

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogDDEExcelProperties 

class CDialogDDEExcelProperties : public CDialog{
   typedef CDialog inherited;

// Konstruktion
public:
	CDialogDDEExcelProperties(CDialogDDEParamWizard* pParent);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDialogDDEExcelProperties)
	enum { IDD = IDD_DDE_EXCEL_PROPERTIES };
	CString	m_column;
	CString	m_fileName;
	CString	m_folder;
	CString	m_row;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDialogDDEExcelProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

   virtual char * const GetClassName(){return "CDialogDDEExcelProperties";};
// Implementierung
protected:
	void CheckNextButton();
	void SetDDEValues();
	CDialogDDEParamWizard* m_parent;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogDDEExcelProperties)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnFileSelectButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeColumnEdit();
	afx_msg void OnChangeRowEdit();
	afx_msg void OnChangeFileNameEdit();
	afx_msg void OnChangeFolderPageEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGDDEEXCELPROPERTIES_H__68E79D71_AF9E_11D2_9A09_0080C7304F8F__INCLUDED_
