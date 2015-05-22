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

#include "stdafx.h"
#include "Application\DigitalSimulatorApp.h"
#include "OsziStroke.h"
#include "DragDropDocument.h"
#include "OsziView.h"
#include "Application\Debug\LogManager.h"

#define MAX_POINT_FOR_STROKE 500

IMPLEMENT_SERIAL(COsziStroke, DragDropStroke,4)

const  COsziStroke::m_version = 1;

//----------------------------------------------------------------------------
COsziStroke::COsziStroke() : DragDropStroke(2){
//----------------------------------------------------------------------------
	PROC_TRACE;


   m_pLabel        = NULL;
   m_yOffset       = -50;
   m_triggerHeight = 50;
   m_triggerWidth  = 10;
   SetStockPen(DragDropNoStock);
   SetPenColor(COLORREF(0x0000FF00));
   SetBrushColor(COLORREF(0x0000FF00));
   Set(CLogicValue(CLogicValue::High));
}


//----------------------------------------------------------------------------
COsziStroke::~COsziStroke(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   delete m_pLabel;
}


//----------------------------------------------------------------------------
void COsziStroke::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

   BOOL b;

   if (ar.IsStoring()){
      ar << m_version;
      ar << m_currentValue.IsHigh();
      ar << m_pLabel;  
      ar << m_triggerHeight;
      ar << m_triggerWidth;
      ar << m_yOffset;
   }
   else{
       int version;
       ar >> version;

       switch (version){
       case 1:
            ar >> b; m_currentValue= b?CLogicValue::High: CLogicValue::Low;
            ar >> m_pLabel;  
            ar >> m_triggerHeight;
            ar >> m_triggerWidth;
            ar >> m_yOffset;
            m_pDocument=NULL;
            m_pLabel->SetDocument(NULL);
            break;
       default:
            LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
            break;
       }
    }
}


//----------------------------------------------------------------------------
void COsziStroke::GainedSelection(DragDropSelection* pSelection){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Ein OsziStroke kann zwar verschoben werden, aber er zeichnet
   // keinen Selectionsrahmen oder Handles
   //
   //   -- do nothing --
}


//----------------------------------------------------------------------------
void COsziStroke::SetLabel(const CString &label){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_pLabel == NULL){
      m_pLabel  = new DragDropText(CPoint(0,0),CSize(40,40),"juhu");
      m_pLabel->SetEditable(FALSE);
      m_pLabel->SetSelectable(FALSE);
      m_pLabel->SetDraggable(FALSE);
      m_pLabel->SetResizable(FALSE);
   }

   m_pLabel->SetString(label);
   GeometryChange(&m_boundingRect);
}


//-----------------------------------------------------------------------------
void COsziStroke::SetLocation(CPoint pPoint){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   SetLocation(0, pPoint.y);
}


//-----------------------------------------------------------------------------
void COsziStroke::SetLocation(int , int y){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   CSize sizeThis = GetSize();
   SetBoundingRect(0, y, 0 + sizeThis.cx, y - sizeThis.cy);
   if(m_pLabel)
      m_pLabel->SetSpotLocation(DragDropObject::spotTopLeft,this,DragDropObject::spotTopLeft);
}                                        


//-----------------------------------------------------------------------------
void COsziStroke::SetLocationOffset(CPoint pPoint, CSize pOffset){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   SetLocationOffset(pPoint.x, pPoint.y, 0, pOffset.cy);
}


//-----------------------------------------------------------------------------
void COsziStroke::SetLocationOffset(CPoint pPoint, int , int cy){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   SetLocationOffset(pPoint.x, pPoint.y, 0, cy);
}     


//-----------------------------------------------------------------------------
void COsziStroke::SetLocationOffset(int x, int y, int , int cy){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   CSize sizeThis = GetSize();
   int nLeft   = x ;
   int nTop    = y ;
   SetBoundingRect(nLeft, nTop, nLeft + sizeThis.cx, nTop - sizeThis.cy);

   if(m_pLabel){
      m_pLabel->SetSpotLocation(DragDropObject::spotTopLeft,this,DragDropObject::spotTopLeft);
   }
}         


//-----------------------------------------------------------------------------
void COsziStroke::GeometryChange(CRect* pRectPrevious){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropStroke::GeometryChange(pRectPrevious);
}


