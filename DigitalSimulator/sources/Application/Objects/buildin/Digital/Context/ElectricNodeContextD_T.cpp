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
#include "ElectricNodeContextD_T.h"


IMPLEMENT_REGISTER(CElectricNodeContextD_T);
//----------------------------------------------------------------------------
CElectricNodeContextD_T::CElectricNodeContextD_T(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void CElectricNodeContextD_T::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;
   assert(data.inPorts.GetSize()>=2);
   assert(data.outPorts.GetSize()>=2);

   if(data.inPorts[1]->IsHigh() && data.inPorts[1]->HasValueChanged() ){
      data.outPorts[0]->SetValue(data.inPorts[0]->GetValue());
      data.outPorts[1]->SetValue(data.inPorts[0]->GetValue()); // Note: is an inverter port
   }
}

//-----------------------------------------------------------------------------
void CElectricNodeContextD_T::InitOutputPorts(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::InitOutputPorts(data);

   // and invert the Reset input
   //
   assert(data.outPorts.GetSize()>=2);
   data.outPorts[1]->SetInverter(true);
}

//----------------------------------------------------------------------------
void CElectricNodeContextD_T::LayoutInput(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.icons.GetSize() >=1 );

   long elements      = data.inPorts.GetSize();

   CPoint  topLeft    = data.icons[0]->GetBoundingRect().TopLeft();

   // Die ganzen InputPunkte ein bischen nach oben verschieben
   //
   float   yOffset = data.icons[0]->GetBoundingRect().Height() / (float)(elements+2);

   for(long loop=0 ;loop <elements  ; loop++){
      int xPos = topLeft.x;
      int yPos = (int)(topLeft.y+(yOffset*(loop+1)));

      data.inPorts[loop]->SetSpotLocation(DragDropObject::spotRightCenter,xPos,yPos);
   }
}
