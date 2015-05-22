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

#if !defined(AFX_ELECTRICNODECONTEXTPLUGINWRAPPER_H__73F45316_5197_11D4_B5B8_C3F4DAE247BA__INCLUDED_)
#define AFX_ELECTRICNODECONTEXTPLUGINWRAPPER_H__73F45316_5197_11D4_B5B8_C3F4DAE247BA__INCLUDED_

#include "Application\Objects\buildin\digital\ElectricNodeContext.h"
#include "Plugins\DLL\Standard\build\IObjectContext.h"

class CElectricNodeContextPluginWrapper : public CElectricNodeContext  
{
   typedef CElectricNodeContext inherited;

public:
   CElectricNodeContextPluginWrapper(IObjectContext* pluginContext);
   virtual ~CElectricNodeContextPluginWrapper();

   // Init group
   //
   virtual CSize   GetInputCountRange() const;
   virtual CSize   GetOutputCountRange() const;
   virtual DWORD   GetParamCount() const ;
   virtual CSize   GetSize(CElectricNode::CElectricNodeDokument& data) const;
   virtual int     GetContextMenuId() const {return IDR_POPUP_ELECTRIC_OBJECT;};
   virtual CString GetDescriptionText() const;
   virtual CString GetGroup()const;
   virtual CString GetName()const;
   virtual CString GetKey()const;
   virtual void    Initialize(CElectricNode::CElectricNodeDokument& data);
   virtual void    InitParam(CElectricNode::CElectricNodeDokument& data);
   virtual void    CleanupParam(CElectricNode::CElectricNodeDokument& data);

   virtual void    onOption(CElectricNode::CElectricNodeDokument& data);

   // DoCalculate group
   //
   virtual void DoCalculate(CElectricNode::CElectricNodeDokument& data);
   virtual void OnStartCalculate(CElectricNode::CElectricNodeDokument& data);
   virtual void OnStopCalculate(CElectricNode::CElectricNodeDokument& data);

   virtual bool paint(CElectricNode::CElectricNodeDokument& data,CDC* pDC);

   // debug stuff
   //
   virtual char * const GetClassName(){return "CElectricNodeContextPluginWrapper";};

protected:
   // Init group
   //
   virtual void InitIcon(CElectricNode::CElectricNodeDokument& data);

   // Layout group
   //
	virtual void LayoutOutput(CElectricNode::CElectricNodeDokument& data);
	virtual void LayoutInput(CElectricNode::CElectricNodeDokument& data);

   // icon group
   //
   virtual CString GetIconName(CElectricNode::CElectricNodeDokument& data) const ;

   IObjectContext*    m_pluginContext;
};

#endif // !defined(AFX_ELECTRICNODECONTEXTPLUGINWRAPPER_H__73F45316_5197_11D4_B5B8_C3F4DAE247BA__INCLUDED_)
