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
#include "Application\Windows\Workplace\DigitalTraineeStudioView.h"
#include "Application\Windows\Oszi\OsziView.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Debug\LogManager.h"

#include "ElectricPortLink.h"


IMPLEMENT_SERIAL(CElectricPortLink, DragDropLink, 4)
const  CElectricPortLink::m_version = 2;

//----------------------------------------------------------------------------
CElectricPortLink::CElectricPortLink(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    // this empty constructor should be used by serialization only
   m_routingHasChanged = true;
   m_viewPoint         = NULL;
   m_osziStroke        = NULL;
	SetHighlightWidth(14);
}

//----------------------------------------------------------------------------
CElectricPortLink::CElectricPortLink(DragDropPort* pFrom, DragDropPort* pTo) 
   : DragDropLink(pFrom, pTo){   
//----------------------------------------------------------------------------
   assert(pFrom!= NULL);
   assert(pTo != NULL);

   SetHighlightColor(RGB(55,155,135));
	SetStockPen(DragDropNoStock);
   SetPenColor(COLORREF(0x000000));
   SetResizable( TRUE);

   m_osziStroke        = NULL;
   m_routingHasChanged = false;
   m_viewPoint         = NULL;
	SetHighlightWidth(14);
	AutoStroke();
}








//----------------------------------------------------------------------------
void CElectricPortLink::AutoStroke(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if( m_routingHasChanged == false){
       // Das Routing der Leitung wurde noch nicht 
       // mit Hand ver�dert. Man kann somit die gesamte 
       // Leitung automatisch verlegen, ohne ein eventuell
       // festgelegtes Routing zu zerstoeren
       //
       FullAutoStroke();
    }
    else{
       // Die Leitung wurde zuvor mit Hand veraendert. Man
       // sollte jetzt nur die Punkte aendern, die unbedingt 
       // notwendig sind.
       //
       HalfAutoStroke();
    }

    LayoutViewPointImage();
    LayoutSplitPointImage();
}


