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
#include "Application\Objects\buildin\digital\ElectricNode.h"
#include "Application\Dialogs\ObjectDialogs\DialogDividerParam.h"

#include "ElectricNodeContextDivider.h"


IMPLEMENT_REGISTER(CElectricNodeContextDivider);
//----------------------------------------------------------------------------
CElectricNodeContextDivider::CElectricNodeContextDivider(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}


//----------------------------------------------------------------------------
void CElectricNodeContextDivider::Initialize(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

    inherited::Initialize(data);

    // sicherstellen, dass niemals der Faktor <=0 wird
    //
    data.param[DivideRation]=max(1,data.param[DivideRation]);
}


//----------------------------------------------------------------------------
void CElectricNodeContextDivider::onOption(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;


   CDialogDividerParam d(NULL);

   d.m_faktor = data.param[DivideRation];
   if(d.DoModal()==IDOK) {
       data.param[DivideRation] = max(1,d.m_faktor);
   }
}


//----------------------------------------------------------------------------
void CElectricNodeContextDivider::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.inPorts.GetSize()>=1);
   assert(data.outPorts.GetSize()>=1);

   if(data.inPorts[0]->HasValueChanged() ){
      data.param[CurrentState]++;
	   if(data.param[CurrentState]>=data.param[DivideRation]){
          data.outPorts[0]->ToggleValue();
		    data.param[CurrentState]  = 0;
      }
   }
}

