/////////////////////////////////////////////////////////////////////////////
// SelBtn.cpp : implementation file
// 
// Windows 2000 / Office 2000 style file dialog.
// 
// This WILL work on Win 95 / 98 / NT 4 / NT 5 (2000) / WinME
// 
// Original code by Norm Almond
// 
// Update History:
//    06 Aug 2000 - David Wulff, Now the buttons are only drawn in the 'up'
//                  position when the mouse is over them.
//                  The pressed state is also stored.
//                  Drawing code has been redone to mimick the Windows 2000
//                  File dialog appearance (for the 'side bar')
//    06 Sep 2000 - David Wulff, Buttons now act like real buttons and don't
//                  fire until the mouse is released.
//                  Hover 'light-up' now possible (see code).
//                  Other miscellaneous drawing code redone.
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SelBtn.h"
#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL bDotNetUI;

/////////////////////////////////////////////////////////////////////////////
// BXSelBtn

BXSelBtn::BXSelBtn()
{
	m_Enabled = FALSE;
	m_DrawPressed = FALSE;
	m_Pressed = FALSE;
	m_MouseOnButton = FALSE;
}

BXSelBtn::~BXSelBtn()
{

}

BEGIN_MESSAGE_MAP(BXSelBtn, CWnd)
	//{{AFX_MSG_MAP(BXSelBtn)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// BXSelBtn message handlers

BOOL BXSelBtn::Create( LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID , CImageList* pImage, UINT nPos )
{
	m_pParentWnd = pParentWnd->GetParent();
	m_pIL = pImage;
	m_nPos = nPos;
	m_strText = lpszCaption;
	m_nID = nID;

	return CWnd::Create(NULL,NULL, dwStyle, rect, pParentWnd, nID );
}

void BXSelBtn::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (!m_Enabled)
		return;

	m_DrawPressed = TRUE;
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}

void BXSelBtn::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (!m_Enabled)
		return;

	CRect rect;
	GetWindowRect(rect);
    ScreenToClient(&rect);

	if (rect.PtInRect(point))
	{
		m_Pressed = 1;
		m_MouseOnButton = 0;
		m_pParentWnd->PostMessage(WM_COMMAND, m_nID, 0);
	}

	m_DrawPressed = FALSE;
	Invalidate();

	CWnd::OnLButtonUp(nFlags, point);
}

