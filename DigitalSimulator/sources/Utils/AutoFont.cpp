#include "stdafx.h"
#include "AutoFont.h"

//----------------------------------------------------------------------------
CAutoFont::CAutoFont(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	lf.lfHeight=-12;
	lf.lfWidth=0;
	lf.lfEscapement=0;
	lf.lfOrientation=0;
	lf.lfWeight=FW_NORMAL;
	lf.lfItalic=0;
	lf.lfUnderline=0;
	lf.lfStrikeOut=0;
	lf.lfCharSet=ANSI_CHARSET;
	lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfQuality=PROOF_QUALITY;
	lf.lfPitchAndFamily=VARIABLE_PITCH | FF_ROMAN;
	strcpy(lf.lfFaceName, "Times New Roman");

	CreateFontIndirect(&lf);

	fontColor=0;
	hDC=NULL;
}

//----------------------------------------------------------------------------
CAutoFont::CAutoFont(int height){
//----------------------------------------------------------------------------
	PROC_TRACE;


	lf.lfHeight=-12;
	lf.lfWidth=0;
	lf.lfEscapement=0;
	lf.lfOrientation=0;
	lf.lfWeight=FW_NORMAL;
	lf.lfItalic=0;
	lf.lfUnderline=0;
	lf.lfStrikeOut=0;
	lf.lfCharSet=ANSI_CHARSET;
	lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfQuality=PROOF_QUALITY;
	lf.lfPitchAndFamily=VARIABLE_PITCH | FF_ROMAN;
	strcpy(lf.lfFaceName, "Times New Roman");

	CreateFontIndirect(&lf);

	fontColor=0;
	hDC=NULL;

   SetHeight(height);
}
//----------------------------------------------------------------------------
CAutoFont::CAutoFont(CString facename){
//----------------------------------------------------------------------------
	PROC_TRACE;


	lf.lfHeight=-12;
	lf.lfWidth=0;
	lf.lfEscapement=0;
	lf.lfOrientation=0;
	lf.lfWeight=FW_NORMAL;
	lf.lfItalic=0;
	lf.lfUnderline=0;
	lf.lfStrikeOut=0;
	lf.lfCharSet=ANSI_CHARSET;
	lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfQuality=PROOF_QUALITY;
	lf.lfPitchAndFamily=VARIABLE_PITCH | FF_ROMAN;
	strcpy(lf.lfFaceName, (LPCTSTR)facename);

	CreateFontIndirect(&lf);

	fontColor=0;
	hDC=NULL;
}

//----------------------------------------------------------------------------
CAutoFont::CAutoFont(LOGFONT& logfont){
//----------------------------------------------------------------------------
	PROC_TRACE;


	lf=logfont;
	CreateFontIndirect(&lf);

	fontColor=0;
	hDC=NULL;
}

//----------------------------------------------------------------------------
CAutoFont::CAutoFont(CFont font){
//----------------------------------------------------------------------------
	PROC_TRACE;


	HFONT hFont=(HFONT)font;
	Attach((HFONT)hFont);

	GetLogFont(&lf);

	fontColor=0;
	hDC=NULL;
}

//----------------------------------------------------------------------------
CAutoFont::~CAutoFont(){
//----------------------------------------------------------------------------
	PROC_TRACE;


}

//----------------------------------------------------------------------------
BOOL CAutoFont::CreateStockObject(int nIndex){
//----------------------------------------------------------------------------
	PROC_TRACE;


	ASSERT (nIndex >= OEM_FIXED_FONT && nIndex <=DEFAULT_GUI_FONT);

	BOOL bResult;
	bResult=CFont::CreateStockObject(nIndex);
	if (bResult)
	{
		GetLogFont(&lf);
		DeleteObject();
		CreateFontIndirect(&lf);
	}
	return bResult;
}

