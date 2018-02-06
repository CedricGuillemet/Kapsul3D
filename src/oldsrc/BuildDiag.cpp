// BuildDiag.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BuildDiag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuildDiag dialog


CBuildDiag::CBuildDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CBuildDiag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuildDiag)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBuildDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuildDiag)
	DDX_Control(pDX, IDC_CHECK1, m_BuildIt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuildDiag, CDialog)
	//{{AFX_MSG_MAP(CBuildDiag)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuildDiag message handlers

void CBuildDiag::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_BuildIt.SetCheck(1);
    SetPluginActive();
}

BOOL CBuildDiag::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    SetPluginActive();
    //OnHemis2();
	m_BuildIt.SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBuildDiag::OnOK( )
{

}

void CBuildDiag::OnCancel( )
{

}