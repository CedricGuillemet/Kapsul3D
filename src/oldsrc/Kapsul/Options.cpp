// Options.cpp : implementation file
//

#include "stdafx.h"
//#include "t7.h"
//#include "memmgr/mmgr.h"

#include "Options.h"
#include "resource.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MOptions dialog


MOptions::MOptions(CWnd* pParent /*=NULL*/)
	: CDialog(MOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(MOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MOptions)
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MOptions, CDialog)
	//{{AFX_MSG_MAP(MOptions)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MOptions message handlers

void MOptions::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OptEdit.ShowWindow(SW_HIDE);
	OptIncPaths.ShowWindow(SW_HIDE);
	OptMapPaths.ShowWindow(SW_HIDE);

	switch(m_Tab.GetCurSel())
	{
	case 0:
		OptEdit.ShowWindow(SW_SHOWNORMAL);
		break;
	case 1:
		OptIncPaths.ShowWindow(SW_SHOWNORMAL);
		break;
	case 2:
		OptMapPaths.ShowWindow(SW_SHOWNORMAL);
		break;

	}
	


	*pResult = 0;
}

BOOL MOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Tab.InsertItem(1,"Editing");
	m_Tab.InsertItem(2,"Include paths");
	m_Tab.InsertItem(3,"Map paths");

	OptEdit.Create(IDD_OPTIONS_EDITING,this);
	OptIncPaths.Create(IDD_OPTIONS_INCPATHS,this);
	OptMapPaths.Create(IDD_OPTIONS_MAPPATHS,this);

	OptEdit.MoveWindow(20,45,535,330);
	OptEdit.ShowWindow(SW_SHOWNORMAL);

	OptIncPaths.MoveWindow(20,45,535,330);
	OptIncPaths.ShowWindow(SW_HIDE);

	OptMapPaths.MoveWindow(20,45,535,330);
	OptMapPaths.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
