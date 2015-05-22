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

#if !defined(AFX_DIGITALTRAINEESTUDIO_H__94F3F5E6_6114_11D2_890F_004F49031E0C__INCLUDED_)
#define AFX_DIGITALTRAINEESTUDIO_H__94F3F5E6_6114_11D2_890F_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

#include "Application\i18n\TranslateDocManager.h"
#include "Application\Debug\LogManager.h"
#include "DragDropClientApp.h"

class StringTranslater;
class ParameterManager;
class CMainFrame;


class DigitalSimulatorApp : public CDragDropApp
{
public:
	DigitalSimulatorApp();
   CMainFrame* MainFrame() { return (CMainFrame*) m_pMainWnd; }

   virtual int ExitInstance();

   static HANDLE GetMainThread(){return m_mainThread;};
   virtual BOOL InitApplication();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(DigitalSimulatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


	//{{AFX_MSG(DigitalSimulatorApp)
	afx_msg void OnAppAbout();
    afx_msg void OnHelp( );
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
   virtual char * const GetClassName(){return "DigitalSimulatorApp";};
protected:
      void RegisterAllPlugins();
	   BOOL RegisterPlugin(CString fileName);

      CTranslateDocManager  *m_transDocManager;
      static HANDLE m_mainThread;
	
   DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_DIGITALTRAINEESTUDIO_H__94F3F5E6_6114_11D2_890F_004F49031E0C__INCLUDED_)
