//////////////////////////////////////////////////////////////////////////////
//
// RollupCtrl.cpp
// 
// Code Johann Nadalutti
// Mail: jnadalutti@worldonline.fr
//
//////////////////////////////////////////////////////////////////////////////
//
// This code is free for personal and commercial use, providing this 
// notice remains intact in the source files and all eventual changes are
// clearly marked with comments.
//
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
//////////////////////////////////////////////////////////////////////////////
//
// History
// --------
// #v1.0
//	31/03/01:	Created
//
// #v1.01
//	13/04/01:	Added ScrollToPage() method
//				Added automatic page visibility to ExpandPage() method
//				Added Mousewheel support
//	15/04/01:	Added mouse capture checking on WM_MOUSEMOVE dialog msg
//				Added SetCursor() on Dialog WM_SETCURSOR
//				Added MovePageAt() method
//	17/04/01:	Fixed Group Boxes displayed over Buttons
//	20/04/01:	Added IsPageExpanded() and IsPageExpanded() methods
//				Added PopupMenu
//				Added Button subclassing (now button's focus not drawn)
//
// Note
// -----
//	Dialog box width is
//		RollupCtrlClientRect.Width() - RC_SCROLLBARWIDTH - (RC_GRPBOXINDENT*2)
//
//
// Thanks to
// ----------
// PJ Arends, Ramon Smits, Uwe Keim, Daniel Madden, Do Quyet Tien,
// Ravi Bhavnani, Masaaki Onishi, ...
// and all others users for their comments.
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRollupCtrl Includes
#include "stdafx.h"
#include "RollupCtrl.h"

/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRollupCtrl Message Map

BEGIN_MESSAGE_MAP(CRollupCtrl, CWnd)
	//{{AFX_MSG_MAP(CRollupCtrl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEACTIVATE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRollupCtrl Implementation

IMPLEMENT_DYNCREATE(CRollupCtrl, CWnd)

char * m_strRollUpClass=NULL;

//---------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------
CRollupCtrl::CRollupCtrl()
{
	/*
*/
	m_nStartYPos = m_nPageHeight = 0;
}

//---------------------------------------------------------------------------
// Destructor
//---------------------------------------------------------------------------
CRollupCtrl::~CRollupCtrl()
{
	//Remove all pages allocations
	for (int i=0; i<m_PageList.GetSize(); i++) {
		if (m_PageList[i]->pwndButton)		delete m_PageList[i]->pwndButton;
		if (m_PageList[i]->pwndGroupBox)	delete m_PageList[i]->pwndGroupBox;

		if (m_PageList[i]->pwndTemplate && m_PageList[i]->bAutoDestroyTpl)	{
			m_PageList[i]->pwndTemplate->DestroyWindow();
			delete m_PageList[i]->pwndTemplate;
		}

		delete m_PageList[i];
	}

}

//---------------------------------------------------------------------------
// Create
//---------------------------------------------------------------------------
BOOL CRollupCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return  CWnd::Create(m_strRollUpClass, "RollupCtrl", dwStyle, rect, pParentWnd, nID);
}


//---------------------------------------------------------------------------
// Function name	: InsertPage
// Description		: Return -1 if an error occurs
//					  Make sure template had WS_CHILD style
//---------------------------------------------------------------------------
int CRollupCtrl::InsertPage(LPCTSTR caption, UINT nIDTemplate, CRuntimeClass* rtc, int idx)
{
	if (idx>0 && idx>=m_PageList.GetSize())		idx=-1;

	//Create Template
	ASSERT(rtc!=NULL);
	CDialog* pwndTemplate = (CDialog*)rtc->CreateObject();
	BOOL b = pwndTemplate->Create(nIDTemplate, this);
	if (!b)	{ delete pwndTemplate; return -1; }

	//Insert Page
	return _InsertPage(caption, pwndTemplate, idx, TRUE);
}


