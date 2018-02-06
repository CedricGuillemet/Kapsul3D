// KBrowseFolder.cpp : implementation file
//

#include "stdafx.h"
//#include "kore.h"
#include "KBrowseFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKBrowseFolder dialog


CKBrowseFolder::CKBrowseFolder(CWnd* pParent /*=NULL*/)
	: CDialog(CKBrowseFolder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKBrowseFolder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CKBrowseFolder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKBrowseFolder)
	DDX_Control(pDX, IDC_BTOK, m_Ok);
	DDX_Control(pDX, IDC_BTCANCEL, m_Cancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKBrowseFolder, CDialog)
	//{{AFX_MSG_MAP(CKBrowseFolder)
	ON_BN_CLICKED(IDC_BTOK, OnBtok)
	ON_BN_CLICKED(IDC_BTCANCEL, OnBtcancel)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKBrowseFolder message handlers

void CKBrowseFolder::OnBtok() 
{
	// TODO: Add your control notification handler code here
	m_Folder=m_TreeCtl.GetSelectedPath();
	OnClose();
	CDialog::OnOK();
}

void CKBrowseFolder::OnBtcancel() 
{
	OnClose();
	CDialog::OnCancel();
}

BOOL CKBrowseFolder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_TreeCtl.Create(WS_VISIBLE | WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS, CRect(8,10,210,310), this, 100);

	WINDOWPLACEMENT wp;
	CString RegSection="BrowseFolder";
	wp.length=sizeof(WINDOWPLACEMENT);

	wp.flags=AfxGetApp()->GetProfileInt (RegSection,"flags",-1);
	wp.showCmd=AfxGetApp()->GetProfileInt (RegSection,"showCmd",0);
	wp.ptMinPosition.x=AfxGetApp()->GetProfileInt (RegSection,"ptMinPositionx",0);
	wp.ptMinPosition.y=AfxGetApp()->GetProfileInt (RegSection,"ptMinPositiony",0);
	wp.ptMaxPosition.x=AfxGetApp()->GetProfileInt (RegSection,"ptMaxPositionx",0);
	wp.ptMaxPosition.y=AfxGetApp()->GetProfileInt (RegSection,"ptMaxPositiony",0);
	wp.rcNormalPosition.left=AfxGetApp()->GetProfileInt (RegSection,"rcNormalPositionl",0);
	wp.rcNormalPosition.right=AfxGetApp()->GetProfileInt (RegSection,"rcNormalPositionr",300);
	wp.rcNormalPosition.top=AfxGetApp()->GetProfileInt (RegSection,"rcNormalPositiont",0);
	wp.rcNormalPosition.bottom=AfxGetApp()->GetProfileInt (RegSection,"rcNormalPositionb",300);

    if (wp.flags!=-1)
    {
	    SetWindowPlacement(&wp);
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKBrowseFolder::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (IsWindow(m_TreeCtl))
	{
		m_TreeCtl.MoveWindow(8,8,cx-16,cy-16-25);
		m_Ok.MoveWindow(cx-80-8,cy-8-22,80,22);
		m_Cancel.MoveWindow(cx-80-8-80,cy-8-22,80,22);
		
	}
	
}

void CKBrowseFolder::OnClose() 
{
	WINDOWPLACEMENT wp;
	CString RegSection="BrowseFolder";

	wp.length=sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&wp);

	AfxGetApp()->WriteProfileInt(RegSection,"flags",wp.flags);
	AfxGetApp()->WriteProfileInt(RegSection,"showCmd",wp.showCmd);
	AfxGetApp()->WriteProfileInt(RegSection,"ptMinPositionx",wp.ptMinPosition.x);
	AfxGetApp()->WriteProfileInt(RegSection,"ptMinPositiony",wp.ptMinPosition.y);
	AfxGetApp()->WriteProfileInt(RegSection,"ptMaxPositionx",wp.ptMaxPosition.x);
	AfxGetApp()->WriteProfileInt(RegSection,"ptMaxPositiony",wp.ptMaxPosition.y);
	AfxGetApp()->WriteProfileInt(RegSection,"rcNormalPositionl",wp.rcNormalPosition.left);
	AfxGetApp()->WriteProfileInt(RegSection,"rcNormalPositionr",wp.rcNormalPosition.right);
	AfxGetApp()->WriteProfileInt(RegSection,"rcNormalPositiont",wp.rcNormalPosition.top);
	AfxGetApp()->WriteProfileInt(RegSection,"rcNormalPositionb",wp.rcNormalPosition.bottom);

	
	CDialog::OnClose();
}
