// AnimOutput.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "AnimOutput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimOutput dialog


CAnimOutput::CAnimOutput(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimOutput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimOutput)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAnimOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimOutput)
	DDX_Control(pDX, IDC_TAB1, m_Tabs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnimOutput, CDialog)
	//{{AFX_MSG_MAP(CAnimOutput)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimOutput message handlers

void CAnimOutput::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	/*
	switch (m_Tabs.GetCurSel())
	{
	case 0:
		m_Dump.ShowWindow(SW_HIDE);
		m_Animate.ShowWindow(SW_SHOWNORMAL);
		break;
	case 1:
		m_Dump.ShowWindow(SW_SHOWNORMAL);
		m_Animate.ShowWindow(SW_HIDE);
		break;
	}
	*/
	*pResult = 0;
}

BOOL CAnimOutput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Tabs.InsertItem(0,"Anim");
	m_Tabs.InsertItem(1,"Output");
	m_Dump.Create(MAKEINTRESOURCE(IDD_OUTPUT),this);
	m_Animate.Create(MAKEINTRESOURCE(IDD_ANIM),this);

	m_Dump.ShowWindow(SW_SHOWNORMAL);
	m_Animate.ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAnimOutput::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if (m_Tabs.m_hWnd!=NULL)
	{
		m_Tabs.MoveWindow(2,2,cx-4,cy-4);
		m_Dump.MoveWindow(4,4,cx-8,cy-28);
		m_Animate.MoveWindow(4,4,cx-8,cy-28);
	}
	
}