//----------------------------------------------------------------------------
LONG CAutoFont::SetHeight(LONG height){
//----------------------------------------------------------------------------
	PROC_TRACE;


	LONG l=lf.lfHeight;

	DeleteObject();
	lf.lfHeight=height;
	CreateFontIndirect(&lf);

	return l;
}

//----------------------------------------------------------------------------
LONG CAutoFont::SetHeightA(LONG height){
//----------------------------------------------------------------------------
	PROC_TRACE;


	LONG l=lf.lfHeight;

	DeleteObject();
	if (height>0)
		height=0-height;
	lf.lfHeight=height * 4;
	lf.lfHeight=(int)lf.lfHeight/3;
	CreateFontIndirect(&lf);

	return l;
}

//----------------------------------------------------------------------------
LONG CAutoFont::SetWidth(LONG width){
//----------------------------------------------------------------------------
	PROC_TRACE;


	LONG l=lf.lfWidth;

	DeleteObject();
	lf.lfWidth=width;
	CreateFontIndirect(&lf);

	return l;
}

//----------------------------------------------------------------------------
LONG CAutoFont::SetEscapement(LONG esc){
//----------------------------------------------------------------------------
	PROC_TRACE;


	LONG l=lf.lfEscapement;

	DeleteObject();
	lf.lfEscapement=esc;
	CreateFontIndirect(&lf);

	return l;
}

//----------------------------------------------------------------------------
LONG CAutoFont::SetOrientation(LONG or){
//----------------------------------------------------------------------------
	PROC_TRACE;


	LONG l=lf.lfOrientation;

	DeleteObject();
	lf.lfOrientation=or;
	CreateFontIndirect(&lf);

	return l;
}

//----------------------------------------------------------------------------
LONG CAutoFont::SetWeight(LONG weight){
//----------------------------------------------------------------------------
	PROC_TRACE;


	LONG l=lf.lfWeight;

	DeleteObject();
	lf.lfWeight=weight;
	CreateFontIndirect(&lf);

	return l;
}

//----------------------------------------------------------------------------
BYTE CAutoFont::SetCharset(BYTE charset){
//----------------------------------------------------------------------------
	PROC_TRACE;


	BYTE b=lf.lfCharSet;

	DeleteObject();
	lf.lfCharSet=charset;
	CreateFontIndirect(&lf);

	return b;
}

//----------------------------------------------------------------------------
BYTE CAutoFont::SetOutPrecision(BYTE op){
//----------------------------------------------------------------------------
	PROC_TRACE;


	BYTE b=lf.lfOutPrecision;

	DeleteObject();
	lf.lfOutPrecision=op;
	CreateFontIndirect(&lf);

	return b;
}

//----------------------------------------------------------------------------
BYTE CAutoFont::SetClipPrecision(BYTE cp){
//----------------------------------------------------------------------------
	PROC_TRACE;


	BYTE b=lf.lfClipPrecision;

	DeleteObject();
	lf.lfClipPrecision=cp;
	CreateFontIndirect(&lf);

	return b;
}

//----------------------------------------------------------------------------
BYTE CAutoFont::SetQuality(BYTE qual){
//----------------------------------------------------------------------------
	PROC_TRACE;


	BYTE b=lf.lfQuality;

	DeleteObject();
	lf.lfQuality=qual;
	CreateFontIndirect(&lf);

	return b;
}

//----------------------------------------------------------------------------
BYTE CAutoFont::SetPitchAndFamily(BYTE paf){
//----------------------------------------------------------------------------
	PROC_TRACE;


	BYTE b=lf.lfPitchAndFamily;

	DeleteObject();
	lf.lfPitchAndFamily=paf;
	CreateFontIndirect(&lf);

	return b;
}

//----------------------------------------------------------------------------
CString CAutoFont::SetFaceName(CString facename){
//----------------------------------------------------------------------------
	PROC_TRACE;


	CString str=lf.lfFaceName;

	DeleteObject();
	strcpy(lf.lfFaceName, (LPCTSTR)facename);
	CreateFontIndirect(&lf);

	return str;
}

