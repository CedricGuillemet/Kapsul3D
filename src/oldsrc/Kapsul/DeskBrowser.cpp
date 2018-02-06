// DeskBrowser.cpp : implementation file
//

#include "stdafx.h"
#include "kapsul.h"
#include "DeskBrowser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeskBrowser dialog


CDeskBrowser::CDeskBrowser(CWnd* pParent /*=NULL*/)
	: CDialog(CDeskBrowser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeskBrowser)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDeskBrowser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeskBrowser)
	DDX_Control(pDX, IDC_TREE1, m_TreeHierar);
	DDX_Control(pDX, IDC_TAB1, m_Tabs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeskBrowser, CDialog)
	//{{AFX_MSG_MAP(CDeskBrowser)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeskBrowser message handlers

BOOL CDeskBrowser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Tabs.InsertItem(1,"Hierarchie");
	m_Tabs.InsertItem(2,"File browser");
	m_Tabs.InsertItem(3,"Project");

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDeskBrowser::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (IsWindow(m_Tabs.m_hWnd))
	{
		m_Tabs.MoveWindow(2,2,cx-4,cy-4,FALSE);

		m_TreeHierar.MoveWindow(6,6,cx-12,cy-32,FALSE);

	}
	
}
