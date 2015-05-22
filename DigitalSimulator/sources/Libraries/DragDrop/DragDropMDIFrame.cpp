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
#include "DragDropstdafx.h"
#include "DragDropApp.h"      // for color palette stuff
#include "DragDropClientApp.h"
#include "DragDropView.h"
#include "DragDropEdit.h"
#include "DragDropMDIFrame.h"   

IMPLEMENT_DYNCREATE(DragDropMDIFrameWnd, CMDIFrameWnd)
BEGIN_MESSAGE_MAP(DragDropMDIFrameWnd, CMDIFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_QUERYNEWPALETTE()
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
DragDropMDIFrameWnd::DragDropMDIFrameWnd(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_pInLineEditView = NULL;
}

//----------------------------------------------------------------------------
DragDropMDIFrameWnd::~DragDropMDIFrameWnd(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
int DragDropMDIFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (inherited::OnCreate(lpCreateStruct) == -1)
        return -1;

	// avoid flicker on resize
   //
	DWORD dwStyle = ::GetClassLong(m_hWnd, GCL_STYLE);
	::SetClassLong(m_hWnd, GCL_STYLE, dwStyle & ~(CS_HREDRAW | CS_VREDRAW));

    return 0;
}

//----------------------------------------------------------------------------
BOOL DragDropMDIFrameWnd::PreTranslateMessage(MSG* pMsg){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (inherited::PreTranslateMessage(pMsg))
        return TRUE;
    else 
    {
        //  Test for actions that should end in-place editing.
        if (m_pInLineEditView)  
        {    
            BOOL end = FALSE;            
            //  If this is a mouse button down the mouse is outside of the edit control...
            //  If a menu is selected is tested in OnMenuSelect...
            if (pMsg->message == WM_LBUTTONDOWN || 
                pMsg->message == WM_RBUTTONDOWN ||
                pMsg->message == WM_MBUTTONDOWN)
            {                        
                if (pMsg->hwnd != m_pInLineEditView->EditControl()->m_hWnd)
                    end = TRUE;
            }
                
            if (end) 
            {
                m_pInLineEditView->DoEndEdit();
                return TRUE;
            }
        }
    }

    return FALSE;
}


//----------------------------------------------------------------------------
BOOL DragDropMDIFrameWnd::OnQueryNewPalette(){
//----------------------------------------------------------------------------
	PROC_TRACE;
    
   CDragDropApp::OnQueryNewPalette();  
   
   return inherited::OnQueryNewPalette();
}
