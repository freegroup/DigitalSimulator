#include "stdafx.h"
#include "resource.h"
#include "FindFileDlg.h"
#include "FileFinder.h"

UINT _SearchForFile(void *p);
#define ICONS 11
HICON g_FindFileIconArray[ICONS];


BEGIN_MESSAGE_MAP(CFindFileDlg, CSnapDialog)
	//{{AFX_MSG_MAP(CFindFileDlg)
	ON_BN_CLICKED(ID_STOP, OnStop)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_BEGIN_SEARCH, OnBegin)
END_MESSAGE_MAP()


CFindFileDlg::CFindFileDlg(CWnd* pParent /*=NULL*/)
	: inherited(CFindFileDlg::IDD, pParent)
{
	PROC_TRACE;

	//{{AFX_DATA_INIT(CFindFileDlg)
	//}}AFX_DATA_INIT

	m_bInThread = false;

	m_bFindSingleFile = false;	
	m_bRecurse = true;
	m_bCancel = false;
	
	m_bSearchNetworkDrives = false;
	m_bSearchRemovableDrives = false;
	m_bSearchCDROMDrives = false;

	m_bCancel = false;

	m_iCurIcon = 0;

	m_csTitle = "Searching for the file...";

	g_FindFileIconArray[0]  = AfxGetApp()->LoadIcon(IDI_SEARCH01);
	g_FindFileIconArray[1]  = AfxGetApp()->LoadIcon(IDI_SEARCH02);
	g_FindFileIconArray[2]  = AfxGetApp()->LoadIcon(IDI_SEARCH03);
	g_FindFileIconArray[3]  = AfxGetApp()->LoadIcon(IDI_SEARCH04);
	g_FindFileIconArray[4]  = AfxGetApp()->LoadIcon(IDI_SEARCH05);
	g_FindFileIconArray[5]  = AfxGetApp()->LoadIcon(IDI_SEARCH06);
	g_FindFileIconArray[6]  = AfxGetApp()->LoadIcon(IDI_SEARCH07);
	g_FindFileIconArray[7]  = AfxGetApp()->LoadIcon(IDI_SEARCH08);
	g_FindFileIconArray[8]  = AfxGetApp()->LoadIcon(IDI_SEARCH09);
	g_FindFileIconArray[9]  = AfxGetApp()->LoadIcon(IDI_SEARCH10);
	g_FindFileIconArray[10] = AfxGetApp()->LoadIcon(IDI_SEARCH11);
}

//////////////////////////////////////////////////////////////////////

void CFindFileDlg::DoDataExchange(CDataExchange* pDX)
{
	PROC_TRACE;

	inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindFileDlg)
	DDX_Control(pDX, IDC_PROCESS_STATIC, m_processStatic);
	DDX_Control(pDX, ID_STOP, m_stopButton);
	//}}AFX_DATA_MAP
}


BOOL CFindFileDlg::OnInitDialog() 
{
	PROC_TRACE;

	inherited::OnInitDialog();

	UpdateData(FALSE);

	SetWindowText(m_csTitle);
   m_stopButton.SetShaded();

	m_processStatic.SetMax(50);
	m_processStatic.SetStep(1);
	m_processStatic.SetGradientFill(RGB(192,192,192),RGB(238,248,238));
	m_processStatic.SetBkColor(RGB(192,192,192));
	m_processStatic.SetSize(20);
   m_processStatic.StepIt();		

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////

void CFindFileDlg::OnCancel() 
{
	PROC_TRACE;

	if (!m_bInThread)
	{
		inherited::OnCancel();
	}
	else
	{
		m_bCancel = true;
	}
}


void CFindFileDlg::MsgPump(DWORD dwLen)
{
	PROC_TRACE;

	MSG m_msgCur;                   // current message

	CWinApp	*pWinApp = AfxGetApp();                     

    DWORD dInitTime = GetTickCount();

	while (::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE)  &&
			(GetTickCount() - dInitTime < dwLen) )
	{
		pWinApp->PumpMessage();
	}

}


void CFindFileDlg::OnStop() 
{
	PROC_TRACE;

	m_bCancel = true;
}


void CFindFileDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	PROC_TRACE;

	inherited::OnShowWindow(bShow, nStatus);
	
	PostMessage(WM_BEGIN_SEARCH);
}


long CFindFileDlg::OnBegin(UINT u, LONG l)
{
	PROC_TRACE;

	SetTimer(1, 50, NULL);

	// this will protect our data while the two threads access it
	InitializeCriticalSection(&g_findFileCritSection);

	// our shared data space
	searchStruct	ss;
	ss.m_bFindSingleFile		= m_bFindSingleFile;
	ss.m_csFindFile				= m_csFindFile;
	ss.m_bRecurse				= m_bRecurse;
	ss.m_csRootFolder			= m_csRootFolder;
	ss.m_bSearchNetworkDrives	= m_bSearchNetworkDrives;
	ss.m_bSearchRemovableDrives = m_bSearchRemovableDrives;
	ss.m_bSearchCDROMDrives		= m_bSearchCDROMDrives;

	ss.m_csaFoundFiles.RemoveAll();

	ss.m_bDone = false;
	ss.m_bOk = true;
	ss.m_bCancel = false;
	
	// create the thread
	CWinThread * pThread = AfxBeginThread(_SearchForFile, (LPVOID)&ss, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);

	// be nice
	if (pThread==NULL)
	{
		AfxMessageBox("Thread Creation Failed", MB_ICONEXCLAMATION);
	}
	else
	{

		// here we go!
		m_bInThread = true;

		// whee!!!
		pThread->ResumeThread();

		// while the thread is still alive...
		while (!GET_SAFE(ss.m_bDone)) 
		{
			// have we been cancelled?
			if (m_bCancel)
			{
				//if (!GET_SAFE(ss.m_bDone))
				{
					SET_SAFE(ss.m_bCancel, true);
				}
			}
			// push some msgs around
			MsgPump();
		}

		// done (the thread said so)
		m_bInThread = false;
		m_bCancel = false;
	}

	// don't need this any more
	DeleteCriticalSection(&g_findFileCritSection);

	// copy to output
	m_csaFoundFiles.RemoveAll();
	m_csaFoundFiles.Copy(ss.m_csaFoundFiles);

	KillTimer(1);

	if (ss.m_bOk)
	{
		inherited::OnOK();
	}
	else
	{
		inherited::OnCancel();
	}
	
	return 0L;
}

//////////////////////////////////////////////////////////////////////

UINT _SearchForFile(void *p)
{
	PROC_TRACE;

	// this is serious trouble...
	if (p==NULL)
	{
		return 0L;
	}

	// let this class do all of the work for us
	CFileFinder finder((searchStruct *)p);
	
	// do it
	bool ok = finder.FindFile();

	// set the output status
	SET_SAFE(((searchStruct *)p)->m_bOk, ok);

 	SET_SAFE(((searchStruct *)p)->m_bDone, true);

	AfxEndThread(0, TRUE);

	return 0;
}

//////////////////////////////////////////////////////////////////////

void CFindFileDlg::OnTimer(UINT nIDEvent) 
{
	PROC_TRACE;

	if (nIDEvent==1)
	{
      m_processStatic.StepIt();		
		return;
	}
	
	inherited::OnTimer(nIDEvent);
}
