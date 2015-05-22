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

#ifndef _ELECTRICPORT_H_
#define _ELECTRICPORT_H_
#pragma warning(disable : 4786)

#include <assert.h>
#include "stdafx.h"
#include "resource.h"       
#include "DragDrop.h"
#include "DragDropObject.h"
#include "DragDropText.h"
#include "DragDropDocument.h"
#include "DragDropMetafile.h"
#include "DragDropLink.h"
#include "DragDropPort.h"
#include "DragDropArea.h"
#include "Application\Objects\buildin\Digital\LogicValue.h"

enum SimplePortnBitMapIds {SimplePortDot, NegatePortDot,SimplePortHighDot,NegatePortHighDot, SimplePortMAX};

class CElectricPort : public DragDropPort{
   typedef DragDropPort inherited;
public:
   CElectricPort();
   CElectricPort(CPoint pPoint, int nToSide, int nFromSide);
   virtual ~CElectricPort();

   virtual bool        HasValueChanged(){return m_oldLogicValue != m_logicValue;};
   virtual void        SetValue(const CLogicValue &v);
   virtual void        SetValue(CLogicValue::state s);
   virtual void        ToggleValue(){SetValue(!m_logicValue);};
   virtual bool        IsHigh(){return m_logicValue.IsHigh();};
   virtual bool        IsLow(){return m_logicValue.IsLow();};
   virtual bool        IsInput(){return m_input;};
   virtual bool        IsOutput(){return m_output;};
   virtual void        SetInput(bool value){m_input=value;};
   virtual void        SetOutput(bool value){m_output=value;};
   virtual CLogicValue GetValue() const ;
   virtual CLogicValue GetLastValue() const ;
   virtual void        SetInverter(bool );

   virtual DragDropObject*  Clone() const;
   virtual void        Serialize(CArchive& ar);

   virtual char * const GetClassName(){return "CElectricPort";};
protected:
   virtual int PortMax(); 
   virtual int GetPortWidth();
   virtual int GetPortHeight();
   virtual int GetPortOffset();

   virtual void RemoveLink(DragDropObject* pLink);  

   bool         m_negater;
   bool         m_input;
   bool         m_output;
   CLogicValue  m_logicValue;
   CLogicValue  m_oldLogicValue;
   void         InitBitmaps();

   DECLARE_SERIAL(CElectricPort)

private:
   static const int m_version ;

};


#endif 
