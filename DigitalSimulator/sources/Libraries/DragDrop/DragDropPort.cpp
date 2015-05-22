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

#include "DragDropstdafx.h"      
#include "afxcmn.h"
#include "DragDrop.h"
#include "DragDropApp.h"
#include "DragDropClientapp.h"
#include "DragDropPort.h"
#include "DragDropDocument.h"
#include "DragDropView.h"
#include "DragDropLink.h"

static CSize StaticSize(0,0);
static int portFudge = -1;

CImageList*  DragDropPort::m_pImglist        = NULL;

int DragDropPort::m_nScaleNoDraw   = 40;
int DragDropPort::m_nScaleFakeDraw = 40;

IMPLEMENT_SERIAL(DragDropPort, DragDropObject, 2)

//----------------------------------------------------------------------------
DragDropPort::DragDropPort(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    // this empty constructor should be used by serialization only
    m_bUserCreatedLinks = TRUE;     // Mouse down starts link creation
}

//----------------------------------------------------------------------------
DragDropPort::DragDropPort(CPoint location, int nBitMapId, int nToSide, int nFromSide) : inherited(location, StaticSize){   
//----------------------------------------------------------------------------
	PROC_TRACE;

    assert((nFromSide >= 0) && (nFromSide < PortSidesLast));
    assert((nToSide >= 0) && (nToSide < PortSidesLast));

    SetSelectable (FALSE);          // DragDropObject attributes
    SetResizable  (FALSE);          // fixed sized object
    m_bUserCreatedLinks = TRUE;     // Mouse down starts link creation

    m_nBitmapId = nBitMapId;
        
    m_nFromSide = nFromSide; 
    m_nToSide   = nToSide;                                                                                    
}

//----------------------------------------------------------------------------
void DragDropPort::Init(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   InitSize();
   SetValidLink(FALSE);            // Valid link must be set by view on each mouse down  
}

//----------------------------------------------------------------------------
void DragDropPort::InitSize(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_nBitmapId = GetBitmapId();    // load in case this Get.. is an override
    
    assert((m_nBitmapId >= -1) && (m_nBitmapId < PortMax()));

    if (m_nBitmapId >= 0) {
        m_nWidth = GetPortWidth();
        m_nHeight = GetPortHeight();
    }
    else  {
        m_nWidth  = 0;   // -1 is special NULL port
        m_nHeight = 0;
    }                        
    Measure();
}

//----------------------------------------------------------------------------
int DragDropPort::GetBitmapId(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_nBitmapId;
}

//----------------------------------------------------------------------------
void DragDropPort::SetBitmapId (int nBitmapId){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // No-op if the bitmap hasn't changed.

    if (m_nBitmapId == nBitmapId) 
       return;

    int nOldW = m_nWidth;       // save old width
    int nOldH = m_nHeight;      // save old height
    SetUpdateNeeded(TRUE);      // clear old region 

    m_nBitmapId = nBitmapId;    // New ID
    InitSize();                 // Set new pixel widths and measure

    // Now, if the new bitmap is bigger, need to update newer region
    if ((nOldW < m_nWidth) || (nOldH < m_nHeight)){
       SetUpdateNeeded(TRUE);  // clear new region 
    }
}

//----------------------------------------------------------------------------
DragDropPort::~DragDropPort(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   for (POSITION pos = m_oblistLinks.GetHeadPosition(); pos != NULL; ) {
        DragDropLink* pLink =(DragDropLink*) m_oblistLinks.GetNext(pos);
        ASSERT(pLink->IsKindOf(RUNTIME_CLASS(DragDropLink)));
        pLink->PortMarkedDelete();  
    }   
    ASSERT(m_oblistLinks.IsEmpty());  
	
} 

//----------------------------------------------------------------------------
void DragDropPort::AppRunDown(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   delete m_pImglist;
   m_pImglist = NULL;
}