//----------------------------------------------------------------------------
void CElectricPortLink::HalfAutoStroke(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CPoint fromPt, toPt;
    int fromDir, toDir;
    
    // fromPt is an x,y to start from.  
    // fromDir is an angle that the first link must 
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

    // Falls es nicht moeglich ist ein vernuenftiges Routing
    // mehr zu machen, muss autorouting eingeschaltet werden
    //
    if((fromDir ==0 ) && (toDir == 180) && (fromPt.x> toPt.x) && (NumPoints()<=4)){
       m_routingHasChanged = false;
       return;
    }

    // Falls Anfang und Endpunkt verschoben werden (DragDrop) mu�auch die
    // GESAMTE Leitung verschoben werden und nicht nur die Anfangs und Endpunkte
    // angepasste werden!
    //
    // Da bei einem Verschieben der Leitung dieser Codeteil 2 mal durchlaufen wird
    // ( einmal fr den FromPort und einmal fr den ToPort) wird nur die erste
    // Notifikation beachtet und in diesem Teil schon alle Punkte ver�dert. Die
    // zweite Notifikation kann ignoriert werden, da sein verschieben schon 
    // bei der ersten behandelt wurde
    //
    // 1. Notifikation
    //
    CPoint divFrom  = fromPt - GetPoint(0);
    CPoint divTo    = toPt   - GetPoint(NumPoints()-1);
    if( m_selected && (divFrom.x!=0 || divFrom.y!=0)){
       for (int i=0; i < NumPoints(); i++){
           CPoint p =GetPoint(i);
           SetPoint(i,p+divFrom);
       }
       return;
    }
    // 2. Notifikation
    //
    if( m_selected && (divTo.x!=0 || divTo.y!=0)){
       return;
    }
    

    // Der Anschlusspunkt (p0) des Link wurde verschoben
    //
    if(fromPt != GetPoint(0)){
       //          .
       //   p0     . p1
       //   +------+
       //          .
       //          .
       //
       if(fromDir == 0){
         CPoint p1 = GetPoint(1);
         CPoint p2 = GetPoint(2);
         SetPoint(0,fromPt);
         SetPoint(1,CPoint(max(fromPt.x+10,p1.x),fromPt.y));
         SetPoint(2,CPoint(max(fromPt.x+10,p1.x),p2.y));  // p2
       }
       //   .       
       //   . p1     p0
       //   +------+
       //   .       
       //   .       
       //
       else if(fromDir == 180){
         CPoint p1 = GetPoint(1);
         CPoint p2 = GetPoint(2);
         SetPoint(0,fromPt);
         SetPoint(1,CPoint(min(fromPt.x-10,p1.x),fromPt.y));
         SetPoint(2,CPoint(min(fromPt.x-10,p1.x),p2.y));  // p2
       }
       //     ...+....
       //     p1 |      
       //        |  
       //        |  
       //     p0 +  
       //
       else if ((fromDir == 90) || (fromDir ==270)){
         CPoint p1 = GetPoint(1);
         SetPoint(0,fromPt);
         SetPoint(1,CPoint(fromPt.x,p1.y));
       }
    }

    // Der Endpunkt (hier p0)  des Link wurde verschoben
    //
    if(toPt != GetPoint(NumPoints()-1)){
      switch(toDir){
      //    
      //               .
      //      p0       . p1
      //    +----------+ 
      //               .
      //               .
      //    
      //
      case 0:{
         CPoint p1 = GetPoint(NumPoints()-2);
         CPoint p2 = GetPoint(NumPoints()-3);
         SetPoint(NumPoints()-1,toPt);                                // p0
         SetPoint(NumPoints()-2,CPoint(max(toPt.x+10,p1.x),toPt.y));  // p1
         SetPoint(NumPoints()-3,CPoint(max(toPt.x+10,p1.x),p2.y));    // p2
         }   
         break;
      //    .
      //    .
      //    . p1         p0
      //    +----------+ 
      //    .
      //    .
      //    .
      //
      case 180:{
         CPoint p1 = GetPoint(NumPoints()-2);
         CPoint p2 = GetPoint(NumPoints()-3);
         SetPoint(NumPoints()-1,toPt);                                // p0
         SetPoint(NumPoints()-2,CPoint(min(toPt.x-10,p1.x),toPt.y));  // p1
         SetPoint(NumPoints()-3,CPoint(min(toPt.x-10,p1.x),p2.y));    // p2
         }
         break;
      //     ...+....
      //     p1 |      
      //        |  
      //        |  
      //     p0 +  
      //
      case 90:{
         CPoint p1 = GetPoint(NumPoints()-2);
         CPoint p2 = GetPoint(NumPoints()-3);
         SetPoint(NumPoints()-1,toPt);                                // p0
         SetPoint(NumPoints()-2,CPoint(toPt.x,max(toPt.y+10,p1.y)));  // p1
         SetPoint(NumPoints()-3,CPoint(p2.x  ,max(toPt.y+10,p1.y)));  // p2
         }
         break;
      //        +    
      //     p0 |      
      //        |  
      //     p1 |  
      //     ...+...
      //
      case 270:{
         CPoint p1 = GetPoint(NumPoints()-2);
         CPoint p2 = GetPoint(NumPoints()-3);
         SetPoint(NumPoints()-1,toPt);                                // p0
         SetPoint(NumPoints()-2,CPoint(toPt.x,max(toPt.y+10,p1.y)));  // p1
         SetPoint(NumPoints()-3,CPoint(p2.x  ,max(toPt.y+10,p1.y)));  // p2
         }
         break;
      }
   }
}

