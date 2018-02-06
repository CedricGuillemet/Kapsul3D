// PluginDiag.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PluginDiag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPluginDiag dialog


CPluginDiag::CPluginDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CPluginDiag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPluginDiag)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPluginDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPluginDiag)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPluginDiag, CDialog)
	//{{AFX_MSG_MAP(CPluginDiag)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPluginDiag message handlers
