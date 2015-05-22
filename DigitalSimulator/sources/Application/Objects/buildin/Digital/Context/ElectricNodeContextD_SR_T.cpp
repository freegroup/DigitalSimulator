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
#include "ElectricNodeContextD_SR_T.h"
#include "Application\Debug\LogManager.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
IMPLEMENT_REGISTER(CElectricNodeContextD_SR_T);

//----------------------------------------------------------------------------
CElectricNodeContextD_SR_T::CElectricNodeContextD_SR_T(){
//----------------------------------------------------------------------------
	PROC_TRACE;


}

//-----------------------------------------------------------------------------
void CElectricNodeContextD_SR_T::InitInputPorts(CElectricNode::CElectricNodeDokument& data)
//-----------------------------------------------------------------------------
{
   // call the base class
   //
   CElectricNodeContext::InitInputPorts(data);

   // and invert the Reset and Set input
   //
   assert(data.inPorts.GetSize()>=4);
   data.inPorts[0]->SetInverter(true);
   data.inPorts[3]->SetInverter(true);
}

//----------------------------------------------------------------------------
void CElectricNodeContextD_SR_T::InitOutputPorts(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // call the base class
   //
   CElectricNodeContext::InitOutputPorts(data);

   // and invert the Reset and Set input
   //
   assert(data.outPorts.GetSize()>=2);
   data.outPorts[1]->SetInverter(true);
}


//----------------------------------------------------------------------------
void CElectricNodeContextD_SR_T::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.inPorts.GetSize()>=4);
   assert(data.outPorts.GetSize()>=2);

   if(data.inPorts[0]->IsHigh()){      // Set
      data.outPorts[0]->SetValue(CLogicValue::High);
      data.outPorts[1]->SetValue(CLogicValue::High); // Is an inverter Port
   }
   else if(data.inPorts[3]->IsHigh()){ // Reset
      data.outPorts[0]->SetValue(CLogicValue::Low);
      data.outPorts[1]->SetValue(CLogicValue::Low); // Is an inverter Port
   }
   else if(data.inPorts[2]->IsHigh() && data.inPorts[2]->HasValueChanged() ){
      data.outPorts[0]->SetValue(data.inPorts[1]->GetValue());
      data.outPorts[1]->SetValue(data.inPorts[1]->GetValue()); // Is an inverter Port
   }
}
