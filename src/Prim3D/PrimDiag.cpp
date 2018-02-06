// PrimDiag.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PrimDiag.h"
#include "Tree/tree/tree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrimDiag dialog

extern  CRollupCtrl *m_wndRollupCtrl;

extern CMapping m_Mapping;
extern CParameters m_Parameters;
extern CTreeParam m_TreeParam;


CPrimDiag::CPrimDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CPrimDiag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrimDiag)
	//}}AFX_DATA_INIT
}


void CPrimDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrimDiag)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrimDiag, CDialog)
	//{{AFX_MSG_MAP(CPrimDiag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrimDiag message handlers

BOOL CPrimDiag::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CPrimDiag::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::OnNotify(wParam, lParam, pResult);
}

BOOL CPrimDiag::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

    m_Mapping.Create(MAKEINTRESOURCE(IDD_MODDIAG4),m_wndRollupCtrl);
    m_Parameters.Create(MAKEINTRESOURCE(IDD_MODDIAG3),m_wndRollupCtrl);
    m_TreeParam.Create(MAKEINTRESOURCE(IDD_MODDIAG2),m_wndRollupCtrl);
    //m_Primitive.Create(MAKEINTRESOURCE(IDD_MODDIAG1),m_wndRollupCtrl);

    //m_wndRollupCtrl->InsertPage("Primitive",&m_Primitive);
    m_wndRollupCtrl->InsertPage("Parameters",&m_Parameters);
    m_wndRollupCtrl->InsertPage("Tree parameters",&m_TreeParam);
    m_wndRollupCtrl->InsertPage("Mapping",&m_Mapping);

    //m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(2,TRUE);
    m_wndRollupCtrl->EnablePage(1,FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrimDiag::OnOK( )
{

}

void CPrimDiag::OnCancel( )
{

}