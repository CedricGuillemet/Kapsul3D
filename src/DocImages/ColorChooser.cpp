/////////////////////////////////////////////////////////////////////////////
//
// Disclaimer Notice
// ------------------
// The Author cannot guarantee this software is error free.
// The author also disclaims all responsibility for damages or 
// loss of profits caused by the failure of this software
//. Your usage of these modifications indicates your willingness to 
// accept complete responsibility.
//
//
// Developed by: Norm Almond for www.codeproject.com 
//
// Please use this software freely, if you fix or make any modifications to
// the software you can let me know so I can improve future versions.
//
// Version 1.00 - First Released 03 March 2001
//
/////////////////////////////////////////////////////////////////////////////

// ColorChooser.cpp : implementation file
//

#include "stdafx.h"
#include "ColorChooser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Internal Child IDs
#define ID_TAB_WND			0x1001
#define ID_PALETTE_WND		0x1002
#define ID_WEBCOLOR_WND		0x1003
#define ID_SYSCOLOR_WND		0x1004


/////////////////////////////////////////////////////////////////////////////
// CColorChooser

CColorChooser::CColorChooser()
{	
}

CColorChooser::CColorChooser(CPoint pt, CWnd *pWnd, COLORREF crCurrent)
{
	m_pWndSelect = NULL;
	Create(pt, pWnd, crCurrent);
}

CColorChooser::~CColorChooser()
{
}


BEGIN_MESSAGE_MAP(CColorChooser, CWnd)
	//{{AFX_MSG_MAP(CColorChooser)
	ON_NOTIFY(TCN_SELCHANGE, ID_TAB_WND, OnSelchangeTab)
	ON_NOTIFY(COLOR_CHANGED, ID_PALETTE_WND, OnPaletteColorChange)
	ON_NOTIFY(COLOR_CHANGED, ID_SYSCOLOR_WND, OnSystemColorChange)
	ON_NOTIFY(COLOR_CHANGED, ID_WEBCOLOR_WND, OnWebColorChange)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CColorChooser message handlers


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CColorChooser::Create
// 
// DESCRIPTION:		Create a shapes CColorChooser Window
// 
// ACCESSIBILTY:	Public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            03MAR2001  1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
BOOL CColorChooser::Create(CPoint pt, CWnd *pWnd, COLORREF crCurrent)
{
	CRect rcChild;
	CRect rc(pt,pt);

	m_pWndParent = pWnd;

    // Get the class name and create the window
    CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW);

	BOOL bRet = CWnd::CreateEx(0, szClassName, _T(""), WS_VISIBLE | WS_CHILD, rc, pWnd, 0, NULL);
	if (!bRet)
		return FALSE;


	// Palette Defines Window Shape
	m_wndPalette.Create(CPoint(2,24), this, ID_PALETTE_WND);
	m_wndPalette.GetClientRect(rcChild);
/*
	m_wndWebColor.Create(CPoint(2,24), this, ID_WEBCOLOR_WND);		
	m_wndWebColor.SetWindowPos(NULL, 0, 0, rcChild.Width(), rcChild.Height(), SWP_NOMOVE | SWP_NOZORDER);	

	m_wndSysColor.Create(CPoint(2,24), this, ID_SYSCOLOR_WND);		
	m_wndSysColor.SetWindowPos(NULL, 0, 0, rcChild.Width(), rcChild.Height(), SWP_NOMOVE | SWP_NOZORDER);	
		*/

	rcChild.InflateRect(GetSystemMetrics(SM_CXBORDER)*4,GetSystemMetrics(SM_CYBORDER)*4);
	rcChild.top    += 4;
	rcChild.bottom += 27;
	rcChild.left+=5;
	
	m_wndTab.Create(WS_VISIBLE|WS_CHILD|TCS_TABS|TCS_FOCUSNEVER,rcChild, this, ID_TAB_WND);
	m_wndTab.InsertItem(0, _T("Palette"));
	/*
	m_wndTab.InsertItem(1, _T("Web"));
	m_wndTab.InsertItem(2, _T("System"));
*/
	CFont* pFont =  CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	m_wndTab.SetFont(pFont, TRUE);

	SetWindowPos(NULL, 0, 0, rcChild.Width(), rcChild.Height(), SWP_NOMOVE | SWP_NOZORDER);	

	