//----------------------------------------------------------------------------
DragDropObject* DragDropPort::Clone() const{   
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pObject = inherited::Clone(); 

   ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropPort)));                  
   DragDropPort* pPort =(DragDropPort*) pObject; 
   pPort->m_nWidth     = m_nWidth;
   pPort->m_nHeight    = m_nHeight;
   pPort->m_nFromSide  = m_nFromSide;   // top, right, left, bottom
   pPort->m_nToSide    = m_nToSide;   // top, right, left, bottom
   pPort->m_nBitmapId  = m_nBitmapId;

   return pObject;
}

//----------------------------------------------------------------------------
void DragDropPort::Measure(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC dc(AfxGetApp()->m_pMainWnd);
   Measure(&dc);
}

//----------------------------------------------------------------------------
void DragDropPort::Measure(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   CDragDropApp* theapp = (CDragDropApp*) AfxGetApp();
   theapp->OnPrepareDC(pDC, NULL, 100);
    
   CPoint size(m_nWidth, m_nHeight);
   pDC->DPtoLP(&size);
   SetSize(size.x, abs(size.y));
}

//----------------------------------------------------------------------------
BOOL DragDropPort::paint(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!isVisible() || m_nBitmapId == -1) 
       return TRUE;

	DragDropView* pView;
	if (m_pDocument) 
      pView = m_pDocument->GetCurrentDrawView();
	else 
      pView = m_pView;

	int nScale =100;
	if (pView) 
      nScale = pView->GetScale();

	if (nScale < m_nScaleNoDraw) 
      return TRUE; 

   if (m_pImglist){
      CPoint point = GetTopLeft();
      point += CPoint(0,-19);
      m_pImglist->Draw(pDC, GetBitmapId(),point,ILD_TRANSPARENT);
	}

   return TRUE;
}


//----------------------------------------------------------------------------
void DragDropPort::PortChanged(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    for (POSITION pos = m_oblistLinks.GetHeadPosition(); pos != NULL; )  {
       DragDropLink* pLink =(DragDropLink*) m_oblistLinks.GetNext(pos);
        ASSERT(pLink->IsKindOf(RUNTIME_CLASS(DragDropLink)));
        pLink->PortChange();
    }  
}

//----------------------------------------------------------------------------
void DragDropPort::GeometryChange(CRect* pRectPrevious){
//----------------------------------------------------------------------------
	PROC_TRACE;

   PortChanged();
}

//----------------------------------------------------------------------------
void DragDropPort::AddLink(DragDropObject* pLink){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_oblistLinks.AddTail(pLink);   
}

//----------------------------------------------------------------------------    
void DragDropPort::RemoveLink(DragDropObject* pLink){
//----------------------------------------------------------------------------
	PROC_TRACE;

   POSITION pos;  
   if( ( pos = m_oblistLinks.Find( pLink ) ) != NULL ){                                        
        m_oblistLinks.RemoveAt(pos);
   }
   else
        TRACE0("Error removing link from port\n");
}

//----------------------------------------------------------------------------
CPoint DragDropPort::GetLinkPoint(int nSide){
//----------------------------------------------------------------------------
	PROC_TRACE;

    int nWidth = abs(m_boundingRect.Width());
    int nHeight = abs(m_boundingRect.Height());
    
    int x1 = m_boundingRect.left;
    int x3 = m_boundingRect.left + (nWidth/2);
    int x6 = m_boundingRect.right;
    
    int y1 = m_boundingRect.top;
    int y3 = m_boundingRect.top - (nHeight/2) - portFudge;    // fudge factor derived from experiment
    int y6 = m_boundingRect.bottom;

    if (nSide == PSNone)   return CPoint (x3,y3);    // middle
    if (nSide == PSTop)    return CPoint (x3,y1);    // top
    if (nSide == PSRight)  return CPoint (x6,y3);    // right
    if (nSide == PSBottom) return CPoint (x3,y6);    // bottom
    if (nSide == PSLeft)   return CPoint (x1,y3);    // left
    
    // error
    TRACE0("Error in DragDropPort::GetLinkPoint();\n");
    return CPoint (0,0);
}

//----------------------------------------------------------------------------
CPoint DragDropPort::GetFromLinkPoint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return GetLinkPoint(m_nFromSide);
}

