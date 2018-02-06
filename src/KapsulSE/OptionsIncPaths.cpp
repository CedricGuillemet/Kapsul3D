// OptionsIncPaths.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulSE.h"

//#include "memmgr/mmgr.h"

#include "OptionsIncPaths.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsIncPaths dialog

extern CKapsulApp theApp;

COptionsIncPaths::COptionsIncPaths(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsIncPaths::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsIncPaths)
	//}}AFX_DATA_INIT
}


void COptionsIncPaths::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsIncPaths)
	DDX_Control(pDX, IDC_LIST, m_ListBoxEx);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsIncPaths, CDialog)
	//{{AFX_MSG_MAP(COptionsIncPaths)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsIncPaths message handlers

BOOL COptionsIncPaths::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i=0;
	char temp[100],temp2[512];
	
	// TODO: Add extra initialization here
	/*
	m_ListBoxExBuddy.SubclassDlgItem( IDC_LISTBUDDY, this );
	m_ListBoxExBuddy.SetListbox( &m_ListBoxEx );
*/
	wsprintf(temp,"IncPath%d",i);
	strcpy(temp2,(LPCTSTR)theApp.GetProfileString("IncPath",temp));
	while(strcmp(temp2,"")!=0)
	{
		m_ListBoxEx.InsertString( -1, temp2);
		i++;
		wsprintf(temp,"IncPath%d",i);
		strcpy(temp2,(LPCTSTR)theApp.GetProfileString("IncPath",temp));
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsIncPaths::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	int i;
	char temp[100],temp2[512];

	for (i=0;i<m_ListBoxEx.GetCount();i++)
	{
		wsprintf(temp,"IncPath%d",i);
		m_ListBoxEx.GetText(i,temp2);
		theApp.WriteProfileString("IncPath",temp,temp2);
	}	

	for (i=m_ListBoxEx.GetCount();i<100;i++)
	{
		wsprintf(temp,"IncPath%d",i);
		theApp.WriteProfileString("IncPath",temp,"");
	}	

}

void COptionsIncPaths::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}
