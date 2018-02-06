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
// COptionsPrefabPaths dialog


COptionsPrefabPaths::COptionsPrefabPaths(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsPrefabPaths::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsPrefabPaths)
	//}}AFX_DATA_INIT
}


void COptionsPrefabPaths::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsPrefabPaths)
	DDX_Control(pDX, IDC_EDIT1, m_FolderEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsPrefabPaths, CDialog)
	//{{AFX_MSG_MAP(COptionsPrefabPaths)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_DELSELECTED, OnDelselected)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_ADDPATH, OnAddpath)
	ON_BN_CLICKED(IDC_BROWSEBT, OnBrowsebt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsPrefabPaths message handlers

BOOL COptionsPrefabPaths::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i=0;
//	char temp[100],temp2[512];
	
	m_PrefabList.SubclassDlgItem( IDC_LIST1, this);
	m_PrefabList.DragAcceptFiles(TRUE);
	//m_MapList.Create(WS_CHILD|WS_VISIBLE,CRect(20,20,120,120),this,1541);

	/*
	wsprintf(temp,"PrefabPath%d",i);
	strcpy(temp2,(LPCTSTR)theApp.GetProfileString("PrefabPath",temp));
	while(strcmp(temp2,"")!=0)
	{
		m_PrefabList.AddString( temp2);
		i++;
		wsprintf(temp,"PrefabPath%d",i);
		strcpy(temp2,(LPCTSTR)theApp.GetProfileString("PrefabPath",temp));
	}
	*/
	for (i=0;i<KOption->GetnbPrefabDir();i++)
	{
		m_PrefabList.AddString(KOption->GetPrefabDir(i));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsPrefabPaths::OnDestroy() 
{
	CDialog::OnDestroy();

	char temp2[512];
	int i;

	KOption->DelAllPrefabDir();

	for (i=0;i<m_PrefabList.GetCount();i++)
	{
		m_PrefabList.GetText(i,temp2);
		KOption->AddPrefabDir(CString(temp2));
	}
	/*
	


	for (i=0;i<m_PrefabList.GetCount();i++)
	{
		wsprintf(temp,"PrefabPath%d",i);
		m_PrefabList.GetText(i,temp2);
		theApp.WriteProfileString("PrefabPath",temp,temp2);
	}

    for (i=m_PrefabList.GetCount();i<100;i++)
    {
		wsprintf(temp,"PrefabPath%d",i);
		theApp.WriteProfileString("PrefabPath",temp,"");
    }
	*/
}

void COptionsPrefabPaths::OnDelselected() 
{
	m_PrefabList.DeleteFiles();
	
}

void COptionsPrefabPaths::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void COptionsPrefabPaths::OnAddpath() 
{
	CString tmpFolder;
	m_FolderEdit.GetWindowText(tmpFolder);
	if (!tmpFolder.IsEmpty())
	{
		m_PrefabList.AddString(tmpFolder);
	}
}

void COptionsPrefabPaths::OnBrowsebt() 
{
	/*
	CKBrowseFolder diag;
	if (diag.DoModal()==IDOK)
	{
		m_FolderEdit.SetWindowText(diag.m_Folder);
	}
	*/
	char dirn[512];

    if (BrowseDialog(dirn))
	{
		m_FolderEdit.SetWindowText(dirn);
	}

}
