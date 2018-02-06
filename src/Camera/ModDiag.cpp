// ModDiag.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
//#include "aglmfc.h"
#include "ModDiag.h"
#include "CamKF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModDiag dialog
extern CRollupCtrl *m_wndRollupCtrl;



CModDiag::CModDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CModDiag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModDiag)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModDiag)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModDiag, CDialog)
	//{{AFX_MSG_MAP(CModDiag)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModDiag message handlers

BOOL CModDiag::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	m_ParamDiag=new CParamDiag;


	m_ParamDiag->Create(MAKEINTRESOURCE(IDD_MOD),m_wndRollupCtrl);
    m_wndRollupCtrl->InsertPage("Parameters",m_ParamDiag);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CModDiag::UnSetPlugin(void)
{
//    m_BuildDiag->m_BuildIt.SetCheck(0);
}

void CModDiag::OnOK( )
{

}

void CModDiag::OnCancel( )
{

}

void CModDiag::OnDestroy() 
{
	CDialog::OnDestroy();

	m_wndRollupCtrl->DestroyWindow();
/*	
	m_wndRollupCtrl->RemoveAllPages();
*/
	delete m_wndRollupCtrl;
	
	
}
