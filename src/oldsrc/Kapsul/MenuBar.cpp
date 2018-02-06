// MenuBar.cpp : implementation file
// CMenuBar version 2.12

#include "stdafx.h"
#include "MenuBar.h"
#include <afxole.h>

#define max(a, b)  (((a) > (b)) ? (a) : (b)) 


//#include "memmgr/mmgr.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
	const BOOL bTraceOn = FALSE;
	#define LTRACE if (bTraceOn) TRACE
	const BOOL bTraceOn2 = TRUE;
	#define LTRACE2 if (bTraceOn2) TRACE
#else
	#define LTRACE
	#define LTRACE2
#endif

//////////////////////////////////////////////////////////////////////
// I've found string resource of "More windows" in "user.exe".
// But I can't load it, so please replace a following with your language.
static const TCHAR _szMoreWindows[] = _T("&More windows...");

//////////////////////////////////////////////////////////////////////
// used for OLE menu (easy fix)
static BOOL _bWindowMenuSendCmd = FALSE;
static int _nPrevIndexForCmd = -1;

//////////////////////////////////////////////////////////////////////
// hook
static CMenuBar* g_pMenuBar = NULL;
static HHOOK	 g_hMsgHook = NULL;

// message
const UINT CMenuBar::WM_GETMENU = ::RegisterWindowMessage(_T("CMenuBar::WM_GETMENU"));
const UINT MB_SET_MENU_NULL = ::RegisterWindowMessage(_T("CMenuBar::MB_SET_MENU_NULL"));

const int cxBorder2 = ::GetSystemMetrics(SM_CXBORDER)*2;
const int cyBorder2 = ::GetSystemMetrics(SM_CYBORDER)*2;

// common resources
static CFont _fontHorzMenu, _fontVertMenu;
static int _cyHorzFont, _cyMenuOnBar, _cyTextMargin;
const int CXTEXTMARGIN = 5;

static BOOL _InitCommonResources(BOOL bForce = FALSE)
{
	if (bForce == FALSE && _fontHorzMenu.m_hObject != NULL)
		return TRUE;// no need to reinitialize

	// clean up
	_fontHorzMenu.DeleteObject();
	_fontVertMenu.DeleteObject();

	// create fonts
	NONCLIENTMETRICS info; info.cbSize = sizeof(info);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);
	if (!_fontHorzMenu.CreateFontIndirect(&info.lfMenuFont))
		return FALSE;

	// create vertical font
	info.lfMenuFont.lfEscapement = -900;
	info.lfMenuFont.lfOrientation = -900;
	if (!_fontVertMenu.CreateFontIndirect(&info.lfMenuFont))
		return FALSE;

	// get font height
	_cyHorzFont = abs(info.lfMenuFont.lfHeight);

	// calc Y text margin
	_cyMenuOnBar = info.iMenuHeight;
	_cyMenuOnBar = max(_cyMenuOnBar, ::GetSystemMetrics(SM_CYSMICON));
	_cyTextMargin = (_cyMenuOnBar - _cyHorzFont) / 2;

	return TRUE;
}

// I wanted to control popup point, but I've fount we can never get popupmenu rect before popup.
// even if not owner draw menu...
static CPoint _ComputeMenuTrackPoint(const CRect& rcItem, DWORD dwStyle, UINT& fuFlags, TPMPARAMS& tpm)
{
	fuFlags = TPM_LEFTBUTTON | TPM_LEFTALIGN | TPM_HORIZONTAL;
	tpm.cbSize = sizeof(tpm);
	CPoint pt;
	CRect& rcExclude = (CRect&)tpm.rcExclude;
	CWnd::GetDesktopWindow()->GetWindowRect(&rcExclude);

	CRect rcFrame;
	AfxGetMainWnd()->GetWindowRect(&rcFrame);

	switch (dwStyle & CBRS_ALIGN_ANY) {
	case CBRS_ALIGN_RIGHT:
	case CBRS_ALIGN_LEFT:
		pt = CPoint(rcItem.right+1, rcItem.top-1);
		// to avoid strange menu flip, won't do : [rcExclude.right = rcItem.right+1;]
		// I want to use : fuFlags |= TPM_HORNEGANIMATION;
		break;

	default: //	case CBRS_ALIGN_TOP:
		pt = CPoint(rcItem.left-1, rcItem.bottom);
		rcExclude.bottom = rcItem.bottom+1;// <- insead of [fuFlags |= TPM_VERPOSANIMATION;]

		break;
	}
	return pt;
}

static int _CalcTextWidth(const CString& strText)
{
	CWindowDC dc(NULL);
	CRect rcText(0, 0, 0, 0);
	CFont* pOldFont = dc.SelectObject(&_fontHorzMenu);
	dc.DrawText(strText, &rcText, DT_SINGLELINE | DT_CALCRECT);
	dc.SelectObject(pOldFont);

	return rcText.Width();
}

// grippers pasted from MFC6
#define CX_GRIPPER  3
#define CY_GRIPPER  3
#define CX_BORDER_GRIPPER 2
#define CY_BORDER_GRIPPER 2
#define CX_GRIPPER_ALL CX_GRIPPER + CX_BORDER_GRIPPER*2
#define CY_GRIPPER_ALL CY_GRIPPER + CY_BORDER_GRIPPER*2

/////////////////////////////////////////////////////////////////////////////
// CMenuBar
BEGIN_MESSAGE_MAP(CMenuBar, CControlBar)
	//{{AFX_MSG_MAP(CMenuBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(MB_SET_MENU_NULL, OnSetMenuNull)
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CMenuBar, CControlBar)

/////////////////////////////////////////////////////////////////////////////
// CMenuBar Construction
CMenuBar::CMenuBar()
{
	m_nCurIndex  = -1;
	m_nTrackingState = none;
	m_bProcessRightArrow = m_bProcessLeftArrow = TRUE;
	m_bIgnoreAlt = FALSE;
	m_hMenu = NULL;
	m_nIDEvent = NULL;

	m_bMDIMaximized = FALSE;
	m_hWndMDIClient = NULL;
	m_hWndActiveChild = NULL;

	m_pMenuIcon = NULL;
	m_pMenuControl = NULL;

	m_bDelayedButtonLayout = TRUE;
	m_dwExStyle = 0;

	m_bFrameActive = FALSE;
	m_bMDIApp = FALSE;
}

BOOL CMenuBar::Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID)
{
	return CreateEx(pParentWnd, dwStyle,
		CRect(m_cxLeftBorder, m_cyTopBorder, m_cxRightBorder, m_cyBottomBorder), nID);
}

BOOL CMenuBar::CreateEx(CWnd* pParentWnd, DWORD dwStyle, CRect rcBorders, UINT nID)
{
	ASSERT_VALID(pParentWnd);// must have a parent
	ASSERT (!((dwStyle & CBRS_SIZE_FIXED) && (dwStyle & CBRS_SIZE_DYNAMIC)));

	SetBorders(rcBorders);

	// save the original style
	m_dwExStyle = dwStyle;

	// save the style
	m_dwStyle = (dwStyle & CBRS_ALL);// ******fixed by Mark Gentry, thanx!******
	
	dwStyle &= ~CBRS_ALL;

	CString strClass = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW |
		CS_DBLCLKS,// don't forget!
		AfxGetApp()->LoadStandardCursor(IDC_ARROW),
		(HBRUSH)(COLOR_BTNFACE+1));

	return CWnd::Create(strClass, _T("MenuBar"), dwStyle, CRect(), pParentWnd, nID);
}

int CMenuBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CWnd* pFrame = GetOwner();
	ASSERT_VALID(pFrame);

	// hook frame window to trap WM_MENUSELECT
	m_hookFrame.Install(this, pFrame->GetSafeHwnd());

	// If this is an MDI app, hook client window to trap WM_MDISETMENU
	if (pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd))) {
		m_bMDIApp = TRUE;
		m_hWndMDIClient = ((CMDIFrameWnd*)pFrame)->m_hWndMDIClient;
		ASSERT(::IsWindow(m_hWndMDIClient));
		m_hookMDIClient.Install(this, m_hWndMDIClient);
	}

	if (!_InitCommonResources()) {
		TRACE(_T("Failed to create menubar resource\n"));
		return FALSE;
	}	

	return 0;
}

BOOL CMenuBar::InitItems()
{
	ASSERT(m_hMenu);

	// clean up all items
	DeleteItems();

	// buttons
	for (int i = 0; i < ::GetMenuItemCount(m_hMenu); ++i) {
		m_arrItem.Add(new CMenuButton(m_hMenu, i));
	}

	if (m_bMDIApp) {
		// icon
		m_pMenuIcon = new CMenuIcon(this);
		m_arrItem.InsertAt(0, m_pMenuIcon);
		// frame control
		m_pMenuControl = new CMenuControl(this);
		m_arrItem.Add(m_pMenuControl);

		// reinitializing
		m_pMenuIcon->OnActivateChildWnd();
		m_pMenuControl->OnActivateChildWnd();
	}

	return TRUE;
}

BOOL CMenuBar::LoadMenuBar(UINT nIDResource)
{
	ASSERT(m_hMenu == NULL);
//	if (m_hMenu) {
//		::DestroyMenu(m_hMenu);
//		m_hMenu = NULL;
//	}

	ASSERT_VALID(m_pDockSite);
	if (m_pDockSite->GetMenu()) {
		PostMessage(MB_SET_MENU_NULL, (WPARAM)m_pDockSite->GetSafeHwnd());
	}
	
	m_hMenu = ::LoadMenu(AfxGetInstanceHandle(), MAKEINTRESOURCE(nIDResource));
	if (m_hMenu == NULL) {
		TRACE(_T("Failed to load menu\n"));
		return FALSE;
	}

	return InitItems();
}

HMENU CMenuBar::LoadMenu(HMENU hMenu, HMENU hWindowMenu)
{
	ASSERT(::IsMenu(hMenu));
	ASSERT_VALID(this);
	
	CFrameWnd* pFrame = GetParentFrame();
	if (::GetMenu(pFrame->GetSafeHwnd()) != NULL) {
		// not to make MFC ignore SetMenu(NULL), post it.
		PostMessage(MB_SET_MENU_NULL, (WPARAM)pFrame->GetSafeHwnd());
	}

	HMENU hOldMenu = m_hMenu;
	m_hMenu = hMenu;// menu is shared with MFC

	// initialize Items 
	VERIFY(InitItems());

	if (hMenu) {
		m_hWindowMenu = hWindowMenu;
		RefreshBar();// and menubar itself
	}

	return hOldMenu;
}

void CMenuBar::RefreshBar()
{
	InvalidateRect(NULL);

#if _MFC_VER >= 0x600
		if (GetParent()->IsKindOf(RUNTIME_CLASS(CReBar))) {
			m_bDelayedButtonLayout = TRUE;// to avoid ASSERTION
			Layout();
		}
#endif

	CFrameWnd* pFrame = (CFrameWnd*)GetTopLevelFrame();
	ASSERT_VALID(pFrame); ASSERT(pFrame->IsFrameWnd());
	pFrame->RecalcLayout();

	// floating frame
	CFrameWnd* pMiniFrame = GetParentFrame();
	if (pMiniFrame->IsKindOf(RUNTIME_CLASS(CMiniFrameWnd)))
		pMiniFrame->RecalcLayout();
}

/////////////////////////////////////////////////////////////////////////////
// CMenuBar clean up 
CMenuBar::~CMenuBar()
{

}

