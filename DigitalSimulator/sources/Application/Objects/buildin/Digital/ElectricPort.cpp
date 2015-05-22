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

#include "ElectricPort.h"
#include "Application\Debug\LogManager.h"

#define TITLE_TEXT_RGB  RGB(0,0,0)
#define LABEL_OFFSET    5

static SIZE simple_port_sizes[] = 
{
    {7,7},    /* dot */
    {6,9},    /* negate dot */
    {7,7},    /* HIGH dot */
    {6,9},    /* HIGH negate dot */
};


IMPLEMENT_SERIAL(CElectricPort, DragDropPort, 2)
const  CElectricPort::m_version = 2;

//----------------------------------------------------------------------------
CElectricPort::CElectricPort(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   InitBitmaps();
}

//----------------------------------------------------------------------------
CElectricPort::CElectricPort(CPoint location, int nToSide, int nFromSide) 
    : DragDropPort(location, SimplePortDot, nToSide, nFromSide){   
//----------------------------------------------------------------------------

   m_negater = false;
   m_input   = false;
   m_output  = false;
   InitBitmaps();
}

//----------------------------------------------------------------------------
CElectricPort::~CElectricPort(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DragDropObject* CElectricPort::Clone() const{   
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pObj = inherited::Clone();
   ASSERT(pObj->IsKindOf(RUNTIME_CLASS(CElectricPort)));                  
   CElectricPort *pNode =(CElectricPort*) pObj ;

   pNode->m_negater = m_negater;
   pNode->m_input   = m_input;
   pNode->m_output  = m_output ;

   return pNode;
}


//----------------------------------------------------------------------------
void CElectricPort::SetValue(CLogicValue::state s){
//----------------------------------------------------------------------------
	PROC_TRACE;

   SetValue(CLogicValue(s));
}


//----------------------------------------------------------------------------
void CElectricPort::SetValue(const CLogicValue &v){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   m_oldLogicValue = m_logicValue;
   
   if(m_negater==true){
      m_logicValue = !v;
   }
   else{
      m_logicValue = v;
   }
   
   if(HasValueChanged()){
      if(m_logicValue.IsHigh())
         SetBitmapId(m_negater?NegatePortHighDot:SimplePortHighDot);
      else
         SetBitmapId(m_negater?NegatePortDot:SimplePortDot);
   }
}

//----------------------------------------------------------------------------
CLogicValue CElectricPort::GetValue() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_logicValue;
}

//----------------------------------------------------------------------------
CLogicValue CElectricPort::GetLastValue() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_oldLogicValue;
}


//----------------------------------------------------------------------------
void CElectricPort::SetInverter(bool v){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_negater = v;
   if(m_negater==true)
      SetBitmapId(NegatePortDot);
    else
      SetBitmapId(SimplePortDot);
}

//----------------------------------------------------------------------------
void CElectricPort::InitBitmaps(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   EnableImageList(IDB_SIMPLE_PORTS,20);
}


//----------------------------------------------------------------------------
void CElectricPort::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

   if (ar.IsStoring()){
       ar << m_version;
       ar << m_negater;
       ar << m_input;
       ar << m_output;
       ar << m_logicValue.IsHigh();
       ar << m_oldLogicValue.IsHigh();
   }
   else{
       int version;
       int bool_temp;
       ar >> version;
      
       switch (version){
       case 1:
           ar >> bool_temp; m_negater = bool_temp==0 ?false:true;
           ar >> bool_temp; m_input   = bool_temp==0 ?false:true;
           ar >> bool_temp; m_output  = bool_temp==0 ?false:true;
           break;
       case 2:
          {
           BOOL b;
           ar >> bool_temp; m_negater = bool_temp==0 ?false:true;
           ar >> bool_temp; m_input   = bool_temp==0 ?false:true;
           ar >> bool_temp; m_output  = bool_temp==0 ?false:true;
           ar >> b; m_logicValue   = b?CLogicValue::High: CLogicValue::Low;
           ar >> b; m_oldLogicValue= b?CLogicValue::High: CLogicValue::Low;
          }
           break;
       default:
           LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
           break;
       }
    }
}



//----------------------------------------------------------------------------
int CElectricPort::PortMax(){ 
//----------------------------------------------------------------------------
	PROC_TRACE;

   return SimplePortMAX; 
}


//----------------------------------------------------------------------------
int CElectricPort::GetPortWidth() {
//----------------------------------------------------------------------------
	PROC_TRACE;

    return simple_port_sizes[GetBitmapId()].cx;
}

//----------------------------------------------------------------------------
int CElectricPort::GetPortHeight(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return simple_port_sizes[GetBitmapId()].cy;
}

//----------------------------------------------------------------------------
int CElectricPort::GetPortOffset(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return 10*GetBitmapId();
}

//----------------------------------------------------------------------------
void  CElectricPort::RemoveLink(DragDropObject* pLink){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::RemoveLink(pLink);

   // Ist Kein Link mehr an den Port angeschlossen, so wird der Wert
   // des Einganges auf High gesetzt. Unbeschaltete Eingaenge sind immer
   // High.
   if( GetLinks()->GetCount()==0){
      SetValue(CLogicValue::High);
   }
}


