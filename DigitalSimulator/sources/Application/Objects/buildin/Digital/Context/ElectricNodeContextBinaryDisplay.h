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

#if !defined(AFX_ELECTRICNODEINITILIZERBINARYDISPLAY_H__672DCA02_6BF0_11D2_891D_004F49031E0C__INCLUDED_)
#define AFX_ELECTRICNODEINITILIZERBINARYDISPLAY_H__672DCA02_6BF0_11D2_891D_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "Application\Objects\buildin\digital\ElectricNodeContext.h"

class CElectricNodeContextBinaryDisplay : public CElectricNodeContext{
   typedef CElectricNodeContext inherited;

public:

   // Init group
   //
   virtual CSize GetInputCountRange() const {return CSize(1,1);};// keinen Eingang
   virtual CSize GetOutputCountRange() const {return CSize(0,0);};// mindesten und hoechsten ein Eingang (min,max)
   virtual CString GetGroup()const{return CString("OBJECTGROUP.DISPLAY");};
   virtual CString GetName()const{return CString("OBJECT.BINARYDISPLAY");};
   // icon selecter
   //
   virtual void selectIcon(CElectricNode::CElectricNodeDokument& data);

   // DoCalculate group
   //
   virtual void DoCalculate(CElectricNode::CElectricNodeDokument& data);

   // param group
   virtual CSize GetSize(CElectricNode::CElectricNodeDokument& data) const {return CSize(50,0);};

   virtual char * const GetClassName(){return "CElectricNodeContextBinaryDisplay";};
protected:
   CElectricNodeContextBinaryDisplay();

   // Init group
   //
   virtual void InitIcon(CElectricNode::CElectricNodeDokument& data);

   // icon group
   //
   virtual CString GetIconName(CElectricNode::CElectricNodeDokument& data) const;

private:
   DECLARE_REGISTER(OBJ_LED,CElectricNodeContextBinaryDisplay)
};

#endif // !defined(AFX_ELECTRICNODEINITILIZERBINARYDISPLAY_H__672DCA02_6BF0_11D2_891D_004F49031E0C__INCLUDED_)