void CMenuBar::DeleteItems()
{
	for(int i = 0; i < m_arrItem.GetSize(); ++i) {
		CMenuItem* pItem = m_arrItem[i];
		delete pItem;
	}

	m_arrItem.RemoveAll();

	m_pMenuIcon = NULL;
	m_pMenuControl = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CMenuBar draw
void CMenuBar::DoPaint(CDC* pDC)
{
//	if (m_bDelayedButtonLayout)
//		Layout();

	//LTRACE(_T("CMenuBar::DoPaint\n"));
	CRect rect;	GetClientRect(rect);

	// draw items
	for (int i = 0; i < m_arrItem.GetSize(); ++i) {
		m_arrItem[i]->Update(pDC);
	}

	// delay draw captions 
	if (m_pMenuControl) {
		if (IsFloating()) {
			m_pMenuControl->DelayLayoutAndDraw(pDC, rect.Size());
		}
		else {
			if (m_dwStyle & CBRS_ORIENT_HORZ)
				m_pMenuControl->DelayLayoutAndDraw(pDC, CSize(GetClipBoxLength(TRUE), rect.Height()));
			else
				m_pMenuControl->DelayLayoutAndDraw(pDC, CSize(rect.Width(), GetClipBoxLength(FALSE)));
		}
	}
}

void CMenuBar::UpdateBar(TrackingState nState, int nNewIndex)
{
	if (m_nTrackingState == buttonmouse)	
		m_bIgnoreAlt = FALSE;// if prev state is BUTTONMOUSE, always should be FALSE!

	m_nTrackingState = nState;

#ifdef _DEBUG
//	static LPCTSTR lpszStates[] = { _T("NONE"), _T("BUTTON"), _T("POPUP"), _T("BUTTONMOUSE") };
//	LTRACE(_T("CMenuBar::UpdateBar state to %s, button=%d\n"),
//		lpszStates[nState], nNewIndex);
#endif

	// clean up
	if (IsValidIndex(m_nCurIndex)) {
		CMenuItem* pItem = m_arrItem[m_nCurIndex];
		CClientDC dc(this);
		pItem->ModifyState(MISTATE_HOT | MISTATE_PRESSED, 0);
		pItem->Update(&dc);

		// draw captions forcefully
		if (m_pMenuControl) {
			CRect rcCross = m_pMenuControl->GetRect() & m_arrItem[m_nCurIndex]->GetRect();
			if (!rcCross.IsRectEmpty()) {
				m_pMenuControl->ForceDrawControl(&dc);
			}
		}

		m_nCurIndex = -1;
	}

	if (nState != none) {
		ASSERT(IsValidIndex(nNewIndex));
		m_nCurIndex = nNewIndex;
		CMenuItem* pItem = m_arrItem[m_nCurIndex];
		CClientDC dc(this);

		if (nState == button || nState == buttonmouse) {
			pItem->ModifyState(MISTATE_PRESSED, MISTATE_HOT);
			pItem->Update(&dc);
		}
		else if (nState == popup) {
			pItem->ModifyState(MISTATE_HOT, MISTATE_PRESSED);
			pItem->Update(&dc);
		}

		// draw captions forcefully
		if (m_pMenuControl) {
			CRect rcCross = m_pMenuControl->GetRect() & m_arrItem[m_nCurIndex]->GetRect();
			if (!rcCross.IsRectEmpty()) {
				m_pMenuControl->ForceDrawControl(&dc);
			}
		}
	}
	else {
		// must be default parameter
		ASSERT(nNewIndex == -1);
	}

	m_bProcessRightArrow = m_bProcessLeftArrow = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMenuBar message handler
int CMenuBar::HitTestOnTrack(CPoint point)
{
	for (int i = 0; i < GetItemCount(); ++i) {
		CMenuItem* pItem = m_arrItem[i];
		CRect rcItem = pItem->GetRect();
		
		if ((pItem->GetStyle() & MISTYLE_TRACKABLE) &&
			rcItem.PtInRect(point))
			return i;
	}

	return -1;
}

void CMenuBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
//	LTRACE("CMenuBar::OnLButtonDown\n");
	if (m_pMenuControl && m_pMenuControl->OnMouseMsg(WM_LBUTTONDOWN, nFlags, point)) {
		return;		// eat it!
	}	

	int nIndex = HitTestOnTrack(point);
	if (IsValidIndex(nIndex) &&	(m_arrItem[nIndex]->GetStyle() & MISTYLE_TRACKABLE)) {
		TrackPopup(nIndex);
		return;		// eat it!
	}

	CControlBar::OnLButtonDown(nFlags, point);
}

void CMenuBar::OnMouseMove(UINT nFlags, CPoint point)
{
//	LTRACE(_T("CMenuBar::OnMouseMove\n"));

	if (m_pMenuControl && m_pMenuControl->OnMouseMsg(WM_MOUSEMOVE, nFlags, point)) {
		CControlBar::OnMouseMove(nFlags, point);
		return;
	}

	int nIndex = HitTestOnTrack(point);
	if (IsValidIndex(nIndex)) {	
		if (m_nCurIndex == -1 || m_nCurIndex != nIndex) {// if other button
			UpdateBar(buttonmouse, nIndex);// button made hot with mouse

			if (!m_nIDEvent)
				m_nIDEvent = SetTimer(1, 100, NULL);
		}
	}
	else {
		UpdateBar();
	}

	CControlBar::OnMouseMove(nFlags, point);
}

LRESULT CMenuBar::OnSetMenuNull(WPARAM wParam, LPARAM)
{
	HWND hWnd = (HWND)wParam;
	ASSERT(::IsWindow(hWnd));
	::SetMenu(hWnd, NULL);
	
	return 0;
}

LRESULT CMenuBar::OnSettingChange(WPARAM wParam, LPARAM lParam)
{
	// reinitialize fonts etc
	if (!_InitCommonResources(TRUE)) {
		TRACE(_T("Failed to create bar resource\n"));
		return FALSE;
	}

	VERIFY(InitItems());

	CFrameWnd* pFrame = GetParentFrame();
	ASSERT_VALID(pFrame);
	pFrame->RecalcLayout();
	return 0;
}

void CMenuBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: 
//	LTRACE(_T("CMenuBar::OnLButtonUp\n"));
	if (m_pMenuControl && m_pMenuControl->OnMouseMsg(WM_LBUTTONUP, nFlags, point)) {
		CControlBar::OnLButtonUp(nFlags, point);
		return;
	}	

	CControlBar::OnLButtonUp(nFlags, point);
}

void CMenuBar::CheckActiveChildWndMaximized()
{
	//LTRACE(_T("CMenuBar::CheckActiveChildWndMaximized\n"));
	ASSERT(m_pMenuControl);
	ASSERT(m_pMenuIcon);

	BOOL bMaximized = FALSE;
	GetActiveChildWnd(bMaximized);
	if (m_bMDIMaximized != bMaximized) {
		LTRACE(_T("CMenuBar::CheckActiveChildWndMaximized---state changed, refreshing\n"));
		m_bMDIMaximized = bMaximized;
		m_pMenuControl->OnActivateChildWnd();
		m_pMenuIcon->OnActivateChildWnd();
		RefreshBar();
	}
}

void CMenuBar::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	LTRACE(_T("CMenuBar::OnInitMenuPopup\n"));
	CMenu menu;
	menu.Attach((HMENU)m_hWindowMenu);

	// scan for first window command
	int n = menu.GetMenuItemCount();
	BOOL bAddSeperator = TRUE;
	for (int iPos=0; iPos<n; iPos++) {
		if (menu.GetMenuItemID(iPos) >= AFX_IDM_FIRST_MDICHILD) {
			bAddSeperator = FALSE;
			break;
		}
	}

	// iPos is either first window item, or end if none found.

	// delete everything after.
	while (iPos < (int)menu.GetMenuItemCount())
		menu.RemoveMenu(iPos, MF_BYPOSITION);

	// get active window so I can check its menu item
	ASSERT(m_hWndMDIClient);
	HWND hwndActive = (HWND)::SendMessage(m_hWndMDIClient,
		WM_MDIGETACTIVE, 0, NULL);

	// append window names in the form "# title"
	// *****fixed by VORGA, thanks!*****
	int iWin;
	int nID = AFX_IDM_FIRST_MDICHILD;
	CString sWinName, sMenuItem;
	HWND hwnd;
	for (iWin = 1; iWin <= 10; iWin++, nID++)
	{
		hwnd = ::GetDlgItem(m_hWndMDIClient, nID);
		if (hwnd == NULL)
			break;

		if (bAddSeperator)
		{
			menu.InsertMenu(iPos++, MF_BYPOSITION | MF_SEPARATOR);
		bAddSeperator = FALSE;
		}

		if (iWin < 10)
		{
			CWnd::FromHandle(hwnd)->GetWindowText(sWinName);
			sMenuItem.Format(_T("&%d %s"), iWin, (LPCTSTR)sWinName);
			menu.InsertMenu(iPos, MF_BYPOSITION, nID, sMenuItem);
			if (hwnd == hwndActive)
				menu.CheckMenuItem(iPos, MF_BYPOSITION | MF_CHECKED);
		}
		else
		{
			menu.InsertMenu(iPos, MF_BYPOSITION, nID, _szMoreWindows);
		}
		iPos++;
	}

	menu.Detach();
}

void CMenuBar::OnSetMenu(HMENU hNewMenu, HMENU hWindowMenu)
{
	ASSERT(m_pMenuIcon && m_pMenuControl);
	// We can get active MDI child window on this message!
	BOOL bMax = FALSE;
	HWND hWndChild = GetActiveChildWnd(bMax);

	if (!m_hWndActiveChild || m_hWndActiveChild != hWndChild) {// an active child window changed
		LTRACE(_T("CMenuBar::OnSetMenu---an active child window changed\n"));
		m_hWndActiveChild = hWndChild;
		// tell MenuIcon child window has been changed
		m_pMenuIcon->OnActivateChildWnd();
	}

	if (!m_hMenu || m_hMenu != hNewMenu) {	// menu changed
		LTRACE(_T("CMenuBar::OnSetMenu---menu changed\n"));
		LoadMenu(hNewMenu, hWindowMenu);	// set menubar menu
		GetOwner()->SetMenu(NULL);			// clear frame menu
	}
}

void CMenuBar::OnNcPaint() 
{
	EraseNonClientEx();
}

UINT CMenuBar::OnNcHitTest(CPoint point) 
{
	// make nonclient area clickable
	return HTCLIENT;
}

void CMenuBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	// calculate border space (will add to top/bottom, subtract from right/bottom)
	CRect rect; rect.SetRectEmpty();
	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	_CalcInsideRect(rect, bHorz);
//	ASSERT(_afxComCtlVersion != -1);
//	ASSERT(_afxComCtlVersion >= VERSION_IE4 || rect.top >= 2);

	// adjust non-client area for border space
	lpncsp->rgrc[0].left += rect.left;
	lpncsp->rgrc[0].top += rect.top;
	// previous versions of COMCTL32.DLL had a built-in 2 pixel border
//	if (_afxComCtlVersion < VERSION_IE4)
//		lpncsp->rgrc[0].top -= 2;
	lpncsp->rgrc[0].right += rect.right;
	lpncsp->rgrc[0].bottom += rect.bottom;
}

void CMenuBar::OnDestroy() 
{
	CControlBar::OnDestroy();
	
	// TODO: 
	DeleteItems();
	
	if (m_nIDEvent)
		KillTimer(m_nIDEvent);

		// for SDI application
	if (m_bMDIApp == FALSE && m_hMenu != NULL)
		::FreeResource(m_hMenu);
}

void CMenuBar::OnTimer(UINT nIDEvent) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (m_nTrackingState == buttonmouse) {
		CPoint pt; ::GetCursorPos(&pt);
		CRect rect;
		GetWindowRect(&rect);

		if (!rect.PtInRect(pt)) {
			UpdateBar();

			if (m_nIDEvent) {
				KillTimer(m_nIDEvent);
				m_nIDEvent = NULL;
			}
		}
	}	

	CControlBar::OnTimer(nIDEvent);
}

HWND CMenuBar::GetActiveChildWnd(BOOL& bMaximized)
{
	if (!m_hWndMDIClient)
		return NULL;

	BOOL bMax = FALSE;
	HWND hWnd = (HWND)::SendMessage(m_hWndMDIClient,
		WM_MDIGETACTIVE, 0, (LPARAM)&bMax);
	bMaximized = bMax;

	return hWnd;
}