/*
	// Test for System Color
	if (crCurrent & SYSTEM_COLOR_MASK)
	{
		m_wndSysColor.SetCurrentColor(crCurrent);
		m_wndTab.SetCurSel(2);

		m_wndSysColor.ShowWindow(SW_SHOW);
		m_pWndSelect = &m_wndSysColor;
	}
	else
	{
		if (crCurrent & WEB_COLOR_MASK)
		{
			m_wndWebColor.SetCurrentColor(crCurrent);
			m_wndTab.SetCurSel(1);

			m_wndWebColor.ShowWindow(SW_SHOW);
			m_pWndSelect = &m_wndWebColor;
		}
		else
		{
		*/
			m_wndPalette.SetCurrentColor(crCurrent);
			m_wndPalette.ShowWindow(SW_SHOW);
			m_pWndSelect = &m_wndPalette;
			/*
		}

	}
*/

	return bRet;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CColorChooser::OnSelchangeTab
// 
// DESCRIPTION:		Called when user select a tab
// 
// ACCESSIBILTY:	Public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            03MAR2001  1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CColorChooser::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	/*
	int nFocus = m_wndTab.GetCurSel();

	m_pWndSelect->ShowWindow(SW_HIDE);

	switch (nFocus)
	{
	case 0:
		m_wndPalette.ShowWindow(SW_SHOW); 
		m_pWndSelect = &m_wndPalette;
		break;
	
	case 1:
		m_wndWebColor.ShowWindow(SW_SHOW); 
		m_pWndSelect = &m_wndWebColor;
		break;
	
	case 2:
		m_wndSysColor.ShowWindow(SW_SHOW); 
		m_pWndSelect = &m_wndSysColor;
		break;
	}*/

	*pResult = 0;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CColorChooser::OnPaletteColorChange
// 
// DESCRIPTION:		Called when user selects a color in the palette window
// 
// ACCESSIBILTY:	Public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            03MAR2001  1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
COLORREF *m_CurrentColor=NULL;
void CColorChooser::OnPaletteColorChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	COLOR_NOTIFY* pColorNtfy = (COLOR_NOTIFY*) pNMHDR;
	TRACE("PaletteColorChanged %x\n", pColorNtfy->color);

	// Forward to Parent
	m_pWndParent->PostMessage(CCN_COLOR_CHANGED, 0, (LPARAM) pColorNtfy->color); 

	*pResult = 1;
}

void CColorChooser::SetCurrentColorValues(COLORREF daNewVal)
{
	if (m_CurrentColor!=NULL)
		*m_CurrentColor=daNewVal;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CColorChooser::OnSystemColorChange
// 
// DESCRIPTION:		Called when user selects a color in the system color window
// 
// ACCESSIBILTY:	Public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            03MAR2001  1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CColorChooser::OnSystemColorChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	COLOR_NOTIFY* pColorNtfy = (COLOR_NOTIFY*) pNMHDR;
	TRACE("SystemColorChanged %x\n", pColorNtfy->color);

	// Forward to Parent
	m_pWndParent->PostMessage(CCN_COLOR_CHANGED, 0, (LPARAM) pColorNtfy->color); 

	*pResult = 1;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CColorChooser::OnWebColorChange
// 
// DESCRIPTION:		Called when user selects a color in the system color window
// 
// ACCESSIBILTY:	Public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            03MAR2001  1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CColorChooser::OnWebColorChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	COLOR_NOTIFY* pColorNtfy = (COLOR_NOTIFY*) pNMHDR;
	TRACE("WebColorChange %x\n", pColorNtfy->color);

	// Forward to Parent
	m_pWndParent->PostMessage(CCN_COLOR_CHANGED, 0, (LPARAM) pColorNtfy->color); 

	*pResult = 1;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CColorChooser::OnKillFocus
// 
// DESCRIPTION:		Cancel the control when the focus changes
// 
// ACCESSIBILTY:	Public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            05OCT2001  1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CColorChooser::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);

	if (pNewWnd && pNewWnd->GetParent() != this)
			m_pWndParent->PostMessage(CCN_CANCEL, 0, 0); 
	
	
}
