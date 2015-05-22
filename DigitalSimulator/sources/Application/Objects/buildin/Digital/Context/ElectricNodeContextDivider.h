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

#if !defined(AFX_ELECTRICNODECONTEXTDIVIDER_H__9C3F5521_B446_11D2_9A11_0080C7304F8F__INCLUDED_)
#define AFX_ELECTRICNODECONTEXTDIVIDER_H__9C3F5521_B446_11D2_9A11_0080C7304F8F__INCLUDED_
#pragma warning(disable : 4786)

#include "Application\Objects\buildin\digital\ElectricNodeContext.h"

class CElectricNodeContextDivider : public CElectricNodeContext  {
   typedef CElectricNodeContext inherited;

public:
   // DoCalculateer group
   //
   virtual void DoCalculate(CElectricNode::CElectricNodeDokument& data);

   virtual CSize GetInputCountRange() const {return CSize(1,1);};
   virtual CSize GetOutputCountRange() const {return CSize(1,1);};
   virtual CString GetGroup()const{return CString("OBJECTGROUP.SWITCH");};
   virtual CString GetName()const{return CString("OBJECT.DIVIDER");};

   enum ParamMeaning
   {
      DivideRation = 0,
	   CurrentState,
      MAX_PARAM
   };
   virtual DWORD GetParamCount() const {return MAX_PARAM;};
   virtual void onOption(CElectricNode::CElectricNodeDokument& data);
   virtual void Initialize(CElectricNode::CElectricNodeDokument& data);

   virtual char * const GetClassName(){return "CElectricNodeContextDivider";};
protected:
   CElectricNodeContextDivider();

private:
   DECLARE_REGISTER(OBJ_DIVIDER,CElectricNodeContextDivider)
};

#endif // !defined(AFX_ELECTRICNODECONTEXTDIVIDER_H__9C3F5521_B446_11D2_9A11_0080C7304F8F__INCLUDED_)
