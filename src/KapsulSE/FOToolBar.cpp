// FOToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "FOToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlyout - implemented only in this cpp file

/////////////////////////////////////////////////////////////////////////////
// CFOToolBar

CFOToolBar::CFOToolBar() : toDrawDropDownArrows(false), index(-1), nID(0)
{
}

CFOToolBar::~CFOToolBar()
{
}


BEGIN_MESSAGE_MAP(CFOToolBar, CToolBar)
	//{{AFX_MSG_MAP(CFOToolBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFOToolBar message handlers

void CFOToolBar::Init()
{
	m_flyout.m_NormalList=GetToolBarCtrl().GetImageList();
	m_flyout.m_HotList=GetToolBarCtrl().GetHotImageList();
	m_flyout.daParent=(CToolBarCtrl*)this;

	m_flyout.Init();
	m_flyout.SetButton(0);

	m_flyout2.m_NormalList=GetToolBarCtrl().GetImageList();
	m_flyout2.m_HotList=GetToolBarCtrl().GetHotImageList();
	m_flyout2.daParent=(CToolBarCtrl*)this;
	m_flyout2.SetButton(0);

	m_flyout3.m_NormalList=GetToolBarCtrl().GetImageList();
	m_flyout3.m_HotList=GetToolBarCtrl().GetHotImageList();
	m_flyout3.daParent=(CToolBarCtrl*)this;
	m_flyout3.SetButton(2);
	

	CToolBarCtrl& m_toolBarCtrl = GetToolBarCtrl();

	// get the information about the button. If there's no such button - return
	TBBUTTON m_btnInfo;

	if (m_toolBarCtrl.GetButton(5, &m_btnInfo) == 0) return;
	ids.push_back(make_pair(m_btnInfo.idCommand, NULL));

	if (m_toolBarCtrl.GetButton(6, &m_btnInfo) == 0) return;
	ids.push_back(make_pair(m_btnInfo.idCommand, NULL));

	if (m_toolBarCtrl.GetButton(7, &m_btnInfo) == 0) return;
	ids.push_back(make_pair(m_btnInfo.idCommand, NULL));

	// signal that a new drop-down arrow has to be drawn on the button
	toDrawDropDownArrows = true;

}

void CFOToolBar::addFlyout(UINT buttonIndex, UINT toolbarID)
{
	CToolBarCtrl& m_toolBarCtrl = GetToolBarCtrl();

	// get the information about the button. If there's no such button - return
	TBBUTTON m_btnInfo;
	if (m_toolBarCtrl.GetButton(buttonIndex, &m_btnInfo) == 0) return;

	// add the button & toolbar IDs to the ID list
	ids.push_back(make_pair(m_btnInfo.idCommand, toolbarID));

	// signal that a new drop-down arrow has to be drawn on the button
	toDrawDropDownArrows = true;
}

void CFOToolBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	CToolBar::OnLButtonDown(nFlags, point);

	CToolBarCtrl& m_toolBarCtrl = GetToolBarCtrl();

	// test if we're inside a button
	index = m_toolBarCtrl.HitTest(&point);
	if (index < 0) return;	// not on a button

	TBBUTTON m_btnInfo;
	m_toolBarCtrl.GetButton(index, &m_btnInfo);
/*
	// check if we attached a fly-out toolbar to this button
	for (vector<pair<UINT, UINT> >::const_iterator i = ids.begin(); i != ids.end(); ++i)
		if (i->first == m_btnInfo.idCommand) break;

	if (i == ids.end()) return;	// no flyout toolbar is attached to this button - so quit
*/
	//if (m_btnInfo.idCommand
//	nID = i->second;

	if ((index==7)||(index==8)||(index==9))
	// there's a flyout toolbar attached to this button, so start the timer..
	SetTimer(1, 300, NULL);
}

void CFOToolBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	KillTimer(1);

	if (m_flyout.m_hWnd) {
		CToolBarCtrl& m_toolBarCtrl = GetToolBarCtrl();

		InvalidateRect(NULL, FALSE);
	}


	CToolBar::OnLButtonUp(nFlags, point);
}

void CFOToolBar::OnMouseMove(UINT nFlags, CPoint point)
{
	CToolBar::OnMouseMove(nFlags, point);

	if (m_flyout.m_hWnd) {
		// if we have a flyout, delegate the messages to the flyout toolbar
		m_flyout.SetFocus();
		ClientToScreen(&point);
		m_flyout.ScreenToClient(&point);
		m_flyout.SendMessage(WM_MOUSEMOVE, WPARAM(nFlags), MAKELPARAM(point.x, point.y));
	}
}

void CFOToolBar::OnTimer(UINT nIDEvent)
{
	if (nIDEvent != 1) { CToolBar::OnTimer(nIDEvent); return; }

	KillTimer(1);

	// create the toolbar
	CFrameWnd* m_pFrameWnd = IsFloating() ? (CFrameWnd*)(GetParentFrame()->GetParent()) : (CFrameWnd*)(GetParentFrame());
	switch (index)
	{
	case 7:
		m_flyout3.Create(IDD_MODE,m_pFrameWnd);
		break;
	case 8:
		m_flyout2.Create(IDD_SELECTION,m_pFrameWnd);
		break;
	case 9:
		m_flyout.Create(IDD_PRIMITIVES,m_pFrameWnd);
		break;
	}


	//

	// calculate the coordinates where the flyout will be displayed - this should be right next
	// to the button
	CRect m_btnRect;
	GetToolBarCtrl().GetItemRect(index, m_btnRect);
	ClientToScreen(m_btnRect);

	CRect m_tbRect;
	GetWindowRect(m_tbRect);

	CPoint point(0, 0);

	if (IsFloating() || (GetBarStyle() & CBRS_ORIENT_HORZ)) {
		// if floating - the flyout is displayed right under the button
		point.x = m_btnRect.left;
		point.y = m_btnRect.bottom;
	}
	else {
		// vertical - so the flyout is displayed to the right of the button
		point.x = m_btnRect.right;
		point.y = m_btnRect.top;
	}

	CRect ScreenRect(0, 0, ::GetSystemMetrics(SM_CXSCREEN),::GetSystemMetrics(SM_CYSCREEN));
	CRect WindRect;

	switch (index)
	{
	case 7:
		m_flyout3.GetWindowRect(&WindRect);
		break;
	case 8:
		m_flyout2.GetWindowRect(&WindRect);
		break;
	case 9:
		m_flyout.GetWindowRect(&WindRect);
		break;
	}

	WindRect.right-=WindRect.left;
	WindRect.bottom-=WindRect.top;


	if ((point.x+WindRect.right)>ScreenRect.right) point.x=ScreenRect.right-WindRect.right;
	else
		if (point.x<0) point.x=0;

	if ((point.y+WindRect.bottom)>(ScreenRect.bottom-28)) point.y=ScreenRect.bottom-WindRect.bottom-28;
	else
		if (point.y<0) point.y=0;


	switch (index)
	{
	case 7:
		m_flyout3.SetWindowPos(NULL,point.x,point.y,0,0,SWP_NOSIZE|SWP_NOZORDER);
		m_flyout3.ShowWindow(SW_SHOWNORMAL);
		m_flyout3.SetFocus();
		break;
	case 8:
		m_flyout2.SetWindowPos(NULL,point.x,point.y,0,0,SWP_NOSIZE|SWP_NOZORDER);
		m_flyout2.ShowWindow(SW_SHOWNORMAL);
		m_flyout2.SetFocus();
		break;
	case 9:
		m_flyout.SetWindowPos(NULL,point.x,point.y,0,0,SWP_NOSIZE|SWP_NOZORDER);
		m_flyout.ShowWindow(SW_SHOWNORMAL);
		m_flyout.SetFocus();
		break;
	}
}
