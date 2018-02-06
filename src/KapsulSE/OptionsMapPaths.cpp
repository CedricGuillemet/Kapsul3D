// OptionsMapPaths.cpp : implementation file
//

#include "stdafx.h"
//#include "KBrowseFolder.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKapsulApp theApp;
extern CKOption *KOption;


/////////////////////////////////////////////////////////////////////////////
// COptionsMapPaths dialog


COptionsMapPaths::COptionsMapPaths(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsMapPaths::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsMapPaths)
	//}}AFX_DATA_INIT
}


void COptionsMapPaths::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsMapPaths)
	DDX_Control(pDX, IDC_EDIT1, m_FolderEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsMapPaths, CDialog)
	//{{AFX_MSG_MAP(COptionsMapPaths)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_DELSELECTED, OnDelselected)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_ADDPATH, OnAddpath)
	ON_BN_CLICKED(IDC_BROWSEBT, OnBrowsebt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsMapPaths message handlers

BOOL COptionsMapPaths::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i=0;
//	char temp[100],temp2[512];
	
	m_MapList.SubclassDlgItem( IDC_LIST1, this);
	m_MapList.DragAcceptFiles(TRUE);
	//m_MapList.Create(WS_CHILD|WS_VISIBLE,CRect(20,20,120,120),this,1541);
/*
	wsprintf(temp,"MapPath%d",i);
	strcpy(temp2,(LPCTSTR)theApp.GetProfileString("MapPath",temp));
	while(strcmp(temp2,"")!=0)
	{
		m_MapList.AddString( temp2);
		i++;
		wsprintf(temp,"MapPath%d",i);
		strcpy(temp2,(LPCTSTR)theApp.GetProfileString("MapPath",temp));
	}
*/
	for (i=0;i<KOption->GetnbMapDir();i++)
	{
		m_MapList.AddString(KOption->GetMapDir(i));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsMapPaths::OnDestroy() 
{
	CDialog::OnDestroy();

	char temp2[512];
	int i;

	KOption->DelAllMapDir();

	for (i=0;i<m_MapList.GetCount();i++)
	{
		m_MapList.GetText(i,temp2);
		KOption->AddMapDir(CString(temp2));
	}
}

void COptionsMapPaths::OnDelselected() 
{
	m_MapList.DeleteFiles();
	
}

void COptionsMapPaths::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void COptionsMapPaths::OnAddpath() 
{
	CString tmpFolder;
	m_FolderEdit.GetWindowText(tmpFolder);
	if (!tmpFolder.IsEmpty())
	{
		m_MapList.AddString(tmpFolder);
	}
}

void COptionsMapPaths::OnBrowsebt() 
{
	/*
	//SHGetFolder
	CKBrowseFolder diag;
	if (diag.DoModal()==IDOK)
	{
		m_FolderEdit.SetWindowText(diag.m_Folder);

	}
	*/
//	static char tit[]={"Browse for folder"};
	char dirn[512];

    if (BrowseDialog(dirn))
	{
		m_FolderEdit.SetWindowText(dirn);
	}
}
