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


#ifndef AFX_OBJECTPROPERTYDIALOG_H__0EC72EA1_67F5_11D2_8917_004F49031E0C__INCLUDED_
#define AFX_OBJECTPROPERTYDIALOG_H__0EC72EA1_67F5_11D2_8917_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "Application\Objects\buildin\digital\ElectricNodeContext.h"
#include "Application\Dialogs\generic\SnapDialog.h"
#include "Application\Controls\ShadeButton\ShadeButton.h"
#include "GroupTreeControl.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogSecondaryObjectOptions 

class CDialogSecondaryObjectOptions : public CSnapDialog{
   typedef CSnapDialog inherited;

// Konstruktion
public:
	CDialogSecondaryObjectOptions(CWnd* pParent,
                         CElectricNode::CElectricNodeDokument& data);   // Standardkonstruktor


// Dialogfelddaten
	//{{AFX_DATA(CDialogSecondaryObjectOptions)
	enum { IDD = IDD_SECONDARY_OBJECT_PROPERTY };
	CxShadeButton	m_okButton;
	CxShadeButton	m_cancelButton;
	CGroupTreeControl	m_objectTree;
	CEdit	m_descriptionEdit;
	//}}AFX_DATA
   CString       m_metaNameString; 
	int	m_inputCount;
	int 	m_outputCount;
// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDialogSecondaryObjectOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
   virtual char * const GetClassName(){return "CDialogSecondaryObjectOptions";};
protected:
	void UpdateGUI(CString meta);
   CElectricNode::CElectricNodeDokument& m_data;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogSecondaryObjectOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickObjectTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVscrollDescriptionEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_OBJECTPROPERTYDIALOG_H__0EC72EA1_67F5_11D2_8917_004F49031E0C__INCLUDED_
