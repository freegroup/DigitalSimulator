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
#include "imapi.h"
#include "Application\Debug\LogManager.h"

HINSTANCE CIMapi::m_hInstMail   = (HINSTANCE) NULL;
BOOL	    CIMapi::m_isMailAvail = (BOOL) -1;

//----------------------------------------------------------------------------
CIMapi::CIMapi(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_error = 0;										//	Initially error free

	memset(&m_message, 0, sizeof(MapiMessage));
	memset(&m_from, 0, sizeof(MapiRecipDesc));
	m_message.lpOriginator = &m_from;
	m_from.ulRecipClass = MAPI_ORIG;

	if (m_hInstMail == (HINSTANCE) NULL)				//	Load the MAPI dll
		m_hInstMail = ::LoadLibraryA("MAPI32.DLL");

	if (m_hInstMail == (HINSTANCE) NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
		m_error = IMAPI_LOADFAILED;
		return;
	}

	ASSERT(m_hInstMail != (HINSTANCE) NULL);			//	Now get the pointer to the send function
	(FARPROC&) m_lpfnSendMail = GetProcAddress(m_hInstMail, "MAPISendMail");

	if (m_lpfnSendMail == NULL)
	{
		AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
		m_error = IMAPI_INVALIDDLL;
		return;
	}

	ASSERT(m_lpfnSendMail != NULL);
}

//----------------------------------------------------------------------------
CIMapi::~CIMapi(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (m_hInstMail != (HINSTANCE) NULL)
		::FreeLibrary(m_hInstMail);

	m_hInstMail = (HINSTANCE) NULL;
	
	free(m_message.lpFiles);
	free(m_message.lpRecips);
}

//----------------------------------------------------------------------------
BOOL CIMapi::HasEmail(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (m_isMailAvail == (BOOL) -1)
		m_isMailAvail = ::GetProfileInt(_T("MAIL"), _T("MAPI"), 0) != 0 && SearchPath(NULL, _T("MAPI32.DLL"), NULL, 0, NULL, NULL) != 0;

	return m_isMailAvail;
}

//----------------------------------------------------------------------------
UINT CIMapi::Error(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	UINT temp = m_error;

	m_error = IMAPI_SUCCESS;
	return temp;
}

//----------------------------------------------------------------------------
BOOL CIMapi::AllocNewTo(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//	Allocate a new MapiRecipDesc structure and Initialise it to all zeros
	m_message.lpRecips = (MapiRecipDesc *) realloc(m_message.lpRecips, (m_message.nRecipCount + 1) * sizeof(MapiRecipDesc));
	memset(&m_message.lpRecips[m_message.nRecipCount], 0, sizeof(MapiRecipDesc));

	ASSERT(m_message.lpRecips);
	return m_message.lpRecips != (MapiRecipDesc *) NULL;
}

//----------------------------------------------------------------------------
BOOL CIMapi::To(LPCTSTR recip){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (AllocNewTo())
	{
		//	We succeeded in allocating a new recipient record
		m_message.lpRecips[m_message.nRecipCount].lpszAddress = (LPTSTR) malloc(strlen(recip) + 1);
		strcpy(m_message.lpRecips[m_message.nRecipCount].lpszAddress, recip);
		m_message.lpRecips[m_message.nRecipCount].ulRecipClass = MAPI_TO;
		m_message.nRecipCount++;
		return TRUE;
	}

	m_error = IMAPI_FAILTO;
	return FALSE;
}

//----------------------------------------------------------------------------
BOOL CIMapi::Cc(LPCTSTR recip){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (AllocNewTo())
	{
		//	We succeeded in allocating a new recipient record
		m_message.lpRecips[m_message.nRecipCount].lpszAddress = (LPTSTR) malloc(strlen(recip) + 1);
		strcpy(m_message.lpRecips[m_message.nRecipCount].lpszAddress, recip);
		m_message.lpRecips[m_message.nRecipCount].ulRecipClass = MAPI_CC;
		m_message.nRecipCount++;
		return TRUE;
	}

	m_error = IMAPI_FAILCC;
	return FALSE;
}

//----------------------------------------------------------------------------
BOOL CIMapi::Attach(LPCTSTR path, LPCTSTR name){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//	Add a new attachment record
	m_message.lpFiles = (MapiFileDesc *) realloc(m_message.lpFiles, (m_message.nFileCount + 1) * sizeof(MapiFileDesc));
	memset(&m_message.lpFiles[m_message.nFileCount], 0, sizeof(MapiFileDesc));

	ASSERT(m_message.lpFiles);
	
	if (m_message.lpFiles == (MapiFileDesc *) NULL)
	{
		m_error = IMAPI_FAILATTACH;
		return FALSE;
	}

	m_message.lpFiles[m_message.nFileCount].lpszPathName = (LPTSTR) malloc(strlen(path) + 1);
	strcpy(m_message.lpFiles[m_message.nFileCount].lpszPathName, path);

	if (name != (LPCTSTR) NULL)
	{
		m_message.lpFiles[m_message.nFileCount].lpszFileName = (LPTSTR) malloc(strlen(name) + 1);
		strcpy(m_message.lpFiles[m_message.nFileCount].lpszFileName, name);
	}

	m_message.nFileCount++;
	return TRUE;
}

//----------------------------------------------------------------------------
BOOL CIMapi::Send(ULONG flags){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CWaitCursor wait;
	int			offset = m_text.GetLength();

	//	Add 1 space per attachment at the end of the body text.
	m_text += CString(' ', m_message.nFileCount);

	//	Set each attachment to replace one of the added spaces at the end of the body text.
	for (UINT i = 0; i < m_message.nFileCount; i++)
		m_message.lpFiles[i].nPosition = offset++;

	m_message.lpszNoteText = (LPTSTR) (LPCTSTR) m_text;	//  Set the body text

	// prepare for modal dialog box
	AfxGetApp()->EnableModeless(FALSE);
	HWND hWndTop;
	CWnd* pParentWnd = CWnd::GetSafeOwner(NULL, &hWndTop);

	// some extra precautions are required to use MAPISendMail as it
	// tends to enable the parent window in between dialogs (after
	// the login dialog, but before the send note dialog).
	pParentWnd->SetCapture();
	::SetFocus(NULL);
	pParentWnd->m_nFlags |= WF_STAYDISABLED;

	int nError = m_lpfnSendMail(0, (ULONG) pParentWnd->GetSafeHwnd(), &m_message, MAPI_LOGON_UI | flags, 0);

	// after returning from the MAPISendMail call, the window must
	// be re-enabled and focus returned to the frame to undo the DoCalculatearound
	// done before the MAPI call.
	::ReleaseCapture();
	pParentWnd->m_nFlags &= ~WF_STAYDISABLED;

	pParentWnd->EnableWindow(TRUE);
	::SetActiveWindow(NULL);
	pParentWnd->SetActiveWindow();
	pParentWnd->SetFocus();
	
	if (hWndTop != NULL)
		::EnableWindow(hWndTop, TRUE);
	
	AfxGetApp()->EnableModeless(TRUE);

	//	Now free malloced recipients
	for (i = 0; i < m_message.nRecipCount; i++)
		free(m_message.lpRecips[i].lpszName);

	//	Then free malloced attachments
	for (i = 0; i < m_message.nFileCount; i++)
	{
		free(m_message.lpFiles[i].lpszPathName);
		free(m_message.lpFiles[i].lpszFileName);
	}

	if (nError != SUCCESS_SUCCESS && nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
	{
		AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
		return FALSE;
	}

	return TRUE;
}
