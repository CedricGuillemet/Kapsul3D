// MemoEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "MemoEditCtrl.h"
#include "MemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Brush sizes for drawing the button background
#define BRUSHWIDTH      8
#define BRUSHHEIGHT     8

/////////////////////////////////////////////////////////////////////////////
// Button states
#define BTN_UP          0x01
#define BTN_DOWN        0x02
#define BTN_DISABLED    0x04
#define BTN_FLAT        0x08

extern BOOL IsWindow(CWnd *pWnd);

/////////////////////////////////////////////////////////////////////////////
// CMemoEditCtrl

CMemoEditCtrl::CMemoEditCtrl()
{
    m_nButtonState      = BTN_UP;
    m_nButtonWidth      = -1;
    m_rcButtonRect.SetRectEmpty();
}

CMemoEditCtrl::~CMemoEditCtrl()
{
}


BEGIN_MESSAGE_MAP(CMemoEditCtrl, CEdit)
	//{{AFX_MSG_MAP(CMemoEditCtrl)
	ON_WM_ENABLE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoEditCtrl message handlers

void CMemoEditCtrl::OnEnable(BOOL bEnable)
{
    CEdit::OnEnable(bEnable);
    Redraw(TRUE);
    DrawButton(bEnable ? BTN_UP : BTN_DISABLED);
}

void CMemoEditCtrl::OnNcCalcSize(BOOL bCalcValidRects,NCCALCSIZE_PARAMS FAR* lpncsp)
{
    CEdit::OnNcCalcSize(bCalcValidRects, lpncsp);

    // if m_nButtonWidth is -1, set the button width to 80% of the control height
    // else set the button width to m_nButtonWidth
    int ButtonWidth = (m_nButtonWidth == -1) ? (lpncsp->rgrc[0].bottom - lpncsp->rgrc[0].top) * 8/10 : m_nButtonWidth;
    
    // set button area equal to client area of edit control
    m_rcButtonRect = lpncsp->rgrc[0];
    
    int neutral = /*ButtonWidth > 2 ? 1 :*/ 0;
    lpncsp->rgrc[0].right -= ButtonWidth + neutral;
    // shrink the button so its left side is at the right side of client area
    m_rcButtonRect.left = lpncsp->rgrc[0].right + neutral;

	if (bCalcValidRects)
        // convert button coordinates from parent client coordinates to control window coordinates
        m_rcButtonRect.OffsetRect(-lpncsp->rgrc[1].left, -lpncsp->rgrc[1].top);
    m_rcButtonRect.NormalizeRect();
}

void CMemoEditCtrl::OnNcPaint()
{
 CEdit::OnNcPaint();
 DrawButton(m_nButtonState);
}

void CMemoEditCtrl::OnLButtonDown(UINT nFlags,CPoint point)
{
	CEdit::OnLButtonDown(nFlags,point);

    ClientToScreen(&point);
    if(ScreenPointInButtonRect(point))
	{
	 m_nButtonState = BTN_DOWN;
	 DrawButton(m_nButtonState);
	}
}

void CMemoEditCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
    CEdit::OnLButtonUp(nFlags, point);

	if(m_nButtonState != BTN_UP)
		DrawButton(BTN_UP);
    ClientToScreen(&point);
    if(ScreenPointInButtonRect(point))
		ButtonClicked();
}

void CMemoEditCtrl::OnMouseMove(UINT nFlags,CPoint point)
{
 CEdit::OnMouseMove(nFlags,point);

 if(ScreenPointInButtonRect(point))
 {
	if(m_nButtonState != BTN_DOWN)
		DrawButton(BTN_DOWN);
 }
 else if(m_nButtonState != BTN_UP)
	DrawButton(BTN_UP);
}