//----------------------------------------------------------------------------
void COsziStroke::SetDocument(DragDropDocument* pDocument){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::SetDocument(pDocument);

   if((m_pLabel != NULL) && (pDocument != NULL)) {
      pDocument->AddObjectAtTail(m_pLabel);
   }
}


//----------------------------------------------------------------------------
BOOL COsziStroke::PtInObject(CClientDC* pDC, CPoint ptToCheckLP, CPoint ptToCheckDP){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Nicht die Funktion von DragDropStroke verwenden, da diese prueft ob der
   // Punkt auf einer Linie ist. Die Funktion von DragDropObject prueft
   // nur, ob der Punkt innerhalb des OutlineRect ist - ist in diesem
   // Fall besser.
   //
   return DragDropObject::PtInObject(pDC, ptToCheckLP, ptToCheckDP);
}


//----------------------------------------------------------------------------
void COsziStroke::Set(const CLogicValue& newValue ){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   long num    = NumPoints();

   // Der erste Punkt ist immer LOW
   if(num ==0) {
      AddPoint(CPoint(m_triggerWidth, -m_triggerHeight + m_yOffset));
   }

   CPoint p = GetEndPoint();
   
   if(m_currentValue == newValue){
      AddPoint(CPoint(p.x-m_triggerWidth ,p.y));
   }
   else if(newValue.IsHigh()){
      AddPoint(CPoint(p.x                ,p.y+m_triggerHeight));
      AddPoint(CPoint(p.x-m_triggerWidth ,p.y+m_triggerHeight));
   }
   else/* if(newValue.IsLow())*/{
      AddPoint(CPoint(p.x                ,p.y-m_triggerHeight));
      AddPoint(CPoint(p.x-m_triggerWidth ,p.y-m_triggerHeight));
   }

   // Es werden "ungefaehr" 300 Punkte gehalten.
   // Es sind zwischen dem Ermitteln von 'num' eventuell ein paar
   // dazugekommen.
   // - genaue Anzahl ist hier nicht so wichtig, lieber ein bischen
   // schneller sein ;-)
   //
   while((num--)>MAX_POINT_FOR_STROKE)
      RemovePoint(0);


   // TODO-Item 
   // SEHR teure Funktion - lieber selber etwas einfallen lassen
   //
   FinishStroke();

   // Den Punkt unten links in das Raster des Grid einfuegen
   //
   SetLocation(0,GetTopLeft().y);

   m_currentValue = newValue;
}


//----------------------------------------------------------------------------/////////////////////////////////////////////////////////////////////////////
void COsziStroke::FinishStroke(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Calculate the bounding rectangle.  It's needed for smart
   // repainting. SLOW!!!
   

   CRect rect;
   rect.SetRectEmpty();
   assert (NumPoints() > 0);

   int x = m_dwaPoints[0];
   int y = m_dwaPoints[1];

   rect = CRect(x, y,x, y);
   for (int i=1; i < (m_dwaPoints.GetSize()/2); i++) 
   {
       // If the point lies outside of the accumulated bounding
       // rectangle, then inflate the bounding rect to include it.
	   x = m_dwaPoints[i*2];
	   y = m_dwaPoints[i*2+1];

       rect.left     = min(rect.left  , x);
       rect.right    = max(rect.right , x);
       rect.top      = max(rect.top   , y);
       rect.bottom   = min(rect.bottom, y);
   }

   // Add the pen width to the bounding rectangle.  This is necessary
   // to account for the width of the stroke when invalidating
   // the screen.
   int nGrow = m_wPenWidth+3;  

   if (m_nHighlightWidth > nGrow) 
      nGrow = m_nHighlightWidth; // use highlight if bigger?

   rect.left   = rect.left  - nGrow;
   rect.right  = rect.right + nGrow;
   rect.top    = rect.top   + nGrow;
   rect.bottom = rect.bottom - nGrow;
 
   m_rectPrevBounding = m_boundingRect;  // save old one
   SetPrevRectValid(TRUE);
   SetBoundingRectForce(rect.left, rect.top, rect.right, rect.bottom);
   SetUpdateNeeded(FALSE);     // False says "do not clear new rectangle on Invalidate
   SetPrevRectValid(FALSE);
}

