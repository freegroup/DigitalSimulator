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

#ifndef AFX_ELECTRICNODEINITILIZERTAKT_H__8FCEB5B1_6E52_11D2_8921_004F49031E0C__INCLUDED_
#define AFX_ELECTRICNODEINITILIZERTAKT_H__8FCEB5B1_6E52_11D2_8921_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "Application\Objects\buildin\digital\ElectricNodeContext.h"

class CElectricNodeContextTakt : public CElectricNodeContext  {
   typedef CElectricNodeContext inherited;

public:
   // DoCalculate group
   //
   virtual void DoCalculate(CElectricNode::CElectricNodeDokument& data);

   virtual void onOption(CElectricNode::CElectricNodeDokument& data);

   // Init group
   //
   virtual CSize GetInputCountRange() const {return CSize(0,0);};// mindestens ein Eingang, aber hoechstens 10
   virtual CSize GetOutputCountRange() const {return CSize(1,1);};// mindestens ein Ausgang, aber hoechstens 10
   virtual CString GetGroup()const{return CString("OBJECTGROUP.TIMEELEMENT");};
   virtual CString GetName()const{return CString("OBJECT.PULS");};

   enum ParamMeaning
   {
      currentHighTime = 0,
      maxHighTime,
      currentLowTime,
      maxLowTime,
      MAX_PARAM
   };
   virtual DWORD GetParamCount() const {return MAX_PARAM;};

   virtual char * const GetClassName(){return "CElectricNodeContextTakt";};
protected:
	CElectricNodeContextTakt();

private:
   DECLARE_REGISTER(OBJ_TAKT,CElectricNodeContextTakt)
};

#endif // !defined(AFX_ELECTRICNODEINITILIZERTAKT_H__8FCEB5B1_6E52_11D2_8921_004F49031E0C__INCLUDED_)