//---------------------------------------------------------------------------
// Function name	: InsertPage
// Description		: return -1 if an error occurs
//					  Make sure template had WS_CHILD style
//---------------------------------------------------------------------------
int CRollupCtrl::InsertPage(LPCTSTR caption, CDialog* pwndTemplate, BOOL bAutoDestroyTpl, int idx)
{
	if (!pwndTemplate)		return -1;

	if (idx>0 && idx>=m_PageList.GetSize())		idx=-1;

	//Insert Page
	return _InsertPage(caption, pwndTemplate, idx, bAutoDestroyTpl);
}


//---------------------------------------------------------------------------
// Function name	: InsertPage
// Description		: Called by InsertPage(...) methods
//					  Return -1 if an error occurs
//					  Make sure template had WS_CHILD style
//---------------------------------------------------------------------------
int CRollupCtrl::_InsertPage(LPCTSTR caption, CDialog* pwndTemplate, int idx, BOOL bAutoDestroyTpl)
{
	ASSERT(pwndTemplate!=NULL);
	ASSERT(pwndTemplate->m_hWnd!=NULL);

 	//Get client rect
	CRect r; GetClientRect(r);

	//Create GroupBox
	CButton* groupbox = new CButton;
	groupbox->Create("", WS_CHILD|BS_GROUPBOX, r, this, 0 );

	//Create Button
	CButton* but = new CButton;
	but->Create(caption, WS_CHILD|BS_AUTOCHECKBOX|BS_PUSHLIKE|BS_FLAT, r, this, 0 ); 

	//Change Button's font
	HFONT hfont= (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	CFont* font = CFont::FromHandle(hfont);
	but->SetFont(font);

	//Add page at pagelist
	RC_PAGEINFO*	pi = new RC_PAGEINFO;
	pi->bExpanded		= FALSE;
	pi->bEnable			= TRUE;
	pi->pwndTemplate	= pwndTemplate;
	pi->pwndButton		= but;
	pi->pwndGroupBox	= groupbox;
	pi->pOldDlgProc		= (WNDPROC)::GetWindowLong(pwndTemplate->m_hWnd, DWL_DLGPROC);
	pi->pOldButProc		= (WNDPROC)::GetWindowLong(but->m_hWnd, GWL_WNDPROC);
	pi->bAutoDestroyTpl	= bAutoDestroyTpl;

	int newidx;
	if (idx<0)	newidx = m_PageList.Add(pi);
	else	{ m_PageList.InsertAt(idx, pi); newidx=idx; }

	//Set Dlg Window datas
	::SetWindowLong(pwndTemplate->m_hWnd, GWL_USERDATA,	(LONG)m_PageList[newidx]);
	::SetWindowLong(pwndTemplate->m_hWnd, DWL_USER,		(LONG)this);

	//Set But Window data
	::SetWindowLong(but->m_hWnd, GWL_USERDATA,	(LONG)m_PageList[newidx]);

	//SubClass Template window proc
	::SetWindowLong(pwndTemplate->m_hWnd, DWL_DLGPROC, (LONG)CRollupCtrl::DlgWindowProc);

	//SubClass Button window proc
	::SetWindowLong(but->m_hWnd, GWL_WNDPROC, (LONG)CRollupCtrl::ButWindowProc);

	//Update
	m_nPageHeight+=RC_PGBUTTONHEIGHT+(RC_GRPBOXINDENT/2);
	RecalLayout();

	return newidx;
}


//---------------------------------------------------------------------------
// Function name	: RemovePage
// Description		: 
//---------------------------------------------------------------------------
void CRollupCtrl::RemovePage(int idx)
{
	if (idx>=m_PageList.GetSize() || idx<0)				return;

	//Remove
	_RemovePage(idx);

	//Update
	RecalLayout();
}

//---------------------------------------------------------------------------
// Function name	: RemoveAllPages
// Description		:
//---------------------------------------------------------------------------
void CRollupCtrl::RemoveAllPages()
{
	//Remove all
	for (; m_PageList.GetSize();)
		_RemovePage(0);

	//Update
	RecalLayout();
}

//---------------------------------------------------------------------------
// Function name	: _RemovePage
// Description		: Called by RemovePage or RemoveAllPages methods
//---------------------------------------------------------------------------
void CRollupCtrl::_RemovePage(int idx)
{
	RC_PAGEINFO* pi = m_PageList[idx];

	//Get Page Rect
	CRect tr; pi->pwndTemplate->GetWindowRect(&tr);

	//Update PageHeight
	m_nPageHeight-=RC_PGBUTTONHEIGHT+(RC_GRPBOXINDENT/2);
	if (pi->bExpanded)		m_nPageHeight-=tr.Height();

	//Remove wnds
	if (pi->pwndButton)				delete pi->pwndButton;
	if (pi->pwndGroupBox)			delete pi->pwndGroupBox;

	::SetWindowLong(pi->pwndTemplate->m_hWnd, DWL_DLGPROC, (LONG)pi->pOldDlgProc);


	if (pi->pwndTemplate && pi->bAutoDestroyTpl) {
		pi->pwndTemplate->DestroyWindow();
		delete pi->pwndTemplate;
	}

	//Remove page from array
	m_PageList.RemoveAt(idx);




	//Delete pageinfo
	delete pi;
}

//---------------------------------------------------------------------------
// Function name	: ExpandPage
// Description		:
//---------------------------------------------------------------------------
void CRollupCtrl::ExpandPage(int idx, BOOL bExpand)
{
	if (idx>=m_PageList.GetSize() || idx<0)				return;

	//Expand-collapse
	_ExpandPage(m_PageList[idx], bExpand);

	//Update
	RecalLayout();

	//Scroll to this page (Automatic page visibility)
	if (bExpand)	ScrollToPage(idx, FALSE);

}

//---------------------------------------------------------------------------
// Function name	: ExpandAllPages
// Description		: 
//---------------------------------------------------------------------------
void CRollupCtrl::ExpandAllPages(BOOL bExpand)
{
	//Expand-collapse All
	for (int i=0; i<m_PageList.GetSize(); i++)
		_ExpandPage(m_PageList[i], bExpand);

	//Update
	RecalLayout();
}

//---------------------------------------------------------------------------
// Function name	: _ExpandPage
// Description		: Called by ExpandPage or ExpandAllPages methods
//---------------------------------------------------------------------------
void	CRollupCtrl::_ExpandPage(RC_PAGEINFO* pi, BOOL bExpand)
{
	//Check if we need to change state
	if (pi->bExpanded==bExpand)					return;
	if (!pi->bEnable)							return;

	//Get Page Rect
	CRect tr; pi->pwndTemplate->GetWindowRect(&tr);

	//Expand-collapse
	pi->bExpanded = bExpand;

	if (bExpand)	m_nPageHeight+=tr.Height();
	else			m_nPageHeight-=tr.Height();

}


//---------------------------------------------------------------------------
// Function name	: EnablePage
// Description		: 
//---------------------------------------------------------------------------
void CRollupCtrl::EnablePage(int idx, BOOL bEnable)
{
	if (idx>=m_PageList.GetSize() || idx<0)		return;

	//Enable-Disable
	_EnablePage(m_PageList[idx], bEnable);

	//Update
	RecalLayout();
}


//---------------------------------------------------------------------------
// Function name	: EnableAllPages
// Description		: 
//---------------------------------------------------------------------------
void CRollupCtrl::EnableAllPages(BOOL bEnable)
{
	//Enable-disable All
	for (int i=0; i<m_PageList.GetSize(); i++)
		_EnablePage(m_PageList[i], bEnable);

	//Update
	RecalLayout();
}

//---------------------------------------------------------------------------
// Function name	: _EnablePage
// Description		: Called by EnablePage or EnableAllPages methods
//---------------------------------------------------------------------------
void CRollupCtrl::_EnablePage(RC_PAGEINFO* pi, BOOL bEnable)
{
	//Check if we need to change state
	if (pi->bEnable==bEnable)		return;

	//Get Page Rect
	CRect tr; pi->pwndTemplate->GetWindowRect(&tr);

	//Change state
	pi->bEnable = bEnable;

	if (pi->bExpanded)	{ m_nPageHeight-=tr.Height(); pi->bExpanded=FALSE; }
}


//---------------------------------------------------------------------------
// Function name	: ScrollToPage
// Description		: Scroll a page at the top of the RollupCtrl if bAtTheTop=TRUE
//					  or just ensure page visibility into view if bAtTheTop=FALSE
//---------------------------------------------------------------------------
void CRollupCtrl::ScrollToPage(int idx, BOOL bAtTheTop)
{
	if (idx>=m_PageList.GetSize() || idx<0)				return;

	//Get page infos
	RC_PAGEINFO* pi = m_PageList[idx];

	//Get windows rect
	CRect r; GetWindowRect(&r);
	CRect tr; pi->pwndTemplate->GetWindowRect(&tr);

	//Check page visibility
	if (bAtTheTop || ((tr.bottom>r.bottom) || (tr.top<r.top)))
	{
		//Compute new m_nStartYPos
		pi->pwndButton->GetWindowRect(&tr);
		m_nStartYPos-= (tr.top-r.top);

		//Update
		RecalLayout();
	}

}


//---------------------------------------------------------------------------
// Function name	: MovePageAt
// Description		: newidx can be equal to -1 (move at end)
//					  Return -1 if an error occurs
//---------------------------------------------------------------------------
int CRollupCtrl::MovePageAt(int idx, int newidx)
{
	if (idx==newidx)									return -1;
	if (idx>=m_PageList.GetSize() || idx<0)				return -1;

	if (newidx>0 && newidx>=m_PageList.GetSize())		newidx=-1;

	//Remove page from its old position
	RC_PAGEINFO* pi = m_PageList[idx];
	m_PageList.RemoveAt(idx);

	//Insert at its new position
	int retidx;
	if (newidx<0)	retidx = m_PageList.Add(pi);
	else	{ m_PageList.InsertAt(newidx, pi); retidx=newidx; }


	//Update
	RecalLayout();
	
	return retidx;
}


//---------------------------------------------------------------------------
// Function name	: IsPageExpanded
// Description		: 
//---------------------------------------------------------------------------
BOOL CRollupCtrl::IsPageExpanded(int idx)
{
	if (idx>=m_PageList.GetSize() || idx<0)				return FALSE;
	return m_PageList[idx]->bExpanded;
}

//---------------------------------------------------------------------------
// Function name	: IsPageEnabled
// Description		: 
//---------------------------------------------------------------------------
BOOL CRollupCtrl::IsPageEnabled(int idx)
{
	if (idx>=m_PageList.GetSize() || idx<0)				return FALSE;
	return m_PageList[idx]->bEnable;
}


//---------------------------------------------------------------------------
// Function name	: RecalLayout
// Description		: 
//---------------------------------------------------------------------------
void CRollupCtrl::RecalLayout()
{
	//Check StartPosY
	CRect r; GetClientRect(&r);
	int BottomPagePos = m_nStartYPos+m_nPageHeight;

	if (BottomPagePos<r.Height())		m_nStartYPos = r.Height()-m_nPageHeight;
	if (m_nStartYPos>0)					m_nStartYPos = 0;


	//Update layout
	HDWP hdwp = BeginDeferWindowPos(m_PageList.GetSize()*3);	//*3 for pwndButton+pwndTemplate+pwndGroupBox

	int posy=m_nStartYPos;

	for (int i=0; i<m_PageList.GetSize(); i++){
		RC_PAGEINFO* pi = m_PageList[i];

		//Enable-Disable Button
		pi->pwndButton->SetCheck(pi->bEnable&pi->bExpanded);
		pi->pwndButton->EnableWindow(pi->bEnable);

		//Expanded
		if (pi->bExpanded && pi->bEnable) {
			CRect tr; pi->pwndTemplate->GetWindowRect(&tr);

			//Update GroupBox position and size
			DeferWindowPos(hdwp, pi->pwndGroupBox->m_hWnd, 0, 2, posy, r.Width()-3-RC_SCROLLBARWIDTH, tr.Height()+RC_PGBUTTONHEIGHT+RC_GRPBOXINDENT-4, SWP_NOZORDER|SWP_SHOWWINDOW);

			//Update Template position and size
			DeferWindowPos(hdwp, pi->pwndTemplate->m_hWnd, 0, RC_GRPBOXINDENT, posy+RC_PGBUTTONHEIGHT, r.Width()-RC_SCROLLBARWIDTH-(RC_GRPBOXINDENT*2), tr.Height(), SWP_NOZORDER|SWP_SHOWWINDOW);

			//Update Button's position and size
			DeferWindowPos(hdwp, pi->pwndButton->m_hWnd, 0, RC_GRPBOXINDENT, posy, r.Width()-RC_SCROLLBARWIDTH-(RC_GRPBOXINDENT*2), RC_PGBUTTONHEIGHT, SWP_NOZORDER|SWP_SHOWWINDOW);

			posy+=tr.Height()+RC_PGBUTTONHEIGHT;

		//Collapsed
		} else {

			//Update GroupBox position and size
			DeferWindowPos(hdwp, pi->pwndGroupBox->m_hWnd, 0, 2, posy, r.Width()-3-RC_SCROLLBARWIDTH, 16,SWP_NOZORDER|SWP_SHOWWINDOW);

			//Update Template position and size
			DeferWindowPos(hdwp, pi->pwndTemplate->m_hWnd, 0, RC_GRPBOXINDENT, 0, 0, 0,SWP_NOZORDER|SWP_HIDEWINDOW|SWP_NOSIZE|SWP_NOMOVE);

			//Update Button's position and size
			DeferWindowPos(hdwp, pi->pwndButton->m_hWnd, 0, RC_GRPBOXINDENT, posy, r.Width()-RC_SCROLLBARWIDTH-(RC_GRPBOXINDENT*2), RC_PGBUTTONHEIGHT, SWP_NOZORDER|SWP_SHOWWINDOW);

			posy+=RC_PGBUTTONHEIGHT;
		}

		posy+=(RC_GRPBOXINDENT/2);

	}
	EndDeferWindowPos(hdwp);


	//Update Scroll Bar
	CRect br = CRect(r.right-RC_SCROLLBARWIDTH,r.top, r.right, r.bottom);
	InvalidateRect(&br, FALSE);
	UpdateWindow();
}

//---------------------------------------------------------------------------
// Function name	: GetPageIdxFromButtonHWND
// Description		: Return -1 if matching hwnd not found
//---------------------------------------------------------------------------
int CRollupCtrl::GetPageIdxFromButtonHWND(HWND hwnd)
{
	//Search matching button's hwnd
	for (int i=0; i<m_PageList.GetSize(); i++)
		if (hwnd==m_PageList[i]->pwndButton->m_hWnd)		return i;

	return -1;
}

//---------------------------------------------------------------------------
// Function name	: GetPageInfo
// Description		: Return -1 if an error occurs
//---------------------------------------------------------------------------
RC_PAGEINFO* CRollupCtrl::GetPageInfo(int idx)
{
	if (idx>=m_PageList.GetSize() || idx<0)				return (RC_PAGEINFO*)-1;

	return m_PageList[idx];
}


//---------------------------------------------------------------------------
// Dialog SubClasser
//---------------------------------------------------------------------------
LRESULT CALLBACK CRollupCtrl::DlgWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RC_PAGEINFO* pi		= (RC_PAGEINFO*)GetWindowLong(hWnd, GWL_USERDATA);
	CRollupCtrl* _this	= (CRollupCtrl*)GetWindowLong(hWnd, DWL_USER);

	CRect r; _this->GetClientRect(&r);
	if (_this->m_nPageHeight>r.Height())	//Can Scroll ?
	{

		switch (uMsg) {
			/*
		case WM_ERASEBKGND:
			//FillRect(GetDC()->m_hDC,&r,
			Rectangle(GetDC()->m_hDC,0,0,r.left,r.bottom);
			break;
			*/

			case WM_LBUTTONDOWN:
			case WM_MBUTTONDOWN:
			{
				CPoint pos; GetCursorPos(&pos);
				_this->m_nOldMouseYPos = pos.y;
				::SetCapture(hWnd);
			return 0;
			}

			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			{
				if (::GetCapture() == hWnd)	{ ::ReleaseCapture(); return 0; }
			break;
			}

			case WM_MOUSEMOVE:
			{
				if ((::GetCapture() == hWnd) && (wParam==MK_LBUTTON || wParam==MK_MBUTTON)) {
					CPoint pos; GetCursorPos(&pos);
					_this->m_nStartYPos+=(pos.y-_this->m_nOldMouseYPos);
					_this->RecalLayout();
					_this->m_nOldMouseYPos = pos.y;
					return 0;
				}

			break;
			}

			case WM_SETCURSOR:
				if ((HWND)wParam==hWnd)	{ ::SetCursor(::LoadCursor(NULL, RC_ROLLCURSOR)); return TRUE; }
			break;

		}//switch(uMsg)
	}

	return ::CallWindowProc(pi->pOldDlgProc, hWnd, uMsg, wParam, lParam);
}


