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

#ifndef AFX_OSZIVIEW_H__758F5D63_C767_11D2_8970_004F49031E0C__INCLUDED_
#define AFX_OSZIVIEW_H__758F5D63_C767_11D2_8970_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "DragDropGridView.h"

#include "OsziStroke.h"
#include "utils\SortableObArray.h"
#include "Application\Configuration\ParameterManager.h"


class CDigitalTraineeStudioView;

class COsziView : public DragDropGridView{
   typedef DragDropGridView inherited;
public:
	virtual void SetLinkedView(CDigitalTraineeStudioView*);
   virtual void Add(COsziStroke * stroke);
   virtual void OnInitialUpdate();
   virtual void SortStrokes();
   virtual BOOL DropObject(DragDropView* pSourceView, DragDropObject* pSourceObject, CPoint pPoint, UINT nFlags)   {
      return FALSE;
   };
   virtual void RemoveObject(DragDropObject* pObject);
   virtual void setGrid(const CString& Style);

   virtual void SetGridWidth(int  width);
   virtual void SetGridHeight(int height);

   virtual void SetDirection(const CString& direction); // LEFT or RIGHT
   virtual void Print();

   virtual char * const GetClassName(){return "COsziView";};
protected:
   //////////////////////////////////////////////////////////
   class GridXNotifyee : public ValueChangeNotifyee{
   //////////////////////////////////////////////////////////
   public: 
      GridXNotifyee(){
         m_valueNameForNotifyee = "OsziGridX";
         m_listener             = NULL;
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
            m_listener->SetGridWidth(atoi((LPCSTR)value));
      }

      void setListener(COsziView*l){
         m_listener=l;
      }
   protected:
   COsziView* m_listener;
   } m_gridXNotifyee;

   //////////////////////////////////////////////////////////
   class GridYNotifyee : public ValueChangeNotifyee{
   //////////////////////////////////////////////////////////
   public: 
      GridYNotifyee(){
         m_valueNameForNotifyee = "OsziGridY";
         m_listener=NULL;
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
            m_listener->SetGridHeight(atoi((LPCSTR)value));
      }

      void setListener(COsziView*l){
         m_listener=l;
      }
   protected:
   COsziView* m_listener;
   } m_gridYNotifyee;

   //////////////////////////////////////////////////////////
   class GridNotifyee : public ValueChangeNotifyee{
   //////////////////////////////////////////////////////////
   public: 
      GridNotifyee(){
         m_listener=NULL;
         m_valueNameForNotifyee = "OsziGrid";
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
             m_listener->setGrid(value);
      }

      void setListener(COsziView* l){
         m_listener=l;
      }
   protected:
   COsziView* m_listener;
   } m_gridNotifyee;

   //////////////////////////////////////////////////////////
   class BgColorNotifyee : public ValueChangeNotifyee{
   //////////////////////////////////////////////////////////
   public: 
      BgColorNotifyee(){
         m_listener=NULL;
         m_valueNameForNotifyee = "OsziBgColor";
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
             m_listener->GetDocument()->SetPaperColor(atoi(value));
      }

      void setListener(COsziView* l){
         m_listener=l;
      }
   protected:
   COsziView* m_listener;
   } m_bgColorNotifyee;

   //////////////////////////////////////////////////////////
   class FgColorNotifyee : public ValueChangeNotifyee{
   //////////////////////////////////////////////////////////
   public: 
      FgColorNotifyee(){
         m_listener=NULL;
         m_valueNameForNotifyee = "OsziFgColor";
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
             m_listener->SetGridColor(atoi(value));
      }

      void setListener(COsziView* l){
         m_listener=l;
      }
   protected:
   COsziView* m_listener;
   } m_fgColorNotifyee;

   //////////////////////////////////////////////////////////
   class ZoomNotifyee : public ValueChangeNotifyee{
   //////////////////////////////////////////////////////////
   public: 
      ZoomNotifyee(){
         m_valueNameForNotifyee = "OsziZoom";
         m_listener=NULL;
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
            m_listener->SetScale(atoi((LPCSTR)value));
      }

      void setListener(COsziView*l){
         m_listener=l;
      }
   protected:
   COsziView* m_listener;
   } m_zoomNotifyee;

   //////////////////////////////////////////////////////////
   class DirectionNotifyee : public ValueChangeNotifyee{
   //////////////////////////////////////////////////////////
   public: 
      DirectionNotifyee(){
         m_valueNameForNotifyee = "OsziDirection";
         m_listener=NULL;
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
            m_listener->SetDirection(value);
      }

      void setListener(COsziView*l){
         m_listener=l;
      }
   protected:
   COsziView* m_listener;
   } m_directionNotifyee;



	COsziView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	virtual ~COsziView();

   CDigitalTraineeStudioView   *m_linkedView;
	bool m_isInverted;
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COsziView)
	//}}AFX_VIRTUAL

   //{{AFX_MSG(COsziView)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOptions();
	afx_msg void OnGrid();
	afx_msg void OnUpdateGrid(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnResetOszi();
	afx_msg void OnDateiExportPng();
	//}}AFX_MSG
   afx_msg void OnContextMenu(CWnd*, CPoint point);
	DECLARE_MESSAGE_MAP()
   DECLARE_DYNCREATE(COsziView)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_OSZIVIEW_H__758F5D63_C767_11D2_8970_004F49031E0C__INCLUDED_