//----------------------------------------------------------------------------
void CElectricPortLink::FullAutoStroke(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CPoint fromPt, toPt;
    int fromDir, toDir;
    
    // fromPt is an x,y to start from.  
    // fromDir is an angle that the first link must 
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
    AddPoint(fromPt);     // point 1
    
    
	int xseg = 50;	   //** new for rect links
	int yseg = 100;

   int fromMinXOffset = m_pFrom->GetMinXOffset();
   int xsegFrom = max(xseg ,fromMinXOffset);
    
   int toMinXOffset = m_pTo->GetMinXOffset(); 
   int xsegTo = max(xseg, toMinXOffset);

	int ysegTo = yseg;

    //note: no getminYoffset, makes more sense for sides ports with labels. 

    // draw the Initial offset in Initial direction
    int cx = 0;
    int cy = 0;

    if (fromDir == 0) cx = xsegFrom;
    if (fromDir == 90) cy = yseg;
    if (fromDir == 180) cx = - xsegFrom;
    if (fromDir == 270) cy = - yseg;
    
	// do the simple ones (e.g. out the right and into the left of a node positioned to the right.)
	if (fromDir == 0 && toDir == 180 && fromPt.x < toPt.x) {
		// to right
		fromPt.x = fromPt.x + ((toPt.x - fromPt.x) / 2);	// half way to next port (may be less than yseg)
		AddPoint(fromPt);       // point 2
	}
	else if (fromDir == 90 && toDir == 270 && fromPt.y < toPt.y) {
		// up
		fromPt.y = fromPt.y + ((toPt.y - fromPt.y) / 2);	// half way to next port (may be less than yseg)
		AddPoint(fromPt);       // point 2
	}
	else if (fromDir == 180 && toDir == 0 && fromPt.x > toPt.x) {
		// to left
		fromPt.x = fromPt.x - ((fromPt.x - toPt.x) / 2);	// half way to next port (may be less than yseg)
		AddPoint(fromPt);       // point 2
	}
	else if (fromDir == 270 && toDir == 90 && fromPt.y > toPt.y) {
		// down
		fromPt.y = fromPt.y - ((fromPt.y - toPt.y) / 2);	// half way to next port (may be less than yseg)
		AddPoint(fromPt);       // point 2
	}

	else {

		// none of the simple cases DoCalculateed out... do the more complicated routing

		fromPt += CSize(cx, cy);
		AddPoint(fromPt);       // point 2

		// may soon need info about parent areas of these ports
		CRect rectFrom = m_pFrom->GetParent()->GetBoundingRect();
		CRect rectTo   = m_pTo->GetParent()->GetBoundingRect();

		switch (toDir)
		{             
		case 0:
			if (fromPt.x < (toPt.x + xsegTo))  {

				int y = 0;
				// "to" node is to right of "from" node, must put an
				// extra kink in the link.  (i.e. 2 more points)

				if (fromPt.y < toPt.y) 				{
					// from pt below to point, route above From node
					if (rectFrom.top < rectTo.bottom) {
						// route half way  between top and bottom
						y = rectTo.bottom + ((rectFrom.top - rectTo.bottom) / 2);
					}
					else {
						// route over tops of both
						y = max(rectFrom.top, rectTo.top) + 10;
					}
            
				}
				else{
					// from pt above to point, route below From node
					if (rectFrom.bottom > rectTo.top) {
						// route half way  between top and bottom
						y = rectFrom.bottom + ((rectTo.top - rectFrom.bottom) / 2);
					}
					else {
						// route below bottoms of both
						y = min(rectFrom.bottom, rectTo.bottom) - 10;
					}
            
				}
				addPoint(CPoint(fromPt.x, y));  // point 3

				fromPt = CPoint(toPt.x+xsegTo, y);
				addPoint(fromPt);         // point 4

			}
			break;
		case 180:  // into the left side of the To node (typical dataflow left-to-right case)
			if (fromPt.x > (toPt.x - xsegTo))  {

				int y = 0;
				// "to" node is to left of "from" node, must put an
				// extra kink in the link.  (i.e. 2 more points)

				if (fromPt.y < toPt.y) 				{
					// from pt below to point, route above From node
					if (rectFrom.top < rectTo.bottom) {
						// route half way  between top and bottom
						y = rectTo.bottom + ((rectFrom.top - rectTo.bottom) / 2);
					}
					else {
						// route over tops of both
						y = max(rectFrom.top, rectTo.top) + 10;
					}
            
				}
				else{
					// from pt above to point, route below From node
					if (rectFrom.bottom > rectTo.top) {
						// route half way  between top and bottom
						y = rectFrom.bottom + ((rectTo.top - rectFrom.bottom) / 2);
					}
					else {
						// route below bottoms of both
						y = min(rectFrom.bottom, rectTo.bottom) - 10;
					}
            
				}
				AddPoint(CPoint(fromPt.x, y));  // point 3

				fromPt = CPoint(toPt.x-xsegTo, y);
				AddPoint(fromPt);         // point 4

			}
			break;
		case 90: // into to the top.
			if (fromPt.y < (toPt.y + ysegTo))  {

				int y = 0;
				// "to" node is above "from" node, must put an
				// extra kink in the link.  (i.e. 2 more points)

				
				// go up the side of the from node
				fromPt = CPoint(fromPt.x, min(rectFrom.top+10, toPt.y + ysegTo));
				AddPoint(fromPt);         // point 

            if (fromPt.x > rectTo.left && fromPt.x < rectTo.right){ 	 // if to node to left
					AddPoint(CPoint(rectTo.left-10, rectFrom.top+10));  // point 
					AddPoint(CPoint(rectTo.left-10, toPt.y + ysegTo));  // point 
				}
				else {
					AddPoint(CPoint(fromPt.x,toPt.y + ysegTo));  // point 
				}

			} else {
				if (fromPt.x > toPt.x) 
					fromPt = CPoint(fromPt.x, toPt.y + ysegTo);
				else
					fromPt = CPoint(toPt.x, fromPt.y); 
				AddPoint(fromPt);         // point 
			}
			break;
		}
	}
   // calculate the point to make the link rectilinear                                   
   cx = cy = 0;
   if (toDir == 0 || toDir == 180) {
	   cx = fromPt.x;
		cy = toPt.y;
	}
   else if (toDir == 90 || toDir == 270) {
		cx = toPt.x;
		cy = fromPt.y;
	}

   AddPoint(CPoint(cx, cy));    
                              
   // now finish up                              
   AddPoint(toPt);
   FinishStroke();
}


