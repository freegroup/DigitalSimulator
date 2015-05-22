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

#ifndef AUTOFONT
#define AUTOFONT

class CAutoFont : public CFont
{
private:
	LOGFONT lf;//Stores this fonts LogFont for quick retrieval
	COLORREF fontColor;
	CString GetToken(CString& str, LPCTSTR c);//Used in Expand function
	HDC hDC;

public:
	CAutoFont();//Default Constructor
	CAutoFont(int heigth);//Default Constructor
	CAutoFont(CString facename);//Font name constructor
	CAutoFont(LOGFONT& logfont);//LogFont constructor
	CAutoFont(CFont font);//Constructs font based on existing font
	~CAutoFont();//Destructor

	BOOL CreateStockObject(int nIndex);

	LONG SetHeight(LONG height);
	LONG SetHeightA(LONG height);
	LONG SetWidth(LONG width);
	LONG SetEscapement(LONG esc);
	LONG SetOrientation(LONG or);
	LONG SetWeight(LONG weight);
	BYTE SetCharset(BYTE charset);
	BYTE SetOutPrecision(BYTE op);
	BYTE SetClipPrecision(BYTE cp);
	BYTE SetQuality(BYTE qual);
	BYTE SetPitchAndFamily(BYTE paf);
	CString SetFaceName(CString facename);
	LPCTSTR SetFaceName(LPCTSTR facename);
	BOOL SetBold(BOOL B);
	BOOL SetItalic(BOOL i);
	BOOL SetUnderline(BOOL u);
	BOOL SetStrikeOut(BOOL s);
	void SetLogFont(LOGFONT& logfont);
	void SetFontColor(COLORREF color);
	void SetDC(HDC dc);

	LONG GetHeight();
	LONG GetWidth();
	LONG GetEscapement();
	LONG GetOrientation();
	LONG GetWeight();
	BYTE GetCharset();
	BYTE GetOutPrecision();
	BYTE GetClipPrecision();
	BYTE GetQuality();
	BYTE GetPitchAndFamily();
	LPCTSTR GetFaceName();
	BOOL GetBold();
	BOOL GetItalic();
	BOOL GetUnderline();
	BOOL GetStrikeOut();
	COLORREF GetFontColor();
	CString ContractFont();//Places font info into single string
	void ExtractFont(CString& str);//Parses single string font info.

	void GetFontFromDialog(CFont *f=NULL, DWORD *color=0,CDC *pPrinterDC=NULL, CWnd *pParentWnd=NULL);
};

#endif