//----------------------------------------------------------------------------
LPCTSTR CAutoFont::SetFaceName(LPCTSTR facename){
//----------------------------------------------------------------------------
	PROC_TRACE;


	LPCTSTR str=lf.lfFaceName;

	DeleteObject();
	strcpy(lf.lfFaceName, facename);
	CreateFontIndirect(&lf);

	return str;
}

//----------------------------------------------------------------------------
BOOL CAutoFont::SetBold(BOOL B){
//----------------------------------------------------------------------------
	PROC_TRACE;


	BOOL b;

	if (B)
		b=SetWeight(FW_BOLD);
	else
		b=SetWeight(FW_NORMAL);

	if (b >= FW_MEDIUM)
		return TRUE;
	else
		return FALSE;
}

//----------------------------------------------------------------------------
BOOL CAutoFont::SetItalic(BOOL i){
//----------------------------------------------------------------------------
	PROC_TRACE;


	BOOL b=(BOOL)lf.lfItalic;

	DeleteObject();
	lf.lfItalic=i;
	CreateFontIndirect(&lf);

	return b;
}

//----------------------------------------------------------------------------
BOOL CAutoFont::SetUnderline(BOOL u){
//----------------------------------------------------------------------------
	PROC_TRACE;


	BOOL b=(BOOL)lf.lfUnderline;

	DeleteObject();
	lf.lfUnderline=u;
	CreateFontIndirect(&lf);

	return b;
}

//----------------------------------------------------------------------------
BOOL CAutoFont::SetStrikeOut(BOOL s){
//----------------------------------------------------------------------------
	PROC_TRACE;


	BOOL b=(BOOL)lf.lfStrikeOut;

	DeleteObject();
	lf.lfStrikeOut=s;
	CreateFontIndirect(&lf);

	return b;
}

//----------------------------------------------------------------------------
void CAutoFont::SetLogFont(LOGFONT& logfont){
//----------------------------------------------------------------------------
	PROC_TRACE;


	lf=logfont;
	DeleteObject();
	CreateFontIndirect(&lf);
}

//----------------------------------------------------------------------------
LONG CAutoFont::GetHeight(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfHeight;
}

//----------------------------------------------------------------------------
LONG CAutoFont::GetWidth(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfWidth;
}

//----------------------------------------------------------------------------
LONG CAutoFont::GetEscapement(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfEscapement;
}

//----------------------------------------------------------------------------
LONG CAutoFont::GetOrientation(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfEscapement;
}

//----------------------------------------------------------------------------
LONG CAutoFont::GetWeight(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfWeight;
}

//----------------------------------------------------------------------------
BYTE CAutoFont::GetCharset(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfCharSet;
}

//----------------------------------------------------------------------------
BYTE CAutoFont::GetOutPrecision(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfOutPrecision;
}

//----------------------------------------------------------------------------
BYTE CAutoFont::GetClipPrecision(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfClipPrecision;
}

//----------------------------------------------------------------------------
BYTE CAutoFont::GetQuality(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfQuality;
}

//----------------------------------------------------------------------------
BYTE CAutoFont::GetPitchAndFamily(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfPitchAndFamily;
}

//----------------------------------------------------------------------------
LPCTSTR CAutoFont::GetFaceName(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfFaceName;
}

//----------------------------------------------------------------------------
BOOL CAutoFont::GetBold(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return lf.lfWeight >= FW_MEDIUM ? TRUE : FALSE;
}

//----------------------------------------------------------------------------
BOOL CAutoFont::GetItalic(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return (BOOL)lf.lfItalic;
}

//----------------------------------------------------------------------------
BOOL CAutoFont::GetUnderline(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return (BOOL)lf.lfUnderline;
}

//----------------------------------------------------------------------------
BOOL CAutoFont::GetStrikeOut(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return (BOOL)lf.lfStrikeOut;
}

