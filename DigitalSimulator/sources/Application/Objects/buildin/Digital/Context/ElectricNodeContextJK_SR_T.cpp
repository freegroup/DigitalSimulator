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
#include "ElectricNodeContextJK_SR_T.h"
#include "Application\Debug\LogManager.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
IMPLEMENT_REGISTER(CElectricNodeContextJK_SR_T);

//-----------------------------------------------------------------------------
CElectricNodeContextJK_SR_T::CElectricNodeContextJK_SR_T(){
//-----------------------------------------------------------------------------
	PROC_TRACE;

}


//-----------------------------------------------------------------------------
void CElectricNodeContextJK_SR_T::InitInputPorts(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   // call the base class
   //
   inherited::InitInputPorts(data);

   // and invert the Reset input
   //
   assert(data.inPorts.GetSize()>=5);
   data.inPorts[0]->SetInverter(true);
   data.inPorts[4]->SetInverter(true);
}

//-----------------------------------------------------------------------------
void CElectricNodeContextJK_SR_T::InitOutputPorts(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   // call the base class
   //
   inherited::InitOutputPorts(data);

   // and invert the Reset input
   //
   assert(data.outPorts.GetSize()>=2);
   data.outPorts[1]->SetInverter(true);
}

//-----------------------------------------------------------------------------
void CElectricNodeContextJK_SR_T::LayoutInput(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::LayoutInput(data);

   assert(data.inPorts.GetSize()>=5);

   CPoint  topLeft = data.icons[0]->GetBoundingRect().TopLeft();

   long  xPos = topLeft.x;
   long  yPos;

   yPos = topLeft.y - 8 ;
   data.inPorts[0]->SetSpotLocation(DragDropObject::spotTopRight,xPos,yPos);

   yPos = topLeft.y + data.icons[0]->GetBoundingRect().Height() +16;
   data.inPorts[4]->SetSpotLocation(DragDropObject::spotRightCenter,xPos,yPos);
}


//-----------------------------------------------------------------------------
void CElectricNodeContextJK_SR_T::LayoutOutput(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.outPorts.GetSize()>=2);

   long   elements_in  = data.inPorts.GetSize();
   long   elements     = data.outPorts.GetSize();
   CPoint topRight  = data.icons[0]->GetBoundingRect().TopLeft() + CPoint( data.icons[0]->GetBoundingRect().Width(),0);

   float   yOffset = data.icons[0]->GetBoundingRect().Height() / (float)(elements_in+1);

   int xPos = topRight.x;
   int yPos = (int)(topRight.y + (yOffset*2));
   data.outPorts[0]->SetSpotLocation(DragDropObject::spotLeftCenter,xPos,yPos);
   yPos = (int)(topRight.y+(yOffset*4));
   data.outPorts[1]->SetSpotLocation(DragDropObject::spotLeftCenter,xPos,yPos);

}

//-----------------------------------------------------------------------------
void CElectricNodeContextJK_SR_T::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.inPorts.GetSize()>=5);
   assert(data.outPorts.GetSize()>=2);

   if(data.inPorts[0]->IsHigh()) {       // Set
      data.outPorts[0]->SetValue(CLogicValue::High);
      data.outPorts[1]->SetValue(CLogicValue::High); // Note: is an inverter port
   }
   else if(data.inPorts[4]->IsHigh()) { // Reset
      data.outPorts[0]->SetValue(CLogicValue::Low);
      data.outPorts[1]->SetValue(CLogicValue::Low); // Note: is an inverter port
   }
   else {                               // normal DoCalculate
      if(data.inPorts[2]->IsHigh() && data.inPorts[2]->HasValueChanged() ) {
         if(data.inPorts[1]->IsLow() && data.inPorts[3]->IsHigh()){
            data.outPorts[0]->SetValue(CLogicValue::Low);
         }
         else if(data.inPorts[1]->IsHigh() && data.inPorts[3]->IsLow()){
            data.outPorts[0]->SetValue(CLogicValue::High);
         }
         else if(data.inPorts[1]->IsHigh() && data.inPorts[3]->IsHigh()){
            data.outPorts[0]->ToggleValue();
         }
      }
      data.outPorts[1]->SetValue(data.outPorts[0]->GetValue()); // Note: is an inverter port
   }
}
