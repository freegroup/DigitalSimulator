// DialogOsziOptions.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "Application\DigitalSimulatorApp.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Dialogs\ColorSpaceDialog/ColorPickerDlg.h"

#include "DialogOsziOptions.h"

BEGIN_MESSAGE_MAP(CDialogOsziOptions, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogOsziOptions)
	ON_BN_CLICKED(IDC_BG_COLOR, OnBgColor)
	ON_BN_CLICKED(IDC_FG_COLOR, OnFgColor)
	ON_BN_CLICKED(IDC_USE_IT, OnUseIt)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CDialogOsziOptions::CDialogOsziOptions(CWnd* pParent /*=NULL*/): inherited(CDialogOsziOptions::IDD, pParent){
//----------------------------------------------------------------------------
	PROC_TRACE;

	//{{AFX_DATA_INIT(CDialogOsziOptions)
	//}}AFX_DATA_INIT
}

//----------------------------------------------------------------------------
void CDialogOsziOptions::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogOsziOptions)
	DDX_Control(pDX, IDC_FG_COLOR, m_fgColorButton);
	DDX_Control(pDX, IDC_BG_COLOR, m_bgColorButton);
	DDX_Control(pDX, IDC_USE_IT, m_useitButton);
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_ZOOM_SPIN, m_zoomSpin);
	DDX_Control(pDX, IDC_ZOOM_EDIT, m_zoomEdit);
	DDX_Control(pDX, IDC_GRID_CHECK, m_gridCheck);
	DDX_Control(pDX, IDC_GRID_X_EDIT, m_xEdit);
	DDX_Control(pDX, IDC_GRID_Y_EDIT, m_yEdit);
	DDX_Control(pDX, IDC_Y_SPIN, m_ySpin);
	DDX_Control(pDX, IDC_X_SPIN, m_xSpin);
	//}}AFX_DATA_MAP
}


//----------------------------------------------------------------------------
void CDialogOsziOptions::OnBgColor() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   CColorPickerDlg dlg(m_bgColor);
   if(dlg.DoModal() == IDOK)
   {
      m_bgColor=dlg.GetColor();
      Invalidate();
   }
}

//----------------------------------------------------------------------------
void CDialogOsziOptions::OnFgColor() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   CColorPickerDlg dlg(m_fgColor);
   if(dlg.DoModal() == IDOK)
   {
      m_fgColor=dlg.GetColor();
      Invalidate();
   }
}

//----------------------------------------------------------------------------
void CDialogOsziOptions::OnUseIt() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	CString x;
	CString y;
	CString zoom;
	x.Format("%d", (int)m_xSpin.GetPos());
	y.Format("%d", (int)m_ySpin.GetPos());
	zoom.Format("%d", (int)m_zoomSpin.GetPos());
   SET_PARAMETER("OsziGridX"   , (LPCSTR)x);
   SET_PARAMETER("OsziGridY"   , (LPCSTR)y);
   SET_PARAMETER("OsziZoom"    , (LPCSTR)zoom);

	CString bgColor;
	CString fgColor;
	bgColor.Format("%d", m_bgColor);
	fgColor.Format("%d", m_fgColor);
   SET_PARAMETER("OsziBgColor",bgColor);
   SET_PARAMETER("OsziFgColor",fgColor);
   SET_PARAMETER("OsziGrid",m_gridCheck.GetCheck()==TRUE? "On" :"Off");
}

//----------------------------------------------------------------------------
void CDialogOsziOptions::OnOK() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   OnUseIt();
   
	inherited::OnOK();
}

//----------------------------------------------------------------------------
BOOL CDialogOsziOptions::OnInitDialog() {
//----------------------------------------------------------------------------
	PROC_TRACE;

	inherited::OnInitDialog();
	
   TRANSLATE_DIALOG_ITEM(IDOK);
   TRANSLATE_DIALOG_ITEM(IDCANCEL);
   TRANSLATE_DIALOG_ITEM(IDC_GRID_X_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_GRID_Y_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_USE_IT);
   TRANSLATE_DIALOG_ITEM(IDC_BG_COLOR_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_FG_COLOR_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_GRID_CHECK);
   TRANSLATE_DIALOG_ITEM(IDC_DIRECTION_CHECK);
   TRANSLATE_DIALOG_ITEM(IDC_ZOOM_STATIC);
   TRANSLATE_DIALOG_ITEM(IDC_FG_COLOR);
   TRANSLATE_DIALOG_ITEM(IDC_BG_COLOR);

   m_fgColorButton.SetShaded();
   m_bgColorButton.SetShaded();
   m_okButton.SetShaded();
   m_cancelButton.SetShaded();
   m_useitButton.SetShaded();

   SetWindowText(TRANSLATE("COMMON.DIALOGHEADER.OSZIOPTIONS"));

   m_zoomSpin.SetBuddy(&m_zoomEdit);
	m_zoomSpin.SetRange(50, 500.);
	m_zoomSpin.SetPos(min(500,max(50,atoi(GET_PARAMETER("OsziZoom")))));
	m_zoomSpin.SetDelta(10);

   m_xSpin.SetBuddy(&m_xEdit);
	m_xSpin.SetRange(50, 200.);
	m_xSpin.SetPos(min(200,max(50,atoi(GET_PARAMETER("OsziGridX")))));
	m_xSpin.SetDelta(10);

	m_ySpin.SetBuddy(&m_yEdit);
	m_ySpin.SetRange(50, 200.);
	m_ySpin.SetPos(min(200,max(50,atoi(GET_PARAMETER("OsziGridY")))));
	m_ySpin.SetDelta(10);
	
   int color = atoi(GET_PARAMETER("OsziBgColor"));
   m_bgColor= color;
    
   color = atoi(GET_PARAMETER("OsziFgColor"));
   m_fgColor=color;

   m_gridCheck.SetCheck((GET_PARAMETER("OsziGrid") == "On") ? TRUE :FALSE);

	GetDlgItem(IDC_FG_STATIC)->GetWindowRect(&m_fgRect);
	GetDlgItem(IDC_BG_STATIC)->GetWindowRect(&m_bgRect);
	ScreenToClient(&m_fgRect);
	ScreenToClient(&m_bgRect);

   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDialogOsziOptions::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	DrawFilledColor(&dc,m_fgRect,m_fgColor);
	DrawFilledColor(&dc,m_bgRect,m_bgColor);
}

void CDialogOsziOptions::DrawFilledColor(CDC *pDC,CRect cr,COLORREF c)
{
	pDC->FillSolidRect(&cr,c);
	pDC->Draw3dRect(&cr,RGB(0,0,0),RGB(0,0,0));
	cr.InflateRect(-1,-1);
	pDC->Draw3dRect(&cr,RGB(192,192,192),RGB(128,128,128));
}
