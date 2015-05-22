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
#include "NumSpinCtrl.h"
#include "Application\Debug\LogManager.h"


IMPLEMENT_DYNAMIC(CNumSpinCtrl, CSpinButtonCtrl)

BEGIN_MESSAGE_MAP(CNumSpinCtrl, CSpinButtonCtrl)
	//{{AFX_MSG_MAP(CNumSpinCtrl)
	ON_NOTIFY_REFLECT(UDN_DELTAPOS, OnDeltapos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------
CNumSpinCtrl::CNumSpinCtrl(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
CNumSpinCtrl::~CNumSpinCtrl(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}




//----------------------------------------------------------------------------
void CNumSpinCtrl::SetPos(float val){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CSpinButtonCtrl::SetPos(500);
	CNumEdit *m_Edit = GetBuddy();
	if (m_Edit)
		if (m_Edit->IsKindOf(RUNTIME_CLASS(CNumEdit)))
			m_Edit->SetValue(val);
}

//----------------------------------------------------------------------------
float CNumSpinCtrl::GetPos(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CNumEdit *m_Edit = GetBuddy();
	if (m_Edit)
		if (m_Edit->IsKindOf(RUNTIME_CLASS(CNumEdit)))
			return m_Edit->GetValue();
	return 0.0f;
}

//----------------------------------------------------------------------------
void CNumSpinCtrl::SetRange(float nLower, float nUpper){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CSpinButtonCtrl::SetRange(0, 1000);
	CNumEdit *m_Edit = GetBuddy();
	if (m_Edit)
		if (m_Edit->IsKindOf(RUNTIME_CLASS(CNumEdit)))
			m_Edit->SetRange(nLower, nUpper);
}

//----------------------------------------------------------------------------
void CNumSpinCtrl::GetRange(float & lower, float & upper) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

	CNumEdit *m_Edit = GetBuddy();
	if (m_Edit)
		if (m_Edit->IsKindOf(RUNTIME_CLASS(CNumEdit)))
			m_Edit->GetRange(lower, upper);
}

//----------------------------------------------------------------------------
CNumEdit* CNumSpinCtrl::GetBuddy() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

	return (CNumEdit *)CSpinButtonCtrl::GetBuddy();
}

//----------------------------------------------------------------------------
void CNumSpinCtrl::SetBuddy(CNumEdit * edit){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CSpinButtonCtrl::SetBuddy(edit);
	if (edit)
		if (edit->IsKindOf(RUNTIME_CLASS(CNumEdit)))
			edit->SetValue(0.0f);
}

//----------------------------------------------------------------------------
void CNumSpinCtrl::OnDeltapos(NMHDR* pNMHDR, LRESULT* pResult) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if ((pNMUpDown->iPos <= pNMUpDown->iDelta) ||
		(pNMUpDown->iPos >= 1000 - pNMUpDown->iDelta)) pNMUpDown->iPos = 500;
	CNumEdit *m_Edit = GetBuddy();
	if (m_Edit)
		if (m_Edit->IsKindOf(RUNTIME_CLASS(CNumEdit)))
			m_Edit->ChangeAmount(pNMUpDown->iDelta);
	*pResult = 0;
}

//----------------------------------------------------------------------------
float CNumSpinCtrl::GetDelta(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CNumEdit *m_Edit = GetBuddy();
	if (m_Edit)
		if (m_Edit->IsKindOf(RUNTIME_CLASS(CNumEdit)))
			return m_Edit->GetDelta();
	return 0.0f;
}

//----------------------------------------------------------------------------
void CNumSpinCtrl::SetDelta(float delta){
//----------------------------------------------------------------------------
	PROC_TRACE;

	CNumEdit *m_Edit = GetBuddy();
	if (m_Edit)
		if (m_Edit->IsKindOf(RUNTIME_CLASS(CNumEdit)))
			m_Edit->SetDelta(delta);
}
