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

#if !defined(AFX_DDENODE_H__44039266_A662_11D2_99FE_0080C7304F8F__INCLUDED_)
#define AFX_DDENODE_H__44039266_A662_11D2_99FE_0080C7304F8F__INCLUDED_
#pragma warning(disable : 4786)

#include <assert.h>
#include "resource.h"       // Hauptsymbole
#include "DragDrop.h"
#include "DragDropObject.h"
#include "DragDropText.h"
#include "DragDropDocument.h"
#include "DragDropMetafile.h"
#include "DragDropLink.h"
#include "DragDropPort.h"
#include "DragDropArea.h"

#include "ElectricPort.h"
#include "PortContainer.h"
#include "IconContainer.h"
#include "stddde.h"


class CDDENode : public DragDropArea {
   typedef DragDropArea inherited;

public:
	CDDENode();
	virtual ~CDDENode();
   
   virtual long      GetContextMenuId(){return IDR_POPUP_DDE_OBJECT;};
   virtual long      GetHelpId(){return 0;};
   virtual CString   GetGroup()const{return CString("Interface");};
   virtual CString   GetMetaName(){return "DDE object";};

   virtual DragDropObject* Clone() const;
   virtual void       Serialize(CArchive& ar);
   virtual BOOL       DoLButtonDblClk(UINT nFlags, CPoint pointDP, CPoint pointLP, CClientDC* pDC, DragDropView* pView) {
      return DoOption();
   };

   virtual char * const GetClassName(){return "CDDENode";};

protected:
	bool               m_hasError;
   CDDEConv*          m_pDDEConversation;
	CString            m_server;
	CString            m_topic;
	CString            m_item;
   CPortContainer     m_ports;
	DragDropMetaFile*  m_icon;

   static CDDEServer  m_DDEServer;
	static bool        m_isInitilized;


private:
   static const int m_version ;

   DECLARE_SERIAL(CDDENode)
};

#endif // !defined(AFX_DDENODE_H__44039266_A662_11D2_99FE_0080C7304F8F__INCLUDED_)
