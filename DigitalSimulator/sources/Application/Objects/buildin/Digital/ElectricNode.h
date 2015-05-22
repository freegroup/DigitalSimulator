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
#ifndef _CElectricNode_H_
#define _CElectricNode_H_
#pragma warning(disable : 4786)

#include <assert.h>
#include "resource.h"       // Hauptsymbole
#include "Application\i18n\ResourceTranslater.h"
#include "stdafx.h"

#include "Application\Objects\buildin\digital\ElectricPort.h"
#include "Application\Objects\buildin\digital\PortContainer.h"
#include "Application\Objects\buildin\digital\IconContainer.h"
#include "Application\Objects\buildin\digital\LogicValue.h"

class CElectricNodeContext;

/////////////////////////////////////////////////////////////////////////////
// class CElectricNode
//
class CElectricNode : public DragDropArea{
   typedef DragDropArea inherited;

public:
   CElectricNode();
   CElectricNode(CString contextName);
   virtual ~CElectricNode();

   virtual CString     GetDescriptionText();
   virtual CString     GetKey()const;
   virtual CString     GetName()const;
   virtual CString     GetVersion()const;

   // HACK....
   virtual CString     GetMetaNameSuffix();
   virtual CString     GetGroup()const;
   virtual long        GetHelpId();
   virtual long        GetContextMenuId();
	virtual BOOL       DoOption();
	virtual BOOL       DoExtendedOption();

   virtual void        OnTimerStart();
   virtual void        OnTimerEnd();

   virtual DragDropObject*  Clone() const;
  	virtual void        DoCalculate();
   virtual BOOL        DoLButtonDblClk(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL        DoLButtonClick(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL        DoLButtonUp(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL        DoLButtonDown(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL        DoMouseOverStart(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL        DoMouseOver(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual BOOL        DoMouseOverEnd(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView);
   virtual void        GeometryChange(CRect* pRectPrevious);      // Object has been moved/resized event
   virtual void        SetLocation(int x, int y);
   virtual void        SetBoundingRect(int nLeft, int nTop, int nRight, int nBottom);

   virtual void Serialize(CArchive& ar);

   //  for the access for the context classes
   //  (the context classes made a friend of this...?)
   //
   virtual CSize   GetInputCountRange() ;
   virtual CSize   GetOutputCountRange();

   virtual long    GetInputCount();
   virtual long    GetOutputCount();

   virtual CElectricPort*    GetInput(int index);
   virtual CElectricPort*    GetOutput(int index);

   virtual CRect   GetBoundingRect();

   virtual BOOL paint(CDC* pDC);

   virtual char * const GetClassName(){return "CElectricNode";};
protected:
   CElectricNodeContext      *m_pContext;

public:

   class CElectricNodeDokument
   {
      public:
         CElectricNodeDokument()
         {
         	PROC_TRACE;
            pOwner        = NULL;
            pLabel        = NULL;
            key           = "Default";
            inCount       = 0;
            outCount      = 0;
            size          = CSize(0,0);
            location      = CPoint(0,0);
            mousePos      = CPoint(0,0);
            logicState    = CLogicValue(CLogicValue::High);
            param         = NULL;
         };
         ~CElectricNodeDokument(){
         	PROC_TRACE;
            delete[] param;
         }
         CElectricNode         *pOwner;
         DragDropText          *pLabel;
         CLogicValue            logicState;
         CString                key;
	//	   CString                description;
         CSize                  size;
         CPoint                 location;
         CPoint                 mousePos;
         CIconContainer         icons;
         CPortContainer         inPorts;
         CPortContainer         outPorts;
         char*                  param;
         long                   inCount;
         long                   outCount;
   };
   CElectricNodeDokument  m_data;

   DECLARE_SERIAL(CElectricNode)

private:
   static const int m_version ;
};


#endif