//----------------------------------------------------------------------------
void CElectricPortLink::LayoutViewPointImage(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_viewPoint == NULL)
      return;

   CPoint p1 = GetPoint(0);
   CPoint p2 = GetPoint(1);

   CPoint p3;

   p3.x = (p1.x + p2.x)/2+3;
   p3.y = (p1.y + p2.y)/2+3;

   m_viewPoint->SetLocation(p3);

}


//----------------------------------------------------------------------------
void CElectricPortLink::LayoutSplitPointImage(){
//----------------------------------------------------------------------------
	PROC_TRACE;


}


//----------------------------------------------------------------------------
CPoint CElectricPortLink::GetArrowToAnchorPt(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	return GetPoint(NumPoints()-2);
}


//----------------------------------------------------------------------------
CPoint CElectricPortLink::GetArrowFromAnchorPt(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	return GetPoint(1);
}


//----------------------------------------------------------------------------
BOOL CElectricPortLink::HandleResizing(CClientDC *pDC, 
                                       DragDropView   *pView, 
                                       CRect     *pRect, 
                                       CPoint     pPoint, 
                                       int        nHandleHit, 
                                       int        nEvent, int, int) {
//----------------------------------------------------------------------------
   DragDropPort* pPort = NULL;

   CPoint fromPt, toPt;
   int fromDir, toDir;
   
   nHandleHit = nHandleHit-1; // FIXME

   // Es wurde ein eigentlich nicht vorhandener Handle selektiert
   //  - darf eigentlich nie vorkommen
   //
   if(nHandleHit > (HandlesLast+NumPoints()-1))
      return FALSE;

   // fromPt is an x,y to start from.  
   // fromDir is an angle that the first link must 
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
 
   // Es wurde der erste Punkt selectiert 
   // -> neuen Link erzeugen der mit der Maus an einen
   //    neuen Ausgang angehaengt werden kann
   //
   if (nHandleHit == HandlesLast){
      pPort = m_pTo;
      Unlink();
      CPoint point;
      point.x = pPoint.x;
      point.y = pPoint.y;
      pView->StartNewLink(pPort, point);
      return FALSE;
   }
   // Es wurde der letzte Punkt des Link selektiert
   // -> neuen Link erzeugen der mit der Maus an einen 
   //    neuen Eingang angehaengt werden kann
   //
   else if(nHandleHit == (HandlesLast+NumPoints()-1)){
      pPort = m_pFrom;
      Unlink();
      CPoint point;
      point.x = pPoint.x;
      point.y = pPoint.y;
      pView->StartNewLink(pPort, point);
      return FALSE;
   }
   // Es wurde der ERSTE NACH dem STARTPUNKT ausgewaehlt
   // -> Nur der Punkt 'rechts' daneben wird veraendert.
   //
   else if(nHandleHit == (HandlesLast+1)){
      CPoint p0 = GetPoint(0);   // Erster Punkt in der Kette
      CPoint p1 = GetPoint(1);
      CPoint p2 = GetPoint(2);

      // Die Punkte haben eine Anordnung der Art:
      //      p0 +-----+ p1                 + p2
      //               |                    |
      //               |                    |
      //               + p2     p0 +--------+ p1
      if((p1.x == p2.x) && (p0.y == p1.y)){
         switch(fromDir){
         case 0:
            // p0 ist links von p1
            //
            SetPoint(1,(CPoint(max(p0.x+10,pPoint.x), p1.y))); // p1
            SetPoint(2,(CPoint(max(p0.x+10,pPoint.x), p2.y))); // p2
            break;
            // p0 ist rechts von p2
            //
         case 180:
            SetPoint(1,(CPoint(min(p0.x-10,pPoint.x), p1.y))); // p1
            SetPoint(2,(CPoint(min(p0.x-10,pPoint.x), p2.y))); // p2
            break;
         }
      }
      // Die Punkte haben eine Anordnung der Art:
      //      p0 +              p1 +--------+ p2
      //         |                 |
      //         |                 |
      //      p1 +-----+ p2     p0 +
      else{
         switch(fromDir){
         case 90:
            // p0 ist unterhalb von p1
            //
            SetPoint(1,(CPoint(p1.x,min(p0.x-10,pPoint.y)))); // p1
            SetPoint(2,(CPoint(p2.x,min(p0.x-10,pPoint.y)))); // p2
            break;
            // p0 ist oberhalb von p2
            //
         case 270:
            SetPoint(1,(CPoint(p1.x,max(p0.x+10,pPoint.y)))); // p1
            SetPoint(2,(CPoint(p2.x,max(p0.x+10,pPoint.y)))); // p2
            break;
         }
      }
   }
   // Es wurde der ERSTE VOR dem ENDPUNKT ausgewaehlt
   // -> Nur der Punkt 'links' daneben wird veraendert.
   //
   else if(nHandleHit == (HandlesLast+NumPoints()-2)){
      long   count = NumPoints();
      CPoint p2 = GetPoint(count-3);
      CPoint p1 = GetPoint(count-2);
      CPoint p0 = GetPoint(count-1);  // letzter Punkt in der Kette

      // Die Punkte haben eine Anordnung der Art:
      //      p2 +-----* p1                 + p0
      //               |                    |
      //               |                    |
      //               + p0     p2 +--------* p1
      if((p0.x == p1.x) && (p2.y == p1.y)){
         switch(toDir){
         case 90:
            // p0 ist unterhalb von p1
            //
            SetPoint(count - 2,(CPoint(min(p0.x-10,pPoint.x), p1.y))); // p1
            SetPoint(count - 3,(CPoint(min(p0.x-10,pPoint.x), p2.y))); // p2
            break;
            // p0 ist oberhalb von p2
            //
         case 270:
            SetPoint(count - 2,(CPoint(max(p0.x+10,pPoint.x), p1.y))); // p1
            SetPoint(count - 3,(CPoint(max(p0.x+10,pPoint.x), p2.y))); // p2
            break;
         }
      }
      // Die Punkte haben eine Anordnung der Art:
      //      p2 +              p1 *--------+ p0
      //         |                 |
      //         |                 |
      //      p1 *-----+ p0     p2 +
      else{
         switch(toDir){
         case 0:
            // p0 ist links von p1
            //
            SetPoint(count -2,(CPoint(max(p0.x+10,pPoint.x),p1.y))); // p1
            SetPoint(count -3,(CPoint(max(p0.x+10,pPoint.x),p2.y))); // p2
            break;
            // p0 ist rechts von p2
            //
         case 180:
            SetPoint(count -2,(CPoint(min(p0.x-10,pPoint.x),p1.y))); // p1
            SetPoint(count -3,(CPoint(min(p0.x-10,pPoint.x),p2.y))); // p2
            break;
         }
      }
   }
   // Der Punkt ist irgendwo in der Mitte des Links
   // -> Der Link hat MINDESTENS 5 Stuetzpunkte
   //
   else{
      CPoint p_m1= GetPoint(nHandleHit-HandlesLast-2);
      CPoint p0  = GetPoint(nHandleHit-HandlesLast-1);
      CPoint p1  = GetPoint(nHandleHit-HandlesLast);
      CPoint p2  = GetPoint(nHandleHit-HandlesLast+1);
      CPoint p3  = GetPoint(nHandleHit-HandlesLast+2);
      // Die Punkte haben eine Anordnung der Art:
      //
      //               .              .
      //               .              .
      //   p1 *------->+  p0      p0  +<---------* p1
      //      |        .              .          |
      //      |        .              .          |
      //   p2 |                                  | p2
      //   ...+...                         ......+.....
      //
      if((p1.x== p2.x) && (p1.y == p0.y)){
         // p_m1 ist der Startpunkt
         // p0 sollte in der Richtung liegen, in der der Startpunkt zeigt
         //
         if(nHandleHit-HandlesLast-2 == 0) {
            switch(fromDir){
            case 0:
               SetPoint(nHandleHit-HandlesLast-1,CPoint(p0.x,max(pPoint.y,p_m1.y-10)));     // p0
               SetPoint(nHandleHit-HandlesLast  ,CPoint(pPoint.x,max(pPoint.y,p_m1.y-10))); // p1
               SetPoint(nHandleHit-HandlesLast+1,CPoint(pPoint.x,p2.y));                    // p2
               break;
            case 180:
               SetPoint(nHandleHit-HandlesLast-1,CPoint(p0.x,min(pPoint.y,p_m1.y+10)));     // p0
               SetPoint(nHandleHit-HandlesLast  ,CPoint(pPoint.x,min(pPoint.y,p_m1.y+10))); // p1
               SetPoint(nHandleHit-HandlesLast+1,CPoint(pPoint.x,p2.y));                    // p2
               break;
            default:
               break;
               // TODO
            }
         }
         // p3 ist der Endpunkt
         //
         else if((nHandleHit-HandlesLast-NumPoints()+3) == 0) {
            switch(toDir){
            case 0:
               SetPoint(nHandleHit-HandlesLast-1,CPoint(p0.x,pPoint.y));     // p0
               SetPoint(nHandleHit-HandlesLast  ,CPoint(max(pPoint.x,p3.x+10),pPoint.y)); // p1
               SetPoint(nHandleHit-HandlesLast+1,CPoint(max(pPoint.x,p3.x+10),p2.y));                    // p2
               break;
            case 180:
               SetPoint(nHandleHit-HandlesLast-1,CPoint(p0.x,pPoint.y));     // p0
               SetPoint(nHandleHit-HandlesLast  ,CPoint(min(pPoint.x,p3.x-10),pPoint.y)); // p1
               SetPoint(nHandleHit-HandlesLast+1,CPoint(min(pPoint.x,p3.x-10),p2.y));                    // p2
               break;
            }
         }
         else{
            SetPoint(nHandleHit-HandlesLast-1,CPoint(p0.x,pPoint.y));   // p0
            SetPoint(nHandleHit-HandlesLast  ,pPoint);                    // p1
            SetPoint(nHandleHit-HandlesLast+1,CPoint(pPoint.x,p2.y));   // p2
         }
      }
      // Die Punkte haben eine Anordnung der Art:
      //
      //  ...+...                            ...+...
      //  p0 |                        .         | p0
      //     |          .             .         |         
      //     |          .             .         |        
      //  p1 *----------+ p2      p2  +---------* p1 
      //                .             .                    
      //                .             .                    
      else if((p0.x == p1.x) &&(p1.y==p2.y)){
         // p_m1 ist der Startpunkt
         // p0 sollte in der Richtung liegen, in der der Startpunkt zeigt
         //
         if(nHandleHit-HandlesLast-2 == 0) {
            switch(fromDir){
            case 0:
               SetPoint(nHandleHit-HandlesLast-1,CPoint(max(pPoint.x,p_m1.x+10),p0.y));     // p0
               SetPoint(nHandleHit-HandlesLast  ,CPoint(max(pPoint.x,p_m1.x+10),pPoint.y)); // p1
               SetPoint(nHandleHit-HandlesLast+1,CPoint(p2.x,pPoint.y));                    // p2
               break;
            case 180:
               SetPoint(nHandleHit-HandlesLast-1,CPoint(min(pPoint.x,p_m1.x-10),p0.y));     // p0
               SetPoint(nHandleHit-HandlesLast  ,CPoint(min(pPoint.x,p_m1.x-10),pPoint.y)); // p1
               SetPoint(nHandleHit-HandlesLast+1,CPoint(p2.x,pPoint.y));                    // p2
               break;
            }
         }
         // p3 ist der Endpunkt
         //
         else if((nHandleHit-HandlesLast-NumPoints()+3) == 0) {
            switch(toDir){
            case 0:
               SetPoint(nHandleHit-HandlesLast-1,CPoint(p0.x,min(pPoint.y,p3.y+10)));     // p0
               SetPoint(nHandleHit-HandlesLast  ,CPoint(pPoint.x,min(pPoint.y,p3.y+10))); // p1
               SetPoint(nHandleHit-HandlesLast+1,CPoint(pPoint.x,p2.y));                    // p2
               break;
            case 180:
               SetPoint(nHandleHit-HandlesLast-1,CPoint(p0.x,max(pPoint.y,p3.y-10)));     // p0
               SetPoint(nHandleHit-HandlesLast  ,CPoint(pPoint.x,max(pPoint.y,p3.y-10))); // p1
               SetPoint(nHandleHit-HandlesLast+1,CPoint(pPoint.x,p2.y));                    // p2
               break;
            }
         }
         else{
            SetPoint(nHandleHit-HandlesLast-1,CPoint(pPoint.x,p0.y)); // p0
            SetPoint(nHandleHit-HandlesLast  ,pPoint);                // p1
            SetPoint(nHandleHit-HandlesLast+1,CPoint(p2.x,pPoint.y)); // p2
         }
      }
   }  


   // Die Leitungsfuehrung wurde mit Hand veraendert
   // -> Es darf spaeter kein vollstaendiges Autorouting mehr
   // gemacht werden.
   //
   m_routingHasChanged = true;

   // Das Image des ViewPoints an die neue Leitungsfuehrung anpassen
   //
   LayoutViewPointImage();

   return FALSE;   // don't let the view draw the XOR'd rectangle    
}


