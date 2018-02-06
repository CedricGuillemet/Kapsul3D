// KRenderIt.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "KRenderIt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKRenderIt dialog


CKRenderIt::CKRenderIt(CWnd* pParent /*=NULL*/)
	: CDialog(CKRenderIt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKRenderIt)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CKRenderIt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKRenderIt)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKRenderIt, CDialog)
	//{{AFX_MSG_MAP(CKRenderIt)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKRenderIt message handlers
