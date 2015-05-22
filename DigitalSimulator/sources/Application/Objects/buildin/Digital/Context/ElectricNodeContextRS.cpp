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

#pragma warning(disable : 4786)
#include "stdafx.h"
#include "Application\DigitalSimulatorApp.h"
#include "ElectricNodeContextRS.h"


IMPLEMENT_REGISTER(CElectricNodeContextRS);
//-----------------------------------------------------------------------------
CElectricNodeContextRS::CElectricNodeContextRS(){
//-----------------------------------------------------------------------------
	PROC_TRACE;

}

//-----------------------------------------------------------------------------
void CElectricNodeContextRS::InitOutputPorts(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::InitOutputPorts(data);

   // and invert the Reset input
   //
   assert(data.outPorts.GetSize()>=2);
   data.outPorts[1]->SetInverter(true);
}

//-----------------------------------------------------------------------------
void CElectricNodeContextRS::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.inPorts.GetSize()>=2);
   assert(data.outPorts.GetSize()>=2);

   if(data.inPorts[0]->IsLow() && data.inPorts[1]->IsHigh()) {
      data.outPorts[0]->SetValue(CLogicValue::Low);
   }
   else if(data.inPorts[0]->IsHigh() && data.inPorts[1]->IsLow()) {
      data.outPorts[0]->SetValue(CLogicValue::High);
   }

   data.outPorts[1]->SetValue(data.outPorts[0]->GetValue()); // Note: the output #2 is an inverter Port
}
