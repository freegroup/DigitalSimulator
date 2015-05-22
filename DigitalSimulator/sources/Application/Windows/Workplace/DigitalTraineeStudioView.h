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

#if !defined(AFX_DIGITALTRAINEESTUDIOVIEW_H__684B4A2C_6044_11D2_890E_004F49031E0C__INCLUDED_)
#define AFX_DIGITALTRAINEESTUDIOVIEW_H__684B4A2C_6044_11D2_890E_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)


// libraries
#include "DragDropGridView.h"
#include "AVIFile.h"

#include "utils\ThreadMutex.h"

#include "Application\Configuration\ParameterManager.h"
#include "Application\Objects\buildin\digital\ElectricPortLink.h"
#include "Application\Objects\buildin\digital\ElectricNode.h"
#include "Application\Objects\buildin\Common\DocumentProtection.h"
#include "Application\Objects\buildin\Common\DocumentDocumentation.h"
#include "Application\Windows\workplace\DigitalTraineeStudioDoc.h"
#include "Application\Controls\DataTip\tfxdatatip.h"


class COsziView;

class CDigitalTraineeStudioView : public DragDropGridView{
   typedef DragDropGridView inherited;

public:
	virtual ~CDigitalTraineeStudioView();

   virtual DragDropLink* NewLink(DragDropPort* pFrom, DragDropPort* pTo);
   virtual BOOL ValidLink(DragDropPort* pFrom, DragDropPort* pTo);
   virtual BOOL ValidSourcePort(DragDropPort* pFrom);
   virtual BOOL DropObject(DragDropView* pSourceView, DragDropObject* pSourceObject, CPoint pPoint, UINT nFlags);

   virtual void setGrid(const CString& Style);
   virtual void setGridStyle(const CString& Style);
   virtual void setGridX(const long& xSize);
   virtual void setGridY(const long& ySize);
   virtual void setConnectorFlyover(const bool& flag);
   virtual void SetScale(int percent, float clientRectFactor = 0.8);

   virtual void OnWindowToTop();

   virtual CString SaveTempCircuitImage();
   virtual CString SaveTempCircuit();

   static CDigitalTraineeStudioView* GetActiveView(){return s_activeView;};
   COsziView          *m_osziView;

   virtual void    SetDocumentation(CString docAsXml);
   virtual CString GetDocumentation();

protected:
   DocumentProtection    *m_documentProtection;
   DocumentDocumentation *m_documentDocumentation;

   CPoint                 m_contextMenuMousePos;
   CString                m_lastInsertedObjectTyp;
   
   // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDigitalTraineeStudioView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

   virtual char * const GetClassName(){return "CDigitalTraineeStudioView";};

   //////////////////////////////////////////////////////////////////////
   // Callback for GridY Flag
   //
   class GridXNotifyee : public ValueChangeNotifyee{
   public: 
      GridXNotifyee(){
         m_valueNameForNotifyee = "GridX";
         m_listener             = NULL;
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
            m_listener->setGridX(atoi((LPCSTR)value));
      }

      void setListener(CDigitalTraineeStudioView*l){
         m_listener=l;
      }
   protected:
   CDigitalTraineeStudioView* m_listener;
   } m_gridXNotifyee;

   //////////////////////////////////////////////////////////////////////
   // Callback for GridY Flag
   //
   class GridYNotifyee : public ValueChangeNotifyee{
   public: 
      GridYNotifyee(){
         m_valueNameForNotifyee = "GridY";
         m_listener=NULL;
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
            m_listener->setGridY(atoi((LPCSTR)value));
      }

      void setListener(CDigitalTraineeStudioView*l){
         m_listener=l;
      }
   protected:
   CDigitalTraineeStudioView* m_listener;
   } m_gridYNotifyee;


   //////////////////////////////////////////////////////////////////////
   // Callback for Grid Flag
   //
   class GridNotifyee : public ValueChangeNotifyee{
   public: 
      GridNotifyee(){
         m_listener=NULL;
         m_valueNameForNotifyee = "Grid";
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
             m_listener->setGrid(value);
      }

      void setListener(CDigitalTraineeStudioView*l){
         m_listener=l;
      }
   protected:
   CDigitalTraineeStudioView* m_listener;
   } m_gridNotifyee;

   //////////////////////////////////////////////////////////////////////
   // Callback for Connector Flag
   //
   class ConnectorFlyoverNotifyee : public ValueChangeNotifyee{
   public: 
      ConnectorFlyoverNotifyee(){
         m_listener=NULL;
         m_valueNameForNotifyee = "ConnectorFlyover";
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
            m_listener->setConnectorFlyover(value.CompareNoCase("true")==0?true:false);
      }

