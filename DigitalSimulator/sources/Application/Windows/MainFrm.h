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

#if !defined(AFX_MAINFRM_H__94F3F5EB_6114_11D2_890F_004F49031E0C__INCLUDED_)
#define AFX_MAINFRM_H__94F3F5EB_6114_11D2_890F_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)


#include "stdafx.h"
// libraries
#include "DragDropMDIFrame.h"

// application
#include "Application\Windows\Palette\DockingPaletteDoc.h"
#include "Application\Windows\Palette\ObjectDockingControlBar.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Windows\Oszi\OsziDockingControlBar.h"
#include "Application\Windows\MainToolBar.h"

class CMainFrame : public DragDropMDIFrameWnd{
   typedef DragDropMDIFrameWnd inherited;
public:
	CMainFrame();
	virtual ~CMainFrame();

 //  HAS_FREE_MESSAGE;

   virtual void GetMessageString(UINT nID, CString & rMessage) const;
   CObjectDockingControlBar* GetObjectBar(){return &m_wndObjectBar;};
   COsziDockingControlBar*   OsziBar(){return &m_wndOsziBar;};
   virtual char * const GetClassName(){return "CMainFrame";};

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	protected:
	//}}AFX_VIRTUAL


protected:  // Eingebundene Elemente der Steuerleiste
	void FullScreenModeOn();
	void FullScreenModeOff();
    void AttachToolbarImages (UINT inNormalImageID, UINT inDisabledImageID,  UINT inHotImageID);
	BOOL PreCreateWindow(CREATESTRUCT& cs);

   CMainToolBar             m_wndToolBar;

   CObjectDockingControlBar m_wndObjectBar;
   COsziDockingControlBar   m_wndOsziBar;

   // main toolbar
   CImageList m_ToolbarImagesDisabled;
	CImageList m_ToolbarImagesHot;
	CImageList m_ToolbarImages;


   // used for full-screen mode
	bool  m_bOsziBarWasVisible;
	bool  m_bObjectBarWasVisible;
   bool  m_bToolBarWasVisible;
	CRect	m_mainRect;
	bool  m_bChildMax;
	bool  m_bFullScreenMode;
   CMenu m_origMenu;

   // window snap offset
	int m_nYOffset;
	int m_nXOffset;


// Generierte Message-Map-Funktionen
protected:

 
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewObjectBar();
	afx_msg void OnUpdateViewObjectBar(CCmdUI* pCmdUI);
	afx_msg void OnViewToolBar();
	afx_msg void OnUpdateViewToolBar(CCmdUI* pCmdUI);
	afx_msg void OnViewOsziBar();
	afx_msg void OnUpdateViewOsziBar(CCmdUI* pCmdUI);
	afx_msg void OnOptionsOsziloskope();
	afx_msg void OnDestroy();
	afx_msg void OnFullScreen();
	afx_msg void OnUpdateFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnOptionsToolbar();
	afx_msg void OnUpdateOptionsToolbar(CCmdUI* pCmdUI);
   afx_msg void OnTools(UINT id );
	afx_msg void OnUpdateTools(CCmdUI* pCmdUI);
   afx_msg void OnDialogs(UINT id );
	afx_msg void OnUpdateDialogs(CCmdUI* pCmdUI);
	//}}AFX_MSG
public:
   class LanguageNotifyee : public ValueChangeNotifyee{
   public: 
      LanguageNotifyee(){
         m_valueNameForNotifyee = "Language";
         m_listener = NULL;
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL){
            m_listener->TranslateGUI();
         }
      }
      void setListener(CMainFrame*l){
         m_listener=l;
      }
   protected:
   CMainFrame* m_listener;
   } m_languageNotifyee;

   void TranslateGUI();

   DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CMainFrame)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_MAINFRM_H__94F3F5EB_6114_11D2_890F_004F49031E0C__INCLUDED_)