//----------------------------------------------------------------------------
void CElectricPortLink::GainedSelection(DragDropSelection* pSelection){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Falls die Leitung und ein Port selektiert ist MUSS auch der zweite
   // Port selektiert werden da sonst beim DragDrop des Port mit der Leitung
   // Fehler auftretten
   // Der Fehler zeigt sich darin, dass die Leitung sich von dem nicht
   // selektierten Objekt weg bewegt falls man ein DragDrop einleitet.
   //
   if(pSelection->IsInSelection(m_pFrom->GetParent())){
      pSelection->ExtendSelection(m_pTo->GetParent());
   }

   if(pSelection->IsInSelection(m_pTo->GetParent())){
      pSelection->ExtendSelection(m_pFrom->GetParent());
   }

	SetSelected(true);

   // its time to set resize handles
   //
   CPoint point;
   for (int i=0; i < NumPoints(); i++){
       point = GetPoint(i);
       pSelection->CreateResizeHandle (this, point.x, point.y, i + HandlesLast+1, TRUE);
   }  
}


//----------------------------------------------------------------------------
void CElectricPortLink::LostSelection(DragDropSelection* pSelection){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetSelected(false);
	inherited::LostSelection(pSelection);
}



//----------------------------------------------------------------------------
int  CElectricPortLink::GetFirstPickPoint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return 0;
}