      void setListener(CDigitalTraineeStudioView*l){
         m_listener=l;
      }
   protected:
   CDigitalTraineeStudioView* m_listener;
   } m_connectorFlyoverNotifyee;

   //////////////////////////////////////////////////////////////////////
   // Callback for GridStyle Flag
   //
   class GridStyleNotifyee : public ValueChangeNotifyee{
   public: 
      GridStyleNotifyee(){
         m_valueNameForNotifyee = "GridStyle";
         m_listener=NULL;
      };
      virtual void AfterChange(const CString& value){
         if(m_listener!=NULL)
            m_listener->setGridStyle(value);
      }

      void setListener(CDigitalTraineeStudioView*l){
         m_listener=l;
      }
   protected:
   CDigitalTraineeStudioView* m_listener;
   } m_gridStyleNotifyee;

protected:
   CDigitalTraineeStudioView();
   void HandleResizing(CClientDC* pDC, CPoint pPoint, int event);


   TFXDataTip m_toolTip;

   CAVIFile   m_aviFile;
   bool       isRunningNormalMode;
   bool       isRunningAVIMode;
   bool       useConnectorFlyover;
   DragDropLink* m_flyoverLink;

   static CDigitalTraineeStudioView* s_activeView;
   static long                       s_counter;

   // Locking Class
   //
   ThreadMutex m_mutex;
   class ScopeMutex{
   public:
      ScopeMutex(CDigitalTraineeStudioView *p){
         m_parent = p;
         m_parent->m_mutex.lock();
      }

      ~ScopeMutex(){
         m_parent->m_mutex.unlock();
      }
      CDigitalTraineeStudioView* m_parent;
   };
   friend  CDigitalTraineeStudioView::ScopeMutex;


	afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CDigitalTraineeStudioView)
	afx_msg void OnInsertObject();
	afx_msg void OnAlignDown();
	afx_msg void OnUpdateAlignDown(CCmdUI* pCmdUI);
	afx_msg void OnAlignLeft();
	afx_msg void OnUpdateAlignLeft(CCmdUI* pCmdUI);
	afx_msg void OnAlignRight();
	afx_msg void OnUpdateAlignRight(CCmdUI* pCmdUI);
	afx_msg void OnAlignUp();
	afx_msg void OnUpdateAlignUp(CCmdUI* pCmdUI);
	afx_msg void OnGrid();
	afx_msg void OnUpdateGrid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetGrid(CCmdUI* pCmdUI);
	afx_msg void OnStartSimulation();
	afx_msg void OnZoomDecrease();
	afx_msg void OnZoomFit();
	afx_msg void OnZoomIncrease();
	afx_msg void OnZoomStandard();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditCut();
	afx_msg void OnObjectOption();
	afx_msg void OnObjectExtendedOption();
	afx_msg void OnUpdateStartSimulation(CCmdUI* pCmdUI);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnObjectToBack();
	afx_msg void OnUpdateObjectToBack(CCmdUI* pCmdUI);
	afx_msg void OnObjectToFront();
	afx_msg void OnUpdateObjectToFront(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnInsertRemoveViewPoint();
	afx_msg void OnUpdateInsertRemoveViewPoint(CCmdUI* pCmdUI);
	afx_msg void OnRemoveStrokeSegment();
	afx_msg void OnUpdateRemoveStrokeSegment(CCmdUI* pCmdUI);
	afx_msg void OnInsertStrokeSegment();
	afx_msg void OnUpdateInsertStrokeSegment(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnObjectBasics();
	afx_msg void OnUpdateObjectBasics(CCmdUI* pCmdUI);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnUpdateObjectHelp(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUpdateFileClose(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDateiExport(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnStartSimulationRecord();
	afx_msg void OnUpdateStartSimulationRecord(CCmdUI* pCmdUI);
	afx_msg void OnProtectDocument();
	afx_msg void OnUpdateProtectDocument(CCmdUI* pCmdUI);
	afx_msg void OnConnectorFlyover();
	afx_msg void OnUpdateConnectorFlyover(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDateiExportJni();
	afx_msg void OnUpdateDateiExportJni(CCmdUI* pCmdUI);
	afx_msg void OnOsziPrint();
	afx_msg void OnUpdateOsziPrint(CCmdUI* pCmdUI);
	//}}AFX_MSG
    afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg bool OnObjectHelp();
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CDigitalTraineeStudioView)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_DIGITALTRAINEESTUDIOVIEW_H__684B4A2C_6044_11D2_890E_004F49031E0C__INCLUDED_)