//---------------------------------------------------------------------------
// Button SubClasser
//---------------------------------------------------------------------------
LRESULT CALLBACK CRollupCtrl::ButWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg==WM_SETFOCUS)		return FALSE;

	RC_PAGEINFO* pi	= (RC_PAGEINFO*)GetWindowLong(hWnd, GWL_USERDATA);
	return ::CallWindowProc(pi->pOldButProc, hWnd, uMsg, wParam, lParam);
}


/////////////////////////////////////////////////////////////////////////////
// CRollupCtrl message handlers

//---------------------------------------------------------------------------
// OnCommand
//---------------------------------------------------------------------------
BOOL CRollupCtrl::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	//PopupMenu command ExpandAllPages
	if		(LOWORD(wParam)==RC_IDM_EXPANDALL)			ExpandAllPages(TRUE);
	else if	(LOWORD(wParam)==RC_IDM_COLLAPSEALL)		ExpandAllPages(FALSE);

	//PopupMenu command ExpandPage
	else if (LOWORD(wParam)>=RC_IDM_STARTPAGES
		&&	 LOWORD(wParam)<RC_IDM_STARTPAGES+GetPagesCount())
	{
		int idx = LOWORD(wParam)-RC_IDM_STARTPAGES;
		ExpandPage(idx, !IsPageExpanded(idx) );
	}

	//Button command
	else if (HIWORD(wParam)==BN_CLICKED)
	{
		int idx = GetPageIdxFromButtonHWND((HWND)lParam);
		if (idx!=-1) {
			RC_PAGEINFO* pi = m_PageList[idx];
			ExpandPage(idx, !pi->bExpanded);
			return 0;
		}
	}

	return CWnd::OnCommand(wParam, lParam);
}

