#if !defined(AFX_COOLSCROLL_H__1A639938_D35E_4848_9E65_C36511C3A134__INCLUDED_)
#define AFX_COOLSCROLL_H__1A639938_D35E_4848_9E65_C36511C3A134__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CoolScroll.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCoolScroll window

class CCoolScroll : public CStatic
{
// Construction
public:
	CCoolScroll();
	
	int tbSize,tbPos,tbLength;
	BOOL Moving;
	CPoint clpt;
	int clVal,tbPos2;
	HWND daPlug;
// Attributes
public:
	void SetPlug(HWND dahwnd,CWnd *Parent);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoolScroll)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCoolScroll();

	// Generated message map functions
public:
	//{{AFX_MSG(CCoolScroll)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLSCROLL_H__1A639938_D35E_4848_9E65_C36511C3A134__INCLUDED_)
