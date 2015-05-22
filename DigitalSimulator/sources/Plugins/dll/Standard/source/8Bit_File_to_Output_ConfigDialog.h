#if !defined(AFX_CONFIGDIALOG_H__1BD101C2_420D_11D5_B612_002018BA6D85__INCLUDED_)
#define AFX_CONFIGDIALOG_H__1BD101C2_420D_11D5_B612_002018BA6D85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDialog.h : Header-Datei
//
#include "resource.h"
#include "SnapDialog.h"
#include "xShadeButton.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CConfigDialog 

class CConfigDialog : public CSnapDialog
{
   typedef CSnapDialog inherited;
// Konstruktion
public:
	CConfigDialog(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CConfigDialog)
	enum { IDD = IDD_CONFIG_DIALOG };
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CConfigDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CConfigDialog)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_CONFIGDIALOG_H__1BD101C2_420D_11D5_B612_002018BA6D85__INCLUDED_
