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

#if !defined(AFX_OBJECTDOCKINGCONTROLBAR_H__E022ED91_9F1B_11D2_8950_004F49031E0C__INCLUDED_)
#define AFX_OBJECTDOCKINGCONTROLBAR_H__E022ED91_9F1B_11D2_8950_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "Application\Controls\ResizeTabControlBar\SizingTabCtrlBar.h"
#include "Application\Configuration\ParameterManager.h"
#include "ObjectDockingControlBarView.h"

class CObjectDockingControlBar : public CSizingTabCtrlBar  {
   typedef CSizingTabCtrlBar inherited;

public:
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CObjectDockingControlBar)
	//}}AFX_VIRTUAL

    CObjectDockingControlBar();
	virtual ~CObjectDockingControlBar();
   
   virtual void AddAllPaletteFiles();
   virtual BOOL AddPaletteFile(CString fileName);
   virtual CObjectDockingControlBarView* GetViewByPath(CString filename);

   virtual char * const GetClassName(){return "CObjectDockingControlBar";};
   virtual void UpdateLabels();
protected:
	//{{AFX_MSG(CObjectDockingControlBar)
	//}}AFX_MSG
   class LanguageNotifyee : public ValueChangeNotifyee{
   public: 
      LanguageNotifyee(){
         m_valueNameForNotifyee = "Language";
         m_listener = NULL;
      };
      virtual void AfterChange(const CString& value){
         if(m_listener != NULL)
            m_listener->UpdateLabels();
      }

      void setListener(CObjectDockingControlBar*l){
         m_listener=l;
      }
   protected:
	   CObjectDockingControlBar* m_listener;
   } m_languageNotifyee;

   //
   //
   class DocumentReloadNotifyee : public ValueChangeNotifyee{
   public: 
      DocumentReloadNotifyee(){
         m_listener=NULL;
         m_valueNameForNotifyee = "PaletteDocumentReload";
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
		 {
           m_listener->AddPaletteFile(value);
		 }
      }

      void setListener(CObjectDockingControlBar*l){
         m_listener=l;
      }
   protected:
   CObjectDockingControlBar* m_listener;
   } m_documentReloadNotifyee;

   //
   //
   class PaletteAutolayoutNotifyee : public ValueChangeNotifyee{
   public: 
      PaletteAutolayoutNotifyee(){
         m_listener=NULL;
         m_valueNameForNotifyee = "PaletteAutolayout";
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
		 {
           m_listener->AddAllPaletteFiles();
		 }
      }

      void setListener(CObjectDockingControlBar*l){
         m_listener=l;
      }
   protected:
   CObjectDockingControlBar* m_listener;
   } m_paletteAutolayoutNotifyee;

   
	//{{AFX_MSG(CObjectDockingControlBarView)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_OBJECTDOCKINGCONTROLBAR_H__E022ED91_9F1B_11D2_8950_004F49031E0C__INCLUDED_)