//----------------------------------------------------------------------------
CString CAutoFont::ContractFont(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	CString str, color;

	str.Format("%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%s",
		lf.lfHeight,
		lf.lfWidth,
		lf.lfEscapement,
		lf.lfOrientation,
		lf.lfWeight,
		lf.lfItalic,
		lf.lfUnderline,
		lf.lfStrikeOut,
		lf.lfCharSet,
		lf.lfOutPrecision,
		lf.lfClipPrecision,
		lf.lfQuality,
		lf.lfPitchAndFamily,
		lf.lfFaceName);
	color.Format("%u", fontColor);
	str+=",";
	str+=color;

	return str;
}

//----------------------------------------------------------------------------
void CAutoFont::ExtractFont(CString& str){
//----------------------------------------------------------------------------
	PROC_TRACE;


	lf.lfHeight=atol((LPCTSTR)GetToken(str, ","));
	lf.lfWidth=atol((LPCTSTR)GetToken(str, ","));
	lf.lfEscapement=atol((LPCTSTR)GetToken(str, ","));
	lf.lfOrientation=atol((LPCTSTR)GetToken(str, ","));
	lf.lfWeight=atol((LPCTSTR)GetToken(str, ","));
	lf.lfItalic=atoi((LPCTSTR)GetToken(str, ","));
	lf.lfUnderline=atoi((LPCTSTR)GetToken(str, ","));
	lf.lfStrikeOut=atoi((LPCTSTR)GetToken(str, ","));
	lf.lfCharSet=atoi((LPCTSTR)GetToken(str, ","));
	lf.lfOutPrecision=atoi((LPCTSTR)GetToken(str, ","));
	lf.lfClipPrecision=atoi((LPCTSTR)GetToken(str, ","));
	lf.lfQuality=atoi((LPCTSTR)GetToken(str, ","));
	lf.lfPitchAndFamily=atoi((LPCTSTR)GetToken(str, ","));
	strcpy(lf.lfFaceName, (LPCTSTR)GetToken(str, ","));

	DeleteObject();
	CreateFontIndirect(&lf);

	fontColor=atol((LPCTSTR)str);
}

//----------------------------------------------------------------------------
CString CAutoFont::GetToken(CString& str, LPCTSTR c){
//----------------------------------------------------------------------------
	PROC_TRACE;


	int pos;
	CString token;

	pos=str.Find(c);
	token=str.Left(pos);
	str=str.Mid(pos+1);

	return token;
}

void CAutoFont::GetFontFromDialog(CFont *f, DWORD *color,
				CDC *pPrinterDC, CWnd *pParentWnd)
{
	PROC_TRACE;

	LOGFONT tlf;
	if (f==NULL)
		tlf=lf;
	else
		f->GetLogFont(&tlf);

	CFontDialog dlg(&tlf, CF_EFFECTS | CF_SCREENFONTS,
		pPrinterDC, pParentWnd);
	dlg.m_cf.rgbColors=fontColor;
	
	if (dlg.DoModal()==IDOK)
	{
		dlg.GetCurrentFont(&lf);
		DeleteObject();
		CreateFontIndirect(&lf);
		f=(CFont *)this;
		color=&dlg.m_cf.rgbColors;
		SetFontColor(dlg.m_cf.rgbColors);
	}
}

//----------------------------------------------------------------------------
void CAutoFont::SetFontColor(COLORREF color){
//----------------------------------------------------------------------------
	PROC_TRACE;


	fontColor=color;
	if (hDC!=NULL)
		::SetTextColor(hDC, color);
}

//----------------------------------------------------------------------------
COLORREF CAutoFont::GetFontColor(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	return fontColor;
}

//----------------------------------------------------------------------------
void CAutoFont::SetDC(HDC dc){
//----------------------------------------------------------------------------
	PROC_TRACE;


	hDC=dc;
}