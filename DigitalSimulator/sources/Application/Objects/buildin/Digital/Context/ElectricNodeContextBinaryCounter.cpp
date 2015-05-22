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
#include "ElectricNodeContextBinaryCounter.h"



IMPLEMENT_REGISTER(CElectricNodeContextBinaryCounter);
//----------------------------------------------------------------------------
CElectricNodeContextBinaryCounter::CElectricNodeContextBinaryCounter(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}


//-----------------------------------------------------------------------------
void CElectricNodeContextBinaryCounter::InitIcon(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.pOwner != NULL);

   data.size     = CSize(200,0);
   long loop;

   // Alle zuvor angelegten Icons erst einmal loeschen
   //
   for( loop=0 ;loop <data.icons.GetSize() ; loop++) {
      delete data.icons[loop];
   }
   data.icons.RemoveAll();

   // Neue Icons anlegen
   //
   // der Kopf des Zaehlers
   //
   data.icons.SetAtGrow(0, new DragDropMetaFile(data.location, data.size, GetIconName(data), TRUE));
   data.icons[0]->SetSelectable(FALSE);
   data.pOwner->AddChildAtHead(data.icons[0]); 

   // Die Teilelemente fuer jedes Bit des Zaehlers
   //
   long elements  = data.outPorts.GetSize();

   for ( loop = 1 ; loop<(elements+1) ; loop++){
      if(data.icons[loop])
         delete data.icons[loop];
      data.icons.SetAtGrow(loop, 
                           new DragDropMetaFile(data.location, 
                           data.size,
                           WMF_PATH("OBJ_counterelement.wmf"), 
                           TRUE));
      data.icons[loop]->SetSelectable(FALSE);
      data.pOwner->AddChildAtHead(data.icons[loop]); 
   }
}

//-----------------------------------------------------------------------------
void CElectricNodeContextBinaryCounter::reset(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
   for(int loop=0 ;loop <data.outPorts.GetSize() ; loop++){
       data.outPorts[loop]->SetValue(CLogicValue::Low);
   }
   data.param[CurrentValue] = 0;
}

//-----------------------------------------------------------------------------
void CElectricNodeContextBinaryCounter::LayoutOutput(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
   long elements       = data.outPorts.GetSize();

   assert(data.outPorts.GetSize()>=  elements   );
   assert(data.icons.GetSize()   >= (elements+1));

   for(long loop=0 ;loop <elements ; loop++) {
      data.icons[loop+1]->SetSpotLocation(DragDropObject::spotTopCenter,
                                           data.icons[loop],
                                           DragDropObject::spotBottomCenter);
      data.outPorts[loop]->SetSpotLocation(DragDropObject::spotLeftCenter,
                                           data.icons[loop+1],
                                           DragDropObject::spotRightCenter);
   }
}


//-----------------------------------------------------------------------------
void CElectricNodeContextBinaryCounter::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
   assert(data.inPorts.GetSize()>=2);
   assert(data.outPorts.GetSize()>=1);

    if(data.inPorts[1]->IsLow()==true){
       // Nur den Wert erhoehen, falls der Eingang eine positive Flanke hat
       //
       if(data.inPorts[0]->HasValueChanged() && data.inPorts[0]->IsHigh()==true){

          long loop;
          bool carry;
          int  elements = data.outPorts.GetSize();

          // zu dem ersten Bit des Zaehlers 1 addieren (=toggle ..1+1=0 )
          //
          data.outPorts[0]->ToggleValue();
          // Falls der Wert jetzt auf 0 steht, hat es einen
          // Ueberlauf bei diesem bit gegeben
          //
          carry = data.outPorts[0]->GetValue().IsLow();
          for(loop=1 ;loop <elements ; loop++) {
             // falls es keinen Uberlauf bei der 'addition'
             // zuvor gegeben hat kann die schleife verlassen werden.
             //
             if(carry==false)
                break;

             // den Uberlauf zu dem naechsten bit 'addieren'
             //
             data.outPorts[loop]->ToggleValue();
             // ... und feststellen ob es wieder ein ueberlauf
             // gegeben hat
             //
             carry = data.outPorts[loop]->GetValue().IsLow();
          }
		  // gesetzten wert ermitteln, damit andere Zähler (BCD) darauf
		  // zugreifen können
		  //
          long value = 1;
          int  x=0;
		  //data.param[CurrentValue]=0;
          for(loop=0 ;loop <elements ; loop++) {
             if(data.outPorts[loop]->GetValue().IsHigh())
				 x = x +value;
                //data.param[CurrentValue] = data.param[CurrentValue] +  value;
             value = value << 1; 
          }
		  data.param[CurrentValue]=x;
       }
    }
    else {
       reset(data);
    }
}