//----------------------------------------------------------------------------
int  CElectricPortLink::GetLastPickPoint(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return NumPoints();
}


//----------------------------------------------------------------------------
CLogicValue  CElectricPortLink::GetValue(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CElectricPort *pTo   = (CElectricPort*)GetToPort();
   CElectricPort *pFrom = (CElectricPort*)GetFromPort();

   if (pFrom->IsOutput() && pTo->IsInput())	{
      return pFrom->GetValue();
	}
	else if(pFrom->IsInput() && pTo->IsOutput())	{
      return pTo->GetValue();
	}

   return pTo->GetValue();
}


//----------------------------------------------------------------------------
void CElectricPortLink::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

   if (ar.IsStoring()){
      ar << m_version;
      ar << m_viewPoint;  
      ar << m_osziStroke;
   }
   else{
       int version;
       ar >> version;

       switch (version){
       case 1:
           break;
       case 2:
           ar >> m_viewPoint;
           ar >> m_osziStroke;
           break;
       default:
           LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
           break;
       }
    }
}


//----------------------------------------------------------------------------
void CElectricPortLink::SetOsziStroke(COsziStroke *stroke){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m_osziStroke!= NULL){
      delete m_osziStroke;
      m_osziStroke = NULL;
   }
   m_osziStroke = stroke;

   if(m_viewPoint!= NULL){
      delete m_viewPoint;
      m_viewPoint = NULL;
   }

   // Set the first Initial value
   // The stroke must have one value to calculate his position
   // in the osziView.
   // 
   if(m_osziStroke !=NULL){
      m_osziStroke->Set(((CElectricPort*)GetFromPort())->GetValue());
      m_viewPoint = new CViewPoint(this ,CPoint(100,100));
      // Wichtig!!!!
      // Das Image muss nach den derzeit im Speicher stehenden
      // Objekten angehaengt werde.
      // Beim zerstoeren des Dokuments wird somit erst der Destructor
      // des Links aufgerufen. Dieser zerstoert das Image und traegt es
      // somit aus dem Dokument aus. Falls erst das Image geloescht wird,
      // bekommt dies der Link nicht mit, und das Image wird zwei mal
      // zerstoert -> core
      //
      //GetDocument()->AddObjectAtHead(m_viewPointImage);
      GetDocument()->AddObjectAtTail(m_viewPoint);
      LayoutViewPointImage();
      m_viewPoint->SetLabel(TRANSLATE("ViewPoint"));
   }

}

//----------------------------------------------------------------------------
void CElectricPortLink::SetOsziStrokeString(const CString& label){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_osziStroke != NULL);

   m_osziStroke->SetLabel(label);
}

//----------------------------------------------------------------------------
void CElectricPortLink::DoCalculate(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CElectricPort *pTo   = (CElectricPort*)m_pTo;
   CElectricPort *pFrom = (CElectricPort*)m_pFrom;
   
	if (pFrom->IsOutput() && pTo->IsInput())	{
	  m_currentValue = pFrom->GetValue();
      pTo->SetValue(m_currentValue);
	}
	else/* if(pFrom->IsInput() && pTo->IsOutput())*/	{
	  m_currentValue = pTo->GetValue();
      pFrom->SetValue(m_currentValue);
	}

	SetPenColor(m_currentValue.IsHigh()?RGB(255,0,0):RGB(0,0,255));

   // an dieser stelle braucht man nicht mehr pruefen
   // ob es sich wirklich um den Input handelt, da jetzt
   // Input und Output sowieso den gleichen Wert haben
   //
   if(m_osziStroke != NULL)
      m_osziStroke->Set(pFrom->GetValue());
}