/////////////////////////////////////////////////////////////////////////////
// CMenuBar system hook
void CMenuBar::OnMenuSelect(HMENU hMenu, UINT nIndex)
{
//	LTRACE(_T("CMenuBar::OnMenuSelect\n"));
	if (m_nTrackingState == popup) {
		m_bProcessRightArrow = (::GetSubMenu(hMenu, nIndex) == NULL);
		HMENU hSubMenu = ::GetSubMenu(hMenu, m_nCurIndex);
		if (hSubMenu == NULL)
			return;
		m_bProcessLeftArrow = (hMenu == hSubMenu);
	}
}

void CMenuBar::OnFrameNcActivate(BOOL bActive) 
{
	CFrameWnd* pFrame = GetTopLevelFrame();
	ASSERT_VALID(pFrame);

	if (pFrame->m_nFlags & WF_STAYACTIVE)
		bActive = TRUE;
	if (!pFrame->IsWindowEnabled())
		bActive = FALSE;
	if (bActive == m_bFrameActive)
		return;

	if (!bActive) {
		for (int i = 0; i < GetItemCount(); ++i) {
			m_arrItem[i]->ModifyState(0, MISTATE_INACTIVE);
		}
	}
	else {
		for (int i = 0; i < GetItemCount(); ++i) {
			m_arrItem[i]->ModifyState(MISTATE_INACTIVE, 0);
		}
	}

	m_bFrameActive = bActive;

	// InvalidateRect(NULL); is better, but too late
	// while clicking the application title bar (like IE5)
	// so we have to redraw now!
	CClientDC dc(this);
	DoPaint(&dc);
}

LRESULT CALLBACK CMenuBar::MenuInputFilter(int code, WPARAM wParam, LPARAM lParam)
{
	return (
		code == MSGF_MENU &&
		g_pMenuBar &&
		g_pMenuBar->OnMenuInput( *((MSG*)lParam) )
		) ? TRUE : CallNextHookEx(g_hMsgHook, code, wParam, lParam);
}

void CMenuBar::TrackPopup(int nIndex)
{
	ASSERT_VALID(this);

	m_nCurIndex = nIndex;
	m_bLoop = TRUE;
	while (m_bLoop == TRUE) {
		UpdateWindow();	// force to repaint when button hidden by other window
		UpdateBar(popup, m_nCurIndex);
	
		// install hook
		ASSERT(g_pMenuBar == NULL);
		g_pMenuBar = this;
		ASSERT(g_hMsgHook == NULL);

		m_bLoop = FALSE;
		g_hMsgHook = ::SetWindowsHookEx(WH_MSGFILTER,
			MenuInputFilter, NULL, AfxGetApp()->m_nThreadID);// m_bLoop may become TRUE

		// popup!!
		m_nTrackingState = popup;
		_nPrevIndexForCmd = m_nCurIndex;
		m_arrItem[m_nCurIndex]->TrackPopup(this, GetTopLevelParent());

		// uninstall hook
		::UnhookWindowsHookEx(g_hMsgHook);
		g_hMsgHook = NULL;
		g_pMenuBar = NULL;
	}

	UpdateBar();
}

BOOL CMenuBar::OnMenuInput(MSG& m)
{
	ASSERT_VALID(this);
	int nMsg = m.message;
	CPoint pt = m.lParam;
	ScreenToClient(&pt);

	switch (nMsg) {
	case WM_MOUSEMOVE:
		if (pt != m_ptMouse) {
			int nIndex = HitTestOnTrack(pt);
			if (IsValidIndex(nIndex) && nIndex != m_nCurIndex) {
				// defferent button clicked
				AfxGetMainWnd()->PostMessage(WM_CANCELMODE); // destroy popupped menu
				UpdateBar();							// clean up
				m_nCurIndex = nIndex;
				m_bLoop = TRUE;							// continue loop
			}
			m_ptMouse = pt;
		}
		break;

	case WM_LBUTTONDOWN:
		if (HitTestOnTrack(pt) != -1 && HitTestOnTrack(pt) == m_nCurIndex) {
			// same button clicked
			AfxGetMainWnd()->PostMessage(WM_CANCELMODE); // destroy popupped menu
			UpdateBar(button, m_nCurIndex);
			m_bLoop = FALSE;						// out of loop
			return TRUE;							// eat it!
		}
		break;

	case WM_KEYDOWN:	{
		TCHAR vKey = m.wParam;
		if (m_dwStyle & CBRS_ORIENT_VERT) {	// if vertical
			break; // do nothing
		}

		if ((vKey == VK_LEFT  && m_bProcessLeftArrow) ||
			(vKey == VK_RIGHT && m_bProcessRightArrow)) {
			// no submenu
			int nNewIndex = GetNextOrPrevButton(m_nCurIndex, vKey==VK_LEFT);
			AfxGetMainWnd()->PostMessage(WM_CANCELMODE); // destroy popupped menu
			UpdateBar();
			m_nCurIndex = nNewIndex;
			m_bLoop = TRUE;							// continue loop			
			return TRUE;							// eat it!
		}
						}
		break;

	case WM_SYSKEYDOWN:
//		LTRACE(_T("    m_bIgnore = TRUE\n"));
		m_bIgnoreAlt = TRUE;					// next SysKeyUp will be ignored
		break;
	}

	return FALSE;	// pass along...
}

BOOL CMenuBar::TranslateFrameMessage(MSG* pMsg)
{
	ASSERT_VALID(this);
	ASSERT(pMsg);

/*	if (_GetCmdSentWnd(NULL)->GetSafeHwnd() != GetTopLevelParent()->GetSafeHwnd()) {
		if (m_nTrackingState == popup) {
			LTRACE(_T("CMenuBar::TranslateMessage - SendMessage\n"));
			pMsg->hwnd = _GetCmdSentWnd(NULL)->GetSafeHwnd();
			_GetCmdSentWnd(NULL)->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
			return TRUE;
		}
	}
*/
	UINT nMsg = pMsg->message;
	if (WM_LBUTTONDOWN <= nMsg && nMsg <= WM_MOUSELAST) {
		if (pMsg->hwnd != m_hWnd && m_nTrackingState > 0) {
			// clicked outside
			UpdateBar();
		}
	}
	else if (nMsg == WM_SYSKEYDOWN || nMsg == WM_SYSKEYUP || nMsg == WM_KEYDOWN) {
		BOOL bAlt = HIWORD(pMsg->lParam) & KF_ALTDOWN;	// Alt key presed?
		TCHAR vkey = pMsg->wParam;						// + X key
		if (vkey == VK_MENU ||
			(vkey == VK_F10 && !((GetKeyState(VK_SHIFT) & 0x80000000) ||
			                   (GetKeyState(VK_CONTROL) & 0x80000000) || bAlt))) {
			// only alt key pressed
			if (nMsg == WM_SYSKEYUP) {
				switch (m_nTrackingState) {
				case none:
					if (m_bIgnoreAlt == TRUE) {
//						LTRACE(_T("    ignore ALT key up\n"));
						m_bIgnoreAlt = FALSE;
						break;
					}
				
					if (m_bMDIApp) {
						UpdateBar(button, GetNextOrPrevButton(0, FALSE));
					}
					else {
						UpdateBar(button, 0);
					}
					break;
				case button:
					UpdateBar();
					break;
				case buttonmouse:
					break;	// do nothing
				}
			}
			return TRUE;
		}
		else if ((nMsg == WM_SYSKEYDOWN || nMsg == WM_KEYDOWN)) {
			if (m_nTrackingState == button) {
				if (m_dwStyle & CBRS_ORIENT_HORZ) {	// if horizontal
					switch (vkey) {
					case VK_LEFT:
					case VK_RIGHT: {
						int nNewIndex  = GetNextOrPrevButton(m_nCurIndex, vkey == VK_LEFT);
						UpdateBar(button, nNewIndex);
						return TRUE;
								   }
					case VK_SPACE:
					case VK_UP:
					case VK_DOWN:
						TrackPopup(m_nCurIndex);
						return TRUE;

					case VK_ESCAPE:
						UpdateBar();
						return TRUE;
					}
				}
				else {								// if vertical
					switch (vkey) {
					case VK_UP:
					case VK_DOWN:{
						int nNewIndex = GetNextOrPrevButton(m_nCurIndex, vkey == VK_UP);
						UpdateBar(button, nNewIndex);
						return TRUE;
								   }
					case VK_SPACE:
					case VK_RIGHT:
					case VK_LEFT:
						TrackPopup(m_nCurIndex);
						return TRUE;

					case VK_ESCAPE:
						UpdateBar();
						return TRUE;
					}
				}
			}

			// Alt + X pressed
			if ((bAlt || m_nTrackingState == button) && _istalnum(vkey)) {
				int nIndex;
				if (MapAccessKey(vkey, nIndex) == TRUE) {
					UpdateBar();
					TrackPopup(nIndex);
					return TRUE;		// eat it!
				}
				else if (m_nTrackingState==button && !bAlt) {
//					MessageBeep(0);		// if you want
					return TRUE;
				}
			}

			if (m_nTrackingState > 0) {	// unknown key
				if (m_nTrackingState != buttonmouse) {	// if tracked with mouse, don't update bar
					UpdateBar();
				}
			}
		}
	}
	return FALSE;	// pass along...
}

