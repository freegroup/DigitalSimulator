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
#include "ElectricNodeContextBCDtoDEZ.h"
#include "Application\Debug\LogManager.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
IMPLEMENT_REGISTER(CElectricNodeContextBCDtoDEZ);

//----------------------------------------------------------------------------
CElectricNodeContextBCDtoDEZ::CElectricNodeContextBCDtoDEZ(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void CElectricNodeContextBCDtoDEZ::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;
   assert(data.inPorts.GetSize()>=4);
   assert(data.outPorts.GetSize()>=10);

   int e =  (data.inPorts[0]->IsHigh()?1:0) +
            (data.inPorts[1]->IsHigh()?2:0) +
            (data.inPorts[2]->IsHigh()?4:0) +
            (data.inPorts[3]->IsHigh()?8:0);

   data.outPorts[0]->SetValue(CLogicValue::Low);
   data.outPorts[1]->SetValue(CLogicValue::Low);
   data.outPorts[2]->SetValue(CLogicValue::Low);
   data.outPorts[3]->SetValue(CLogicValue::Low);
   data.outPorts[4]->SetValue(CLogicValue::Low);
   data.outPorts[5]->SetValue(CLogicValue::Low);
   data.outPorts[6]->SetValue(CLogicValue::Low);
   data.outPorts[7]->SetValue(CLogicValue::Low);
   data.outPorts[8]->SetValue(CLogicValue::Low);
   data.outPorts[9]->SetValue(CLogicValue::Low);

   if(e<=9)
      data.outPorts[e]->SetValue(CLogicValue::High);
}
