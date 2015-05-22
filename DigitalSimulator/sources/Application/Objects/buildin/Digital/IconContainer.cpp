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
#include "IconContainer.h"
#include "Application\Debug\LogManager.h"

IMPLEMENT_SERIAL( CIconContainer, CObArray, 1 )
const  CIconContainer::m_version = 1;

//-------------------------------------------------------------------------
CIconContainer::CIconContainer(){
//-------------------------------------------------------------------------
	PROC_TRACE;

}


//-------------------------------------------------------------------------
DragDropMetaFile* CIconContainer::operator[](int index) const{
//-------------------------------------------------------------------------
	PROC_TRACE;

   assert(index >= 0);
   if (index >=  GetSize())
      return NULL;

   return (DragDropMetaFile*)inherited::GetAt(index);
}


//-------------------------------------------------------------------------
void CIconContainer::Serialize(CArchive& ar){
//-------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

   if (ar.IsStoring()){
       ar << m_version;
   }
   else{
      int version;
      ar >> version;

      switch (version){
      case 1:
           break;
       default:
           LM::log(LM::error,"Unknown objekt version %d during serializing of class %s found",version,GetClassName());
           break;
       }
    }
}

//-------------------------------------------------------------------------
void CIconContainer::destroyAll(){
//-------------------------------------------------------------------------
	PROC_TRACE;

   for(long loop=0 ;loop <GetSize() ; loop++){
      delete (*this)[loop];
   }
   RemoveAll();
}
