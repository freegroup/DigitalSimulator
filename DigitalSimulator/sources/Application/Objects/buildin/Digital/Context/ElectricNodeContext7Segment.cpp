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
#include "ElectricNodeContext7Segment.h"

IMPLEMENT_REGISTER(CElectricNodeContext7Segment);

//-----------------------------------------------------------------------------
CElectricNodeContext7Segment::CElectricNodeContext7Segment(){
//-----------------------------------------------------------------------------
	PROC_TRACE;

}


//-----------------------------------------------------------------------------
void CElectricNodeContext7Segment::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.icons.GetSize()   >= 8);
   assert(data.inPorts.GetSize() >= 7);

   data.icons[1]->SetVisible(data.inPorts[0]->IsHigh());
   data.icons[2]->SetVisible(data.inPorts[1]->IsHigh());
   data.icons[3]->SetVisible(data.inPorts[2]->IsHigh());
   data.icons[4]->SetVisible(data.inPorts[3]->IsHigh());
   data.icons[5]->SetVisible(data.inPorts[4]->IsHigh());
   data.icons[6]->SetVisible(data.inPorts[5]->IsHigh());
   data.icons[7]->SetVisible(data.inPorts[6]->IsHigh());
}


//-----------------------------------------------------------------------------
void CElectricNodeContext7Segment::InitIcon(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::InitIcon( data);

   // Die Teilelemente fuer jedes Segment
   //
   assert(data.icons.GetSize() == 1);

   // A
  data.icons.SetAtGrow(1,new DragDropMetaFile(data.location, 
             data.size,WMF_PATH("Segment_A.wmf"),TRUE));
  data.icons[1]->SetSelectable(FALSE);
  data.pOwner->AddChildAtTail(data.icons[1]); 
  data.icons[1]->SetSpotLocation(DragDropObject::spotTopLeft,
                                 data.icons[0],
                                 DragDropObject::spotTopLeft);

  // B
  data.icons.SetAtGrow(2,new DragDropMetaFile(data.location, 
             data.size,
             WMF_PATH("Segment_B.wmf"), 
             TRUE));
  data.icons[2]->SetSelectable(FALSE);
  data.pOwner->AddChildAtTail(data.icons[2]); 
  data.icons[2]->SetSpotLocation(DragDropObject::spotTopLeft,
                                 data.icons[0],
                                 DragDropObject::spotTopLeft);

  // C
  data.icons.SetAtGrow(3,new DragDropMetaFile(data.location, 
             data.size,
             WMF_PATH("Segment_C.wmf"), 
             TRUE));
  data.icons[3]->SetSelectable(FALSE);
  data.pOwner->AddChildAtTail(data.icons[3]); 
  data.icons[3]->SetSpotLocation(DragDropObject::spotTopLeft,
                                 data.icons[0],
                                 DragDropObject::spotTopLeft);


  // D
  data.icons.SetAtGrow(4,new DragDropMetaFile(data.location, 
             data.size,
             WMF_PATH("Segment_D.wmf"), 
             TRUE));
  data.icons[4]->SetSelectable(FALSE);
  data.pOwner->AddChildAtTail(data.icons[4]); 
  data.icons[4]->SetSpotLocation(DragDropObject::spotTopLeft,
                                 data.icons[0],
                                 DragDropObject::spotTopLeft);

  // E
  data.icons.SetAtGrow(5,new DragDropMetaFile(data.location, 
             data.size,
             WMF_PATH("Segment_E.wmf"), 
             TRUE));
  data.icons[5]->SetSelectable(FALSE);
  data.pOwner->AddChildAtTail(data.icons[5]); 
  data.icons[5]->SetSpotLocation(DragDropObject::spotTopLeft,
                                 data.icons[0],
                                 DragDropObject::spotTopLeft);

  // F
  data.icons.SetAtGrow(6,new DragDropMetaFile(data.location, 
             data.size,
             WMF_PATH("Segment_F.wmf"), 
             TRUE));
  data.icons[6]->SetSelectable(FALSE);
  data.pOwner->AddChildAtTail(data.icons[6]); 
  data.icons[6]->SetSpotLocation(DragDropObject::spotTopLeft,
                                 data.icons[0],
                                 DragDropObject::spotTopLeft);

  //  G
  data.icons.SetAtGrow(7,new DragDropMetaFile(data.location, 
             data.size,
             WMF_PATH("Segment_G.wmf"), 
             TRUE));
  data.icons[7]->SetSelectable(FALSE);
  data.pOwner->AddChildAtTail(data.icons[7]); 
  data.icons[7]->SetSpotLocation(DragDropObject::spotTopLeft,
                                 data.icons[0],
                                 DragDropObject::spotTopLeft);

  assert(data.icons.GetSize() >= 8);
}

