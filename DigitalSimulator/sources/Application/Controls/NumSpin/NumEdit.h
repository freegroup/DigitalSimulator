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

#if !defined(AFX_NUMEDIT_H__7482F7FF_A479_11D2_A6A7_00600844997A__INCLUDED_)
#define AFX_NUMEDIT_H__7482F7FF_A479_11D2_A6A7_00600844997A__INCLUDED_
#pragma warning(disable : 4786)


class  CNumEdit : public CEdit{
   typedef CEdit inherited;
public:
	CNumEdit();

// Attributes
public:
	enum {VALID = 0x00, OUT_OF_RANGE = 0x01, INVALID_CHAR = 0x02};
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void ChangeAmount(int step);
	virtual float GetDelta();
	virtual void SetDelta(float delta);
	virtual void GetRange(float &min, float &max)const; 
	virtual void SetRange(float min, float max);
	virtual void Verbose(BOOL v);
	virtual BOOL Verbose()const; 
	virtual int IsValid()const; 
	virtual int IsValid(const CString &str)const; 

	virtual BOOL SetValue(float val);
	virtual float GetValue()const; 
	virtual ~CNumEdit();

	// Generated message map functions
protected:
	virtual CString& ConstructFormat(CString &str, float num);
	BYTE m_NumberOfNumberAfterPoint;
	BOOL m_Verbose;
	float m_Delta, m_MinValue, m_MaxValue;
	//{{AFX_MSG(CNumEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CNumEdit)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMEDIT_H__7482F7FF_A479_11D2_A6A7_00600844997A__INCLUDED_)