BOOL CMenuBar::MapAccessKey(TCHAR cAccessKey, int& nIndex)
{
	for (int i = 0; i < GetItemCount(); ++i) {
		// fixing point
		TCHAR cKey = m_arrItem[i]->GetAccessKey();
		if (toupper(cKey)/*_totupper(cKey)*/ == cAccessKey) {// *****fixed by andi, thanx!*****
			nIndex = i;
			return TRUE;
		}
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CMenuBar layout
int CMenuBar::GetClipBoxLength(BOOL bHorz)
{
	CFrameWnd* pFrame = GetTopLevelFrame(); ASSERT_VALID(pFrame);
	CRect rcFrame; pFrame->GetWindowRect(rcFrame);

	CWnd* pParent = GetParent(); ASSERT_VALID(pParent);
	CRect rcParent; pParent->GetWindowRect(rcParent);

	const int cxFrameBorder = ::GetSystemMetrics(SM_CXFRAME);
	int cxNonClient = cxFrameBorder*2 + m_cxLeftBorder + m_cxRightBorder;
	if (m_dwExStyle & CBRS_GRIPPER)
		cxNonClient += CX_GRIPPER_ALL;

	if (m_dwStyle & CBRS_SIZE_DYNAMIC) {
		if (bHorz) {
			return rcFrame.Width() - cxNonClient;
		}
		else {
			int nResult = rcParent.Height();
			// I don't know the reason of the following code...
			nResult -= m_cxRightBorder + m_cxLeftBorder + cyBorder2*2;	
			if (m_dwExStyle & CBRS_GRIPPER)
				nResult -= CY_GRIPPER_ALL;

			return nResult;
		}
	}
	else {
		CRect rect; GetClientRect(rect);
		if (bHorz) {
			return rect.Width();
		}
		else {
			return rect.Height();
		}
	}
}

CSize CMenuBar::CalcLayout(DWORD dwMode, int nLength)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));
	if (dwMode & LM_HORZDOCK)
		ASSERT(dwMode & LM_HORZ);

	// make SC_CLOSE button disable
	if (m_dwStyle & CBRS_FLOATING) {
		CFrameWnd* pMiniFrame = GetParentFrame(); ASSERT_KINDOF(CMiniFrameWnd, pMiniFrame);
//		Don't do this, cause right click menu turns unavairable
//		pMiniFrame->ModifyStyle(WS_SYSMENU, 0);
		CMenu* pSysMenu = pMiniFrame->GetSystemMenu(FALSE);	ASSERT_VALID(pSysMenu);
		pSysMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
	}

	int nCount = GetItemCount();
	CSize sizeResult(0, 0);

	if (nCount > 0)
	{
		if (!(m_dwStyle & CBRS_SIZE_FIXED))
		{
			BOOL bDynamic = m_dwStyle & CBRS_SIZE_DYNAMIC;

			if (bDynamic && (dwMode & LM_MRUWIDTH))
			{
				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---LM_MRUWIDTH\n"));
				SizeMenuBar(m_nMRUWidth);
				CalcItemLayout(nCount);// added

				sizeResult = CalcSize(nCount);
			}
			else if (bDynamic && (dwMode & LM_HORZDOCK))
			{
				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---LM_HORZDOCK\n"));
				if (IsFloating() || (m_dwStyle & CBRS_ORIENT_VERT)) {
					// I can't synchronize horz size on dragging with size on dock bar
					// as VC++ developer can't.
					SizeMenuBar(32767);
				}
				else {
					// Menu Button wrapped by frame width
					SizeMenuBar(GetClipBoxLength(TRUE));
				}

				CalcItemLayout(nCount);// added
				
				sizeResult = CalcSize(nCount);
				if (!IsFloating() && !(m_dwStyle & CBRS_ORIENT_VERT)) {
					if (m_pDockContext->m_pDC) {// while dragging (m_pDockContext->m_bDragging is helpless)
						sizeResult.cx = GetClipBoxLength(TRUE);
					}
				}
			}
			else if (bDynamic && (dwMode & LM_VERTDOCK))
			{
				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---LM_VERTDOCK\n"));
				//SizeMenuBar(0);
				CalcItemLayout(nCount, TRUE);// added

				sizeResult = CalcVertDockSize(nCount);
				if (!IsFloating() && !(m_dwStyle & CBRS_ORIENT_HORZ)) {
					if (m_pDockContext->m_pDC) {// while dragging
						sizeResult.cy = GetClipBoxLength(FALSE);//GetrcParent.Height() - m_cxRightBorder - m_cxLeftBorder;
					}
				}
			}
			else if (bDynamic && (nLength != -1))
			{
				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---nLength != -1\n"));
				CRect rect; rect.SetRectEmpty();
				_CalcInsideRect(rect, (dwMode & LM_HORZ));
				BOOL bVert = (dwMode & LM_LENGTHY);
				int nLen = nLength + (bVert ? rect.Height() : rect.Width());

				SizeMenuBar(nLen, bVert);
				CalcItemLayout(nCount, bVert);// added

				sizeResult = CalcSize(nCount);
			}
			else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
			{
				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---CBRS_FLOATING\n"));
				SizeMenuBar(m_nMRUWidth);
				CalcItemLayout(nCount);// added

				sizeResult = CalcSize(nCount);
			}
			else
			{
				if (!bDynamic) {
					InvalidateRect(NULL);
					goto Junk;
				}

				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---other\n"));
				BOOL bVert = !(dwMode & LM_HORZ);
				SizeMenuBar(GetClipBoxLength(TRUE));
				CalcItemLayout(nCount, bVert);// added

				if (bVert) {
					InvalidateRect(NULL);// draw forcefully for captions
					sizeResult = CalcVertDockSize(nCount);
					// DockBar not replaced yet, so I can't get precise size
					sizeResult.cy = 10000;
				}
				else {
					sizeResult = CalcSize(nCount);
					sizeResult.cx = GetClipBoxLength(TRUE);
				}
			}
		}
		else {// CBRS_SIZE_FIXED
			LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_FIXED)\n"));
Junk:
			BOOL bVert = !(dwMode & LM_HORZ);
			SizeMenuBar(32767);
			CalcItemLayout(nCount, bVert);// added

			if (bVert) {
				sizeResult = CalcVertDockSize(nCount);
			}
			else {
				sizeResult = CalcSize(nCount);
			}
		}

		if (dwMode & LM_COMMIT)
		{
			LTRACE(_T("CMenuBar::CalcLayout---LM_COMMIT\n"));
			int nControlCount = 0;
			BOOL bIsDelayed = m_bDelayedButtonLayout;
			m_bDelayedButtonLayout = FALSE;

			if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
				m_nMRUWidth = sizeResult.cx;

			//CalcItemLayout(nCount, dwMode);

			m_bDelayedButtonLayout = bIsDelayed;
		}
	}

	//BLOCK: Adjust Margins
	{
		CRect rect; rect.SetRectEmpty();
		_CalcInsideRect(rect, (dwMode & LM_HORZ));
		sizeResult.cy -= rect.Height();
		sizeResult.cx -= rect.Width();

		CSize size = CControlBar::CalcFixedLayout((dwMode & LM_STRETCH), (dwMode & LM_HORZ));
		sizeResult.cx = max(sizeResult.cx, size.cx);
		sizeResult.cy = max(sizeResult.cy, size.cy);
	}
	return sizeResult;
}

CSize CMenuBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	LTRACE(_T("CMenuBar::CalcFixedLayout\n"));
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));

	DWORD dwMode = bStretch ? LM_STRETCH : 0;
	dwMode |= bHorz ? LM_HORZ : 0;

	return CalcLayout(dwMode);
}

CSize CMenuBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	LTRACE(_T("CMenuBar::CalcDynamicLayout\n"));
	if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
		((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
	{
		LTRACE(_T("    FixedLayout\n"));
		return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZDOCK);
	}
	return CalcLayout(dwMode, nLength);
}

// set m_bWrapped by nWidth
int CMenuBar::WrapMenuBar(int nCount, int nWidth)
{
//	LTRACE(_T("CMenuBar::WrapMenuBar\n"));
	int nResult = 0;
	int x = 0;

	for (int i = 0; i < nCount; ++i) {
		CMenuItem* pItem = m_arrItem[i];
		if (i+1 == nCount)
			return ++nResult;
		
		if (x + pItem->GetHorizontalSize().cx> nWidth) {// itself is over
			if (pItem->GetStyle() & MISTYLE_WRAPPABLE) {
				pItem->ModifyState(0, MISTATE_WRAP);
				++nResult;
				x = 0;
			}
		}
		else if (x + pItem->GetHorizontalSize().cx + 
				 m_arrItem[i+1]->GetHorizontalSize().cx> nWidth) {
			if (pItem->GetStyle() & MISTYLE_WRAPPABLE) {
				pItem->ModifyState(0, MISTATE_WRAP);
				++nResult;
				x = 0;
			}
		}
		else {
			pItem->ModifyState(MISTATE_WRAP, 0);
			x += pItem->GetHorizontalSize().cx;
		}
	}

	return nResult + 1;
}

// calc only size, by using m_bWrapped
CSize CMenuBar::CalcSize(int nCount)
{
	ASSERT(nCount > 0);
	CPoint cur(0,0);
	CSize sizeResult(0,0);
	int nWrap = 0;
	for (int i = 0; i < nCount; ++i) {
		CMenuItem* pItem = m_arrItem[i];
		sizeResult.cx = max(cur.x + pItem->GetHorizontalSize().cx, sizeResult.cx);
		sizeResult.cy = max(cur.y + pItem->GetHorizontalSize().cy, sizeResult.cy);

		cur.x += pItem->GetHorizontalSize().cx;
		
		if (pItem->GetState() & MISTATE_WRAP) {
			//LTRACE(_T("    nIndex:%d is wrapped\n"), i);
			cur.x = 0;// reset x pos
			cur.y += pItem->GetHorizontalSize().cy;
			++nWrap;
		}
	}

	return sizeResult;
}

void CMenuBar::Layout()
{
	ASSERT(m_bDelayedButtonLayout);

	m_bDelayedButtonLayout = FALSE;

	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
		((CMenuBar*)this)->CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH | LM_COMMIT);
	else if (bHorz)
		((CMenuBar*)this)->CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK | LM_COMMIT);
	else
		((CMenuBar*)this)->CalcDynamicLayout(0, LM_VERTDOCK | LM_COMMIT);
}

void CMenuBar::SizeMenuBar(int nLength, BOOL bVert)
{
	//LTRACE("CMenuBar::SizeMenuBar\n");
	int nCount = GetItemCount(); ASSERT(nCount > 0);

	if (!bVert) {				// nLength is horizontal length

		if (IsFloating()) {		// half size wrapping

			CSize sizeMax, sizeMin, sizeMid;

			// Wrap MenuBar vertically
			WrapMenuBar(nCount, 0);
			sizeMin = CalcSize(nCount);

			// Wrap MenuBar horizontally
			WrapMenuBar(nCount, 32767);
			sizeMax = CalcSize(nCount);

			// we can never understand this algorithm :), see CToolBar implementation
			while (sizeMin.cx < sizeMax.cx) {
//				LTRACE("looping sizeMin.cx:%d < sizeMax.cx:%d\n", sizeMin.cx, sizeMax.cx);
				sizeMid.cx = (sizeMin.cx + sizeMax.cx) / 2;
				WrapMenuBar(nCount, sizeMid.cx);
				sizeMid = CalcSize(nCount);
				if (sizeMid.cx == sizeMax.cx) {	// if you forget, it loops forever!
					return;
				}
//				LTRACE("    sizeMid : %d %d\n", sizeMid.cx, sizeMid.cy);

				if (nLength >= sizeMax.cx) {
//					LTRACE("    nLength:%d >= sizeMax.cx:%d\n", nLength, sizeMax.cx);
					if (sizeMin == sizeMid) {
						WrapMenuBar(nCount, sizeMax.cx);
//						LTRACE("out SizeMenuBar\n");
						return;
					}
					sizeMin = sizeMid;
				}
				else if (nLength < sizeMax.cx) {
//					LTRACE("    nLength:%d < sizeMax.cx:%d\n", nLength, sizeMax.cx);
					sizeMax = sizeMid;
				}
				else {
//					LTRACE("out SizeMenuBar\n");
					return;
				}
			}
		}
		else {								// each one wrapping
			//LTRACE("    just each one wrapping\n");
			WrapMenuBar(nCount, nLength);
		}
	}
	else {						// nLength is vertical length
		CSize sizeMax, sizeMin, sizeMid;

		// Wrap MenuBar vertically
		WrapMenuBar(nCount, 0);
		sizeMin = CalcSize(nCount);

		// Wrap MenuBar horizontally
		WrapMenuBar(nCount, 32767);
		sizeMax = CalcSize(nCount);

		while (sizeMin.cx < sizeMax.cx) {
			sizeMid.cx = (sizeMin.cx + sizeMax.cx) / 2;
			WrapMenuBar(nCount, sizeMid.cx);
			sizeMid = CalcSize(nCount);
			if (sizeMid.cx == sizeMax.cx) {
				return;
			}
			if (nLength < sizeMid.cy) {
				if (sizeMin == sizeMid) {
					WrapMenuBar(nCount, sizeMax.cx);
					//LTRACE("out SizeMenuBar\n");
					return;
				}
				sizeMin = sizeMid;
			}
			else if (nLength > sizeMid.cy)
				sizeMax = sizeMid;
			else {
				//LTRACE("out SizeMenuBar\n");
				return;
			}
		}
	}

	//LTRACE("out SizeMenuBar\n");
}

CSize CMenuBar::CalcVertDockSize(int nCount)
{
	ASSERT(nCount > 0);
	CSize sizeResult(0, 0);

	for (int i = 0; i < nCount; ++i) {
		CMenuItem* pItem = m_arrItem[i];
		sizeResult.cy += pItem->GetRect().Height();
	}

	sizeResult.cx = _cyMenuOnBar;
	return sizeResult;
}