//---------------------------------------------------------------------------
// OnPaint
//---------------------------------------------------------------------------
void CRollupCtrl::OnPaint() 
{
	CPaintDC dc(this);

	//Draw ScrollBar
	CRect r; GetClientRect(&r);
	dc.FillSolidRect(&r, GetSysColor(COLOR_BTNFACE));

	CRect br = CRect(r.right-RC_SCROLLBARWIDTH,r.top, r.right, r.bottom);
	dc.DrawEdge(&br, EDGE_RAISED, BF_RECT  );

	int SB_Pos	= 0;
	int SB_Size = 0;
	int ClientHeight = r.Height()-4;

	if (m_nPageHeight>r.Height()) {
		SB_Size = ClientHeight-(((m_nPageHeight-r.Height())*ClientHeight)/m_nPageHeight);
		SB_Pos	= -(m_nStartYPos*ClientHeight)/m_nPageHeight;
	} else {
		SB_Size = ClientHeight;
	}

	br.left		+=2;
	br.right	-=1;
	br.top		= SB_Pos+2;
	br.bottom	= br.top+SB_Size;

	dc.FillSolidRect(&br, RC_SCROLLBARCOLOR);
	dc.FillSolidRect(CRect(br.left,2,br.right,br.top), RGB(0,0,0));
	dc.FillSolidRect(CRect(br.left,br.bottom,br.right,2+ClientHeight), RGB(0,0,0));

	// Do not call CWnd::OnPaint() for painting messages
}

