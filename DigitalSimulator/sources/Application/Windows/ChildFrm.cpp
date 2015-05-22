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

#include "stdafx.h"
#include "resource.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Windows\Workplace\DigitalTraineeStudioView.h"

#include "ChildFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	//}}AFX_MSG_MAP
   ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW,0,0xFFFF,OnToolTipText)
   ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA,0,0xFFFF,OnToolTipText)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
CChildFrame::CChildFrame(){
//----------------------------------------------------------------------------
	PROC_TRACE;


}


#define _countof(array) (sizeof(array)/sizeof(array[0]))

//----------------------------------------------------------------------------
BOOL CChildFrame::OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT pResult){
//----------------------------------------------------------------------------
	PROC_TRACE;


   ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);
   char buffer [100];

   TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
   TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;

   sprintf(buffer,"TOOLTIP.%d",pNMHDR->idFrom);

   CString translation = TRANSLATE(buffer);
//   if(translation == CString(buffer))
//      return FALSE;

   if(pNMHDR->code == TTN_NEEDTEXTA)
      lstrcpyn(pTTTA->szText,(LPCSTR)translation,_countof(pTTTA->szText));
   else
      _mbstowcsz(pTTTW->szText,(LPCSTR)translation,_countof(pTTTW->szText));

   return TRUE;
}
