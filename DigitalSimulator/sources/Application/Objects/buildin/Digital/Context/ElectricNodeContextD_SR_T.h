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

#if !defined(AFX_ELECTRICNODECONTEXTD_SR_T_H__FEE500E1_F80D_11D2_8990_004F49031E0C__INCLUDED_)
#define AFX_ELECTRICNODECONTEXTD_SR_T_H__FEE500E1_F80D_11D2_8990_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "Application\Objects\buildin\digital\ElectricNodeContext.h"

class CElectricNodeContextD_SR_T : public CElectricNodeContext  {
   typedef CElectricNodeContext inherited;

public:
   // Init group
   //
   virtual CSize GetInputCountRange() const {return CSize(4,4);};// mindestens zwei Eingaenge, aber hoechstens 10
   virtual CSize GetOutputCountRange() const {return CSize(2,2);};// genau ein Ausgang
   virtual CSize GetSize(CElectricNode::CElectricNodeDokument& data) const {return CSize(120,0);};
   virtual CString GetGroup()const{return CString("OBJECTGROUP.FLIPFLOP");};
   virtual CString GetName()const{return CString("OBJECT.FLIPFLOP.D.SR.T");};

   // DoCalculateer group
   //
   virtual void DoCalculate(CElectricNode::CElectricNodeDokument& data);

   virtual char * const GetClassName(){return "CElectricNodeContextD_SR_T";};
protected:
   CElectricNodeContextD_SR_T();

   // Init group
   //
   virtual void InitInputPorts(CElectricNode::CElectricNodeDokument& data);
   virtual void InitOutputPorts(CElectricNode::CElectricNodeDokument& data);



private:
   DECLARE_REGISTER(OBJ_D_SR_T,CElectricNodeContextD_SR_T)
};

#endif // !defined(AFX_ELECTRICNODECONTEXTD_SR_T_H__FEE500E1_F80D_11D2_8990_004F49031E0C__INCLUDED_)
