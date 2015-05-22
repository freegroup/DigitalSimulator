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

#if !defined(AFX_ELECTRICNODECONTEXTMULTIPLEXER_H__ADE4F4F1_F4F3_11D2_898D_004F49031E0C__INCLUDED_)
#define AFX_ELECTRICNODECONTEXTMULTIPLEXER_H__ADE4F4F1_F4F3_11D2_898D_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

#include "ElectricNodeContextGenericGate.h"

class CElectricNodeContextMultiplexer : public CElectricNodeContextGenericGate  {
   typedef CElectricNodeContextGenericGate inherited;
   
public:
   // Init group
   //
   virtual CSize GetInputCountRange() const  {return CSize(3,20);};
   virtual CSize GetOutputCountRange() const {return CSize(1,1);};
   virtual void  AdjustInputOutputCount(int &inCount, int &outCount);
   virtual CSize GetSize(CElectricNode::CElectricNodeDokument& data) const {return CSize(150,0);};
   virtual CString GetGroup()const{return CString("OBJECTGROUP.SELECTOR");};
   virtual CString GetName()const{return CString("OBJECT.MULTIPLEXER");};
   
   virtual void    SetInputCount(CElectricNode::CElectricNodeDokument& data,long );
   virtual void    SetOutputCount(CElectricNode::CElectricNodeDokument& data,long);

   virtual void onOption(CElectricNode::CElectricNodeDokument& data);

   virtual void DoCalculate(CElectricNode::CElectricNodeDokument& data);

   enum ParamMeaning
   {
      addressCount = 0,
      inputCount      ,
      MAX_PARAM  
   };
   virtual DWORD GetParamCount() const {return MAX_PARAM;};

   virtual char * const GetClassName(){return "CElectricNodeContextMultiplexer";};

protected:
   CElectricNodeContextMultiplexer();

   virtual void LayoutInput(CElectricNode::CElectricNodeDokument& data);

private:
   DECLARE_REGISTER(OBJ_MULTIPLEXER,CElectricNodeContextMultiplexer)
};

#endif // !defined(AFX_ELECTRICNODECONTEXTMULTIPLEXER_H__ADE4F4F1_F4F3_11D2_898D_004F49031E0C__INCLUDED_)
