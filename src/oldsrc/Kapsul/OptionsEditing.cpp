// OptionsEditing.cpp : implementation file
//

#include "stdafx.h"
#include "kapsul.h"
//#include "memmgr/mmgr.h"

#include "OptionsEditing.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsEditing dialog
extern CKapsulApp theApp;

COptionsEditing::COptionsEditing(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsEditing::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsEditing)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COptionsEditing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsEditing)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsEditing, CDialog)
	//{{AFX_MSG_MAP(COptionsEditing)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsEditing message handlers
