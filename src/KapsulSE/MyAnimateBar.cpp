// mybar.cpp : implementation file
//

#include "stdafx.h"
#include "myAnimatebar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyAnimBar

CMyAnimBar::CMyAnimBar()
{
}

CMyAnimBar::~CMyAnimBar()
{
}


BEGIN_MESSAGE_MAP(CMyAnimBar, baseCMyAnimBar)
	//{{AFX_MSG_MAP(CMyAnimBar)
	ON_WM_CREATE()
	ON_WM_SIZING()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyAnimBar message handlers

int CMyAnimBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (baseCMyAnimBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	m_cDialog.Create(MAKEINTRESOURCE(IDD_ANIMOUTPUT), this);

	return 0;
}

void CMyAnimBar::OnSizing(UINT fwSide, LPRECT pRect) 
{
	baseCMyAnimBar::OnSizing(fwSide, pRect);

}

void CMyAnimBar::OnSize(UINT nType, int cx, int cy) 
{
	baseCMyAnimBar::OnSize(nType, cx, cy);
}
