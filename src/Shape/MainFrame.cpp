// MainFrame.cpp : implementation file
//

#include "stdafx.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame dialog

CRollupCtrl *m_wndRollupCtrl;
CParameters m_Parameters;

CMainFrame::CMainFrame(CWnd* pParent /*=NULL*/)
	: CDialog(CMainFrame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainFrame)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMainFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainFrame)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_Parameters.Create(MAKEINTRESOURCE(IDD_PARAM),m_wndRollupCtrl);

    m_wndRollupCtrl->InsertPage("Parameters",&m_Parameters);

    m_wndRollupCtrl->ExpandPage(0,TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainFrame::OnOK( )
{

}

void CMainFrame::OnCancel( )
{

}