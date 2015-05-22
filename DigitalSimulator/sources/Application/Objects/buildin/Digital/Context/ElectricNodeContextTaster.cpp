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
#include "Application\Dialogs\ObjectDialogs\DialogTasterParam.h"

#include "ElectricNodeContextTaster.h"

IMPLEMENT_REGISTER(CElectricNodeContextTaster);
//----------------------------------------------------------------------------
CElectricNodeContextTaster::CElectricNodeContextTaster(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}


//----------------------------------------------------------------------------
void CElectricNodeContextTaster::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(data.param[CurrentState]==1)
	   data.outPorts[0]->SetValue(data.inPorts[0]->GetValue());
   else
	   data.outPorts[0]->SetValue(CLogicValue::Low);
}

//-----------------------------------------------------------------------------
CString CElectricNodeContextTaster::GetIconName(CElectricNode::CElectricNodeDokument& data)const{
//-----------------------------------------------------------------------------
	PROC_TRACE;


   if(data.param[CurrentState]==1)
      return WMF_PATH(data.key+"on.wmf");
   else
      return WMF_PATH(data.key+"off.wmf");
}


//-----------------------------------------------------------------------------
void CElectricNodeContextTaster::OnLButtonUp(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;


   data.param[CurrentState] = data.param[DefaultState];
}

//-----------------------------------------------------------------------------
void CElectricNodeContextTaster::OnLButtonDown(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;


   data.param[CurrentState] = 1-data.param[DefaultState];
}


//-----------------------------------------------------------------------------
void CElectricNodeContextTaster::OnGeometryChange(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   data.param[CurrentState] = data.param[DefaultState];
}

//----------------------------------------------------------------------------
void CElectricNodeContextTaster::onOption(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CDialogTasterParam d(NULL,data);

   if(d.DoModal()==IDOK){
      data.param[CurrentState] = data.param[DefaultState];
      selectIcon(data);
   }
}
