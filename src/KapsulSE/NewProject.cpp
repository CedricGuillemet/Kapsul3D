// NewProject.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "NewProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewProject dialog


CNewProject::CNewProject(CWnd* pParent /*=NULL*/)
	: CDialog(CNewProject::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewProject)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNewProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProject)
	DDX_Control(pDX, IDC_EDIT2, m_PrjLoc);
	DDX_Control(pDX, IDC_EDIT1, m_PrjName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProject, CDialog)
	//{{AFX_MSG_MAP(CNewProject)
	ON_BN_CLICKED(IDC_PRJBROWSELOC, OnPrjbrowseloc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProject message handlers

void CNewProject::OnPrjbrowseloc() 
{
	// TODO: Add your control notification handler code here
	
}

void CNewProject::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