//----------------------------------------------------------------------------
CPoint DragDropPort::GetToLinkPoint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return GetLinkPoint(m_nToSide);
}

//---------------------------------------------------------------------------- 
int DragDropPort::GetLinkDir(int nSide){
//----------------------------------------------------------------------------
	PROC_TRACE;

    *   <li>up -&gt; 0</li>
    *   <li>right -&gt; 1</li>
    *   <li>down -&gt; 2</li>
    *   <li>left -&gt; 3</li>

   if (nSide == PSNone)   return -1;   // None means "no offset in any direction"
    if (nSide == PSTop)    return 90;   // top
    if (nSide == PSRight)  return 0;        // right
    if (nSide == PSBottom) return 270;  // bottom
    if (nSide == PSLeft)   return 180;  // left
    
    // error
    TRACE0("Error in DragDropPort::GetLinkDir()\n");
    return 0;
}

//----------------------------------------------------------------------------
int DragDropPort::GetFromLinkDir(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return GetLinkDir(m_nFromSide);
}

//----------------------------------------------------------------------------
int DragDropPort::GetToLinkDir(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return GetLinkDir(m_nToSide);
}

//----------------------------------------------------------------------------
BOOL DragDropPort::IsValidLink(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_bValidLink;
}

//----------------------------------------------------------------------------
void DragDropPort::SetValidLink(BOOL bValid){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // ValidLink is used to cache state about whether this port is a valid end point
   // for one other port in the document.  It is used by the view to cache this
   // value on a mouse-down that starts a link creation.
   m_bValidLink = bValid;
}

//----------------------------------------------------------------------------
int DragDropPort::SetFromSide(int nNewSide){
//----------------------------------------------------------------------------
	PROC_TRACE;

   int tmp = m_nFromSide;
   m_nFromSide = nNewSide; 
   if (tmp != nNewSide) 
      PortChanged();     // don't call if no change
   return tmp;
}

//----------------------------------------------------------------------------
int DragDropPort::SetToSide(int nNewSide){
//----------------------------------------------------------------------------
	PROC_TRACE;

    int tmp = m_nToSide;
    m_nToSide = nNewSide;
    if (tmp != nNewSide) PortChanged();     // don't call if no change
    return tmp;
}



//----------------------------------------------------------------------------
int DragDropPort::PortMax(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   TRACE0("DragDropPort::PortMax, function must be overriden in derived class\n");
   return 0;   
}

//----------------------------------------------------------------------------
int DragDropPort::GetPortWidth(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return 16;
}

//----------------------------------------------------------------------------
int DragDropPort::GetPortHeight(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return 16;
}

//----------------------------------------------------------------------------
int DragDropPort::GetPortOffset(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return 16*GetBitmapId();
}

//----------------------------------------------------------------------------
BOOL DragDropPort::EnableImageList(UINT nResId, int cx){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (m_pImglist)
      return TRUE;

	// a fancier way to setup the port bitmaps, using the new ImageList Win32 control
	// advantage is that it has transparancy.

	m_pImglist = new CImageList();
	BOOL status = m_pImglist->Create(nResId, cx, 1,  RGB(255,255,255));
	if (!status) {
		TRACE(_T("DragDropPort::EnableImageList, error creating imagelist\n"));
		return FALSE;
	}

	return TRUE;
}                

//----------------------------------------------------------------------------
void DragDropPort::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);
   if (ar.IsStoring()) {
        ar << (WORD) m_nBitmapId; 
        ar << (WORD) m_nFromSide; 
        ar << (WORD) m_nToSide; 
        ar << (WORD) m_nWidth;
        ar << (WORD) m_nHeight;
    }
    else {
        WORD w;
        ar >> w;
        m_nBitmapId = (int) w; 
        ar >> w;
        m_nFromSide = (int) w; 
        ar >> w;
        m_nToSide = (int) w; 
        ar >> w;
        m_nWidth = (int) w;
        ar >> w;
        m_nHeight = (int) w;                
    }
}                          

