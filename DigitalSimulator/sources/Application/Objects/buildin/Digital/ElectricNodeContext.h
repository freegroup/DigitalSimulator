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

#if !defined(AFX_ELECTRICNODECONTEXT_H__CAB17031_7884_11D2_99E0_0080C7304F8F__INCLUDED_)
#define AFX_ELECTRICNODECONTEXT_H__CAB17031_7884_11D2_99E0_0080C7304F8F__INCLUDED_
#pragma warning(disable : 4786)

#include <afxtempl.h>
#include "utils\HelpIDs.h"
#include "ElectricNode.h"
#include "PortContainer.h"
#include "Application\Debug\LogManager.h"

class CElectricNodeContext;


typedef CTypedPtrMap<CMapStringToPtr,CString,CElectricNodeContext*> CMapStringToNodeContext;
extern CMapStringToNodeContext* g_contextMap;

#define DECLARE_REGISTER(context,className)                    \
   public:                                                     \
      static void registerClass(CString metaname)              \
      {                                                        \
         className* obj=new className;                         \
        	g_contextMap->SetAt(metaname, obj);                   \
         LM::log(LM::info,"register object '%s'",(LPCSTR)metaname); \
      };                                                       \
                                                               \
      class helperClassForRegister                             \
      {                                                        \
      public:                                                  \
         helperClassForRegister(){                             \
            className::registerClass(#context);                \
         };                                                    \
      };                                                       \
      virtual CString GetKey()const {return #context;};   \
      virtual long    GetHelpId()  const {return context;};   
  


#ifndef IMPLEMENT_REGISTER
   #define IMPLEMENT_REGISTER(className)                          \
   className::helperClassForRegister  helper##className##_Object;
#endif


class CElectricNodeContext  
{
public:
   static  CElectricNodeContext* GetContext(CString metaName);
   static  clear();

   // Init group
   //
   virtual void    Initialize(CElectricNode::CElectricNodeDokument& data);
   virtual CSize   GetInputCountRange() const {return CSize(0,30);};
   virtual CSize   GetOutputCountRange() const {return CSize(0,30);};
   virtual void    AdjustInputOutputCount(int &outCount, int &inCount){};
   virtual DWORD   GetParamCount() const {return 0;};
   virtual CSize   GetSize(CElectricNode::CElectricNodeDokument& data) const {return CSize(100,0);};
   virtual int     GetContextMenuId() const {return IDR_POPUP_ELECTRIC_OBJECT;};
   virtual CString GetDescriptionText() const;
   virtual CString GetGroup()const{return CString("Generic");};
   virtual CString GetName()const{return CString("Generic");};
   virtual CString GetVersion()const{return CString("1.0");};
   virtual void    SetInputCount(CElectricNode::CElectricNodeDokument& data,long );
   virtual void    SetOutputCount(CElectricNode::CElectricNodeDokument& data,long);
   virtual void    InitParam(CElectricNode::CElectricNodeDokument& data);
   virtual void    CleanupParam(CElectricNode::CElectricNodeDokument& data);

   // icon selecter
   //
   virtual void selectIcon(CElectricNode::CElectricNodeDokument& data);

   // DoCalculate group
   //
   virtual void DoCalculate(CElectricNode::CElectricNodeDokument& data);
   virtual void OnStartCalculate(CElectricNode::CElectricNodeDokument& data);
   virtual void OnStopCalculate(CElectricNode::CElectricNodeDokument& data);

   // Layout group
   //
   virtual void Layout(CElectricNode::CElectricNodeDokument& data);

   // event group
   //
   virtual void OnLButtonDblClk(CElectricNode::CElectricNodeDokument& data);
   virtual void OnLButtonClick(CElectricNode::CElectricNodeDokument& data);
   virtual void OnLButtonUp(CElectricNode::CElectricNodeDokument& data);
   virtual void OnLButtonDown(CElectricNode::CElectricNodeDokument& data);
   virtual void onOption(CElectricNode::CElectricNodeDokument& data);
   virtual void OnGeometryChange(CElectricNode::CElectricNodeDokument& data);
   virtual void OnMouseOverStart(CElectricNode::CElectricNodeDokument& data);
   virtual void OnMouseOver(CElectricNode::CElectricNodeDokument& data);
   virtual void OnMouseOverEnd(CElectricNode::CElectricNodeDokument& data);

   // painting stuff
   //
   virtual bool paint(CElectricNode::CElectricNodeDokument& data,CDC* pDC){ return false;};

   // debug stuff
   //
   virtual char * const GetClassName(){return "CElectricNodeContext";};

protected:
   CElectricNodeContext();

   // Init group
   //
   virtual void InitInputPorts(CElectricNode::CElectricNodeDokument& data);
   virtual void InitOutputPorts(CElectricNode::CElectricNodeDokument& data);
   virtual void InitIcon(CElectricNode::CElectricNodeDokument& data);

   // icon group
   //
   virtual CString GetIconName(CElectricNode::CElectricNodeDokument& data) const ;

   // Layout group
   //
//   virtual void LayoutLabel(CElectricNode::CElectricNodeDokument& data);
   virtual void LayoutOutput(CElectricNode::CElectricNodeDokument& data);
   virtual void LayoutInput(CElectricNode::CElectricNodeDokument& data);

   // This 'Hack' is required for the export modul
   // e.g.
   // a 'POWER_TASTER' with default 'off' will be export to the xml with 'POWER_TASTER0'
   // a 'POWER_TASTER' with default 'on'  will be export to the xml with 'POWER_TASTER1'
public:
   virtual CString GetMetaNameSuffix(CElectricNode::CElectricNodeDokument& data)const {return "";};

   DECLARE_REGISTER(OBJ_GENERIC,CElectricNodeContext)
};

#endif // !defined(AFX_ELECTRICNODECONTEXT_H__CAB17031_7884_11D2_99E0_0080C7304F8F__INCLUDED_)