void BXSelBtn::OnPaint() 
{
	COLORREF clrWhite = GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF clrDkGrey = !bDotNetUI ? GetSysColor(COLOR_BTNSHADOW) : RGB(10, 36, 106);
	COLORREF clrMedGrey = !bDotNetUI ? GetSysColor(COLOR_BTNSHADOW) + RGB(5, 5, 5) : RGB(133, 146, 181);
	COLORREF clrLtGrey = !bDotNetUI ? GetSysColor(COLOR_BTNFACE) : RGB(182, 189, 210);
	COLORREF clrBlack = GetSysColor(COLOR_BTNTEXT);
	COLORREF clrBtnFace = GetSysColor(COLOR_BTNFACE);
	
	CPaintDC dc(this); // device context for painting
	CMemDC dcMem(&dc);
	
	CRect rc;
	GetClientRect(rc);
	
	if (bDotNetUI)
	{
		if (m_MouseOnButton) // mouse on and pressed
			dcMem.FillRect(rc,&CBrush(clrMedGrey));
		else if (m_Pressed || m_DrawPressed) // pressed but not mouse on
			dcMem.FillRect(rc,&CBrush(clrLtGrey));
		else
			dcMem.FillRect(rc,&CBrush(clrBtnFace)); // not pressed or mouse on
	}
	else
		dcMem.FillRect(rc, &CBrush(GetSysColor(COLOR_BTNSHADOW)));
	
	rc.DeflateRect(0, 0, 4, 0);

	if (!bDotNetUI)
	{
		if (m_MouseOnButton && !m_Pressed && !m_DrawPressed) // Up (and not pressed)
			dcMem.Draw3dRect(rc, clrLtGrey, clrBlack);
		else if (m_Pressed) // Down
		{
			if (!m_MouseOnButton)
				dcMem.FillRect(rc, &CBrush(clrMedGrey));

			dcMem.Draw3dRect( rc, clrBlack, clrLtGrey);
		}
		else if (m_DrawPressed)
		{
			dcMem.FillRect(rc, &CBrush(clrMedGrey));
			dcMem.Draw3dRect(rc, clrBlack, clrLtGrey);
		}
	}
	else
	{
		if (m_MouseOnButton || m_Pressed || m_DrawPressed)
			dcMem.Draw3dRect(rc, clrDkGrey, clrDkGrey);
	}

	// Centre image
	CPoint pt;

	if (m_Pressed || m_DrawPressed)
	{
		pt.x = ((rc.Width()  - 32) / 2) + 1;
		pt.y = ((rc.Height() - 32) / 2) - 8 + 1;
	}
	else
	{
		pt.x = (rc.Width()  - 32) / 2;
		pt.y = ((rc.Height() - 32) / 2) - 8;
	}

	dcMem.SetBkMode(TRANSPARENT);

	HICON hicon;
	hicon = m_pIL->ExtractIcon(m_nPos);
	CSize sz = CSize(32, 32);

	if (m_Enabled)
		dcMem.DrawState(pt, sz, hicon, DST_ICON | DSS_NORMAL, CBrush());
	else
		dcMem.DrawState(pt, sz, hicon, DST_ICON | DSS_DISABLED, CBrush());

	CFont *pFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	dcMem.SelectObject(pFont);

	CRect rcText;
	rcText.SetRect(0,pt.y+32+8,rc.Width(),pt.y+32+8);
	rcText.InflateRect(0,20);

	if (m_Pressed || m_DrawPressed)
		rcText.OffsetRect(1, 0);

	if (m_Enabled)
	{
		if (m_MouseOnButton || !bDotNetUI)
			dcMem.SetTextColor(clrWhite);
		else
			dcMem.SetTextColor(clrBlack);
		
		dcMem.DrawText(m_strText,rcText, DT_VCENTER|DT_SINGLELINE|DT_CENTER);
	}
	else
	{
		dcMem.SetTextColor(clrBlack);
		dcMem.DrawText(m_strText,rcText, DT_VCENTER|DT_SINGLELINE|DT_CENTER);

		rcText.OffsetRect(1, 1);
		dcMem.SetTextColor(clrWhite);
		dcMem.DrawText(m_strText,rcText, DT_VCENTER|DT_SINGLELINE|DT_CENTER);
	}
}

BOOL BXSelBtn::OnEraseBkgnd(CDC* pDC) 
{	
	return TRUE;
}
	
void BXSelBtn::SetState(BOOL bPressed)
{
	m_Pressed = bPressed;
	Invalidate();
}

void BXSelBtn::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd* pWnd;
	CWnd* pParent;

	CWnd::OnMouseMove(nFlags, point);

	// If the mouse enter the button with the left button pressed
	// then do nothing
	if (nFlags & MK_LBUTTON && m_MouseOnButton == FALSE)
		return;

	if (!m_Enabled)
		return;

	pWnd = GetActiveWindow();
	pParent = GetOwner();

	if ((GetCapture() != this) && (pParent != NULL))
	{
		m_MouseOnButton = TRUE;
		SetCapture();
		Invalidate();
	}
	else
	{
		POINT p2 = point;
		ClientToScreen(&p2);
		CWnd* wndUnderMouse = WindowFromPoint(p2);

		if (wndUnderMouse && wndUnderMouse->m_hWnd != this->m_hWnd)
		{
			// Redraw only if mouse goes out
			if (m_MouseOnButton == TRUE)
			{
				m_MouseOnButton = FALSE;
				Invalidate();
			}

			// If user is NOT pressing left button then release capture!
			if (!(nFlags & MK_LBUTTON)) ReleaseCapture();
		}
	}
}