//---------------------------------------------------------------------------
// OnSize
//---------------------------------------------------------------------------
void CRollupCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	RecalLayout();
}

//---------------------------------------------------------------------------
// OnLButtonDown
//---------------------------------------------------------------------------
void CRollupCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect r; GetClientRect(&r);
	if (m_nPageHeight<=r.Height())		return;	//Can't Scroll

	CRect br = CRect(r.right-RC_SCROLLBARWIDTH,r.top, r.right, r.bottom);

	if ((nFlags&MK_LBUTTON) && br.PtInRect(point)) {

		SetCapture();

		int ClientHeight = r.Height()-4;

		int SB_Size = ClientHeight-(((m_nPageHeight-r.Height())*ClientHeight)/m_nPageHeight);
		int	SB_Pos	= -(m_nStartYPos*ClientHeight)/m_nPageHeight;

		//Click inside scrollbar cursor
		if ((point.y<(SB_Pos+SB_Size)) && (point.y>SB_Pos)) {

			m_nSBOffset = SB_Pos-point.y+1;
		
		//Click outside scrollbar cursor (2 cases => above or below cursor)
		} else {
			int distup	= point.y-SB_Pos;	
			int distdown= (SB_Pos+SB_Size)-point.y;
			if (distup<distdown)	m_nSBOffset = 0;		//above
			else					m_nSBOffset = -SB_Size;	//below
		}

		//Calc new m_nStartYPos from mouse pos
		int TargetPos	= point.y + m_nSBOffset;
		m_nStartYPos=-(TargetPos*m_nPageHeight)/ClientHeight;

		//Update
		RecalLayout();
	}


	CWnd::OnLButtonDown(nFlags, point);
}

