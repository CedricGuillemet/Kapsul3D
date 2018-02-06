
#include "stdafx.h"
#include "SnapDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSnapDialog dialog


CSnapDialog::CSnapDialog(UINT IDD, CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CSnapDialog)
		// NOTE: the ClassWizard will add member initialization here
	m_nYOffset = 15;
	m_nXOffset = 15;
	//}}AFX_DATA_INIT
}

void CSnapDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSnapDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSnapDialog, CDialog)
	//{{AFX_MSG_MAP(CSnapDialog)
		// NOTE: the ClassWizard will add message map macros here
		ON_WM_WINDOWPOSCHANGING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnapDialog message handlers

void CSnapDialog::OnWindowPosChanging( WINDOWPOS* lpwndpos )
{
	CRect	wndRect, trayRect;
	int		leftTaskbar = 0, rightTaskbar = 0, topTaskbar = 0, bottomTaskbar = 0;

	GetWindowRect(&wndRect);

	// Screen resolution
	int screenWidth =	GetSystemMetrics(SM_CXSCREEN); 
	int screenHeight =	GetSystemMetrics(SM_CYSCREEN);

	// Find the taskbar
	CWnd* pWnd = FindWindow(_T("Shell_TrayWnd"), _T(""));
	pWnd->GetWindowRect(&trayRect);

	int wndWidth = wndRect.right - wndRect.left;
	int wndHeight = wndRect.bottom - wndRect.top;

	if(trayRect.top <= 0 && trayRect.left <= 0 && trayRect.right >= screenWidth) {
		// top taskbar
		topTaskbar = trayRect.bottom - trayRect.top;
	}
	else if(trayRect.top > 0 && trayRect.left <= 0) {
		// bottom taskbar
		bottomTaskbar = trayRect.bottom - trayRect.top;
	}
	else if(trayRect.top <= 0 && trayRect.left > 0) {
		// right taskbar
		rightTaskbar = trayRect.right - trayRect.left;
	}
	else {
		// left taskbar
		leftTaskbar = trayRect.right - trayRect.left;
	}

	// Snap to screen border
	// Left border
	if(lpwndpos->x >= -m_nXOffset + leftTaskbar && lpwndpos->x <= leftTaskbar + m_nXOffset) {
		lpwndpos->x = leftTaskbar;
	}

	// Top border
	if(lpwndpos->y >= -m_nYOffset && lpwndpos->y <= topTaskbar + m_nYOffset) {
		lpwndpos->y = topTaskbar;
	}

	// Right border
	if(lpwndpos->x + wndWidth <= screenWidth - rightTaskbar + m_nXOffset && lpwndpos->x + wndWidth >= screenWidth - rightTaskbar - m_nXOffset) {
		lpwndpos->x = screenWidth - rightTaskbar - wndWidth;
	}

	// Bottom border
	if( lpwndpos->y + wndHeight <= screenHeight - bottomTaskbar + m_nYOffset && lpwndpos->y + wndHeight >= screenHeight - bottomTaskbar - m_nYOffset) {
		lpwndpos->y = screenHeight - bottomTaskbar - wndHeight;
	}
}
