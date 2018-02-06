// KUpNetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KUpNet.h"
#include "KUpNetDlg.h"
#include "request.h"
#include "wininet.h"
#include "InetDL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKUpNetDlg dialog

CKUpNetDlg::CKUpNetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKUpNetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKUpNetDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKUpNetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKUpNetDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKUpNetDlg, CDialog)
	//{{AFX_MSG_MAP(CKUpNetDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

const UINT WM_HTTPDOWNLOAD_THREAD_FINISHED = WM_APP + 1;

/////////////////////////////////////////////////////////////////////////////
// CKUpNetDlg message handlers


UINT CKUpNetDlg::_DownloadThread(LPVOID pParam)
{
  //Convert from the SDK world to the C++ world
	/*
  CHttpDownloadDlg* pDlg = (CHttpDownloadDlg*) pParam;
  ASSERT(pDlg);
  ASSERT(pDlg->IsKindOf(RUNTIME_CLASS(CHttpDownloadDlg)));
  */
  DownloadThread((CThInfo*)pParam);
  return 0;
}

BOOL CKUpNetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	char ItHeaders[512];
	BYTE mybuffer[1024];
	DWORD btread;

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here


//	DownloadThread();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKUpNetDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKUpNetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKUpNetDlg::OnCancel() 
{
	if (MessageBox("Are you sure you want to exit the Net Updater?","Quit?",MB_YESNO)==IDYES)
		CDialog::OnCancel();
}

void CKUpNetDlg::OnNext() 
{
	// TODO: Add your control notification handler code here
	EndDialog(3);
}