//---------------------------------------------------------------------------
// OnLButtonUp
//---------------------------------------------------------------------------
void CRollupCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (GetCapture()==this)		ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}


//---------------------------------------------------------------------------
// OnMouseMove
//---------------------------------------------------------------------------
void CRollupCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect r; GetClientRect(&r);
	if (m_nPageHeight<=r.Height())		return;	//Can't Scroll

	CRect br = CRect(r.right-RC_SCROLLBARWIDTH,r.top, r.right, r.bottom);

	if ((nFlags&MK_LBUTTON) && (GetCapture()==this)) {

		//Calc new m_nStartYPos from mouse pos
		int ClientHeight	= r.Height()-4;
		int TargetPos		= point.y + m_nSBOffset;
		m_nStartYPos=-(TargetPos*m_nPageHeight)/ClientHeight;

		//Update
		RecalLayout();
	}

	CWnd::OnMouseMove(nFlags, point);
}


//---------------------------------------------------------------------------
// OnMouseWheel
//---------------------------------------------------------------------------
BOOL CRollupCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	//Calc new m_nStartYPos
	m_nStartYPos+=(zDelta/4);

	//Update
	RecalLayout();

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

//---------------------------------------------------------------------------
// OnMouseActivate
//---------------------------------------------------------------------------
int CRollupCtrl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	SetFocus();
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


//---------------------------------------------------------------------------
// OnContextMenu
//---------------------------------------------------------------------------
void CRollupCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;
	if (menu.CreatePopupMenu())
	{
		menu.AppendMenu(MF_STRING,		RC_IDM_EXPANDALL,	"Expand all"	);
		menu.AppendMenu(MF_STRING,		RC_IDM_COLLAPSEALL,	"Collapse all"	);
		menu.AppendMenu(MF_SEPARATOR,	0,					""				);

		//Add all pages with checked style for expanded ones
		for (int i=0; i<m_PageList.GetSize(); i++) {
			CString cstrPageName;
			m_PageList[i]->pwndButton->GetWindowText(cstrPageName);
			menu.AppendMenu(MF_STRING, RC_IDM_STARTPAGES+i, cstrPageName);	
			if (m_PageList[i]->bExpanded)
				menu.CheckMenuItem(RC_IDM_STARTPAGES+i, MF_CHECKED);
		}

		menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, this);
	}
}