void CMemoEditCtrl::OnSize(UINT nType, int cx, int cy) 
{
    CEdit::OnSize(nType, cx, cy);

    SetWindowPos(NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

UINT CMemoEditCtrl::OnNcHitTest(CPoint point) 
{
    UINT where = CEdit::OnNcHitTest(point);
    if (where == HTNOWHERE && ScreenPointInButtonRect(point))
        where = HTBORDER;
	return where;
}

void CMemoEditCtrl::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
    CEdit::OnNcLButtonDown(nHitTest, point);

    if (ScreenPointInButtonRect(point))
    {
        SetFocus();
        SetCapture();
        DrawButton(BTN_DOWN);
    }
}

void CMemoEditCtrl::DrawButton(int nButtonState)
{   // if the button is too small, do not draw it
    if (m_rcButtonRect.Width() < 3 || m_rcButtonRect.Height() < 3)
        return;

	ASSERT(IsWindow(this));

    // if the control is disabled, ensure the button is drawn disabled
    if (GetStyle() & WS_DISABLED)
        nButtonState = BTN_DISABLED;

    CRect DrawRect(m_rcButtonRect);
    DrawRect.OffsetRect(0 - m_rcButtonRect.left, 0 - m_rcButtonRect.top);

    CWindowDC WndDC(this);     // get the DC for drawing

    // Create a memory DC to prevent flicker
    CDC DC;
    DC.CreateCompatibleDC(&WndDC);
    int savedDC = DC.SaveDC();
    CBitmap Bitmap;
    Bitmap.CreateCompatibleBitmap(&WndDC, m_rcButtonRect.Width(), m_rcButtonRect.Height());
    DC.SelectObject(&Bitmap);

    // use HS_DIAGCROSS pattern brush to test brush alignment
    CBrush theBrush(/*HS_DIAGCROSS,*/ GetSysColor(COLOR_3DFACE));     // the colour of the button background
    CPoint BrushOrg;
    CPoint Origin = WndDC.GetBrushOrg();
    BrushOrg.x = (BRUSHWIDTH - (m_rcButtonRect.left - Origin.x) % BRUSHWIDTH);
    BrushOrg.y = (BRUSHHEIGHT - (m_rcButtonRect.top - Origin.y) % BRUSHHEIGHT);
    DC.SetBrushOrg(BrushOrg);

    DC.SelectObject(&theBrush);
    DC.FillRect(&DrawRect, &theBrush);

    if (nButtonState == BTN_DOWN)
    {
        // draw the border
        CPen thePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
        CPen *pOldPen = DC.SelectObject(&thePen);
        DC.Rectangle(DrawRect);
        DC.SelectObject(pOldPen);
        thePen.DeleteObject();

        DrawDots(&DC, GetSysColor(COLOR_BTNTEXT), 1);
    }
    else    // draw button as up
    {
        // draw the border
        DC.DrawEdge(DrawRect, EDGE_RAISED, BF_RECT);

        if (nButtonState & BTN_DISABLED)
        {
         DrawDots(&DC, GetSysColor(COLOR_3DHILIGHT), 1);
         DrawDots(&DC, GetSysColor(COLOR_3DSHADOW));
        }
        else if (nButtonState & BTN_UP)
        {
         COLORREF dotcolour = GetSysColor(COLOR_BTNTEXT);
		 DrawDots(&DC, dotcolour);
        }
        else
        {
            ASSERT(FALSE);  // Invalid nButtonState
        }
    }

    // Blit the button image onto the screen
    WndDC.BitBlt(m_rcButtonRect.left,
        m_rcButtonRect.top,
        m_rcButtonRect.Width(),
        m_rcButtonRect.Height(),
        &DC,
        0,
        0,
        SRCCOPY);

    // clean up the memory DC
    DC.RestoreDC(savedDC);
    Bitmap.DeleteObject();

    // update m_nButtonState
    m_nButtonState = m_nButtonState & BTN_FLAT ? nButtonState | BTN_FLAT : nButtonState;
}

void CMemoEditCtrl::DrawDots(CDC *pDC, COLORREF CR, int nOffset /* = 0 */)
{
    int width = m_rcButtonRect.Width();         
    div_t divt = div(width, 4);
    int delta = divt.quot;                      
    int left = width / 2 - delta - (divt.rem ? 0 : 1); 
    width = width / 10;                         
    int top = m_rcButtonRect.Height() / 2 - width / 2;  
    left += nOffset;                            
    top += nOffset;

    if (width < 2)
    {
        pDC->SetPixelV(left, top, CR);
        left += delta;
        pDC->SetPixelV(left, top, CR);
        left += delta;
        pDC->SetPixelV(left, top, CR);
    }
    else
    {
        CPen thePen(PS_SOLID, 1, CR);           
        CPen *pOldPen = pDC->SelectObject(&thePen);
        CBrush theBrush(CR);
        CBrush *pOldBrush = pDC->SelectObject(&theBrush);
        pDC->Ellipse(left, top, left + width, top + width);
        left += delta;
        pDC->Ellipse(left, top, left + width, top + width);
        left += delta;
        pDC->Ellipse(left, top, left + width, top + width);
        pDC->SelectObject(pOldBrush);           // reset the DC
        theBrush.DeleteObject();
        pDC->SelectObject(pOldPen);
        thePen.DeleteObject();
    }
}

void CMemoEditCtrl::Redraw(BOOL Flat)
{

}

BOOL CMemoEditCtrl::ScreenPointInButtonRect(CPoint point)
{
    CRect ControlRect;
    GetWindowRect(&ControlRect);
    // convert point from screen coordinates to window coordinates
    point.Offset(-ControlRect.left, -ControlRect.top);
    return m_rcButtonRect.PtInRect(point);
}

void CMemoEditCtrl::ButtonClicked()
{
 CString tmp;
 GetWindowText(tmp);

 CMemoDlg dlg;
 dlg.m_MemoEdit = tmp;
 if(dlg.DoModal() == IDOK)
 {
  SetWindowText(dlg.m_MemoEdit);
 }
}
