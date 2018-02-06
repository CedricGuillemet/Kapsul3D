// mybar.cpp : implementation file
//

#include "stdafx.h"
#include "myDeskbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDeskBar

CMyDeskBar::CMyDeskBar()
{
}

CMyDeskBar::~CMyDeskBar()
{
}


BEGIN_MESSAGE_MAP(CMyDeskBar, baseCMyDeskBar)
	//{{AFX_MSG_MAP(CMyDeskBar)
	ON_WM_CREATE()
	ON_WM_SIZING()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyDeskBar message handlers

int CMyDeskBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (baseCMyDeskBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	m_szFixedWidth=182;
	m_cDialog.Create(MAKEINTRESOURCE(IDD_TVTEST_DIALOG), this);
    
	return 0;
}

void CMyDeskBar::OnSizing(UINT fwSide, LPRECT pRect) 
{
	baseCMyDeskBar::OnSizing(fwSide, pRect);
}

void CMyDeskBar::OnSize(UINT nType, int cx, int cy) 
{
	baseCMyDeskBar::OnSize(nType, cx, cy);
}
