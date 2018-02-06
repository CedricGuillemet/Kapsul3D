// PathModDiag.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PathModDiag.h"
#include "Lathe.h"
#include "Mapping.h"
#include "Path.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathModDiag dialog


CPathModDiag::CPathModDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CPathModDiag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPathModDiag)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPathModDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPathModDiag)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPathModDiag, CDialog)
	//{{AFX_MSG_MAP(CPathModDiag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathModDiag message handlers
CLathe m_Lathe;
CMapping m_Mapping;
CPath m_Path;
extern "C" CRollupCtrl *m_wndRollupCtrl;

BOOL CPathModDiag::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Mapping.Create(MAKEINTRESOURCE(IDD_MAPPING),m_wndRollupCtrl);
    m_Lathe.Create(MAKEINTRESOURCE(IDD_LATHE),m_wndRollupCtrl);
    m_Path.Create(MAKEINTRESOURCE(IDD_PATH),m_wndRollupCtrl);
    //m_Primitive.Create(MAKEINTRESOURCE(IDD_MODDIAG1),m_wndRollupCtrl);

    //m_wndRollupCtrl->InsertPage("Primitive",&m_Primitive);
    m_wndRollupCtrl->InsertPage("Path extrude",&m_Path);
    m_wndRollupCtrl->InsertPage("Lathe",&m_Lathe);
    m_wndRollupCtrl->InsertPage("Mapping",&m_Mapping);

    //m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);	
	m_wndRollupCtrl->ExpandPage(2,TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
