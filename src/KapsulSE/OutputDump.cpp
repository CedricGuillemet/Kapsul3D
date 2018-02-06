// OutputDump.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "OutputDump.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputDump dialog


COutputDump::COutputDump(CWnd* pParent /*=NULL*/)
	: CDialog(COutputDump::IDD, pParent)
{
	//{{AFX_DATA_INIT(COutputDump)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COutputDump::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutputDump)
	DDX_Control(pDX, IDC_EDIT1, m_Output);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutputDump, CDialog)
	//{{AFX_MSG_MAP(COutputDump)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputDump message handlers

void COutputDump::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (m_Output.m_hWnd!=NULL)
	{
		m_Output.MoveWindow(2,2,cx-4,cy-4);
	}
}
