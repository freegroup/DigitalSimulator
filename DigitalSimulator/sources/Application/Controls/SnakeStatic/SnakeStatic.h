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

#if !defined(AFX_EZSNAKECTRL_H__0FB972C1_9D3E_11D1_9D77_90672FE32418__INCLUDED_)
#define AFX_EZSNAKECTRL_H__0FB972C1_9D3E_11D1_9D77_90672FE32418__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CEZSnakeCtrl : public CStatic
{
public:
	CEZSnakeCtrl();

	int GetMax();
	void ResetProgress();
	int GetTail();
	COLORREF GetGradientEndColor();
	COLORREF GetGradientStartColor();
	COLORREF GetBkColor();
	BOOL IsReverse();
	int GetSize();
	int GetStep();
	int GetPos();
	void SetMax(int nMax);
	void SetStep(int nStep);
	int StepIt();
	void SetGradientFill(COLORREF clrStart,COLORREF clrEnd);
	void SetBkColor(COLORREF clrFG);
	void SetSize(int nSize);
	virtual ~CEZSnakeCtrl();

protected:
	int SafeStepTail();
	int SafeStepHead();
	void DrawGradient(CDC *pDC,CRect rcGrad);
	//{{AFX_MSG(CEZSnakeCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bTimeForTail;
	BOOL m_bReverse;

	int m_nStep;
	int m_nPos;
	int m_nTail;
	int m_nSize;
	int m_nMax;
	
	COLORREF m_clrBk;
	COLORREF m_clrEnd;
	COLORREF m_clrStart;
	COLORREF m_clrCurEnd;
	COLORREF m_clrCurStart;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EZSNAKECTRL_H__0FB972C1_9D3E_11D1_9D77_90672FE32418__INCLUDED_)
