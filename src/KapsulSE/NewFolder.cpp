// NewFolder.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "NewFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewFolder dialog


CNewFolder::CNewFolder(CWnd* pParent /*=NULL*/)
	: CDialog(CNewFolder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewFolder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNewFolder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewFolder)
	DDX_Control(pDX, IDC_LIBNEWFOLDER2, m_FolderLib2);
	DDX_Control(pDX, IDC_LIBNEWFOLDER, m_FolderLib1);
	DDX_Control(pDX, IDC_FOLDERNAME, m_FolderName);
	DDX_Control(pDX, IDC_FOLDEREXT, m_FolderExt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewFolder, CDialog)
	//{{AFX_MSG_MAP(CNewFolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewFolder message handlers

void CNewFolder::OnOK() 
{

	m_FolderExt.GetWindowText(FolderExt);
	m_FolderName.GetWindowText(FolderName);
	if ( (!FolderName.IsEmpty())&&(!FolderExt.IsEmpty()) )
		CDialog::OnOK();
}

BOOL CNewFolder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
