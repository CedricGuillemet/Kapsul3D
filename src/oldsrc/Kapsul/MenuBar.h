#if !defined(AFX_MENUBAR_H__02D8B982_4869_11D3_8D37_C0620A1F032F__INCLUDED_)
#define AFX_MENUBAR_H__02D8B982_4869_11D3_8D37_C0620A1F032F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MenuBar.h : header file
//
#include <afxtempl.h>
#include <afxpriv.h>
#include "Subclass.h"

//////////////////////////////////////////////////////////////////////
// CMenuBar class version 2.12
//		simulates a Dev Studio style dockable menu bar.
//		based on PixieLib written by Paul DiLascia<www.dilascia.com>
//
// version history
//		2.12 : support OLE menu carelessly.
//		2.11 : WindowMenu fixed by VORGA.
//		2.10 : CMenuDockBar's problem fixed again and again.
//		2.08 : give up precise ComputeMenuTrackPoint
//		2.07 : Sychronizing with frame activation problem fixed
//		2.06 : CMenuItem::ComputeMenuTrackPoint fixed a little
//		2.05 : CMenuDockBar fixed
//			 : Inactive state problem fixed
//		2.04 : bug with ::TrackPopupEx carelessly fixed 
//           : synchronizing TrackPopup animation with win98 effect
//
//						written by MB <mb2@geocities.co.jp> 1999.11.27
//////////////////////////////////////////////////////////////////////
// CMenuItem interface
class CMenuItem
{
// Construction
public:
	CMenuItem();

// Attributes
	BYTE GetStyle() const { return m_fsStyle; }
	void ModifyState(BYTE fsRemove, BYTE fsAdd);
	BYTE GetState() const { return m_fsState; }
	CSize GetHorizontalSize() const;
	CRect GetRect() const { return m_rcItem; }
	TCHAR GetAccessKey() const { return m_cAccessKey; }

// Overidables
	virtual void Update(CDC*) = 0;
	virtual void Layout(CPoint, BOOL bHorz) = 0;
	virtual void TrackPopup(CWnd* pBar, CWnd* pWndSentCmd) = 0;

// Implementation
public:
	virtual ~CMenuItem() { }

protected:
	BYTE m_fsStyle;    // menu item style
	BYTE m_fsState;    // menu item state
	CRect m_rcItem;    // current rect
	CSize m_sizeHorz;  // ordinary horizontal size
	TCHAR m_cAccessKey;// access key (Alt key + X)
};
// CMenuItem style flags
#define MISTYLE_TRACKABLE		0x01
#define MISTYLE_WRAPPABLE		0x02
// CMenuItem state flags
#define MISTATE_HOT             0x01
#define MISTATE_PRESSED         0x02
#define MISTATE_HORZ            0x04
#define MISTATE_HIDDEN          0x08
#define MISTATE_WRAP            0x10
#define MISTATE_INACTIVE		0x20

//////////////////////////////////////////////////////////////////////
// CMenuButton class
class CMenuButton : public CMenuItem  
{
// Construction
public:
	CMenuButton(HMENU hMenu, int nIndex);

// Overidables
	virtual void Update(CDC*);
	virtual void Layout(CPoint, BOOL bHorz);
	virtual void TrackPopup(CWnd* pBar, CWnd* pWndSentCmd);

// Implementation
public:
	virtual ~CMenuButton() { }

private:
	CString m_strBtn;                // string on button
	CPoint  m_ptLineFrom, m_ptLineTo;// vertical line point on button
	HMENU   m_hSubMenu;              // handle to sub menu
	UINT    m_nID;                   // Item ID (if no sub menu)

	// Implementation helper
	// used on Update
	void DrawHot(CDC*);
	void DrawPressed(CDC*);
	void DrawNone(CDC*);
	void DrawHorzText(CDC*, CPoint ptOffset = CPoint(0, 0));
	void DrawVertText(CDC*, CPoint ptOffset = CPoint(0, 0));
	// used on constructing
	void InitButtonStringAndSubMenuHandle(HMENU hMenu, int nIndex);
	void InitHorizontalButtonSize();
	void InitAccessKeyAndVerticalLinePoint();
};

