#include "stdafx.h"

//#include "memmgr/mmgr.h"

#include "resource.h"

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_EXPLORER1, m_Explorer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT7App message handlers


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char	buf[MAX_PATH];
	GetTempPath(sizeof(buf) - 1, buf);

	// Our Help page uses an image, which is also in the resources...
	CString	tempFileName = CString(buf) + "About_Kapsul.jpg";
	WriteResourceToDisk(tempFileName,IDR_ABOUTKAPSUL,"IMAGES");
	tempFileName = CString(buf) + "About_esque.jpg";
	WriteResourceToDisk(tempFileName,IDR_ABOUTESQUE,"IMAGES");
	tempFileName = CString(buf) + "About_Kapsul.html";
	if (WriteResourceToDisk(tempFileName,IDR_ABOUT, RT_HTML))
	{
		COleVariant varEmpty;
		m_Explorer.Navigate(tempFileName, &varEmpty, &varEmpty, &varEmpty, &varEmpty);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
