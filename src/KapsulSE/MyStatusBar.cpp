// mybar.cpp : implementation file
//

#include "stdafx.h"
#include "myStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatusBar

CMyStatusBar::CMyStatusBar()
{
}

CMyStatusBar::~CMyStatusBar()
{
}


BEGIN_MESSAGE_MAP(CMyStatusBar, baseCMyStatusBar)
	//{{AFX_MSG_MAP(CMyStatusBar)
	ON_WM_CREATE()
	ON_WM_SIZING()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyStatusBar message handlers

int CMyStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (baseCMyStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_szFixedHeight=66;
	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	m_cDialog.Create(MAKEINTRESOURCE(IDD_STATUSBAR), this);

	return 0;
}

void CMyStatusBar::OnSizing(UINT fwSide, LPRECT pRect) 
{
	baseCMyStatusBar::OnSizing(fwSide, pRect);

}

void CMyStatusBar::OnSize(UINT nType, int cx, int cy) 
{
	baseCMyStatusBar::OnSize(nType, cx, cy);
}
