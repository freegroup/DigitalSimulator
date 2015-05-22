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

#if !defined(AFX_ELECTRICNODECONTEXTUM_H__8C2D20F1_A4EC_11D2_99FC_0080C7304F8F__INCLUDED_)
#define AFX_ELECTRICNODECONTEXTUM_H__8C2D20F1_A4EC_11D2_99FC_0080C7304F8F__INCLUDED_
#pragma warning(disable : 4786)


#include "Application\Objects\buildin\digital\ElectricNodeContext.h"

class CElectricNodeContextSwitchUM : public CElectricNodeContext  {
   typedef CElectricNodeContext inherited;

public:
   // DoCalculateer group
   //
   virtual void DoCalculate(CElectricNode::CElectricNodeDokument& data);

   virtual void OnLButtonClick(CElectricNode::CElectricNodeDokument& data);

   virtual CSize GetInputCountRange() const {return CSize(2,2);};// keinen Eingang
   virtual CSize GetOutputCountRange() const {return CSize(1,1);};// mindesten und hoechsten ein Eingang (min,max)
   virtual CSize GetSize() const {return CSize(50,0);};
   virtual CString GetGroup()const{return CString("OBJECTGROUP.SWITCH");};
   virtual CString GetName()const{return CString("OBJECT.SWITCH.TOGGLE");};

   enum ParamMeaning
   {
      CurrentState = 0,
      MAX_PARAM
   };
   virtual DWORD GetParamCount() const {return MAX_PARAM;};

   virtual char * const GetClassName(){return "CElectricNodeContextSwitchUM";};
protected:
   CElectricNodeContextSwitchUM();

   virtual CString GetIconName(CElectricNode::CElectricNodeDokument& data) const ;

private:
   DECLARE_REGISTER(OBJ_SWITCH_UM,CElectricNodeContextSwitchUM)
};

#endif // !defined(AFX_ELECTRICNODECONTEXTUM_H__8C2D20F1_A4EC_11D2_99FC_0080C7304F8F__INCLUDED_)
