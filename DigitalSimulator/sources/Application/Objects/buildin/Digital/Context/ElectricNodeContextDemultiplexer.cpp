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

#include "math.h"
#include "stdafx.h"

#include "Application\Objects\buildin\digital\ElectricNode.h"
#include "Application\Dialogs\ObjectDialogs\DialogDemultiplexerParam.h"
#include "Application\Debug\LogManager.h"

#include "ElectricNodeContextDemultiplexer.h"


IMPLEMENT_REGISTER(CElectricNodeContextDemultiplexer);
//----------------------------------------------------------------------------
CElectricNodeContextDemultiplexer::CElectricNodeContextDemultiplexer(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void  CElectricNodeContextDemultiplexer::AdjustInputOutputCount(int &inCount, int &outCount){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Ein demultiplexer hat einen Eingang und mehrere Addressleitungen
   // Die Anzahl der Ausgänge wird durch die Anzahl der Addressleitungen
   // bestimmt
   //
   outCount =  (int)pow(2,inCount-1);
}

//-----------------------------------------------------------------------------
void CElectricNodeContextDemultiplexer::LayoutInput(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   CPoint  topLeft    = data.icons[0]->GetBoundingRect().TopLeft();
   CPoint  bottomRight= data.icons[0]->GetBoundingRect().BottomRight();

   float   xOffset = data.icons[0]->GetBoundingRect().Width()  / (float)(data.param[addressCount]+1);

   // Eingang plazieren
   //
   long xPos = topLeft.x;
   long yPos = topLeft.y+ data.icons[0]->GetBoundingRect().Height()/2;
   data.inPorts[0]->SetSpotLocation(DragDropObject::spotRightCenter,xPos,yPos);

   // Adresspunkte  plazieren
   //
   for(int loop=0 ;loop < data.param[addressCount]; loop++)   {
      yPos = bottomRight.y - (xOffset*(loop));
      xPos = (int)(topLeft.x+(xOffset*(loop+1)));
      assert((loop+1) < data.inPorts.GetSize() );
      data.inPorts[1+loop]->SetSpotLocation(DragDropObject::spotTopCenter,xPos,yPos);
   }
}
//-----------------------------------------------------------------------------
void CElectricNodeContextDemultiplexer::SetInputCount( CElectricNode::CElectricNodeDokument& data, long count){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   data.param[addressCount] = count-1;
   data.inCount= count;
}


//-----------------------------------------------------------------------------
void CElectricNodeContextDemultiplexer::SetOutputCount(CElectricNode::CElectricNodeDokument& data, long count){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   if(count ==2){
      data.param[addressCount] = 1;
   }
   else if(count ==4){
      data.param[addressCount] = 2;
   }
   else if(count ==8){
      data.param[addressCount] = 3;
   }
   else if(count ==16){
      data.param[addressCount] = 4;
   }
   else
      assert(FALSE);

   data.param[outputCount]  = count;
   data.outCount= count;
}

//-----------------------------------------------------------------------------
void CElectricNodeContextDemultiplexer::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   int address = 0;
   long loop =0;

   // Adresse ermitteln
   //
	for (loop =1; loop<data.param[addressCount]+1; loop++)   {
      if(data.inPorts[loop]->IsHigh()){
         address += pow(2,loop-1);
      }
   }

   assert(address <  data.param[outputCount]);
   assert(address >= 0);

   for( loop=0 ;loop <data.outPorts.GetSize() ; loop++) {
      if(address==loop)
         data.outPorts[loop]->SetValue(data.inPorts[0]->GetValue());
      else
         data.outPorts[loop]->SetValue(CLogicValue::Low);
   }
}

//----------------------------------------------------------------------------
void CElectricNodeContextDemultiplexer::onOption(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CDialogDemultiplexerParam d(NULL,data);

   if(d.DoModal()==IDOK){
      data.param[addressCount]  = d.m_addressCount;
      data.param[outputCount]   = d.m_outputCount ;
      Initialize(data);
   }
}
