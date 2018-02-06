// TreeDesign.cpp : implementation file
//

#include "stdafx.h"
#include "terrained.h"
#include "TreeDesign.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeDesign dialog


CTreeDesign::CTreeDesign(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeDesign::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeDesign)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTreeDesign::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeDesign)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreeDesign, CDialog)
	//{{AFX_MSG_MAP(CTreeDesign)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeDesign message handlers
