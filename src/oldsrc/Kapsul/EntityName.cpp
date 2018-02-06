// EntityName.cpp : implementation file
//

#include "stdafx.h"
//#include "Enti.h"
#include "EntityName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEntityName dialog


CEntityName::CEntityName(CWnd* pParent /*=NULL*/)
	: CDialog(CEntityName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEntityName)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEntityName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntityName)
	DDX_Control(pDX, IDC_EDIT1, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEntityName, CDialog)
	//{{AFX_MSG_MAP(CEntityName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntityName message handlers

void CEntityName::OnCancel() 
{
	Name[0]=0;
	
	CDialog::OnCancel();
}

void CEntityName::OnOK() 
{
	m_Name.GetWindowText(Name,32);
    Name[31]=0;
	
	CDialog::OnOK();
}
