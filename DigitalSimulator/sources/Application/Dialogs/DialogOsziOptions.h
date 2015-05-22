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

#if !defined(AFX_DIALOGOSZIOPTIONS_H__73F45313_5197_11D4_B5B8_C3F4DAE247BA__INCLUDED_)
#define AFX_DIALOGOSZIOPTIONS_H__73F45313_5197_11D4_B5B8_C3F4DAE247BA__INCLUDED_

#include "Application\Dialogs\generic\SnapDialog.h"
#include "Application\Controls\ShadeButton\ShadeButton.h"
#include "Application\Controls\ImageStatic\TransparentImageStatic.h"
#include "Application\Controls\NumSpin\NumSpinCtrl.h"
#include "Application\Controls\NumSpin\NumEdit.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogOsziOptions 

class CDialogOsziOptions : public CSnapDialog
{
   typedef CSnapDialog inherited;
public:
	CDialogOsziOptions(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDialogOsziOptions)
	enum { IDD = IDD_OSZI_OPTIONS };
	CxShadeButton	m_fgColorButton;
	CxShadeButton	m_bgColorButton;
	CxShadeButton	m_useitButton;
	CxShadeButton	m_okButton;
	CxShadeButton	m_cancelButton;
	CNumSpinCtrl	m_zoomSpin;
	CNumEdit   	   m_zoomEdit;
	CButton     	m_gridCheck;
	CNumEdit	      m_xEdit;
	CNumEdit	      m_yEdit;
	CNumSpinCtrl	m_ySpin;
	CNumSpinCtrl	m_xSpin;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDialogOsziOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
   COLORREF m_fgColor;
   COLORREF m_bgColor;
   CRect    m_fgRect;
   CRect    m_bgRect;
   void     DrawFilledColor(CDC *pDC,CRect cr,COLORREF c);

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogOsziOptions)
	afx_msg void OnBgColor();
	afx_msg void OnFgColor();
	afx_msg void OnUseIt();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOGOSZIOPTIONS_H__73F45313_5197_11D4_B5B8_C3F4DAE247BA__INCLUDED_
