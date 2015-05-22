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
#include "NumEdit.h"
#include "Float.h"
#include "Application\Debug\LogManager.h"


IMPLEMENT_DYNAMIC(CNumEdit, CEdit)
BEGIN_MESSAGE_MAP(CNumEdit, CEdit)
	//{{AFX_MSG_MAP(CNumEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
CNumEdit::CNumEdit(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_NumberOfNumberAfterPoint = 0;
	m_Verbose = FALSE;
	m_MinValue = -FLT_MAX;
	m_MaxValue = FLT_MAX;
	m_Delta = FLT_ROUNDS;
}

//----------------------------------------------------------------------------
CNumEdit::~CNumEdit(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}



//----------------------------------------------------------------------------
float CNumEdit::GetValue() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

	float f = 0.0f;
	if (IsValid() == VALID)
	{
		CString str;
		GetWindowText(str);
		sscanf(str, "%f", &f);
	}
	return f;
}

//----------------------------------------------------------------------------
BOOL CNumEdit::SetValue(float val){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (val > m_MaxValue || val < m_MinValue) return FALSE;
	CString str, s;
	str.Format(ConstructFormat(s, val), val);
	SetWindowText(str);
	return TRUE;
}

//----------------------------------------------------------------------------
int CNumEdit::IsValid() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

	CString str;
	GetWindowText(str);
	int res = VALID;
	float f;
	char lp[10];
	if (sscanf(str, "%f%s", &f, lp) != 1) res = INVALID_CHAR;
	if (f > m_MaxValue || f < m_MinValue) res = OUT_OF_RANGE;
	if (m_Verbose && res != VALID)
	{
		str.Empty();
		if (res & OUT_OF_RANGE) str += _T("Given value is out of range.\n");
		if (res & INVALID_CHAR) str += _T("Characters must be a number.\n");
		AfxMessageBox(str, MB_OK | MB_ICONSTOP);
	}
	return res;
}

//----------------------------------------------------------------------------
int CNumEdit::IsValid(const CString &str) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

	int res = VALID;
	float f;
	char lp[10];
	if (sscanf(str, "%f%s", &f, lp) != 1) res = INVALID_CHAR;
	if (f > m_MaxValue && f < m_MinValue) res = OUT_OF_RANGE;
	if (m_Verbose && res != VALID)
	{
		CString msg;
		msg.Empty();
		if (res & OUT_OF_RANGE) msg += _T("Given value is out of range.\n");
		if (res & INVALID_CHAR) msg += _T("Characters must be a number.\n");
		AfxMessageBox(str, MB_OK | MB_ICONSTOP);
	}
	return res;
}

//----------------------------------------------------------------------------
void CNumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (nChar == ' ') return;
	float oldValue;
	oldValue = GetValue();
	CEdit::OnChar(nChar, nRepCnt, nFlags);
	if (IsValid() != VALID)
	{
		SetValue(oldValue);
		SetSel(0, -1);
		MSG msg;
		while (::PeekMessage(&msg, m_hWnd, WM_CHAR, WM_CHAR, PM_REMOVE));
	} else
	{
		CString s;
		ConstructFormat(s, GetValue());
	}
}

//----------------------------------------------------------------------------
BOOL CNumEdit::Verbose() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

	return m_Verbose;
}

//----------------------------------------------------------------------------
void CNumEdit::Verbose(BOOL v){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_Verbose = v;
}

//----------------------------------------------------------------------------
void CNumEdit::SetRange(float min, float max){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_MinValue = min;
	m_MaxValue = max;
}

//----------------------------------------------------------------------------
void CNumEdit::GetRange(float & min, float & max) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

	min = m_MinValue;
	max = m_MaxValue;
}

//----------------------------------------------------------------------------
void CNumEdit::SetDelta(float delta){
//----------------------------------------------------------------------------
	PROC_TRACE;

	m_Delta = delta;
}

//----------------------------------------------------------------------------
float CNumEdit::GetDelta(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	return m_Delta;
}

//----------------------------------------------------------------------------
void CNumEdit::ChangeAmount(int step){
//----------------------------------------------------------------------------
	PROC_TRACE;

	float f = GetValue() + step * m_Delta;
	if (f > m_MaxValue) f = m_MaxValue;
	else if (f < m_MinValue) f = m_MinValue;
	SetValue(f);
}

//----------------------------------------------------------------------------
CString& CNumEdit::ConstructFormat(CString &str, float num){
//----------------------------------------------------------------------------
	PROC_TRACE;

	str.Format("%G", num);
	int n = str.Find('.');
	if (n >= 0)
	{
		n = str.GetLength() - n - 1;
		if (n > m_NumberOfNumberAfterPoint) m_NumberOfNumberAfterPoint = n;
	}
	str.Format("%%.%df", m_NumberOfNumberAfterPoint);
	return str;
}
