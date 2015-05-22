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

#if !defined(AFX_MYFXB_H)
#define AFX_MYFXB_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CxDib class
/////////////////////////////////////////////////////////////////////////////
#define HDIB HANDLE
#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi))==sizeof(BITMAPINFOHEADER))
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)
#define BFT_ICON   0x4349   // 'IC'
#define BFT_BITMAP 0x4d42   // 'BM'
#define BFT_CURSOR 0x5450   // 'PT'

class CxDib
{
public:
	CxDib();
	~CxDib();
	HDIB Create(DWORD dwWidth, DWORD dwHeight, WORD wBitCount);
	void Clear(BYTE bval=0);
	void Clone(CxDib *src);
	BOOL IsValid();
	long GetSize();
	BYTE* GetBits();
	DWORD GetHeight() {return m_bi.biHeight;};
	DWORD GetWidth() {return m_bi.biWidth;};
	DWORD GetLineWidth() {return m_LineWidth;};
	WORD GetNumColors() {return m_nColors;};
	WORD GetBitCount() {return m_bi.biBitCount;};
	WORD GetPaletteSize();
	BYTE GetPixelIndex(long x,long y);
	RGBQUAD GetPaletteIndex(BYTE idx);
	RGBQUAD GetPixelColor(long x,long y);
	BYTE GetNearestIndex(RGBQUAD c);
	long Draw(HDC pDC, long xoffset, long yoffset);
	long Stretch(HDC pDC, long xoffset, long yoffset, long xsize, long ysize);
	void BlendPalette(COLORREF cr,long perc);
	void SetPaletteIndex(BYTE idx, BYTE r, BYTE g, BYTE b);
	void SetPaletteIndex(BYTE idx, RGBQUAD c);
	void SetPaletteIndex(BYTE idx, COLORREF cr);
	void SetPixelColor(long x,long y,RGBQUAD c);
	void SetPixelIndex(long x,long y,BYTE i);
	void SetPixelColor(long x,long y,COLORREF cr);
	void SetGrayPalette();
	long WriteBMP(LPSTR bmpFileName);
	RGBQUAD HSLtoRGB(COLORREF cHSLColor);
	RGBQUAD RGB2RGBQUAD(COLORREF cr);
	COLORREF RGBQUAD2RGB (RGBQUAD c);
	RGBQUAD RGBtoHSL(RGBQUAD lRGBColor);
	RGBQUAD HSLtoRGB(RGBQUAD lHSLColor);
protected:
	HDIB hDib;
    BITMAPINFOHEADER    m_bi;
	DWORD m_LineWidth;
	WORD  m_nColors;
	bool IsWin30Dib();
	WORD HueToRGB(WORD n1,WORD n2,WORD hue);
};
/////////////////////////////////////////////////////////////////////////////
// CxShadeButton window

#define SHS_NOISE 0
#define SHS_DIAGSHADE 1
#define SHS_HSHADE 2
#define SHS_VSHADE 3
#define SHS_HBUMP 4
#define SHS_VBUMP 5
#define SHS_SOFTBUMP 6
#define SHS_HARDBUMP 7
#define SHS_METAL 8

class CxShadeButton : public CButton
{
// Construction
public:
	CxShadeButton();
// Attributes
private:
// Operations
public:
// Overrides
   // ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxShadeButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL


// Implementation
public:
	void SetFlat(bool bFlag);
	void SetTextAlign(UINT nTextAlign);
	void SetIcon(UINT nIcon, UINT nIconAlign=BS_CENTER);
	void SetShade(UINT shadeID=0,BYTE granularity=8,BYTE highlight=10,BYTE coloring=0,COLORREF color=0);
   void SetShaded();
	void SetToolTipText(CString s);
	COLORREF SetTextColor(COLORREF new_color);
	virtual ~CxShadeButton();
	// Generated message map functions
protected:
	CxDib m_dNormal,m_dDown,m_dDisabled,m_dOver,m_dh,m_dv;
    bool m_tracking;
    bool m_button_down;
	void RelayEvent(UINT message, WPARAM wParam, LPARAM lParam);
	CToolTipCtrl m_tooltip;
	short	m_FocusRectMargin;		//dotted margin offset
	COLORREF m_TextColor;			//button text color
	BOOL	m_Border;				//0=flat; 1=3D;
	HICON	m_Icon;
	CRect	m_IconBox;
	UINT	m_TextAlign;
	UINT	m_IconAlign;
	bool	m_flat;
	//{{AFX_MSG(CxShadeButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnClicked();
	afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_MYFXB_H)
