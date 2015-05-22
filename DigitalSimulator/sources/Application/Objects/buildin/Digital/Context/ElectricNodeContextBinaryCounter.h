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

#if !defined(AFX_ELECTRICNODECONTEXTBINARYCOUNTER_H__9D2FCE91_9FC6_11D2_8954_004F49031E0C__INCLUDED_)
#define AFX_ELECTRICNODECONTEXTBINARYCOUNTER_H__9D2FCE91_9FC6_11D2_8954_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "Application\Objects\buildin\digital\ElectricNodeContext.h"

class CElectricNodeContextBinaryCounter : public CElectricNodeContext  {
   typedef CElectricNodeContext inherited;

public:
   // Init group
   //
   virtual CSize GetInputCountRange() const {return CSize(2,2);};// mind. 2  und max. 2 Eingänge
   virtual CSize GetOutputCountRange() const {return CSize(1,14);};// mindesten und hoechsten ein Eingang (min,max)
   virtual CString GetGroup()const{return CString("OBJECTGROUP.COUNTER");};
   virtual CString GetName()const{return CString("OBJECT.BINARYCOUNTER");};

   enum ParamMeaning {
      CurrentValue = 0,
      MAX_PARAM
   };
   virtual DWORD GetParamCount() const {return MAX_PARAM;};

   // DoCalculate group
   //
   virtual void DoCalculate(CElectricNode::CElectricNodeDokument& data);

   virtual char * const GetClassName(){return "CElectricNodeContextBinaryCounter";};
protected:
	CElectricNodeContextBinaryCounter();

   // Init group
   //
   virtual void InitIcon(CElectricNode::CElectricNodeDokument& data) ;

   // Layout group
   //
	virtual void LayoutOutput(CElectricNode::CElectricNodeDokument& data);

   virtual void reset(CElectricNode::CElectricNodeDokument& data);

private:

   DECLARE_REGISTER(OBJ_BINARYCOUNTER,CElectricNodeContextBinaryCounter)

};

#endif // !defined(AFX_ELECTRICNODECONTEXTBINARYCOUNTER_H__9D2FCE91_9FC6_11D2_8954_004F49031E0C__INCLUDED_)
