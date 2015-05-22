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
#include "Application\Dialogs\ObjectDialogs\DialogMultiplexerParam.h"
#include "Application\Debug\LogManager.h"

#include "ElectricNodeContextMultiplexer.h"


IMPLEMENT_REGISTER(CElectricNodeContextMultiplexer);
//----------------------------------------------------------------------------
CElectricNodeContextMultiplexer::CElectricNodeContextMultiplexer(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}


//----------------------------------------------------------------------------
void  CElectricNodeContextMultiplexer::AdjustInputOutputCount(int &inCount, int &outCount){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // ein demultiplexer hat genau einen Ausgang
   //
   outCount = 1;

   // und mehrere Eingänge 
   // mögliche Werte sind 
   // 3   => 2  Datenleitungen & 1 Addressleitung 
   // 6   => 4  Datenleitungen & 2 Addressleitungen
   // 11  => 8  Datenleitungen & 3 Addressleitungen
   // 20  => 16 Datenleitungen & 4 Addressleitungen
   if(inCount <3){
      inCount = 3;
   }
   else if(inCount <6){
      inCount = 6;
   }
   else if(inCount <11){
      inCount = 11;
   }
   else /*if(inCount <20)*/{
      inCount = 20;
   }
}


//-----------------------------------------------------------------------------
void CElectricNodeContextMultiplexer::LayoutInput(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   
   long elements      = data.inPorts.GetSize();
   CPoint  topLeft    = data.icons[0]->GetBoundingRect().TopLeft();
   CPoint  bottomRight= data.icons[0]->GetBoundingRect().BottomRight();

   float   yOffset = data.icons[0]->GetBoundingRect().Height() / (float)(data.param[inputCount]+1);
   float   xOffset = data.icons[0]->GetBoundingRect().Width()  / (float)(data.param[addressCount]+1);

   // Eingänge plazieren
   //
   for(long loop=0 ;loop <data.param[inputCount] ; loop++)   {
      int xPos = topLeft.x;
      int yPos = (int)(topLeft.y+(yOffset*(loop+1)));

      data.inPorts[loop]->SetSpotLocation(DragDropObject::spotRightCenter,xPos,yPos);
   }

   // Adresspunkte  plazieren
   //
   for( loop=0 ;loop < data.param[addressCount]; loop++)   {
      int yPos = bottomRight.y - (xOffset*(loop));
      int xPos = (int)(topLeft.x+(xOffset*(loop+1)));

      data.inPorts[data.param[inputCount]+loop]->SetSpotLocation(DragDropObject::spotTopCenter,xPos,yPos);
   }
}

//-----------------------------------------------------------------------------
void CElectricNodeContextMultiplexer::SetInputCount( CElectricNode::CElectricNodeDokument& data, long count){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   if(count ==3){
      data.param[addressCount] = 1;
      data.param[inputCount]   = 2 ;
   }
   else if(count ==6){
      data.param[addressCount] = 2;
      data.param[inputCount]   = 4 ;
   }
   else if(count ==11){
      data.param[addressCount] = 3;
      data.param[inputCount]   = 8 ;
   }
   else if(count ==20){
      data.param[addressCount] = 4;
      data.param[inputCount]   = 16 ;
   }
   else
      assert(FALSE);

   data.inCount= count;
}


//-----------------------------------------------------------------------------
void CElectricNodeContextMultiplexer::SetOutputCount(CElectricNode::CElectricNodeDokument& data, long count){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   //data.param[addressCount] = count-1;
   data.outCount= count;
}


//-----------------------------------------------------------------------------
void CElectricNodeContextMultiplexer::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   int address = 0;
   long loop =0;

   // Adresse ermitteln
   //
	for (loop =data.param[inputCount]; loop<data.param[addressCount]+data.param[inputCount]; loop++)   {
      if(data.inPorts[loop]->IsHigh()){
         address += pow(2,loop-data.param[inputCount]);
      }
   }

   assert(address <  data.param[inputCount]);
   assert(address <  data.inPorts.GetSize());
   assert(address >= 0);

   for( loop=0 ;loop <data.outPorts.GetSize() ; loop++) {
      data.outPorts[loop]->SetValue(data.inPorts[address]->GetValue());
   }
}

//----------------------------------------------------------------------------
void CElectricNodeContextMultiplexer::onOption(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CDialogMultiplexerParam d(NULL,data);

   if(d.DoModal()==IDOK){
      data.param[addressCount] = d.m_addressCount;
      data.param[inputCount]   = d.m_inputCount ;
      Initialize(data);
   }
}