//////////////////////////////////////////////////////////////////////
// CMenuIcon class
class CMenuIcon : public CMenuItem  
{
// Construction
public:
	CMenuIcon(CWnd* pMenuBar);

// Operations
	void OnActivateChildWnd();
	
// Overidables
	virtual void Update(CDC*);
	virtual void Layout(CPoint, BOOL bHorz);
	virtual void TrackPopup(CWnd* pBar, CWnd* pWndSentCmd);

// Implementation
public:
	virtual ~CMenuIcon();

private:
	CWnd* m_pMenuBar;
	HICON m_hDocIcon;
	HICON m_hIconWinLogo;// used on View which has no own Doc icon
};

//////////////////////////////////////////////////////////////////////
// CMenuControl class
class CMenuControl : public CMenuItem  
{
// Construction
public:
	CMenuControl(CWnd* pMenuBar);

// Operations
	void OnActivateChildWnd();
	BOOL OnMouseMsg(UINT msg, UINT nFlags, CPoint pt);
	void ForceDrawControl(CDC*);
	void DelayLayoutAndDraw(CDC* pDC, CSize sizeBar);
	
// Overidables
	virtual void Update(CDC*);
	virtual void Layout(CPoint, BOOL bHorz);
	virtual void TrackPopup(CWnd* pBar, CWnd* pWndSentCmd) { ASSERT(TRUE); }

// Implementation
public:
	virtual ~CMenuControl() { }

private:
	CWnd* m_pMenuBar;
	CRect m_arrCaption[3];
	BOOL  m_bDown;
	int	  m_nTracking;

	// Implementation helper
	void DrawControl(CDC*, int nIndex, BOOL bDown);
	int HitTest(CPoint point);
	CSize GetCaptionSize();
};

/////////////////////////////////////////////////////////////////////////////
// CMenuBarFrameHook
class CMenuBar;

class CMainFrameHook : public CSubclassWnd
{
public:
	CMainFrameHook();
	BOOL Install(CMenuBar* pMenuBar, HWND hWndToHook);
	virtual ~CMainFrameHook();

protected:
	virtual LRESULT WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);

private:
	CMenuBar* m_pMenuBar;
};

class CMDIClientHook : public CSubclassWnd
{
public:
	CMDIClientHook();
	BOOL Install(CMenuBar* pMenuBar, HWND hWndToHook);
	virtual ~CMDIClientHook();

protected:
	virtual LRESULT WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);

private:
	CMenuBar* m_pMenuBar;
};

/////////////////////////////////////////////////////////////////////////////
// CMenuBar 

#if _MFC_VER >= 0x0600
#define AFX_IDW_MENUBAR			0xE806  // Menu bar
#else
#define AFX_IDW_MENUBAR			0xE804  // Menu bar
#define CBRS_GRIPPER			0x00400000L
#endif

#define CBRS_RAISEDBORDER		0x01000000L

class /*AFX_EXT_CLASS*/ CMenuBar : public CControlBar
{
	DECLARE_DYNAMIC(CMenuBar)
// Constructors
public:
	CMenuBar();
	BOOL Create(CWnd* pParentWnd,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
		UINT nID = AFX_IDW_MENUBAR);
	BOOL CreateEx(CWnd* pParentWnd,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
		CRect rcBorders = CRect(0, 0, 0, 0),
		UINT nID = AFX_IDW_MENUBAR);

	BOOL LoadMenuBar(UINT nIDResource);
	HMENU LoadMenu(HMENU hMenu, HMENU hMenuWindow);

// Operations
public:
	BOOL TranslateFrameMessage(MSG* pMsg);
	void EnableDockingEx(DWORD dwStyle);
	static const UINT WM_GETMENU;
	
// Overidables
	//{{AFX_VIRTUAL(CMenuBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMenuBar();
	virtual void DoPaint(CDC* pDC);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);

