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

#if !defined(AFX_FINDFILEDLG_H__7D455BC3_51E2_11D4_91F8_0080C8DA7A5E__INCLUDED_)
#define AFX_FINDFILEDLG_H__7D455BC3_51E2_11D4_91F8_0080C8DA7A5E__INCLUDED_


#define WM_BEGIN_SEARCH (WM_APP + 200)

#include "Application\Dialogs\generic\SnapDialog.h"
#include "Application\Controls\ShadeButton\ShadeButton.h"
#include "Application\Controls\ImageStatic\TransparentImageStatic.h"
#include "Application\Controls\SnakeStatic\SnakeStatic.h"

class CFindFileDlg : public CSnapDialog
{
   typedef CSnapDialog inherited;

// Construction
public:
	CFindFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindFileDlg)
	enum { IDD = IDD_FIND_FILE };
	CEZSnakeCtrl	m_processStatic;
	CxShadeButton	m_stopButton;
	//}}AFX_DATA

	
	// setup
	CString	m_csFindFile;				// filename, no path (bob.txt, not c:\temp\bob.txt)
	CString	m_csRootFolder;				// start here. if blank, search all local hard drives, starting with "C:"

	bool	m_bSearchNetworkDrives;		// this ignores network drives by default (m_csRootFolder will override)
	bool	m_bSearchRemovableDrives;	// this ignores non-fixed drives by default (m_csRootFolder will override)
	bool	m_bSearchCDROMDrives;		// this ignores CD-ROM drives by default (m_csRootFolder will override)

	bool	m_bFindSingleFile;			// false = find all files (default), true = stop after first
	bool	m_bRecurse;					// true = recurse subfolders (default), false = don't recurse
	
	CString	m_csTitle;					// dialog title

	// output
	CStringArray	m_csaFoundFiles;	// full paths to files found matching m_csFindFile

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
	void	MsgPump(DWORD dw = 80);

	// Generated message map functions
	//{{AFX_MSG(CFindFileDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnStop();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg long OnBegin(UINT u, LONG l);
	DECLARE_MESSAGE_MAP()

	bool m_bInThread;
	bool m_bCancel;
	int	m_iCurIcon;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDFILEDLG_H__7D455BC3_51E2_11D4_91F8_0080C8DA7A5E__INCLUDED_)