void CMenuBar::CalcItemLayout(int nCount, BOOL bVert)
{
	ASSERT(nCount > 0);
	int x = 0; int y = 0;

	if (!bVert) {
		for (int i = 0; i < nCount; ++i) {
			CMenuItem* pItem = m_arrItem[i];
			CPoint ptItem(x, y);
			pItem->Layout(ptItem, TRUE);// layout by itself!
			if (pItem->GetState() & MISTATE_WRAP) {
				x = 0;// reset x to 0
				y += pItem->GetRect().Height();
			}
			else
				x += pItem->GetRect().Width();
		}		
	}
	else {
		for (int i = 0; i < nCount; ++i) {
			CMenuItem* pItem = m_arrItem[i];
			CPoint	ptItem(0, y);
			pItem->Layout(ptItem, FALSE);	// layout by itself
			y += pItem->GetRect().Height();
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Added by Koay Kah Hoe. Thanx!
void CMenuBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
//	LTRACE(_T("CMenuBar::OnUpdateCmdUI\n"));
	/*
	// if mouse out of frame window, OnUpdateCmdUI never called...
	if (m_nTrackingState == buttonmouse) {
		CPoint pt; ::GetCursorPos(&pt);
		CRect rect;
		GetWindowRect(&rect);

		if (!rect.PtInRect(pt))
			UpdateBar();
	}
	*/

	// but thanks to Koay Kah Hoe,
	// I've found it's nice place for checking child window status.
	if (m_bMDIApp)
		CheckActiveChildWndMaximized();
}

//////////////////////////////////////////////////////////////////////
// CMenuBar decoration
void CMenuBar::EraseNonClientEx()
{
	// get window DC that is clipped to the non-client area
	CWindowDC dc(this);
	CRect rectClient;
	GetClientRect(rectClient);
	CRect rectWindow;
	GetWindowRect(rectWindow);
	ScreenToClient(rectWindow);
	rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
	dc.ExcludeClipRect(rectClient);

	// draw borders in non-client area
	rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);

	if (m_dwExStyle & CBRS_RAISEDBORDER)
		DrawRaisedBorders(&dc, rectWindow);
	else
		DrawBorders(&dc, rectWindow);

	// erase parts not drawn
	dc.IntersectClipRect(rectWindow);
	SendMessage(WM_ERASEBKGND, (WPARAM)dc.m_hDC);

	// draw gripper in non-client area
	_DrawGripper(&dc, rectWindow);
}

#define CX_BORDER   1
#define CY_BORDER   1
void CMenuBar::DrawRaisedBorders(CDC* pDC, CRect& rect)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	DWORD dwStyle = m_dwStyle;
	if (!(dwStyle & CBRS_BORDER_ANY))
		return;

	// prepare for dark lines
	ASSERT(rect.top == 0 && rect.left == 0);
	CRect rect1, rect2;
	rect1 = rect;
	rect2 = rect;
	COLORREF clrBtnShadow = ::GetSysColor(COLOR_BTNSHADOW);//afxData.bWin4 ? afxData.clrBtnShadow : afxData.clrWindowFrame;
	COLORREF clrBtnFace = ::GetSysColor(COLOR_BTNFACE);
	COLORREF clrBtnHilight = ::GetSysColor(COLOR_BTNHILIGHT);

	// draw dark line one pixel back/up
	if (dwStyle & CBRS_BORDER_3D)
	{
		rect1.right -= CX_BORDER;
		rect1.bottom -= CY_BORDER;
	}
	if (dwStyle & CBRS_BORDER_TOP)
		rect2.top += cyBorder2;
	if (dwStyle & CBRS_BORDER_BOTTOM)
		rect2.bottom -= cyBorder2;

	// draw left and top
	if (dwStyle & CBRS_BORDER_LEFT)
		pDC->FillSolidRect(0, rect2.top, CX_BORDER, rect2.Height(), clrBtnFace);
	if (dwStyle & CBRS_BORDER_TOP)
		pDC->FillSolidRect(0, 0, rect.right, CY_BORDER, clrBtnFace);

	// draw right and bottom
	if (dwStyle & CBRS_BORDER_RIGHT)
		pDC->FillSolidRect(rect1.right, rect2.top, -CX_BORDER, rect2.Height(), clrBtnShadow);
	if (dwStyle & CBRS_BORDER_BOTTOM)
		pDC->FillSolidRect(0, rect1.bottom, rect.right, -CY_BORDER, clrBtnShadow);

	if (dwStyle & CBRS_BORDER_3D)
	{
		// draw left and top
		if (dwStyle & CBRS_BORDER_LEFT)
			pDC->FillSolidRect(1, rect2.top, CX_BORDER, rect2.Height(), clrBtnHilight);
		if (dwStyle & CBRS_BORDER_TOP)
			pDC->FillSolidRect(0, 1, rect.right, CY_BORDER, clrBtnHilight);

		// draw right and bottom
		if (dwStyle & CBRS_BORDER_RIGHT)
			pDC->FillSolidRect(rect.right, rect2.top, -CX_BORDER, rect2.Height(), clrBtnFace);
		if (dwStyle & CBRS_BORDER_BOTTOM)
			pDC->FillSolidRect(0, rect.bottom, rect.right, -CY_BORDER, clrBtnFace);
	}

	if (dwStyle & CBRS_BORDER_LEFT)
		rect.left += cxBorder2;
	if (dwStyle & CBRS_BORDER_TOP)
		rect.top += cyBorder2;
	if (dwStyle & CBRS_BORDER_RIGHT)
		rect.right -= cxBorder2;
	if (dwStyle & CBRS_BORDER_BOTTOM)
		rect.bottom -= cyBorder2;		
}

int CMenuBar::GetNextOrPrevButton(int nIndex, BOOL bPrev)
{
	int nCount = GetItemCount();
	if (bPrev) {				// <-
		--nIndex;
		if (nIndex < 0)
			nIndex = nCount - 1;
	}
	else {						// ->
		++nIndex;
		if (nIndex >= nCount)
			nIndex = 0;
	}

	if (!(m_arrItem[nIndex]->GetStyle() & MISTYLE_TRACKABLE) ||
		(m_arrItem[nIndex]->GetState() & MISTATE_HIDDEN)) {
		return GetNextOrPrevButton(nIndex, bPrev);
	}

	return nIndex;
}

