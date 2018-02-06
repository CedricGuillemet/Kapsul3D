// ModeBar.cpp : implementation file
//

#include "stdafx.h"
//#include "t7.h"

//#include "memmgr/mmgr.h"

//#include "ModeBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModeBar

CModeBar::CModeBar()
{
}

CModeBar::~CModeBar()
{
}


BEGIN_MESSAGE_MAP(CModeBar, CMyToolBar)
	//{{AFX_MSG_MAP(CModeBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModeBar message handlers


int CModeBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMyToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	
	return 0;
}
