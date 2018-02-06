// Mainframe.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainframe dialog


extern CRollupCtrl *m_wndRollupCtrl;

extern CBuildSkel m_Build;
extern CWeightSkel m_Weight;
extern CAnimSkel m_Anim;

CMainframe::CMainframe(CWnd* pParent /*=NULL*/)
	: CDialog(CMainframe::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainframe)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMainframe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainframe)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainframe, CDialog)
	//{{AFX_MSG_MAP(CMainframe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainframe message handlers

BOOL CMainframe::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_Build.Create(MAKEINTRESOURCE(IDD_BUILD),m_wndRollupCtrl);
    m_Weight.Create(MAKEINTRESOURCE(IDD_WEIGHTS),m_wndRollupCtrl);
    m_Anim.Create(MAKEINTRESOURCE(IDD_ANIMS),m_wndRollupCtrl);

    m_wndRollupCtrl->InsertPage("Build",&m_Build);
    m_wndRollupCtrl->InsertPage("Vertex weight",&m_Weight);
    m_wndRollupCtrl->InsertPage("Animation",&m_Anim);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(2,TRUE);

    //m_Build.OnAddroot();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


