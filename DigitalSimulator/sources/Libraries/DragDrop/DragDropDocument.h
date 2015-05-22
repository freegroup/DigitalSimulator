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

#ifndef _DRAGDROPDOC_H_
#define _DRAGDROPDOC_H_

#include "DragDropObject.h"
//#include <afxole.h>    
#include "DragDropLayout.h"
class DragDropView;

class DragDropDocument : public CDocument{
   typedef CDocument inherited;

public:
	virtual void LayoutDiagram(int nDirection = LAYOUT_HORIZ,
        int nNodeHeight = 300,
        int nNodeWidth = 300,
        int nSpacePrcnt = 30,
        BOOL bBalanceLayout = TRUE,
        BOOL bResizeNodes = FALSE,
        int nHorizOffset = 0,
        int nVertOffset = 0
        );
    virtual CSize GetDocumentSize() const { return m_sizeDocument; }
    virtual void  SetDocumentSize (CSize size) {m_sizeDocument = size;}
	 virtual void  GrowDocument(int cx, int cy);	
    virtual CSize GetDocumentLineSize() const { return m_sizeDocumentLine; }
    virtual void  SetDocumentLineSize (CSize size) {m_sizeDocumentLine = size;}
    virtual int   GetViewCount() const {return m_viewList.GetCount();}
    virtual int   GetUnitSize()  {return m_nUnit ;}     //ISO
    virtual const int MaxDoc()   {return m_nMaxDoc;}
    virtual const int MinScale() {return m_nMinScale;}
    virtual const int MaxScale() {return m_nMaxScale;}

    virtual CSize GetMinLayoutSize();

    virtual CSize GetMinSize() {return m_sizeMinimum;}
    virtual void SetMinSize(CSize sizeMin) {m_sizeMinimum = sizeMin;}
    
    
    virtual COLORREF GetPaperColor() const { return m_paperColor; }
    virtual void SetPaperColor(COLORREF color);    
    virtual void OnSysColorChange();
    
public:
    virtual POSITION AddObjectAtHead(DragDropObject* pObject, BOOL bForceFirstDraw = TRUE); 
    virtual POSITION AddObjectAtTail(DragDropObject* pObject, BOOL bForceFirstDraw = TRUE);


    virtual void RemoveObject(DragDropObject* pObject);  
    virtual void DeleteObject(DragDropObject* pObject);
    virtual void DeleteContents();

    virtual BOOL IsEmpty() {return m_oblistObjects.IsEmpty();}

    virtual void BringObjectToFront(DragDropObject* pObject);
    virtual void SendObjectToBack(DragDropObject* pObject);
    
    // Document iterators
    
    virtual POSITION GetFirstObjectPos() const;
    virtual DragDropObject* GetNextObject(POSITION& pos) const;
    virtual DragDropObject* GetNextObjectAtTop(POSITION& pos) const; 

    virtual DragDropObject* PickInDocument(CClientDC* pDC, CPoint ptToCheckLP, BOOL bSelectableOnly = FALSE);

     
    virtual void SetCurrentDrawView(DragDropView* pView) {m_pCurrentDrawView = pView;}
    DragDropView* GetCurrentDrawView() {return m_pCurrentDrawView;}


	 virtual void StartAutomation(DragDropObject* pObj = NULL);
	 virtual void EndAutomation(DragDropObject* pObj = NULL);
    virtual void UpdateAutomation();

    // Suspend updates - dangerous stuff...
    virtual void SuspendUpdates() {m_bSuspendUpdates = TRUE;}
    virtual void ResumeUpdates()  {m_bSuspendUpdates = FALSE;}
    virtual BOOL UpdatesSuspended() {return m_bSuspendUpdates; }
    virtual DragDropPort* FromPort(DragDropPort* pPort1, DragDropPort* pPort2);
    virtual DragDropPort* ToPort(DragDropPort* pPort1, DragDropPort* pPort2);

// Implementation
public:
    virtual ~DragDropDocument();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o

protected: 
    DragDropDocument();
//    virtual BOOL    OnNewDocument();
//    virtual BOOL    OnOpenDocument(LPCTSTR pPathName);
    virtual void    Init(); 
    
    CObList m_oblistObjects;    // the objects the document can contain.
    CSize m_sizeDocument;
    CSize m_sizeDocumentLine;
    CSize m_sizeMinimum;
    int   m_nMaxDoc;
    int   m_nMinScale;
    int   m_nMaxScale;
    int   m_nUnit;

    DragDropView* m_pCurrentDrawView;
    
    COLORREF    m_paperColor;
    BOOL        m_bUseSystemPaperColor;    
    BOOL        m_bSuspendUpdates; 


protected:
    //{{AFX_MSG(DragDropDocument)
    afx_msg void OnEditClearAll();
    afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
    //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   DECLARE_DYNCREATE(DragDropDocument)
};


#endif