/////////////////////////////////////////////////////////////////////////////
// CMenuBar insists own bar line 
void CMenuBar::EnableDockingEx(DWORD dwDockStyle)
{
	// pasted from CFrameWnd implementation
	static const DWORD dwDockBarMap[4][2] =
	{
		{ AFX_IDW_DOCKBAR_TOP,      CBRS_TOP    },
		{ AFX_IDW_DOCKBAR_BOTTOM,   CBRS_BOTTOM },
		{ AFX_IDW_DOCKBAR_LEFT,     CBRS_LEFT   },
		{ AFX_IDW_DOCKBAR_RIGHT,    CBRS_RIGHT  },
	};

	EnableDocking(dwDockStyle);

	// must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
	ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

	CFrameWnd* pFrame = GetParentFrame(); ASSERT_VALID(pFrame);
	//pFrame->m_pFloatingFrameClass = RUNTIME_CLASS(CMiniDockFrameWnd);
	for (int i = 0; i < 4; i++)
	{
		if (dwDockBarMap[i][1] & dwDockStyle & CBRS_ALIGN_ANY)
		{
			CDockBar* pDock = (CDockBar*)pFrame->GetControlBar(dwDockBarMap[i][0]);
			if (pDock == NULL)
			{
				pDock = new CMenuDockBar;// which wait for CMenuBar
				if (!pDock->Create(pFrame,
					WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CHILD|WS_VISIBLE |
					dwDockBarMap[i][1], dwDockBarMap[i][0]))
				{
					AfxThrowResourceException();
				}
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// CMenuBar OLE menu support
//		MFC does'nt do command routing for other process server.
//		::TrackPopupMenuEx won't accept HWND of other process and
//		we have to determine a message target(ole server window or not)
//		as ::OleCreateMenuDescriptor do.
//		This is a hard coding. 
//		First menu(ordinarily File menu) and WindowMenu regarded as container's own menu.
//		Some components can't update toolbar button and statusbar pane.
HWND CMenuBar::OleMenuDescriptor(BOOL& bSend, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	CWnd* pOleWnd = GetCmdSentOleWnd();
	if (pOleWnd == NULL)
		return NULL;
	HWND hWndSentCmd = NULL;

	HMENU hMenu = NULL;
	if (nMsg == WM_INITMENUPOPUP || nMsg == WM_INITMENU)
		hMenu = (HMENU)wParam;
	else if (nMsg == WM_MENUSELECT)
		hMenu = (HMENU)lParam;

	switch (nMsg) {
	case WM_INITMENUPOPUP:
	case WM_INITMENU:
	case WM_MENUSELECT:
		bSend = TRUE;
		if (m_nTrackingState == popup) {
			LTRACE2(_T("    now popup\n"));
			if (m_bMDIApp) {
				LTRACE2(_T("    this is MDI\n"));
				if (m_nCurIndex == 0 || m_nCurIndex == 1 || hMenu == m_hWindowMenu) {
					LTRACE2(_T("    it's container menu, send to frame\n"));
					return NULL;
				}
			}
			else {
				LTRACE2(_T("    it's container menu, send to frame\n"));
				if (m_nCurIndex == 0) {
					return NULL;
				}
			}
			LTRACE2(_T("    it's server menu, send to server\n"));
			return pOleWnd->GetSafeHwnd();
		}
		break;

	case WM_COMMAND:
		bSend = FALSE;
		if (m_bMDIApp) {
			LTRACE2(_T("    this is MDI\n"));
			if (_nPrevIndexForCmd == 0 || _nPrevIndexForCmd == 1 || _bWindowMenuSendCmd) {
				LTRACE2(_T("    it's container menu, send to frame\n"));
				return NULL;
			}
		}
		else {
			if (_nPrevIndexForCmd == 0) {
				LTRACE2(_T("    it's container menu, send to frame\n"));
				return NULL;
			}
		}
		LTRACE2(_T("    it's server menu, send to server\n"));
		return pOleWnd->GetSafeHwnd();
	}

	return NULL;// send to frame
}

CWnd* CMenuBar::GetCmdSentOleWnd()
{
	// *****fixed by VORGA, thanks!*****
	CWnd* pWnd = AfxGetMainWnd();
	if (pWnd == NULL || !pWnd->IsFrameWnd())
		return NULL;
	
	CFrameWnd* pFrame = NULL;
	if (m_bMDIApp) {
		CMDIFrameWnd *pMDIFrame = STATIC_DOWNCAST(CMDIFrameWnd, pWnd);
		if (pMDIFrame == NULL)
			return NULL;
		pFrame = pMDIFrame->GetActiveFrame();
	}
	else {
		pFrame = STATIC_DOWNCAST(CFrameWnd, pWnd);
	}

	if (pFrame == NULL)
		return NULL;

	CDocument* pDoc = pFrame->GetActiveDocument();
	if (pDoc != NULL && pDoc->IsKindOf(RUNTIME_CLASS(COleDocument))) {
		COleDocument* pOleDoc = STATIC_DOWNCAST(COleDocument, pDoc);
		ASSERT_VALID(pOleDoc);
		COleClientItem* pClientItem = pOleDoc->GetInPlaceActiveItem(pFrame);
		CWnd* pWnd = (pClientItem == NULL) ? NULL : pClientItem->GetInPlaceWindow();
		if (pWnd != NULL) {
//			TCHAR str[256];
//			::GetClassName(pWnd->GetSafeHwnd(), str, 256);
//			LTRACE2(_T("    server wnd : %s\n"), str);
			return pWnd;
		}
	}

	return NULL;
}
/////////////////////////////////////////////////////////////////////////////
// CMDIClientHook 
CMDIClientHook::CMDIClientHook()
{
	m_pMenuBar = NULL;
}

BOOL CMDIClientHook::Install(CMenuBar* pMenuBar, HWND hWndToHook)
{
	ASSERT_VALID(pMenuBar);
	ASSERT(m_pMenuBar == NULL);
	m_pMenuBar = pMenuBar;
	return HookWindow(hWndToHook);
}

CMDIClientHook::~CMDIClientHook()
{
}

LRESULT CMDIClientHook::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	ASSERT_VALID(m_pMenuBar);

	switch (nMsg) {
	case WM_MDISETMENU:			// only sent to MDI client window
		// Setting new frame/window menu: bypass MDI. wParam is new menu.
		if (wParam) {
			//LTRACE(_T("CMenuBar::WM_MDISETMENU 0x%04x\n"), wParam);
			m_pMenuBar->OnSetMenu((HMENU)wParam, (HMENU)lParam);
		}
		return 0;

	case WM_MDIREFRESHMENU:		// only sent to MDI client window
		// Normally, would call DrawMenuBar, but I have the menu, so eat it.
		//LTRACE(_T("CMenuBar::WM_MDIREFRESHMENU\n"));
		return 0;

//	case WM_PAINT:
		//LTRACE(_T("CMenuBar:WM_PAINT\n"));
		// If you use no Doc-View project, when child window maximized,
		// WM_PAINT never sent! so this trick never do.
		// So this code moved to OnUpdateCmdUI.

		// After changing the MDI maximized state, the client window gets a
		// paint message. This is the most convenient place to find out; there
		// is no WM_MDIMAXIMIZED message.
//		if (/*m_pWndHooked->*/m_hWnd == m_pMenuBar->m_hWndMDIClient)
//			m_pMenuBar->CheckActiveChildWndMaximized();
//		break;
	}

	return CSubclassWnd::WindowProc(nMsg, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrameHook 
CMainFrameHook::CMainFrameHook()
{
	m_pMenuBar = NULL;
}

BOOL CMainFrameHook::Install(CMenuBar* pMenuBar, HWND hWndToHook)
{
	ASSERT_VALID(pMenuBar);
	ASSERT(m_pMenuBar == NULL);
	m_pMenuBar = pMenuBar;
	return HookWindow(hWndToHook);
}

CMainFrameHook::~CMainFrameHook()
{
}

LRESULT CMainFrameHook::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	ASSERT_VALID(m_pMenuBar);
	// be care for other windows(MainFrame) hooking
	// possible called when already this wnd destroyed (WM_NCACTIVATE is)
	if (!::IsWindow(m_pMenuBar->m_hWnd)) {
		return CSubclassWnd::WindowProc(nMsg, wParam, lParam);
	}

	BOOL bSend = FALSE;
	if (HWND hWndServer = m_pMenuBar->OleMenuDescriptor(bSend, nMsg, wParam, lParam)) {
		// OLE wnd will handle message
		if (bSend)
			return ::SendMessage(hWndServer, nMsg, wParam, lParam);
		else
			return ::PostMessage(hWndServer, nMsg, wParam, lParam);
	}

	switch (nMsg) {
	case WM_MENUSELECT:
		m_pMenuBar->OnMenuSelect((HMENU)lParam, (UINT)LOWORD(wParam));
		break;

	case WM_INITMENUPOPUP:
		if (!HIWORD(lParam) && (HMENU)wParam == m_pMenuBar->m_hWindowMenu)
			m_pMenuBar->OnInitMenuPopup(CMenu::FromHandle((HMENU)wParam),
				LOWORD(lParam), (BOOL)HIWORD(lParam));
		break;

	case WM_NCACTIVATE:
		m_pMenuBar->OnFrameNcActivate((BOOL)wParam);
		break;
	
	case WM_SYSCOLORCHANGE:
	case WM_SETTINGCHANGE:
		LTRACE(_T("CMenuBar::WM_SETTINGCHANGE\n"));
		// It's enough to reinitialize common resources once.
		m_pMenuBar->OnSettingChange(wParam, lParam);
		break;
	}

	if (nMsg == CMenuBar::WM_GETMENU)
		return (LRESULT)m_pMenuBar->m_hMenu;

	return CSubclassWnd::WindowProc(nMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////
// CMenuItem interface
CMenuItem::CMenuItem()
{
	m_fsStyle = 0;
	m_fsState = 0;
	m_rcItem.SetRectEmpty();
	m_sizeHorz = CSize(0, 0);
	m_cAccessKey = 0;
}

void CMenuItem::ModifyState(BYTE fsRemove, BYTE fsAdd)
{
	m_fsState = (m_fsState & ~fsRemove) | fsAdd;
}

CSize CMenuItem::GetHorizontalSize() const
{
	if (m_fsState & MISTATE_HIDDEN)
		return CSize(0, 0);
	else
		return m_sizeHorz;
}

//////////////////////////////////////////////////////////////////////
// CMenuButton class	
CMenuButton::CMenuButton(HMENU hMenu, int nIndex)
{
	ASSERT(::IsMenu(hMenu));
	ASSERT(nIndex >= 0);

	m_fsStyle |= (MISTYLE_TRACKABLE | MISTYLE_WRAPPABLE);
	InitButtonStringAndSubMenuHandle(hMenu, nIndex);
	InitHorizontalButtonSize();
	InitAccessKeyAndVerticalLinePoint();
}

void CMenuButton::InitButtonStringAndSubMenuHandle(HMENU hMenu, int nIndex)
{
	// get menu button Text
	TCHAR szText[256];
	MENUITEMINFO info; ::memset(&info, 0, sizeof(MENUITEMINFO));
	info.cbSize		= sizeof(MENUITEMINFO);
	info.fMask		= MIIM_ID | MIIM_TYPE;
	info.dwTypeData = szText;
	info.cch		= sizeof(szText);
	::GetMenuItemInfo(hMenu, nIndex, TRUE, &info);
	m_strBtn = CString(szText);

	m_hSubMenu = ::GetSubMenu(hMenu, nIndex);
	if (!m_hSubMenu) {
		m_nID = ::GetMenuItemID(hMenu, nIndex);
		ASSERT(m_nID != -1);
	}
	else {
		m_nID = -1;
	}
}

void CMenuButton::InitHorizontalButtonSize()
{
	// get menu button Text size
	ASSERT(m_strBtn.IsEmpty() == FALSE);
	m_sizeHorz.cx = _CalcTextWidth(m_strBtn) + CXTEXTMARGIN*2;
	m_sizeHorz.cy = _cyHorzFont + _cyTextMargin*2;
}

void CMenuButton::InitAccessKeyAndVerticalLinePoint()
{
	int nIndex = m_strBtn.Find('&');
	if (nIndex + 1 == m_strBtn.GetLength()) {
		TRACE(_T("warning : & is bad position, access key is invalid.\n"));
		m_cAccessKey = 0;
		m_ptLineFrom = m_ptLineTo = CPoint(0, 0);
		return;
	}
	
	m_cAccessKey = m_strBtn[nIndex + 1];// -1 + 1 = 0; it's ok

	if (nIndex == -1) {
		m_ptLineFrom = m_ptLineTo = CPoint(0, 0);
	}
	else if (nIndex == 0) {
		m_ptLineFrom = CPoint(_cyTextMargin, CXTEXTMARGIN);
		m_ptLineTo	 = CPoint(_cyTextMargin, CXTEXTMARGIN + _CalcTextWidth(m_strBtn.Left(nIndex+2)));
	}
	else {
		m_ptLineFrom = CPoint(_cyTextMargin, CXTEXTMARGIN + _CalcTextWidth(m_strBtn.Left(nIndex)));
		m_ptLineTo = CPoint(_cyTextMargin, CXTEXTMARGIN + _CalcTextWidth(m_strBtn.Left(nIndex+2)));
	}
}

void CMenuButton::Layout(CPoint point, BOOL bHorz)
{
	if (bHorz)
		m_fsState |= MISTATE_HORZ;
	else
		m_fsState &= ~MISTATE_HORZ;

	if (m_fsState & MISTATE_HIDDEN) {
		m_rcItem.SetRectEmpty();
		return;
	}
	
	if (bHorz) {
		m_rcItem = CRect(point, m_sizeHorz);
	}
	else {
		m_rcItem = CRect(point, CSize(m_sizeHorz.cy, m_sizeHorz.cx));
	}
}

void CMenuButton::Update(CDC* pDC)
{
	if (m_fsState & MISTATE_HIDDEN)
		return;
	
	// clean background
	COLORREF clr = ::GetSysColor(COLOR_BTNFACE);
	pDC->FillSolidRect(m_rcItem, clr);

	if (m_fsState & MISTATE_HOT){
		DrawHot(pDC);
	}
	else if (m_fsState & MISTATE_PRESSED){
		DrawPressed(pDC);
	}
	else {
		DrawNone(pDC);
	}
}

void CMenuButton::TrackPopup(CWnd* pBar, CWnd* pWndSentCmd)
{
	LTRACE(_T("CMenuButton::TrackPopup\n"));
	ASSERT_VALID(pBar);
	ASSERT(!(m_fsState & MISTATE_HIDDEN));
	CMenuBar* pMenuBar = STATIC_DOWNCAST(CMenuBar, pBar);
	ASSERT_VALID(pMenuBar);

	// "! menu" (no sub menu)
	if (!m_hSubMenu) {
		ASSERT(m_nID != -1);
		pWndSentCmd->SendMessage(WM_COMMAND, (WPARAM)m_nID, (LPARAM)pBar->GetSafeHwnd());		
		return;
	}

	CRect rcItem(m_rcItem);	pMenuBar->ClientToScreen(rcItem);
	UINT fuFlags; TPMPARAMS tpm;
	CPoint pt = _ComputeMenuTrackPoint(rcItem, pMenuBar->GetBarStyle(), fuFlags, tpm);

	if (m_hSubMenu == pMenuBar->m_hWindowMenu)
		_bWindowMenuSendCmd = TRUE;
	else
		_bWindowMenuSendCmd = FALSE;

	::TrackPopupMenuEx(m_hSubMenu, fuFlags,
		pt.x, pt.y, pWndSentCmd->GetSafeHwnd(), &tpm);
}

void CMenuButton::DrawHorzText(CDC* pDC, CPoint ptOffset)
{
	COLORREF clr = (m_fsState & MISTATE_INACTIVE) ? 
		::GetSysColor(COLOR_GRAYTEXT) : ::GetSysColor(COLOR_MENUTEXT);
	pDC->SetTextColor(clr);

	CRect rcBtn = m_rcItem;
	pDC->SetBkMode(TRANSPARENT);
	CFont* pOldFont = pDC->SelectObject(&_fontHorzMenu);
	// I know precise text size, but better to leave this job to Windows
	// *****fixed by andi, thanks!*****
	pDC->DrawText(m_strBtn, rcBtn + ptOffset,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	
	pDC->SelectObject(pOldFont);
}

void CMenuButton::DrawVertText(CDC* pDC, CPoint ptOffset)
{
	COLORREF clr = (m_fsState & MISTATE_INACTIVE) ? 
		::GetSysColor(COLOR_GRAYTEXT) : ::GetSysColor(COLOR_MENUTEXT);
	pDC->SetTextColor(clr);

	CRect rcBtn = m_rcItem;
	int nLength = m_strBtn.GetLength();
	int nIndex = m_strBtn.Find('&');
	CString strBtn = m_strBtn.Left(nIndex) + m_strBtn.Right(nLength - (nIndex+1));

	// fixed for WinNT. *****fixed by Simon, thanks!*****
	int iGraphicsMode = ::GetGraphicsMode(pDC->m_hDC);
	::SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);

	pDC->SetBkMode(TRANSPARENT);
	CFont* pOldFont = pDC->SelectObject(&_fontVertMenu);
	// I know precise text size
	CRect rcString = CRect(
		CPoint(rcBtn.right - _cyTextMargin, rcBtn.top + CXTEXTMARGIN), m_sizeHorz);
	pDC->DrawText(strBtn, rcString + ptOffset,
		DT_SINGLELINE | DT_NOCLIP | DT_NOPREFIX);// don't forget DT_NOCLIP
	
	pDC->SelectObject(pOldFont);

	// CDC::DrawText is poor, so we have to draw vertical line by ourselves
	CPen pen(PS_SOLID, 0, clr);
	CPen* pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(rcBtn.TopLeft() + m_ptLineFrom + ptOffset);
	pDC->LineTo(rcBtn.TopLeft() + m_ptLineTo + ptOffset);

	pDC->SelectObject(pOldPen);
	::SetGraphicsMode( pDC->m_hDC, iGraphicsMode );
}

void CMenuButton::DrawHot(CDC* pDC)
{
	if (m_fsState & MISTATE_HORZ) {
		// draw pressed button
		pDC->DrawEdge(m_rcItem, BDR_RAISEDINNER, BF_RECT);
		DrawHorzText(pDC);
	}
	else {
		pDC->DrawEdge(m_rcItem, BDR_RAISEDINNER, BF_RECT);
		DrawVertText(pDC);
	}
}

void CMenuButton::DrawPressed(CDC* pDC)
{
	if (m_fsState & MISTATE_HORZ) {
		pDC->DrawEdge(m_rcItem, BDR_SUNKENOUTER, BF_RECT);// draw pressed button
		DrawHorzText(pDC, CPoint(1, 1));
	}
	else {
		pDC->DrawEdge(m_rcItem, BDR_SUNKENOUTER, BF_RECT);
		DrawVertText(pDC, CPoint(1, 1));
	}
}

void CMenuButton::DrawNone(CDC* pDC)
{
	if (m_fsState & MISTATE_HORZ) {
		DrawHorzText(pDC);
	}
	else {
		DrawVertText(pDC);
	}
}

//////////////////////////////////////////////////////////////////////
// CMenuIcon class
CMenuIcon::CMenuIcon(CWnd* pMenuBar)
{
	ASSERT_VALID(pMenuBar);
	m_pMenuBar = pMenuBar;
	m_hIconWinLogo = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ASSERT(m_hIconWinLogo);

	m_fsStyle |= MISTYLE_TRACKABLE;
	m_fsState |= MISTATE_HIDDEN;
	m_sizeHorz = CSize(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
}

CMenuIcon::~CMenuIcon()
{
	if (m_hIconWinLogo != NULL)
		::FreeResource(m_hIconWinLogo);
}

void CMenuIcon::OnActivateChildWnd()
{
	//LTRACE(_T("CMenuIcon::OnActivateChildWnd\n"));

	ASSERT_VALID(m_pMenuBar);
	
	CWnd* pFrame = m_pMenuBar->GetTopLevelFrame();
	ASSERT_VALID(pFrame);
	CMDIFrameWnd* pMDIFrame = STATIC_DOWNCAST(CMDIFrameWnd, pFrame);
	HWND hWndMDIClient = pMDIFrame->m_hWndMDIClient;
	ASSERT(::IsWindow(hWndMDIClient));

	BOOL bMaximized = FALSE;
	HWND hWndChild = (HWND)::SendMessage(hWndMDIClient,
		WM_MDIGETACTIVE, 0, (LPARAM)&bMaximized);

	if (bMaximized == FALSE) {
		//LTRACE(_T("    not maximized\n"));
		m_fsState |= MISTATE_HIDDEN;
	}
	else {
		//LTRACE(_T("    maximized\n"));
		m_fsState &= ~MISTATE_HIDDEN;
	}

	m_hDocIcon = (HICON)::GetClassLong(hWndChild, GCL_HICONSM);

	if (m_hDocIcon == NULL) // if hWndChild doesn't have own icon
		m_hDocIcon = m_hIconWinLogo;
}

void CMenuIcon::Update(CDC* pDC)
{
	if (m_fsState & MISTATE_HIDDEN)
		return;

	ASSERT(m_hDocIcon);
	ASSERT(m_rcItem.IsRectEmpty() == FALSE);
	::DrawIconEx(pDC->m_hDC, m_rcItem.left, m_rcItem.top, m_hDocIcon,
		m_rcItem.Width(), m_rcItem.Height(), 0, NULL, DI_NORMAL);
}

void CMenuIcon::TrackPopup(CWnd* /*pBar*/, CWnd* pWndSentCmd)
{
	ASSERT(!(m_fsState & MISTATE_HIDDEN));
	ASSERT_VALID(m_pMenuBar);
	
	CWnd* pFrame = m_pMenuBar->GetTopLevelFrame();
	ASSERT_VALID(pFrame);
	CMDIFrameWnd* pMDIFrame = STATIC_DOWNCAST(CMDIFrameWnd, pFrame);
	HWND hWndMDIClient = pMDIFrame->m_hWndMDIClient;
	ASSERT(::IsWindow(hWndMDIClient));

	BOOL bMaximized = FALSE;
	HWND hWndChild = (HWND)::SendMessage(hWndMDIClient,
		WM_MDIGETACTIVE, 0, (LPARAM)&bMaximized);
	ASSERT(bMaximized);
	HMENU hSysMenu = ::GetSystemMenu(hWndChild, FALSE);
	ASSERT(::IsMenu(hSysMenu));	

	CControlBar* pControlBar = STATIC_DOWNCAST(CControlBar, m_pMenuBar);
	ASSERT_VALID(pControlBar);
	CRect rcItem(m_rcItem);	m_pMenuBar->ClientToScreen(rcItem);
	UINT fuFlags; TPMPARAMS tpm;
	CPoint pt = _ComputeMenuTrackPoint(rcItem, pControlBar->GetBarStyle(), fuFlags, tpm);

	::TrackPopupMenuEx(hSysMenu, fuFlags, pt.x, pt.y, pWndSentCmd->GetSafeHwnd(), &tpm);
}

void CMenuIcon::Layout(CPoint point, BOOL bHorz)
{
	if (bHorz)
		m_fsState |= MISTATE_HORZ;
	else
		m_fsState &= ~MISTATE_HORZ;

	if (m_fsState & MISTATE_HIDDEN) {
		m_rcItem.SetRectEmpty();
		return;
	}
	
	m_rcItem = CRect(point, CSize(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON)));
}

//////////////////////////////////////////////////////////////////////
// CMenuControl class
#define CX_GAP_CAPTION 2

CMenuControl::CMenuControl(CWnd* pMenuBar)
{
	ASSERT_VALID(pMenuBar);
	m_pMenuBar = pMenuBar;
	m_bDown = FALSE;
	m_nTracking = -1;

	m_fsState |= MISTATE_HIDDEN;

	CSize sizeCaption = GetCaptionSize();
	m_sizeHorz = CSize(sizeCaption.cx*3 + CX_GAP_CAPTION + 1, sizeCaption.cy + 2);
}

void CMenuControl::Update(CDC* pDC)
{
	// do nothing
}

void CMenuControl::Layout(CPoint point, BOOL bHorz)
{
	//LTRACE(_T("CMenuControl::Layout bHorz:%d\n"), bHorz);

	if (bHorz)
		m_fsState |= MISTATE_HORZ;
	else
		m_fsState &= ~MISTATE_HORZ;

	if (m_fsState & MISTATE_HIDDEN) {
		m_rcItem.SetRectEmpty();
		return;
	}

	// just layout easily
	if (bHorz) {
		m_rcItem = CRect(point, m_sizeHorz);
	}
	else {
		m_rcItem = CRect(point, CSize(m_sizeHorz.cy, m_sizeHorz.cx));
	}
}

void CMenuControl::DelayLayoutAndDraw(CDC* pDC, CSize sizeBar)
{
	//LTRACE(_T("CMenuControl::DelayLayoutAndDraw\n"));
	//LTRACE(_T("    %d, %d\n"), sizeBar.cx, sizeBar.cy);
	// layout
	CSize sizeCaption = GetCaptionSize();
	int cxCaption = sizeCaption.cx;
	int cyCaption = sizeCaption.cy;

	if (m_fsState & MISTATE_HORZ) {
		CRect rcCaption;
		rcCaption.right = sizeBar.cx;
		rcCaption.bottom = sizeBar.cy;
		rcCaption.left = rcCaption.right - cxCaption;
		rcCaption.top = rcCaption.bottom - cyCaption;

		m_arrCaption[0] = rcCaption;

		rcCaption -= CPoint(cxCaption+CX_GAP_CAPTION, 0);
		m_arrCaption[1] = rcCaption;

		rcCaption -= CPoint(cxCaption, 0);
		m_arrCaption[2] = rcCaption;

		m_rcItem = CRect(m_arrCaption[2].left, m_arrCaption[2].top,
			m_arrCaption[0].right, m_arrCaption[0].bottom);
	}
	else {
		CRect rcCaption;
		rcCaption.left = 0;
		rcCaption.bottom = sizeBar.cy;
		rcCaption.right = rcCaption.left + cxCaption;
		rcCaption.top = rcCaption.bottom - cyCaption;

		m_arrCaption[0] = rcCaption;	

		rcCaption -= CPoint(0, cyCaption+CX_GAP_CAPTION);
		m_arrCaption[1] = rcCaption;

		rcCaption -= CPoint(0, cyCaption);
		m_arrCaption[2] = rcCaption;

		m_rcItem = CRect(m_arrCaption[2].left, m_arrCaption[2].top,
			m_arrCaption[0].right, m_arrCaption[0].bottom);
	}

	if (m_fsState & MISTATE_HIDDEN) {
		//LTRACE(_T("    hidden\n"));
		return;
	}

	// draw frame controls
	for (int i = 0; i < 3; ++i) {
		DrawControl(pDC, i, FALSE);
	}	
}

BOOL CMenuControl::OnMouseMsg(UINT msg, UINT nFlags, CPoint pt)
{
	if (m_fsState & MISTATE_HIDDEN)
		return FALSE;

	if (msg == WM_LBUTTONDOWN) {
		//LTRACE(_T("    WM_LBUTTONDOWN\n"));
		m_nTracking = HitTest(pt);
		if (m_nTracking >= 0) {
			CClientDC dc(m_pMenuBar);
			DrawControl(&dc, m_nTracking, TRUE);
			m_bDown = TRUE;
			m_pMenuBar->SetCapture();				  // grab mouse input
			return TRUE;
		}
	}
	else if ((msg == WM_MOUSEMOVE) && m_nTracking >= 0) {
		// mouse moved, and I am tracking: possibly draw button up/down
		BOOL bOldDown = m_bDown;
		m_bDown = m_arrCaption[m_nTracking].PtInRect(pt);
		if (bOldDown != m_bDown) {
			// up/down state changed: need to redraw button
			CClientDC dc(m_pMenuBar);
			DrawControl(&dc, m_nTracking, m_bDown);
		}
		return TRUE; // handled

	}
	else if (msg == WM_LBUTTONUP && m_nTracking >= 0) {
		// user released the mouse and I am tracking: do button command
		ReleaseCapture(); // let go the mouse
		if (m_bDown) {
			// if button was down when released: draw button up, and do system cmd
			CClientDC dc(m_pMenuBar);
			DrawControl(&dc, m_nTracking, FALSE);
			CFrameWnd* pFrame = m_pMenuBar->GetTopLevelFrame()->GetActiveFrame();
			ASSERT_VALID(pFrame);
			static int syscmd[3] =
			{ /*SC_MOUSEMENU,*/ SC_CLOSE, SC_RESTORE, SC_MINIMIZE };
			// SendMessage occur access violation!
			// *****fixed by Koay Kah Hoe. Thanks!*****
			pFrame->PostMessage(WM_SYSCOMMAND, syscmd[m_nTracking]);
		}
		m_nTracking = -1; // stop tracking
		return TRUE;	  // handled (eat)
	}

	return FALSE;
}

int CMenuControl::HitTest(CPoint point)
{
	for (int i = 0; i < 3; ++i) {
		if (m_arrCaption[i].PtInRect(point))
			return i;
	}

	return -1;
}

void CMenuControl::DrawControl(CDC* pDC, int nIndex, BOOL bPressed)
{
	//LTRACE(_T("CMenuControl::DrawControl\n"));
	// draw frame controls
	CRect& rc = m_arrCaption[nIndex];
	//LTRACE(_T("    %d, %d, %d, %d\n"), rc.left, rc.top, rc.right, rc.bottom);
	static UINT dfcs[3] = { DFCS_CAPTIONCLOSE, DFCS_CAPTIONRESTORE, DFCS_CAPTIONMIN };
	UINT uState = dfcs[nIndex];
	if (bPressed)
		uState |= DFCS_PUSHED;
	pDC->DrawFrameControl(rc, DFC_CAPTION, uState);
}

void CMenuControl::ForceDrawControl(CDC * pDC)
{
	if (m_fsState & MISTATE_HIDDEN)
		return;

	for (int i = 0; i < 3; ++i) {
		DrawControl(pDC, i, FALSE);
	}
}

void CMenuControl::OnActivateChildWnd()
{
	//LTRACE(_T("CMenuControl::OnActivateChildWnd\n"));
	ASSERT_VALID(m_pMenuBar);
	
	CWnd* pFrame = m_pMenuBar->GetTopLevelFrame();
	ASSERT_VALID(pFrame);
	CMDIFrameWnd* pMDIFrame = STATIC_DOWNCAST(CMDIFrameWnd, pFrame);
	HWND hWndMDIClient = pMDIFrame->m_hWndMDIClient;
	ASSERT(::IsWindow(hWndMDIClient));

	BOOL bMaximized = FALSE;
	HWND hWndChild = (HWND)::SendMessage(hWndMDIClient,
		WM_MDIGETACTIVE, 0, (LPARAM)&bMaximized);

	if (bMaximized == FALSE) {
		m_fsState |= MISTATE_HIDDEN;
	}
	else {
		m_fsState &= ~MISTATE_HIDDEN;
	}
}

CSize CMenuControl::GetCaptionSize()
{
	NONCLIENTMETRICS info; info.cbSize = sizeof(info);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);

	// due to my own feeling
	return CSize(info.iMenuHeight - info.iBorderWidth*2, info.iMenuHeight - info.iBorderWidth*4);
}

#if _MFC_VER < 0x0600
void CMenuBar::SetBorders(int cxLeft, int cyTop, int cxRight, int cyBottom)
{
	ASSERT(cxLeft >= 0);
	ASSERT(cyTop >= 0);
	ASSERT(cxRight >= 0);
	ASSERT(cyBottom >= 0);

	m_cxLeftBorder = cxLeft;
	m_cyTopBorder = cyTop;
	m_cxRightBorder = cxRight;
	m_cyBottomBorder = cyBottom;
}
#endif

void CMenuBar::_DrawGripper(CDC* pDC, const CRect& rect)
{
	COLORREF clrBtnHilite = ::GetSysColor(COLOR_BTNHILIGHT);
	COLORREF clrBtnShadow = ::GetSysColor(COLOR_BTNSHADOW);

	BOOL bDrawGripper = !(m_dwStyle & CBRS_FLOATING) && (m_dwExStyle & CBRS_GRIPPER);

	// only draw the gripper if not floating and gripper is specified
	if (bDrawGripper)
	{
		// draw the gripper in the border
		if (m_dwStyle & CBRS_ORIENT_HORZ)
		{
			if (bDrawGripper) {
				pDC->Draw3dRect(rect.left+CX_BORDER_GRIPPER,
					rect.top+m_cyTopBorder,
					CX_GRIPPER, rect.Height()-m_cyTopBorder-m_cyBottomBorder,
					clrBtnHilite, clrBtnShadow);
			}		
		}
		else
		{
			if (bDrawGripper) {
				pDC->Draw3dRect(rect.left+m_cyTopBorder,
					rect.top+CY_BORDER_GRIPPER,
					rect.Width()-m_cyTopBorder-m_cyBottomBorder, CY_GRIPPER,
					clrBtnHilite, clrBtnShadow);
			}
		}
	}
}

// input CRect should be client rectangle size
void CMenuBar::_CalcInsideRect(CRect& rect, BOOL bHorz) const
{
	LTRACE(_T("CMenuBar::_CalcInsideRect\n"));
	ASSERT_VALID(this);
	DWORD dwStyle = m_dwStyle;

	if (dwStyle & CBRS_BORDER_LEFT)
		rect.left += cxBorder2;
	if (dwStyle & CBRS_BORDER_TOP)
		rect.top += cyBorder2;
	if (dwStyle & CBRS_BORDER_RIGHT)
		rect.right -= cxBorder2;
	if (dwStyle & CBRS_BORDER_BOTTOM)
		rect.bottom -= cyBorder2;

	BOOL bDrawGripper = !(m_dwStyle & CBRS_FLOATING) && (m_dwExStyle & CBRS_GRIPPER);

	// inset the top and bottom.
	if (bHorz)
	{
		rect.left += m_cxLeftBorder;
		rect.top += m_cyTopBorder;
		rect.right -= m_cxRightBorder;
		rect.bottom -= m_cyBottomBorder;
		if (bDrawGripper)
			rect.left += CX_GRIPPER_ALL;
	}
	else
	{
		rect.left += m_cyTopBorder;
		rect.top += m_cxLeftBorder;
		rect.right -= m_cyBottomBorder;
		rect.bottom -= m_cxRightBorder;
		if (bDrawGripper)
			rect.top += CY_GRIPPER_ALL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMenuDockBar implementation
// a little changed from CDockBar implementation

static BOOL _IsMenuBar(int nPos, CPtrArray& arrBars)
{
	if (nPos < arrBars.GetSize()) {
		CControlBar* pBar = (CControlBar*)arrBars[nPos];
		if (pBar && pBar->GetDlgCtrlID() == AFX_IDW_MENUBAR)
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}

CSize CMenuDockBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	LTRACE(_T("CMenuDockBar::CalcFixedLayout\n"));
	ASSERT_VALID(this);

	CSize sizeFixed = CControlBar::CalcFixedLayout(bStretch, bHorz);

	// get max size
	CSize sizeMax;
	if (!m_rectLayout.IsRectEmpty())
		sizeMax = m_rectLayout.Size();
	else
	{
		CRect rectFrame;
		CFrameWnd* pFrame = GetParentFrame();
		pFrame->GetClientRect(&rectFrame);
		sizeMax = rectFrame.Size();
	}

	// prepare for layout
	AFX_SIZEPARENTPARAMS layout;
	layout.hDWP = m_bLayoutQuery ?
		NULL : ::BeginDeferWindowPos(m_arrBars.GetSize());
	CPoint pt(-cxBorder2, -cyBorder2);
	int nWidth = 0;

	BOOL bWrapped = FALSE;

	// layout all the control bars
	for (int nPos = 0; nPos < m_arrBars.GetSize(); nPos++)
	{
		CControlBar* pBar = GetDockedControlBar(nPos);
		void* pVoid = m_arrBars[nPos];

		if (pBar != NULL)// pBar is valid
		{
			if (pBar->IsVisible())// visible
			{
				// get ideal rect for bar
				DWORD dwMode = 0;
				if ((pBar->m_dwStyle & CBRS_SIZE_DYNAMIC) &&
					(pBar->m_dwStyle & CBRS_FLOATING))
					dwMode |= LM_HORZ | LM_MRUWIDTH;
				else if (pBar->m_dwStyle & CBRS_ORIENT_HORZ)
					dwMode |= LM_HORZ | LM_HORZDOCK;
				else
					dwMode |=  LM_VERTDOCK;

				CSize sizeBar = pBar->CalcDynamicLayout(-1, dwMode);

				CRect rect(pt, sizeBar);

				// get current rect for bar
				CRect rectBar;
				pBar->GetWindowRect(&rectBar);
				ScreenToClient(&rectBar);

				if (bHorz)// horizontal
				{
					// Offset Calculated Rect out to Actual
					if (rectBar.left > rect.left && !m_bFloating)
						rect.OffsetRect(rectBar.left - rect.left, 0);

					// If ControlBar goes off the right, then right justify
					if (rect.right > sizeMax.cx && !m_bFloating)
					{
						int x = rect.Width() - cxBorder2;
						x = max(sizeMax.cx - x, pt.x);
						rect.OffsetRect(x - rect.left, 0);
					}

					// If ControlBar has been wrapped, then left justify
					if (bWrapped)
					{
						bWrapped = FALSE;
						rect.OffsetRect(-(rect.left + cxBorder2), 0);
					}
					// If ControlBar is completely invisible, then wrap it
					else if ((rect.left >= (sizeMax.cx - cxBorder2) || _IsMenuBar(nPos, m_arrBars))
						&& (nPos > 0) && (m_arrBars[nPos - 1] != NULL))
					{
						m_arrBars.InsertAt(nPos, (CObject*)NULL);
						pBar = NULL; pVoid = NULL;
						bWrapped = TRUE;
					}
					if (!bWrapped)
					{
						if (rect != rectBar)
						{
							if (!m_bLayoutQuery &&
								!(pBar->m_dwStyle & CBRS_FLOATING))
							{
								pBar->m_pDockContext->m_rectMRUDockPos = rect;
							}
							AfxRepositionWindow(&layout, pBar->m_hWnd, &rect);
						}
						pt.x = rect.left + sizeBar.cx - cxBorder2;
						nWidth = max(nWidth, sizeBar.cy);
					}
				}
				else	// vertical
				{
					// Offset Calculated Rect out to Actual
					if (rectBar.top > rect.top && !m_bFloating)
						rect.OffsetRect(0, rectBar.top - rect.top);

					// If ControlBar goes off the bottom, then bottom justify
					if (rect.bottom > sizeMax.cy && !m_bFloating)
					{
						int y = rect.Height() - cyBorder2;
						y = max(sizeMax.cy - y, pt.y);
						rect.OffsetRect(0, y - rect.top);
					}

					// If ControlBar has been wrapped, then top justify
					if (bWrapped)
					{
						bWrapped = FALSE;
						rect.OffsetRect(0, -(rect.top + cyBorder2));
					}
					// If ControlBar is completely invisible, then wrap it
					else if ((rect.top >= (sizeMax.cy - cyBorder2) || _IsMenuBar(nPos, m_arrBars))
						&& (nPos > 0) && (m_arrBars[nPos - 1] != NULL))
					{
						m_arrBars.InsertAt(nPos, (CObject*)NULL);
						pBar = NULL; pVoid = NULL;
						bWrapped = TRUE;
					}

					if (!bWrapped)
					{
						if (rect != rectBar)
						{
							if (!m_bLayoutQuery &&
								!(pBar->m_dwStyle & CBRS_FLOATING))
							{
								pBar->m_pDockContext->m_rectMRUDockPos = rect;
							}
							AfxRepositionWindow(&layout, pBar->m_hWnd, &rect);
						}
						pt.y = rect.top + sizeBar.cy - cyBorder2;
						nWidth = max(nWidth, sizeBar.cx);
					}
				}// if vertical
			}// if visible
			if (!bWrapped)
			{
				// handle any delay/show hide for the bar
				pBar->RecalcDelayShow(&layout);
			}
		}// if pBar is valid
		if (pBar == NULL && pVoid == NULL && nWidth != 0)
		{
			// end of row because pBar == NULL
			if (bHorz)
			{
				pt.y += nWidth - cyBorder2;
				sizeFixed.cx = max(sizeFixed.cx, pt.x);
				sizeFixed.cy = max(sizeFixed.cy, pt.y);
				pt.x = -cxBorder2;
			}
			else
			{
				pt.x += nWidth - cxBorder2;
				sizeFixed.cx = max(sizeFixed.cx, pt.x);
				sizeFixed.cy = max(sizeFixed.cy, pt.y);
				pt.y = -cyBorder2;
			}
			nWidth = 0;
		}
	}// for
	if (!m_bLayoutQuery)
	{
		// move and resize all the windows at once!
		if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
			TRACE0("Warning: DeferWindowPos failed - low system resources.\n");
	}

	// adjust size for borders on the dock bar itself
	CRect rect;
	rect.SetRectEmpty();
	CalcInsideRect(rect, bHorz);

	if ((!bStretch || !bHorz) && sizeFixed.cx != 0)
		sizeFixed.cx += -rect.right + rect.left;
	if ((!bStretch || bHorz) && sizeFixed.cy != 0)
		sizeFixed.cy += -rect.bottom + rect.top;

	return sizeFixed;
}


