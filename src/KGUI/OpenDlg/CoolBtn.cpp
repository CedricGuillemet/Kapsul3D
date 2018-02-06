/////////////////////////////////////////////////////////////////////////////
// BXCoolBtn
// ========
// 
// To Use:
// 1. Create a Bitmap resource 16x15 Pixels normal default size for a toolbar
//    bitmap.
//
// 2. Call BXCoolBtns on Create function.
//
// 3. Call SetButtonImage specificing the Transparency color reference.
//    (Usally RGB(255, 0, 255) magenta)
// 
// 4. Add menu items with AddMenuItem using nMenuFlags to add disabled and
///   seperator menu items
//
// 5. Add the appropiate ON_COMMAND handlers in the parent windows message map
//
// 6. Enjoy...
////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  BXCoolBtn
//
// DESCRIPTION:	
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
// David Wulff			1.1			Stuff was changed (see individual functions)
//
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CoolBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nDropBtnWidth =  13;

BXCoolBtn::BXCoolBtn()
{
	m_bPushed = FALSE;
	m_bLoaded = FALSE;
	m_bMenuPushed = FALSE;
	m_bMenuLoaded = FALSE;
	
	ZeroMemory(&m_bm, sizeof m_bm);
	m_menu.CreatePopupMenu();
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  ~BXCoolBtn
//
// DESCRIPTION:	
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
//
////////////////////////////////////////////////////////////////////////////////
BXCoolBtn::~BXCoolBtn()
{
}


BEGIN_MESSAGE_MAP(BXCoolBtn, CButton)
//{{AFX_MSG_MAP(BXCoolBtn)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_SETFOCUS()
ON_WM_SYSCOLORCHANGE()
ON_WM_ERASEBKGND()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BXCoolBtn message handlers

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  Create
//
// DESCRIPTION:	Create the button
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
//
////////////////////////////////////////////////////////////////////////////////
BOOL BXCoolBtn::Create( LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
{
	dwStyle |= BS_OWNERDRAW; // Enforce
	m_pParentWnd = pParentWnd;
	m_nID = nID;
	return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID );	;
}



////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  DrawItem
//
// DESCRIPTION:	Called in response to draw the button
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
// David Wulff	8/8/00    1.1       Updated to look like the Office(r) 2000 button.
//
////////////////////////////////////////////////////////////////////////////////
void BXCoolBtn::DrawItem(DRAWITEMSTRUCT* lpDIS) 
{
	if (lpDIS->CtlType != ODT_BUTTON)
		return;
	
	CFont *pFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	
	CDC dcMem;
	CBitmap bmp;
	
	CRect btnRect(lpDIS->rcItem);
	CRect trueRect(btnRect);
	
	CDC *pDC = CDC::FromHandle(lpDIS->hDC);
	
	////////////////////////////////////////
	// Button Background                  //
	////////////////////////////////////////
	pDC->FillRect(trueRect,&CBrush(GetSysColor(COLOR_BTNFACE)));
	
	BOOL bDefaultBtn = GetWindowLong(m_hWnd,GWL_STYLE) & BS_DEFPUSHBUTTON;
	BOOL bDisabled = ODS_DISABLED & lpDIS->itemState;
	
	if (bDefaultBtn)
		btnRect.DeflateRect(1,1);
	
	CRect rectFocus(btnRect);
	
	rectFocus.DeflateRect(3,3);
	
	if (!m_bMenuPushed)
		rectFocus.OffsetRect(m_bPushed,m_bPushed);
	
	if (m_menu.GetMenuItemCount() > 0)
		rectFocus.right -= nDropBtnWidth;
	
	
	////////////////////////////////////////
	// Button in a normal state           //
	////////////////////////////////////////
	if (!m_bPushed || m_bMenuPushed)
		pDC->DrawFrameControl(&btnRect,DFC_BUTTON,DFCS_BUTTONPUSH);
	
	
	////////////////////////////////////////
	// Default Button State               //
	////////////////////////////////////////
	if ((bDefaultBtn || m_bPushed) && !bDisabled)
	{
		pDC->FrameRect(&lpDIS->rcItem,CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
		if (m_bPushed && !m_bMenuPushed)
			pDC->FrameRect(&btnRect,CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH))); 
	}
	
	
	////////////////////////////////////////
	// State Focus                        //
	////////////////////////////////////////
	if (lpDIS->itemState & ODS_FOCUS || m_bPushed) 
	{
		if (!m_bMenuPushed)
			pDC->DrawFocusRect(&rectFocus);
	}
	
	
	////////////////////////////////////////
	// Action Focus                       //
	////////////////////////////////////////
	if ((lpDIS->itemAction & ODA_FOCUS))
	{
		if (!m_bMenuPushed)
			pDC->DrawFocusRect(&rectFocus);
	}
	
	////////////////////////////////////////
	// Draw out bitmap                    //
	////////////////////////////////////////
	if (m_bLoaded)
		m_IL.DrawIndirect( pDC,0,CPoint(3+m_bPushed,3+m_bPushed),CSize(m_bm.bmWidth, m_bm.bmHeight),CPoint(0,0),ILD_NORMAL);
	
	////////////////////////////////////////
	// Draw out text                      //
	////////////////////////////////////////
	pDC->SelectObject(pFont);
	CRect rectText(rectFocus);
	rectFocus.left += m_bm.bmWidth + 2;
	
	CString strCaption;
	GetWindowText(strCaption);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetBkColor(GetSysColor(COLOR_BTNFACE));
	
	if (ODS_DISABLED & lpDIS->itemState)
	{
		rectFocus.OffsetRect(1,1);
		pDC->SetTextColor(GetSysColor(COLOR_WINDOW));
		pDC->DrawText(strCaption,rectFocus,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		
		rectFocus.OffsetRect(-1,-1);
		pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		pDC->DrawText(strCaption,rectFocus,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	}
	else
	{
		pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		pDC->DrawText(strCaption,rectFocus,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	}
	
	
	CRect rectSplit(btnRect);
	rectSplit.DeflateRect(2,2);
	rectSplit.right -= nDropBtnWidth;
	
	rectSplit.top -= 2;
	
	if(m_bPushed)
		rectSplit.OffsetRect(1, 1);
	
	////////////////////////////////////////
	// Drop down split                    //
	////////////////////////////////////////
	if (m_menu.GetMenuItemCount() > 0)
	{
		CPen brFace(PS_SOLID,1,GetSysColor(COLOR_3DSHADOW));
		pDC->SelectObject(&brFace);
		pDC->MoveTo(rectSplit.right, rectSplit.top);
		pDC->LineTo(rectSplit.right, rectSplit.bottom);
		
		
		CPen brLite(PS_SOLID,1,GetSysColor(COLOR_3DHILIGHT));
		pDC->SelectObject(&brLite);
		pDC->MoveTo(rectSplit.right+1 , rectSplit.top);
		pDC->LineTo(rectSplit.right+1, rectSplit.bottom);
		
		
		rectSplit.left = rectSplit.right;
		rectSplit.right += nDropBtnWidth;
		
		CPoint pt(rectSplit.CenterPoint());
		pt += CPoint(m_bPushed,m_bPushed);
		
		CPen penBlack(PS_SOLID, 1, bDisabled ? GetSysColor(COLOR_GRAYTEXT) : GetSysColor(COLOR_WINDOWTEXT));
		pDC->SelectObject(&penBlack);
		DrawArrow(pDC,pt);
		
		////////////////////////////////////////
		// Drop down state                    //
		////////////////////////////////////////
		if (m_bMenuPushed && !bDisabled)
		{    
			rectSplit.InflateRect(1,1);
			pDC->DrawEdge(rectSplit,BDR_SUNKENOUTER, BF_RECT);
			
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  DrawArrow
//
// DESCRIPTION:	Draws drop down arrow, we could use DrawFrameControl - a bit too 
//              messy
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
//
////////////////////////////////////////////////////////////////////////////////
void BXCoolBtn::DrawArrow(CDC* pDC,CPoint ArrowTip)
{
	
	CPoint ptDest;
	
	pDC->SetPixel(ArrowTip,RGB(0,0,0));
	
	ArrowTip -= CPoint(1,1);
	pDC->MoveTo(ArrowTip);
	
	ptDest = ArrowTip;
	ptDest += CPoint(3,0);
	pDC->LineTo(ptDest);
	
	ArrowTip -= CPoint(1,1);
	pDC->MoveTo(ArrowTip);
	
	ptDest = ArrowTip;
	ptDest += CPoint(5,0);
	pDC->LineTo(ptDest);
	
}


////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  OnLButtonDown
//
// DESCRIPTION:	handles button pressed state, including drop down menu
//              
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
//
////////////////////////////////////////////////////////////////////////////////
void BXCoolBtn::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	if (m_bMenuPushed)
	{
		m_bMenuPushed = FALSE;
		Invalidate();
		return;
		
	}
	
	if (HitMenuBtn(point))
	{
		m_bMenuPushed = TRUE;
		Invalidate();
		
		CRect rc;
		GetWindowRect(rc);
		
		int x = rc.left;
		int y = rc.bottom;
		
		m_menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,x,y,m_pParentWnd);
		
		m_bMenuPushed = FALSE;
	}
	else
	{
		m_bPushed = TRUE;
	}
	
	Invalidate();
	
	
	CButton::OnLButtonDown(nFlags, point);
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  OnLButtonUp
//
// DESCRIPTION:	Redraws button in normal state
//              
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
// DJ WULFF     6 SEP 00            sends notification to parent window
//
////////////////////////////////////////////////////////////////////////////////
void BXCoolBtn::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bPushed)
	{
		m_bPushed = FALSE;
		ReleaseCapture();
		Invalidate();
		
		m_pParentWnd->PostMessage(WM_COMMAND, m_nID, 0);
	}
	
	CButton::OnLButtonUp(nFlags, point);
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  OnMouseMove
//
// DESCRIPTION:	Tracks mouse whilst pressed
//              
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
//
////////////////////////////////////////////////////////////////////////////////
void BXCoolBtn::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bPushed)
	{
		ClientToScreen(&point);
		
		if (WindowFromPoint(point) != this)
		{
			m_bPushed = FALSE;
			ReleaseCapture();
			Invalidate();
		}
	}
	
	CButton::OnMouseMove(nFlags, point);
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  SetButtonImage
//
// DESCRIPTION:	Sets the button image, COLORREF crMask specifics the transparency
//              color              
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
//
////////////////////////////////////////////////////////////////////////////////
BOOL BXCoolBtn::SetButtonImage(UINT nResourceId, COLORREF crMask)
{
	// The ID must exist also as a bitmap resource!!!
	m_btnImage.LoadBitmap(nResourceId);  
	m_btnImage.GetObject(sizeof m_bm, &m_bm);
	m_IL.Create( nResourceId, m_bm.bmWidth, 1, crMask );
	m_bLoaded = TRUE;
	
	return m_bLoaded;
}

void BXCoolBtn::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);
	
	Invalidate();
	
}


////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  OnSysColorChange
//
// DESCRIPTION:	Called when system colors change, force a button redraw
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
//
////////////////////////////////////////////////////////////////////////////////
void BXCoolBtn::OnSysColorChange() 
{
	CButton::OnSysColorChange();
	Invalidate();	
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  HitMenuBtn
//
// DESCRIPTION:	Helper function to test for menu button hit...
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
//
////////////////////////////////////////////////////////////////////////////////
BOOL BXCoolBtn::HitMenuBtn(CPoint point)
{
	if (!m_bMenuLoaded)
		return FALSE; // Don't allow menu button drop down if no menu items are loaded
	
	ClientToScreen(&point);
	
	CRect rect;
	GetWindowRect(rect);
	rect.left = rect.right - nDropBtnWidth;
	
	return rect.PtInRect(point);    
}


////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  AddMenuItem
//
// DESCRIPTION:	Adds a menu item and id to our menu.
//
// NOTES:			
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
//
////////////////////////////////////////////////////////////////////////////////
BOOL BXCoolBtn::AddMenuItem(UINT nMenuId,const CString strMenu, UINT nMenuFlags)
{
	BOOL bRet = m_menu.AppendMenu(nMenuFlags | MF_STRING, nMenuId, (LPCTSTR)strMenu);
	
	m_bMenuLoaded |= bRet;
	
	return bRet;
}

BOOL BXCoolBtn::AddMenuSeperator() // shortcut function
{
	BOOL bRet = m_menu.AppendMenu(MF_SEPARATOR);
	
	m_bMenuLoaded |= bRet;
	
	return bRet;
}

BOOL BXCoolBtn::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}