// Generated message map functions
protected:
	//{{AFX_MSG(CMenuBar)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnSetMenuNull(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSettingChange(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	// for message hook
	void OnMenuSelect(HMENU hMenu, UINT nIndex);
	void OnSetMenu(HMENU hNewMenu, HMENU hWindowMenu);
	void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	void OnFrameNcActivate(BOOL bActive);

protected:
	// Implementation helper
	enum TrackingState { none = 0, button, popup, buttonmouse };
	void UpdateBar(TrackingState nState = none, int nNewIndex = -1);

	// layout
	CSize CalcLayout(DWORD nMode, int nLength = -1);
	CSize CalcSize(int nCount);
	int WrapMenuBar(int nCount, int nWidth);
	void SizeMenuBar(int nLength, BOOL bVert = FALSE);
	void Layout(); // called for for delayed button layout
	void CalcItemLayout(int nCount, BOOL bVert = FALSE);
	CSize CalcVertDockSize(int nCount);
	int GetClipBoxLength(BOOL bHorz);

	// draw
	void RefreshBar();
	void EraseNonClientEx();
	void DrawRaisedBorders(CDC*, CRect&);
	// won't use MFC6 functions
	void _DrawGripper(CDC* pDC, const CRect& rect);
	void _CalcInsideRect(CRect& rect, BOOL bHorz) const;

	// Items
	BOOL InitItems();
	void DeleteItems();
	int GetItemCount() const { return m_arrItem.GetSize(); }
	BOOL IsValidIndex(int nIndex) const { return 0 <= nIndex && nIndex < GetItemCount(); }
	BOOL MapAccessKey(TCHAR cKey, int& nIndex);
	int HitTestOnTrack(CPoint point);

	// system hook
	static LRESULT CALLBACK MenuInputFilter(int code, WPARAM wParam, LPARAM lParam);
	BOOL OnMenuInput(MSG&);

	// popup
	void TrackPopup(int nIndex);
	int GetNextOrPrevButton(int nIndex, BOOL bPrev);

	void CheckActiveChildWndMaximized();
	HWND GetActiveChildWnd(BOOL& bMaximized);

#if _MFC_VER < 0x0600
	void SetBorders(int cxLeft, int cyTop, int cxRight, int cyBottom);
	void SetBorders(LPCRECT lpRect)
	{ SetBorders(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom); }
#endif

private:
	// used for important functions
	BOOL m_bLoop;
	int  m_nCurIndex;
	BOOL m_bIgnoreAlt;
	TrackingState m_nTrackingState;
	CArray<CMenuItem*, CMenuItem*> m_arrItem;
public:	
	HMENU m_hMenu;// CMenu object is unavaiable, cause we have to share menu with MFC in MDI app.

	CPoint m_ptMouse;// cursor position while hooking
	BOOL   m_bProcessRightArrow, m_bProcessLeftArrow;
	UINT   m_nIDEvent;// Timer ID for mouse moving away

	CMainFrameHook m_hookFrame;
	BOOL m_bFrameActive;// synchronize with Frame Activation

	CMDIClientHook m_hookMDIClient;
	BOOL m_bMDIApp;// this is a MDI application?
	HWND m_hWndMDIClient;
	CMenuControl* m_pMenuControl;
	CMenuIcon* m_pMenuIcon;
	BOOL m_bMDIMaximized;
	HMENU m_hWindowMenu;
	HWND m_hWndActiveChild;

	BOOL m_bDelayedButtonLayout;// what is this?
	DWORD m_dwExStyle;// my service

	friend class CMainFrameHook;
	friend class CMDIClientHook;

	// for OLE menu
	HWND OleMenuDescriptor(BOOL& bSend, UINT nMsg, WPARAM wParam, LPARAM lParam);
	CWnd* GetCmdSentOleWnd();
};

/////////////////////////////////////////////////////////////////////////////
// CMenuDocBar 
//     for insisting its own line on DockBar
// I'm afraid this trick will make some problems.

class CMenuDockBar : public CDockBar  
{
public:
	CMenuDockBar() { }

protected:
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);

public:
	virtual ~CMenuDockBar() { }
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++

#endif // !defined(AFX_MENUBAR_H__02D8B982_4869_11D3_8D37_C0620A1F032F__INCLUDED_)
