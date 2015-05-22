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
#include "ElectricNodeContextBinaryDisplay.h"


IMPLEMENT_REGISTER(CElectricNodeContextBinaryDisplay);
//----------------------------------------------------------------------------
CElectricNodeContextBinaryDisplay::CElectricNodeContextBinaryDisplay(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}


//-----------------------------------------------------------------------------
CString CElectricNodeContextBinaryDisplay::GetIconName(CElectricNode::CElectricNodeDokument& data) const{
//-----------------------------------------------------------------------------
	PROC_TRACE;

   if(data.logicState.IsHigh()==true)
      return WMF_PATH(data.key + "high.wmf");
   else
      return WMF_PATH(data.key + "low.wmf");
}


//-----------------------------------------------------------------------------
void CElectricNodeContextBinaryDisplay::InitIcon(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   // Alle zuvor angelegten Icons erst einmal loeschen
   //
   for(int loop=0 ;loop <data.icons.GetSize() ; loop++) {
      delete data.icons[loop];
   }
   data.icons.RemoveAll();
 
   CLogicValue tmp= data.logicState;
   // Jetzt die benoetigten Icons wieder anlegen
   // Das umsetzten des Logischen Zustand ist fuer die richtige Auswahl des Icons notwendig
   // Fuer High liefert die Funktion 'GetIconName' einen anderen Wert als fuer Low
   //
   // HIGH
   data.logicState = CLogicValue(CLogicValue::High);
   data.icons.SetAtGrow(0, new DragDropMetaFile(data.location, data.size, GetIconName(data), TRUE));
   data.icons[0]->SetSelectable(FALSE);
   data.pOwner->AddChildAtHead(data.icons[0]); 

   //
   // LOW
   data.logicState = CLogicValue(CLogicValue::Low);
   data.icons.SetAtGrow(1, new DragDropMetaFile(data.location, data.size, GetIconName(data), TRUE));
   data.icons[1]->SetSelectable(FALSE);
   data.pOwner->AddChildAtHead(data.icons[1]); 

   // alten Wert wieder herstellen;
   data.logicState = tmp;
}


//-----------------------------------------------------------------------------
void CElectricNodeContextBinaryDisplay::selectIcon(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;


}

//-----------------------------------------------------------------------------
void CElectricNodeContextBinaryDisplay::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.icons.GetSize()   >= 2);
   assert(data.inPorts.GetSize() >= 1);

   data.logicState=data.inPorts[0]->GetValue();

   // Je nach Zustand des Eingangs das Bildchen fuer High oder
   // Low anzeigen.
   //
   data.icons[0]->SetVisible(data.logicState.IsHigh());
   data.icons[1]->SetVisible(!data.logicState.IsHigh());
}

