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
#include "LogicValue.h"
#include "Application\Debug\LogManager.h"


//----------------------------------------------------------------------------
CLogicValue::CLogicValue(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_value = 0.1;
}


//----------------------------------------------------------------------------
CLogicValue::~CLogicValue(){
//----------------------------------------------------------------------------
	PROC_TRACE;


}


//----------------------------------------------------------------------------
bool CLogicValue::IsHigh() const {
//----------------------------------------------------------------------------
	PROC_TRACE;

   return ((m_value < 5.5) && (m_value > 2.8)) ? true : false;
}



//----------------------------------------------------------------------------
bool CLogicValue::IsLow() const {
//----------------------------------------------------------------------------
	PROC_TRACE;

   return ((m_value < 2.1) && (m_value >=0.0)) ? true : false;
}


//----------------------------------------------------------------------------
const CLogicValue& CLogicValue::operator=(const CLogicValue& s){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if(this==&s)   {
   	return *this;
   }

   m_value =s.m_value;

   return *this;
}


//----------------------------------------------------------------------------
const bool CLogicValue::operator!=(const CLogicValue& s) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

	if(this==&s)   {
   	return false;
   }

   if((s.IsLow()== IsLow()) || (s.IsHigh() == IsHigh()))   {
      return false;
   }

   return true;
}

//----------------------------------------------------------------------------
const bool CLogicValue::operator==(const CLogicValue& s) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

	if(this==&s)   {
   	return true;
   }

   return !(s != *this);
}


//----------------------------------------------------------------------------
const CLogicValue CLogicValue::operator||(const CLogicValue& s) const{
//----------------------------------------------------------------------------
	PROC_TRACE;


   return (s.IsHigh() || IsHigh())?CLogicValue::High:CLogicValue::Low;
}

//----------------------------------------------------------------------------
const CLogicValue CLogicValue::operator&&(const CLogicValue& s) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return (s.IsHigh() && IsHigh())?CLogicValue::High:CLogicValue::Low;
}

//----------------------------------------------------------------------------
const CLogicValue CLogicValue::operator!() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return CLogicValue(!IsHigh()?CLogicValue::High:CLogicValue::Low);
}