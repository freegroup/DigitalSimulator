#if !defined(AFX_STDAFX_H__94F3F5E9_6114_11D2_890F_004F49031E0C__INCLUDED_)
#define AFX_STDAFX_H__94F3F5E9_6114_11D2_890F_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden

#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#include <afxole.h>         // MFC OLE-Klassen
#include <afxodlgs.h>       // MFC OLE-Dialogfeldklassen
#include <afxdisp.h>        // MFC OLE-Automatisierungsklassen
#include <afxpriv.h>
#include <afxole.h>
#include <afxtempl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterstützung für gängige Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC-Socket-Erweiterungen

#define chSTR(x)  #x
#define chSTR2(x) chSTR(x)
#define TODO(desc) message( __FILE__"(" chSTR2(__LINE__) "): TODO => " #desc)

         
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_STDAFX_H__94F3F5E9_6114_11D2_890F_004F49031E0C__INCLUDED_)
