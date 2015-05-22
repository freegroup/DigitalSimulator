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
#include "DragDrop.h"  
#include "defines.h"
#include "math.h"  


#include "DragDropLink.h"
#include "DragDropPort.h"
#include "DragDropSelection.h"
#include "DragDropView.h"

IMPLEMENT_SERIAL(DragDropLink, DragDropStroke, 2)

//----------------------------------------------------------------------------
DragDropLink::DragDropLink(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_pFrom = NULL;
   m_pTo   = NULL;
}

//----------------------------------------------------------------------------
DragDropLink::DragDropLink(DragDropPort* pFrom, DragDropPort* pTo) : inherited(1){   
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(pFrom != NULL);
   assert(pTo   != NULL);

   m_pFrom = pFrom;
   m_pTo   = pTo;

   pFrom->AddLink(this);
   pTo->AddLink(this);
    
   SetDraggable(FALSE);
}                                                  

//----------------------------------------------------------------------------
DragDropLink::~DragDropLink(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   
    if (m_pFrom != NULL) 
       m_pFrom->RemoveLink(this);
    if (m_pTo != NULL)   
       m_pTo->RemoveLink(this);
}


//----------------------------------------------------------------------------
BOOL DragDropLink::paint(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!isVisible()) 
       return TRUE;

    if (NumPoints() > 0) {
       inherited::paint(pDC);   
    }

    return TRUE;
}

//----------------------------------------------------------------------------
void DragDropLink::GainedSelection(DragDropSelection* pSelection){
//----------------------------------------------------------------------------
	PROC_TRACE;


   assert(pSelection!=NULL);
   // the link has gained selection, it is time to set up resize handles
    
   if (!IsResizable()) {
       pSelection->CreateBoundingHandle (this);    
       return;
   }
       
    
   CPoint point;
   for (int i=1; i < NumPoints()-1; i++){
       point = GetPoint(i);
       pSelection->CreateResizeHandle (this, point.x, point.y, i + HandlesLast, TRUE);
   }           
    
    return;
                                                           
} 

//----------------------------------------------------------------------------
BOOL DragDropLink::HandleResizing(CClientDC* pDC, DragDropView* pView, CRect* pRect, CPoint pPoint, int nHandleHit, int nEvent, int, int){
//----------------------------------------------------------------------------
	PROC_TRACE;
    
    assert (nEvent == WM_LBUTTONDOWN);      // should only get here on a mouse down

    DragDropPort* pPort = m_pFrom;
    if (nHandleHit == 1 + HandlesLast) 
       pPort = m_pTo;

    Unlink();   // over-ridable to allow deletion of (this) link.

    CPoint point;
    point.x = pPoint.x;
    point.y = pPoint.y;
    pView->StartNewLink(pPort, point);

    return FALSE;   // don't let the view draw the XOR'd rectangle    
}

//----------------------------------------------------------------------------
void DragDropLink::Unlink(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   delete this;
}


//----------------------------------------------------------------------------
int DragDropLink::GetFirstPickPoint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return 1;
}

//----------------------------------------------------------------------------
int DragDropLink::GetLastPickPoint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return NumPoints()-1;
}

//----------------------------------------------------------------------------
void DragDropLink::AutoStroke(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pFrom != NULL);
   assert(m_pTo   != NULL);

    CPoint fromPt, toPt;
    int fromDir, toDir;
    
    // fromPt is an x,y to start from.  fromDir is an angle that the first link must 
    //    obey (0,90,180,270 for now)
    //
    //   0 - right
    //  90 - up
    // 180 - left
    // 270 - down
    
    fromPt  = m_pFrom->GetFromLinkPoint();
    fromDir = m_pFrom->GetFromLinkDir();
    
    toPt    = m_pTo->GetToLinkPoint();
    toDir   = m_pTo->GetToLinkDir();
                           
    // draw a line between the two points.
    
    StartStroke();
    AddPoint(fromPt);
    
    // MIN_LINK_SEGMENT = minimum length of Initial/final link segment
    // MAX_LINK_SEGMENT = maximum length of Initial/final link segment
    // CALC_LINK_SEGMENT = divisor to calculate Initial/final link segment
    
    // Minimize "Z-shaped" links by adjusting the Initial & final link
    // segments when the x and y deltas are small.
        
    int xseg = abs(fromPt.x - toPt.x) / CALC_LINK_SEGMENT;
    int yseg = abs(fromPt.y - toPt.y) / CALC_LINK_SEGMENT;
        
    if (xseg > MAX_LINK_SEGMENT) 
       xseg = MAX_LINK_SEGMENT;
    else if (xseg < MIN_LINK_SEGMENT) 
       xseg = MIN_LINK_SEGMENT;      
        
    if (yseg > MAX_LINK_SEGMENT) 
       yseg = MAX_LINK_SEGMENT;
    else if (yseg < MIN_LINK_SEGMENT) 
       yseg = MIN_LINK_SEGMENT;
    
    // now, we have the minimum X offsets for the normal case.  It is
    // time to see if the port would like to increase that minimum offset
    
    int fromMinXOffset = m_pFrom->GetMinXOffset();
    int xsegFrom = (xseg > fromMinXOffset) ?  xseg : fromMinXOffset;
    
    int toMinXOffset = m_pTo->GetMinXOffset(); 
    int xsegTo = (xseg > toMinXOffset) ?  xseg : toMinXOffset;
    
    // draw the Initial offset in Initial direction
    int cx = 0;
    int cy = 0;

    if (fromDir == 0) cx = xsegFrom;
    if (fromDir == 90) cy = yseg;
    if (fromDir == 180) cx = - xsegFrom;
    if (fromDir == 270) cy = - yseg;
    
    fromPt += CSize(cx, cy);
    AddPoint(fromPt);
                                        
    // calculate the offset from the "to" point                                     
    fromPt = toPt;      // copy to point    
    cx = cy = 0;
    if (toDir == 0)   cx = xsegTo;
    if (toDir == 90)  cy = yseg;
    if (toDir == 180) cx = - xsegTo;
    if (toDir == 270) cy = - yseg;
    
    fromPt += CSize(cx, cy);
    AddPoint(fromPt);    
                              
    // now finish up                              
    AddPoint(toPt);
    FinishStroke();
    
}


//----------------------------------------------------------------------------
void DragDropLink::PortChange(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    AutoStroke();       
}

//----------------------------------------------------------------------------
void DragDropLink::PortMarkedDelete(){ 
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_pFrom != NULL) {
      m_pFrom->RemoveLink(this);
      m_pFrom = NULL;
   }
    
   if (m_pTo != NULL){
      m_pTo->RemoveLink(this);
      m_pTo = NULL;
   }
    
   delete this;
}

//----------------------------------------------------------------------------
void DragDropLink::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);
   if (ar.IsStoring())    {       
       ar << m_pFrom;
       ar << m_pTo;
   }
   else {
       ar >> m_pFrom;
       ar >> m_pTo;
       if(m_pFrom !=NULL)
           m_pFrom->AddLink(this);
       if(m_pTo!=NULL)
           m_pTo->AddLink(this);
   }
}
