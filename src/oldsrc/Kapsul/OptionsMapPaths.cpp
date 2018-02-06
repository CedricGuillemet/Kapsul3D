// OptionsMapPaths.cpp : implementation file
//

#include "stdafx.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKapsulApp theApp;
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
	DDX_Control(pDX, IDC_LIST, m_ListBoxEx);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsMapPaths, CDialog)
	//{{AFX_MSG_MAP(COptionsMapPaths)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsMapPaths message handlers

BOOL COptionsMapPaths::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i=0;
	char temp[100],temp2[512];
	
	m_ListBoxExBuddy.SubclassDlgItem( IDC_LISTBUDDY, this );
	m_ListBoxExBuddy.SetListbox( &m_ListBoxEx );

	wsprintf(temp,"MapPath%d",i);
	strcpy(temp2,(LPCTSTR)theApp.GetProfileString("MapPath",temp));
	while(strcmp(temp2,"")!=0)
	{
		m_ListBoxEx.InsertString( -1, temp2);
		i++;
		wsprintf(temp,"MapPath%d",i);
		strcpy(temp2,(LPCTSTR)theApp.GetProfileString("MapPath",temp));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsMapPaths::OnDestroy() 
{
	CDialog::OnDestroy();

	int i;
	char temp[100],temp2[512];

	for (i=0;i<m_ListBoxEx.GetCount();i++)
	{
		wsprintf(temp,"MapPath%d",i);
		m_ListBoxEx.GetText(i,temp2);
		theApp.WriteProfileString("MapPath",temp,temp2);
	}

    for (i=m_ListBoxEx.GetCount();i<100;i++)
    {
		wsprintf(temp,"MapPath%d",i);
		theApp.WriteProfileString("MapPath",temp,"");
    }
	
	// TODO: Add your message handler code here
	
}
